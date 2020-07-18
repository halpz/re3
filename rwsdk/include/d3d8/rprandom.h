/**********************************************************************
 *
 * File :     rprandom.h
 *
 * Abstract : Random Number Generator
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

#ifndef RPRANDOM_H
#define RPRANDOM_H

/**
 * \defgroup rprandom RpRandom
 * \ingroup mathtools
 *
 * Random Number Generation Plugin for RenderWare Graphics.
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rprandom.rpe"    /* automatically generated header file */

/*--- Plugin API Functions ---*/

#define RPRANDMAX (~((~0)<<31))

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RwBool RpRandomPluginAttach(void);

/* Getting values */

extern RwUInt32 RpRandom(void);
extern void RpRandomSeed(RwUInt32 seed);

extern RwUInt32 RpRandomMT(void);
extern void RpRandomSeedMT(RwUInt32 seed);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RPRANDOM_H */

