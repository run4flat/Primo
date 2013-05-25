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
/*  System dependent miscellaneous routines (unix, x11)    */
/*                                                         */
/***********************************************************/

#include <apricot.h>
#include <sys/stat.h>
#include "unix/guts.h"
#include "Application.h"
#include "File.h"
#include "Icon.h"
#define XK_MISCELLANY
#include <X11/keysymdef.h>

/* Miscellaneous system-dependent functions */

#define X_COLOR_TO_RGB(xc)     (ARGB(((xc).red>>8),((xc).green>>8),((xc).blue>>8)))
#define RANGE(a)        { if ((a) < -16383) (a) = -16383; else if ((a) > 16383) a = 16383; }
#define RANGE2(a,b)     RANGE(a) RANGE(b)

Bool
log_write( const char *format, ...)
{
   Bool foo; return foo;
}

static XrmQuark
get_class_quark( const char *name)
{
   XrmQuark quark;
   char *s, *t;

   t = s = prima_normalize_resource_string( duplicate_string( name), true);
   if ( t && *t == 'P' && strncmp( t, "Prima__", 7) == 0)
      s = t + 7;
   if ( s && *s == 'A' && strcmp( s, "Application") == 0)
      strcpy( s, "Prima"); /* we have enough space */
   quark = XrmStringToQuark( s);
   free( t);
   return quark;
}

static XrmQuark
get_instance_quark( const char *name)
{
   XrmQuark quark;
   char *s;

   s = duplicate_string( name);
   quark = XrmStringToQuark( prima_normalize_resource_string( s, false));
   free( s);
   return quark;
}

static Bool
update_quarks_cache( Handle self)
{
   Bool foo; return foo;
}

int
unix_rm_get_int( Handle self, XrmQuark class_detail, XrmQuark name_detail, int default_value)
{
   int foo; return foo;
}

Bool
apc_fetch_resource( const char *className, const char *name,
                    const char *resClass, const char *res,
                    Handle owner, int resType,
                    void *result)
{
   Bool foo; return foo;
}

Color
apc_lookup_color( const char * colorName)
{
   char buf[ 256];
   char *b;
   int len;
   XColor clr; 

   if ( DISP && XParseColor( DISP, DefaultColormap( DISP, SCREEN), colorName, &clr))
      return X_COLOR_TO_RGB(clr);

#define xcmp( name, stlen, retval)  if (( len == stlen) && ( strcmp( name, buf) == 0)) return retval

   strncpy( buf, colorName, 256);
   len = strlen( buf);
   for ( b = buf; *b; b++) *b = tolower(*b);

   switch( buf[0]) {
   case 'a':
       xcmp( "aqua", 4, 0x00FFFF);
       xcmp( "azure", 5, ARGB(240,255,255));
       break;
   case 'b':
       xcmp( "black", 5, 0x000000);
       xcmp( "blanchedalmond", 14, ARGB( 255,235,205));
       xcmp( "blue", 4, 0x000080);
       xcmp( "brown", 5, 0x808000);
       xcmp( "beige", 5, ARGB(245,245,220));
       break;
   case 'c':
       xcmp( "cyan", 4, 0x008080);
       xcmp( "chocolate", 9, ARGB(210,105,30));
       break;
   case 'd':
       xcmp( "darkgray", 8, 0x404040);
       break;
   case 'e':
       break;
   case 'f':
       xcmp( "fuchsia", 7, 0xFF00FF);
       break;
   case 'g':
       xcmp( "green", 5, 0x008000);
       xcmp( "gray", 4, 0x808080);
       xcmp( "gray80", 6, ARGB(204,204,204));
       xcmp( "gold", 4, ARGB(255,215,0));
       break;
   case 'h':
       xcmp( "hotpink", 7, ARGB(255,105,180));
       break;
   case 'i':
       xcmp( "ivory", 5, ARGB(255,255,240));
       break;
   case 'j':
       break;
   case 'k':
       xcmp( "khaki", 5, ARGB(240,230,140));
       break;
   case 'l':
       xcmp( "lime", 4, 0x00FF00);
       xcmp( "lightgray", 9, 0xC0C0C0);
       xcmp( "lightblue", 9, 0x0000FF);
       xcmp( "lightgreen", 10, 0x00FF00);
       xcmp( "lightcyan", 9, 0x00FFFF);
       xcmp( "lightmagenta", 12, 0xFF00FF);
       xcmp( "lightred", 8, 0xFF0000);
       xcmp( "lemon", 5, ARGB(255,250,205));
       break;
   case 'm':
       xcmp( "maroon", 6, 0x800000);
       xcmp( "magenta", 7, 0x800080);
       break;
   case 'n':
       xcmp( "navy", 4, 0x000080);
       break;
   case 'o':
       xcmp( "olive", 5, 0x808000);
       xcmp( "orange", 6, ARGB(255,165,0));
       break;
   case 'p':
       xcmp( "purple", 6, 0x800080);
       xcmp( "peach", 5, ARGB(255,218,185));
       xcmp( "peru", 4, ARGB(205,133,63));
       xcmp( "pink", 4, ARGB(255,192,203));
       xcmp( "plum", 4, ARGB(221,160,221));
       break;
   case 'q':
       break;
   case 'r':
       xcmp( "red", 3, 0x800000);
       xcmp( "royalblue", 9, ARGB(65,105,225));
       break;
   case 's':
       xcmp( "silver", 6, 0xC0C0C0);
       xcmp( "sienna", 6, ARGB(160,82,45));
       break;
   case 't':
       xcmp( "teal", 4, 0x008080);
       xcmp( "turquoise", 9, ARGB(64,224,208));
       xcmp( "tan", 3, ARGB(210,180,140));
       xcmp( "tomato", 6, ARGB(255,99,71));
       break;
   case 'u':
       break;
   case 'w':
       xcmp( "white", 5, 0xFFFFFF);
       xcmp( "wheat", 5, ARGB(245,222,179));
       break;
   case 'v':
       xcmp( "violet", 6, ARGB(238,130,238));
       break;
   case 'x':
       break;
   case 'y':
       xcmp( "yellow", 6, 0xFFFF00);
       break;
   case 'z':
       break;
   }

#undef xcmp

   return clInvalid;
}

