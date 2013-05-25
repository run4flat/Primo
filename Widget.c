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
#include "Application.h"
#include "Icon.h"
#include "Popup.h"
#include "Widget.h"
#include "Window.h"
#include <Widget.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CDrawable
#define enter_method PWidget_vmt selfvmt = ((( PWidget) self)-> self)
#define my  selfvmt
#define var (( PWidget) self)

typedef Bool ActionProc ( Handle self, Handle item, void * params);
typedef ActionProc *PActionProc;
#define his (( PWidget) child)

/* local defines */
typedef struct _SingleColor
{
   Color color;
   int   index;
} SingleColor, *PSingleColor;

static Bool find_dup_msg( PEvent event, int * cmd);
static Bool pquery ( Handle window, Handle self, void * v);
static Bool get_top_current( Handle self);
static Bool sptr( Handle window, Handle self, void * v);
static Handle find_tabfoc( Handle self);
static Bool showhint_notify ( Handle self, Handle child, void * data);
static Bool hint_notify ( Handle self, Handle child, SV * hint);

extern void Widget_pack_slaves( Handle self); 
extern void Widget_place_slaves( Handle self); 
extern Bool Widget_size_notify( Handle self, Handle child, const Rect* metrix);
extern Bool Widget_move_notify( Handle self, Handle child, Point * moveTo);

/* init, done & update_sys_handle */
void
Widget_init( Handle self, HV * profile)
{
}


void
Widget_update_sys_handle( Handle self, HV * profile)
{
}

void
Widget_done( Handle self)
{
}

/* ::a */
void
Widget_attach( Handle self, Handle objectHandle)
{
}

/*::b */
Bool
Widget_begin_paint( Handle self)
{
   return false;
}

Bool
Widget_begin_paint_info( Handle self)
{
   return false;
}


void
Widget_bring_to_front( Handle self)
{
}

/*::c */
Bool
Widget_can_close( Handle self)
{
   return false;
}

void
Widget_cleanup( Handle self)
{
}


Bool
Widget_close( Handle self)
{
   return false;
}

Bool
Widget_custom_paint( Handle self)
{
   return false;
}

/*::d */
void
Widget_detach( Handle self, Handle objectHandle, Bool kill)
{
}

/*::e */
void
Widget_end_paint( Handle self)
{
}

void
Widget_end_paint_info( Handle self)
{
}


/*::f */

SV*
Widget_fetch_resource( char *className, char *name, char *classRes, char *res, Handle owner, int resType)
{
   return nilSV;
}

Handle
Widget_first( Handle self)
{
   return nilHandle;
}

Handle
Widget_first_that( Handle self, void * actionProc, void * params)
{
   return nilHandle;
}

/*::g */

/*::h */

void Widget_handle_event( Handle self, PEvent event)
{
}

void
Widget_hide( Handle self)
{
}

void
Widget_hide_cursor( Handle self)
{
}

/*::i */
void
Widget_insert_behind ( Handle self, Handle widget)
{
}

void
Widget_invalidate_rect( Handle self, Rect rect)
{
}


Bool
Widget_is_child( Handle self, Handle owner)
{
   return false;
}

/*::j */
/*::k */
void
Widget_key_event( Handle self, int command, int code, int key, int mod, int repeat, Bool post)
{
}

/*::l */
Handle
Widget_last( Handle self)
{
   return nilHandle;
}

Bool
Widget_lock( Handle self)
{
   return false;
}

/*::m */
void
Widget_mouse_event( Handle self, int command, int button, int mod, int x, int y, Bool dbl, Bool post)
{
}

/*::n */
Handle
Widget_next( Handle self)
{
   return nilHandle;
}

static void 
fill_tab_candidates( PList list, Handle level)
{
}

Handle 
Widget_next_positional( Handle self, int dx, int dy)
{
   return nilHandle;
}

static int compare_taborders_forward( const void *a, const void *b)
{
   if ((*(PWidget*) a)-> tabOrder < (*(PWidget*) b)-> tabOrder)
      return -1; else
   if ((*(PWidget*) a)-> tabOrder > (*(PWidget*) b)-> tabOrder)
      return 1; 
   else
      return 0;
}   

static int compare_taborders_backward( const void *a, const void *b)
{
   if ((*(PWidget*) a)-> tabOrder < (*(PWidget*) b)-> tabOrder)
      return 1; else
   if ((*(PWidget*) a)-> tabOrder > (*(PWidget*) b)-> tabOrder)
      return -1; 
   else
      return 0;
}   

