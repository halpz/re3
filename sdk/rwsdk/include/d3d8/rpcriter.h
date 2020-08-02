/* Doxygen Core Library groups */

/**
 * \defgroup rwcore Core Library
 *
 * Core Library
 */

/**
 * \defgroup datatypes Data Types
 * \ingroup rwcore
 *
 * Basic Data Types
 */

#ifndef RWPLCORE
/**
 * \defgroup rwbbox RwBBox
 * \ingroup rwcore
 *
 * Bounding Box
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwcamera RwCamera
 * \ingroup rwcore
 *
 * Cameras define how and what things can be seen. They also define the
 * depth and width of the view by the use of clip-planes and the view
 * window.
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwcameravertex RwCameraVertex
 * \ingroup rwcore
 *
 * Camera space vertex data access
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwdebug RwDebug
 * \ingroup rwcore
 *
 *  Debug handling
 */

/**
 * \defgroup rwengine RwEngine
 * \ingroup rwcore
 *
 * Device handling.
 */

/**
 * \defgroup rwerror RwError
 * \ingroup rwcore
 *
 * Error code handling
 */

#ifndef RWPLCORE
/**
 * \defgroup rwframe RwFrame
 * \ingroup rwcore
 *
 * Frames define relationships between objects and the world
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwfreelist RwFreeList
 * \ingroup rwcore
 *
 * Free lists
 */

#ifndef RWPLCORE
/**
 * \defgroup rwimage RwImage
 * \ingroup rwcore
 *
 * Image handling.
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwim2d RwIm2D
 * \ingroup rwcore
 *
 * 2D immediate mode support
 */

#ifndef RWPLCORE
/**
 * \defgroup rwim2dcameravertex RwIm2DCameraVertex
 * \ingroup rwcore
 *
 * 2D Camera space vertex data access
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwim2dvertex RwIm2DVertex
 * \ingroup rwcore
 *
 * Im2D Vertex data access
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwim3d RwIm3D
 * \ingroup rwcore
 *
 * 3D immediate mode support
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwim3dvertex RwIm3DVertex
 * \ingroup rwcore
 *
 * Im3D Vertex data access
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwmatrix RwMatrix
 * \ingroup rwcore
 *
 * Handling binary matrix representations.
 */

/**
 * \defgroup rwmem RwMem
 * \ingroup rwcore
 *
 * Memory
 */

#ifndef RWPLCORE
/**
 * \defgroup rwobject RwObject
 * \ingroup rwcore
 *
 * object
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwos RwOs
 * \ingroup rwcore
 *
 * Operating System
 */

#ifndef RWPLCORE
/**
 * \defgroup rwraster RwRaster
 * \ingroup rwcore
 *
 * Image/raster coupling handling.
 */
#endif /* RWPLCORE */

/**
 * \defgroup rwrenderstate RwRenderState
 * \ingroup rwcore
 *
 * Render states
 */

/**
 * \defgroup rwresources RwResources
 * \ingroup rwcore
 *
 * Resource handling.
 * Resources are used to instance objects into.
 */


/**
 * \defgroup rwrgba RwRGBA
 * \ingroup rwcore
 *
 * Color space functionality.
 */


/**
 * \defgroup rwstream RwStream
 * \ingroup rwcore
 *
 * Stream
 */

#ifndef RWPLCORE
/**
 * \defgroup rwtexdict RwTexDictionary
 * \ingroup rwcore
 *
 * Texture Dictionary
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwtexture RwTexture
 * \ingroup rwcore
 *
 * Texture handling.
 * Textures are special cases of rasters that can be applied to polygons.
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwv2d RwV2d
 * \ingroup rwcore
 *
 * 2D Vector mathematics.
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwv3d RwV3d
 * \ingroup rwcore
 *
 * 3D Vector mathematics.
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwcorepowerpipe PowerPipe
 * \ingroup rwcore
 *
 * PowerPipe
 */
#endif /* RWPLCORE */

#ifndef RWPLCORE
/**
 * \defgroup rwcoregeneric Generic
 * \ingroup rwcorepowerpipe
 *
 * Generic Pipeline
 *
 */
#endif /* RWPLCORE */

