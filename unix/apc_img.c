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
   PrimaXImage *i;
   int extra_bytes;

   if (width == 0 || height == 0) return false;
  
   switch ( guts.idepth) {
   case 16:     extra_bytes = 1;        break;
   case 24:     extra_bytes = 5;        break;
   case 32:     extra_bytes = 7;        break;
   default:     extra_bytes = 0;
   }

   i = malloc( sizeof( PrimaXImage));
   if (!i) {
      warn("No enough memory");
      return nil;
   }   
   bzero( i, sizeof( PrimaXImage));

#ifdef USE_MITSHM
   if ( guts. shared_image_extension && !bitmap) {
      i-> image = XShmCreateImage( DISP, VISUAL, 
                                   bitmap ? 1 : guts.depth,
                                   bitmap ? XYBitmap : ZPixmap,
                                   nil, &i->xmem, width, height);
      XCHECKPOINT;
      if ( !i-> image) goto normal_way;
      i-> bytes_per_line_alias = i-> image-> bytes_per_line;
      i-> xmem. shmid = shmget( IPC_PRIVATE,
                                i-> image-> bytes_per_line * height + extra_bytes,
                                IPC_CREAT | 0666);
      if ( i-> xmem. shmid < 0) {
         XDestroyImage( i-> image);
         goto normal_way;
      }
      i-> xmem. shmaddr = i-> image-> data = shmat( i-> xmem. shmid, 0, 0);
      if ( i-> xmem. shmaddr == (void*)-1 || i-> xmem. shmaddr == nil) {
         i-> image-> data = nil;
         XDestroyImage( i-> image);
         shmctl( i-> xmem. shmid, IPC_RMID, 0);
         goto normal_way;
      }
      i-> xmem. readOnly = false;
      guts.xshmattach_failed = false;
      XSetErrorHandler(shm_ignore_errors);
      if ( XShmAttach(DISP, &i->xmem) == 0) {
         XCHECKPOINT;
bad_xshm_attach:
         XSetErrorHandler(guts.main_error_handler);
         i-> image-> data = nil;
         XDestroyImage( i-> image);
         shmdt( i-> xmem. shmaddr);
         shmctl( i-> xmem. shmid, IPC_RMID, 0);
         goto normal_way;
      }
      XCHECKPOINT;
      XSync(DISP,false);
      XCHECKPOINT;
      if (guts.xshmattach_failed)       goto bad_xshm_attach;
      shmctl( i-> xmem. shmid, IPC_RMID, 0);
      i-> data_alias = i-> image-> data;
      i-> shm = true;
      return i;
   }
normal_way:
#endif
   i-> bytes_per_line_alias = (( width * (bitmap ? 1 : guts.idepth) + 31) / 32) * 4;
   i-> data_alias = malloc( height * i-> bytes_per_line_alias + extra_bytes);
   if (!i-> data_alias) {
      warn("No enough memory");
      free(i);
      return nil;
   }
   i-> image = XCreateImage( DISP, VISUAL, 
                             bitmap ? 1 : guts.depth,
                             bitmap ? XYBitmap : ZPixmap,
                             0, i-> data_alias,
                             width, height, 32, i-> bytes_per_line_alias);
   XCHECKPOINT;
   if ( !i-> image) {
      warn("XCreateImage(%d,%d) error", width, height);
      free( i-> data_alias);
      free( i);
      return nil;
   }
   return i;
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
   return (ApiHandle) X(self)-> gdrawable;
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
   return (ApiHandle) X(self)-> gdrawable;
}