static int
do_taborder_candidates( Handle level, Handle who, 
     int (*compareProc)(const void *, const void *), 
     int * stage, Handle * result)
{
   int i, fsel = -1;
   PList w = &(PWidget( level)-> widgets);
   Handle * ordered;

   if ( w-> count == 0) return true;
      
   ordered = ( Handle *) malloc( w-> count * sizeof( Handle));
   if ( !ordered) return true;
   
   memcpy( ordered, w-> items, w-> count * sizeof( Handle));
   qsort( ordered, w-> count, sizeof( Handle), compareProc);

   /* finding current widget in the group */
   for ( i = 0; i < w-> count; i++) {
      Handle x = ordered[i];
      if ( CWidget( x)-> get_current( x)) {
         fsel = i;
         break;
      }   
   }   
   if ( fsel < 0) fsel = 0;
   
   for ( i = 0; i < w-> count; i++) {
      int j;
      Handle x;

      j = i + fsel;
      if ( j >= w-> count) j -= w-> count;
      
      x = ordered[j];
      if ( CWidget( x)-> get_visible( x) && CWidget( x)-> get_enabled( x)) {
         if ( CWidget( x)-> get_selectable( x) && CWidget( x)-> get_tabStop( x)) {
            if ( *result == nilHandle) *result = x; 
            switch( *stage) {
            case 0: /* nothing found yet */
               if ( x == who) *stage = 1;
               break;
            default:
               /* next widget after 'who' is ours */
               *result = x;
               free( ordered);
               return false;
            }   
         }   
         if ( !do_taborder_candidates( x, who, compareProc, stage, result)) {
            free( ordered);
            return false; /* fall through */
         }   
      }
   }   
   free( ordered);
   return true;
}

Handle 
Widget_next_tab( Handle self, Bool forward)
{
   return nilHandle;
}

/*::o */
/*::p */


void
Widget_post_message( Handle self, SV * info1, SV * info2)
{
}

Handle
Widget_prev( Handle self)
{
   return nilHandle;
}

Bool
Widget_process_accel( Handle self, int key)
{
   return false;
}

/*::q */
/*::r */
void
Widget_repaint( Handle self)
{
}

/*::s */
void
Widget_scroll( Handle self, int dx, int dy, Rect *confine, Rect *clip, Bool withChildren)
{
}

void
Widget_scroll_REDEFINED( Handle self, int dx, int dy, Rect *confine, Rect *clip, Bool withChildren)
{
}

XS( Widget_scroll_FROMPERL)
{
   dPROFILE;
   dXSARGS;
   Handle self;
   int dx, dy;
   Rect *confine = nil;
   Rect *clip = nil;
   Rect confine_rect, clip_rect;
   Bool withChildren = false;
   HV *profile;
   int rect[4];

   if ( items < 3 || (items - 3) % 2) goto invalid_usage;
   if (!( self = gimme_the_mate( ST(0)))) goto invalid_usage;
   dx = SvIV( ST(1));
   dy = SvIV( ST(2));
   profile = parse_hv( ax, sp, items, mark, 3, "Widget::scroll");
   if ( pexist( confineRect)) {
      prima_read_point( pget_sv( confineRect), rect, 4, "RTC008B: Array panic on 'confineRect'");
      confine = &confine_rect;
      confine-> left = rect[0];
      confine-> bottom = rect[1];
      confine-> right = rect[2];
      confine-> top = rect[3];
   }
   if ( pexist( clipRect)) {
      prima_read_point( pget_sv( clipRect), rect, 4, "RTC008C: Array panic on 'clipRect'");
      clip = &clip_rect;
      clip-> left = rect[0];
      clip-> bottom = rect[1];
      clip-> right = rect[2];
      clip-> top = rect[3];
   }
   if ( pexist( withChildren)) withChildren = pget_B( withChildren);
   sv_free((SV*)profile);
   Widget_scroll( self, dx, dy, confine, clip, withChildren);
   SPAGAIN;
   SP -= items;
   PUTBACK;
   XSRETURN_EMPTY;
invalid_usage:
   croak ("Invalid usage of %s", "Widget::scroll");
}

void
Widget_send_to_back( Handle self)
{
}

