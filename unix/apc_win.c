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
   long * prop;
   unsigned long i, n;
   int horiz = 0, vert = 0;

   if ( guts. icccm_only) return false;

   prop = ( long *) prima_get_window_property( window, property, XA_ATOM, NULL, NULL, &n);
   if ( !prop) return false;

   for ( i = 0; i < n; i++) {
      if ( prop[i] == NET_WM_STATE_MAXIMIZED_VERT) vert = 1;
      /* KDE v2 defines _HORIZ, KDE v3 defines _HORZ - a horrible hack follows */
      else if ( prop[i] == guts. atoms[ AI_NET_WM_STATE_MAXIMIZED_HORZ]) {
         if ( guts. net_wm_maximize_HORZ_vs_HORIZ == 0) {
            guts. net_wm_maximize_HORZ_vs_HORIZ = AI_NET_WM_STATE_MAXIMIZED_HORZ;
            Mdebug("wm: kde-3 style detected\n");
         }
         horiz = 1;
      }
      else if ( prop[i] == guts. atoms[ AI_NET_WM_STATE_MAXIMIZED_HORIZ]) {
         if ( guts. net_wm_maximize_HORZ_vs_HORIZ == 0) {
            guts. net_wm_maximize_HORZ_vs_HORIZ = AI_NET_WM_STATE_MAXIMIZED_HORIZ;
            Mdebug("wm: kde-2 style detected\n");
         }
         horiz = 1;
      }
   }  

   free( prop);
   return vert && horiz;
}

