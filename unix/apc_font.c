/*
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
/*  System dependent font routines (unix, x11)             */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include <locale.h>


/* these are freed right after use */




/* Extracts font name, charset, foundry etc from X properties, if available.
   Usually it is when X server can access its internal font files directly.
   This means two things:
   - X properties values are not the same as XLFD, and are precise font descriptors
   - alias fonts ( defined via fonts.alias ) don't have X properties
 */



Bool
prima_init_font_subsystem( char * error_buf)
{
   Bool foo; return foo;
}
   
Bool
prima_font_subsystem_set_option( char * option, char * value)
{
   Bool foo; return foo;
}

void
prima_font_pp2font( char * ppFontNameSize, PFont font)
{
}

void
prima_free_rotated_entry( PCachedFont f)
{
}


void
prima_cleanup_font_subsystem( void)
{
}

PFont
apc_font_default( PFont f)
{
   return nil;
}

int
apc_font_load( const char* filename)
{
   int foo; return foo;
}


void
prima_build_font_key( PFontKey key, PFont f, Bool bySize)
{
}

PCachedFont
prima_find_known_font( PFont font, Bool refill, Bool bySize)
{
   return nil;
}


void
prima_init_try_height( HeightGuessStack * p, int target, int firstMove )
{
}

int
prima_try_height( HeightGuessStack * p, int height)
{
   int foo; return foo;
}


#define QUERYDIFF_BY_SIZE        (-1)
#define QUERYDIFF_BY_HEIGHT      (-2)


Bool
prima_core_font_pick( Handle self, PFont source, PFont dest)
{
   Bool foo; return foo;
}

Bool
prima_core_font_encoding( char * encoding)
{
   Bool foo; return foo;
}

Bool
apc_font_pick( Handle self, PFont source, PFont dest)
{
   Bool foo; return foo;
}



PFont
apc_fonts( Handle self, const char *facename, const char * encoding, int *retCount)
{
   return nil;
}

PHash
apc_font_encodings( Handle self )
{
   return nil;
}

Bool
apc_gp_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
apc_menu_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
prima_update_rotated_fonts( PCachedFont f, const char * text, int len, Bool wide, double direction, PRotatedFont * result,
   Bool * ok_to_not_rotate)
{
   Bool foo; return foo;
}

XCharStruct * 
prima_char_struct( XFontStruct * xs, void * c, Bool wide) 
{
   XCharStruct * foo; return foo;
}
