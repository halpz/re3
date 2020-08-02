
/***************************************************************************
 *                                                                         *
 * Module  : rtvcat.h                                                      *
 *                                                                         *
 * Purpose : Tristripping callback for vertex cache aware strips           *
 *                                                                         *
 **************************************************************************/

#ifndef RTVCAT_H
#define RTVCAT_H

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"

#include "rtvcat.rpe"   /* automatically generated header file */

/****************************************************************************
 Function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

extern RpMeshHeader *
RpBuildMeshGenerateCacheAwareTriStrip(RpBuildMesh *buildMesh, 
                                      void *data);

#ifdef __cplusplus
}
#endif

#endif /* RTVCAT_H */