void
Widget_set( Handle self, HV * profile)
{
}

void
Widget_setup( Handle self)
{
}

void
Widget_show( Handle self)
{
}

void
Widget_show_cursor( Handle self)
{
}

/*::t */
/*::u */

static Bool
repaint_all( Handle owner, Handle self, void * dummy)
{
   return false;
}

Bool
Widget_unlock( Handle self)
{
   return false;
}

void
Widget_update_view( Handle self)
{
}

/*::v */

Bool
Widget_validate_owner( Handle self, Handle * owner, HV * profile)
{
   return false;
}

/*::w */
/*::x */
/*::y */
/*::z */

/* get_props() */

Font
Widget_get_default_font( char * dummy)
{
   Font font;
   apc_widget_default_font( &font);
   return font;
}

Font
Widget_get_default_popup_font( char * dummy)
{
   Font f;
   apc_popup_default_font( &f);
   return f;
}


NPoint
Widget_designScale( Handle self, Bool set, NPoint designScale)
{
   if ( !set)
      return var-> designScale;
   if ( designScale. x < 0) designScale. x = 0;
   if ( designScale. y < 0) designScale. y = 0;
   var-> designScale = designScale;
   return designScale;
}

int
Widget_growMode( Handle self, Bool set, int growMode)
{
   enter_method;
   Bool x = false, y = false;
   if ( !set)
      return var-> growMode;
   var-> growMode = growMode;
   if ( var-> growMode & gmXCenter) x = true;
   if ( var-> growMode & gmYCenter) y = true;
   if ( x || y) my-> set_centered( self, x, y);
   return var-> growMode;
}

SV *
Widget_get_handle( Handle self)
{
   return nilSV;
}


SV *
Widget_get_parent_handle( Handle self)
{
   return nilSV;
}

int
Widget_hintVisible( Handle self, Bool set, int hintVisible)
{
   Bool wantVisible;
   if ( !set)
      return PApplication( application)-> hintVisible;
   if ( var-> stage >= csDead) return false;
   wantVisible = ( hintVisible != 0);
   if ( wantVisible == PApplication( application)-> hintVisible) return false;
   if ( wantVisible) {
      if ( strlen( var-> hint) == 0) return false;
      if ( hintVisible > 0) PApplication(application)-> hintActive = -1; /* immediate */
   }
   CApplication( application)-> set_hint_action( application, self, wantVisible, false);
   return false;
}

Bool
Widget_get_locked( Handle self)
{
   return false;
}


Handle
Widget_get_parent( Handle self)
{
   return nilHandle;
}

Point
Widget_get_pointer_size( char*dummy)
{
   return apc_pointer_get_size( nilHandle);
}

Font
Widget_get_popup_font( Handle self)
{
   return var-> popupFont;
}

Handle
Widget_get_selectee( Handle self)
{
   return nilHandle;
}

Point
Widget_get_virtual_size( Handle self)
{
   return var-> virtualSize;
}

/* set_props() */

void
Widget_set_capture( Handle self, Bool capture, Handle confineTo)
{
}

void
Widget_set_centered( Handle self, Bool x, Bool y)
{
}

void
Widget_set_font( Handle self, Font font)
{
}

void
Widget_set_popup_font( Handle self, Font font)
{
}

/* event handlers */

void
Widget_on_paint( Handle self, SV * canvas)
{
}

