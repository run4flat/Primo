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
#include "AbstractMenu.h"
#include "Image.h"
#include "Menu.h"
#include "Widget.h"
#include <AbstractMenu.inc>

#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CComponent->
#define my  ((( PAbstractMenu) self)-> self)
#define var (( PAbstractMenu) self)

typedef Bool MenuProc ( Handle self, PMenuItemReg m, void * params);
typedef MenuProc *PMenuProc;

static int key_normalize( const char * key) { return 0; }

static int is_var_id_name( char * name) { return 0; }

void AbstractMenu_dispose_menu( Handle self, void * menu) { }

/* #define log_write debug_write */

void * AbstractMenu_new_menu( Handle self, SV * sv, int level) { return nil; }

void AbstractMenu_init( Handle self, HV * profile) { }

void AbstractMenu_done( Handle self) { }

Bool AbstractMenu_validate_owner( Handle self, Handle * owner, HV * profile) {
   return false;
}

void AbstractMenu_cleanup( Handle self) { }

void AbstractMenu_set( Handle self, HV * profile) { }

static SV * new_av(  PMenuItemReg m, int level) { return nil; }

static Bool var_match( Handle self, PMenuItemReg m, void * params) {
   return false;
}

static Bool id_match( Handle self, PMenuItemReg m, void * params) {
   return false;
}

static Bool key_match( Handle self, PMenuItemReg m, void * params) {
   return false;
}

static PMenuItemReg
find_menuitem( Handle self, char * var_name, Bool match_disabled)
{
   return nil;
}

char *
AbstractMenu_make_var_context( Handle self, PMenuItemReg m, char * buffer)
{
   return nil;
}

char *
AbstractMenu_make_id_context( Handle self, int id, char * buffer)
{
   return nil;
}

SV *
AbstractMenu_get_items( Handle self, char * varName)
{
   return nilSV;
}

void AbstractMenu_set_items( Handle self, SV * items) { }


static PMenuItemReg
do_link( Handle self, PMenuItemReg m, PMenuProc p, void * params, Bool useDisabled)
{
   return nil;
}


void *
AbstractMenu_first_that( Handle self, void * actionProc, void * params, Bool useDisabled)
{
   return nil;
}

Bool
AbstractMenu_has_item( Handle self, char * varName)
{
   return false;
}

SV *
AbstractMenu_accel( Handle self, Bool set, char * varName, SV * accel)
{
   return nilSV;
}


SV *
AbstractMenu_action( Handle self, Bool set, char * varName, SV * action)
{
   return nilSV;
}

Bool
AbstractMenu_checked( Handle self, Bool set, char * varName, Bool checked)
{
   return false;
}

SV *
AbstractMenu_data( Handle self, Bool set, char * varName, SV * data)
{
   return nilSV;
}

Bool
AbstractMenu_enabled( Handle self, Bool set, char * varName, Bool enabled)
{
   return false;
}

Handle
AbstractMenu_image( Handle self, Bool set, char * varName, Handle image)
{
   return nilHandle;
}

SV *
AbstractMenu_text( Handle self, Bool set, char * varName, SV * text)
{
   return nilSV;
}

SV *
AbstractMenu_key( Handle self, Bool set, char * varName, SV * key)
{
   return nilSV;
}

void
AbstractMenu_set_variable( Handle self, char * varName, SV * newName)
{
   return;
}

Bool
AbstractMenu_sub_call( Handle self, PMenuItemReg m)
{
   return false;
}

Bool
AbstractMenu_sub_call_id( Handle self, int sysId)
{
   return false;
}

Bool
AbstractMenu_sub_call_key ( Handle self, int key)
{
   return false;
}

static Bool kmcc ( Handle self, PMenuItemReg m, void * params) { return false; }

void AbstractMenu_set_command( Handle self, char * key, Bool enabled) {}

Bool AbstractMenu_selected( Handle self, Bool set, Bool selected)
{
   return false;
}

SV * AbstractMenu_get_handle( Handle self) { return nilSV; }

int AbstractMenu_translate_accel( Handle self, char * accel) { return 0; }

int AbstractMenu_translate_key( Handle self, int code, int key, int mod) {
   return 0;
}

int AbstractMenu_translate_shortcut( Handle self, char * key) { return 0; }

static Bool up_match   ( Handle self, PMenuItemReg m, void * params) { return false; }
static Bool prev_match ( Handle self, PMenuItemReg m, void * params) { return false; }

void AbstractMenu_remove( Handle self, char * varName) {}

void
AbstractMenu_insert( Handle self, SV * menuItems, char * rootName, int index)
{}


#ifdef __cplusplus
}
#endif

