/*
 * Potentially Visible Set plug-in
 */

/**********************************************************************
 *
 * file :     rppvs.h
 *
 * abstract : handle culling of worldsectors in RenderWare
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
 * Copyright (c) 2001 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 ************************************************************************/

#ifndef _RPPVS_H
#define _RPPVS_H

/**
 * \defgroup rppvs RpPVS
 * \ingroup pvs
 *
 * Geometric Potentially Visible Set Plugin for RenderWare Graphics.
 */

/****************************************************************************
 Defines
 */

typedef RwUInt8     RpPVSVisMap;

#define PVSFROMWORLDSECTOR(sector) \
    ((RpPVS *)(((char *)(sector))+rpPVSGlobals.sectorOffset))

#define WORLDSECTORFROMPVS(pvs)    \
    ((RpWorldSector *)(((char *)(pvs))-rpPVSGlobals.sectorOffset))

#define PVSFROMCONSTWORLDSECTOR(sector) \
    ((const RpPVS *)(((const char *)(sector))+rpPVSGlobals.sectorOffset))


#define PVSCACHEFROMWORLD(world) \
    ((RpPVSCache *)(((char *)(world))+rpPVSGlobals.worldOffset))
#define PVSCACHEFROMCONSTWORLD(world) \
    ((const RpPVSCache *)(((const char *)(world))+rpPVSGlobals.worldOffset))

#define PVSVISMAPSETSECTOR(_vismap, _id)        \
    (_vismap)[(_id) >> 3] |= (1 << ((_id) & 7))

#define PVSVISMAPUNSETSECTOR(_vismap, _id)        \
    (_vismap)[(_id) >> 3] ^= (1 << ((_id) & 7))

#define PVSVISMAPGETSECTOR(_vismap, _id)        \
    ((_vismap)[(_id) >> 3] & (1 << ((_id) & 7)))

#define PVSVISMAPLENGTH(_vismaplength, _nosectors) \
    (_vismaplength) = ((_nosectors + 7) >> 3)


/* Progress callback message types */
#define rpPVSPROGRESSSTART              20
#define rpPVSPROGRESSUPDATE             12
#define rpPVSPROGRESSEND                22

/**
 * \ingroup rppvs
 * \ref RpPVSProgressCallBack
 * This typedef sets the callback function for sampling within a world sector.
 *
 * \param value     A value between 0.0 and 100.0 to represent the percentage completion.
 * \param msg       The message may take one of the following:
 *
 * \li rpPVSPROGRESSSTART
 * The PVS creation process is about to start.  The argument value is equal to 0.0.
 *
 * \li rpPVSPROGRESSUPDATE
 * The PVS creation process has finished processing a subsection of the world.
 * The argument value is equal to the percentage of the world processed up to this point.
 *
 * \li rpPVSPROGRESSEND
 * The PVS creation process has ended.  All world sectors have been processed.
 * The argument value is equal to 100.0.
 *
 * The progress callback may return FALSE to indicate that the generation of PVS data
 * should terminate. Otherwise, return TRUE to continue.
 *
 * The PVS plugin must be attached before using this function.
 *
 *
 */
typedef             RwBool(*RpPVSProgressCallBack) (RwInt32 msg,
                                                     RwReal value);


/**
 * \ingroup rppvs
 * \ref RpPVSCallBack
 * This typedef sets the callback function for sampling within a world sector.
 *
 * \param worldSector       A pointer to the \ref RpWorldSector being sampled.
 * \param box               The bounding box of the region being sampled.
 * \param pData             A pointer to private data for the sampling function.
 */
typedef RpWorldSector *(*RpPVSCallBack) (RpWorldSector * worldSector,
                                         const RwBBox * box,
                                         void *pData);

#define RpPVSCallback                   RpPVSCallBack

typedef struct _RpPVSCallBack _RpPVSCallBack;

#if (!defined(DOXYGEN))
struct _RpPVSCallBack
{
    RpPVSCallBack      callback;
    void               *data;
};
#endif /* (!defined(DOXYGEN)) */

enum _rpPVSPartitionId
{
    rpNAPVSPARTITIONID = 0,
    rpPVSFRONT,
    rpPVSBACK,
    rpPVSSPLIT,
    rpPVSCOPLANAR,
    rpPVSPARTITIONIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum _rpPVSPartitionId _rpPVSPartitionId;

typedef struct _rpPVSPolyList _rpPVSPolyList;
typedef struct _rpPVSPolyList *_rpPVSPolyListPtr;

typedef struct _rpPVSPoly _rpPVSPoly;
typedef struct _rpPVSPoly *_rpPVSPolyPtr;

#if (!defined(DOXYGEN))
typedef struct _rpPVSPlaneEq _rpPVSPlaneEq;
struct _rpPVSPlaneEq
{
    RwReal              x;
    RwReal              y;
    RwReal              z;
    RwReal              w;

    RwReal              l;      /* recip of length of the normal */

    _rpPVSPartitionId         lastresult; /* temp: stores result of last polygon wrt this plane */
};

typedef struct RwV3i RwV3i;
struct RwV3i
{
    RwInt32 x;
    RwInt32 y;
    RwInt32 z;
};

typedef struct _rpPVSPolyRecord _rpPVSPolyRecord;
struct _rpPVSPolyRecord
{
    RwBool              original; /* True if not a fragment */
    RwReal              priority; /* Used for sorting, lower values higher priority */
    _rpPVSPolyListPtr         parent; /* Unique pointer to original parent */
    _rpPVSPolyPtr             geom;   /* corners of the poly */
    _rpPVSPlaneEq             plane;  /* plane equation of the poly */
    RwInt32             home;   /* world sector id in range 0..numsectors */
    RpWorldSector      *homeaddr; /* world sector pointer */
    RwBool              translucent;

