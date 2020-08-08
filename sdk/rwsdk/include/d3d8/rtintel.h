/**
 * Intel specific support toolkit
 */

/**********************************************************************
 *
 * File :     rtintel.h
 *
 * Abstract : Intel specific support/emulation
 *
 **********************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd. or
 * Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. will not, under any
 * circumstances, be liable for any lost revenue or other damages arising
 * from the use of this file.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 ************************************************************************/

#ifndef RTINTEL_H
#define RTINTEL_H

/**
 * \defgroup rtintel RtIntel
 * \ingroup rttool
 *
 * Intel CPU Toolkit for RenderWare.
 */

/****************************************************************************
 Include files
 */

/*
 * Pick up
 *    typedef struct _rwResEntryTag RwResEntry;
 * from baresour.h (internal) / rwcore.h (external)
 */

/****************************************************************************
 Global Types
 */

#include "rtintel.rpe"         /* automatically generated header file */

#if (!defined(RW_FIXED_64))
typedef struct RwFixed64 RwFixed64;
struct RwFixed64
{
    RwInt32             msb;
    RwUInt32            lsb;
};

#define RW_FIXED_64
#endif /* (!defined(RW_FIXED_64)) */

#define doubleFromRwFixed64(x) \
 ( ((double)((x).msb))*((double)(1<<16))*((double)(1<<16)) \
 + ((double)((x).lsb)) )

#if (!defined(RPINTELTIMEFUNCTION))
typedef             RwBool(*RtIntelTimeFunction) (void *data);

#define RPINTELTIMEFUNCTION
#endif /* (!defined(RPINTELTIMEFUNCTION)) */

typedef struct RtIntelOverload RtIntelOverload;

typedef void        (*RwTransformFunction) (RwResEntry * repEntry);

struct RtIntelOverload
{
    rwMatrixMultFn      MatrixMultiplyFunction;
    rwVectorMultFn      VectorMultPointFunction;
    rwVectorMultFn      VectorMultVectorFunction;
    RwTransformFunction TransformFunction;
};

#if (defined(__ICL))
#define DEFINED__ICL " __ICL"
#define UNDEFINED__ICL ""
#else /* (defined(__ICL)) */
#define DEFINED__ICL ""
#define UNDEFINED__ICL " __ICL"
#endif /* (defined(__ICL)) */

#if (defined(_MSC_VER))

# pragma comment ( user, "comment:" __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : " "DEFINED " DEFINED__ICL " ; UNDEFINED " UNDEFINED__ICL )
/* # pragma message (__FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : " "DEFINED " DEFINED__ICL " ; UNDEFINED " UNDEFINED__ICL ) */
/* # pragma comment ( user, "comment:" __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : " "DEFINED " DEFINED__ICL " ; UNDEFINED " UNDEFINED__ICL ) */
#if (! (defined(__ICL) || defined(XBOX_DRVMODEL_H)) )
#pragma message (__DATE__ " " __TIME__ " " __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : No MMX intrinsics - defaulting to software emulation")
#pragma message (__DATE__ " " __TIME__ " " __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : No SSE intrinsics - defaulting to software emulation")
#pragma comment ( user, "comment:" __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ") : No MMX intrinsics - defaulting to software emulation")
#endif /* (! (defined(__ICL) || defined(XBOX_DRVMODEL_H)) ) */
#endif /* (defined(_MSC_VER)) */

/*
 * MMX
 */

#if (defined(__ICL))

#if (!defined(MMINTRIN_H))
#include "mmintrin.h"
#define MMINTRIN_H
#endif /* (!defined(MMINTRIN_H)) */

#else /* (defined(__ICL)) */

#if (defined(_MSC_VER))

#if (!defined(__M64))
typedef __int64     Rt_m64;

#define __M64
#endif /* (!defined(__M64)) */

#else /* (defined(_MSC_VER)) -- e.g. __GNUC__ */

#if (!defined(__M64))

typedef RwInt64 Rt_m64;

#define __M64

#endif /* (!defined(__M64)) */

#endif /* (defined(_MSC_VER)) */

#endif /* (defined(__ICL)) */

/*
 * SSE
 */

/*
 * From
 * ccomp.pdf
 * 12 Intel C/C++ Compiler User's Guide
 *     for Win32 Systems With Katmai New Instruction Support
 * --------------------------------------------------------
 * Functionality Intrinsics Usage
 * You need only define one preprocessor symbol and include the header file
 * xmmintrin.h in your application to use the following functionality
 * intrinsics:
 * #define _MM_FUNCTIONALITY
 * #include "xmmintrin.h"
 * To encourage the compiler to inline the functionality intrinsic functions for
 * better performance, consider using the -Qip and -Qipo compiler switches.
 */

#if (defined(__ICL))

/* #define _MM2_FUNCTIONALITY */

/* #define _MM_FUNCTIONALITY */

/* #define _MM_NO_ABORT */

/* #define _MM_NO_ACCURACY */

/* #define _MM_NO_ALIGN_CHECK */

/* #define _MM_NO_INLINE */

/*
 * Undefine "or", since this is valid assembler; e.g. in
 * SDK10/include/xmm_func.h
 *                                                                              _asm                                                                            {
 *                push      eax
 *                fld       f
 *                fstcw     saved_cw
 *                mov       eax, saved_cw
 *                or        eax, 3072
 *                mov       new_cw, eax
 *                fldcw     new_cw
 *                fistp     ret
 *                fldcw     saved_cw
 *                pop       eax
 *                                                                              }
 */

#if (!defined(XMMINTRIN_H))
#include "xmmintrin.h"
#define XMMINTRIN_H
#endif /* (!defined(XMMINTRIN_H)) */

typedef __m64       Rt_m64;
typedef __m128      Rt_m128;

#if (450 <= __ICL)
#if (!defined(EMMINTRIN_H))
#include "emmintrin.h"
#define EMMINTRIN_H
typedef __m128d     Rt_m128d;
typedef __m128i     Rt_m128i;
#endif /* (!defined(EMMINTRIN_H)) */
#else /* (450 <= __ICL) */
typedef __m128      Rt_m128d;
typedef __m128      Rt_m128i;
#endif /* (450 <= __ICL) */

/*
 * Report SSE options as compiler messages and object file comments
 */

#ifdef _MM2_FUNCTIONALITY
#define DEFINED__MM2_FUNCTIONALITY " _MM2_FUNCTIONALITY"
#define UNDEFINED__MM2_FUNCTIONALITY ""
#else /* _MM2_FUNCTIONALITY */
#define DEFINED__MM2_FUNCTIONALITY ""
#define UNDEFINED__MM2_FUNCTIONALITY  " _MM2_FUNCTIONALITY"
#endif /* _MM2_FUNCTIONALITY */

#ifdef _MM_FUNCTIONALITY
#define DEFINED__MM_FUNCTIONALITY DEFINED__MM2_FUNCTIONALITY ## " _MM_FUNCTIONALITY"
#define UNDEFINED__MM_FUNCTIONALITY UNDEFINED__MM2_FUNCTIONALITY
#else /* _MM_FUNCTIONALITY */
#define DEFINED__MM_FUNCTIONALITY DEFINED__MM2_FUNCTIONALITY
#define UNDEFINED__MM_FUNCTIONALITY UNDEFINED__MM2_FUNCTIONALITY ## " _MM_FUNCTIONALITY"
#endif /* _MM_FUNCTIONALITY */