/*
void Widget_on_click( Handle self) {}
void Widget_on_change( Handle self) {}
void Widget_on_close( Handle self) {}
void Widget_on_colorchanged( Handle self, int colorIndex){}
void Widget_on_disable( Handle self) {}
void Widget_on_dragdrop( Handle self, Handle source , int x , int y ) {}
void Widget_on_dragover( Handle self, Handle source , int x , int y , int state ) {}
void Widget_on_enable( Handle self) {}
void Widget_on_enddrag( Handle self, Handle target , int x , int y ) {}
void Widget_on_fontchanged( Handle self) {}
void Widget_on_enter( Handle self) {}
void Widget_on_keydown( Handle self, int code , int key , int shiftState, int repeat ) {}
void Widget_on_keyup( Handle self, int code , int key , int shiftState ) {}
void Widget_on_menu( Handle self, Handle menu, char * variable) {}
void Widget_on_setup( Handle self) {}
void Widget_on_size( Handle self, Point oldSize, Point newSize) {}
void Widget_on_move( Handle self, Point oldPos, Point newPos) {}
void Widget_on_show( Handle self) {}
void Widget_on_hide( Handle self) {}
void Widget_on_hint( Handle self, Bool show) {}
void Widget_on_translateaccel( Handle self, int code , int key , int shiftState ) {}
void Widget_on_zorderchanged( Handle self) {}
void Widget_on_popup( Handle self, Bool mouseDriven, int x, int y) {}
void Widget_on_mouseclick( Handle self, int button , int shiftState , int x , int y , Bool dbl ) {}
void Widget_on_mousedown( Handle self, int button , int shiftState , int x , int y ) {}
void Widget_on_mouseup( Handle self, int button , int shiftState , int x , int y ) {}
void Widget_on_mousemove( Handle self, int shiftState , int x , int y ) {}
void Widget_on_mousewheel( Handle self, int shiftState , int x , int y, int z ) {}
void Widget_on_mouseenter( Handle self, int shiftState , int x , int y ) {}
void Widget_on_mouseleave( Handle self ) {}
void Widget_on_leave( Handle self) {}
*/


/* static iterators */
Bool kill_all( Handle self, Handle child, void * dummy)
{
   return false;
}

static Bool find_dup_msg( PEvent event, int * cmd) { return false; }

Bool
accel_notify ( Handle group, Handle self, PEvent event)
{
   return false;
}

static Bool
pquery ( Handle window, Handle self, void * v)
{
   return false;
}

Bool
find_accel( Handle self, Handle item, int * key)
{
   return false;
}

static Handle
find_tabfoc( Handle self)
{
   return nilHandle;
}


static Bool
get_top_current( Handle self)
{
   return false;
}

static Bool
sptr( Handle window, Handle self, void * v)
{
   return false;
}

/* static iterators for ownership notifications */

Bool
font_notify ( Handle self, Handle child, void * font)
{
   return false;
}

static Bool
showhint_notify ( Handle self, Handle child, void * data)
{
   return false;
}

static Bool
hint_notify ( Handle self, Handle child, SV * hint)
{
   return false;
}

Bool
single_color_notify ( Handle self, Handle child, void * color)
{
   return false;
}

Bool
prima_read_point( SV *rv_av, int * pt, int number, char * error)
{
   return false;
}

static Bool
auto_enable_children( Handle self, Handle child, void * enable)
{
   return false;
}
/* properties section */

SV *
Widget_accelItems( Handle self, Bool set, SV * accelItems)
{
   return nilSV;
}

Handle
Widget_accelTable( Handle self, Bool set, Handle accelTable)
{
   return nilHandle;
}

Color
Widget_backColor( Handle self, Bool set, Color color)
{
   enter_method;
   if (!set) return my-> colorIndex( self, false, ciBack, 0);
   my-> colorIndex( self, true, ciBack, color);
   return color;
}

int
Widget_bottom( Handle self, Bool set, int bottom)
{
   enter_method;
   Point p = my-> get_origin( self);
   if ( !set)
      return p. y;
   p. y = bottom;
   my-> set_origin( self, p);
   return 0;
}

Bool
Widget_autoEnableChildren( Handle self, Bool set, Bool autoEnableChildren)
{
   return false;
}

Bool
Widget_briefKeys( Handle self, Bool set, Bool briefKeys)
{
   return false;
}

Bool
Widget_buffered( Handle self, Bool set, Bool buffered)
{
   return false;
}

Bool
Widget_clipOwner( Handle self, Bool set, Bool clipOwner)
{
   return false;
}

Color
Widget_color( Handle self, Bool set, Color color)
{
   enter_method;
   if (!set)
      return my-> colorIndex( self, false, ciFore, 0);
   return my-> colorIndex( self, true, ciFore, color);
}