static Bool
net_supports_maximization(void)
/* If WM supports customization, root.NET_SUPPORTED contains NET_WM_STATE_MAXIMIZED atoms.
   Stores result in guts. net_wm_maximization, so ConfigureEvent handler doesn't apply
   maximization heuristics. */
{
   Bool has_max;
   has_max = prima_wm_net_state_read_maximization( guts. root, NET_SUPPORTED);
   if ( has_max != guts. net_wm_maximization) {
      guts. net_wm_maximization = has_max;
      Mdebug( has_max ? "wm: supports maximization\n" : "win: WM quits supporting maximization\n");
   }
   return has_max;
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
   DEFXX;
   Handle real_owner;
   XSizeHints hints;
   XSetWindowAttributes attrs;
   Point p0 = {0,0};
   Atom atoms[ 2];
   XWMHints wmhints;
   XClassHint *class_hint;
   ConfigureEventPair *cep;

   if ( border_style != bsSizeable) border_style = bsDialog;
   border_icons &= biAll;

   if ( X_WINDOW) { /* recreate request */
      Bool destructive_motif_hints = 0; /* KDE 3.1: setting motif hints kills net_wm hints */
      if ( !guts.icccm_only && (
           ( border_style != ( XX-> flags. sizeable ? bsSizeable : bsDialog)) ||
           ( border_icons != XX-> borderIcons) || 
	   ( on_top >= 0)
         )) {
	 Bool visible = XX-> flags. mapped;
	 if (
           ( border_style != ( XX-> flags. sizeable ? bsSizeable : bsDialog)) ||
           ( border_icons != XX-> borderIcons))
	    destructive_motif_hints = 1;
	 if ( destructive_motif_hints && on_top < 0)
	    on_top = apc_window_get_on_top( self);
	 if ( visible) {
	    XUnmapWindow( DISP, X_WINDOW);
            prima_wm_sync( self, UnmapNotify);
	 }
         if ( destructive_motif_hints)
            set_motif_hints( X_WINDOW, border_style, border_icons);
	 if ( on_top >= 0)
	    set_net_hints( X_WINDOW, -1, -1, -1, on_top);
	 if ( visible) { 
	    XMapWindow( DISP, X_WINDOW);
            prima_wm_sync( self, MapNotify);
	 }
         XX-> borderIcons = border_icons;
         XX-> flags. sizeable = ( border_style == bsSizeable) ? 1 : 0;
      }
      if (
            (( task_list ? 1 : 0) != ( XX-> flags. task_listed ? 1 : 0)) 
	    || destructive_motif_hints
	 )
         apc_window_task_listed( self, task_list);
      return true; 
   }   

   /* create */
   attrs. event_mask = 0
      | KeyPressMask              /* Key events unmasked for both windows, since */
      | KeyReleaseMask            /* focusing is unpredicatble for some WM */
      /*| ButtonPressMask */
      /*| ButtonReleaseMask */
      /*| EnterWindowMask */
      /*| LeaveWindowMask */
      /*| PointerMotionMask */
      /* | PointerMotionHintMask */
      /* | Button1MotionMask */
      /* | Button2MotionMask */
      /* | Button3MotionMask */
      /* | Button4MotionMask */
      /* | Button5MotionMask */
      /*| ButtonMotionMask */
      /*| KeymapStateMask */
      | ExposureMask
      | VisibilityChangeMask
      | StructureNotifyMask
      /* | ResizeRedirectMask */
      /* | SubstructureNotifyMask */
      /* | SubstructureRedirectMask */
      | FocusChangeMask
      | PropertyChangeMask
      | ColormapChangeMask
      | OwnerGrabButtonMask;
   attrs. override_redirect = false;
   attrs. do_not_propagate_mask = attrs. event_mask;
   attrs. colormap = guts. defaultColormap;
   X_WINDOW = XCreateWindow( DISP, guts. root,
	                     0, 0, 1, 1, 0, guts. visual. depth,
	                     InputOutput, VISUAL,
	                     0
	                     /* | CWBackPixmap */
	                     /* | CWBackPixel */
	                     /* | CWBorderPixmap */
	                     /* | CWBorderPixel */
	                     /* | CWBitGravity */
	                     /* | CWWinGravity */
	                     /* | CWBackingStore */
	                     /* | CWBackingPlanes */
	                     /* | CWBackingPixel */
	                     | CWOverrideRedirect
	                     /* | CWSaveUnder */
	                     | CWEventMask
	                     /* | CWDontPropagate */
	                      | CWColormap 
	                     /* | CWCursor */
	                     , &attrs);
   if (!X_WINDOW) return false;

   attrs. event_mask = 0
      | KeyPressMask
      | KeyReleaseMask
      | ButtonPressMask
      | ButtonReleaseMask
      | EnterWindowMask
      | LeaveWindowMask
      | PointerMotionMask
      /* | PointerMotionHintMask */
      /* | Button1MotionMask */
      /* | Button2MotionMask */
      /* | Button3MotionMask */
      /* | Button4MotionMask */
      /* | Button5MotionMask */
      | ButtonMotionMask
      | KeymapStateMask
      | ExposureMask
      | VisibilityChangeMask
      | StructureNotifyMask
      /* | ResizeRedirectMask */
      /* | SubstructureNotifyMask */
      /* | SubstructureRedirectMask */
      | FocusChangeMask
      | PropertyChangeMask
      | ColormapChangeMask
      | OwnerGrabButtonMask;
   attrs. override_redirect = false;
   attrs. do_not_propagate_mask = attrs. event_mask;
   attrs. colormap = guts. defaultColormap;

   XX-> client = XCreateWindow( DISP, X_WINDOW,
	                     0, 0, 1, 1, 0, guts. visual. depth,
	                     InputOutput, VISUAL,
	                     0
	                     /* | CWBackPixmap */
	                     /* | CWBackPixel */
	                     /* | CWBorderPixmap */
	                     /* | CWBorderPixel */
	                     /* | CWBitGravity */
	                     /* | CWWinGravity */
	                     /* | CWBackingStore */
	                     /* | CWBackingPlanes */
	                     /* | CWBackingPixel */
	                     | CWOverrideRedirect
	                     /* | CWSaveUnder */
	                     | CWEventMask
	                     /* | CWDontPropagate */
	                      | CWColormap 
	                     /* | CWCursor */
	                     , &attrs);
   if (!XX-> client) return false;
   hash_store( guts.windows, &XX-> client, sizeof(XX-> client), (void*)self);
   hash_store( guts.windows, &X_WINDOW, sizeof(X_WINDOW), (void*)self);
   XCHECKPOINT;
   XMapWindow( DISP, XX-> client);

   XX-> flags. iconic = ( window_state == wsMinimized) ? 1 : 0;
   wmhints. flags = InputHint | StateHint;
   wmhints. input = false;
   wmhints. initial_state = XX-> flags. iconic ? IconicState : NormalState;
   XSetWMHints( DISP, X_WINDOW, &wmhints);
   XCHECKPOINT;

   atoms[ 0] = WM_DELETE_WINDOW;
   atoms[ 1] = WM_TAKE_FOCUS;
   XSetWMProtocols( DISP, X_WINDOW, atoms, 2);
   XCHECKPOINT;

   if (( class_hint = XAllocClassHint()) != nil) {
      class_hint-> res_class  = PComponent(application)-> name;
      class_hint-> res_name = CObject( self)-> className;
      XSetClassHint( DISP, X_WINDOW, class_hint);
      XFree (class_hint);
   }

   if ( guts. hostname. value)
      XSetWMClientMachine(DISP, X_WINDOW, &guts. hostname);
   XSetCommand(DISP, X_WINDOW, PL_origargv, PL_origargc);

   set_motif_hints( X_WINDOW, border_style, border_icons);
   XX-> borderIcons = border_icons;
  
   XX-> type.drawable = true;
   XX-> type.widget = true;
   XX-> type.window = true;

   real_owner = application;
   XX-> parent = guts. root;
   XX-> real_parent = nilHandle;
   XX-> udrawable = XX-> gdrawable = XX-> client;

   XX-> flags. clip_owner = false;
   XX-> flags. sync_paint = sync_paint;
   XX-> flags. task_listed = 1;

   XX-> above = nilHandle;
   XX-> owner = real_owner;
   apc_component_fullname_changed_notify( self);
   prima_send_create_event( X_WINDOW);
   if ( on_top > 0) set_net_hints( X_WINDOW, -1, -1, -1, 1);
   apc_window_task_listed( self, task_list);
   if ( border_style == bsSizeable) XX-> flags. sizeable = 1;

   /* setting initial size */
   XX-> size = guts. displaySize;
   if ( window_state != wsMaximized) {
      XX-> zoomRect. right = XX-> size. x;
      XX-> zoomRect. top   = XX-> size. y;
      XX-> size. x *= 0.75;
      XX-> size. y *= 0.75;
   } else {
      XX-> flags. zoomed = 1;
      set_net_hints( X_WINDOW, -1, -1, 1, -1);
      if ( net_supports_maximization()) {
         XX-> zoomRect. right = XX-> size. x;
         XX-> zoomRect. top   = XX-> size. y;
         XX-> size. x *= 0.75;
         XX-> size. y *= 0.75;
      }
   }
   XX-> origin. x = XX-> origin. y = 
   XX-> ackOrigin. x = XX-> ackOrigin. y = 
   XX-> ackSize. x = XX-> ackOrigin. y = 
   XX-> ackFrameSize. x = XX-> ackFrameSize.y = 0;
   
   bzero( &hints, sizeof( XSizeHints));
   hints. flags  = PBaseSize;
   hints. width  = hints. base_width  = XX-> size. x;
   hints. height = hints. base_height = XX-> size. y;
   XSetWMNormalHints( DISP, X_WINDOW, &hints);
   XResizeWindow( DISP, XX-> client, XX-> size. x, XX-> size. y); 
   XResizeWindow( DISP, X_WINDOW, XX-> size. x, XX-> size. y); 

   TAILQ_INIT( &XX-> configure_pairs);
   if (( cep = malloc( sizeof( ConfigureEventPair)))) {
      bzero( cep, sizeof( ConfigureEventPair));
      cep-> w = XX-> size. x;
      cep-> h = XX-> size. y;
      TAILQ_INSERT_TAIL( &XX-> configure_pairs, cep, link);
   }

   prima_send_cmSize( self, p0);
   
   return true;
}

