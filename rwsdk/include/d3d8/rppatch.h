
#ifndef RPPATCH_H
#define RPPATCH_H

/**
 * \defgroup rppatch RpPatch
 * \ingroup bezierpatches
 *
 * Bezier patch library
 *
 * This library provides efficient evaluation of patches.
 */

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include "rwcore.h"
#include "rpworld.h"

#include "rpcriter.h"
#include "rppatch.rpe"

/*===========================================================================*
 *--- Defines ---------------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rppatch
 * \def rpQUADPATCHNUMCONTROLPOINTS defines the number of control points in
 * a quadrilateral patch.
 *
 * \see RpQuadPatch
 * \see rpQUADPATCHNUMCONTROLINDICES
 * \see RpPatchMeshSetQuadPatch
 */
#define rpQUADPATCHNUMCONTROLPOINTS (16)

/**
 * \ingroup rppatch
 * \def rpTRIPATCHNUMCONTROLPOINTS defines the number of control points in
 * a triangular patch.
 *
 * \see RpTriPatch
 * \see rpTRIPATCHNUMCONTROLINDICES
 * \see RpPatchMeshSetTriPatch
 */
#define rpTRIPATCHNUMCONTROLPOINTS (10)

/**
 * \ingroup rppatch
 * \def rpQUADPATCHNUMCONTROLINDICES defines the number of control point
 * indices in a \ref RpQuadPatch quadrilateral patch.
 *
 * \see rpQUADPATCHNUMCONTROLPOINTS
 * \see RpPatchMeshSetQuadPatch
 */
#define rpQUADPATCHNUMCONTROLINDICES rpQUADPATCHNUMCONTROLPOINTS

/**
 * \ingroup rppatch
 * \def rpTRIPATCHNUMCONTROLINDICES defines the number of control points
 * indices in a \ref RpTriPatch triangular patch.
 *
 * \see rpTRIPATCHNUMCONTROLPOINTS
 * \see RpPatchMeshSetTriPatch
 */
#define rpTRIPATCHNUMCONTROLINDICES rpTRIPATCHNUMCONTROLPOINTS

/**
 * \ingroup rppatch
 * \def rpPATCHLODMAXVALUE defines the maximum value that can be returned for
 * the patch evaluation LOD.
 *
 * \see rpPATCHSKINLODMAXVALUE
 * \see rpPATCHLODMINVALUE
 * \see RpPatchLODCallBack
 */
#define rpPATCHLODMAXVALUE (20)

/**
 * \ingroup rppatch
 * \def rpPATCHSKINLODMAXVALUE defines the maximum value that can be returned
 * for the skinned patch evaluation LOD.
 *
 * \see rpPATCHLODMAXVALUE
 * \see rpPATCHLODMINVALUE
 * \see RpPatchLODCallBack
 */
#define rpPATCHSKINLODMAXVALUE (18)

/**
 * \ingroup rppatch
 * \def rpPATCHLODMINVALUE defines the minimum value that can be returned for
 * the patch evaluation LOD.
 *
 * \see rpPATCHSKINLODMAXVALUE
 * \see rpPATCHLODMAXVALUE
 * \see RpPatchLODCallBack
 */
#define rpPATCHLODMINVALUE (4)

/**
 * \ingroup rppatch
 * \def rpPATCHMESHTEXCOORDSETS Multi texture coordinate format specifier
 * for \ref RpPatchMeshCreate(). This should be OR'd into the
 * \ref RpPatchMeshFlag .
 */
#define rpPATCHMESHTEXCOORDSETS(_num)                                   \
    ((_num & 0xff) << 16)

/**
 * \ingroup rppatch
 * \def rpPATCHMESHLOCKTEXCOORDSIDX
 * Convenience macro for generating a texture coordinate lock flag.
 */
#define rpPATCHMESHLOCKTEXCOORDSIDX(_idx)                               \
    (rpPATCHMESHLOCKTEXCOORDS1 << (_idx))

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rppatch
 * \ref RpPatchMeshFlag
 * When creating a \ref RpPatchMesh, these flags can be OR'ed together to
 * specify the format along with the \ref rpPATCHMESHTEXCOORDSETS(num) macro
 * to specify the number of texture coordinate sets required.
 *
 * \see RpPatchMeshCreate
 */
