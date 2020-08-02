/***************************************************************************
 *                                                                         *
 * Module  : rtintsec.h                                                    *
 *                                                                         *
 * Purpose : Intersection tests on geometry primitives.                    *
 *                                                                         *
 **************************************************************************/

#ifndef RTINTSEC_H
#define RTINTSEC_H

/**
 * \defgroup rtintersection RtIntersection
 * \ingroup mathtools
 *
 * Object Intersection Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include <rwcore.h>
#include "rtintsec.rpe"    /* automatically generated header file */

/****************************************************************************
 Defines
 */

#define RTINTSECEPSILON (RwReal)(1e-8)
#define RTINTSECEDGEEPS (RwReal)(1e-5)

#define RtIntersectionLineTriangleMacro(_result,                        \
                                     _lineStart, _lineDelta,            \
                                     _v0, _v1, _v2,                     \
                                     _distance)                         \
MACRO_START                                                             \
{                                                                       \
    RwV3d               edge1, edge2, tVec, pVec, qVec;                 \
    RwReal              det;                                            \
                                                                        \
    /* Find vectors for two edges sharing vert0 */                      \
    RwV3dSubMacro(&edge1, (_v1), (_v0));                                \
    RwV3dSubMacro(&edge2, (_v2), (_v0));                                \
                                                                        \
    /* Begin calculating determinant                                    \
     * - also used to calculate U parameter */                          \
    RwV3dCrossProductMacro(&pVec, (_lineDelta), &edge2);                \
                                                                        \
    /* If determinant is                                                \
     * + near zero, ray lies in plane of                                \
     *   triangle                                                       \
     * + negative, triangle is backfacing                               \
     */                                                                 \
    det = RwV3dDotProductMacro(&edge1, &pVec);                          \
    (_result) = (det > RTINTSECEPSILON);                                \
                                                                        \
    if ((_result))                                                      \
    {                                                                   \
        RwReal  lo, hi, u;                                              \
                                                                        \
        /* Calculate bounds for parameters with tolerance */            \
        lo = - det*RTINTSECEDGEEPS;                                     \
        hi = det - lo;                                                  \
                                                                        \
        /* Calculate U parameter and test bounds */                     \
        RwV3dSubMacro(&tVec, (_lineStart), (_v0));                      \
        u = RwV3dDotProductMacro(&tVec, &pVec);                         \
        (_result) =  (u >= lo && u <= hi);                              \
                                                                        \
        if ((_result))                                                  \
        {                                                               \
            RwReal  v;                                                  \
                                                                        \
            /* Calculate V parameter and test bounds */                 \
            RwV3dCrossProductMacro(&qVec, &tVec, &edge1);               \
            v = RwV3dDotProductMacro((_lineDelta), &qVec);              \
            (_result) = (v >= lo && (u + v) <= hi);                     \
                                                                        \
            if ((_result))                                              \
            {                                                           \
                /* Calculate t,                                         \
                 * and make sure intersection is in bounds of line */   \
                *(_distance) = RwV3dDotProductMacro(&edge2, &qVec);     \
                                                                        \
                /* Within bounds of line? */                            \
                (_result) = (*(_distance) >= lo && *(_distance) <= hi); \
                                                                        \
                if ((_result))                                          \
                {                                                       \
                    *(_distance) = ((*(_distance)) / (det));            \
                }                                                       \
            }                                                           \
        }                                                               \
    }                                                                   \
}                                                                       \
MACRO_STOP


/****************************************************************************
 Global Types
 */


/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Line intersections */
extern RwBool
RtIntersectionLineTriangle(RwV3d *lineStart, RwV3d *lineDelta,
                        RwV3d *v0, RwV3d *v1, RwV3d *v2, 
                        RwReal *distance);

/* Sphere intersections */
extern RwBool
RtIntersectionSphereTriangle(RwSphere *sphere, 
                          RwV3d  *v0, RwV3d *v1, RwV3d *v2,
                          RwV3d  *normal,
                          RwReal *distance);

/* BBox intersections */
extern RwBool
RtIntersectionBBoxTriangle(RwBBox *bbox, RwV3d *v0, RwV3d *v1, RwV3d *v2);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RTINTSEC_H */
