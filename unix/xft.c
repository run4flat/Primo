#include "unix/guts.h"

#ifdef USE_XFT

#ifdef HAVE_ICONV_H
#include <iconv.h>
#endif

void
prima_xft_init(void)
{
}

void
prima_xft_done(void)
{
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

PFont
prima_xft_fonts( PFont array, const char *facename, const char * encoding, int *retCount)
{
   return nil;
}

void
prima_xft_font_encodings( PHash hash)
{
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
#endif