Bool
apc_window_activate( Handle self)
{
   DEFXX;
   int rev;
   XWindow xfoc;
   XEvent ev;

   if ( !XX-> flags. mapped) return true;
   if ( guts. message_boxes) return false;
   if ( self && ( self != CApplication( application)-> map_focus( application, self)))
      return false;

   XMapRaised( DISP, X_WINDOW);
   if ( XX-> flags. iconic || XX-> flags. withdrawn)
      prima_wm_sync( self, MapNotify);
   XGetInputFocus( DISP, &xfoc, &rev);
   if ( xfoc == X_WINDOW || xfoc == XX-> client) return true;
   XSetInputFocus( DISP, XX-> client, RevertToParent, guts. currentFocusTime);
   XCHECKPOINT;

   XSync( DISP, false);
   while ( XCheckMaskEvent( DISP, FocusChangeMask|ExposureMask, &ev))
      prima_handle_event( &ev, nil);
   return true;
}

Bool
apc_window_is_active( Handle self)
{
   return apc_window_get_active() == self;
}

Bool
apc_window_close( Handle self)
{
   return prima_simple_message( self, cmClose, true);
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
   XWMHints * hints;
   Pixmap xor, and;
   unsigned int xx, xy, ax, ay, xd, ad;
   Bool ret;

   if ( !icon) 
      return X(self)-> flags. has_icon ? true : false;
   else
      if ( !X(self)-> flags. has_icon) return false;

   if ( !( hints = XGetWMHints( DISP, X_WINDOW))) return false;  
   if ( !icon || !hints-> icon_pixmap) {
      Bool ret = hints-> icon_pixmap != nilHandle;
      XFree( hints);
      return ret;
   }
   xor = hints-> icon_pixmap;
   and = hints-> icon_mask;
   XFree( hints); 

   {
      XWindow foo;
      unsigned int bar;
      int bar2;
      if ( !XGetGeometry( DISP, xor, &foo, &bar2, &bar2, &xx, &xy, &bar, &xd))
         return false;
      if ( and && (!XGetGeometry( DISP, and, &foo, &bar2, &bar2, &ax, &ay, &bar, &ad)))
         return false;
   } 

   CImage( icon)-> create_empty( icon, xx, xy, ( xd == 1) ? 1 : guts. qdepth);
   if ( !prima_std_query_image( icon, xor)) return false;
   
   if ( and) {
      HV * profile = newHV();
      Handle mask = Object_create( "Prima::Image", profile);
      sv_free(( SV *) profile);
      CImage( mask)-> create_empty( mask, ax, ay, ( ad == 1) ? imBW : guts. qdepth);
      ret = prima_std_query_image( mask, and);
      if (( PImage( mask)-> type & imBPP) != 1)
         CImage( mask)-> type( mask, true, imBW);
      if ( ret) {
         int i; 
         Byte *d = PImage(mask)-> data;
         for ( i = 0; i < PImage(mask)-> dataSize; i++, d++)
            *d = ~(*d);
      } else
         bzero( PImage( mask)-> data, PImage( mask)-> dataSize);
      if ( xx != ax || xy != ay)  {
         Point p;
         p.x = xx;
         p.y = xy;
         CImage( mask)-> size( mask, true, p);
      }
      memcpy( PIcon( icon)-> mask, PImage( mask)-> data, PIcon( icon)-> maskSize);
      Object_destroy( mask);
   }

   return true;
}

