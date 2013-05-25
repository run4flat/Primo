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
 * --------------------------------------------------------------------
 *  Parabolic spline procedures taken from TclTk's tkTrig.c
 *  
 *  Copyright (c) 1992-1994 The Regents of the University of California.
 *  Copyright (c) 1994 Sun Microsystems, Inc.
 *
 * See the file "license.terms" in TclTk distribution 
 * for information on usage and redistribution
 * of this code, and for a DISCLAIMER OF ALL WARRANTIES.
 * ---------------------------------------------------------------------
 *
 * $Id$
 */

#include "apricot.h"
#include "Drawable.h"
#include "Image.h"
#include <Drawable.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef my
#define inherited CComponent->
#define my  ((( PDrawable) self)-> self)
#define var (( PDrawable) self)

#define gpARGS            Bool inPaint = opt_InPaint
#define gpENTER(fail)     if ( !inPaint) if ( !my-> begin_paint_info( self)) return (fail)
#define gpLEAVE           if ( !inPaint) my-> end_paint_info( self)

void
Drawable_init( Handle self, HV * profile)
{
}

static void
clear_font_abc_caches( Handle self)
{
}

void
Drawable_done( Handle self)
{
}

void
Drawable_cleanup( Handle self)
{
}

Bool
Drawable_begin_paint( Handle self)
{
   return false;
}

void
Drawable_end_paint( Handle self)
{
}

Bool
Drawable_begin_paint_info( Handle self)
{
   return false;
}

void
Drawable_end_paint_info( Handle self)
{
}

void 
Drawable_set( Handle self, HV * profile)
{
}


Font *
Drawable_font_match( char * dummy, Font * source, Font * dest, Bool pick)
{
   if ( pick) 
      apc_font_pick( nilHandle, source, dest);
   else
      Drawable_font_add( nilHandle, source, dest);
   return dest;
}

Bool
Drawable_font_add( Handle self, Font * source, Font * dest)
{
   Bool useHeight = source-> height    != C_NUMERIC_UNDEF;
   Bool useWidth  = source-> width     != C_NUMERIC_UNDEF;
   Bool useSize   = source-> size      != C_NUMERIC_UNDEF;
   Bool usePitch  = source-> pitch     != C_NUMERIC_UNDEF;
   Bool useStyle  = source-> style     != C_NUMERIC_UNDEF;
   Bool useDir    = source-> direction != C_NUMERIC_UNDEF;
   Bool useName   = strcmp( source-> name, C_STRING_UNDEF) != 0;
   Bool useEnc    = strcmp( source-> encoding, C_STRING_UNDEF) != 0;

   /* assignning values */
   if ( dest != source) {
      if ( useHeight) dest-> height    = source-> height;
      if ( useWidth ) dest-> width     = source-> width;
      if ( useDir   ) dest-> direction = source-> direction;
      if ( useStyle ) dest-> style     = source-> style;
      if ( usePitch ) dest-> pitch     = source-> pitch;
      if ( useSize  ) dest-> size      = source-> size;
      if ( useName  ) strcpy( dest-> name, source-> name);
      if ( useEnc   ) strcpy( dest-> encoding, source-> encoding);
   }

   /* nulling dependencies */
   if ( !useHeight && useSize)
      dest-> height = 0;
   if ( !useWidth && ( usePitch || useHeight || useName || useSize || useDir || useStyle))
      dest-> width = 0;
   if ( !usePitch && ( useStyle || useName || useDir || useWidth))
      dest-> pitch = fpDefault;
   if ( useHeight)
      dest-> size = 0;
   if ( !useHeight && !useSize && ( dest-> height <= 0 || dest-> height > 16383)) 
      useSize = 1;

   /* validating entries */
   if ( dest-> height <= 0) dest-> height = 1;
      else if ( dest-> height > 16383 ) dest-> height = 16383;
   if ( dest-> width  <  0) dest-> width  = 1;
      else if ( dest-> width  > 16383 ) dest-> width  = 16383;
   if ( dest-> size   <= 0) dest-> size   = 1;
      else if ( dest-> size   > 16383 ) dest-> size   = 16383;
   if ( dest-> name[0] == 0)
      strcpy( dest-> name, "Default");
   if ( dest-> pitch < fpDefault || dest-> pitch > fpFixed)
      dest-> pitch = fpDefault;
   if ( dest-> direction == C_NUMERIC_UNDEF)
      dest-> direction = 0;
   if ( dest-> style == C_NUMERIC_UNDEF)
      dest-> style = 0;

   return useSize && !useHeight;
}


int
Drawable_get_paint_state( Handle self)
{
   int foo; return foo;
}

int
Drawable_get_bpp( Handle self)
{
   int foo; return foo;
}

SV *
Drawable_linePattern( Handle self, Bool set, SV * pattern)
{
   return nilSV;
}

Color
Drawable_get_nearest_color( Handle self, Color color)
{
   Color c; return c;
}

Point
Drawable_resolution( Handle self, Bool set, Point resolution)
{
   Point foo; return foo;
}

SV *
Drawable_get_physical_palette( Handle self)
{
   return nilSV;
}

SV *
Drawable_get_font_abc( Handle self, int first, int last, Bool unicode)
{
   return nilSV;
}

SV *
Drawable_get_font_ranges( Handle self)
{
   return nilSV;
}


SV *
Drawable_get_handle( Handle self)
{
   return nilSV;
}

int
Drawable_height( Handle self, Bool set, int height)
{
   int foo; return foo;
}

