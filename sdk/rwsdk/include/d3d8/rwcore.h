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
 * Copyright (c) 1999. Criterion Software Ltd.
 * All Rights Reserved.
 */

/*************************************************************************
 *
 * Filename: <C:/daily/rwsdk/include/d3d8/rwcore.h>
 * Automatically Generated on: Thu Jan 23 11:06:24 2003
 *
 ************************************************************************/

#ifndef RWCORE_H
#define RWCORE_H

/*--- System Header Files ---*/
#include <rwplcore.h>


/*--- Automatically derived from: C:/daily/rwsdk/driver/common/barwasmm.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2resort.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2macros.h ---*/

#define RxClusterDecCursorByStride(_cluster, _stride)                           \
    ((_cluster)->currentData =                                                  \
      (void *)(((RwUInt8 *)(_cluster)->currentData) -                           \
         (_stride)))

#define RxClusterDecCursor(_cluster) \
    RxClusterDecCursorByStride(_cluster, (_cluster)->stride)

#define RxClusterIncCursorByStride(_cluster, _stride)                           \
    ((_cluster)->currentData =                                                  \
     (void *)(((RwUInt8 *)(_cluster)->currentData) +                            \
              (_stride)))

#define RxClusterIncCursor(_cluster) \
    RxClusterIncCursorByStride(_cluster, (_cluster)->stride)

#define RxClusterResetCursor(_cluster) \
    ((_cluster)->currentData = (_cluster)->data)

#define RxClusterGetCursorData(_cluster, _type) \
    ((_type *)(_cluster)->currentData)

#define RxClusterGetIndexedData(_cluster, _type, _index)                        \
    ((_type *)(((RwUInt8 *)(_cluster)->data) + (_cluster)->stride*(_index)))

#define RxClusterGetFreeIndex(_cluster) ( (_cluster)->numUsed++ )

#define RxPipelineClusterAssertAttributeSet(_cluster, _attributeSet)    \
    RWASSERT( (_cluster)->clusterRef->attributeSet != NULL &&           \
              rwstrcmp((_cluster)->clusterRef->attributeSet,              \
                     (_attributeSet)) == 0 )

#define RxPipelineNodeParamGetData(_param) \
    ( (_param)->dataParam )

#define RxPipelineNodeParamGetHeap(_param) \
    ( (_param)->heap )



/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2heap.h ---*/

#if (defined(RWDEBUG) && (defined(RWMEMDEBUG)))

#if (!defined(DISABLERWHEAP))
#define DISABLERWHEAP
#endif /* (!defined(DISABLERWHEAP)) */

#endif /* (defined(RWDEBUG) && (defined(RWMEMDEBUG))) */

typedef struct rxHeapFreeBlock rxHeapFreeBlock;
typedef struct rxHeapSuperBlockDescriptor rxHeapSuperBlockDescriptor;
typedef struct RxHeap RxHeap;
typedef struct rxHeapBlockHeader rxHeapBlockHeader;

#if (!defined(DOXYGEN))
struct rxHeapFreeBlock
{
    RwUInt32            size;
    rxHeapBlockHeader  *ptr;
};

struct rxHeapSuperBlockDescriptor
{
    void *start;
    RwUInt32 size;
    rxHeapSuperBlockDescriptor *next;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwcoregeneric
 * \struct RxHeap 
 * structure describing a pipeline execution heap 
 */
struct RxHeap
{
    RwUInt32            superBlockSize; /**< Granularity of heap growth */
    rxHeapSuperBlockDescriptor *head;   /**< Internally used superblock pointer */
    rxHeapBlockHeader  *headBlock;      /**< Internally used block pointer */
    rxHeapFreeBlock    *freeBlocks;     /**< Internally used free blocks pointer */
    RwUInt32            entriesAlloced; /**< Number of entries allocated */
    RwUInt32            entriesUsed;    /**< Number of entries used */
    RwBool              dirty;          /**< Internally used boolean, flags whether
                                         *   the heap needs resetting or not. */
};

#if (!defined(DOXYGEN))
struct rxHeapBlockHeader
{
    /* present in all blocks (used & unused) */
    rxHeapBlockHeader  *prev, *next;
    RwUInt32            size;
    rxHeapFreeBlock    *freeEntry; /* (or null) */
    RwUInt32            pad[4]; /* alignment padding to 32 bytes */
};
#endif /* (!defined(DOXYGEN)) */

/* This wrapper cheaply early-outs when a heap doesn't *need* resetting */
#define RxHeapReset(heap) \
    ((FALSE == (heap)->dirty) ? (TRUE) : (_rxHeapReset(heap)))

#ifdef __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RxHeap      *RxHeapCreate(RwUInt32 size);
extern void         RxHeapDestroy(RxHeap * heap);
extern RwBool       _rxHeapReset(RxHeap * heap);
extern void        *RxHeapAlloc(RxHeap * heap, RwUInt32 size);
extern void         RxHeapFree(RxHeap * heap, void *block);
extern void        *RxHeapRealloc(RxHeap * heap, void *block,
                                  RwUInt32 newSize, RwBool allowCopy);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#if (defined(DISABLERWHEAP))

typedef struct rxHeapMallocTrace rxHeapMallocTrace;
struct rxHeapMallocTrace
{
    rxHeapMallocTrace *next;
    rxHeapBlockHeader *block;
};

#endif                          /* (defined(DISABLERWHEAP)) */


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2dep.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2core.h ---*/

extern RwInt32 _rxPipelineMaxNodes;
extern RwInt32 _rxHeapInitialSize;
/* LEGACY-SUPPORT MACRO */
#define _rwRxHeapInitialSize _rxHeapInitialSize

/* Beneficial padding of PowerPipe types is still being worked out... */
#define PADCLUSTERSx


/*************************************************************
 * Global Defines
 */

#define RWBOOLTOGGLE(bVar) ((bVar == FALSE)?(bVar = TRUE):(bVar = FALSE))

/* Both these currently limited due to the use of RwUInt32 bit-fields */
#define RXNODEMAXCLUSTERSOFINTEREST 32
#define RXNODEMAXOUTPUTS            32

/* Useful (for memory alloc) to limit this during pipeline construction */
#define RXPIPELINEDEFAULTMAXNODES   64

/*
 * Cluster flags
 */

#define rxCLFLAGS_NULL          ((RwUInt16) 0x0000U)
#define rxCLFLAGS_CLUSTERVALID  ((RwUInt16) 0x0001U)
#define rxCLFLAGS_EXTERNAL ((RwUInt16) 0x0002U)
#define rxCLFLAGS_EXTERNALMODIFIABLE ((RwUInt16) 0x0004U | 0x0002U)
#define rxCLFLAGS_MODIFIED ((RwUInt16) 0x0008U)

/*
 * Packet flags
 */

#define rxPKFLAGS_NULL        ((RwUInt16) 0x0000U)

/*
 * used in input specification
 */

/**
 * \ingroup rwcoregeneric
 * \ref RxClusterValidityReq
 * Flags specifying the state requirements for
 * a \ref RxCluster on entry to a node */
enum RxClusterValidityReq
{
    rxCLREQ_DONTWANT = 0, /**<The cluster is required but any data within it is
                           * not wanted and will be overwritten */
    rxCLREQ_REQUIRED = 1, /**<The cluster is required and it must contain
                           * valid data */
    rxCLREQ_OPTIONAL = 2, /**<The cluster will be used if it is present and
                           * contains valid data, otherwise the node will
                           * make do without it. */
    rxCLUSTERVALIDITYREQFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};


/**
 * \ingroup rwcoregeneric
 * \ref RxClusterValid
 * Flags specifying the state requirements for
 * a \ref RxCluster on exit from a node */
enum RxClusterValid
{
    rxCLVALID_NOCHANGE = 0, /**<The cluster and its data will not change in
                             * validity on passing through this node */
    rxCLVALID_VALID = 1,    /**<The cluster and its data will be valid on
                             * exit from this node */
    rxCLVALID_INVALID = 2,  /**<The cluster's data will be invalid on
                             * exit from this node */
    rxCLUSTERVALIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/****************************************************************************
 Global Types
 */

typedef struct RxClusterDefinition RxClusterDefinition;

typedef struct rxReq rxReq;

typedef enum RxClusterValidityReq RxClusterValidityReq;
typedef enum RxClusterValid RxClusterValid;
typedef struct RxOutputSpec RxOutputSpec;
typedef struct RxClusterRef RxClusterRef;
typedef struct RxIoSpec RxIoSpec;

typedef struct RxNodeMethods RxNodeMethods;
typedef struct RxNodeDefinition RxNodeDefinition;

typedef struct RxCluster RxCluster;
typedef struct RxPipelineCluster RxPipelineCluster;
typedef struct RxPacket RxPacket;
typedef struct RxPipelineNode RxPipelineNode;
typedef struct RxPipelineNodeTopSortData RxPipelineNodeTopSortData;
typedef struct RxPipelineNode RxPipelineNodeInstance;
typedef struct RxPipelineNodeParam RxPipelineNodeParam;
typedef struct RxExecutionContext RxExecutionContext;
typedef struct RxPipelineRequiresCluster RxPipelineRequiresCluster;
typedef struct RxPipeline RxPipeline;

/***************************************************************************
 *
 * C L U S T E R   D E F I N I T I O N
 *
 ***************************************************************************/

/**
 * \ingroup rwcoregeneric
 * \struct RxClusterDefinition
 * Structure describing a cluster */
struct RxClusterDefinition
{
    RwChar             *name;                  /**< Name */
    RwUInt32            defaultStride;         /**< Default stride */
    RwUInt32            defaultAttributes;     /**< Default attributes */
    const RwChar         *attributeSet;           /**< Attribute set */
};


/***************************************************************************
 *
 * N O D E   D E F I N I T I O N   S T R U C T S
 *
 ***************************************************************************/

/**
 * \ingroup rwcoregeneric
 * \struct RxOutputSpec
 * Structure describing an output specification of a node */
struct RxOutputSpec
{
     RwChar             *name;                  /**< Name */
     RxClusterValid     *outputClusters;        /**< States of clusters of interest on output */
     RxClusterValid      allOtherClusters;      /**< States of clusters not of interest on output */
};



/**
 * \ingroup rwcoregeneric
 * \ref RxClusterForcePresent
 *  Flags specifying whether an \ref RxCluster
 * should be forced to be present in an \ref RxPipelineNode */
enum RxClusterForcePresent
{
    rxCLALLOWABSENT = FALSE, /**<The cluster is allowed to be absent if no prior
                              *  nodes create it and no subsequent nodes require it */
    rxCLFORCEPRESENT = TRUE, /**<The cluster must be present even if no prior
                              *  nodes create it and no subsequent nodes require it */

    rxCLUSTERFORCEPRESENTFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxClusterForcePresent RxClusterForcePresent;

/**
 * \ingroup rwcoregeneric
 * \struct RxClusterRef
 * Structure describing a cluster reference */
struct RxClusterRef
{
    RxClusterDefinition  *clusterDef;           /**< Cluster definition */
    RxClusterForcePresent forcePresent;         /**< Specifies whether the cluster should be forced present */
    RwUInt32              reserved;             /**< Omit or initialize to zero */
};

#define rxCLRESERVED       ((RwUInt32)0)

/**
 * \ingroup rwcoregeneric
 * \struct RxIoSpec
 * Structure describing an input/output specification of a node */
struct RxIoSpec
{
    RwUInt32              numClustersOfInterest;/**< Number of Clusters of interest */
    RxClusterRef         *clustersOfInterest;   /**< Clusters of interest array */
    RxClusterValidityReq *inputRequirements;    /**< Requirements of the clusters of interest on input to the node */
    RwUInt32              numOutputs;           /**< Number of outputs from the node */
    RxOutputSpec         *outputs;              /**< Output specification array */
};

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeBodyFn is the callback to be
 * called during pipeline execution -- and, typically, process
 * \ref RxPacket's -- for the owning pipeline node.
 *
 * \param  self   A pointer to the pipeline node being executed
 * \param  params   A pointer to a parameter structure
 *
 * \return TRUE on success, FALSE otherwise.
 *
 * \see RxNodeMethods
 */
typedef RwBool (*RxNodeBodyFn) (RxPipelineNode * self,
                                const RxPipelineNodeParam *params);

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeInitFn
 * is the callback to be called,
 * for the owning node definition, the first time an \ref RxPipeline
 * referencing that node definition is unlocked.
 *
 * \param  self   A pointer to the node definition
 *
 * \return TRUE on success, FALSE otherwise.
 *
 * \see RxNodeMethods
 */
typedef RwBool (*RxNodeInitFn) (RxNodeDefinition * self);

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeTermFn
 * is the callback to be called,
 * for the owning node definition, the last time an \ref RxPipeline
 * referencing that node definition is destroyed or locked.
 *
 * \param  self   A pointer to the node definition
 *
 * \return None
 *
 * \see RxNodeMethods
 */
typedef void   (*RxNodeTermFn) (RxNodeDefinition * self);

/**
 * \ingroup rwcoregeneric
 * \ref RxPipelineNodeInitFn
 * is the callback to be called, for the owning pipeline node, whenever a
 * \ref RxPipeline containing that that pipeline node is unlocked.
 *
 * \param  self   A pointer to the pipeline node
 *
 * \return TRUE on success, FALSE otherwise.
 *
 * \see RxNodeMethods
 */
typedef RwBool (*RxPipelineNodeInitFn) (RxPipelineNode * self);

/**
 * \ingroup rwcoregeneric
 * \ref RxPipelineNodeTermFn
 * is the callback to be called, for the owning pipeline node, whenever a
 * \ref RxPipeline containing that that pipeline node is locked or
 * destroyed.
 *
 * \param  self   A pointer to the pipeline node
 *
 * \return None
 *
 * \see RxNodeMethods
 */
typedef void   (*RxPipelineNodeTermFn) (RxPipelineNode * self);

/**
 * \ingroup rwcoregeneric
 * \ref RxPipelineNodeConfigFn
 * is the callback to be called, for the owning pipeline node, whenever a
 * \ref RxPipeline containing that that pipeline node is unlocked,
 * *after* all \ref RxPipelineNodeInitFn's have been called for the
 * pipeline in question. This func is to be used as described in
 * RxPipelineNodeSendConfigMsg.
 *
 * \param  self       A pointer to the pipeline node
 * \param  pipeline   A pointer to the containing pipeline
 *
 * \return TRUE on success, FALSE otherwise.
 *
 * \see RxNodeMethods
 */
typedef RwBool (*RxPipelineNodeConfigFn) (RxPipelineNode * self,
                                          RxPipeline * pipeline);

/**
 * \ingroup rwcoregeneric
 * \ref RxConfigMsgHandlerFn
 * is the callback to be called, for the owning pipeline node, whenever
 * a message is sent to it by the \ref RxPipelineNodeConfigFn of another
 * pipeline node in the same pipeline. See \ref RxPipelineNodeSendConfigMsg.
 * 
 * \param  self   A pointer to the pipeline node
 * \param  msg   Message ID
 * \param  intparam   Meaning is message-specific
 * \param  ptrparam   Meaning is message-specific
 *
 * \return A RwInt32 value, 0: unserviced; -ve: error; +ve: informative success
 * 
 * \see RxNodeMethods
 */
typedef RwUInt32 (*RxConfigMsgHandlerFn) (RxPipelineNode * self,
                                          RwUInt32 msg,
                                          RwUInt32 intparam,
                                          void *ptrparam);

/**
 * \ingroup rwcoregeneric
 * \struct RxNodeMethods
 * A structure describing a set
 * of node methods
 *
 * \see RxNodeBodyFn
 * \see RxNodeInitFn
 * \see RxNodeTermFn
 * \see RxPipelineNodeInitFn
 * \see RxPipelineNodeTermFn
 * \see RxPipelineNodeConfigFn
 * \see RxConfigMsgHandlerFn
 */
struct RxNodeMethods
{
    RxNodeBodyFn         nodeBody;              /**< Node body function */
    RxNodeInitFn         nodeInit;              /**< Node initialization function */
    RxNodeTermFn         nodeTerm;              /**< Node termination function */
    RxPipelineNodeInitFn pipelineNodeInit;      /**< Pipeline node initialization function */
    RxPipelineNodeTermFn pipelineNodeTerm;      /**< Pipeline node termination function */
    RxPipelineNodeConfigFn pipelineNodeConfig;  /**< Pipleline node configuation function */
    RxConfigMsgHandlerFn configMsgHandler;      /**< Configuaraton message handler function */
};

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeDefEditable
 * Flags specifying whether an \ref RxNodeDefinition
 * is editable or not (\ref RxPipelineNodeCloneDefinition,
 * \ref RxPipelineNodeReplaceCluster and \ref RxPipelineNodeRequestCluster
 * create editable copies of node definitions as the originals may be
 * static definitions). */
enum RxNodeDefEditable
{
    /**<This node definition should not be freed */
    rxNODEDEFCONST = FALSE,
    /**< This node definition is a temporary,
     * modified copy of another and can be freed */
    rxNODEDEFEDITABLE = TRUE,
    rxNODEDEFEDITABLEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxNodeDefEditable RxNodeDefEditable;

/**
 * \ingroup rwcoregeneric
 * \struct RxNodeDefinition
 * A structure describing a node definition */
struct RxNodeDefinition
{
    RwChar             *name;                   /**< Name */
    RxNodeMethods       nodeMethods;            /**< Node methods */
    RxIoSpec            io;                     /**< Input/output specification */
    RwUInt32            pipelineNodePrivateDataSize; /**< Size in bytes of node's private data  */
    RxNodeDefEditable   editable;               /**< Flags whether a node is editable */
    RwInt32             InputPipesCnt;          /**< Count of the unlocked pipelines containing this node */
};

/***************************************************************************
 *
 * P I P E L I N E - E X E C U T I O N - T I M E   S T R U C T S
 *
 ***************************************************************************/

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineCluster
 * A structure describing a pipeline cluster;
 * that is, an \ref RxClusterDefinition in the context of a specific \ref RxPipeline
 * (in the same way as an \ref RxPipelineNode is an \ref RxNodeDefinition in the
 * context of a specific \ref RxPipeline). The \ref RxCluster is the structure
 * representing this and the \ref RxClusterDefinition within \ref RxPacket's at
 * pipeline-execution-time */
struct RxPipelineCluster
{
    RxClusterDefinition *clusterRef;            /**< Cluster refererence */
    RwUInt32             creationAttributes;    /**< Creation Attributes */
};

/**
 * \ingroup rwcoregeneric
 * \struct RxCluster
 * A structure describing a cluster; this is
 * the representative of an \ref RxClusterDefinition and \ref RxPipelineCluster
 * within \ref RxPacket's at pipeline-execution-time. */
struct RxCluster
{
    RwUInt16            flags;                  /**< Bitfield of flags e.g. modification permissions */
    RwUInt16            stride;                 /**< Stride in bytes of the cluster's data */
    void               *data;                   /**< The Cluster's data */
    void               *currentData;            /**< A 'cursor', referencing the current element in the data */
    RwUInt32            numAlloced;             /**< Allocated count */
    RwUInt32            numUsed;                /**< Used count */
    RxPipelineCluster  *clusterRef;             /**< Valid after a cluster has been locked for writing,
                                                 *   otherwise NULL. Analog of \ref RxPipelineNode and
                                                 *   its 'nodeDef' member. */
    RwUInt32            attributes;             /**< Attributes */
#ifdef PADCLUSTERS
    RwUInt32 pad[1];                            /**< Alignment padding */
#endif
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPacket
 * A structure describing a packet header */
struct RxPacket
{
    RwUInt16            flags;                  /**< Flags to guide pipeline execution */
    RwUInt16            numClusters;            /**< Maximum number of clusters simultanesouly present in the current pipeline */
    RxPipeline         *pipeline;               /**< The pipeline in which this packet is embedded (the current pipeline) */
    RwUInt32           *inputToClusterSlot;     /**< LUT to locate clusters of interest in the packet */
    RwUInt32           *slotsContinue;          /**< Bitfields specifying clusters persisting to output node */
    RxPipelineCluster **slotClusterRefs;        /**< Internal Use */
#ifdef PADCLUSTERS
    RwUInt32 pad[3];                            /**< Alignment padding */
#endif
    RxCluster           clusters[1];            /**< Cluster array large enough for widest part of the pipeline */
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineNode
 * Structure describing a pipeline Node;
 * that is an \ref RxNodeDefinition in the context 
 * of a specific \ref RxPipeline. 
 */
struct RxPipelineNode
{
    RxNodeDefinition   *nodeDef;            /**< Node definition reference */
    RwUInt32            numOutputs;         /**< Output count */
    RwUInt32           *outputs;            /**< Output array, indexing the pipeline's array of pipeline nodes */
    RxPipelineCluster **slotClusterRefs;    /**< For packets passing through this node, SlotClusterRefs[n]
                                             * identifies the cluster to be found at index n in the packet's
                                             * Clusters[] array. These assignments are determined at pipeline
                                             * Unlock() time and are good for the life of the pipeline. */
    RwUInt32           *slotsContinue;      /**< Cluster persistence table for the node's outputs */
    void               *privateData;        /**< Pointer to the pipeline Node's private data */
    RwUInt32           *inputToClusterSlot; /**< LUT to locate clusters of interest in packets passing through this pipeline Node */
    RxPipelineNodeTopSortData *topSortData; /**< Internal Use */
    void               *initializationData; /**< Used by the pipeline node initialisation
                                             * function in setting up the Private data. */
    RwUInt32        initializationDataSize; /**< Present so that if the node is cloned
                                             * we can copy the initialisation data. */
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineNodeTopSortData
 * Structure describing data used during topological sorting 
 * during \ref RxLockedPipeUnlock ; 
 * RenderWare users do not need to understand this */
struct RxPipelineNodeTopSortData
{
    RwUInt32            numIns;                 /**< Input count */
    RwUInt32            numInsVisited;          /**< Count of inputs visited during dependencies
                                                 * propagation/cluster slot allocation */
    rxReq              *req;                    /**< Req used in dependencies propagation/cluster
                                                 * slot allocation */
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineNodeParam
 * Structure holding parameters
 * to pass to node body functions */
struct RxPipelineNodeParam
{
    void   *dataParam;   /**< The data pointer passed in to \ref RxPipelineExecute */
    RxHeap *heap;        /**< The heap associated with the current pipeline exeuction */
};

enum rxEmbeddedPacketState
{
    rxPKST_PACKETLESS = 0, /* Packet not created */
    rxPKST_UNUSED     = 1, /* Packet created and then destroyed */
    rxPKST_INUSE      = 2, /* Packet created but not yet destroyed and fetched but not yet dispatched */
    rxPKST_PENDING    = 3, /* Packet created but not destroyed and dispatched but not yet fetched */
    rxEMBEDDEDPACKETSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum rxEmbeddedPacketState rxEmbeddedPacketState;

/**
 * \ingroup rwcoregeneric
 * \struct RxExecutionContext
 * Structure describing an execution context */
struct RxExecutionContext
{
    RxPipeline           *pipeline;     /**< Currently executing pipeline */
    RxPipelineNode       *currentNode;  /**< Currently executing node */
    RwInt32               exitCode;     /**< Used internally for nodes returning error codes on exit */
    RwUInt32              pad;          /**< Alignment padding */
    RxPipelineNodeParam   params;       /**< The parameters passed to node bodies */
    /*RwUInt32              pad[2];*/
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPipelineRequiresCluster
 * Structure describing a pipeline requirement of a cluster */
struct RxPipelineRequiresCluster
{
    RxClusterDefinition *clusterDef;    /**< Reference to a Cluster definition */
    RxClusterValidityReq rqdOrOpt;      /**< Cluster validity requirement (rxCLREQ_DONTWANT, rxCLREQ_REQUIRED or rxCLREQ_OPTIONAL) */
    RwUInt32             slotIndex;     /**< Index into the packet's cluster array within this pipeline */
};

/**
 * \ingroup rwcoregeneric
 * \struct RxPipeline
 * Structure describing a pipeline */
struct RxPipeline
{
    RwBool                     locked;                /**< Flags whether the pipeline is locked for editing */
    RwUInt32                   numNodes;              /**< Node count */
    RxPipelineNode            *nodes;                 /**< Topologically sorted array of pipeline nodes */
    RwUInt32                   packetNumClusterSlots; /**< Number of slots allocated for clusters */
    rxEmbeddedPacketState      embeddedPacketState;   /**< The state of this pipeline's embedded packet */
    RxPacket                  *embeddedPacket;        /**< This pipeline's embedded packet */

