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
   dPROFILE;
   SV * sv;
   inherited init( self, profile);

   opt_set( optSystemSelectable);
   opt_assign( optOwnerIcon, pget_B( ownerIcon));
   opt_assign( optMainWindow, pget_B( mainWindow));
   my-> set_icon( self, pget_H( icon));
   my-> set_modalResult( self, pget_i( modalResult));
   my-> set_modalHorizon( self, pget_B( modalHorizon));
   CORE_INIT_TRANSIENT(Window);
}

void
Window_cancel( Handle self)
{
   my-> set_modalResult ( self, mbCancel);
   my-> end_modal( self);
}

void
Window_ok( Handle self)
{
   my-> set_modalResult ( self, mbOK);
   my-> end_modal( self);
}


void
Window_cleanup( Handle self)
{
   if ( var-> modal) my-> cancel( self);
   inherited cleanup( self);
}

void Window_update_sys_handle( Handle self, HV * profile)
{
   dPROFILE;
   var-> widgetClass = wcWindow;
   if (!(
       pexist( owner) ||
       pexist( syncPaint) ||
       pexist( taskListed) ||
       pexist( borderIcons) ||
       pexist( onTop) ||
       pexist( borderStyle)
    )) return;
   if ( pexist( owner)) my-> cancel_children( self);
   if ( !apc_window_create( self,
      pexist( owner )      ? pget_H( owner )      : var-> owner ,
      pexist( syncPaint)   ? pget_B( syncPaint)   : my-> get_syncPaint( self),
      pexist( borderIcons) ? pget_i( borderIcons) : my-> get_borderIcons( self),
      pexist( borderStyle) ? pget_i( borderStyle) : my-> get_borderStyle( self),
      pexist( taskListed)  ? pget_B( taskListed)  : my-> get_taskListed( self),
      pexist( windowState) ? pget_i( windowState) : my-> get_windowState( self),
      pexist( onTop) ? pget_B( onTop) : -1, /* This is way better. I should've thought of this before! */
      !( pexist( originDontCare) && pget_B( originDontCare)),
      !( pexist( sizeDontCare)   && pget_B( sizeDontCare))
   ))
      croak("RTC0090: Cannot create window");
   pdelete( borderStyle);
   pdelete( borderIcons);
   pdelete( syncPaint);
   pdelete( taskListed);
   pdelete( windowState);
   pdelete( onTop);
}

void Window_handle_event( Handle self, PEvent event)
{
#define evOK ( var-> evStack[ var-> evPtr - 1])
#define objCheck if ( var-> stage > csNormal) return
   switch (event-> cmd)
   {
   case cmExecute:
      my-> notify( self, "<s", "Execute");
      break;
   case cmEndModal:
      my-> notify( self, "<s", "EndModal");
      break;
   case cmActivate:
      if ( var-> owner)
         PWidget( var-> owner)-> currentWidget = self;
      my-> notify( self, "<s", "Activate");
      break;
   case cmDeactivate:
      my-> notify( self, "<s", "Deactivate");
      break;
   case cmWindowState:
      my-> notify( self, "<si", "WindowState", event-> gen. i);
      break;
   case cmDelegateKey:
      #define leave { my-> clear_event( self); return; }
      if ( var-> modal && event-> key. subcmd == 0)
      {
          Event ev = *event;
          ev. key. cmd   = cmTranslateAccel;
          if ( !my-> message( self, &ev)) leave;
          if ( my-> first_that( self, (void*)accel_notify, &ev)) leave;
          ev. key. cmd    = cmDelegateKey;
          ev. key. subcmd = 1;
          if ( my-> first_that( self, (void*)accel_notify, &ev)) leave;
      }
      objCheck;
      break;
   case cmTranslateAccel:
      if ( event-> key. key == kbEsc && var-> modal)
      {
         my-> cancel( self);
         my-> clear_event( self);
         return;
      }
      break;
   }
   inherited handle_event ( self, event);
}

void
Window_end_modal( Handle self)
{
   Event ev = { cmEndModal};
   if ( !var-> modal) return;

   apc_window_end_modal( self);
   ev. gen. source = self;
   my-> message( self, &ev);
}

int
Window_get_modal( Handle self)
{
   return var-> modal;
}

