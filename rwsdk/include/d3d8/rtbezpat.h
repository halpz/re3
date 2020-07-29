/*
 * Data structures for rtbezpat toolkit
 * Copyright (c) Criterion Software Limited
 */

#if (!defined(RTBEZPAT_H))
#define RTBEZPAT_H

/**
 * \defgroup rtbezpatch RtBezPat
 * \ingroup mathtools
 *
 * The Bezier Patch Toolkit is a group of functions that support the way
 * RenderWare processes patches.
 */

typedef struct RtBezierV4d RtBezierV4d;

/**
 * \ingroup rtbezpatch
 * \struct RtBezierV4d
 *  This type represents 4d points and vectors specified by
 * the (x, y, z, w) coordinates of a 4d point or
 * the (x, y, z, w) components of a 4d vector.
 */
struct RtBezierV4d
{
    RwReal              x;
                /**< X value */
    RwReal              y;
                /**< Y value */
    RwReal              z;
                /**< Z value */
    RwReal              w;
                /**< W value */
};

/**
 * \ingroup rtbezpatch
 * \ref RtBezierRow
 *  typedef for a row of vectors.
 * RtBezierRow is an  array of 4 vectors
 */
typedef RtBezierV4d RtBezierRow[4];

/**
 * \ingroup rtbezpatch
 * \ref RtBezierMatrix
 *  typedef for a matrix of 4*4 vectors.
 *  RtBezierMatrix is an array of 4 rows.
 */
typedef RtBezierRow RtBezierMatrix[4];

/*
 * Bernstein polynomials;
 */

#define RtBern03(_u, _cu) ( (_cu) * (_cu) * (_cu) )
#define RtBern13(_u, _cu) ( 3 * (_u) * (_cu) * (_cu) )
#define RtBern23(_u, _cu) ( 3 * (_u) * (_u) * (_cu) )
#define RtBern33(_u, _cu) ( (_u) * (_u) * (_u) )

#define RtBezierQuadSample3dMacro(_out, _P, _u, _v)                     \
MACRO_START                                                             \
{                                                                       \
    const RtBezierV4d       * const P0 = &(_P)[0][0];                   \
    const RtBezierV4d       * const P1 = &(_P)[1][0];                   \
    const RtBezierV4d       * const P2 = &(_P)[2][0];                   \
    const RtBezierV4d       * const P3 = &(_P)[3][0];                   \
    const RwReal              _pu = (_u);                               \
    const RwReal              _cu = ((RwReal)1) - _pu;                  \
    const RwReal              B03u = RtBern03(_pu,_cu);                 \
    const RwReal              B13u = RtBern13(_pu,_cu);                 \
    const RwReal              B23u = RtBern23(_pu,_cu);                 \
    const RwReal              B33u = RtBern33(_pu,_cu);                 \
    const RwReal              _pv = (_v);                               \
    const RwReal              _cv = ((RwReal)1) - _pv;                  \
    const RwReal              B03v = RtBern03(_pv,_cv);                 \
    const RwReal              B13v = RtBern13(_pv,_cv);                 \
    const RwReal              B23v = RtBern23(_pv,_cv);                 \
    const RwReal              B33v = RtBern33(_pv,_cv);                 \
    RtBezierRow               A;                                        \
                                                                        \
    A[0].x = B03u*P0[0].x + B13u*P1[0].x + B23u*P2[0].x + B33u*P3[0].x; \
    A[0].y = B03u*P0[0].y + B13u*P1[0].y + B23u*P2[0].y + B33u*P3[0].y; \
    A[0].z = B03u*P0[0].z + B13u*P1[0].z + B23u*P2[0].z + B33u*P3[0].z; \
    A[1].x = B03u*P0[1].x + B13u*P1[1].x + B23u*P2[1].x + B33u*P3[1].x; \
    A[1].y = B03u*P0[1].y + B13u*P1[1].y + B23u*P2[1].y + B33u*P3[1].y; \
    A[1].z = B03u*P0[1].z + B13u*P1[1].z + B23u*P2[1].z + B33u*P3[1].z; \
    A[2].x = B03u*P0[2].x + B13u*P1[2].x + B23u*P2[2].x + B33u*P3[2].x; \
    A[2].y = B03u*P0[2].y + B13u*P1[2].y + B23u*P2[2].y + B33u*P3[2].y; \
    A[2].z = B03u*P0[2].z + B13u*P1[2].z + B23u*P2[2].z + B33u*P3[2].z; \
    A[3].x = B03u*P0[3].x + B13u*P1[3].x + B23u*P2[3].x + B33u*P3[3].x; \
    A[3].y = B03u*P0[3].y + B13u*P1[3].y + B23u*P2[3].y + B33u*P3[3].y; \
    A[3].z = B03u*P0[3].z + B13u*P1[3].z + B23u*P2[3].z + B33u*P3[3].z; \
                                                                        \
    (_out)->x = A[0].x*B03v + A[1].x*B13v + A[2].x*B23v + A[3].x*B33v;  \
    (_out)->y = A[0].y*B03v + A[1].y*B13v + A[2].y*B23v + A[3].y*B33v;  \
    (_out)->z = A[0].z*B03v + A[1].z*B13v + A[2].z*B23v + A[3].z*B33v;  \
}                                                                       \
MACRO_STOP

