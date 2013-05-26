#include "unix/guts.h"
#include <locale.h>

Bool
prima_init_font_subsystem( char * error_buf)
{
   Bool foo; return foo;
}
   
Bool
prima_font_subsystem_set_option( char * option, char * value)
{
   Bool foo; return foo;
}

void
prima_font_pp2font( char * ppFontNameSize, PFont font)
{
}

void
prima_free_rotated_entry( PCachedFont f)
{
}


void
prima_cleanup_font_subsystem( void)
{
}

PFont
apc_font_default( PFont f)
{
   return nil;
}

int
apc_font_load( const char* filename)
{
   int foo; return foo;
}


void
prima_build_font_key( PFontKey key, PFont f, Bool bySize)
{
}

PCachedFont
prima_find_known_font( PFont font, Bool refill, Bool bySize)
{
   return nil;
}


void
prima_init_try_height( HeightGuessStack * p, int target, int firstMove )
{
}

int
prima_try_height( HeightGuessStack * p, int height)
{
   int foo; return foo;
}

Bool
prima_core_font_pick( Handle self, PFont source, PFont dest)
{
   Bool foo; return foo;
}

Bool
prima_core_font_encoding( char * encoding)
{
   Bool foo; return foo;
}

Bool
apc_font_pick( Handle self, PFont source, PFont dest)
{
   Bool foo; return foo;
}



PFont
apc_fonts( Handle self, const char *facename, const char * encoding, int *retCount)
{
   return nil;
}

PHash
apc_font_encodings( Handle self )
{
   return nil;
}

Bool
apc_gp_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
apc_menu_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
prima_update_rotated_fonts( PCachedFont f, const char * text, int len, Bool wide, double direction, PRotatedFont * result,
   Bool * ok_to_not_rotate)
{
   Bool foo; return foo;
}

XCharStruct * 
prima_char_struct( XFontStruct * xs, void * c, Bool wide) 
{
   XCharStruct * foo; return foo;
}
