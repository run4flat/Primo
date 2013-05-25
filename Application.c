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
   Font font;
   apc_font_default( &font);
   return font;
}

Font
Application_get_message_font( char * dummy)
{
   Font font;
   apc_sys_get_msg_font( &font);
   return font;
}

Font
Application_get_caption_font( char * dummy)
{
   Font font;
   apc_sys_get_caption_font( &font);
   return font;
}


int
Application_get_default_cursor_width( char * dummy)
{
   return apc_sys_get_value( svXCursor);
}

Point
Application_get_default_scrollbar_metrics( char * dummy)
{
   Point ret;
   ret. x = apc_sys_get_value( svXScrollbar);
   ret. y = apc_sys_get_value( svYScrollbar);
   return ret;
}

Point
Application_get_default_window_borders( char * dummy, int borderStyle)
{
   Point ret = { 0,0};
   switch ( borderStyle) {
   case bsNone:
      ret.x = svXbsNone;
      ret.y = svYbsNone;
      break;
   case bsSizeable:
      ret.x = svXbsSizeable;
      ret.y = svYbsSizeable;
      break;
   case bsSingle:
      ret.x = svXbsSingle;
      ret.y = svYbsSingle;
      break;
   case bsDialog:
      ret.x = svXbsDialog;
      ret.y = svYbsDialog;
      break;
   default:
      return ret;
   }
   ret. x = apc_sys_get_value( ret. x);
   ret. y = apc_sys_get_value( ret. y);
   return ret;
}

int
Application_get_system_value( char * dummy, int sysValue)
{
   return apc_sys_get_value( sysValue);
}

SV *
Application_get_system_info( char * dummy)
{
   return nilSV;
}

Handle
Application_get_widget_from_handle( Handle self, SV * handle)
{
   ApiHandle apiHandle;
   if ( SvIOK( handle))
           apiHandle = SvUVX( handle);
   else
      apiHandle = sv_2uv( handle);
   return apc_application_get_handle( self, apiHandle);
}

Handle
Application_get_hint_widget( Handle self)
{
   return var->  hintWidget;
}

static Bool
icon_notify ( Handle self, Handle child, Handle icon)
{
   return false;
}

Handle
Application_icon( Handle self, Bool set, Handle icon)
{
   if ( var-> stage > csFrozen) return nilHandle;

   if ( !set)
      return var-> icon;

   if ( icon && !kind_of( icon, CImage)) {
       warn("RTC0013: Illegal object reference passed to Application::icon");
       return nilHandle;
   }
   if ( icon) {
      icon = ((( PImage) icon)-> self)-> dup( icon);
      ++SvREFCNT( SvRV((( PAnyObject) icon)-> mate));
   }
   my-> first_that( self, (void*)icon_notify, (void*)icon);
   if ( var-> icon)
      my-> detach( self, var-> icon, true);
   var-> icon = icon;
   if ( icon && ( list_index_of( var-> components, icon) < 0))
      my-> attach( self, icon);
   return nilHandle;
}

Handle
Application_get_focused_widget( Handle self)
{
   return apc_widget_get_focused();
}

Handle
Application_get_active_window( Handle self)
{
   return apc_window_get_active();
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
   if ( var->  stage > csFrozen) return clInvalid;
   if (( index < 0) || ( index > ciMaxId)) return clInvalid;
   if ( !set) {
      switch ( index) {
        case ciFore:
           return opt_InPaint ?
              CDrawable-> get_color ( self) : var-> colors[ index];
        case ciBack:
           return opt_InPaint ?
              CDrawable-> get_backColor ( self) : var-> colors[ index];
        default:
           return  var->  colors[ index];
      }
   } else {
      SingleColor s;
      s. color = color;
      s. index = index;
      if ( !opt_InPaint) my-> first_that( self, (void*)single_color_notify, &s);
      if ( opt_InPaint) switch ( index) {
         case ciFore:
            CDrawable-> set_color ( self, color);
            break;
         case ciBack:
            CDrawable-> set_backColor ( self, color);
            break;
       }
       var-> colors[ index] = color;
   }
   return clInvalid;
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
   if ( modalFlag == mtExclusive) {
      return topMost ? var-> topExclModal   : var-> exclModal;
   } else if ( modalFlag == mtShared) {
      return topMost ? var-> topSharedModal : var-> sharedModal;
   } 
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
   Point ret;
   ret. x = apc_sys_get_value( svAutoScrollFirst);
   ret. y = apc_sys_get_value( svAutoScrollNext);
   return ret;
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
   if ( !set)
      return CWidget( var-> hintWidget)-> get_color( var->  hintWidget);
   return CWidget( var->  hintWidget)-> set_color( var->  hintWidget, hintColor);
}

Color
Application_hintBackColor( Handle self, Bool set, Color hintBackColor)
{
   if ( !set)
      return CWidget( var->  hintWidget)-> get_backColor( var-> hintWidget);
   return CWidget( var->  hintWidget)-> set_backColor( var->  hintWidget, hintBackColor);
}

int
Application_hintPause( Handle self, Bool set, int hintPause)
{
   if ( !set)
      return CTimer( var->  hintTimer)-> get_timeout( var->  hintTimer);
   return CTimer( var->  hintTimer)-> set_timeout( var->  hintTimer, hintPause);
}

void
Application_set_hint_font( Handle self, Font hintFont)
{
}


Font
Application_get_hint_font( Handle self)
{
   return CWidget( var->  hintWidget)-> get_font( var->  hintWidget);
}

Bool
Application_showHint( Handle self, Bool set, Bool showHint)
{
   return false;
}

