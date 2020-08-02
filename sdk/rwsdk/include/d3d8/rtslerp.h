/* 
 * Data Structures for Slerps/Spherical Linear Interpolations
 * See also GemsIII/quatspin.c in
 * http://www.acm.org/pubs/tog/GraphicsGems/gemsiii.zip
 * Copyright (c) Criterion Software Limited
 */

/***************************************************************************
 *                                                                         *
 * Module  : rtslerp.h                                                     *
 *                                                                         *
 * Purpose : Slerp functionality                                           *
 *                                                                         *
 **************************************************************************/

#ifndef RTSLERP_H
#define RTSLERP_H

/**
 * \defgroup rtslerp RtSlerp
 * \ingroup mathtools
 *
 * Slerp/Spherical Linear Interpolations Toolkit for RenderWare.
 *
 * See also http://www.cis.ohio-state.edu/~parent/book/Full.html
 */

#include "rwcore.h"
#include "rtquat.h"

/****************************************************************************
 Includes
 */

#include "rtslerp.rpe"         /* automatically generated header file */

/****************************************************************************
 Defines
 */

/* Masks for specifying which matrices to store by reference */
#define rtSLERPREFNONE          0x00
#define rtSLERPREFSTARTMAT      0x01
#define rtSLERPREFENDMAT        0x02
#define rtSLERPREFALL           (~rtSLERPREFNONE)

/****************************************************************************
 Global Types
 */


typedef struct RtSlerp RtSlerp;
/**
 * \ingroup rtslerp
 * \struct RtSlerp 
 * structure describing a Slerps/Spherical Linear Interpolations.
 * See also GemsIII/quatspin.c in
 * http://www.acm.org/pubs/tog/GraphicsGems/gemsiii.zip
 */
struct RtSlerp
{
    RwInt32             matRefMask; /**< Which matrices do we NOT own */
    RwMatrix           *startMat; /**< The start matrix */
    RwMatrix           *endMat; /**< The end matrix */
    RwV3d               axis;   /**< The axis of rotation for the slerp */
    RwReal              angle;  /**< The angle (in degrees) between src & dest */

    /* Though a slerp may be a bad idea and opting for a lerp is better */
    RwBool              useLerp; /**< Do we want to use lerps? */
};

/* static frame sequence animation - contains no state */


typedef struct RtQuatSlerpCache RtQuatSlerpCache;
/**
 * \ingroup rtslerp
 * \struct RtQuatSlerpCache 
 *  structure describing a SlerpCache,
 *  which should be initialized with \ref RtQuatSetupSlerpCache.
 */
struct RtQuatSlerpCache
{
    RtQuat              raFrom; /**< Scaled initial quaternion  */
    RtQuat              raTo;   /**< Scaled final quaternion */
    RwReal              omega;  /**< Angular displacement in radians */
    RwBool              nearlyZeroOm; /**< Flags near-zero angular 
                                                displacement*/
};


typedef struct RtQuatSlerpArgandCache RtQuatSlerpArgandCache;
/**
 * \ingroup rtslerp
 * \struct RtQuatSlerpArgandCache 
 * a structure describing 
 * an Argand SlerpCache which should be 
 * initialized with \ref RtQuatSetupSlerpArgandCache.
 * See http://www-groups.dcs.st-and.ac.uk/~history/Mathematicians/Argand.html
 * Jean Argand was an accountant and amateur mathematician. 
 * He is famed for his geometrical interpretation of the complex numbers 
 * where i is interpreted as a rotation through 90.
 */
struct RtQuatSlerpArgandCache
{
    RtQuat              logTo;  /**< field Logarithm of final quaternion */
    RtQuat              logBase; /**< Logarithm of initial relative to final quaternion */
};

