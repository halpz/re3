
#ifndef RPPTANK_H
#define RPPTANK_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"

/*---- start: ./ptank.h----*/

/**
 * \defgroup rpptank RpPTank
 * \ingroup rpplugin
 *
 * PTank Plugin for RenderWare.
 */

/*--- Include files ---*/
#include <string.h>

#include "rwcore.h"

#include "rpptank.rpe"    /* automatically generated header file */

/******************************************************************************
 *  Global Types
 */

/**
 * \ingroup rpptank
 * Passed to \ref RpPTankAtomicCreate, these flags specify
 * the type and properties held by the particles.
 * Some flags are mutually exclusive and should not be mixed.
 * The debug version of the library will assert and signal these problems.
 */
enum RpPTankDataFlags
{
    rpPTANKDFLAGNONE                     = ((int)0x00000000),
    rpPTANKDFLAGPOSITION                 = ((int)0x00000001),   /**<Uses a position per particle*/
    rpPTANKDFLAGCOLOR                    = ((int)0x00000002),   /**<Uses a color per particle*/
    rpPTANKDFLAGSIZE                     = ((int)0x00000004),   /**<Uses a size per particle*/
    rpPTANKDFLAGMATRIX                   = ((int)0x00000008),   /**<Uses a matrix per particle*/
    rpPTANKDFLAGNORMAL                   = ((int)0x00000010),   /**<Uses a normal per particle*/
    rpPTANKDFLAG2DROTATE                 = ((int)0x00000020),   /**<Uses a 2D rotation per particle*/
    rpPTANKDFLAGVTXCOLOR                 = ((int)0x00000040),   /**<Uses a color per Billboard vertex*/
    rpPTANKDFLAGVTX2TEXCOORDS            = ((int)0x00000080),   /**<Uses Top-Left and Bottom-Right Texture coordinates*/
    rpPTANKDFLAGVTX4TEXCOORDS            = ((int)0x00000100),   /**<Uses a texture UV per vertex*/
/*    free                               = ((int)0x00000200),    */
/*    free                               = ((int)0x00000400),    */
/*    free                               = ((int)0x00000800),    */
/*    free                               = ((int)0x00001000),    */
/*    free                               = ((int)0x00002000),    */
/*    free                               = ((int)0x00004000),    */
    rpPTANKDFLAGCNSMATRIX                = ((int)0x00008000),   /**<Uses a constant matrix*/
    rpPTANKDFLAGCNSNORMAL                = ((int)0x00010000),   /**<Uses a constant normal*/
    rpPTANKDFLAGCNS2DROTATE              = ((int)0x00020000),   /**<Uses a constant 2D rotation*/
    rpPTANKDFLAGCNSVTXCOLOR              = ((int)0x00040000),   /**<Uses a constant color per Billboard vertex*/
    rpPTANKDFLAGCNSVTX2TEXCOORDS         = ((int)0x00080000),   /**<Uses constant Top-Left and Bottom-Right Texture coordinates*/
    rpPTANKDFLAGCNSVTX4TEXCOORDS         = ((int)0x00100000),   /**<Uses a constant texture UV per vertex*/
/*    free                               = ((int)0x00200000),    */
/*    free                               = ((int)0x00400000),    */
/*    free                               = ((int)0x00800000),    */
    rpPTANKDFLAGUSECENTER                = ((int)0x01000000),    /**<The position of the particles are shifted*/
/*    free                               = ((int)0x04000000),    */
/*    free                               = ((int)0x08000000),    */
    rpPTANKDFLAGARRAY                    = ((int)0x10000000),    /**<Data is organized in an array */
    rpPTANKDFLAGSTRUCTURE                = ((int)0x20000000),    /**<Data is organized in a structure */

    RPPTANKDATAFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPTankDataFlags RpPTankDataFlags;

#define rpPTANKDFLAGTHINPARTICLES (rpPTANKDFLAGPOSITION)
#define rpPTANKDFLAGFATPARTICLES ( rpPTANKDFLAGPOSITION | rpPTANKDFLAGSIZE        \
                                 | rpPTANKDFLAG2DROTATE | rpPTANKDFLAGVTXCOLOR \
                                 | rpPTANKDFLAGVTX4TEXCOORDS)


