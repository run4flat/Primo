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
#include "Timer.h"
#include "Window.h"
#include "Image.h"
#include "Application.h"
#include <Application.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CWidget->
#define my  ((( PApplication) self)-> self)
#define var (( PApplication) self)

static void Application_HintTimer_handle_event( Handle, PEvent);

void
Application_init( Handle self, HV * profile)
{
}

void
Application_done( Handle self)
{
}

void
Application_cleanup( Handle self)
{
}


void
Application_set( Handle self, HV * profile)
{
}

void Application_handle_event( Handle self, PEvent event)
{
}

void
Application_sync( char * dummy)
{
}

void
Application_yield( char * dummy)
{
}

Bool
Application_begin_paint( Handle self)
{
   return false;
}

Bool
Application_begin_paint_info( Handle self)
{
   return false;
}

void
Application_detach( Handle self, Handle objectHandle, Bool kill)
{
}

void
Application_end_paint( Handle self)
{
}

void
Application_end_paint_info( Handle self)
{
}

Bool
Application_focused( Handle self, Bool set, Bool focused)
{
   return false;
}

void Application_bring_to_front( Handle self) {}
void Application_show( Handle self) {}
void Application_hide( Handle self) {}
void Application_insert_behind( Handle self, Handle view) {}
void Application_send_to_back( Handle self) {}

SV*
Application_fonts( Handle self, char * name, char * encoding)
{
   return nilSV;
}

SV*
Application_font_encodings( Handle self, char * encoding)
{
   return nilSV;
}

Font
Application_get_default_font( char * dummy)
{
   Font foo; return foo;
}

Font
Application_get_message_font( char * dummy)
{
   Font foo; return foo;
}

Font
Application_get_caption_font( char * dummy)
{
   Font foo; return foo;
}


int
Application_get_default_cursor_width( char * dummy)
{
   int foo; return foo;
}

Point
Application_get_default_scrollbar_metrics( char * dummy)
{
   Point foo; return foo;
}

Point
Application_get_default_window_borders( char * dummy, int borderStyle)
{
   Point foo; return foo;
}

int
Application_get_system_value( char * dummy, int sysValue)
{
   int foo; return foo;
}

SV *
Application_get_system_info( char * dummy)
{
   return nilSV;
}

Handle
Application_get_widget_from_handle( Handle self, SV * handle)
{
   return nilHandle;
}

Handle
Application_get_hint_widget( Handle self)
{
   return nilHandle;
}

static Bool
icon_notify ( Handle self, Handle child, Handle icon)
{
   return false;
}

Handle
Application_icon( Handle self, Bool set, Handle icon)
{
   return nilHandle;
}

Handle
Application_get_focused_widget( Handle self)
{
   return nilHandle;
}

Handle
Application_get_active_window( Handle self)
{
   return nilHandle;
}

Bool
Application_autoClose( Handle self, Bool set, Bool autoClose)
{
   return false;
}

SV *
Application_sys_action( char * dummy, char * params)
{
   return nilSV;
}

typedef struct _SingleColor
{
   Color color;
   int   index;
} SingleColor, *PSingleColor;


Color
Application_colorIndex( Handle self, Bool set, int index, Color color)
{
   Color c; return c;
}

void
Application_set_font( Handle self, Font font)
{
}


Bool
Application_close( Handle self)
{
   return false;
}

Bool
Application_insertMode( Handle self, Bool set, Bool insMode)
{
   return false;
}


Handle 
Application_get_modal_window( Handle self, int modalFlag, Bool topMost)
{
   return nilHandle;
}

Handle
Application_get_parent( Handle self)
{
   return nilHandle;
}

Point
Application_get_scroll_rate( Handle self)
{
   Point foo; return foo;
}

static void hshow( Handle self)
{
}

void
Application_HintTimer_handle_event( Handle timer, PEvent event)
{
}

void
Application_set_hint_action( Handle self, Handle view, Bool show, Bool byMouse)
{
}

