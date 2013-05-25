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

#include "img.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <math.h>
#include "apricot.h"
#include "Image.h"
#include "img_conv.h"
#include <Image.inc>
#include "Clipboard.h"

#ifdef PerlIO
typedef PerlIO *FileStream;
#else
#define PERLIO_IS_STDIO 1
typedef FILE *FileStream;
#define PerlIO_fileno(f) fileno(f)
#endif


#ifdef __cplusplus
extern "C" {
#endif


#undef  my
#define inherited CDrawable->
#define my  ((( PImage) self)-> self)
#define var (( PImage) self)

static Bool Image_set_extended_data( Handle self, HV * profile);
static void Image_reset_notifications( Handle self);

void
Image_init( Handle self, HV * profile)
{
}

void
Image_handle_event( Handle self, PEvent event)
{
}

void
Image_reset( Handle self, int new_type, RGBColor * palette, int palSize)
{
}

void
Image_stretch( Handle self, int width, int height)
{
}

static void
Image_reset_sv( Handle self, int new_type, SV * palette, Bool triplets)
{
}

void
Image_set( Handle self, HV * profile)
{
}


void
Image_done( Handle self)
{
}

void
Image_make_empty( Handle self)
{
}

Bool
Image_hScaling( Handle self, Bool set, Bool scaling)
{
   return false;
}

Bool
Image_vScaling( Handle self, Bool set, Bool scaling)
{
   return false;
}

Point
Image_resolution( Handle self, Bool set, Point resolution)
{
   Point foo; return foo;
}

Point
Image_size( Handle self, Bool set, Point size)
{
   Point foo; return foo;
}

SV *
Image_get_handle( Handle self)
{
   return nilSV;
}

Color
Image_get_nearest_color( Handle self, Color color)
{
   Color c; return c;
}

SV *
Image_data( Handle self, Bool set, SV * svdata)
{
   return nilSV;
}

/*
  Routine sets image data almost as Image::set_data, but taking into
  account 'lineSize', 'type', and 'reverse' fields. To be called from bunch routines,
  line ::init or ::set. Returns true if relevant fields were found and
  data extracted and set, and false if user data should be set throught ::set_data.
  Image itself may undergo conversion during the routine; in that case 'palette'
  property may be used also. All these fields, if used, or meant to be used but
  erroneously set, will be deleted regardless of routine success. 
*/
Bool
Image_set_extended_data( Handle self, HV * profile)
{
   return false;
}

static size_t
img_perlio_read( void * f, size_t bufsize, void * buffer)
{
   size_t foo; return foo;
}

static size_t
img_perlio_write( void * f, size_t bufsize, void * buffer)
{
   size_t foo; return foo;
}

static int
img_perlio_seek( void * f, long offset, int whence)
{
   int foo; return foo;
}

static long 
img_perlio_tell( void * f)
{
   long foo; return foo;
}

static int
img_perlio_flush( void * f)
{
   int foo; return foo;
}

static int
img_perlio_error( void * f)
{
   int foo; return foo;
}

XS( Image_load_FROMPERL) 
{
}

int
Image_lineSize( Handle self, Bool set, int dummy)
{
   int foo; return foo;
}

PList
Image_load_REDEFINED( SV * who, char *filename, HV * profile)
{
   return nil;
}

PList
Image_load( SV * who, char *filename, HV * profile)
{
   return nil;
}


XS( Image_save_FROMPERL) 
{
}

int
Image_save_REDEFINED( SV * who, char *filename, HV * profile)
{
   int foo; return foo;
}

int
Image_save( SV * who, char *filename, HV * profile)
{
   int foo; return foo;
}

int
Image_type( Handle self, Bool set, int type)
{
   int foo; return foo;
}

int
Image_get_bpp( Handle self)
{
   int foo; return foo;
}


Bool
Image_begin_paint( Handle self)
{
   return false;
}

Bool
Image_begin_paint_info( Handle self)
{
   return false;
}


void
Image_end_paint( Handle self)
{
}

void
Image_end_paint_info( Handle self)
{
}

void
Image_update_change( Handle self)
{
}

double
Image_stats( Handle self, Bool set, int index, double value)
{
   double foo; return foo;
}

void
Image_resample( Handle self, double srcLo, double srcHi, double dstLo, double dstHi)
{
}

SV *
Image_palette( Handle self, Bool set, SV * palette)
{
   return nilSV;
}

int
Image_conversion( Handle self, Bool set, int conversion)
{
   int foo; return foo;
}

void
Image_create_empty( Handle self, int width, int height, int type)
{
}

Bool
Image_preserveType( Handle self, Bool set, Bool preserveType)
{
   return false;
}

SV *
Image_pixel( Handle self, Bool set, int x, int y, SV * pixel)
{
   return nilSV;
}

Handle
Image_bitmap( Handle self)
{
   return nilHandle;
}


Handle
Image_dup( Handle self)
{
   return nilHandle;
}

Handle
Image_extract( Handle self, int x, int y, int width, int height)
{
   return nilHandle;
}

/*
  divide the pixels, by whether they match color or not on two 
  groups, F and B. Both are converted correspondingly to the settings
  of color/backColor and rop/rop2. Possible variations:
  rop == rop::NoOper,    pixel value remains ths same
  rop == rop::CopyPut,   use the color value
  rop == rop::Blackness, use black pixel
  rop == rop::Whiteness, use white pixel
  rop == rop::AndPut   , result is dest & color value
  etc...
*/   

void
Image_map( Handle self, Color color)
{
}

SV * 
Image_codecs( SV * dummy)
{
   return nilSV;
}

Bool
Image_put_image_indirect( Handle self, Handle image, int x, int y, int xFrom, int yFrom, int xDestLen, int yDestLen, int xLen, int yLen, int rop)
{
   return false;
}

UV
Image_add_notification( Handle self, char * name, SV * subroutine, Handle referer, int index)
{
   UV foo; return foo;
}

void
Image_remove_notification( Handle self, UV id)
{
}

static void
Image_reset_notifications( Handle self)
{
}

#ifdef __cplusplus
}
#endif