    RwUInt32                   numInputRequirements;  /**< Input requirements count */
    RxPipelineRequiresCluster *inputRequirements;     /**< Input requirements array */

    void                      *superBlock;            /**< Internally used block of memory */
    RwUInt32                   superBlockSize;        /**< Internally used block of memory */

    RwUInt32                   entryPoint;            /**< The index of the node which is the entry point of this pipeline */
    RwUInt32                   pluginId;              /**< If required, the Id of the plugin owning this pipeline, or 0 */
    RwUInt32                   pluginData;            /**< Rights callback extra data */
};

/****************************************************************************
 * Global Prototypes
 */

/**
 * \ingroup rwcoregeneric
 * \ref RxPipelineNodeOutputCallBack 
 * is the callback function supplied 
 * to \ref RxPipelineNodeForAllConnectedOutputs.
 *
 * The callback will be passed a pointer to the \ref RxPipelineNode whose
 * outputs are being traversed and a pointer to the current output
 * \ref RxPipelineNode, as well as a pointer to an optional user-defined
 * data structure (callbackdata). If no such structure was specified, this
 * will be NULL.
 *
 * \param  node         A pointer to the pipeline node whose outputs
 *                      are being traversed
 * \param  outputnode   A pointer to the current output
 *                      pipeline node
 * \param  callbackdata A pointer to optional user-supplied data
 *
 * \return Returns a pointer to the \ref RxPipelineNode whose outputs are being
 * traversed, or NULL to terminate traversal
 */
typedef RxPipelineNode * (*RxPipelineNodeOutputCallBack) (RxPipelineNode * node,
                                                  RxPipelineNode * outputnode,
                                                  void *callbackdata);

#ifdef RWDEBUG
#define RXCHECKFORUSERTRAMPLING(_pipeline)                       \
    ( _rwPipelineCheckForTramplingOfNodePrivateSpace(_pipeline) )
#endif /* RWDEBUG */

#if (!defined(RXCHECKFORUSERTRAMPLING))
#define RXCHECKFORUSERTRAMPLING(_pipeline) /* No op */
#endif /* (!defined(RXCHECKFORUSERTRAMPLING)) */


#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern void
RxPipelineSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwBool
_rxPipelineOpen(void);

extern RwBool
_rxPipelineClose(void);

extern RwBool
rxPipelinePluginsAttach(void);

extern RxPipeline *
RxPipelineCreate(void);


extern void
_rxPipelineDestroy(RxPipeline * Pipeline);

#define _RxPipelineDestroy(_ppln)  _rxPipelineDestroy(_ppln)
#define RxPipelineDestroy(_ppln) (_rxPipelineDestroy(_ppln), TRUE)

extern RxHeap      *
RxHeapGetGlobalHeap(void);

extern RxPipeline *
RxPipelineExecute(RxPipeline  * pipeline,
                  void        * data,
                  RwBool       heapReset);

extern RxPacket *
RxPacketCreate(RxPipelineNode * node);

extern RxCluster   *
RxClusterSetStride(RxCluster * cluster,
                   RwInt32 stride);

extern RxCluster   *
RxClusterSetExternalData(RxCluster * cluster,
                         void *data,
                         RwInt32 stride,
                         RwInt32 numElements);

extern RxCluster   *
RxClusterSetData(RxCluster * cluster,
                 void *data,
                 RwInt32 stride,
                 RwInt32 numElements);

/* underlying PacketDestroy function */
extern void
_rxPacketDestroy(RxPacket * Packet);

/* more convenient parameterization */
#define RxPacketDestroy(pk, self) \
    ( _rxPacketDestroy(pk) )

#if (defined(RWDEBUG))
extern RxPacket *RxPacketFetch(RxPipelineNode * Node);
extern void      RxPacketDispatch(RxPacket * packet,
                                  RwUInt32 output,
                                  RxPipelineNode * self);
extern void      RxPacketDispatchToPipeline(RxPacket * packet,
                                            RxPipeline * dest,
                                            RxPipelineNode * self);
#else /* (defined(RWDEBUG)) */
#define RxPacketFetch(_self) \
    rxPacketFetchMacro(_self)
#define RxPacketDispatch(     _packet, _output, _self) \
    rxPacketDispatchMacro(_packet, _output, _self)
#define RxPacketDispatchToPipeline(     _packet, _pipeline, _self) \
    rxPacketDispatchToPipelineMacro(_packet, _pipeline, _self)
#endif /* (defined(RWDEBUG)) */

#define RxClusterInitialiseData(_clstr, _nmlmnts, _strd) \
    ( RxClusterInitializeData((_clstr), (_nmlmnts), (_strd)) )
extern RxCluster   *
RxClusterInitializeData(RxCluster *cluster, RwUInt32 numElements, RwUInt16 stride);

extern RxCluster   *
RxClusterResizeData(RxCluster *CurrentCluster, RwUInt32 NumElements);

extern RxCluster   *
RxClusterDestroyData(RxCluster *CurrentCluster);

#if (defined(RWDEBUG))

extern RxCluster *RxClusterLockRead(RxPacket * packet, RwUInt32 clusterIndex);

#else  /* !RWDEBUG */

#define RXCLSLOT(PKT, CLIND)             \
    ((PKT)->inputToClusterSlot[(CLIND)])

#define RxClusterLockRead(PKT, CLIND)                               \
    ( (((RwInt32)RXCLSLOT(PKT, CLIND)) == -1) ?                     \
      ((RxCluster *)NULL) :                                         \
      (RxClusterResetCursor(&PKT->clusters[RXCLSLOT(PKT, CLIND)]),  \
       &PKT->clusters[RXCLSLOT(PKT, CLIND)]) )

#endif /* !RWDEBUG */

extern RxCluster   *
RxClusterLockWrite(RxPacket * packet,
                   RwUInt32 clusterIndex,
                   RxPipelineNode * node);

extern void
RxClusterUnlock(RxCluster * cluster);

extern RwUInt32
RxPipelineNodeSendConfigMsg(RxPipelineNode * dest,
                            RwUInt32 msg,
                            RwUInt32 intparam,
                            void *ptrparam);

extern RxPipelineNode *
RxPipelineNodeForAllConnectedOutputs(RxPipelineNode * node,
                                     RxPipeline * pipeline,
                                     RxPipelineNodeOutputCallBack callbackfn,
                                     void *callbackdata);

/* Cluster attributes api [pipeline construction time] */

extern RxPipelineCluster *
RxPipelineNodeGetPipelineCluster(RxPipelineNode *node,
                                   RwUInt32 clustersOfInterestIndex);

extern RwUInt32
RxPipelineClusterGetCreationAttributes(RxPipelineCluster *cluster);

extern RxPipelineCluster *
RxPipelineClusterSetCreationAttributes(RxPipelineCluster *cluster,
                                         RwUInt32 creationAttributes);

/* Cluster attributes api [pipeline execution time] */

extern RwUInt32
RxClusterGetAttributes(RxCluster *cluster);

extern RxCluster *
RxClusterSetAttributes(RxCluster *cluster, RwUInt32 attributes);


extern void
_rxEmbeddedPacketBetweenPipelines(RxPipeline * fromPipeline,
                                 RxPipeline * toPipeline);

extern RxPipelineNode *
_rxEmbeddedPacketBetweenNodes(RxPipeline     *pipeline,
                             RxPipelineNode *nodeFrom,
                             RwUInt32        whichOutput);

extern RxExecutionContext _rxExecCtxGlobal;

/* Summary of dispatch rules:
 * o nodes that never fetch are safe to dispatch NULL, whether
 *   nodes above pass them a packet or not
 * o if you destroy the packet you can dispatch(NULL,,)
 * o if you fetch/create and dispatch(NULL), it doesn't really
 *   matter - the packet'll get passed on anyway */

/* TODO: there's currently no way to prematurely terminate the pipeline
 *      without doing so as an error condition. You should create an
 *      enum for the exit code, either RXNODEEXITCONTINUE, RXNODEEXITTERMINATE
 *      or RXNODEEXTTERMINATEERROR and then test for RXNODEEXITCONTINUE in
 *      the below macros rather than FALSE. */

/* TODO: _packet redundant here... create a new macro and legacy wrapper */
#define rxPacketDispatchMacro(_packet, _output, _self)                      \
MACRO_START                                                                 \
{                                                                           \
    RxPipeline *curPipeline = _rxExecCtxGlobal.pipeline;                    \
                                                                            \
    /* _packet is now an obsolete parameter */                              \
                                                                            \
    if ( FALSE != _rxExecCtxGlobal.exitCode )                               \
    {                                                                       \
        RxPipelineNode *nextNode =                                          \
            _rxEmbeddedPacketBetweenNodes(curPipeline,                      \
                                         _self,                             \
                                         (_output));                        \
        if ( nextNode != NULL )                                             \
        {                                                                   \
            RwUInt32 exitCode =                                             \
                nextNode->nodeDef->nodeMethods.nodeBody(                    \
                    nextNode, &(_rxExecCtxGlobal.params));                  \
            /* Don't overwrite 'error' with 'success' */                    \
            if (FALSE == exitCode) _rxExecCtxGlobal.exitCode = exitCode;    \
        }                                                                   \
    }                                                                       \
    if ( curPipeline->embeddedPacketState > rxPKST_UNUSED                   \
         /* !UNUSED and !PACKETLESS */ )                                    \
    {                                                                       \
        curPipeline->embeddedPacketState = rxPKST_INUSE;                    \
        _rxPacketDestroy(curPipeline->embeddedPacket);                      \
    }                                                                       \
}                                                                           \
MACRO_STOP

/* TODO: _self redundant here... create a new macro and legacy wrapper */
#define rxPacketDispatchToPipelineMacro(_packet, _pipeline, _self)          \
MACRO_START                                                                 \
{                                                                           \
    RxPipeline *toPipeline = (_pipeline);                                   \
                                                                            \
    /* _packet is now an obsolete parameter */                              \
                                                                            \
    if ( FALSE != _rxExecCtxGlobal.exitCode )                               \
    {                                                                       \
        RwUInt32 exitCode;                                                  \
        RxPipeline *fromPipeline = _rxExecCtxGlobal.pipeline; /* save */    \
        _rxEmbeddedPacketBetweenPipelines(fromPipeline,                     \
                                         toPipeline);                       \
        _rxExecCtxGlobal.pipeline = toPipeline; /* modify */                \
        exitCode =                                                          \
            toPipeline->nodes[0].nodeDef->nodeMethods.nodeBody(             \
                &toPipeline->nodes[0], &(_rxExecCtxGlobal.params));         \
        if ( FALSE == exitCode ) _rxExecCtxGlobal.exitCode = exitCode;      \
        _rxExecCtxGlobal.pipeline = fromPipeline; /* restore */             \
    }                                                                       \
    if ( toPipeline->embeddedPacketState > rxPKST_UNUSED                    \
         /* !UNUSED and !PACKETLESS */ )                                    \
    {                                                                       \
        toPipeline->embeddedPacketState = rxPKST_INUSE;                     \
        _rxPacketDestroy(toPipeline->embeddedPacket);                       \
    }                                                                       \
}                                                                           \
MACRO_STOP

#define rxPacketFetchMacro(_node)                                           \
    ( ((_rxExecCtxGlobal.pipeline)->embeddedPacketState == rxPKST_PENDING) ?\
      ((_rxExecCtxGlobal.pipeline)->embeddedPacketState = rxPKST_INUSE,     \
       (_rxExecCtxGlobal.pipeline)->embeddedPacket) :                       \
      (NULL) )

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/d3d8/nodeD3D8SubmitNoLight.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2define.h ---*/

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeOutput 
 * typedef for a reference to an output of a pipeline node */
typedef RwUInt32       *RxNodeOutput;

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeInput 
 *  typedef for a reference to the input of a pipeline node */
typedef RxPipelineNode *RxNodeInput;

/**
 * \ingroup rwcoregeneric
 * \ref RxLockedPipe
 * typedef for a reference to a locked pipeline 
 */
typedef RxPipeline      RxLockedPipe;


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */


/* PIPELINENODE API */

extern RxNodeOutput
RxPipelineNodeFindOutputByName(RxPipelineNode *node,
                               const RwChar *outputname);

extern RxNodeOutput
RxPipelineNodeFindOutputByIndex(RxPipelineNode *node,
                                RwUInt32 outputindex);

extern RxNodeInput
RxPipelineNodeFindInput(RxPipelineNode *node);

extern RxNodeDefinition *
RxPipelineNodeCloneDefinition(RxPipelineNode *node,
                              RxClusterDefinition *cluster2add);

extern RxPipeline *
RxPipelineNodeRequestCluster(RxPipeline *pipeline,
                             RxPipelineNode *node,
                             RxClusterDefinition *clusterDef);

extern RxPipeline *
RxPipelineNodeReplaceCluster(RxPipeline *pipeline,
                             RxPipelineNode *node,
                             RxClusterDefinition *oldClusterDef,
                             RxClusterDefinition *newClusterDef);

extern void *
RxPipelineNodeGetInitData(RxPipelineNode *node);

extern void *
RxPipelineNodeCreateInitData(RxPipelineNode *node,
                             RwUInt32 size);

/* PIPELINE MANIPULATION API */

extern RxPipeline *
RxPipelineClone(RxPipeline *pipeline);

extern RxPipelineNode *
RxPipelineFindNodeByName(RxPipeline *pipeline,
                         const RwChar *name,
                         RxPipelineNode *start,
                         RwInt32 *nodeIndex);

extern RxPipelineNode *
RxPipelineFindNodeByIndex(RxPipeline *pipeline,
                          RwUInt32 nodeindex);

extern RxLockedPipe *
RxPipelineLock(RxPipeline *pipeline);

extern RxPipeline *
RxLockedPipeUnlock(RxLockedPipe *pipeline);


extern RxLockedPipe *
RxLockedPipeAddFragment(RxLockedPipe *pipeline,
                        RwUInt32 *firstIndex,
                        RxNodeDefinition *nodeDef0,
                        ...);


extern RxPipeline *
RxLockedPipeReplaceNode(RxLockedPipe *pipeline,
                        RxPipelineNode *node,
                        RxNodeDefinition *nodeDef);

extern RxPipeline *
RxLockedPipeDeleteNode(RxLockedPipe *pipeline,
                       RxPipelineNode *node);


extern RxPipeline *
RxLockedPipeSetEntryPoint(RxLockedPipe *pipeline,
                          RxNodeInput in);


extern RxPipelineNode *
RxLockedPipeGetEntryPoint(RxLockedPipe *pipeline);


extern RxPipeline *
RxLockedPipeAddPath(RxLockedPipe *pipeline,
                    RxNodeOutput out,
                    RxNodeInput in);

extern RxPipeline *
RxLockedPipeDeletePath(RxLockedPipe *pipeline,
                       RxNodeOutput out,
                       RxNodeInput in);


extern RxPipeline *
RxPipelineInsertDebugNode(RxPipeline *pipeline,
                          RxPipelineNode *before,
                          RxPipelineNode *after,
                          RxNodeDefinition *debugNode);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2altmdl.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8texdic.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8rendst.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8raster.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8device.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8convrt.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d82drend.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/common/ssematml.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/common/cpuext.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/common/palquant.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/common/datblkcb.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/baraster.h ---*/

/****************************************************************************
 Defines
 */

/**
 * \ingroup rwraster
 * \ref RwRasterLockMode represents the options available for locking 
 * a raster so that it may be modified (see API function \ref RwRasterLock). An 
 * application may wish to write to the raster, read from the raster or
 * simultaneously write and read a raster (rwRASTERLOCKWRITE | rwRASTERLOCKREAD).
 */
enum RwRasterLockMode
{
    rwRASTERLOCKWRITE = 0x01,   /**<Lock for writing */
    rwRASTERLOCKREAD = 0x02,    /**<Lock for reading */
    rwRASTERLOCKNOFETCH = 0x04, /**<When used in combination with
                                 *  rwRASTERLOCKWRITE, asks the driver not to
                                 *  fetch the pixel data. This is only useful
                                 *  if it is known that ALL the raster data is
                                 *  going to be overwritten before the raster
                                 *  is unlocked, i.e. from an 
                                 *  \ref RwRasterSetFromImage call. This flag
                                 *  is not supported by all drivers. */
    rwRASTERLOCKRAW = 0x08,    /**<When used in combination with
                                   rwRASTERLOCKWRITE or rwRASTERLOCKREAD
                                   allows access to the raw platform specific
                                   pixel format */
    rwRASTERLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

#define rwRASTERLOCKREADWRITE   (rwRASTERLOCKREAD|rwRASTERLOCKWRITE)

typedef enum RwRasterLockMode RwRasterLockMode;

/**
 * \ingroup rwraster
 *  \ref RwRasterFlipMode represents
 *  raster flip modes */
enum RwRasterFlipMode
{
    rwRASTERFLIPDONTWAIT = 0,   /**<Don't wait for VSync */
    rwRASTERFLIPWAITVSYNC = 1,  /**<Flip on VSync */
    rwRASTERFLIPMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFlipMode RwRasterFlipMode;

/**
 * \ingroup rwraster
 *  RwRasterType 
 *  This type represents the options available for creating a new 
 * raster (se API function \ref RwRasterCreate)*/
enum RwRasterType
{
    rwRASTERTYPENORMAL = 0x00,          /**<Normal */
    rwRASTERTYPEZBUFFER = 0x01,         /**<Z Buffer */
    rwRASTERTYPECAMERA = 0x02,          /**<Camera */
    rwRASTERTYPETEXTURE = 0x04,         /**<Texture */
    rwRASTERTYPECAMERATEXTURE = 0x05,   /**<Camera texture */
    rwRASTERTYPEMASK = 0x07,            /**<Mask for finding type */

