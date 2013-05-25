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
#include "Icon.h"
#include "img_conv.h"
#include <Icon.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CImage->
#define my  ((( PIcon) self)-> self)
#define var (( PIcon) self)

static void
produce_mask( Handle self)
{
}

void
Icon_init( Handle self, HV * profile)
{
}


SV *
Icon_mask( Handle self, Bool set, SV * svmask)
{
   return nilSV;
}

int
Icon_autoMasking( Handle self, Bool set, int autoMasking)
{
   if ( !set)
      return var-> autoMasking;
   if ( var-> autoMasking == autoMasking) return 0;
   var-> autoMasking = autoMasking;
   if ( is_opt( optInDraw)) return 0;
   my-> update_change( self);
   return 0;
}   

Color
Icon_maskColor( Handle self, Bool set, Color color)
{
   if ( !set)
      return var-> maskColor;
   if ( var-> maskColor == color) return 0;
   var-> maskColor = color;
   if ( is_opt( optInDraw)) return 0;
   if ( var-> autoMasking == amMaskColor) 
      my-> update_change( self);
   return clInvalid;
}   

int
Icon_maskIndex( Handle self, Bool set, int index)
{
   if ( !set)
      return var-> maskIndex;
   var-> maskIndex = index;
   if ( is_opt( optInDraw)) return 0;
   if ( var-> autoMasking == amMaskIndex) 
      my-> update_change( self);
   return -1;
}   

void
Icon_update_change( Handle self)
{
}

void
Icon_stretch( Handle self, int width, int height)
{
}

void
Icon_create_empty( Handle self, int width, int height, int type)
{
}

Handle
Icon_dup( Handle self)
{
   return nilHandle;
}

IconHandle
Icon_split( Handle self)
{
   IconHandle ret = {0,0};
   PImage i;
   HV * profile = newHV();
   char* className = var-> self-> className;

   pset_H( owner,        var-> owner);
   pset_i( width,        var-> w);
   pset_i( height,       var-> h);
   pset_i( type,         imMono|imGrayScale);
   pset_i( conversion,   var->conversion);
   pset_i( hScaling,     is_opt( optHScaling));
   pset_i( vScaling,     is_opt( optVScaling));
   pset_i( preserveType, is_opt( optPreserveType));

   ret. andMask = Object_create( "Prima::Image", profile);
   sv_free(( SV *) profile);
   i = ( PImage) ret. andMask;
   memcpy( i-> data, var-> mask, var-> maskSize);
   i-> self-> update_change(( Handle) i);

   var-> self-> className = inherited className;
   ret. xorMask         = inherited dup( self);
   var-> self-> className = className;

   --SvREFCNT( SvRV( i-> mate));
   return ret;
}

void
Icon_combine( Handle self, Handle xorMask, Handle andMask)
{
}

#ifdef __cplusplus
}
#endif
