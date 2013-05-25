/*
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
/*  System dependent window management (unix, x11)         */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include "Menu.h"
#include "Icon.h"
#include "Window.h"
#include "Application.h"

/* Tell a NET-compliant window manager that the window needs special treatment.
    See freedesktop.org for docs 

    params - -1 - don't touch, 0 - clear, 1 - set
 */
static void
set_net_hints( XWindow window, int task_listed, int modal, int zoom, int on_top)
{
   long data[40], * prop;
   Atom type;
   int count = 0, format;
   XClientMessageEvent ev;
   unsigned long i, n, left;
   
   if ( guts. icccm_only) return;

   /* read and preserve all state properties we don't know about */
   if ( XGetWindowProperty( DISP, window, NET_WM_STATE, 0, 32, false, XA_ATOM,
          &type, &format, &n, &left, (unsigned char**)&prop) == Success) {
     if ( prop) {
         if ( n > 32) n = 32;
         for ( i = 0; i < n; i++) {
            if (( prop[i] != NET_WM_STATE_SKIP_TASKBAR || task_listed < 0) && 
                ( prop[i] != NET_WM_STATE_MODAL || modal < 0) && 
                ( prop[i] != NET_WM_STATE_STAYS_ON_TOP || on_top < 0) && 
                ( prop[i] != NET_WM_STATE_ABOVE || on_top < 0) && 
                (( prop[i] != NET_WM_STATE_MAXIMIZED_VERT && 
                   prop[i] != NET_WM_STATE_MAXIMIZED_HORZ) || ( zoom < 0)))
               data[ count++] = prop[i];
         }
         XFree(( unsigned char *) prop);
      }
   }

   /* Send change message to root window, it's responsible for
      on-the-fly changes. Otherwise, the properties are not re-read
      until next XMapWindow() */
   bzero( &ev, sizeof(ev));
   ev. type = ClientMessage;
   ev. display = DISP;
   ev. window = window;
   ev. message_type = NET_WM_STATE;
   ev. format = 32;
   /*
      _NET_WM_STATE_REMOVE        0    // remove/unset property 
      _NET_WM_STATE_ADD           1    // add/set property 
      _NET_WM_STATE_TOGGLE        2    // toggle property  
    */

   if ( task_listed >= 0) {
      ev. data. l[0] = ( task_listed > 0) ? 0 : 1;
      ev. data. l[1] = ( long) NET_WM_STATE_SKIP_TASKBAR;
      ev. data. l[2] = 0;
      XSendEvent( DISP, guts. root, false, 0, (XEvent*)&ev);
   }

   if ( modal >= 0) {
      ev. data. l[0] = ( modal > 0) ? 1 : 0;
      ev. data. l[1] = ( long) NET_WM_STATE_MODAL;
      XSendEvent( DISP, guts. root, false, 0, (XEvent*)&ev);
   }

   if ( zoom >= 0) {
      ev. data. l[0] = ( zoom > 0) ? 1 : 0;
      ev. data. l[1] = ( long) NET_WM_STATE_MAXIMIZED_VERT;
      ev. data. l[2] = ( long) NET_WM_STATE_MAXIMIZED_HORZ;
      XSendEvent( DISP, guts. root, false, 0, (XEvent*)&ev);
   }
   
   if ( on_top >= 0) {
      ev. data. l[0] = ( on_top > 0) ? 1 : 0;
      ev. data. l[1] = ( long) NET_WM_STATE_STAYS_ON_TOP;
      ev. data. l[1] = ( long) NET_WM_STATE_ABOVE;
      XSendEvent( DISP, guts. root, false, 0, (XEvent*)&ev);
   }

   /* finally reset the list of properties */
   if ( task_listed == 0) data[ count++] = NET_WM_STATE_SKIP_TASKBAR;
   if ( modal > 0) data[ count++] = NET_WM_STATE_MODAL;
   if ( zoom > 0)  {
      data[ count++] = NET_WM_STATE_MAXIMIZED_VERT;
      data[ count++] = NET_WM_STATE_MAXIMIZED_HORZ;
   }
   if ( on_top > 0) {
      data[ count++] = NET_WM_STATE_STAYS_ON_TOP;
      data[ count++] = NET_WM_STATE_ABOVE;
   }
   XChangeProperty( DISP, window, NET_WM_STATE, XA_ATOM, 32,
       PropModeReplace, ( unsigned char *) data, count);
}

