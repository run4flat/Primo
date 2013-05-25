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
#include "Window.h"
#include "Icon.h"
#include "Application.h"
#include <Window.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CWidget->
#define my  ((( PWindow) self)-> self)
#define var (( PWindow) self)


void
Window_init( Handle self, HV * profile)
{
}

void
Window_cancel( Handle self)
{
}

void
Window_ok( Handle self)
{
}


void
Window_cleanup( Handle self)
{
}

void Window_update_sys_handle( Handle self, HV * profile)
{
}

void Window_handle_event( Handle self, PEvent event)
{
}

void
Window_end_modal( Handle self)
{
}

int
Window_get_modal( Handle self)
{
   int foo; return foo;
}

SV *
Window_get_client_handle( Handle self)
{
   return nilSV;
}

Handle
Window_get_modal_window( Handle self, int modalFlag, Bool next)
{
   return nilHandle;
}

Handle
Window_get_horizon( Handle self)
{
   return nilHandle;
}


void
Window_exec_enter_proc( Handle self, Bool sharedExec, Handle insertBefore)
{
}

void
Window_exec_leave_proc( Handle self)
{
}

void
Window_cancel_children( Handle self)
{
}


int
Window_execute( Handle self, Handle insertBefore)
{
   int foo; return foo;
}

Bool
Window_execute_shared( Handle self, Handle insertBefore)
{
   return false;
}

Bool
Window_modalHorizon( Handle self, Bool set, Bool modalHorizon)
{
   return false;
}

int
Window_modalResult ( Handle self, Bool set, int modalResult)
{
   int foo; return foo;
}

static void
activate( Handle self, Bool ok)
{
}

Bool
Window_focused( Handle self, Bool set, Bool focused)
{
   return false;
}

void Window_set( Handle self, HV * profile)
{
}

static Bool
icon_notify ( Handle self, Handle child, Handle icon)
{
   return false;
}

Handle
Window_icon( Handle self, Bool set, Handle icon)
{
   return nilHandle;
}

Bool
Window_mainWindow( Handle self, Bool set, Bool mainWindow)
{
   return false;
}

Bool
Window_onTop( Handle self, Bool set, Bool onTop)
{
   return false;
}

Bool
Window_ownerIcon( Handle self, Bool set, Bool ownerIcon)
{
   return false;
}

Bool
Window_process_accel( Handle self, int key)
{
   return false;
}

void  Window_on_execute( Handle self) {}
void  Window_on_endmodal( Handle self) {}
void  Window_on_activate( Handle self) {}
void  Window_on_deactivate( Handle self) {}
void  Window_on_windowstate( Handle self, int windowState) {}

Bool
Window_transparent( Handle self, Bool set, Bool transparent)
{
   return false;
}

int
Window_borderIcons( Handle self, Bool set, int borderIcons)
{
   int foo; return foo;
}

int
Window_borderStyle( Handle self, Bool set, int borderStyle)
{
   int foo; return foo;
}

Point
Window_frameOrigin( Handle self, Bool set, Point frameOrigin)
{
   Point foo; return foo;
}

Point
Window_frameSize( Handle self, Bool set, Point frameSize)
{
   Point foo; return foo;
}

Point
Window_origin( Handle self, Bool set, Point origin)
{
   Point foo; return foo;
}

Rect
Window_rect( Handle self, Bool set, Rect r)
{
   Rect foo; return foo;
}

Bool
Window_selected( Handle self, Bool set, Bool selected)
{
   return false;
}

Point
Window_size( Handle self, Bool set, Point size)
{
   Point foo; return foo;
}

Bool
Window_taskListed( Handle self, Bool set, Bool taskListed)
{
   return false;
}


SV *
Window_text( Handle self, Bool set, SV * text)
{
   return nilSV;
}

Bool
Window_validate_owner( Handle self, Handle * owner, HV * profile)
{
   return false;
}

int
Window_windowState( Handle self, Bool set, int windowState)
{
   int foo; return foo;
}

#ifdef __cplusplus
}
#endif
