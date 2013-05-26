#include "apricot.h"
#include "unix/guts.h"
#include "Application.h"
#include "File.h"
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

UnixGuts guts, *pguts = &guts;

UnixGuts *
prima_unix_guts(void)
{
   return &guts;
}

int
prima_debug( const char *format, ...)
{
   int foo; return foo;
}


Bool
apc_application_begin_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_begin_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_create( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_close( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_destroy( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_end_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_end_paint_info( Handle self)
{
   Bool foo; return foo;
}

int
apc_application_get_gui_info( char * description, int len)
{
   int foo; return foo;
}

Handle
apc_application_get_widget_from_point( Handle self, Point p)
{
   return nilHandle;
}

Handle
apc_application_get_handle( Handle self, ApiHandle apiHandle)
{
   return nilHandle;
}


Rect
apc_application_get_indents( Handle self)
{
   Rect foo; return foo;
}

int
apc_application_get_os_info( char *system, int slen,
			     char *release, int rlen,
			     char *vendor, int vlen,
			     char *arch, int alen)
{
   int foo; return foo;
}

Point
apc_application_get_size( Handle self)
{
   Point foo; return foo;
}


Bool
apc_watch_filehandle( int no, void *sub, void *glob)
{
   Bool foo; return foo;
}

Bool
prima_one_loop_round( Bool wait, Bool careOfApplication)
{
   Bool foo; return foo;
}

Bool
apc_application_go( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_lock( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_unlock( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_application_sync(void)
{
   Bool foo; return foo;
}

Bool
apc_application_yield( void)
{
   Bool foo; return foo;
}
