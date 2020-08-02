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
 * Filename: <C:/daily/rwsdk/include/d3d8/rpworld.h>
 * Automatically Generated on: Wed Jul 10 10:45:01 2002
 *
 ************************************************************************/

#ifndef RPWORLD_H
#define RPWORLD_H

/*--- Check For Previous Required Includes ---*/
#ifndef RWCORE_H
#error "Include RWCORE.H before including this file"
#endif /* RWCORE_H */

/*--- System Header Files ---*/
#include <stdarg.h>
#include <stdlib.h>

/*--- Error enumerations ---*/
#include "rpworld.rpe"


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/native.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/wrldpipe.h ---*/

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/nodeD3D8WorldSectorAllInOne.h ---*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetD3D8WorldSectorAllInOne(void);
#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/nodeD3D8AtomicAllInOne.h ---*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetD3D8AtomicAllInOne(void);
#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/D3D8VertexBufferManager.h ---*/
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */
#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeWorldSectorInstance.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetWorldSectorInstance(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeWorldSectorEnumerateLights.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetWorldSectorEnumerateLights(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodePreLight.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetPreLight(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodePostLight.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetPostLight(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeMaterialScatter.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetMaterialScatter(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeLight.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetLight(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeFastPathSplitter.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetFastPathSplitter(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeAtomicInstance.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetAtomicInstance(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/nodeAtomicEnumerateLights.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetAtomicEnumerateLights(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: c:/daily/rwsdk/world/bamateri.h ---*/

/*
 * Handling surface materials
 * Materials describe how things are to appear when rendered
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */

/****************************************************************************
 Global Types
 */


typedef struct RpMaterialChunkInfo RpMaterialChunkInfo;
typedef struct RpMaterialChunkInfo _rpMaterial;

struct RpMaterialChunkInfo
{
    RwInt32             flags;  /**<  Material flags - unused currently - 
                                   for future expansion */
    RwRGBA              color;  /**<  Colour of material. */
    RwInt32             unused;  /**<  Not used */
    RwBool              textured;  /**<  Are we textured? */
    RwSurfaceProperties surfaceProps;   /**<  Surface properties */
};

#if (!defined(RwMaterialAssign))
#define RwMaterialAssign(_target, _source)             \
    ( *(_target) = *(_source) )
#endif /* (!defined(RwMaterialAssign)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpMaterial 
 * Material object. This should be 
 * considered an opaque type. Use the RpMaterial API functions to access.
 */
typedef struct RpMaterial RpMaterial;

#if (!defined(DOXYGEN))
struct RpMaterial
{
        RwTexture           *texture; /**< texture */
        RwRGBA              color; /**< color */              
        RxPipeline          *pipeline; /**< pipeline */     
        RwSurfaceProperties surfaceProps; /**< surfaceProps */
        RwInt16             refCount;          /* C.f. rwsdk/world/bageomet.h:RpGeometry */
        RwInt16             pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpMaterialCallBack
 \ref RpMaterialCallBack 
 * represents the function called from \ref RpGeometryForAllMaterials and 
 * \ref RpWorldForAllMaterials for all materials referenced by polygons in a 
 * given geometry. This function should return a pointer to the current 
 * material to indicate success. The callback may return NULL to terminate 
 * further callbacks on the materials.
 * 
 * \param  material   Pointer to the current material
 * \param  data  Pointer to developer-defined data structure.
 * 
 * \return Pointer to the current material.
 */
typedef RpMaterial *(*RpMaterialCallBack)(RpMaterial *material, void *data);

/****************************************************************************
 <macro/inline functionality
 */

#define RpMaterialAddRefMacro(_material)                            \
    (((_material)->refCount++), (_material))

#define RpMaterialAddRefVoidMacro(_material)                        \
MACRO_START                                                         \
{                                                                   \
    (_material)->refCount++;                                        \
}                                                                   \
MACRO_STOP


#define RpMaterialSetColorMacro(_material, _color)                  \
    (RwRGBAAssign(&((_material)->color), (_color)), (_material))

#define RpMaterialGetColorMacro(_material)                          \
    (&((_material)->color))

#define RpMaterialSetSurfacePropertiesMacro(_material, _surfProps)  \
    (RwSurfacePropertiesAssign(&((_material)->surfaceProps),        \
                               (_surfProps)), (_material))

#define RpMaterialSetSurfacePropertiesVoidMacro(_material, _surfProps)  \
MACRO_START                                                             \
{                                                                       \
    RwSurfacePropertiesAssign(&((_material)->surfaceProps),             \
                              (_surfProps));                            \
}                                                                       \
MACRO_STOP

#define RpMaterialGetSurfacePropertiesMacro(_material)              \
    (&((_material)->surfaceProps))

#define RpMaterialGetTextureMacro(_material)                        \
    ((_material)->texture)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpMaterialAddRef(_material)                                 \
    RpMaterialAddRefMacro(_material)

#define RpMaterialSetColor(_material, _color)                       \
    RpMaterialSetColorMacro(_material, _color)

#define RpMaterialGetColor(_material)                               \
    RpMaterialGetColorMacro(_material)

#define RpMaterialSetSurfaceProperties(_material, _surfProps)       \
    RpMaterialSetSurfacePropertiesMacro(_material, _surfProps)

#define RpMaterialGetSurfaceProperties(_material)                   \
    RpMaterialGetSurfacePropertiesMacro(_material)

#define RpMaterialGetTexture(_material)                             \
    RpMaterialGetTextureMacro(_material)

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */


/* Creating, destroying and referencing materials */
extern RpMaterial *RpMaterialCreate(void);
extern RwBool RpMaterialDestroy(RpMaterial *material);
extern RpMaterial *RpMaterialClone(RpMaterial *material);

/* Textures */
extern RpMaterial *RpMaterialSetTexture(RpMaterial *material, RwTexture *texture);


#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RpMaterial *RpMaterialAddRef(RpMaterial *material);

/* Textures */
extern RwTexture *RpMaterialGetTexture(const RpMaterial *material);

/* Setting and getting colors */
extern RpMaterial *RpMaterialSetColor(RpMaterial *material, const RwRGBA *color);
extern const RwRGBA *RpMaterialGetColor(const RpMaterial *material);

/* Setting and getting surface properties */
extern RpMaterial *
RpMaterialSetSurfaceProperties(RpMaterial *material,
                               const RwSurfaceProperties *surfaceProperties);

extern const RwSurfaceProperties *
RpMaterialGetSurfaceProperties(const RpMaterial *material);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/* Attaching toolkits */
extern RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                        RwPluginObjectConstructor constructCB,
                                        RwPluginObjectDestructor destructCB,
                                        RwPluginObjectCopy copyCB);
extern RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID,
                                              RwPluginDataChunkReadCallBack readCB,
                                              RwPluginDataChunkWriteCallBack writeCB,
                                              RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 RpMaterialSetStreamAlwaysCallBack(
                        RwUInt32 pluginID,
                        RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 RpMaterialGetPluginOffset(RwUInt32 pluginID);
extern RwBool RpMaterialValidatePlugins(const RpMaterial *material);

/* Binary format */
extern RwUInt32 RpMaterialStreamGetSize(const RpMaterial *material);
extern RpMaterial *RpMaterialStreamRead(RwStream *stream);
extern const RpMaterial *RpMaterialStreamWrite(const RpMaterial *material, RwStream *stream);
extern RpMaterialChunkInfo *
_rpMaterialChunkInfoRead(RwStream *stream, 
                         RpMaterialChunkInfo *materialChunkInfo, 
                         RwInt32 *bytesRead);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpMaterialChunkInfoRead(stream, materialChunkInfo, bytesRead) \
       _rpMaterialChunkInfoRead(stream, materialChunkInfo, bytesRead)


/*--- Automatically derived from: c:/daily/rwsdk/world/bamatlst.h ---*/
/****************************************************************************
 Global Types
 */

typedef struct RpMaterialList RpMaterialList;
struct RpMaterialList
{
    RpMaterial     **materials;
    RwInt32        numMaterials;
    RwInt32        space;
};

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

#define rpMaterialListGetNumMaterials(mlist) ((mlist)->numMaterials)

/* Setting up and destroying material lists */
extern RpMaterialList *_rpMaterialListInitialize(RpMaterialList *matList);
extern RpMaterialList *_rpMaterialListDeinitialize(RpMaterialList *matList);

/* Accessing material lists */
extern RpMaterial     ** _rpMaterialListAlloc(RwUInt32 count);
extern RpMaterial *_rpMaterialListGetMaterial(const RpMaterialList *matList,
                                             RwInt32 matIndex);
extern RpMaterialList * _rpMaterialListSetSize(RpMaterialList * matList, 
                                               RwInt32 size);
extern RpMaterialList *_rpMaterialListCopy(RpMaterialList *matListOut,
                                          const RpMaterialList *matListIn);
extern RwInt32 _rpMaterialListAppendMaterial(RpMaterialList *matList,
                                            RpMaterial *material);
extern RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList *matList,
                                               const RpMaterial *material);

/* Binary format */
extern RwUInt32 _rpMaterialListStreamGetSize(const RpMaterialList *matList);
extern RpMaterialList *_rpMaterialListStreamRead(RwStream *stream,
                                                RpMaterialList *matList);
extern const RpMaterialList *_rpMaterialListStreamWrite(const RpMaterialList *matList,
                                                       RwStream *stream);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define rpMaterialListInitialize(_matList) \
    _rpMaterialListInitialize(_matList)

#define rpMaterialListDeinitialize(_matList) \
    _rpMaterialListDeinitialize(_matList)

#define rpMaterialListGetMaterial(_matList, _matIndex) \
    _rpMaterialListGetMaterial(_matList, _matIndex)

#define rpMaterialListCopy(_matListOut, _matListIn) \
    _rpMaterialListCopy(_matListOut, _matListIn)

#define rpMaterialListAppendMaterial(_matList, _material) \
    _rpMaterialListAppendMaterial(_matList, _material)

#define rpMaterialListStreamRead(_stream, _matList) \
    _rpMaterialListStreamRead(_stream, _matList)

#define rpMaterialListStreamWrite(_matList, _stream) \
    _rpMaterialListStreamWrite(_matList, _stream)


/*--- Automatically derived from: c:/daily/rwsdk/world/bamesh.h ---*/

/*
 *
 * Purpose: Provide construction and enumeration facilities for meshes.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */

#define RPMESHGLOBAL(var)                                   \
    (RWPLUGINOFFSET(rpMeshGlobals,                          \
                    RwEngineInstance,                       \
                    meshModule.globalsOffset)->var)

#define rwPRIMTYPEOR                            \
    (rwPRIMTYPELINELIST |                       \
      rwPRIMTYPEPOLYLINE |                      \
      rwPRIMTYPETRILIST |                       \
      rwPRIMTYPETRISTRIP |                      \
      rwPRIMTYPETRIFAN   |                      \
      rwPRIMTYPEPOINTLIST)

#define rpMESHHEADERPRIMTYPEOR                  \
    (0 /* rpMESHHEADERTRILIST*/ |               \
      rpMESHHEADERTRISTRIP |                    \
      rpMESHHEADERTRIFAN  |                     \
      rpMESHHEADERLINELIST |                    \
      rpMESHHEADERPOLYLINE |                    \
      rpMESHHEADERPOINTLIST)

/****************************************************************************
 Global variables
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwModuleInfo meshModule;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/****************************************************************************
 Global types
 */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpMeshHeader
 * typedef for header structure listing all meshes
 * constituting a single RpGeometry or RpWorldSector
 */
typedef struct RpMeshHeader RpMeshHeader;

/**
 * \ingroup rpworlddatatypes
 * \ref RpMeshHeaderFlags
 * represents the different types of mesh.
 * \see RpMeshHeader
 */
enum RpMeshHeaderFlags
{
    /* NOTE: trilists are denoted by absence of any other
     *       primtype flags, so be careful that you test:
     *        (triListFlag == flags&triListFlag)
     *       or:
     *        (0 == flags&rpMESHHEADERPRIMMASK)
     *       and not:
     *        (flags&triListFlag)
     */
    rpMESHHEADERTRISTRIP  = 0x0001, /**< Render as tristrips */
    rpMESHHEADERTRIFAN    = 0x0002, /**< On PS2 these will be converted to trilists */
    rpMESHHEADERLINELIST  = 0x0004, /**< Render as linelists */
    rpMESHHEADERPOLYLINE  = 0x0008, /**< On PS2 these will be converted to linelists */
    rpMESHHEADERPOINTLIST = 0x0010, /**< Pointlists are supported only if rendered by
                                     *   custom pipelines; there is no default RenderWare 
                                     *   way to render pointlists. */