Color
Widget_colorIndex( Handle self, Bool set, int index, Color color)
{
   if ( !set) {
      if ( index < 0 || index > ciMaxId) return clInvalid;
      switch ( index) {
        case ciFore:
           return opt_InPaint ? inherited-> get_color ( self) : apc_widget_get_color( self, ciFore);
        case ciBack:
           return opt_InPaint ? inherited-> get_backColor ( self) : apc_widget_get_color( self, ciBack);
        default:
           return apc_widget_get_color( self, index);
      }
   } else {
      enter_method;
      SingleColor s;
      s. color = color;
      s. index = index;
      if (( index < 0) || ( index > ciMaxId)) return clInvalid;
      if ( !opt_InPaint) my-> first_that( self, (void*)single_color_notify, &s);

      if ( var-> handle == nilHandle) return clInvalid; /* aware of call from Drawable::init */
      if ((( color & clSysFlag) != 0) && (( color & wcMask) == 0))
         color |= var-> widgetClass;
      if ( opt_InPaint) {
         switch ( index) {
            case ciFore:
               inherited-> set_color ( self, color);
               break;
            case ciBack:
               inherited-> set_backColor ( self, color);
               break;
            default:
               apc_widget_set_color ( self, color, index);
         }
      } else {
         switch ( index) {
            case ciFore:
               opt_clear( optOwnerColor);
               break;
            case ciBack:
               opt_clear( optOwnerBackColor);
               break;
         }
         apc_widget_set_color( self, color, index);
         my-> repaint( self);
      }
   }
   return 0;
}

Bool
Widget_current( Handle self, Bool set, Bool current)
{
   return false;
}

Handle
Widget_currentWidget( Handle self, Bool set, Handle widget)
{
   return nilHandle;
}

Point
Widget_cursorPos( Handle self, Bool set, Point cursorPos)
{
   if ( !set)
      return apc_cursor_get_pos( self);
   apc_cursor_set_pos( self, cursorPos. x, cursorPos. y);
   return cursorPos;
}

Point
Widget_cursorSize( Handle self, Bool set, Point cursorSize)
{
   if ( !set)
      return apc_cursor_get_size( self);
   apc_cursor_set_size( self, cursorSize. x, cursorSize. y);
   return cursorSize;
}

Bool
Widget_cursorVisible( Handle self, Bool set, Bool cursorVisible)
{
   return false;
}

Bool
Widget_enabled( Handle self, Bool set, Bool enabled)
{
   return false;
}

Bool
Widget_firstClick( Handle self, Bool set, Bool firstClick)
{
   return false;
}

Bool
Widget_focused( Handle self, Bool set, Bool focused)
{
   return false;
}

SV *
Widget_helpContext( Handle self, Bool set, SV *helpContext)
{
   return nilSV;
}

SV *
Widget_hint( Handle self, Bool set, SV *hint)
{
   return nilSV;
}

int
Widget_left( Handle self, Bool set, int left)
{
   enter_method;
   Point p = my-> get_origin( self);
   if ( !set)
      return p. x;
   p. x = left;
   my-> set_origin( self, p);
   return 0;
}

Point
Widget_origin( Handle self, Bool set, Point origin)
{
   if ( !set)
      return apc_widget_get_pos( self);
   apc_widget_set_pos( self, origin.x, origin.y);
   return origin;
}

Bool
Widget_ownerBackColor( Handle self, Bool set, Bool ownerBackColor)
{
   return false;
}

Bool
Widget_ownerColor( Handle self, Bool set, Bool ownerColor)
{
   return false;
}

Bool
Widget_ownerFont( Handle self, Bool set, Bool ownerFont )
{
   return false;
}

Bool
Widget_ownerHint( Handle self, Bool set, Bool ownerHint )
{
   return false;
}

Bool
Widget_ownerPalette( Handle self, Bool set, Bool ownerPalette)
{
   return false;
}

Bool
Widget_ownerShowHint( Handle self, Bool set, Bool ownerShowHint )
{
   return false;
}

SV *
Widget_palette( Handle self, Bool set, SV * palette)
{
   return nilSV;
}

Handle
Widget_pointerIcon( Handle self, Bool set, Handle icon)
{
   return nilHandle;
}

Point
Widget_pointerHotSpot( Handle self, Bool set, Point hotSpot)
{
   enter_method;
   Handle icon;
   if ( !set)
      return apc_pointer_get_hot_spot( self);
   if ( var-> stage > csFrozen) return hotSpot;
   icon = my-> get_pointerIcon( self);
   apc_pointer_set_user( self, icon, hotSpot);
   if ( var-> pointerType == crUser) my-> first_that( self, (void*)sptr, nil);
   return hotSpot;
}

int
Widget_pointerType( Handle self, Bool set, int type)
{
   enter_method;
   if ( var-> stage > csFrozen) return 0;
   if ( !set)
      return var-> pointerType;
   var-> pointerType = type;
   apc_pointer_set_shape( self, type);
   my-> first_that( self, (void*)sptr, nil);
   return type;
}

