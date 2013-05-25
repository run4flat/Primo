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
   int foo; return foo;
}

static int compare_taborders_backward( const void *a, const void *b)
{
   int foo; return foo;
}

static int
do_taborder_candidates( Handle level, Handle who, 
     int (*compareProc)(const void *, const void *), 
     int * stage, Handle * result)
{
   int foo; return foo;
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
   Font foo; return foo;
}

Font
Widget_get_default_popup_font( char * dummy)
{
   Font foo; return foo;
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
   int foo; return foo;
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
   int foo; return foo;
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
   Point foo; return foo;
}

Font
Widget_get_popup_font( Handle self)
{
   Font foo; return foo;
}

Handle
Widget_get_selectee( Handle self)
{
   return nilHandle;
}

Point
Widget_get_virtual_size( Handle self)
{
   Point foo; return foo;
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
   Color c; return c;
}

int
Widget_bottom( Handle self, Bool set, int bottom)
{
   int foo; return foo;
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
   Color c; return c;
}

Color
Widget_colorIndex( Handle self, Bool set, int index, Color color)
{
   Color c; return c;
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
   Point foo; return foo;
}

Point
Widget_cursorSize( Handle self, Bool set, Point cursorSize)
{
   Point foo; return foo;
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
   int foo; return foo;
}

Point
Widget_origin( Handle self, Bool set, Point origin)
{
   Point foo; return foo;
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
   Point foo; return foo;
}

int
Widget_pointerType( Handle self, Bool set, int type)
{
   int foo; return foo;
}

Point
Widget_pointerPos( Handle self, Bool set, Point p)
{
   Point foo; return foo;
}

Handle
Widget_popup( Handle self, Bool set, Handle popup)
{
   return nilHandle;
}

Color
Widget_popupColorIndex( Handle self, Bool set, int index, Color color)
{
   Color c; return c;
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
   int foo; return foo;
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
   int foo; return foo;
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
   Point foo; return foo;
}

Bool
Widget_syncPaint( Handle self, Bool set, Bool syncPaint)
{
   return false;
}

int
Widget_tabOrder( Handle self, Bool set, int tabOrder)
{
   int foo; return foo;
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
   int foo; return foo;
}

Bool
Widget_visible( Handle self, Bool set, Bool visible)
{
   return false;
}

int
Widget_widgetClass( Handle self, Bool set, int widgetClass)
{
   int foo; return foo;
}

/* XS section */
XS( Widget_client_to_screen_FROMPERL)
{
}

XS( Widget_screen_to_client_FROMPERL)
{
}


XS( Widget_get_widgets_FROMPERL)
{
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
