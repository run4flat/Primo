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
 */

/* $Id$ */

#ifndef _APRICOT_H_
#define _APRICOT_H_

#define PRIMA_CORE 1
#ifdef PRIMA_CORE
#define POLLUTE_NAME_SPACE 1
#endif

#define PRIMA_CORE_VERSION 2012080101

#define PRIMA_VERSION_BOOTCHECK \
    if(apc_get_core_version()!=PRIMA_CORE_VERSION) \
        croak("Prima object version(%ld) doesn't match module version(%ld). Recompile the module", apc_get_core_version(), PRIMA_CORE_VERSION )

#include "generic/config.h"

#if (PERL_PATCHLEVEL < 4 || (( PERL_PATCHLEVEL == 4) && ( PERL_SUBVERSION <= 4)))
#error "Prima require at least perl 5.005"
#endif

/* #define PARANOID_MALLOC */

#ifdef _MSC_VER
   #define BROKEN_COMPILER       1
   #define BROKEN_PERL_PLATFORM  1
   #define snprintf              _snprintf
   #define vsnprintf             _vsnprintf
   #define stricmp               _stricmp
   #define strnicmp              _strnicmp
   #define HAVE_SNPRINTF         1
   #define HAVE_STRICMP          1
   #define HAVE_STRNICMP         1
#elif defined( __BORLANDC__)
   #define BROKEN_PERL_PLATFORM  1
   #define BROKEN_COMPILER       1
#elif defined(WIN32)
   #define BROKEN_PERL_PLATFORM  1
#endif

#ifdef WORD
#error "Reconsider the order in which you #include files"
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_BITYPES_H
#include <sys/bitypes.h>
#endif
#ifdef HAVE_SYS_INTTYPES_H
#include <sys/inttypes.h>
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#define __XSlock_h__ 28
#include <EXTERN.h>
#include <perl.h>
#ifdef REMOVE_dTHR_FROM_dSP
#undef dSP
#define dSP                djSP
#endif
#include <XSUB.h>

#ifdef PERL_OBJECT
   #define XS_STARTPARAMS   CV* cv, CPerlObj* pPerl
   #define XS_CALLPARAMS    cv, pPerl
#else
   #define XS_STARTPARAMS   CV* cv
   #define XS_CALLPARAMS    cv
#endif

#if defined(_MSC_VER) && defined(PERL_OBJECT)
class XSLockManager
{
public:
        XSLockManager() { InitializeCriticalSection(&cs); };
        ~XSLockManager() { DeleteCriticalSection(&cs); };
        void Enter(void) { EnterCriticalSection(&cs); };
        void Leave(void) { LeaveCriticalSection(&cs); };
protected:
        CRITICAL_SECTION cs;
};

extern XSLockManager g_XSLock;
extern CPerlObj* pPerl;

class XSLock
{
public:
        XSLock(CPerlObj *p) {
            g_XSLock.Enter();
            ::pPerl = p;
        };
        ~XSLock() { g_XSLock.Leave(); };
};

/* PERL_CAPI does its own locking in xs_handler() */
#if defined(PERL_OBJECT) && !defined(PERL_CAPI)
#undef dXSARGS
#define dXSARGS \
        XSLock localLock(pPerl);                        \
        dSP; dMARK;                                     \
        I32 ax = mark - PL_stack_base + 1;              \
        I32 items = sp - mark
#endif  /* PERL_OBJECT && !PERL_CAPI */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
#undef realloc
#undef malloc
#undef free
*/


#if defined (package)
   #undef mod
   #undef list
   #undef package
   #undef ref
#endif

#if defined(WORD) && (WORD==257)
#undef WORD
#endif
#include <stdlib.h>

