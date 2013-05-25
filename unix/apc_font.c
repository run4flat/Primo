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
   while ( *s) {
      *d++ = tolower( *s++);
   }
   *d = '\0';
}

static void
fill_default_font( Font * font )
{
   bzero( font, sizeof( Font));
   strcpy( font-> name, "Default");
   font-> height = C_NUMERIC_UNDEF;
   font-> size = 12;
   font-> width = C_NUMERIC_UNDEF;
   font-> style = fsNormal;
   font-> pitch = fpDefault;
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
   unsigned long v;
   char * c;

   if ( !f-> flags. encoding) {
      c = nil;
      if ( XGetFontProperty( s, FXA_CHARSET_REGISTRY, &v) && v) {
         XCHECKPOINT;
         c = XGetAtomName( DISP, (Atom)v);
         XCHECKPOINT;
         if ( c) {
            f-> flags. encoding = true;
            str_lwr( f-> font. encoding, c);
            XFree( c);
         } 
      }

      if ( c) {
         c = nil;
         if ( XGetFontProperty( s, FXA_CHARSET_ENCODING, &v) && v) {
            XCHECKPOINT;
            c = XGetAtomName( DISP, (Atom)v);
            XCHECKPOINT;
            if ( c) {
               strcat( f-> font. encoding, "-");
               str_lwr( f-> font. encoding + strlen( f-> font. encoding), c);
               XFree( c);
            } 
         }
      }
      
      if ( !c) {
         f-> flags. encoding = false;
         f-> font. encoding[0] = 0;
      }
   }

   /* detailing family */   
   if ( ! f-> flags. family && XGetFontProperty( s, FXA_FOUNDRY, &v) && v) {
      XCHECKPOINT;
      c = XGetAtomName( DISP, (Atom)v);
      XCHECKPOINT;
      if ( c) {
         f-> flags. family = true;
         strncpy( f-> font. family, c, 255);  f-> font. family[255] = '\0';
         str_lwr( f-> font. family, f-> font. family);
         XFree( c);
      }
   } 

   /* detailing name */
   if ( ! f-> flags. name && XGetFontProperty( s, FXA_FAMILY_NAME, &v) && v) {
      XCHECKPOINT;
      c = XGetAtomName( DISP, (Atom)v);
      XCHECKPOINT;
      if ( c) {
         f-> flags. name = true;
         strncpy( f-> font. name, c, 255);  f-> font. name[255] = '\0';
         str_lwr( f-> font. name, f-> font. name);
         XFree( c);
      } 
   }

   if ( ! f-> flags. family && ! f-> flags. name) {
      c = f-> xname;
      if ( strchr( c, '-') == NULL) {
         strcpy( f-> font. name, c);
         strcpy( f-> font. family, c);
      } else {
         char * d = c;
         int cnt = 0, lim;
         if ( *d == '-') d++;
         while ( *(c++)) {
            if ( *c == '-' || *(c + 1)==0) {
               if ( c == d ) continue;
               if ( cnt == 0 ) {
                  lim = ( c - d > 255 ) ? 255 : c - d;
                  strncpy( f-> font. family, d, lim);
                  cnt++;
               } else if ( cnt == 1) {
                  lim = ( c - d > 255 ) ? 255 : c - d;
                  strncpy( f-> font. name, d, lim);
                  break;
               } else 
                  break;
               d = c + 1;
            }
         }

         if (( strlen( f-> font. family) == 0) || (strcmp( f-> font. family, "*") == 0))
            strcpy( f-> font. family, guts. default_font. family);
         if (( strlen( f-> font. name) == 0) || (strcmp( f-> font. name, "*") == 0)) {
            if ( guts. default_font_ok) {
               strcpy( f-> font. name, guts. default_font. name);
            } else {
               Font fx = f-> font;
               fill_default_font( &fx);
               if ( f-> flags. encoding) strcpy( fx. encoding, f-> font. encoding);
               prima_core_font_pick( application, &fx, &fx);
               strcpy( f-> font. name, fx. name);
            }
         } else {
            char c[256];
            snprintf( c, 256, "%s %s", f-> font. family, f-> font. name);
            strcpy( f-> font. name, c);
         }
      }
      str_lwr( f-> font. family, f-> font. family);
      str_lwr( f-> font. name, f-> font. name);
      f-> flags. name = true;
      f-> flags. family = true;
   } else if ( ! f-> flags. family ) {
      str_lwr( f-> font. family, f-> font. name);
      f-> flags. name = true;
   } else if ( ! f-> flags. name ) {
      str_lwr( f-> font. name, f-> font. family);
      f-> flags. name = true;
   }
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
   int i, newEntry = 0, len, dash = 0;
   FontInfo fi;
   XFontStruct * xf;
   Font dummy, def_dummy, *def;
   char buf[512], *p;

   if ( !font) font = &dummy;
   

   /* check if font is XLFD and ends in -*-*, so we can replace it with $LANG */
   len = strlen( ppFontNameSize);
   for ( i = 0, p = ppFontNameSize; i < len; i++, p++)
      if ( *p == '-') dash++;
   if (( dash == 14) && guts. locale[0] && (strcmp( ppFontNameSize + len - 4, "-*-*") == 0)) {
      memcpy( buf, ppFontNameSize, len - 3);
      buf[ len - 3] = 0;
      strncat( buf, guts. locale, 512 - strlen(buf) - 1);
      buf[511] = 0;
      ppFontNameSize = buf;
      len = strlen( ppFontNameSize);
   }

   /* check if the parsed font already present */
   memset( font, 0, sizeof( Font));
   for ( i = 0; i < guts. n_fonts; i++) {
      if ( strcmp( guts. font_info[i]. xname, ppFontNameSize) == 0) {
         *font = guts. font_info[i]. font;
         return;
      }
   }
   
   xf = ( XFontStruct * ) hash_fetch( xfontCache, ppFontNameSize, len);

   if ( !xf ) {
      xf = XLoadQueryFont( DISP, ppFontNameSize);
      if ( !xf) {
         Fdebug("font: cannot load %s\n", ppFontNameSize);
         if ( !guts. default_font_ok) {
            fill_default_font( font);
            apc_font_pick( application, font, font);
            font-> pitch = fpDefault;
         }
#ifdef USE_XFT
         if ( !guts. use_xft || !prima_xft_parse( ppFontNameSize, font))
#endif         
            if ( font != &guts. default_font)
               *font = guts. default_font;
         return;
      }
      hash_store( xfontCache, ppFontNameSize, len, xf);
      newEntry = 1;
   }
  
   bzero( &fi, sizeof( fi));
   fi. flags. sloppy = true;
   fi. xname = ppFontNameSize;
   xlfd_parse_font( ppFontNameSize, &fi, false);
   font_query_name( xf, &fi);
   detail_font_info( &fi, font, false, false);
   *font = fi. font;
   if ( guts. default_font_ok) {
      def = &guts. default_font;
   } else {
      fill_default_font( def = &def_dummy);
      apc_font_pick( application, def, def);
   }
   if ( font-> height == 0) font-> height = def-> height;
   if ( font-> size   == 0) font-> size   = def-> size;
   if ( strlen( font-> name) == 0) strcpy( font-> name, def-> name);
   if ( strlen( font-> family) == 0) strcpy( font-> family, def-> family);
   apc_font_pick( application, font, font);
   if (
       ( stricmp( font-> family, fi. font. family) == 0) &&
       ( stricmp( font-> name, fi. font. name) == 0)
      ) newEntry = 0;
   
   if ( newEntry ) {
      PFontInfo n = realloc( guts. font_info, sizeof( FontInfo) * (guts. n_fonts + 1));
      if ( n) {
         guts. font_info = n;
         fi. font = *font;
         guts. font_info[ guts. n_fonts++] = fi;
      }
   }
   Fdebug("font: %s%s parsed to: %d.[w=%d,s=%d].%s.%s\n", 
	  newEntry ? "new " : "", ppFontNameSize, DEBUG_FONT((*font)));
}