    rpMESHHEADERPRIMMASK  = 0x00FF, /**< All bits reserved for specifying primitive type */
    rpMESHHEADERUNINDEXED = 0x0100, /**< Topology is defined implicitly by vertex
                                     *   order, ergo the mesh contains no indices */
    rpMESHHEADERFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*
 * Typedef for RpMeshHeaderFlags enumeration
 * representing the different types of mesh
 */
typedef enum RpMeshHeaderFlags RpMeshHeaderFlags;

typedef struct rpMeshGlobals rpMeshGlobals;
struct rpMeshGlobals
{
    RwInt16             nextSerialNum;
    RwFreeList         *triStripListEntryFreeList;
    RwUInt8             meshFlagsToPrimType[rpMESHHEADERPRIMTYPEOR];
    RwUInt8             primTypeToMeshFlags[rwPRIMTYPEOR];
};

typedef struct RpBuildMeshTriangle RpBuildMeshTriangle;

/**
 * \ingroup rpworlddatatypes
 * \struct RpBuildMeshTriangle
 * This type represents an array of indices into
 * the object vertex array. Used during the construction
 * of tristrips.
 *
 * See API functions
 * \see RpBuildMeshGeneratePreprocessTriStrip
 * \see RpBuildMeshGenerateExhaustiveTriStrip
 * \see RpBuildMeshGenerateTrivialTriStrip
 * \see RpBuildMeshGenerateDefaultTriStrip
 * and
 * \see RpMeshSetTriStripMethod
 * \see RpMeshGetTriStripMethod
 */
struct RpBuildMeshTriangle
{
    RwUInt16            vertIndex[3]; /**< indices into object vertex
                                       *   array. */
    RpMaterial         *material;     /**< pointer to material used to
                                       *   render the mesh. */
};

typedef struct RpBuildMesh RpBuildMesh;

/**
 * \ingroup rpworlddatatypes
 * \struct RpBuildMesh
 * This type represents a mesh ready for tri stripping.
 *
 * See API functions
 * \see RpBuildMeshGeneratePreprocessTriStrip
 * \see RpBuildMeshGenerateExhaustiveTriStrip
 * \see RpBuildMeshGenerateTrivialTriStrip
 * \see RpBuildMeshGenerateDefaultTriStrip
 * and
 * \see RpMeshSetTriStripMethod
 * \see RpMeshGetTriStripMethod
 */
struct RpBuildMesh
{
    RwUInt32            triangleBufferSize; /**< number of triangles
                                             *   space has been allocated
                                             *   for. */
    RwUInt32            numTriangles;       /**< number of triangles to be
                                             *   tristripped. */
    RpBuildMeshTriangle *meshTriangles;     /**< pointer to build mesh
                                             *   triangles. */
};

typedef struct RpMesh RpMesh;

/**
 * \ingroup rpworlddatatypes
 * \struct RpMesh
 * This type represents a single polygon mesh.
 * A mesh is defined as a collection of triangles derived from an RpGeometry
 * or RpWorldSector which have a common material.
 *
 * See API functions \see RpGeometryForAllMeshes and
 * \see RpWorldSectorForAllMeshes and
 * the corresponding function callback types:
 */
struct RpMesh
{
    RxVertexIndex      *indices;    /**< vertex indices defining the mesh */
    RwUInt32            numIndices; /**< number of vertices in mesh */
    RpMaterial         *material;   /**< pointer to material used to
                                     *   render the mesh. */
};

/**
 * \ingroup rpworlddatatypes
 * \struct RpMeshHeader
 * Header for all meshes that constitute a single RpGeometry or RpWorldSector
 */
struct RpMeshHeader
{
    RwUInt32            flags;    /**< \see RpMeshHeaderFlags */
    RwUInt16            numMeshes; /**< Number of meshes in object */
    RwUInt16            serialNum; /**< Determine if mesh has changed
                                    * since last instance */
    RwUInt32            totalIndicesInMesh; /**< Total triangle index
                                             * count in all meshes
                                             */
    RwUInt32            firstMeshOffset; /**< Offset in bytes from end this
                                          * structure RpMeshHeader
                                          * to the first mesh
                                          */
};

/**
 * \ingroup rpworlddatatypes
 * \typedef RpMeshCallBack
 *  \ref RpMeshCallBack is the callback
 * function supplied to \ref RpGeometryForAllMeshes and
 * \ref RpWorldSectorForAllMeshes for all meshes in a given geometry.
 *
 * This function should return a pointer to the current mesh to indicate
 * success. The callback may return NULL to terminate further callbacks
 * on the meshes.
 *
 * \param  mesh   Pointer to the current mesh, supplied by
 * iterator.
 * \param  meshHeader   Pointer to the meshes header
 * \param  data  Pointer to developer-defined data structure.
 *
 * \return
 * Returns a pointer to the current mesh if successful or NULL if an error
 * occurred.
 */
typedef RpMesh     *(*RpMeshCallBack) (RpMesh * mesh,
                                       RpMeshHeader * meshHeader,
                                       void *pData);

/****************************************************************************
 Function prototypes
 */

#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpMeshHeaderGetPrimType(_mshHdr)                                        \
    ( (RwPrimitiveType)RPMESHGLOBAL(meshFlagsToPrimType)[(_mshHdr)->flags &     \
                                                         rpMESHHEADERPRIMMASK] )

#define RpMeshHeaderSetPrimType(_mshHdr, _prmTyp)                   \
    ( (_mshHdr)->flags =                                            \
          ((_mshHdr)->flags & ~rpMESHHEADERPRIMMASK) |              \
          (rpMESHHEADERPRIMMASK &                                   \
           RPMESHGLOBAL(primTypeToMeshFlags)[(_prmTyp) &            \
                                           rpMESHHEADERPRIMMASK]),  \
      (_mshHdr) )

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Opening and closing module */
extern void        *_rpMeshOpen(void *instance, RwInt32 offset,
                                RwInt32 size);
extern void        *_rpMeshClose(void *instance, RwInt32 offset,
                                 RwInt32 size);

extern RwInt16      _rpMeshGetNextSerialNumber(void);

/* Create a build mesh with nothing in */
extern RpBuildMesh *_rpBuildMeshCreate(RwUInt32 bufferSize);

/* Destroy a build mesh */
extern RwBool       _rpBuildMeshDestroy(RpBuildMesh * mesh);

/* Destroy a build mesh */
extern RwBool       _rpMeshDestroy(RpMeshHeader * mesh);

/* Add a triangle to a mesh */
extern RpBuildMesh *_rpBuildMeshAddTriangle(RpBuildMesh * mesh,
                                            RpMaterial * material,
                                            RwInt32 vert1,
                                            RwInt32 vert2,
                                            RwInt32 vert3);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

/* Get primtype from a mesh header */
extern RwPrimitiveType RpMeshHeaderGetPrimType(RpMeshHeader *
                                               meshHeader);

/* Set primtype for a mesh header */
extern RpMeshHeader *RpMeshHeaderSetPrimType(RpMeshHeader *
                                             meshHeader,
                                             RwPrimitiveType
                                             primType);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/* Enumerate meshes within a mesh header */
extern RpMeshHeader *_rpMeshHeaderForAllMeshes(RpMeshHeader *
                                               meshHeader,
                                               RpMeshCallBack
                                               fpCallBack,
                                               void *pData);

/* Mesh serialisation functions */
extern RwStream    *_rpMeshWrite(const RpMeshHeader * meshHeader,
                                 const void *object,
                                 RwStream * stream,
                                 const RpMaterialList * matList);
extern RpMeshHeader *_rpMeshRead(RwStream * stream,
                                 const void *object,
                                 const RpMaterialList * matList);
extern RwInt32      _rpMeshSize(const RpMeshHeader *meshHeader,
                                const void *object);
/* Mesh header create/destroy functions */
extern void          _rpMeshHeaderDestroy(RpMeshHeader * meshHeader);
extern RpMeshHeader * _rpMeshHeaderCreate(RwUInt32 size);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: c:/daily/rwsdk/world/basector.h ---*/

/*
 * Handling atomic sectors
 * Atomic sectors are use to divide up the world into manageable portions
 *
 * Copyright (c) 1998 Criterion Software Ltd.
*/

/****************************************************************************
 Defines
 */

/* Type ID */
#define rpWorldSector 0xff     /* Not a true 'type'! */

#define rpMINDISTANCEBETWEENVERTICES (RwReal)(0.0001)

#define RPV3DFROMVERTEXNORMAL(v, n) \
    (v).x = (((RwReal)((n).x)) * ( (RwReal)(1.0/128))); \
    (v).y = (((RwReal)((n).y)) * ( (RwReal)(1.0/128))); \
    (v).z = (((RwReal)((n).z)) * ( (RwReal)(1.0/128)))

#define RPVERTEXNORMALFROMRWV3D(n, v)           \
    {                                           \
        RwFixed naTmp[3];                       \
                                                \
        naTmp[0] = RwRealToFixed((v).x);        \
        naTmp[1] = RwRealToFixed((v).y);        \
        naTmp[2] = RwRealToFixed((v).z);        \
                                                \
        if (naTmp[0] >= RwFixedCast(1))         \
        {                                       \
            naTmp[0] = RwFixedCast(1)-1;        \
        }                                       \
        if (naTmp[0] <= RwFixedCast(-1))        \
        {                                       \
            naTmp[0] = RwFixedCast(-1)+1;       \
        }                                       \
        if (naTmp[1] >= RwFixedCast(1))         \
        {                                       \
            naTmp[1] = RwFixedCast(1)-1;        \
        }                                       \
        if (naTmp[1] <= RwFixedCast(-1))        \
        {                                       \
            naTmp[1] = RwFixedCast(-1)+1;       \
        }                                       \
        if (naTmp[2] >= RwFixedCast(1))         \
        {                                       \
            naTmp[2] = RwFixedCast(1)-1;        \
        }                                       \
        if (naTmp[2] <= RwFixedCast(-1))        \
        {                                       \
            naTmp[2] = RwFixedCast(-1)+1;       \
        }                                       \
                                                \
        (n).x = (RwInt8)(naTmp[0]>>9);          \
        (n).y = (RwInt8)(naTmp[1]>>9);          \
        (n).z = (RwInt8)(naTmp[2]>>9);          \
    }

/* RpCollSector access macros - for pre v304 data */
#define RWCOLLSECTORGETTYPE(sect) \
    ((sect).cType&0x80)

#define RWCOLLSECTORGETPLANE(sect) \
    ((((sect).cType)>>3)&0xc)

#define RWCOLLSECTORGETON(sect) \
    (((sect).cType)&0x1f)

#define RWCOLLSECTORGETVERTEX(sect) \
    (sect).vertex

#define RWCOLLSECTORGETSTART(sect) \
    (sect).start

#define RWCOLLSECTORGETNOPOLYS(sect) \
    (sect).cType

#define RWCOLLSECTORSETPOLYGONS(sect,no,st) \
    (sect).cType = (RwUInt8)(no); \
    (sect).start = (RwUInt8)(st)

#define rwMAXCOLLISIONCUTS 7

/****************************************************************************
 Global types
 */

typedef struct RpVertexNormal RpVertexNormal;

struct RpVertexNormal
{
    RwInt8          x;
    RwInt8          y;
    RwInt8          z;
    RwUInt8         pad; /* pad character to force alignment */
};

typedef struct RpPolygon RpPolygon;

struct RpPolygon
{
    RwUInt16        matIndex;
    RwUInt16        vertIndex[3];
};

/* RpCollSector - for pre v304 data */
#define RWCOLLSECTORSETPLANE(sect,plane,vert,no,st) \
    (sect).cType = (RwUInt8)(0x80|((plane)<<3)|(no)); \
    (sect).vertex = (RwUInt8)(vert); \
    (sect).start = (RwUInt8)(st)

typedef struct RpCollSector RpCollSector;

struct RpCollSector
{
    RwUInt8 cType;    /* Bit 7   - 1 plane */
                      /*           0 polygons */
                      /* Bit 6-5 - plane */
                      /* Bit 4-0 - amount ON plane */
    RwUInt8 vertex;   /* Vertex index used for the split */
    RwUInt8 start;    /* Starting polygon */
};

/**
 * \ingroup rpworlddatatypes
 * \typedef RpWorldSector
 * World Sector object. This should be
 * considered an opaque type. Use the RpWorldSector API functions to access.
 */
typedef struct RpWorldSector RpWorldSector;

#if (!defined(DOXYGEN))
struct RpWorldSector
{
    RwInt32                 type;

    RpPolygon               *polygons;              /* Polygons themselves */

    RwV3d                   *vertices;              /* Vertex positions */
    RpVertexNormal          *normals;               /* Vertex normals */

    RwTexCoords             *texCoords[rwMAXTEXTURECOORDS]; /* Texture coordinates */

    RwRGBA                  *preLitLum;             /* Pre lit luminances */

    /* Pointer to memory allocated for vertex and poly pointers */
    RwResEntry              *repEntry;

    /* Atomics in this sectors */
    /* The pointers are frigged so they look like they are pointing to
       Atomics when they are pointing to here */
    RwLinkList              collAtomicsInWorldSector;       /* Coll priority */
    RwLinkList              noCollAtomicsInWorldSector;     /* No Coll priority */

    /* Lights in an atomic sector */
    RwLinkList              lightsInWorldSector;

    /* Outer bounding box of sector based on BSP planes */
    RwBBox                  boundingBox;

    /* Bounding box tightly enclosing geometry */
    RwBBox                  tightBoundingBox;

    /* The root of the bsp collision tree for pre v304 data */
    RpCollSector            *colSectorRoot;

    /* The mesh which groups same material polygons together */
    RpMeshHeader            *mesh;

    /* The WorldSector object pipeline for this WorldSector */
    RxPipeline    *pipeline;

    /* Material list window base
     * (triangles in a given sector can "see"
     * the 256 materials from
     * MatList[matListWindowBase] -> MatList[matListWindowBase + 255])
     */
    RwUInt16                matListWindowBase;

    RwUInt16                numVertices;            /* Num vertices */
    RwUInt16                numPolygons;            /* Num polygons */
    RwUInt16                pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpWorldSectorCallBack
 \ref RpWorldSectorCallBack
 * represents the function called from \ref RpWorldForAllWorldSectors,
 * \ref RpAtomicForAllWorldSectors and \ref RpLightForAllWorldSectors for all
 * world sectors in a given world or world sectors a given atomic or light lies
 * in. This function should return a pointer to the current world sector to
 * indicate success. The callback may return NULL to terminate further
 * callbacks on the atomic or light.
 *
 * \return Pointer to the current world sector.
 *
 * \param  sector   Pointer to the current world sector
 * \param  data  Pointer to developer-defined data structure.
 */
typedef RpWorldSector *(*RpWorldSectorCallBack)(RpWorldSector *worldSector, void *data);

typedef struct RpSector RpSector;

struct RpSector
{
    RwInt32                 type;
};

/* NOTE: The left and right pointers can point to an RpPlaneSector or
 *       an RpWorldSector
 * This is determined what the type is via the type value
 */

typedef struct RpPlaneSector RpPlaneSector;

struct RpPlaneSector
{
    RwInt32                 type;

