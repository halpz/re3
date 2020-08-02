
/**
 * \defgroup rtltmap RtLtMap
 * \ingroup lighting
 *
 * Lightmap Generation Toolkit for RenderWare.
 */

#ifndef RTLTMAP_H
#define RTLTMAP_H

/*===========================================================================*
 *--- Includes --------------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"

#include "rpltmap.h"


/**
 * \ingroup rtltmap
 * \ref RtLtMapIlluminateSampleCallBack is the callback to be called, from
 * within \ref RtLtMapIlluminate, for groups of samples in the objects
 * currently being illuminated.
 *
 * For lightmapped objects, samples are grouped on a per-polygon basis and
 * for vertex-lit objects, samples are grouped on a per-object basis (see
 * \ref RtLtMapObjectFlags).
 *
 * This callback will receive an array of color values to fill in, each
 * representing one sample in the current object - this may correspond to
 * a texel in the current object's lightmap or the prelight color of a
 * vertex, depending on whether the object is lightmapped and/or vertex-lit.
 * It will receive positions (in world-space) for each sample and the normal
 * vector (again, in world-space) of each sample (normals are interpolated
 * across polygons for non-flat-shaded materials. See \ref RtLtMapMaterialFlags).
 * For lightmap samples (not vertex-lighting samples), it will receive
 * barycentric coordinates within the current polygon.  It will also receive
 * a list of RpLights affecting the current object.
 *
 * The barycentric coordinates may be used, for example, to allow a callback
 * to easily import existing lighting data (e.g from previously generated
 * lightmaps in a different format, or from an art package with lighting
 * functionality).
 *
 * NOTE: The alpha channel of the RwRGBA results array must NOT be modified.
 * These values are used internally and their modification may result in
 * unwanted visual artifacts in the resulting lighting solution.
 *
 * The default RtLtMapIlluminateSampleCallBacks supplied with RtLtMap is
 * \ref RtLtMapDefaultSampleCallBack. This callback performs point and area
 * lighting (the area lights use are those passed to \ref RtLtMapIlluminate).
 *
 * \param  results          A pointer to an array of \ref RwRGBA sample color values
 * \param  samplePositions  A pointer to an array of \ref RwV3d values specifying the
 *                          world-space positions of each of the samples in the results array
 * \param  baryCoords       A pointer to an array of \ref RwV3d values specifying the
 *                          barycentric coordinates (within the current polygon) of
 *                          each of the samples in the results array
 * \param  numSamples       The length of the results, samplePositions, baryCoords and normals arrays
 * \param  lights           An array of pointers to \ref RpLight's affecting the current object
 * \param  numLights        The length of the lights array
 * \param  normals          A pointer to an array of \ref RwV3d values specifying the
 *                          world-space, unit normals of each of the samples in the results array
 *
 * \return A pointer to the results array on success, NULL otherwise
 *
 * \see RtLtMapIlluminate
 * \see RtLtMapIlluminateVisCallBack
 * \see RtLtMapIlluminateProgressCallBack
 */
typedef RwRGBA *(*RtLtMapIlluminateSampleCallBack)(RwRGBA        *results,
                                                   RwV3d         *samplePositions,
                                                   RwV3d         *baryCoords,
                                                   RwUInt32       numSamples,
                                                   RpLight      **lights,
                                                   RwUInt32       numLights,
                                                   RwV3d         *normals);