/**
 * \ingroup rpptank
 * Passed to \ref RpPTankAtomicLock, these flags specify
 * the data accessed.
 * those flags are mutually exclusive and should not be mixed.
 */
enum RpPTankDataLockFlags
{
    rpPTANKLFLAGNONE                     = ((int)0x00000000),
    rpPTANKLFLAGPOSITION                 = ((int)0x00000001),   /**<Access the positions buffer*/
    rpPTANKLFLAGCOLOR                    = ((int)0x00000002),   /**<Access the colors buffer*/
    rpPTANKLFLAGSIZE                     = ((int)0x00000004),   /**<Access the sizes buffer*/
    rpPTANKLFLAGMATRIX                   = ((int)0x00000008),   /**<Access the matrixes buffer*/
    rpPTANKLFLAGNORMAL                   = ((int)0x00000010),   /**<Access the normals buffer*/
    rpPTANKLFLAG2DROTATE                 = ((int)0x00000020),   /**<Access the 2D rotations buffer*/
    rpPTANKLFLAGVTXCOLOR                 = ((int)0x00000040),   /**<Access the colors buffer (when using a color per vertex) */
    rpPTANKLFLAGVTX2TEXCOORDS            = ((int)0x00000080),   /**<Access the Top-Left and Bottom-Right Texture coordinates buffer*/
    rpPTANKLFLAGVTX4TEXCOORDS            = ((int)0x00000100),   /**<Access the texture UVs Buffer (when using a color per vertex)*/

    RPPTANKLOCKFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPTankDataLockFlags RpPTankDataLockFlags;


#if (!defined(DOXYGEN))

/**
 * \ingroup rpptank
 * RpPTankInstanceFlags
 */
enum RpPTankInstanceFlags
{
    rpPTANKIFLAGNONE             = ((int)0x00000000),
    rpPTANKIFLAGPOSITION         = ((int)0x00000001),    /**<Particles position changed*/
    rpPTANKIFLAGCOLOR            = ((int)0x00000002),   /**<Particles color changed*/
    rpPTANKIFLAGSIZE             = ((int)0x00000004),   /**<Particles size changed*/
    rpPTANKIFLAGMATRIX           = ((int)0x00000008),   /**<Particles matrix changed*/
    rpPTANKIFLAGNORMAL           = ((int)0x00000010),   /**<Particles normal changed*/
    rpPTANKIFLAG2DROTATE         = ((int)0x00000020),   /**<Particles 2D rotation changed*/
    rpPTANKIFLAGVTXCOLOR         = ((int)0x00000040),    /**<Vertex color changed*/
    rpPTANKIFLAGVTX2TEXCOORDS    = ((int)0x00000080),   /**<Vertex 2 Texture coordinates changed*/
    rpPTANKIFLAGVTX4TEXCOORDS    = ((int)0x00000100),   /**<Vertex 4 Texture coordinates changed*/
/*    free                       = ((int)0x00000200),    */
/*    free                       = ((int)0x00000400),    */
/*    free                       = ((int)0x00000800),    */
/*    free                       = ((int)0x00001000),    */
    rpPTANKIFLAGCNSCOLOR         = ((int)0x00002000),   /**<Constant color changed*/
    rpPTANKIFLAGCNSSIZE          = ((int)0x00004000),   /**<Constant size changed*/
    rpPTANKIFLAGCNSMATRIX        = ((int)0x00008000),   /**<Constant matrix changed*/
    rpPTANKIFLAGCNSNORMAL        = ((int)0x00010000),   /**<Constant normal changed*/
    rpPTANKIFLAGCNS2DROTATE      = ((int)0x00020000),   /**<Constant 2D rotation changed*/
    rpPTANKIFLAGCNSVTXCOLOR      = ((int)0x00040000),   /**<Constant vertex color changed*/
    rpPTANKIFLAGCNSVTX2TEXCOORDS = ((int)0x00080000),   /**<Constant vertex 2 Texture coordinates changed*/
    rpPTANKIFLAGCNSVTX4TEXCOORDS = ((int)0x00100000),   /**<Constant vertex 4 Texture coordinates changed*/
/*    free                       = ((int)0x00200000),    */
/*    free                       = ((int)0x00400000),    */
    rpPTANKIFLAGACTNUMCHG        = ((int)0x00800000),    /**<Number of active particle changed*/
    rpPTANKIFLAGCENTER           = ((int)0x01000000),    /**<Center position changed*/
/*    free                       = ((int)0x04000000),    */
/*    free                       = ((int)0x08000000),    */
/*    free                       = ((int)0x10000000),    */
    rpPTANKIFLAGALL              = ((int)0xFFFFFFFF),

    RPPTANKINSTANCEFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef enum RpPTankInstanceFlags RpPTankInstanceFlags;

#endif

/**
 * \ingroup rpptank
 * Passed to \ref RpPTankAtomicLock to specify the type of access needed.
 *
 * Accessing data using \ref rpPTANKLOCKWRITE will force the PTank object to reinstance
 * the rendered data. The instantiation of this data takes place at rendering
 * time and is done once per frame.
 */
enum RpPTankLockFlags
{
    rpPTANKLOCKWRITE     = ((int)0x40000000),    /**<Lock data for writing. */
    rpPTANKLOCKREAD      = ((int)0x80000000)    /**<Lock data for reading. */
};

typedef enum RpPTankLockFlags RpPTankLockFlags;

typedef struct RpPTankLockStruct RpPTankLockStruct;

/**
 * \ingroup rpptank
 * \struct RpPTankLockStruct
 * Returned by \ref RpPTankAtomicLock
 */
struct  RpPTankLockStruct{
    RwUInt8 *data;            /**<Pointer to the locked data. */
    RwInt32 stride;            /**<Stride of the data accessed. */
};

typedef struct RpPTankFormatDescriptor RpPTankFormatDescriptor;

/**
 * \ingroup rpptank
 * \struct RpPTankFormatDescriptor
 * Returned by \ref RpPTankAtomicGetDataFormat
 */
struct RpPTankFormatDescriptor
{
    RwInt32 numClusters;    /**<Number of clusters */
    RwInt32 stride;         /**<Size of a single structure when using
                             * structure organization, 0 otherwise */
    RwInt32 dataFlags;      /**<flags passed to \ref RpPTankAtomicCreate */
};

#if (!defined(DOXYGEN))

typedef struct RpPTankData RpPTankData;

struct RpPTankData
{
    void     *data;         /*  PI data array
                             * in the A form :
                             * Point to the ptrList table
                             * in the S form :
                             * point to the structure
                             *
                             */
    RpPTankLockStruct clusters[9];

    void *userData;         /* void pointer for platform use */

    RpPTankFormatDescriptor format;

    /* constant values */
    RwUInt32    srcBlend;
    RwUInt32    dstBlend;
    RwBool      vertexAlphaBlend;

    RwV2d           cCenter;
    RwV2d           cSize;
    RwReal          cRotate;
    RwRGBA          cColor;
    RwRGBA          cVtxColor[4];
    RwTexCoords     cUV[4];
    RwMatrix cMatrix;
};




/* data piece size */
extern const RwInt32 datasize[];

#define RPPTANKSIZEPOSITION         0
#define RPPTANKSIZEMATRIX           1
#define RPPTANKSIZENORMAL           2
#define RPPTANKSIZESIZE             3
#define RPPTANKSIZECOLOR            4
#define RPPTANKSIZEVTXCOLOR         5
#define RPPTANKSIZE2DROTATE         6
#define RPPTANKSIZEVTX2TEXCOORDS    7
#define RPPTANKSIZEVTX4TEXCOORDS    8


/**
 * \ingroup rpptank
 * \typedef rpptankAllocCallBack
 * ...
 */
typedef void *(* rpPTankAllocCallBack)(RpPTankData *ptankGlobal,
                                        RwInt32 maxPCount,
                                        RwUInt32 dataFlags,
                                        RwUInt32 platFlags);

/**
 * \ingroup rpptank
 * \typedef rpPTankCreateCallBack
 * ...
 */
typedef RwBool (* rpPTankCreateCallBack)(RpAtomic *atomic,
                                        RpPTankData *ptankGlobal,
                                        RwInt32 maxPCount,
                                        RwUInt32 dataFlags,
                                        RwUInt32 platFlags);

/**
 * \ingroup rpptank
 * \typedef rpPTankInstanceCallBack
 * ...
 */
typedef RwBool (* rpPTankInstanceCallBack)(RpAtomic *atomic,
                                            RpPTankData *ptankGlobal,
                                            RwInt32 actPCount,
                                            RwUInt32 instFlags);

/**
 * \ingroup rpptank
 * \typedef rpPTankRenderCallBack
 * ...
 */
typedef RwBool (* rpPTankRenderCallBack)(RpAtomic *atomic,
                                            RpPTankData *ptankGlobal,
                                            RwInt32 actPCount);

typedef struct rpPTankCallBacks rpPTankCallBacks;

struct rpPTankCallBacks
{
    rpPTankAllocCallBack        alloc;
    rpPTankCreateCallBack       create;
    rpPTankInstanceCallBack        instance;
    rpPTankRenderCallBack        render;
};

/* private typedefs */
typedef struct rpPTANKInstanceSetupData rpPTANKInstanceSetupData;

struct rpPTANKInstanceSetupData
{
    RwBool instancePositions;
    RwBool instanceUVs;
    RwBool instanceColors;
    RwBool instanceNormals;

