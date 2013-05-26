#include "unix/guts.h"
#include "Application.h"
#include "Clipboard.h"
#include "Icon.h"

Bool
prima_init_clipboard_subsystem(char * error_buf)
{
   Bool foo; return foo;
}

PList
apc_get_standard_clipboards( void)
{
   return nil;
}

Bool
apc_clipboard_create( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_destroy( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_open( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_close( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_clear( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_has_format( Handle self, Handle id)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_get_data( Handle self, Handle id, PClipboardDataRec c)
{
   Bool foo; return foo;
}

Bool
apc_clipboard_set_data( Handle self, Handle id, PClipboardDataRec c)
{
   Bool foo; return foo;
}


Handle
apc_clipboard_register_format( Handle self, const char* format)
{
   return nilHandle;
}

Bool
apc_clipboard_deregister_format( Handle self, Handle id)
{
   Bool foo; return foo;
}

ApiHandle
apc_clipboard_get_handle( Handle self)
{
   return nilHandle;
}


void
prima_handle_selection_event( XEvent *ev, XWindow win, Handle self)
{
}