    rwRASTERDONTALLOCATE = 0x80,        /**<If set the raster is not allocated */
    rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterType RwRasterType;

/**
 * \ingroup rwraster
 * \ref RwRasterFormat is a set of values and flags which may be combined to
 * specify a raster format. The format chosen for a particular raster depends
 * on the hardware device and the raster type specified at creation time
 * (see API function \ref RwRasterCreate). The format may be retrieved using
 * API function \ref RwRasterGetFormat.
 *
 * The raster format is a packed set of bits which contains the following
 * four pieces of information (these may be combined with bitwise OR):-
 *
 * <ol>
 * <li> The pixel color format corresponding to one of the following values:-
 *      <ul>
 *      <li> rwRASTERFORMAT1555
 *      <li> rwRASTERFORMAT565
 *      <li> rwRASTERFORMAT4444
 *      <li> rwRASTERFORMATLUM8
 *      <li> rwRASTERFORMAT8888
 *      <li> rwRASTERFORMAT888
 *      <li> rwRASTERFORMAT16
 *      <li> rwRASTERFORMAT24
 *      <li> rwRASTERFORMAT32
 *      <li> rwRASTERFORMAT555
 *      </ul>
 *      This value may be masked out of the raster format using
 *      rwRASTERFORMATPIXELFORMATMASK.
 * <li> The palette depth if the raster is palettized:-
 *      <ul> 
 *      <li> rwRASTERFORMATPAL4
 *      <li> rwRASTERFORMATPAL8
 *      </ul>
 *      In these cases, the color format refers to that of the palette.
 * <li> Flag rwRASTERFORMATMIPMAP. Set if the raster contains mipmap levels.
 * <li> Flag rwRASTERFORMATAUTOMIPMAP. Set if the mipmap levels were generated
 *      automatically by RenderWare.
 * </ol>
 */
enum RwRasterFormat
{
    rwRASTERFORMATDEFAULT = 0x0000, /* Whatever the hardware likes best */

    rwRASTERFORMAT1555 = 0x0100,    /**<16 bits - 1 bit alpha, 5 bits red, green and blue */
    rwRASTERFORMAT565 = 0x0200,     /**<16 bits - 5 bits red and blue, 6 bits green */
    rwRASTERFORMAT4444 = 0x0300,    /**<16 bits - 4 bits per component */
    rwRASTERFORMATLUM8 = 0x0400,    /**<Gray scale */
    rwRASTERFORMAT8888 = 0x0500,    /**<32 bits - 8 bits per component */
    rwRASTERFORMAT888 = 0x0600,     /**<24 bits - 8 bits per component */
    rwRASTERFORMAT16 = 0x0700,      /**<16 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT24 = 0x0800,      /**<24 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT32 = 0x0900,      /**<32 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT555 = 0x0a00,     /**<16 bits - 5 bits red, green and blue */

    rwRASTERFORMATAUTOMIPMAP = 0x1000, /**<RenderWare generated the mip levels */

    rwRASTERFORMATPAL8 = 0x2000,    /**<8 bit palettised */
    rwRASTERFORMATPAL4 = 0x4000,    /**<4 bit palettised */

    rwRASTERFORMATMIPMAP = 0x8000,  /**<Mip mapping on */

    rwRASTERFORMATPIXELFORMATMASK = 0x0f00, /**<The pixel color format 
                                             *  (excluding palettised bits) */
    rwRASTERFORMATMASK = 0xff00     /**<The whole format */ ,
    rwRASTERFORMATFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFormat RwRasterFormat;

enum RwRasterPrivateFlag
{
    rwRASTERGAMMACORRECTED = 0x01,
    rwRASTERPIXELLOCKEDREAD = 0x02, /* pixels are locked for reading */
    rwRASTERPIXELLOCKEDWRITE = 0x04, /* pixels are locked for writing */
    rwRASTERPALETTELOCKEDREAD = 0x08, /* palette is locked for reading */
    rwRASTERPALETTELOCKEDWRITE = 0x10, /* palette is locked for writing */
    rwRASTERPIXELLOCKEDRAW = 0x20, /* the pixels are in platform specific
                                      format, used in combination with
                                      rwRASTERPIXELLOCKEDREAD &
                                      rwRASTERPIXELLOCKEDWRITE */
    rwRASTERPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterPrivateFlag RwRasterPrivateFlag;

#define rwRASTERPIXELLOCKED     (rwRASTERPIXELLOCKEDREAD | rwRASTERPIXELLOCKEDWRITE)
#define rwRASTERPALETTELOCKED   (rwRASTERPALETTELOCKEDREAD | rwRASTERPALETTELOCKEDWRITE)
#define rwRASTERLOCKED          (rwRASTERPIXELLOCKED|rwRASTERPALETTELOCKED)

/* How big is my stack!!! */
#define rwRASTERCONTEXTSTACKSIZE 10

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwraster
 * \struct RwRaster 
 * Raster containing device-dependent pixels. 
 * This should be considered an opaque type.
 * Use the RwRaster API functions to access.
 */
typedef struct RwRaster RwRaster;

#if (!defined(DOXYGEN))
struct RwRaster
{
    RwRaster           *parent; /* Top level raster if a sub raster */
    RwUInt8            *cpPixels; /* Pixel pointer when locked */
    RwUInt8            *palette; /* Raster palette */
    RwInt32             width, height, depth; /* Dimensions of raster */
    RwInt32             stride; /* Lines bytes of raster */
    RwInt16             nOffsetX, nOffsetY; /* Sub raster offset */
    RwUInt8             cType;  /* Type of raster */
    RwUInt8             cFlags; /* Raster flags */
    RwUInt8             privateFlags; /* Raster private flags */
    RwUInt8             cFormat; /* Raster format */

    RwUInt8            *originalPixels;
    RwInt32             originalWidth;
    RwInt32             originalHeight;
    RwInt32             originalStride;
};
#endif /* (!defined(DOXYGEN)) */


/****************************************************************************
 <macro/inline functionality
 */

#define RwRasterGetWidthMacro(_raster) \
    ((_raster)->width)

#define RwRasterGetHeightMacro(_raster) \
    ((_raster)->height)

#define RwRasterGetStrideMacro(_raster) \
    ((_raster)->stride)

#define RwRasterGetDepthMacro(_raster) \
    ((_raster)->depth)

#define RwRasterGetFormatMacro(_raster) \
    ((((_raster)->cFormat) & (rwRASTERFORMATMASK >> 8)) << 8)

#define RwRasterGetTypeMacro(_raster) \
    (((_raster)->cType) & rwRASTERTYPEMASK)

#define RwRasterGetParentMacro(_raster) \
    ((_raster)->parent)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwRasterGetWidth(_raster)                   \
    RwRasterGetWidthMacro(_raster)

#define RwRasterGetHeight(_raster)                  \
    RwRasterGetHeightMacro(_raster)

#define RwRasterGetStride(_raster)                  \
    RwRasterGetStrideMacro(_raster)

#define RwRasterGetDepth(_raster)                   \
    RwRasterGetDepthMacro(_raster)

#define RwRasterGetFormat(_raster)                  \
    RwRasterGetFormatMacro(_raster)

#define RwRasterGetType(_raster)                  \
    RwRasterGetTypeMacro(_raster)

#define RwRasterGetParent(_raster)                  \
    RwRasterGetParentMacro(_raster)

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Creating destroying rasters */
extern void RwRasterSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwRaster    *RwRasterCreate(RwInt32 width, RwInt32 height,
                                   RwInt32 depth, RwInt32 flags);
extern RwBool       RwRasterDestroy(RwRaster * raster);

/* Pulling info out of raster structure */

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwInt32      RwRasterGetWidth(const RwRaster *raster);
extern RwInt32      RwRasterGetHeight(const RwRaster *raster);
extern RwInt32      RwRasterGetStride(const RwRaster *raster);
extern RwInt32      RwRasterGetDepth(const RwRaster *raster);
extern RwInt32      RwRasterGetFormat(const RwRaster *raster);
extern RwInt32      RwRasterGetType(const RwRaster *raster);
extern RwRaster    *RwRasterGetParent(const RwRaster *raster);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern RwRaster    *RwRasterGetOffset(RwRaster *raster, 
                                      RwInt16 *xOffset, RwInt16 *yOffset);

extern RwInt32      RwRasterGetNumLevels(RwRaster * raster);

extern RwRaster    *RwRasterSubRaster(RwRaster * subRaster,
                                      RwRaster * raster, RwRect * rect);

extern RwRaster    *RwRasterRenderFast(RwRaster * raster, RwInt32 x,
                                       RwInt32 y);
extern RwRaster    *RwRasterRender(RwRaster * raster, RwInt32 x,
                                       RwInt32 y);
extern RwRaster    *RwRasterRenderScaled(RwRaster * raster,
                                         RwRect * rect);

/* Raster rendering context */
extern RwRaster    *RwRasterPushContext(RwRaster * raster);
extern RwRaster    *RwRasterPopContext(void);
extern RwRaster    *RwRasterGetCurrentContext(void);

/* Clearing rasters */
extern RwBool       RwRasterClear(RwInt32 pixelValue);
extern RwBool       RwRasterClearRect(RwRect * rpRect,
                                          RwInt32 pixelValue);

/* Displaying rasters */
extern RwRaster    *RwRasterShowRaster(RwRaster * raster, void *dev,
                                       RwUInt32 flags);

/* Locking and releasing */
extern RwUInt8     *RwRasterLock(RwRaster * raster, RwUInt8 level,
                                 RwInt32 lockMode);
extern RwRaster    *RwRasterUnlock(RwRaster * raster);
extern RwUInt8     *RwRasterLockPalette(RwRaster * raster,
                                        RwInt32 lockMode);
extern RwRaster    *RwRasterUnlockPalette(RwRaster * raster);

/* Attaching toolkits */
extern RwInt32      RwRasterRegisterPlugin(RwInt32 size,
                                           RwUInt32 pluginID,
                                           RwPluginObjectConstructor
                                           constructCB,
                                           RwPluginObjectDestructor
                                           destructCB,
                                           RwPluginObjectCopy copyCB);
extern RwInt32      RwRasterGetPluginOffset(RwUInt32 pluginID);
extern RwBool       RwRasterValidatePlugins(const RwRaster * raster);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/drvmodel.h ---*/
#ifndef D3D8_DRVMODEL_H
#define D3D8_DRVMODEL_H

#if (defined(__ICL))
/* Avoid voluminous
 *   'warning #344: typedef name has already been declared (with same type)'
 * warnings from MS include files
 */
#pragma warning( disable : 344 )
#endif /* (defined(__ICL)) */


#if (defined(RWDEBUG))
#if (defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC))
#define _CRTDBG_MAP_ALLOC
#endif /* defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC)) */
#include <crtdbg.h>
#define ERR_WRAP(A) (_rwRePrintErrorDDD3D((A), __FILE__, __LINE__))
#endif /* (defined(RWDEBUG)) */

#if (!defined(ERR_WRAP))
#define ERR_WRAP(A) (A)
#endif /* (!defined(ERR_WRAP)) */

/****************************************************************************
 Defines
 */

/* Set true depth information (for fogging, eg) */
#define RwIm2DVertexSetCameraX(vert, camx)          /* Nothing */
#define RwIm2DVertexSetCameraY(vert, camy)          /* Nothing */
#define RwIm2DVertexSetCameraZ(vert, camz)          /* Nothing */

#define RwIm2DVertexSetRecipCameraZ(vert, recipz)   ((vert)->rhw = recipz)

#define RwIm2DVertexGetCameraX(vert)                (cause an error)
#define RwIm2DVertexGetCameraY(vert)                (cause an error)
#define RwIm2DVertexGetCameraZ(vert)                (cause an error)
#define RwIm2DVertexGetRecipCameraZ(vert)           ((vert)->rhw)

/* Set screen space coordinates in a device vertex */
#define RwIm2DVertexSetScreenX(vert, scrnx)         ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny)         ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz)         ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert)                ((vert)->x)
#define RwIm2DVertexGetScreenY(vert)                ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert)                ((vert)->z)

/* Set texture coordinates in a device vertex */
#define RwIm2DVertexSetU(vert, texU, recipz)        ((vert)->u = (texU))
#define RwIm2DVertexSetV(vert, texV, recipz)        ((vert)->v = (texV))
#define RwIm2DVertexGetU(vert)                      ((vert)->u)
#define RwIm2DVertexGetV(vert)                      ((vert)->v)

/* Modify the luminance stuff */
#define RwIm2DVertexSetRealRGBA(vert, red, green, blue, alpha)  \
    ((vert)->emissiveColor =                                    \
     (((RwFastRealToUInt32(alpha)) << 24) |                        \
      ((RwFastRealToUInt32(red)) << 16) |                          \
      ((RwFastRealToUInt32(green)) << 8) |                         \
      ((RwFastRealToUInt32(blue)))))

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)   \
    ((vert)->emissiveColor =                                    \
     ((((RwUInt32)(alpha)) << 24) |                             \
      (((RwUInt32)(red)) << 16) |                               \
      (((RwUInt32)(green)) << 8) |                              \
      (((RwUInt32)(blue)))))

#define RwIm2DVertexGetRed(vert)    \
    (((vert)->emissiveColor >> 16) & 0xFF)

#define RwIm2DVertexGetGreen(vert)  \
    (((vert)->emissiveColor >> 8) & 0xFF)

#define RwIm2DVertexGetBlue(vert)   \
    ((vert)->emissiveColor & 0xFF)

#define RwIm2DVertexGetAlpha(vert)  \
    (((vert)->emissiveColor >> 24) & 0xFF)

#define RwIm2DVertexCopyRGBA(dst, src)  \
    ((dst)->emissiveColor = (src)->emissiveColor)

/* Clipper stuff */

#define RwIm2DVertexClipRGBA(o, i, n, f)                                \
MACRO_START                                                             \
{                                                                       \
    const RwInt32        _factor =                                      \
        (RwFastRealToUInt32(i * (RwReal)(255))) & 255;                  \
                                                                        \
    (o)->emissiveColor =                                                \
        (((((RwIm2DVertexGetAlpha(f) - RwIm2DVertexGetAlpha(n)) *       \
            _factor) >> 8) + RwIm2DVertexGetAlpha(n)) << 24) |          \
        (((((RwIm2DVertexGetRed(f) - RwIm2DVertexGetRed(n)) *           \
            _factor) >> 8) + RwIm2DVertexGetRed(n)) << 16) |            \
        (((((RwIm2DVertexGetGreen(f) - RwIm2DVertexGetGreen(n)) *       \
            _factor) >> 8) + RwIm2DVertexGetGreen(n)) << 8) |           \
        (((((RwIm2DVertexGetBlue(f) - RwIm2DVertexGetBlue(n)) *         \
            _factor) >> 8) + RwIm2DVertexGetBlue(n)));                  \
}                                                                       \
MACRO_STOP

/****************************************************************************
 Global Types
 */

/* We use RwD3D8Vertex to drive the hardware in 2D mode */

/*
 * D3D8 vertex structure definition for 2D geometry
 */
#if !defined(RWADOXYGENEXTERNAL)
typedef struct RwD3D8Vertex RwD3D8Vertex;
/**
 * \ingroup rwcoredriverd3d8
 * \struct RwD3D8Vertex
 * D3D8 vertex structure definition for 2D geometry
 */
struct RwD3D8Vertex
{
    RwReal      x;              /**< Screen X */
    RwReal      y;              /**< Screen Y */
    RwReal      z;              /**< Screen Z */
    RwReal      rhw;            /**< Reciprocal of homogeneous W */