int
apc_window_get_window_state( Handle self)
{
   int foo; return foo;
}

Bool
apc_window_get_task_listed( Handle self)
{
   return X(self)-> flags. task_listed;
}

Bool
apc_window_set_caption( Handle self, const char *caption, Bool utf8)
{
   XTextProperty p;

   if ( utf8) {
      if ( XStringListToTextProperty(( char **) &caption, 1, &p) != 0) {
         XSetWMIconName( DISP, X_WINDOW, &p);
         XSetWMName( DISP, X_WINDOW, &p);
         XFree( p. value);
      }
      XChangeProperty( DISP, X_WINDOW, NET_WM_NAME, UTF8_STRING, 8, 
         PropModeReplace, ( unsigned char*) caption, strlen( caption) + 1);
      XChangeProperty( DISP, X_WINDOW, NET_WM_ICON_NAME, UTF8_STRING, 8, 
         PropModeReplace, ( unsigned char*) caption, strlen( caption) + 1);
   } else {
      XDeleteProperty( DISP, X_WINDOW, NET_WM_NAME);
      XDeleteProperty( DISP, X_WINDOW, NET_WM_ICON_NAME);
      if ( XStringListToTextProperty(( char **) &caption, 1, &p) != 0) {
         XSetWMIconName( DISP, X_WINDOW, &p);
         XSetWMName( DISP, X_WINDOW, &p);
         XFree( p. value);
      }
   }
   XFlush( DISP);
   return true;
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
   DEFXX;
   XWindow p, dummy;
   int px, py;
   unsigned int pw, ph, pb, pd;

   bzero( r, sizeof( Rect));
   p = prima_find_frame_window( X_WINDOW);
   if ( p == nilHandle) {
      r-> left = XX-> decorationSize. x;
      r-> top  = XX-> decorationSize. y;
   } else if ( p != X_WINDOW) 
      if ( !XTranslateCoordinates( DISP, X_WINDOW, p, 0, 0, &r-> left, &r-> bottom, &dummy))
         warn( "error in XTranslateCoordinates()");
      if ( !XGetGeometry( DISP, p, &dummy, &px, &py, &pw, &ph, &pb, &pd)) {
         warn( "error in XGetGeometry()");
      r-> right = pw - r-> left  - XX-> size. x;
      r-> top   = ph - r-> right - XX-> size. y;
   }
   r-> top += XX-> menuHeight;
   return true;
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
   DEFXX;
   XSizeHints hints;

   bzero( &hints, sizeof( XSizeHints));

   if ( XX-> flags. zoomed) {
      XX-> zoomRect. left = x;
      XX-> zoomRect. bottom = y;
      return true;
   }

   if ( x == XX-> origin. x && y == XX-> origin. y) return true;
   XX-> flags. position_determined = 1;

   if ( XX-> client == guts. grab_redirect) {
      XWindow rx;
      XTranslateCoordinates( DISP, XX-> client, guts. root, 0, 0, 
         &guts. grab_translate_mouse.x, &guts. grab_translate_mouse.y, &rx);
   }
  
   y = guts. displaySize.y - XX-> size.y - XX-> menuHeight - y;
   hints. flags = USPosition;
   hints. x = x - XX-> decorationSize. x;
   hints. y = y - XX-> decorationSize. y;
   XMoveWindow( DISP, X_WINDOW, hints. x, hints. y);
   prima_wm_sync( self, ConfigureNotify);
   return true;
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
   DEFXX;
   XSizeHints hints;
   PWidget widg = PWidget( self);
   Bool implicit_move = false;
   Point post, psize;
   ConfigureEventPair *cep;
   
   widg-> virtualSize. x = width;
   widg-> virtualSize. y = height;

   width = ( width >= widg-> sizeMin. x)
	  ? (( width <= widg-> sizeMax. x)
              ? width 
	      : widg-> sizeMax. x)
	  : widg-> sizeMin. x;
   if ( width == 0) width = 1;

   height = ( height >= widg-> sizeMin. y)
	  ? (( height <= widg-> sizeMax. y)
	      ? height
	      : widg-> sizeMax. y)
	  : widg-> sizeMin. y;
   if ( height == 0) height = 1;

   if ( XX-> flags. zoomed) {
      XX-> zoomRect. right = width;
      XX-> zoomRect. top   = height;
      return true;
   }

   bzero( &hints, sizeof( XSizeHints));
   hints. flags = USSize | ( XX-> flags. position_determined ? USPosition : 0);
   post = XX-> origin;
   psize = XX-> size;
   hints. x = XX-> origin. x - XX-> decorationSize. x;
   hints. y = guts. displaySize.y - height - XX-> menuHeight - XX-> origin. y - XX-> decorationSize.y;
   hints. width = width;
   hints. height = height + XX-> menuHeight;
   XX-> size. x = width;
   XX-> size. y = height;
   apc_SetWMNormalHints( self, &hints);
   XMoveResizeWindow( DISP, XX-> client, 0, XX-> menuHeight, width, height);
   if ( XX-> flags. position_determined) {
      XMoveResizeWindow( DISP, X_WINDOW, hints. x, hints. y, width, height + XX-> menuHeight);
      implicit_move = true;
   } else {
      XResizeWindow( DISP, X_WINDOW, width, height + XX-> menuHeight);
   }
   XCHECKPOINT;
   prima_send_cmSize( self, psize);
   if ( PObject( self)-> stage == csDead) return false; 
   prima_wm_sync( self, ConfigureNotify);
   if ( implicit_move && (( XX-> origin.x != post.x) || (XX-> origin.y != post.y))) {
      XX-> decorationSize. x =   XX-> origin.x - post. x;
      XX-> decorationSize. y = - XX-> origin.y + post. y;
   }
   if (( cep = malloc( sizeof( ConfigureEventPair)))) {
      bzero( cep, sizeof( ConfigureEventPair));
      cep-> w = hints. width;
      cep-> h = hints. height;
      TAILQ_INSERT_TAIL( &XX-> configure_pairs, cep, link);
   }
   return true;
}
  
