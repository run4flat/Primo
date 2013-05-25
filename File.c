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
#ifdef PerlIO
typedef PerlIO *FileStream;
#else
#define PERLIO_IS_STDIO 1
typedef FILE *FileStream;
#define PerlIO_fileno(f) fileno(f)
#endif
#include "File.h"
#include <File.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CComponent
#define my  ((( PFile) self)-> self)
#define var (( PFile) self)

static void File_reset_notifications( Handle self);

void
File_init( Handle self, HV * profile)
{
}

void
File_cleanup( Handle self)
{
}

Bool
File_is_active( Handle self, Bool autoDetach)
{
   return false;
}

void
File_handle_event( Handle self, PEvent event)
{
}

SV *
File_file( Handle self, Bool set, SV * file)
{
   return nilSV;
}

SV *
File_get_handle( Handle self)
{
   return nilSV;
}

int
File_mask( Handle self, Bool set, int mask)
{
   int foo; return foo;
}

UV
File_add_notification( Handle self, char * name, SV * subroutine, Handle referer, int index)
{
   UV foo; return foo;
}

void
File_remove_notification( Handle self, UV id)
{
}


static void
File_reset_notifications( Handle self)
{
}

#ifdef __cplusplus
}
#endif
