/***************************************************************************
 *                                                                         *
 * Module  : rtpick.h                                                      *
 *                                                                         *
 * Purpose : Utils for picking atomics.                                    *
 *                                                                         *
 **************************************************************************/

#ifndef RTPICK_H
#define RTPICK_H

/**
 * \defgroup rtpick RtPick
 * \ingroup collisiondetection
 *
 * Picking Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rtpick.rpe"    /* automatically generated header file */

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Camera pixel ray */
extern const RwCamera   *RwCameraCalcPixelRay(const RwCamera *camera, 
                                              RwLine *line, 
                                              const RwV2d *pixel);

/* Picking atomics */
extern RpAtomic         *RpWorldPickAtomicOnLine(RpWorld *world,
                                                 const RwLine *line);
extern RpAtomic         *RwCameraPickAtomicOnPixel(const RwCamera *camera,
                                                   const RwV2d *pixel);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#endif /* RTPICK_H */
