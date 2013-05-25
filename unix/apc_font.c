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

static PHash xfontCache = nil;
static Bool have_vector_fonts = false;
static PHash encodings = nil;
static char **ignore_encodings;
static int n_ignore_encodings;
static char *s_ignore_encodings;

/* these are freed right after use */
static char * do_default_font = nil;
static char * do_caption_font = nil;
static char * do_msg_font = nil;
static char * do_menu_font = nil;
static char * do_widget_font = nil;
static Bool   do_xft = true;
static Bool   do_core_fonts = true;
static Bool   do_xft_no_antialias = false;
static Bool   do_xft_priority = true;
static Bool   do_no_scaled_fonts = false;

static void detail_font_info( PFontInfo f, PFont font, Bool addToCache, Bool bySize);

static void
str_lwr( char *d, const char *s)
{
}

static void
fill_default_font( Font * font )
{
}

/* Extracts font name, charset, foundry etc from X properties, if available.
   Usually it is when X server can access its internal font files directly.
   This means two things:
   - X properties values are not the same as XLFD, and are precise font descriptors
   - alias fonts ( defined via fonts.alias ) don't have X properties
 */
static void
font_query_name( XFontStruct * s, PFontInfo f)
{
}

static Bool
xlfd_parse_font( char * xlfd_name, PFontInfo info, Bool do_vector_fonts)
{
   Bool foo; return foo;
}

static Bool
pick_default_font_with_encoding(void)
{
   Bool foo; return foo;
}

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

static Bool
free_rotated_entries( PCachedFont f, int keyLen, void * key, void * dummy)
{
   Bool foo; return foo;
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

static void
dump_font( PFont f)
{
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

static Bool
add_font_to_cache( PFontKey key, PFontInfo f, const char *name, XFontStruct *s, int uPos, int uThinkness)
{
   Bool foo; return foo;
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

static void
detail_font_info( PFontInfo f, PFont font, Bool addToCache, Bool bySize)
{
}

#define QUERYDIFF_BY_SIZE        (-1)
#define QUERYDIFF_BY_HEIGHT      (-2)

static double 
query_diff( PFontInfo fi, PFont f, char * lcname, int selector)
{
   double foo; return foo;
}

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


static PFont
spec_fonts( int *retCount)
{
   return nil;
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
   XCharStruct * cs;
   int d = xs-> max_char_or_byte2 - xs-> min_char_or_byte2 + 1;
   int index1        = wide ? (( XChar2b*) c)-> byte1 : 0;
   int index2        = wide ? (( XChar2b*) c)-> byte2 : *((char*)c);
   int default_char1 = wide ? ( xs-> default_char >> 8) : 0;
   int default_char2 = xs-> default_char & 0xff;

   if ( default_char1 < xs-> min_byte1 ||
        default_char1 > xs-> max_byte1)
      default_char1 = xs-> min_byte1;
   if ( default_char2 < xs-> min_char_or_byte2 ||
        default_char2 > xs-> max_char_or_byte2)
      default_char2 = xs-> min_char_or_byte2;
   
   if ( index1 < xs-> min_byte1 || 
        index1 > xs-> max_byte1) { 
      index1 = default_char1;
      index2 = default_char2;
   }
   if ( index2 < xs-> min_char_or_byte2 || 
        index2 > xs-> max_char_or_byte2) { 
      index1 = default_char1;
      index2 = default_char2;
   }
   cs = xs-> per_char ? 
      xs-> per_char + 
        ( index1 - xs-> min_byte1) * d +
        ( index2 - xs-> min_char_or_byte2) : 
      &(xs-> min_bounds);
   return cs;
}   
