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
/*  System dependent color management                      */
/*                                                         */
/***********************************************************/

#include "unix/guts.h"
#include "Drawable.h"
#include "Window.h"

/* have two color layouts for panel widgets (lists, edits) and gray widgets (buttons, labels) */
#define COLOR_DEFAULT_TEXT         0x000000
#define COLOR_DEFAULT_GRAY         0xcccccc
#define COLOR_DEFAULT_BACK         0xffffff

#define COLOR_GRAY_NORMAL_TEXT     COLOR_DEFAULT_TEXT
#define COLOR_GRAY_NORMAL_BACK     COLOR_DEFAULT_GRAY
#define COLOR_GRAY_HILITE_TEXT     COLOR_DEFAULT_TEXT
#define COLOR_GRAY_HILITE_BACK     COLOR_DEFAULT_GRAY
#define COLOR_GRAY_DISABLED_TEXT   0x606060
#define COLOR_GRAY_DISABLED_BACK   0xcccccc

#define COLOR_PANEL_NORMAL_TEXT    COLOR_DEFAULT_TEXT
#define COLOR_PANEL_NORMAL_BACK    COLOR_DEFAULT_BACK
#define COLOR_PANEL_HILITE_TEXT    COLOR_DEFAULT_BACK
#define COLOR_PANEL_HILITE_BACK    COLOR_DEFAULT_TEXT
#define COLOR_PANEL_DISABLED_TEXT  0x606060
#define COLOR_PANEL_DISABLED_BACK  0xdddddd

#define COLOR_LIGHT3D              0xffffff
#define COLOR_DARK3D               0x808080

#define COLORSET_GRAY_NORMAL       COLOR_GRAY_NORMAL_TEXT,   COLOR_GRAY_NORMAL_BACK
#define COLORSET_GRAY_HILITE       COLOR_GRAY_HILITE_TEXT,   COLOR_GRAY_HILITE_BACK
#define COLORSET_GRAY_ALT_HILITE   COLOR_GRAY_HILITE_BACK,   COLOR_GRAY_HILITE_TEXT
#define COLORSET_GRAY_DISABLED     COLOR_GRAY_DISABLED_TEXT, COLOR_GRAY_DISABLED_BACK

#define COLORSET_PANEL_NORMAL      COLOR_PANEL_NORMAL_TEXT,   COLOR_PANEL_NORMAL_BACK
#define COLORSET_PANEL_HILITE      COLOR_PANEL_HILITE_TEXT,   COLOR_PANEL_HILITE_BACK
#define COLORSET_PANEL_DISABLED    COLOR_PANEL_DISABLED_TEXT, COLOR_PANEL_DISABLED_BACK

#define COLORSET_3D                COLOR_LIGHT3D, COLOR_DARK3D

#define COLORSET_GRAY              COLORSET_GRAY_NORMAL, COLORSET_GRAY_HILITE, \
                                   COLORSET_GRAY_DISABLED, COLORSET_3D
#define COLORSET_ALT_GRAY          COLORSET_GRAY_NORMAL, COLORSET_GRAY_ALT_HILITE, \
                                   COLORSET_GRAY_DISABLED, COLORSET_3D
#define COLORSET_PANEL             COLORSET_PANEL_NORMAL, COLORSET_PANEL_HILITE, \
                                   COLORSET_PANEL_DISABLED, COLORSET_3D

static Color standard_button_colors[]      = { COLORSET_GRAY     };
static Color standard_checkbox_colors[]    = { COLORSET_GRAY     };
static Color standard_combo_colors[]       = { COLORSET_GRAY     };
static Color standard_dialog_colors[]      = { COLORSET_GRAY     };
static Color standard_edit_colors[]        = { COLORSET_PANEL    };
static Color standard_inputline_colors[]   = { COLORSET_PANEL    };
static Color standard_label_colors[]       = { COLORSET_GRAY     };
static Color standard_listbox_colors[]     = { COLORSET_PANEL    };
static Color standard_popup_colors[]       = { COLORSET_ALT_GRAY };
static Color standard_radio_colors[]       = { COLORSET_GRAY     };
static Color standard_scrollbar_colors[]   = { COLORSET_ALT_GRAY };
static Color standard_slider_colors[]      = { COLORSET_GRAY     };
static Color standard_widget_colors[]      = { COLORSET_ALT_GRAY };
static Color standard_window_colors[]      = { COLORSET_GRAY     };
static Color standard_application_colors[] = { COLORSET_GRAY     };

