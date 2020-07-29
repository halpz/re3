/**
 * Mipmap K toolkit
 */

/***************************************************************************
 *                                                                         *
 * Module  : rtmipk.h                                                      *
 *                                                                         *
 * Purpose : To calculate mipmap K values for Sky                          *
 *                                                                         *
 **************************************************************************/

#ifndef RTMIPK_H
#define RTMIPK_H

/**
 * \defgroup rtmipk RtMipmapK
 * \ingroup mipmapping
 *
 * PlayStation 2 / Mipmap K Value Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rpworld.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Function prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern void RtMipKWorldCalculateKValues(RpWorld *world, RwCamera *camera);
extern void RtMipKClumpCalculateKValues(RpClump *clump, RwCamera *camera);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

/* RWPUBLICEND */

#endif /* RTMIPK_H */