#ifdef _MM_NO_ABORT
#define DEFINED__MM_NO_ABORT DEFINED__MM_FUNCTIONALITY ## " _MM_NO_ABORT"
#define UNDEFINED__MM_NO_ABORT UNDEFINED__MM_FUNCTIONALITY
#else /* _MM_NO_ABORT */
#define DEFINED__MM_NO_ABORT DEFINED__MM_FUNCTIONALITY
#define UNDEFINED__MM_NO_ABORT UNDEFINED__MM_FUNCTIONALITY ## " _MM_NO_ABORT"
#endif /* _MM_NO_ABORT */

#ifdef _MM_NO_ACCURACY
#define DEFINED__MM_NO_ACCURACY DEFINED__MM_NO_ABORT ## " _MM_NO_ACCURACY"
#define UNDEFINED__MM_NO_ACCURACY UNDEFINED__MM_NO_ABORT
#else /* _MM_NO_ACCURACY */
#define DEFINED__MM_NO_ACCURACY DEFINED__MM_NO_ABORT
#define UNDEFINED__MM_NO_ACCURACY UNDEFINED__MM_NO_ABORT ## " _MM_NO_ACCURACY"
#endif /* _MM_NO_ACCURACY */

#ifdef _MM_NO_ALIGN_CHECK
#define DEFINED__MM_NO_ALIGN_CHECK DEFINED__MM_NO_ACCURACY ## " _MM_NO_ALIGN_CHECK"
#define UNDEFINED__MM_NO_ALIGN_CHECK UNDEFINED__MM_NO_ACCURACY
#else /* _MM_NO_ALIGN_CHECK */
#define DEFINED__MM_NO_ALIGN_CHECK DEFINED__MM_NO_ACCURACY
#define UNDEFINED__MM_NO_ALIGN_CHECK UNDEFINED__MM_NO_ACCURACY ## " _MM_NO_ALIGN_CHECK"
#endif /* _MM_NO_ALIGN_CHECK */

#ifdef _MM_NO_INLINE
#define DEFINED__MM_NO_INLINE DEFINED__MM_NO_ALIGN_CHECK ## " _MM_NO_INLINE"
#define UNDEFINED__MM_NO_INLINE UNDEFINED__MM_NO_ALIGN_CHECK
#else /* _MM_NO_INLINE */
#define DEFINED__MM_NO_INLINE DEFINED__MM_NO_ALIGN_CHECK
#define UNDEFINED__MM_NO_INLINE UNDEFINED__MM_NO_ALIGN_CHECK ## " _MM_NO_INLINE"
#endif /* _MM_NO_INLINE */

#pragma comment ( user, "comment:" __DATE__" "  __TIME__ " - " __FILE__ ":" RW_STRINGIFY_EXPANDED(__LINE__) )
#pragma comment ( user, "comment:" "DEFINED  :" DEFINED__MM_NO_INLINE )
#pragma comment ( user, "comment:" "UNDEFINED:" UNDEFINED__MM_NO_INLINE )

#pragma message (__DATE__" "  __TIME__ " - " __FILE__ ":" RW_STRINGIFY_EXPANDED(__LINE__) )
#pragma message ("DEFINED  :" DEFINED__MM_NO_INLINE )
#pragma message ("UNDEFINED:" UNDEFINED__MM_NO_INLINE )

#else /* (defined(__ICL)) */

#define _MM_HINT_T0     1
#define _MM_HINT_T1     2
#define _MM_HINT_T2     3
#define _MM_HINT_NTA    0

#if (defined(__R5900__))
typedef RwInt128 Rt_m128;
#else /* (defined(__R5900__)) */
#if (!defined(_PAIR__M64))
struct Rt_m128
{
    Rt_m64              lo;
    Rt_m64              hi;
};
#define _PAIR__M64
typedef struct Rt_m128 Rt_m128;
#endif /* (!defined(_PAIR__M64)) */
#endif /* (defined(__R5900__)) */

typedef Rt_m128     Rt_m128d;
typedef Rt_m128     Rt_m128i;
#endif /* (defined(__ICL)) */

typedef struct RtIntelV4d RtIntelV4d;
struct RtIntelV4d
{
    RwReal              w;
    RwV3d               v3d;
};

typedef union _RpSSEOverlayM128 RpSSEOverlayM128;

union _RpSSEOverlayM128
{
    float               _f[4];
    RwInt32             _d[4];
    RwUInt32            ud[4];
    RwInt16             _w[8];
    RwUInt16            uw[8];
    RwInt8              _b[16];
    RwUInt8             ub[16];
    Rt_m64              m64[2];
    Rt_m128             m128;
    RtIntelV4d          v4d;
    RwSplitBits         bits[4];
};

typedef RpSSEOverlayM128 RpWNIOverlayM128;

typedef union _RpWNIOverlayM128d RpWNIOverlayM128d;

union _RpWNIOverlayM128d
{
    double              df[2];
    float               _f[4];
    RwInt32             _d[4];
    RwUInt32            ud[4];
    RwInt16             _w[8];
    RwUInt16            uw[8];
    RwInt8              _b[16];
    RwUInt8             ub[16];
    Rt_m64              m64[2];
    Rt_m128d            m128d;
    RtIntelV4d          v4d;
    RwSplitBits         bits[4];
};

typedef union _RpWNIOverlayM128i RpWNIOverlayM128i;

union _RpWNIOverlayM128i
{
    double              df[2];
    float               _f[4];
    RwInt32             _d[4];
    RwUInt32            ud[4];
    RwInt16             _w[8];
    RwUInt16            uw[8];
    RwInt8              _b[16];
    RwUInt8             ub[16];
    Rt_m64              m64[2];
    Rt_m128i            m128i;
    RtIntelV4d          v4d;
    RwSplitBits         bits[4];
};

#define RWUNALIGNED16BYTE(ptr) (0x0000000FUL & ((RwUInt32)(ptr)))

/*--- Plugin API Functions ---*/

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/*
 * MMX
 */

