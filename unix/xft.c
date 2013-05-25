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

/*********************************/
/*                               */
/*  Xft - client-side X11 fonts  */
/*                               */
/*********************************/


/*

   USAGE
   -----
   To use specific Xft fonts, set Prima font names in your X resource 
   database in fontconfig formats - for example, Palatino-12. Consult
   'man fontconfig' for the syntax, but be aware that Prima uses only
   size, weight, and name fields.

   IMPLEMENTATION NOTES
   --------------------

   This implementations doesn't work with non-scalable Xft fonts,
   since their rasterization capabilities are currently ( June 2003) very limited - 
   no scaling and no rotation. Plus, the selection of the non-scalable fonts is
   a one big something, and I believe that one in apc_font.c is enough.

   The following Xft/fontconfig problems, if fixed in th next versions, need to be 
   taken into the consideration:
     - no font/glyph data - internal leading, underscore size/position,
       no strikeout size/position, average width.
     - no raster operations
     - no glyph reference point shift
     - no client-side access to glyph bitmaps
     - no on-the-fly antialiasing toggle
     - no text background painting ( only rectangles )
     - no text strikeout / underline drawing routines
     - produces xlib failures for large polygons - answered to be a Xrender bug;
       the X error handler catches this now.

   TO DO
   -----
    - The full set of raster operations - not supported by xft ( stupid )
    - apc_show_message - probably never will be implemented though
    - Investigate if ICONV can be replaced by native perl's ENCODE interface
    - Under some circumstances Xft decides to put antialiasing aside, for
      example, on the paletted displays. Check, if some heuristics that would
      govern whether Xft is to be used there, are needed.
       
 */

#include "unix/guts.h"

#ifdef USE_XFT

#ifdef HAVE_ICONV_H
#include <iconv.h>
#endif

/* fontconfig version < 2.2.0 */
#ifndef FC_WEIGHT_NORMAL
#define FC_WEIGHT_NORMAL 80
#endif
#ifndef FC_WEIGHT_THIN
#define FC_WEIGHT_THIN 0
#endif
#ifndef FC_WIDTH
#define FC_WIDTH "width"
#endif

typedef struct {
   char      *name;
   FcCharSet *fcs;
   int        glyphs;
   Bool       enabled;
   uint32_t   map[128];   /* maps characters 128-255 into unicode */
} CharSetInfo;

static CharSetInfo std_charsets[] = {
    { "iso8859-1",  nil, 0, 1 }
#ifdef HAVE_ICONV_H    
    ,
    { "iso8859-2",  nil, 0, 0 },
    { "iso8859-3",  nil, 0, 0 },
    { "iso8859-4",  nil, 0, 0 },
    { "iso8859-5",  nil, 0, 0 },
    { "iso8859-7",  nil, 0, 0 },
    { "iso8859-8",  nil, 0, 0 },
    { "iso8859-9",  nil, 0, 0 },
    { "iso8859-10", nil, 0, 0 },
    { "iso8859-13", nil, 0, 0 },
    { "iso8859-14", nil, 0, 0 },
    { "iso8859-15", nil, 0, 0 },
    { "koi8-r",     nil, 0, 0 }  /* this is special - change the constant
                                    KOI8_INDEX as well when updating
                                    the table */
/* You are welcome to add more 8-bit charsets here - just keep in mind
   that each encoding requires iconv() to load a file */
#endif    
};

#define KOI8_INDEX 12
#define MAX_CHARSET (sizeof(std_charsets)/sizeof(CharSetInfo))
#define MAX_GLYPH_SIZE (guts.limits.request_length / 256)

static PHash encodings    = nil;
static PHash mismatch     = nil; /* fonts not present in xft base */
static char  fontspecific[] = "fontspecific";
static CharSetInfo * locale = nil;

#ifdef NEED_X11_EXTENSIONS_XRENDER_H
/* piece of Xrender guts */
typedef struct _XExtDisplayInfo {
    struct _XExtDisplayInfo *next;      
    Display *display;                   
    XExtCodes *codes;                   
    XPointer data;                      
} XExtDisplayInfo;

extern XExtDisplayInfo *
XRenderFindDisplay (Display *dpy);
#endif

