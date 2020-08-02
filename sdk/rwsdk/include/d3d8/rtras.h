/***************************************************************************
 *                                                                         *
 * Module  : rtRAS.h                                                       *
 *                                                                         *
 * Purpose : Load RAS format files                                         *
 *                                                                         *
 **************************************************************************/

#ifndef RTRAS_H
#define RTRAS_H

/**
 * \defgroup rtras RtRAS
 * \ingroup imageconversiontools
 *
 * RAS/Sun Raster Fule Format Image Format Toolkit for RenderWare.
 *
 * See also http://www.sworks.com/hollasch/cgindex/formats/sunraster.html
 *
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rtras.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwImage *RtRASImageWrite(RwImage * image,
                                const RwChar * imageName);
extern RwImage *RtRASImageRead(const RwChar * imageName);

extern void  _rwImageGammaUnCorrectArrayOfRGBA(RwRGBA * rgbaOut,
                                               RwRGBA * rgbaIn,
                                               RwInt32 numEls);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RTRAS_H */