/* General support intrinsics */
extern void         Rt_m_empty(void);
extern Rt_m64       Rt_m_from_int(int i);
extern int          Rt_m_to_int(Rt_m64 m);
extern Rt_m64       Rt_m_packsswb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_packssdw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_packuswb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpckhbw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpckhwd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpckhdq(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpcklbw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpcklwd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_punpckldq(Rt_m64 m1, Rt_m64 m2);

/* Packed arithmetic intrinsics */
extern Rt_m64       Rt_m_paddb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddsb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddsw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddusb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_paddusw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubsb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubsw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubusb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_psubusw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pmaddwd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pmulhw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pmullw(Rt_m64 m1, Rt_m64 m2);

/* Shift intrinsics */
extern Rt_m64       Rt_m_psllw(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psllwi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_pslld(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_pslldi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psllq(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psllqi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psraw(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psrawi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psrad(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psradi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psrlw(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psrlwi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psrld(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psrldi(Rt_m64 m, int count);
extern Rt_m64       Rt_m_psrlq(Rt_m64 m, Rt_m64 count);
extern Rt_m64       Rt_m_psrlqi(Rt_m64 m, int count);

/* Logical intrinsics */
extern Rt_m64       Rt_m_pand(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pandn(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_por(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pxor(Rt_m64 m1, Rt_m64 m2);

/* Comparision intrinsics */
extern Rt_m64       Rt_m_pcmpeqb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pcmpeqw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pcmpeqd(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pcmpgtb(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pcmpgtw(Rt_m64 m1, Rt_m64 m2);
extern Rt_m64       Rt_m_pcmpgtd(Rt_m64 m1, Rt_m64 m2);

/*
 * SSE
 */

/*
 * Arithmetic Operations
 */

extern Rt_m128      Rt_mm_add_ss(Rt_m128 a, Rt_m128 b) /* ADDSS */ ;
extern Rt_m128      Rt_mm_add_ps(Rt_m128 a, Rt_m128 b) /* ADDPS */ ;
extern Rt_m128      Rt_mm_sub_ss(Rt_m128 a, Rt_m128 b) /* SUBSS */ ;
extern Rt_m128      Rt_mm_sub_ps(Rt_m128 a, Rt_m128 b) /* SUBPS */ ;
extern Rt_m128      Rt_mm_mul_ss(Rt_m128 a, Rt_m128 b) /* MULSS */ ;
extern Rt_m128      Rt_mm_mul_ps(Rt_m128 a, Rt_m128 b) /* MULPS */ ;
extern Rt_m128      Rt_mm_div_ss(Rt_m128 a, Rt_m128 b) /* DIVSS */ ;
extern Rt_m128      Rt_mm_div_ps(Rt_m128 a, Rt_m128 b) /* DIVPS */ ;
extern Rt_m128      Rt_mm_sqrt_ss(Rt_m128 a) /* SQRTSS */ ;
extern Rt_m128      Rt_mm_sqrt_ps(Rt_m128 a) /* SQRTPS */ ;
extern Rt_m128      Rt_mm_rcp_ss(Rt_m128 a) /* RCPSS */ ;
extern Rt_m128      Rt_mm_rcp_ps(Rt_m128 a) /* RCPPS */ ;
extern Rt_m128      Rt_mm_rsqrt_ss(Rt_m128 a) /* RSQRTSS */ ;
extern Rt_m128      Rt_mm_rsqrt_ps(Rt_m128 a) /* RSQRTPS */ ;
extern Rt_m128      Rt_mm_min_ss(Rt_m128 a, Rt_m128 b) /* MINSS */ ;
extern Rt_m128      Rt_mm_min_ps(Rt_m128 a, Rt_m128 b) /* MINPS */ ;
extern Rt_m128      Rt_mm_max_ss(Rt_m128 a, Rt_m128 b) /* MAXSS */ ;
extern Rt_m128      Rt_mm_max_ps(Rt_m128 a, Rt_m128 b) /* MAXPS */ ;

/*
 * Logical Operations
 */

extern Rt_m128      Rt_mm_and_ps(Rt_m128 a, Rt_m128 b) /* ANDPS */ ;
extern Rt_m128      Rt_mm_andnot_ps(Rt_m128 a,
                                    Rt_m128 b) /* ANDNPS */ ;
extern Rt_m128      Rt_mm_or_ps(Rt_m128 a, Rt_m128 b) /* ORPS */ ;
extern Rt_m128      Rt_mm_xor_ps(Rt_m128 a, Rt_m128 b) /* XORPS */ ;

/*
 * Comparisons
 */

extern Rt_m128      Rt_mm_cmpeq_ss(Rt_m128 a,
                                   Rt_m128 b) /* CMPEQSS */ ;
extern Rt_m128      Rt_mm_cmpeq_ps(Rt_m128 a,
                                   Rt_m128 b) /* CMPEQPS */ ;
extern Rt_m128      Rt_mm_cmplt_ss(Rt_m128 a,
                                   Rt_m128 b) /* CMPLTSS */ ;
extern Rt_m128      Rt_mm_cmplt_ps(Rt_m128 a,
                                   Rt_m128 b) /* CMPLTPS */ ;
extern Rt_m128      Rt_mm_cmple_ss(Rt_m128 a,
                                   Rt_m128 b) /* CMPLESS */ ;
extern Rt_m128      Rt_mm_cmple_ps(Rt_m128 a,
                                   Rt_m128 b) /* CMPLEPS */ ;
extern Rt_m128      Rt_mm_cmpgt_ss(Rt_m128 a, Rt_m128 b) /* CMPLTSS        r */
                   ;
extern Rt_m128      Rt_mm_cmpgt_ps(Rt_m128 a, Rt_m128 b) /* CMPLTPS        r */
                   ;
extern Rt_m128      Rt_mm_cmpge_ss(Rt_m128 a, Rt_m128 b) /* CMPLESS        r */
                   ;
extern Rt_m128      Rt_mm_cmpge_ps(Rt_m128 a, Rt_m128 b) /* CMPLEPS        r */
                   ;
extern Rt_m128      Rt_mm_cmpneq_ss(Rt_m128 a,
                                    Rt_m128 b) /* CMPNEQSS */ ;
extern Rt_m128      Rt_mm_cmpneq_ps(Rt_m128 a,
                                    Rt_m128 b) /* CMPNEQPS */ ;
extern Rt_m128      Rt_mm_cmpnlt_ss(Rt_m128 a,
                                    Rt_m128 b) /* CMPNLTSS */ ;
extern Rt_m128      Rt_mm_cmpnlt_ps(Rt_m128 a,
                                    Rt_m128 b) /* CMPNLTPS */ ;
extern Rt_m128      Rt_mm_cmpnle_ss(Rt_m128 a,
                                    Rt_m128 b) /* CMPNLESS */ ;
extern Rt_m128      Rt_mm_cmpnle_ps(Rt_m128 a,
                                    Rt_m128 b) /* CMPNLEPS */ ;
extern Rt_m128      Rt_mm_cmpngt_ss(Rt_m128 a, Rt_m128 b)
    /* CMPNLTSS       r */ ;
extern Rt_m128      Rt_mm_cmpngt_ps(Rt_m128 a, Rt_m128 b)
    /* CMPNLTPS       r */ ;
extern Rt_m128      Rt_mm_cmpnge_ss(Rt_m128 a, Rt_m128 b)
    /* CMPNLESS       r */ ;
extern Rt_m128      Rt_mm_cmpnge_ps(Rt_m128 a, Rt_m128 b)
    /* CMPNLEPS       r */ ;
extern Rt_m128      Rt_mm_cmpord_ss(Rt_m128 a,
                                    Rt_m128 b) /* CMPORDSS */ ;
extern Rt_m128      Rt_mm_cmpord_ps(Rt_m128 a,
                                    Rt_m128 b) /* CMPORDPS */ ;
extern Rt_m128      Rt_mm_cmpunord_ss(Rt_m128 a,
                                      Rt_m128 b) /* CMPUNORDSS */ ;
extern Rt_m128      Rt_mm_cmpunord_ps(Rt_m128 a,
                                      Rt_m128 b) /* CMPUNORDPS */ ;
extern int          Rt_mm_comieq_ss(Rt_m128 a,
                                    Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_comilt_ss(Rt_m128 a,
                                    Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_comile_ss(Rt_m128 a,
                                    Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_comigt_ss(Rt_m128 a,
                                    Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_comige_ss(Rt_m128 a,
                                    Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_comineq_ss(Rt_m128 a,
                                     Rt_m128 b) /* COMISS */ ;
extern int          Rt_mm_ucomieq_ss(Rt_m128 a,
                                     Rt_m128 b) /* UCOMISS */ ;
extern int          Rt_mm_ucomilt_ss(Rt_m128 a,
                                     Rt_m128 b) /* UCOMISS */ ;
extern int          Rt_mm_ucomile_ss(Rt_m128 a,
                                     Rt_m128 b) /* UCOMISS */ ;
extern int          Rt_mm_ucomigt_ss(Rt_m128 a,
                                     Rt_m128 b) /* UCOMISS */ ;
extern int          Rt_mm_ucomige_ss(Rt_m128 a,
                                     Rt_m128 b) /* UCOMISS */ ;
extern int          Rt_mm_ucomineq_ss(Rt_m128 a,
                                      Rt_m128 b) /* UCOMISS */ ;

/*
 * Conversion Operations
 */

extern int          Rt_mm_cvt_ss2si(Rt_m128 a) /* CVTSS2SI */ ;
extern Rt_m64       Rt_mm_cvt_ps2pi(Rt_m128 a) /* CVTPS2PI */ ;
extern int          Rt_mm_cvtt_ss2si(Rt_m128 a) /* CVTTSS2SI */ ;
extern Rt_m64       Rt_mm_cvtt_ps2pi(Rt_m128 a) /* CVTTPS2PI */ ;
extern Rt_m128      Rt_mm_cvt_si2ss(Rt_m128 a,
                                    int b) /* CVTSI2SS */ ;
extern Rt_m128      Rt_mm_cvt_pi2ps(Rt_m128 a,
                                    Rt_m64 b) /* CVTPI2PS */ ;

/*
 *     Miscellaneous
 */

extern Rt_m128      Rt_mm_shuffle_ps(Rt_m128 a, Rt_m128 b,
                                     int i) /* SHUFPS */ ;
extern Rt_m128      Rt_mm_unpackhi_ps(Rt_m128 a,
                                      Rt_m128 b) /* UNPCKHPS */ ;
extern Rt_m128      Rt_mm_unpacklo_ps(Rt_m128 a,
                                      Rt_m128 b) /* UNPCKLPS */ ;
extern Rt_m128      Rt_mm_loadh_pi(Rt_m128 a, Rt_m64 * p) /* MOVHPS         reg, mem */
                   ;
extern void         Rt_mm_storeh_pi(Rt_m64 * p, Rt_m128 a) /* MOVHPS         mem, reg */
                   ;
extern Rt_m128      Rt_mm_movehl_ps(Rt_m128 a,
                                    Rt_m128 b) /* MOVHLPS */ ;
extern Rt_m128      Rt_mm_movelh_ps(Rt_m128 a,
                                    Rt_m128 b) /* MOVLHPS */ ;
extern Rt_m128      Rt_mm_loadl_pi(Rt_m128 a, Rt_m64 * p)
    /* MOVLPS         reg,    mem */ ;
extern void         Rt_mm_storel_pi(Rt_m64 * p, Rt_m128 a) /* MOVLPS         mem, reg */
                   ;
extern int          Rt_mm_movemask_ps(Rt_m128 a) /* MOVMSKPS */ ;
extern unsigned int Rt_mm_getcsr(void) /* STMXCSR */ ;
extern void         Rt_mm_setcsr(unsigned int i) /* LDMXCSR */ ;

/*
 * Load Operations
 */

extern Rt_m128      Rt_mm_load_ss(float *p) /* MOVSS */ ;
extern Rt_m128      Rt_mm_load_ps1(float *p) /* MOVSS + shuffling */
                   ;
extern Rt_m128      Rt_mm_load_ps(float *p) /* MOVAPS */ ;
extern Rt_m128      Rt_mm_loadu_ps(float *p) /* MOVUPS */ ;
extern Rt_m128      Rt_mm_loadr_ps(float *p)
    /* MOVAPS + shuffling  */ ;

/*
 * Set Operations
 */

extern Rt_m128      Rt_mm_set_ss(float w) /* (composite) */ ;
extern Rt_m128      Rt_mm_set_ps1(float w) /* (composite) */ ;
extern Rt_m128      Rt_mm_set_ps(float z, float y, float x,
                                 float w) /* (composite) */ ;
extern Rt_m128      Rt_mm_setr_ps(float z, float y, float x,
                                  float w) /* (composite) */ ;
extern Rt_m128      Rt_mm_setzero_ps(void) /* (composite) */ ;

/*
 * Store Operations
 */

extern void         Rt_mm_store_ss(float *p,
                                   Rt_m128 a) /* MOVSS */ ;
extern void         Rt_mm_store_ps1(float *p, Rt_m128 a)
    /* MOVSS + shuffling */ ;
extern void         Rt_mm_store_ps(float *p,
                                   Rt_m128 a) /* MOVAPS */ ;
extern void         Rt_mm_storeu_ps(float *p,
                                    Rt_m128 a) /* MOVUPS */ ;
extern void         Rt_mm_storer_ps(float *p, Rt_m128 a)
    /* MOVAPS + shuffling */ ;
extern Rt_m128      Rt_mm_move_ss(Rt_m128 a,
                                  Rt_m128 b) /* MOVSS */ ;

/*
 * Integer Intrinsics
 */

extern int          Rt_m_pextrw(Rt_m64 a, int n) /* PEXTRW */ ;
extern Rt_m64       Rt_m_pinsrw(Rt_m64 a, int d,
                                int n) /* PINSRW */ ;
extern Rt_m64       Rt_m_pmaxsw(Rt_m64 a, Rt_m64 b) /* PMAXSW */ ;
extern Rt_m64       Rt_m_pmaxub(Rt_m64 a, Rt_m64 b) /* PMAXUB */ ;
extern Rt_m64       Rt_m_pminsw(Rt_m64 a, Rt_m64 b) /* PMINSW */ ;
extern Rt_m64       Rt_m_pminub(Rt_m64 a, Rt_m64 b) /* PMINUB */ ;
extern int          Rt_m_pmovmskb(Rt_m64 a) /* PMOVMSKB */ ;
extern Rt_m64       Rt_m_pmulhuw(Rt_m64 a, Rt_m64 b) /* PMULHUW */ ;
extern Rt_m64       Rt_m_pshufw(Rt_m64 a, int n) /* PSHUFW */ ;
extern void         Rt_m_lwmaskmovq(Rt_m64 d, Rt_m64 n,
                                    char *p) /* MASKMOVQ */ ;

/*
 * Cacheability Support
 */

extern void         Rt_mm_prefetch(char *p, int i) /* PREFETCH */ ;
extern void         Rt_mm_stream_pi(Rt_m64 * p,
                                    Rt_m64 a) /* MOVNTQ */ ;
extern void         Rt_mm_stream_ps(float *p,
                                    Rt_m128 a) /* MOVNTPS */ ;
extern void         Rt_mm_sfence(void) /* SFENCE */ ;

/*
 * WNI
 */

/* Arithmetic Operations  */

extern Rt_m128d     Rt_mm_add_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_add_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_div_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_div_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_max_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_max_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_min_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_min_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_mul_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_mul_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_sqrt_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_sqrt_pd(Rt_m128d a);
extern Rt_m128d     Rt_mm_sub_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_sub_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_andnot_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_and_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_or_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_xor_pd(Rt_m128d a, Rt_m128d b);

/* Comparisons */

extern Rt_m128d     Rt_mm_cmpeq_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmplt_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmple_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpgt_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpge_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpord_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpunord_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpneq_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnlt_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnle_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpngt_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnge_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpeq_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmplt_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmple_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpgt_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpge_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpord_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpunord_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpneq_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnlt_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnle_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpngt_sd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cmpnge_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comieq_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comilt_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comile_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comigt_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comige_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_comineq_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomieq_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomilt_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomile_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomigt_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomige_sd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_ucomineq_sd(Rt_m128d a, Rt_m128d b);

/* Conversion Operations  */

extern Rt_m128      Rt_mm_cvtpd_ps(Rt_m128d a);
extern Rt_m128d     Rt_mm_cvtps_pd(Rt_m128 a);
extern Rt_m128d     Rt_mm_cvtepi32_pd(Rt_m128i a);
extern Rt_m128i     Rt_mm_cvtpd_epi32(Rt_m128d a);
extern int          Rt_mm_cvtsd_si32(Rt_m128d a);
extern Rt_m128      Rt_mm_cvtsd_ss(Rt_m128 a, Rt_m128d b);
extern Rt_m128d     Rt_mm_cvtsi32_sd(Rt_m128d a, int b);
extern Rt_m128d     Rt_mm_cvtss_sd(Rt_m128d a, Rt_m128 b);
extern Rt_m128i     Rt_mm_cvttpd_epi32(Rt_m128d a);
extern int          Rt_mm_cvttsd_si32(Rt_m128d a);
extern Rt_m128      Rt_mm_cvtepi32_ps(Rt_m128i a);
extern Rt_m128i     Rt_mm_cvtps_epi32(Rt_m128 a);
extern Rt_m128i     Rt_mm_cvttps_epi32(Rt_m128 a);
extern Rt_m64       Rt_mm_cvtpd_pi32(Rt_m128d a);
extern Rt_m64       Rt_mm_cvttpd_pi32(Rt_m128d a);
extern Rt_m128d     Rt_mm_cvtpi32_pd(Rt_m64 a);

/* Miscellaneous Operations  */

extern Rt_m128d     Rt_mm_unpackhi_pd(Rt_m128d a, Rt_m128d b);
extern Rt_m128d     Rt_mm_unpacklo_pd(Rt_m128d a, Rt_m128d b);
extern int          Rt_mm_movemask_pd(Rt_m128d a);
extern Rt_m128d     Rt_mm_shuffle_pd(Rt_m128d a, Rt_m128d b, int i);
extern Rt_m128d     Rt_mm_load_pd(const double *p);
extern Rt_m128d     Rt_mm_load1_pd(const double *p);
extern Rt_m128d     Rt_mm_loadr_pd(const double *p);
extern Rt_m128d     Rt_mm_loadu_pd(const double *p);
extern Rt_m128d     Rt_mm_load_sd(const double *p);
extern Rt_m128d     Rt_mm_loadh_pd(Rt_m128d a, const double *p);
extern Rt_m128d     Rt_mm_loadl_pd(Rt_m128d a, const double *p);
extern Rt_m128d     Rt_mm_set_sd(double w);
extern Rt_m128d     Rt_mm_set1_pd(double w);
extern Rt_m128d     Rt_mm_set_pd(double w, double x);
extern Rt_m128d     Rt_mm_setr_pd(double w, double x);
extern Rt_m128d     Rt_mm_setzero_pd(void);
extern Rt_m128d     Rt_mm_move_sd(Rt_m128d a, Rt_m128d b);
extern void         Rt_mm_stream_pd(double *p, Rt_m128d a);
extern void         Rt_mm_store_sd(double *p, Rt_m128d a);
extern void         Rt_mm_store1_pd(double *p, Rt_m128d a);
extern void         Rt_mm_store_pd(double *p, Rt_m128d a);
extern void         Rt_mm_storeu_pd(double *p, Rt_m128d a);
extern void         Rt_mm_storer_pd(double *p, Rt_m128d a);
extern void         Rt_mm_storeh_pd(double *p, Rt_m128d a);
extern void         Rt_mm_storel_pd(double *p, Rt_m128d a);
extern Rt_m128i     Rt_mm_add_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_add_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_add_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m64       Rt_mm_add_si64(Rt_m64 a, Rt_m64 b);
extern Rt_m128i     Rt_mm_add_epi64(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_adds_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_adds_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_adds_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_adds_epu16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_avg_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_avg_epu16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_madd_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_max_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_max_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_min_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_min_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_mulhi_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_mulhi_epu16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_mullo_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m64       Rt_mm_mul_su32(Rt_m64 a, Rt_m64 b);
extern Rt_m128i     Rt_mm_mul_epu32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_sad_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_sub_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_sub_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_sub_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m64       Rt_mm_sub_si64(Rt_m64 a, Rt_m64 b);
extern Rt_m128i     Rt_mm_sub_epi64(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_subs_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_subs_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_subs_epu8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_subs_epu16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_and_si128(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_andnot_si128(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_or_si128(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_xor_si128(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_slli_si128(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_slli_epi16(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_sll_epi16(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_slli_epi32(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_sll_epi32(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_slli_epi64(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_sll_epi64(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_srai_epi16(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_sra_epi16(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_srai_epi32(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_sra_epi32(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_srli_si128(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_srli_epi16(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_srl_epi16(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_srli_epi32(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_srl_epi32(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_srli_epi64(Rt_m128i a, int count);
extern Rt_m128i     Rt_mm_srl_epi64(Rt_m128i a, Rt_m128i count);
extern Rt_m128i     Rt_mm_cmpeq_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmpeq_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmpeq_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmpgt_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmpgt_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmpgt_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmplt_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmplt_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cmplt_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_cvtsi32_si128(int a);
extern int          Rt_mm_cvtsi128_si32(Rt_m128i a);

/* Miscellaneous Operations  */

extern Rt_m64       Rt_mm_movepi64_pi64(Rt_m128i a);
extern Rt_m128i     Rt_mm_movpi64_epi64(Rt_m64 a);
extern Rt_m128i     Rt_mm_move_epi64(Rt_m128i a);
extern Rt_m128i     Rt_mm_packs_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_packs_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_packus_epi16(Rt_m128i a, Rt_m128i b);
extern int          Rt_mm_extract_epi16(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_insert_epi16(Rt_m128i a, int b, int imm);
extern int          Rt_mm_movemask_epi8(Rt_m128i a);
extern Rt_m128i     Rt_mm_shuffle_epi32(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_shufflehi_epi16(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_shufflelo_epi16(Rt_m128i a, int imm);
extern Rt_m128i     Rt_mm_unpackhi_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpackhi_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpackhi_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpackhi_epi64(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpacklo_epi8(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpacklo_epi16(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpacklo_epi32(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_unpacklo_epi64(Rt_m128i a, Rt_m128i b);
extern Rt_m128i     Rt_mm_loadl_epi64(Rt_m128i const *p);
extern Rt_m128i     Rt_mm_load_si128(const Rt_m128i * p);
extern Rt_m128i     Rt_mm_loadu_si128(const Rt_m128i * p);
extern Rt_m128i     Rt_mm_set_epi64(Rt_m64 q1, Rt_m64 q0);
extern Rt_m128i     Rt_mm_set_epi32(int i3, int i2, int i1, int i0);
extern              Rt_m128i
    Rt_mm_set_epi16(short w7, short w6,
                    short w5, short w4, short w3, short w2,
                    short w1, short w0);
extern Rt_m128i     Rt_mm_set_epi8(char b15, char b14,
                                   char b13, char b12,
                                   char b11, char b10,
                                   char b9, char b8,
                                   char b7, char b6,
                                   char b5, char b4,
                                   char b3, char b2,
                                   char b1, char b0);
extern Rt_m128i     Rt_mm_set1_epi64(Rt_m64 q);
extern Rt_m128i     Rt_mm_set1_epi32(int i);
extern Rt_m128i     Rt_mm_set1_epi16(short w);
extern Rt_m128i     Rt_mm_set1_epi8(char b);
extern Rt_m128i     Rt_mm_setr_epi64(Rt_m64 q0, Rt_m64 q1);
extern Rt_m128i     Rt_mm_setr_epi32(int i0, int i1, int i2,
                                     int i3);
extern Rt_m128i     Rt_mm_setr_epi16(short w0, short w1,
                                     short w2, short w3,
                                     short w4, short w5,
                                     short w6, short w7);
extern Rt_m128i     Rt_mm_setr_epi8(char b0, char b1,
                                    char b2, char b3,
                                    char b4, char b5,
                                    char b6, char b7,
                                    char b8, char b9,
                                    char b10, char b11,
                                    char b12, char b13,
                                    char b14, char b15);
extern Rt_m128i     Rt_mm_setzero_si128(void);

/* Store Operations  */

extern void         Rt_mm_store_si128(Rt_m128i * p, Rt_m128i a);
extern void         Rt_mm_storeu_si128(Rt_m128i * p, Rt_m128i a);
extern void         Rt_mm_maskmoveu_si128(Rt_m128i s, Rt_m128i n,
                                          char *p);
extern void         Rt_mm_storel_epi64(Rt_m128i * p, Rt_m128i a);
extern void         Rt_mm_stream_si128(Rt_m128i * p, Rt_m128i a);
extern void         Rt_mm_stream_si32(int *p, int a);
extern void         Rt_mm_clflush(void const *p);
extern void         Rt_mm_lfence(void);
extern void         Rt_mm_mfence(void);

/*
 * API
 */
extern RwUInt32     RtIntelRDTSC(void);
extern RwUInt32     RtIntelToggleEFLAGS(int mask);
extern RwUInt32     RtIntelCPUID(RwUInt32 level, 
                                 void *pb, void *pc, void *pd);
extern RwUInt32     RtIntelHaveCPUID(void);
extern RwUInt32     RtIntelHaveRDTSC(void);
extern RwUInt32     RtIntelHaveMMX(void);
extern RwUInt32     RtIntelHaveSSE(void);
extern RwUInt32     RtIntelHaveWNI(void);
extern RwUInt32     RtIntelCpuType(void);

extern RwBool       RtIntelStartTiming(void * data);
extern RwBool       RtIntelStopTiming(void *data);
extern RwBool       RtIntelTime(RwFixed64 * result,
                                RtIntelTimeFunction func,
                                void *data);

extern RwBool       RtIntelPluginAttach(void);

extern RtIntelOverload *_rtIntelOverloadGetHandle(void);

extern RxNodeDefinition *RxNodeDefinitionGetSSETransformCSL(void);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*
 * LEGACY-SUPPORT -- e.g.
 * rwsdk/driver/d3d/baintd3d.c
 * is locked at time of writing
 */

#define RpIntelRDTSC()                  RtIntelRDTSC()
#define RpIntelToggleEFLAGS(_mask)      RtIntelToggleEFLAGS(_mask)
#define RpIntelCPUID(_level, _pb, _pc, _pd) \
                                        RtIntelCPUID(_level, _pb, _pc, _pd)
#define RpIntelHaveCPUID()              RtIntelHaveCPUID()
#define RpIntelHaveRDTSC()              RtIntelHaveRDTSC()
#define RpIntelHaveMMX()                RtIntelHaveMMX()
#define RpIntelHaveSSE()                RtIntelHaveSSE()
#define RpIntelHaveWNI()                RtIntelHaveWNI()
#define RpIntelCpuType()                RtIntelCpuType()
#define RpIntelStartTiming(_data)       RtIntelStartTiming(_data)
#define RpIntelStopTiming(_data)        RtIntelStopTiming(_data)
#define RpIntelTime(_result, _func, _data) \
                                        RtIntelTime(_result, _func, _data)
#define RpIntelPluginAttach()           RtIntelPluginAttach()
#define RpNodeDefinitionGetSSETransformCSL() \
                               RxNodeDefinitionGetSSETransformCSL()

typedef RtIntelOverload RwIntelOverload;
typedef RtIntelOverload RpIntelOverload;

#define _rwIntelOverloadGetHandle()     _rtIntelOverloadGetHandle()
#define _rpIntelOverloadGetHandle()     _rtIntelOverloadGetHandle()
#define RwIntelHaveSSE()                RtIntelHaveSSE()
#define RpIntelHaveSSE()                RtIntelHaveSSE()

#if (defined(RWEMULATEINTELSIMD) || !defined(__ICL))

/*
 * MMX
 */

/* General support intrinsics */
#define     _m_empty()                  Rt_m_empty()
#define     _m_from_int(i)              Rt_m_from_int(i)
#define     _m_to_int(m)                Rt_m_to_int(m)
#define     _m_packsswb(m1, m2)         Rt_m_packsswb(m1, m2)
#define     _m_packssdw(m1, m2)         Rt_m_packssdw(m1, m2)
#define     _m_packuswb(m1, m2)         Rt_m_packuswb(m1, m2)
#define     _m_punpckhbw(m1, m2)        Rt_m_punpckhbw(m1, m2)
#define     _m_punpckhwd(m1, m2)        Rt_m_punpckhwd(m1, m2)
#define     _m_punpckhdq(m1, m2)        Rt_m_punpckhdq(m1, m2)
#define     _m_punpcklbw(m1, m2)        Rt_m_punpcklbw(m1, m2)
#define     _m_punpcklwd(m1, m2)        Rt_m_punpcklwd(m1, m2)
#define     _m_punpckldq(m1, m2)        Rt_m_punpckldq(m1, m2)

/* Packed arithmetic intrinsics */
#define     _m_paddb(m1, m2)            Rt_m_paddb(m1, m2)
#define     _m_paddw(m1, m2)            Rt_m_paddw(m1, m2)
#define     _m_paddd(m1, m2)            Rt_m_paddd(m1, m2)
#define     _m_paddsb(m1, m2)           Rt_m_paddsb(m1, m2)
#define     _m_paddsw(m1, m2)           Rt_m_paddsw(m1, m2)
#define     _m_paddusb(m1, m2)          Rt_m_paddusb(m1, m2)
#define     _m_paddusw(m1, m2)          Rt_m_paddusw(m1, m2)
#define     _m_psubb(m1, m2)            Rt_m_psubb(m1, m2)
#define     _m_psubw(m1, m2)            Rt_m_psubw(m1, m2)
#define     _m_psubd(m1, m2)            Rt_m_psubd(m1, m2)
#define     _m_psubsb(m1, m2)           Rt_m_psubsb(m1, m2)
#define     _m_psubsw(m1, m2)           Rt_m_psubsw(m1, m2)
#define     _m_psubusb(m1, m2)          Rt_m_psubusb(m1, m2)
#define     _m_psubusw(m1, m2)          Rt_m_psubusw(m1, m2)
#define     _m_pmaddwd(m1, m2)          Rt_m_pmaddwd(m1, m2)
#define     _m_pmulhw(m1, m2)           Rt_m_pmulhw(m1, m2)
#define     _m_pmullw(m1, m2)           Rt_m_pmullw(m1, m2)

/* Shift intrinsics */
#define     _m_psllw(m, count)          Rt_m_psllw(m, count)
#define     _m_psllwi(m, count)         Rt_m_psllwi(m, count)
#define     _m_pslld(m, count)          Rt_m_pslld(m, count)
#define     _m_pslldi(m, count)         Rt_m_pslldi(m, count)
#define     _m_psllq(m, count)          Rt_m_psllq(m, count)
#define     _m_psllqi(m, count)         Rt_m_psllqi(m, count)
#define     _m_psraw(m, count)          Rt_m_psraw(m, count)
#define     _m_psrawi(m, count)         Rt_m_psrawi(m, count)
#define     _m_psrad(m, count)          Rt_m_psrad(m, count)
#define     _m_psradi(m, count)         Rt_m_psradi(m, count)
#define     _m_psrlw(m, count)          Rt_m_psrlw(m, count)
#define     _m_psrlwi(m, count)         Rt_m_psrlwi(m, count)
#define     _m_psrld(m, count)          Rt_m_psrld(m, count)
#define     _m_psrldi(m, count)         Rt_m_psrldi(m, count)
#define     _m_psrlq(m, count)          Rt_m_psrlq(m, count)
#define     _m_psrlqi(m, count)         Rt_m_psrlqi(m, count)

/* Logical intrinsics */
#define     _m_pand(m1, m2)             Rt_m_pand(m1, m2)
#define     _m_pandn(m1, m2)            Rt_m_pandn(m1, m2)
#define     _m_por(m1, m2)              Rt_m_por(m1, m2)
#define     _m_pxor(m1, m2)             Rt_m_pxor(m1, m2)

/* Comparison intrinsics */
#define     _m_pcmpeqb(m1, m2)          Rt_m_pcmpeqb(m1, m2)
#define     _m_pcmpeqw(m1, m2)          Rt_m_pcmpeqw(m1, m2)
#define     _m_pcmpeqd(m1, m2)          Rt_m_pcmpeqd(m1, m2)
#define     _m_pcmpgtb(m1, m2)          Rt_m_pcmpgtb(m1, m2)
#define     _m_pcmpgtw(m1, m2)          Rt_m_pcmpgtw(m1, m2)
#define     _m_pcmpgtd(m1, m2)          Rt_m_pcmpgtd(m1, m2)

/*
 * SSE
 */

/*
 * Arithmetic Operations
 */

#define _mm_add_ss(a, b)                 Rt_mm_add_ss(a, b)
#define _mm_add_ps(a, b)                 Rt_mm_add_ps(a, b)
#define _mm_sub_ss(a, b)                 Rt_mm_sub_ss(a, b)
#define _mm_sub_ps(a, b)                 Rt_mm_sub_ps(a, b)
#define _mm_mul_ss(a, b)                 Rt_mm_mul_ss(a, b)
#define _mm_mul_ps(a, b)                 Rt_mm_mul_ps(a, b)
#define _mm_div_ss(a, b)                 Rt_mm_div_ss(a, b)
#define _mm_div_ps(a, b)                 Rt_mm_div_ps(a, b)
#define _mm_sqrt_ss(a)                   Rt_mm_sqrt_ss(a)
#define _mm_sqrt_ps(a)                   Rt_mm_sqrt_ps(a)
#define _mm_rcp_ss(a)                    Rt_mm_rcp_ss(a)
#define _mm_rcp_ps(a)                    Rt_mm_rcp_ps(a)
#define _mm_rsqrt_ss(a)                  Rt_mm_rsqrt_ss(a)
#define _mm_rsqrt_ps(a)                  Rt_mm_rsqrt_ps(a)
#define _mm_min_ss(a, b)                 Rt_mm_min_ss(a, b)
#define _mm_min_ps(a, b)                 Rt_mm_min_ps(a, b)
#define _mm_max_ss(a, b)                 Rt_mm_max_ss(a, b)
#define _mm_max_ps(a, b)                 Rt_mm_max_ps(a, b)

/*
 * Logical Operations
 */

#define _mm_and_ps(a, b)                 Rt_mm_and_ps(a, b)
#define _mm_andnot_ps(a, b)              Rt_mm_andnot_ps(a, b)
#define _mm_or_ps(a, b)                  Rt_mm_or_ps(a, b)
#define _mm_xor_ps(a, b)                 Rt_mm_xor_ps(a, b)

/*
 * Comparisons
 */

#define _mm_cmpeq_ss(a, b)               Rt_mm_cmpeq_ss(a, b)
#define _mm_cmpeq_ps(a, b)               Rt_mm_cmpeq_ps(a, b)
#define _mm_cmplt_ss(a, b)               Rt_mm_cmplt_ss(a, b)
#define _mm_cmplt_ps(a, b)               Rt_mm_cmplt_ps(a, b)
#define _mm_cmple_ss(a, b)               Rt_mm_cmple_ss(a, b)
#define _mm_cmple_ps(a, b)               Rt_mm_cmple_ps(a, b)
#define _mm_cmpgt_ss(a, b)               Rt_mm_cmpgt_ss(a, b)
#define _mm_cmpgt_ps(a, b)               Rt_mm_cmpgt_ps(a, b)
#define _mm_cmpge_ss(a, b)               Rt_mm_cmpge_ss(a, b)
#define _mm_cmpge_ps(a, b)               Rt_mm_cmpge_ps(a, b)
#define _mm_cmpneq_ss(a, b)              Rt_mm_cmpneq_ss(a, b)
#define _mm_cmpneq_ps(a, b)              Rt_mm_cmpneq_ps(a, b)
#define _mm_cmpnlt_ss(a, b)              Rt_mm_cmpnlt_ss(a, b)
#define _mm_cmpnlt_ps(a, b)              Rt_mm_cmpnlt_ps(a, b)
#define _mm_cmpnle_ss(a, b)              Rt_mm_cmpnle_ss(a, b)
#define _mm_cmpnle_ps(a, b)              Rt_mm_cmpnle_ps(a, b)
#define _mm_cmpngt_ss(a, b)              Rt_mm_cmpngt_ss(a, b)
#define _mm_cmpngt_ps(a, b)              Rt_mm_cmpngt_ps(a, b)
#define _mm_cmpnge_ss(a, b)              Rt_mm_cmpnge_ss(a, b)
#define _mm_cmpnge_ps(a, b)              Rt_mm_cmpnge_ps(a, b)
#define _mm_cmpord_ss(a, b)              Rt_mm_cmpord_ss(a, b)
#define _mm_cmpord_ps(a, b)              Rt_mm_cmpord_ps(a, b)
#define _mm_cmpunord_ss(a, b)            Rt_mm_cmpunord_ss(a, b)
#define _mm_cmpunord_ps(a, b)            Rt_mm_cmpunord_ps(a, b)
#define _mm_comieq_ss(a, b)              Rt_mm_comieq_ss(a, b)
#define _mm_comilt_ss(a, b)              Rt_mm_comilt_ss(a, b)
#define _mm_comile_ss(a, b)              Rt_mm_comile_ss(a, b)
#define _mm_comigt_ss(a, b)              Rt_mm_comigt_ss(a, b)
#define _mm_comige_ss(a, b)              Rt_mm_comige_ss(a, b)
#define _mm_comineq_ss(a, b)             Rt_mm_comineq_ss(a, b)
#define _mm_ucomieq_ss(a, b)             Rt_mm_ucomieq_ss(a, b)
#define _mm_ucomilt_ss(a, b)             Rt_mm_ucomilt_ss(a, b)
#define _mm_ucomile_ss(a, b)             Rt_mm_ucomile_ss(a, b)
#define _mm_ucomigt_ss(a, b)             Rt_mm_ucomigt_ss(a, b)
#define _mm_ucomige_ss(a, b)             Rt_mm_ucomige_ss(a, b)
#define _mm_ucomineq_ss(a, b)            Rt_mm_ucomineq_ss(a, b)

/*
 * Conversion Operations
 */

#define _mm_cvt_ss2si(a)                 Rt_mm_cvt_ss2si(a)
#define _mm_cvt_ps2pi(a)                 Rt_mm_cvt_ps2pi(a)
#define _mm_cvtt_ss2si(a)                Rt_mm_cvtt_ss2si(a)
#define _mm_cvtt_ps2pi(a)                Rt_mm_cvtt_ps2pi(a)
#define _mm_cvt_si2ss(a, b)              Rt_mm_cvt_si2ss(a, b)
#define _mm_cvt_pi2ps(a, b)              Rt_mm_cvt_pi2ps(a, b)

/*
 *     Miscellaneous
 */

#define _mm_shuffle_ps(a, b, i)          Rt_mm_shuffle_ps(a, b, i)
#define _mm_unpackhi_ps(a, b)            Rt_mm_unpackhi_ps(a, b)
#define _mm_unpacklo_ps(a, b)            Rt_mm_unpacklo_ps(a, b)
#define _mm_loadh_pi(a, p)               Rt_mm_loadh_pi(a, p)
#define _mm_storeh_pi(p, a)              Rt_mm_storeh_pi(p, a)
#define _mm_movehl_ps(a, b)              Rt_mm_movehl_ps(a, b)
#define _mm_movelh_ps(a, b)              Rt_mm_movelh_ps(a, b)
#define _mm_loadl_pi(a, p)               Rt_mm_loadl_pi(a, p)
#define _mm_storel_pi(p, a)              Rt_mm_storel_pi(p, a)
#define _mm_movemask_ps(a)               Rt_mm_movemask_ps(a)
#define _mm_getcsr()                     Rt_mm_getcsr()
#define _mm_setcsr(i)                    Rt_mm_setcsr(i)

/*
 *Load Operations
 */

#define _mm_load_ss(p)                  Rt_mm_load_ss(p)
#define _mm_load_ps1(p)                 Rt_mm_load_ps1(p)
#define _mm_load_ps(p)                  Rt_mm_load_ps(p)
#define _mm_loadu_ps(p)                 Rt_mm_loadu_ps(p)
#define _mm_loadr_ps(p)                 Rt_mm_loadr_ps(p)

/*
 * Set Operations
 */

#define _mm_set_ss(w)                   Rt_mm_set_ss(w)
#define _mm_set_ps1(w)                  Rt_mm_set_ps1(w)
#define _mm_set_ps(z, y, x, w)          Rt_mm_set_ps(z, y, x, w)
#define _mm_setr_ps(z, y, x, w)         Rt_mm_setr_ps(z, y, x, w)
#define _mm_setzero_ps()                Rt_mm_setzero_ps()

/*
 * Store Operations
 */

#define _mm_store_ss(p, a)              Rt_mm_store_ss(p, a)
#define _mm_store_ps1(p, a)             Rt_mm_store_ps1(p, a)
#define _mm_store_ps(p, a)              Rt_mm_store_ps(p, a)
#define _mm_storeu_ps(p, a)             Rt_mm_storeu_ps(p, a)
#define _mm_storer_ps(p, a)             Rt_mm_storer_ps(p, a)
#define _mm_move_ss(a, b)               Rt_mm_move_ss(a, b)

/*
 * Integer Intrinsics
 */

#define _m_pextrw(a, n)                 Rt_m_pextrw(a, n)
#define _m_pinsrw(a, d, n)              Rt_m_pinsrw(a, d, n)
#define _m_pmaxsw(a, b)                 Rt_m_pmaxsw(a, b)
#define _m_pmaxub(a, b)                 Rt_m_pmaxub(a, b)
#define _m_pminsw(a, b)                 Rt_m_pminsw(a, b)
#define _m_pminub(a, b)                 Rt_m_pminub(a, b)
#define _m_pmovmskb(a)                  Rt_m_pmovmskb(a)
#define _m_pmulhuw(a, b)                Rt_m_pmulhuw(a, b)
#define _m_pshufw(a, n)                 Rt_m_pshufw(a, n)
#define _m_lwmaskmovq(d, n, p)          Rt_m_lwmaskmovq(d, n, p)

/*
 * Cacheability Support
 */

#define _mm_prefetch(p, i)              Rt_mm_prefetch(p, i)
#define _mm_stream_pi(p, a)             Rt_mm_stream_pi(p, a)
#define _mm_stream_ps(p, a)             Rt_mm_stream_ps(p, a)
#define _mm_sfence()                    Rt_mm_sfence()

#endif /* (defined(RWEMULATEINTELSIMD) || !defined(__ICL)) */

#endif /* RTINTEL_H */
