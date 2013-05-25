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
/*  System dependent miscellaneous routines (unix, x11)    */
/*                                                         */
/***********************************************************/

#include <apricot.h>
#include <sys/stat.h>
#include "unix/guts.h"
#include "Application.h"
#include "File.h"
#include "Icon.h"
#define XK_MISCELLANY
#include <X11/keysymdef.h>

/* Miscellaneous system-dependent functions */

#define X_COLOR_TO_RGB(xc)     (ARGB(((xc).red>>8),((xc).green>>8),((xc).blue>>8)))
#define RANGE(a)        { if ((a) < -16383) (a) = -16383; else if ((a) > 16383) a = 16383; }
#define RANGE2(a,b)     RANGE(a) RANGE(b)

Bool
log_write( const char *format, ...)
{
   Bool foo; return foo;
}




int
unix_rm_get_int( Handle self, XrmQuark class_detail, XrmQuark name_detail, int default_value)
{
   int foo; return foo;
}

Bool
apc_fetch_resource( const char *className, const char *name,
                    const char *resClass, const char *res,
                    Handle owner, int resType,
                    void *result)
{
   Bool foo; return foo;
}

Color
apc_lookup_color( const char * colorName)
{
   Color foo; return foo;
}

/* Component-related functions */

Bool
apc_component_create( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_component_destroy( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_component_fullname_changed_notify( Handle self)
{
   Bool foo; return foo;
}

/* Cursor support */

void
prima_no_cursor( Handle self)
{
}

void
prima_update_cursor( Handle self)
{
}

void
prima_cursor_tick( void)
{
}

Bool
apc_cursor_set_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_cursor_set_size( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_cursor_set_visible( Handle self, Bool visible)
{
   Bool foo; return foo;
}

Point
apc_cursor_get_pos( Handle self)
{
   Point foo; return foo;
}

Point
apc_cursor_get_size( Handle self)
{
   Point foo; return foo;
}

Bool
apc_cursor_get_visible( Handle self)
{
   Bool foo; return foo;
}

/* File */

void
prima_rebuild_watchers( void)
{
}

Bool
apc_file_attach( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_file_detach( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_file_change_mask( Handle self)
{
   Bool foo; return foo;
}

int
apc_pointer_get_state( Handle self)
{
   int foo; return foo;
}

int
apc_kbd_get_state( Handle self)
{
   int foo; return foo;
}

/* Messages */

Bool
prima_simple_message( Handle self, int cmd, Bool is_post)
{
   Bool foo; return foo;
}

Bool
apc_message( Handle self, PEvent e, Bool is_post)
{
   Bool foo; return foo;
}


void
prima_msgdlg_event( XEvent * ev, struct MsgDlg * md)
{
}
     
extern char ** Drawable_do_text_wrap( Handle, TextWrapRec *);

Bool
apc_show_message( const char * message, Bool utf8)
{
   Bool foo; return foo;
}

/* system metrics */

Bool
apc_sys_get_insert_mode( void)
{
   Bool foo; return foo;
}

PFont
apc_sys_get_msg_font( PFont f)
{
   return nil;
}

PFont
apc_sys_get_caption_font( PFont f)
{
   return nil;
}

int
apc_sys_get_value( int v)  /* XXX one big XXX */
{
   int foo; return foo;
}

Bool
apc_sys_set_insert_mode( Bool insMode)
{
   Bool foo; return foo;
}

/* etc */

Bool
apc_beep( int style)
{
   Bool foo; return foo;
}

Bool
apc_beep_tone( int freq, int duration)
{
   Bool foo; return foo;
}

char *
apc_system_action( const char *s)
{
   char * foo; return foo;
}

Bool
apc_query_drives_map( const char* firstDrive, char *result, int len)
{
   Bool foo; return foo;
}

int
apc_query_drive_type( const char *drive)
{
   int foo; return foo;
}

char *
apc_get_user_name( void)
{
   char * foo; return foo;
}

Bool
apc_dl_export(char *path)
{
   Bool foo; return foo;
}

PList
apc_getdir( const char *dirname)
{
   return nil;
}

void
prima_rect_union( XRectangle *t, const XRectangle *s)
{
}

void
prima_rect_intersect( XRectangle *t, const XRectangle *s)
{
}


void
prima_utf8_to_wchar( const char * utf8, XChar2b * u16, int src_len_bytes, int target_len_xchars )
{
}

XChar2b *
prima_alloc_utf8_to_wchar( const char * utf8, int length_chars)
{
   XChar2b * foo; return foo;
}

void 
prima_wchar2char( char * dest, XChar2b * src, int lim)
{
}

void 
prima_char2wchar( XChar2b * dest, char * src, int lim)
{
}

char *
apc_last_error( void )
{
   char * foo; return foo;
}