    RwUInt32    emissiveColor;  /**< Vertex color */

    RwReal      u;              /**< Texture coordinate U */
    RwReal      v;              /**< Texture coordinate V */
};
#endif /* !defined(RWADOXYGENEXTERNAL) */

/* Define types used */

#if !defined(RWADOXYGENEXTERNAL)
/**
 * \ingroup rwcoredriverd3d8
 * \ref RwIm2DVertex
 * Typedef for a RenderWare Graphics Immediate Mode 2D Vertex
 */
typedef RwD3D8Vertex    RwIm2DVertex;
#endif /* !defined(RWADOXYGENEXTERNAL) */

#if !defined(RWADOXYGENEXTERNAL)
/**
 * \ingroup rwcoredriverd3d8
 * \ref RxVertexIndex
 *
 * Typedef for a RenderWare Graphics PowerPipe Immediate
 * Mode Vertex
 */
typedef RwUInt16        RxVertexIndex;
#endif /* !defined(RWADOXYGENEXTERNAL) */

#if !defined(RWADOXYGENEXTERNAL)

/**
 * \ingroup rwcoredriverd3d8
 * \ref RwImVertexIndex
 * Typedef for a RenderWare Graphics Immediate Mode Vertex.
 */
typedef RxVertexIndex   RwImVertexIndex;
#endif /* !defined(RWADOXYGENEXTERNAL) */

#if !defined(RWADOXYGENEXTERNAL)

/**
 * \ingroup rwcoredriverd3d8
 * \struct RwD3D8Metrics
 * Structure containing metrics counters
 */
typedef struct
{
    RwUInt32    numRenderStateChanges;          /**< Number of Render States changed */
    RwUInt32    numTextureStageStateChanges;    /**< Number of Texture Stage States changed */
    RwUInt32    numMaterialChanges;             /**< Number of Material changes */
    RwUInt32    numLightsChanged;               /**< Number of Lights changed */
    RwUInt32    numVBSwitches;                  /**< Number of Vertex Buffer switches */
}
RwD3D8Metrics;
#endif /* !defined(RWADOXYGENEXTERNAL) */

#endif /* D3D8_DRVMODEL_H */

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/d3d8/pip2model.h ---*/





/****************************************************************************
 Global Defines
 */

#define RXHEAPPLATFORMDEFAULTSIZE  (1 << 12) /* 4k */

/****************************************************************************
 Global Types
 */

/* We use D3D8 formats for the instanced versions, to allow hardware T&L */

/*
 * Typedef for an RxObjSpace3DVertex.
 */
typedef struct RxObjSpace3DVertex RxObjSpace3DVertex;

/**
 * \ingroup cored3d8
 * \struct RxObjSpace3DVertex
 * Structure representing object space vertex.
 */
struct RxObjSpace3DVertex
{
    RwV3d       objVertex;        /**< position */
    RwV3d       objNormal;        /**< normal */
    RwUInt32    color;            /**< emissive color*/
    RwReal      u;                /**< u */
    RwReal      v;                /**< v */
};

/* This vertex is non truncatable */
#define RxObjSpace3DVertexNoUVsNoNormalsSize (sizeof(RxObjSpace3DVertex))
#define RxObjSpace3DVertexNoUVsSize          (sizeof(RxObjSpace3DVertex))
#define RxObjSpace3DVertexFullSize           (sizeof(RxObjSpace3DVertex))

/**
 * \ingroup cored3d8
 * \ref RxObjSpace3DLitVertex
 * Typedef for an RxObjSpace3DLitVertex.
 */
typedef RxObjSpace3DVertex RxObjSpace3DLitVertex;

/** 
 * \ingroup cored3d8
 * \ref RwIm3DVertex
 * Typedef for an RwIm3DVertex.
 */
typedef RxObjSpace3DLitVertex RwIm3DVertex;

/* LEGACY-SUPPORT macro */
/**
 * \ingroup cored3d8
 * \ref RxScrSpace2DVertex
 * Typedef for an RxScrSpace2DVertex structure
 */
typedef RwIm2DVertex RxScrSpace2DVertex;

/****************************************************************************
 Object-space 3D unlit vertex macros
 */

/* Vertex positions */
#define RxObjSpace3DVertexGetPos(_vert, _pos) \
    (*(_pos) = (_vert)->objVertex)
#define RxObjSpace3DVertexSetPos(_vert, _pos) \
    ((_vert)->objVertex = *(_pos))

/* Pre-lighting colours */
#define RxObjSpace3DVertexGetPreLitColor(_vert, _col) \
MACRO_START \
{ \
    (_col)->alpha = (RwUInt8)((_vert)->color >> 24) & 0xFF; \
    (_col)->red   = (RwUInt8)((_vert)->color >> 16) & 0xFF; \
    (_col)->green = (RwUInt8)((_vert)->color >>  8) & 0xFF; \
    (_col)->blue  = (RwUInt8)((_vert)->color      ) & 0xFF; \
} \
MACRO_STOP

#define RxObjSpace3DVertexSetPreLitColor(_vert, _col) \
    ((_vert)->color = (((RwUInt32)(_col)->alpha) << 24) | \
                              (((RwUInt32)(_col)->red)   << 16) | \
                              (((RwUInt32)(_col)->green) <<  8) | \
                              (((RwUInt32)(_col)->blue)       ))

/* This uses the same slot as color (they are mutually exclusive) */
#define RxObjSpace3DVertexGetColor RxObjSpace3DVertexGetPreLitColor

/* Normals */
#define RxObjSpace3DVertexGetNormal(_vert, _normal)             \
    (*(_normal) = (_vert)->objNormal)
#define RxObjSpace3DVertexSetNormal(_vert, _normal)             \
    ((_vert)->objNormal = *(_normal))

/* Us and Vs */
#define RxObjSpace3DVertexGetU(_vert)                          \
    ((_vert)->u)
#define RxObjSpace3DVertexGetV(_vert)                          \
    ((_vert)->v)
#define RxObjSpace3DVertexSetU(_vert, _imu)                     \
    ((_vert)->u = (_imu))
#define RxObjSpace3DVertexSetV(_vert, _imv)                     \
    ((_vert)->v = (_imv))

/****************************************************************************
 Object-space 3D lit vertex macros
 */

/* Vertex positions */
#define RxObjSpace3DLitVertexGetPos(_vert, _pos) \
    (*(_pos) = (_vert)->objVertex)
#define RxObjSpace3DLitVertexSetPos(_vert, _pos) \
    ((_vert)->objVertex = *(_pos))

/* Vertex colours */
#define RxObjSpace3DLitVertexGetColor(_vert, _col) \
MACRO_START \
{ \
    (_col)->red   = ((_vert)->color >> 16) & 0xFF; \
    (_col)->green = ((_vert)->color >>  8) & 0xFF; \
    (_col)->blue  = ((_vert)->color      ) & 0xFF; \
    (_col)->alpha = ((_vert)->color >> 24) & 0xFF; \
} \
MACRO_STOP
#define RxObjSpace3DLitVertexSetColor(_vert, _col) \
    ((_vert)->color = (((RwUInt32)(_col)->alpha) << 24) | \
                              (((RwUInt32)(_col)->red)   << 16) | \
                              (((RwUInt32)(_col)->green) <<  8) | \
                              (((RwUInt32)(_col)->blue)       ))

/* Us and Vs */
#define RxObjSpace3DLitVertexGetU(_vert) \
    ((_vert)->u)
#define RxObjSpace3DLitVertexGetV(_vert) \
    ((_vert)->v)
#define RxObjSpace3DLitVertexSetU(_vert, _imu) \
    ((_vert)->u = (_imu))
#define RxObjSpace3DLitVertexSetV(_vert, _imv) \
    ((_vert)->v = (_imv))

/* LEGACY-SUPPORT for old objvert names - NB does NOT guarantee the
 * app will work, because the old IM3DVERTEX macros are NOT correctly
 * abstracted - 'Get' will return pointers to RwV3ds inside the
 * ObjVert, but you can't assume there are any RwV3ds inside an
 * opaque vertex type */

#define RwIm3DVertexSetU   RxObjSpace3DLitVertexSetU
#define RwIm3DVertexSetV   RxObjSpace3DLitVertexSetV
#define RwIm3DVertexGetNext(_vert)      ((_vert) + 1)

#define RwIm2DCameraVertexSetU(_devvert, _camvert, _u, _recipz) \
MACRO_START                                                     \
{                                                               \
    RwReal _uTmp = _u;                                          \
    _camvert->u = _uTmp;                                        \
    RwIm2DVertexSetU(_devvert, _uTmp, _recipz);                 \
}                                                               \
MACRO_STOP
#define RwIm2DCameraVertexSetV(_devvert, _camvert, _v, _recipz) \
MACRO_START                                                     \
{                                                               \
    RwReal _vTmp = _v;                                          \
    _camvert->v = _vTmp;                                        \
    RwIm2DVertexSetV(_devvert, _vTmp, _recipz);                 \
}                                                               \
MACRO_STOP

#define RwIm3DVertexSetPos(_vert, _imx, _imy, _imz) \
MACRO_START \
{ \
    (_vert)->objVertex.x = _imx; \
    (_vert)->objVertex.y = _imy; \
    (_vert)->objVertex.z = _imz; \
} \
MACRO_STOP

#define RwIm3DVertexSetNormal(vert, imx, imy, imz)         \
MACRO_START                                                \
{                                                          \
    RwV3d packed;                                          \
    packed.x = imx;                                        \
    packed.y = imy;                                        \
    packed.z = imz;                                        \
    RxObjSpace3DVertexSetNormal(vert, &packed);            \
}                                                          \
MACRO_STOP

#define RwIm3DVertexSetRGBA(_vert, _r, _g, _b, _a) \
MACRO_START \
{ \
    ((_vert)->color = ((_a) << 24) | \
                              ((_r) << 16) | \
                              ((_g) << 8) | \
                              ((_b))); \
} \
MACRO_STOP

#define RwIm3DVertexGetPos(_vert) (&((_vert)->objVertex))
#define RwIm3DVertexGetNormal(vert) (&((vert)->objNormal))

#define RwIm3DVertexCopyRGBA(_dst, _src) (((_dst)->color) = ((_src)->color))


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2renderstate.h ---*/

/**
 * \ingroup rwcoregeneric
 *  RxRenderStateFlag 
 *  Flags used in the \ref RxRenderStateVector structure */
enum RxRenderStateFlag
{
    rxRENDERSTATEFLAG_TEXTUREPERSPECTIVE   = 0x00000001, /**<Perspective texturing is to be enabled */
    rxRENDERSTATEFLAG_ZTESTENABLE          = 0x00000002, /**<Z-Buffer testing is to be performed */
    rxRENDERSTATEFLAG_ZWRITEENABLE         = 0x00000004, /**<Z-Buffer writing is to be enabled */
    rxRENDERSTATEFLAG_VERTEXALPHAENABLE    = 0x00000008, /**<Vertex alpha is to be enabled */
    rxRENDERSTATEFLAG_FOGENABLE            = 0x00000010, /**<Fog is to be enabled */
    rxRENDERSTATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxRenderStateFlag RxRenderStateFlag;

typedef struct RxRenderStateVector RxRenderStateVector;
/**
 * \ingroup rwcoregeneric
 * \struct RxRenderStateVector
 * Structure describing a render-state vector,
 * used by the RxClRenderState cluster */
struct RxRenderStateVector
{
    RwUInt32             Flags;         /**< A load of the boolean renderstate options */
    RwShadeMode          ShadeMode;     /**< Flat or Gouraud currently */
    RwBlendFunction      SrcBlend;      /**< Src  alpha, 1-src  alpha, etc */
    RwBlendFunction      DestBlend;     /**< Dest alpha, 1-dest alpha, etc */
    RwRaster            *TextureRaster; /**< texture raster */
    RwTextureAddressMode AddressModeU;  /**< U addressing mode - WRAP, MIRROR, CLAMP, BORDER */
    RwTextureAddressMode AddressModeV;  /**< V addressing mode - WRAP, MIRROR, CLAMP, BORDER */
    RwTextureFilterMode  FilterMode;    /**< filtering mode - combos of NEAREST LINEAR MIP */
    RwRGBA               BorderColor;   /**< Border color for texturing address mode border */
    RwFogType            FogType;       /**< Select the type of fogging to use */
    RwRGBA               FogColor;      /**< Color used for fogging */
};

#if (!defined(RxRenderStateVectorAssign))
#define RxRenderStateVectorAssign(_target, _source)            \
    ( *(_target) = *(_source) )
#endif /* (!defined(RxRenderStateVectorAssign)) */



#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern       RxRenderStateVector *RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector *rsvp);
extern const RxRenderStateVector *RxRenderStateVectorGetDefaultRenderStateVector(void);
extern       RxRenderStateVector *RxRenderStateVectorCreate(RwBool current);
extern       void                 RxRenderStateVectorDestroy(RxRenderStateVector *rsvp);
extern       RxRenderStateVector *RxRenderStateVectorLoadDriverState(RxRenderStateVector *rsvp);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/baimage.h ---*/

/****************************************************************************
 Defines
 */

/* If this bit is set then the image has been allocated by the user */

enum RwImageFlag
{
    rwNAIMAGEFLAG = 0x00,
    rwIMAGEALLOCATED = 0x1,
    rwIMAGEGAMMACORRECTED = 0x2,
    rwIMAGEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwImageFlag RwImageFlag;

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwimage
 * \struct RwImage 
 * Image containing device-independent pixels. 
 * This should be considered an opaque type.
 * Use the RwImage API functions to access.
 */
typedef struct RwImage RwImage;

#if (!defined(DOXYGEN))
struct RwImage
{
        RwInt32             flags;

        RwInt32             width;  /* Device may have different ideas */
        RwInt32             height; /* internally !! */

        RwInt32             depth;  /* Of referenced image */
        RwInt32             stride;

        RwUInt8            *cpPixels;
        RwRGBA             *palette;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwimage
 * \ref RwImageCallBackRead 
 * is the function registered with \ref RwImageRegisterImageFormat that is used,
 * for example by \ref RwImageRead and \ref RwImageReadMaskedImage,
 * to read images of a specific format from a disk file.
 * 
 * \param  imageName   Pointer to a string containing the file name of the image.
 *
 * \return Returns a pointer to the image read.
 *
 * \see RwImageRegisterImageFormat
 *
 */
typedef RwImage *(*RwImageCallBackRead)(const RwChar * imageName);

/**
 * \ingroup rwimage
 * \ref RwImageCallBackWrite 
 * is the function registered with \ref RwImageRegisterImageFormat that is used,
 * for example by \ref RwImageWrite, 
 * to write images of a specific format to a disk file.
 * 
 * \param  image   Pointer to the image.
 *
 * \param  imageName   Pointer to a string containing the file name
 * of the image.
 *
 *
 * \return Pointer to the written image.
 *
 * \see RwImageRegisterImageFormat
 *
 */
typedef RwImage *(*RwImageCallBackWrite)(RwImage *image, const RwChar *imageName);


/****************************************************************************
 <macro/inline functionality
 */

#define RwImageSetStrideMacro(_image, _stride)      \
    (((_image)->stride = (_stride)), (_image))

#define RwImageSetPixelsMacro(_image, _pixels)      \
    (((_image)->cpPixels = (_pixels)), (_image))

#define RwImageSetPaletteMacro(_image, _palette)    \
    (((_image)->palette = (_palette)), (_image))

#define RwImageGetWidthMacro(_image)                \
    ((_image)->width)

#define RwImageGetHeightMacro(_image)               \
    ((_image)->height)

#define RwImageGetDepthMacro(_image)                \
    ((_image)->depth)

#define RwImageGetStrideMacro(_image)               \
    ((_image)->stride)

#define RwImageGetPixelsMacro(_image)               \
    ((_image)->cpPixels)

#define RwImageGetPaletteMacro(_image)              \
    ((_image)->palette)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwImageSetStride(_image, _stride)           \
    RwImageSetStrideMacro(_image, _stride)

#define RwImageSetPixels(_image, _pixels)           \
    RwImageSetPixelsMacro(_image, _pixels)

#define RwImageSetPalette(_image, _palette)         \
    RwImageSetPaletteMacro(_image, _palette)

#define RwImageGetWidth(_image)                     \
    RwImageGetWidthMacro(_image)

#define RwImageGetHeight(_image)                    \
    RwImageGetHeightMacro(_image)

#define RwImageGetDepth(_image)                     \
    RwImageGetDepthMacro(_image)

#define RwImageGetStride(_image)                    \
    RwImageGetStrideMacro(_image)

#define RwImageGetPixels(_image)                    \
    RwImageGetPixelsMacro(_image)

#define RwImageGetPalette(_image)                   \
    RwImageGetPaletteMacro(_image)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

    /* Creating and destroying */

extern void RwImageSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void RwImageFormatSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwImage     *RwImageCreate(RwInt32 width, RwInt32 height,
                                  RwInt32 depth);
extern RwBool       RwImageDestroy(RwImage * image);

    /* Allocating */
extern RwImage     *RwImageAllocatePixels(RwImage * image);
extern RwImage     *RwImageFreePixels(RwImage * image);

    /* Converting images */
extern RwImage     *RwImageCopy(RwImage * destImage,
                                const RwImage * sourceImage);

    /* Resizing images */
extern RwImage     *RwImageResize(RwImage * image, RwInt32 width,
                                  RwInt32 height);

    /* Producing masks ! */
extern RwImage     *RwImageApplyMask(RwImage * image,
                                     const RwImage * mask);
extern RwImage     *RwImageMakeMask(RwImage * image);

    /* Helper functions */
extern RwImage     *RwImageReadMaskedImage(const RwChar * imageName,
                                           const RwChar * maskname);
extern RwImage     *RwImageRead(const RwChar * imageName);
extern RwImage     *RwImageWrite(RwImage * image,
                                 const RwChar * imageName);

    /* Setting and getting the default path for images */
extern RwChar      *RwImageGetPath(void);
extern const RwChar *RwImageSetPath(const RwChar * path);
    /* Fast image path change */
extern void        _rwImageSwapPath(RwChar **path, RwInt32 *size);

    /* Setting */
#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwImage     *RwImageSetStride(RwImage * image, RwInt32 stride);
extern RwImage     *RwImageSetPixels(RwImage * image, RwUInt8 * pixels);
extern RwImage     *RwImageSetPalette(RwImage * image, RwRGBA * palette);

