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
#include "DeviceBitmap.h"
#include <DeviceBitmap.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CDrawable->
#define my  ((( PDeviceBitmap) self)-> self)
#define var (( PDeviceBitmap) self)

void
DeviceBitmap_init( Handle self, HV * profile)
{
}

void
DeviceBitmap_done( Handle self)
{
}

Bool DeviceBitmap_begin_paint      ( Handle self) { return false; }
Bool DeviceBitmap_begin_paint_info ( Handle self) { return false; }
void DeviceBitmap_end_paint        ( Handle self) {}

Bool
DeviceBitmap_monochrome( Handle self, Bool set, Bool monochrome)
{
   return false;
}

static Handle xdup( Handle self, char * className)
{
   return nilHandle;
}

Handle DeviceBitmap_image( Handle self) { return nilHandle; }
Handle DeviceBitmap_icon( Handle self) { return nilHandle; }

SV *
DeviceBitmap_get_handle( Handle self)
{
   return nilSV;
}

#ifdef __cplusplus
}
#endif