unsigned char * 
prima_get_window_property( XWindow window, Atom property, Atom req_type, Atom * actual_type,
                           int * actual_format, unsigned long * nitems)
{
   Atom a_actual_type;
   unsigned char * ret, * ptr;
   unsigned long left, n, a_nitems;
   int a_actual_format, curr_size, new_size, malloc_size, offset;

   ret = NULL;
   offset = 0;
   new_size = curr_size = malloc_size = 0;
   if ( actual_type   == NULL) actual_type   = &a_actual_type;
   if ( actual_format == NULL) actual_format = &a_actual_format;
   if ( nitems        == NULL) nitems        = &a_nitems;

   *nitems = 0;

   while ( XGetWindowProperty( DISP, window, property, offset, 2048, false, req_type,
          actual_type, actual_format, &n, &left, &ptr) == Success) {
     if ( ptr) {
         if ( n > 0) {
	     if ( *actual_format == 32) *actual_format = sizeof(long) * 8; /* MUAHAHA!! That's even documented now */
	     curr_size = n * *actual_format / 8;
	     new_size += curr_size;
             offset += curr_size / 4;
	     *nitems += n;

	     if ( ret == NULL) {
	         malloc_size = new_size;
		 ret = malloc( malloc_size);
		 if ( ret == NULL) {
                    warn("Not enough memory: %d bytes\n", malloc_size);
		    return NULL;
		 }
	     } else {
                 if ( new_size > malloc_size) {
		     unsigned char * p;
		     malloc_size = new_size * 2;
		     p = realloc( ret, malloc_size);
		     if ( p) {
		        ret = p;
		     } else {
		        free( ret);
                        warn("Not enough memory: %d bytes\n", malloc_size);
			return NULL;
		     }
		 }
	     }
	     memcpy( ret + new_size - curr_size, ptr, curr_size);
         }
         XFree( ptr);
      }
      if ( left <= 0) break;
   }

   return ret;
}

Bool
prima_wm_net_state_read_maximization( XWindow window, Atom property)
/*
   reads property, returns true if it has both vertical and horizontal properties set.
  */
{
   Bool foo; return foo;
}

static Bool
net_supports_maximization(void)
/* If WM supports customization, root.NET_SUPPORTED contains NET_WM_STATE_MAXIMIZED atoms.
   Stores result in guts. net_wm_maximization, so ConfigureEvent handler doesn't apply
   maximization heuristics. */
{
   Bool foo; return foo;
}

static void
apc_window_task_listed( Handle self, Bool task_list)
{
   DEFXX;
   XX-> flags. task_listed = ( task_list ? 1 : 0);
   set_net_hints( X_WINDOW, XX-> flags.task_listed, -1, -1, -1);
} 

/* Motif window hints */
#define MWM_HINTS_FUNCTIONS           (1L << 0)
#define MWM_HINTS_DECORATIONS         (1L << 1)

/* bit definitions for MwmHints.functions */
#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

/* bit definitions for MwmHints.decorations */
#define MWM_DECOR_ALL                 (1L << 0)
#define MWM_DECOR_BORDER              (1L << 1)
#define MWM_DECOR_RESIZEH             (1L << 2)
#define MWM_DECOR_TITLE               (1L << 3)
#define MWM_DECOR_MENU                (1L << 4)
#define MWM_DECOR_MINIMIZE            (1L << 5)
#define MWM_DECOR_MAXIMIZE            (1L << 6)