    /* Getting */
extern RwInt32      RwImageGetWidth(const RwImage * image);
extern RwInt32      RwImageGetHeight(const RwImage * image);
extern RwInt32      RwImageGetDepth(const RwImage * image);
extern RwInt32      RwImageGetStride(const RwImage * image);
extern RwUInt8     *RwImageGetPixels(const RwImage * image);
extern RwRGBA      *RwImageGetPalette(const RwImage * image);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

    /* Get device dependent pixel value */
extern RwUInt32     RwRGBAToPixel(RwRGBA * rgbIn, RwInt32 rasterFormat);
extern RwRGBA      *RwRGBASetFromPixel(RwRGBA * rgbOut,
                                       RwUInt32 pixelValue,
                                       RwInt32 rasterFormat);

    /* Gamma correction */
extern RwBool       RwImageSetGamma(RwReal gammaValue);
extern RwReal       RwImageGetGamma(void);
extern RwImage     *RwImageGammaCorrect(RwImage * image);

    /* Adding and removing gamma correction */
extern RwRGBA      *RwRGBAGammaCorrect(RwRGBA * rgb);

    /* Attaching toolkits */
extern RwInt32      RwImageRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                          RwPluginObjectConstructor
                                          constructCB,
                                          RwPluginObjectDestructor
                                          destructCB,
                                          RwPluginObjectCopy copyCB);
extern RwInt32      RwImageGetPluginOffset(RwUInt32 pluginID);
extern RwBool       RwImageValidatePlugins(const RwImage * image);

extern RwBool       RwImageRegisterImageFormat(const RwChar * extension,
                                               RwImageCallBackRead
                                               imageRead,
                                               RwImageCallBackWrite
                                               imageWrite);

    /* Finding an extension for an image to load */
extern const RwChar *RwImageFindFileType(const RwChar * imageName);

    /* Reading and writing images to streams */
extern RwInt32      RwImageStreamGetSize(const RwImage * image);
extern RwImage     *RwImageStreamRead(RwStream * stream);
extern const RwImage *RwImageStreamWrite(const RwImage * image,
                                         RwStream * stream);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/src/batextur.h ---*/

/****************************************************************************
 Defines
 */

/* Type ID */
#define rwTEXDICTIONARY 6

/* Mipmap Name generation - maximum number of RwChar characters which can
 * be appended to the root name.
 */
#define rwTEXTUREMIPMAPNAMECHARS    16

/* We define texture names to be a maximum of 16 ISO chars */
#define rwTEXTUREBASENAMELENGTH     32

#define rwTEXTUREFILTERMODEMASK     0x000000FF
#define rwTEXTUREADDRESSINGUMASK    0x00000F00
#define rwTEXTUREADDRESSINGVMASK    0x0000F000
#define rwTEXTUREADDRESSINGMASK     (rwTEXTUREADDRESSINGUMASK |  \
                                     rwTEXTUREADDRESSINGVMASK)

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwtexdict
 * \struct RwTexDictionary 
 * is a texture dictionary containing textures. 
 * This should be considered an opaque type.
 * Use the RwTexDictionary API functions to access.
 */
typedef struct RwTexDictionary RwTexDictionary;

#if (!defined(DOXYGEN))
struct RwTexDictionary
{
    RwObject            object; /* Homogeneous type */
    RwLinkList          texturesInDict; /* List of textures in dictionary */
    RwLLLink            lInInstance; /* Link list of all dicts in system */
};
/* Information is entirely device dependent */
#endif /* (!defined(DOXYGEN)) */


/* Parent is the dictionary */

/**
 * \ingroup rwtexture
 * \struct  RwTexture 
 * is a texture object. 
 * This should be considered an opaque type.
 * Use the RwTexture API functions to access.
 */
typedef struct RwTexture RwTexture;

#if (!defined(DOXYGEN))
struct RwTexture
{
    RwRaster           *raster; /** pointer to RwRaster with data */
    RwTexDictionary    *dict;   /* Dictionary this texture is in */
    RwLLLink            lInDictionary; /* List of textures in this dictionary */

    RwChar              name[rwTEXTUREBASENAMELENGTH];  /* Name of the texture */
    RwChar              mask[rwTEXTUREBASENAMELENGTH];  /* Name of the textures mask */

    /* 31 [xxxxxxxx xxxxxxxx vvvvuuuu ffffffff] 0 */
    RwUInt32            filterAddressing; /* Filtering & addressing mode flags */

    RwInt32             refCount; /* Reference count, surprisingly enough */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackRead 
 * represents the function used by \ref RwTextureRead to read the specified
 * texture from a disk file. This function should return a pointer to the
 * texture to indicate success.
 * 
 * \param  name   Pointer to a string containing the name of
 * the texture to read.
 *
 * \param  maskName   Pointer to a string containing the name
 * of the mask to read and apply to the texture.
 *
 * \return Pointer to the texture
 *
 * \see RwTextureSetReadCallBack
 * \see RwTextureGetReadCallBack
 */
typedef RwTexture *(*RwTextureCallBackRead)(const RwChar *name,
                                            const RwChar *maskName);

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBack
 * represents the function called from \ref RwTexDictionaryForAllTextures
 * for all textures in a given texture dictionary. This function should
 * return the current texture to indicate success. The callback may return
 * NULL to terminate further callbacks on the texture dictionary.
 * 
 * \param  texture   Pointer to the current texture.
 *
 * \param  pData   User-defined data pointer.
 *
 * \return Pointer to the current texture
 *
 * \see RwTexDictionaryForAllTextures
 */
typedef RwTexture *(*RwTextureCallBack)(RwTexture *texture, void *pData);


/**
 * \ingroup rwtexdict
 * \ref RwTexDictionaryCallBack
 * represents the function called from \ref RwTexDictionaryForAllTexDictionaries
 * for all texture dictionaries that currently exist. This function should
 * return the current texture dictionary to indicate success. The callback may
 * return NULL to terminate further callbacks on the texture dictionary. It may
 * safely destroy the current texture dictionary without adversely affecting
 * the iteration process.
 * 
 * \param  dict   Pointer to the current texture dictionary.
 *
 * \param  pData   User-defined data pointer.
 *
 * \return Pointer to the current texture dictionary
 *
 * \see RwTexDictionaryForAllTexdictionaries
 */
typedef RwTexDictionary *(*RwTexDictionaryCallBack)(RwTexDictionary *dict, void *data);


/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackMipmapGeneration 
 * is the callback function supplied to \ref RwTextureSetMipmapGenerationCallBack 
 * and returned from \ref RwTextureGetMipmapGenerationCallBack.
 *
 * The supplied function will be passed a pointer to a raster and an image.
 * The raster is the target for the generated mipmap levels and the image 
 * provides the base for their generation.
 * 
 * \param  raster   Pointer to raster, the target for generated mipmap levels
 * \param  image    Pointer to image, used to generate mipmap levels.
 * 
 * \return
 * Returns a pointer to the raster if successful or NULL if an error occurred.
 * 
 * \see RwTextureSetMipmapGenerationCallBack
 * \see RwTextureGetMipmapGenerationCallBack
 * \see RwTextureSetAutoMipmapping
 * \see RwTextureGetAutoMipmapping
 */
typedef RwRaster *(*RwTextureCallBackMipmapGeneration)(RwRaster * raster,
                                                       RwImage * image);

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackMipmapName
 * is the callback function supplied to \ref RwTextureSetMipmapNameCallBack and
 * returned from \ref RwTextureGetMipmapNameCallBack.
 *
 * The supplied function will be passed a pointer to a root name, a maskName, a mipmap
 * level and a format. The function returns TRUE if successful and the root name will have been 
 * modified to equal the mipmap name.
 * 
 * \param  name       Pointer to a string containing the root name of the texture. The 
 * mipmap level name is put here.
 * \param  maskName   Pointer to a string containing the root mask name of the texture or
 * NULL if no mask name is required.
 * \param  mipLevel   A value equal to the mipmap level for which the name is required.
 * \param  format     A value describing the mipmapping mode. A combination of the bit
 * flags rwRASTERFORMATMIPMAP and rwRASTERFORMATAUTOMIPMAP.
 * 
 * \return
 * Returns TRUE if the name is generated successfully or FALSE if an error occurred.
 * 
 * \see RwTextureGenerateMipmapName
 * \see RwTextureSetMipmapNameCallBack
 * \see RwTextureGetMipmapNameCallBack
 * \see RwTextureSetAutoMipmapping
 * \see RwTextureGetAutoMipmapping
 */
typedef RwBool (*RwTextureCallBackMipmapName)(RwChar *name,
                                              RwChar *maskName,
                                              RwUInt8 mipLevel,
                                              RwInt32 format);

/****************************************************************************
 <macro/inline functionality
 */

#define RwTextureGetRasterMacro(_tex)                       \
    ((_tex)->raster)

#define RwTextureAddRefMacro(_tex)                          \
    (((_tex)->refCount++), (_tex))

#define RwTextureAddRefVoidMacro(_tex)                      \
MACRO_START                                                 \
{                                                           \
    (_tex)->refCount++;                                     \
}                                                           \
MACRO_STOP

#define RwTextureGetNameMacro(_tex)                         \
    ((_tex)->name)

#define RwTextureGetMaskNameMacro(_tex)                     \
    ((_tex)->mask)

#define RwTextureGetDictionaryMacro(_tex)                   \
    ((_tex)->dict)

#define RwTextureSetFilterModeMacro(_tex, _filtering)                       \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREFILTERMODEMASK) |               \
      (((RwUInt32)(_filtering)) &  rwTEXTUREFILTERMODEMASK)),               \
     (_tex))

#define RwTextureGetFilterModeMacro(_tex)                                   \
    ((RwTextureFilterMode)((_tex)->filterAddressing &                       \
                           rwTEXTUREFILTERMODEMASK))

#define RwTextureSetAddressingMacro(_tex, _addressing)                      \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGMASK) |               \
      (((((RwUInt32)(_addressing)) <<  8) & rwTEXTUREADDRESSINGUMASK) |     \
       ((((RwUInt32)(_addressing)) << 12) & rwTEXTUREADDRESSINGVMASK))),    \
     (_tex))

#define RwTextureSetAddressingUMacro(_tex, _addressing)                     \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGUMASK) |              \
      (((RwUInt32)(_addressing) << 8) & rwTEXTUREADDRESSINGUMASK)),         \
     (_tex))

#define RwTextureSetAddressingVMacro(_tex, _addressing)                     \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGVMASK) |              \
      (((RwUInt32)(_addressing) << 12) & rwTEXTUREADDRESSINGVMASK)),        \
     (_tex))

#define RwTextureGetAddressingMacro(_tex)                                   \
    (((((_tex)->filterAddressing & rwTEXTUREADDRESSINGUMASK) >>  8) ==      \
      (((_tex)->filterAddressing & rwTEXTUREADDRESSINGVMASK) >> 12)) ?      \
     ((RwTextureAddressMode)(((_tex)->filterAddressing &                    \
                              rwTEXTUREADDRESSINGVMASK) >> 12)) :           \
     rwTEXTUREADDRESSNATEXTUREADDRESS)

#define RwTextureGetAddressingUMacro(_tex)                                  \
    ((RwTextureAddressMode)(((_tex)->filterAddressing &                     \
                             rwTEXTUREADDRESSINGUMASK) >> 8))

#define RwTextureGetAddressingVMacro(_tex)                                  \
    ((RwTextureAddressMode)(((_tex)->filterAddressing &                     \
                             rwTEXTUREADDRESSINGVMASK) >> 12))


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwTextureGetRaster(_tex)                            \
    RwTextureGetRasterMacro(_tex)

#define RwTextureAddRef(_tex)                               \
    RwTextureAddRefMacro(_tex)

#define RwTextureGetName(_tex)                              \
    RwTextureGetNameMacro(_tex)

#define RwTextureGetMaskName(_tex)                          \
    RwTextureGetMaskNameMacro(_tex)

#define RwTextureGetDictionary(_tex)                        \
    RwTextureGetDictionaryMacro(_tex)

#define RwTextureSetFilterMode(_tex, _filtering)            \
    RwTextureSetFilterModeMacro(_tex, _filtering)

#define RwTextureGetFilterMode(_tex)                        \
    RwTextureGetFilterModeMacro(_tex)

#define RwTextureSetAddressing(_tex, _addressing)           \
    RwTextureSetAddressingMacro(_tex, _addressing)

#define RwTextureSetAddressingU(_tex, _addressing)          \
    RwTextureSetAddressingUMacro(_tex, _addressing)

#define RwTextureSetAddressingV(_tex, _addressing)          \
    RwTextureSetAddressingVMacro(_tex, _addressing)

#define RwTextureGetAddressing(_tex)                        \
    RwTextureGetAddressingMacro(_tex)

#define RwTextureGetAddressingU(_tex)                       \
    RwTextureGetAddressingUMacro(_tex)

#define RwTextureGetAddressingV(_tex)                       \
    RwTextureGetAddressingVMacro(_tex)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */



/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

    /* Reading mip maps */

    /* Setting mip mapping states */
extern RwBool       RwTextureSetMipmapping(RwBool enable);
extern RwBool       RwTextureGetMipmapping(void);
extern RwBool       RwTextureSetAutoMipmapping(RwBool enable);
extern RwBool       RwTextureGetAutoMipmapping(void);

    /* Setting and getting the mipmap generation function */
extern              RwBool
RwTextureSetMipmapGenerationCallBack(RwTextureCallBackMipmapGeneration
                                     callback);
extern              RwTextureCallBackMipmapGeneration
RwTextureGetMipmapGenerationCallBack(void);

    /* Setting and getting the mipmap file name generation function */
extern              RwBool
RwTextureSetMipmapNameCallBack(RwTextureCallBackMipmapName callback);
extern RwTextureCallBackMipmapName RwTextureGetMipmapNameCallBack(void);

    /* Generating mipmaps for a raster */
extern RwBool       RwTextureGenerateMipmapName(RwChar * name,
                                                RwChar * maskName,
                                                RwUInt8 mipLevel,
                                                RwInt32 format);
extern RwBool       RwTextureRasterGenerateMipmaps(RwRaster * raster,
                                                   RwImage * image);

    /* LEGACY-SUPPORT mip mapping */
extern RwBool       _rwTextureSetAutoMipMapState(RwBool enable);
extern RwBool       _rwTextureGetAutoMipMapState(void);

    /* Setting and getting the callback function */
extern RwTextureCallBackRead RwTextureGetReadCallBack(void);
extern RwBool       RwTextureSetReadCallBack(RwTextureCallBackRead
                                             fpCallBack);

    /* Texture and mask names */
extern RwTexture   *RwTextureSetName(RwTexture * texture,
                                     const RwChar * name);
extern RwTexture   *RwTextureSetMaskName(RwTexture * texture,
                                         const RwChar * maskName);

    /* Creating/destroying dictionaries */
extern void RwTexDictionarySetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwTexDictionary *RwTexDictionaryCreate(void);
extern RwBool       RwTexDictionaryDestroy(RwTexDictionary * dict);

    /* Textures */
void RwTextureSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwTexture   *RwTextureCreate(RwRaster * raster);
extern RwBool       RwTextureDestroy(RwTexture * texture);

    /* Setting and getting texture map rasters */
extern RwTexture   *RwTextureSetRaster(RwTexture * texture,
                                       RwRaster * raster);

    /* Dictionary access */
extern RwTexture   *RwTexDictionaryAddTexture(RwTexDictionary * dict,
                                              RwTexture * texture);
extern RwTexture   *RwTexDictionaryRemoveTexture(RwTexture * texture);
extern RwTexture   *RwTexDictionaryFindNamedTexture(RwTexDictionary *
                                                    dict,
                                                    const RwChar * name);

    /* Reading a texture */
extern RwTexture   *RwTextureRead(const RwChar * name,
                                  const RwChar * maskName);

    /* Setting the current dictionary */
extern RwTexDictionary *RwTexDictionaryGetCurrent(void);
extern RwTexDictionary *RwTexDictionarySetCurrent(RwTexDictionary * dict);

    /* Enumerating textures */
extern const RwTexDictionary *RwTexDictionaryForAllTextures(const
                                                            RwTexDictionary
                                                            * dict,
                                                            RwTextureCallBack
                                                            fpCallBack,
                                                            void *pData);

    /* Enumerating the texture dictionaries currently in the system */
extern RwBool RwTexDictionaryForAllTexDictionaries(
    RwTexDictionaryCallBack fpCallBack, void *pData);


    /* Attaching toolkits */
extern RwInt32      RwTextureRegisterPlugin(RwInt32 size,
                                            RwUInt32 pluginID,
                                            RwPluginObjectConstructor
                                            constructCB,
                                            RwPluginObjectDestructor
                                            destructCB,
                                            RwPluginObjectCopy copyCB);
extern RwInt32      RwTexDictionaryRegisterPlugin(RwInt32 size,
                                                  RwUInt32 pluginID,
                                                  RwPluginObjectConstructor
                                                  constructCB,
                                                  RwPluginObjectDestructor
                                                  destructCB,
                                                  RwPluginObjectCopy
                                                  copyCB);
extern RwInt32      RwTextureGetPluginOffset(RwUInt32 pluginID);
extern RwInt32      RwTexDictionaryGetPluginOffset(RwUInt32 pluginID);
extern RwBool       RwTextureValidatePlugins(const RwTexture * texture);
extern RwBool       RwTexDictionaryValidatePlugins(const RwTexDictionary *
                                                   dict);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
/* Textures */
extern RwRaster *RwTextureGetRaster(const RwTexture *texture);
extern RwTexture *RwTextureAddRef(RwTexture *texture);

/* Texture and mask names */
extern RwChar *RwTextureGetName(RwTexture *texture);
extern RwChar *RwTextureGetMaskName(RwTexture *texture);

/* Get owner dictionary */
extern RwTexDictionary *RwTextureGetDictionary(RwTexture *texture);

/* Filtering */
extern RwTexture *RwTextureSetFilterMode(RwTexture *texture,
                                         RwTextureFilterMode filtering);

extern RwTextureFilterMode RwTextureGetFilterMode(const RwTexture *texture);

/* Addressing */
extern RwTexture *RwTextureSetAddressing(RwTexture *texture,
                                         RwTextureAddressMode addressing);
extern RwTexture *RwTextureSetAddressingU(RwTexture *texture,
                                          RwTextureAddressMode addressing);
extern RwTexture *RwTextureSetAddressingV(RwTexture *texture,
                                          RwTextureAddressMode addressing);

extern RwTextureAddressMode RwTextureGetAddressing(const RwTexture *texture);
extern RwTextureAddressMode RwTextureGetAddressingU(const RwTexture *texture);
extern RwTextureAddressMode RwTextureGetAddressingV(const RwTexture *texture);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RwTextureSetAutoMipMapState(_enable) \
    _rwTextureSetAutoMipMapState(_enable)

#define RwTextureGetAutoMipMapState() \
    _rwTextureGetAutoMipMapState()


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/p2stdcls.h ---*/

/*
 * Current:
 *
 * wait on Simon for instructions to do cluster renaming thing,
 * or go thru and  change all cluster type names and cluster
 * names (add CSL?)
 *
 */

/* CamVerts.csl */

/* clip flags */

/**
 * \ingroup rwcoregeneric
 * \ref RwClipFlag
 * Flags specifying the clipping status of a vertex
 */
enum RwClipFlag
{
    rwXLOCLIP   = 0x01, /**<The vertex is outside the low X clip-plane */
    rwXHICLIP   = 0x02, /**<The vertex is outside the high X clip-plane */
    rwXCLIP     = 0x03, /**<The vertex is outside an X clip-plane */