Color
Application_hintColor( Handle self, Bool set, Color hintColor)
{
   Color c; return c;
}

Color
Application_hintBackColor( Handle self, Bool set, Color hintBackColor)
{
   Color c; return c;
}

int
Application_hintPause( Handle self, Bool set, int hintPause)
{
   int foo; return foo;
}

void
Application_set_hint_font( Handle self, Font hintFont)
{
}


Font
Application_get_hint_font( Handle self)
{
   Font foo; return foo;
}

Bool
Application_showHint( Handle self, Bool set, Bool showHint)
{
   return false;
}

Handle Application_next( Handle self) { return nilHandle; }
Handle Application_prev( Handle self) { return nilHandle; }

SV *
Application_palette( Handle self, Bool set, SV * palette)
{
   return nilSV;
}

Handle
Application_top_frame( Handle self, Handle from)
{
   return nilHandle;
}

Handle
Application_get_image( Handle self, int x, int y, int xLen, int yLen)
{
   return nilHandle;
}

/*
 * Cannot return nilHandle.
 */
Handle
Application_map_focus( Handle self, Handle from)
{
   return nilHandle;
}

static Handle
popup_win( Handle xTop)
{
   return nilHandle;
}

Handle
Application_popup_modal( Handle self)
{
   return nilHandle;
}

Bool
Application_pointerVisible( Handle self, Bool set, Bool pointerVisible)
{
   return false;
}

Point
Application_size( Handle self, Bool set, Point size)
{
   Point foo; return foo;
}

Point
Application_origin( Handle self, Bool set, Point origin)
{
   Point foo; return foo;
}

Bool
Application_modalHorizon( Handle self, Bool set, Bool modalHorizon)
{
   return false;
}

Bool
Application_wantUnicodeInput( Handle self, Bool set, Bool want_ui)
{
   return false;
}


void   Application_update_sys_handle( Handle self, HV * profile) {}
Bool   Application_get_capture( Handle self) { return false; }
void   Application_set_capture( Handle self, Bool capture, Handle confineTo) {}
void   Application_set_centered( Handle self, Bool x, Bool y) {}

Bool   Application_tabStop( Handle self, Bool set, Bool tabStop)       { return false; }
Bool   Application_selectable( Handle self, Bool set, Bool selectable) { return false; }
Handle Application_shape( Handle self, Bool set, Handle mask)          { return nilHandle; }
Bool   Application_syncPaint( Handle self, Bool set, Bool syncPaint)   { return false; }
Bool   Application_visible( Handle self, Bool set, Bool visible)       { return false; }
Bool   Application_buffered( Handle self, Bool set, Bool buffered)     { return false; }
Bool   Application_enabled( Handle self, Bool set, Bool enable)        { return false; }
int    Application_growMode( Handle self, Bool set, int flags)         { int foo; return foo; }
Bool   Application_hintVisible( Handle self, Bool set, Bool visible)   { return false; }
Handle Application_owner( Handle self, Bool set, Handle owner)         { return nilHandle; }
Bool   Application_ownerColor( Handle self, Bool set, Bool ownerColor) { return false; }
Bool   Application_ownerBackColor( Handle self, Bool set, Bool ownerBackColor) { return false; }
Bool   Application_ownerFont( Handle self, Bool set, Bool ownerFont)   { return false; }
Bool   Application_ownerShowHint( Handle self, Bool set, Bool ownerShowHint) { return false; }
Bool   Application_ownerPalette( Handle self, Bool set, Bool ownerPalette) { return false; }
Bool   Application_clipOwner( Handle self, Bool set, Bool clipOwner)   { return false; }
int    Application_tabOrder( Handle self, Bool set, int tabOrder)      { int foo; return foo; }
SV   * Application_text    ( Handle self, Bool set, SV * text)       { return nilSV; }
Bool   Application_transparent( Handle self, Bool set, Bool transparent) { return false; }
Bool   Application_validate_owner( Handle self, Handle * owner, HV * profile) { return false; }

#ifdef __cplusplus
}
#endif
