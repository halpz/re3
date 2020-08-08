/***************************************************************************
 *                                                                         *
 * Module  : rtimport.h                                                    *
 *                                                                         *
 * Purpose : World handling functions.                                     *
 *                                                                         *
 **************************************************************************/

#ifndef RTIMPORT_H
#define RTIMPORT_H

/**
 * \defgroup rtimport RtWorldImport
 * \ingroup rttool
 *
 * World Import Toolkit for Renderware.
 */

/**
 * \defgroup selectors RtWorldImportPartitionSelectors
 * \ingroup rtimport
 *
 * The set of provided RtWorldImportPartitionSelectors:
 * Selects a good partition by calling one of the
 * \ref iterators and then
 * one of the \ref evaluators to
 * see which is best.
 */

/**
 * \defgroup iterators RtWorldImportPartitionIterators
 * \ingroup rtimport
 *
 * The set of provided RtWorldImportPartitionIterators:
 * Iterates through a set of candidate partitions, possibly
 * using the geometric information in the build sector, or perhaps
 * using some other criteria.
 */

/**
 * \defgroup evaluators RtWorldImportPartitionEvaluators
 * \ingroup rtimport
 *
 * The set of provided RtWorldImportPartitionEvaluators:
 * Uses a combination of statistics, build sector, build status, and 
 * possibly other criteria to evaluate a partition. While the value
 * returned can be any real value, all provided evaluators are return
 * lower values for better partitioners, and are in the range [0..1]
 * where appropriate
 */

/**
 * \defgroup terminators RtWorldImportPartitionTerminators
 * \ingroup rtimport
 *
 * The set of provided RtWorldImportPartitionTerminators:
 * Checks given criteria about the statistics, build sector, build status, and
 * possibly other criteria to see whether the building process should be
 * allowed to terminate, or whether more parititoning is necessary.
 */

/**
 * \defgroup kd RtWorldImportGuideKD
 * \ingroup rtimport
 *
 * Tools to manipulate the \ref RtWorldImportGuideKDTree that is used to
 * manually build the sectors of a world.
 */

/**
 * \defgroup hints RtWorldImportHints
 * \ingroup rtimport
 *
 * Tools to aid the build process by giving hints as to what geometry should
 * not be split, and what geometry makes for a good partitioning guide.
 */

/****************************************************************************
 Includes
 */
#include "rwcore.h"
#include "rpworld.h"

#include "rtimport.rpe"        /* automatically generated header file */

/****************************************************************************
 Defines
 */

/* Progress callback message types */
#define rtWORLDIMPORTPROGRESSBSPBUILDSTART      0
#define rtWORLDIMPORTPROGRESSBSPBUILDUPDATE     1
#define rtWORLDIMPORTPROGRESSBSPBUILDEND        2
#define rtWORLDIMPORTPROGRESSBSPCOMPRESSSTART   3
#define rtWORLDIMPORTPROGRESSBSPCOMPRESSUPDATE  4
#define rtWORLDIMPORTPROGRESSBSPCOMPRESSEND     5

/**
 * \ingroup rtimport
 * \def rtWORLDIMPORTINVALIDPARTITION
 *
 * This value means that no partition was found, or that the partition was
 * invalid or impractical. The value represents infinity. 
 */
#define rtWORLDIMPORTINVALIDPARTITION  RwRealMAXVAL

/****************************************************************************
 Global types
 */

/**
 * Internal use only
 */
typedef union RtWorldImportVertexState RtWorldImportVertexState;


/**
 * \ingroup rtimport
 * \typedef RtWorldImportVertex
 *
 * typedef for struct \ref RtWorldImportVertex
 */
typedef struct RtWorldImportVertex RtWorldImportVertex;

/**
 * \ingroup rtimport
 * \typedef RtWorldImportWeldVertex
 *
 * typedef for struct \ref RtWorldImportWeldVertex
 */
typedef struct RtWorldImportWeldVertex RtWorldImportWeldVertex;

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildVertex
 *
 * typedef for struct \ref RtWorldImportBuildVertex
 */
typedef struct RtWorldImportBuildVertex RtWorldImportBuildVertex;



/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildPolyInfo
 *
 * typedef for struct \ref RtWorldImportBuildPolyInfo
 */
typedef struct RtWorldImportBuildPolyInfo RtWorldImportBuildPolyInfo;
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildPolyInfo
 *
 * Information about a polygon
 */
struct RtWorldImportBuildPolyInfo
{
    RwInt16 matIndex;
    /**< The material index */
    RwUInt8 clipFlags;
    /**< Clipping flags */
    RwUInt8 hasAlpha;
    /**< Alpha status */
    void   *pUserdata;
    /**< Userdata */
};