void
prima_xft_init(void)
{
   CharSetInfo *csi;
   int i;
   FcCharSet * fcs_ascii;
#ifdef HAVE_ICONV_H
   iconv_t ii;
   unsigned char in[128], *iptr;
   char ucs4[12];
   size_t ibl, obl;
   uint32_t *optr;
   int j;
#endif  

#ifdef NEED_X11_EXTENSIONS_XRENDER_H
   { /* snatch error code from xrender guts */
      XExtDisplayInfo *info = XRenderFindDisplay( DISP);
      if ( info && info-> codes)
         guts. xft_xrender_major_opcode = info-> codes-> major_opcode;
   }
#endif   

   if ( !apc_fetch_resource( "Prima", "", "UseXFT", "usexft", 
                              nilHandle, frUnix_int, &guts. use_xft))
      guts. use_xft = 1;
   if ( guts. use_xft) {
      if ( !XftInit(0)) guts. use_xft = 0;
   }
   /* After this point guts.use_xft must never be altered */
   if ( !guts. use_xft) return;
   Fdebug("XFT ok\n");

   csi = std_charsets;
   fcs_ascii = FcCharSetCreate();
   for ( i = 32; i < 127; i++)  FcCharSetAddChar( fcs_ascii, i);


   std_charsets[0]. fcs = FcCharSetUnion( fcs_ascii, fcs_ascii);
   for ( i = 161; i < 255; i++) FcCharSetAddChar( std_charsets[0]. fcs, i);
   for ( i = 128; i < 255; i++) std_charsets[0]. map[i - 128] = i;
   std_charsets[0]. glyphs = ( 127 - 32) + ( 255 - 161);
      
#ifdef HAVE_ICONV_H
   sprintf( ucs4, "UCS-4%cE", (guts.machine_byte_order == LSBFirst) ? 'L' : 'B');
   for ( i = 1; i < MAX_CHARSET; i++) {
      memset( std_charsets[i]. map, 0, sizeof(std_charsets[i]. map));

      ii = iconv_open(ucs4, std_charsets[i]. name);
      if ( ii == (iconv_t)(-1)) continue;

      std_charsets[i]. fcs = FcCharSetUnion( fcs_ascii, fcs_ascii);
      for ( j = 0; j < 128; j++) in[j] = j + 128;
      iptr = in;
      optr = std_charsets[i]. map;
      ibl = 128;
      obl = 128 * sizeof( uint32_t);
      while ( 1 ) {
         int ret = iconv( ii, ( char **) &iptr, &ibl, ( char **) &optr, &obl);
         if ( ret < 0 && errno == EILSEQ) {
            iptr++;
            optr++;
            ibl--;
            obl -= sizeof(uint32_t);
            continue;
         }
         break;
      }
      iconv_close(ii);

      optr = std_charsets[i]. map - 128;
      std_charsets[i]. glyphs = 127 - 32;
      for ( j = (( i == KOI8_INDEX) ? 191 : 161); j < 256; j++) 
         /* koi8 hack - 161-190 are pseudo-graphic symbols, not really characters,
            so don't use them for font matching by a charset */
         if ( optr[j]) {
            FcCharSetAddChar( std_charsets[i]. fcs, optr[j]);
            std_charsets[i]. glyphs++;
         }
      if ( std_charsets[i]. glyphs > 127 - 32) 
         std_charsets[i]. enabled = true;
   }
#endif

   mismatch     = hash_create();
   encodings    = hash_create();
   for ( i = 0; i < MAX_CHARSET; i++) {
      int length = 0;
      char upcase[256], *dest = upcase, *src = std_charsets[i].name;
      if ( !std_charsets[i]. enabled) continue;
      while ( *src) {
         *dest++ = toupper(*src++);
         length++;
      }
      hash_store( encodings, upcase, length, (void*) (std_charsets + i));
      hash_store( encodings, std_charsets[i]. name, length, (void*) (std_charsets + i));
   }
 
   locale = hash_fetch( encodings, guts. locale, strlen( guts.locale));
   if ( !locale) locale = std_charsets;
   FcCharSetDestroy( fcs_ascii);
}

void
prima_xft_done(void)
{
   int i;
   if ( !guts. use_xft) return;
   for ( i = 0; i < MAX_CHARSET; i++)
      if ( std_charsets[i]. fcs)
         FcCharSetDestroy( std_charsets[i]. fcs);
   hash_destroy( encodings, false);
   hash_destroy( mismatch, false);
}