/**
 * \ingroup rtltmap
 * \ref RtLtMapIlluminateVisCallBack is the callback to be called, from
 * within \ref RtLtMapIlluminate, to determine the visibility between a
 * sample and a light.
 *
 * This callback is called for all samples in the current
 * \ref RtLtMapLightingSession and for each light source which may
 * potentially affect each of those samples (this may not be all the
 * lights in the scene, as some hierarchical culling is performed).
 * Each sample may represent a texel in the current object's lightmap
 * or the prelight color of a vertex, depending on whether the object
 * is lightmapped and/or vertex-lit (see \ref RtLtMapObjectFlags).
 *
 * The callback will receive a pointer to the world of the current
 * \ref RtLtMapLightingSession (this may be used to perform intersection
 * tests), the world-space position of the sample, the world-space
 * position of the light, a pointer to a light and a pointer to an
 * \ref RwRGBAReal result value.
 *
 * If the light pointer is NULL, this means that the current light
 * is an area light (as opposed to an \ref RpLight), of an internal
 * format. The area lights use are those passed to \ref RtLtMapIlluminate.
 *
 * The callback should return FALSE to signify that the light is wholly
 * occluded w.r.t the sample position, otherwise it should return TRUE.
 * Partial degrees of (color-frequency-dependent) occlusion may be
 * expressed by modifying the RwRGBAReal value. This defaults to bright
 * white but may be reduced to signify that the light from the light
 * source should be attenuated. This could be used to take into account
 * light-filtering objects in the scene (such as colored glass or fog).
 *
 * The default RtLtMapIlluminateVisCallBack supplied with RtLtMap is
 * \ref RtLtMapDefaultVisCallBack. This callback performs visibility
 * tests using the line-intersection tests from \ref rtintersection. It tests
 * for occlusion by RpWorldSectors and RpAtomics and it respects the
 * relevant \ref RtLtMapObjectFlags and \ref RtLtMapMaterialFlags but it
 * does not filter light; visibility is determined to be either one or zero.
 *
 * \param  world      The world of the current RtLtMapLightingSession
 * \param  result     An RwRGBAReal value to attentuate this light's
 *                    contribution to the current sample
 * \param  samplePos  The world-space positiuon of the sample
 * \param  lightPos   The world-space positiuon of the light
 * \param  light      A pointer to the light (NULL if it is an are light)
 *
 * \return TRUE if the light is visible from the sample, FALSE if it is occluded
 *
 * \see RtLtMapIlluminate
 * \see RtLtMapIlluminateSampleCallBack
 * \see RtLtMapIlluminateProgressCallBack
 */
typedef RwBool (*RtLtMapIlluminateVisCallBack)(RpWorld    *world,
                                               RwRGBAReal *result,
                                               RwV3d      *samplePos,
                                               RwV3d      *lightPos,
                                               RpLight    *light);

/**
 * \ingroup rtltmap
 * \ref RtLtMapIlluminateProgressCallBack is the callback to be called, from
 * within \ref RtLtMapIlluminate, to allow a user to track lighting progress.
 *
 * The progress callback will be called at several stages during lighting,
 * with a different 'message' parameter value used at each stage (see
 * \ref RtLtMapProgressMessage). It will be called at the very start of
 * lighting (for a given \ref RtLtMapLightingSession), before any samples
 * are lit. It will also be called at the very end of lighting, after all
 * samples have been lit. It will be called before and after each lighting
 * 'slice' (see \ref RtLtMapIlluminate) and also after each group of
 * samples have been lit.
 *
 * For lightmapped objects, samples are grouped on a per-polygon basis and
 * for vertex-lit objects, samples are grouped on a per-object basis (see
 * \ref RtLtMapObjectFlags).
 *
 * The progress callback will receive a RwReal value specifying the percentage
 * of samples already lit in the current \ref RtLtMapLightingSession (see
 * \ref RtLtMapLightingSessionGetNumSamples).
 *
 * By returning FALSE, the progress callback may cause early termination of
 * the current lighting 'slice' (this may be used, for example, to keep
 * the time spent lighting each slice fairly constant).
 *
 * There is no default progress callback supplied with RtLtMap.
 *
 * \param  message  A \ref RtLtMapProgressMessage identifying the stage
 *                  of the current call to the progress callback
 * \param  value    The percentage of samples already lit in the
 *                  current \ref RtLtMapLightingSession
 *
 * \return FALSE to immediately terminate lighting, otherwise TRUE
 *
 * \see RtLtMapIlluminate
 * \see RtLtMapIlluminateSampleCallBack
 * \see RtLtMapIlluminateVisCallBack
 */
typedef RwBool (*RtLtMapIlluminateProgressCallBack)(RwInt32 message,
                                                    RwReal value);


/**
 * \ingroup rtltmap
 * \ref RtLtMapProgressMessage is an enumerated type identifying the different
 * stages at which the \ref RtLtMapIlluminateProgressCallBack may be called
 * from within \ref RtLtMapIlluminate.
 *
 * \see RtLtMapIlluminateProgressCallBack
 * \see RtLtMapIlluminate
 */