typedef union RtWorldImportBuildVertexMode RtWorldImportBuildVertexMode;
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildVertexMode
 *
 * Mode of the vertex.
 *
 */
union RtWorldImportBuildVertexMode
{
    RtWorldImportVertex     *vpVert;
    /**< The vertex */
    RwInt32                     index;
    /**< The index */
};

/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildVertex
 *
 * A list of polygons as a list of vertices where the end of poly boundary
 * is marked by mode.vpVert == NULL.
 *
 */
struct RtWorldImportBuildVertex
{
    RtWorldImportBuildVertexMode mode;
    /**< The mode of the element */

    RtWorldImportBuildPolyInfo pinfo;
    /**< we store some poly info in the end marker of a boundary */
};



/**
 * \ingroup rtimport
 * \typedef RtWorldImportGuideKDTree
 *
 * typedef for struct \ref RtWorldImportGuideKDTree
 */
typedef struct RtWorldImportGuideKDTree RtWorldImportGuideKDTree;

/* NB Merged RtWorldImportPartition with RtWorldImportBuildClipStatistics because
 * there was a unique one-to-one relationship between them, and it made things easier
 * just updating one stucture, without having to update both in sequence...
 */

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildClipStatistics
 *
 * typedef for struct \ref RtWorldImportBuildClipStatistics
 */
typedef struct RtWorldImportBuildClipStatistics RtWorldImportBuildClipStatistics;
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildClipStatistics
 *
 * Holds statistics about a partition or candidate partition during
 * the build process.
 */
struct RtWorldImportBuildClipStatistics
{
    RwInt32 numPotentialSplit;
    /**< The number of polygons split by the partition,
     *   disgregarding overlaps */

    RwInt32 numPotentialLeft;
    /**< The number of potential polygons and fragments on the
     *   left of the partition, disgregarding overlaps */

    RwInt32 numPotentialRight;
    /**< The number of potential polygons and fragments on the
     *   right of the partition, disgregarding overlaps */


    RwInt32 numActualSplit;
    /**< The number of polygons split by the partition */

    RwInt32 numActualLeft;
    /**< The number of polygons and fragments on the
     *   left of the partition */

    RwInt32 numActualRight;
    /**< The number of polygons and fragments on the
     *   right of the partition */


    RwInt32 numMaterialLeft;
    /**< The number of materials on the left of the partition */

    RwInt32 numMaterialRight;
    /**< The number of materials on the right of the partition */

    RwInt32 numMaterialSplits;
    /**< The number of materials split by the partition */

    
    RwInt32 numMaterialSector;
    /**< The total number of materials in the sector containing
     *   the partition */


    RwReal overlapLeft;
    /**< The actual, relative size of the overlap on the left of the partition */

    RwReal overlapRight;
    /**< The actual, relative size of the overlap on the right of the partition */
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportPartition
 *
 * typedef for struct \ref RtWorldImportPartition
 */
typedef struct RtWorldImportPartition RtWorldImportPartition;
/**
 * \ingroup rtimport
 * \struct RtWorldImportPartition
 *
 * A partitioning plane.
 */
struct RtWorldImportPartition
{
    RwInt32 type;
    /**< Plane type, i.e. 0,4,8 for being normal to the x,y,z axes respectively. */

    RwReal  value;
    /**< The distance of the plane from the origin */

    RwReal  maxLeftValue;
    /**< The maximum value of the left face of the overlap. This is derived
     *   from the maxOverlapPercent value in \ref RtWorldImportParameters
     */

    RwReal  maxRightValue;
    /**< The maximum value of the right face of the overlap. This is derived
     *   from the maxOverlapPercent value in \ref RtWorldImportParameters
     */

    RtWorldImportBuildClipStatistics buildStats;
    /**< The statistics for the partition */
};

/**
 * \ingroup rtimport
 * \struct RtWorldImportGuideKDTree
 * Represents the structure of a binary tree with
 * no contents per se. It is used to build a BSP in a user specified
 * manner instead of using any heuristic.
 *
 */
struct RtWorldImportGuideKDTree
{
    RtWorldImportPartition partition;
    /**< A partitioning plane */

    RwBBox      bbox;
    /**< Bounding box of the sector or super-sector */

    RtWorldImportGuideKDTree  *parent;
    /**< Pointer to its parent */

    RwInt32     order;
    /**< Relationship information - 0 for left child, 1 for right child */

    RtWorldImportGuideKDTree  *left;
    /**< Left child */