static unsigned short
utf8_flag_strncpy( char * dst, const char * src, unsigned int maxlen, unsigned short is_utf8_flag)
{
	int is_utf8 = 0;
	while ( maxlen-- && *src) {
		if ( *((unsigned char*)src) > 0x7f) 
			is_utf8 = 1;
		*(dst++) = *(src++);
	}
	*dst = 0;
	return is_utf8 ? is_utf8_flag : 0;
}

static void
fcpattern2font( FcPattern * pattern, PFont font)
{
   FcChar8 * s;
   int i, j;
   double d = 1.0;
   FcCharSet *c = nil;

   /* FcPatternPrint( pattern); */
   if ( FcPatternGetString( pattern, FC_FAMILY, 0, &s) == FcResultMatch)
      font-> utf8_flags |= utf8_flag_strncpy( font-> name, (char*)s, 255, FONT_UTF8_NAME);
   if ( FcPatternGetString( pattern, FC_FOUNDRY, 0, &s) == FcResultMatch)
      font-> utf8_flags |= utf8_flag_strncpy( font-> family, (char*)s, 255, FONT_UTF8_FAMILY);
   font-> style = 0;
   if ( FcPatternGetInteger( pattern, FC_SLANT, 0, &i) == FcResultMatch) 
      if ( i == FC_SLANT_ITALIC || i == FC_SLANT_OBLIQUE)
         font-> style |= fsItalic;
   if ( FcPatternGetInteger( pattern, FC_WEIGHT, 0, &i) == FcResultMatch) {
      if ( i <= FC_WEIGHT_LIGHT)
         font-> style |= fsThin;
      else if ( i >= FC_WEIGHT_BOLD)
         font-> style |= fsBold;
   }
   if ( FcPatternGetInteger( pattern, FC_SPACING, 0, &i) == FcResultMatch)
      font-> pitch = (( i == FC_PROPORTIONAL) ? fpVariable : fpFixed);

   if ( FcPatternGetInteger( pattern, FC_PIXEL_SIZE, 0, &font-> height) == FcResultMatch) {
       Fdebug("xft:height factor read:%d\n", font-> height);
   }
   font-> width = 100; /* warning, FC_WIDTH does not reflect FC_MATRIX scale changes */
   if ( FcPatternGetInteger( pattern, FC_WIDTH, 0, &font-> width) == FcResultMatch) {
       Fdebug("xft:width factor read:%d\n", font-> width);
   }
   font-> width = ( font-> width * font-> height) / 100.0 + .5;
   font-> yDeviceRes = guts. resolution. y;
   FcPatternGetInteger( pattern, FC_DPI, 0, &font-> yDeviceRes);
   if ( font-> yDeviceRes <= 0)
      font-> yDeviceRes = guts. resolution. y;
   FcPatternGetBool( pattern, FC_SCALABLE, 0, &font-> vector);
   FcPatternGetDouble( pattern, FC_ASPECT, 0, &d);
   font-> xDeviceRes = font-> yDeviceRes * d;
   if ( 
         (FcPatternGetInteger( pattern, FC_SIZE, 0, &font-> size) != FcResultMatch) &&
         (font-> height != C_NUMERIC_UNDEF)
      ) {
      font-> size = font-> height * 72.27 / font-> yDeviceRes + .5;
      Fdebug("xft:size calculated:%d\n", font-> size);
   }

   font-> firstChar = 32; font-> lastChar = 255;
   font-> breakChar = 32; font-> defaultChar = 32;
   if (( FcPatternGetCharSet( pattern, FC_CHARSET, 0, &c) == FcResultMatch) && c) {
      FcChar32 ucs4, next, map[FC_CHARSET_MAP_SIZE];
      if (( ucs4 = FcCharSetFirstPage( c, map, &next)) != FC_CHARSET_DONE) {
         for (i = 0; i < FC_CHARSET_MAP_SIZE; i++) 
            if ( map[i] ) {
               for (j = 0; j < 32; j++)
                  if (map[i] & (1 << j)) {
                      FcChar32 u = ucs4 + i * 32 + j;
                      font-> firstChar = u;
                      if ( font-> breakChar   < u) font-> breakChar   = u;
                      if ( font-> defaultChar < u) font-> defaultChar = u;
                      goto STOP_1;
                  }
            }
STOP_1:;
         while ( next != FC_CHARSET_DONE)
            ucs4 = FcCharSetNextPage (c, map, &next);
         for (i = FC_CHARSET_MAP_SIZE - 1; i >= 0; i--) 
            if ( map[i] ) {
               for (j = 31; j >= 0; j--)
                  if (map[i] & (1 << j)) {
                      FcChar32 u = ucs4 + i * 32 + j;
                      font-> lastChar = u;
                      if ( font-> breakChar   > u) font-> breakChar   = u;
                      if ( font-> defaultChar > u) font-> defaultChar = u;
                      goto STOP_2;
                  }
            }
STOP_2:;
      }
   }
   
   /* XXX other details? */
   font-> descent = font-> height / 4;
   font-> ascent  = font-> height - font-> descent;
   font-> maximalWidth = font-> width;
   font-> internalLeading = 0;
   font-> externalLeading = 0;
}