    RpPTankLockStruct positionOut;
    RpPTankLockStruct UVOut;
    RpPTankLockStruct colorsOut;
    RpPTankLockStruct normalsOut;

    RwV3d right;
    RwV3d up;

};

typedef void (* rpPTankGENInstancePosCallback)(
    RpPTankLockStruct *dstCluster,
    RwV3d *right,
    RwV3d *up,
    RwInt32 pCount,
    RpPTankData *ptankGlobal);

typedef void (* rpPTankGENInstanceCallback)(
    RpPTankLockStruct *dstCluster,
    RwInt32 pCount,
    RpPTankData *ptankGlobal);

typedef void (* rpPTankGENInstanceSetupCallback)(
    rpPTANKInstanceSetupData *data,
    RpAtomic *atomic,
    RpPTankData *ptankGlobal,
    RwInt32 actPCount,
    RwUInt32 instFlags);

typedef void (* rpPTankGENInstanceEndingCallback)(
    rpPTANKInstanceSetupData *data,
    RpAtomic *atomic,
    RpPTankData *ptankGlobal,
    RwInt32 actPCount,
    RwUInt32 instFlags);

typedef struct RpPTankAtomicExtPrv RpPTankAtomicExtPrv;

struct RpPTankAtomicExtPrv
{
    RwInt32  maxPCount;        /* max number of particles */
    RwInt32  actPCount;       /* number of actives particles */

    RwBool   isAStructure;  /* is in a structure of array form */
    void    *rawdata;        /* unaligned pointer to the PI data */

    /* Rendering callback */
    RpAtomicCallBackRender defaultRenderCB;

    rpPTankCallBacks       ptankCallBacks;
    
    /* Instancing CallBacks */
    rpPTankGENInstanceSetupCallback     insSetupCB;
    rpPTankGENInstancePosCallback       insPosCB;
    rpPTankGENInstanceCallback          insUVCB;
    rpPTankGENInstanceCallback          insColorsCB;
    rpPTankGENInstanceCallback          insNormalsCB;
    rpPTankGENInstanceEndingCallback    insEndingCB;

    RwUInt32 lockFlags;
    RwUInt32 instFlags;
    RwUInt32 platFlags;