    RtWorldImportGuideKDTree  *right;
    /**< Right child */
};

typedef struct _rtWorldImportGuideKDStackElement _rtWorldImportGuideKDStackElement;

struct _rtWorldImportGuideKDStackElement
{
    RwBool terminal;
    RtWorldImportGuideKDTree *node;
    _rtWorldImportGuideKDStackElement *next;
};

typedef struct _rtWorldImportGuideKDStack _rtWorldImportGuideKDStack;

struct _rtWorldImportGuideKDStack
{
    _rtWorldImportGuideKDStackElement *top;
    _rtWorldImportGuideKDStackElement *current;
    _rtWorldImportGuideKDStackElement *bottom;
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildSector
 *
 * typedef for struct \ref RtWorldImportBuildSector
 */
typedef struct RtWorldImportBuildSector RtWorldImportBuildSector;
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildSector
 *
 * Holds information about the sector that is being subdivided
 */
struct RtWorldImportBuildSector
{
    RwInt32 type;                   
    /**< Sector type (so can handle in an RpWorld) */

    RtWorldImportVertex *vertices;
    /**< A pointer to the list of vertices */

    RwInt32 numVertices;
    /**< The number of vertices */

    RtWorldImportBuildVertex *boundaries;
    /**< A list of boundaries \see RtWorldImportBuildVertex */
        
    RwInt32 numBoundaries;
    /**< The number of boundaries */

    RwInt32 numPolygons;
    /**< The number of polygons (triangles) */

    RwBBox boundingBox;
    /**< Sector's bounding box */

    RwReal overlap;
    /**< The percentage that the sector overlaps with its neighbour */

    RwUInt32 maxNumMaterials;
    /**< Maximum number of materials in the in the world */
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildStatus
 *
 * typedef for struct \ref RtWorldImportBuildStatus
 */
typedef struct RtWorldImportBuildStatus RtWorldImportBuildStatus;
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildStatus
 * World Import Build Status Structure
 * Used to store the current tree's build status
 */
struct RtWorldImportBuildStatus
{
    RwInt32 depth; /**< current depth in the tree */
};

/**
 * Internal use only
 */
union RtWorldImportVertexState
{
    /* clipFlags, two types, first is based on partition only, 2nd is
     * also based on partition, but takes overlaps into consideration. i.e.
     * number splits is usually higher in clipFlags[0] than [1] */
    RwInt32                    clipFlags[2];       /**< Internal use only */
    RwInt32                    forwardingAddress;  /**< Internal use only */
    RtWorldImportVertex       *vpVert;             /**< Internal use only */
    RtWorldImportWeldVertex   *vpWeldVert;         /**< Internal use only */
    RtWorldImportBuildVertex  *vpBuildVert;        /**< Internal use only */
    RwSList                   *slist;              /**< Internal use only */
};

/**
 * \ingroup rtimport
 * \struct RtWorldImportVertex
 * Holds data for each vertex in the import world.
 *
 */
struct RtWorldImportVertex
{
    RwV3d           OC;         /**< World space vertex position */
    RwV3d           normal;     /**< World space vertex normal */
    RwRGBA          preLitCol;  /**< Vertex Prelight color */
    RwTexCoords     texCoords[rwMAXTEXTURECOORDS];  
                                /**< Vertex texture coordinates */
    RtWorldImportVertexState state;  /**< Internal use only */
    RwInt32         matIndex;   /**< Vertex material index */
    void           *pUserdata;  /**< Pointer to unspecified per vertex user data */
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportTriangle 
 * Holds data for each triangle in the import world.
 *
 * \see RtWorldImportTriangle
 */
typedef struct RtWorldImportTriangle RtWorldImportTriangle;
/**
 * \ingroup rtimport
 * \struct RtWorldImportTriangle
 * Holds data for each triangle in the import world.
 *
 * \see RtWorldImportTriangle
 */
struct RtWorldImportTriangle
{
    RwInt32             matIndex;       /**< Index into material list */
    RwInt32             vertIndex[3];   /**< Indices into vertex list */
    void               *pUserdata;      /**< Pointer to unspecified per triangle user data */
};


/**
 * \ingroup rtimport
 * \typedef RtWorldImportHints
 *
 * typedef for struct \ref RtWorldImportHints
 */
typedef struct RtWorldImportHints RtWorldImportHints;

/**
 * \ingroup rtimport
 * \struct RtWorldImportHints
 * Bounding box hints used to control the world sectorization process.
 * \see RtWorldImportHintsSet
 */
struct RtWorldImportHints
{    
    /** The bounding box hints */
    RwBBox *boundingBoxes;   
    /** The number of bounding box hints */
    RwInt32 numBoundingBoxes;
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportParameters
 *
 * typedef for struct \ref RtWorldImportParameters
 */
typedef struct RtWorldImportParameters RtWorldImportParameters;

/**
 * \ingroup rtimport
 * \struct RtWorldImportParameters
 * Parameters used with \ref RtWorldImportCreateWorld.
 * They are initialized to default values using \ref RtWorldImportParametersInit.
 * 
 */
struct RtWorldImportParameters
{
    RwReal              worldSectorMaxSize;
    /**< The maximum world sector size. */
    RwInt32             maxWorldSectorPolygons;
    /**< The maximum number of polygons in a world sector. */
    RwReal              maxOverlapPercent;
    /**< Total fraction of world sector overlap allowed. */
    RwReal              weldThreshold;
    /**< Threshold for welding vertices. */
    RwReal              angularThreshold;
    /**< Angular threshold for welding vertex normals */
    RwBool              calcNormals;
    /**< If TRUE then importer creates normals. */
    RwBool              conditionGeometry;
    /**< If TRUE perform vertex welding and degenerate triangle removal.*/
    RwBool              userSpecifiedBBox;
    /**< If TRUE allows user to specify minimum bounding-box for the
     *   world using the userBBox parameter. */
    RwBBox              userBBox;
    /**< User specified world bounding-box if userSpecifiedBBox is TRUE.*/
    RwReal              uvLimit;
    /**< If conditionGeometry is TRUE limit texture coordinates to this
     *  value. */
    RwBool              retainCreases;
    /**< If TRUE then duplicate vertices with differing normals will not
     *  be merged. */
    RwBool              fixTJunctions;
    /**< If TRUE then T-junctions are fixed in the geometry (slow). */
    RwBool              weldPolygons;
    /**< If TRUE then polygons are welded where possible to reduce the
     *  polygon count. */
    RwInt32             flags;
    /**< Conversion flags (see RpWorldFlag). */
    RwTextureAddressMode mode;
    /**< If \ref rwTEXTUREADDRESSWRAP than weld vertices according to
     *   mod(1) congruent texture coordinates */
    RwBool              sortPolygons;
    /**< If TRUE then polygons are sorted by their centroid */
    RwBool              cullZeroAreaPolygons;    
    /**< If TRUE then zero-area polygons are culled  */
    RwInt32             numTexCoordSets;
    /**< The number of texture coordinate sets to use. If set to zero, then
     *   the number is taken from the flags parameter which, for backward
     *   compatibility, can include the \ref rpWORLDTEXTURED or \ref rpWORLDTEXTURED2
     *   flags. These specify one or two sets respectively. */
    RwBool              terminatorCheck;
    /**< If TRUE the world will be checked for validity during the build process. */
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImport
 *
 * typedef for struct \ref RtWorldImport
 */
typedef struct RtWorldImport RtWorldImport;
/**
 * \ingroup rtimport
 * \struct RtWorldImport
 * World Import State Structure
 */
struct RtWorldImport
{
    RpMaterialList      matList;     /**< Material list */
    RtWorldImportVertex *vertices;   /**< Vertex array */
    RwInt32             numVertices; /**< Vertex count */

