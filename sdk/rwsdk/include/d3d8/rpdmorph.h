/*****************************************************************************
 *
 * File :     rpdmorph.h
 *
 * Abstract : DeltaMorph plugin for Renderware.
 *
 *****************************************************************************
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
 * Copyright (c) 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 *****************************************************************************/

#ifndef RPDMORPH_H
#define RPDMORPH_H

/**
 * \defgroup rpdmorph RpDMorph
 * \ingroup deltamorphing
 * \file rpdmorph.h
 *
 * Delta Morphing Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include <rwcore.h>
#include <rpworld.h>

#include "rpdmorph.rpe" /* automatically generated header file */


/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpdmorph
 * \struct RpDMorphTarget
 * Delta morph target object for defining a target for
 * a base geometry.
 * This should be considered an opaque type.
 * Use the RpDMorphGeometry and RpDMorphTarget API
 * functions to access.
 */
typedef struct RpDMorphTarget RpDMorphTarget;

/**
 * \ingroup rpdmorph
 * \struct RpDMorphAnimation
 * Contains frame sequences for animating delta
 * morph target objects.
 * This should be considered an opaque type.
 * Use the RpDMorphAnimation API
 * functions to access.
 */
typedef struct RpDMorphAnimation RpDMorphAnimation;

#define rpDMORPHNULLFRAME ((RwUInt32)~0)

/*===========================================================================*
 *--- Global variables ------------------------------------------------------*
 *===========================================================================*/

extern RwModuleInfo rpDMorphModule;

/*===========================================================================*
 *--- Plugin API Functions --------------------------------------------------*
 *===========================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*--- DMorphPlugin functions ------------------------------------------------*/
extern RwBool
RpDMorphPluginAttach( void );

/*--- DMorphGeometry functions ----------------------------------------------
 *
 * These functios work on the DMorphGeometry level.
 * Each DMorphGeometry has a list of DMorphTargets.
 */
extern RpGeometry *
RpDMorphGeometryCreateDMorphTargets( RpGeometry *geometry,
                                     RwUInt32 number );

extern RpGeometry *
RpDMorphGeometryDestroyDMorphTargets( RpGeometry *geometry );

extern RpGeometry *
RpDMorphGeometryAddDMorphTarget( RpGeometry  *geometry,
                                 RwUInt32    index,
                                 RwV3d       *vertices,
                                 RwV3d       *normals,
                                 RwRGBA      *preLightColors,
                                 RwTexCoords *texCoords,
                                 RwUInt32    flags );

extern RpGeometry *
RpDMorphGeometryRemoveDMorphTarget( RpGeometry *geometry,
                                    RwUInt32 index );

extern RpDMorphTarget *
RpDMorphGeometryGetDMorphTarget( const RpGeometry *geometry,
                                 RwUInt32 index );

extern RwUInt32
RpDMorphGeometryGetNumDMorphTargets( const RpGeometry *geometry );

extern RpGeometry *
RpDMorphGeometryTransformDMorphTargets( RpGeometry *geometry,
                                        const RwMatrix *matrix );

/*--- DMorphTarget functions ------------------------------------------------
 *
 * These functios work on the DMorphGeometry level.
 * Each DMorphGeometry has a list of DMorphTargets.
 */

extern const RwSphere *
RpDMorphTargetGetBoundingSphere( const RpDMorphTarget *dMorphTarget );

extern RpDMorphTarget *
RpDMorphTargetSetName( RpDMorphTarget *dMorphTarget,
                       RwChar *name );

extern RwChar *
RpDMorphTargetGetName( RpDMorphTarget *dMorphTarget );

extern RpGeometryFlag
RpDMorphTargetGetFlags( RpDMorphTarget *dMorphTarget );


/*--- ANIMATION SYSTEM ------------------------------------------------------
 */

/*--- DMorphAtomic functions ------------------------------------------------
 *
 * These functions work at the DMorphAtomic level.
 */
extern RpAtomic *
RpDMorphAtomicInitialize( RpAtomic *atomic );

extern RwReal *
RpDMorphAtomicGetDMorphValues( RpAtomic *atomic );

extern RpAtomic *
RpDMorphAtomicSetAnimation( RpAtomic *atomic,
                            RpDMorphAnimation *animation );

extern RpDMorphAnimation *
RpDMorphAtomicGetAnimation( const RpAtomic *atomic );

extern RpAtomic *
RpDMorphAtomicAddTime( RpAtomic *atomic,
                       RwReal time );

extern RwReal
RpDMorphAtomicGetAnimTime( const RpAtomic *atomic );

extern RpAtomic *
RpDMorphAtomicSetAnimLoopCallBack( RpAtomic *atomic,
                                   RpAtomicCallBack callBack,
                                   void *data );