static void
xft_build_font_key( PFontKey key, PFont f, Bool bySize)
{
   bzero( key, sizeof( FontKey));
   key-> height = bySize ? -f-> size : f-> height;
   key-> width = f-> width;
   key-> style = f-> style & ~(fsUnderlined|fsOutline|fsStruckOut);
   key-> pitch = f-> pitch;
   key-> direction = f-> direction;
   strcpy( key-> name, f-> name);
}

static PCachedFont
try_size( Handle self, Font f, double size)
{
   FontKey key;
   f. size = size;
   f. height = f. width = C_NUMERIC_UNDEF;
   f. direction = 0;
   if ( !prima_xft_font_pick( self, &f, &f, &size)) return nil;
   f. width = 0;
   xft_build_font_key( &key, &f, true);
   return ( PCachedFont) hash_fetch( guts. font_hash, &key, sizeof( FontKey));
}


Bool
prima_xft_font_pick( Handle self, Font * source, Font * dest, double * size)
{
   Bool foo; return foo;
}

Bool
prima_xft_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

PCachedFont
prima_xft_get_cache( PFont font)
{
   FontKey key;
   PCachedFont kf;
   xft_build_font_key( &key, font, false);
   kf = ( PCachedFont) hash_fetch( guts. font_hash, &key, sizeof( FontKey));
   if ( !kf || !kf-> xft) return nil;
   return kf;
}

/*
   performs 3 types of queries:
   defined(facename) - list of fonts with facename and encoding, if defined encoding
   defined(encoding) - list of fonts with encoding
   !defined(encoding) && !defined(facename) - list of all fonts with all available encodings.

   since apc_fonts does the same and calls xft_fonts, array is the list of fonts
   filled already, so xft_fonts reallocates the list when needed.

   XXX - find proper font metrics, but where??
 */
