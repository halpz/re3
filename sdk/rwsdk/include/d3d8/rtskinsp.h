/***************************************************************************
 *                                                                         *
 * Module  :                                                               *
 *                                                                         *
 * Purpose :                                                               *
 *                                                                         *
 **************************************************************************/

/* RWPUBLIC */

#ifndef RTSKINSP_H
#define RTSKINSP_H

/**
 * \defgroup rtskinsplit RtSkinSplit
 * \ingroup skinning
 *
 * Skin Splitting Toolkit for RenderWare Graphics.
 */

/****************************************************************************
 Includes
 */
#include <rwcore.h>
#include <rpworld.h>

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Global variables (across program)
 */

/****************************************************************************
 Function prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cpluscplus */

extern RpAtomic *
RtSkinSplitAtomicSplitGeometry( RpAtomic *atomic, RwUInt32 boneLimit );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RTSKINSP_H */

/* RWPUBLICEND */