void
prima_free_rotated_entry( PCachedFont f)
{
   while ( f-> rotated) {
      PRotatedFont r = f-> rotated;
      while ( r-> length--) {
          if ( r-> map[ r-> length]) {
             prima_free_ximage( r-> map[ r-> length]);
             r-> map[ r-> length] = nil;
          }      
      }   
      f-> rotated = ( PRotatedFont) r-> next;
      XFreeGC( DISP, r-> arena_gc);
      if ( r-> arena) 
         XFreePixmap( DISP, r-> arena);
      if ( r-> arena_bits)
         free( r-> arena_bits);
      free( r);
   }
}   

static Bool
free_rotated_entries( PCachedFont f, int keyLen, void * key, void * dummy)
{
   Bool foo; return foo;
}

void
prima_cleanup_font_subsystem( void)
{
   int i;

   if ( guts. font_names)
      XFreeFontNames( guts. font_names);
   if ( guts. font_info) {
      for ( i = 0; i < guts. n_fonts; i++)
	 if ( guts. font_info[i]. vecname)
	    free( guts. font_info[i]. vecname);
      free( guts. font_info);
   }
   guts. font_names = nil;
   guts. n_fonts = 0;
   guts. font_info = nil;
   
   free(ignore_encodings);
   free(s_ignore_encodings);

   if ( guts. font_hash) {
      hash_first_that( guts. font_hash, (void*)free_rotated_entries, nil, nil, nil); 
      hash_destroy( guts. font_hash, false);
      guts. font_hash = nil;
   }

   hash_destroy( xfontCache, false);
   xfontCache = nil;
   hash_destroy( encodings, false);
   encodings = nil;
#ifdef USE_XFT
   prima_xft_done();
#endif
   
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
   if ( !DISP) return;
   fprintf( stderr, "*** BEGIN FONT DUMP ***\n");
   fprintf( stderr, "height: %d\n", f-> height);
   fprintf( stderr, "width: %d\n", f-> width);
   fprintf( stderr, "style: %d\n", f-> style);
   fprintf( stderr, "pitch: %d\n", f-> pitch);
   fprintf( stderr, "direction: %g\n", f-> direction);
   fprintf( stderr, "name: %s\n", f-> name);
   fprintf( stderr, "family: %s\n", f-> family);
   fprintf( stderr, "size: %d\n", f-> size);
   fprintf( stderr, "*** END FONT DUMP ***\n");
}