SV *
Window_get_client_handle( Handle self)
{
   char buf[ 256];
   snprintf( buf, 256, "0x%08lx", apc_window_get_client_handle( self));
   return newSVpv( buf, 0);
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
   if ( var-> modal)
      return;

   if ( sharedExec) {
      Handle mh = my-> get_horizon( self);
      var-> modal = mtShared;

      /* adding new modal horizon in global mh-list */
      if ( mh != application && !PWindow(mh)-> nextSharedModal)
         list_add( &PApplication( application)-> modalHorizons, mh);

      if (( var-> nextSharedModal = insertBefore)) {
         /* inserting window in between of modal list */
         Handle *iBottom = ( mh == application) ?
            &PApplication(mh)-> sharedModal : &PWindow(mh)-> nextSharedModal;
         var-> prevSharedModal = PWindow( insertBefore)-> prevSharedModal;
         if ( *iBottom == insertBefore)
            *iBottom = self;
      } else {
         /* inserting window on top of modal list */
         Handle *iTop = ( mh == application) ?
            &PApplication(mh)-> topSharedModal : &PWindow(mh)-> topSharedModal;
         if ( *iTop)
            PWindow( *iTop)-> nextSharedModal = self;
         else {
            if ( mh == application)
               PApplication(mh)-> sharedModal = self;
            else
               PWindow(mh)-> nextSharedModal = self;
         }
         var-> prevSharedModal = *iTop;
         *iTop = self;
      }
   }
   /* end of shared exec */
   else
   /* start of exclusive exec */
   {
      PApplication app = ( PApplication) application;
      var-> modal = mtExclusive;
      if (( var-> nextExclModal = insertBefore)) {
         var-> prevExclModal = PWindow( insertBefore)-> prevExclModal;
         if ( app-> exclModal == insertBefore)
            app-> exclModal = self;
      } else {
         var-> prevExclModal = app-> topExclModal;
         if ( app-> exclModal)
            PWindow( app-> topExclModal)-> nextExclModal = self;
         else
            app-> exclModal = self;
         app-> topExclModal = self;
      }
   }
}

void
Window_exec_leave_proc( Handle self)
{
   if ( !var-> modal)
      return;

   if ( var-> modal == mtShared) {
      Handle mh = my-> get_horizon( self);

      if ( var-> prevSharedModal) {
         PWindow prev = ( PWindow) var-> prevSharedModal;
         if ( prev-> nextSharedModal == self)
            prev-> nextSharedModal = var-> nextSharedModal;
      }
      if ( var-> nextSharedModal) {
         PWindow next = ( PWindow) var-> nextSharedModal;
         if ( next-> prevSharedModal == self)
            next-> prevSharedModal = var-> prevSharedModal;
      }
      if ( mh == application) {
         PApplication app = ( PApplication) application;
         if ( app) {
            if ( app-> sharedModal == self)
               app-> sharedModal = var-> nextSharedModal;
            if ( app-> topSharedModal == self)
               app-> topSharedModal = var-> prevSharedModal;
         }
      } else {
         PWindow win = ( PWindow) mh;
         if ( win-> nextSharedModal == self)
            win-> nextSharedModal = var-> nextSharedModal;
         if ( win-> topSharedModal == self)
            win-> topSharedModal = var-> prevSharedModal;
         /* removing horizon from global mh-list */
         if ( !win-> nextSharedModal)
             list_delete( &PApplication(application)-> modalHorizons, mh);
      }

      var-> prevSharedModal = var-> nextSharedModal = nilHandle;
   } /* end of shared exec */
   else
   /* start of exclusive exec */
   {
      PApplication app = ( PApplication) application;
      if ( var-> prevExclModal) {
         PWindow prev = ( PWindow) var-> prevExclModal;
         if ( prev-> nextExclModal == self)
            prev-> nextExclModal = var-> nextExclModal;
      }
      if ( var-> nextExclModal) {
         PWindow next = ( PWindow) var-> nextExclModal;
         if ( next-> prevExclModal == self)
            next-> prevExclModal = var-> prevExclModal;
      }
      if ( app) {
         if ( app-> exclModal == self)
            app-> exclModal = var-> nextExclModal;
         if ( app-> topExclModal == self)
            app-> topExclModal = var-> prevExclModal;
      }
      var-> prevExclModal = var-> nextExclModal = nilHandle;
   }
   var-> modal = mtNone;
}

void
Window_cancel_children( Handle self)
{
   protect_object( self);
   if ( my-> get_modalHorizon( self)) {
      Handle next = var-> nextSharedModal;
      while ( next) {
         CWindow( next)-> cancel( next);
         next = var-> nextSharedModal;
      }
   } else {
      Handle mh   = my-> get_horizon( self);
      Handle next = ( mh == application) ?
                  PApplication(mh)-> sharedModal :
                  PWindow(mh)-> nextSharedModal;
      while ( next) {
         if ( Widget_is_child( next, self)) {
            CWindow( next)-> cancel( next);
            next = PWindow(mh)-> nextSharedModal;
         } else
            next = PWindow(next)-> nextSharedModal;
      }
   }
   unprotect_object( self);
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
   if ( var-> modal || var-> nextSharedModal) return false;
   if ( insertBefore &&
         (( insertBefore == self) ||
         ( !kind_of( insertBefore, CWindow)) ||
         ( PWindow( insertBefore)-> modal != mtShared) ||
         ( CWindow( insertBefore)-> get_horizon( insertBefore) != my-> get_horizon( self))))
             insertBefore = nilHandle;
   return apc_window_execute_shared( self, insertBefore);
}