Bool
apc_window_set_client_rect( Handle self, int x, int y, int width, int height)
{
   DEFXX;
   PWidget widg = PWidget( self);
   
   widg-> virtualSize. x = width;
   widg-> virtualSize. y = height;

   width = ( width >= widg-> sizeMin. x)
	  ? (( width <= widg-> sizeMax. x)
              ? width 
	      : widg-> sizeMax. x)
	  : widg-> sizeMin. x;
   if ( width == 0) width = 1;

   height = ( height >= widg-> sizeMin. y)
	  ? (( height <= widg-> sizeMax. y)
	      ? height
	      : widg-> sizeMax. y)
	  : widg-> sizeMin. y;
   if ( height == 0) height = 1;

   if ( XX-> flags. zoomed) {
      XX-> zoomRect. left = x;
      XX-> zoomRect. bottom = y;
      XX-> zoomRect. right = width;
      XX-> zoomRect. top   = height;
      return true;
   }
   
   if ( x == XX-> origin. x && y == XX-> origin. y && 
        width == XX-> size. x && height == XX-> size. y ) return true;
   
   apc_window_set_rect( self, x, y, width, height);
   return true;
}


Bool
apc_window_set_client_size( Handle self, int width, int height)
{
   DEFXX;
   if ( width == XX-> size. x && height == XX-> size. y) return true;
   return window_set_client_size( self, width, height);
}