#ifdef BROKEN_PERL_PLATFORM
   #undef open
   #undef fopen
   #undef vfprintf
   #undef fclose
   #undef feof
   #undef ferror
   #undef environ
   #undef strerror
   #undef fread
   #undef fwrite
   #undef fopen
   #undef fdopen
   #undef freopen
   #undef fclose
   #undef fputc
   #undef ungetc
   #undef getc
   #undef fileno
   #undef clearerr
   #undef fflush
   #undef ftell
   #undef fseek
   #undef fgetpos
   #undef fsetpos
   #undef rewind
   #undef tmpfile
   #undef abort
   #undef fstat
   #undef stat
   #undef rename
   #undef setmode
   #undef lseek
   #undef tell
   #undef dup
   #undef dup2
   #undef open
   #undef close
   #undef eof
   #undef read
   #undef write
   #undef _open_osfhandle
   #undef _get_osfhandle
   #undef spawnvp
   #undef mkdir
   #undef rmdir
   #undef chdir
   #undef flock
   #undef execv
   #undef execvp
   #undef perror
   #undef setbuf
   #undef setvbuf
   #undef flushall
   #undef fcloseall
   #undef fgets
   #undef gets
   #undef fgetc
   #undef putc
   #undef puts
   #undef getchar
   #undef putchar
   #undef close
   #undef dup
   #ifdef win32_close
      #define close  win32_close
      #define dup    win32_dup
   #endif
   #ifdef PerlIO_stderr    /* ActiveState quirks */
      #if (PERL_VERSION == 8) /* broken stderr definition */
         #undef stderr
         #define stderr PerlIO_stderr()
      #endif
      #if (PERL_VERSION >= 6) /* broken fprintf definition */
         #define fprintf PerlIO_printf
      #else
      #endif
   #elif (PERL_VERSION == 7)
      #define fprintf PerlIO_printf
   #else
      #undef fprintf
      #ifdef win32_stderr
         #undef stderr
         #define stderr win32_stderr()
      #endif
   #endif
#endif

#ifdef PTRV
#undef PTR2UV
#define PTR2UV(x) ((UV)(PTRV)(x))
#undef PTR2IV
#define PTR2IV(x) ((IV)(PTRV)(x))
#undef INT2PTR
#define INT2PTR(type,x) ((type)((PTRV)x))
#endif

#ifndef SvPV_nolen
#define SvPV_nolen(_sv)  SvPV(_sv,na)
#endif

#define PERL_CALL_SV_DIE_BUG_AWARE 1

#ifdef PERL_CALL_SV_DIE_BUG_AWARE
#define PERL_CALL_METHOD   clean_perl_call_method
#define PERL_CALL_PV       clean_perl_call_pv
#else
#define PERL_CALL_METHOD   perl_call_method
#define PERL_CALL_PV       perl_call_pv
#endif

#ifndef HAVE_BZERO
extern void bzero(void*,size_t);
#endif
#ifdef HAVE_STRICMP
#ifndef HAVE_STRCASECMP
#define strcasecmp(a,b) stricmp((a),(b))
#endif
#else
#ifdef HAVE_STRCASECMP
#define stricmp(a,b) strcasecmp((a),(b))
#else
#define strcasecmp(a,b) stricmp((a),(b))
#define PRIMA_NEED_OWN_STRICMP 1
extern int
stricmp(const char *s1, const char *s2);
#endif
#ifdef HAVE_STRNICMP
#ifndef HAVE_STRNCASECMP
#define strncasecmp(a,b,c) strnicmp((a),(b),(c))
#endif
#else
#ifdef HAVE_STRNCASECMP
#define strnicmp(a,b,c) strncasecmp((a),(b),(c))
#else
#define strncasecmp(a,b) strnicmp((a),(b))
#define PRIMA_NEED_OWN_STRNICMP 1
extern int
strnicmp(const char *s1, const char *s2, size_t count);
#endif
#endif
#endif
#ifndef HAVE_STRCASESTR
char * strcasestr( const char * s, const char * find);
#endif
#ifndef HAVE_REALLOCF
extern void *
reallocf(void *ptr, size_t size);
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_PMPRINTF_H
#define printf PmPrintf
extern unsigned long PmPrintf(char *, ...);
#endif


#if ! ( defined( HAVE_SNPRINTF) || defined( HAVE__SNPRINTF))
extern int
snprintf( char *, size_t, const char *, ...);

extern int
vsnprintf( char *, size_t, const char *, va_list);
#endif

