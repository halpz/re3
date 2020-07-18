
/***************************************************************************
 *                                                                         *
 * Module  : rtsplpvs.h                                                    *
 *                                                                         *
 * Purpose : To generate pvs data for a world froma spline                 *
 *                                                                         *
 **************************************************************************/

#ifndef RTSPLINEPVS_H
#define RTSPLINEPVS_H

/**
 * \defgroup rtsplinepvs RtSplinePVS
 * \ingroup pvs
 * 
 * Spline PVS Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include "rpworld.h"
#include "rpspline.h"

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


#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RpWorld *
RtSplinePVSConstruct(RpWorld * world,
                     RpSpline *spline, RwInt32 samples);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

/* for back compatibility */
#define RtSplinePVSCreate(_world, _raster, _zraster,        \
                  _mindist, _maxdist, _spline, _samples)    \
        RtSplinePVSConstruct(_world,                        \
                  _spline, _samples)


#endif                          /* RTSPLINEPVS_H */