enum RtLtMapProgressMessage
{
    rtLTMAPPROGRESSNAMESSAGE = 0,

    rtLTMAPPROGRESSSTART      = 1, /**< This is issued at the beginning of
                                    *   an incremental lighting session */
    rtLTMAPPROGRESSSTARTSLICE = 2, /**< This is issued at the beginning of every
                                    *   slice in an incremental lighting session */
    rtLTMAPPROGRESSUPDATE     = 3, /**< This is issued after the lighting of each
                                    *   lightmapped triangle or vertex-lit object */
    rtLTMAPPROGRESSENDSLICE   = 4, /**< This is issued at the end of every slice
                                    *   in an incremental lighting session */
    rtLTMAPPROGRESSEND        = 5, /**< This is issued at the end of an
                                    *   incremental lighting session */

    rtLTMAPPROGRESSFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RtLtMapProgressMessage RtLtMapProgressMessage;

typedef struct RtLtMapLightingSession RtLtMapLightingSession;
/**
 * \ingroup rtltmap
 * \struct RtLtMapLightingSession
 * The RtLtMapLightingSession structure holds information to be passed to
 * \ref RtLtMapIlluminate. It is used to parameterize the lighting process.
 *
 * The RtLtMapLightingSession structure encapsulates a set of objects and
 * keeps track of the proportion of samples, within that set, that have already
 * been lit by calls to \ref RtLtMapIlluminate. Each call performs lighting for
 * one 'slice' of the whole 'session'. If the camera member is non-NULL, it is
 * important that the camera is not moved between lighting slices.
 *
 * The RtLtMapLightingSession is also passed to
 * \ref RtLtMapLightMapsCreate, \ref RtLtMapLightMapsClear,
 * \ref RtLtMapLightMapsDestroy and \ref RtLtMapAreaLightGroupCreate,
 * though not all of the session structure's member will be used in
 * each of these cases.
 *
 * \see RtLtMapIlluminate
 * \see RtLtMapLightMapsCreate
 * \see RtLtMapLightMapsClear
 * \see RtLtMapLightMapsDestroy
 * \see RtLtMapAreaLightGroupCreate
 */
struct RtLtMapLightingSession
{
    RpWorld        *world;       /**< This world is that in which collisions are performed
                                  *   during illumination (for the purposes of lighting
                                  *   visibility determination) */
    RwCamera       *camera;      /**< An optional pointer to a camera. The camera's frustum
                                  *   may be used to cull objects and/or triangles from the
                                  *   set of those to be processed. */
    RpWorldSector **sectorList;  /**< An optional array of \ref RpWorldSector pointers,
                                  *   specifying which sectors in the world to light. If
                                  *   this is NULL, then all sectors in the world (or those
                                  *   inside the optional camera's frustum) will be lit. */
    RwInt32         numSectors;  /**< The length of the sectorList array. If this is set to
                                  *   '-1' then none of the sectors in the world will be lit. */
    RpAtomic      **atomicList;  /**< An optional array of \ref RpAtomic pointers,
                                  *   specifying which atomics to light. If this is NULL
                                  *   then all atomics in the world  (or those inside the
                                  *   optional camera's frustum) will be lit. */
    RwInt32         numAtomics;  /**< The length of the atomicList array. If this is set to
                                  *   '-1' then none of the atomics in the world will be lit. */
    RwUInt32        startSample; /**< Lighting for the current 'slice' should begin with this
                                  *   sample. It is the user's responsibility to increment this
                                  *   value after each slice. Note that partial lighting is
                                  *   quantized to be per-polygon (for lightmapped objects).
                                  *   startSample will always be rounded down, not up. */
    RwUInt32        numSamples;  /**< This specifies how many lightmap samples should be lit.
                                  *   If it is left zero then all samples in the current set
                                  *   of objects will be lit. Note that partial lighting is
                                  *   quantized to be per-polygon (for lightmapped objects).
                                  *   numSamples will always be rounded up, not down. */
    RwUInt32        totalSamples;/**< This specifies how many lightmap samples will be lit in
                                  *   total for the world specified (this is filled in by
                                  *   \ref RtLtMapIlluminate, not the calling function). */
    RtLtMapIlluminateSampleCallBack   sampleCallBack;   /**< A \ref RtLtMapIlluminateSampleCallBack
                                                         *     to use during lighting. If this is left
                                                         *     NULL, the default callback will be used. */
    RtLtMapIlluminateVisCallBack      visCallBack;      /**< A \ref RtLtMapIlluminateVisCallBack
                                                         *     to use during lighting. If this is left
                                                         *     NULL, the default callback will be used. */
    RtLtMapIlluminateProgressCallBack progressCallBack; /**< A \ref RtLtMapIlluminateProgressCallBack
                                                         *     to use during lighting. If this is left
                                                         *     NULL, no progress callback will be used. */
};

/**
 * \ingroup rtltmap
 * \ref RtLtMapMaterialFlags is an enumerated type specifying the different
 * lightmap-related flags which may be applied to materials. These values
 * will be taken into consideration within \ref RtLtMapIlluminate.
 *
 * \see RtLtMapMaterialGetFlags
 * \see RtLtMapMaterialSetFlags
 * \see RtLtMapMaterialGetAreaLightColor
 * \see RtLtMapMaterialSetAreaLightColor
 * \see RtLtMapMaterialGetLightMapDensityModifier
 * \see RtLtMapMaterialSetLightMapDensityModifier
 * \see RtLtMapMaterialGetAreaLightDensityModifier
 * \see RtLtMapMaterialSetAreaLightDensityModifier
 * \see RtLtMapMaterialSetAreaLightRadiusModifier
 * \see RtLtMapMaterialGetAreaLightRadiusModifier
 * \see RtLtMapIlluminate
 * \see RtLtMapAreaLightGroupCreate
 * \see RtLtMapIlluminateVisCallBack
 */
enum RtLtMapMaterialFlags
{
    rtLTMAPMATERIALNAFLAG      = 0,

