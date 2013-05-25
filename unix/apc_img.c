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
/*
 * System dependent image routines (unix, x11)
 */

#include "unix/guts.h"
#include "Image.h"
#include "Icon.h"
#include "DeviceBitmap.h"

#define REVERT(a)	( XX-> size. y - (a) - 1 )
#define SHIFT(a,b)	{ (a) += XX-> gtransform. x + XX-> btransform. x; \
                           (b) += XX-> gtransform. y + XX-> btransform. y; }
/* Multiple evaluation macro! */
#define REVERSE_BYTES_32(x) ((((x)&0xff)<<24) | (((x)&0xff00)<<8) | (((x)&0xff0000)>>8) | (((x)&0xff000000)>>24))
#define REVERSE_BYTES_16(x) ((((x)&0xff)<<8 ) | (((x)&0xff00)>>8))

#define ByteBits                8
#define ByteMask                0xff
#define ByteValues              256
#define LOWER_BYTE(x)           ((x)&ByteMask)
#define ColorComponentMask      ByteMask
#define LSNibble                0x0f
#define LSNibbleShift           0
#define MSNibble                0xf0
#define MSNibbleShift           4
#define NPalEntries4            16
#define NPalEntries8            256

typedef U8 Pixel8;
typedef unsigned long XPixel;

typedef uint16_t Pixel16;

typedef struct
{
   Pixel16 a;
   Pixel16 b;
} Duplet16;

typedef struct
{
   ColorComponent a0, a1, a2;
} Pixel24;

typedef struct
{
   ColorComponent a0, a1, a2;
   ColorComponent b0, b1, b2;
} Duplet24;

typedef uint32_t Pixel32;

typedef struct
{
   Pixel32 a;
   Pixel32 b;
} Duplet32;


#define get_ximage_data(xim)            ((xim)->data_alias)
#define get_ximage_bytes_per_line(xim)  ((xim)->bytes_per_line_alias)

#ifdef USE_MITSHM
static int
shm_ignore_errors(Display *d, XErrorEvent *ev)
{
   int foo; return foo;
}
#endif

PrimaXImage*
prima_prepare_ximage( int width, int height, Bool bitmap)
{
   return nil;
}

void
prima_XDestroyImage( XImage * i)
{
}

Bool
prima_free_ximage( PrimaXImage *i) 
{
   Bool foo; return foo;
}

static Bool
destroy_ximage( PrimaXImage *i)
{
   Bool foo; return foo;
}

static Bool
destroy_one_ximage( PrimaXImage *i, int nothing1, void *nothing2, void *nothing3)
{
   Bool foo; return foo;
}

void
prima_gc_ximages( void )
{
}

void
prima_ximage_event( XEvent *eve) /* to be called from apc_event's handle_event */
{
}

void
prima_put_ximage( 
	XDrawable win, GC gc, PrimaXImage *i, 
	int src_x, int src_y, int dst_x, int dst_y, int width, int height
) {
}


/* image & bitmaps */
Bool
apc_image_create( Handle self)
{
   Bool foo; return foo;
}

static void
clear_caches( Handle self)
{
}

Bool
apc_image_destroy( Handle self)
{
   Bool foo; return foo;
}

ApiHandle
apc_image_get_handle( Handle self)
{
   return nilHandle;
}