static void
set_motif_hints( XWindow window, int border_style, int border_icons)
{
   struct {
     unsigned long flags, functions, decorations;
     long  input_mode;
     unsigned long status;
   } mwmhints;


#define MWMHINT_OR(field,value) mwmhints.field |= (value)

   if ( guts. icccm_only) return;

   bzero( &mwmhints, sizeof(mwmhints));
   MWMHINT_OR( flags, MWM_HINTS_DECORATIONS);
   MWMHINT_OR( flags, MWM_HINTS_FUNCTIONS);
   if ( border_style == bsSizeable) {
      MWMHINT_OR( decorations, MWM_DECOR_BORDER);
      MWMHINT_OR( decorations, MWM_DECOR_RESIZEH);
      MWMHINT_OR( functions, MWM_FUNC_RESIZE);
   }
   MWMHINT_OR( functions, MWM_FUNC_MOVE);
   MWMHINT_OR( functions, MWM_FUNC_CLOSE);
   if ( border_icons & biTitleBar)
      MWMHINT_OR( decorations, MWM_DECOR_TITLE);
   if ( border_icons & biSystemMenu)
      MWMHINT_OR( decorations, MWM_DECOR_MENU);
   if ( border_icons & biMinimize) {
      MWMHINT_OR( decorations, MWM_DECOR_MINIMIZE);
      MWMHINT_OR( functions, MWM_FUNC_MINIMIZE);
   }
   if (( border_icons & biMaximize) && ( border_style == bsSizeable)) {
      MWMHINT_OR( decorations, MWM_DECOR_MAXIMIZE);
      MWMHINT_OR( functions, MWM_FUNC_MAXIMIZE);
   }

   XChangeProperty(DISP, window, XA_MOTIF_WM_HINTS, XA_MOTIF_WM_HINTS, 32,
       PropModeReplace, (unsigned char *) &mwmhints, 5);
}

Bool
apc_window_create( Handle self, Handle owner, Bool sync_paint, int border_icons,
		   int border_style, Bool task_list, int window_state, 
		   int on_top, Bool use_origin, Bool use_size)
{
   Bool foo; return foo;
}