static Byte*
mirror_bits( void)
{
   static Bool initialized = false;
   static Byte bits[256];
   unsigned int i, j;
   int k;

   if (!initialized) {
      for ( i = 0; i < 256; i++) {
         bits[i] = 0;
         j = i;
         for ( k = 0; k < 8; k++) {
            bits[i] <<= 1;
            if ( j & 0x1)
               bits[i] |= 1;
            j >>= 1;
         }
      }
      initialized = true;
   }

   return bits;
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
   Pixmap px;
   XGCValues gcv;
   GC gc;
   PImage img = ( PImage) self;
   unsigned long fore, back;

   ImageCache * xi = prima_create_image_cache(( PImage) self, nilHandle, type);
   if ( !xi) return nilHandle;
   
   px = XCreatePixmap( DISP, guts. root, img-> w, img-> h, 
       ( type == CACHE_BITMAP) ? 1 : guts. depth);
   if ( !px) return nilHandle;
   
   gcv. graphics_exposures = false;
   gc = XCreateGC( DISP, guts. root, GCGraphicsExposures, &gcv);
   if ( guts. palSize > 0) {
      fore = prima_color_find( self,
          RGB_COMPOSITE( img-> palette[1].r, img-> palette[1].g, img-> palette[1].b),
          -1, nil, RANK_NORMAL);
      back = prima_color_find( self,
          RGB_COMPOSITE( img-> palette[0].r, img-> palette[0].g, img-> palette[0].b),
          -1, nil, RANK_NORMAL);
   } else {
      fore = 
         (((img-> palette[1].r << guts. red_range  ) >> 8) << guts.   red_shift) |
         (((img-> palette[1].g << guts. green_range) >> 8) << guts. green_shift) |
         (((img-> palette[1].b << guts. blue_range ) >> 8) << guts.  blue_shift);
      back = 
         (((img-> palette[0].r << guts. red_range  ) >> 8) << guts.   red_shift) |
         (((img-> palette[0].g << guts. green_range) >> 8) << guts. green_shift) |
         (((img-> palette[0].b << guts. blue_range ) >> 8) << guts.  blue_shift);
   }
      
   XSetForeground( DISP, gc, fore);
   XSetBackground( DISP, gc, back);
   prima_put_ximage( px, gc, xi->image, 0, 0, 0, 0, img-> w, img-> h);
   XFreeGC( DISP, gc);
   return px;
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
   Byte *data;
   PrimaXImage *stretch;
   StretchSeed xseed, yseed;
   XRectangle cr;
   int bpp;
   int sls;
   int tls;
   int xclipstart, xclipsize;
   int yclipstart, yclipsize;

   prima_gp_get_clip_rect( self, &cr, 1);
   xclipstart = cr. x - dst_x;
   xclipsize = cr. width;
   yclipstart = cr. y - dst_y;
   yclipsize = cr. height;
   bpp = ( cache-> image-> format == XYBitmap || cache-> image-> format == XYPixmap) ? 1 : guts. idepth;
   if ( xclipstart + xclipsize <= 0 || yclipstart + yclipsize <= 0) return nil;
   stretch_calculate_seed( src_w, dst_w, &xclipstart, &xclipsize, &xseed);
   stretch_calculate_seed( src_h, dst_h, &yclipstart, &yclipsize, &yseed);
   if ( xclipsize <= 0 || yclipsize <= 0) return nil;
   stretch = prima_prepare_ximage( xclipsize, yclipsize, bpp == 1);
   if ( !stretch) return false;

   tls = get_ximage_bytes_per_line( stretch);
   sls = get_ximage_bytes_per_line( cache);
   data = get_ximage_data( stretch);
   
   {
      Byte * last_source = nil;
      Byte * srcData = ( Byte*) get_ximage_data(cache) + ( src_y + yseed. source) * sls;
      Byte * dstData = data;
      Bool   xshrink = dst_w < 0 ? -dst_w < src_w : dst_w < src_w;
      Bool   yshrink = dst_h < 0 ? -dst_h < src_h : dst_h < src_h;
      mStretchProc * proc = ( mStretchProc*) nil;
      int targetwidth  = xclipsize;
      int targetheight = yclipsize;
      int copyBytes = tls > sls ? sls : tls;
      switch ( bpp) {
      case 1:
          srcData += src_x / ByteBits;
          xseed. source += src_x % ByteBits;
          bzero( dstData, targetheight * tls);
          mbs_init_bits();
          proc = ( mStretchProc * )( xshrink ? mbs_mono_in : mbs_mono_out);
          break;
      case 8: 
          srcData += src_x * sizeof( Pixel8);
          proc = ( mStretchProc * )( xshrink ? mbs_Pixel8_in : mbs_Pixel8_out);
          if ( dst_w == src_w) proc = ( mStretchProc *) mbs_copy;
          break;          
      case 16: 
          srcData += src_x * sizeof( Pixel16);
          proc = ( mStretchProc * )( xshrink ? mbs_Pixel16_in : mbs_Pixel16_out);
          if ( dst_w == src_w) proc = ( mStretchProc *) mbs_copy;
          break;
      case 24: 
          srcData += src_x * sizeof( Pixel24); 
          proc = ( mStretchProc * )( xshrink ? mbs_Pixel24_in : mbs_Pixel24_out);
          if ( dst_w == src_w) proc = ( mStretchProc *) mbs_copy;
          break;
      case 32:    
          srcData += src_x * sizeof( Pixel32); 
          proc = ( mStretchProc * )( xshrink ? mbs_Pixel32_in : mbs_Pixel32_out);
          if ( dst_w == src_w) proc = ( mStretchProc *) mbs_copy;
          break;
      default:
          warn( "UAI_020: %d-bit stretch is not yet implemented", bpp); 
          prima_free_ximage( stretch);
          return nil;
      }   
      
      if ( dst_h < 0) {
         dstData += ( yclipsize - 1) * tls;
         tls = -tls;
      }   

      if ( yshrink) {
         proc( srcData, dstData, dst_w < 0, targetwidth, 
            xseed.step, xseed.count, xseed.source, xseed.last, copyBytes);
         dstData += tls;
         targetheight--;
         while ( targetheight) {
            if ( yseed.count.i.i > yseed.last) {  
               proc( srcData, dstData, dst_w < 0, targetwidth, 
                     xseed.step, xseed.count, xseed.source, xseed.last, copyBytes);
               dstData += tls;
               yseed. last = yseed.count.i.i;
               targetheight--;
            }   
            yseed.count.l += yseed.step.l;
            srcData += sls;
         }   
      } else {
         while ( targetheight) {
            if ( yseed.count.i.i > yseed.last) {
               srcData += sls;
               yseed.last = yseed.count.i.i;
            }   
            yseed.count.l += yseed.step.l;
            if ( last_source == srcData) 
               memcpy( dstData, dstData - tls, ABS(tls)); 
            else {
               last_source = srcData;
               proc( srcData, dstData, dst_w < 0, targetwidth, 
                     xseed.step, xseed.count, xseed.source, xseed. last, copyBytes);
            }   
            dstData += tls;
            targetheight--;
         }   
      }   
   }   
   *x = dst_x + xclipstart;
   *y = dst_y + yclipstart;
   *w = xclipsize;
   *h = yclipsize;
   return stretch;
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

