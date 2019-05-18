/*
 * Stereo camera plugin
 */

/**********************************************************************
 * 
 * File :     rpstereo.h
 *
 * Abstract : Add Stereo Camera support to RenderWare
 *
 **********************************************************************
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
 * Copyright (c) 1998 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 ************************************************************************/

#ifndef RPSTEREO_H
#define RPSTEREO_H

/**
 * \defgroup rpstereo RpStereo
 * \ingroup rpplugin
 *
 * Stereo Camera Plugin for RenderWare Graphics.
 */

/*--- Include files ---*/
#include <rwcore.h>
#include <rpworld.h>

#include "rpstereo.rpe"    /* automatically generated header file */

/*--- Global Structures ---*/

/* Supported Stereo Modes */

/**
 * \ingroup rpstereo
 * \ref RpStereoCameraMode
 * Stereo camera mode enumeration.
 */
enum RpStereoCameraMode
{
    rpNASTEREOMODE = 0,
    rpSTEREOMONO,                   /**< Render as Mono camera - single 
                                     * image 
                                     */
    rpSTEREOLEFTRIGHT,              /**< Vertical split screen. Left eye 
                                     * image on left of screen. Right eye 
                                     * image on right of screen.
                                     */
    rpSTEREORIGHTLEFT,              /**< Vertical split screen. Right eye
                                     * image on left of screen. Left eye image
                                     * on right of screen.
                                     */

    rpSTEREOROTATE90,               /**< As for rpSTEREOLEFTRIGHT - with 
                                     * the images rotated inwards by 90 degrees
                                     */
    rpSTEREOINTERLACEDLEFTRIGHT,    /**< Left and right eye images on 
                                     * alternate scanlines. The left eye image
                                     * on the topmost line of the display.
                                     */

    rpSTEREOINTERLACEDRIGHTLEFT,    /**< Left and right eye images on 
                                     * alternate scanlines. The right eye 
                                     * image is on the topmost line of the 
                                     * display.
                                     */
    rpSTEREOLASTMODE,
    rpSTEREOCAMERAMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*
 * typedef for stereo camera mode enumeration.
 */
typedef enum RpStereoCameraMode RpStereoCameraMode;

/*--- Constants ---*/

/* These may be used to quickly adapt an existing application to a 
 * stereo version. 
 */

#ifdef RPSTEREO_OVERLOAD
#define RwCameraBeginUpdate RpStereoCameraBeginUpdate
#define RwCameraEndUpdate RpStereoCameraEndUpdate
#undef RpWorldRender
#define RpWorldRender RpStereoWorldRender
#undef RpClumpRender
#define RpClumpRender RpStereoClumpRender
#undef RpAtomicRender
#define RpAtomicRender RpStereoAtomicRender
#undef RpWorldSectorRender
#define RpWorldSectorRender RpStereoWorldSectorRender
#endif

/*--- Plugin API Functions ---*/

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RwBool RpStereoPluginAttach(void);

RpWorld *RpStereoWorldRender(RpWorld *world);
RpClump *RpStereoClumpRender(RpClump *clump);
RpAtomic *RpStereoAtomicRender(RpAtomic *atomic);
RpWorldSector *RpStereoWorldSectorRender(RpWorldSector *sector);

RwCamera *RpStereoCameraBeginUpdate(RwCamera *camera);
RwCamera *RpStereoCameraEndUpdate(RwCamera *stereoCam);

RwReal RpStereoCameraGetSeparation(RwCamera *stereoCam);
RwReal RpStereoCameraGetFocal(RwCamera *stereoCam);
RpStereoCameraMode RpStereoCameraGetMode(RwCamera *stereoCam);

RwCamera *RpStereoCameraSetSeparation(RwCamera *stereoCam, RwReal dist);
RwCamera *RpStereoCameraSetFocal(RwCamera *stereoCam, RwReal focal);
RwCamera *RpStereoCameraSetMode(RwCamera *stereoCam, RpStereoCameraMode newMode);
 
#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RPSTEREO_H */

