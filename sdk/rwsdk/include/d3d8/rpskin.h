
#ifndef RPSKIN_H
#define RPSKIN_H

/**
 * \defgroup rpskin RpSkin
 * \ingroup skinning
 *
 * Skin Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include "rwcore.h"
#include "rpworld.h"

#include "rpcriter.h"
#include "rpskin.rpe"

#include "rphanim.h"

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/
typedef struct RwMatrixWeights RwMatrixWeights;

/**
 * \ingroup rpskin
 * \struct RwMatrixWeights
 * A structure for defining up to four matrix weights per vertex.
 * Not all entries need to be used.
 *
 * \note
 * Values should be sorted, such that any zero 0.0f entries appear
 * after the valid weights. Any weights that appear after a zero
 * entry will be ignored.
 *
 * \see RpSkinCreate
 */
struct RwMatrixWeights
{
    RwReal w0; /**< The first matrix weight.  */
    RwReal w1; /**< The second matrix weight. */
    RwReal w2; /**< The third matrix weight.  */
    RwReal w3; /**< The fourth matrix weight. */
};

/**
 * \ingroup rpskin
 * \struct RpSkin
 *
 * Skin object. This should be considered an opaque type.
 * Use the RpSkin API functions to access.
 *
 * \see RpSkinCreate
 * \see RpSkinDestroy
 */
typedef struct RpSkin RpSkin;

/*===========================================================================*
 *--- Plugin API Functions --------------------------------------------------*
 *===========================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*---------------------------------------------------------------------------*
 *-   Plugin functions                                                      -*
 *---------------------------------------------------------------------------*/