/* These are plugins */
#define rwID_METRICSPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x01)
#define rwID_SPLINEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x02)
#define rwID_STEREOPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x03)
#define rwID_VRMLPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x04)
#define rwID_MORPHPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x05)
#define rwID_PVSPLUGIN       MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x06)
#define rwID_MEMLEAKPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x07)
#define rwID_ANIMPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x08)
#define rwID_GLOSSPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x09)
#define rwID_LOGOPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0a)
#define rwID_MEMINFOPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0b)
#define rwID_RANDOMPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0c)
#define rwID_PNGIMAGEPLUGIN  MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0d)
#define rwID_BONEPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0e)
#define rwID_VRMLANIMPLUGIN  MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x0f)
#define rwID_SKYMIPMAPVAL    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x10)
#define rwID_MRMPLUGIN       MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x11)
#define rwID_LODATMPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x12)
#define rwID_MEPLUGIN        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x13)
#define rwID_LTMAPPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x14)
#define rwID_REFINEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x15)
#define rwID_SKINPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x16)
#define rwID_LABELPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x17)
#define rwID_PARTICLESPLUGIN MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x18)
#define rwID_GEOMTXPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x19)
#define rwID_SYNTHCOREPLUGIN MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1a)
#define rwID_STQPPPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1b)
#define rwID_PARTPPPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1c)
#define rwID_COLLISPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1d)
#define rwID_HANIMPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1e)
#define rwID_USERDATAPLUGIN  MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x1f)
#define rwID_MATERIALEFFECTSPLUGIN \
                             MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x20)
#define rwID_PARTICLESYSTEMPLUGIN \
                             MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x21)
#define rwID_DMORPHPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x22)
#define rwID_PATCHPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x23)
#define rwID_TEAMPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x24)
#define rwID_CROWDPPPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x25)
#define rwID_MIPSPLITPLUGIN  MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x26)
#define rwID_ANISOTPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x27)
/* #define THIS SPACE FREE!     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x28) */
#define rwID_GCNMATPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x29)
#define rwID_GPVSPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2a)
#define rwID_XBOXMATPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2b)
#define rwID_MULTITEXPLUGIN  MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2c)
#define rwID_CHAINPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2d)
#define rwID_TOONPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2e)
#define rwID_PTANKPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x2f)

#define rwID_PRTSTDPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x30)


/********************************************************/

/* Doxygen plugin groups. */

#ifndef RWPLCORE

/**
 * \defgroup rpplugin Plugins
 *
 * API Plugins
 *
 */

/**
 * \defgroup rpworld RpWorld
 * \ingroup rpplugin
 *
 * World handling Plugin
 *
 * Gives objects context,
 * and provides a mechanism for efficient static object rendering.
 */

/********************************************************/

/**
 * \defgroup rpworlddatatypes Data Types
 * \ingroup rpworld
 *
 * RpWorld Data types
 */

/**
 * \defgroup rpatomic RpAtomic
 * \ingroup rpworld
 *
 * Atomics
 */

/**
 * \defgroup rpclump RpClump
 * \ingroup rpworld
 *
 * Clumps
 */

/**
 * \defgroup rpgeometry RpGeometry
 * \ingroup rpworld
 *
 * Handling atomic's geometry
 */


/**
 * \defgroup rpinterpolator RpInterpolator
 * \ingroup rpworld
 *
 * Interpolators
 */

/**
 * \defgroup rplight RpLight
 * \ingroup rpworld
 *
 * Lighting 3D objects.
 * Lights are used to illuminate atomics and worlds
 */

/**
 * \defgroup rpmaterial RpMaterial
 * \ingroup rpworld
 *
 * Handling surface materials
 * Materials describe how things are to appear when rendered
 */

/**
 * \defgroup rpmesh RpMesh
 * \ingroup rpworld
 *
 * Provide construction and enumeration facilities for meshes.
 */

/**
 * \defgroup rpmorphtarget RpMorphTarget
 * \ingroup rpworld
 *
 * Morph Targets
 */

/**
 * \defgroup rpworldsub RpWorld
 * \ingroup rpworld
 *
 * RpWorld sub group
 */

/**
 * \defgroup rpworldsector RpWorldSector
 * \ingroup rpworld
 *
 * Handling atomic sectors
 */

/**
 * \defgroup rpworldrwcamera RwCamera
 * \ingroup rpworld
 *
 * Cameras
 */

/**
 * \defgroup rpworldpowerpipe PowerPipe
 * \ingroup rpworld
 *
 * PowerPipe
 */

/**
 * \defgroup rpworldp2generic Generic
 * \ingroup rpworldpowerpipe
 *
 * Generic
 */
#endif /* RWPLCORE */

