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

#include "unix/guts.h"
#include "Application.h"
#include "Clipboard.h"
#include "Icon.h"

#define WIN PComponent(application)-> handle

#define CF_NAME(x)   (guts. clipboard_formats[(x)*3])
#define CF_TYPE(x)   (guts. clipboard_formats[(x)*3+1])
#define CF_FORMAT(x) (guts. clipboard_formats[(x)*3+2])
#define CF_ASSIGN(i,a,b,c) CF_NAME(i)=(a);CF_TYPE(i)=(b);CF_FORMAT(i)=((Atom)c)
#define CF_32        (sizeof(long)*8)        /* 32-bit properties are hacky */

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

static void
clipboard_free_data( void * data, int size, Handle id)
{
}

/*
   each clipboard type can be represented by a set of 
   X properties pairs, where each is X name and X type.
   get_typename() returns such pairs by the index.
 */
static Atom
get_typename( Handle id, int index, Atom * type)
{
   Atom foo; return foo;
}

static void
clipboard_kill_item( PClipboardDataItem item, Handle id)
{
}

/*
   Deletes a transfer record from pending xfer chain.
 */
static void
delete_xfer( PClipboardSysData cc, ClipboardXfer * xfer)
{
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

/*
   Detaches data for pending transfers from XX, so eventual changes 
   to XX->internal would not affect them. detach_xfers() should be
   called before clipboard_kill_item(XX-> internal), otherwise
   there's a chance of coredump.
 */
static void
detach_xfers( PClipboardSysData XX, Handle id, Bool clear_original_data)
{
}

Bool
apc_clipboard_clear( Handle self)
{
   Bool foo; return foo;
}

typedef struct {
   Atom selection;
   long mask;
} SelectionProcData;

#define SELECTION_NOTIFY_MASK 1
#define PROPERTY_NOTIFY_MASK  2

static int
selection_filter( Display * disp, XEvent * ev, SelectionProcData * data)
{
   int foo; return foo;
}

#define CFDATA_NONE            0
#define CFDATA_NOT_ACQUIRED  (-1)
#define CFDATA_ERROR         (-2)

#define RPS_OK       0
#define RPS_PARTIAL  1
#define RPS_NODATA   2
#define RPS_ERROR    3

static int
read_property( Atom property, Atom * type, int * format, 
               unsigned long * size, unsigned char ** data)
{
   int foo; return foo;
}

static Bool
query_datum( Handle self, Handle id, Atom query_target, Atom query_type)
{
   Bool foo; return foo;
}


static Bool
query_data( Handle self, Handle id)
{
   Bool foo; return foo;
}

static Atom
find_atoms( Atom * data, int length, int id)
{
   Atom foo; return foo;
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

static Bool
expand_clipboards( Handle self, int keyLen, void * key, void * dummy)
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
  return C(self)-> selection;
}

static Bool
delete_xfers( Handle self, int keyLen, void * key, XWindow * window)
{
   Bool foo; return foo;
}

void
prima_handle_selection_event( XEvent *ev, XWindow win, Handle self)
{
}