    RwReal                  value;
    RpSector                *leftSubTree;   /* Sector 'left' (less) of the plane */
    RpSector                *rightSubTree;  /* Sector 'right' (more) of the plane */
    RwReal                  leftValue;
    RwReal                  rightValue;
};


#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwPluginRegistry sectorTKList;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpWorldSectorGetBBoxMacro(_sctr)      (&((_sctr)->boundingBox))
#define RpWorldSectorGetTightBBoxMacro(_sctr) (&((_sctr)->tightBoundingBox))

#if ((!defined(RWDEBUG)) && (!defined(RWSUPPRESSINLINE)))

#define RpWorldSectorGetBBox      RpWorldSectorGetBBoxMacro
#define RpWorldSectorGetTightBBox RpWorldSectorGetTightBBoxMacro

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */


/* Get info from atomic sectors */
extern RwInt32 RpWorldSectorGetNumPolygons(const RpWorldSector *Sector);
extern RwInt32 RpWorldSectorGetNumVertices(const RpWorldSector *Sector);

/* Instancing and deinstancing sectors */
extern RpWorldSector * RpWorldSectorRender(RpWorldSector *worldSector);

extern const RpWorldSector *RpWorldSectorForAllMeshes(const RpWorldSector *sector,
                                                      RpMeshCallBack fpCallBack,
                                                      void *pData);


#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

extern const RwBBox *RpWorldSectorGetBBox(const RpWorldSector *sector);
extern const RwBBox *RpWorldSectorGetTightBBox(const RpWorldSector *sector);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/* Plugins */
extern RwInt32 RpWorldSectorRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                           RwPluginObjectConstructor constructCB,
                                           RwPluginObjectDestructor destructCB,
                                           RwPluginObjectCopy copyCB);
extern RwInt32 RpWorldSectorRegisterPluginStream(RwUInt32 pluginID,
                                                 RwPluginDataChunkReadCallBack readCB,
                                                 RwPluginDataChunkWriteCallBack writeCB,
                                                 RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 RpWorldSectorSetStreamAlwaysCallBack(
                    RwUInt32 pluginID,
                    RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 RpWorldSectorSetStreamRightsCallBack(RwUInt32 pluginID,
                                      RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32 RpWorldSectorGetPluginOffset(RwUInt32 pluginID);
extern RwBool RpWorldSectorValidatePlugins(const RpWorldSector *sector);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/*--- Automatically derived from: c:/daily/rwsdk/world/bameshop.h ---*/

/****************************************************************************
 Defines
 */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpTriStripMeshCallBack
 * \ref RpTriStripMeshCallBack is the callback to generate triangle strips
 * when the triangle stripped geometries or world sectors are unlocked.
 *
 * \param buildMesh pointer to the mesh which the triangle strip will be
 * generated from.
 * \param data  pointer to user-supplied data to pass to the callback
 * function.
 *
 * \return a pointer to the constructed mesh header.
 *
 */
typedef RpMeshHeader *
(*RpTriStripMeshCallBack) (RpBuildMesh *buildMesh, void *data);


/****************************************************************************
 Global types
 */


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


/* Callback mesh generating functions */
extern RpMeshHeader *
RpBuildMeshGenerateTrivialTriStrip(RpBuildMesh *buildMesh, void *data);

extern RpMeshHeader *
RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh *buildmesh, void *data);

extern RpMeshHeader *
RpBuildMeshGeneratePreprocessTriStrip(RpBuildMesh *buildmesh, void *data);

extern RpMeshHeader *
RpBuildMeshGenerateExhaustiveTriStrip(RpBuildMesh *buildmesh, void *data);

extern RpMeshHeader *
RpBuildMeshGenerateDefaultIgnoreWindingTriStrip(RpBuildMesh *buildmesh, 
                                                void *data);

extern RpMeshHeader *
RpBuildMeshGeneratePreprocessIgnoreWindingTriStrip(RpBuildMesh *buildmesh, 
                                                   void *data);

extern RpMeshHeader *
RpBuildMeshGenerateExhaustiveIgnoreWindingTriStrip(RpBuildMesh *buildmesh, 
                                                   void *data);

/* Functions to set and get the global mesh tristrip algorithm */
extern RwBool
RpMeshSetTriStripMethod(RpTriStripMeshCallBack callback, void *data);

extern RwBool
RpMeshGetTriStripMethod(RpTriStripMeshCallBack *callback, void **data);


extern RpMeshHeader *
_rpTriListMeshGenerate(RpBuildMesh *buildMesh, void *data);

/* 
 * Optimise the mesh ordering 
 * (sort on material and place transparent materials last)
 */
extern RpMeshHeader *
_rpMeshOptimise(RpBuildMesh *buildmesh, RwUInt32 flags);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#define _rpTriStripMeshTrivialGenerate(_buildMesh, _data)      \
    RpBuildMeshGenerateTrivialTriStrip(_buildMesh, _data)

#define _rpTriStripMeshDefaultGenerate(_buildmesh, _data)      \
    RpBuildMeshGenerateDefaultTriStrip(_buildmesh, _data)

#define _rpTriStripMeshPreprocessGenerate(_buildmesh, _data)   \
    RpBuildMeshGeneratePreprocessTriStrip(_buildmesh, _data)

#define _rpTriStripMeshExhaustiveGenerate(_buildmesh, _data)   \
    RpBuildMeshGenerateExhaustiveTriStrip(_buildmesh, _data)

#define _rpMeshSetTristripMethod(_callback, _data)             \
    RpMeshSetTriStripMethod(_callback, _data)

#define _rpMeshGetTristripMethod(_callback, _data)             \
    RpMeshGetTriStripMethod(_callback, _data)



/*--- Automatically derived from: c:/daily/rwsdk/world/balight.h ---*/

/*
 * Lighting 3D objects.
 * Lights are used to illuminate atomics and worlds
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */


/****************************************************************************
 Defines
 */

/* Binary Light */
typedef struct RpLightChunkInfo RpLightChunkInfo;
typedef struct RpLightChunkInfo _rpLight;

struct RpLightChunkInfo
{
        RwReal              radius; /**< radius */
        RwReal              red; /**< red */
        RwReal              green; /**< green */
        RwReal              blue; /**< blue */
        RwReal              minusCosAngle; /**< minusCosAngle */
        RwUInt32            typeAndFlags; /**< typeAndFlags */
};

/* Type ID */
#define rpLIGHT 3

/* Beyond this the lights must be positioned */
#define rpLIGHTPOSITIONINGSTART 0x80

/**
 * \ingroup rpworlddatatypes
 * \ref RpLightType are
 * light sub types.  This type represents the different 
 * types of light source that can be created using the API function \ref RpLightCreate.  
 * Note that lights of types rpLIGHTPOINT, rpLIGHTSPOT and rpLIGHTSPOTSOFT have linear 
 * intensity fall-off with distance from the source, reducing to zero at the light's radius:*/
enum RpLightType
{
    rpNALIGHTTYPE = 0,

    /* These don't take part in the tie mechanism (no position) */
    rpLIGHTDIRECTIONAL, /**<Directional Light */
    rpLIGHTAMBIENT, /**<Ambient Light */

    /* These do take part in the tie mechanism (do have position) */
    rpLIGHTPOINT = rpLIGHTPOSITIONINGSTART, /**<Point Light */
    rpLIGHTSPOT, /**<Spot Light */
    rpLIGHTSPOTSOFT, /**<Soft Spot Light */
    rpLIGHTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLightType RpLightType;

#define rpLIGHTMINCONEANGLE ((RwReal)0.0f)
#if ((defined(XBOX_DRVMODEL_H)) || (defined(OPENGL_DRVMODEL_H)) || (defined(GCN_DRVMODEL_H)))
/* XBox has Micro$oft-penned drivers, no wonder it crashes... */
/* OpenGL and GCN clamp to 90 internally, so we mirror that behaviour */
#define rpLIGHTMAXCONEANGLE ((RwReal)89.9999f)
#else
#define rpLIGHTMAXCONEANGLE ((RwReal)180.0f)
#endif

/*************/

/*** FLAGS ***/

/*************/

/**
 * \ingroup rpworlddatatypes
 * \ref RpLightFlag defines what geometry is influenced by the light. 
 * The bit-field RpLightFlag specifies the options available for controlling the scope 
 * of a light source (see API function \ref RpLightSetFlags):*/
enum RpLightFlag
{
    rpLIGHTLIGHTATOMICS = 0x01, /**<The light source illuminates all atomics in a world */
    rpLIGHTLIGHTWORLD = 0x02, /**<The light source illuminates all static geometry in a world */
    rpLIGHTFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLightFlag RpLightFlag;

/* rpLIGHTPRIVATENOCHROMA - turns on optimisations to do with
 *                          lights which are a shade of grey
 */
enum rpLightPrivateFlag
{
    rpLIGHTPRIVATENOCHROMA = 0x01,
    rpLIGHTPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum rpLightPrivateFlag rpLightPrivateFlag;

/*********************/


#define RWMINUSCOSFROMTAN(_minusCosAngle, _tanAngle)                  \
MACRO_START                                                           \
{                                                                     \
   const RwReal TanAngle2 = (_tanAngle) * (_tanAngle);                \
   const RwReal CosAngle2 = ((RwReal)1) / ( ((RwReal)1) + TanAngle2); \
   RwReal CosAngle;                                                   \
   rwSqrtMacro(&CosAngle, CosAngle2);                                 \
   (_minusCosAngle) = - CosAngle;                                     \
}                                                                     \
MACRO_STOP

#define RWTANFROMMINUSCOS(_tanAngle, _minusCosAngle)                    \
MACRO_START                                                             \
{                                                                       \
    const RwReal CosAngle2 = (_minusCosAngle) * (_minusCosAngle);       \
    const RwReal TanAngle2 = (((RwReal)1) - (CosAngle2)) / (CosAngle2); \
    rwSqrtMacro(&_tanAngle, TanAngle2);                                 \
}                                                                       \
MACRO_STOP


/**
 * \ingroup rpworlddatatypes
 * \typedef RpLight 
 * Light. This should be 
 * considered an opaque type. User the RpLight API functions to access.
 */
typedef struct RpLight RpLight;

#if (!defined(DOXYGEN))
struct RpLight
{
        RwObjectHasFrame    object; /**< object */
        RwReal              radius; /**< radius */
        RwRGBAReal          color; /**< color */  /* Light color */
        RwReal              minusCosAngle; /**< minusCosAngle */  
        RwLinkList          WorldSectorsInLight; /**< WorldSectorsInLight */
        RwLLLink            inWorld; /**< inWorld */
        RwUInt16            lightFrame; /**< lightFrame */
        RwUInt16            pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpLightCallBack
 * \ref RpLightCallBack 
 * represents the function called from \ref RpWorldForAllLights and 
 * \ref RpWorld SectorForAllLights for all lights in a given world or world 
 * sector. This function should return a pointer to the current light to 
 * indicate success. The callback may return NULL to terminate further 
 * callbacks on the world sector.
 *
 * \return Pointer to the current light.
 * 
 * \param  light   Pointer to the current light in the world 
 * sector.
 * \param  data  Pointer to developer-defined data structure.
 */
typedef RpLight    *(*RpLightCallBack) (RpLight * light, void *data);

typedef struct RpLightTie RpLightTie;

struct RpLightTie
{
    /* Information for an atomic sector */
    RwLLLink            lightInWorldSector; /* Lights IN this ATOMIC SECTOR */
    RpLight            *light;

    /* Information for a atomic */
    RwLLLink            WorldSectorInLight; /* Atomic sectors HOLDING this Light */
    RpWorldSector      *sect;
};


/****************************************************************************
 <macro/inline functionality
 */

#define RpLightGetRadiusMacro(_light)                       \
    ((_light)->radius)

#define RpLightGetColorMacro(_light)                        \
    (&((_light)->color))

#define RpLightSetFrameMacro(_light, _frame)                \
    (rwObjectHasFrameSetFrame((_light), (_frame)), (_light))

#define RpLightGetFrameMacro(_light)                        \
    ((RwFrame *)rwObjectGetParent((_light)))

#define RpLightGetTypeMacro(_light)                         \
    ((RpLightType)rwObjectGetSubType((_light)))

#define RpLightSetFlagsMacro(_light, _flags)                \
    ((rwObjectSetFlags((_light), (_flags))), (_light))

#define RpLightGetFlagsMacro(_light)                        \
    (rwObjectGetFlags((_light)))


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpLightGetRadius(_light)                            \
    RpLightGetRadiusMacro(_light)

#define RpLightGetColor(_light)                             \
    RpLightGetColorMacro(_light)

#define RpLightSetFrame(_light, _frame)                     \
    RpLightSetFrameMacro(_light, _frame)

#define RpLightGetFrame(_light)                             \
    RpLightGetFrameMacro(_light)

#define RpLightGetType(_light)                              \
    RpLightGetTypeMacro(_light)

#define RpLightSetFlags(_light, _flags)                     \
    RpLightSetFlagsMacro(_light, _flags)

#define RpLightGetFlags(_light)                             \
    RpLightGetFlagsMacro(_light)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */


#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwReal RpLightGetRadius(const RpLight *light);
extern const RwRGBAReal *RpLightGetColor(const RpLight *light);
extern RpLight *RpLightSetFrame(RpLight *light, RwFrame *frame);
extern RwFrame *RpLightGetFrame(const RpLight *light);
extern RpLightType RpLightGetType(const RpLight *light);
extern RpLight *RpLightSetFlags(RpLight *light, RwUInt32 flags);
extern RwUInt32 RpLightGetFlags(const RpLight *light);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/* API Functions */
extern RpLight *RpLightCreate(RwInt32 type);
extern RwBool RpLightDestroy(RpLight *light);
extern RpLight *RpLightSetRadius(RpLight *light, RwReal radius);
extern RpLight *RpLightSetColor(RpLight *light, const RwRGBAReal *color);
extern RwReal RpLightGetConeAngle(const RpLight *light);
extern RpLight *RpLightSetConeAngle(RpLight * ight, RwReal angle);
extern RwUInt32 RpLightStreamGetSize(const RpLight *light);
extern RpLight *RpLightStreamRead(RwStream *stream);
extern const RpLight *RpLightStreamWrite(const RpLight *light,
                                         RwStream *stream);
extern RpLightChunkInfo *_rpLightChunkInfoRead(RwStream *stream,
                                               RpLightChunkInfo *lightChunkInfo,
                                               RwInt32 *bytesRead);

/* Attaching toolkits */
extern RwInt32 RpLightRegisterPlugin(RwInt32 size,
                                     RwUInt32 pluginID,
                                     RwPluginObjectConstructor constructCB,
                                     RwPluginObjectDestructor destructCB,
                                     RwPluginObjectCopy copyCB);
extern RwInt32 RpLightRegisterPluginStream(RwUInt32 pluginID,
                                           RwPluginDataChunkReadCallBack readCB,
                                           RwPluginDataChunkWriteCallBack writeCB,
                                           RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 RpLightSetStreamAlwaysCallBack(RwUInt32 pluginID,
                                              RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 RpLightGetPluginOffset(RwUInt32 pluginID);
extern RwBool RpLightValidatePlugins(const RpLight * light);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpLightChunkInfoRead(stream, lightChunkInfo, bytesRead) \
       _rpLightChunkInfoRead(stream, lightChunkInfo, bytesRead)


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/D3D8lights.h ---*/
/**
 * \ingroup rplightd3d8
 * \typedef RpD3D8AttenuationParams
 * typedef for struct RpD3D8AttenuationParams
 */
typedef struct RpD3D8AttenuationParams RpD3D8AttenuationParams;
/**
 * \ingroup rplightd3d8
 * \struct RpD3D8AttenuationParams
 *  This type represents the attenuation model of a spot or point light.
 */
struct RpD3D8AttenuationParams
{
    RwReal constant;    /**< Constant attenuation coefficient */
    RwReal linear;      /**< Linear attenuation coefficient */
    RwReal quadratic;   /**< Quadratic attenuation coefficient */
};

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern void
RpD3D8LightSetAttenuationParams(RpLight *light,
                                const RpD3D8AttenuationParams *params);

extern void
RpD3D8LightGetAttenuationParams(const RpLight *light,
                                RpD3D8AttenuationParams *params);

extern RwBool
_rwD3D8LightsOpen(void);

extern RwBool
_rwD3D8LightsGlobalEnable(RpLightFlag flags);

extern RwBool
_rwD3D8LightDirectionalEnable(RpLight *light);

extern RwBool
_rwD3D8LightLocalEnable(RpLight *light);

extern void
_rwD3D8LightsEnable(RwBool enable, RwUInt32 type);

extern void
_rwD3D8LightsClose(void);


#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/p2stdclsw.h ---*/
typedef RpLight *RxLight;
#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RxClusterDefinition RxClLights; /* Uses the RxLight type (see above) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */



/*--- Automatically derived from: c:/daily/rwsdk/world/bageomet.h ---*/

/*
 * Handling atomic's geometry
 * Geometry describe objects, and are the building blocks for atomics
 *
 * Copyright (c) 1998 Criterion Software Ltd.
*/


/****************************************************************************
 Defines
 */

/* Type ID */
#define rpGEOMETRY 8

/**
 * \ingroup rpworlddatatypes
 * RpGeometryFlag
 * Geometry type flags 
 *
 * When creating a geometry, these flags can be OR'ed together to
 * specify the format along with the rpGEOMETRYTEXCOORDSETS(n) macro if more
 * than two sets of texture coordinates are required. See \ref RpGeometryCreate
 * for more details.
 *
 * \see RpGeometryCreate().
 */
enum RpGeometryFlag
{
    rpGEOMETRYTRISTRIP  = 0x00000001, /**<This geometry's meshes can be
                                          rendered as strips.
                                          \ref RpMeshSetTriStripMethod is
                                          used to change this method.*/
    rpGEOMETRYPOSITIONS = 0x00000002, /**<This geometry has positions */  
    rpGEOMETRYTEXTURED  = 0x00000004, /**<This geometry has only one set of
                                          texture coordinates. Texture
                                          coordinates are specified on a per
                                          vertex basis */
    rpGEOMETRYPRELIT    = 0x00000008, /**<This geometry has pre-light colors */
    rpGEOMETRYNORMALS   = 0x00000010, /**<This geometry has vertex normals */
    rpGEOMETRYLIGHT     = 0x00000020, /**<This geometry will be lit */
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040, /**<Modulate material color 
                                                      with vertex colors
                                                      (pre-lit + lit) */

    rpGEOMETRYTEXTURED2 = 0x00000080, /**<This geometry has at least 2 sets of
                                          texture coordinates. */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpGeometry.
     */

    rpGEOMETRYNATIVE            = 0x01000000,
    rpGEOMETRYNATIVEINSTANCE    = 0x02000000,

    rpGEOMETRYFLAGSMASK         = 0x000000FF,
    rpGEOMETRYNATIVEFLAGSMASK   = 0x0F000000,

    rpGEOMETRYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryFlag RpGeometryFlag;

/* Multi texture coordinate format specifier for RpGeometryCreate() */
#define rpGEOMETRYTEXCOORDSETS(_num) ((_num & 0xff) << 16)

/**
 * \ingroup rpworlddatatypes
 * RpGeometryLockMode
 * Geometry lock flags 
 */
enum RpGeometryLockMode
{
    rpGEOMETRYLOCKPOLYGONS   =   0x01, /**<Lock the polygons (triangle list) */
    rpGEOMETRYLOCKVERTICES   =   0x02, /**<Lock the vertex positional data */
    rpGEOMETRYLOCKNORMALS    =   0x04, /**<Lock the vertex normal data */
    rpGEOMETRYLOCKPRELIGHT   =   0x08, /**<Lock the pre-light values */
    rpGEOMETRYLOCKTEXCOORDS  =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS1 =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS2 =   0x20, /**<Lock the texture coordinates set 2*/
    rpGEOMETRYLOCKTEXCOORDS3 =   0x40, /**<Lock the texture coordinates set 3*/
    rpGEOMETRYLOCKTEXCOORDS4 =   0x80, /**<Lock the texture coordinates set 4*/
    rpGEOMETRYLOCKTEXCOORDS5 = 0x0100, /**<Lock the texture coordinates set 5*/
    rpGEOMETRYLOCKTEXCOORDS6 = 0x0200, /**<Lock the texture coordinates set 6*/
    rpGEOMETRYLOCKTEXCOORDS7 = 0x0400, /**<Lock the texture coordinates set 7*/
    rpGEOMETRYLOCKTEXCOORDS8 = 0x0800, /**<Lock the texture coordinates set 8*/
    rpGEOMETRYLOCKTEXCOORDSALL = 0x0ff0, /**<Lock all texture coordinate sets*/
    rpGEOMETRYLOCKALL        = 0x0fff, /**<Combination of all the above */

    rpGEOMETRYLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryLockMode RpGeometryLockMode;

/* Convenience macro for generating a tex coord lock flag */
#define rpGEOMETRYLOCKTEXCOORDSIDX(_idx) (rpGEOMETRYLOCKTEXCOORDS1 << (_idx))


/****************************************************************************
 Global Types
 */

typedef struct rpGeometryGlobals rpGeometryGlobals;
struct rpGeometryGlobals
{
        RwFreeList         *geomFreeList;
};

/**
 * \ingroup rpworlddatatypes
 * \typedef RpGeometry 
 * Geometry object. This should be considered an opaque type. 
 * Use the RpGeometry API functions to access.
 */
typedef struct RpGeometry RpGeometry;

/**
 * \ingroup rpworlddatatypes
 * \typedef RpMorphTarget 
 * Morph target -- vertex positions and normals. 
 * This should be considered an opaque type. 
 * Use RpMorphTarget API functions to access.
 */
typedef struct RpMorphTarget RpMorphTarget;

#if (!defined(DOXYGEN))
struct RpMorphTarget
{
        RpGeometry *parentGeom; 
        RwSphere   boundingSphere;
        RwV3d      *verts;
        RwV3d      *normals;
};
#endif /* (!defined(DOXYGEN)) */

typedef struct RpTriangle RpTriangle;

/**
 * \ingroup rpworlddatatypes
 * \struct RpTriangle 
 * This type represents a triangle in a geometry specified 
 * by three indices into the geometry's vertex list (vertIndex)
 * together with an  index in to the geometry's 
 * material list (matIndex) (see API function \ref RpGeometryGetTriangles)
 */
struct RpTriangle
{
    RwUInt16            vertIndex[3]; /**< vertex indices */
    RwInt16             matIndex; /**< Index into material list */
};

#if (!defined(DOXYGEN))
struct RpGeometry
{
    RwObject            object;     /* Generic type */

    RwUInt32            flags;      /* Geometry flags */

    RwUInt16            lockedSinceLastInst; /* What has been locked since we last instanced - for re-instancing */
    RwInt16             refCount;   /* Reference count (for keeping track of atomics referencing geometry) */

    RwInt32             numTriangles; /* Quantity of various things (polys, verts and morph targets) */
    RwInt32             numVertices;
    RwInt32             numMorphTargets;
    RwInt32             numTexCoordSets;

    RpMaterialList      matList;

    RpTriangle         *triangles;  /* The triangles */

    RwRGBA             *preLitLum;  /* The pre-lighting values */

    RwTexCoords        *texCoords[rwMAXTEXTURECOORDS]; /* Texture coordinates */

    RwSurfaceProperties ignoredSurfaceProps; /* Not used in pp rendering, but present
                                              * so if pipe1 files are read and written these
                                              * values are not lost
                                              */

    RpMeshHeader       *mesh;   /* The mesh - groups polys of the same material */

    RwResEntry         *repEntry;       /* Information for an instance */

    RpMorphTarget      *morphTarget;    /* The Morph Target */
};
#endif /* (!defined(DOXYGEN)) */

typedef struct RpGeometryChunkInfo RpGeometryChunkInfo;
typedef struct RpGeometryChunkInfo _rpGeometry;

struct RpGeometryChunkInfo
{
    RwInt32             format;  /* Compression flags and number of texture coord sets */

    RwInt32             numTriangles;
    RwInt32             numVertices;

    RwInt32             numMorphTargets;

    RwSurfaceProperties ignoredSurfaceProps;
};

/* Callbacks */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpGeometryCallBack 
 * \ref RpGeometryCallBack represents the simple callback function for the \ref RpGeometry object.
 * The callback may return NULL to terminate further callbacks on 
 * the geometry.
 * 
 * \param  geometry   Pointer to the current geometry, supplied by iterator.
 * \param  data  Pointer to developer-defined data structure.
 */
typedef RpGeometry *(*RpGeometryCallBack)(RpGeometry *geometry, void *data);

/**
 * \ingroup rpworlddatatypes
 * \typedef RpGeometrySortByMaterialCallBack 
 * \ref RpGeometrySortByMaterialCallBack is used by
 * \ref RpGeometrySortByMaterial in order to preserve the validity of plugin
 * data when the vertices in an \ref RpGeometry are sorted (and some possibly
 * duplicated).
 *
 * A vertex map table is provided to the callback - this contains, for each
 * vertex in the new geometry, the index of the corresponding vertex in the
 * original geometry.
 *
 * \param  oldGeom   Pointer to the source geometry.
 * \param  newGeom   Pointer to the new, sorted geometry.
 * \param  remapTable   pointer to the vertex map table
 * \param  numberOfEntries   Number of vertices in the new 
 * geometry (size of the map table)
 */
typedef void (*RpGeometrySortByMaterialCallBack)(const RpGeometry *oldGeom,
                                                 RpGeometry *newGeom,
                                                 RwUInt16 *remapTable,
                                                 RwUInt16 numberOfEntries);


/****************************************************************************
 <macro/inline functionality
 */

#define RpMorphTargetSetBoundingSphereMacro(_mt, _sphere)       \
    (RwSphereAssign(&((_mt)->boundingSphere), (_sphere)), (_mt))

#define RpMorphTargetGetBoundingSphereMacro(_mt)                \
    (&((_mt)->boundingSphere))

#define RpGeometryGetNumMorphTargetsMacro(_geometry)            \
    ((_geometry)->numMorphTargets)

#define RpGeometryGetMorphTargetMacro(_geometry, _index)        \
    (&((_geometry)->morphTarget[(_index)]))

#define RpGeometryGetPreLightColorsMacro(_geometry)             \
    ((_geometry)->preLitLum)

#define RpGeometryGetVertexTexCoordsMacro(_geometry, _uvIndex)    \
    ((_geometry)->texCoords[(_uvIndex) - 1])

#define RpGeometryGetNumTexCoordSetsMacro(_geometry)            \
    ((_geometry)->numTexCoordSets)

#define RpGeometryGetNumVerticesMacro(_geometry)                \
    ((_geometry)->numVertices)

#define RpMorphTargetGetVerticesMacro(_mt)                      \
    ((_mt)->verts)

#define RpMorphTargetGetVertexNormalsMacro(_mt)                 \
    ((_mt)->normals)

#define RpGeometryGetTrianglesMacro(_geometry)                  \
    ((_geometry)->triangles)

#define RpGeometryGetNumTrianglesMacro(_geometry)               \
    ((_geometry)->numTriangles)

#define RpGeometryGetMaterialMacro(_geometry, _num)             \
    (((_geometry)->matList.materials)[(_num)])

#define RpGeometryGetNumMaterialsMacro(_geometry)               \
    ((_geometry)->matList.numMaterials)

#define RpGeometryGetFlagsMacro(_geometry)                      \
    ((_geometry)->flags)

#define RpGeometrySetFlagsMacro(_geometry, _flags)              \
    (((_geometry)->flags = (_flags)), (_geometry))


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpMorphTargetSetBoundingSphere(_geometry, _sphere)      \
    RpMorphTargetSetBoundingSphereMacro(_geometry, _sphere)

#define RpMorphTargetGetBoundingSphere(_geometry)               \
    RpMorphTargetGetBoundingSphereMacro(_geometry)

#define RpGeometryGetNumMorphTargets(_geometry)                 \
    RpGeometryGetNumMorphTargetsMacro(_geometry)

#define RpGeometryGetMorphTarget(_geometry, _index)             \
    RpGeometryGetMorphTargetMacro(_geometry, _index)

#define RpGeometryGetPreLightColors(_geometry)                  \
    RpGeometryGetPreLightColorsMacro(_geometry)

#define RpGeometryGetVertexTexCoords(_geometry, _uvIndex)       \
    RpGeometryGetVertexTexCoordsMacro(_geometry, _uvIndex)

#define RpGeometryGetNumTexCoordSets(_geometry)                 \
    RpGeometryGetNumTexCoordSetsMacro(_geometry)

#define RpGeometryGetNumVertices(_geometry)                     \
    RpGeometryGetNumVerticesMacro(_geometry)

#define RpMorphTargetGetVertices(_mt)                           \
    RpMorphTargetGetVerticesMacro(_mt)

#define RpMorphTargetGetVertexNormals(_mt)                      \
    RpMorphTargetGetVertexNormalsMacro(_mt)

#define RpGeometryGetTriangles(_geometry)                       \
    RpGeometryGetTrianglesMacro(_geometry)

#define RpGeometryGetNumTriangles(_geometry)                    \
    RpGeometryGetNumTrianglesMacro(_geometry)

#define RpGeometryGetMaterial(_geometry, _num)                  \
    RpGeometryGetMaterialMacro(_geometry, _num)

#define RpGeometryGetNumMaterials(_geometry)                    \
    RpGeometryGetNumMaterialsMacro(_geometry)

#define RpGeometryGetFlags(_geometry)                           \
    RpGeometryGetFlagsMacro(_geometry)

#define RpGeometrySetFlags(_geometry, _flags)                   \
    RpGeometrySetFlagsMacro(_geometry, _flags)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */


/* Transforms geometry morph target vertices */

extern RpGeometry  *
RpGeometryTransform(RpGeometry *geometry,
                    const RwMatrix *matrix);

/* Create geometry for a 'space' marker */

extern RpGeometry  *
RpGeometryCreateSpace(RwReal radius);

/* Morph targets - Accessing geometry contents */

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

extern RpMorphTarget  *
RpMorphTargetSetBoundingSphere(RpMorphTarget *morphTarget,
                               const RwSphere *boundingSphere);

extern RwSphere  *
RpMorphTargetGetBoundingSphere(RpMorphTarget *morphTarget);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern const RpMorphTarget  *
RpMorphTargetCalcBoundingSphere(const RpMorphTarget *morphTarget,
                                RwSphere *boundingSphere);

extern RwInt32
RpGeometryAddMorphTargets(RpGeometry *geometry,
                          RwInt32 mtcount);

extern RwInt32
RpGeometryAddMorphTarget(RpGeometry *geometry);

extern RpGeometry  *
RpGeometryRemoveMorphTarget(RpGeometry *geometry,
                            RwInt32 morphTarget);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwInt32
RpGeometryGetNumMorphTargets(const RpGeometry *geometry);

extern RpMorphTarget  *
RpGeometryGetMorphTarget(const RpGeometry *geometry,
                         RwInt32 morphTarget);

extern RwRGBA  *
RpGeometryGetPreLightColors(const RpGeometry *geometry);

extern RwTexCoords  *
RpGeometryGetVertexTexCoords(const RpGeometry *geometry,
                             RwTextureCoordinateIndex uvIndex);

extern RwInt32
RpGeometryGetNumTexCoordSets(const RpGeometry *geometry);

extern RwInt32
RpGeometryGetNumVertices (const RpGeometry *geometry);

extern RwV3d  *
RpMorphTargetGetVertices(const RpMorphTarget *morphTarget);

extern RwV3d  *
RpMorphTargetGetVertexNormals(const RpMorphTarget *morphTarget);

extern RpTriangle  *
RpGeometryGetTriangles(const RpGeometry *geometry);

extern RwInt32
RpGeometryGetNumTriangles(const RpGeometry *geometry);

extern RpMaterial  *
RpGeometryGetMaterial(const RpGeometry *geometry,
                      RwInt32 matNum);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern const RpGeometry  *
RpGeometryTriangleSetVertexIndices(const RpGeometry *geometry,
                                   RpTriangle *triangle,
                                   RwUInt16 vert1,
                                   RwUInt16 vert2,
                                   RwUInt16 vert3);

extern RpGeometry  *
RpGeometryTriangleSetMaterial(RpGeometry *geometry,
                              RpTriangle *triangle,
                              RpMaterial *material);

extern const RpGeometry  *
RpGeometryTriangleGetVertexIndices(const RpGeometry *geometry,
                                   const RpTriangle *triangle,
                                   RwUInt16 *vert1,
                                   RwUInt16 *vert2,
                                   RwUInt16 *vert3);

extern RpMaterial   *
RpGeometryTriangleGetMaterial(const RpGeometry *geometry,
                              const RpTriangle *triangle);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
extern RwInt32
RpGeometryGetNumMaterials(const RpGeometry *geometry);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern RpGeometry  *
RpGeometryForAllMaterials(RpGeometry *geometry,
                          RpMaterialCallBack fpCallBack,
                          void *pData);

/* Accessing the inards of geometry */
extern RpGeometry  *
RpGeometryLock(RpGeometry *geometry,
               RwInt32 lockMode);

extern RpGeometry  *
RpGeometryUnlock(RpGeometry *geometry);

extern const RpGeometry  *
RpGeometryForAllMeshes(const RpGeometry *geometry,
                       RpMeshCallBack fpCallBack,
                       void *pData);

/* Creation and destruction */
extern RpGeometry  *
RpGeometryCreate(RwInt32 numVert,
                 RwInt32 numTriangles,
                 RwUInt32 format);

extern RwBool
RpGeometryDestroy(RpGeometry *geometry);

extern RpGeometry *
_rpGeometryAddRef(RpGeometry *geometry);

/* Attaching toolkits */
extern RwInt32
RpGeometryRegisterPlugin(RwInt32 size,
                         RwUInt32 pluginID,
                         RwPluginObjectConstructor constructCB,
                         RwPluginObjectDestructor destructCB,
                         RwPluginObjectCopy copyCB);

extern RwInt32
RpGeometryRegisterPluginStream(RwUInt32 pluginID,
                               RwPluginDataChunkReadCallBack readCB,
                               RwPluginDataChunkWriteCallBack writeCB,
                               RwPluginDataChunkGetSizeCallBack getSizeCB);

extern RwInt32
RpGeometrySetStreamAlwaysCallBack(RwUInt32 pluginID,
                                  RwPluginDataChunkAlwaysCallBack alwaysCB);

extern RwInt32
RpGeometryGetPluginOffset(RwUInt32 pluginID);

extern RwBool
RpGeometryValidatePlugins(const RpGeometry *geometry);

/* Binary format */
extern RwUInt32
RpGeometryStreamGetSize(const RpGeometry *geometry);

extern const RpGeometry  *
RpGeometryStreamWrite(const RpGeometry *geometry,
                      RwStream *stream);

extern RpGeometry  *
RpGeometryStreamRead(RwStream *stream);

extern RpGeometryChunkInfo *
_rpGeometryChunkInfoRead(RwStream *stream,
                         RpGeometryChunkInfo *geometryChunkInfo,
                         RwInt32 *bytesRead);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
/* Flags */
extern RwUInt32
RpGeometryGetFlags(const RpGeometry *geometry);

extern RpGeometry  *
RpGeometrySetFlags(RpGeometry *geometry,
                   RwUInt32 flags);

#endif

/* Lighting characteristics */

extern const RwSurfaceProperties *
_rpGeometryGetSurfaceProperties(const RpGeometry *geometry);

extern RpGeometry *
_rpGeometrySetSurfaceProperties(RpGeometry *geometry,
                                const RwSurfaceProperties *surfaceProperties);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpGeometryGetSurfaceProperties(_geometry) \
    _rpGeometryGetSurfaceProperties(_geometry)

#define RpGeometrySetSurfaceProperties(_geometry, _surfaceProperties) \
    _rpGeometrySetSurfaceProperties(_geometry, _surfaceProperties)

#define rpGeometryAddRef(_geometry) \
    _rpGeometryAddRef(_geometry) 

#define RpGeometryChunkInfoRead(stream, geometryChunkInfo, bytesRead) \
       _rpGeometryChunkInfoRead(stream, geometryChunkInfo, bytesRead)


/*--- Automatically derived from: c:/daily/rwsdk/world/baclump.h ---*/

/*
 * Clump and atomic handling.
 * Clumps and atomics are the movable rendered objects in the world
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */


/****************************************************************************
 Defines
 */

/****************************** Object type ID ******************************/

/* Type IDs */

#define rpATOMIC 1
#define rpCLUMP 2

/* Interpolator flags */
enum RpInterpolatorFlag
{
    rpINTERPOLATORDIRTYINSTANCE = 0x01,
    rpINTERPOLATORDIRTYSPHERE = 0x02,
    rpINTERPOLATORNOFRAMEDIRTY = 0x04,
    rpINTERPOLATORFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpInterpolatorFlag rpInterpolatorFlag;

/**
 * \ingroup rpworlddatatypes
 * The bit-field type RpAtomicFlag specifies the options available for
 * controlling the behavior of atomics. See API function \ref RpAtomicSetFlags.
 *
 * \see RpAtomicSetFlags
 * \see RpAtomicGetFlags
 * \see RpWorldSectorForAllCollisionAtomics
 */

enum RpAtomicFlag
{
    rpATOMICCOLLISIONTEST = 0x01, /**<A generic collision flag to indicate
                                   * that the atomic should be considered
                                   * in collision tests.
                                   */
    rpATOMICRENDER = 0x04,      /**<The atomic is rendered if it is
                                 * in the view frustum.
                                 */

    rpATOMICFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicFlag RpAtomicFlag;

/**
 * \ingroup rpworlddatatypes
 * \ref RpAtomicSetGeomFlag defines how an atomic references a new geometry
 *
 * \see RpAtomicSetGeometry
 */
enum RpAtomicSetGeomFlag
{
    rpATOMICSAMEBOUNDINGSPHERE = 0x01, /**<The bounding-sphere for the
                                        * new geometry is assumed to be the
                                        * same as the old one, if any, and
                                        * should not be recalculated.
                                        */

    rpATOMICSETGEOMFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicSetGeomFlag RpAtomicSetGeomFlag;

enum RpAtomicPrivateFlag
{
    rpATOMICPRIVATEWORLDBOUNDDIRTY = 0x01,
    rpATOMICPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicPrivateFlag rpAtomicPrivateFlag;


/**
 * \ingroup rpworlddatatypes
 * \typedef RpAtomic
 * Atomic Geometry object. This should be
 * considered an opaque type. Use the RpAtomic API functions to access.
 */
typedef struct RpAtomic RpAtomic;

/**
 * \ingroup rpworlddatatypes
 * \typedef RpInterpolator
 * Morph Target Interpolator.
 * This should be considered an opaque type.
 * Use the RpInterpolator API functions to access.
 */
typedef struct RpInterpolator RpInterpolator;

#if (!defined(DOXYGEN))
struct RpInterpolator
{
        RwInt32             flags; /**< flags */
        RwInt16             startMorphTarget; /**< startMorphTarget */
        RwInt16             endMorphTarget; /**< endMorphTarget */
        RwReal              time; /**< time */
        RwReal              recipTime; /**< recipTime */
        RwReal              position; /**< position */
};
#endif /* (!defined(DOXYGEN)) */

/* More callbacks */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpClump
 * Clump Geometry object. This should be
 * considered an opaque type. Use the RpClump API functions to access.
 */
typedef struct RpClump RpClump;

/**
 * \ingroup rpworlddatatypes
 * \typedef RpClumpCallBack
 * \ref RpClumpCallBack represents the
 * function called from \ref RwCameraForAllClumpsInFrustum and
 * \ref RwCameraForAllClumpsNotInFrustum when a clump lies inside the current camera's
 * view frustum.  It is also called from \ref RpWorldForAllClumps.  This function should
 * return a pointer to the current clump to indicate success.  The callback may return
 * NULL to terminate further callbacks on the clumps.
 *
 * \param  clump   Pointer to the current clump, supplied by
 * iterator.
 * \param  data  Pointer to developer-defined data structure.
 *
 * \return Pointer to the current clump.
 *
 * \see RpWorldForAllClumps
 * \see RpClumpGetCallBack
 * \see RpClumpSetCallBack
 * \see RwCameraForAllClumpsInFrustum
 * \see RwCameraForAllClumpsNotInFrustum
 */
typedef RpClump    *(*RpClumpCallBack) (RpClump * clump, void *data);

#if (!defined(DOXYGEN))
struct RpClump
{
        RwObject            object;

        /* Information about all the Atomics */
        RwLinkList          atomicList;

        /* Lists of lights and cameras */
        RwLinkList          lightList;
        RwLinkList          cameraList;

        /* The clump in the world */
        RwLLLink            inWorldLink;

        /* Clump callback */
        RpClumpCallBack     callback;

        /* Render frame - used to prevent multiple invocations
         * of the clump frustum callback
         */
        RwUInt16            renderFrame;
        RwUInt16            pad;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpAtomicCallBackRender
 * \ref RpAtomicCallBackRender represents the function called from
 * \ref RpAtomicRender when the specified atomic
 * lies inside the current camera's view frustum. The default callback
 * initiates execution of the atomic rendering pipeline. This function should
 * return a pointer to the atomic to indicate success.
 *
 * \param  atomic   Pointer to the current atomic, supplied by
 * iterator.
 *
 * \see RpAtomicRender
 */
typedef RpAtomic   *(*RpAtomicCallBackRender) (RpAtomic * atomic);

#if (!defined(DOXYGEN))
struct RpAtomic
{
    RwObjectHasFrame    object;

    /* Information for an instance */
    RwResEntry         *repEntry;

    /* Triangles making the object */
    RpGeometry         *geometry;

    /* Interpolated bounding sphere (in object space and world space) */
    RwSphere            boundingSphere;
    RwSphere            worldBoundingSphere;

    /* Connections to other atomics */
    RpClump            *clump;
    RwLLLink            inClumpLink;

    /* callbacks */
    RpAtomicCallBackRender renderCallBack;

    /* Interpolation animation pointer */
    RpInterpolator      interpolator;

    /* Counter for checks of "render has occurred already" */
    RwUInt16            renderFrame;
    RwUInt16            pad;

    /* Connections to sectors */
    RwLinkList          llWorldSectorsInAtomic;

    /* The Atomic object pipeline for this Atomic */
    RxPipeline         *pipeline;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rpworlddatatypes
 * \typedef RpAtomicCallBack
 * \ref RpAtomicCallBack represents the function called from \ref RpWorldSectorForAllAtomics and
 * \ref RpClumpForAllAtomics for all atomics in a given world sector or clump.
 * This function should return a pointer to the current atomic to indicate
 * success. The callback may return NULL to terminate further callbacks on
 * the world sector.
 *
 * \param  atomic   Pointer to the current atomic, supplied by
 * iterator.
 * \param  data  Pointer to developer-defined data structure.
 */
typedef RpAtomic   *(*RpAtomicCallBack) (RpAtomic * atomic, void *data);

typedef struct RpTie RpTie;

struct RpTie
{
    /* Information for an atomic sector */
    RwLLLink            lAtomicInWorldSector; /* Atomics IN this ATOMIC SECTOR */
    RpAtomic           *apAtom;

    /* Information for a atomic */
    RwLLLink            lWorldSectorInAtomic; /* Atomic sectors HOLDING this atomic */
    RpWorldSector      *worldSector;
};

typedef struct RpClumpChunkInfo RpClumpChunkInfo;
typedef struct RpClumpChunkInfo _rpClump;
typedef struct RpClumpChunkInfo33000 _rpClump33000;

struct RpClumpChunkInfo
{
    RwInt32             numAtomics;
    RwInt32             numLights;
    RwInt32             numCameras;
};

struct RpClumpChunkInfo33000
{
    RwInt32             numAtomics;
};

/****************************************************************************
 <macro/inline functionality

 */

/* NB "RpAtomicRender(atom++) will break it */
#define RpAtomicRenderMacro(_atomic)                                    \
    ((_atomic)->renderCallBack(_atomic))

#define RpAtomicGetGeometryMacro(_atomic)                               \
    ((_atomic)->geometry)

#if (!defined(RpAtomicSetRenderCallBackMacro))

/* NB "RpAtomicSetRenderCallBack(atom++, callback)" will break it */
#define RpAtomicSetRenderCallBackMacro(_atomic, _callback)              \
MACRO_START                                                             \
{                                                                       \
    (_atomic)->renderCallBack = (_callback);                            \
    if (!(_atomic)->renderCallBack)                                     \
    {                                                                   \
        (_atomic)->renderCallBack = AtomicDefaultRenderCallBack;        \
    }                                                                   \
}                                                                       \
MACRO_STOP

#endif /* (!defined(RpAtomicSetRenderCallBackMacro)) */

#define RpAtomicGetRenderCallBackMacro(_atomic)                         \
    ((_atomic)->renderCallBack)

#define RpAtomicGetInterpolatorMacro(_atomic)                         \
    (&((_atomic)->interpolator))

#define RpInterpolatorGetStartMorphTargetMacro(_intrp)                  \
    ((_intrp)->startMorphTarget)

#define RpInterpolatorGetEndMorphTargetMacro(_intrp)                    \
    ((_intrp)->endMorphTarget)

#define RpInterpolatorGetValueMacro(_intrp)                             \
    ((_intrp)->position)

#define RpInterpolatorGetScaleMacro(_intrp)                             \
    ((_intrp)->time)

/* NB "RpInterpolatorSetStartMorphTarget(interp++, target)" will break it */
#define RpInterpolatorSetStartMorphTargetMacro(_intrp, _target, _atomic)\
    ((_intrp)->startMorphTarget = (RwInt16) (_target),                  \
     (_intrp)->flags |= (RwInt32)(rpINTERPOLATORDIRTYINSTANCE |         \
                                  rpINTERPOLATORDIRTYSPHERE     ),      \
     ((!((_intrp)->flags & rpINTERPOLATORNOFRAMEDIRTY))?                \
         ((RpAtomicGetFrame(_atomic))?                                  \
            (RwFrameUpdateObjects(RpAtomicGetFrame(_atomic))):          \
            (0)):                                                       \
         (0)),                                                          \
     (_intrp))

/* NB "RpInterpolatorSetEndMorphTarget(interp++, target)" will break it */
#define RpInterpolatorSetEndMorphTargetMacro(_intrp, _target, _atomic)  \
    ((_intrp)->endMorphTarget = (RwInt16) (_target),                    \
     (_intrp)->flags |= (RwInt32)(rpINTERPOLATORDIRTYINSTANCE |         \
                                  rpINTERPOLATORDIRTYSPHERE     ),      \
     ((!((_intrp)->flags & rpINTERPOLATORNOFRAMEDIRTY))?                \
         ((RpAtomicGetFrame(_atomic))?                                  \
            (RwFrameUpdateObjects(RpAtomicGetFrame(_atomic))):          \
            (0)):                                                       \
         (0)),                                                          \
     (_intrp))

/* NB "RpInterpolatorSetValue(interp++, value)" will break it */
#define RpInterpolatorSetValueMacro(_intrp, _value, _atomic)            \
    ((_intrp)->position = (_value),                                     \
     (_intrp)->flags |= (RwInt32)(rpINTERPOLATORDIRTYINSTANCE |         \
                                  rpINTERPOLATORDIRTYSPHERE     ),      \
     ((!((_intrp)->flags & rpINTERPOLATORNOFRAMEDIRTY))?                \
         ((RpAtomicGetFrame(_atomic))?                                  \
            (RwFrameUpdateObjects(RpAtomicGetFrame(_atomic))):          \
            (0)):                                                       \
         (0)),                                                          \
     (_intrp))

/* NB "RpInterpolatorSetScale(interp++, *(scale++))" will break it */
#define RpInterpolatorSetScaleMacro(_intrp, _scale, _atomic)            \
    ((_intrp)->time = (_scale),                                         \
     (_intrp)->recipTime = (RwReal) (1.0) / (_scale),                   \
     (_intrp)->flags |= (RwInt32)(rpINTERPOLATORDIRTYINSTANCE |         \
                                  rpINTERPOLATORDIRTYSPHERE     ),      \
     ((!((_intrp)->flags & rpINTERPOLATORNOFRAMEDIRTY))?                \
         ((RpAtomicGetFrame(_atomic))?                                  \
            (RwFrameUpdateObjects(RpAtomicGetFrame(_atomic))):          \
            (0)):                                                       \
         (0)),                                                          \
     (_intrp))

#define RpAtomicGetClumpMacro(_atomic)                                  \
    ((_atomic)->clump)

/* NB "RpAtomicGetBoundingSphere(atomic++)" will break it */
#define RpAtomicGetBoundingSphereMacro(_atomic)                         \
    ((((_atomic)->interpolator.flags & rpINTERPOLATORDIRTYSPHERE)?      \
      _rpAtomicResyncInterpolatedSphere(_atomic), 0: 0),                \
      &((_atomic)->boundingSphere))
#define RpAtomicGetFrameMacro(_atomic)                                  \
    ((RwFrame *) rwObjectGetParent(_atomic))

/* NB "RpClumpSetFrame(clump++, frame)" will break it */
#if (!defined(RpClumpSetFrameMacro))
#define RpClumpSetFrameMacro(_clump, _frame)                            \
    (rwObjectSetParent(_clump, _frame),                                 \
     (_clump))
#endif /* (!defined(RpClumpSetFrameMacro)) */

#if (!defined(RpClumpSetFrameVoidMacro))
#define RpClumpSetFrameVoidMacro(_clump, _frame)                        \
MACRO_START                                                             \
{                                                                       \
    rwObjectSetParent(_clump, _frame);                                  \
}                                                                       \
MACRO_STOP
#endif /* (!defined(RpClumpSetFrameVoidMacro)) */

#define RpClumpGetFrameMacro(_clump)                                    \
    ((RwFrame *) rwObjectGetParent(_clump))

/* NB "RpAtomicSetFlags(atomic++, flags)" will break it */
#if (!defined(RpAtomicSetFlagsMacro))
#define RpAtomicSetFlagsMacro(_atomic, _flags)                          \
    (rwObjectSetFlags(_atomic, _flags),                                 \
     (_atomic))
#endif /* (!defined(RpAtomicSetFlagsMacro)) */

#define RpAtomicGetFlagsMacro(_atomic)                                  \
    (rwObjectGetFlags(_atomic))

#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))

#define RpAtomicRender(_atomic) \
    RpAtomicRenderMacro(_atomic)

#define RpAtomicGetGeometry(_atomic) \
    RpAtomicGetGeometryMacro(_atomic)

#define RpAtomicSetRenderCallBack(_atomic, _callback) \
    RpAtomicSetRenderCallBackMacro(_atomic, _callback)

#define RpAtomicGetRenderCallBack(_atomic) \
    RpAtomicGetRenderCallBackMacro(_atomic)

#define RpAtomicGetInterpolator(_atomic) \
    RpAtomicGetInterpolatorMacro(_atomic)

#define RpInterpolatorGetStartMorphTarget(_intrp) \
    RpInterpolatorGetStartMorphTargetMacro(_intrp)

#define RpInterpolatorGetEndMorphTarget(_intrp) \
    RpInterpolatorGetEndMorphTargetMacro(_intrp)

#define RpInterpolatorGetValue(_intrp) \
    RpInterpolatorGetValueMacro(_intrp)

#define RpInterpolatorGetScale(_intrp) \
    RpInterpolatorGetScaleMacro(_intrp)

#define RpInterpolatorSetStartMorphTarget(_intrp, _target, _atomic) \
    RpInterpolatorSetStartMorphTargetMacro(_intrp, _target, _atomic)

#define RpInterpolatorSetEndMorphTarget(_intrp, _target, _atomic) \
    RpInterpolatorSetEndMorphTargetMacro(_intrp, _target, _atomic)

#define RpInterpolatorSetValue(_intrp, _value, _atomic) \
    RpInterpolatorSetValueMacro(_intrp, _value, _atomic)

#define RpInterpolatorSetScale(_intrp, _scale, _atomic) \
    RpInterpolatorSetScaleMacro(_intrp, _scale, _atomic)

#define RpAtomicGetClump(_atomic) \
    RpAtomicGetClumpMacro(_atomic)

#define RpAtomicGetBoundingSphere(_atomic) \
    RpAtomicGetBoundingSphereMacro(_atomic)

#define RpAtomicGetFrame(_atomic) \
    RpAtomicGetFrameMacro(_atomic)

#define RpClumpSetFrame(_clump, _frame) \
    RpClumpSetFrameMacro(_clump, _frame)

#define RpClumpGetFrame(_clump) \
    RpClumpGetFrameMacro(_clump)

#define RpAtomicSetFlags(_atomic, _flags) \
    RpAtomicSetFlagsMacro(_atomic, _flags)

#define RpAtomicGetFlags(_atomic) \
    RpAtomicGetFlagsMacro(_atomic)

#endif /* (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */


/* Macro version of RpAtomicSetRenderCallBack needs this */
extern RpAtomic *
AtomicDefaultRenderCallBack(RpAtomic * atomic);

extern void
_rpAtomicResyncInterpolatedSphere(RpAtomic * atomic);

extern const RwSphere *
RpAtomicGetWorldBoundingSphere(RpAtomic *  atomic);

/* Enumeration */
extern RpClump *
RpClumpForAllAtomics(RpClump * clump,
                     RpAtomicCallBack callback,
                     void *pData);

extern RpClump *
RpClumpForAllLights(RpClump * clump,
                    RpLightCallBack callback,
                    void *pData);

extern RpClump *
RpClumpForAllCameras(RpClump * clump,
                     RwCameraCallBack callback,
                     void *pData);

/* Frames */
extern RpAtomic *
RpAtomicSetFrame(RpAtomic * atomic,
                 RwFrame * frame);

/* Create a space marking clump */
extern RpClump *
RpClumpCreateSpace(const RwV3d * position,
                   RwReal radius);

/* Instancing and rendering */
extern RpClump *
RpClumpRender(RpClump * clump);

extern RpClump *
RpClumpRemoveAtomic(RpClump * clump,
                    RpAtomic * atomic);

extern RpClump *
RpClumpAddAtomic(RpClump * clump,
                 RpAtomic * atomic);

extern RpClump *
RpClumpRemoveLight(RpClump * clump,
                   RpLight * light);

extern RpClump *
RpClumpAddLight(RpClump * clump,
                RpLight * light);

extern RpClump *
RpClumpRemoveCamera(RpClump * clump,
                    RwCamera * camera);

extern RpClump *
RpClumpAddCamera(RpClump * clump,
                 RwCamera * camera);

/* Creation and destruction of clumps */
extern RwBool
RpClumpDestroy(RpClump * clump);

extern RpClump *
RpClumpCreate(void);

extern RpClump *
RpClumpClone(RpClump * clump);

/* Creation and destruction of atomics*/
extern RwBool
RpAtomicDestroy(RpAtomic * atomic);

extern RpAtomic *
RpAtomicClone(RpAtomic * atomic);

extern RpAtomic *
RpAtomicCreate(void);

/* Setting and getting geometry for an atomic */
extern RpAtomic *
RpAtomicSetGeometry(RpAtomic * atomic,
                    RpGeometry * geometry,
                    RwUInt32 flags);

/* Frustum callbacks */
extern RpClump *
RpClumpSetCallBack(RpClump * clump,
                   RpClumpCallBack callback);

extern RpClumpCallBack
RpClumpGetCallBack(const RpClump * clump);

/* The number of atomics in a clump */
extern RwInt32
RpClumpGetNumAtomics(RpClump * clump);

extern RwInt32
RpClumpGetNumLights(RpClump * clump);

extern RwInt32
RpClumpGetNumCameras(RpClump * clump);

/* Light and camera extensions */
extern RpClump *
RpLightGetClump(const RpLight *light);

extern RpClump *
RwCameraGetClump(const RwCamera *camera);

/* Binary format */
extern RwUInt32
RpAtomicStreamGetSize(RpAtomic * atomic);

extern RpAtomic *
RpAtomicStreamRead(RwStream * stream);

extern RpAtomic *
RpAtomicStreamWrite(RpAtomic * atomic,
                    RwStream * stream);

extern RwUInt32
RpClumpStreamGetSize(RpClump * clump);

extern RpClump *
RpClumpStreamRead(RwStream * stream);

extern RpClump *
RpClumpStreamWrite(RpClump * clump,
                   RwStream * stream);

extern RpClumpChunkInfo *
_rpClumpChunkInfoRead(RwStream * stream,
                      RpClumpChunkInfo * clumpChunkInfo,
                      RwInt32 * bytesRead);

/* Attaching toolkits */
extern RwInt32
RpAtomicRegisterPlugin(RwInt32 size,
                       RwUInt32 pluginID,
                       RwPluginObjectConstructor constructCB,
                       RwPluginObjectDestructor destructCB,
                       RwPluginObjectCopy copyCB);

extern RwInt32
RpClumpRegisterPlugin(RwInt32 size,
                      RwUInt32 pluginID,
                      RwPluginObjectConstructor constructCB,
                      RwPluginObjectDestructor destructCB,
                      RwPluginObjectCopy copyCB);

extern RwInt32
RpAtomicRegisterPluginStream(RwUInt32 pluginID,
                             RwPluginDataChunkReadCallBack
                             readCB,
                             RwPluginDataChunkWriteCallBack
                             writeCB,
                             RwPluginDataChunkGetSizeCallBack
                             getSizeCB);

extern RwInt32
RpAtomicSetStreamAlwaysCallBack(RwUInt32 pluginID,
                                     RwPluginDataChunkAlwaysCallBack alwaysCB);

extern RwInt32
RpAtomicSetStreamRightsCallBack(RwUInt32 pluginID,
                                     RwPluginDataChunkRightsCallBack rightsCB);

extern RwInt32
RpClumpRegisterPluginStream(RwUInt32 pluginID,
                            RwPluginDataChunkReadCallBack  readCB,
                            RwPluginDataChunkWriteCallBack writeCB,
                            RwPluginDataChunkGetSizeCallBack getSizeCB);

extern RwInt32
RpClumpSetStreamAlwaysCallBack(RwUInt32 pluginID,
                                    RwPluginDataChunkAlwaysCallBack alwaysCB);

extern RwInt32
RpAtomicGetPluginOffset(RwUInt32 pluginID);

extern RwInt32
RpClumpGetPluginOffset(RwUInt32 pluginID);

extern RwBool
RpAtomicValidatePlugins(const RpAtomic * atomic);

extern RwBool
RpClumpValidatePlugins(const RpClump * clump);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )
extern RwFrame *
RpAtomicGetFrame(const RpAtomic * atomic);

extern RwFrame *
RpClumpGetFrame(const RpClump * clump);

extern RpClump *
RpClumpSetFrame(RpClump * clump,
                RwFrame * frame);

/* Flags */
extern RpAtomic *
RpAtomicSetFlags(RpAtomic * atomic,
                 RwUInt32 flags);

extern RwUInt32
RpAtomicGetFlags(const RpAtomic * atomic);

extern RwSphere *
RpAtomicGetBoundingSphere(RpAtomic * atomic);

extern RwInt32
RpInterpolatorGetEndMorphTarget(const RpInterpolator * interpolator);

extern RwInt32
RpInterpolatorGetStartMorphTarget(const RpInterpolator * interpolator);

extern RwReal
RpInterpolatorGetValue(const RpInterpolator * interpolator);

extern RwReal
RpInterpolatorGetScale(const RpInterpolator * interpolator);

extern RpInterpolator *
RpInterpolatorSetEndMorphTarget(RpInterpolator * interpolator,
                                RwInt32 morphTarget,
                                RpAtomic * atomic);

extern RpInterpolator *
RpInterpolatorSetStartMorphTarget(RpInterpolator * interpolator,
                                  RwInt32 morphTarget,
                                  RpAtomic * atomic);

extern RpInterpolator *
RpInterpolatorSetValue(RpInterpolator *  interpolator,
                       RwReal value,
                       RpAtomic *atomic);

extern RpInterpolator *
RpInterpolatorSetScale(RpInterpolator * interpolator,
                       RwReal scale,
                       RpAtomic *atomic);

extern RpAtomic *
RpAtomicRender(RpAtomic * atomic);

/* Building clumps */
extern RpClump *
RpAtomicGetClump(const RpAtomic * atomic);

extern RpInterpolator *
RpAtomicGetInterpolator(RpAtomic * atomic);

extern RpGeometry *
RpAtomicGetGeometry(const RpAtomic * atomic);

extern void
RpAtomicSetRenderCallBack(RpAtomic * atomic,
                          RpAtomicCallBackRender callback);

extern RpAtomicCallBackRender
RpAtomicGetRenderCallBack(const RpAtomic * atomic);

#endif

/* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */

extern RwBool RpAtomicInstance(RpAtomic *atomic);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpClumpChunkInfoRead(stream, clumpChunkInfo, bytesRead) \
       _rpClumpChunkInfoRead(stream, clumpChunkInfo, bytesRead)


/*--- Automatically derived from: c:/daily/rwsdk/world/baworld.h ---*/

/*
 * World handling.
 * World give objects scope, and provide a mechanism for
 * efficiency static object rendering.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 *
 */

/****************************************************************************
 Defines
 */

/* Type ID */
#define rpWORLD 7

/* RpWorld private flags (in RwObject) */
enum RpWorldPrivateFlag
{
    rpWORLDSINGLEMALLOC = 0x01,
    rpWORLDPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldPrivateFlag RpWorldPrivateFlag;

/**
 * \ingroup rpworlddatatypes
 * The bit-field type \ref RpWorldFlag specifies the options available
 * for creating the static geometry component of a world (see API function \ref RpWorldSetFlags):
 */
enum RpWorldFlag
{
    rpWORLDTRISTRIP  = 0x01, /**<This world's meshes can be rendered
                                 as tri strips */
    rpWORLDPOSITIONS = 0x02, /**<This world has positions */
    rpWORLDTEXTURED  = 0x04, /**<This world has only one set of texture coordinates */
    rpWORLDPRELIT    = 0x08, /**<This world has luminance values */
    rpWORLDNORMALS   = 0x10, /**<This world has normals */
    rpWORLDLIGHT     = 0x20, /**<This world will be lit */
    rpWORLDMODULATEMATERIALCOLOR = 0x40, 
                             /**<Modulate material color with vertex colors 
                                 (pre-lit + lit) */
    rpWORLDTEXTURED2 = 0x80, /**<This world has 2 or more sets of texture coordinates */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpWorld.
     */

    rpWORLDNATIVE               = 0x01000000,
    rpWORLDNATIVEINSTANCE       = 0x02000000,

    rpWORLDFLAGSMASK            = 0x000000FF,
    rpWORLDNATIVEFLAGSMASK      = 0x0F000000,

    rpWORLDSECTORSOVERLAP       = 0x40000000,

    rpWORLDFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldFlag RpWorldFlag;

/* Multi texture coordinate format specifier */
#define rpWORLDTEXCOORDSETS(_num)  ((_num & 0xff) << 16)

/* Maximum depth of BSP tree */
#define rpWORLDMAXBSPDEPTH 64


/* macro/inline functionality */
#define RpWorldGetBBoxMacro(_world)                         \
    (&((_world)->boundingBox))

#define RpWorldGetOriginMacro(_world)                       \
    (&((_world)->worldOrigin))

#define RpWorldGetNumMaterialsMacro(_world)                 \
    ((_world)->matList.numMaterials)

#define RpWorldGetMaterialMacro(_world, _num)               \
    (((_world)->matList.materials)[(_num)])

#define RpWorldGetNumClumpsMacro(_world)                    \
    ((_world)->numClumpsInWorld)

#define RpWorldSetRenderOrderMacro(_world, _renderOrder)    \
    (((_world)->renderOrder = _renderOrder), (_world))

#define RpWorldGetRenderOrderMacro(_world)                  \
    ((_world)->renderOrder)

#define RpWorldSetFlagsMacro(_world, _flags)                \
    (((_world)->flags = (_flags)), (_world))

#define RpWorldGetFlagsMacro(_world)                        \
    ((_world)->flags)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpWorldGetBBox(_world)                              \
    RpWorldGetBBoxMacro(_world)

#define RpWorldGetOrigin(_world)                            \
    RpWorldGetOriginMacro(_world)

#define RpWorldGetNumMaterials(_world)                      \
    RpWorldGetNumMaterialsMacro(_world)

#define RpWorldGetMaterial(_world, _num)                    \
    RpWorldGetMaterialMacro(_world, _num)

#define RpWorldGetNumClumps(_world)                         \
    RpWorldGetNumClumpsMacro(_world)

#define RpWorldSetRenderOrder(_world, _renderOrder)         \
    RpWorldSetRenderOrderMacro(_world, _renderOrder)

#define RpWorldGetRenderOrder(_world)                       \
    RpWorldGetRenderOrderMacro(_world)

#define RpWorldSetFlags(_world, _flags)                     \
    RpWorldSetFlagsMacro(_world, _flags)

#define RpWorldGetFlags(_world)                             \
    RpWorldGetFlagsMacro(_world)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/****************************************************************************
 Global types
 */


/**
 * \ingroup rpworlddatatypes
 * \ref RpWorldRenderOrder
 * represents the options available for
 * the rendering order of world sectors in the camera's view frustum (see
 * API function \ref RpWorldSetRenderOrder).
 */
enum RpWorldRenderOrder
{
    rpWORLDRENDERNARENDERORDER = 0,
    rpWORLDRENDERFRONT2BACK,  /**<Renders nearest sectors first */
    rpWORLDRENDERBACK2FRONT, /**<Renders furthest sectors first */
    rpWORLDRENDERORDERFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldRenderOrder RpWorldRenderOrder;

/**
 * \ingroup rpworlddatatypes
 * \typedef RpWorldSectorCallBackRender
 * \ref RpWorldSectorCallBackRender represents the function called from
 * \ref RpWorldSectorRender when the specified world sector lies inside the
 * current camera's view frustum. The default callback initiates execution of
 * the world sector rendering pipeline. This function should return a pointer
 * to the world sector to indicate success
 *
 * \return Pointer to the world sector.
 *
 * \param  worldSector   Pointer to the world sector to be
 * rendered
 */
typedef RpWorldSector *(*RpWorldSectorCallBackRender) (RpWorldSector *
                                                       worldSector);

/**
 * \ingroup rpworlddatatypes
 * \typedef RpWorld
 * World object. This should be considered an opaque type.
 * Use the RpWorld API functions to access.
 */
typedef struct RpWorld RpWorld;

#if (!defined(DOXYGEN))
struct RpWorld
{
    RwObject            object;

    RwUInt32            flags;

    RpWorldRenderOrder  renderOrder;

    /* Materials */
    RpMaterialList      matList;

    /* The world stored as a BSP tree */
    RpSector           *rootSector;

    /* The number of texture coordinate sets in each sector */
    RwInt32             numTexCoordSets;

    /* Render frame used when last rendered */
    RwInt32             numClumpsInWorld;
    RwLLLink           *currentClumpLink;

    /* All the clumps in the world */
    RwLinkList          clumpList;

    /* All of the lights in the world */
    RwLinkList          lightList;

    /* Directional lights in the world */
    RwLinkList          directionalLightList;

    /* The worlds origin offset */
    RwV3d               worldOrigin;

    /* Bounding box around the whole world */
    RwBBox              boundingBox;

    /* Surface properties */
    RwSurfaceProperties surfaceProps;

    /* The callbacks functions */
    RpWorldSectorCallBackRender renderCallBack;

    RxPipeline         *pipeline;
};
#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Global Variables
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwPluginRegistry worldTKList;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwBool       _rpWorldFindBBox(RpWorld * world,
                                    RwBBox * boundingBox);

/* Generate sector bounding boxes from BSP planes (not tight boxes) */
extern RpWorld      *_rpWorldSetupSectorBoundingBoxes(RpWorld *world);


/* These stealth-API */
extern RwBool       _rpWorldForAllGlobalLights(RpLightCallBack callBack,
                                              void *pData);
extern RpWorldSector *_rpWorldSectorForAllLocalLights(RpWorldSector *
                                                     sector,
                                                     RpLightCallBack
                                                     callBack,
                                                     void *pData);

extern RpWorldSector *_rpSectorDefaultRenderCallBack(RpWorldSector *
                                                    sector);

/* Accessing worlds geometry */
extern RpWorld     *RpWorldLock(RpWorld * world);
extern RpWorld     *RpWorldUnlock(RpWorld * world);

/* Managing a list of the worlds */
extern void         _rpWorldRegisterWorld(RpWorld * world,
                                         RwUInt32 memorySize);
extern void         _rpWorldUnregisterWorld(RpWorld * world);

/* Hook into world management */
extern RwBool       RpWorldPluginAttach(void);

/* Enumerating objects in the world */
extern RpWorld     *RpWorldForAllClumps(RpWorld * world,
                                        RpClumpCallBack fpCallBack,
                                        void *pData);
extern RpWorld     *RpWorldForAllMaterials(RpWorld * world,
                                           RpMaterialCallBack fpCallBack,
                                           void *pData);
extern RpWorld     *RpWorldForAllLights(RpWorld * world,
                                        RpLightCallBack fpCallBack,
                                        void *pData);
extern RpWorld     *RpWorldForAllWorldSectors(RpWorld * world,
                                              RpWorldSectorCallBack
                                              fpCallBack, void *pData);

/* Rendering */
extern RpWorld     *RpWorldRender(RpWorld * world);

/* Creation/destruction */
extern RwBool       RpWorldDestroy(RpWorld * world);
extern RpWorld     *RpWorldCreate(RwBBox * boundingBox);
extern RwBool       RpWorldInstance(RpWorld *world);

/* Getting/setting */
extern RpWorld     *_rpWorldSetSurfaceProperties(RpWorld * world,
                                                const RwSurfaceProperties
                                                * surface);
extern const RwSurfaceProperties *
   _rpWorldGetSurfaceProperties(const RpWorld *world);

/* Sector callbacks */
extern RpWorld     *RpWorldSetSectorRenderCallBack(RpWorld * world,
                                                   RpWorldSectorCallBackRender
                                                   fpCallBack);
extern RpWorldSectorCallBackRender RpWorldGetSectorRenderCallBack(const
                                                                  RpWorld
                                                                  *
                                                                  world);

/* Getting world from sector */
extern RpWorld     *RpWorldSectorGetWorld(const RpWorldSector * sector);

extern RwInt32      RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                          RwPluginObjectConstructor
                                          constructCB,
                                          RwPluginObjectDestructor
                                          destructCB,
                                          RwPluginObjectCopy copyCB);
extern RwInt32      RpWorldRegisterPluginStream(RwUInt32 pluginID,
                                                RwPluginDataChunkReadCallBack
                                                readCB,
                                                RwPluginDataChunkWriteCallBack
                                                writeCB,
                                                RwPluginDataChunkGetSizeCallBack
                                                getSizeCB);
extern RwInt32      RpWorldSetStreamAlwaysCallBack(
                        RwUInt32 pluginID,
                        RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32      RpWorldSetStreamRightsCallBack(RwUInt32 pluginID,
                                     RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32      RpWorldGetPluginOffset(RwUInt32 pluginID);
extern RwBool       RpWorldValidatePlugins(RpWorld * world);


#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

/* Getting/setting */
extern const RwBBox *RpWorldGetBBox(const RpWorld *world);
extern const RwV3d *RpWorldGetOrigin(const RpWorld *world);

/* Accessing a worlds materials */
extern RwInt32 RpWorldGetNumMaterials(const RpWorld *world);
extern RpMaterial *RpWorldGetMaterial(const RpWorld *world, RwInt32 matNum);

/* Clumps */
extern RwInt32 RpWorldGetNumClumps(RpWorld *world);

/* Render order */
extern RpWorld *RpWorldSetRenderOrder(RpWorld *world,
                                      RpWorldRenderOrder renderOrder);
extern RpWorldRenderOrder RpWorldGetRenderOrder(const RpWorld *world);

/* Flags */
extern RpWorld *RpWorldSetFlags(RpWorld *world, RwUInt32 flags);
extern RwUInt32 RpWorldGetFlags(const RpWorld *world);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpWorldSetSurfaceProperties(_world, _surface) \
    _rpWorldSetSurfaceProperties(_world, _surface)

#define RpWorldGetSurfaceProperties(_world) \
    _rpWorldGetSurfaceProperties(_world)

#define rpWorldFindBBox(_world, _boundingBox) \
    _rpWorldFindBBox(_world, _boundingBox)

#define rpWorldForAllGlobalLights(_callBack, _pData) \
    _rpWorldForAllGlobalLights(_callBack, _pData)

#define rpWorldSectorForAllLocalLights(_sector, _callBack, _pData) \
    _rpWorldSectorForAllLocalLights(_sector, _callBack, _pData)

#define _rpWorldLock(_world) \
    RpWorldLock(_world)

#define _rpWorldUnlock(_world) \
    RpWorldUnlock(_world)

#define rpWorldLock(_world) \
    RpWorldLock(_world)

#define rpWorldUnlock(_world) \
    RpWorldUnlock(_world)


/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/d3d8/D3D8pipe.h ---*/

typedef struct RxD3D8ResEntryHeader RxD3D8ResEntryHeader;
/**
 * \ingroup rpworldd3d8
 * \struct RxD3D8ResEntryHeader
 * This structure contains D3D8 resource specific components.
 */
struct RxD3D8ResEntryHeader
{
    RwUInt16    serialNumber;   /**< The mesh headers serial number */
    RwUInt16    numMeshes;      /**< The number of meshes */
};

/* This is what I keep in memory as part of the instance data setup */
typedef struct RxD3D8InstanceData RxD3D8InstanceData;
/**
 * \ingroup rpworldd3d8
 * \struct RxD3D8InstanceData
 * This structure contains D3D8 resource specific components.
 */
struct RxD3D8InstanceData
{
    RwUInt32        minVert;        /**< The vertex index where the
                                         meshes vertices begin. Needed for
                                         reinstancing, not for rendering */

    RwInt32         stride;         /**< Stride of vertex */

    RwInt32         numVertices;    /**< Number of vertices in the vertex buffer */
    RwInt32         numIndices;     /**< Number of indices to render the primitive */

    RpMaterial      *material;      /**< The material for this instanced data */

    RwUInt32        vertexShader;   /**< Vertex shader or FVF flags */

    RwUInt32        primType;       /**< Primitive type */
    
    void            *indexBuffer;   /**< Index buffer */
    void            *vertexBuffer;  /**< Vertex buffer */

    RwUInt32        baseIndex;      /**< Needed if we share the vertex buffer */

    RwUInt8         vertexAlpha;    /**< The prelight data contains alpha */
    RwUInt8         managed;        /**< Created by the Vertex Buffer Manager */
    RwUInt8         remapped;       /**< Vertices where remapped to save VB space */
};

/**
 * \ingroup rpworldd3d8
 * \ref RxD3D8AllInOneInstanceCallBack callback function.
 * 
 * \param object Pointer to the object.
 * \param instancedData Pointer to \ref RxD3D8InstanceData.
 * \param reinstance Boolean whether to reinstance.
 *
 * \see RxD3D8AllInOneSetInstanceCallBack
 * \see RxD3D8AllInOneGetInstanceCallBack
 * \see RxNodeDefinitionGetD3D8AtomicAllInOne
 * \see RxNodeDefinitionGetD3D8WorldSectorAllInOne
 */
typedef RwBool (*RxD3D8AllInOneInstanceCallBack)(void *object,
                                                 RxD3D8InstanceData *instancedData,
                                                 RwBool reinstance);

/**
 * \ingroup rpworldd3d8
 * \ref RxD3D8AllInOneReinstanceCallBack callback function.
 * 
 * \param object Pointer to the object.
 * \param meshHeader Const pointer to \ref RpMeshHeader.
 * \param resEntry Pointer to \ref RxD3D8ResEntryHeader.
 * \param instanceCallback Pointer to \ref RxD3D8AllInOneInstanceCallBack.
 *
 * \see RxD3D8AllInOneSetReinstanceCallBack
 * \see RxD3D8AllInOneGetReinstanceCallBack
 * \see RxNodeDefinitionGetD3D8AtomicAllInOne
 * \see RxNodeDefinitionGetD3D8WorldSectorAllInOne
 */
typedef RwBool (*RxD3D8AllInOneReinstanceCallBack)(void *object,
                                                   RwResEntry *resEntry,
                                                   const RpMeshHeader *meshHeader,
                                                   RxD3D8AllInOneInstanceCallBack instanceCallback);

/**
 * \ingroup rpworldd3d8
 * \ref RxD3D8AllInOneLightingCallBack callback function.
 * 
 * \param object Void pointer to the object.
 *
 * \see RxD3D8AllInOneSetLightingCallBack
 * \see RxD3D8AllInOneGetLightingCallBack
 * \see RxNodeDefinitionGetD3D8AtomicAllInOne
 * \see RxNodeDefinitionGetD3D8WorldSectorAllInOne
 */
typedef void (*RxD3D8AllInOneLightingCallBack)(void *object);

/**
 * \ingroup rpworldd3d8
 * \ref RxD3D8AllInOneRenderCallBack callback function.
 * 
 * \param repEntry Pointer to a resource entry.
 * \param object Pointer to a object that the resource entry belongs to.
 * \param type rpATOMIC or rwSECTORATOMIC.
 * \param flags \ref RpGeometryFlag's or \ref RpWorldFlag's.
 *
 * \see RxD3D8AllInOneSetRenderCallBack
 * \see RxD3D8AllInOneGetRenderCallBack
 * \see RxNodeDefinitionGetD3D8AtomicAllInOne
 * \see RxNodeDefinitionGetD3D8WorldSectorAllInOne
 */
typedef void (*RxD3D8AllInOneRenderCallBack)(RwResEntry *repEntry,
                                             void *object,
                                             RwUInt8 type,
                                             RwUInt32 flags);

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */
extern void
RxD3D8AllInOneSetInstanceCallBack(RxPipelineNode *node,
                                  RxD3D8AllInOneInstanceCallBack callback);

extern RxD3D8AllInOneInstanceCallBack
RxD3D8AllInOneGetInstanceCallBack(RxPipelineNode *node);

extern void
RxD3D8AllInOneSetReinstanceCallBack(RxPipelineNode *node,
                                  RxD3D8AllInOneReinstanceCallBack callback);

extern RxD3D8AllInOneReinstanceCallBack
RxD3D8AllInOneGetReinstanceCallBack(RxPipelineNode *node);

extern void
RxD3D8AllInOneSetLightingCallBack(RxPipelineNode *node,
                                  RxD3D8AllInOneLightingCallBack callback);

extern RxD3D8AllInOneLightingCallBack
RxD3D8AllInOneGetLightingCallBack(RxPipelineNode *node);

extern void
RxD3D8AllInOneSetRenderCallBack(RxPipelineNode *node,
                                RxD3D8AllInOneRenderCallBack callback);

extern RxD3D8AllInOneRenderCallBack
RxD3D8AllInOneGetRenderCallBack(RxPipelineNode *node);


#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*--- Automatically derived from: C:/daily/rwsdk/world/pipe/p2/bapipew.h ---*/

#define RpWorldGetGenericSectorPipelineMacro() \
    (RXPIPELINEGLOBAL(genericWorldSectorPipeline))

#define RpWorldGetDefaultSectorPipelineMacro() \
    (RXPIPELINEGLOBAL(currentWorldSectorPipeline))

#define RpWorldSetSectorPipelineMacro(_world, _pipeline) \
    ( ((_world)->pipeline = _pipeline), _world )

#define RpWorldGetSectorPipelineMacro(_world, _pipeline) \
    ( (*(_pipeline) = (_world)->pipeline), _world )

#define RpWorldSectorSetPipelineMacro(_sector, _pipeline) \
    ( ((_sector)->pipeline = _pipeline), _sector )

#define RpWorldSectorGetPipelineMacro(_sector, _pipeline) \
    ( (*(_pipeline) = (_sector)->pipeline), _sector )

#define RpAtomicGetGenericPipelineMacro() \
    (RXPIPELINEGLOBAL(genericAtomicPipeline))

#define RpAtomicGetDefaultPipelineMacro() \
    (RXPIPELINEGLOBAL(currentAtomicPipeline))

#define RpAtomicSetPipelineMacro(_atomic, _pipeline) \
    ( ((_atomic)->pipeline = _pipeline), _atomic )

#define RpAtomicGetPipelineMacro(_atomic, _pipeline) \
    ( (*(_pipeline) = (_atomic)->pipeline), _atomic )

#define RpMaterialGetGenericPipelineMacro() \
    (RXPIPELINEGLOBAL(genericMaterialPipeline))

#define RpMaterialGetDefaultPipelineMacro() \
    (RXPIPELINEGLOBAL(currentMaterialPipeline))

#define RpMaterialSetPipelineMacro(_material, _pipeline) \
    ( ((_material)->pipeline = _pipeline), _material )

#define RpMaterialGetPipelineMacro(_material, _pipeline) \
    ( (*(_pipeline) = (_material)->pipeline), _material )


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpWorldGetGenericSectorPipeline RpWorldGetGenericSectorPipelineMacro
#define RpWorldGetDefaultSectorPipeline RpWorldGetDefaultSectorPipelineMacro
#define RpWorldSetSectorPipeline        RpWorldSetSectorPipelineMacro
#define RpWorldGetSectorPipeline        RpWorldGetSectorPipelineMacro
#define RpWorldSectorSetPipeline        RpWorldSectorSetPipelineMacro
#define RpWorldSectorGetPipeline        RpWorldSectorGetPipelineMacro

#define RpAtomicGetGenericPipeline      RpAtomicGetGenericPipelineMacro
#define RpAtomicGetDefaultPipeline      RpAtomicGetDefaultPipelineMacro
#define RpAtomicSetPipeline             RpAtomicSetPipelineMacro
#define RpAtomicGetPipeline             RpAtomicGetPipelineMacro

#define RpMaterialGetGenericPipeline    RpMaterialGetGenericPipelineMacro
#define RpMaterialGetDefaultPipeline    RpMaterialGetDefaultPipelineMacro
#define RpMaterialSetPipeline           RpMaterialSetPipelineMacro
#define RpMaterialGetPipeline           RpMaterialGetPipelineMacro

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RxPipeline       *RpWorldSetDefaultSectorPipeline(RxPipeline *pipeline);
extern RxPipeline       *RpAtomicSetDefaultPipeline(RxPipeline *pipeline);
extern RxPipeline       *RpMaterialSetDefaultPipeline(RxPipeline *pipeline);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

extern RxPipeline       *RpWorldGetGenericSectorPipeline(void);
extern RxPipeline       *RpWorldGetDefaultSectorPipeline(void);
extern RpWorld          *RpWorldSetSectorPipeline(RpWorld       *world,
                                                  RxPipeline    *pipeline);
extern RpWorld          *RpWorldGetSectorPipeline(RpWorld       *world,
                                                  RxPipeline   **pipeline);
extern RpWorldSector    *RpWorldSectorSetPipeline(RpWorldSector *sector,
                                                  RxPipeline    *pipeline);
extern RpWorldSector    *RpWorldSectorGetPipeline(RpWorldSector *sector,
                                                  RxPipeline   **pipeline);

extern RxPipeline       *RpAtomicGetGenericPipeline(void);
extern RxPipeline       *RpAtomicGetDefaultPipeline(void);
extern RpAtomic         *RpAtomicSetPipeline(RpAtomic             *atomic,
                                             RxPipeline           *pipeline);
extern const RpAtomic   *RpAtomicGetPipeline(const RpAtomic *const atomic, 
                                             RxPipeline          **pipeline);

extern RxPipeline       *RpMaterialGetGenericPipeline(void);
extern RxPipeline       *RpMaterialGetDefaultPipeline(void);
extern RpMaterial       *RpMaterialSetPipeline(RpMaterial  *material,
                                               RxPipeline  *pipeline);
extern RpMaterial       *RpMaterialGetPipeline(RpMaterial  *material,
                                               RxPipeline **pipeline);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern const RpGeometry *RpGeometryIsCorrectlySorted(const RpGeometry * geometry,
                                                     RwBool * result);
extern RpGeometry       *RpGeometrySortByMaterial(const RpGeometry * geometry,
                                                  RpGeometrySortByMaterialCallBack  callback);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* LEGACY-SUPPORT macros */
#define RpWorldGetGenericSectorInstancePipeline RpWorldGetGenericSectorPipeline
#define RpWorldSetDefaultSectorInstancePipeline RpWorldSetDefaultSectorPipeline
#define RpWorldGetDefaultSectorInstancePipeline RpWorldGetDefaultSectorPipeline
#define RpWorldSetSectorInstancePipeline        RpWorldSetSectorPipeline
#define RpWorldGetSectorInstancePipeline        RpWorldGetSectorPipeline
#define RpWorldSectorSetInstancePipeline        RpWorldSectorSetPipeline
#define RpWorldSectorGetInstancePipeline        RpWorldSectorGetPipeline

#define RpAtomicGetGenericInstancePipeline      RpAtomicGetGenericPipeline
#define RpAtomicGetDefaultInstancePipeline      RpAtomicGetDefaultPipeline
#define RpAtomicSetDefaultInstancePipeline      RpAtomicSetDefaultPipeline
#define RpAtomicSetInstancePipeline             RpAtomicSetPipeline
#define RpAtomicGetInstancePipeline             RpAtomicGetPipeline

#define RpMaterialGetGenericRenderPipeline      RpMaterialGetGenericPipeline
#define RpMaterialSetDefaultRenderPipeline      RpMaterialSetDefaultPipeline
#define RpMaterialGetDefaultRenderPipeline      RpMaterialGetDefaultPipeline
#define RpMaterialSetRenderPipeline             RpMaterialSetPipeline
#define RpMaterialGetRenderPipeline             RpMaterialGetPipeline


/*--- Automatically derived from: c:/daily/rwsdk/world/baworobj.h ---*/
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Adding and removing cameras to/from the world */
extern RpWorld *RpWorldRemoveCamera(RpWorld *world, RwCamera *camera);
extern RpWorld *RpWorldAddCamera(RpWorld *world, RwCamera *camera);
extern RpWorld *RwCameraGetWorld(const RwCamera *camera);

/* Adding and removing atomics to/from the world */
extern RpWorld *RpWorldRemoveAtomic(RpWorld *world, RpAtomic *atomic);
extern RpWorld *RpWorldAddAtomic(RpWorld *world, RpAtomic *atomic);
extern RpWorld *RpAtomicGetWorld(const RpAtomic *atomic);

/* Adding and removing clumps to/from the world */
extern RpWorld *RpWorldAddClump(RpWorld *world, RpClump *clump);
extern RpWorld *RpWorldRemoveClump(RpWorld *world, RpClump *clump);
extern RpWorld *RpClumpGetWorld(const RpClump *clump);

/* Adding and removing lights to/from the world */
extern RpWorld *RpWorldAddLight(RpWorld *world, RpLight *light);
extern RpWorld *RpWorldRemoveLight(RpWorld *world, RpLight *light);
extern RpWorld *RpLightGetWorld(const RpLight *light);

/* Finding whats in the view frustum */
extern RwCamera *RwCameraForAllClumpsInFrustum(RwCamera *camera, void *data);
extern RwCamera *RwCameraForAllClumpsNotInFrustum(RwCamera *camera,
                                                    RwInt32 numClumps, void *data);
extern RwCamera *RwCameraForAllSectorsInFrustum(RwCamera *camera,
                                                RpWorldSectorCallBack callBack,
                                                void *pData);

/* Enumeration involving the world sectors */
extern RpLight *RpLightForAllWorldSectors(RpLight *light,
                                          RpWorldSectorCallBack callback,
                                          void *data);
extern RpAtomic *RpAtomicForAllWorldSectors(RpAtomic *atomic,
                                            RpWorldSectorCallBack callback,
                                            void *data);
extern RpWorldSector *RpWorldSectorForAllAtomics(RpWorldSector *sector,
                                                 RpAtomicCallBack callback,
                                                 void *data);
extern RpWorldSector *RpWorldSectorForAllCollisionAtomics(RpWorldSector *sector,
                                                 RpAtomicCallBack callback,
                                                 void *data);
extern RpWorldSector *RpWorldSectorForAllLights(RpWorldSector *sector,
                                                RpLightCallBack callback,
                                                void *data);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: c:/daily/rwsdk/world/babinwor.h ---*/
/****************************************************************************
 Global types
 */

/* Binary Representation
 *
 */
typedef struct RpWorldChunkInfoSector RpWorldSectorChunkInfo;
typedef struct RpWorldChunkInfoSector _rpWorldSector;

struct RpWorldChunkInfoSector
{
    RwInt32 matListWindowBase;
    RwInt32 numPolygons;
    RwInt32 numVertices;
    RwV3d inf;
    RwV3d sup;
    RwBool collSectorPresent;
    RwBool unused;
};

typedef struct RpPlaneSectorChunkInfo RpPlaneSectorChunkInfo;
typedef struct RpPlaneSectorChunkInfo _rpPlaneSector;

struct RpPlaneSectorChunkInfo
{
    RwInt32 type;
    RwReal value;    
    RwBool leftIsWorldSector;
    RwBool rightIsWorldSector;
    RwReal leftValue;
    RwReal rightValue;
};

typedef struct RpWorldChunkInfo RpWorldChunkInfo;
typedef struct RpWorldChunkInfo _rpWorld;

struct RpWorldChunkInfo
{
    RwBool rootIsWorldSector;

    RwV3d invWorldOrigin;

    RwSurfaceProperties surfaceProps;

    RwInt32 numPolygons;
    RwInt32 numVertices;
    RwInt32 numPlaneSectors;
    RwInt32 numWorldSectors;
    RwInt32 colSectorSize;    

    RwInt32 format;  /* Flags about the world */
};

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Binary format */
extern RwUInt32 RpWorldStreamGetSize(const RpWorld *world);
extern RpWorld *RpWorldStreamRead(RwStream *stream);
extern const RpWorld *RpWorldStreamWrite(const RpWorld *world,
                                         RwStream *stream);
extern RpWorldSectorChunkInfo *
_rpWorldSectorChunkInfoRead(RwStream *stream,
                            RpWorldSectorChunkInfo *worldSectorChunkInfo,
                            RwInt32 *bytesRead);
extern RpPlaneSectorChunkInfo *
_rpPlaneSectorChunkInfoRead(RwStream *stream,
                            RpPlaneSectorChunkInfo *planeSectorChunkInfo,
                            RwInt32 *bytesRead);
extern RpWorldChunkInfo *
_rpWorldChunkInfoRead(RwStream *stream,
                      RpWorldChunkInfo *worldChunkInfo,
                      RwInt32 *bytesRead);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpWorldSectorChunkInfoRead(stream, worldSectorChunkInfo, bytesRead) \
       _rpWorldSectorChunkInfoRead(stream, worldSectorChunkInfo, bytesRead)

#define RpPlaneSectorChunkInfoRead(stream, planeSectorChunkInfo, bytesRead) \
       _rpPlaneSectorChunkInfoRead(stream, planeSectorChunkInfo, bytesRead)

#define RpWorldChunkInfoRead(stream, worldChunkInfo, bytesRead) \
       _rpWorldChunkInfoRead(stream, worldChunkInfo, bytesRead)

#endif /* RPWORLD_H */