    rwYLOCLIP   = 0x04, /**<The vertex is outside the low Y clip-plane */
    rwYHICLIP   = 0x08, /**<The vertex is outside the high Z clip-plane */
    rwYCLIP     = 0x0C, /**<The vertex is outside a Y clip-plane */

    rwZLOCLIP   = 0x10, /**<The vertex is outside the low Z clip-plane */
    rwZHICLIP   = 0x20, /**<The vertex is outside the high Z clip-plane */
    rwZCLIP     = 0x30, /**<The vertex is outside a Z clip-plane */

    rwCLIPMASK  = 0x3F, /**<Mask covering all used bits in the clip flags
                         * in case a plugin  wants free ones to use (e.g RpGloss) */

    rwCLIPFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
/*
 * Typedef for RwClipFlag enumeration specifying the clipping status of a vertex
 */
typedef enum RwClipFlag RwClipFlag;



typedef struct RxCamSpace3DVertex RxCamSpace3DVertex;

/**
 * \ingroup rwcoregeneric
 * \struct RxCamSpace3DVertex
 * Structure describing a camera-space 3D vertex.
 */
struct RxCamSpace3DVertex
{
    /* Position in sheared camera-space (pre-projection) */
    RwV3d           cameraVertex; /**< \ref RwV3d camera-space position of the vertex */
    /* Clip flags on this vertex */
    RwUInt8         clipFlags;    /**< Clip flags for the vertex generated during transformation into camera-space, see \ref RwClipFlag */
    RwUInt8         pad[3];       /**< Alignment padding */
    /* Lit color */
    RwRGBAReal      col;          /**< Accumulated \ref RwReal light values (initialized to zero or prelight colors) */
    /* Only used by the clipper */
    RwReal          u;            /**< Texture U coordinate */
    RwReal          v;            /**< Texture V coordinate */
};

/* Supports pipeline1 apps: */
/**
 * \ingroup rwcoregeneric
 * \ref RwCameraVertex
 * typedef for a structure describing a camera-space 3D vertex.
 */
typedef RxCamSpace3DVertex RwCameraVertex;

/* (used during lighting) Doesn't use alpha yet, but it will */
#define RxCamSpace3DVertexSetRGBA(camvert, r, g, b, a)  \
MACRO_START                                             \
{                                                       \
    ((camvert)->col.red = (r));                         \
    ((camvert)->col.green = (g));                       \
    ((camvert)->col.blue = (b));                        \
    ((camvert)->col.alpha = (a));                       \
}                                                       \
MACRO_STOP

#define RxCamSpace3DVertexAddRGBA(camvert, r, g, b, a)  \
MACRO_START                                             \
{                                                       \
    ((camvert)->col.red += (r));                        \
    ((camvert)->col.green += (g));                      \
    ((camvert)->col.blue += (b));                       \
    ((camvert)->col.alpha += (a));                      \
}                                                       \
MACRO_STOP

/* LEGACY-SUPPORT macros */
#define RXCAMSPACE3DVERTEXSetRGBA(camvert, r, g, b, a)  \
    RxCamSpace3DVertexSetRGBA(camvert, r, g, b, a)
#define RXCAMSPACE3DVERTEXAddRGBA(camvert, r, g, b, a)  \
    RxCamSpace3DVertexAddRGBA(camvert, r, g, b, a)

/* MeshState.csl */


/**
 * \ingroup rwcoregeneric
 * \ref RxGeometryFlag
 * Flags describing geometry properties
 */
enum RxGeometryFlag
{
    rxGEOMETRY_TRISTRIP      = 0x01,  /**<This geometry's meshes can be rendered as tri-strips */
    rxGEOMETRY_POSITIONS     = 0x02,  /**<This geometry has positions */
    rxGEOMETRY_TEXTURED      = 0x04,  /**<This geometry has textures applied */
    rxGEOMETRY_PRELIT        = 0x08,  /**<This geometry has luminance values */
    rxGEOMETRY_NORMALS       = 0x10,  /**<This geometry has normals */
    rxGEOMETRY_LIGHT         = 0x20,  /**<This geometry will be lit */
    rxGEOMETRY_MODULATE      = 0x40,  /**<This geometry will modulate the material color with the vertex colors (prelit + lit) */
    rxGEOMETRY_TEXTURED2     = 0x80,  /**<This geometry has 2 set of texture coordinates */

    rxGEOMETRY_COLORED       = 0x100, /**<This mesh specifies per-vertex colors. NB: ONLY USED IN IM3D */

    rxGEOMETRYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
/*
 * Typedef for RxGeometryFlag enumeration describing geometry properties
 */
typedef enum RxGeometryFlag RxGeometryFlag;

typedef struct RxMeshStateVector RxMeshStateVector;

/**
 * \ingroup rwcoregeneric
 * \struct RxMeshStateVector
 * Structure describing a mesh-state vector,
 * used by the RxClMeshState cluster
 */
struct RxMeshStateVector
{
    RwInt32             Flags;              /**< \ref RxGeometryFlag Flags from the source geometry */
    void               *SourceObject;       /**< A void pointer. In immediate mode it points to an
                                             * internal structure and in atomic/world-sector object
                                             * or material pipelines it points to an \ref RpMaterial. */
    RwMatrix            Obj2World;          /**< \ref RwMatrix to transform from object-space to world-space */
    RwMatrix            Obj2Cam;            /**< \ref RwMatrix to transform from object-space to camera-space */
    RwSurfaceProperties SurfaceProperties;  /**< \ref RwSurfaceProperties */
    /* We can't necessarily reference an RpMaterial in here (i.e with Im3D),
     * because RpMaterials are defined in RpWorld not RwCore */
    RwTexture          *Texture;            /**< A pointer to a \ref RwTexture */
    RwRGBA              MatCol;             /**< \ref RwRGBA material color */
    RxPipeline         *Pipeline;           /**< A pointer to the material pipeline where appropriate */
    /* rwPRIMTYPETRILIST/TRIFAN/TRISTRIP/LINELIST/POLYLINE */
    RwPrimitiveType     PrimType;           /**< \ref RwPrimitiveType primitive type */
    /* Interpretation based on PrimType */
    RwUInt32            NumElements;        /**< \ref RwUInt32 number of elements (triangles, lines...) */
    RwUInt32            NumVertices;        /**< \ref RwUInt32 number of vertices */
    RwInt32             ClipFlagsOr;        /**< Boolean OR of the \ref RwClipFlag clip flags of all vertices in the mesh */
    RwInt32             ClipFlagsAnd;       /**< Boolean AND of the \ref RwClipFlag clip flags of all vertices in the mesh */
    void               *SourceMesh;         /**< A void pointer to the source \ref RpMesh */
    void               *DataObject;         /**< Mirrors the void data pointer of \ref RxPipelineExecute */
};

/* RxScatter.csl */
typedef struct RxScatter RxScatter;
/**
 * \ingroup rwcoregeneric
 * \struct RxScatter
 * Structure used by the RxClScatter cluster
 */
struct RxScatter
{
    RxPipeline    *pipeline; /**< \ref RxPipeline pointer, causes Scatter.csl
                              * to spit the packet out to the specified pipeline */
    RxPipelineNode *node;    /**< \ref RxPipelineNode pointer, causes Scatter.csl
                              * to send the packet to the specified PipelineNode
                              * (as long as it is actually one of its outputs!) */
};

/* RxInterpolants.csl */
typedef struct RxInterp RxInterp;
/**
 * \ingroup rwcoregeneric
 * \struct RxInterp
 * Structure used by the RxClInterp cluster
 */
struct RxInterp
{
    RxVertexIndex originalVert; /**< \ref RxVertexIndex index to the new vertex generated on the clipped edge */
    RxVertexIndex parentVert1;  /**< \ref RxVertexIndex index to the first vertex of the clipped edge */
    RxVertexIndex parentVert2;  /**< \ref RxVertexIndex index to the second vertex of the clipped edge */
    RwReal        interp;       /**< \ref RwReal interpolant along the clipped edge */
};

/* RxUVs.csl */
typedef struct RxUV RxUV;
/**
 * \ingroup rwcoregeneric
 * \struct RxUV
 * Structure used by the RxClUV cluster
 */
struct RxUV
{
    RwReal u; /**< \ref RwReal U texture coordinate */
    RwReal v; /**< \ref RwReal V texture coordinate */
};

/* RxTriPlanes.csl */
typedef struct RxTriPlane RxTriPlane;

/**
 * \ingroup rwcoregeneric
 * \struct RxTriPlane
 * for the packed plane structure used in RpWorlds and by the RxClTriPlane cluster
 * NOTE: this is currently not used in any nodes that ship with the SDK
 */
struct RxTriPlane
{
    /* Packed plane format used in RpWorlds */
    RwUInt32 N; /**< \ref RwUInt32 Packed normal */
    RwReal   w; /**< \ref RwReal distance from origin */
};

/* RxVSteps.csl */

#if (defined(_MSC_VER))
#  if (_MSC_VER>=1000)
#    pragma pack(push, 1)
#  endif /* (_MSC_VER>=1000) */
#endif /* (defined(_MSC_VER)) */

typedef struct RxVStep RxVStep;
/**
 * \ingroup rwcoregeneric
 * \struct RxVStep
 * Structure used by the RxClVStep cluster.
 * To use the step values in the RxClVStep cluster, start at the beginning
 * of the RxVStep and vertex arrays and proceed as follows: (a) Process one
 * vertex, (b) Skip 'step' vertices, (c) Increment the cursor of the RxClVStep
 * cluster. Repeat (a)-(c) until the entire vertex array has been processed.
 * If the RxVStep array contains valid data, you should not have to bounds-check
 * its cursor.
 */
struct RxVStep
{
    RwUInt8 step; /**< \ref RwUInt8 The number of vertices after the current one
                   * which can be skipped in lighting and other calculations because,
                   * for example, they belong only to back-facing triangles */
};

#if (defined(_MSC_VER))
#  if (_MSC_VER>=1000)
#    pragma pack(pop)
#  endif /* (_MSC_VER>=1000) */
#endif /* (defined(_MSC_VER)) */

/* CamNorms.csl */
/**
 * \ingroup rwcoregeneric
 * \ref RxCamNorm
 * typedef for \ref RwV3d used by the RxClVStep cluster */
typedef RwV3d RxCamNorm;


#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Uses the RxObjSpace3DVertex type (see pipmodel.h) */
extern RxClusterDefinition RxClObjSpace3DVertices;
/* Uses the RxCamSpace3DVertex type */
extern RxClusterDefinition RxClCamSpace3DVertices;
/* Uses the RxScrSpace2DVertex type (see pipmodel.h) */
extern RxClusterDefinition RxClScrSpace2DVertices;
/* Uses the RxInterp type */
extern RxClusterDefinition RxClInterpolants;
/* Uses the RxMeshStateVector type */
extern RxClusterDefinition RxClMeshState;
/* Uses the RxRenderStateVector type (p2renderstate.c/h) */
extern RxClusterDefinition RxClRenderState;
/* Uses the RxVertexIndex type */
extern RxClusterDefinition RxClIndices;
/* Uses the RxScatter type */
extern RxClusterDefinition RxClScatter;
/* Uses the RxUV type */
extern RxClusterDefinition RxClUVs;
/* Uses the RxVStep type */
extern RxClusterDefinition RxClVSteps;
/* Uses the RwRGBAReal type */
extern RxClusterDefinition RxClRGBAs;
/* Uses the RxCamNorm type */
extern RxClusterDefinition RxClCamNorms;

/* Uses the RxTriPlane type.
 * NOTE: this is currently not used in any nodes that ship with the SDK */
extern RxClusterDefinition RxClTriPlanes;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/baim3d.h ---*/

/**
 * \ingroup rwim3d
 * RwIm3DTransformFlags
 *  The bit-field type  RwIm3DTransformFlags
 * specifies options available for controlling execution of the 3D immediate
 * mode pipeline (see API function \ref RwIm3DTransform):*/
enum RwIm3DTransformFlags
{
    rwIM3D_VERTEXUV      = 1,   /**<Texture coordinates in source vertices should be used */
    rwIM3D_ALLOPAQUE     = 2,   /**<All source vertices are opaque (alpha is 255) */
    rwIM3D_NOCLIP        = 4,   /**<No clipping should be performed on the geometry (the
                                 * app may know it is all onscreen or within the guard band clipping
                                 * region for the current hardware, so clipping can be skipped) */
    rwIM3D_VERTEXXYZ     = 8,   /**<Vertex positions */
    rwIM3D_VERTEXRGBA    = 16,  /**<Vertex color */

    rwIM3DTRANSFORMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwIm3DTransformFlags RwIm3DTransformFlags;



typedef struct rwIm3DPool            rwIm3DPool;
typedef struct rwImmediGlobals       rwImmediGlobals;
typedef struct rwIm3DRenderPipelines rwIm3DRenderPipelines;
typedef struct _rwIm3DPoolStash       _rwIm3DPoolStash;

#if (0 && defined(SKY2))
typedef struct rwIm3DVertexCache     RwIm3DVertexCache;
#endif /* (0&& defined(SKY2)) */

/* complete information to reconstruct post-transform Im3D "mesh" packet */

#if (!defined(DOXYGEN))
struct _rwIm3DPoolStash
{
    RwUInt32                 flags;    /* rwIM3D_VERTEXUV, rwIM3D_ALLOPAQUE, rwIM3D_NOCLIP etc */
    RwMatrix                *ltm;      /* world-space frame of the vertices, if they have one */
    RwUInt32                 numVerts;
    RxObjSpace3DVertex      *objVerts;
    RxCamSpace3DVertex      *camVerts;
    RxScrSpace2DVertex      *devVerts;
    RxMeshStateVector       *meshState;
    RxRenderStateVector     *renderState;
    RxPipeline              *pipeline;
    RwPrimitiveType          primType;
    RxVertexIndex           *indices;
    RwUInt32                 numIndices;
};

/* Used as a cache of transformed vertices */
struct rwIm3DPool
{
    RwUInt16         numElements; /* could become RwUInt32 nowadays */
    RwUInt16         pad;         /* alignment padding */
    void            *elements;    /* the original array of verts (or whatever...) - referenced not copied */
    RwInt32          stride;      /* the stride of the element */
    _rwIm3DPoolStash  stash;
};

struct rwIm3DRenderPipelines
{
    /* One Im3D render pipeline pointer per rwPRIMTYPE
     * (several pointers may point to the same pipeline though) */
    RxPipeline *triList;
    RxPipeline *triFan;
    RxPipeline *triStrip;
    RxPipeline *lineList;
    RxPipeline *polyLine;
    RxPipeline *pointList;
};

struct rwImmediGlobals
{
    RxPipeline           *im3DTransformPipeline;
    rwIm3DRenderPipelines im3DRenderPipelines;

    /* Platforms that have their own non-generic pipelines
     * (OPENGL, D3D8, SKY2, KAMUI2, DOLPHIN) put them here: */
    RxPipeline           *platformIm3DTransformPipeline;
    rwIm3DRenderPipelines platformIm3DRenderPipelines;

#if (defined(SKY2_DRVMODEL_H))
    /* The triangle PS2All render pipe automatically
     * calls this PS2AllMat pipeline: */
    RxPipeline           *ps2AllMatIm3DTrianglePipeline;
    /* The line PS2All render pipe automatically
     * calls this PS2AllMat pipeline: */
    RxPipeline           *ps2AllMatIm3DLinePipeline;
#endif /* (defined(SKY2_DRVMODEL_H)) */

