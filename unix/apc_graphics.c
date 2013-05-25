/*-
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
/*  System dependent graphics (unix, x11)                  */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include "Image.h"

#define SORT(a,b)	{ int swp; if ((a) > (b)) { swp=(a); (a)=(b); (b)=swp; }}
#define REVERT(a)	(XX-> size. y - (a) - 1)
#define SHIFT(a,b)	{ (a) += XX-> gtransform. x + XX-> btransform. x; \
                           (b) += XX-> gtransform. y + XX-> btransform. y; }
#define RANGE(a)        { if ((a) < -16383) (a) = -16383; else if ((a) > 16383) a = 16383; }
#define RANGE2(a,b)     RANGE(a) RANGE(b)
#define RANGE4(a,b,c,d) RANGE(a) RANGE(b) RANGE(c) RANGE(d)
#define REVERSE_BYTES_32(x) ((((x)&0xff)<<24) | (((x)&0xff00)<<8) | (((x)&0xff0000)>>8) | (((x)&0xff000000)>>24))
#define REVERSE_BYTES_24(x) ((((x)&0xff)<<16) | ((x)&0xff00) | (((x)&0xff0000)>>8))
#define REVERSE_BYTES_16(x) ((((x)&0xff)<<8 ) | (((x)&0xff00)>>8))

#define COLOR_R16(x) (((x)>>8)&0xFF00)
#define COLOR_G16(x) ((x)&0xFF00)
#define COLOR_B16(x) (((x)<<8)&0xFF00)

 static int rop_map[] = {
   GXcopy	/* ropCopyPut */,		/* dest  = src */
   GXxor	/* ropXorPut */,		/* dest ^= src */
   GXand	/* ropAndPut */,		/* dest &= src */
   GXor		/* ropOrPut */,			/* dest |= src */
   GXcopyInverted /* ropNotPut */,		/* dest = !src */
   GXinvert	/* ropInvert */,		/* dest = !dest */
   GXclear	/* ropBlackness */,		/* dest = 0 */
   GXandReverse	/* ropNotDestAnd */,		/* dest = (!dest) & src */
   GXorReverse	/* ropNotDestOr */,		/* dest = (!dest) | src */
   GXset	/* ropWhiteness */,		/* dest = 1 */
   GXandInverted /* ropNotSrcAnd */,		/* dest &= !src */
   GXorInverted	/* ropNotSrcOr */,		/* dest |= !src */
   GXequiv	/* ropNotXor */,		/* dest ^= !src */
   GXnand	/* ropNotAnd */,		/* dest = !(src & dest) */
   GXnor	/* ropNotOr */,			/* dest = !(src | dest) */
   GXnoop	/* ropNoOper */			/* dest = dest */
};

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

/* 
   macros to multiply line pattern entries to line width in 
   a more-less aestethic fashion :-)
*/
#define MAX_DASH_LEN 2048
#define dDASH_FIX(line_width,source,length) \
   int df_i, df_lw = line_width, df_len = length; \
   char df_list[MAX_DASH_LEN], *df_src = (char*)source, *df_dst = df_list
#define DASH_FIX \
   if ( df_lw > 1) {\
      int on = 0;\
      if ( df_len > MAX_DASH_LEN) df_len = MAX_DASH_LEN;\
      for ( df_i = 0; df_i < df_len; df_i++) {\
	 unsigned int w = *((unsigned char*)df_src++);\
	 if (( on = !on)) {\
	    if ( w > 1) w *= df_lw;\
	 } else {\
	    w = w * df_lw + 1;\
	 }\
	 if ( w > 255) w = 255;\
	 *((unsigned char*)df_dst++) = w;\
      }\
      df_src = df_list;\
   }
#define DASHES df_src, df_len

void
prima_prepare_drawable_for_painting( Handle self, Bool inside_on_paint)
{
}

void
prima_cleanup_drawable_after_painting( Handle self)
{
}

#define PURE_FOREGROUND if (!XX->flags.brush_fore) {\
   XSetForeground( DISP, XX-> gc, XX-> fore. primary);\
   XX->flags.brush_fore=1;\
}\
XSetFillStyle( DISP, XX-> gc, FillSolid);\

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

static int
arc_completion( double * angleStart, double * angleEnd, int * needFigure)
{
   int foo; return foo;
}

static void
calculate_ellipse_divergence(void)
{
}

#define ELLIPSE_RECT x - ( dX + 1) / 2 + 1, y - dY / 2, dX-guts.ellipseDivergence.x, dY-guts.ellipseDivergence.y
#define FILL_ANTIDEFECT_REPAIRABLE \
      ( rop_map[XX-> paint_rop] == GXcopy ||\
        rop_map[XX-> paint_rop] == GXset  ||\
        rop_map[XX-> paint_rop] == GXclear) 
#define FILL_ANTIDEFECT_OPEN {\
  XGCValues gcv;\
  gcv. line_width = 1;\
  gcv. line_style = LineSolid;\
  XChangeGC( DISP, XX-> gc, GCLineWidth, &gcv);\
}   
#define FILL_ANTIDEFECT_CLOSE {\
  XGCValues gcv;\
  gcv. line_width = XX-> line_width;\
  gcv. line_style = ( XX-> paint_rop2 == ropNoOper) ? LineOnOffDash : LineDoubleDash;\
  XChangeGC( DISP, XX-> gc, GCLineWidth, &gcv);\
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

#define GRAD 57.29577951

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

static int
get_pixel_depth( int depth) 
{
   int foo; return foo;
}
   

static uint32_t
color_to_pixel( Handle self, Color color, int depth)
{
   uint32_t foo; return foo;
}

typedef struct {
   XImage *  i;
   Rect      clip;
   uint32_t  color;
   int       depth;
   int       y;
   Bool      singleBorder;
   XDrawable drawable;
   GC        gc;
   int       first;
   PList  *  lists;
} FillSession;

static Bool 
fs_get_pixel( FillSession * fs, int x, int y)
{
   Bool foo; return foo;
}

static void
hline( FillSession * fs, int x1, int y, int x2)
{
}

static int
fill( FillSession * fs, int sx, int sy, int d, int pxl, int pxr)
{
   int foo; return foo;
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

static Point
gp_get_text_overhangs( Handle self, const char *text, int len, Bool wide)
{
   Point foo; return foo;
}

static int
gp_get_text_width( Handle self, const char *text, int len, Bool addOverhang, Bool wide);

static Point *
gp_get_text_box( Handle self, const char * text, int len, Bool wide);

static Bool
gp_text_out_rotated( Handle self, const char * text, int x, int y, int len, Bool wide, Bool * ok_to_not_rotate) 
{
   Bool foo; return foo;
}

Bool
apc_gp_text_out( Handle self, const char * text, int x, int y, int len, Bool utf8)
{
   Bool foo; return foo;
}

/* gpi settings */
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

/* returns rect in X coordinates BUT without menuHeight deviation */
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

static int
gp_get_text_width( Handle self, const char *text, int len, Bool addOverhang, Bool wide)
{
   int foo; return foo;
}

int
apc_gp_get_text_width( Handle self, const char * text, int len, Bool addOverhang, Bool utf8)
{
   int foo; return foo;
}

static Point *
gp_get_text_box( Handle self, const char * text, int len, Bool wide)
{
   Point * foo; return foo;
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

/*- see apc_font.c
void
apc_gp_set_font( Handle self, PFont font)
*/

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