enum RpPatchMeshFlag
{
    rpNAPATCHMESHFLAG      = 0,
    rpPATCHMESHPOSITIONS   = 0x01, /**<Patch mesh contains control point
                                       positions.                          */
    rpPATCHMESHNORMALS     = 0x02, /**<Patch mesh contains control point
                                       normals.                            */
    rpPATCHMESHPRELIGHTS   = 0x04, /**<Patch mesh contains control point
                                       pre-light color values.             */
    rpPATCHMESHTEXTURED    = 0x08, /**<Patch mesh is textured. The number
                                       of texture sets must also be
                                       defined.                            */
    rpPATCHMESHLIGHT       = 0x10, /**<Patch mesh will be lit.             */
    rpPATCHMESHMODULATEMATERIALCOLOR = 0x20,
                                   /**<Control point color will be
                                       modulated with the material color.  */
    rpPATCHMESHSMOOTHNORMALS = 0x40,
                                   /**<Patch mesh normals will be
                                       smoothed automatically.             */
    rpPATCHMESHFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPatchMeshFlag RpPatchMeshFlag;

/**
 * \ingroup rppatch
 * \ref RpPatchMeshLockMode patch mesh lock flags.
 *
 * \see rpPATCHMESHLOCKTEXCOORDSIDX
 */
enum RpPatchMeshLockMode
{
    rpNAPATCHMESHLOCKMODE       = 0,
    rpPATCHMESHLOCKPATCHES      = 0x0001, /**<Lock the mesh patches.       */
    rpPATCHMESHLOCKPOSITIONS    = 0x0002, /**<Lock the control point
                                              positions.                   */
    rpPATCHMESHLOCKNORMALS      = 0x0004, /**<Lock the control point
                                              normals.                     */
    rpPATCHMESHLOCKPRELIGHTS    = 0x0008, /**<Lock the control point
                                              pre-light color values.      */
    rpPATCHMESHLOCKTEXCOORDS1   = 0x0100, /**<Lock the texture coordinates
                                              set 1.                       */
    rpPATCHMESHLOCKTEXCOORDS2   = 0x0200, /**<Lock the texture coordinates
                                              set 2.                       */
    rpPATCHMESHLOCKTEXCOORDS3   = 0x0400, /**<Lock the texture coordinates
                                              set 3.                       */
    rpPATCHMESHLOCKTEXCOORDS4   = 0x0800, /**<Lock the texture coordinates
                                              set 4.                       */
    rpPATCHMESHLOCKTEXCOORDS5   = 0x1000, /**<Lock the texture coordinates
                                              set 5.                       */
    rpPATCHMESHLOCKTEXCOORDS6   = 0x2000, /**<Lock the texture coordinates
                                              set 6.                       */
    rpPATCHMESHLOCKTEXCOORDS7   = 0x4000, /**<Lock the texture coordinates
                                              set 7.                       */
    rpPATCHMESHLOCKTEXCOORDS8   = 0x8000, /**<Lock the texture coordinates
                                              set 8.                       */
    rpPATCHMESHLOCKTEXCOORDSALL = 0xff00, /**<Lock all texture coordinate
                                              sets.                        */
    rpPATCHMESHLOCKALL          = 0xffff, /**<Combination of all the
                                              above.                       */
    rpPATCHMESHLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPatchMeshLockMode RpPatchMeshLockMode;

typedef struct RpPatchMeshDefinition RpPatchMeshDefinition;
/**
 * \ingroup rppatch
 * \struct RpPatchMeshDefinition
 * holds the definition sizes of the patch mesh. This data should be considered
 * read only.
 */
struct RpPatchMeshDefinition
{
    RwUInt32 flag;             /**<Patch mesh definition flag.            */
    RwUInt32 numControlPoints; /**<Number of control points.              */
    RwUInt32 numTriPatches;    /**<Number of tri patches.                 */
    RwUInt32 numQuadPatches;   /**<Number of quad patches.                */
    RwUInt32 numTexCoordSets;  /**<Number of sets of texture coordinates. */
};

typedef struct RpPatchMesh RpPatchMesh;
/**
 * \ingroup rppatch
 * \struct RpPatchMesh
 * holds the control point data for a patch mesh. The patch mesh should be
 * created with \ref RpPatchMeshCreate. The patch mesh should be locked with
 * \ref RpPatchMeshLock before the data is edited. Quadrilateral and triangle
 * patches can be defined from the control points with
 * \ref RpPatchMeshSetQuadPatch and \ref RpPatchMeshSetTriPatch respectively.
 * The patch mesh should be unlocked with \ref RpPatchMeshUnlock before it is
 * added to an \ref RpAtomic with \ref RpPatchAtomicSetPatchMesh.
 *
 * \see RpPatchMeshDefinition
 */
struct RpPatchMesh
{
    RwV3d       *positions;           /**<Control point positions.           */
    RwV3d       *normals;             /**<Control point normals.             */
    RwRGBA      *preLightColors;      /**<Control point pre-light colors.    */
    RwTexCoords *texCoords[rwMAXTEXTURECOORDS];
                                      /**<Control point texture coordinates. */
    RpPatchMeshDefinition definition; /**<Patch mesh definition data.        */
};

typedef struct RpQuadPatch RpQuadPatch;
/**
 * \ingroup rppatch
 * \struct RpQuadPatch
 * holds the control point indices for a quadrilateral patch. There are
 * \ref rpQUADPATCHNUMCONTROLINDICES indices for a quadrilateral patch.
 *
 * \see RpPatchMeshSetQuadPatch
 */
struct RpQuadPatch
{
    RwUInt32 cpIndices[rpQUADPATCHNUMCONTROLINDICES]; /**<Control point
                                                          indices. */
};

typedef struct RpTriPatch RpTriPatch;
/**
 * \ingroup rppatch
 * \struct RpTriPatch
 * holds the control point indices for a triangle patch. There are
 * \ref rpTRIPATCHNUMCONTROLINDICES indices for a triangular patch.
 *
 * \see RpPatchMeshSetTriPatch
 */
struct RpTriPatch
{
    RwUInt32 cpIndices[rpTRIPATCHNUMCONTROLINDICES]; /**<Control point
                                                         indices. */
};

typedef struct RpPatchLODRange RpPatchLODRange;
/**
 * \ingroup rppatch
 * \struct RpPatchLODRange
 * holds the variables used by the default atomic LOD call back function.
 */
struct RpPatchLODRange
{
    RwUInt32 minLod; /**<Minimum LOD value. */
    RwUInt32 maxLod; /**<Maximum LOD value. */
    RwReal minRange; /**<Minimum LOD range. */
    RwReal maxRange; /**<Maximum LOD range. */
};

/**
 * \ingroup rppatch
 * \ref RpPatchLODUserData
 * typedef for the user data passed to the \ref RpPatchLODCallBack
 * function which calculates the atomics' LOD.
 *
 * \see RpPatchAtomicSetPatchLODCallBack
 * \see RpPatchAtomicGetPatchLODCallBack
 */
typedef void *RpPatchLODUserData;

/**
 * \ingroup rppatch
 * \ref RpPatchLODCallBack
 * typedef for the patch atomic LOD calculation function.
 *
 * \param atomic
 * \param userData
 *
 * \return
 *
 * \see RpPatchAtomicSetPatchLODCallBack
 * \see RpPatchAtomicGetPatchLODCallBack
 */
typedef RwUInt32 (* RpPatchLODCallBack)( RpAtomic *atomic,
                                         RpPatchLODUserData userData );

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
extern void
RpPatchGeometrySetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
RpPatchAtomicSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );


extern RwBool
RpPatchPluginAttach(void);

/*---------------------------------------------------------------------------*
 *-   Patch Mesh functions                                                  -*
 *---------------------------------------------------------------------------*/
extern RpPatchMesh *
RpPatchMeshCreate( RwUInt32 numQuadPatches,
                   RwUInt32 numTriPatches,
                   RwUInt32 numControlPoints,
                   RwUInt32 definitionFlag );

extern RwBool
RpPatchMeshDestroy( RpPatchMesh *patchMesh );

extern RpPatchMesh *
RpPatchMeshLock( RpPatchMesh *patchMesh,
                 RwUInt32 lockMode );

extern RpPatchMesh *
RpPatchMeshUnlock( RpPatchMesh *patchMesh );

/*---------------------------------------------------------------------------*
 *-   Patch mesh helper functions                                           -*
 *---------------------------------------------------------------------------*/

extern RpPatchMesh *
RpPatchMeshTransform( RpPatchMesh *patchMesh,
                      const RwMatrix *matrix );

/*---------------------------------------------------------------------------*/
#define RpPatchMeshGetFlagsMacro(patchMesh)                                 \
    (patchMesh->definition.flag)

#define RpPatchMeshSetFlagsMacro(patchMesh, flags)                          \
    (patchMesh->definition.flag = flags)

#define RpPatchMeshGetNumControlPointsMacro(patchMesh)                      \
    (patchMesh->definition.numControlPoints)

#define RpPatchMeshGetNumTriPatchesMacro(patchMesh)                         \
    (patchMesh->definition.numTriPatches)

#define RpPatchMeshGetNumQuadPatchesMacro(patchMesh)                        \
    (patchMesh->definition.numQuadPatches)

#define RpPatchMeshGetNumTexCoordSetsMacro(patchMesh)                       \
    (patchMesh->definition.numTexCoordSets)

#define RpPatchMeshGetPositionsMacro(patchMesh)                             \
    (patchMesh->positions)

#define RpPatchMeshGetNormalsMacro(patchMesh)                               \
    (patchMesh->normals)

#define RpPatchMeshGetPreLightColorsMacro(patchMesh)                        \
    (patchMesh->preLightColors)

#define RpPatchMeshGetTexCoordsMacro(patchMesh, index)                      \
    (patchMesh->texCoords[index - 1])
/*---------------------------------------------------------------------------*/

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

/*---------------------------------------------------------------------------*/
extern RwUInt32
RpPatchMeshGetFlags( const RpPatchMesh *patchMesh );

extern RpPatchMesh *
RpPatchMeshSetFlags( RpPatchMesh *patchMesh,
                     RwUInt32 flags );

extern RwUInt32
RpPatchMeshGetNumControlPoints( const RpPatchMesh *patchMesh );

extern RwUInt32
RpPatchMeshGetNumTriPatches( const RpPatchMesh *patchMesh );

extern RwUInt32
RpPatchMeshGetNumQuadPatches( const RpPatchMesh *patchMesh );

extern RwUInt32
RpPatchMeshGetNumTexCoordSets( const RpPatchMesh *patchMesh );

extern RwV3d *
RpPatchMeshGetPositions( const RpPatchMesh *patchMesh );

extern RwV3d *
RpPatchMeshGetNormals( const RpPatchMesh *patchMesh );

extern RwRGBA *
RpPatchMeshGetPreLightColors( const RpPatchMesh *patchMesh );

extern RwTexCoords *
RpPatchMeshGetTexCoords( const RpPatchMesh *patchMesh,
                         RwTextureCoordinateIndex index );
/*---------------------------------------------------------------------------*/

#else /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/*---------------------------------------------------------------------------*/
#define RpPatchMeshGetFlags(patchMesh)                                      \
    RpPatchMeshGetFlagsMacro(patchMesh)

#define RpPatchMeshSetFlags(patchMesh, flags)                               \
    RpPatchMeshSetFlagsMacro(patchMesh, flags)

#define RpPatchMeshGetNumControlPoints(patchMesh)                           \
    RpPatchMeshGetNumControlPointsMacro(patchMesh)

#define RpPatchMeshGetNumTriPatches(patchMesh)                              \
    RpPatchMeshGetNumTriPatchesMacro(patchMesh)

#define RpPatchMeshGetNumQuadPatches(patchMesh)                             \
    RpPatchMeshGetNumQuadPatchesMacro(patchMesh)

#define RpPatchMeshGetNumTexCoordSets(patchMesh)                            \
    RpPatchMeshGetNumTexCoordSetsMacro(patchMesh)

#define RpPatchMeshGetPositions(patchMesh)                                  \
    RpPatchMeshGetPositionsMacro(patchMesh)

#define RpPatchMeshGetNormals(patchMesh)                                    \
    RpPatchMeshGetNormalsMacro(patchMesh)

#define RpPatchMeshGetPreLightColors(patchMesh)                             \
    RpPatchMeshGetPreLightColorsMacro(patchMesh)

#define RpPatchMeshGetTexCoords(patchMesh, index)                           \
    RpPatchMeshGetTexCoordsMacro(patchMesh, index)
/*---------------------------------------------------------------------------*/

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/*---------------------------------------------------------------------------*
 *-   Patch streaming functions                                             -*
 *---------------------------------------------------------------------------*/
extern RwUInt32
RpPatchMeshStreamGetSize( const RpPatchMesh *patchMesh );

extern RpPatchMesh *
RpPatchMeshStreamRead( RwStream *stream );

extern const RpPatchMesh *
RpPatchMeshStreamWrite( const RpPatchMesh *patchMesh,
                        RwStream *stream );

/*---------------------------------------------------------------------------*
 *-   Patch Mesh patch functions                                            -*
 *---------------------------------------------------------------------------*/
extern RpPatchMesh *
RpPatchMeshSetQuadPatch( RpPatchMesh *patchMesh,
                         RwUInt32 quadIndex,
                         RpQuadPatch *quadPatch );

extern RpPatchMesh *
RpPatchMeshSetTriPatch( RpPatchMesh *patchMesh,
                        RwUInt32 triIndex,
                        RpTriPatch *triPatch );

extern const RpQuadPatch *
RpPatchMeshGetQuadPatch( const RpPatchMesh *patchMesh,
                         RwUInt32 quadIndex );

extern const RpTriPatch *
RpPatchMeshGetTriPatch( const RpPatchMesh *patchMesh,
                        RwUInt32 triIndex );

/*---------------------------------------------------------------------------*
 *-   Patch Mesh material functions                                         -*
 *---------------------------------------------------------------------------*/
extern RpPatchMesh *
RpPatchMeshSetQuadPatchMaterial( RpPatchMesh *patchMesh,
                                 RwUInt32 quadIndex,
                                 RpMaterial *material );

extern RpPatchMesh *
RpPatchMeshSetTriPatchMaterial( RpPatchMesh *patchMesh,
                                RwUInt32 triIndex,
                                RpMaterial *material );

extern RpMaterial *
RpPatchMeshGetQuadPatchMaterial( const RpPatchMesh *patchMesh,
                                 RwUInt32 quadIndex );

extern RpMaterial *
RpPatchMeshGetTriPatchMaterial( const RpPatchMesh *patchMesh,
                                RwUInt32 triIndex );

extern const RpPatchMesh *
RpPatchMeshForAllMaterials( const RpPatchMesh *patchMesh,
                            RpMaterialCallBack callBack,
                            void *userData );

extern RwUInt32
RpPatchMeshGetNumMaterials( const RpPatchMesh *patchMesh );

extern RpMaterial *
RpPatchMeshGetMaterial( const RpPatchMesh *patchMesh,
                        RwUInt32 materialIndex );

/*---------------------------------------------------------------------------*
 *-   Patch Skin functions                                                  -*
 *---------------------------------------------------------------------------*/
#if (defined(RPSKIN_H))

extern RpSkin *
RpPatchMeshGetSkin( RpPatchMesh *patchMesh );

extern RpPatchMesh *
RpPatchMeshSetSkin( RpPatchMesh *patchMesh,
                    RpSkin *skin );

#endif /* (defined(RPSKIN_H)) */

/*---------------------------------------------------------------------------*
 *-   Patch Atomic functions                                                -*
 *---------------------------------------------------------------------------*/
extern RpAtomic *
RpPatchAtomicSetPatchMesh( RpAtomic *atomic,
                           RpPatchMesh *patchMesh );

extern RpPatchMesh *
RpPatchAtomicGetPatchMesh( const RpAtomic *atomic );

/*---------------------------------------------------------------------------*
 *-   Patch Atomic LOD functions                                            -*
 *---------------------------------------------------------------------------*/
extern RwBool
RpPatchAtomicSetPatchLODCallBack( RpAtomic *atomic,
                                  RpPatchLODCallBack callback,
                                  RpPatchLODUserData userData );

extern RwBool
RpPatchAtomicGetPatchLODCallBack( const RpAtomic *atomic,
                                  RpPatchLODCallBack *callback,
                                  RpPatchLODUserData *userData );

/*---------------------------------------------------------------------------*
 *-   Patch default LOD range                                               -*
 *---------------------------------------------------------------------------*/
extern RwBool
RpPatchSetDefaultLODCallBackRange( RpPatchLODRange *lodRange );

extern RwBool
RpPatchGetDefaultLODCallBackRange( RpPatchLODRange *lodRange );

/*---------------------------------------------------------------------------*
 *-   Patch pipeline                                                        -*
 *---------------------------------------------------------------------------*/

/**
 * \ingroup rppatch
 * \ref RpPatchType defines the different ways a patch atomic can be rendered.
 * Once a \ref RpPatchMesh has been attached to an \ref RpAtomic with
 * \ref RpPatchAtomicSetPatchMesh the atomic must be setup with the correct
 * rendering pipeline with \ref RpPatchAtomicSetType .
 *
 * The patch plugin makes no assumptions about how to render the
 * patch atomics. Once an \ref RpPatchMesh has been attached to an
 * \ref RpAtomic it is necessary to attach a suitable patch
 * rendering pipeline. The patch plugin supports four different
 * rendering types, these are defined in the \ref RpPatchType
 * enumeration:-
 * \li \ref rpPATCHTYPEGENERIC
 *          The patch \ref RpAtomic will be rendered with the
 *          default generic patch rendering pipeline.
 * \li \ref rpPATCHTYPESKIN
 *          The patch \ref RpAtomic will be rendered with a
 *          custom pipeline for rendering skinning patches. Make sure
 *          an \ref RpSkin has been attached to the \ref RpPatchMesh
 *          and an \ref RpHAnimHierarchy has been attached to the
 *          \ref RpAtomic.
 * \li \ref rpPATCHTYPEMATFX
 *          The patch \ref RpAtomic will be rendered with a
 *          custom pipeline for rendering the material effects
 *          of patches. The
 *          patch matfx pipeline supports all the material effects
 *          defined in the \ref rpmatfx plugin. The patches
 *          materials should be setup as usual.
 * \li \ref rpPATCHTYPESKINMATFX
 *          The patch \ref RpAtomic will be rendered with a
 *          custom skinned material effects patch rendering pipeline.
 *          The \ref RpPatchMesh, \ref RpAtomic and the patches'
 *          \ref RpMaterial's must be setup correctly.
 */
enum RpPatchType
{
    rpNAPATCHTYPE        = 0, /**<Invalid patch pipeline.                   */
    rpPATCHTYPEGENERIC   = 1, /**<Generic patch rendering.                  */
    rpPATCHTYPESKIN      = 2, /**<Skinned patch rendering.                  */
    rpPATCHTYPEMATFX     = 3, /**<Material effects patch rendering.         */
    rpPATCHTYPESKINMATFX = 4, /**<Skinned material effects patch rendering. */
    rpPATCHTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPatchType RpPatchType;

extern RpAtomic *
RpPatchAtomicSetType( RpAtomic *atomic,
                      RpPatchType type );

extern RpPatchType
RpPatchAtomicGetType( const RpAtomic *atomic );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

/*---- start: ./d3d8/patchplatform.h----*/

/**
 * \defgroup rppatchd3d8 D3D8
 * \ingroup rppatch
 *
 * D3D8 patch pipeline extension.
 */


/*===========================================================================*
 *--- D3D8 Defines -----------------------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- D3D8 Global Types ------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rppatchd3d8
 * \ref RpPatchD3D8Pipeline rendering pipelines available within the
 * \ref rppatch plugin. Use \ref RpPatchGetD3D8Pipeline to retrieve
 * the \ref RxPipeline s.
 */
enum RpPatchD3D8Pipeline
{
    rpPATCHD3D8PIPELINEGENERIC      = 0, /**<D3D8 generic
                                            patch rendering pipeline.        */
    rpPATCHD3D8PIPELINEMATFX        = 1, /**<D3D8 material effect
                                            (single set of texture coordinates)
                                            patch rendering pipeline.        */
    rpPATCHD3D8PIPELINESKINNED      = 2, /**<D3D8 skinned
                                            patch rendering pipeline.        */
    rpPATCHD3D8PIPELINESKINMATFX    = 3, /**<D3D8 skinned material effect
                                            (single set of texture coordinates)
                                            patch rendering pipeline.        */
    rpPATCHD3D8PIPELINEMAX,
    rpPATCHD3D8PIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpPatchD3D8Pipeline RpPatchD3D8Pipeline;

/*===========================================================================*
 *--- D3D8 Plugin API Functions ----------------------------------------------*
 *===========================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/*---------------------------------------------------------------------------*/

extern RxPipeline *
RpPatchGetD3D8Pipeline( RpPatchD3D8Pipeline d3d8Pipeline );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

/*---- end: ./d3d8/patchplatform.h----*/

#endif /* RPPATCH_H */