#define RtQuatSlerpMacro(qpResult, qpFrom, qpTo, rT, sCache)            \
MACRO_START                                                             \
{                                                                       \
    if ((rT) <= ((RwReal) 0))                                           \
    {                                                                   \
        /* t is before start */                                         \
        *(qpResult) = *(qpFrom);                                        \
    }                                                                   \
    else if (((RwReal) 1) <= (rT))                                      \
    {                                                                   \
                                                                        \
        /* t is after end */                                            \
        *(qpResult) = *(qpTo);                                          \
    }                                                                   \
    else                                                                \
    {                                                                   \
        /* ... so t must be in the interior then */                     \
        /* Calc coefficients rSclFrom, rSclTo */                        \
        RwReal rSclFrom = ((RwReal) 1) - (rT);                          \
        RwReal rSclTo = (rT);                                           \
                                                                        \
        if (!((sCache)->nearlyZeroOm))                                  \
        {                                                               \
            /* Standard case: slerp */                                  \
            /* SLERPMESSAGE(("Neither nearly ZERO nor nearly PI")); */  \
                                                                        \
            rSclFrom *= (sCache)->omega;                                \
            RwSinMinusPiToPiMacro(rSclFrom, rSclFrom);                   \
            rSclTo *= (sCache)->omega;                                  \
            RwSinMinusPiToPiMacro(rSclTo, rSclTo);                       \
        }                                                               \
                                                                        \
        /* Calc final values */                                         \
        RwV3dScaleMacro(&(qpResult)->imag,                              \
                        &(sCache)->raFrom.imag, rSclFrom);              \
        RwV3dIncrementScaledMacro(&(qpResult)->imag,                    \
                             &(sCache)->raTo.imag, rSclTo);             \
        (qpResult)->real =                                              \
            ((sCache)->raFrom.real * rSclFrom) +                        \
            ((sCache)->raTo.real * rSclTo);                             \
    }                                                                   \
}                                                                       \
MACRO_STOP

#define RtQuatSlerpArgandMacro(qpResult, qpFrom, qpTo, rT, sArgandCache) \
MACRO_START                                                              \
{                                                                        \
    if ((rT) <= ((RwReal) 0))                                            \
    {                                                                    \
        /* t is before start */                                          \
        *(qpResult) = *(qpFrom);                                         \
    }                                                                    \
    else if (((RwReal) 1) <= (rT))                                       \
    {                                                                    \
        /* t is after end */                                             \
        *(qpResult) = *(qpTo);                                           \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        RtQuat              logBlend;                                    \
                                                                         \
        /* ... so t must be in the interior then */                      \
                                                                         \
        logBlend.imag.x =                                                \
            (sArgandCache)->logBase.imag.x +                             \
            (rT) * (sArgandCache)->logTo.imag.x;                         \
        logBlend.imag.y =                                                \
            (sArgandCache)->logBase.imag.y +                             \
            (rT) * (sArgandCache)->logTo.imag.y;                         \
        logBlend.imag.z =                                                \
            (sArgandCache)->logBase.imag.z +                             \
            (rT) * (sArgandCache)->logTo.imag.z;                         \
        logBlend.real = 0;                                               \
                                                                         \
        RtQuatUnitExpMacro((qpResult), &logBlend);                       \
                                                                         \
    }                                                                    \
}                                                                        \
MACRO_STOP

#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))

#define RtQuatSlerp(qpResult, qpFrom, qpTo, rT, sCache) \
   RtQuatSlerpMacro(qpResult, qpFrom, qpTo, rT, sCache)

#define RtQuatSlerpArgand(qpResult, qpFrom, qpTo, rT, sArgandCache) \
   RtQuatSlerpArgandMacro(qpResult, qpFrom, qpTo, rT, sArgandCache)

#endif /* (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Creating and destroying slerps */

extern RtSlerp     *RtSlerpCreate(RwInt32 nMatRefMask);

extern void         RtSlerpDestroy(RtSlerp * spSlerp);

/* setting up a slerp */
extern RtSlerp     *RtSlerpInitialize(RtSlerp * spSlerp,
                                      RwMatrix * mpMat1,
                                      RwMatrix * mpMat2);

/* Get a matrix */
extern RwMatrix    *RtSlerpGetMatrix(RtSlerp * spSlerp,
                                     RwMatrix * mpResultMat,
                                     RwReal nDelta);

/* Set if lerp or slerp */
extern RtSlerp     *RtSlerpSetLerp(RtSlerp * spSlerp,
                                   RwBool bUseLerp);

extern void
RtQuatSetupSlerpCache(RtQuat * qpFrom,
                      RtQuat * qpTo,
                      RtQuatSlerpCache * sCache);

extern void
RtQuatSetupSlerpArgandCache(RtQuat * qpFrom,
                            RtQuat * qpTo,
                            RtQuatSlerpArgandCache * sArgandCache);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )

extern void
RtQuatSlerp(RtQuat * qpResult,
            RtQuat * qpFrom,
            RtQuat * qpTo,
            RwReal rT,
            RtQuatSlerpCache * sCache);

extern void
RtQuatSlerpArgand(RtQuat * qpResult,
                  RtQuat * qpFrom,
                  RtQuat * qpTo,
                  RwReal rT,
                  RtQuatSlerpArgandCache * sArgandCache);

#endif /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* RTSLERP_H */