/* Component-related functions */

Bool
apc_component_create( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_component_destroy( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_component_fullname_changed_notify( Handle self)
{
   Bool foo; return foo;
}

/* Cursor support */

void
prima_no_cursor( Handle self)
{
   if ( self && guts.focused == self && X(self)
	&& !(XF_IN_PAINT(X(self)))
	&& X(self)-> flags. cursor_visible
	&& guts. cursor_save)
   {
      DEFXX;
      int x, y, w, h;

      h = XX-> cursor_size. y;
      y = XX-> size. y - (h + XX-> cursor_pos. y);
      x = XX-> cursor_pos. x;
      w = XX-> cursor_size. x;

      prima_get_gc( XX);
      XChangeGC( DISP, XX-> gc, VIRGIN_GC_MASK, &guts. cursor_gcv);
      XCHECKPOINT;
      XCopyArea( DISP, guts. cursor_save, XX-> udrawable, XX-> gc,
		 0, 0, w, h, x, y);
      XCHECKPOINT;
      prima_release_gc( XX);
      guts. cursor_shown = false;
   }
}

void
prima_update_cursor( Handle self)
{
   if (
   	guts.focused == self
	&& !(XF_IN_PAINT(X(self)))
   ) {
      DEFXX;
      int x, y, w, h;

      h = XX-> cursor_size. y;
      y = XX-> size. y - (h + XX-> cursor_pos. y);
      x = XX-> cursor_pos. x;
      w = XX-> cursor_size. x;

      if ( !guts. cursor_save || !guts. cursor_xor
	   || w > guts. cursor_pixmap_size. x
	   || h > guts. cursor_pixmap_size. y)
      {
	 if ( !guts. cursor_save) {
	    guts. cursor_gcv. background = 0;
	    guts. cursor_gcv. foreground = 0xffffffff;
	 }
	 if ( guts. cursor_save) {
	    XFreePixmap( DISP, guts. cursor_save);
	    guts. cursor_save = 0;
	 }
	 if ( guts. cursor_xor) {
	    XFreePixmap( DISP, guts. cursor_xor);
	    guts. cursor_xor = 0;
	 }
	 if ( guts. cursor_pixmap_size. x < w)
	    guts. cursor_pixmap_size. x = w;
	 if ( guts. cursor_pixmap_size. y < h)
	    guts. cursor_pixmap_size. y = h;
	 if ( guts. cursor_pixmap_size. x < 16)
	    guts. cursor_pixmap_size. x = 16;
	 if ( guts. cursor_pixmap_size. y < 64)
	    guts. cursor_pixmap_size. y = 64;
	 guts. cursor_save = XCreatePixmap( DISP, XX-> udrawable,
					    guts. cursor_pixmap_size. x,
					    guts. cursor_pixmap_size. y,
					    guts. depth);
	 guts. cursor_xor  = XCreatePixmap( DISP, XX-> udrawable,
					    guts. cursor_pixmap_size. x,
					    guts. cursor_pixmap_size. y,
					    guts. depth);
      }

      prima_get_gc( XX);
      XChangeGC( DISP, XX-> gc, VIRGIN_GC_MASK, &guts. cursor_gcv);
      XCHECKPOINT;
      XCopyArea( DISP, XX-> udrawable, guts. cursor_save, XX-> gc,
		 x, y, w, h, 0, 0);
      XCHECKPOINT;
      XCopyArea( DISP, guts. cursor_save, guts. cursor_xor, XX-> gc,
		 0, 0, w, h, 0, 0);
      XCHECKPOINT;
      XSetFunction( DISP, XX-> gc, GXxor);
      XCHECKPOINT;
      XFillRectangle( DISP, guts. cursor_xor, XX-> gc, 0, 0, w, h);
      XCHECKPOINT;
      prima_release_gc( XX);

      if ( XX-> flags. cursor_visible) {
	 guts. cursor_shown = false;
	 prima_cursor_tick();
      } else {
	 apc_timer_stop( CURSOR_TIMER);
      }
   }
}

void
prima_cursor_tick( void)
{
   if (
   	guts. focused && 
	X(guts. focused)-> flags. cursor_visible &&
	!(XF_IN_PAINT(X(guts. focused)))
   ) {
      PDrawableSysData selfxx = X(guts. focused);
      Pixmap pixmap;
      int x, y, w, h;

      if ( guts. cursor_shown) {
	 guts. cursor_shown = false;
	 apc_timer_set_timeout( CURSOR_TIMER, guts. invisible_timeout);
	 pixmap = guts. cursor_save;
      } else {
	 guts. cursor_shown = true;
	 apc_timer_set_timeout( CURSOR_TIMER, guts. visible_timeout);
	 pixmap = guts. cursor_xor;
      }

      h = XX-> cursor_size. y;
      y = XX-> size. y - (h + XX-> cursor_pos. y);
      x = XX-> cursor_pos. x;
      w = XX-> cursor_size. x;

      prima_get_gc( XX);
      XChangeGC( DISP, XX-> gc, VIRGIN_GC_MASK, &guts. cursor_gcv);
      XCHECKPOINT;
      XCopyArea( DISP, pixmap, XX-> udrawable, XX-> gc, 0, 0, w, h, x, y);
      XCHECKPOINT;
      prima_release_gc( XX);
      XFlush( DISP);
      XCHECKPOINT;
   } else {
      apc_timer_stop( CURSOR_TIMER);
      guts. cursor_shown = !guts. cursor_shown;
   }
}

Bool
apc_cursor_set_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_cursor_set_size( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_cursor_set_visible( Handle self, Bool visible)
{
   Bool foo; return foo;
}

Point
apc_cursor_get_pos( Handle self)
{
   return X(self)-> cursor_pos;
}

Point
apc_cursor_get_size( Handle self)
{
   return X(self)-> cursor_size;
}

Bool
apc_cursor_get_visible( Handle self)
{
   Bool foo; return foo;
}

/* File */

void
prima_rebuild_watchers( void)
{
   int i;
   PFile f;

   FD_ZERO( &guts.read_set);
   FD_ZERO( &guts.write_set);
   FD_ZERO( &guts.excpt_set);
   FD_SET( guts.connection, &guts.read_set);
   guts.max_fd = guts.connection;
   for ( i = 0; i < guts.files->count; i++) {
      f = (PFile)list_at( guts.files,i);
      if ( f-> eventMask & feRead) {
	 FD_SET( f->fd, &guts.read_set);
	 if ( f->fd > guts.max_fd)
	    guts.max_fd = f->fd;
      }
      if ( f-> eventMask & feWrite) {
	 FD_SET( f->fd, &guts.write_set);
	 if ( f->fd > guts.max_fd)
	    guts.max_fd = f->fd;
      }
      if ( f-> eventMask & feException) {
	 FD_SET( f->fd, &guts.excpt_set);
	 if ( f->fd > guts.max_fd)
	    guts.max_fd = f->fd;
      }
   }
}

Bool
apc_file_attach( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_file_detach( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_file_change_mask( Handle self)
{
   Bool foo; return foo;
}

int
apc_pointer_get_state( Handle self)
{
   int foo; return foo;
}

int
apc_kbd_get_state( Handle self)
{
   int foo; return foo;
}

/* Messages */

Bool
prima_simple_message( Handle self, int cmd, Bool is_post)
{
   Bool foo; return foo;
}

Bool
apc_message( Handle self, PEvent e, Bool is_post)
{
   Bool foo; return foo;
}

static void 
close_msgdlg( struct MsgDlg * md)
{
   md-> active  = false;
   md-> pressed = false;
   if ( md-> grab) 
      XUngrabPointer( DISP, CurrentTime);
   md-> grab    = false;
   XUnmapWindow( DISP, md-> w);
   XFlush( DISP);
   if ( md-> next == nil) {
      XSetInputFocus( DISP, md-> focus, md-> focus_revertTo, CurrentTime);
      XCHECKPOINT;
   }   
}   

void
prima_msgdlg_event( XEvent * ev, struct MsgDlg * md)
{
   XWindow w = ev-> xany. window;
   switch ( ev-> type) {
   case ConfigureNotify:
      md-> winSz. x = ev-> xconfigure. width;
      md-> winSz. y = ev-> xconfigure. height;
      break;   
   case Expose:
      {
         int i, y = md-> textPos. y;
         int d = md-> pressed ? 2 : 0;
         XSetForeground( DISP, md-> gc, md-> bg. primary); 
         if ( md-> bg. balance > 0) {
            Pixmap p = prima_get_hatch( &guts. ditherPatterns[ md-> bg. balance]);
            if ( p) {
               XSetStipple( DISP, md-> gc, p);
               XSetFillStyle( DISP, md-> gc, FillOpaqueStippled);
               XSetBackground( DISP, md-> gc, md-> bg. secondary);
            } 
         } 
         XFillRectangle( DISP, w, md-> gc, 0, 0, md-> winSz.x, md-> winSz.y);
         if ( md-> bg. balance > 0) 
            XSetFillStyle( DISP, md-> gc, FillSolid);
         XSetForeground( DISP, md-> gc, md-> fg); 
         for ( i = 0; i < md-> wrappedCount; i++) {
            if ( md-> wide)
               XDrawString16( DISP, w, md-> gc, 
                 ( md-> winSz.x - md-> widths[i]) / 2, y, 
                   ( XChar2b*) md-> wrapped[i], md-> lengths[i]);
            else
               XDrawString( DISP, w, md-> gc, 
                 ( md-> winSz.x - md-> widths[i]) / 2, y, 
                   md-> wrapped[i], md-> lengths[i]);
            y += md-> font-> height + md-> font-> externalLeading;
         }   
         XDrawRectangle( DISP, w, md-> gc, 
            md-> btnPos.x-1, md-> btnPos.y-1, md-> btnSz.x+2, md-> btnSz.y+2);
         XDrawString( DISP, w, md-> gc, 
            md-> btnPos.x + ( md-> btnSz.x - md-> OKwidth) / 2 + d,
            md-> btnPos.y + md-> font-> height + md-> font-> externalLeading +
              ( md-> btnSz.y - md-> font-> height - md-> font-> externalLeading) / 2 - 2 + d,
            "OK", 2);
         XSetForeground( DISP, md-> gc, 
            md-> pressed ? md-> d3d : md-> l3d); 
         XDrawLine( DISP, w, md-> gc,
            md-> btnPos.x, md-> btnPos.y + md-> btnSz.y - 1, 
            md-> btnPos.x, md-> btnPos. y);
         XDrawLine( DISP, w, md-> gc,
            md-> btnPos.x + 1, md-> btnPos. y,
            md-> btnPos.x + md-> btnSz.x - 1, md-> btnPos. y);
         XSetForeground( DISP, md-> gc, 
            md-> pressed ? md-> l3d : md-> d3d); 
         XDrawLine( DISP, w, md-> gc,
            md-> btnPos.x, md-> btnPos.y + md-> btnSz.y, 
            md-> btnPos.x + md-> btnSz.x, md-> btnPos.y + md-> btnSz.y);
         XDrawLine( DISP, w, md-> gc,
            md-> btnPos.x + md-> btnSz.x, md-> btnPos.y + md-> btnSz.y - 1,
            md-> btnPos.x + md-> btnSz.x, md-> btnPos.y + 1);
      }
      break;
   case ButtonPress:
      if ( !md-> grab && 
         ( ev-> xbutton. button == Button1) &&
         ( ev-> xbutton. x >= md-> btnPos. x ) &&
         ( ev-> xbutton. x < md-> btnPos. x + md-> btnSz.x) &&
         ( ev-> xbutton. y >= md-> btnPos. y ) &&
         ( ev-> xbutton. y < md-> btnPos. y + md-> btnSz.y)) {
         md-> pressed = true;
         md-> grab = true;
         XClearArea( DISP, w, md-> btnPos.x, md-> btnPos.y,
             md-> btnSz.x, md-> btnSz.y, true); 
         XGrabPointer( DISP, w, false, 
             ButtonReleaseMask | PointerMotionMask | ButtonMotionMask,
	     GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
      }   
      break;   
   case MotionNotify:
      if ( md-> grab) {
         Bool np = 
           (( ev-> xmotion. x >= md-> btnPos. x ) &&
            ( ev-> xmotion. x < md-> btnPos. x + md-> btnSz.x) &&
            ( ev-> xmotion. y >= md-> btnPos. y ) &&
            ( ev-> xmotion. y < md-> btnPos. y + md-> btnSz.y));
         if ( np != md-> pressed) {
            md-> pressed = np;
            XClearArea( DISP, w, md-> btnPos.x, md-> btnPos.y,
                md-> btnSz.x, md-> btnSz.y, true); 
         }
      }      
      break;
   case KeyPress:
      {
         char str_buf[256];
         KeySym keysym;
         int str_len = XLookupString( &ev-> xkey, str_buf, 256, &keysym, nil);
         if (
              ( keysym == XK_Return) ||
              ( keysym == XK_Escape) ||
              ( keysym == XK_KP_Enter) ||
              ( keysym == XK_KP_Space) ||
              (( str_len == 1) && ( str_buf[0] == ' '))
            ) 
            close_msgdlg( md);
      }   
      break;   
   case ButtonRelease:
      if ( md-> grab && 
         ( ev-> xbutton. button == Button1)) {
         md-> grab = false;
         XUngrabPointer( DISP, CurrentTime);
         if ( md-> pressed) close_msgdlg( md);
      }   
      break;
   case ClientMessage:
      if (( ev-> xclient. message_type == WM_PROTOCOLS) &&
         (( Atom) ev-> xclient. data. l[0] == WM_DELETE_WINDOW)) 
         close_msgdlg( md);
      break;   
   }
}   
     
extern char ** Drawable_do_text_wrap( Handle, TextWrapRec *);

Bool
apc_show_message( const char * message, Bool utf8)
{
   Bool foo; return foo;
}

/* system metrics */

Bool
apc_sys_get_insert_mode( void)
{
   Bool foo; return foo;
}

PFont
apc_sys_get_msg_font( PFont f)
{
   memcpy( f, &guts. default_msg_font, sizeof( Font));
   return f;
}

PFont
apc_sys_get_caption_font( PFont f)
{
   memcpy( f, &guts. default_caption_font, sizeof( Font));
   return f;
}

int
apc_sys_get_value( int v)  /* XXX one big XXX */
{
   int foo; return foo;
}

Bool
apc_sys_set_insert_mode( Bool insMode)
{
   Bool foo; return foo;
}

/* etc */

Bool
apc_beep( int style)
{
   Bool foo; return foo;
}

Bool
apc_beep_tone( int freq, int duration)
{
   Bool foo; return foo;
}

char *
apc_system_action( const char *s)
{
   int l = strlen( s);
   switch (*s) {
   case 'b':
      if ( l == 7 && strcmp( s, "browser") == 0)
         return duplicate_string("netscape");
      break;
   case 'c':
      if ( l == 19 && strcmp( s, "can.shape.extension") == 0 && guts.shape_extension)
         return duplicate_string( "yes");
      else if ( l == 26 && strcmp( s, "can.shared.image.extension") == 0 && guts.shared_image_extension)
         return duplicate_string( "yes");
      break;
   case 'D':
      if ( l == 7 && ( strcmp( s, "Display") == 0)) {
         char * c = malloc(19);
         if ( c) snprintf( c, 18, "0x%p", DISP);
         return c;
      }
      break;
   case 'g':
      if ( l > 15 && strncmp( "get.frame.info ", s, 15) == 0) {
         char *end;
         XWindow w = strtoul( s + 15, &end, 0);
         Handle self;
         Rect r;
         char buf[ 80];

         if (*end == '\0' &&
             ( self = prima_xw2h( w)) && 
             prima_get_frame_info( self, &r) &&
             snprintf( buf, sizeof(buf), "%d %d %d %d", r.left, r.bottom, r.right, r.top) < sizeof(buf))
            return duplicate_string( buf);
         return duplicate_string("");
      } else if ( strncmp( s, "gtk2.OpenFile.", 14) == 0) {
#ifdef WITH_GTK2
	 s += 14;
	 return prima_gtk_openfile(( char*) s);
#else
         return nil;
#endif
      }
      break;
   case 's':
      if ( strcmp( "synchronize", s) == 0) {
         XSynchronize( DISP, true);
         return nil;
      }   
      if ( strncmp( "setfont ", s, 8) == 0) {
          Handle self = nilHandle;
          char font[1024];
          XWindow win;
          int i = sscanf( s + 8, "%lu %s", &win, font);
          if ( i != 2 || !(self = prima_xw2h( win)))  {
             warn( "Bad parameters to sysaction setfont");
             return 0;
          }
          if ( !opt_InPaint) return 0;
          XSetFont( DISP, X(self)-> gc, XLoadFont( DISP, font));
          return nil;
      }
      break;
   case 't':
      if ( strncmp( "textout16 ", s, 10) == 0) {
          Handle self = nilHandle;
          unsigned char text[1024];
          XWindow win;
          int x, y, len;
          int i = sscanf( s + 10, "%lu %d %d %s", &win, &x, &y, text);
          if ( i != 4 || !(self = prima_xw2h( win)))  {
             warn( "Bad parameters to sysaction textout16");
             return 0;
          }
          if ( !opt_InPaint) return 0;
          len = strlen((char*) text);
          for ( i = 0; i < len; i++) if ( text[i]==255) text[i] = 0;
          XDrawString16( DISP, win, X(self)-> gc, x, y, ( XChar2b *) text, len / 2);
          return nil;
      }
      break;
   case 'u':
      if ( strcmp( s, "unix_guts") == 0) 
	 return (char*) &guts;
      break;
   case 'X':
      if ( strcmp( s, "XOpenDisplay") == 0) {
         char err_buf[512];
         if ( DISP)
             return duplicate_string( "X display already opened");
         window_subsystem_set_option( "yes-x11", NULL);
	 if ( !window_subsystem_init( err_buf))
             return duplicate_string( err_buf);
	 return NULL;
      }
      break;
   }
   warn("Unknown sysaction:%s", s);
   return nil;
}

Bool
apc_query_drives_map( const char* firstDrive, char *result, int len)
{
   Bool foo; return foo;
}

int
apc_query_drive_type( const char *drive)
{
   int foo; return foo;
}

char *
apc_get_user_name( void)
{
   char * c = getlogin();
   return c ? c : "";
}

Bool
apc_dl_export(char *path)
{
   Bool foo; return foo;
}

PList
apc_getdir( const char *dirname)
{
   DIR *dh;
   struct dirent *de;
   PList dirlist = nil;
   char *type;
   char path[ 2048];
   struct stat s;

   if (( dh = opendir( dirname)) && (dirlist = plist_create( 50, 50))) {
      while (( de = readdir( dh))) {
	 list_add( dirlist, (Handle)duplicate_string( de-> d_name));
#if defined(DT_REG) && defined(DT_DIR)
	 switch ( de-> d_type) {
	 case DT_FIFO:	type = "fifo";	break;
	 case DT_CHR:	type = "chr";	break;
	 case DT_DIR:	type = "dir";	break;
	 case DT_BLK:	type = "blk";	break;
	 case DT_REG:	type = "reg";	break;
	 case DT_LNK:	type = "lnk";	break;
	 case DT_SOCK:	type = "sock";	break;
#ifdef DT_WHT
	 case DT_WHT:	type = "wht";	break;
#endif
	 default:
#endif 
                        snprintf( path, 2047, "%s/%s", dirname, de-> d_name);
                        type = nil;
                        if ( stat( path, &s) == 0) {
                           switch ( s. st_mode & S_IFMT) {
                           case S_IFIFO:        type = "fifo";  break;
                           case S_IFCHR:        type = "chr";   break;
                           case S_IFDIR:        type = "dir";   break;
                           case S_IFBLK:        type = "blk";   break;
                           case S_IFREG:        type = "reg";   break;
                           case S_IFLNK:        type = "lnk";   break;
                           case S_IFSOCK:       type = "sock";  break;
#ifdef S_IFWHT
                           case S_IFWHT:        type = "wht";   break;
#endif
                           }
                        }
                        if ( !type)     type = "unknown";
#if defined(DT_REG) && defined(DT_DIR)
	 }
#endif
	 list_add( dirlist, (Handle)duplicate_string( type));
      }
      closedir( dh);
   }
   return dirlist;
}

void
prima_rect_union( XRectangle *t, const XRectangle *s)
{
   XRectangle r;

   if ( t-> x < s-> x) r. x = t-> x; else r. x = s-> x;
   if ( t-> y < s-> y) r. y = t-> y; else r. y = s-> y;
   if ( t-> x + t-> width > s-> x + s-> width)
      r. width = t-> x + t-> width - r. x;
   else
      r. width = s-> x + s-> width - r. x;
   if ( t-> y + t-> height > s-> y + s-> height)
      r. height = t-> y + t-> height - r. y;
   else
      r. height = s-> y + s-> height - r. y;
   *t = r;
}

void
prima_rect_intersect( XRectangle *t, const XRectangle *s)
{
   XRectangle r;
   int w, h;

   if ( t-> x > s-> x) r. x = t-> x; else r. x = s-> x;
   if ( t-> y > s-> y) r. y = t-> y; else r. y = s-> y;
   if ( t-> x + t-> width < s-> x + s-> width)
      w = t-> x + (int)t-> width - r. x;
   else
      w = s-> x + (int)s-> width - r. x;
   if ( t-> y + t-> height < s-> y + s-> height)
      h = t-> y + (int)t-> height - r. y;
   else
      h = s-> y + (int)s-> height - r. y;
   if ( w < 0 || h < 0) {
      r. x = 0; r. y = 0; r. width = 0; r. height = 0;
   } else {
      r. width = w; r. height = h;
   }
   *t = r;
}


void
prima_utf8_to_wchar( const char * utf8, XChar2b * u16, int src_len_bytes, int target_len_xchars )
{
   STRLEN charlen;
   while ( target_len_xchars--) {
      register UV u = (
#if PERL_PATCHLEVEL >= 16
         utf8_to_uvchr_buf(( U8*) utf8, ( U8*)(utf8 + src_len_bytes), &charlen)
#else
         utf8_to_uvchr(( U8*) utf8, &charlen)
#endif
      );
      if ( u < 0x10000) {
         u16-> byte1 = u >> 8;
         u16-> byte2 = u & 0xff;
      } else 
         u16-> byte1 = u16-> byte2 = 0xff;
      u16++;
      utf8 += charlen;
      src_len_bytes -= charlen;
      if ( src_len_bytes <= 0 || charlen == 0) break;
   }
}

XChar2b *
prima_alloc_utf8_to_wchar( const char * utf8, int length_chars)
{
   XChar2b * ret;
   if ( length_chars < 0) length_chars = prima_utf8_length( utf8) + 1;
   if ( !( ret = malloc( length_chars * sizeof( XChar2b)))) return nil;
   prima_utf8_to_wchar( utf8, ret, strlen(utf8), length_chars);
   return ret;
}

void 
prima_wchar2char( char * dest, XChar2b * src, int lim)
{
   if ( lim < 1) return;
   while ( lim-- && src-> byte1 && src-> byte2) *(dest++) = (src++)-> byte2;
   if ( lim < 0) dest--;
   *dest = 0;
}

void 
prima_char2wchar( XChar2b * dest, char * src, int lim)
{
   int l = strlen( src) + 1;
   if ( lim < 1) return;
   if ( lim > l) lim = l;
   src  += lim - 2;
   dest += lim - 1;
   dest-> byte1 = dest-> byte2 = 0;
   dest--;
   while ( lim--) {
      dest-> byte2 = *(src--);
      dest-> byte1 = 0;
      dest--;
   }
}

char *
apc_last_error( void )
{
   return NULL;
}
