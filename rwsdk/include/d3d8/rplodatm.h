
/******************************************
 *                                        *
 *    RenderWare(TM) Graphics Library     *
 *                                        *
 ******************************************/

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

/***************************************************************************
 *                                                                         *
 * Module  : rplodatm.h                                                    *
 *                                                                         *
 * Purpose : LODATM Geometry                                               *
 *                                                                         *
 **************************************************************************/

#ifndef RPLODATM_H
#define RPLODATM_H


/**
 * \defgroup rplodatm RpLODAtomic
 * \ingroup scenemanagement
 *
 * Level of Detail Management Plugin for RenderWare Graphics.
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rpworld.h"

#include "rpcriter.h"          /* Note: each vendor can choose their own method for
                                * allocation of unique ID's. This file defines 
                                * the ID's used by Criterion.
                                */
#include "rplodatm.rpe"        /* automatically generated header file */

/****************************************************************************
 Defines
 */
#define RPLODATOMICMAXLOD 10


/****************************************************************************
 Type defs 
 */
typedef RwInt32 (*RpLODAtomicLODCallBack)( RpAtomic *atomic );

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

    extern void
        RpLODAtomicCacheSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

    extern RwBool
        RpLODAtomicPluginAttach( void );

    extern RpAtomic *
        RpLODAtomicSetGeometry(
            RpAtomic *atomic, RwInt32 lodIdx, RpGeometry *geometry );

    extern RpGeometry *
        RpLODAtomicGetGeometry(
            RpAtomic *atomic, RwInt32 lodIdx );

    extern RpAtomic *
        RpLODAtomicSetCurrentLOD(
            RpAtomic *atomic, RwInt32 lodIdx );

    extern RwInt32
        RpLODAtomicGetCurrentLOD(
            RpAtomic *atomic );

    extern RpAtomic *
        RpLODAtomicSetRange(
            RpAtomic *atomic, RwReal farRange );

    extern RwReal
        RpLODAtomicGetRange(
            RpAtomic *atomic );

    extern void 
        RpLODAtomicSetCamera(
            RwCamera *camera );

    extern RpAtomic *
        RpLODAtomicSetLODCallBack(
            RpAtomic *atomic, RpLODAtomicLODCallBack callback );

    extern RpAtomic *
        RpLODAtomicSelectLOD(
            RpAtomic *atomic );

    extern RpAtomic *
        RpLODAtomicForAllLODGeometries(
            RpAtomic *atomic, RpGeometryCallBack callback, void *pData );

    extern RpAtomic * 
        RpLODAtomicHookRender(
            RpAtomic *atomic );

    extern RpAtomic * 
        RpLODAtomicUnHookRender(
            RpAtomic *atomic );

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* RPLODATM_H */