    rwIm3DPool   curPool;              /* The current cache of transformed vertices */
};
#endif /* (!defined(DOXYGEN)) */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern rwIm3DPool *_rwIm3DGetPool( void );

extern void  *RwIm3DTransform(RwIm3DVertex *pVerts, RwUInt32 numVerts,
                              RwMatrix *ltm, RwUInt32 flags);
extern RwBool RwIm3DEnd(void);

extern RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2);
extern RwBool RwIm3DRenderTriangle(RwInt32 vert1, RwInt32 vert2,
                                   RwInt32 vert3);
extern RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType,
                                           RwImVertexIndex *indices,
                                           RwInt32 numIndices);
extern RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType);

extern RxPipeline *RwIm3DGetTransformPipeline(void);
extern RxPipeline *RwIm3DGetRenderPipeline(   RwPrimitiveType  primType);
extern RxPipeline *RwIm3DSetTransformPipeline(RxPipeline *pipeline);
extern RxPipeline *RwIm3DSetRenderPipeline(   RxPipeline *pipeline,
                                              RwPrimitiveType primType);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/d3d8/im3dpipe.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/d3d8dxttex.h ---*/
#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwTexture *RwD3D8DDSTextureRead(const RwChar *name, const RwChar *maskname);

extern RwBool RwD3D8RasterIsCompressed(const RwRaster *raster);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/driver/d3d8/drvfns.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/****************************************************************************
 Function prototypes
 */

/*******/
/* API */
/*******/

/* Reports on whether D3D8 can render S3TC textures */
extern RwBool 
RwD3D8DeviceSupportsDXTTexture(void);

/* Get handle to D3D8 device - useful for setting D3D8 renderstate*/
extern void *
RwD3D8GetCurrentD3DDevice(void);

/* Get maximun number of multisampling levels */
extern RwUInt32
RwD3D8EngineGetMaxMultiSamplingLevels(void);

/* Set number of multisampling levels */
extern void
RwD3D8EngineSetMultiSamplingLevels(RwUInt32 numLevels);

/* Set maximun full screen refresh rate */
extern void
RwD3D8EngineSetRefreshRate(RwUInt32 refreshRate);

/* Get handle to D3D8 rendering surface - useful for advanced blit ops */
extern void *
RwD3D8GetCurrentD3DRenderTarget(void);

/* Atach a window to a camera */
extern RwBool
RwD3D8CameraAttachWindow(void *camera, void *hwnd);

/* Immediate mode rendering */
extern RwBool       RwD3D8SetVertexShader(RwUInt32 handle);
extern RwBool       RwD3D8SetPixelShader(RwUInt32 handle);
extern RwBool       RwD3D8SetStreamSource(RwUInt32 streamNumber, void *streamData, RwUInt32 stride);
extern RwBool       RwD3D8SetIndices(void *indexData, RwUInt32 baseVertexIndex);

extern RwBool       RwD3D8DrawIndexedPrimitiveUP(RwUInt32 primitiveType,
                                                  RwUInt32 minIndex,
                                                  RwUInt32 numVertices,
                                                  RwUInt32 numIndices,
                                                  const void* indexData,
                                                  const void* vertexStreamZeroData,
                                                  RwUInt32 VertexStreamZeroStride);

extern RwBool       RwD3D8DrawPrimitiveUP(RwUInt32 primitiveType,
                                                  RwUInt32 numVertices,
                                                  const void* vertexStreamZeroData,
                                                  RwUInt32 VertexStreamZeroStride);

extern RwBool       RwD3D8DrawIndexedPrimitive(RwUInt32 primitiveType,
                                                  RwUInt32 minIndex,
                                                  RwUInt32 numVertices,
                                                  RwUInt32 startIndex,
                                                  RwUInt32 numIndices);

extern RwBool       RwD3D8DrawPrimitive(RwUInt32 primitiveType,
                                                  RwUInt32 startVertex,
                                                  RwUInt32 numVertices);

extern RwBool       RwD3D8SetTexture(RwTexture *texture, RwUInt32 stage);

extern RwBool       RwD3D8SetRenderState(RwUInt32 state, RwUInt32 value);
extern RwBool       RwD3D8SetTextureStageState(RwUInt32 stage, RwUInt32 type, RwUInt32 value);
extern RwBool       RwD3D8SetTransform(RwUInt32 state, const void *matrix);
extern RwBool       RwD3D8SetMaterial(const void *material);
extern void         RwD3D8SetStencilClear(RwUInt32 stencilClear);


extern void         RwD3D8GetRenderState(RwUInt32 state, void *value);
extern void         RwD3D8GetTextureStageState(RwUInt32 stage, RwUInt32 type, void *value);
extern void         RwD3D8GetTransform(RwUInt32 state, void *matrix);
extern RwUInt32     RwD3D8GetStencilClear(void);

/*
 * To convert between RwMatrix to D3DMATRIX when setting the
 * world matrix
 */
extern RwBool       RwD3D8SetTransformWorld(const RwMatrix *matrix);

/*
 * To convert between RpMaterial to D3DMATERIAL8
 */
extern RwBool       RwD3D8SetSurfaceProperties(const RwRGBA *color,
                                                const RwSurfaceProperties *surfaceProps,
                                                RwBool modulate);

/*
 * To set on that index the light from the descriptor
 */
extern RwBool       RwD3D8SetLight(RwInt32 index, const void *light);
extern void         RwD3D8GetLight(RwInt32 index, void *light);

extern RwBool       RwD3D8EnableLight(RwInt32 index, RwBool enable);

/*
 * To get a pointer to a Dynamic vertex buffer
 * Use both functions, Create and Destroy, not only Create
 */
extern RwBool RwD3D8DynamicVertexBufferCreate(RwUInt32 fvf, RwUInt32 size,
                                               void **vertexBuffer);

extern void RwD3D8DynamicVertexBufferDestroy(void *vertexBuffer);

/*
 * To get a temporary pointer to a Dynamic vertex buffer memory
 * Don't use with the previous functions because
 * it mantains an internal list of dinamic vertex buffers
 */
extern RwBool RwD3D8DynamicVertexBufferLock(RwUInt32 vertexSize,
                                            RwUInt32 numVertex,
                                            void **vertexBufferOut,
                                            void **vertexDataOut,
                                            RwUInt32 *baseIndexOut);

extern RwBool RwD3D8DynamicVertexBufferUnlock(void *vertexBuffer);

/*
 * To get a pointer to an Index vertex buffer
 * It's created as WRITEONLY, MANAGED and D3DFMT_INDEX16
 */
extern RwBool RwD3D8IndexBufferCreate(RwUInt32 numIndices,
                                       void **indexBuffer);

/*
 * To create a vertex shader from the declaration, also the function
 * for deleting it.
 */
extern RwBool RwD3D8CreateVertexShader(const RwUInt32 *declaration,
                                      const RwUInt32 *function,
                                      RwUInt32 *handle,
                                      RwUInt32 usage);

extern void RwD3D8DeleteVertexShader(RwUInt32 handle);

extern RwBool RwD3D8SetVertexShaderConstant(RwUInt32 registerAddress,
                                          const void *constantData,
                                          RwUInt32  constantCount);

/*
 * To create a pixel shader from the function, also the function
 * for deleting it.
 */
extern RwBool RwD3D8CreatePixelShader(const RwUInt32 *function, RwUInt32 *handle);

extern void RwD3D8DeletePixelShader(RwUInt32 handle);

extern RwBool RwD3D8SetPixelShaderConstant(RwUInt32 registerAddress,
                                          const void *constantData,
                                          RwUInt32  constantCount);

/*
 * Get a const pointer to the D3DCAPS8 struct, (you need to do the cast)
 */
extern const void *RwD3D8GetCaps(void);

/*
 * Check if the sphere is fully inside of the frustum
 */
extern RwBool RwD3D8CameraIsSphereFullyInsideFrustum(const void *camera, const void *sphere);

/*
 * Check if the Bounding Box is fully inside of the frustum
 */
extern RwBool RwD3D8CameraIsBBoxFullyInsideFrustum(const void *camera, const void *boundingBox);

/*
 * Cheking the CPU capabilities
 */

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwBool _rwIntelMMXsupported(void);
extern RwBool _rwIntelSSEsupported(void);
extern RwBool _rwIntelSSE2supported(void);
extern RwBool _rwAMD3DNowSupported(void);

#else
extern RwBool _rwD3D8CPUSupportsMMX;
extern RwBool _rwD3D8CPUSupportsSSE;
extern RwBool _rwD3D8CPUSupportsSSE2;
extern RwBool _rwD3D8CPUSupports3DNow;

#define _rwIntelMMXsupported() _rwD3D8CPUSupportsMMX
#define _rwIntelSSEsupported() _rwD3D8CPUSupportsSSE
#define _rwIntelSSE2supported() _rwD3D8CPUSupportsSSE2
#define _rwAMD3DNowSupported() _rwD3D8CPUSupports3DNow
#endif

/*
 * Enabling texture format conversions when loading textures from a texture
 * dictionary. FALSE by default.
 */
extern void
_rwD3D8TexDictionaryEnableRasterFormatConversion(RwBool enable);

/* Called from RwEngineInit to give the driver a chance to register plugins */
extern RwBool _rwDeviceRegisterPlugin(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/* LEGACY-MACRO */
/**
 * \ingroup rwcoredriverd3d8
 * \ref RwD3DLoadNativeTexture is a legacy macro for compatibility with
 * RWD3D7 applications that can be used to read a compressed texture from
 * the specified DDS file on disk.
 *
 * It is recommended that applications for RWD3D8 should use the RWD3D8
 * function \ref RwD3D8DDSTextureRead instead.
 *
 * \param name Pointer to a string containing the name of the texture to be read.
 * \param maskname  Pointer to a string containing the name of the mask or
 * NULL if not required.
 *
 * \return Returns pointer to the new texture if successful or NULL if there
 * is an error.
 *
 * \see RwD3D8DDSTextureRead
 * \see RwD3D8DeviceSupportsDXTTexture
 * \see RwImageSetPath
 * \see RwTextureSetReadCallBack
 * \see RwTextureSetMipmapping
 * \see RwTextureSetAutoMipmapping
 * \see RwTextureDestroy
 *
 */
#define RwD3DLoadNativeTexture RwD3D8DDSTextureRead


/*--- Automatically derived from: C:/daily/rwsdk/src/baresamp.h ---*/

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwImage *RwImageResample(RwImage *dstImage, const RwImage *srcImage);
extern RwImage *RwImageCreateResample(const RwImage *srcImage, RwInt32 width,
                                                               RwInt32 height);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/baimras.h ---*/
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Images from rasters */
extern RwImage *RwImageSetFromRaster(RwImage *image, RwRaster *raster);

/* Rasters from images */
extern RwRaster *RwRasterSetFromImage(RwRaster *raster, RwImage *image);

/* Finding raster formats */
extern RwRGBA *RwRGBAGetRasterPixel(RwRGBA *rgbOut, RwRaster *raster,
                                   RwInt32 x, RwInt32 y);

/* Read a raster */
extern RwRaster *RwRasterRead(const RwChar *filename);
extern RwRaster *RwRasterReadMaskedRaster(const RwChar *filename, const RwChar *maskname);

/* Finding appropriate raster formats */
extern RwImage *RwImageFindRasterFormat(RwImage *ipImage,RwInt32 nRasterType,
                                        RwInt32 *npWidth,RwInt32 *npHeight,
                                        RwInt32 *npDepth,RwInt32 *npFormat);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/baframe.h ---*/

/****************************************************************************
 Defines
 */

#if (!defined(RWFRAMESTATICPLUGINSSIZE))
#define RWFRAMESTATICPLUGINSSIZE 0
#endif

#define RWFRAMEALIGNMENT(_frame) \
   (! (((rwFRAMEALIGNMENT)-1) & ((RwUInt32)(_frame))))

/* Type ID */
#define rwFRAME 0

/* dirty flag bits */
#define rwFRAMEPRIVATEHIERARCHYSYNCLTM  0x01
#define rwFRAMEPRIVATEHIERARCHYSYNCOBJ  0x02
#define rwFRAMEPRIVATESUBTREESYNCLTM    0x04
#define rwFRAMEPRIVATESUBTREESYNCOBJ    0x08
#define rwFRAMEPRIVATESTATIC            0x10

/****************************************************************************
 Global Types
 */

#if (!defined(DOXYGEN))
struct RwFrame
{
    RwObject            object;

    RwLLLink            inDirtyListLink;

    /* Put embedded matrices here to ensure they remain 16-byte aligned */
    RwMatrix            modelling;
    RwMatrix            ltm;

    RwLinkList          objectList; /* List of objects connected to a frame */

    struct RwFrame      *child;
    struct RwFrame      *next;
    struct RwFrame      *root;   /* Root of the tree */

#if (RWFRAMESTATICPLUGINSSIZE)
    RWALIGN(RwUInt8             pluginData[RWFRAMESTATICPLUGINSSIZE], rwFRAMEALIGNMENT);
#endif /* defined(RWFRAMESTATICPLUGINSIZE)) */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwframe
 * \struct RwFrame 
 * Frame for defining object position and orientation. 
 * This should be considered an opaque type.
 * Use the RwFrame API functions to access.
 */
typedef struct RwFrame RWALIGN(RwFrame, rwFRAMEALIGNMENT);

/**
 * \ingroup rwframe
 * \ref RwFrameCallBack type represents the function 
 * called from \ref RwFrameForAllChildren for all child frames linked to a given frame.  
 * This function should return a pointer to the current frame to indicate success.  
 * The callback may return NULL to terminate further callbacks on the child frames.
 * 
 * \param  frame   Pointer to the current frame, supplied by
 * iterator.
 * \param  data  Pointer to developer-defined data structure.
 *
 * \return
 *
 * \see RwFrameForAllChildren
 *
 */
typedef RwFrame *(*RwFrameCallBack)(RwFrame *frame, void *data);


#define RwFrameGetParentMacro(_f)   ((RwFrame *)rwObjectGetParent(_f))
#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))
#define RwFrameGetParent(_f)    RwFrameGetParentMacro(_f)
#endif

#define RwFrameGetMatrixMacro(_f)   (&(_f)->modelling)
#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))
#define RwFrameGetMatrix(_f)    RwFrameGetMatrixMacro(_f)
#endif



/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern void RwFrameSetFreeListCreateParams(RwInt32 blockSize,
                                           RwInt32 numBlocksToPrealloc );

/* Finding what is attached to a frame */
extern RwFrame *
RwFrameForAllObjects(RwFrame * frame,
                     RwObjectCallBack callBack,
                     void *data);

/* Matrix operations */
extern RwFrame *
RwFrameTranslate(RwFrame * frame,
                 const RwV3d * v,
                 RwOpCombineType combine);

extern RwFrame *
RwFrameRotate(RwFrame * frame,
              const RwV3d * axis,
              RwReal angle,
              RwOpCombineType combine);

extern RwFrame *
RwFrameScale(RwFrame * frame,
             const RwV3d * v,
             RwOpCombineType combine);

extern RwFrame *
RwFrameTransform(RwFrame * frame,
                 const RwMatrix * m,
                 RwOpCombineType combine);

extern RwFrame *
RwFrameOrthoNormalize(RwFrame * frame);

extern RwFrame *
RwFrameSetIdentity(RwFrame * frame);

/* Cloning */
extern RwFrame *
RwFrameCloneHierarchy(RwFrame * root);

/* Destruction */
extern RwBool
RwFrameDestroyHierarchy(RwFrame * frame);

/* Building a frame */
extern RwFrame *
RwFrameForAllChildren(RwFrame * frame,
                      RwFrameCallBack callBack,
                      void *data);

extern RwFrame *
RwFrameRemoveChild(RwFrame * child);

extern RwFrame *
RwFrameAddChild(RwFrame * parent,
                RwFrame * child);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )
extern RwFrame *
RwFrameGetParent(const RwFrame * frame);
#endif

/* Getting the root */
extern RwFrame *
RwFrameGetRoot(const RwFrame * frame);

/* Getting Matrices */
extern RwMatrix *
RwFrameGetLTM(RwFrame * frame);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )
extern RwMatrix *
RwFrameGetMatrix(RwFrame * frame);
#endif

/* Elements */
extern RwFrame *
RwFrameUpdateObjects(RwFrame * frame);

/* Creating destroying frames */
extern void
RwFrameSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwFrame *
RwFrameCreate(void);

extern RwBool
RwFrameInit(RwFrame *frame);

extern RwBool
RwFrameDeInit(RwFrame *frame);

extern RwBool
RwFrameDestroy(RwFrame * frame);

/* internal function used by Create and Init */
extern void
_rwFrameInit(RwFrame *frame);

/* internal function used by Destroy and DeInit */
extern void
_rwFrameDeInit(RwFrame *frame);

/* Finding a frames state */
extern RwBool
RwFrameDirty(const RwFrame * frame);

/* Find the amount of frames in a hierarchy */
extern RwInt32
RwFrameCount(RwFrame * frame);

/* Plugins */
extern RwBool
RwFrameSetStaticPluginsSize(RwInt32 size);

extern RwInt32
RwFrameRegisterPlugin(RwInt32 size,
                      RwUInt32 pluginID,
                      RwPluginObjectConstructor constructCB,
                      RwPluginObjectDestructor destructCB,
                      RwPluginObjectCopy copyCB);

extern RwInt32
RwFrameGetPluginOffset(RwUInt32 pluginID);

extern RwBool
RwFrameValidatePlugins(const RwFrame * frame);

/* Cloning */
extern RwFrame *
_rwFrameCloneAndLinkClones(RwFrame * root);

extern
RwFrame *
_rwFramePurgeClone(RwFrame *root);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Compatibility macros */

#define rwFrameGetParent(frame) \
       _rwFrameGetParent(frame)

#define rwFrameInit(frame) \
       _rwFrameInit(frame)

#define rwFrameDeInit(frame) \
       _rwFrameDeInit(frame)

#define rwFrameCloneAndLinkClones(root) \
       _rwFrameCloneAndLinkClones(root)

#define rwFramePurgeClone(root) \
       _rwFramePurgeClone(root)

#define rwFrameClose(instance, offset, size) \
       _rwFrameClose(instance, offset, size)

#define rwFrameOpen(instance, offset, size) \
       _rwFrameOpen(instance, offset, size)


/*--- Automatically derived from: C:/daily/rwsdk/src/batypehf.h ---*/

typedef struct RwObjectHasFrame RwObjectHasFrame;
typedef RwObjectHasFrame * (*RwObjectHasFrameSyncFunction)(RwObjectHasFrame *object);

#if (!defined(DOXYGEN))
struct RwObjectHasFrame
{
    RwObject                     object;
    RwLLLink                     lFrame;
    RwObjectHasFrameSyncFunction sync;
};
#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Frames */
extern void _rwObjectHasFrameSetFrame(void *object, RwFrame *frame);
extern void _rwObjectHasFrameReleaseFrame(void *object);

/* ObjectHASFRAME METHODS */
#define rwObjectHasFrameInitialize(o, type, subtype, syncFunc)  \
MACRO_START                                                     \
{                                                               \
    rwObjectInitialize(o, type, subtype);                       \
    ((RwObjectHasFrame *)o)->sync = syncFunc;                   \
}                                                               \
MACRO_STOP

#define rwObjectHasFrameSync(o) \
    ((RwObjectHasFrame *)(o))->sync(o)

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Compatibility macros */

#define rwObjectHasFrameSetFrame(object, frame) \
        _rwObjectHasFrameSetFrame(object, frame)
#define rwObjectHasFrameReleaseFrame(object) \
        _rwObjectHasFrameReleaseFrame(object)



/*--- Automatically derived from: C:/daily/rwsdk/src/basync.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/babintex.h ---*/
/****************************************************************************
 Global types
 */
typedef struct rpTextureChunkInfo RwTextureChunkInfo;

#if (!defined(DOXYGEN))
struct rpTextureChunkInfo
{
    RwTextureFilterMode filtering;
    RwTextureAddressMode addressingU;
    RwTextureAddressMode addressingV;
};
#endif /* (!defined(DOXYGEN)) */

/* Bit flags defining properties of textures when stream */
enum RwTextureStreamFlags
{
    rwNATEXTURESTREAMFLAG = 0x00,
    rwTEXTURESTREAMFLAGSUSERMIPMAPS = 0x01,
    rwTEXTURESTREAMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureStreamFlags RwTextureStreamFlags;
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Texture binary format */
extern RwInt32
RwTextureRegisterPluginStream(RwUInt32 pluginID,
                              RwPluginDataChunkReadCallBack readCB,
                              RwPluginDataChunkWriteCallBack writeCB,
                              RwPluginDataChunkGetSizeCallBack getSizeCB);

extern RwInt32
RwTextureSetStreamAlwaysCallBack(RwUInt32 pluginID,
                                 RwPluginDataChunkAlwaysCallBack alwaysCB);

extern RwUInt32
RwTextureStreamGetSize(const RwTexture *texture);

extern RwTexture *
RwTextureStreamRead(RwStream *stream);

extern const RwTexture *
RwTextureStreamWrite(const RwTexture *texture,
                     RwStream *stream);

/* Texture dictionary binary format */
extern RwInt32
RwTexDictionaryRegisterPluginStream(RwUInt32 pluginID,
                                    RwPluginDataChunkReadCallBack readCB,
                                    RwPluginDataChunkWriteCallBack writeCB,
                                    RwPluginDataChunkGetSizeCallBack getSizeCB);

extern RwInt32
RwTexDictionarySetStreamAlwaysCallBack(RwUInt32 pluginID,
                                       RwPluginDataChunkAlwaysCallBack alwaysCB);

extern RwUInt32
RwTexDictionaryStreamGetSize(const RwTexDictionary *texDict);

extern RwTexDictionary
*RwTexDictionaryStreamRead(RwStream *stream);

extern const RwTexDictionary *
RwTexDictionaryStreamWrite(const RwTexDictionary *texDict,
                           RwStream *stream);

extern RwTextureChunkInfo *
_rwTextureChunkInfoRead(RwStream *stream,
                        RwTextureChunkInfo *textureChunkInfo,
                        RwInt32 *bytesRead);

/* Compatibility macro */

#define  RwTextureChunkInfoRead(_stream, _textureChunkInfo, _bytesRead) \
        _rwTextureChunkInfoRead(_stream, _textureChunkInfo, _bytesRead) 

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/babinfrm.h ---*/
/****************************************************************************
 Global types
 */

typedef struct rwFrameList rwFrameList;

#if (!defined(DOXYGEN))
struct rwFrameList
{
    RwFrame **frames;
    RwInt32 numFrames;
};
#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Global Variables 
 */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Frame binary format */

extern RwInt32 
RwFrameRegisterPluginStream(RwUInt32 pluginID,
                            RwPluginDataChunkReadCallBack readCB,
                            RwPluginDataChunkWriteCallBack writeCB,
                            RwPluginDataChunkGetSizeCallBack getSizeCB);

extern RwInt32 
RwFrameSetStreamAlwaysCallBack(RwUInt32 pluginID,
                               RwPluginDataChunkAlwaysCallBack alwaysCB);


extern rwFrameList *
_rwFrameListInitialize(rwFrameList *frameList,
                      RwFrame *frame);

extern RwBool 
_rwFrameListFindFrame(const rwFrameList *frameList,
                     const RwFrame *frame,
                     RwInt32 *npIndex);

extern rwFrameList *
_rwFrameListDeinitialize(rwFrameList *frameList);

extern RwUInt32 
_rwFrameListStreamGetSize(const rwFrameList *frameList);

extern rwFrameList *
_rwFrameListStreamRead(RwStream *stream,
                      rwFrameList *fl);

extern const rwFrameList *
_rwFrameListStreamWrite(const rwFrameList *frameList,
                       RwStream *stream);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Comparibility macros */

#define rwFrameListInitialize(frameList,frame) \
       _rwFrameListInitialize(frameList,frame)

#define rwFrameListFindFrame(frameList, frame, index) \
       _rwFrameListFindFrame(frameList, frame, index)

#define rwFrameListDeinitialize(frameList) \
       _rwFrameListDeinitialize(frameList)

#define rwFrameListStreamGetSize(frameList) \
       _rwFrameListStreamGetSize(frameList)

#define rwFrameListStreamRead(stream, fl) \
       _rwFrameListStreamRead(stream, fl)

#define rwFrameListStreamWrite(frameList, stream) \
       _rwFrameListStreamWrite(frameList, stream)


/*--- Automatically derived from: C:/daily/rwsdk/src/babbox.h ---*/
/****************************************************************************
 Global types
 */

typedef struct RwBBox RwBBox;
/**
 * \ingroup rwbbox
 * \struct RwBBox
 * This type represents a 3D axis-aligned bounding-box
 * specified by the positions of two corners which lie on a diagonal.
 * Typically used to specify a world bounding-box when the world is created
 * 
 * \param sup Supremum vertex (contains largest values)
 * \param inf Infimum vertex (contains smallest values)
 * 
 * \see RpWorldCreate
 */
struct RwBBox
{
    /* Must be in this order */
    RwV3d sup;   /**< Supremum vertex. */
    RwV3d inf;   /**< Infimum vertex. */
};

#if (!defined(RwBBoxAssign))
#define RwBBoxAssign(_target, _source)            \
    ( *(_target) = *(_source) )
#endif /* (!defined(RwBBoxAssign)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */


extern RwBBox *RwBBoxCalculate(RwBBox *boundBox,
                               const RwV3d *verts,
                               RwInt32 numVerts);
extern RwBBox *RwBBoxInitialize(RwBBox *boundBox,
                                const RwV3d *vertex);
extern RwBBox *RwBBoxAddPoint(RwBBox *boundBox,
                              const RwV3d *vertex);
extern RwBool RwBBoxContainsPoint(const RwBBox *boundBox,
                                  const RwV3d *vertex);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/src/bacamera.h ---*/

/****************************************************************************
 Defines
 */

/* Type ID */
#define rwCAMERA 4



/****************************************************************************
 <macro/inline functionality
 */

#define RwCameraGetViewOffsetMacro(_camera)                     \
    (&((_camera)->viewOffset))

#define RwCameraSetRasterMacro(_camera, _raster)                \
    (((_camera)->frameBuffer = (_raster)), (_camera))

#define RwCameraSetRasterVoidMacro(_camera, _raster)            \
MACRO_START                                                     \
{                                                               \
    (_camera)->frameBuffer = (_raster);                         \
}                                                               \
MACRO_STOP

#define RwCameraGetRasterMacro(_camera)                         \
    ((_camera)->frameBuffer)

#define RwCameraSetZRasterMacro(_camera, _raster)               \
    (((_camera)->zBuffer = (_raster)), (_camera))

#define RwCameraSetZRasterVoidMacro(_camera, _raster)           \
MACRO_START                                                     \
{                                                               \
    (_camera)->zBuffer = (_raster);                             \
}                                                               \
MACRO_STOP

#define RwCameraGetZRasterMacro(_camera)                        \
    ((_camera)->zBuffer)

#define RwCameraGetNearClipPlaneMacro(_camera)                  \
    ((_camera)->nearPlane)

#define RwCameraGetFarClipPlaneMacro(_camera)                   \
    ((_camera)->farPlane)

#define RwCameraSetFogDistanceMacro(_camera, _distance)         \
    (((_camera)->fogPlane = (_distance)), (_camera))

#define RwCameraGetFogDistanceMacro(_camera)                    \
    ((_camera)->fogPlane)

#define RwCameraGetCurrentCameraMacro()                         \
    ((RwCamera *)RWSRCGLOBAL(curCamera))

#define RwCameraGetProjectionMacro(_camera)                     \
    ((_camera)->projectionType)

#define RwCameraGetViewWindowMacro(_camera)                     \
    (&((_camera)->viewWindow))

#define RwCameraGetViewMatrixMacro(_camera)                     \
    (&((_camera)->viewMatrix))

#define RwCameraSetFrameMacro(_camera, _frame)                  \
    (_rwObjectHasFrameSetFrame((_camera), (_frame)), (_camera))

#define RwCameraSetFrameVoidMacro(_camera, _frame)      \
MACRO_START                                             \
{                                                       \
    _rwObjectHasFrameSetFrame((_camera), (_frame));     \
}                                                       \
MACRO_STOP


#define RwCameraGetFrameMacro(_camera)                          \
    ((RwFrame *)rwObjectGetParent((_camera)))

#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwCameraGetViewOffset(_camera)                          \
    RwCameraGetViewOffsetMacro(_camera)

#define RwCameraSetRaster(_camera, _raster)                     \
    RwCameraSetRasterMacro(_camera, _raster)

#define RwCameraGetRaster(_camera)                              \
    RwCameraGetRasterMacro(_camera)

#define RwCameraSetZRaster(_camera, _raster)                    \
    RwCameraSetZRasterMacro(_camera, _raster)

#define RwCameraGetZRaster(_camera)                             \
    RwCameraGetZRasterMacro(_camera)

#define RwCameraGetNearClipPlane(_camera)                       \
    RwCameraGetNearClipPlaneMacro(_camera)

#define RwCameraGetFarClipPlane(_camera)                        \
    RwCameraGetFarClipPlaneMacro(_camera)

#define RwCameraSetFogDistance(_camera, _distance)              \
    RwCameraSetFogDistanceMacro(_camera, _distance)

#define RwCameraGetFogDistance(_camera)                         \
    RwCameraGetFogDistanceMacro(_camera)

#define RwCameraGetCurrentCamera()                              \
    RwCameraGetCurrentCameraMacro()

#define RwCameraGetProjection(_camera)                          \
    RwCameraGetProjectionMacro(_camera)

#define RwCameraGetViewWindow(_camera)                          \
    RwCameraGetViewWindowMacro(_camera)

#define RwCameraGetViewMatrix(_camera)                          \
    RwCameraGetViewMatrixMacro(_camera)

#define RwCameraSetFrame(_camera, _frame)                       \
    RwCameraSetFrameMacro(_camera, _frame)

#define RwCameraGetFrame(_camera)                               \
    RwCameraGetFrameMacro(_camera)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwcamera
 * RwCameraClearMode 
 * Camera clear flags */
enum RwCameraClearMode
{
    rwCAMERACLEARIMAGE = 0x1,   /**<Clear the frame buffer */
    rwCAMERACLEARZ = 0x2,       /**<Clear the Z buffer */
    rwCAMERACLEARSTENCIL = 0x4, /**<\if xbox   Clear the stencil buffer \endif
                                  * \if d3d8   Clear the stencil buffer \endif
                                  * \if opengl Clear the stencil buffer \endif
                                  */
    rwCAMERACLEARMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraClearMode RwCameraClearMode;

/**
 * \ingroup rwcamera
 * RwCameraProjection 
 * This type represents the options available for 
 * setting the camera projection model, either perspective projection or 
* parallel projection (see API function \ref RwCameraSetProjection)*/
enum RwCameraProjection
{
    rwNACAMERAPROJECTION = 0,   /**<Invalid projection */
    rwPERSPECTIVE = 1,          /**<Perspective projection */
    rwPARALLEL = 2,             /**<Parallel projection */
    rwCAMERAPROJECTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraProjection RwCameraProjection;

/**
 * \ingroup rwcamera
 * RwFrustumTestResult 
 * This type represents the results from a 
 * camera frustum test on a given sphere (see API function 
 * \ref RwCameraFrustumTestSphere)*/
enum RwFrustumTestResult
{
    rwSPHEREOUTSIDE = 0,    /**<Outside the frustum */
    rwSPHEREBOUNDARY = 1,   /**<On the boundary of the frustum */
    rwSPHEREINSIDE = 2,     /**<Inside the frustum */
    rwFRUSTUMTESTRESULTFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwFrustumTestResult RwFrustumTestResult;


/**
 * \ingroup rwcamera
 * \struct RwCamera
 * Camera object for rendering a view. 
 * This should be considered an opaque type.
 * Use the RwCamera API functions to access.
 */
typedef struct RwCamera RWALIGN(RwCamera, rwMATRIXALIGNMENT);

/* This allows a world to overload functionality */
typedef RwCamera   *(*RwCameraBeginUpdateFunc) (RwCamera * camera);
typedef RwCamera   *(*RwCameraEndUpdateFunc) (RwCamera * camera);

typedef struct RwFrustumPlane RwFrustumPlane;

#if (!defined(DOXYGEN))
/*
 * Structure describing a frustrum plane.
 */
struct RwFrustumPlane
{
        RwPlane             plane;
        RwUInt8             closestX;
        RwUInt8             closestY;
        RwUInt8             closestZ;
        RwUInt8             pad;
};


struct RwCamera
{
        RwObjectHasFrame    object;

