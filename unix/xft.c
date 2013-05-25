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
}

void
prima_xft_done(void)
{
}

static unsigned short
utf8_flag_strncpy( char * dst, const char * src, unsigned int maxlen, unsigned short is_utf8_flag)
{
   return 0;
}

static void
fcpattern2font( FcPattern * pattern, PFont font)
{
}

static void
xft_build_font_key( PFontKey key, PFont f, Bool bySize)
{
}

static PCachedFont
try_size( Handle self, Font f, double size)
{
   return nil;
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
   return nil;
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
   return nil;
}

void
prima_xft_font_encodings( PHash hash)
{
}
   
static FcChar32 *
xft_text2ucs4( const unsigned char * text, int len, Bool utf8, uint32_t * map8)
{
   FcChar32 *ret;
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
   Point * foo; return foo;
}

static XftFont *
create_no_aa_font( XftFont * font)
{
   FcPattern * request;
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
   unsigned long * foo; return foo;
}

PFontABC
prima_xft_get_font_abc( Handle self, int firstChar, int lastChar, Bool unicode)
{
   return nil;
}

uint32_t *
prima_xft_map8( const char * encoding)
{
   uint32_t * foo; return foo;
}

Bool
prima_xft_parse( char * ppFontNameSize, Font * font)
{
   Bool foo; return foo;
}

void
prima_xft_update_region( Handle self)
{
}

#else
#error Required: Xft version 2.1.0 or higher; fontconfig version 2.0.1 or higher. To compile without Xft, re-run 'perl Makefile.PL WITH_XFT=0'
#endif /* USE_XFT */
