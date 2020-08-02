/***************************************************************************
 *                                                                         *
 * Module  : rttilerd.h                                                    *
 *                                                                         *
 * Purpose : Tile renderer                                                 *
 *                                                                         *
 **************************************************************************/

#ifndef RTTILERD_H
#define RTTILERD_H

/**
 * \defgroup rttilerender RtTileRender
 * \ingroup cameras
 *
 * Tile renderer - e.g. grabbing screen shots -  Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */
#include "rwcore.h"

#include "rpcriter.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

typedef RwCamera * (*RtTileRenderCallBack)(RwCamera *camera,
                                           RwInt32 x, RwInt32 y,
                                           void *pData);

typedef RwImage * (*RtTileArchiveCallBack)(RwImage *image,
                                           RwInt32 x, RwInt32 y,
                                           void *pData);

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Tile renderer */

extern RwCamera *
RtTileRender(RwCamera *camera,
             RwInt32 imageWidth, RwInt32 imageHeight,
             RwInt32 tileWidth, RwInt32 tileHeight,
             RtTileRenderCallBack renderCallBack,
             RtTileArchiveCallBack archiveCallBack,
             void *pData);

extern RwImage *
RtTileDefaultArchive(RwImage *image,
                     RwInt32 x, RwInt32 y, void *pData);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RTTILERD_H */