static Color* standard_colors[] = {
   nil,
   standard_button_colors,		/* Prima.Button.* */
   standard_checkbox_colors,		/* Prima.Checkbox.* */
   standard_combo_colors,		/* Prima.Combo.* */
   standard_dialog_colors,		/* Prima.Dialog.* */
   standard_edit_colors,		/*   ...etc... */
   standard_inputline_colors,
   standard_label_colors,
   standard_listbox_colors,
   standard_popup_colors,
   standard_radio_colors,
   standard_scrollbar_colors,
   standard_slider_colors,
   standard_widget_colors,
   standard_window_colors,
   standard_application_colors,
};

static const int MAX_COLOR_CLASS = sizeof( standard_colors) / sizeof( standard_colors[ 0]) - 1;

/* maps RGB or cl-constant value to RGB value.  */
Color 
prima_map_color( Color clr, int * hint)
{
   long cls;
   if ( hint) *hint = COLORHINT_NONE;
   if (( clr & clSysFlag) == 0) return clr;
   
   cls = (clr & wcMask) >> 16;
   if ( cls <= 0 || cls > MAX_COLOR_CLASS) cls = (wcWidget) >> 16;
   if (( clr = ( clr & ~wcMask)) > clMaxSysColor) clr = clMaxSysColor;
   if ( clr == clSet)   {
      if ( hint) *hint = COLORHINT_WHITE;
      return 0xffffff; 
   } else if ( clr == clClear) {
      if ( hint) *hint = COLORHINT_BLACK;
      return 0; 
   } else return standard_colors[cls][(clr & clSysMask) - 1];
}   

Color
apc_widget_map_color( Handle self, Color color)
{
   if ((( color & clSysFlag) != 0) && (( color & wcMask) == 0)) color |= PWidget(self)-> widgetClass;
   return prima_map_color( color, nil);
}   

static PHash  hatches;
static Bool   kill_hatches( Pixmap pixmap, int keyLen, void * key, void * dummy);
static Bool   prima_color_new( XColor * xc);

/*
static int card[256];
static int cardi = 0;
static Bool
my_XAllocColor( Display * disp, Colormap cm, XColor * xc, int line)
{
   Bool foo; return foo;
}

static void
my_XFreeColors( Display * disp, Colormap cm, long * ls, int count, long pal, int line)
{
}

#define XAllocColor(a,b,c) my_XAllocColor(a,b,c,__LINE__)
#define XFreeColors(a,b,c,d,e) my_XFreeColors(a,b,c,d,e,__LINE__)
*/

static Bool
alloc_color( XColor * c) 
{
   Bool foo; return foo;
}

/*
     Fills Brush structure. If dithering is needed,
  brush.secondary and brush.balance are set. Tries to
  get new colors via XAllocColor, assigns new color cells
  to self if successfull.
     If no brush structure is given, no dithering is
  preformed. 
     Returns closest matching color, always the same as
  brush-> primary.
 */
