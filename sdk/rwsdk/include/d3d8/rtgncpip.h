/* *INDENT-OFF* */

/* RWPUBLIC */

/****************************************************************************
 *
 * File: rwg/rwsdk/tool/gencpipe/rtgncpip.h
 *
 * Copyright (C) 2002 Criterion Technologies.
 *
 * Purpose: Toolkit containing generic C rendering pipeline nodes.
 *
 ****************************************************************************/

#if (!defined(_RTGNCPIP_H))
#define _RTGNCPIP_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"



#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

    
/****************************************************************************
 global types
 */

typedef RpLight *RxLight;


/* RGBA Interpolation node structures */
#if (!defined(DOXYGEN))
struct NodeRGBAInterpData
{
    RwBool              rgbaInterpOn;
    RxRenderStateVector state;
};
#endif /* (!defined(DOXYGEN)) */

typedef struct NodeRGBAInterpData NodeRGBAInterpData;

/* UV Interpolation node structures */
typedef struct RxNodeUVInterpSettings RxNodeUVInterpSettings;

/**
 * \ingroup rtgencpipe
 * \struct RxNodeUVInterpSettings
 * 
 * TODO
 */
struct RxNodeUVInterpSettings
{
    RwBool              uvInterpOn;  /**< TODO */
    RxRenderStateVector state;       /**< TODO */
};

/* Cloning node structures */
typedef struct RxPacketCacheCluster RxPacketCacheCluster;

/**
 * \ingroup rtgencpipe
 * \struct RxPacketCacheCluster
 * structure containing a cache of an \ref RxCluster's
 * within an \ref RxPacketCache 
 */
struct RxPacketCacheCluster
{
    RwUInt32            slot;       /**< A \ref RwUInt32 index into the \ref RxPacketCache's
                                     * array of RxPacketCacheCluster's */
    RwUInt16            flags;      /**< A cache of the original cluster's flags */
    RwUInt16            stride;     /**< A cache of the original cluster's stride */
    void               *data;       /**< A cache of the original cluster's data */
    RwUInt32            numAlloced; /**< A cache of the original cluster's numAlloced */
    RwUInt32            numUsed;    /**< A cache of the original cluster's numUsed */
    RxPipelineCluster  *clusterRef; /**< A cache of the original cluster's \ref RxPipelineCluster */
};
typedef struct RxPacketCache RxPacketCache;

/**
 * \ingroup rtgencpipe
 * \struct RxPacketCache
 * structure containing a cache of a \ref RxPacket */
struct RxPacketCache
{
    RwUInt16             packetFlags; /**< A cache of the original packet's flags */
    RwUInt16             pad[1];      /**< Alignment padding */
    RwUInt32             numClusters; /**< The number of present clusters in the
                                       * original packet when it was cloned */
    RwBool               lastCloneDone;/**< Once the cache has been cloned by \ref RxPacketCacheClone
                                       * with (lastClone == TRUE), it should not be used again! */
    RwUInt32             pad2[1];      /**< Alignment padding */
    RxPacketCacheCluster clusters[1]; /**< An array of \ref RxPacketCacheCluster's,
                                       * extending beyond 1 element */
};
    

typedef struct RxNodeCloneInitData RxNodeCloneInitData;
/**
 * \ingroup rtgencpipe
 * \struct RxNodeCloneInitData
 * structure with which to initialize 
 * clone a \ref RxNodeDefinition, 
 * through \ref RxNodeDefinitionCloneCreate and
 * set up cloned \ref RxPipelineNode modes, through
 * \ref RxPipelineNodeCloneDefineModes */
struct RxNodeCloneInitData
{
    RwUInt32   numModes;   /**< Specifies the number of modes in
                              which the node should operate */
    RwUInt32   numOutputs; /**< Specifies the number of outputs of this
                              Clone node, which is also the maximum
                              number of outputs to which any one mode
                              may dispatch packets */
    RwUInt32  *modeSizes;  /**< Specifies the number of outputs to which
                              each mode dispatches packets */
    RwUInt32 **modes;      /**< An array of numModes pointers to arrays
                              (of length numOutputs) specifying the
                              outputs, in order, to which each mode
                              should dispatch packets (output zero is
                              the first output) */
};

/**
 * \ingroup rtgencpipe
 * \struct RxNodeCloneData
 * structure which is the private
 * data of Clone nodes \ref RxPipelineNode */
typedef struct RxNodeCloneData RxNodeCloneData;
struct RxNodeCloneData
{
    RwBool optimized;         /**< \ref RwBool specifying whether \ref RxPipelineNodeCloneOptimize
                               * has been run on this \ref RxPipelineNode yet */
    RwUInt32 currentMode;     /**< \ref RwUInt32 The current mode of operation */
    RxNodeCloneInitData *data;/**< A pointer to \ref RxNodeCloneInitData data
                               * specifying the modes of operation */
};

