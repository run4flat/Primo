/*
 * Copyright (c) 2007 Dmitry Karasik
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

/*********************************/
/*                               */
/*  Gtk file dialog              */
/*                               */
/*********************************/

#include "unix/guts.h"

#ifdef WITH_GTK2

#undef dirty

#include <gtk/gtk.h>

static int gtk_initialized = 0;

static GtkWidget *gtk_dialog           = NULL;
static char	gtk_dialog_title[256];
static char*	gtk_dialog_title_ptr   = NULL;
static Bool	gtk_select_multiple    = FALSE;
static Bool	gtk_overwrite_prompt   = FALSE;
static Bool	gtk_show_hidden_files  = FALSE;
static char	gtk_current_folder[MAXPATHLEN+1];
static char*	gtk_current_folder_ptr = NULL;
static List*	gtk_filters            = NULL;
static int	gtk_filter_index       = 0;

Bool
prima_gtk_init(void)
{
   Bool foo; return foo;
}

Bool
prima_gtk_done(void)
{
   Bool foo; return foo;
}

static gboolean do_events(gpointer data)
{
	prima_one_loop_round( false, true);
	return gtk_dialog != NULL;
}

static char *
gtk_openfile( Bool open)
{
   char * foo; return foo;
}

char *
prima_gtk_openfile( char * params)
{
   char * foo; return foo;
}

#endif