    RtWorldImportTriangle *polygons; /**< Triangle array */
    RwInt32             numPolygons; /**< Triangle count */

    
    RwSurfaceProperties surfaceProps; /**< The world's surface 
                                           lighting properties */
};

/**
 * \ingroup rtimport
 * \ref RtWorldImportProgressCallBack is the type for the callback function supplied to
 * \ref RtWorldImportSetProgressCallBack.
 *
 * \param  msg   Message type corresponding to one of the following:
 *      \li rtWORLDIMPORTPROGRESSBSPBUILDSTART -
 *          The BSP creation process is about to start.
 *          The argument value is equal to 0.0.
 *      \li rtWORLDIMPORTPROGRESSBSPBUILDUPDATE -
 *          The BSP creation process has finished processing a subsection of
 *          the world. The argument value is equal to the percentage of the
 *          world processed up to this point.
 *      \li rtWORLDIMPORTPROGRESSBSPBUILDEND -
 *          The BSP creation process has ended.
 *          The argument value is equal to 100.0.
 *      \li rtWORLDIMPORTPROGRESSBSPCOMPRESSSTART -
 *          The BSP compression process is about to start. The argument value
 *          is equal to 0.0.
 *      \li rtWORLDIMPORTPROGRESSBSPCOMPRESSUPDATE -
 *          The BSP compression has finished processing a subsection of the
 *          world. The argument value is equal to the percentage of the world
 *          processed up to this point.
 *      \li rtWORLDIMPORTPROGRESSBSPCOMPRESSEND -
 *          The BSP compression process has ended. The argument value is equal
 *          to 100.0.
 *
 * \param  value   The percentage of the progress made in either BSP
 *          building or BSP compression.
 *
 * \return TRUE to continue BSP processing, FALSE to abort.
 *
 * \see RtWorldImportSetProgressCallBack
 */
typedef RwBool (*RtWorldImportProgressCallBack)(RwInt32 msg, RwReal value);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportDestroyVertexUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * vertex destruction.
 */
typedef RwBool (*RtWorldImportDestroyVertexUserdataCallBack)(void **pUserdata);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportCloneVertexUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * vertex cloning.
 */
typedef RwBool (*RtWorldImportCloneVertexUserdataCallBack)(void **pUserdataDst, void **pUserdataSrc);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportInterpVertexUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * vertex interpolation.
 */
typedef RwBool (*RtWorldImportInterpVertexUserdataCallBack)(void **pUserdataDst, void **pUserdata1, void **pUserdata2, RwReal delta);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportDestroyPolygonUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * polygon destruction.
 */
typedef RwBool (*RtWorldImportDestroyPolygonUserdataCallBack)(void **pUserdata);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportSplitPolygonUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * polygon division.
 */
typedef RwBool (*RtWorldImportSplitPolygonUserdataCallBack)(void **pUserdataDst, void **pUserdataSrc);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportSectorSetVertexUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * the setting of the vertex user data.
 */
typedef RwBool (*RtWorldImportSectorSetVertexUserdataCallBack)(void **pUserdata, RpWorldSector *sector, RwInt32 index);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportSectorSetPolygonUserdataCallBack
 *
 * A pointer to the CallBack function that will be called during
 * the setting of the polygon user data.
 */
typedef RwBool (*RtWorldImportSectorSetPolygonUserdataCallBack)(void **pUserdata, RpWorldSector *sector, RwInt32 index);




/**
 * \ingroup rtimport
 * \typedef RtWorldImportTerminationBuildCallBack
 *
 * A pointer to the function that will be called during the
 * build process to determine whether the current sector should
 * be subdivided further, or terminated.
 */
typedef RwBool (*RtWorldImportTerminationBuildCallBack)
               (RtWorldImportBuildSector *buildSector,
    	 	    RtWorldImportBuildStatus *buildStatus,
                void *pData);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportPartitionBuildCallBack
 *
 * A pointer to the function that will be called during the
 * build process to select a suitable sector partition.
 */
typedef RwReal (*RtWorldImportPartitionBuildCallBack)
             (RtWorldImportBuildSector *buildSector,
              RtWorldImportBuildStatus *buildStatus,
              RtWorldImportPartition *partition,
              void *pData);

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildCallBacks
 *
 * typedef for struct \ref RtWorldImportBuildCallBacks
 */
typedef struct RtWorldImportBuildCallBacks RtWorldImportBuildCallBacks; /* MAYBE: rename to SectorCallBacks ?*/
/**
 * \ingroup rtimport
 * \struct RtWorldImportBuildCallBacks
 * Sectorization callbacks
 */
struct RtWorldImportBuildCallBacks
{
    RtWorldImportPartitionBuildCallBack  partitionBuild;
    /**< Callback for choosing partition */
    void *partitionUserData;
    /**< Partition callback user data */
    RtWorldImportTerminationBuildCallBack terminationBuild;
    /**< Callback for termination of further partitioning */
    void *terminationUserData;
    /**< Termination callback user data */    
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportUserdataCallBacks
 *
 * typedef for struct \ref RtWorldImportUserdataCallBacks
 */
typedef struct RtWorldImportUserdataCallBacks RtWorldImportUserdataCallBacks;
/**
 * \ingroup rtimport
 * \struct RtWorldImportUserdataCallBacks
 * Bundle of callbacks
 */
struct RtWorldImportUserdataCallBacks
{
    RtWorldImportDestroyVertexUserdataCallBack destroyVertexUserdata;
        /**< Callback on vertex destruction */
    RtWorldImportCloneVertexUserdataCallBack cloneVertexUserdata;
        /**< Callback on vertex cloning */
    RtWorldImportInterpVertexUserdataCallBack interpVertexUserdata;
        /**< Callback on vertex interpolation */
    RtWorldImportDestroyPolygonUserdataCallBack destroyPolygonUserdata;
        /**< Callback on polygon destruction */
    RtWorldImportSplitPolygonUserdataCallBack splitPolygonUserdata;
        /**< Callback on polygon division */
    RtWorldImportSectorSetVertexUserdataCallBack sectorSetVertexUserdata;
        /**< Callback on setting vertex user data */
    RtWorldImportSectorSetPolygonUserdataCallBack sectorSetPolygonUserdata;
        /**< Callback on setting polygon user data */
};

/**
 * \ingroup rtimport
 * \typedef RtWorldImportBuildPartitionSelector
 *
 * An enumeration that can be passed to
 * \ref RtWorldImportSetStandardBuildPartitionSelector to determine
 * whether partitioning will be achieved automatically, using the
 * default partition selected, or manually using the \ref RtWorldImportGuideKDTree
 */
typedef enum 
{
    rwBUILDPARTITIONSELECTOR_DEFAULT,
        /**< Sets the default automated process */
    rwBUILDPARTITIONSELECTOR_GUIDED
        /**< Sets the guided manual process */
}
RtWorldImportBuildPartitionSelector;




/* Builds overlaps from plane and conversion params */
#define BuildSectorSetOverlapsMacro(_boundingBox, _partition, _conversionParams)    \
MACRO_START                                                                         \
{                                                                                   \
    RwReal sup = GETCOORD((_boundingBox).sup, (_partition).type);                   \
    RwReal inf = GETCOORD((_boundingBox).inf, (_partition).type);                   \
                                                                                    \
    (_partition).maxLeftValue =                                                       \
        (_partition).value +                                                        \
        ((sup - (_partition).value) * (_conversionParams).maxOverlapPercent);       \
                                                                                    \
    (_partition).maxRightValue =                                                        \
        (_partition).value -                                                        \
        ((((_partition).value) - inf) * (_conversionParams).maxOverlapPercent);     \
}                                                                                   \
MACRO_STOP

/*****************************************************************************
 *  Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif /* __cplusplus */

extern RwBool
_rtImportBuildSectorFindBBox(RtWorldImportBuildSector *buildSector, RwBBox *bbpOut);

/* TODO: decide where these scheme functions are going and which ones are public and 
    whether _rt or RT should be used */
extern void
    _rtWorldImportGuideKDCopy(RtWorldImportGuideKDTree *KD, RpSector *spSector, RwInt32 depth);
extern void _rtWorldImportGuideKDStackDestroy(_rtWorldImportGuideKDStack *stack);
extern void
_rtWorldImportGuideKDEncodeAsStack(RtWorldImportGuideKDTree *tree, _rtWorldImportGuideKDStack *stack);

extern RtWorldImportGuideKDTree *RtWorldImportGuideKDCreate(RwBBox *bbox);
extern RtWorldImportGuideKDTree *RtWorldImportGuideKDAddPartition
                        (RtWorldImportGuideKDTree *KD, RwInt32 type, RwReal value);
extern void RtWorldImportGuideKDDeletePartition(RtWorldImportGuideKDTree *KD);
extern void RtWorldImportGuideKDDestroy(RtWorldImportGuideKDTree *KD);

extern RtWorldImportGuideKDTree *RtWorldImportGuideKDWrite(
                        RtWorldImportGuideKDTree *guideKD, const RwChar *filename);
extern RtWorldImportGuideKDTree * RtWorldImportGuideKDRead(
                        const RwChar *filename, const RwBBox *bbox);

/*****************************************************************************
 *  PARTITION SELECTORS - These callbacks for used to select a partition
 *  from a sector.
 */

extern RwReal
RtWorldImportBalancedCullPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportMaterialCountPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportMaterialSeparatePartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportMaximumOccluderPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportDisjointOccluderPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportLeastCutAndBalancedPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportMaximumExtentPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportCullMiddleSpacePartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportCullEndSpacePartitionSelector(RtWorldImportBuildSector * buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportCullSpacePartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportHintBBoxPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportGeneralOccluderPartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportBalancedTreePartitionSelector(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

/*****************************************************************************
 *  PARTITION ITERATORS - These callbacks iterate though a set of partitions
 */

extern RwBool
RtWorldImportOrthogonalAutoPartitionIterator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData,
                                    RwInt32* loopCounter);


extern RwBool
RtWorldImportRegularIntervalPartitionIterator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData,
                                    RwInt32* loopCounter);


extern RwBool
RtWorldImportMiddleAxisPartitionIterator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData,
                                    RwInt32 * loopCounter);


extern RwBool 
RtWorldImportMedianPercentagePartitionIterator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData,
                                    RwInt32 *loopCounter);


extern RwBool
RtWorldImportHintBBoxPartitionIterator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData,
                                    RwInt32* loopCounter);

extern RwBool
RtWorldImportHighestVertexAccommodatingPlanePartitionIterator(RtWorldImportBuildSector *buildSector,
                                                              RtWorldImportBuildStatus * buildStatus,
                                                              RtWorldImportPartition *partition,
                                                              void * userData,
                                                              RwInt32* loopCounter);

extern RwBool
RtWorldImportMaterialBoundsPartitionIterator(RtWorldImportBuildSector *buildSector,
                                             RtWorldImportBuildStatus * buildStatus,
                                             RtWorldImportPartition *partition,
                                             void *userData,
                                             RwInt32 *loopCounter);

/*****************************************************************************
 *  PARTITION EVALUATORS - These callbacks iterate though a set of partitions
 */

extern RwReal
RtWorldImportFuzzyBalancedPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);


extern RwReal
RtWorldImportPotentialSplitPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);


extern RwReal
RtWorldImportBalancedPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);


extern RwReal
RtWorldImportExtentPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);