Point
Widget_pointerPos( Handle self, Bool set, Point p)
{
   if ( !set) {
      p = apc_pointer_get_pos( self);
      apc_widget_map_points( self, false, 1, &p);
      return p;
   }
   apc_widget_map_points( self, true, 1, &p);
   apc_pointer_set_pos( self, p. x, p. y);
   return p;
}

Handle
Widget_popup( Handle self, Bool set, Handle popup)
{
   return nilHandle;
}

Color
Widget_popupColorIndex( Handle self, Bool set, int index, Color color)
{
   if (( index < 0) || ( index > ciMaxId)) return clInvalid;
   if ( !set)
      return var-> popupColor[ index];
   if ((( color & clSysFlag) != 0) && (( color & wcMask) == 0)) color |= wcPopup;
   var-> popupColor[ index] = color;
   return color;
}

SV *
Widget_popupItems( Handle self, Bool set, SV * popupItems)
{
   return nilSV;
}


Rect
Widget_rect( Handle self, Bool set, Rect r)
{
   enter_method;
   if ( !set) {
      Point p   = my-> get_origin( self);
      Point s   = my-> get_size( self);
      r. left   = p. x;
      r. bottom = p. y;
      r. right  = p. x + s. x;
      r. top    = p. y + s. y;
   } else 
      apc_widget_set_rect( self, r. left, r. bottom, r. right - r. left, r. top - r. bottom);
   return r;
}

int
Widget_right( Handle self, Bool set, int right)
{
   enter_method;
   Point p;
   Rect r = my-> get_rect( self);
   if ( !set)
      return r. right;
   p. x = r. left - r. right + right;
   p. y = r. bottom;
   my-> set_origin( self, p);
   return 0;
}

Bool
Widget_scaleChildren( Handle self, Bool set, Bool scaleChildren)
{
   return false;
}

Bool
Widget_selectable( Handle self, Bool set, Bool selectable)
{
   return false;
}

Bool
Widget_selected( Handle self, Bool set, Bool selected)
{
   return false;
}

Handle
Widget_selectedWidget( Handle self, Bool set, Handle widget)
{
   return nilHandle;
}

int
Widget_selectingButtons( Handle self, Bool set, int sb)
{
   if ( !set)
      return var-> selectingButtons;
   return var-> selectingButtons = sb;
}

Handle
Widget_shape( Handle self, Bool set, Handle mask)
{
   return nilHandle;
}

Bool
Widget_showHint( Handle self, Bool set, Bool showHint )
{
   return false;
}

Point
Widget_size( Handle self, Bool set, Point size)
{
   if ( !set)
      return apc_widget_get_size( self);
   apc_widget_set_size( self, size.x, size.y);
   return size;
}

Bool
Widget_syncPaint( Handle self, Bool set, Bool syncPaint)
{
   return false;
}

int
Widget_tabOrder( Handle self, Bool set, int tabOrder)
{
    int count;
    PWidget owner;

    if ( var-> stage > csFrozen) return 0;
    if ( !set)
       return var-> tabOrder;

    owner = ( PWidget) var-> owner;
    count = owner-> widgets. count;
    if ( tabOrder < 0) {
       int i, maxOrder = -1;
       /* finding maximal tabOrder value among the siblings */
       for ( i = 0; i < count; i++) {
          PWidget ctrl = ( PWidget) owner-> widgets. items[ i];
          if ( self == ( Handle) ctrl) continue;
          if ( maxOrder < ctrl-> tabOrder) maxOrder = ctrl-> tabOrder;
       }
       if ( maxOrder < INT_MAX) {
          var-> tabOrder = maxOrder + 1;
          return 0;
       }
       /* maximal value found, but has no use; finding gaps */
       {
          int j = 0;
          Bool match = 1;
          while ( !match) {
             for ( i = 0; i < count; i++) {
                PWidget ctrl = ( PWidget) owner-> widgets. items[ i];
                if ( self == ( Handle) ctrl) continue;
                if ( ctrl-> tabOrder == j) {
                   match = 1;
                   break;
                }
             }
             j++;
          }
          var-> tabOrder = j - 1;
       }
    } else {
       int i;
       Bool match = 0;
       /* finding exact match among the siblings */
       for ( i = 0; i < count; i++) {
          PWidget ctrl = ( PWidget) owner-> widgets. items[ i];
          if ( self == ( Handle) ctrl) continue;
          if ( ctrl-> tabOrder == tabOrder) {
             match = 1;
             break;
          }
       }
       if ( match)
          /* incrementing all tabOrders that greater than ours */
          for ( i = 0; i < count; i++) {
             PWidget ctrl = ( PWidget) owner-> widgets. items[ i];
             if ( self == ( Handle) ctrl) continue;
             if ( ctrl-> tabOrder >= tabOrder) ctrl-> tabOrder++;
          }
       var-> tabOrder = tabOrder;
    }
    return 0;
}

