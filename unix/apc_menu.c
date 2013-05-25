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
/*  System dependent menu routines (unix, x11)             */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include "Menu.h"
#include "Image.h"
#include "Window.h"
#include "Application.h"
#define XK_MISCELLANY
#define XK_LATIN1
#define XK_XKB_KEYS
#include <X11/keysymdef.h>

#define TREE            (PAbstractMenu(self)->tree)

static PMenuWindow
get_menu_window( Handle self, XWindow xw)
{
   return nil;
}

extern Cursor predefined_cursors[];

static PMenuWindow
get_window( Handle self, PMenuItemReg m)
{
   return nil;
}

static int
item_count( PMenuWindow w)
{
   int foo; return foo;
}

static void
free_unix_items( PMenuWindow w)
{
}

static void
menu_window_delete_downlinks( PMenuSysData XX, PMenuWindow wx)
{
}

#define MENU_XOFFSET 5
#define MENU_CHECK_XOFFSET 10

static int
get_text_width( PCachedFont font, const char * text, int byte_length, Bool utf8, uint32_t * xft_map8)
{
   int foo; return foo;
}

typedef struct {
   void        * xft_drawable;
   uint32_t    * xft_map8;
   Color         rgb;
   unsigned long pixel;
   XWindow       win;
   GC            gc;
} MenuDrawRec;

static void
get_font_abc( PCachedFont font, char * index, Bool utf8, FontABC * rec, MenuDrawRec * data)
{
}

static void
text_out( PCachedFont font, const char * text, int length, int x, int y, 
          Bool utf8, MenuDrawRec * data)
{
}

static void
update_menu_window( PMenuSysData XX, PMenuWindow w)
{
}

static int
menu_point2item( PMenuSysData XX, PMenuWindow w, int x, int y, PMenuItemReg * m_ptr)
{
   int foo; return foo;
}

static Point
menu_item_offset( PMenuSysData XX, PMenuWindow w, int index)
{
   Point foo; return foo;
}

static Point
menu_item_size( PMenuSysData XX, PMenuWindow w, int index)
{
   Point foo; return foo;
}

static void
menu_select_item( PMenuSysData XX, PMenuWindow w, int index)
{
}

static Bool
send_cmMenu( Handle self, PMenuItemReg m)
{
   Bool foo; return foo;
}

static Bool
menu_enter_item( PMenuSysData XX, PMenuWindow w, int index, int type)
{
   Bool foo; return foo;
}


static void
store_char( char * src, int srclen, int * srcptr, char * dst, int * dstptr, Bool utf8, MenuDrawRec * data)
{
}

void
prima_handle_menu_event( XEvent *ev, XWindow win, Handle self)
{
}

int prima_handle_menu_shortcuts( Handle self, XEvent * ev, KeySym keysym) {
   int foo; return foo;
}

void prima_end_menu(void) {}

Bool apc_menu_create( Handle self, Handle owner) { Bool foo; return foo; }

Bool apc_menu_destroy( Handle self) { Bool foo; return foo; }

PFont apc_menu_default_font( PFont f) { return nil; }

Color apc_menu_get_color( Handle self, int index) { Color c; return c; }

/* apc_menu_set_font is in apc_font.c */

void menu_touch( Handle self, PMenuItemReg who, Bool kill) {}

static void  menu_reconfigure( Handle self) {}

static void menubar_repaint( Handle self) {}

Bool
apc_menu_update( Handle self, PMenuItemReg oldBranch, PMenuItemReg newBranch)
{ Bool foo; return foo; }
 
Bool apc_menu_item_delete( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_accel( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_check( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_enabled( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_image( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_key( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_text( Handle self, PMenuItemReg m) { Bool foo; return foo; }

ApiHandle apc_menu_get_handle( Handle self) { return nilHandle; }

Bool apc_popup_create( Handle self, Handle owner) { Bool foo; return foo; }

PFont apc_popup_default_font( PFont f) { return nil; }

Bool apc_popup( Handle self, int x, int y, Rect *anchor) { Bool foo; return foo; }

Bool apc_window_set_menu( Handle self, Handle menu) { Bool foo; return foo; }