Bool
prima_window_reset_menu( Handle self, int newMenuHeight)
{
   DEFXX;
   int ret = true;
   if ( newMenuHeight != XX-> menuHeight) {
      int oh = XX-> menuHeight;
      XX-> menuHeight = newMenuHeight;
      if ( PWindow(self)-> stage <= csNormal)
         ret = window_set_client_size( self, XX-> size.x, XX-> size.y);
      else
         XX-> size. y -= newMenuHeight - oh;
      
#ifdef HAVE_X11_EXTENSIONS_SHAPE_H
     if ( XX-> shape_extent. x != 0 || XX-> shape_extent. y != 0) {
        int ny = XX-> size. y + XX-> menuHeight - XX-> shape_extent. y;
        if ( XX-> shape_offset. y != ny) {
           XShapeOffsetShape( DISP, X_WINDOW, ShapeBounding, 0, ny - XX-> shape_offset. y);
           XX-> shape_offset. y = ny;
        }
     }
#endif     
   }
   return ret;
}

Bool
apc_window_set_visible( Handle self, Bool show)
{
   DEFXX;

   if ( show) {
      if ( XX-> flags. mapped) return true;
   } else {
      if ( !XX-> flags. mapped) return true;
   }

   XX-> flags. want_visible = show;
   if ( show) {
      Bool iconic = XX-> flags. iconic;
      if ( XX-> flags. withdrawn) {
         XWMHints wh;
         wh. initial_state = iconic ? IconicState : NormalState;
         wh. flags = StateHint;
         XSetWMHints( DISP, X_WINDOW, &wh);
         XX-> flags. withdrawn = 0;
      }   
      XMapWindow( DISP, X_WINDOW);
      XX-> flags. iconic = iconic;
      prima_wm_sync( self, MapNotify);
   } else {
      if ( XX-> flags. iconic) {
         XWithdrawWindow( DISP, X_WINDOW, SCREEN);
         XX-> flags. withdrawn = 1;
      } else
         XUnmapWindow( DISP, X_WINDOW);
      prima_wm_sync( self, UnmapNotify);
   }   
   XCHECKPOINT;
   return true;
}

/* apc_window_set_menu is in apc_menu.c */

Bool
apc_window_set_icon( Handle self, Handle icon)
{
   DEFXX;
   PIcon i = ( PIcon) icon;
   XIconSize * sz = nil; 
   Pixmap xor, and;
   XWMHints wmhints;
   int n;

   if ( !icon || i-> w == 0 || i-> h == 0) {
      if ( !XX-> flags. has_icon) return true;
      XX-> flags. has_icon = false;
      XDeleteProperty( DISP, X_WINDOW, XA_WM_HINTS);
      wmhints. flags = InputHint;
      wmhints. input = false; 
      XSetWMHints( DISP, X_WINDOW, &wmhints);
      return true;
   }

   if ( XGetIconSizes( DISP, guts.root, &sz, &n) && n > 0) {
      int zx = sz-> min_width, zy = sz-> min_height;
      while ( 1) {
         if ( i-> w <= zx || i-> h <= zy) break;
         zx += sz-> width_inc;
         zy += sz-> height_inc;
         if ( zx >= sz-> max_width || zy >= sz-> max_height) break;
      }
      if ( zx > sz-> max_width)  zx = sz-> max_width;
      if ( zy > sz-> max_height) zy = sz-> max_height;
      if (( zx != i-> w && zy != i-> h) || ( sz-> max_width != i-> w && sz-> max_height != i-> h)) {
         Point z;
         i = ( PIcon) i-> self-> dup( icon);
         z.x = zx;
         z.y = zy;
         i-> self-> size(( Handle) i, true, z);
      }
      XFree( sz);
   } 

   xor = prima_std_pixmap( icon, CACHE_LOW_RES);
   if ( !xor) goto FAIL;
   {
      GC gc;
      XGCValues gcv;
      
      and = XCreatePixmap( DISP, guts. root, i-> w, i-> h, 1);
      if ( !and) {
         XFreePixmap( DISP, xor);
         goto FAIL;
      }
      
      gcv. graphics_exposures = false;
      gc = XCreateGC( DISP, and, GCGraphicsExposures, &gcv);
      if ( X(icon)-> image_cache. icon) {
         XSetBackground( DISP, gc, 0xffffffff);
         XSetForeground( DISP, gc, 0x00000000);
         prima_put_ximage( and, gc, X(icon)-> image_cache. icon, 0, 0, 0, 0, i-> w, i-> h);
      } else {
         XSetForeground( DISP, gc, 0xffffffff);
         XFillRectangle( DISP, and, gc, 0, 0, i-> w + 1, i-> h + 1);
      }
      XFreeGC( DISP, gc);
   }
   if (( Handle) i != icon) Object_destroy(( Handle) i);

   wmhints. flags = InputHint | IconPixmapHint | IconMaskHint;
   wmhints. icon_pixmap = xor;
   wmhints. icon_mask   = and;
   wmhints. input       = false;
   XSetWMHints( DISP, X_WINDOW, &wmhints);
   XCHECKPOINT;

   XX-> flags. has_icon = true;
   
   return true;
FAIL:

   if (( Handle) i != icon) Object_destroy(( Handle) i);
   return false;
}