unsigned long
prima_allocate_color( Handle self, Color color, Brush * brush)
{
   DEFXX;
   Brush b;
   int a[3], hint;

   if ( !brush) brush = &b;
   brush-> balance = 0;
   brush-> color = color = prima_map_color( color, &hint);

   if ( hint) 
      return ( brush-> primary = (( hint == COLORHINT_BLACK) ? LOGCOLOR_BLACK : LOGCOLOR_WHITE));
   
   a[0] = COLOR_R(color);
   a[1] = COLOR_G(color);
   a[2] = COLOR_B(color);

   if ( guts. grayScale) {
      a[0] = a[1] = a[2] = ( a[0] + a[1] + a[2]) / 3;
      color = a[0] * ( 65536 + 256 + 1);
   }
   Pdebug("color: %s asked for %06x\n", self?PWidget(self)->name:"null", color);
   if (self && XT_IS_BITMAP(XX)) {
      Byte balance = ( a[0] + a[1] + a[2] + 6) / (3 * 4);
      if ( balance < 64) {
         brush-> primary   = 0;
         brush-> secondary = 1;
         brush-> balance   = balance;
      } else
         brush-> primary = 1;
   } else {
      if ( guts. palSize > 0) {
         int ab2;
         Bool dyna = guts. dynamicColors && self && X(self)-> type. widget && ( self != application);
         brush-> primary = prima_color_find( self, color, -1, &ab2, RANK_FREE);
         
         if ( dyna && ab2 > 12) {
            XColor xc;
            xc. red   = COLOR_R16(color);
            xc. green = COLOR_G16(color);
            xc. blue  = COLOR_B16(color);
            xc. flags = DoGreen | DoBlue | DoRed;
            prima_color_sync();
            if ( alloc_color( &xc)) {
               prima_color_new( &xc);
               Pdebug("color: %s alloc %d ( wanted %06x). got %02x %02x %02x\n", PWidget(self)-> name, xc.pixel, color, xc.red>>8,xc.green>>8,xc.blue>>8);
               prima_color_add_ref( self, xc. pixel, RANK_NORMAL);
               return brush-> primary = xc. pixel;
            }
         }

         if ( guts. useDithering && (brush != &b) && (ab2 > 12)) {
            if ( guts. grayScale && guts. systemColorMapSize > guts. palSize / 2) {
               int clr = ( COLOR_R(color) + COLOR_G(color) + 
                     COLOR_B(color)) / 3;
               int grd  = 256 / ( guts. systemColorMapSize - 1);
               int left = clr / grd;
               brush-> balance = ( clr - left * grd) * 64 / grd;
               brush-> primary = guts. systemColorMap[ left];
               brush-> secondary = guts. systemColorMap[ left + 1];
            } else {
               int i;
               Bool cubic = (XX-> type.dbm && guts. dynamicColors) ||
                            ( guts. colorCubeRib > 4);
DITHER:               
               if ( cubic) {
/* fast search of dithering colors - based on color cube.
   used either on restricted drawables ( as dbm) or when
   have enough colors - small cubes give noisy picture
                          
     .  .  .  *R"G"   assume here that blue component does not require dithering
 R |                  R'G' and R"G" are 2 colors blended with proprotion to make
   | '''* A           color A. R'G' is a closest cubic color. If A(G)/A(R) < y,
   |    |             R"G" is G-point, if A(G)/A(R) > 1 + y, it's R-point, otherwise
   *---------- G      it's RG-point. (y=sqrt(2)-1=0.41; y=0.41x and y=1.41x are
R'G' , B=0            maximal error lines). balance is computed as diff between
                      R'G' and R"G"
 */              
                  int base[3], l[3], z[3], r[3], cnt = 0, sum = 0;
                  int grd = 256 / ( guts. colorCubeRib - 1);
                  for ( i = 0; i < 3; i++) {
                     base[i] = a[i] / grd;
                     r[i] = l[i] = ( a[i] >= base[i] + grd / 2) ? 1 : 0;
                     z[i] = l[i] ? (base[i] + 1) * grd - a[i]: a[i] - base[i] * grd;
                  }
                  if ( z[1] > 1) {
                     int ratio1 = 100 * z[0] / z[1];
                     int ratio2 = 100 * z[2] / z[1];
                     if ( ratio1 > 59)  r[0] = r[0] ? 0 : 1;
                     if ( ratio2 > 59)  r[2] = r[2] ? 0 : 1;
                     if ( ratio1 < 141 && ratio2 < 141) r[1] = r[1] ? 0 : 1;
                  }  else if ( z[2] > 1) {
                     int ratio = 100 * z[0] / z[2];
                     if ( ratio > 59) r[0] = r[0] ? 0 : 1;
                     if ( ratio < 141) r[2] = r[2] ? 0 : 1;
                  } else if ( z[0] > 1) {
                     r[0] = r[0] ? 0 : 1;
                  }
                  for ( i = 0; i < 3; i++) 
                     if ( r[i] != l[i]) {
                        sum += z[i];
                        cnt++;
                     }
                  brush-> primary = guts. systemColorMap[ 
                      l[2] + base[2] + 
                    ( l[1] + base[1]) * guts.colorCubeRib + 
                    ( l[0] + base[0]) * guts.colorCubeRib * guts.colorCubeRib];
                  brush-> secondary = guts. systemColorMap[ 
                      r[2] + base[2] + 
                    ( r[1] + base[1]) * guts.colorCubeRib + 
                    ( r[0] + base[0]) * guts.colorCubeRib * guts.colorCubeRib];
                  brush-> balance = cnt ? (sum / cnt) * 64 / grd : 0;
               } else {
/*  slow search for dithering counterpart color; takes long time
    but gives closest possible colors. 

     A*          A - color to be expressed by B and D
     /|  .       B - closest color
    / |    .     D - candidate color
   /  |      .   C - closest color that can be expressed using B and D
  *---*-------*  The objective is to find such D whose AC is minimal and
  B   C       D  CD>BD. ( CD = (AD*AD-AB*AB+BD*BD)/2BD, AC=sqrt(AD*AD-CD*CD))
*/   
                  int b[3], d[3], i;
                  int ab2, bd2, ac2, ad2;
                  float cd, bd, BMcd=0, BMbd=0;
                  int maxDiff = 16777216, bestMatch = -1;
                  int mincd = maxDiff;
                  b[0] = guts. palette[brush-> primary].r;
                  b[1] = guts. palette[brush-> primary].g;
                  b[2] = guts. palette[brush-> primary].b;
                  Pdebug("color:want %06x, closest is %06x\n", color, guts.palette[brush-> primary].composite);
                  ab2 = (a[0]-b[0])*(a[0]-b[0]) +
                        (a[1]-b[1])*(a[1]-b[1]) +
                        (a[2]-b[2])*(a[2]-b[2]);
                  for ( i = 0; i < guts.palSize; i++) {
                     if ( guts.palette[i].rank == RANK_FREE) continue;
                     d[0] = guts. palette[i].r;
                     d[1] = guts. palette[i].g;
                     d[2] = guts. palette[i].b;
                     Pdebug("color:tasting %06x\n", guts.palette[i].composite);
                     bd2 = (d[0]-b[0])*(d[0]-b[0]) +
                           (d[1]-b[1])*(d[1]-b[1]) +
                           (d[2]-b[2])*(d[2]-b[2]);
                     bd  = sqrt( bd2);
                     if ( bd == 0) continue;
                     ad2 = (d[0]-a[0])*(d[0]-a[0]) +
                           (d[1]-a[1])*(d[1]-a[1]) +
                           (d[2]-a[2])*(d[2]-a[2]);
                     cd  = ( ad2 - ab2 + bd2) / (2 * bd);
                     Pdebug("color:bd:%g,bd2:%d, ad2:%d, cd:%g\n", bd, bd2, ad2, cd);
                     if ( cd < bd) {
                        ac2 = ad2 - cd * cd;
                        Pdebug("color:ac2:%d\n", ac2);
                        if ( ac2 < maxDiff || (( ac2 < maxDiff + 12) && (cd < mincd))) {
                           maxDiff = ac2;
                           bestMatch = i;
                           BMcd = cd;
                           BMbd = bd;
                           mincd = cd;
                           if ( mincd < 42) goto ENOUGH;
                        }
                     }
                  }
ENOUGH:;                  
                  if ( !guts. grayScale && maxDiff > (64/(guts.colorCubeRib-1))) {
                     cubic = true;
                     goto DITHER;
                  } 
                  brush-> secondary = bestMatch;
                  brush-> balance   = 63 - BMcd * 64 / BMbd;
               }
            }
         }
         
         if ( dyna) {
            if ( wlpal_get( self, brush-> primary) == RANK_FREE) 
               prima_color_add_ref( self, brush-> primary, RANK_NORMAL);
            if (( brush-> balance > 0) &&
               ( wlpal_get( self, brush->secondary) == RANK_FREE)) 
               prima_color_add_ref( self, brush-> secondary, RANK_NORMAL);
         }
      } else  
         brush-> primary = 
            (((a[0] << guts. red_range  ) >> 8) << guts.   red_shift) |
            (((a[1] << guts. green_range) >> 8) << guts. green_shift) |
            (((a[2] << guts. blue_range ) >> 8) << guts.  blue_shift);
   }
   return brush-> primary;
}