Bool
Window_modalHorizon( Handle self, Bool set, Bool modalHorizon)
{
   if ( !set)
      return is_opt( optModalHorizon);
   if ( is_opt( optModalHorizon) == modalHorizon) return false;
   my-> cancel_children( self);
   opt_assign( optModalHorizon, modalHorizon);
   return modalHorizon;
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
   if ( var-> stage == csNormal) {
      if ( ok)
         apc_window_activate( self);
      else
         if ( apc_window_is_active( self))
            apc_window_activate( nilHandle);
   }
}

Bool
Window_focused( Handle self, Bool set, Bool focused)
{
   if ( set)
      activate( self, focused);
   return inherited focused( self, set, focused);
}

void Window_set( Handle self, HV * profile)
{
   dPROFILE;
   Bool owner_icon = false;
   
   if ( pexist( owner)) {
      owner_icon = pexist( ownerIcon) ? pget_B( ownerIcon) : my-> get_ownerIcon( self);
      pdelete( ownerIcon);
   }

   if ( pexist( frameOrigin) || pexist( frameSize)) {
      Bool io = 0, is = 0;
      Point o, s;
      if ( pexist( frameOrigin)) {
         int set[2];
         prima_read_point( pget_sv( frameOrigin), set, 2, "RTC0092: Array panic on 'frameOrigin'");
         pdelete( frameOrigin);
         o. x = set[0];
         o. y = set[1];
         io = 1;
      } else {
         o.x = o. y = 0;
      }
      if ( pexist( frameSize)) {
         int set[2];
         prima_read_point( pget_sv( frameSize), set, 2, "RTC0093: Array panic on 'frameSize'");
         pdelete( frameSize);
         s. x = set[0];
         s. y = set[1];
         is = 1;
      } else {
         s.x = s. y = 0;
      }
      if ( is && io)
         apc_widget_set_rect( self, o. x, o. y, s. x, s. y);
      else if ( io) 
         my-> set_frameOrigin( self, o);
      else
         my-> set_frameSize( self, s);
  }

   inherited set( self, profile);
   if ( owner_icon) {
      my-> set_ownerIcon( self, 1);
      opt_set( optOwnerIcon);
   }
}

static Bool
icon_notify ( Handle self, Handle child, Handle icon)
{
    if ( kind_of( child, CWindow) && (( PWindow) child)-> options. optOwnerIcon) {
       (( PWindow) child)-> self-> set_icon( child, icon);
       (( PWindow) child)-> options. optOwnerIcon = 1;
    }
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
   if ( !set)
      return is_opt( optMainWindow);
   opt_assign( optMainWindow, mainWindow);
   return false;
}

Bool
Window_onTop( Handle self, Bool set, Bool onTop)
{
   HV * profile;
   if ( !set)
      return apc_window_get_on_top( self);
   profile = newHV();
   pset_i( onTop, onTop);
   my-> set( self, profile);
   sv_free(( SV *) profile);
   return true;
}

Bool
Window_ownerIcon( Handle self, Bool set, Bool ownerIcon)
{
   if ( !set)
      return is_opt( optOwnerIcon);
   opt_assign( optOwnerIcon, ownerIcon);
   if ( is_opt( optOwnerIcon) && var-> owner) {
      Handle icon = ( var-> owner == application) ?
         CApplication( application)-> get_icon( application) :
         CWindow(      var-> owner)-> get_icon( var-> owner);
      my-> set_icon( self, icon);
      opt_set( optOwnerIcon);
   }
   return false;
}

Bool
Window_process_accel( Handle self, int key)
{
   return var-> modal ? my-> first_that_component( self, (void*)find_accel, &key)
     : inherited process_accel( self, key);
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
   if (!set)
      return inherited get_selected( self);
   activate( self, selected);
   inherited selected( self, set, selected);
   return selected;
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
   HV * profile;
   if ( !set)
      return apc_window_get_task_listed( self);
   profile = newHV();
   pset_i( taskListed, taskListed);
   my-> set( self, profile);
   sv_free(( SV *) profile);
   return nilHandle;
}


SV *
Window_text( Handle self, Bool set, SV * text)
{
   SV *ret = inherited text( self, set, text);
   if (set)
      apc_window_set_caption( self, var-> text, is_opt( optUTF8_text));
   return ret;
}

Bool
Window_validate_owner( Handle self, Handle * owner, HV * profile)
{
   dPROFILE;
   *owner = pget_H( owner);
   if ( *owner != application && !kind_of( *owner, CWidget)) return false;
   return inherited validate_owner( self, owner, profile);
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
