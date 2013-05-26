#include "unix/guts.h"
#include "Drawable.h"
#include "Window.h"

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

int
prima_color_find( Handle self, long color, int maxDiff, int * diff, int maxRank)
{
   int foo; return foo;
}

Bool
prima_color_add_ref( Handle self, int index, int rank)
{
   Bool foo; return foo;
}

int
prima_color_sync( void)
{
   int foo; return foo;
}

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