/****************************************************************************
 global prototypes
 */

extern RxClusterDefinition RxClLights; /* Uses the RxLight type (see above) */


/*********************************************************************************

        Generic Nodes

  *******************************************************************************/

extern RxNodeDefinition *RxNodeDefinitionGetAtomicInstance(void);
extern RxNodeDefinition *RxNodeDefinitionGetClipLine(void);
extern RxNodeDefinition *RxNodeDefinitionGetClipTriangle(void);
extern RxNodeDefinition *RxNodeDefinitionGetWorldSectorEnumerateLights(void);
extern RxNodeDefinition *RxNodeDefinitionGetCullTriangle(void);
extern RxNodeDefinition *RxNodeDefinitionGetFastPathSplitter(void);
extern RxNodeDefinition *RxNodeDefinitionGetImmInstance(void);
extern RxNodeDefinition *RxNodeDefinitionGetImmMangleLineIndices(void);
extern RxNodeDefinition *RxNodeDefinitionGetImmMangleTriangleIndices(void);
extern RxNodeDefinition *RxNodeDefinitionGetImmRenderSetup(void);
extern RxNodeDefinition *RxNodeDefinitionGetImmStash(void);
extern RxNodeDefinition *RxNodeDefinitionGetLight(void);
extern RxNodeDefinition *RxNodeDefinitionGetMaterialScatter(void);
extern RxNodeDefinition *RxNodeDefinitionGetPostLight(void);
extern RxNodeDefinition *RxNodeDefinitionGetPreLight(void);
extern RxNodeDefinition *RxNodeDefinitionGetRGBAInterp(void);
extern RxNodeDefinition *RxNodeDefinitionGetUVInterp(void);
extern RxNodeDefinition *RxNodeDefinitionGetScatter(void);
extern RxNodeDefinition *RxNodeDefinitionGetSubmitLine(void);
extern RxNodeDefinition *RxNodeDefinitionGetSubmitTriangle(void);
extern RxNodeDefinition *RxNodeDefinitionGetTransform(void);
extern RxNodeDefinition *RxNodeDefinitionGetAtomicEnumerateLights(void);
extern RxNodeDefinition *RxNodeDefinitionGetWorldSectorInstance(void);
extern RxNodeDefinition *RxNodeDefinitionCloneCreate(RxNodeCloneInitData *data);
extern RwBool            RxPipelineNodeCloneDefineModes(
                             RxPipeline          *pipeline,
                             RxPipelineNode      *node,
                             RxNodeCloneInitData   *data);
extern RwBool            RxNodeDefinitionCloneDestroy(RxNodeDefinition *def);
extern RwBool            RxPipelineNodeCloneOptimize(RxPipeline     *pipeline,
                                                     RxPipelineNode *node);


/*********************************************************************************

        Generic Core Pipes

  *******************************************************************************/


extern RwBool RtGenCPipeCreateGenericIm3DTransformPipeline(void);
extern void RtGenCPipeDestroyGenericIm3DTransformPipeline(void);
extern RwBool RtGenCPipeCreateGenericIm3DRenderPipelines(void);
extern void RtGenCPipeDestroyGenericIm3DRenderPipelines(void);

extern RxPipeline *RwIm3DGetGenericTransformPipeline(void);
extern RxPipeline *RwIm3DGetGenericRenderPipeline(RwPrimitiveType primType);


/*********************************************************************************

        Generic World Pipes

  *******************************************************************************/

extern RwBool RtGenCPipeCreateGenericWorldPipelines(void);
extern void RtGenCPipeDestroyGenericWorldPipelines(void);

#define RpWorldGetGenericSectorPipelineMacro() \
    (RXPIPELINEGLOBAL(genericWorldSectorPipeline))

#define RpAtomicGetGenericPipelineMacro() \
    (RXPIPELINEGLOBAL(genericAtomicPipeline))

#define RpMaterialGetGenericPipelineMacro() \
    (RXPIPELINEGLOBAL(genericMaterialPipeline))


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpWorldGetGenericSectorPipeline RpWorldGetGenericSectorPipelineMacro
#define RpAtomicGetGenericPipeline      RpAtomicGetGenericPipelineMacro
#define RpMaterialGetGenericPipeline    RpMaterialGetGenericPipelineMacro

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

extern RxPipeline       *RpWorldGetGenericSectorPipeline(void);

extern RxPipeline       *RpAtomicGetGenericPipeline(void);

extern RxPipeline       *RpMaterialGetGenericPipeline(void);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

#ifdef    __cplusplus
}
#endif /* __cplusplus */


#endif /* (!defined(_RTGNCPIP_H)) */

/* RWPUBLICEND */

/* *INDENT-ON* */