    RwBool              hasbeenclipper; /* Used during WA creation */

    /* used by proximity culling, calculated once */
    RwV3d               centroid;
    RwReal              radius;
    RwV3d               extreme; /* the vertex furthest away from the centroid */

    RwReal              coneRadius; /* Used during clipping only */

};

struct _rpPVSPoly
{
    RwV3d               v;
    _rpPVSPoly               *next;

    RwInt32             pscalar; /* Used during clipping only */
    RwReal              scalar; /* Used during clipping only */
    _rpPVSPlaneEq             shadowPlane; /* Used during clipping only */
};

struct _rpPVSPolyList
{
    _rpPVSPolyRecord          data;
    _rpPVSPolyList           *next;
};

typedef struct RpPVS RpPVS;

struct RpPVS
{
    RwInt32             sectorID;
    RwInt32             vismaplength;
    RwInt32             sampleKey;

    RpPVSVisMap        *vismap;

    _rpPVSPolyListPtr         sectailpoly; 
    _rpPVSPartitionId         potential;

    RwUInt32            numpols;
    RwBBox              sbox;
    RwBBox              gbox;
    RwReal              diagonal;
    RwV3d               centre;
    RwInt32             axessig[3];
};

typedef struct RpPVSCache RpPVSCache;
struct RpPVSCache
{
    RwBool              processed;
    RwBool              formatted;
    RwInt32             NumWorldSectors;

    RwInt32             ptotal;
    RwInt32             paccept;

    RwBool              hooked;

    RwUInt32            nextID;

    RwInt32             viscount;

    RpPVSProgressCallBack progressCallBack;

    _rpPVSPolyListPtr         polygons;

    RpWorldSectorCallBackRender     renderCallBack;
};

typedef struct RpPVSGlobalVars RpPVSGlobalVars;
struct RpPVSGlobalVars
{
    RpWorld            *World;

    RwInt32             worldOffset;
    RwInt32             sectorOffset;

    RwBool              collis;
    RwBool              bfc;


    RwInt32             progress_count;
    RwReal              diagonal;

    RwReal              gran;

    RwInt32             InSector;
    RwV3d               ViewPos;
    RpPVS             *CurrPVS;
};
#endif /* (!defined(DOXYGEN)) */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RpPVSGlobalVars    rpPVSGlobals;

extern RpWorld *
RpPVSSetProgressCallBack(RpWorld * wpWorld,
                         RpPVSProgressCallBack
                         callback);

extern RpWorldSector *
RpPVSSetViewPosition(RpWorld * wpWorld,
                     RwV3d * pos);

extern RpWorldSector *
RpPVSSetViewSector(RpWorld * wpWorld, RpWorldSector * spSect);

extern RpWorldSector *
RpPVSSetWorldSectorPairedVisibility(RpWorldSector * spSectA,
                                    RpWorldSector * spSectB,
                                    RwBool visible,
                                    RwBool mutual);

extern RpWorld *
RpPVSDestroy(RpWorld * wpWorld);

extern RwBool
RpPVSWorldSectorVisible(RpWorldSector * spSect);

extern RwBool
RpPVSPluginAttach(void);

extern RwBool
RpPVSQuery(RpWorld * wpWorld);

extern RwBool
RpPVSAtomicVisible(RpAtomic * atom);

extern RpWorld *
RpPVSStatisticsGet(RpWorld * wpWorld,
                   RwInt32 * ptotal,
                   RwInt32 * paccept);

extern RpPVSProgressCallBack
RpPVSGetProgressCallBack(RpWorld *
                         wpWorld);

extern RpWorld *
RpPVSConstruct(RpWorld * wpWorld,
            RpPVSCallBack callback,
            void *pData);

extern RpWorld*
RpPVSConstructSector(RpWorld * wpWorld,
            RpWorldSector * spSector,
            RpPVSCallBack callback,
            void *pData);


extern RpWorldSector *
RpPVSGeneric(RpWorldSector * spSect,
             const RwBBox __RWUNUSED__ * box,
             void *data);

extern RwBool
RpPVSSetCollisionDetection(RwBool collis);

extern RwBool
RpPVSSetBackFaceCulling(RwBool bfc);

extern RpWorld *
RpPVSUnhook(RpWorld * wpWorld);

extern RpWorld *
RpPVSHook(RpWorld * wpWorld);

extern RpWorldSector *
RpPVSSetWorldSectorVisibility(RpWorldSector * spSect,
                              RwBool visible);

extern RwBool
RpPVSSamplePOV(RwV3d * pos,
               RwBool colltest);

extern RxNodeDefinition *
RxNodeDefinitionGetPVSWorldSectorCSL(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* These functions are added for backwards compatibility... */
#define RpPVSCreate(_wpWorld,                               \
            _raster, _zraster, _mindist,                    \
            _maxdist, _maxdepth, _callback, _pData)         \
            RpPVSConstruct(_wpWorld, _callback, _pData)

#define RpPVSAddPOV(_pos) \
    RpPVSSamplePOV(_pos, FALSE)

#define RpPVSAddWorldSector(_sector) \
    RpPVSSetWorldSectorVisibility(_sector, TRUE)

#define RpPVSAddExtraPOV(_world, _raster, _zraster, _mindist, _mazdist, _matrix) \
MACRO_START                                     \
{                                               \
    rpPVSGlobals.World = (_world);              \
    RpPVSSamplePOV(&((_matrix)->pos), TRUE);    \
}                                               \
MACRO_STOP


#endif /*  _RPPVS_H */
