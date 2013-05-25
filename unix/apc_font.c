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
   memcpy( f, &guts. default_font, sizeof( Font));
   return f;
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
   FontKey key;
   PCachedFont kf;

   prima_build_font_key( &key, font, bySize);
   kf = hash_fetch( guts. font_hash, &key, sizeof( FontKey));
   if ( kf && refill) {
      memcpy( font, &kf-> font, sizeof( Font));
   }
   return kf;
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
   double diff = 0.0;
   int enc_match = 0;

   if ( fi-> flags. encoding && f-> encoding[0]) {
      if ( strcmp( f-> encoding, fi-> font. encoding) != 0)
         diff += 16000.0;
      else
         enc_match = 1;
   }

   if ( guts. locale[0] && !f-> encoding[0] && fi-> flags. encoding) {
      if ( strcmp( fi-> font. encoding, guts. locale) != 0)
         diff += 50;
   }
   
   if ( fi->  flags. pitch) {
      if ( f-> pitch == fpDefault && fi-> font. pitch == fpFixed) {
         diff += 1.0;
      } else if ( f-> pitch == fpFixed && fi-> font. pitch == fpVariable) {
         diff += 16000.0;
      } else if ( f-> pitch == fpVariable && fi-> font. pitch == fpFixed) {
         diff += 16000.0;
      }
   } else if ( f-> pitch != fpDefault) {
      diff += 10000.0;  /* 2/3 of the worst case */
   }
   
   if ( fi-> flags. name && stricmp( lcname, fi-> font. name) == 0) {
      diff += 0.0;
   } else if ( fi-> flags. family && stricmp( lcname, fi-> font. family) == 0) {
      diff += 1000.0;
   } else if ( fi-> flags. family && strcasestr( fi-> font. family, lcname)) {
      diff += 2000.0;
   } else if ( !fi-> flags. family) {
      diff += 8000.0;
   } else if ( fi-> flags. name && strcasestr( fi-> font. name, lcname)) {
      diff += 7000.0;
   } else {
      diff += 10000.0;
      if ( fi-> flags. funky && !enc_match) diff += 10000.0; 
   }

   if ( fi-> font. vector) {
      if ( fi-> flags. bad_vector) {
         diff += 20.0;    
      }   
   } else {   
      int a, b;
      switch ( selector) {
      case QUERYDIFF_BY_SIZE:
         a = fi-> font. size;
         b = f-> size;
         break;
      case QUERYDIFF_BY_HEIGHT:
         a = fi-> font. height;
         b = f-> height;
         break;
      default:
         a = fi-> font. height;
         b = fi-> flags. sloppy ? selector : f-> height;
         break;
      }
      if ( a > b) {
         if ( have_vector_fonts) diff += 1000000.0;
         diff += 600.0; 
         diff += 150.0 * (a - b);
      } else if ( a < b) {
         if ( have_vector_fonts) diff += 1000000.0;
         diff += 150.0 * ( b - a);
      }
   } 

   if ( f-> width) {
      if ( fi-> font. vector) {
         if ( fi-> flags. bad_vector) {
            diff += 20.0;    
         }   
      } else {
         if ( fi-> font. width > f-> width) {
            if ( have_vector_fonts) diff += 1000000.0;
            diff += 200.0;
            diff += 50.0 * (fi->  font. width - f-> width); 
         } else if ( fi-> font. width < f-> width) {
            if ( have_vector_fonts) diff += 1000000.0;
            diff += 50.0 * (f-> width - fi->  font. width);
         }   
      }   
   }   
   
   if ( fi->  flags. xDeviceRes && fi-> flags. yDeviceRes) {
      diff += 30.0 * (int)fabs( 0.5 +
         (float)( 100.0 * guts. resolution. y / guts. resolution. x) -
         (float)( 100.0 * fi->  font. yDeviceRes / fi->  font. xDeviceRes));
   }

   if ( fi->  flags. yDeviceRes) {
      diff += 1.0 * abs( guts. resolution. y - fi->  font. yDeviceRes);
   }
   if ( fi->  flags. xDeviceRes) {
      diff += 1.0 * abs( guts. resolution. x - fi->  font. xDeviceRes);
   }

   if ( fi-> flags. style && ( f-> style & ~(fsUnderlined|fsOutline|fsStruckOut))== fi->  font. style) {
      diff += 0.0;
   } else if ( !fi->  flags. style) {
      diff += 2000.0;
   } else {
      if (( f-> style & fsBold) != ( fi-> font. style & fsBold))
         diff += 3000;
      if (( f-> style & fsItalic) != ( fi-> font. style & fsItalic))
         diff += 3000;
   }
   return diff;
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
   int i, count = guts. n_fonts;
   PFontInfo info = guts. font_info;
   PFont fmtx = nil;
   Font defaultFont;
   List list;
   PHash hash = nil;

   list_create( &list, 256, 256);

   *retCount = 0;
   defaultFont. width  = 0;
   defaultFont. height = 0;
   defaultFont. size   = 10;
   
  
   if ( !( hash = hash_create())) {
      list_destroy( &list);
      return nil;
   }

   /* collect font info */
   for ( i = 0; i < count; i++) {
      int len;
      PFont fm;
      if ( info[ i]. flags. disabled) continue;
      
      len = strlen( info[ i].font.name);

      fm = hash_fetch( hash, info[ i].font.name, len);
      if ( fm) {
         char ** enc = (char**) fm-> encoding;
         unsigned char * shift = (unsigned char*)enc + sizeof(char *) - 1;
         if ( *shift + 2 < 256 / sizeof(char*)) {
            int j, exists = 0;
            for ( j = 1; j <= *shift; j++) {
               if ( strcmp( enc[j], info[i].xname + info[i].info_offset) == 0) {
                  exists = 1;
                  break;
               }
            }
            if ( exists) continue;
            *(enc + ++(*shift)) = info[i].xname + info[i].info_offset;
         }
         continue;
      }

      if ( !( fm = ( PFont) malloc( sizeof( Font)))) {
         if ( hash) hash_destroy( hash, false);
         list_delete_all( &list, true);
         list_destroy( &list);
         return nil;
      }

      /*
      if ( info[i]. flags. sloppy) 
         detail_font_info( info + i, &defaultFont, false, true);
       */
      *fm = info[i]. font;
     
      { /* multi-encoding format */
         char ** enc = (char**) fm-> encoding;
         unsigned char * shift = (unsigned char*)enc + sizeof(char *) - 1;      
         memset( fm-> encoding, 0, 256);
         *(enc + ++(*shift)) = info[i].xname + info[i].info_offset;
         hash_store( hash, info[ i].font.name, strlen( info[ i].font.name), fm); 
      }

      list_add( &list, ( Handle) fm);
   }

   if ( hash) hash_destroy( hash, false);      

   if ( list. count == 0) goto Nothing;
   fmtx = ( PFont) malloc( list. count * sizeof( Font));
   if ( !fmtx) {
      list_delete_all( &list, true);   
      list_destroy( &list);
      return nil;
   }
   
   *retCount = list. count;
      for ( i = 0; i < list. count; i++)
         memcpy( fmtx + i, ( void *) list. items[ i], sizeof( Font));
   list_delete_all( &list, true);

