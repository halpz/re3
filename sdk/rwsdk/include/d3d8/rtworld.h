/*
 * World toolkit.
 */
/***************************************************************************
 *                                                                         *
 * Module  : rtworld.h                                                     *
 *                                                                         *
 * Purpose : World tool helper functions header                            *
 *                                                                         *
 **************************************************************************/

#ifndef RTWORLD_H
#define RTWORLD_H

/**
 * \defgroup rtworld RtWorld
 * \ingroup basicgeometry
 *
 * World Import Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include "rpworld.h"

#include "rtworld.rpe"    /* automatically generated header file */

/****************************************************************************
 Defines
 */

/* RWPUBLIC */
/****************************************************************************
 Global Types
 */

/* RWPUBLICEND */

/****************************************************************************
 Exported globals
 */

/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Get the number of various things in the world */
extern RwInt32 RtWorldGetNumWorldSectors(RpWorld *world);
extern RwInt32 RtWorldGetNumVertices(RpWorld *world);
extern RwInt32 RtWorldGetNumPolygons(RpWorld *world);

/* Find things out about materials in the world */
extern RwInt32 RtWorldFindMaterialNum(RpWorld *world, RpMaterial *material);
extern RpMaterial *RtWorldFindMaterialWithTextureName(RpWorld *world, RwChar *name);

/* Optimisation functions in optimise.c */
extern RpClump *RtClumpOptimize(RpClump *clump, RwReal dist);
extern RpAtomic *RtAtomicOptimize(RpAtomic *atomic, RwReal dist);

/*
 * This function has been removed, however it still exists as a stealth
 * function, _rtGeometryOptimize.
 */
#define RtGeometryOptimize(geometry, dist) (geometry)

extern RpGeometry *_rtGeometryOptimize(RpGeometry *geometry, RwReal dist);

/* Import utility functions from imputil.c */
extern RpGeometry *RtGeometryCalculateVertexNormals(RpGeometry *geometry);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWTLWRLD_H */