extern RwReal
RtWorldImportOccluderPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);


extern RwReal
RtWorldImportWeightedOccluderPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void * userData);

extern RwReal
RtWorldImportHintBBoxPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                    RtWorldImportBuildStatus *buildStatus,
                                    RtWorldImportPartition *partition,
                                    void *userData);

extern RwReal
RtWorldImportVolumeBalancedPartitionEvaluator(RtWorldImportBuildSector * buildSector,
                                              RtWorldImportBuildStatus * buildStatus,
                                              RtWorldImportPartition *partition,
                                              void * userData);

extern RwReal
RtWorldImportWeightedDisjointOccluderPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                                        RtWorldImportBuildStatus *buildStatus,
                                                        RtWorldImportPartition *partition,
                                                        void * userData);

extern RwReal
RtWorldImportMaterialCutsPartitionEvaluator(RtWorldImportBuildSector * buildSector,
                                            RtWorldImportBuildStatus * buildStatus,
                                            RtWorldImportPartition *partition,
                                            void * userData);

extern RwReal
RtWorldImportMaterialBalancedPartitionEvaluator(RtWorldImportBuildSector * buildSector,
                                                RtWorldImportBuildStatus *buildStatus,
                                                RtWorldImportPartition *partition,
                                                void * userData);

extern RwReal
RtWorldImportAspectPartitionEvaluator(RtWorldImportBuildSector *buildSector,
                                      RtWorldImportBuildStatus * buildStatus,
                                      RtWorldImportPartition *partition,
                                      void * userData);