    RpPTankData publicData;
};

/*--- Plugin API Functions ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* private globals */
extern RwInt32 _rpPTankAtomicDataOffset; /* Offset in RpAtomic */

extern RwInt32 _rpPTankGlobalsOffset; /* Offset in RwEngine */

/* Macro tools */
#define RPATOMICPTANKPLUGINDATA(atomic)                \
    (*RWPLUGINOFFSET(RpPTankAtomicExtPrv *, (atomic), _rpPTankAtomicDataOffset))

#define GLOBALPTANKPLUGINDATA()                \
    (*RWPLUGINOFFSET(void *, RwEngineInstance, _rpPTankGlobalsOffset))

#endif



extern RwBool
RpPTankPluginAttach(void);


/*
 * PTank Management API ******************************************************
 */

extern RpAtomic *
RpPTankAtomicCreate(RwInt32 maxParticleNum,
                    RwUInt32 dataFlags,
                    RwUInt32 platFlags);

extern void
RpPTankAtomicDestroy(RpAtomic *ptank);

extern RwBool
RpAtomicIsPTank(RpAtomic *atomic);

extern const RpPTankFormatDescriptor *
RpPTankAtomicGetDataFormat(RpAtomic *atomic);

/*
 * Particles Management API **************************************************
 */

#define RpPTankAtomicGetActiveParticlesCountMacro(_atm)\
                     (RPATOMICPTANKPLUGINDATA(_atm)->actPCount)

#define RpPTankAtomicGetMaximumParticlesCountMacro(_atm)\
                     (RPATOMICPTANKPLUGINDATA(_atm)->maxPCount)

#define RpPTankAtomicSetActiveParticlesCountMacro(atm_,cnt_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGACTNUMCHG;\
    RPATOMICPTANKPLUGINDATA(atm_)->actPCount = cnt_;\
}\
MACRO_STOP

#define RpPTankAtomicSetTextureMacro(atm_, tex_)\
MACRO_START\
{\
RpMaterialSetTexture(RpGeometryGetMaterial(RpAtomicGetGeometry(atm_),0), tex_);\
}\
MACRO_STOP

#define RpPTankAtomicGetTextureMacro(atm_)\
    (RpMaterialGetTexture(RpGeometryGetMaterial(RpAtomicGetGeometry(atm_),0)))

#define RpPTankAtomicGetMaterialMacro(atm_)\
    (RpGeometryGetMaterial(RpAtomicGetGeometry(atm_),0))

#define RpPTankAtomicSetBlendModesMacro(atm_,src_,dst_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.srcBlend = src_;\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.dstBlend = dst_;\
}\
MACRO_STOP    

#define RpPTankAtomicGetBlendModesMacro(atm_,src_,dst_)\
MACRO_START\
{\
    *src_ =\
    (RwBlendFunction)(RPATOMICPTANKPLUGINDATA(atm_)->publicData.srcBlend);\
    *dst_ =\
    (RwBlendFunction)(RPATOMICPTANKPLUGINDATA(atm_)->publicData.dstBlend);\
}\
MACRO_STOP

#define RpPTankAtomicSetVertexAlphaMacro(atm_, vas_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.vertexAlphaBlend = vas_;\
}\
MACRO_STOP

#define RpPTankAtomicGetVertexAlphaMacro(atm_)\
    (RPATOMICPTANKPLUGINDATA(atm_)->publicData.vertexAlphaBlend)

#define RpPTankAtomicSetConstantCenterMacro(atm_, ctr_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.cCenter = *ctr_;\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCENTER;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantCenterMacro(atm_)\
        (&(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cCenter))


#define RpPTankAtomicSetConstantSizeMacro(atm_, size_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.cSize = *size_;\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSSIZE;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantSizeMacro(atm_)\
        (&RPATOMICPTANKPLUGINDATA(atm_)->publicData.cSize)

#define RpPTankAtomicSetConstantRotateMacro(atm_, rot_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.cRotate = rot_;\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNS2DROTATE;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantRotateMacro(atm_)\
    (RPATOMICPTANKPLUGINDATA(atm_)->publicData.cRotate)