Bool
apc_window_activate( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_is_active( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_close( Handle self)
{
   Bool foo; return foo;
}

Handle
apc_window_get_active( void)
{
   Handle x = guts. focused;
   while ( x && !X(x)-> type. window) x = PWidget(x)-> owner;
   return x;
}

int
apc_window_get_border_icons( Handle self)
{
   int foo; return foo;
}

int
apc_window_get_border_style( Handle self)
{
   int foo; return foo;
}

ApiHandle
apc_window_get_client_handle( Handle self)
{
   return X(self)-> client;
}

Point
apc_window_get_client_pos( Handle self)
{
   if ( !X(self)-> flags. configured) prima_wm_sync( self, ConfigureNotify);
   return X(self)-> origin;
}

Point
apc_window_get_client_size( Handle self)
{
   if ( !X(self)-> flags. configured) prima_wm_sync( self, ConfigureNotify);
   return X(self)-> size;
}

Bool
apc_window_get_icon( Handle self, Handle icon)
{
   Bool foo; return foo;
}

int
apc_window_get_window_state( Handle self)
{
   int foo; return foo;
}

Bool
apc_window_get_task_listed( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_set_caption( Handle self, const char *caption, Bool utf8)
{
   Bool foo; return foo;
}

XWindow
prima_find_frame_window( XWindow w)
{
   XWindow r, p, *c;
   unsigned int nc;

   if ( w == None)
      return None;
   while ( XQueryTree( DISP, w, &r, &p, &c, &nc)) {
      if (c)
         XFree(c);
      if ( p == r)
         return w;
      w = p;
   }
   return None;
}

Bool
prima_get_frame_info( Handle self, PRect r)
{
   Bool foo; return foo;
}

void
apc_SetWMNormalHints( Handle self, XSizeHints * hints)
{
   DEFXX;
   hints-> flags |= PMinSize | PMaxSize;
   if ( XX-> flags. sizeable) {
      int h = PWidget(self)-> sizeMin.y;
      if ( h == 0) h = 1;
      hints-> min_width  = PWidget(self)-> sizeMin.x;
      hints-> min_height = h + XX-> menuHeight;
      hints-> max_width  = PWidget(self)-> sizeMax.x;
      hints-> max_height = PWidget(self)-> sizeMax.y + XX-> menuHeight;
      if ( !XX-> flags. sizemax_set && 
         PWidget(self)-> sizeMax.x == 16384 &&
         PWidget(self)-> sizeMax.y == 16384) {
         hints-> flags &= ~ PMaxSize;
      }
      else 
         XX-> flags. sizemax_set = 1;
   } else {   
      Point who; 
      who. x = ( hints-> flags & USSize) ? hints-> width  : XX-> size. x;
      who. y = ( hints-> flags & USSize) ? hints-> height : XX-> size. y + XX-> menuHeight;
      hints-> min_width  = who. x;
      hints-> min_height = who. y;
      hints-> max_width  = who. x;
      hints-> max_height = who. y;
      XX-> flags. sizemax_set = 1;
   }
   XSetWMNormalHints( DISP, X_WINDOW, hints);
   XCHECKPOINT;
}   


Bool
apc_window_set_client_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

static void
apc_window_set_rect( Handle self, int x, int y, int szx, int szy)
{
    DEFXX;
    XSizeHints hints;
    Point psize = XX-> size;
    ConfigureEventPair *cep;

    bzero( &hints, sizeof( XSizeHints));
    hints. flags = USPosition | USSize;
    hints. x = x - XX-> decorationSize. x;
    hints. y = guts. displaySize. y - szy - XX-> menuHeight - y - XX-> decorationSize. y;
    hints. width  = szx;
    hints. height = szy + XX-> menuHeight;
    XX-> flags. position_determined = 1;
    XX-> size. x = szx;
    XX-> size. y = szy;
    XMoveResizeWindow( DISP, XX-> client, 0, XX-> menuHeight, hints. width, hints. height - XX-> menuHeight);
    XMoveResizeWindow( DISP, X_WINDOW, hints. x, hints. y, hints. width, hints. height);
    if (( cep = malloc( sizeof( ConfigureEventPair)))) {
       bzero( cep, sizeof( ConfigureEventPair));
       cep-> w = hints. width;
       cep-> h = hints. height;
       TAILQ_INSERT_TAIL( &XX-> configure_pairs, cep, link);
    }

    apc_SetWMNormalHints( self, &hints);
    prima_send_cmSize( self, psize);
    if ( PObject( self)-> stage == csDead) return; 
    prima_wm_sync( self, ConfigureNotify); 
}   

static Bool
window_set_client_size( Handle self, int width, int height)
{
   Bool foo; return foo;
}
  
Bool
apc_window_set_client_rect( Handle self, int x, int y, int width, int height)
{
   Bool foo; return foo;
}


Bool
apc_window_set_client_size( Handle self, int width, int height)
{
   Bool foo; return foo;
}

Bool
prima_window_reset_menu( Handle self, int newMenuHeight)
{
   Bool foo; return foo;
}

Bool
apc_window_set_visible( Handle self, Bool show)
{
   Bool foo; return foo;
}

/* apc_window_set_menu is in apc_menu.c */

Bool
apc_window_set_icon( Handle self, Handle icon)
{
   Bool foo; return foo;
}

Bool
apc_window_set_window_state( Handle self, int state)
{
   Bool foo; return foo;
}

static Bool
window_start_modal( Handle self, Bool shared, Handle insert_before)
{
   Bool foo; return foo;
}

Bool
apc_window_execute( Handle self, Handle insert_before)
{
   Bool foo; return foo;
}

Bool
apc_window_execute_shared( Handle self, Handle insert_before)
{
   Bool foo; return foo;
}

Bool
apc_window_end_modal( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_get_on_top( Handle self)
{
   Bool foo; return foo;
}