extern RpAtomicCallBack
RpDMorphAtomicGetAnimLoopCallBack( const RpAtomic *atomic,
                                   void **callBackData );

extern RpAtomic *
RpDMorphAtomicSetAnimFrame( RpAtomic *atomic,
                            RwUInt32 dMorphTargetIndex,
                            RwUInt32 index );

extern RwUInt32
RpDMorphAtomicGetAnimFrame( const RpAtomic *atomic,
                            RwUInt32 dMorphTargetIndex );


extern RpAtomic *
RpDMorphAtomicSetAnimFrameTime( RpAtomic *atomic,
                                RwUInt32 dMorphTargetIndex,
                                RwReal time );

extern RwReal
RpDMorphAtomicGetAnimFrameTime( const RpAtomic *atomic,
                                RwUInt32 dMorphTargetIndex );

/*--- Animation Functions --------------------------------------------------
 */
extern RpDMorphAnimation *
RpDMorphAnimationCreate(RwUInt32 numDMorphTargets);

extern RpDMorphAnimation *
RpDMorphAnimationDestroy(RpDMorphAnimation *anim);

extern RwUInt32
RpDMorphAnimationGetNumDMorphTargets(RpDMorphAnimation *animation);

/* Animation Frames */
extern RpDMorphAnimation *
RpDMorphAnimationCreateFrames(RpDMorphAnimation  *anim,
                              RwUInt32           dMorphTargetIndex,
                              RwUInt32           numFrames);

extern RpDMorphAnimation *
RpDMorphAnimationDestroyFrames(RpDMorphAnimation  *anim,
                               RwUInt32           dMorphTargetIndex);

extern RwUInt32
RpDMorphAnimationGetNumFrames(RpDMorphAnimation *animation,
                              RwUInt32          dMorphTargetIndex);

/* Stream I/O */
extern RpDMorphAnimation *
RpDMorphAnimationStreamRead(RwStream *stream);

extern RpDMorphAnimation *
RpDMorphAnimationStreamWrite(RpDMorphAnimation *animation,
                             RwStream *stream);

extern RwUInt32
RpDMorphAnimationStreamGetSize(RpDMorphAnimation *animation);

extern RpDMorphAnimation *
RpDMorphAnimationRead(const RwChar *filename);

extern RpDMorphAnimation *
RpDMorphAnimationWrite(RpDMorphAnimation *animation, const RwChar *filename);

/*--- Animation Frame Functions --------------------------------------------
 *
 * These functions work on the DMorphAnimationFrame level.
 * Each Frame can have a reference to the next Frame for the
 * DMorphTarget.
 */
extern RpDMorphAnimation *
RpDMorphAnimationFrameSetNext(RpDMorphAnimation *anim,
                              RwUInt32 dMorphTargetIndex,
                              RwUInt32 frameIndex,
                              RwUInt32 nextFrame );

extern RwUInt32
RpDMorphAnimationFrameGetNext(RpDMorphAnimation *anim,
                              RwUInt32 dMorphTargetIndex,
                              RwUInt32 frameIndex );

extern RpDMorphAnimation *
RpDMorphAnimationFrameSet(RpDMorphAnimation *anim,
                          RwUInt32   dMorphTargetIndex,
                          RwUInt32   frameIndex,
                          RwReal startValue,
                          RwReal endValue,
                          RwReal duration,
                          RwUInt32 nextFrame );

extern RpDMorphAnimation *
RpDMorphAnimationFrameSetStartValue(RpDMorphAnimation *anim,
                                    RwUInt32 dMorphTargetIndex,
                                    RwUInt32 frameIndex,
                                    RwReal   startValue );

extern RwReal
RpDMorphAnimationFrameGetStartValue(RpDMorphAnimation *anim,
                                    RwUInt32 dMorphTargetIndex,
                                    RwUInt32 frameIndex );

extern RpDMorphAnimation *
RpDMorphAnimationFrameSetEndValue(RpDMorphAnimation *anim,
                                  RwUInt32  dMorphTargetIndex,
                                  RwUInt32  frameIndex,
                                  RwReal    endValue );

extern RwReal
RpDMorphAnimationFrameGetEndValue(RpDMorphAnimation *anim,
                                  RwUInt32  dMorphTargetIndex,
                                  RwUInt32  frameIndex );

extern RpDMorphAnimation *
RpDMorphAnimationFrameSetDuration(RpDMorphAnimation *anim,
                                  RwUInt32  dMorphTargetIndex,
                                  RwUInt32  frameIndex,
                                  RwReal    duration );

extern RwReal
RpDMorphAnimationFrameGetDuration(RpDMorphAnimation *anim,
                                  RwUInt32 dMorphTargetIndex,
                                  RwUInt32 frameIndex );

/*--------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RPDMORPH_H */

