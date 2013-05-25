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

/***********************************************************/
/*                                                         */
/*  System dependent widget management (unix, x11)         */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include "Window.h"
#include "Application.h"

#define SORT(a,b)       { int swp; if ((a) > (b)) { swp=(a); (a)=(b); (b)=swp; }}
#define REVERT(a)	( XX-> size. y - (a) - 1)

Bool
apc_widget_map_points( Handle self, Bool toScreen, int n, Point *p)
{
   Bool foo; return foo;
}

ApiHandle
apc_widget_get_parent_handle( Handle self)
{
   return X(self)-> parentHandle;
}

Handle
apc_widget_get_z_order( Handle self, int zOrderId)
{
   DEFXX;
   XWindow root, parent, *children;
   unsigned int count;
   int i, inc;
   Handle ret = nilHandle;

   if ( !( PComponent(self)-> owner))
      return self;

   switch ( zOrderId) {
   case zoFirst:
      i = 1;
      inc = -1;
      break;
   case zoLast:
      i  = 1;
      inc = 1;
      break;
   case zoNext:
      i = 0;
      inc = -1;
      break;
   case zoPrev:
      i = 0;
      inc = 1;
      break;
   default:
      return nilHandle;
   }

   if ( XQueryTree( DISP, X(PComponent(self)-> owner)-> client, 
      &root, &parent, &children, &count) == 0)
         return nilHandle;

   if ( count == 0) goto EXIT;

   if ( i == 0) {
      int found = -1;
      for ( i = 0; i < count; i++) {
         if ( children[ i] == XX-> client) {
            found = i;
            break;
         }   
      }   
      if ( found < 0) { /* if !clipOwner */
         ret = self;
         goto EXIT; 
      }   
      i = found + inc;
      if ( i < 0 || i >= count) goto EXIT; /* last in line */
   } else
      i = ( zOrderId == zoFirst) ? count - 1 : 0;
   
   while ( 1) {
      Handle who = ( Handle) hash_fetch( guts. windows, (void*)&(children[i]), sizeof(X_WINDOW));
      if ( who) {
         ret = who;
         break;
      }   
      i += inc;
      if ( i < 0 || i >= count) break;
   }   

EXIT:   
   if ( children) XFree( children);
   return ret;
}   

void
process_transparents( Handle self)
{
}

static int
flush_events( Display * disp, XEvent * ev, Handle self)
{
   int foo; return foo;
}

Bool
apc_widget_create( Handle self, Handle owner, Bool sync_paint,
		   Bool clip_owner, Bool transparent, ApiHandle parentHandle)
{
   Bool foo; return foo;
}

Bool
apc_widget_begin_paint( Handle self, Bool inside_on_paint)
{
   Bool foo; return foo;
}

Bool
apc_widget_begin_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_destroy( Handle self)
{
   Bool foo; return foo;
}

PFont
apc_widget_default_font( PFont f)
{
   memcpy( f, &guts. default_widget_font, sizeof( Font));
   return f;
}

Bool
apc_widget_end_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_end_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_get_clip_owner( Handle self)
{
   Bool foo; return foo;
}

Color
apc_widget_get_color( Handle self, int index)
{
   return X(self)-> colors[ index];
}

Bool
apc_widget_get_first_click( Handle self)
{
   Bool foo; return foo;
}

Handle
apc_widget_get_focused( void)
{
   return guts. focused;
}

ApiHandle
apc_widget_get_handle( Handle self)
{
   return X_WINDOW;
}

Rect
apc_widget_get_invalid_rect( Handle self)
{
   DEFXX;
   Rect ret;
   XRectangle r;
   if ( !XX-> invalid_region) {
      Rect r = {0,0,0,0}; 
      return r;
   }
   XClipBox( XX-> invalid_region, &r);
   ret. left = r.x;
   ret. bottom = XX-> size.y - r.height - r.y; 
   ret. right = r.x + r.width;
   ret. top =  XX-> size.y - r.y;
   return ret;
}

Point
apc_widget_get_pos( Handle self)
{
   DEFXX;
   XWindow r;
   Point ret;
   int x, y;
   unsigned int w, h, d, b;

   if ( XX-> type. window) {
      Rect rc;
      Point p = apc_window_get_client_pos( self);
      prima_get_frame_info( self, &rc);
      p. x -= rc. left;
      p. y -= rc. bottom;
      return p;
   }   
      
   if ( XX-> parentHandle == nilHandle)
      return XX-> origin;
   
   XGetGeometry( DISP, X_WINDOW, &r, &x, &y, &w, &h, &b, &d);
   XTranslateCoordinates( DISP, XX-> parentHandle, guts. root, x, y, &x, &y, &r);
   ret. x = x;
   ret. y = DisplayHeight( DISP, SCREEN) - y - w; 
   return ret;
}

Bool
apc_widget_get_shape( Handle self, Handle mask)
{
   Bool foo; return foo;
}

Point
apc_widget_get_size( Handle self)
{
   DEFXX;
   if ( XX-> type. window) {
      Rect rc;
      Point p = apc_window_get_client_size( self);
      prima_get_frame_info( self, &rc);
      p. x += rc. left + rc. right;
      p. y += rc. bottom + rc. top;
      return p;
   }   
   
   return XX-> size;
}

Bool
apc_widget_get_sync_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_get_transparent( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_captured( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_enabled( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_exposed( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_focused( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_responsive( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_showing( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_visible( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_invalidate_rect( Handle self, Rect *rect)
{
   Bool foo; return foo;
}

static Bool 
scroll( Handle owner, Handle self, Point * delta)
{
   Bool foo; return foo;
}

Bool
apc_widget_scroll( Handle self, int horiz, int vert,
		   Rect *confine, Rect *clip, Bool withChildren)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_capture( Handle self, Bool capture, Handle confineTo)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_color( Handle self, Color color, int i)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_enabled( Handle self, Bool enable)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_first_click( Handle self, Bool firstClick)
{
   Bool foo; return foo;
}

static int
flush_refocus( Display * disp, XEvent * ev, void * dummy)
{
   int foo; return foo;
}

Bool
apc_widget_set_focused( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_palette( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_shape( Handle self, Handle mask)
{
   Bool foo; return foo;
}

/* Used instead of XUnmapWindow sometimes because when a focused
   widget gets hidden, the X server's revert_to is sometimes
   weirdly set to RevertToPointerRoot ( mwm is the guilty one ) */
static void
apc_XUnmapWindow( Handle self)
{
}

void
prima_send_cmSize( Handle self, Point oldSize)
{
}

Bool
apc_widget_set_size( Handle self, int width, int height)
{
   Bool foo; return foo;
}


Bool
apc_widget_set_rect( Handle self, int x, int y, int width, int height)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_size_bounds( Handle self, Point min, Point max)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_visible( Handle self, Bool show)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_z_order( Handle self, Handle behind, Bool top)
{
   Bool foo; return foo;
}

Bool
apc_widget_update( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_validate_rect( Handle self, Rect rect)
{
   Bool foo; return foo;
}