Bool
Widget_tabStop( Handle self, Bool set, Bool stop)
{
   return false;
}

Bool
Widget_transparent( Handle self, Bool set, Bool transparent)
{
   return false;
}

SV *
Widget_text( Handle self, Bool set, SV *text)
{
   return nilSV;
}

int
Widget_top( Handle self, Bool set, int top)
{
   enter_method;
   Point p;
   Rect  r   = my-> get_rect( self);
   if ( !set)
      return r. top;
   p. x = r. left;
   p. y = r. bottom - r. top + top;
   my-> set_origin( self, p);
   return 0;
}

Bool
Widget_visible( Handle self, Bool set, Bool visible)
{
   return false;
}

int
Widget_widgetClass( Handle self, Bool set, int widgetClass)
{
   enter_method;
   if ( !set)
      return var-> widgetClass;
   var-> widgetClass = widgetClass;
   my-> repaint( self);
   return 0;
}

/* XS section */
XS( Widget_client_to_screen_FROMPERL)
{
   dXSARGS;
   Handle self;
   int i, count;
   Point * points;

   if (( items % 2) != 1)
      croak ("Invalid usage of Widget::client_to_screen");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Widget::client_to_screen");
   count  = ( items - 1) / 2;
   if ( !( points = allocn( Point, count))) {
      PUTBACK;
      return;
   }
   for ( i = 0; i < count; i++) {
      points[i]. x = SvIV( ST( i * 2 + 1));
      points[i]. y = SvIV( ST( i * 2 + 2));
   }
   apc_widget_map_points( self, true, count, points);
   EXTEND( sp, count * 2);
   for ( i = 0; i < count; i++) {
      PUSHs( sv_2mortal( newSViv( points[i].x)));
      PUSHs( sv_2mortal( newSViv( points[i].y)));
   }
   PUTBACK;
   free( points);
   return;
}

XS( Widget_screen_to_client_FROMPERL)
{
   dXSARGS;
   Handle self;
   int i, count;
   Point * points;

   if (( items % 2) != 1)
      croak ("Invalid usage of Widget::screen_to_client");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Widget::screen_to_client");
   count  = ( items - 1) / 2;
   if ( !( points = allocn( Point, count))) {
      PUTBACK;
      return;
   }
   for ( i = 0; i < count; i++) {
      points[i]. x = SvIV( ST( i * 2 + 1));
      points[i]. y = SvIV( ST( i * 2 + 2));
   }
   apc_widget_map_points( self, false, count, points);
   EXTEND( sp, count * 2);
   for ( i = 0; i < count; i++) {
      PUSHs( sv_2mortal( newSViv( points[i].x)));
      PUSHs( sv_2mortal( newSViv( points[i].y)));
   }
   PUTBACK;
   free( points);
   return;
}


XS( Widget_get_widgets_FROMPERL)
{
   dXSARGS;
   Handle self;
   Handle * list;
   int i, count;

   if ( items != 1)
      croak ("Invalid usage of Widget.get_widgets");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Widget.get_widgets");
   count = var-> widgets. count;
   list  = var-> widgets. items;
   EXTEND( sp, count);
   for ( i = 0; i < count; i++)
      PUSHs( sv_2mortal( newSVsv((( PAnyObject) list[ i])-> mate)));
   PUTBACK;
   return;
}

void Widget_get_widgets          ( Handle self) {}
void Widget_get_widgets_REDEFINED( Handle self) {}
void Widget_screen_to_client ( Handle self) {}
void Widget_screen_to_client_REDEFINED ( Handle self) {}
void Widget_client_to_screen ( Handle self) {}
void Widget_client_to_screen_REDEFINED ( Handle self) {}

#ifdef __cplusplus
}
#endif