extern RwReal
RtWorldImportMaterialSeparatorPartitionEvaluator(RtWorldImportBuildSector * buildSector,
                                                 RtWorldImportBuildStatus * buildStatus,
                                                 RtWorldImportPartition *partition,
                                                 void * userData);
/*****************************************************************************
 *  PARTITION TERMINATORS - These callbacks are used to decide when
 *  partitioning of a sector should stop
 */
extern RwBool
RtWorldImportNeverPartitionTerminator(RtWorldImportBuildSector * buildSector,
                    RtWorldImportBuildStatus * buildStatus,
                    void * userData);

extern RwBool
RtWorldImportMaximumLegalPartitionTerminator(RtWorldImportBuildSector * buildSector,
                    RtWorldImportBuildStatus * __RWUNUSED__ buildStatus,
                    void * __RWUNUSED__ userData);

extern RwBool
RtWorldImportDefaultPartitionTerminator(RtWorldImportBuildSector * buildSector,
                    RtWorldImportBuildStatus * buildStatus,
                    void * pData);


extern RwBool
RtWorldImportDepthPartitionTerminator(RtWorldImportBuildSector * buildSector,
                    RtWorldImportBuildStatus * buildStatus,
                    void * userData);


extern RwBool
RtWorldImportSectorHeightPartitionTerminator(RtWorldImportBuildSector * buildSector,
                    RtWorldImportBuildStatus * buildStatus,
                    void * userData);

