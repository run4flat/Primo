/*-
 * Copyright (c) 1997-2002 The Protein Laboratory, University of Copenhagen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#include "apricot.h"
#include "Widget.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef  my
#define inherited CDrawable
#define my  ((( PWidget) self)-> self)
#define var (( PWidget) self)
#define his (( PWidget) child)

void Widget_pack_slaves( Handle self); 
void Widget_place_slaves( Handle self); 
Bool Widget_size_notify( Handle self, Handle child, const Rect* metrix);
Bool Widget_move_notify( Handle self, Handle child, Point * moveTo);
static void Widget_pack_enter( Handle self); 
static void Widget_pack_leave( Handle self); 
static void Widget_place_enter( Handle self); 
static void Widget_place_leave( Handle self); 

/*
   geometry managers.

   growMode - native Prima model, borrowed from TurboVision. Does not live with
              geomSize request size, uses virtualSize instead.

   pack and place - copy-pasted from Perl-Tk.  
   
  */

/*
pack Handle fields:

   next       - available only when geometry == gtPack
   order, in  - available always, but is guaranteedly valid when geometry == gtPack only

   in and order cause croaks when submitted via packInfo(), but are silently
   converted to nil when geometry changes and the references are not valid anymore

*/


#define MASTER      ((var->geometry != gtGrowMode && var->geomInfo.in)?var->geomInfo.in:var->owner)
#define geometry_reset_all() geometry_reset(MASTER,-1)
                     

/* resets particular ( or all, if geometry < 0 ) geometry widgets */

static void
geometry_reset( Handle self, int geometry)
{
}

int
Widget_geometry( Handle self, Bool set, int geometry)
{
   if ( !set)
      return var-> geometry;
   if ( geometry == var-> geometry) {
      /* because called within set_owner() */
      if ((var-> geometry == gtGrowMode) && (var-> growMode & gmCenter)) 
         my-> set_centered( self, var-> growMode & gmXCenter, var-> growMode & gmYCenter);
      return geometry;
   }

   if ( geometry < gtDefault || geometry > gtMax)
      croak("Prima::Widget::geometry: invalid value passed");
   
   switch ( var-> geometry) {
   case gtPlace:
      Widget_place_leave( self);
      break;
   case gtPack:
      Widget_pack_leave( self);
      break;
   }
   var-> geometry = geometry;
   switch ( var-> geometry) {
   case gtGrowMode:
      if ( var-> growMode & gmCenter)
         my-> set_centered( self, var-> growMode & gmXCenter, var-> growMode & gmYCenter);
      break;
   case gtPlace:
      Widget_place_enter( self);
      break;
   case gtPack:
      Widget_pack_enter( self);
      break;
   }
   geometry_reset_all();
   return var-> geometry;
}

Point
Widget_geomSize( Handle self, Bool set, Point geomSize)
{
   if ( !set)
      return var-> geomSize;
      /* return ( var-> geometry == gtDefault) ? my-> get_size(self) : var-> geomSize; */
   var-> geomSize = geomSize;
   if ( var-> geometry == gtDefault) 
      my-> set_size( self, var-> geomSize);
   else
      geometry_reset_all();
   return var-> geomSize;
}

int
Widget_geomHeight( Handle self, Bool set, int geomHeight)
{
   if ( set) {
      Point p = { var-> geomSize. x, geomHeight};
      my-> set_geomSize( self, p);
   }
   return var-> geomSize. y;
}

int
Widget_geomWidth( Handle self, Bool set, int geomWidth)
{
   if ( set) {
      Point p = { geomWidth, var-> geomSize. y};
      my-> set_geomSize( self, p);
   }
   return var-> geomSize. x;
}

Bool
Widget_packPropagate( Handle self, Bool set, Bool propagate)
{
   return false;
}

void
Widget_reset_children_geometry( Handle self)
{
}

/* checks if Handle in is allowed to be a master for self -
   used for gt::Pack */
