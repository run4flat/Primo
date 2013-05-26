#include "unix/guts.h"
#include "AbstractMenu.h"
#include "Application.h"
#include "Window.h"
#define XK_MISCELLANY
#define XK_LATIN1
#define XK_XKB_KEYS
#include <X11/keysymdef.h>


void
prima_send_create_event( XWindow win)
{
}

Handle
prima_xw2h( XWindow win)
{
   return nilHandle;
}

extern Bool appDead;

Bool
prima_no_input( PDrawableSysData XX, Bool ignore_horizon, Bool beep)
{
   Bool foo; return foo;
}

void
prima_handle_event( XEvent *ev, XEvent *next_event)
{
}

void
prima_wm_sync( Handle self, int eventType)
{
}
