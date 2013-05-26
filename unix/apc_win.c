#include "unix/guts.h"
#include "Menu.h"
#include "Icon.h"
#include "Window.h"
#include "Application.h"

unsigned char * 
prima_get_window_property( XWindow window, Atom property, Atom req_type, Atom * actual_type,
                           int * actual_format, unsigned long * nitems)
{
   unsigned char * foo; return foo;
}

Bool
prima_wm_net_state_read_maximization( XWindow window, Atom property)
{
   Bool foo; return foo;
}

Bool
apc_window_create( Handle self, Handle owner, Bool sync_paint, int border_icons,
		   int border_style, Bool task_list, int window_state, 
		   int on_top, Bool use_origin, Bool use_size)
{
   Bool foo; return foo;
}

Bool
apc_window_activate( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_is_active( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_close( Handle self)
{
   Bool foo; return foo;
}

Handle
apc_window_get_active( void)
{
   return nilHandle;
}

int
apc_window_get_border_icons( Handle self)
{
   int foo; return foo;
}

int
apc_window_get_border_style( Handle self)
{
   int foo; return foo;
}

ApiHandle
apc_window_get_client_handle( Handle self)
{
   return nilHandle;
}

Point
apc_window_get_client_pos( Handle self)
{
   Point foo; return foo;
}

Point
apc_window_get_client_size( Handle self)
{
   Point foo; return foo;
}

Bool
apc_window_get_icon( Handle self, Handle icon)
{
   Bool foo; return foo;
}

int
apc_window_get_window_state( Handle self)
{
   int foo; return foo;
}

Bool
apc_window_get_task_listed( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_set_caption( Handle self, const char *caption, Bool utf8)
{
   Bool foo; return foo;
}

XWindow
prima_find_frame_window( XWindow w)
{
   XWindow foo; return foo;
}

Bool
prima_get_frame_info( Handle self, PRect r)
{
   Bool foo; return foo;
}

void
apc_SetWMNormalHints( Handle self, XSizeHints * hints)
{
}


Bool
apc_window_set_client_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_window_set_client_rect( Handle self, int x, int y, int width, int height)
{
   Bool foo; return foo;
}

Bool
apc_window_set_client_size( Handle self, int width, int height)
{
   Bool foo; return foo;
}

Bool
prima_window_reset_menu( Handle self, int newMenuHeight)
{
   Bool foo; return foo;
}

Bool
apc_window_set_visible( Handle self, Bool show)
{
   Bool foo; return foo;
}

Bool
apc_window_set_icon( Handle self, Handle icon)
{
   Bool foo; return foo;
}

Bool
apc_window_set_window_state( Handle self, int state)
{
   Bool foo; return foo;
}

Bool
apc_window_execute( Handle self, Handle insert_before)
{
   Bool foo; return foo;
}

Bool
apc_window_execute_shared( Handle self, Handle insert_before)
{
   Bool foo; return foo;
}

Bool
apc_window_end_modal( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_window_get_on_top( Handle self)
{
   Bool foo; return foo;
}
