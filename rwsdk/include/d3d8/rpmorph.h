
/******************************************/
/*                                        */
/*    RenderWare(TM) Graphics Library     */
/*                                        */
/******************************************/

/*
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 1998. Criterion Software Ltd.
 * All Rights Reserved.
 */


/****************************************************************************
 *                                                                         
 * Morph animation controller
 * Copyright (C) 1998 Criterion Technologies
 *
 * Module  : rpmorph.h
 *                                                                         
 * Purpose : Functions for controlling morph target animation
 *                                                                         
 ****************************************************************************/

#ifndef RPMORPH_H
#define RPMORPH_H


/**
 * \defgroup rpmorph RpMorph
 * \ingroup morphing
 *
 * Morphing Plugin for RenderWare Graphics.
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rpworld.h"

#include "rpmorph.rpe"    /* automatically generated header file */

/****************************************************************************
 Global Types
 */
typedef struct RpMorphInterpolator RpMorphInterpolator;

/**
 * \ingroup rpmorph
 * \struct RpMorphInterpolator
 * structure describing morph interpolator
 */
struct RpMorphInterpolator
{
    RwInt32  flags; /**< flags */
    RwInt16  startMorphTarget; /**< startMorphTarget */
    RwInt16  endMorphTarget; /**< endMorphTarget */
    RwReal   time; /**< time */
    RwReal   recipTime; /**< recipTime */
    RpMorphInterpolator *next; /**< next */
};

/* Morph Animation */

/**
 * \ingroup rpmorph
 * This is the callback function supplied to \ref RpMorphGeometrySetCallBack 
 * and returned from \ref RpMorphGeometryGetCallBack.
 * The supplied function will be passed a pointer to the geometry's parent atomic,
 * and the position of the current interpolator.
 * The function will only be called when the position of the geometry's current
 * interpolator moves out of the current range.
 *
 * \param  atomic     Pointer to the geometry's parent atomic.
 * \param  position   Value of the current interpolator.
 * 
 * \return
 * 
 * \see RpMorphGeometrySetCallBack
 * \see RpMorphGeometryGetCallBack
 */
typedef RwReal (*RpMorphGeometryCallBack)(RpAtomic *atomic, RwReal position);

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RwBool                    RpMorphPluginAttach(void);

/* Morph Animation */
extern RpGeometry               *RpMorphGeometryCreateInterpolators(RpGeometry *geometry, RwInt32 numInterps);
extern RpGeometry               *RpMorphGeometrySetInterpolator(RpGeometry *geometry,
                                                                RwInt32 interpNum,
                                                                RwInt32 startKey, RwInt32 endKey, RwReal time);
extern RpGeometry               *RpMorphGeometrySetNextInterpolator(RpGeometry *geometry,
                                                                RwInt32 interpNum, RwInt32 interpNumNext);
extern RpGeometry               *RpMorphGeometrySetCallBack(RpGeometry *geometry, RpMorphGeometryCallBack animCB);
extern RpMorphGeometryCallBack   RpMorphGeometryGetCallBack(const RpGeometry *geometry);

extern RpAtomic                 *RpMorphAtomicSetCurrentInterpolator(RpAtomic *atomic, RwInt32 interpNum);
extern RwInt32                   RpMorphAtomicGetCurrentInterpolator(RpAtomic *atomic);

extern RpMorphInterpolator      *RpMorphGeometryGetInterpolator(RpGeometry *geometry, RwInt32 interpNum);

extern RpAtomic                 *RpMorphAtomicSetTime(RpAtomic *atomic, RwReal time);
extern RpAtomic                 *RpMorphAtomicAddTime(RpAtomic *atomic, RwReal time);


/* LEGACY-SUPPORT version: */
extern RpMorphInterpolator      *_rpMorphAtomicGetInterpolator(RpAtomic *atomic, RwInt32 interpNum);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#define RpMorphAtomicGetInterpolator(_atomic, _interpNum) \
        _rpMorphAtomicGetInterpolator(_atomic, _interpNum)

#endif /* RPMORPH_H */