extern RwBool
RtWorldImportSizePartitionTerminator(RtWorldImportBuildSector * buildSector,
                                     RtWorldImportBuildStatus * buildStatus,
                                     void * userData);

extern RwBool
RtWorldImportSectorAspectSizePartitionTerminator(RtWorldImportBuildSector * buildSector,
                                                 RtWorldImportBuildStatus * buildStatus,
                                                 void * userData);



/* END TODO */

/* WorldImport hints */
extern void
RtWorldImportHintsSet(RtWorldImportHints *hints);

extern RtWorldImportHints *
RtWorldImportHintsGet(void);

extern RtWorldImportHints *
RtWorldImportHintsCreate(void);

extern RwBool
RtWorldImportHintsDestroy(RtWorldImportHints *hints);

extern RtWorldImportHints *
RtWorldImportHintsAddBoundingBoxes(RtWorldImportHints *hints, RwInt32 numBoundingBoxes);

extern void
RtWorldImportMaterialGroupHintGenerator(RtWorldImportBuildSector *buildSector,
                                        RtWorldImportHints *materialGroupHints);

/* Initializing the conversion structure */
extern RtWorldImportParameters *RtWorldImportParametersInit(void);
extern void RtWorldImportParametersSet(RtWorldImportParameters *params);
extern RtWorldImportParameters *RtWorldImportParametersGet(void);