Point
Drawable_size ( Handle self, Bool set, Point size)
{
   Point foo; return foo;
}

int
Drawable_width( Handle self, Bool set, int width)
{
   int foo; return foo;
}

Bool
Drawable_put_image_indirect( Handle self, Handle image, int x, int y, int xFrom, int yFrom, int xDestLen, int yDestLen, int xLen, int yLen, int rop)
{
   return false;
}

Bool
Drawable_text_out( Handle self, SV * text, int x, int y)
{
   return false;
}

Point *
Drawable_polypoints( SV * points, char * procName, int mod, int * n_points)
{
   Point * foo; return foo;
}

static Bool
polypoints( Handle self, SV * points, char * procName, int mod, Bool (*procPtr)(Handle,int,Point*))
{
   return false;
}

Bool
Drawable_polyline( Handle self, SV * points)
{
   return false;
}

Bool
Drawable_lines( Handle self, SV * points)
{
   return false;
}

Bool
Drawable_fillpoly( Handle self, SV * points)
{
   return false;
}

static void
TkBezierScreenPoints(
    double control[],			/* Array of coordinates for four
					 * control points:  x0, y0, x1, y1,
					 * ... x3 y3. */
    int numSteps,			/* Number of curve points to
					 * generate.  */
    register Point *xPointPtr)		/* Where to put new points. */
{
}

static int
TkMakeBezierCurve(
    int *pointPtr,			/* Array of input coordinates:  x0,
					 * y0, x1, y1, etc.. */
    int numPoints,			/* Number of points at pointPtr. */
    int numSteps,			/* Number of steps to use for each
					 * spline segments (determines
					 * smoothness of curve). */
    Point xPoints[])			/* Array of Points to fill in (e.g.
					 * for display.  NULL means don't
					 * fill in any Points. */
{
   int foo; return foo;
}

#define STATIC_ARRAY_SIZE 200

static Bool
plot_spline( Handle self, int count, Point * points, Bool fill)
{
   return false; 
}  

static Bool
spline( Handle self, int count, Point * points)
{
   return false;
}

static Bool
fill_spline( Handle self, int count, Point * points)
{
   return false;
}

Bool
Drawable_spline( Handle self, SV * points)
{
   return false;
}

Bool
Drawable_fill_spline( Handle self, SV * points)
{
   return false;
}

SV * 
Drawable_render_spline( SV * obj, SV * points, int precision)
{
   return nilSV;
}

int
Drawable_get_text_width( Handle self, SV * text, Bool addOverhang)
{
   int foo; return foo;
}

SV *
Drawable_get_text_box( Handle self, SV * text)
{
   return nilSV;
}

static PFontABC
query_abc_range( Handle self, TextWrapRec * t, unsigned int base)
{
   PFontABC abc;
   return abc;
}

static Bool
precalc_abc_buffer( PFontABC src, float * width, PFontABC dest)
{
   return false;
}

static Bool
add_wrapped_text( TextWrapRec * t, int start, int utfstart, int end, int utfend,
                  int tildeIndex, int * tildePos, int * tildeLPos, int * tildeLine,
                  char *** lArray, int * lSize)
{
   return false;
}
   
char **
Drawable_do_text_wrap( Handle self, TextWrapRec * t)
{
   char **ret;
   return ret;
}

SV*
Drawable_text_wrap( Handle self, SV * text, int width, int options, int tabIndent)
{
   return nilSV;
}


PRGBColor
read_palette( int * palSize, SV * palette)
{
   return nil;
}

Color
Drawable_backColor( Handle self, Bool set, Color color)
{
   Color c; return c;
}

Color
Drawable_color( Handle self, Bool set, Color color)
{
   Color c; return c;
}

Rect
Drawable_clipRect( Handle self, Bool set, Rect clipRect)
{
   return clipRect;
}

Bool
Drawable_fillWinding( Handle self, Bool set, Bool fillWinding)
{
   return fillWinding;
}

int
Drawable_lineEnd( Handle self, Bool set, int lineEnd)
{
   int foo; return foo;
}

int
Drawable_lineJoin( Handle self, Bool set, int lineJoin)
{
   int foo; return foo;
}

int
Drawable_lineWidth( Handle self, Bool set, int lineWidth)
{
   int foo; return foo;
}

SV *
Drawable_palette( Handle self, Bool set, SV * palette)
{
   return nilSV;
}

SV *
Drawable_pixel( Handle self, Bool set, int x, int y, SV * color)
{
   return nilSV;
}

Handle
Drawable_region( Handle self, Bool set, Handle mask)
{
   return nilHandle;
}

int
Drawable_rop( Handle self, Bool set, int rop)
{
   int foo; return foo;
}

int
Drawable_rop2( Handle self, Bool set, int rop2)
{
   int foo; return foo;
}

int
Drawable_splinePrecision( Handle self, Bool set, int splinePrecision)
{
   int foo; return foo;
}

Bool
Drawable_textOpaque( Handle self, Bool set, Bool opaque)
{
   return opaque;
}

Bool
Drawable_textOutBaseline( Handle self, Bool set, Bool textOutBaseline)
{
   return textOutBaseline;
}

Point
Drawable_translate( Handle self, Bool set, Point translate)
{
   Point foo; return foo;
}

SV *
Drawable_fillPattern( Handle self, Bool set, SV * svpattern)
{
   return nilSV;
}

Font
Drawable_get_font( Handle self)
{
   Font foo;
   return foo;
}

void
Drawable_set_font( Handle self, Font font)
{
}


#ifdef __cplusplus
}
#endif
