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

unsigned char * 
prima_get_window_property( XWindow window, Atom property, Atom req_type, Atom * actual_type,
                           int * actual_format, unsigned long * nitems)
{
   unsigned char * foo; return foo;
}

Bool
prima_wm_net_state_read_maximization( XWindow window, Atom property)
/*
   reads property, returns true if it has both vertical and horizontal properties set.
  */
{
   Bool foo; return foo;
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
   return nilHandle;
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
   return nilHandle;
}

Point
apc_window_get_client_pos( Handle self)
{
   Point foo; return foo;
}

Point
apc_window_get_client_size( Handle self)
{
   Point foo; return foo;
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
   XWindow foo; return foo;
}

Bool
prima_get_frame_info( Handle self, PRect r)
{
   Bool foo; return foo;
}

void
apc_SetWMNormalHints( Handle self, XSizeHints * hints)
{
}


Bool
apc_window_set_client_pos( Handle self, int x, int y)
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
