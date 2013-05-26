#include "unix/guts.h"

#ifdef WITH_GTK2
#undef dirty
#include <gtk/gtk.h>

Bool
prima_gtk_init(void)
{
   Bool foo; return foo;
}

Bool
prima_gtk_done(void)
{
   Bool foo; return foo;
}

char *
prima_gtk_openfile( char * params)
{
   char * foo; return foo;
}

#endif