static Handle
Widget_check_in( Handle self, Handle in, Bool barf)
{
   Handle h = in;

   /* check overall validity */
   if ( !in || !kind_of( in, CWidget)) {
      if ( barf)
         croak("%s: invalid 'in': not a widget", "RTC008F: Prima::Widget::pack");
      else
         return nilHandle;
   }

   /* check direct inheritance */
   while ( h) {
      if ( h == self) {
         if ( barf)
            croak("%s: invalid 'in': is already a child", "RTC008F: Prima::Widget::pack");
         else
            return nilHandle;
      }
      h = PWidget( h)-> owner;
   }

   /* check slaves chain */
   h = PWidget( in)-> packSlaves;
   while ( h) {
      if ( h == in) {
         if ( barf)
            croak("%s: invalid 'in': already a pack slave", "RTC008F: Prima::Widget::pack");
         else
            return nilHandle;
      }
      h = PWidget( h)-> geomInfo. next;
   }
   
   h = PWidget( in)-> placeSlaves;
   while ( h) {
      if ( h == in) {
         if ( barf)
            croak("%s: invalid 'in': already a place slave", "RTC008F: Prima::Widget::pack");
         else
            return nilHandle;
      }
      h = PWidget( h)-> geomInfo. next;
   }

   /* place to check other chains if needed */

   return in;
}

Point
Widget_sizeMin( Handle self, Bool set, Point min)
{
   if ( !set)
      return var-> sizeMin;
   var-> sizeMin = min;
   if ( var-> stage <= csFrozen) {
      Point sizeActual  = my-> get_size( self);
      Point newSize     = sizeActual;
      if ( sizeActual. x < min. x) newSize. x = min. x;
      if ( sizeActual. y < min. y) newSize. y = min. y;
      if (( newSize. x != sizeActual. x) || ( newSize. y != sizeActual. y))
         my-> set_size( self, newSize);
      if ( var-> geometry != gtDefault)
         geometry_reset_all();
   }
   apc_widget_set_size_bounds( self, var-> sizeMin, var-> sizeMax);
   return min;
}

Point
Widget_sizeMax( Handle self, Bool set, Point max)
{
   if ( !set)
      return var-> sizeMax;
   var-> sizeMax = max;
   if ( var-> stage <= csFrozen) {
      Point sizeActual  = my-> get_size( self);
      Point newSize     = sizeActual;
      if ( sizeActual. x > max. x) newSize. x = max. x;
      if ( sizeActual. y > max. y) newSize. y = max. y;
      if (( newSize. x != sizeActual. x) || ( newSize. y !=  sizeActual. y))
          my-> set_size( self, newSize);
      if ( var-> geometry != gtDefault)
         geometry_reset_all();
   }
   apc_widget_set_size_bounds( self, var-> sizeMin, var-> sizeMax);
   return max;
}


/* geometry managers */

/* gtGrowMode */

Bool
Widget_size_notify( Handle self, Handle child, const Rect* metrix)
{
   return false;
}

Bool
Widget_move_notify( Handle self, Handle child, Point * moveTo)
{
   return false;
}

/*
    PACK
*/    

#define LEFT    0
#define BOTTOM  1
#define RIGHT   2
#define TOP     3

#define SOUTH   0
#define NORTH   2
#define WEST    0
#define EAST    2
#define CENTER  1

/* pack() internal mechanism - stolen from Tk v800.24, tkPack.c 
   Note that the original algorithm is taught to respect sizeMin
   and sizeMax, not present in Tk */

/*
 *----------------------------------------------------------------------
 *
 * XExpansion --
 *
 *	Given a list of packed slaves, the first of which is packed
 *	on the left or right and is expandable, compute how much to
 *	expand the child.
 *
 * Results:
 *	The return value is the number of additional pixels to give to
 *	the child.
 *
 *----------------------------------------------------------------------
 */

static int
slave_width( register PWidget slavePtr, register int plus)
{
   register int width = slavePtr-> geomSize. x + slavePtr-> geomInfo. pad.x + 
                        slavePtr-> geomInfo. ipad.x + plus;
   if ( width < slavePtr-> sizeMin.x) width = slavePtr-> sizeMin.x;
   if ( width > slavePtr-> sizeMax.x) width = slavePtr-> sizeMax.x;
   return width;
}