extern void RpSkinSetFreeListCreateParams(
      RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwBool
RpSkinPluginAttach(void);

/*---------------------------------------------------------------------------*
 *-   Skin Atomic functions                                                 -*
 *---------------------------------------------------------------------------*/
extern RpAtomic *
RpSkinAtomicSetHAnimHierarchy( RpAtomic *atomic,
                               RpHAnimHierarchy *hierarchy );

extern RpHAnimHierarchy *
RpSkinAtomicGetHAnimHierarchy( const RpAtomic *atomic );

/*---------------------------------------------------------------------------*
 *-   Skin Geometry functions                                               -*
 *---------------------------------------------------------------------------*/
extern RpGeometry *
RpSkinGeometrySetSkin( RpGeometry *geometry,
                       RpSkin *skin );

extern RpSkin *
RpSkinGeometryGetSkin( RpGeometry *geometry );

extern RpSkin *
RpSkinCreate( RwUInt32 numVertices,
              RwUInt32 numBones,
              RwMatrixWeights *vertexWeights,
              RwUInt32 *vertexIndices,
              RwMatrix *inverseMatrices );

extern RpSkin *
RpSkinDestroy( RpSkin *skin );

extern RwUInt32
RpSkinGetNumBones( RpSkin *skin );

extern const RwMatrixWeights *
RpSkinGetVertexBoneWeights( RpSkin *skin );

extern const RwUInt32 *
RpSkinGetVertexBoneIndices( RpSkin *skin );

extern const RwMatrix *
RpSkinGetSkinToBoneMatrices( RpSkin *skin );

extern RwBool
RpSkinIsSplit( RpSkin *skin );

/*---------------------------------------------------------------------------*
 *-   Skin pipeline                                                         -*
 *---------------------------------------------------------------------------*/

/**
 * \ingroup rpskin
 * \ref RpSkinType defines the different ways a skinned atomic can
 * be rendered. Once a skinned \ref RpGeometry has been attached to
 * an \ref RpAtomic the atomic must be setup with the correct skin
 * rendering pipeline with \ref RpSkinAtomicSetType.
 */
enum RpSkinType
{
    rpNASKINTYPE        = 0, /**<Invalid skin pipeline.           */
    rpSKINTYPEGENERIC   = 1, /**<Generic skin rendering.          */
    rpSKINTYPEMATFX     = 2, /**<Material effects skin rendering. */
    rpSKINTYPETOON      = 3, /**<Toon skin rendering.             */
    rpSKINTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpSkinType RpSkinType;

extern RpAtomic *
RpSkinAtomicSetType( RpAtomic *atomic,
                     RpSkinType type );

extern RpSkinType
RpSkinAtomicGetType( RpAtomic *atomic );

/*---------------------------------------------------------------------------*
 *-   Internal API                                                          -*
 *---------------------------------------------------------------------------*/
extern RpGeometry *
_rpSkinInitialize(RpGeometry *geometry);

extern RpGeometry *
_rpSkinDeinitialize(RpGeometry *geometry);

extern RwUInt8 *
_rpSkinGetMeshBoneRemapIndices( RpSkin *skin );

extern RwUInt8 *
_rpSkinGetMeshBoneRLECount( RpSkin *skin );

extern RwUInt8 *
_rpSkinGetMeshBoneRLE( RpSkin *skin );

extern RpSkin *
_rpSkinSplitDataCreate( RpSkin *skin, RwUInt32 boneLimit,
                        RwUInt32 numMatrices, RwUInt32 numMeshes,
                        RwUInt32 numRLE );

extern RwBool
_rpSkinSplitDataDestroy( RpSkin *skin );

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*---------------------------------------------------------------------------*
 *-   Backwards macros                                                      -*
 *---------------------------------------------------------------------------*/

#define RpSkinAtomicGetSkin(_a)                                         \
    RpSkinGeometryGetSkin(RpAtomicGetGeometry(_a))

/*---------------------------------------------------------------------------*/

/*---- start: ./d3d8/skinplatform.h----*/

/**
 * \defgroup rpskind3d8 D3D8
 * \ingroup rpskin
 *
 * D3D8 skin pipeline extension.
 */

/**
 * \defgroup rpskind3d8features Features
 * \ingroup rpskind3d8
 *
 * D3D8 skin pipeline features.
 */

/**
 * \defgroup rpskind3d8restrictions Restrictions
 * \ingroup rpskind3d8
 *
 * D3D8 skin pipeline restrictions.
 */

/**
 * \defgroup rpskinbonelimit Bone limit
 * \ingroup rpskind3d8restrictions
 *
 * \par Bone limit
 * The bone limit is 256 as skinning is performed on the CPU.
 *
 */


/*===========================================================================*
 *--- D3D8 Defines -----------------------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- D3D8 Global Types ------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpskind3d8
 * \ref RpSkinD3D8Pipeline rendering pipelines available within
 * the \ref RpSkin plugin. Use \ref RpSkinGetD3D8Pipeline to
 * retrieve the \ref RxPipeline's.
 */
enum RpSkinD3D8Pipeline
{
    rpNASKIND3D8PIPELINE              = 0,
    rpSKIND3D8PIPELINEGENERIC         = 1,
    /**<D3D8 generic skin rendering pipeline.                           */
    rpSKIND3D8PIPELINEMATFX           = 2,
    /**<D3D8 material effect skin rendering pipeline.                   */
    rpSKIND3D8PIPELINETOON            = 3,
    /**<D3D8 toon skin rendering pipeline.                              */
    rpSKIND3D8PIPELINEMATFXTOON       = 4,
    /**<D3D8 toon matfx skin rendering pipeline not supported           */
    rpSKIND3D8PIPELINEMAX,
    rpSKIND3D8PIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpSkinD3D8Pipeline RpSkinD3D8Pipeline;

/*===========================================================================*
 *--- D3D8 Plugin API Functions ----------------------------------------------*
 *===========================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/*---------------------------------------------------------------------------*/

extern RxPipeline *
RpSkinGetD3D8Pipeline( RpSkinD3D8Pipeline D3D8Pipeline );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

/*---- end: ./d3d8/skinplatform.h----*/

#endif /* RPSKIN_H */


