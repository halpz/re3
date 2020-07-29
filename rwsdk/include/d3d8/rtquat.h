/*
 * Data structures for Quaternions
 * See http://www-groups.dcs.st-and.ac.uk/~history/Mathematicians/Hamilton.html
 *
 * Copyright (c) Criterion Software Limited
 */

#ifndef RTQUAT_H
#define RTQUAT_H

/**
 * \defgroup rtquat RtQuat
 * \ingroup mathtools
 *
 * Quaternion Toolkit for RenderWare.
 *
 * See also http://www.gamasutra.com/features/19980703/quaternions_01.htm
 */

/*
 * See http://www-groups.dcs.st-and.ac.uk/~history/Mathematicians/Hamilton.html
 * On 16 October 1843 (a Monday) Hamilton was walking in along the Royal
 * Canal with his wife to preside at a Council meeting of the Royal Irish
 * Academy.
 * 
 * Although his wife talked to him now and again Hamilton hardly
 * heard, for the discovery of the quaternions, the first noncommutative
 * algebra to be studied, was taking shape in his mind:-
 * 
 *    "And here there dawned on me the notion that we must admit, in
 *     some sense, a fourth dimension of space for the purpose of calculating
 *     with triples ...  An electric circuit seemed to close, and a spark
 *     flashed forth."
 */


/****************************************************************************
 Includes
 */

#include <math.h>
/* renderware */
#include "rwcore.h"

#include "rtquat.rpe"          /* automatically generated header file */

#define RW_TOL_ORTHONORMAL  ((RwReal)0.01)

/****************************************************************************
 Global Types
 */


typedef struct RtQuat RtQuat;
/**
 * \ingroup rtquat
 * \struct RtQuat 
 * A structure describing a Quaternion
 *
*/ 
struct RtQuat
{
    RwV3d               imag;   /**< The imaginary part(s) */
    RwReal              real;   /**< The real part */
};


/****************************************************************************
 Defines
 */

#define RtQuatInitMacro( result, _x, _y, _z, _w)                           \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (_w);                                                 \
    (result)->imag.x = (_x);                                               \
    (result)->imag.y = (_y);                                               \
    (result)->imag.z = (_z);                                               \
}                                                                          \
MACRO_STOP

#if (!defined(RtQuatAssignMacro))
#define RtQuatAssignMacro(_target, _source)            \
    ( *(_target) = *(_source) )
#endif /* (!defined(RtQuatAssignMacro)) */

#define RtQuatAddMacro( result, q1, q2 )                                   \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q1)->real + (q2)->real;                              \
    RwV3dAddMacro(&(result)->imag, &(q1)->imag, &(q2)->imag);              \
}                                                                          \
MACRO_STOP

#define RtQuatIncrementRealPartMacro(result, s, q)                         \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q)->real + s;                                        \
    (result)->imag.x = (q)->imag.x;                                        \
    (result)->imag.y = (q)->imag.y;                                        \
    (result)->imag.z = (q)->imag.z;                                        \
}                                                                          \
MACRO_STOP

#define RtQuatDecrementRealPartMacro(result, s, q)                         \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q)->real - s;                                        \
    (result)->imag.x = (q)->imag.x;                                        \
    (result)->imag.y = (q)->imag.y;                                        \
    (result)->imag.z = (q)->imag.z;                                        \
}                                                                          \
MACRO_STOP

#define RtQuatIncrementMacro( result, dq )                                 \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (result)->real + (dq)->real;                          \
    RwV3dAddMacro(&(result)->imag, &(result)->imag, &(dq)->imag);          \
}                                                                          \
MACRO_STOP

#define RtQuatSubMacro( result, q1, q2 )                                   \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q1)->real - (q2)->real;                              \
    RwV3dSubMacro(&(result)->imag, &(q1)->imag, &(q2)->imag);              \
}                                                                          \
MACRO_STOP

#define RtQuatNegateMacro( result, q )                                     \
MACRO_START                                                                \
{                                                                          \
    (result)->real = -(q)->real;                                           \
    (result)->imag.x = -(q)->imag.x;                                       \
    (result)->imag.y = -(q)->imag.y;                                       \
    (result)->imag.z = -(q)->imag.z;                                       \
}                                                                          \
MACRO_STOP

#define RtQuatConjugateMacro( result, q)                                   \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q)->real;                                            \
    (result)->imag.x = -(q)->imag.x;                                       \
    (result)->imag.y = -(q)->imag.y;                                       \
    (result)->imag.z = -(q)->imag.z;                                       \
}                                                                          \
MACRO_STOP