static int
slave_height( register PWidget slavePtr, register int plus)
{
   register int height = slavePtr-> geomSize.y + slavePtr-> geomInfo. pad.y + 
                        slavePtr-> geomInfo. ipad.y + plus;
   if ( height < slavePtr-> sizeMin.y) height = slavePtr-> sizeMin.y;
   if ( height > slavePtr-> sizeMax.y) height = slavePtr-> sizeMax.y;
   return height;
}

static int
XExpansion(slavePtr, cavityWidth)
    register PWidget slavePtr;		        /* First in list of remaining slaves. */
    int cavityWidth;			/* Horizontal space left for all
					 * remaining slaves. */
{
    int numExpand, minExpand, curExpand;
    int childWidth;

    /*
     * This procedure is tricky because windows packed top or bottom can
     * be interspersed among expandable windows packed left or right.
     * Scan through the list, keeping a running sum of the widths of
     * all left and right windows (actually, count the cavity space not
     * allocated) and a running count of all expandable left and right
     * windows.  At each top or bottom window, and at the end of the
     * list, compute the expansion factor that seems reasonable at that
     * point.  Return the smallest factor seen at any of these points.
     */

    minExpand = cavityWidth;
    numExpand = 0;
    for (; slavePtr != NULL;
        slavePtr = ( PWidget) slavePtr-> geomInfo. next) {
	childWidth = slave_width(slavePtr, 0);
	if ((slavePtr-> geomInfo. side == TOP) || (slavePtr-> geomInfo. side == BOTTOM)) {
	    curExpand = (cavityWidth - childWidth)/numExpand;
	    if (curExpand < minExpand) {
		minExpand = curExpand;
	    }
	} else {
	    cavityWidth -= childWidth;
	    if (slavePtr->geomInfo. expand) {
		numExpand++;
	    }
	}
    }
    curExpand = cavityWidth/numExpand;
    if (curExpand < minExpand) {
	minExpand = curExpand;
    }
    return (minExpand < 0) ? 0 : minExpand;
}
/*
 *----------------------------------------------------------------------
 *
 * YExpansion --
 *
 *	Given a list of packed slaves, the first of which is packed
 *	on the top or bottom and is expandable, compute how much to
 *	expand the child.
 *
 * Results:
 *	The return value is the number of additional pixels to give to
 *	the child.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

static int
YExpansion(slavePtr, cavityHeight)
    register PWidget slavePtr;	        /* First in list of remaining
					 * slaves. */
    int cavityHeight;			/* Vertical space left for all
					 * remaining slaves. */
{
    int numExpand, minExpand, curExpand;
    int childHeight;

    /*
     * See comments for XExpansion.
     */

    minExpand = cavityHeight;
    numExpand = 0;
    for (; slavePtr != NULL; slavePtr = (PWidget) slavePtr->geomInfo. next) {
	childHeight = slave_height(slavePtr, 0);
	if ((slavePtr-> geomInfo. side == LEFT) || (slavePtr-> geomInfo. side == RIGHT)) {
	    curExpand = (cavityHeight - childHeight)/numExpand;
	    if (curExpand < minExpand) {
		minExpand = curExpand;
	    }
	} else {
	    cavityHeight -= childHeight;
	    if (slavePtr-> geomInfo. expand) {
		numExpand++;
	    }
	}
    }
    curExpand = cavityHeight/numExpand;
    if (curExpand < minExpand) {
	minExpand = curExpand;
    }
    return (minExpand < 0) ? 0 : minExpand;
}

void
Widget_pack_slaves( Handle self)
{
}

/* applies pack parameters and enters pack slaves chain */

void
Widget_pack_enter( Handle self)
{
}

/* removes widget from list of pack slaves */
void
Widget_pack_leave( Handle self)
{
}

