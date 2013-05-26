/*-
 * Copyright (c) 2013 David Mertens
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
#include "Hummingbird.h"
#include <Hummingbird.inc>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#undef  my
#define inherited CObject->
#define my  ((( PHummingbird) self)-> self)
#define var (( PHummingbird) self)

void Hummingbird_init ( Handle self, HV * profile)
{
   dPROFILE;
   inherited init( self, profile);
   var->age = 0;
   var->color = 0;
   CORE_INIT_TRANSIENT(Hummingbird);
}

void Hummingbird_describe ( Handle self)
{
   printf("**** Hummingbird base class describe begin ****\n");
   printf("I am a hummingbird, %d years old, color %d\n",
      var->age, var->color);
   printf("**** Hummingbird base class describe done****\n");
}

void Hummingbird_done (Handle self)
{
   printf("About to call done from hummingbird with description:\n");
   my->describe(self);
   inherited done(self);
   printf("Done with that\n");
}


#ifdef __cplusplus
}
#endif