#define RtBezierQuadDifferenceStepU3dMacro(_row)        \
MACRO_START                                             \
{                                                       \
    (_row)[0].x += (_row)[1].x;                         \
    (_row)[0].y += (_row)[1].y;                         \
    (_row)[0].z += (_row)[1].z;                         \
                                                        \
    (_row)[1].x += (_row)[2].x;                         \
    (_row)[1].y += (_row)[2].y;                         \
    (_row)[1].z += (_row)[2].z;                         \
                                                        \
    (_row)[2].x += (_row)[3].x;                         \
    (_row)[2].y += (_row)[3].y;                         \
    (_row)[2].z += (_row)[3].z;                         \
                                                        \
}                                                       \
MACRO_STOP

#define RtBezierQuadDifferenceStepU4dMacro(_row)        \
MACRO_START                                             \
{                                                       \
    (_row)[0].x += (_row)[1].x;                         \
    (_row)[0].y += (_row)[1].y;                         \
    (_row)[0].z += (_row)[1].z;                         \
    (_row)[0].w += (_row)[1].w;                         \
                                                        \
    (_row)[1].x += (_row)[2].x;                         \
    (_row)[1].y += (_row)[2].y;                         \
    (_row)[1].z += (_row)[2].z;                         \
    (_row)[1].w += (_row)[2].w;                         \
                                                        \
    (_row)[2].x += (_row)[3].x;                         \
    (_row)[2].y += (_row)[3].y;                         \
    (_row)[2].z += (_row)[3].z;                         \
    (_row)[2].w += (_row)[3].w;                         \
                                                        \
}                                                       \
MACRO_STOP