static Bool
alloc_main_color_range( XColor * xc, int count, int maxDiff)
{
   Bool foo; return foo;
}

static Bool
create_std_palettes( XColor * xc, int count)
{
   Bool foo; return foo;
}

static void
fill_cubic( XColor * xc, int d)
{
}

static char * do_visual = nil;
static PList color_options = nil;

static void
set_color_class( int class, char * option, char * value)
{
}

static void
apply_color_class( int c_class, Color value) 
{
}

Bool
prima_init_color_subsystem(char * error_buf)
{
   Bool foo; return foo;
}

Bool
prima_color_subsystem_set_option( char * option, char * value)
{
   Bool foo; return foo;
}

typedef struct 
{
   int count;
   unsigned long free[256];
} FreeColorsStruct;

void
prima_done_color_subsystem( void)
{
}

/*
   Finds closest possible color in system palette.
   Colors can be selectively filtered using maxRank
   parameter - if it is greater that RANK_FREE, the colors
   with rank lower that maxRank are not matched. Ranking can
   make sense when self != nil and self != application, and
   of course when color cell manipulation is possible. In other
   words, local palette is never used if maxRank > RANK_FREE.
   maxDiff tells the maximal difference for a color. If
   no color is found that is closer than maxDiff, -1 is returned
   and pointer to actual diff is returned.
   */
