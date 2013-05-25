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
/*  System dependent application management (unix, x11)    */
/*                                                         */
/***********************************************************/

#include "apricot.h"
#include "unix/guts.h"
#include "Application.h"
#include "File.h"
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#if !defined(BYTEORDER)
#error "BYTEORDER is not defined"
#endif
#define LSB32   0x1234
#define LSB64   0x12345678
#define MSB32   0x4321
#define MSB64   0x87654321
#ifndef BUFSIZ
#define BUFSIZ  2048
#endif

UnixGuts guts, *pguts = &guts;

UnixGuts *
prima_unix_guts(void)
{
   return &guts;
}







int
prima_debug( const char *format, ...)
{
   int foo; return foo;
}


Bool
apc_application_begin_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_begin_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_create( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_close( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_destroy( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_end_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_end_paint_info( Handle self)
{
   Bool foo; return foo;
}

int
apc_application_get_gui_info( char * description, int len)
{
   int foo; return foo;
}

Handle
apc_application_get_widget_from_point( Handle self, Point p)
{
   return nilHandle;
}

Handle
apc_application_get_handle( Handle self, ApiHandle apiHandle)
{
   return nilHandle;
}


Rect
apc_application_get_indents( Handle self)
{
   Rect foo; return foo;
}

int
apc_application_get_os_info( char *system, int slen,
			     char *release, int rlen,
			     char *vendor, int vlen,
			     char *arch, int alen)
{
   int foo; return foo;
}

Point
apc_application_get_size( Handle self)
{
   Point foo; return foo;
}


Bool
apc_watch_filehandle( int no, void *sub, void *glob)
{
   Bool foo; return foo;
}

Bool
prima_one_loop_round( Bool wait, Bool careOfApplication)
{
   Bool foo; return foo;
}

Bool
apc_application_go( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_lock( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_unlock( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_sync(void)
{
   Bool foo; return foo;
}

Bool
apc_application_yield( void)
{
   Bool foo; return foo;
}
