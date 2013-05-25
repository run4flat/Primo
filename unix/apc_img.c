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

void
prima_copy_xybitmap( unsigned char *data, const unsigned char *idata, int w, int h, int ls, int ils)
{
}

void
prima_mirror_bytes( unsigned char *data, int dataSize)
{
}
















ImageCache*
prima_create_image_cache( PImage img, Handle drawable, int type)
{
   ImageCache* foo; return foo;
}

Bool
prima_create_icon_pixmaps( Handle self, Pixmap *xor, Pixmap *and)
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