    rtLTMAPMATERIALLIGHTMAP    = 1,  /**< This material should be lightmapped
                                      *   [for non-lightmapped materials within lightmapped objects,
                                      *    texel values will be set to (0, 0, 0) (or (255, 255, 255) if
                                      *    the rtLTMAPMATERIALAREALIGHT flag is present, so that light-
                                      *    emitting textures appear as bright as the light which they are
                                      *    emittering) and the mesh may be 'shrunk' in UV-space so as not
                                      *    to waste lightmap texels] */
    rtLTMAPMATERIALAREALIGHT   = 2,  /**< This material is an area light emitter
                                      *   (see \ref RtLtMapAreaLightGroupCreate) */
    rtLTMAPMATERIALNOSHADOW    = 4,  /**< This material does not block light */
    rtLTMAPMATERIALSKY         = 8,  /**< This material blocks everything but directional
                                      *   lights, to allow sky polygons to occlude geometry
                                      *   and yet emit directional light (sky or sun light,
                                      *   being as if cast from an infinite distance) */
    rtLTMAPMATERIALFLATSHADE   = 16, /**< This material will be lit as if flat-shaded
                                      *   (polygon normals will be used during illumination) */

    rtLTMAPMATERIALFLAGFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RtLtMapMaterialFlags RtLtMapMaterialFlags;

/**
 * \ingroup rtltmap
 * RtLtMapObjectFlags is an enumerated type specifying the different
 * lightmap-related flags which may be applied to world sectors and
 * atomics. These values will be taken into consideration within
 * \ref RtLtMapLightMapsCreate and \ref RtLtMapIlluminate.
 *
 * \see RtLtMapAtomicGetFlags
 * \see RtLtMapAtomicSetFlags
 * \see RtLtMapWorldSectorGetFlags
 * \see RtLtMapWorldSectorSetFlags
 * \see RtLtMapLightMapsCreate
 * \see RtLtMapIlluminate
 * \see RtLtMapIlluminateVisCallBack
 */
enum RtLtMapObjectFlags
{
    rtLTMAPOBJECTNAFLAG = 0,

    rtLTMAPOBJECTLIGHTMAP    = 1, /**< This object is to be lightmapped */
    rtLTMAPOBJECTVERTEXLIGHT = 2, /**< This object's vertex prelight colors should
                                       be lit within \ref RtLtMapIlluminate. */
    rtLTMAPOBJECTNOSHADOW    = 4, /**< This object does not cast shadows (useful, for
                                       example, for moving objects for which dynamic
                                       shadows are to be rendered - such as doors) */

    rtLTMAPOBJECTFLAGFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RtLtMapObjectFlags RtLtMapObjectFlags;

/* Area-lighting stuff:*
 ***********************/


typedef struct RtLtMapAreaLightGroup RtLtMapAreaLightGroup;

/**
 * \ingroup rtltmap
 * \struct RtLtMapAreaLightGroup
 * RtLtMapAreaLightGroup is a structure which acts as a container
 * for area lights created by a call to \ref RtLtMapAreaLightGroupCreate.
 * The containers may be chained and passed to \ref RtLtMapIlluminate.
 * Each container has an optional pointer to a RwFrame which is used to
 * transform the contained area lights relative to the world of the current
 * \ref RtLtMapLightingSession and relative to each other (such that, for
 * example, lights from multiple worlds, which are connected by portals,
 * or which are composed of atomics and not world sectors, may be used
 * within a single call to \ref RtLtMapIlluminate).
 *
 * \see RtLtMapAreaLightGroupCreate
 * \see RtLtMapAreaLightGroupDestroy
 * \see RtLtMapIlluminate
 * \see RtLtMapIlluminateVisCallBack
 */
struct RtLtMapAreaLightGroup
{
    RwSList *meshes; /**< A list of hierarchically-grouped area lights */
    RwFrame *frame;  /**< An (optional) pointer to a frame (owned by something else)
                      *   whose LTM specifies the coordinate system of this container,
                      *   relative to the world of the current \ref RtLtMapLightingSession. */
    RtLtMapAreaLightGroup *next; /**< A pointer for chaining are light groups together */
};

/* Area light triangles are grouped by source mesh (this may change) */
typedef struct LtMapAreaLightMesh LtMapAreaLightMesh;

#if (!defined(DOXYGEN))
struct LtMapAreaLightMesh
{
    RwUInt32        flags;      /* To hold hierarchical visibility culling flags,
                                 * relevant to the object/triangle *currently* being lit. */
    RpMaterial     *material;   /* The emitter material, containing color, etc */
    RwSphere        sphere;     /* Each mesh has an associated center and radius */
    RwReal          ROI;        /* Centered on the above sphere, the R.O.I. of the
                                 * samples in this mesh (a conservative estimate) */
    RwSList        *triangles;  /* A list of the area light triangles in this mesh */
};

/* Area light samples are grouped by source triangle */
typedef struct LtMapAreaLight LtMapAreaLight;
struct LtMapAreaLight
{
    RwUInt16 flags;         /* To hold hierarchical visibility culling flags,
                             * relevant to the object/triangle *currently* being lit. */
    RwUInt16 numSamples;    /* Number of area light samples in this triangle */
    RwReal   areaPerSample; /* (triangleArea / numSamples) for this triangle */
    RwPlane  plane;         /* This 'area light' is a triangle, this is its plane. */
    RwSphere sphere;        /* This bounds the triangle's points in world-space (it's
                             * not worth storing 3 points, coarse culling is fine) */
    RwV3d   *lights;        /* Array of area light sample positions (in world-space) */
};
#endif /* (!defined(DOXYGEN)) */

#if (defined(SKY2_DRVMODEL_H) || defined(NULLSKY_DRVMODEL_H))

/**
 * \ingroup rtltmapps2
 * \ref RtLtMapSkyLumCalcCallBack is the callback to be called, from
 * within \ref RtLtMapSkyBaseTextureProcess, to allow a user to select the
 * function to process the textures for rendering on the PlayStation 2.
 *
 * The function is called for each span of a full color image, or for the
 * CLUT in a palettised image, to compute the luminance and stores it in
 * the alpha component of the texel.
 *
 * \param  scanline  A pointer to a scanline of \ref RwRGBA data.
 * \param  width     Width of the scanline, in pixels.
 *
 * \return A pointer to the scanline on success, NULL otherwise.
 *
 * \see RtLtMapSkyBaseTextureProcess
 * \see RtLtMapSkyLightingSessionBaseTexturesProcess
 * \see RtLtMapSkyLightMapMakeDarkMap
 * \see RtLtMapSkyLumCalcMaxCallBack
 * \see RtLtMapSkyLumCalcSigmaCallBack
 * \see RtLtMapSkySetLumCalcCallBack
 * \see RtLtMapSkyGetLumCalcCallBack
 */
typedef RwRGBA *(*RtLtMapSkyLumCalcCallBack)(RwRGBA *scanline,
                                             RwUInt32 width );

#endif /* (defined(SKY2_DRVMODEL_H) || defined(NULLSKY_DRVMODEL_H)) */


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/* Lightmap creation functionality: */
extern RtLtMapLightingSession *
RtLtMapLightMapsCreate(RtLtMapLightingSession *session,
                       RwReal density, RwRGBA *color);

extern void
RtLtMapLightMapsDestroy(RtLtMapLightingSession *session);
extern RpAtomic *
RtLtMapAtomicLightMapDestroy(RpAtomic *atomic);
extern RpWorldSector *
RtLtMapWorldSectorLightMapDestroy(RpWorldSector *sector);

extern RwReal
RtLtMapGetVertexWeldThreshold(void);
extern RwBool
RtLtMapSetVertexWeldThreshold(RwReal threshold);

extern RwUInt32
RtLtMapLightMapGetDefaultSize(void);
extern RwBool
RtLtMapLightMapSetDefaultSize(RwUInt32 size);

extern RwUInt32
RtLtMapAtomicGetLightMapSize(RpAtomic *atomic);
extern RpAtomic *
RtLtMapAtomicSetLightMapSize(RpAtomic *atomic, RwUInt32 size);
extern RwUInt32
RtLtMapWorldSectorGetLightMapSize(RpWorldSector *sector);
extern RpWorldSector *
RtLtMapWorldSectorSetLightMapSize(RpWorldSector *sector, RwUInt32 size);

extern RwUInt32
RtLtMapAtomicGetFlags(RpAtomic *atomic);
extern RpAtomic *
RtLtMapAtomicSetFlags(RpAtomic *atomic, RwUInt32 flags);
extern RwUInt32
RtLtMapWorldSectorGetFlags(RpWorldSector *sector);
extern RpWorldSector *
RtLtMapWorldSectorSetFlags(RpWorldSector *sector, RwUInt32 flags);


/* Lightmap illumination functionality: */
extern RwUInt32
RtLtMapIlluminate(RtLtMapLightingSession *session,
                  RtLtMapAreaLightGroup  *lights);

extern RwReal
RtLtMapGetSliverAreaThreshold(void);
extern RwBool
RtLtMapSetSliverAreaThreshold(RwReal threshold);

extern RwRGBA *
RtLtMapDefaultSampleCallBack(RwRGBA        *results,
                             RwV3d         *samplePositions,
                             RwV3d * __RWUNUSED__ baryCoords,
                             RwUInt32       numSamples,
                             RpLight      **lights,
                             RwUInt32       numLights,
                             RwV3d         *normals);

extern RwBool
RtLtMapDefaultVisCallBack(RpWorld    *world,
                          RwRGBAReal __RWUNUSED__ *result,
                          RwV3d      *samplePos,
                          RwV3d      *lightPos,
                          RpLight __RWUNUSED__ *light);

extern void
RtLtMapSetVisCallBackCollisionScalar(RwReal scalar);

extern RwReal
RtLtMapGetVisCallBackCollisionScalar(void);

extern RtLtMapLightingSession *
RtLtMapLightingSessionInitialize(RtLtMapLightingSession *session,
                                 RpWorld *world);

extern RwInt32
RtLtMapLightingSessionGetNumSamples(RtLtMapLightingSession *session);
extern RwInt32
RtLtMapWorldSectorGetNumSamples(RpWorldSector *sector);
extern RwInt32
RtLtMapAtomicGetNumSamples(RpAtomic *atomic);

extern RtLtMapLightingSession *
RtLtMapImagesPurge(RtLtMapLightingSession *session);
extern RpAtomic *
RtLtMapAtomicImagePurge(RpAtomic *atomic);
extern RpWorldSector *
RtLtMapWorldSectorImagePurge(RpWorldSector *sector);

extern RtLtMapLightingSession *
RtLtMapLightMapsClear(RtLtMapLightingSession *session, RwRGBA *color);
extern RpAtomic *
RtLtMapAtomicLightMapClear(RpAtomic *atomic, RwRGBA *color);
extern RpWorldSector *
RtLtMapWorldSectorLightMapClear(RpWorldSector *sector, RwRGBA *color);


/* Material/area-lighting functionality: */
extern RtLtMapAreaLightGroup *
RtLtMapAreaLightGroupCreate(RtLtMapLightingSession *session, RwReal density);
extern RwBool
RtLtMapAreaLightGroupDestroy(RtLtMapAreaLightGroup *lights);

extern RwUInt32
RtLtMapMaterialGetFlags(RpMaterial *material);
extern RpMaterial *
RtLtMapMaterialSetFlags(RpMaterial *material, RwUInt32 flags);

extern RwReal
RtLtMapMaterialGetLightMapDensityModifier(RpMaterial *material);
extern RpMaterial *
RtLtMapMaterialSetLightMapDensityModifier(RpMaterial *material, RwReal modifier);

extern RwRGBA
RtLtMapMaterialGetAreaLightColor(RpMaterial *material);
extern RpMaterial *
RtLtMapMaterialSetAreaLightColor(RpMaterial *material, RwRGBA color);

extern RwReal
RtLtMapMaterialGetAreaLightDensityModifier(RpMaterial *material);
extern RpMaterial *
RtLtMapMaterialSetAreaLightDensityModifier(RpMaterial *material, RwReal modifier);

extern RwReal
RtLtMapMaterialGetAreaLightRadiusModifier(RpMaterial *material);
extern RpMaterial *
RtLtMapMaterialSetAreaLightRadiusModifier(RpMaterial *material, RwReal modifier);

extern RwUInt32
RtLtMapGetMaxAreaLightSamplesPerMesh(void);
extern RwBool
RtLtMapSetMaxAreaLightSamplesPerMesh(RwUInt32 maxSamples);
extern RwReal
RtLtMapGetAreaLightDensityModifier(void);
extern RwBool
RtLtMapSetAreaLightDensityModifier(RwReal modifier);
extern RwReal
RtLtMapGetAreaLightRadiusModifier(void);
extern RwBool
RtLtMapSetAreaLightRadiusModifier(RwReal modifier);
extern RwReal
RtLtMapGetAreaLightErrorCutoff(void);
extern RwBool
RtLtMapSetAreaLightErrorCutoff(RwReal tolerance);


/* Texture-saving functionality: */
extern RwTexDictionary *
RtLtMapTexDictionaryCreate(RtLtMapLightingSession *session);

extern const RwChar *
RtLtMapGetDefaultPrefixString(void);
extern RwBool
RtLtMapSetDefaultPrefixString(RwChar *string);

extern RwUInt32
RtLtMapGetLightMapCounter(void);
extern RwBool
RtLtMapSetLightMapCounter(RwUInt32 value);


#if (defined(SKY2_DRVMODEL_H) || defined(NULLSKY_DRVMODEL_H))

/* PS2-specific functionality: */
extern RwTexture *RtLtMapSkyLightMapMakeDarkMap(RwTexture *lightMap);

extern RwTexture *RtLtMapSkyBaseTextureProcess(RwTexture *texture);
extern RpAtomic  *RtLtMapSkyAtomicBaseTexturesProcess(RpAtomic *atomic);
extern RpWorldSector *
RtLtMapSkyWorldSectorBaseTexturesProcess(RpWorldSector *sector);
extern RtLtMapLightingSession *
RtLtMapSkyLightingSessionBaseTexturesProcess(RtLtMapLightingSession *session);

extern RwRGBA *RtLtMapSkyLumCalcMaxCallBack( RwRGBA *scanline, RwUInt32 width );
extern RwRGBA *RtLtMapSkyLumCalcSigmaCallBack( RwRGBA *scanline, RwUInt32 width );

extern RwBool RtLtMapSkySetLumCalcCallBack(RtLtMapSkyLumCalcCallBack cback);
extern RtLtMapSkyLumCalcCallBack RtLtMapSkyGetLumCalcCallBack( void );

#endif /* (defined(SKY2_DRVMODEL_H) || defined(NULLSKY_DRVMODEL_H)) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RTLTMAP_H */