#define alloc1(typ)     ((typ*)malloc(sizeof(typ)))
#define allocn(typ,n)   ((typ*)malloc((n)*sizeof(typ)))
#define allocs(n)       ((char*)malloc(n))
#define allocb(n)       ((Byte*)malloc(n))
#define alloc1z(typ)    ((typ*)prima_mallocz(sizeof(typ)))
#define allocnz(typ,n)  ((typ*)prima_mallocz((n)*sizeof(typ)))

extern void *
prima_mallocz( size_t sz);

typedef I32 Bool;
#if PTRSIZE==LONGSIZE
typedef unsigned long Handle;
#elif PTRSIZE==INTSIZE
typedef unsigned int Handle;
#elif PTRSIZE==SHORTSIZE
typedef unsigned short Handle;
#elif defined(HAS_LONG_LONG) && PTRSIZE==LONGLONGSIZE
typedef unsigned long long Handle;
#elif defined(HAS_QUAD) && PTRSIZE==8
typedef Uquad_t Handle;
#else
#error "Cannot find adequate integer type"
#endif
typedef Handle ApiHandle;

#include "Types.h"

#if !defined(HAVE_INT8_T)
typedef I8 int8_t;
#endif
#if !defined(HAVE_INT16_T)
typedef I16  int16_t;
#endif
#if !defined(HAVE_INT32_T)
typedef I32  int32_t;
#endif
#if !defined(HAVE_UINT8_T)
#if defined(HAVE_U_INT8_T)
typedef u_int8_t        uint8_t;
#else
typedef U8 uint8_t;
#endif
#endif
#if !defined(HAVE_UINT16_T)
#if defined(HAVE_U_INT16_T)
typedef u_int16_t       uint16_t;
#else
typedef U16 uint16_t;
#endif
#endif
#if !defined(HAVE_UINT32_T)
#if defined(HAVE_U_INT32_T)
typedef u_int32_t       uint32_t;
#else
typedef U32 uint32_t;
#endif
#endif
#if !defined(HAVE_UINT64_T)
#if defined(HAVE_U_INT64_T)
typedef u_int64_t       uint64_t;
#elif defined U64
typedef U64 uint64_t;
#elif defined(_MSC_VER) && _MSC_VER < 1500
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#else
typedef unsigned long uint64_t;
#endif
#endif

typedef uint32_t        Color;

typedef uint8_t         Byte;
typedef int16_t         Short;
typedef int32_t         Long;

#undef INT16_MIN
#undef INT16_MAX
#undef INT32_MIN
#undef INT32_MAX
#define INT16_MIN (-32768)
#define INT16_MAX 32768
#define INT32_MIN  (-2147483647L-1)
#define INT32_MAX 2147483647L

typedef struct { float  re, im; } Complex;
typedef struct { double re, im; } DComplex;
typedef struct { float  r,  ph; } TrigComplex;
typedef struct { double r,  ph; } TrigDComplex;

#ifdef __cplusplus
#define nil       NULL
#else
#define nil       Null(void*)
#endif
#define nilHandle Null(Handle)
#define nilSV     &PL_sv_undef

#ifndef true
#define true TRUE
#endif

#ifndef false
#define false FALSE
#endif

/* hashes support */
/* It's a mere coincidence that hashes in Prima guts implemented */
/* by means of Perl hashes */

#ifdef POLLUTE_NAME_SPACE
#define hash_create        prima_hash_create
#define hash_destroy       prima_hash_destroy
#define hash_fetch         prima_hash_fetch
#define hash_delete        prima_hash_delete
#define hash_store         prima_hash_store
#define hash_count         prima_hash_count
#define hash_first_that    prima_hash_first_that
#endif

typedef HV *PHash;
typedef Bool HashProc( void * item, int keyLen, void * key, void * params);
typedef HashProc *PHashProc;

extern PHash primaObjects;

extern PHash
prima_hash_create( void);

extern void
prima_hash_destroy( PHash self, Bool killAll);

extern void*
prima_hash_fetch( PHash self, const void *key, int keyLen);

extern void*
prima_hash_delete( PHash self, const void *key, int keyLen, Bool kill);

extern Bool
prima_hash_store( PHash self, const void *key, int keyLen, void *val);

#define prima_hash_count(hash) (HvKEYS(( HV*) hash))

extern void*
prima_hash_first_that( PHash self, void *action, void *params,
                       int *pKeyLen, void **pKey);