/* These are toolkits */
#define rwID_CHARSEPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x80)
#define rwID_NOHSWORLDPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x81)
#define rwID_IMPUTILPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x82)
#define rwID_SLERPPLUGIN       MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x83)
#define rwID_OPTIMPLUGIN       MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x84)
#define rwID_TLWORLDPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x85)
#define rwID_DATABASEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x86)
#define rwID_RAYTRACEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x87)
#define rwID_RAYPLUGIN         MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x88)
#define rwID_LIBRARYPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x89)
#define rwID_2DPLUGIN          MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x90)
#define rwID_TILERENDPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x91)
#define rwID_JPEGIMAGEPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x92)
#define rwID_TGAIMAGEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x93)
#define rwID_GIFIMAGEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x94)
#define rwID_QUATPLUGIN        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x95)
#define rwID_SPLINEPVSPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x96)
#define rwID_MIPMAPPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x97)
#define rwID_MIPMAPKPLUGIN     MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x98)
#define rwID_2DFONT            MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x99)
#define rwID_INTSECPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9a)
#define rwID_TIFFIMAGEPLUGIN   MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9b)
#define rwID_PICKPLUGIN        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9c)
#define rwID_BMPIMAGEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9d)
#define rwID_RASIMAGEPLUGIN    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9e)
#define rwID_SKINFXPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0x9f)
#define rwID_VCATPLUGIN        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa0)
#define rwID_2DPATH            MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa1)
#define rwID_2DBRUSH           MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa2)
#define rwID_2DOBJECT          MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa3)
#define rwID_2DSHAPE           MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa4)
#define rwID_2DSCENE           MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa5)
#define rwID_2DPICKREGION      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa6)
#define rwID_2DOBJECTSTRING    MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa7)
#define rwID_2DANIMPLUGIN      MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa8)
#define rwID_2DANIM            MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xa9)
#define rwID_2DKEYFRAME        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xb0)
#define rwID_2DMAESTRO         MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xb1)
#define rwID_BARYCENTRIC       MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xb2)
#define rwID_PITEXDICTIONARYTK MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xb3)
#define rwID_TOCTOOLKIT        MAKECHUNKID(rwVENDORID_CRITERIONTK, 0xb4)

/**********************************************************************/

/* Doxygen Toolkit groups */

/**
 * \defgroup rttool Toolkits
 *
 * API Toolkits
 */

/**
 * \defgroup fxpack FXPack
 *
 * FXPack component group
 */

/**********************************************************************/

/**
 * \defgroup platformspecific Platform Specific
 *
 * Links to all platform specific information in the API Reference can
 * be found in this folder.
 */

/**********************************************************************/

/* Index Page definition for API Reference. Don't mess with it unless you know what you're doing. */


/**
 * \mainpage RenderWare Graphics API Reference
 *
 * \image html rwglogo.jpg
 *
 * This document provides an API Reference for release 3.3 of the RenderWare 
 * Graphics SDK.
 *
 * You do not have to wait for a major release to obtain a current API 
 * Reference. An up-to-date API Reference is compiled every week and goes out
 * with the weekly build. The footer declares when it was generated.
 *
 * \section otherdocs Documentation Available
 * RenderWare Graphics is supplied with:
 *
 * - A top-level README.PDF -- If you read nothing else, at least read this!
 * - this API Reference
 * - the User Guide
 * - Artist's documentation (if installed)
 * - Examples documentation
 * - Maestro documentation
 * - Tools documentation
 * - White Papers
 * - readme.txt files for each of the supplied Examples
 *
 * \section contactus Contact Us
 *
 * \subsection csl Criterion Software Ltd.
 * For general information about RenderWare e-mail info@csl.com.
 *
 * \subsection devrels Developer Relations
 *
 * For information regarding Support please email devrels@csl.com
 *
 * \subsection sales Sales
 *
 * For sales information contact: rw-sales@csl.com
 *
 * \section copyright Copyright Notice
 *
 * The information in this document is subject to change without notice and does not represent
 * a commitment on the part of Criterion Software Ltd. The software described in this document is
 * furnished under a license agreement or a non-disclosure agreement. The software may be used or
 * copied only in accordance with the terms of the agreement. It is against the law to copy the
 * software on any medium except as specifically allowed in the license or non-disclosure agreement.
 *
 * No part of this documentation may be reproduced or transmitted in any form or by any means for any
 * purpose without the express written permis­sion of Criterion Software Ltd.
 *
 * Copyright © 1993 - 2002 Criterion Software Ltd. All rights reserved.
 *
 * Canon and RenderWare are registered trademarks of Canon Inc. Nintendo is a registered trademark
 * and NINTENDO GAMECUBE a trademark of Nintendo Co., Ltd. Microsoft is a registered trademark and
 * Xbox is a trademark of Microsoft Corporation. PlayStation is a registered trademark of Sony Computer
 * Entertainment Inc.
 *
 * All other trademarks mentioned herein are the property of their respective companies.
 *
 */
