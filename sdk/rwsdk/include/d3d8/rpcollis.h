
/*****************************************************************************
 *
 * File :     rpcollis.h
 *
 * Abstract : World collision plugin for Renderware.
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

#ifndef RPCOLLIS_H
#define RPCOLLIS_H

/* Doxygen plugin groups. */

/**
 * \defgroup rpcollis RpCollision
 * \ingroup collisiondetection
 *
 * Collision Plugin for RenderWare Graphics.
 */

/******************************************************************************
 *  Include files
 */

#include <rwcore.h>
#include <rpworld.h>

#include "rpcollis.rpe"    /* automatically generated header file */

/******************************************************************************
 *  Global Types
 */

/**
 * \ingroup rpcollis
 * RpIntersectType, this type represents the different types of
 * primitives that can be used to intersect with an object (for example, see
 * \ref RpCollisionWorldForAllIntersections):
 */
enum RpIntersectType
{
    rpINTERSECTNONE = 0,
    rpINTERSECTLINE,   /**<Line Intersection */
    rpINTERSECTPOINT,  /**<Point Intersection */
    rpINTERSECTSPHERE, /**<Sphere Intersection */
    rpINTERSECTBOX,    /**<Box intersection */
    rpINTERSECTATOMIC, /**<Atomic Intersection based on bounding sphere */
    rpINTERSECTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpIntersectType RpIntersectType;

typedef union RpIntersectData RpIntersectData;
/**
 * \ingroup rpcollis
 * RpIntersectData, this union type is used to specify the parameters
 * for an intersection primitive of the desired type (\ref RpIntersectType)
 */
union RpIntersectData
{
    RwLine              line;       /**<For type rpINTERSECTLINE */
    RwV3d               point;      /**<For type rpINTERSECTPOINT */
    RwSphere            sphere;     /**<For type rpINTERSECTSPHERE */
    RwBBox              box;        /**<For type rpINTERSECTBOX */
    void               *object;     /**<For type rpINTERSECTATOMIC - this
                                     * should hold a pointer to the atomic */
};

typedef struct RpIntersection RpIntersection;
/**
 * \ingroup rpcollis
 * \struct  RpIntersection
 * Intersection Object.  This type represents data for an
 * intersection primitive.  It specifies the intersection type
 * (line, sphere, etc.) (type) and parameters describing the given type (t):
 */
struct RpIntersection
{
    RpIntersectData     t; /**< Intersection data. Union type - one
                            * of line, point, sphere or RW object */
    RpIntersectType     type; /**< Intersection type - see
                               * \ref RpIntersectType */
};

typedef struct RpCollisionTriangle RpCollisionTriangle;
/**
 * \ingroup rpcollis
 * \struct RpCollisionTriangle
 * A structure representing a  collision between
 * an \ref RpIntersection primitive and a triangle.
 * The collision is specified by the triangle's plane normal
 * (normal), the first triangle vertex (point), an index to the triangle in
 * the object geometry's triangle list (index) and the positions of the
 * triangle's vertices (vertices). Note all vector components are in object
 * space.
 *
 * \see RpCollisionWorldForAllIntersections
 * \see RpCollisionGeometryForAllIntersections
 * \see RpAtomicForAllIntersections
 * \see RpIntersectionCallBackWorldTriangle
 * \see RpIntersectionCallBackGeometryTriangle
 */
struct RpCollisionTriangle
{
    RwV3d      normal; /**< Triangle normal */
    RwV3d      point;  /**< First triangle vertex */
    RwInt32    index;  /**< Index of triangle in object (if applicable) */
    RwV3d      *vertices[3]; /**< Pointers to three triangle vertices */
};

typedef struct RpCollisionBuildParam  RpCollisionBuildParam;
/**
 * \ingroup rpcollis
 * \struct RpCollisionBuildParam
 * This structure is a place-holder for parameters that may be
 * introduced in future to control the generation of collision data when using
 * the functions \ref RpCollisionWorldSectorBuildData, 
 * \ref RpCollisionWorldBuildData or \ref RpCollisionGeometryBuildData.
 * Currently, a NULL pointer should be passed to these functions, as no
 * parameters are defined. If parameters are introduced, a NULL pointer will
 * indicate that default values should be used.
 */
struct RpCollisionBuildParam
{
    RwInt32     dummy;  /**< Not used */
};

/**
 * \ingroup rpcollis
 * \ref RpIntersectionCallBackWorldTriangle represents the function called
 * from \ref RpCollisionWorldForAllIntersections for all intersections between
 * the specified primitive and the static geometry in a given world. This
 * function should return a pointer to the current collision triangle to
 * indicate success. The callback may return NULL to terminate further
 * callbacks on the world.
 *
 * \note The memory pointed to by collTriangle is stored on the stack. 
 * This memory should be considered volatile. To use this data outside
 * of the iterator, copy the contents.
 *
 * \param  intersection   Pointer to the intersection primitive.
 * \param  sector   Pointer to the world sector containing the triangle.
 * \param  collTriangle   Pointer to the \ref RpCollisionTriangle representing
 *              the triangle in the world's static geometry that is intersected.
 * \param  distance   The distance to the intersection point(s).
 * Note that the distance returned depends on the intersection type and is
 * normalized for the given intersection primitive.
 *  \li rpINTERSECTLINE  Distance from start of line to collision
 *              triangle, normalized to length of line.
 *  \li rpINTERSECTSPHERE  Distance of sphere's center from the collision
 *              triangle along the direction of the normal, and normalized
 *              to the sphere's radius (may be negative if the sphere center
 *              is behind the triangle's plane with respect to the direction
 *              of the normal).
 *  \li rpINTERSECTBOX  Distance is undefined.
 *  \li rpINTERSECTATOMIC  Distance of atomic's bounding-sphere center
 *              from the collision triangle along the direction of the normal
 *              and normalized to sphere's radius.
 * \param  data   User defined data pointer
 *
 * \return Pointer to the current collision triangle.
 */
typedef RpCollisionTriangle *(*RpIntersectionCallBackWorldTriangle)
    (RpIntersection * intersection,
     RpWorldSector * sector,
     RpCollisionTriangle * collTriangle, RwReal distance, void *data);

/**
 * \ingroup rpcollis
 * \ref RpIntersectionCallBackAtomic represents the function called from
 * \ref RpWorldForAllAtomicIntersections for all intersections between the
 * specified primitive and collision atomics in a given world. This function
 * should return the current atomic to indicate success. The callback may
 * return NULL to terminate further callbacks on the world.
 *
 * \param  intersection   Pointer to the intersection primitive.
 * \param  sector   Pointer to the world sector containing
 *                   the intersected triangles.
 * \param  atomic   Pointer to the intersected atomic.
 * \param  distance   The collision distance. The distance returned
 * depends on the intersection type which is defined in \ref RpIntersectType.
 *  \li rpINTERSECTPOINT   Distance of point from atomic's bounding
 *      sphere center, normalized to sphere's radius.
 *  \li rpINTERSECTLINE   Distance of atomic's bounding-sphere center from
 *      start of line, projected onto the line, normalized to length of line.
 *      Note that by this definition, if the line starts or ends inside the
 *      sphere, this distance maybe negative or greater than one.
 *  \li rpINTERSECTSPHERE  Distance of atomic's bounding-sphere center
 *      from sphere's center, normalized to sum of spheres' radii.
 *  \li rpINTERSECTBOX  Distance undefined.
 *  \li rpINTERSECTATOMIC  Distance between atomics' bounding-sphere
 *      centers, normalized to sum of spheres' radii.
 * \param  data   User defined data pointer.
 *
 * \return Pointer to the current atomic.
 */
typedef RpAtomic   *(*RpIntersectionCallBackAtomic)
    (RpIntersection * intersection,
     RpWorldSector * sector, RpAtomic * atomic, RwReal distance, void *data);

/**
 * \ingroup rpcollis
 * \ref RpIntersectionCallBackWorldSector represents the function called from
 * \ref RpWorldForAllWorldSectorIntersections for all intersections between the
 * specified primitive and world sectors in a given world. This function should
 * return the current world sector to indicate success. The callback may return
 * NULL to terminate further callbacks on the world.
 *
 * \param  intersection   Pointer to the intersection primitive.
 * \param  sector   Pointer to the world sector containing the intersected
 *                  polygons.
 * \param  data   User defined data pointer
 *
 * \return Pointer to the current world sector.
 */
typedef RpWorldSector *(*RpIntersectionCallBackWorldSector)
    (RpIntersection * intersection, RpWorldSector * worldSector, void *data);

/**
 * \ingroup rpcollis
 * \ref RpIntersectionCallBackGeometryTriangle represents the function called
 * from \ref RpAtomicForAllIntersections and
 * \ref RpCollisionGeometryForAllIntersections
 * for all intersections between the specified primitive and a given atomic.
 * This function should return a pointer to the current collision triangle to
 * indicate success. The callback may return NULL to terminate further
 * callbacks on the atomic.
 *
 * Note that the vertices and normal of the collision triangle are given
 * in the coordinate space of the geometry. If they are required in world
 * coordinates, they must be transformed using \ref RwV3dTransformPoints and
 * \ref RwV3dTransformVectors with the LTM of the atomic's frame. This must
 * be passed via the user-defined data if required.
 *
 * \param  intersection   Pointer to the intersection primitive.
 * \param  collTri   Pointer to the \ref RpCollisionTriangle
 *              representing the triangle in the atomic that is intersected.
 * \param  distance   The distance to the intersection point(s).
 * Note that the distance returned depends on the intersection type and is
 * normalized for the given intersection primitive.
 *  \li rpINTERSECTLINE   Distance from start of line to collision
 *      triangle, normalized to length of line.
 *  \li rpINTERSECTSPHERE  Distance of sphere's center from the collision
 *              triangle along the direction of the normal, and normalized
 *              to the sphere's radius (may be negative if the sphere center
 *              is behind the triangle's plane with respect to the direction
 *              of the normal).
 *  \li rpINTERSECTATOMIC   Distance of atomic's bounding-sphere center
 *      from the collision triangle along the direction of the normal, and
 *      normalized to sphere's radius.
 * \param  data   User defined data pointer
 *
 * \return Pointer to the current collision triangle.
 */
typedef RpCollisionTriangle *(*RpIntersectionCallBackGeometryTriangle)
    (RpIntersection *intersection, RpCollisionTriangle *collTriangle,
    RwReal distance, void *data);


/******************************************************************************
 *  Plugin API Functions
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Plugin attachment */
extern RwBool
RpCollisionPluginAttach(void);

/* World collisions */
extern RpWorldSector *
RpCollisionWorldSectorBuildData(
    RpWorldSector           *worldSector,
    RpCollisionBuildParam   *param);

extern RpWorldSector *
RpCollisionWorldSectorDestroyData(
    RpWorldSector           *worldSector);

extern RwBool
RpCollisionWorldSectorQueryData(
    RpWorldSector           *worldSector);

extern RpWorld *
RpCollisionWorldBuildData(
    RpWorld                 *world,
    RpCollisionBuildParam   *param);

extern RpWorld *
RpCollisionWorldDestroyData(
    RpWorld                 *world);

extern RwBool
RpCollisionWorldQueryData(
    RpWorld                 *world);


extern RpWorld *
RpWorldForAllWorldSectorIntersections(
    RpWorld                 *world,
    RpIntersection          *intersection,
    RpIntersectionCallBackWorldSector callBack,
    void                    *data);

extern RpWorld *
RpWorldForAllAtomicIntersections(
    RpWorld                 *world,
    RpIntersection          *intersection,
    RpIntersectionCallBackAtomic callBack,
    void                    *data);

extern RpWorld *
RpCollisionWorldForAllIntersections(
    RpWorld                 *world,
    RpIntersection          *intersection,
    RpIntersectionCallBackWorldTriangle callBack,
    void                    *data);

/* Geometry and atomic collisions */
extern RpGeometry *
RpCollisionGeometryBuildData(
    RpGeometry              *geometry,
    RpCollisionBuildParam   *param);

extern RwBool
RpCollisionGeometryQueryData(
    RpGeometry              *geometry);

extern RpGeometry *
RpCollisionGeometryDestroyData(
    RpGeometry              *geometry);

extern RpGeometry *
RpCollisionGeometryForAllIntersections(
    RpGeometry              *geometry,
    RpIntersection          *intersection,
    RpIntersectionCallBackGeometryTriangle callBack,
    void                    *data);

extern RpAtomic *
RpAtomicForAllIntersections(
    RpAtomic                *atomic,
    RpIntersection          *intersection,
    RpIntersectionCallBackGeometryTriangle callBack,
    void                    *data);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RPCOLLIS_H */