SV * 
Widget_packInfo( Handle self, Bool set, SV * packInfo)
{
   if ( !set) {
      HV * profile = newHV();
      GeomInfo *p = &var-> geomInfo;

      switch ( p-> side) {
      case LEFT   : pset_c( side, "top");    break;
      case BOTTOM : pset_c( side, "bottom"); break;
      case RIGHT  : pset_c( side, "right");  break;
      case TOP    : pset_c( side, "top");    break;
      }

      if ( p-> fillx) {
         pset_c( fill, p-> filly ? "both" : "x");
      } else {
         pset_c( fill, p-> filly ? "y" : "none");
      }

      pset_i( expand, p-> expand);

      switch ( p-> anchorx) {
      case WEST:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "nw" : (( p-> anchory == CENTER) ? "w" : "sw"))
               );
         break;
      case CENTER:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "n" : (( p-> anchory == CENTER) ? "center" : "s"))
               );
         break;
      case EAST:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "ne" : (( p-> anchory == CENTER) ? "e" : "se"))
               );
         break;
      }

      pset_H( after,  ( p-> order && p-> after)  ? p-> order : nilHandle);
      pset_H( before, ( p-> order && !p-> after) ? p-> order : nilHandle);
      pset_H( in, var-> geomInfo. in);
      
      pset_i( ipadx, p-> ipad. x);
      pset_i( ipady, p-> ipad. y);
      pset_i( padx, p-> pad. x);
      pset_i( pady, p-> pad. y);
      
      return newRV_noinc(( SV *) profile);
   } else {
      dPROFILE;
      HV * profile;
      Bool reset_zorder = false, set_in = false;
      Handle in = nilHandle;

      if ( SvTYPE(packInfo) == SVt_NULL) return nilSV;
      
      if ( !SvOK(packInfo) || !SvROK(packInfo) || SvTYPE(SvRV(packInfo)) != SVt_PVHV)
         croak("Widget::packInfo: parameter is not a hash");

      profile = ( HV*) SvRV( packInfo);
      if ( pexist( side)) {
         char * c = pget_c( side);
         if ( *c == 'l' && (strcmp( c, "left")==0))   var-> geomInfo. side = LEFT; else
         if ( *c == 'b' && (strcmp( c, "bottom")==0)) var-> geomInfo. side = BOTTOM; else
         if ( *c == 'r' && (strcmp( c, "right")==0))  var-> geomInfo. side = RIGHT; else
         if ( *c == 't' && (strcmp( c, "top")==0))    var-> geomInfo. side = TOP; else
            croak("%s: invalid 'side'", "RTC008F: Prima::Widget::pack");
      }

      if ( pexist( fill)) {
         char * c = pget_c( fill);
         if (( strcmp( c, "x") == 0)) {
            var-> geomInfo. fillx = 1; 
            var-> geomInfo. filly = 0; 
         } else if (( strcmp( c, "y") == 0)) {
            var-> geomInfo. fillx = 0; 
            var-> geomInfo. filly = 1; 
         } else if ( *c == 'n' && ( strcmp( c, "none") == 0)) {
            var-> geomInfo. fillx = 
            var-> geomInfo. filly = 0; 
         } else if ( *c == 'b' && ( strcmp( c, "both") == 0)) {
            var-> geomInfo. fillx = 
            var-> geomInfo. filly = 1; 
         } else
            croak("%s: invalid 'fill'", "RTC008F: Prima::Widget::pack");
      }
      
      if ( pexist( expand)) {
         var-> geomInfo. expand = pget_B( expand);
      }

      if ( pexist( anchor)) {
         char * c = pget_c( anchor);
         if (( strcmp( c, "n") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = NORTH;
         } else if (( strcmp( c, "ne") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = NORTH;
         } else if (( strcmp( c, "e") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = CENTER;
         } else if (( strcmp( c, "se") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "s") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "sw") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "w") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = CENTER;
         } else if (( strcmp( c, "nw") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = NORTH;
         } else if ( *c == 'c' && ( strcmp( c, "center") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = CENTER;
         } else
            croak("%s: invalid 'anchor'", "RTC008F: Prima::Widget::pack");
      }

      if ( pexist( ipadx)) var-> geomInfo. ipad. x = pget_i( ipadx);
      if ( pexist( ipady)) var-> geomInfo. ipad. y = pget_i( ipady);
      if ( pexist( padx))  var-> geomInfo. pad. x  = pget_i( padx);
      if ( pexist( pady))  var-> geomInfo. pad. y  = pget_i( pady);

      if ( pexist( after)) {
         SV * sv = pget_sv( after);
         if ( SvTYPE(sv) != SVt_NULL) {
            if ( !( var-> geomInfo. order = gimme_the_mate( sv)))
               croak("%s: invalid 'after'", "RTC008F: Prima::Widget::pack");
            var-> geomInfo. after = 1;
            if ( pexist( before)) {
               sv = pget_sv( before);
               if ( SvTYPE(sv) != SVt_NULL)
                  croak("%s: 'after' and 'before' cannot be present simultaneously", "RTC008F: Prima::Widget::pack");
            }
         } else {
            var-> geomInfo. order = nilHandle;
            var-> geomInfo. after = 0;
         }
         reset_zorder = true;
      } else if ( pexist( before)) {
         SV * sv = pget_sv( before);
         if ( SvTYPE(sv) != SVt_NULL) {
            if ( !( var-> geomInfo. order = gimme_the_mate( sv)))
               croak("%s: invalid 'before'", "RTC008F: Prima::Widget::pack");
         } else
            var-> geomInfo. order = nilHandle;
         var-> geomInfo. after = 0;
         reset_zorder = true;
      }

      if ( pexist( in)) {
         SV * sv = pget_sv( in);
         in = nilHandle;
         if ( SvTYPE( sv) != SVt_NULL)
            in = Widget_check_in( self, gimme_the_mate( sv), true);
         set_in = reset_zorder = true;
      }

      if ( var-> geometry == gtPack) {
         if ( reset_zorder) 
            Widget_pack_leave( self);
      }
      if ( set_in) var-> geomInfo. in = in;
      if ( var-> geometry == gtPack) {
         if ( reset_zorder) 
            Widget_pack_enter( self);
         geometry_reset( MASTER, gtPack);
      }
   }
   return nilSV;
}

XS( Widget_get_pack_slaves_FROMPERL)
{
   dXSARGS;
   Handle self;

   if ( items != 1)
      croak ("Invalid usage of Widget.get_pack_slaves");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Widget.get_pack_slaves");
   self = var-> packSlaves;
   while ( self) {
      XPUSHs( sv_2mortal( newSVsv((( PAnyObject) self)-> mate)));
      self = var-> geomInfo. next;
   }
   PUTBACK;
   return;
}


void Widget_get_pack_slaves          ( Handle self) {}
void Widget_get_pack_slaves_REDEFINED( Handle self) {}

/* 
  PLACE   
 */
/* place internal mechanism - stolen from Tk v800.24, tkPlace.c */

void
Widget_place_enter( Handle self)
{
}

/* removes widget from list of place slaves */
void
Widget_place_leave( Handle self)
{
}

void
Widget_place_slaves( Handle self)
{
}


SV * 
Widget_placeInfo( Handle self, Bool set, SV * placeInfo)
{
   if ( !set) {
      HV * profile = newHV();
      GeomInfo *p = &var-> geomInfo;

      switch ( p-> anchorx) {
      case WEST:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "nw" : (( p-> anchory == CENTER) ? "w" : "sw"))
               );
         break;
      case CENTER:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "n" : (( p-> anchory == CENTER) ? "center" : "s"))
               );
         break;
      case EAST:
         pset_c( anchor, 
                 (( p-> anchory == NORTH) ? "ne" : (( p-> anchory == CENTER) ? "e" : "se"))
               );
         break;
      }

      pset_H( in, var-> geomInfo. in);
      
      if ( p-> use_x)   pset_i( x, p-> x);
      if ( p-> use_y)   pset_i( y, p-> y);
      if ( p-> use_w)   pset_i( width,  var-> geomSize. x);
      if ( p-> use_h)   pset_i( height, var-> geomSize. y);
      if ( p-> use_rx)  pset_f( relx, p-> relX);
      if ( p-> use_ry)  pset_f( rely, p-> relY);
      if ( p-> use_rw)  pset_f( relwidth, p-> relWidth);
      if ( p-> use_rh)  pset_f( relheight, p-> relHeight);
      
      return newRV_noinc(( SV *) profile);
   } else {
      dPROFILE;
      HV * profile;
      Handle in = nilHandle;
      Bool set_in = false;

      if ( SvTYPE(placeInfo) == SVt_NULL) return nilSV;
      
      if ( !SvOK(placeInfo) || !SvROK(placeInfo) || SvTYPE(SvRV(placeInfo)) != SVt_PVHV)
         croak("Widget::placeInfo: parameter is not a hash");

      profile = ( HV*) SvRV( placeInfo);

      if ( pexist( anchor)) {
         char * c = pget_c( anchor);
         if (( strcmp( c, "n") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = NORTH;
         } else if (( strcmp( c, "ne") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = NORTH;
         } else if (( strcmp( c, "e") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = CENTER;
         } else if (( strcmp( c, "se") == 0)) {
            var-> geomInfo. anchorx = EAST;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "s") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "sw") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = SOUTH;
         } else if (( strcmp( c, "w") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = CENTER;
         } else if (( strcmp( c, "nw") == 0)) {
            var-> geomInfo. anchorx = WEST;
            var-> geomInfo. anchory = NORTH;
         } else if ( *c == 'c' && ( strcmp( c, "center") == 0)) {
            var-> geomInfo. anchorx = CENTER;
            var-> geomInfo. anchory = CENTER;
         } else
            croak("%s: invalid 'anchor'", "RTC008F: Prima::Widget::place");
      }

      if ( pexist( x)) {
         SV * sv = pget_sv( x);
         if (( var-> geomInfo. use_x = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. x = SvIV( sv);
      }
      if ( pexist( y)) {
         SV * sv = pget_sv( y);
         if (( var-> geomInfo. use_y = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. y = SvIV( sv);
      }
      if ( pexist( width)) {
         SV * sv = pget_sv( width);
         if (( var-> geomInfo. use_w = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomSize. x = SvIV( sv);
      }
      if ( pexist( height)) {
         SV * sv = pget_sv( height);
         if (( var-> geomInfo. use_h = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomSize. y = SvIV( sv);
      }
      if ( pexist( relx)) {
         SV * sv = pget_sv( relx);
         if (( var-> geomInfo. use_rx = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. relX = SvNV( sv);
      }
      if ( pexist( rely)) {
         SV * sv = pget_sv( rely);
         if (( var-> geomInfo. use_ry = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. relY = SvNV( sv);
      }
      if ( pexist( relwidth)) {
         SV * sv = pget_sv( relwidth);
         if (( var-> geomInfo. use_rw = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. relWidth = SvNV( sv);
      }
      if ( pexist( relheight)) {
         SV * sv = pget_sv( relheight);
         if (( var-> geomInfo. use_rh = (SvTYPE( sv) != SVt_NULL))) 
            var-> geomInfo. relHeight = SvNV( sv);
      }

      if ( pexist( in)) {
         SV * sv = pget_sv( in);
         in = nilHandle;
         if ( SvTYPE( sv) != SVt_NULL)
            in = Widget_check_in( self, gimme_the_mate( sv), true);
         set_in = true;
      }
      
      if ( var-> geometry == gtPlace) {
         if ( set_in) 
            Widget_place_leave( self);
      }
      if ( set_in) var-> geomInfo. in = in;
      if ( var-> geometry == gtPlace) {
         if ( set_in) 
            Widget_place_enter( self);
         geometry_reset( MASTER, gtPlace);
      }
   }

   return nilSV;
}

XS( Widget_get_place_slaves_FROMPERL)
{
   dXSARGS;
   int i;
   Handle self;

   if ( items != 1)
      croak ("Invalid usage of Widget.get_pack_slaves");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Widget.get_pack_slaves");
   for ( i = 0; i < var-> widgets. count; i++) {
      if ( PWidget( var-> widgets. items[i])-> geometry == gtPlace)
         XPUSHs( sv_2mortal( newSVsv((( PAnyObject)(var-> widgets. items[i]))-> mate)));
   }
   PUTBACK;
   return;
}

void Widget_get_place_slaves          ( Handle self) {}
void Widget_get_place_slaves_REDEFINED( Handle self) {}

/*  */

#ifdef __cplusplus
}
#endif