Nothing:
   list_destroy( &list);
   
#ifdef USE_XFT
   if ( guts. use_xft)
      fmtx = prima_xft_fonts( fmtx, nil, nil, retCount);
#endif

   return fmtx;
}   

PFont
apc_fonts( Handle self, const char *facename, const char * encoding, int *retCount)
{
   int i, count = guts. n_fonts;
   PFontInfo info = guts. font_info;
   PFontInfo * table; 
   int n_table;
   PFont fmtx;
   Font defaultFont;

   if ( !facename && !encoding) return spec_fonts( retCount);
   
   *retCount = 0;
   n_table = 0;
   
   /* stage 1 - browse through names and validate records */
   table = malloc( count * sizeof( PFontInfo));
   if ( !table && count > 0) return nil;
   
   if ( facename == nil) {
      PHash hash = hash_create();
      for ( i = 0; i < count; i++) {
         int len;
         if ( info[ i]. flags. disabled) continue;
         len = strlen( info[ i].font.name);
         if ( hash_fetch( hash, info[ i].font.name, len) || 
            strcmp( info[ i].xname + info[ i].info_offset, encoding) != 0)
              continue;
         hash_store( hash, info[ i].font.name, len, (void*)1);
         table[ n_table++] = info + i;
      }
      hash_destroy( hash, false);
      *retCount = n_table;
   } else {
      for ( i = 0; i < count; i++) {
         if ( info[ i]. flags. disabled) continue;
         if (
               ( stricmp( info[ i].font.name, facename) == 0) &&
               ( 
                   !encoding || 
                   ( strcmp( info[ i].xname + info[ i].info_offset, encoding) == 0)
               )
            )
         {
            table[ n_table++] = info + i;
         }
      }   
      *retCount = n_table;
   }   

   fmtx = malloc( n_table * sizeof( Font)); 
   bzero( fmtx, n_table * sizeof( Font)); 
   if ( !fmtx && n_table > 0) {
      *retCount = 0;
      free( table);
      return nil;
   }
   
   defaultFont. width  = 0;
   defaultFont. height = 0;
   defaultFont. size   = 10;
      
   for ( i = 0; i < n_table; i++) {
      /*
      if ( table[i]-> flags. sloppy)
         detail_font_info( table[i], &defaultFont, false, true);
       */
      fmtx[i] = table[i]-> font;
   }   
   free( table);

#ifdef USE_XFT
   if ( guts. use_xft)
      fmtx = prima_xft_fonts( fmtx, facename, encoding, retCount);
#endif

   return fmtx;
}

PHash
apc_font_encodings( Handle self )
{
   HE *he;
   PHash hash = hash_create();
   if ( !hash) return nil;

#ifdef USE_XFT
   if ( guts. use_xft)
      prima_xft_font_encodings( hash);
#endif

   hv_iterinit(( HV*) encodings);
   for (;;) {
      if (( he = hv_iternext( encodings)) == nil)
         break;
      hash_store( hash, HeKEY( he), HeKLEN( he), (void*)1);
   }
   return hash;
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