int
prima_color_find( Handle self, long color, int maxDiff, int * diff, int maxRank)
{
   int foo; return foo;
}

static Bool
prima_color_new( XColor * xc)
{
   Bool foo; return foo;
}

/*
   Adds reference to widget that is responsible
   for a color cell with given rank. Main palette
   rank can be risen in response, but not lowered -
   that is accomplished by prima_color_sync. 
   */
Bool
prima_color_add_ref( Handle self, int index, int rank)
{
   Bool foo; return foo;
}

/* Frees stale color references */ 
int
prima_color_sync( void)
{
   int foo; return foo;
}

/* updates contents of DefaultColormap.  */
/* NB - never to be called with 'fast' set to true. */

Bool
prima_palette_replace( Handle self, Bool fast)
{
   Bool foo; return foo;
}

Bool
prima_palette_alloc( Handle self)
{
   Bool foo; return foo;
}

void
prima_palette_free( Handle self, Bool priority)
{
}

int
prima_lpal_get( Byte * palette, int index)
{
   int foo; return foo;
}

void 
prima_lpal_set( Byte * palette, int index, int rank )
{
}
          

static Bool kill_hatches( Pixmap pixmap, int keyLen, void * key, void * dummy)
{
   Bool foo; return foo;
}

Pixmap 
prima_get_hatch( FillPattern * fp)
{
   int i;
   Pixmap p;
   FillPattern fprev;
   if ( memcmp( fp, fillPatterns[fpSolid], sizeof( FillPattern)) == 0)
      return nilHandle;
   if (( p = ( Pixmap) hash_fetch( hatches, fp, sizeof( FillPattern))))
      return p;
   for ( i = 0; i < sizeof( FillPattern); i++)
      fprev[i] = (*fp)[ sizeof(FillPattern) - i - 1];
   if (( p = XCreateBitmapFromData( DISP, guts. root, (char*)fprev, 8, 8)) == None) {
      hash_first_that( hatches, (void*)kill_hatches, nil, nil, nil);
      hash_destroy( hatches, false);
      hatches = hash_create();
      if (( p = XCreateBitmapFromData( DISP, guts. root, (char*)fprev, 8, 8)) == None) 
         return nilHandle;
   }
   hash_store( hatches, fp, sizeof( FillPattern), ( void*) p);
   return p;
}