PFont
prima_xft_fonts( PFont array, const char *facename, const char * encoding, int *retCount)
{
   FcFontSet * s;
   FcPattern   *pat, **ppat;
   FcObjectSet *os;
   PFont newarray, f;
   PHash names = nil;
   CharSetInfo * csi = nil;
   int i;

   if ( encoding) {
      if ( !( csi = ( CharSetInfo*) hash_fetch( encodings, encoding, strlen( encoding))))
         return array;
   }

   pat = FcPatternCreate();
   if ( facename) FcPatternAddString( pat, FC_FAMILY, ( FcChar8*) facename);
   FcPatternAddBool( pat, FC_SCALABLE, 1);
   os = FcObjectSetBuild( FC_FAMILY, FC_CHARSET, FC_ASPECT, 
        FC_SLANT, FC_WEIGHT, FC_SIZE, FC_PIXEL_SIZE, FC_SPACING,
        FC_FOUNDRY, FC_SCALABLE, FC_DPI,
        (void*) 0);
   s = FcFontList( 0, pat, os);
   FcObjectSetDestroy( os);
   FcPatternDestroy( pat);
   if ( !s) return array;

   /* XXX make dynamic */
   if ( !( newarray = realloc( array, sizeof(Font) * (*retCount + s-> nfont * MAX_CHARSET)))) {
      FcFontSetDestroy(s);
      return array;
   }
   ppat = s-> fonts; 
   f = newarray + *retCount;
   bzero( f, sizeof( Font) * s-> nfont * MAX_CHARSET);

   names = hash_create();
   
   for ( i = 0; i < s->nfont; i++, ppat++) {
      FcCharSet *c = nil;
      fcpattern2font( *ppat, f);
      FcPatternGetCharSet( *ppat, FC_CHARSET, 0, &c);
      if ( c && FcCharSetCount(c) == 0) continue;
      if ( encoding) {
         /* case 1 - encoding is set, filter only given encoding */
         if ( c && ( FcCharSetIntersectCount( csi-> fcs, c) >= csi-> glyphs - 1)) {
            if ( !facename) {
               /* and, if no facename set, each facename is reported only once */
               if ( hash_fetch( names, f-> name, strlen( f-> name))) continue;
               hash_store( names, f-> name, strlen( f-> name), ( void*)1);
            }
            strncpy( f-> encoding, encoding, 255);
            f++;
         } 
      } else if ( facename) {
         /* case 2 - facename only is set, report each facename with every encoding */
         int j;
         Font * tmpl = f;
         for ( j = 0; j < MAX_CHARSET; j++) {
            if ( !std_charsets[j]. enabled) continue;
            if ( FcCharSetIntersectCount( c, std_charsets[j]. fcs) >= std_charsets[j]. glyphs - 1) {
               *f = *tmpl;
               strncpy( f-> encoding, std_charsets[j]. name, 255);
               f++;
            }
         }
         if ( f == tmpl) {/* no encodings found */
            strcpy( f-> encoding, fontspecific);
            f++;
         }
      } else if ( !facename && !encoding) { 
         /* case 3 - report unique facenames and store list of encodings
            into the hack array */
         if ( hash_fetch( names, f-> name, strlen( f-> name)) == (void*)1) continue;
         hash_store( names, f-> name, strlen( f-> name), (void*)1);
         if ( c) {
            int j, found = 0;
            char ** enc = (char**) f-> encoding;
            unsigned char * shift = (unsigned char*)enc + sizeof(char *) - 1;
            for ( j = 0; j < MAX_CHARSET; j++) {
               if ( !std_charsets[j]. enabled) continue;
               if ( *shift + 2 >= 256 / sizeof(char*)) break;
               if ( FcCharSetIntersectCount( c, std_charsets[j]. fcs) >= std_charsets[j]. glyphs - 1) {
                  char buf[ 512];
                  int len = snprintf( buf, 511, "%s-charset-%s", f-> name, std_charsets[j]. name);
                  if ( hash_fetch( names, buf, len) == (void*)2) continue;
                  hash_store( names, buf, len, (void*)2);
                  *(enc + ++(*shift)) = std_charsets[j]. name;
                  found = 1;
               }
            }
            if ( !found)
               *(enc + ++(*shift)) = fontspecific;
         }
         f++;
      }
   }

   *retCount = f - newarray;
   
   hash_destroy( names, false);
   
   FcFontSetDestroy(s);
   return newarray;
}

void
prima_xft_font_encodings( PHash hash)
{
   int i;
   for ( i = 0; i < MAX_CHARSET; i++) {
      if ( !std_charsets[i]. enabled) continue;
      hash_store( hash, std_charsets[i]. name, strlen(std_charsets[i]. name), (void*) (std_charsets + i));
   }
}
   
static FcChar32 *
xft_text2ucs4( const unsigned char * text, int len, Bool utf8, uint32_t * map8)
{
   FcChar32 *ret, *r;
   if ( utf8) {
      STRLEN charlen, bytelen = strlen(text);
      (void)bytelen;

      if ( len < 0) len = prima_utf8_length(( char*) text);
      if ( !( r = ret = malloc( len * sizeof( FcChar32)))) return nil;
      while ( len--) {
         *(r++) = 
#if PERL_PATCHLEVEL >= 16
         utf8_to_uvchr_buf(( U8*) text, ( U8*) + bytelen, &charlen)
#else
         utf8_to_uvchr(( U8*) text, &charlen)
#endif
         ;
         text += charlen;
	 if ( charlen == 0 ) break;
      }
   } else {
      int i;
      if ( len < 0) len = strlen(( char*) text);
      if ( !( ret = malloc( len * sizeof( FcChar32)))) return nil;
      for ( i = 0; i < len; i++) 
         ret[i] = ( text[i] < 128) ? text[i] : map8[ text[i] - 128];
   }
   return ret;
}