#define RtBezierQuadDifferenceStepV3dMacro(_mat)        \
MACRO_START                                             \
{                                                       \
    RtBezierV4d      * const m0 = &(_mat)[0][0];        \
    RtBezierV4d      * const m1 = &(_mat)[1][0];        \
    RtBezierV4d      * const m2 = &(_mat)[2][0];        \
    RtBezierV4d      * const m3 = &(_mat)[3][0];        \
                                                        \
    /* (_row) 0 */                                      \
    m0[0].x += m1[0].x;                                 \
    m0[0].y += m1[0].y;                                 \
    m0[0].z += m1[0].z;                                 \
                                                        \
    m0[1].x += m1[1].x;                                 \
    m0[1].y += m1[1].y;                                 \
    m0[1].z += m1[1].z;                                 \
                                                        \
    m0[2].x += m1[2].x;                                 \
    m0[2].y += m1[2].y;                                 \
    m0[2].z += m1[2].z;                                 \
                                                        \
    m0[3].x += m1[3].x;                                 \
    m0[3].y += m1[3].y;                                 \
    m0[3].z += m1[3].z;                                 \
                                                        \
    /* (_row) 1 */                                      \
    m1[0].x += m2[0].x;                                 \
    m1[0].y += m2[0].y;                                 \
    m1[0].z += m2[0].z;                                 \
                                                        \
    m1[1].x += m2[1].x;                                 \
    m1[1].y += m2[1].y;                                 \
    m1[1].z += m2[1].z;                                 \
                                                        \
    m1[2].x += m2[2].x;                                 \
    m1[2].y += m2[2].y;                                 \
    m1[2].z += m2[2].z;                                 \
                                                        \
    m1[3].x += m2[3].x;                                 \
    m1[3].y += m2[3].y;                                 \
    m1[3].z += m2[3].z;                                 \
                                                        \
    /* (_row) 2 */                                      \
    m2[0].x += m3[0].x;                                 \
    m2[0].y += m3[0].y;                                 \
    m2[0].z += m3[0].z;                                 \
                                                        \
    m2[1].x += m3[1].x;                                 \
    m2[1].y += m3[1].y;                                 \
    m2[1].z += m3[1].z;                                 \
                                                        \
    m2[2].x += m3[2].x;                                 \
    m2[2].y += m3[2].y;                                 \
    m2[2].z += m3[2].z;                                 \
                                                        \
    m2[3].x += m3[3].x;                                 \
    m2[3].y += m3[3].y;                                 \
    m2[3].z += m3[3].z;                                 \
}                                                       \
MACRO_STOP

#define RtBezierQuadDifferenceStepV4dMacro(_mat)        \
MACRO_START                                             \
{                                                       \
    RtBezierV4d      * const m0 = &(_mat)[0][0];        \
    RtBezierV4d      * const m1 = &(_mat)[1][0];        \
    RtBezierV4d      * const m2 = &(_mat)[2][0];        \
    RtBezierV4d      * const m3 = &(_mat)[3][0];        \
                                                        \
    /* (_row) 0 */                                      \
    m0[0].x += m1[0].x;                                 \
    m0[0].y += m1[0].y;                                 \
    m0[0].z += m1[0].z;                                 \
    m0[0].w += m1[0].w;                                 \
                                                        \
    m0[1].x += m1[1].x;                                 \
    m0[1].y += m1[1].y;                                 \
    m0[1].z += m1[1].z;                                 \
    m0[1].w += m1[1].w;                                 \
                                                        \
    m0[2].x += m1[2].x;                                 \
    m0[2].y += m1[2].y;                                 \
    m0[2].z += m1[2].z;                                 \
    m0[2].w += m1[2].w;                                 \
                                                        \
    m0[3].x += m1[3].x;                                 \
    m0[3].y += m1[3].y;                                 \
    m0[3].z += m1[3].z;                                 \
    m0[3].w += m1[3].w;                                 \
                                                        \
    /* (_row) 1 */                                      \
    m1[0].x += m2[0].x;                                 \
    m1[0].y += m2[0].y;                                 \
    m1[0].z += m2[0].z;                                 \
    m1[0].w += m2[0].w;                                 \
                                                        \
    m1[1].x += m2[1].x;                                 \
    m1[1].y += m2[1].y;                                 \
    m1[1].z += m2[1].z;                                 \
    m1[1].w += m2[1].w;                                 \
                                                        \
    m1[2].x += m2[2].x;                                 \
    m1[2].y += m2[2].y;                                 \
    m1[2].z += m2[2].z;                                 \
    m1[2].w += m2[2].w;                                 \
                                                        \
    m1[3].x += m2[3].x;                                 \
    m1[3].y += m2[3].y;                                 \
    m1[3].z += m2[3].z;                                 \
    m1[3].w += m2[3].w;                                 \
                                                        \
    /* (_row) 2 */                                      \
    m2[0].x += m3[0].x;                                 \
    m2[0].y += m3[0].y;                                 \
    m2[0].z += m3[0].z;                                 \
    m2[0].w += m3[0].w;                                 \
                                                        \
    m2[1].x += m3[1].x;                                 \
    m2[1].y += m3[1].y;                                 \
    m2[1].z += m3[1].z;                                 \
    m2[1].w += m3[1].w;                                 \
                                                        \
    m2[2].x += m3[2].x;                                 \
    m2[2].y += m3[2].y;                                 \
    m2[2].z += m3[2].z;                                 \
    m2[2].w += m3[2].w;                                 \
                                                        \
    m2[3].x += m3[3].x;                                 \
    m2[3].y += m3[3].y;                                 \
    m2[3].z += m3[3].z;                                 \
    m2[3].w += m3[3].w;                                 \
}                                                       \
MACRO_STOP

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */
extern void
RtBezierQuadControlFit3d(RtBezierMatrix B,
                             RtBezierMatrix P);