Bool
apc_image_begin_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_image_end_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_image_update_change( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_dbm_create( Handle self, Bool monochrome)
{
   Bool foo; return foo;
}

Bool
apc_dbm_destroy( Handle self)
{
   Bool foo; return foo;
}

ApiHandle
apc_dbm_get_handle( Handle self)
{
   return nilHandle;
}

static Byte*
mirror_bits( void)
{
   Byte* foo; return foo;
}

void
prima_copy_xybitmap( unsigned char *data, const unsigned char *idata, int w, int h, int ls, int ils)
{
}

void
prima_mirror_bytes( unsigned char *data, int dataSize)
{
}

static Bool
create_cache1_1( Image *img, ImageCache *cache, Bool for_icon)
{
   Bool foo; return foo;
}

static void
create_rgb_to_8_lut( int ncolors, const PRGBColor pal, Pixel8 *lut)
{
}

static void
create_rgb_to_16_lut( int ncolors, const PRGBColor pal, Pixel16 *lut)
{
}

static int *
rank_rgb_shifts( void)
{
   int * foo; return foo;
}

static void
create_rgb_to_xpixel_lut( int ncolors, const PRGBColor pal, XPixel *lut)
{
}

static Bool
create_cache4_8( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}


static Bool
create_cache4_16( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache4_24( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache4_32( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache_equal( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache8_8_tc( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache8_16( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache8_24( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache8_32( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache24_16( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache24_32( Image *img, ImageCache *cache)
{
   Bool foo; return foo;
}

static Bool
create_cache1( Image* img, ImageCache *cache, int bpp)
{
   Bool foo; return foo;
}

static Bool
create_cache4( Image* img, ImageCache *cache, int bpp)
{
   Bool foo; return foo;
}

static Bool
create_cache8( Image* img, ImageCache *cache, int bpp)
{
   Bool foo; return foo;
}

static Bool
create_cache24( Image* img, ImageCache *cache, int bpp)
{
   Bool foo; return foo;
}

static void
cache_remap_8( Image*img, ImageCache* cache)
{
}

static void
cache_remap_4( Image*img, ImageCache* cache)
{
}

static void
cache_remap_1( Image*img, ImageCache* cache)
{
}


ImageCache*
prima_create_image_cache( PImage img, Handle drawable, int type)
{
   PDrawableSysData IMG = X((Handle)img);
   int target_bpp;
   ImageCache *cache    = &X((Handle)img)-> image_cache;
   Bool ret;
   Handle dup = nilHandle;
   PImage pass = img;

   if ( img-> w == 0 || img-> h == 0) return nil;

   if ( img-> palette == nil) {
      warn( "UAI_014: image has no palette");
      return nil;
   }

   switch ( type) {
   case CACHE_AUTODETECT:
      type = ( drawable == nilHandle || X(drawable) == nil ||
         XT_IS_BITMAP(X(drawable)) || ( guts. idepth == 1)) ?
         CACHE_BITMAP : CACHE_PIXMAP;
      break;
   case CACHE_PIXMAP:
      if ( guts. idepth == 1) type = CACHE_BITMAP;
      break;
   case CACHE_LOW_RES:
      if ( !guts. dynamicColors) type = CACHE_PIXMAP; 
      if ( guts. idepth == 1) type = CACHE_BITMAP;
      break;
   }

   if ( drawable == nilHandle) drawable = application;

   target_bpp = ( type == CACHE_BITMAP) ? 1 : guts. idepth;
   
   if ( XT_IS_ICON(IMG)) {
      if ( cache-> icon == nil) {
         if ( !create_cache1_1( img, cache, true)) {
            return nil;
         }
      }
   } else
      cache-> icon = nil;

   if ( cache-> image != nil) {
      if ( cache-> type == type) return cache;
      destroy_ximage( cache-> image);
      cache-> image = nil;
   }

   if (( img-> type & ( imRealNumber | imComplexNumber | imTrigComplexNumber)) ||
       ( img-> type == imLong || img-> type == imShort)) {
      if ( !dup) {
         if (!(dup = img-> self-> dup(( Handle) img)))
            return nil;
      }
      pass = ( PImage) dup;
      pass-> self->resample(( Handle) pass,
         pass-> self->stats(( Handle) pass, false, isRangeLo, 0),
         pass-> self->stats(( Handle) pass, false, isRangeHi, 0),
         0, 255
      );
      pass-> self-> set_type(( Handle) pass, imByte);
   }
   
   if ( target_bpp <= 8 && img-> type != imBW) {
      int bpp, colors = 0;
      RGBColor palbuf[256], *palptr = nil;
      if ( !dup) {
         if (!(dup = img-> self-> dup(( Handle) img)))
            return nil;
      }
      pass = ( PImage) dup;
      if ( target_bpp <= 1) bpp = imbpp1; else
      if ( target_bpp <= 4) bpp = imbpp4; else bpp = imbpp8;

      if ( guts. palSize > 0 && target_bpp > 1) {
         int i, maxRank = RANK_FREE;
         if ( type == CACHE_LOW_RES) maxRank = RANK_LOCKED;
         for ( i = 0; i < guts. palSize; i++) {
            if ( guts. palette[i]. rank <= maxRank) continue;
            palbuf[colors]. r = guts. palette[i]. r;
            palbuf[colors]. g = guts. palette[i]. g;
            palbuf[colors]. b = guts. palette[i]. b;
            colors++;
            if ( colors > 255) break;
         }
         palptr = palbuf;
      }
      pass-> self-> reset( dup, bpp, palptr, colors);
   } 
     
   switch ( pass-> type & imBPP) {
   case 1:   ret = create_cache1( pass, cache, target_bpp); break;
   case 4:   ret = create_cache4( pass, cache, target_bpp); break;
   case 8:   ret = create_cache8( pass, cache, target_bpp); break;
   case 24:  ret = create_cache24(pass, cache, target_bpp); break;
   default:  
      warn( "UAI_015: unsupported image type");
      return nil;
   }
   if ( !ret) {
      if ( dup) Object_destroy(dup);
      return nil;
   }

   if (( guts. palSize > 0) && (( pass-> type & imBPP) != 24)) {
      int i, maxRank = RANK_FREE;
      Byte * p = X((Handle)img)-> palette;
      if ( type == CACHE_LOW_RES) {
         drawable = application;
         maxRank = RANK_LOCKED; 
      }
               
      for ( i = 0; i < pass-> palSize; i++) {
         int j = guts. mappingPlace[i] = prima_color_find( nilHandle,
            RGB_COMPOSITE( 
              pass-> palette[i].r,
              pass-> palette[i].g,
              pass-> palette[i].b
            ), -1, nil, maxRank);

         if ( p && ( prima_lpal_get( p, j) == RANK_FREE)) 
             prima_color_add_ref(( Handle) img, j, RANK_LOCKED);
      }
      for ( i = pass-> palSize; i < 256; i++) guts. mappingPlace[i] = 0;
      
      switch(target_bpp){
      case 8: if ((pass-> type & imBPP) != 1) cache_remap_8( img, cache); break;
      case 4: if ((pass-> type & imBPP) != 1) cache_remap_4( img, cache); break;
      case 1: cache_remap_1( img, cache); break;
      default: warn("UAI_019: palette is not supported");
      }
   }

   if ( dup) Object_destroy(dup);
   cache-> type = type;
   return cache;
}

Bool
prima_create_icon_pixmaps( Handle self, Pixmap *xor, Pixmap *and)
{
   Bool foo; return foo;
}

static Bool
put_pixmap( Handle self, Handle pixmap, int dst_x, int dst_y, int src_x, int src_y, int w, int h, int rop)
{
   Bool foo; return foo;
}

Bool
apc_gp_put_image( Handle self, Handle image, int x, int y, int xFrom, int yFrom, int xLen, int yLen, int rop)
{
   Bool foo; return foo;
}

Bool
apc_image_begin_paint( Handle self)
{
   Bool foo; return foo;
}

static void
convert_16_to_24( XImage *i, PImage img)
{
}

static void
convert_32_to_24( XImage *i, PImage img)
{
}

static void
convert_equal_paletted( XImage *i, PImage img)
{
}

Bool
prima_query_image( Handle self, XImage * i)
{
   Bool foo; return foo;
}
   
Bool
prima_std_query_image( Handle self, Pixmap px)
{
   Bool foo; return foo;
}

Pixmap
prima_std_pixmap( Handle self, int type)
{
   return nil;
}

Bool
apc_image_end_paint( Handle self)
{
   Bool foo; return foo;
}

/*
   static void
   reverse_buffer_bytes_32( void *buffer, size_t bufsize)
   {
      U32 *buf = buffer;

      if ( bufsize % 4) croak( "UAI_018: expect bufsize % 4 == 0");
      bufsize /= 4;

      while ( bufsize) {
         *buf = REVERSE_BYTES_32(*buf);
         buf++;
         bufsize--;
      }
   }
*/

typedef struct {
   Fixed count;
   Fixed step;
   int source;
   int last;
} StretchSeed;

#define ABS(x) (((x)<0)?(-(x)):(x))

static Bool mbsInitialized = false;
static Byte set_bits[ByteValues];
static Byte clear_bits[ByteValues];

static void mbs_init_bits(void)
{
}

static void 
mbs_mono_in( Byte * srcData, Byte * dstData, Bool xreverse, 
    int targetwidth, Fixed step, Fixed count,int first, int last, int targetLineSize )
{
}

static void 
mbs_mono_out( Byte * srcData, Byte * dstData, Bool xreverse,   
    int targetwidth, Fixed step, Fixed count,int first, int last, int targetLineSize)
{                                                                       
}


#define BS_BYTEEXPAND( type)                                                        \
static void mbs_##type##_out( type * srcData, type * dstData, Bool xreverse,    \
    int targetwidth, Fixed step, Fixed count,int first, int last, int targetLineSize)\
{                                                                       \
}

#define BS_BYTEIMPACT( type)                                                        \
static void mbs_##type##_in( type * srcData, type * dstData, Bool xreverse,    \
    int targetwidth, Fixed step, Fixed count, int first, int last, int targetLineSize)    \
{                                                                       \
}

BS_BYTEEXPAND( Pixel8)
BS_BYTEEXPAND( Pixel16)
BS_BYTEEXPAND( Pixel24)
BS_BYTEEXPAND( Pixel32)

BS_BYTEIMPACT( Pixel8)
BS_BYTEIMPACT( Pixel16)
BS_BYTEIMPACT( Pixel24)
BS_BYTEIMPACT( Pixel32)


static void mbs_copy( Byte * srcData, Byte * dstData, Bool xreverse,  
    int targetwidth, Fixed step, Fixed count, int first, int last, int targetLineSize)
{
}


static void
stretch_calculate_seed( int ssize, int tsize,
                        int *clipstart, int *clipsize,
                        StretchSeed *seed)
/*
   ARGUMENTS:

   INP  int ssize       specifies source 1d size
   INP  int tsize       specifies target size
   I/O  int *clipstart  on input, desired start of clipped stretched image
                        on output, adjusted value
   I/O  int *clipsize   on input, desired size of clipped region
                        on output, adjusted value
   OUT  StretchSeed *seed
                        calculated seed values, should be passed without
                        modification to the actual stretch routine
 */
{
}

typedef void mStretchProc( void * srcData, void * dstData, Bool xreverse, 
   int targetwidth, Fixed step, Fixed count, int first, int last, int targetLineSize);


static PrimaXImage *
do_stretch( Handle self, PrimaXImage *cache,
            int src_x, int src_y, int src_w, int src_h,
            int dst_x, int dst_y, int dst_w, int dst_h,
            int *x, int *y, int *w, int *h)
{
   return nil;
}

Bool
apc_gp_stretch_image( Handle self, Handle image,
		      int dst_x, int dst_y, int src_x, int src_y,
		      int dst_w, int dst_h, int src_w, int src_h, int rop)
{
   Bool foo; return foo;
}

Bool
apc_application_get_bitmap( Handle self, Handle image, int x, int y, int xLen, int yLen)
{
   Bool foo; return foo;
}