int
prima_xft_get_text_width( PCachedFont self, const char * text, int len, Bool addOverhang, 
                          Bool utf8, uint32_t * map8, Point * overhangs)
{
   int foo; return foo;
}

Point *
prima_xft_get_text_box( Handle self, const char * text, int len, Bool utf8)
{
   DEFXX;
   Point ovx;
   int width;
   Point * pt = ( Point *) malloc( sizeof( Point) * 5);
   if ( !pt) return nil;

   width = prima_xft_get_text_width( XX-> font, text, len, 
      false, utf8, X(self)-> xft_map8, &ovx);

   pt[0].y = pt[2]. y = XX-> font-> font. ascent - 1;
   pt[1].y = pt[3]. y = - XX-> font-> font. descent;
   pt[4].y = 0;
   pt[4].x = width;
   pt[3].x = pt[2]. x = width + ovx. y;
   pt[0].x = pt[1]. x = - ovx. x;

   if ( !XX-> flags. paint_base_line) {
      int i;
      for ( i = 0; i < 4; i++) pt[i]. y += XX-> font-> font. descent;
   }   
   
   if ( PDrawable( self)-> font. direction != 0) {
      int i;
      double s = sin( PDrawable( self)-> font. direction / 57.29577951);
      double c = cos( PDrawable( self)-> font. direction / 57.29577951);
      for ( i = 0; i < 5; i++) {
         double x = pt[i]. x * c - pt[i]. y * s;
         double y = pt[i]. x * s + pt[i]. y * c;
         pt[i]. x = x + (( x > 0) ? 0.5 : -0.5);
         pt[i]. y = y + (( y > 0) ? 0.5 : -0.5);
      }
   }
 
   return pt;
}

static XftFont *
create_no_aa_font( XftFont * font)
{
   FcPattern * request;
   if (!( request = FcPatternDuplicate( font-> pattern))) return nil;
   FcPatternDel( request, FC_ANTIALIAS);
   FcPatternAddBool( request, FC_ANTIALIAS, 0);
   return XftFontOpenPattern( DISP, request);
}

#define SORT(a,b)	{ int swp; if ((a) > (b)) { swp=(a); (a)=(b); (b)=swp; }}
#define REVERT(a)	(XX-> size. y - (a) - 1)
#define SHIFT(a,b)	{ (a) += XX-> gtransform. x + XX-> btransform. x; \
                           (b) += XX-> gtransform. y + XX-> btransform. y; }
#define RANGE(a)        { if ((a) < -16383) (a) = -16383; else if ((a) > 16383) a = 16383; }
#define RANGE2(a,b)     RANGE(a) RANGE(b)
#define RANGE4(a,b,c,d) RANGE(a) RANGE(b) RANGE(c) RANGE(d)

/* When plotting rotated fonts, xft does not account for the accumulated
   roundoff error, and thus the text line is shown at different angle
   than requested. We track this and align the reference point when it
   deviates from the ideal line */
void
my_XftDrawString32( PDrawableSysData selfxx,
	_Xconst XftColor *color, int x, int y,
	_Xconst FcChar32 *string, int len)
{
	int i, lastchar, lx, ly, ox, oy, shift;
	if ( XX-> font-> font. direction == 0) {
		XftDrawString32( XX-> xft_drawable, color, XX-> font-> xft, x, y, string, len);
		return;
	}
	lx = ox = x;
	ly = oy = y;
	lastchar = 0;
	shift = 0;
	for ( i = 0; i < len; i++) {
		int cx, cy;
		FT_UInt ft_index;
		XGlyphInfo glyph;
		ft_index = XftCharIndex( DISP, XX-> font-> xft, string[i]);
		XftGlyphExtents( DISP, XX-> font-> xft, &ft_index, 1, &glyph);
		lx += glyph. xOff;
		ly += glyph. yOff;
		XftGlyphExtents( DISP, XX-> font-> xft_base, &ft_index, 1, &glyph);
		shift += glyph. xOff;
		cx = ox + (int)(shift * XX-> xft_font_cos + 0.5);
		cy = oy - (int)(shift * XX-> xft_font_sin + 0.5);
		if ( cx == lx && cy == ly) continue;

		XftDrawString32( XX-> xft_drawable, color, XX-> font-> xft, 
			x, y, string + lastchar, i - lastchar + 1);
		lastchar = i + 1;
		x = lx = cx;
		y = ly = cy;
	}

	if ( lastchar < len)
		XftDrawString32( XX-> xft_drawable, color, XX-> font-> xft, 
			x, y, string + lastchar, len - lastchar);
}