extern void
RtBezierQuadBernsteinWeight3d(RtBezierMatrix W,
                              RtBezierMatrix B);

extern void
RtBezierQuadBernsteinWeight4d(RtBezierMatrix W,
                              RtBezierMatrix B);

extern void
RtBezierQuadPointDifference3d(RtBezierMatrix D,
                                         RtBezierMatrix W,
                                         RwReal PointU,
                                         RwReal PointV,
                                         RwReal StepU,
                                         RwReal stepV);

extern void
RtBezierQuadPointDifference4d(RtBezierMatrix D,
                                         RtBezierMatrix W,
                                         RwReal PointU,
                                         RwReal PointV,
                                         RwReal StepU,
                                         RwReal stepV);

extern void
RtBezierQuadOriginDifference3d(RtBezierMatrix D,
                                        RtBezierMatrix W,
                                        RwReal stepU,
                                        RwReal setpV);

extern void
RtBezierQuadOriginDifference4d(RtBezierMatrix D,
                                        RtBezierMatrix W,
                                        RwReal stepU,
                                        RwReal setpV);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )

extern void
RtBezierQuadSample3d(RwV3d * out,
                         RtBezierMatrix B,
                         RwReal u,
                         RwReal v);

extern void         RtBezierQuadDifferenceStepU3d(RtBezierRow row);
extern void         RtBezierQuadDifferenceStepU4d(RtBezierRow row);

extern void         RtBezierQuadDifferenceStepV3d(RtBezierMatrix mat);
extern void         RtBezierQuadDifferenceStepV4d(RtBezierMatrix mat);


#else  /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

#define RtBezierQuadSample3d(_out, _P, _u, _v)          \
        RtBezierQuadSample3dMacro(_out, _P, _u, _v)

#define RtBezierQuadDifferenceStepU3d(_row)             \
        RtBezierQuadDifferenceStepU3dMacro(_row)

#define RtBezierQuadDifferenceStepU4d(_row)             \
        RtBezierQuadDifferenceStepU4dMacro(_row)

#define RtBezierQuadDifferenceStepV3d(_mat)             \
        RtBezierQuadDifferenceStepV3dMacro(_mat)

#define RtBezierQuadDifferenceStepV4d(_mat)             \
        RtBezierQuadDifferenceStepV4dMacro(_mat)

#endif  /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

/*
 *
 */

extern void
RtBezierTriangleControlFit3d(RtBezierMatrix T, RtBezierMatrix P);

extern void
RtBezierQuadFromTriangle(RtBezierMatrix Q, RtBezierMatrix T);

extern void
RtBezierQuadTangent(RtBezierMatrix D,
                    RwReal theta,
                    RtBezierMatrix P);

extern void
RtBezierQuadTangentPair(RtBezierMatrix Dt,
                        RtBezierMatrix Dp,
                        RwReal theta, 
                        RtBezierMatrix P);

extern void
RtBezierQuadGetNormals(RtBezierMatrix N,
                             RtBezierMatrix B);

#if (defined(RWDEBUG) && defined(RWVERBOSE))

extern void
_rtBezierGnuPlot(RtBezierMatrix B, 
                 RwChar * name,
                 RwChar * title);

#else                           /* (defined(RWDEBUG) && defined(RWVERBOSE)) */

#define _rtBezierGnuPlot(B, name, title) /* No-op */

#endif                          /* (defined(RWDEBUG) && defined(RWVERBOSE)) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* (!defined(RTBEZPAT_H)) */