extern RpWorld *RtWorldImportCreateWorld(RtWorldImport *
                                         nohsworld,
                                         RtWorldImportParameters
                                         * conversionParams);

extern RpGeometry *RtWorldImportCreateGeometry(RtWorldImport *
                                               nohsworld,
                                               RtWorldImportParameters
                                               * conversionParams);

extern RtWorldImport *RtWorldImportCreate(void);

extern RwBool RtWorldImportDestroy(RtWorldImport * nohsworld);

extern RtWorldImport *RtWorldImportAddNumVertices(RtWorldImport *
                                                  nohsworld,
                                                  RwInt32
                                                  numNewVertices);

extern RtWorldImport *RtWorldImportAddNumTriangles(RtWorldImport *
                                                   nohsworld,
                                                   RwInt32
                                                   numNewTriangles);

extern RpMaterial *RtWorldImportGetMaterial(RtWorldImport *
                                            nohsworld,
                                            RwInt32 matInd);

extern RwInt32 RtWorldImportGetNumVertices(RtWorldImport * nohsworld);

extern RtWorldImportVertex *RtWorldImportGetVertices(RtWorldImport *
                                                     nohsworld);

extern RwInt32 RtWorldImportGetNumTriangles(RtWorldImport * nohsworld);

extern RtWorldImportTriangle *
RtWorldImportGetTriangles(RtWorldImport * nohsworld);

/* Surface lighting characteristics */
extern RtWorldImport *
RtWorldImportSetSurfaceProperties(RtWorldImport * world,
                                  RwSurfaceProperties *
                                  surface);

extern RwSurfaceProperties *
RtWorldImportGetSurfaceProperties(RtWorldImport * world);

/* Progress callbacks */
extern void
RtWorldImportSetProgressCallBack(RtWorldImportProgressCallBack CB);

extern RpWorldSector * RtWorldImportGetNumMaterials(RpWorldSector *worldSector, void *data);

extern void
_rtImportWorldSendProgressMessage(RwInt32 msgtype, RwReal value);

/* Reading and Writing */

extern RtWorldImport *RtWorldImportWrite(RtWorldImport * world,
                                         RwChar * filename);

extern RtWorldImport *RtWorldImportRead(RwChar * filename);

extern RwInt32 RtWorldImportAddMaterial(RtWorldImport * nohsworld,
                                        RpMaterial * material);

extern RwInt32 RtWorldImportGetMaterialIndex(RtWorldImport * nohsworld,
                                             RpMaterial * material);

extern RtWorldImport *RtWorldImportForAllMaterials(RtWorldImport *
                                                   nohsworld,
                                                   RpMaterialCallBack
                                                   fpCallBack,
                                                   void *pData);

extern void
RtWorldImportSetUserdataCallBacks(RtWorldImportDestroyVertexUserdataCallBack
                                    destroyVertexUserdataCB,
                                  RtWorldImportCloneVertexUserdataCallBack
                                    cloneVertexUserdataCB,
                                  RtWorldImportInterpVertexUserdataCallBack
                                    interpVertexUserdataCB,
                                  RtWorldImportSectorSetVertexUserdataCallBack
                                    sectorSetVertexUserdata,
                                  RtWorldImportDestroyPolygonUserdataCallBack
                                    destroyPolygonUserdataCB,
                                  RtWorldImportSplitPolygonUserdataCallBack
                                    splitPolygonUserdataCB,
                                  RtWorldImportSectorSetPolygonUserdataCallBack
                                    sectorSetPolygonUserdata);

extern void
RtWorldImportSetBuildCallBacks(RtWorldImportPartitionBuildCallBack
                                partitionBuildCB,
                               RtWorldImportTerminationBuildCallBack
                                terminationBuildCB);

extern void
RtWorldImportSetPartitionStatistics(RtWorldImportBuildSector * buildSector,
                                      RtWorldImportPartition * partition);

extern void
RtWorldImportSetBuildCallBacksUserData(void *partitionUserData,
                                       void *terminateUserData);


extern void
RtWorldImportSetStandardBuildPartitionSelector(RtWorldImportBuildPartitionSelector partitionSelector, void* userData);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#define RtWorldImportParametersInitialize(_paramsPtr) \
    *(_paramsPtr) = *RtWorldImportParametersInit();



#endif                          /* RTIMPORT_H */



