Bool
apc_window_set_window_state( Handle self, int state)
{
   DEFXX;
   Event e;
   int sync = 0, did_net_zoom = 0;

   switch ( state) {
   case wsMinimized:
       if ( XX-> flags. iconic) return false;
       break;
   case wsMaximized:
       if ( XX-> flags. zoomed) return false;
       break;
   case wsNormal:
       if ( !XX-> flags. iconic && !XX-> flags. zoomed) return false;
       break;
   default:
       return false;
   }   
   
   /* operate via NET_WM */
   if ( state == wsMaximized && !XX-> flags. zoomed && net_supports_maximization()) {
      Bool visible = XX-> flags. mapped;
      Rect zoomRect;
   /* net hints changes by themselves do not result in maximization -
      need explicit map/unmap. */
      if ( visible) {
	 XUnmapWindow( DISP, X_WINDOW);
         /* suppress reaction to UnmapNotify */
         XX-> flags. suppress_cmMinimize = 1;
         prima_wm_sync( self, UnmapNotify);
         XX-> flags. suppress_cmMinimize = 0;
	 /* in case WM removes NET properties on unmap ( pretty valid )
	    wait a bit so we can push our net hints. Still a race, but 
	    nothing bad if we lose - heuristic maximization works fine also, after all. */
	 XSync( DISP, false);
      }
      set_net_hints( X_WINDOW, -1, -1, 1, -1);
      zoomRect. left   = XX-> origin.x;
      zoomRect. bottom = XX-> origin.y;
      zoomRect. right  = XX-> size.x;
      zoomRect. top    = XX-> size.y;
      if ( visible) {
         XMapWindow( DISP, X_WINDOW);
         /* again, wait and suppress reaction to UnmapNotify */
         XX-> flags. suppress_cmMinimize = 1;
         prima_wm_sync( self, ConfigureNotify);
         XX-> flags. suppress_cmMinimize = 0;
	 if ( !prima_wm_net_state_read_maximization( X_WINDOW, NET_WM_STATE)) {
	    /* wm denies maximization request, or we lost in the race ( see above ),
	       do maximization by casual heuristic */
	    goto FALL_THROUGH;
	 }
      }
      XX-> zoomRect = zoomRect; /* often reset in ConfigureNotify to already maximized window */
      XX-> flags. zoomed = 1;
      did_net_zoom = 1;
      sync = 0;
   FALL_THROUGH:;
   }

   if ( !XX-> flags. withdrawn) {
      if ( state == wsMinimized) {
         XIconifyWindow( DISP, X_WINDOW, SCREEN);
         if ( XX-> flags. mapped) sync = UnmapNotify;
      } else {
         XMapWindow( DISP, X_WINDOW);
         if ( !XX-> flags. mapped && !did_net_zoom) sync = MapNotify;
      }   
   }     
   XX-> flags. iconic = ( state == wsMinimized) ? 1 : 0; 
   
   if ( state == wsMaximized && !XX-> flags. zoomed && !did_net_zoom) {
      int dx = ( XX-> decorationSize. x > 0 ) ? XX-> decorationSize. x : 2;
      int dy = ( XX-> decorationSize. y > 0 ) ? XX-> decorationSize. y : 20;
      XX-> zoomRect. left   = XX-> origin.x;
      XX-> zoomRect. bottom = XX-> origin.y;
      XX-> zoomRect. right  = XX-> size.x;
      XX-> zoomRect. top    = XX-> size.y;
      apc_window_set_rect( self, dx * 2, dy * 2, 
              guts. displaySize.x - dx * 4, guts. displaySize. y - XX-> menuHeight - dy * 4);
      if ( !XX-> flags. zoomed) sync = ConfigureNotify;
      XX-> flags. zoomed = 1;
   }

   if ( XX-> flags. zoomed && state != wsMaximized) {
      set_net_hints( X_WINDOW, -1, -1, 0, -1);
      apc_window_set_rect( self, XX-> zoomRect. left, XX-> zoomRect. bottom, 
         XX-> zoomRect. right, XX-> zoomRect. top);
      if ( XX-> flags. zoomed) sync = ConfigureNotify;
      XX-> flags. zoomed = 0; 
   }   

   bzero( &e, sizeof(e));
   e. gen. source = self;
   e. cmd = cmWindowState;
   e. gen. i = state;
   apc_message( self, &e, false);

   if ( sync) prima_wm_sync( self, sync);

   return true;
}

