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

#include "apricot.h"
#include "Application.h"
#include "Image.h"
#include "Clipboard.h"
#include <Clipboard.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CComponent->
#define my  ((( PClipboard) self)-> self)
#define var (( PClipboard) self)

#define cefInit     0
#define cefDone     1
#define cefStore    2
#define cefFetch    3

struct _ClipboardFormatReg;
typedef SV* ClipboardExchangeFunc( Handle self, struct _ClipboardFormatReg * instance, int function, SV * data);
typedef ClipboardExchangeFunc *PClipboardExchangeFunc;

typedef struct _ClipboardFormatReg
{
   char                          *id;
   Handle                         sysId;
   ClipboardExchangeFunc         *server;
   void                          *data;
   Bool                           written;
} ClipboardFormatReg, *PClipboardFormatReg;

static SV * text_server  ( Handle self, PClipboardFormatReg, int, SV *);
static SV * utf8_server  ( Handle self, PClipboardFormatReg, int, SV *);
static SV * image_server ( Handle self, PClipboardFormatReg, int, SV *);
static SV * binary_server( Handle self, PClipboardFormatReg, int, SV *);

static int clipboards = 0;
static int formatCount = 0;
static Bool protect_formats = false;
static PClipboardFormatReg formats = nil;

void *
Clipboard_register_format_proc( Handle self, char * format, void * serverProc);

void
Clipboard_init( Handle self, HV * profile)
{
}

void
Clipboard_done( Handle self)
{
}

Bool
Clipboard_validate_owner( Handle self, Handle * owner, HV * profile)
{
   return false;
}

typedef Bool ActionProc ( Handle self, PClipboardFormatReg item, void * params);
typedef ActionProc *PActionProc;

static PClipboardFormatReg
first_that( Handle self, void * actionProc, void * params)
{
   return nil;
}

static Bool
find_format( Handle self, PClipboardFormatReg item, char *format)
{
   return false;
}

static Bool
reset_written( Handle self, PClipboardFormatReg item, char *format)
{
   return false;
}

void *
Clipboard_register_format_proc( Handle self, char * format, void * serverProc)
{
   return nil;
}

void
Clipboard_deregister_format( Handle self, char * format)
{
}

Bool
Clipboard_open( Handle self)
{
   return false;
}

void
Clipboard_close( Handle self)
{
}

Bool
Clipboard_format_exists( Handle self, char * format)
{
   return false;
}

SV *
Clipboard_fetch( Handle self, char * format)
{
   return nilSV;
}

void
Clipboard_store( Handle self, char * format, SV * data)
{
}

void
Clipboard_clear( Handle self)
{
}

SV *
Clipboard_get_handle( Handle self)
{
   return nilSV;
}


Bool
Clipboard_register_format( Handle self, char * format)
{
   return false;
}


XS( Clipboard_get_formats_FROMPERL)
{
   dXSARGS;
   Handle self;
   int i;
   PClipboardFormatReg list;

   if ( items != 1)
      croak ("Invalid usage of Clipboard.get_formats");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Clipboard.get_formats");
   my-> open( self);
   list = formats;
   for ( i = 0; i < formatCount; i++) {
      if ( !apc_clipboard_has_format( self, list[ i]. sysId)) continue;
      XPUSHs( sv_2mortal( newSVpv( list[ i]. id, 0)));
   }
   my-> close( self);
   PUTBACK;
}

XS( Clipboard_get_registered_formats_FROMPERL)
{
   dXSARGS;
   Handle self;
   int i;
   PClipboardFormatReg list;

   if ( items < 1)
      croak ("Invalid usage of Clipboard.get_registered_formats");
   SP -= items;
   self = gimme_the_mate( ST( 0));
   if ( self == nilHandle)
      croak( "Illegal object reference passed to Clipboard.get_registered_formats");
   list = formats;
   EXTEND( sp, formatCount);
   for ( i = 0; i < formatCount; i++)
      PUSHs( sv_2mortal( newSVpv( list[ i]. id, 0)));
   PUTBACK;
}

XS( Clipboard_get_standard_clipboards_FROMPERL)
{
   dXSARGS;
   int i;
   PList l;

   (void)ax; SP -= items;
   l = apc_get_standard_clipboards();
   if ( l && l-> count > 0) {
      EXTEND( sp, l-> count);
      for ( i = 0; i < l-> count; i++) {
         char *cc = (char *)list_at( l, i);
         PUSHs( sv_2mortal( newSVpv(cc, 0)));
      }
   }
   if (l) {
      list_delete_all( l, true);
      plist_destroy( l);
   }
   PUTBACK;
}

void Clipboard_get_formats                       ( Handle self) {}
void Clipboard_get_formats_REDEFINED             ( Handle self) {}
void Clipboard_get_registered_formats            ( Handle self) {}
void Clipboard_get_registered_formats_REDEFINED  ( Handle self) {}
void Clipboard_get_standard_clipboards               ( Handle self) {}
void Clipboard_get_standard_clipboards_REDEFINED     ( Handle self) {}

static SV *
text_server( Handle self, PClipboardFormatReg instance, int function, SV * data)
{
   return nilSV;
}

static SV *
utf8_server( Handle self, PClipboardFormatReg instance, int function, SV * data)
{
   return nilSV;
}

static SV *
image_server( Handle self, PClipboardFormatReg instance, int function, SV * data)
{
   return nilSV;
}

static SV *
binary_server( Handle self, PClipboardFormatReg instance, int function, SV * data)
{
   return nilSV;
}

#ifdef __cplusplus
}
#endif
