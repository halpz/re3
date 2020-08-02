/*
 * Structure for splines
 * 
 * 
 * Copyright (c) Criterion Software Limited
 */

/******************************************/
/*                                        */
/*    RenderWare(TM) Graphics Library     */
/*                                        */
/******************************************/

/*
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 1998. Criterion Software Ltd.
 * All Rights Reserved.
 */

/***************************************************************************
 *                                                                         *
 * Module  :    rpspline.h                                                 *
 *                                                                         *
 * Purpose :    Spline operations                                          *
 *                                                                         *
 **************************************************************************/

#ifndef RPSPLINE_H
#define RPSPLINE_H

/**
 * \defgroup rpspline RpSpline
 * \ingroup mathtools
 *
 * Spline Plugin for RenderWare Graphics.
 */

/****************************************************************************
 Includes
 */

/*--- Include files ---*/
#include "rwcore.h"
#include "rpworld.h"

#include "rpspline.rpe"    /* automatically generated header file */

/****************************************************************************
 Global Types
 */

#define rpSPLINENAMELENGTH (32)

typedef struct RpSpline RpSpline;
/**
 * \ingroup rpspline
 * \struct  RpSpline
 * Spline object. This should be considered an opaque type. 
 * Use the RpSpline API functions to access.
 */
struct RpSpline
{
    RwObject        tType;                      /**< Internal Use */
    RwInt32         numCtrlPoints;              /**< Internal Use */
    RwInt32         nSplineType;                /**< Internal Use */
    void            *pUser;                     /**< Internal Use */
    RwV3d           *ctrlPoints;                /**< Internal Use */
    RwChar          caName[rpSPLINENAMELENGTH]; /**< Internal Use */
    /* Keep this at tail */
    RwV3d           vPts[1];                    /**< Internal Use */
};

/* Spline types */
#define rpSPLINETYPEOPENLOOPBSPLINE     (1)     /* Bezier spline, open loop */
#define rpSPLINETYPECLOSEDLOOPBSPLINE   (2)     /* Bezier spline, closed loop */

/* Spline path types */
#define rpSPLINEPATHSMOOTH              (10)    /* Normal */
#define rpSPLINEPATHNICEENDS            (11)    /* Slows down the path at the ends */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Opening the spline plugin */
extern RwBool RpSplinePluginAttach(void);

/* Creating and destroying splines */
extern RpSpline *RpSplineCreate(RwInt32 numCtrlPoints, RwInt32 type, RwV3d *ctrlPoints);
extern RwBool RpSplineDestroy(RpSpline *spline);

/* Finding a point and its tangent vector on the spline */
extern RwV3d *RpSplineFindPosition(RpSpline *spline, RwInt32 path, RwReal where, RwV3d *pos, RwV3d *tangent);

/* Finding a frame on the spline */
extern RwReal RpSplineFindMatrix(RpSpline *spline, RwInt32 path, RwReal where, RwV3d *up, RwMatrix *matrix);
/* LEGACY-SUPPORT MACRO */
#define RpSplineFindFrame RpSplineFindMatrix

/* Getting and setting the control points */
extern RwInt32 RpSplineGetNumControlPoints(const RpSpline *spline);
extern RwV3d *RpSplineGetControlPoint(RpSpline *spline, RwInt32 control, RwV3d *point);
extern RpSpline *RpSplineSetControlPoint(RpSpline *spline, RwInt32 control, RwV3d * point);

/* Copy a spline */
extern RpSpline *RpSplineClone(RpSpline *spline);

/* Spline reading and writing helper functions */
extern RpSpline *RpSplineRead(RwChar *name);
extern RwBool RpSplineWrite(RpSpline *spline, RwChar *name);

/* Binary format */
extern RwUInt32 RpSplineStreamGetSize(const RpSpline *spline);
extern RpSpline *RpSplineStreamRead(RwStream *stream);
extern const RpSpline *RpSplineStreamWrite(const RpSpline *spline, RwStream *stream);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RPSPLINE_H */






