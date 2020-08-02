/***************************************************************************
 *                                                                         *
 * Module  : rtray.h                                                       *
 *                                                                         *
 * Purpose : Picking with rays                                             *
 *                                                                         *
 **************************************************************************/

#ifndef RTRAY_H
#define RTRAY_H

/**
 * \defgroup rtray RtRay
 * \ingroup mathtools
 *
 * Line Toolkit for RenderWare. 
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rtray.rpe"    /* automatically generated header file */

/****************************************************************************
 Defines
 */


 /****************************************************************************
 Global Types
 */


/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Line intersections */
extern RwReal RtLineTriangleIntersectionTest(RwLine *line, RwV3d *normal,
                                             RwV3d *v0, RwV3d *v1, RwV3d *v2);
extern RwBool RtLineSphereIntersectionTest(RwLine *line, 
                                           RwSphere *sphere, 
                                           RwReal *centerDist);

/* Line clipping */
extern RwLine *RtLineClipPlane(RwLine *line, RwPlane *plane);
extern RwLine *RtLineClipBBox(RwLine *line, RwBBox *box);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RTRAY_H */