#define RtQuatScaleMacro(result, q, scale )                                \
MACRO_START                                                                \
{                                                                          \
    (result)->real = (q)->real * scale;                                    \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, scale);                   \
}                                                                          \
MACRO_STOP

#define RtQuatModulusSquaredMacro( q )                                     \
    ((q)->real * (q)->real +                                               \
     RwV3dDotProductMacro(&(q)->imag, &(q)->imag))

#define RtQuatModulusMacro( result, q )         \
MACRO_START                                     \
{                                               \
    (result) = RtQuatModulusSquaredMacro(q);    \
    rwSqrtMacro(&result, result);               \
}                                               \
MACRO_STOP

#define RtQuatMultiplyMacro( result, q1, q2)                               \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes q1 != result != q2                                          \
     */                                                                    \
    (result)->real =                                                       \
        (q1)->real * (q2)->real -                                          \
        RwV3dDotProductMacro(&(q1)->imag,&(q2)->imag);                     \
    RwV3dCrossProductMacro(&(result)->imag, &(q1)->imag, &(q2)->imag);     \
    RwV3dIncrementScaledMacro(&(result)->imag, &(q2)->imag, (q1)->real);   \
    RwV3dIncrementScaledMacro(&(result)->imag, &(q1)->imag, (q2)->real);   \
}                                                                          \
MACRO_STOP

#define RtQuatReciprocalMacro( result, q)                                  \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     */                                                                    \
    RwReal              val = RtQuatModulusSquaredMacro(q);                \
                                                                           \
    if (val > (RwReal) 0)                                                  \
    {                                                                      \
        val = ((RwReal)1) / val;                                           \
        (result)->real = (q)->real * val;                                  \
        val = -val;                                                        \
        RwV3dScaleMacro(&(result)->imag, &(q)->imag, val);                 \
    }                                                                      \
}                                                                          \
MACRO_STOP

#define RtQuatSquareMacro( result, q )                                     \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     */                                                                    \
    RwReal val = ((RwReal)2) * (q)->real ;                                 \
                                                                           \
    (result)->real =                                                       \
        (q)->real * (q)->real -                                            \
         RwV3dDotProductMacro(&(q)->imag, &(q)->imag);                     \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, val);                     \
}                                                                          \
MACRO_STOP

#define RtQuatSquareRootMacro( result, q )                                 \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     * other root is of course -result                                     \
     */                                                                    \
    RwReal              val;                                               \
                                                                           \
    RtQuatModulusMacro(val,q);                                             \
    val = ((q)->real + val) * ((RwReal) 0.5);                              \
                                                                           \
    if (val > ((RwReal)0))                                                 \
    {                                                                      \
        rwSqrtMacro(&val, val);                                            \
        (result)->real = val;                                              \
        val = ((RwReal)0.5) / val;                                         \
        RwV3dScale(&(result)->imag, &(q)->imag, val);                      \
    }                                                                      \
    else                                                                   \
    {                                                                      \
        result->imag.x = -(q)->real;                                       \
        rwSqrtMacro(&(result->imag.x), result->imag.x);                    \
        result->imag.y = ((RwReal)0);                                      \
        result->imag.x = ((RwReal)0);                                      \
        result->real   = ((RwReal)0);                                      \
    }                                                                      \
}                                                                          \
MACRO_STOP

#define RtQuatLogMacro(result, q)                                          \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     */                                                                    \
    const RwReal        mod2 = RtQuatModulusSquaredMacro(q);               \
    RwReal              sin_b;                                             \
    RwReal              radians;                                           \
    RwReal              factor;                                            \
                                                                           \
    sin_b = RwV3dDotProduct(&(q)->imag, &(q)->imag);                       \
    rwSqrtMacro(&sin_b, sin_b);                                            \
    radians = (RwReal) RwATan2(sin_b, (q)->real);                          \
    factor = (sin_b > (RwReal) 0) ? (((RwReal)radians) / sin_b) : 0 ;      \
                                                                           \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, factor);                  \
    (result)->real = ((RwReal) RwLog(mod2)) * ((RwReal) 0.5);              \
                                                                           \
}                                                                          \
MACRO_STOP

#define RtQuatExpMacro(result, q)                                          \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     */                                                                    \
    const RwReal        exp_a = (RwReal)RwExp((q)->real);                  \
    RwReal              mod_b;                                             \
    RwReal              factor;                                            \
                                                                           \
    mod_b = RwV3dDotProduct(&(q)->imag, &(q)->imag);                       \
    rwSqrtMacro(&mod_b, mod_b);                                            \
    factor = ( (mod_b > (RwReal) 0) ?                                      \
               (exp_a * ((RwReal)RwSin(mod_b)) / mod_b) :                  \
               0 ) ;                                                       \
                                                                           \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, factor);                  \
    (result)->real = exp_a * (RwReal)RwCos(mod_b);                         \
}                                                                          \
MACRO_STOP

