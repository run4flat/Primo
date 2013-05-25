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
}

void
prima_update_cursor( Handle self)
{
}

void
prima_cursor_tick( void)
{
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
   Point foo; return foo;
}

Point
apc_cursor_get_size( Handle self)
{
   Point foo; return foo;
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
}

void
prima_msgdlg_event( XEvent * ev, struct MsgDlg * md)
{
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
}

void
prima_rect_intersect( XRectangle *t, const XRectangle *s)
{
}


void
prima_utf8_to_wchar( const char * utf8, XChar2b * u16, int src_len_bytes, int target_len_xchars )
{
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
}

void 
prima_char2wchar( XChar2b * dest, char * src, int lim)
{
}

char *
apc_last_error( void )
{
   return NULL;
}
