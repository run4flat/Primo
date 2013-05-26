#include "unix/guts.h"
#include "Menu.h"
#include "Image.h"
#include "Window.h"
#include "Application.h"
#include <X11/keysymdef.h>

extern Cursor predefined_cursors[];

void
prima_handle_menu_event( XEvent *ev, XWindow win, Handle self)
{
}

int prima_handle_menu_shortcuts( Handle self, XEvent * ev, KeySym keysym) {
   int foo; return foo;
}

void prima_end_menu(void) {}

Bool apc_menu_create( Handle self, Handle owner) { Bool foo; return foo; }

Bool apc_menu_destroy( Handle self) { Bool foo; return foo; }

PFont apc_menu_default_font( PFont f) { return nil; }

Color apc_menu_get_color( Handle self, int index) { Color foo; return foo; }

void menu_touch( Handle self, PMenuItemReg who, Bool kill) {}

Bool
apc_menu_update( Handle self, PMenuItemReg oldBranch, PMenuItemReg newBranch)
{ Bool foo; return foo; }
 
Bool apc_menu_item_delete( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_accel( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_check( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_enabled( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_image( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_key( Handle self, PMenuItemReg m) { Bool foo; return foo; }

Bool apc_menu_item_set_text( Handle self, PMenuItemReg m) { Bool foo; return foo; }

ApiHandle apc_menu_get_handle( Handle self) { return nilHandle; }

Bool apc_popup_create( Handle self, Handle owner) { Bool foo; return foo; }

PFont apc_popup_default_font( PFont f) { return nil; }

Bool apc_popup( Handle self, int x, int y, Rect *anchor) { Bool foo; return foo; }

Bool apc_window_set_menu( Handle self, Handle menu) { Bool foo; return foo; }