#define RtQuatPowMacro( result, q, e)                                      \
MACRO_START                                                                \
{                                                                          \
    RtQuat qLog;                                                           \
                                                                           \
    RtQuatLogMacro(&qLog, q);                                              \
    RtQuatScaleMacro(&qLog, &qLog, e);                                     \
    RtQuatExpMacro(result, &qLog);                                         \
}                                                                          \
MACRO_STOP

#define RtQuatUnitLogMacro(result, q)                                     \
MACRO_START                                                               \
{                                                                         \
    /*                                                                    \
     * Assumes result != q                                                \
     */                                                                   \
    RwReal              sin_b ;                                           \
    RwReal              radians ;                                         \
    RwReal              factor ;                                          \
                                                                          \
    sin_b =  RwV3dDotProduct(&(q)->imag, &(q)->imag);                     \
    rwSqrtMacro(&sin_b, sin_b);                                           \
    radians = (RwReal)RwATan2(sin_b, (q)->real);                          \
    factor = (sin_b > (RwReal) 0) ? (((RwReal)radians) / sin_b) : 0 ;     \
                                                                          \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, factor);                 \
    (result)->real = (RwReal)0;                                           \
                                                                          \
}                                                                         \
MACRO_STOP

#define RtQuatUnitExpMacro(result, q)                                      \
MACRO_START                                                                \
{                                                                          \
    /*                                                                     \
     * Assumes result != q                                                 \
     */                                                                    \
    RwReal              mod_b;                                             \
    RwReal             factor;                                             \
                                                                           \
    mod_b =  RwV3dDotProduct(&(q)->imag, &(q)->imag);                      \
    rwSqrtMacro(&mod_b, mod_b);                                            \
    factor = (mod_b > (RwReal) 0) ? (((RwReal)RwSin(mod_b)) / mod_b) : 0 ; \
                                                                           \
    RwV3dScaleMacro(&(result)->imag, &(q)->imag, factor);                  \
    (result)->real = (RwReal)RwCos(mod_b);                                 \
                                                                           \
}                                                                          \
MACRO_STOP

#define RtQuatUnitPowMacro( result, q, e)                                  \
MACRO_START                                                                \
{                                                                          \
    RtQuat qLog;                                                           \
                                                                           \
    RtQuatUnitLogMacro(&qLog, q);                                          \
    RwV3dScaleMacro(&qLog.imag, &qLog.imag, e);                            \
    RtQuatUnitExpMacro(result, &qLog);                                     \
}                                                                          \
MACRO_STOP

#define RtQuatConvertToMatrixMacro(qpQuat, mpMatrix)                       \
MACRO_START                                                                \
{                                                                          \
    RwReal              rS;                                                \
    RwV3d               rV;                                                \
    RwV3d               rW;                                                \
    RwV3d               square;                                            \
    RwV3d               cross;                                             \
                                                                           \
    rS = ((RwReal) 2) / RtQuatModulusSquaredMacro((qpQuat));               \
                                                                           \
    RwV3dScale(&rV, &(qpQuat)->imag, rS);                                  \
    RwV3dScale(&rW, &rV, (qpQuat)->real);                                  \
                                                                           \
    square.x = (qpQuat)->imag.x * rV.x;                                    \
    square.y = (qpQuat)->imag.y * rV.y;                                    \
    square.z = (qpQuat)->imag.z * rV.z;                                    \
                                                                           \
    cross.x = (qpQuat)->imag.y * rV.z;                                     \
    cross.y = (qpQuat)->imag.z * rV.x;                                     \
    cross.z = (qpQuat)->imag.x * rV.y;                                     \
                                                                           \
    (mpMatrix)->right.x = ((RwReal) 1) - (square.y + square.z);            \
    (mpMatrix)->right.y = cross.z + rW.z;                                  \
    (mpMatrix)->right.z = cross.y - rW.y;                                  \
                                                                           \
    (mpMatrix)->up.x = cross.z - rW.z;                                     \
    (mpMatrix)->up.y = ((RwReal) 1) - (square.z + square.x);               \
    (mpMatrix)->up.z = cross.x + rW.x;                                     \
                                                                           \
    (mpMatrix)->at.x = cross.y + rW.y;                                     \
    (mpMatrix)->at.y = cross.x - rW.x;                                     \
    (mpMatrix)->at.z = ((RwReal) 1) - (square.x + square.y);               \
                                                                           \
    /* Set position */                                                     \
    (mpMatrix)->pos.x = ((RwReal) 0);                                      \
    (mpMatrix)->pos.y = ((RwReal) 0);                                      \
    (mpMatrix)->pos.z = ((RwReal) 0);                                      \
                                                                           \
    /* Matrix is orthogonal */                                             \
    rwMatrixSetFlags((mpMatrix),                                           \
                      (rwMATRIXTYPEORTHOGONAL  &                           \
                       ~rwMATRIXINTERNALIDENTITY) );                       \
                                                                           \
}                                                                          \
MACRO_STOP

