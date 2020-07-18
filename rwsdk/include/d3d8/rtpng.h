
/***************************************************************************
 *                                                                         *
 * Module  : rtPng.h                                                       *
 *                                                                         *
 * Purpose : Load PNG format files                                         *
 *                                                                         *
 **************************************************************************/

#ifndef RTPNG_H
#define RTPNG_H

/**
 * \defgroup rtpng RtPNG
 * \ingroup imageconversiontools
 *
 * PNG/Portable Network Graphics Image Format Toolkit for RenderWare.
 *
 * See also http://www.libpng.org/pub/png/
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rtpng.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwImage *RtPNGImageWrite(RwImage * image, const RwChar * imageName);
extern RwImage *RtPNGImageRead(const RwChar * imageName);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RTPNG_H */