Bool
prima_xft_text_out( Handle self, const char * text, int x, int y, int len, Bool utf8)
{
   Bool foo; return foo;
}
                             
static Bool
xft_add_item( unsigned long ** list, int * count, int * size, FcChar32 chr, 
              Bool decrease_count_if_failed)
{
   Bool foo; return foo;
}

unsigned long *
prima_xft_get_font_ranges( Handle self, int * count)
{
   FcChar32 ucs4, last = 0, haslast = 0;
   FcChar32 map[FC_CHARSET_MAP_SIZE];
   FcChar32 next;
   FcCharSet *c = X(self)-> font-> xft-> charset;
   int size = 16;
   unsigned long * ret;

#define ADD(ch,flag) if(!xft_add_item(&ret,count,&size,ch,flag)) return ret

   *count = 0;
   if ( !c) return false;
   if ( !( ret = malloc( sizeof( unsigned long) * size))) return nil;

   if ( FcCharSetCount(c) == 0) {
      /* better than nothing */
      ADD( 32, true);
      ADD( 128, false);
      return ret;
   }

   for (ucs4 = FcCharSetFirstPage (c, map, &next);
        ucs4 != FC_CHARSET_DONE;
        ucs4 = FcCharSetNextPage (c, map, &next))
   {
       int i, j;
       for (i = 0; i < FC_CHARSET_MAP_SIZE; i++)
           if (map[i]) {
               for (j = 0; j < 32; j++)
                   if (map[i] & (1 << j)) {
                       FcChar32 u = ucs4 + i * 32 + j;
                       if ( haslast) {
                          if ( last != u - 1) {
                             ADD( last,true);
                             ADD( u,false);
                          }
                       } else {
                          ADD( u,false);
                          haslast = 1;
                       }
                       last = u;
                   }
           }
   }
   if ( haslast) ADD( last,true);

   return ret;
}

PFontABC
prima_xft_get_font_abc( Handle self, int firstChar, int lastChar, Bool unicode)
{
   PFontABC abc;
   int i, len = lastChar - firstChar + 1;
   XftFont *font = X(self)-> font-> xft_base;

   if ( !( abc = malloc( sizeof( FontABC) * len))) 
      return nil;

   for ( i = 0; i < len; i++) {
      FcChar32 c = i + firstChar;
      FT_UInt ft_index;
      XGlyphInfo glyph;
      if ( !unicode && c > 128) {
         c = X(self)-> xft_map8[ c - 128];
      }
      ft_index = XftCharIndex( DISP, font, c);
      XftGlyphExtents( DISP, font, &ft_index, 1, &glyph);
      abc[i]. a = -glyph. x;
      abc[i]. b = glyph. width;
      abc[i]. c = glyph. xOff - glyph. width + glyph. x;
   }

   return abc;
}

uint32_t *
prima_xft_map8( const char * encoding)
{
   CharSetInfo * csi;
   if ( !( csi = hash_fetch( encodings, encoding, strlen( encoding))))
      csi = locale;
   return csi-> map;
}

Bool
prima_xft_parse( char * ppFontNameSize, Font * font)
{
   Bool foo; return foo;
}

void
prima_xft_update_region( Handle self)
{
   DEFXX;
   if ( XX-> xft_drawable) {
      XftDrawSetClip( XX-> xft_drawable, XX-> current_region);
      XX-> flags. xft_clip = 1;
   }
}

#else
#error Required: Xft version 2.1.0 or higher; fontconfig version 2.0.1 or higher. To compile without Xft, re-run 'perl Makefile.PL WITH_XFT=0'
#endif /* USE_XFT */
