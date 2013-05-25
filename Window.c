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
   return var-> modal;
}

SV *
Window_get_client_handle( Handle self)
{
   return nilSV;
}

Handle
Window_get_modal_window( Handle self, int modalFlag, Bool next)
{
   if ( modalFlag == mtExclusive) {
      return next ? var-> nextExclModal   : var-> prevExclModal;
   } else if ( modalFlag == mtShared) {
      return next ? var-> nextSharedModal : var-> prevSharedModal;
   } 
   return nilHandle;
}

Handle
Window_get_horizon( Handle self)
{
   /* self trick is appropriate here;
      don't bump into it accidentally */
   self = var-> owner;
   while ( self != application && !my-> get_modalHorizon( self))
      self = var-> owner;
   return self;
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
   if ( var-> modal)
      return mbCancel;

   protect_object( self);
   if ( insertBefore
	&& ( insertBefore == self
	     || !kind_of( insertBefore, CWindow)
	     || PWindow( insertBefore)-> modal != mtExclusive))
      insertBefore = nilHandle;
   if ( !apc_window_execute( self, insertBefore))
      var-> modalResult = mbCancel;

   unprotect_object( self);
   return var-> modalResult;
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
   if ( !set)
      return var-> modalResult;
   return var-> modalResult = modalResult;
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
   if ( var-> stage > csFrozen) return nilHandle;

   if ( !set) {
      if ( apc_window_get_icon( self, nilHandle)) {
         HV * profile = newHV();
         Handle i = Object_create( "Prima::Icon", profile);
         sv_free(( SV *) profile);
         apc_window_get_icon( self, i);
         --SvREFCNT( SvRV((( PAnyObject) i)-> mate));
         return i;
      } else
         return nilHandle;
   }

   if ( icon && !kind_of( icon, CImage)) {
       warn("RTC0091: Illegal object reference passed to Window::icon");
       return nilHandle;
   }
   my-> first_that( self, (void*)icon_notify, (void*)icon);
   apc_window_set_icon( self, icon);
   opt_clear( optOwnerIcon);
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
   HV * profile;
   if ( !set)
      return apc_window_get_border_icons( self);
   profile = newHV();
   pset_i( borderIcons, borderIcons);
   my-> set( self, profile);
   sv_free(( SV *) profile);
   return nilHandle;
}

int
Window_borderStyle( Handle self, Bool set, int borderStyle)
{
   HV * profile;
   if ( !set)
      return apc_window_get_border_style( self);
   profile = newHV();
   pset_i( borderStyle, borderStyle);
   my-> set( self, profile);
   sv_free(( SV *) profile);
   return nilHandle;
}

Point
Window_frameOrigin( Handle self, Bool set, Point frameOrigin)
{
   if ( !set)
      return apc_widget_get_pos( self);
   apc_widget_set_pos( self, frameOrigin.x, frameOrigin.y);
   return frameOrigin;
}

Point
Window_frameSize( Handle self, Bool set, Point frameSize)
{
   if ( !set)
      return apc_widget_get_size( self);
   apc_widget_set_size( self, frameSize.x, frameSize.y);
   return frameSize;
}

Point
Window_origin( Handle self, Bool set, Point origin)
{
   if ( !set)
      return apc_window_get_client_pos( self);
   apc_window_set_client_pos( self, origin.x, origin.y);
   return origin;
}

Rect
Window_rect( Handle self, Bool set, Rect r)
{
   if ( !set) 
      return inherited rect( self, set, r); 
   apc_window_set_client_rect( self, r. left, r. bottom, r. right - r. left, r. top - r. bottom);
   return r;
}

Bool
Window_selected( Handle self, Bool set, Bool selected)
{
   return false;
}

Point
Window_size( Handle self, Bool set, Point size)
{
   if ( !set)
      return apc_window_get_client_size( self);
   apc_window_set_client_size( self, size.x, size.y);
   return size;
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
   if ( !set)
      return apc_window_get_window_state( self);
   return ( int) apc_window_set_window_state( self, windowState);
}

#ifdef __cplusplus
}
#endif