#define RpPTankAtomicSetConstantMatrixMacro(atm_, mtx_)\
MACRO_START\
{\
    RwMatrixCopy(&(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cMatrix),mtx_);\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSMATRIX;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantMatrixMacro(atm_)\
        (&(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cMatrix))

#define RpPTankAtomicSetConstantColorMacro(atm_, col_)\
MACRO_START\
{\
    RPATOMICPTANKPLUGINDATA(atm_)->publicData.cColor = *col_;\
    if( RpGeometryGetMaterial(RpAtomicGetGeometry(atm_),0) )\
    {\
        RpMaterialSetColor(\
        RpGeometryGetMaterial(RpAtomicGetGeometry(atm_),0),\
        &RPATOMICPTANKPLUGINDATA(atm_)->publicData.cColor);\
    }\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSCOLOR;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantColorMacro(atm_)\
    (&(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cColor))

#define RpPTankAtomicSetConstantVtxColorMacro(atm_, col_)\
MACRO_START\
{\
    memcpy(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cVtxColor,\
            col_,\
            sizeof(RwRGBA)*4);\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSVTXCOLOR;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantVtxColorMacro(atm_)\
    (RPATOMICPTANKPLUGINDATA(atm_)->publicData.cVtxColor)

#define RpPTankAtomicSetConstantVtx2TexCoordsMacro(atm_, uv_)\
MACRO_START\
{\
    memcpy(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cUV,\
            uv_,\
            sizeof(RwTexCoords)*2);\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSVTX2TEXCOORDS;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantVtx2TexCoordsMacro(atm_)\
    (RPATOMICPTANKPLUGINDATA(atm_)->publicData.cUV)

#define RpPTankAtomicSetConstantVtx4TexCoordsMacro(atm_, uv_)\
MACRO_START\
{\
    memcpy(RPATOMICPTANKPLUGINDATA(atm_)->publicData.cUV,\
            uv_,\
            sizeof(RwTexCoords)*4);\
    RPATOMICPTANKPLUGINDATA(atm_)->instFlags |= rpPTANKIFLAGCNSVTX4TEXCOORDS;\
}\
MACRO_STOP

#define RpPTankAtomicGetConstantVtx4TexCoordsMacro(atm_)\
    (RPATOMICPTANKPLUGINDATA(atm_)->publicData.cUV)

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwInt32
RpPTankAtomicGetActiveParticlesCount(RpAtomic *atomic);

extern RwInt32
RpPTankAtomicGetMaximumParticlesCount(RpAtomic *atomic);

extern void
RpPTankAtomicSetActiveParticlesCount(RpAtomic *atomic, RwInt32 count);

extern void
RpPTankAtomicSetTexture(RpAtomic *atomic, RwTexture *texture);

extern RwTexture *
RpPTankAtomicGetTexture(RpAtomic *atomic);

extern RpAtomic *
RpPTankAtomicSetMaterial(RpAtomic *atomic, RpMaterial *material);

extern RpMaterial *
RpPTankAtomicGetMaterial(RpAtomic *atomic);

extern void
RpPTankAtomicSetBlendModes(RpAtomic *atomic,
                                 RwBlendFunction srcBlendMode,
                                 RwBlendFunction dstBlendMode );

extern void
RpPTankAtomicGetBlendModes(RpAtomic *atomic,
                                 RwBlendFunction *srcBlendMode,
                                 RwBlendFunction *dstBlendMode );

extern void
RpPTankAtomicSetVertexAlpha(RpAtomic *atomic, RwBool vtxAlphaState);

extern RwBool
RpPTankAtomicGetVertexAlpha(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantCenter(RpAtomic *atomic, RwV2d *center);

const RwV2d *
RpPTankAtomicGetConstantCenter(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantSize(RpAtomic *atomic, RwV2d *size);

extern const RwV2d *
RpPTankAtomicGetConstantSize(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantRotate(RpAtomic *atomic, RwReal rotate);

extern RwReal
RpPTankAtomicGetConstantRotate(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantMatrix(RpAtomic *atomic, RwMatrix *matrix);

extern const RwMatrix *
RpPTankAtomicGetConstantMatrix(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantColor(RpAtomic *atomic, RwRGBA *color);

extern const RwRGBA *
RpPTankAtomicGetConstantColor(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantVtxColor(RpAtomic *atomic, RwRGBA *color);

extern const RwRGBA *
RpPTankAtomicGetConstantVtxColor(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantVtx2TexCoords(RpAtomic *atomic, RwTexCoords *UVs);

extern const RwTexCoords *
RpPTankAtomicGetConstantVtx2TexCoords(RpAtomic *atomic);

extern void
RpPTankAtomicSetConstantVtx4TexCoords(RpAtomic *atomic, RwTexCoords *UVs);

extern const RwTexCoords *
RpPTankAtomicGetConstantVtx4TexCoords(RpAtomic *atomic);
#else

#define RpPTankAtomicGetActiveParticlesCount(atm_)\
        RpPTankAtomicGetActiveParticlesCountMacro(atm_)

#define RpPTankAtomicGetMaximumParticlesCount(atm_)\
        RpPTankAtomicGetMaximumParticlesCountMacro(atm_)

#define RpPTankAtomicSetActiveParticlesCount(atm_,cnt_)\
        RpPTankAtomicSetActiveParticlesCountMacro(atm_,cnt_)


#define RpPTankAtomicSetTexture(atm_,tex_)\
        RpPTankAtomicSetTextureMacro(atm_,tex_)

#define RpPTankAtomicGetTexture(atm_)\
        RpPTankAtomicGetTextureMacro(atm_)

extern RpAtomic *
RpPTankAtomicSetMaterial(RpAtomic *atomic, RpMaterial *material);

#define RpPTankAtomicGetMaterial(atm_)\
        RpPTankAtomicGetMaterialMacro(atm_)

#define RpPTankAtomicSetBlendModes(atm_,src_,dst_)\
        RpPTankAtomicSetBlendModesMacro(atm_,src_,dst_)

#define RpPTankAtomicGetBlendModes(atm_,src_,dst_)\
        RpPTankAtomicGetBlendModesMacro(atm_,src_,dst_)

#define RpPTankAtomicSetVertexAlpha(atm_, vas_)\
        RpPTankAtomicSetVertexAlphaMacro(atm_, vas_)

#define RpPTankAtomicGetVertexAlpha(atm_)\
        RpPTankAtomicGetVertexAlphaMacro(atm_)

#define RpPTankAtomicSetConstantCenter(atm_, ctr_)\
        RpPTankAtomicSetConstantCenterMacro(atm_, ctr_)

#define RpPTankAtomicGetConstantCenter(atm_)\
        RpPTankAtomicGetConstantCenterMacro(atm_)

#define RpPTankAtomicSetConstantSize(atm_, size_)\
        RpPTankAtomicSetConstantSizeMacro(atm_, size_)

#define RpPTankAtomicGetConstantSize(atm_)\
        RpPTankAtomicGetConstantSizeMacro(atm_)

#define RpPTankAtomicSetConstantRotate(atm_, rot_)\
        RpPTankAtomicSetConstantRotateMacro(atm_, rot_)

#define RpPTankAtomicGetConstantRotate(atm_)\
        RpPTankAtomicGetConstantRotateMacro(atm_)

#define RpPTankAtomicSetConstantMatrix(atm_, mtx_)\
        RpPTankAtomicSetConstantMatrixMacro(atm_, mtx_)

#define RpPTankAtomicGetConstantMatrix(atm_)\
        RpPTankAtomicGetConstantMatrixMacro(atm_)

#define RpPTankAtomicSetConstantColor(atm_, col_)\
        RpPTankAtomicSetConstantColorMacro(atm_, col_)

#define RpPTankAtomicGetConstantColor(atm_)\
        RpPTankAtomicGetConstantColorMacro(atm_)

#define RpPTankAtomicSetConstantVtxColor(atm_, _col)\
        RpPTankAtomicSetConstantVtxColorMacro(atm_, _col)

#define RpPTankAtomicGetConstantVtxColor(atm_)\
        RpPTankAtomicGetConstantVtxColorMacro(atm_)

#define RpPTankAtomicSetConstantVtx2TexCoords(atm_, uv_)\
        RpPTankAtomicSetConstantVtx2TexCoordsMacro(atm_, uv_)

#define RpPTankAtomicGetConstantVtx2TexCoords(atm_)\
        RpPTankAtomicGetConstantVtx2TexCoordsMacro(atm_)\

#define RpPTankAtomicSetConstantVtx4TexCoords(atm_, uv_)\
        RpPTankAtomicSetConstantVtx4TexCoordsMacro(atm_, uv_)

#define RpPTankAtomicGetConstantVtx4TexCoords(atm_)\
        RpPTankAtomicGetConstantVtx4TexCoordsMacro(atm_)

#endif

/*
 * Data access API ***********************************************************
 */

extern RwBool
RpPTankAtomicLock(RpAtomic *atomic, RpPTankLockStruct *dst,
            RwUInt32 dataFlags, RpPTankLockFlags lockFlag);

extern void *
RpPTankAtomicLockByIndex(RpAtomic *atomic, RwInt32 idx, RwUInt32 dataFlags, RpPTankLockFlags lockFlag);

extern RpAtomic *
RpPTankAtomicUnlock(RpAtomic *atomic);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*---- end: ./ptank.h----*/

/*---- start: c:/daily/rwsdk/plugin/ptank/d3d8/ptankplatform.h----*/

enum RpPTankD3D8Flags
{
    rpPTANKD3D8FLAGSUSEPOINTSPRITES = 0x00000001,

    rpPTANKD3D8FLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*---- end: c:/daily/rwsdk/plugin/ptank/d3d8/ptankplatform.h----*/

#endif /* RPPTANK_H */


