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
#include <ctype.h>
#include "Component.h"
#include <Component.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CObject->
#define my  ((( PComponent) self)-> self)
#define var (( PComponent) self)

typedef Bool ActionProc ( Handle self, Handle item, void * params);
typedef ActionProc *PActionProc;

void
Component_init( Handle self, HV * profile)
{
}

void
Component_setup( Handle self)
{
}

static Bool bring_by_name( Handle self, PComponent item, char * name)
{
   return false;
}

Handle
Component_bring( Handle self, char * componentName)
{
   return nilHandle;
}

static Bool
detach_all( Handle child, Handle self)
{
   return false;
}

void
Component_cleanup( Handle self)
{
}

static Bool
free_private_posts( PostMsg * msg, void * dummy)
{
   return false;
}

static Bool
free_queue( PEvent event, void * dummy)
{
   return false;
}

static Bool
free_eventref( Handle self, Handle * org)
{
   return false;
}

void
Component_done( Handle self)
{
}

void
Component_attach( Handle self, Handle object)
{
}

void
Component_detach( Handle self, Handle object, Bool kill)
{
}

SV *
Component_name( Handle self, Bool set, SV * name)
{
   return nilSV;
}

Handle
Component_owner( Handle self, Bool set, Handle owner)
{
   return nilHandle;
}


void
Component_set( Handle self, HV * profile)
{
}

static Bool
find_dup_msg( PEvent event, int * cmd)
{
   return false;
}

Bool
Component_message( Handle self, PEvent event)
{
   return false;
}


Bool
Component_can_event( Handle self)
{
   return false;
}

void
Component_clear_event( Handle self)
{
}

void
Component_push_event( Handle self)
{
}

Bool
Component_pop_event( Handle self)
{
   return false;
}


Bool
Component_eventFlag( Handle self, Bool set, Bool eventFlag)
{
   return false;
}

void
Component_event_error( Handle self)
{
}

SV *
Component_get_handle( Handle self)
{
   return nilSV;
}

static Bool
oversend( PEvent event, Handle self)
{
   return false;
}

void
Component_handle_event( Handle self, PEvent event)
{
}

int
Component_is_owner( Handle self, Handle objectHandle)
{
   int foo; return foo;
}

Bool
Component_migrate( Handle self, Handle attachTo)
{
   return false;
}

void
Component_recreate( Handle self)
{
}

Handle
Component_first_that_component( Handle self, void * actionProc, void * params)
{
   return nilHandle;
}

void
Component_post_message( Handle self, SV * info1, SV * info2)
{
}


void
Component_update_sys_handle( Handle self, HV * profile)
{
}

Bool
Component_validate_owner( Handle self, Handle * owner, HV * profile)
{
   return false;
}

void
Component_on_create( Handle self)
{
}

void
Component_on_destroy( Handle self)
{
}

void
Component_on_postmessage( Handle self, SV * info1, SV * info2)
{
}

XS( Component_event_hook_FROMPERL)
{
}

XS( Component_notify_FROMPERL)
{
}

Bool
Component_notify( Handle self, char * format, ...)
{
   return false;
}

Bool
Component_notify_REDEFINED( Handle self, char * format, ...)
{
   return false;
}

XS( Component_get_components_FROMPERL)
{
}

void Component_get_components          ( Handle self) {}
void Component_get_components_REDEFINED( Handle self) {}

UV
Component_add_notification( Handle self, char * name, SV * subroutine, Handle referer, int index)
{
   UV foo; return foo;
}

void
Component_remove_notification( Handle self, UV id)
{
}

void
Component_unlink_notifier( Handle self, Handle referer)
{
}

XS( Component_get_notification_FROMPERL)
{
}

void Component_get_notification          ( Handle self, char * name, int index) {}
void Component_get_notification_REDEFINED( Handle self, char * name, int index) {}

XS( Component_set_notification_FROMPERL)
{
}

void Component_set_notification          ( Handle self, char * name, SV * subroutine) {}
void Component_set_notification_REDEFINED( Handle self, char * name, SV * subroutine) {}

SV *
Component_delegations( Handle self, Bool set, SV * delegations)
{
   return nilSV;
}

#ifdef __cplusplus
}
#endif
