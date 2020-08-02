/***************************************************************************
 *                                                                         *
 * Module  : rttiff.h                                                       *
 *                                                                         *
 * Purpose : Load TIFF format files                                         *
 *                                                                         *
 **************************************************************************/

#ifndef RWTIFF_H
#define RWTIFF_H

/**
 * \defgroup rttiff RtTIFF
 * \ingroup imageconversiontools
 *
 * TIFF/Tag Image File Format Image Format Toolkit for RenderWare.
 *
 * See also http://www.libtiff.org
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rttiff.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwImage *RtTIFFImageRead(const RwChar *imageName);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWTIFF_H */