void
prima_build_font_key( PFontKey key, PFont f, Bool bySize)
{
   bzero( key, sizeof( FontKey));
   key-> height = bySize ? -f-> size : f-> height;
   key-> width = f-> width;
   key-> style = f-> style & ~(fsUnderlined|fsOutline|fsStruckOut);
   key-> pitch = f-> pitch;
   key-> direction = 0;
   strcpy( key-> name, f-> name);
   strcat( key-> name, "\1");
   strcat( key-> name, f-> encoding);
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
   p-> locked = 0;
   p-> sp     = 1;
   p-> target = target;
   p-> xlfd[0] = firstMove;
}

int
prima_try_height( HeightGuessStack * p, int height)
{
   int foo; return foo;
}

static void
detail_font_info( PFontInfo f, PFont font, Bool addToCache, Bool bySize)
{
   XFontStruct *s = nil;
   unsigned long v;
   char name[ 1024];
   FontInfo fi;
   PFontInfo of = f;
   int height = 0, size = 0;
   FontKey key;
   Bool askedDefaultPitch;
   HeightGuessStack hgs;

   if ( f-> vecname) {
      if ( bySize)
         size = font-> size * 10;
      else {
         height = font-> height * 10;
         prima_init_try_height( &hgs, height, f-> flags. heights_cache ? f-> heights_cache[0] : height);
         if ( f-> flags. heights_cache)
            height = prima_try_height( &hgs, f-> heights_cache[1]);
      }
   }

AGAIN:
   if ( f-> vecname) {
      memcpy( &fi, f, sizeof( fi));
      fi. flags. size = fi. flags. height = fi. flags. width = fi. flags. ascent =
         fi. flags. descent = fi. flags. internalLeading = fi. flags. externalLeading = 0;
      f = &fi;

      if ( f-> flags. bad_vector) {
         /* three fields */
         sprintf( name, f-> vecname, height / 10, size, font-> width * 10);
      } else {
         /* five fields */
         sprintf( name, f-> vecname, height / 10, size, 0, 0, font-> width * 10);
      }
      Fdebug("font: construct h=%g, s=%d\n", (float)height/10, size);
   } else {
      strcpy( name, f-> xname);
   }
   
   Fdebug( "font: loading %s\n", name);
   s = hash_fetch( xfontCache, name, strlen( name));
   
   if ( !s) {
      s = XLoadQueryFont( DISP, name);
      XCHECKPOINT;
      if ( !s) {
         if ( !font) 
            warn( "UAF_004: font %s load error", name);
         if ( of-> flags. disabled) 
            warn( "UAF_005: font %s pick-up error", name);
         of-> flags. disabled = true;
              
         Fdebug( "font: kill %s\n", name);
         if ( font) apc_font_pick( nilHandle, font, font);
         of-> flags. disabled = false;
         return;
      } else {
         hash_store( xfontCache, name, strlen( name), s);
      }   
   }

   if ( f-> flags. sloppy || f-> vecname) {
      /* check first if height is o.k. */
      f-> font. height = s-> max_bounds. ascent + s-> max_bounds. descent;
      f-> flags. height = true;
      if ( f-> vecname && !bySize && f-> font. height != font-> height) {
         int h = prima_try_height( &hgs, f-> font. height * 10);
         Fdebug("font height pick: %d::%d => %d, advised %d\n", hgs.sp-1, font-> height, f-> font. height, h);
         if ( h > 9) {
            if ( !of-> flags. heights_cache) {
               of-> heights_cache[0] = font-> height * 10;
               of-> heights_cache[1] = f-> font. height;
            }
            height = h;
            goto AGAIN;
         } 
      }
      
      /* detailing y-resolution */
      if ( !f-> flags. yDeviceRes) {
         if ( XGetFontProperty( s, FXA_RESOLUTION_Y, &v) && v) {
            XCHECKPOINT;
            f-> font. yDeviceRes = v;
         } else {
            f-> font. yDeviceRes = 72;
         }
         f-> flags. yDeviceRes = true;
      }
      
      /* detailing x-resolution */
      if ( !f-> flags. xDeviceRes) {
         if ( XGetFontProperty( s, FXA_RESOLUTION_X, &v) && v) {
            XCHECKPOINT;
            f-> font. xDeviceRes = v;
         } else {
            f-> font. xDeviceRes = 72;
         }
         f-> flags. xDeviceRes = true;
      }

      /* detailing internal leading */
      if ( !f-> flags. internalLeading) {
         if ( XGetFontProperty( s, FXA_CAP_HEIGHT, &v) && v) {
            XCHECKPOINT;
            f-> font. internalLeading = s-> max_bounds. ascent - v;
         } else {
            if ( f-> flags. height) { 
               f-> font. internalLeading = s-> max_bounds. ascent + s-> max_bounds. descent - f-> font. height;
            } else if ( f-> flags. size) {
               f-> font. internalLeading = s-> max_bounds. ascent + s-> max_bounds. descent - 
                  ( f-> font. size * f-> font. yDeviceRes) / 72.27 + 0.5;
            } else {
               f-> font. internalLeading = 0;
            }
         }
         f-> flags. internalLeading = true;
      }

      /* detailing point size and height */
      if ( bySize) {
         if ( f-> vecname)
            f-> font. size = size / 10;
         else if ( !f-> flags. size)
            f-> font. size = font-> size;
      } else {

         if ( f-> vecname && f-> font. height < font-> height) { /* adjust anyway */
            f-> font. internalLeading += font-> height - f-> font. height;
            f-> font. height = font-> height;
         }

         if ( !f-> flags. size) {
            if ( XGetFontProperty( s, FXA_POINT_SIZE, &v) && v) {
               XCHECKPOINT;
               f-> font. size = ( v < 10) ? 1 : ( v / 10);
            } else 
               f-> font. size = ( f-> font. height - f-> font. internalLeading) * 72.27 / f-> font. height + 0.5;
         }
      }
      f-> flags. size = true;

      /* misc stuff */
      f-> flags. resolution      = true;
      f-> font. resolution       = f-> font. yDeviceRes * 0x10000 + f-> font. xDeviceRes;
      f-> flags. ascent          = true;
      f-> font. ascent           = f-> font. height - s-> max_bounds. descent;
      f-> flags. descent         = true;
      f-> font. descent          = s-> max_bounds. descent; 
      f-> flags. defaultChar     = true;
      f-> font. defaultChar      = s-> default_char;
      f-> flags. firstChar       = true;
      f-> font.  firstChar       = s-> min_byte1 * 256 + s-> min_char_or_byte2;
      f-> flags. lastChar        = true;
      f-> font.  lastChar        = s-> max_byte1 * 256 + s-> max_char_or_byte2;
      f-> flags. direction       = true;
      f-> font.  direction       = 0;
      f-> flags. externalLeading = true;
      f-> font.  externalLeading = abs( s-> max_bounds. ascent - s-> ascent) + 
                                   abs( s-> max_bounds. descent - s-> descent);
      f-> font.  utf8_flags      = 0;				  

      /* detailing width */
      if ( f-> font. width == 0 || !f-> flags. width) {
         if ( XGetFontProperty( s, FXA_AVERAGE_WIDTH, &v) && v) {
            XCHECKPOINT;
            f-> font. width = v / 10;
         } else 
            f-> font. width = s-> max_bounds. width;
      }
      f-> flags. width = true;

      /* detailing maximalWidth */
      if ( !f-> flags. maximalWidth) {
         f-> flags. maximalWidth = true;   
         if ( s-> per_char) {
            int kl = 0, kr = 255, k;
            int rl = 0, rr = 255, r, d;
            f-> font. maximalWidth = 0;
            if ( rl < s-> min_byte1) rl = s-> min_byte1;
            if ( rr > s-> max_byte1) rr = s-> max_byte1;
            if ( kl < s-> min_char_or_byte2) kl = s-> min_char_or_byte2;
            if ( kr > s-> max_char_or_byte2) kr = s-> max_char_or_byte2;
            d = kr - kl + 1;
            for ( r = rl; r <= rr; r++) 
               for ( k = kl; k <= kr; k++) {
                  int x = s-> per_char[( r - s-> min_byte1) * d + k - s-> min_char_or_byte2]. width;
                  if ( f-> font. maximalWidth < x)
                     f-> font. maximalWidth = x;
               }
         } else 
            f-> font. width = f-> font. maximalWidth = s-> max_bounds. width;
      }
      of-> flags. sloppy = false;
   } 

   if ( addToCache && font) {
      /* detailing stuff */
      int underlinePos = 0, underlineThickness = 1;

      /* trust the slant part of style */
      font-> style = f-> font. style;

      /* detailing underline things */
      if ( XGetFontProperty( s, XA_UNDERLINE_POSITION, &v) && v) {
         XCHECKPOINT;
         underlinePos =  -s-> max_bounds. descent + v;
      } else 
         underlinePos = - s-> max_bounds. descent + 1;
      
      if ( XGetFontProperty( s, XA_UNDERLINE_THICKNESS, &v) && v) {
         XCHECKPOINT;
         underlineThickness = v;
      } else
         underlineThickness = 1;

      underlinePos -= underlineThickness;
      if ( -underlinePos + underlineThickness / 2 > s-> max_bounds. descent) 
         underlinePos = -s-> max_bounds. descent + underlineThickness / 2;

      prima_build_font_key( &key, font, bySize); 
      Fdebug("font cache add to :%d.%d.{%d}.%s\n", f-> font.height, f-> font.size, f-> font. style, f-> font.name);
      if ( !add_font_to_cache( &key, f, name, s, underlinePos, underlineThickness))
         return;
      askedDefaultPitch = font-> pitch == fpDefault;
      memcpy( font, &f-> font, sizeof( Font));
      prima_build_font_key( &key, font, false);
      if ( !hash_fetch( guts. font_hash, &key, sizeof( FontKey))) {
         if ( !add_font_to_cache( &key, f, name, s, underlinePos, underlineThickness))
            return;
      }
      
      if ( askedDefaultPitch && font-> pitch != fpDefault) {
        int pitch = font-> pitch;
        font-> pitch = fpDefault;
        prima_build_font_key( &key, font, false);
        if ( !hash_fetch( guts. font_hash, &key, sizeof( FontKey))) {
           if ( !add_font_to_cache( &key, f, name, s, underlinePos, underlineThickness))
              return;
        }
        font-> pitch = pitch;
      }
   }
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
