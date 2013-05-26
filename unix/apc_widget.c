#include "unix/guts.h"
#include "Window.h"
#include "Application.h"

Bool
apc_widget_map_points( Handle self, Bool toScreen, int n, Point *p)
{
   Bool foo; return foo;
}

ApiHandle
apc_widget_get_parent_handle( Handle self)
{
   return nilHandle;
}

Handle
apc_widget_get_z_order( Handle self, int zOrderId)
{
   return nilHandle;
}

void
process_transparents( Handle self)
{
}


Bool
apc_widget_create( Handle self, Handle owner, Bool sync_paint,
		   Bool clip_owner, Bool transparent, ApiHandle parentHandle)
{
   Bool foo; return foo;
}

Bool
apc_widget_begin_paint( Handle self, Bool inside_on_paint)
{
   Bool foo; return foo;
}

Bool
apc_widget_begin_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_destroy( Handle self)
{
   Bool foo; return foo;
}

PFont
apc_widget_default_font( PFont f)
{
   return nil;
}

Bool
apc_widget_end_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_end_paint_info( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_get_clip_owner( Handle self)
{
   Bool foo; return foo;
}

Color
apc_widget_get_color( Handle self, int index)
{
   Color foo; return foo;
}

Bool
apc_widget_get_first_click( Handle self)
{
   Bool foo; return foo;
}

Handle
apc_widget_get_focused( void)
{
   return nilHandle;
}

ApiHandle
apc_widget_get_handle( Handle self)
{
   return nilHandle;
}

Rect
apc_widget_get_invalid_rect( Handle self)
{
   Rect foo; return foo;
}

Point
apc_widget_get_pos( Handle self)
{
   Point foo; return foo;
}

Bool
apc_widget_get_shape( Handle self, Handle mask)
{
   Bool foo; return foo;
}

Point
apc_widget_get_size( Handle self)
{
   Point foo; return foo;
}

Bool
apc_widget_get_sync_paint( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_get_transparent( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_captured( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_enabled( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_exposed( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_focused( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_responsive( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_showing( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_is_visible( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_invalidate_rect( Handle self, Rect *rect)
{
   Bool foo; return foo;
}


Bool
apc_widget_scroll( Handle self, int horiz, int vert,
		   Rect *confine, Rect *clip, Bool withChildren)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_capture( Handle self, Bool capture, Handle confineTo)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_color( Handle self, Color color, int i)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_enabled( Handle self, Bool enable)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_first_click( Handle self, Bool firstClick)
{
   Bool foo; return foo;
}


Bool
apc_widget_set_focused( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_font( Handle self, PFont font)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_palette( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_shape( Handle self, Handle mask)
{
   Bool foo; return foo;
}

void
prima_send_cmSize( Handle self, Point oldSize)
{
}

Bool
apc_widget_set_size( Handle self, int width, int height)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_rect( Handle self, int x, int y, int width, int height)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_size_bounds( Handle self, Point min, Point max)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_visible( Handle self, Bool show)
{
   Bool foo; return foo;
}

Bool
apc_widget_set_z_order( Handle self, Handle behind, Bool top)
{
   Bool foo; return foo;
}

Bool
apc_widget_update( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_widget_validate_rect( Handle self, Rect rect)
{
   Bool foo; return foo;
}