#define RtQuatUnitConvertToMatrixMacro(qpQuat, mpMatrix)                   \
MACRO_START                                                                \
{                                                                          \
    const RwReal        x = (qpQuat)->imag.x;                              \
    const RwReal        y = (qpQuat)->imag.y;                              \
    const RwReal        z = (qpQuat)->imag.z;                              \
    const RwReal        w = (qpQuat)->real;                                \
    RwV3d               square;                                            \
    RwV3d               cross;                                             \
    RwV3d               wimag;                                             \
                                                                           \
    square.x = x * x;                                                      \
    square.y = y * y;                                                      \
    square.z = z * z;                                                      \
                                                                           \
    cross.x = y * z;                                                       \
    cross.y = z * x;                                                       \
    cross.z = x * y;                                                       \
                                                                           \
    wimag.x = w * x;                                                       \
    wimag.y = w * y;                                                       \
    wimag.z = w * z;                                                       \
                                                                           \
    (mpMatrix)->right.x = 1 - 2 * (square.y + square.z);                   \
    (mpMatrix)->right.y = 2 * (cross.z + wimag.z);                         \
    (mpMatrix)->right.z = 2 * (cross.y - wimag.y);                         \
                                                                           \
    (mpMatrix)->up.x = 2 * (cross.z - wimag.z);                            \
    (mpMatrix)->up.y = 1 - 2 * (square.x + square.z);                      \
    (mpMatrix)->up.z = 2 * (cross.x + wimag.x);                            \
                                                                           \
    (mpMatrix)->at.x = 2 * (cross.y + wimag.y);                            \
    (mpMatrix)->at.y = 2 * (cross.x - wimag.x);                            \
    (mpMatrix)->at.z = (1 - 2 * (square.x + square.y));                    \
                                                                           \
    /* Set position */                                                     \
    (mpMatrix)->pos.x = ((RwReal) 0);                                      \
    (mpMatrix)->pos.y = ((RwReal) 0);                                      \
    (mpMatrix)->pos.z = ((RwReal) 0);                                      \
                                                                           \
    /* Matrix is orthonormal */                                            \
    rwMatrixSetFlags((mpMatrix),                                           \
                      (rwMATRIXTYPEORTHONORMAL  &                          \
                       ~rwMATRIXINTERNALIDENTITY) );                       \
}                                                                          \
MACRO_STOP

#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))

#define RtQuatInit( result, _x, _y, _z, _w)                                \
    RtQuatInitMacro( result, _x, _y, _z, _w)

#define RtQuatAssign( to, from )                                           \
    RtQuatAssignMacro( to, from )

#define RtQuatAdd( result, q1, q2 )                                        \
    RtQuatAddMacro( result, q1, q2 )

#define RtQuatIncrementRealPart(result, s, q)                              \
    RtQuatIncrementRealPartMacro(result, s, q)

#define RtQuatDecrementRealPart(result, s, q)                              \
    RtQuatDecrementRealPartMacro(result, s, q)

#define RtQuatIncrement( result, dq )                                      \
    RtQuatIncrementMacro( result, dq )

#define RtQuatSub( result, q1, q2 )                                        \
    RtQuatSubMacro( result, q1, q2 )

#define RtQuatNegate( result, q )                                          \
    RtQuatNegateMacro( result, q )

#define RtQuatConjugate( result, q)                                        \
    RtQuatConjugateMacro( result, q)

#define RtQuatScale(result, q, scale )                                     \
    RtQuatScaleMacro(result, q, scale )

#define RtQuatModulusSquared( q )                                          \
    RtQuatModulusSquaredMacro( q )

#define RtQuatMultiply( result, q1, q2)                                    \
    RtQuatMultiplyMacro( result, q1, q2)

#define RtQuatReciprocal( result, q)                                       \
    RtQuatReciprocalMacro( result, q)

