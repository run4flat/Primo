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
   Color foo; return foo;
}

Color
apc_widget_map_color( Handle self, Color color)
{
   Color foo; return foo;
}


/*


#define XAllocColor(a,b,c) my_XAllocColor(a,b,c,__LINE__)
#define XFreeColors(a,b,c,d,e) my_XFreeColors(a,b,c,d,e,__LINE__)
*/


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
   unsigned long foo; return foo;
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
          


Pixmap 
prima_get_hatch( FillPattern * fp)
{
   return nil;
}
