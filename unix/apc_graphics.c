#include "unix/guts.h"
#include "Image.h"

int
prima_rop_map( int rop)
{
   int foo; return foo;
}

void
prima_get_gc( PDrawableSysData selfxx)
{
}

void
prima_release_gc( PDrawableSysData selfxx)
{
}

void
prima_prepare_drawable_for_painting( Handle self, Bool inside_on_paint)
{
}

void
prima_cleanup_drawable_after_painting( Handle self)
{
}

Bool
prima_make_brush( DrawableSysData * XX, int colorIndex)
{
   Bool foo; return foo;
}
   
Bool
apc_gp_init( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_gp_done( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_gp_arc( Handle self, int x, int y, int dX, int dY, double angleStart, double angleEnd)
{
   Bool foo; return foo;
}

Bool
apc_gp_bar( Handle self, int x1, int y1, int x2, int y2)
{
   Bool foo; return foo;
}

Bool
apc_gp_clear( Handle self, int x1, int y1, int x2, int y2)
{
   Bool foo; return foo;
}

Bool
apc_gp_chord( Handle self, int x, int y, int dX, int dY, double angleStart, double angleEnd)
{
   Bool foo; return foo;
}

Bool
apc_gp_draw_poly( Handle self, int n, Point *pp)
{
   Bool foo; return foo;
}

Bool
apc_gp_draw_poly2( Handle self, int np, Point *pp)
{
   Bool foo; return foo;
}

Bool
apc_gp_ellipse( Handle self, int x, int y, int dX, int dY)
{
   Bool foo; return foo;
}

Bool
apc_gp_fill_chord( Handle self, int x, int y, int dX, int dY, double angleStart, double angleEnd)
{
   Bool foo; return foo;
}

Bool
apc_gp_fill_ellipse( Handle self, int x, int y,  int dX, int dY)
{
   Bool foo; return foo;
}

Bool
apc_gp_fill_poly( Handle self, int numPts, Point *points)
{
   Bool foo; return foo;
}

Bool
apc_gp_fill_sector( Handle self, int x, int y, int dX, int dY, double angleStart, double angleEnd)
{
   Bool foo; return foo;
}

Bool
apc_gp_flood_fill( Handle self, int x, int y, Color color, Bool singleBorder)
{
   Bool foo; return foo;
}

Color
apc_gp_get_pixel( Handle self, int x, int y)
{
   Color foo; return foo;
}

Color
apc_gp_get_nearest_color( Handle self, Color color)
{
   Color foo; return foo;
}

PRGBColor
apc_gp_get_physical_palette( Handle self, int * colors)
{
   return nil;
}

Bool
apc_gp_get_region( Handle self, Handle mask)
{
   Bool foo; return foo;
}

Bool
apc_gp_line( Handle self, int x1, int y1, int x2, int y2)
{
   Bool foo; return foo;
}

Bool
apc_gp_rectangle( Handle self, int x1, int y1, int x2, int y2)
{
   Bool foo; return foo;
}

Bool
apc_gp_sector( Handle self, int x, int y,  int dX, int dY, double angleStart, double angleEnd)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_palette( Handle self)
{
   Bool foo; return foo;
}

Region
region_create( Handle mask)
{
   Region foo; return foo;
}

Bool
apc_gp_set_region( Handle self, Handle mask)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_pixel( Handle self, int x, int y, Color color)
{
   Bool foo; return foo;
}

Bool
apc_gp_text_out( Handle self, const char * text, int x, int y, int len, Bool utf8)
{
   Bool foo; return foo;
}

Color
apc_gp_get_back_color( Handle self)
{
   Color foo; return foo;
}

int
apc_gp_get_bpp( Handle self)
{
   int foo; return foo;
}

Color
apc_gp_get_color( Handle self)
{
   Color foo; return foo;
}

void
prima_gp_get_clip_rect( Handle self, XRectangle *cr, Bool for_internal_paints)
{
}

Rect
apc_gp_get_clip_rect( Handle self)
{
   Rect foo; return foo;
}

PFontABC
prima_xfont2abc( XFontStruct * fs, int firstChar, int lastChar)
{
   return nil;
}

PFontABC
apc_gp_get_font_abc( Handle self, int firstChar, int lastChar, Bool unicode)
{
   return nil;
}

unsigned long *
apc_gp_get_font_ranges( Handle self, int * count)
{
   unsigned long * foo; return foo;
}

Bool
apc_gp_get_fill_winding( Handle self)
{
   Bool foo; return foo;
}

FillPattern *
apc_gp_get_fill_pattern( Handle self)
{
   return &(X(self)-> fill_pattern);
}

int
apc_gp_get_line_end( Handle self)
{
   int foo; return foo;
}

int
apc_gp_get_line_join( Handle self)
{
   int foo; return foo;
}

int
apc_gp_get_line_width( Handle self)
{
   int foo; return foo;
}

int
apc_gp_get_line_pattern( Handle self, unsigned char *dashes)
{
   int foo; return foo;
}

Point
apc_gp_get_resolution( Handle self)
{
   Point foo; return foo;
}

int
apc_gp_get_rop( Handle self)
{
   int foo; return foo;
}

int
apc_gp_get_rop2( Handle self)
{
   int foo; return foo;
}


int
apc_gp_get_text_width( Handle self, const char * text, int len, Bool addOverhang, Bool utf8)
{
   int foo; return foo;
}


Point *
apc_gp_get_text_box( Handle self, const char * text, int len, Bool utf8)
{
   Point * foo; return foo;
}

Point
apc_gp_get_transform( Handle self)
{
   Point foo; return foo;
}

Bool
apc_gp_get_text_opaque( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_gp_get_text_out_baseline( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_clip_rect( Handle self, Rect clipRect)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_back_color( Handle self, Color color)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_color( Handle self, Color color)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_fill_winding( Handle self, Bool fillWinding)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_fill_pattern( Handle self, FillPattern pattern)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_line_end( Handle self, int lineEnd)
{
}

Bool
apc_gp_set_line_join( Handle self, int lineJoin)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_line_width( Handle self, int line_width)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_line_pattern( Handle self, unsigned char *pattern, int len)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_rop( Handle self, int rop)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_rop2( Handle self, int rop)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_transform( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_text_opaque( Handle self, Bool opaque)
{
   Bool foo; return foo;
}

Bool
apc_gp_set_text_out_baseline( Handle self, Bool baseline)
{
   Bool foo; return foo;
}

ApiHandle
apc_gp_get_handle( Handle self)
{
   return nilHandle;
}

