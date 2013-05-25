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
#include "Icon.h"

 static int
cursor_map[] = {
   /* crArrow           => */   XC_left_ptr,
   /* crText            => */   XC_xterm,
   /* crWait            => */   XC_watch,
   /* crSize            => */   XC_sizing,
   /* crMove            => */   XC_fleur,
   /* crSizeWest        => */   XC_left_side,
   /* crSizeEast        => */   XC_right_side,
   /* crSizeNE          => */   XC_sb_h_double_arrow,
   /* crSizeNorth       => */   XC_top_side,
   /* crSizeSouth       => */   XC_bottom_side,
   /* crSizeNS          => */   XC_sb_v_double_arrow,
   /* crSizeNW          => */   XC_top_left_corner,
   /* crSizeSE          => */   XC_bottom_right_corner,
   /* crSizeNE          => */   XC_top_right_corner,
   /* crSizeSW          => */   XC_bottom_left_corner,
   /* crInvalid         => */   XC_X_cursor,
};

 Cursor
predefined_cursors[] = {
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None,
   None
};

static int
get_cursor( Handle self, Pixmap *source, Pixmap *mask, Point *hot_spot, Cursor *cursor)
{
   int foo; return foo;
}

static Bool
load_pointer_font( void)
{
   Bool foo; return foo;
}

Point
apc_pointer_get_hot_spot( Handle self)
{
   Point foo; return foo;
}

Point
apc_pointer_get_pos( Handle self)
{
   Point foo; return foo;
}

int
apc_pointer_get_shape( Handle self)
{
   int foo; return foo;
}

Point
apc_pointer_get_size( Handle self)
{
   Point foo; return foo;
}

Bool
apc_pointer_get_bitmap( Handle self, Handle icon)
{
   Bool foo; return foo;
}

Bool
apc_pointer_get_visible( Handle self)
{
   Bool foo; return foo;
}

Bool
apc_pointer_set_pos( Handle self, int x, int y)
{
   Bool foo; return foo;
}

Bool
apc_pointer_set_shape( Handle self, int id)
{
   Bool foo; return foo;
}

Bool
apc_pointer_set_user( Handle self, Handle icon, Point hot_spot)
{
   Bool foo; return foo;
}



Bool
apc_pointer_set_visible( Handle self, Bool visible)
{
   Bool foo; return foo;
}

Cursor
prima_null_pointer( void)
{
   Cursor foo; return foo;
}