Handle Application_next( Handle self) { return self;}
Handle Application_prev( Handle self) { return self;}

SV *
Application_palette( Handle self, Bool set, SV * palette)
{
   return nilSV;
}

Handle
Application_top_frame( Handle self, Handle from)
{
   while ( from) {
      if ( kind_of( from, CWindow) &&
             (( PWidget( from)-> owner == application) || !CWidget( from)-> get_clipOwner(from))
         )
         return from;
      from = PWidget( from)-> owner;
   }
   return application;
}

Handle
Application_get_image( Handle self, int x, int y, int xLen, int yLen)
{
   HV * profile;
   Handle i;
   Bool ret;
   Point sz;
   if ( var->  stage > csFrozen) return nilHandle;
   if ( x < 0 || y < 0 || xLen <= 0 || yLen <= 0) return nilHandle;
   sz = apc_application_get_size( self);
   if ( x + xLen > sz. x) xLen = sz. x - x;
   if ( y + yLen > sz. y) yLen = sz. y - y;
   if ( x >= sz. x || y >= sz. y || xLen <= 0 || yLen <= 0) return nilHandle;

   profile = newHV();
   i = Object_create( "Prima::Image", profile);
   sv_free(( SV *) profile);
   ret = apc_application_get_bitmap( self, i, x, y, xLen, yLen);
   --SvREFCNT( SvRV((( PAnyObject) i)-> mate));
   return ret ? i : nilHandle;
}

/*
 * Cannot return nilHandle.
 */
Handle
Application_map_focus( Handle self, Handle from)
{
   Handle topFrame = my-> top_frame( self, from);
   Handle topShared;

   if ( var->  topExclModal)
      return ( topFrame == var->  topExclModal) ? from : var->  topExclModal;

   if ( !var->  topSharedModal && var->  modalHorizons. count == 0)
      return from; /* return from if no shared modals active */

  if ( topFrame == self) {
      if ( !var->  topSharedModal) return from;
      topShared = var->  topSharedModal;
   } else {
      Handle horizon =
         ( !CWindow( topFrame)-> get_modalHorizon( topFrame)) ?
         CWindow( topFrame)-> get_horizon( topFrame) : topFrame;
      if ( horizon == self)
         topShared = var->  topSharedModal;
      else
         topShared = PWindow( horizon)-> topSharedModal;
   }

   return ( !topShared || ( topShared == topFrame)) ? from : topShared;
}

static Handle
popup_win( Handle xTop)
{
   PWindow_vmt top = CWindow( xTop);
   if ( !top-> get_visible( xTop))
      top-> set_visible( xTop, 1);
   if ( top-> get_windowState( xTop) == wsMinimized)
      top-> set_windowState( xTop, wsNormal);
   top-> set_selected( xTop, 1);
   return xTop;
}

Handle
Application_popup_modal( Handle self)
{
   Handle ha = apc_window_get_active();
   Handle xTop;

   if ( var->  topExclModal) {
   /* checking exclusive modal chain */
      xTop = ( !ha || ( PWindow(ha)->modal == 0)) ? var->  exclModal : ha;
      while ( xTop) {
         if ( PWindow(xTop)-> nextExclModal) {
            CWindow(xTop)-> bring_to_front( xTop);
            xTop = PWindow(xTop)-> nextExclModal;
         } else {
            return popup_win( xTop);
         }
      }
   } else {
      if ( !var->  topSharedModal && var->  modalHorizons. count == 0)
         return nilHandle; /* return from if no shared modals active */
      /* checking shared modal chains */
      if ( ha) {
         xTop = ( PWindow(ha)->modal == 0) ? CWindow(ha)->get_horizon(ha) : ha;
         if ( xTop == application) xTop = var->  sharedModal;
      } else
         xTop = var->  sharedModal ? var->  sharedModal : var->  modalHorizons. items[ 0];

      while ( xTop) {
         if ( PWindow(xTop)-> nextSharedModal) {
            CWindow(xTop)-> bring_to_front( xTop);
            xTop = PWindow(xTop)-> nextSharedModal;
         } else {
            return popup_win( xTop);
         }
      }
   }

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
   if ( set) return size;
   return apc_application_get_size( self);
}

Point
Application_origin( Handle self, Bool set, Point origin)
{
   Point p = { 0, 0};
   return p;
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
int    Application_growMode( Handle self, Bool set, int flags)         { return 0; }
Bool   Application_hintVisible( Handle self, Bool set, Bool visible)   { return false; }
Handle Application_owner( Handle self, Bool set, Handle owner)         { return nilHandle; }
Bool   Application_ownerColor( Handle self, Bool set, Bool ownerColor) { return false; }
Bool   Application_ownerBackColor( Handle self, Bool set, Bool ownerBackColor) { return false; }
Bool   Application_ownerFont( Handle self, Bool set, Bool ownerFont)   { return false; }
Bool   Application_ownerShowHint( Handle self, Bool set, Bool ownerShowHint) { return false; }
Bool   Application_ownerPalette( Handle self, Bool set, Bool ownerPalette) { return false; }
Bool   Application_clipOwner( Handle self, Bool set, Bool clipOwner)   { return false; }
int    Application_tabOrder( Handle self, Bool set, int tabOrder)      { return 0; }
SV   * Application_text    ( Handle self, Bool set, SV * text)       { return nilSV; }
Bool   Application_transparent( Handle self, Bool set, Bool transparent) { return false; }
Bool   Application_validate_owner( Handle self, Handle * owner, HV * profile) { return false; }

#ifdef __cplusplus
}
#endif
