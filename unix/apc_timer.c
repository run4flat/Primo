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

#include "unix/guts.h"

static void
inactivate_timer( PTimerSysData sys)
{
   if ( sys-> older || sys-> younger || guts. oldest == sys) {
      if ( sys-> older) {
	 sys-> older-> younger = sys-> younger;
      } else {
	 guts. oldest = sys-> younger;
      }
      if ( sys-> younger)
	 sys-> younger-> older = sys-> older;
   }
   sys-> older = nil;
   sys-> younger = nil;
}

static void
fetch_sys_timer( Handle self, PTimerSysData *s, Bool *real_timer)
{
   if ( self == 0) {
      *s = nil;
      *real_timer = false;
   } else if ( self >= FIRST_SYS_TIMER && self <= LAST_SYS_TIMER) {
      *s = &guts. sys_timers[ self - FIRST_SYS_TIMER];
      *real_timer = false;
   } else {
      *s = ((PTimerSysData)(PComponent((self))-> sysData));
      *real_timer = true;
   }
}

#define ENTERTIMER \
	PTimerSysData sys; \
	Bool real; \
	\
	fetch_sys_timer( self, &sys, &real)

Bool
apc_timer_create( Handle self, Handle owner, int timeout)
{
   Bool foo; return foo;
}

Bool
apc_timer_destroy( Handle self)
{
   Bool foo; return foo;
}

int
apc_timer_get_timeout( Handle self)
{
   int foo; return foo;
}

Bool
apc_timer_set_timeout( Handle self, int timeout)
{
   Bool foo; return foo;
}

Bool
apc_timer_start( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_timer_stop( Handle self)
{
   Bool foo; return foo;
}


ApiHandle
apc_timer_get_handle( Handle self)
{
   ENTERTIMER;
   return (ApiHandle) sys;
}

