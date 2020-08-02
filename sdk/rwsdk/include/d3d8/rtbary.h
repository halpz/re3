/***************************************************************************
 *                                                                         *
 * Module  : rtbary.h                                                      *
 *                                                                         *
 * Purpose : Barycentric operations                                        *
 *                                                                         *
 **************************************************************************/

#ifndef RTBARY_H
#define RTBARY_H

/**
 * \defgroup rtbary RtBary
 * \ingroup mathtools
 *
 * Barycentric Toolkit for RenderWare.
 */


/****************************************************************************
 Includes
 */

#include <rwcore.h>

#include <rtbary.rpe>          /* automatically generated header file */


/****************************************************************************
 Global types
 */

/**
 * \ingroup rtbary
 * \ref RtBaryV4d
 * typedef for the 4 element homogeneous row of a transform matrix mapping 
 * a point from Cartesian space to the barycentric space defined by a triangle.
 */
typedef RwReal      RtBaryV4d[4];

/**
 * \ingroup rtbary
 * \ref RtBaryTransform
 * typedef for the 4x4 homogeneous transform matrix mapping a point
 * from Cartesian space to the barycentric space defined by a triangle.
 */
typedef RtBaryV4d   RtBaryTransform[4];

/****************************************************************************
 Defines
 */

#define RtBaryV3dFromWeightsMacro(_out, _b, _v0, _v1, _v2)      \
MACRO_START                                                     \
{                                                               \
    (_out)->x = (RwReal)( ((_v0)->x * (_b)[0]) +                \
                          ((_v1)->x * (_b)[1]) +                \
                          ((_v2)->x * (_b)[2]) );               \
    (_out)->y = (RwReal)( ((_v0)->y * (_b)[0]) +                \
                          ((_v1)->y * (_b)[1]) +                \
                          ((_v2)->y * (_b)[2]) );               \
    (_out)->z = (RwReal)( ((_v0)->z * (_b)[0]) +                \
                          ((_v1)->z * (_b)[1]) +                \
                          ((_v2)->z * (_b)[2]) );               \
}                                                               \
MACRO_STOP

#define RtBaryWeightsFromV3dMacro(_out, _m, _in)        \
MACRO_START                                             \
{                                                       \
    (_out)[0] = ( (_m)[0][0] * (_in)->x +               \
                  (_m)[1][0] * (_in)->y +               \
                  (_m)[2][0] * (_in)->z +               \
                  (_m)[3][0] );                         \
    (_out)[1] = ( (_m)[0][1] * (_in)->x +               \
                  (_m)[1][1] * (_in)->y +               \
                  (_m)[2][1] * (_in)->z +               \
                  (_m)[3][1] );                         \
    (_out)[2] = ( (_m)[0][2] * (_in)->x +               \
                  (_m)[1][2] * (_in)->y +               \
                  (_m)[2][2] * (_in)->z +               \
                  (_m)[3][2] );                         \
    (_out)[3] = ( (_m)[0][3] * (_in)->x +               \
                  (_m)[1][3] * (_in)->y +               \
                  (_m)[2][3] * (_in)->z +               \
                  (_m)[3][3] );                         \
}                                                       \
MACRO_STOP

#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))

#define RtBaryV3dFromWeights(_out, _b, _v0, _v1, _v2)     \
        RtBaryV3dFromWeightsMacro(_out, _b, _v0, _v1, _v2)

#define RtBaryWeightsFromV3d(_out, _m, _in)               \
        RtBaryWeightsFromV3dMacro(_out, _m, _in)

#endif /* (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwBool
RtBaryGetTransform(RtBaryTransform m,
                   RwReal * const area,
                   const RwV3d * const v0,
                   const RwV3d * const v1,
                   const RwV3d * const v2);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )

extern void
RtBaryV3dFromWeights(RwV3d * const out,
                     const RtBaryV4d weights,
                     const RwV3d * const v0, 
                     const RwV3d * const v1, 
                     const RwV3d * const v2);

extern void
RtBaryWeightsFromV3d(RtBaryV4d out,
                        RtBaryTransform mat,
                        const RwV3d * const in);

extern void
_rtImportWorldBaryFromEdge(RtBaryV4d out,
                           RtBaryTransform mat,
                           const RwV3d * const in);

#endif   /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RTBARY_H */
