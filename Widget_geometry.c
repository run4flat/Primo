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
   Point foo; return foo;
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
   return nilHandle;
}

Point
Widget_sizeMin( Handle self, Bool set, Point min)
{
   Point foo; return foo;
}

Point
Widget_sizeMax( Handle self, Bool set, Point max)
{
   Point foo; return foo;
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