extern char *
prima_normalize_resource_string( char *name, Bool isClass);

/* tables of constants support */

#ifdef GENERATE_TABLE_GENERATOR
#ifndef TABLE_GENERATOR_NEWSVSTRING
#define TABLE_GENERATOR_NEWSVSTRING
static SV*
newSVstring( char *s)
{
   return newSVpv( s, 0);
}
#endif
#define START_TABLE(package,type) \
typedef struct { \
   char *name;   \
   type value;  \
} ConstTable_##package; \
ConstTable_##package Prima_Autoload_##package##_constants[] = {
#define CONSTANT(package,const_name) \
   { #const_name , package##const_name },
#define CONSTANT2(package,const_name,string_name) \
   { #string_name , package##const_name },
#define END_TABLE4(package,type,suffix,conversion) \
}; /* end of table */ \
static SV* newSVstring( char *s); \
XS(prima_autoload_##package##_constant) \
{ \
   static PHash table = nil; \
   dXSARGS; \
   char *name; \
   int i; \
   type *r; \
 \
   if (!table) { \
      table = hash_create(); \
      if (!table) croak( #package "::constant: cannot create hash"); \
      for ( i = 0; i < sizeof( Prima_Autoload_##package##_constants) \
               / sizeof( ConstTable_##package); i++) \
         hash_store( table, \
                     Prima_Autoload_##package##_constants[i]. name, \
                     (I32) strlen( Prima_Autoload_##package##_constants[i]. name), \
                     &Prima_Autoload_##package##_constants[i]. value); \
   } \
 \
   if ( items != 1) croak( "invalid call to " #package "::constant"); \
   name = SvPV_nolen( ST( 0)); \
   SPAGAIN; \
   SP -= items; \
   r = (type *)hash_fetch( table, name, (I32) strlen( name)); \
   if ( !r) croak( "invalid value: " #package "::%s", name); \
   XPUSHs( sv_2mortal( newSV##suffix((conversion)*r))); \
   PUTBACK; \
   return; \
} \
void register_##package##_constants( void) { \
   HV *unused_hv; \
   GV *unused_gv; \
   SV *sv; \
   CV *cv; \
   int i; \
 \
   newXS( #package "::constant", prima_autoload_##package##_constant, #package); \
   sv = newSVpv("", 0); \
   for ( i = 0; i < sizeof( Prima_Autoload_##package##_constants) \
            / sizeof( ConstTable_##package); i++) { \
      sv_setpvf( sv, "%s::%s", #package, Prima_Autoload_##package##_constants[i]. name); \
      cv = sv_2cv(sv, &unused_hv, &unused_gv, true); \
      sv_setpv((SV*)cv, ""); \
   } \
   sv_free( sv); \
}
#else
#define START_TABLE(package,type) \
typedef struct { \
   char *name;   \
   type value;  \
} ConstTable_##package;
#define CONSTANT(package,const_name) /* nothing */
#define CONSTANT2(package,const_name,string_name) /* nothing */
#define END_TABLE4(package,type,suffix,conversion) /* nothing */
#endif
#define END_TABLE(package,type) END_TABLE4(package,type,iv,IV)
#define END_TABLE_CHAR(package,type) END_TABLE4(package,type,string,char*)

/* Object life stages */
#define csDeadInInit    -2         /* dead before any init() code */
#define csConstructing  -1         /* before create() finished */
#define csNormal         0         /* normal during life stage */
#define csDestroying     1         /* destroy() started */
#define csFrozen         2         /* cleanup() started - no messages
                                      available at this point */
#define csFinalizing     3         /* done() started */
#define csDead           4         /* destroy() finished - no methods
                                      available at this point */

/* Please, please, PLEASE!  Do not use directly! */

typedef struct _VmtPatch
{
   void *vmtAddr;
   void *procAddr;
   char *name;
} VmtPatch;

typedef struct _VMT {         /* Whatever VMT */
   char *className;
   struct _VMT *super;
   struct _VMT *base;
   int instanceSize;
   VmtPatch *patch;
   int patchLength;
   int vmtSize;
} VMT, *PVMT;

typedef struct _AnyObject {   /* Whatever Object */
   PVMT self;
   PVMT *super;
   SV   *mate;
   struct _AnyObject *killPtr;
} AnyObject, *PAnyObject;

/* gencls rtl support */

#define C_NUMERIC_UNDEF   -90909090
#define C_STRING_UNDEF    "__C_CHAR_UNDEF__"
#define C_POINTER_UNDEF   nilSV

/* run-time class information functions */

extern Bool
kind_of( Handle object, void *cls);

/* debugging functions */
extern int
debug_write( const char *format, ...);

/* perl links */
#if (PERL_PATCHLEVEL < 5)
/* ...(perl stinks)... */
#undef  SvREFCNT_inc
#define SvREFCNT_inc(sv) ((Sv = (SV*)(sv)),             \
                          (void)(Sv && ++SvREFCNT(Sv)), \
                          (SV*)Sv)
#endif

#ifdef PERL_CALL_SV_DIE_BUG_AWARE
extern I32
clean_perl_call_method( char* methname, I32 flags);

extern I32
clean_perl_call_pv( char* subname, I32 flags);
#endif

extern void
build_static_vmt( void *vmt);

extern Bool
build_dynamic_vmt( void *vmt, const char *ancestorName, int ancestorVmtSize);

extern PVMT
gimme_the_vmt( const char *className);

extern Handle
gimme_the_mate( SV *perlObject);

extern Handle
create_mate( SV *perlObject);

extern SV*
eval( char* string);

extern CV*
sv_query_method( SV * object, char *methodName, Bool cacheIt);

extern CV*
query_method( Handle object, char *methodName, Bool cacheIt);

extern SV*
call_perl_indirect( Handle self, char *subName, const char *format,
                    Bool cdecl, Bool coderef, va_list params);

extern SV*
call_perl( Handle self, char *subName, const char *format, ...);

extern SV*
sv_call_perl( SV * mate, char *subName, const char *format, ...);

extern SV*
notify_perl( Handle self, char *methodName, const char *format, ...);

extern SV*
cv_call_perl( SV * mate, SV * coderef, const char *format, ...);

extern Handle
Object_create( char * className, HV * profile);

extern void
Object_destroy( Handle self);

extern void
protect_object( Handle obj);

extern void
unprotect_object( Handle obj);

extern void
kill_zombies( void);

extern HV*
parse_hv( I32 ax, SV **sp, I32 items, SV **mark,
          int expected, const char *methodName);

extern void
push_hv( I32 ax, SV **sp, I32 items, SV **mark, int callerReturns, HV *hv);

extern SV**
push_hv_for_REDEFINED( SV **sp, HV *hv);

extern int
pop_hv_for_REDEFINED( SV **sp, int count, HV *hv, int shouldBe);

extern void
perl_error(void);

extern void*
create_object( const char *objClass, const char *types, ...);

#ifdef __GNUC__
#define SvBOOL(sv) ({ SV *svsv = sv; SvTRUE(svsv);})
#else
__INLINE__ Bool
SvBOOL( SV *sv)
{
   return SvTRUE(sv);
}
#endif

#define pexist( key) hv_exists( profile, # key, (I32) strlen( #key))
#define pdelete( key) (void) hv_delete( profile, # key, (I32) strlen( #key), G_DISCARD)
#define dPROFILE  SV ** temporary_prf_Sv
#define pget_sv( key) ((( temporary_prf_Sv = hv_fetch( profile, # key, (I32) strlen( # key), 0)) == nil) ? croak( "Panic: bad profile key (``%s'') requested in ``%s'', line %d\n", # key, __FILE__, __LINE__ ), &PL_sv_undef : *temporary_prf_Sv)
#define pget_i( key)  ( pget_sv( key), SvIV( *temporary_prf_Sv))
#define pget_f( key)  ( pget_sv( key), SvNV( *temporary_prf_Sv))
#define pget_c( key)  ( pget_sv( key), SvPV_nolen( *temporary_prf_Sv))
#define pget_H( key)  gimme_the_mate( pget_sv( key))
#define pget_B( key)  ( SvTRUE( pget_sv( key)))

#define pset_sv_noinc( key, value) (void)hv_store( profile, # key, (I32) strlen( # key), value, 0)
#define pset_sv( key, value) pset_sv_noinc( key, newSVsv( value))
#define pset_i( key, value)  pset_sv_noinc( key, newSViv( value))
#define pset_f( key, value)  pset_sv_noinc( key, newSVnv( value))
#define pset_c( key, value)  pset_sv_noinc( key, newSVpv( value, 0))
#define pset_b( key, value, len)  pset_sv_noinc( key, newSVpv( value, ( len)))
#define pset_H( key, value)  pset_sv_noinc( key, (value) ? newSVsv((( PAnyObject) (value))-> mate) : nilSV)

#define create_instance( obj)  (                                   \
   temporary_prf_Sv = ( SV **) Object_create( obj, profile),       \
   ( temporary_prf_Sv ?                                            \
       --SvREFCNT( SvRV((( PAnyObject) temporary_prf_Sv)-> mate))  \
       : 0),                                                       \
   ( Handle) temporary_prf_Sv                                      \
   )

#ifdef POLLUTE_NAME_SPACE
#define TransmogrifyHandle(c,h)         ((P##c)(h))
#define PObject(h)                      TransmogrifyHandle(Object,(h))
#define CObject(h)                      (PObject(h)-> self)
#endif


/* mapping functions */

#define endCtx          0x19740108

extern Handle
ctx_remap_def ( Handle value, Handle * table, Bool direct, Handle default_value);

#define ctx_remap_end(a,b,c)    ctx_remap_def((a),(b),(c), endCtx)
#define ctx_remap(a,b,c)        ctx_remap_def((a),(b),(c), 0)

/* utility functions */

extern char *
duplicate_string( const char *);

/* lists support */

typedef struct _List
{
   Handle * items;
   int    count;
   int    size;
   int    delta;
} List, *PList;

typedef Bool ListProc ( Handle item, void * params);
typedef ListProc *PListProc;

extern void
list_create( PList self, int size, int delta);

extern PList
plist_create( int size, int delta);

extern void
list_destroy( PList self);

extern void
plist_destroy( PList self);

extern int
list_add( PList self, Handle item);

extern int
list_insert_at( PList self, Handle item, int pos);

extern Handle
list_at( PList self, int index);

extern void
list_delete( PList self, Handle item);

extern void
list_delete_at( PList self, int index);

extern void
list_delete_all( PList self, Bool kill);

extern int
list_first_that( PList self, void * action, void * params);

extern int
list_index_of( PList self, Handle item);

/* utf8 */
#if PERL_PATCHLEVEL > 5
#define PERL_SUPPORTS_UTF8  1
#if (PERL_PATCHLEVEL == 6)
#define utf8_to_uvchr utf8_to_uv_simple
#define utf8_to_uvuni utf8_to_uv_simple
#define uvchr_to_utf8 uv_to_utf8
#define uvuni_to_utf8 uv_to_utf8
#endif
#else
/* dummy utf8 functionality */
#undef utf8_hop
#undef utf8_length
#undef  PERL_SUPPORTS_UTF8
#define IN_BYTES            1
#define DO_UTF8(sv)         0
#define SvUTF8(sv)          0
#define utf8_length(s,e)    ((U8*)(e)-(U8*)(s))
#define utf8_hop(s,off)     ((U8*)((s)+(off)))
#define SvUTF8_on(sv)       {}
#define SvUTF8_off(sv)      {}

#define utf8_to_uvchr       prima_utf8_to_uv
#define utf8_to_uvuni       prima_utf8_to_uv
#define uvchr_to_utf8        prima_uv_to_utf8
#define uvuni_to_utf8        prima_uv_to_utf8
extern UV
prima_utf8_to_uv( U8 * utf8, STRLEN * len);

extern U8 *
prima_uv_to_utf8( U8 * utf8, UV uv);

#endif

extern int
prima_utf8_length( const char * utf8);

extern Bool
prima_is_utf8_sv( SV * sv);

/* OS types */
#define APC(const_name) CONSTANT(apc,const_name)
START_TABLE(apc,UV)
#define apcOs2                  1
APC(Os2)
#define apcWin32                2
APC(Win32)
#define apcUnix                 3
APC(Unix)
END_TABLE(apc,UV)
#undef APC

/* apc error constants */
#define errOk                    0x0000
#define errApcError              0x0001
#define errInvObject             0x0002
#define errInvParams             0x0003


/* system-independent object option flags */
typedef struct _ObjectOptions_ {
   unsigned optInDestroyList       : 1;   /* Object */
   unsigned optcmDestroy           : 1;   /* Component */
   unsigned optUTF8_name           : 1;
   unsigned optInDraw              : 1;   /* Drawable */
   unsigned optInDrawInfo          : 1;
   unsigned optTextOutBaseLine     : 1;
   unsigned optAutoEnableChildren  : 1;   /* Widget */
   unsigned optBriefKeys           : 1;
   unsigned optBuffered            : 1;
   unsigned optModalHorizon        : 1;
   unsigned optOwnerBackColor      : 1;
   unsigned optOwnerColor          : 1;
   unsigned optOwnerFont           : 1;
   unsigned optOwnerHint           : 1;
   unsigned optOwnerShowHint       : 1;
   unsigned optOwnerPalette        : 1;
   unsigned optPackPropagate       : 1;
   unsigned optSetupComplete       : 1;
   unsigned optSelectable          : 1;
   unsigned optShowHint            : 1;
   unsigned optSystemSelectable    : 1;
   unsigned optTabStop             : 1;
   unsigned optScaleChildren       : 1;
   unsigned optUTF8_helpContext    : 1;
   unsigned optUTF8_hint           : 1;
   unsigned optUTF8_text           : 1;
   unsigned optPreserveType        : 1;   /* Image */
   unsigned optVScaling            : 1;
   unsigned optHScaling            : 1;
   unsigned optAutoPopup           : 1;   /* Popup */
   unsigned optActive              : 1;   /* Timer */
   unsigned optOwnerIcon           : 1;   /* Window */
   unsigned optMainWindow          : 1;
} ObjectOptions;

#define opt_set( option)           (PObject(self)-> options. option = 1)
#define opt_clear( option)         (PObject(self)-> options. option = 0)
#define is_opt( option)            (PObject(self)-> options. option)
#define opt_assign( option, value) (PObject(self)->options. option = \
                                    (value) ? 1 : 0)
#define opt_InPaint                ( is_opt( optInDraw) \
                                     || is_opt( optInDrawInfo))

extern Handle application;
extern long   apcError;

/* *****************
*  apc functions   *
***************** */

extern Handle
apc_get_core_version();

extern Handle
apc_get_application(void);

/* Memory bugs debugging tools */
#ifdef PARANOID_MALLOC
extern void *
_test_malloc( size_t size, int ln, char *fil, Handle self);

extern void *
_test_realloc( void * ptr, size_t size, int ln, char *fil, Handle self);

extern void
_test_free( void *ptr, int ln, char *fil, Handle self);

#define plist_create( sz, delta) paranoid_plist_create( sz, delta, __FILE__, __LINE__)
#define list_create( slf, sz, delta) paranoid_list_create( slf, sz, delta, __FILE__, __LINE__)
extern PList
paranoid_plist_create( int, int, char *, int);

extern void
paranoid_list_create( PList, int, int, char *, int);

extern Handle self;

#undef malloc
#undef realloc
#undef free
#define realloc(ptr,sz) _test_realloc((ptr),(sz),__LINE__,__FILE__,self)
#define malloc(sz) _test_malloc((sz),__LINE__,__FILE__,self)
#define free(ptr) _test_free((ptr),__LINE__,__FILE__,self)
#endif /* PARANOID_MALLOC */

#if defined( USE_GC)
#if defined( HAVE_GC_H)
#define GC_DEBUG 1
#include <gc.h>
#undef malloc
#undef free
#undef realloc
#define malloc( sz) GC_MALLOC( sz)
#define free( p) GC_FREE( p)
#define realloc( old, sz) GC_REALLOC( old, sz)
#define CHECK_LEAKS GC_gcollect()
#else
#warning USE_GC requires presence of gc.h
#define CHECK_LEAKS
#endif /* HAVE_GC_H */
#else
#define CHECK_LEAKS
#endif /* USE_GC */

#ifdef __cplusplus
}
#endif

#endif

