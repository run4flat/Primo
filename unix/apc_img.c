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
prima_ximage_event( XEvent *eve)
{
}

void
prima_put_ximage( 
	XDrawable win, GC gc, PrimaXImage *i, 
	int src_x, int src_y, int dst_x, int dst_y, int width, int height
) {
}


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