#define RtQuatSquare( result, q )                                          \
    RtQuatSquareMacro( result, q )

#define RtQuatSquareRoot( result, q )                                      \
    RtQuatSquareRootMacro( result, q )

#define RtQuatLog( result, q )                                             \
    RtQuatLogMacro( result, q )

#define RtQuatExp( result, q )                                             \
    RtQuatExpMacro( result, q )

#define RtQuatPow( result, q, e )                                          \
    RtQuatPowMacro( result, q, e )

#define RtQuatUnitLog( result, q )                                         \
    RtQuatUnitLogMacro( result, q )

#define RtQuatUnitExp( result, q )                                         \
    RtQuatUnitExpMacro( result, q )

#define RtQuatUnitPow( result, q, e )                                      \
    RtQuatUnitPowMacro( result, q, e )

#define RtQuatConvertToMatrix(qpQuat, mpMatrix)                            \
    RtQuatConvertToMatrixMacro(qpQuat, mpMatrix)    

#define RtQuatUnitConvertToMatrix(qpQuat, mpMatrix)                        \
    RtQuatUnitConvertToMatrixMacro(qpQuat, mpMatrix)    

#endif /* (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )) */

/****************************************************************************
 Function prototypes
 */
#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwBool
RtQuatConvertFromMatrix(RtQuat * const qpQuat,
                        const RwMatrix * const mpMatrix);

extern RtQuat             *
RtQuatRotate(RtQuat * quat,
             const RwV3d * axis, 
             RwReal angle, 
             RwOpCombineType combineOp);

extern const RtQuat     *
RtQuatQueryRotate(const RtQuat *quat, 
                  RwV3d * unitAxis, 
                  RwReal * angle);

extern RwV3d *
RtQuatTransformVectors(RwV3d * vectorsOut,
                       const RwV3d * vectorsIn,
                       const RwInt32 numPoints,
                       const RtQuat *quat);

extern RwReal
RtQuatModulus(RtQuat * q);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )

extern void
RtQuatInit(RtQuat * result, RwReal x, RwReal y, RwReal z, RwReal w);

extern void
RtQuatAssign(RtQuat * to, RtQuat * from);

extern void
RtQuatAdd(RtQuat * result, RtQuat * q1, RtQuat * q2);

extern void
RtQuatIncrementRealPart(RtQuat * result, RwReal s, RtQuat * q);

extern void
RtQuatDecrementRealPart(RtQuat * result, RwReal s, RtQuat * q);

extern void
RtQuatIncrement(RtQuat * result, RtQuat * dq);

extern void
RtQuatSub(RtQuat * result, RtQuat * q1, RtQuat * q2);

extern void
RtQuatNegate(RtQuat * result, RtQuat * q);

extern void
RtQuatConjugate(RtQuat * result, RtQuat * q);

extern void
RtQuatScale(RtQuat * result, RtQuat * q, RwReal scale);

extern RwReal
RtQuatModulusSquared(RtQuat * q);

extern void
RtQuatMultiply(RtQuat * result, RtQuat * q1, RtQuat * q2);

extern void
RtQuatReciprocal(RtQuat * result, RtQuat * q);

extern void
RtQuatSquare(RtQuat * result, RtQuat * q);

extern void
RtQuatSquareRoot(RtQuat * result, RtQuat * q);

extern void
RtQuatLog(RtQuat * result, RtQuat * q);

extern void
RtQuatExp(RtQuat * result, RtQuat * q);

extern void
RtQuatPow(RtQuat * result, RtQuat * q, RwReal e);

extern void
RtQuatUnitLog(RtQuat * result, RtQuat * q);

extern void
RtQuatUnitExp(RtQuat * result, RtQuat * q);

extern void
RtQuatUnitPow(RtQuat * result, RtQuat * q, RwReal e);

extern void
RtQuatConvertToMatrix(const RtQuat * const qpQuat,
                      RwMatrix * const mpMatrix);

extern void
RtQuatUnitConvertToMatrix(const RtQuat * const qpQuat,
                          RwMatrix * const mpMatrix);

#endif /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*
 * Backwards compatibility code
 */

typedef RtQuat RpQuat;

#define RpAnimQuatConvertFromMatrix(qpQuat, mpMatrix)                      \
    RtQuatConvertFromMatrix(qpQuat, mpMatrix)

#define RpAnimQuatConvertToMatrix(qpQuat,mpMatrix)                         \
    RtQuatUnitConvertToMatrix(qpQuat,mpMatrix)


#endif                          /* RTQUAT_H */