static Bool
window_start_modal( Handle self, Bool shared, Handle insert_before)
{
   DEFXX;
   Handle selectee;
   if ( guts. grab_widget)
      apc_widget_set_capture( guts. grab_widget, 0, 0);
   if (( XX-> preexec_focus = apc_widget_get_focused()))
      protect_object( XX-> preexec_focus);
   CWindow( self)-> exec_enter_proc( self, shared, insert_before);
   apc_widget_set_enabled( self, true);
   apc_widget_set_visible( self, true);
   apc_window_activate( self);
   selectee = CWindow(self)->get_selectee( self);
   if ( selectee && selectee != self) Widget_selected( selectee, true, true);
   prima_simple_message( self, cmExecute, true);
   guts. modal_count++;
   return true;
}

Bool
apc_window_execute( Handle self, Handle insert_before)
{
   DEFXX;
   Handle toplevel;
   
   if (!application) return false;

   toplevel = CApplication(application)-> get_modal_window(application, mtExclusive, true);
   if ( toplevel == nilHandle) {
      if ( 
          PWindow(self)-> owner && 
	  PWindow(self)-> owner != application
      ) 
         toplevel = PWindow(self)-> owner;
   }
   /* find main window */
   if ( toplevel == nilHandle) {
   	int i;
	PList l = & PWidget(application)-> widgets;
	for ( i = 0; i < l-> count; i++)
	    if ( PObject(l-> items[i])-> options. optMainWindow) {
	       toplevel = l-> items[i];
	       break;
	    }
   }
   if ( toplevel) XSetTransientForHint( DISP, X_WINDOW, PWidget(toplevel)-> handle);

   XX-> flags.modal = true;
   set_net_hints( X_WINDOW, -1, XX-> flags.modal, -1, -1);
   if ( !window_start_modal( self, false, insert_before))
      return false;

   protect_object( self);

   XSync( DISP, false);
   while ( prima_one_loop_round( true, true) && XX-> flags.modal)
      ;
   
   if ( toplevel) XSetTransientForHint( DISP, X_WINDOW, None);
   if ( X_WINDOW) set_net_hints( X_WINDOW, -1, XX-> flags.modal, -1, -1);
   unprotect_object( self);
   return true;
}

Bool
apc_window_execute_shared( Handle self, Handle insert_before)
{
   return window_start_modal( self, true, insert_before);
}

Bool
apc_window_end_modal( Handle self)
{
   PWindow win = PWindow(self);
   Handle modal, oldfoc;
   DEFXX;
   XX-> flags.modal = false;
   CWindow( self)-> exec_leave_proc( self);
   apc_widget_set_visible( self, false);
   if ( application) {
      modal = CApplication(application)->popup_modal( application);
      if ( !modal && win->owner)
         CWidget( win->owner)-> set_selected( win->owner, true);
      if (( oldfoc = XX-> preexec_focus)) {
         if ( PWidget( oldfoc)-> stage == csNormal)
            CWidget( oldfoc)-> set_focused( oldfoc, true);
         unprotect_object( oldfoc);
      }
   }
   if ( guts. modal_count > 0)
      guts. modal_count--;
   return true;
}

Bool
apc_window_get_on_top( Handle self)
{
   Atom type;
   long * prop;
   int format;
   unsigned long i, n, left;
   Bool on_top = 0;
   
   if ( guts. icccm_only) return false;
   
   if ( XGetWindowProperty( DISP, X_WINDOW, NET_WM_STATE, 0, 32, false, XA_ATOM,
          &type, &format, &n, &left, (unsigned char**)&prop) == Success) {
     if ( prop) {
         for ( i = 0; i < n; i++) {
            if ( 
	       prop[i] == NET_WM_STATE_STAYS_ON_TOP ||
	       prop[i] == NET_WM_STATE_ABOVE
	    ) {
	       on_top = 1;
	       break;
	    }
         }
         XFree(( unsigned char *) prop);
      }
   }

   return on_top;
}