        /* Parallel or perspective projection */
        RwCameraProjection  projectionType;

        /* Start/end update functions */
        RwCameraBeginUpdateFunc beginUpdate;
        RwCameraEndUpdateFunc endUpdate;

        /* The view matrix */
        RwMatrix            viewMatrix;

        /* The cameras image buffer */
        RwRaster           *frameBuffer;

        /* The Z buffer */
        RwRaster           *zBuffer;

        /* Cameras mathmatical characteristics */
        RwV2d               viewWindow;
        RwV2d               recipViewWindow;
        RwV2d               viewOffset;
        RwReal              nearPlane;
        RwReal              farPlane;
        RwReal              fogPlane;

        /* Transformation to turn camera z or 1/z into a Z buffer z */
        RwReal              zScale, zShift;

        /* Render frame counter -> used for the frustum callback stuff */
        RwUInt16            renderFrame;
        RwUInt16            pad;

        /* The clip-planes making up the viewing frustum */
        RwFrustumPlane      frustumPlanes[6];
        RwBBox              frustumBoundBox;

        /* Points on the tips of the view frustum */
        RwV3d               frustumCorners[8];
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwcamera
 * \ref RwCameraCallBack type represents a function called from any camera
 * iterator that may be implemented in plugins. This function should return a
 * pointer to the current camera to indicate success. The callback may return
 * NULL to terminate further callbacks on other cameras.
 * 
 * \param  camera   Pointer to the current camera, supplied by iterator.
 * \param  data  Pointer to developer-defined data structure.
 *
 * \return 
 */
typedef RwCamera *(*RwCameraCallBack)(RwCamera *camera, void *data);


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

    /* Rendering */
extern RwCamera    *RwCameraBeginUpdate(RwCamera * camera);
extern RwCamera    *RwCameraEndUpdate(RwCamera * camera);

extern RwCamera    *RwCameraClear(RwCamera * camera, RwRGBA * colour,
                                  RwInt32 clearMode);

/* Displaying results */
extern RwCamera    *RwCameraShowRaster(RwCamera * camera, void *pDev,
                                       RwUInt32 flags);

/* Creation and destruction */
extern void RwCameraSetFreeListCreateParams( RwInt32 blockSize,
                                            RwInt32 numBlocksToPrealloc );
extern RwBool       RwCameraDestroy(RwCamera * camera);
extern RwCamera    *RwCameraCreate(void);
extern RwCamera    *RwCameraClone(RwCamera * camera);

/* Offset */
extern RwCamera    *RwCameraSetViewOffset(RwCamera *camera,
                                          const RwV2d *offset);

/* View window */
extern RwCamera    *RwCameraSetViewWindow(RwCamera *camera,
                                          const RwV2d *viewWindow);

/* Projection */
extern RwCamera    *RwCameraSetProjection(RwCamera *camera,
                                          RwCameraProjection projection);

/* Clip planes */
extern RwCamera    *RwCameraSetNearClipPlane(RwCamera *camera, RwReal nearClip);
extern RwCamera    *RwCameraSetFarClipPlane(RwCamera *camera, RwReal farClip);

/* Attaching toolkits */
extern RwInt32      RwCameraRegisterPlugin(RwInt32 size,
                                           RwUInt32 pluginID,
                                           RwPluginObjectConstructor
                                           constructCB,
                                           RwPluginObjectDestructor
                                           destructCB,
                                           RwPluginObjectCopy copyCB);
extern RwInt32      RwCameraGetPluginOffset(RwUInt32 pluginID);
extern RwBool       RwCameraValidatePlugins(const RwCamera * camera);

/* Frustum testing */
extern RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera *
                                                     camera,
                                                     const RwSphere *
                                                     sphere);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

/* Offset */
extern const RwV2d *RwCameraGetViewOffset(const RwCamera *camera);

/* Rasters */
extern RwCamera    *RwCameraSetRaster(RwCamera *camera, RwRaster *raster);
extern RwRaster    *RwCameraGetRaster(const RwCamera *camera);
extern RwCamera    *RwCameraSetZRaster(RwCamera *camera, RwRaster *zRaster);
extern RwRaster    *RwCameraGetZRaster(const RwCamera *camera);

/* Clip planes */
extern RwReal       RwCameraGetNearClipPlane(const RwCamera *camera);
extern RwReal       RwCameraGetFarClipPlane(const RwCamera *camera);
extern RwCamera    *RwCameraSetFogDistance(RwCamera *camera, RwReal fogDistance);
extern RwReal       RwCameraGetFogDistance(const RwCamera *camera);

extern RwCamera    *RwCameraGetCurrentCamera(void);

/* Projection */
extern RwCameraProjection RwCameraGetProjection(const RwCamera *camera);

/* View window */
extern const RwV2d *RwCameraGetViewWindow(const RwCamera *camera);

extern RwMatrix    *RwCameraGetViewMatrix(RwCamera *camera);

/* Frames */
extern RwCamera    *RwCameraSetFrame(RwCamera *camera, RwFrame *frame);
extern RwFrame     *RwCameraGetFrame(const RwCamera *camera);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/driver/common/barwtyp.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/pipe/p2/bapipe.h ---*/

#if (!defined(DOXYGEN))
struct rwPipeGlobals
{
    RwFreeList          *pipesFreeList;   /* Save mallocs, use a freelist */
    RxRenderStateVector  defaultRenderState;
    RwLinkList           allPipelines;    /* Unused as of yet, meant to be used to keep track of all
                                           * created pipelines (for CBs and maybe cleanup) */
    RwUInt32             maxNodesPerPipe; /* Initialised from _rxPipelineMaxNodes at startup. Used to
                                           * allow conservative, single allocations during pipelock */

    /* NOTE: Rw and RpWorld PowerPipe globals kept together for simplicity */

    /* The current default pipelines (used if pipe == NULL for an object) */
    RxPipeline          *currentAtomicPipeline;
    RxPipeline          *currentWorldSectorPipeline;
    RxPipeline          *currentMaterialPipeline;
    /* Generic C-based pipes that run on all platforms
     * - these are set as the current pipes at startup unless
     *   platform-specific pipes (below) are created */
    RxPipeline          *genericAtomicPipeline;
    RxPipeline          *genericWorldSectorPipeline;
    RxPipeline          *genericMaterialPipeline;
    /* Platforms that have their own non-generic pipelines
     * (OPENGL, D3D8, SKY2, KAMUI2, DOLPHIN) put them here: */
    RxPipeline          *platformAtomicPipeline;
    RxPipeline          *platformWorldSectorPipeline;
    RxPipeline          *platformMaterialPipeline;
};
#endif /* (!defined(DOXYGEN)) */

typedef struct rwPipeGlobals rwPipeGlobals;

#define RXPIPELINEGLOBAL(var) (RWPLUGINOFFSET(rwPipeGlobals, RwEngineInstance, _rxPipelineGlobalsOffset)->var)

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RwInt32      _rxPipelineGlobalsOffset;

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/driver/common/imrascnv.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/src/babincam.h ---*/
/****************************************************************************
 Global types
 */

/* Camera stream format */

/**
 * \ingroup rwcamera
 * \ref RwCameraChunkInfo is typedef'd to a structure that holds camera
 * data. This should be considered an opaque type. Use the RwCamera
 * API functions to access it.
 */

typedef struct rwStreamCamera RwCameraChunkInfo;
typedef struct rwStreamCamera rwStreamCamera;

#if (!defined(DOXYGEN))
struct rwStreamCamera
{
    RwV2d viewWindow;
    RwV2d viewOffset;
    RwReal nearPlane, farPlane;
    RwReal fogPlane;
    RwUInt32 projection;
};
#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Camera binary format */
extern RwInt32 RwCameraRegisterPluginStream(RwUInt32 pluginID,
                                            RwPluginDataChunkReadCallBack readCB,
                                            RwPluginDataChunkWriteCallBack writeCB,
                                            RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 RwCameraSetStreamAlwaysCallBack(
                   RwUInt32 pluginID,
                   RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwUInt32 RwCameraStreamGetSize(const RwCamera *camera);
extern RwCamera *RwCameraStreamRead(RwStream *stream);
extern const RwCamera *RwCameraStreamWrite(const RwCamera *camera,
                                           RwStream *stream);
extern RwCameraChunkInfo * RwCameraChunkInfoRead(RwStream *stream,
                                                 RwCameraChunkInfo *cameraChunkInfo,
                                                 RwInt32 *bytesRead);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RWCORE_H */
