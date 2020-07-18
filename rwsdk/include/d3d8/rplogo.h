/** 
 * Logo plugin
 */


/**********************************************************************
 *
 * File :     rplogo.h
 *
 * Abstract : Add CSL Logo 
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

#ifndef RPLOGO_H
#define RPLOGO_H

/**
 * \defgroup rplogo RpLogo
 * \ingroup 2dtools
 *
 * Logo Plugin for RenderWare Graphics.
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rplogo.rpe"          /* automatically generated header file */

/*--- Global Structures ---*/

enum RpLogoPosition
{
    rpNALOGOPOSITION = 0,
    rpLOGOTOP,
    rpLOGOCENTER,
    rpLOGOBOTTOM,
    rpLOGOLEFT,
    rpLOGORIGHT,
    rpLOGOTOPLEFT,
    rpLOGOTOPRIGHT,
    rpLOGOBOTTOMLEFT,
    rpLOGOBOTTOMRIGHT,
    rpLOGOPOSITIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLogoPosition RpLogoPosition;

/*--- Plugin API Functions ---*/

#ifdef    __cplusplus
extern          "C"
{
#endif         /* __cplusplus */

    RwBool          RpLogoPluginAttach(void);
    RwBool          RpLogoSetPosition(RpLogoPosition pos);
    RpLogoPosition  RpLogoGetPosition(void);
    RwBool          RpLogoSetState(RwCamera * cam, RwBool state);
    RwBool          RpLogoGetState(RwCamera * cam);
    RwRect         *RpLogoGetRenderingRect(void);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif         /* RPLOGO_H */

