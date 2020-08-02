/******************************************
 *                                        *
 *    RenderWare(TM) Graphics Library     *
 *                                        *
 ******************************************/

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
 * Module  : rpanim.h                                                      *
 *                                                                         *
 * Purpose : Hierarchical animation                                        *
 *                                                                         *
 **************************************************************************/
#ifndef RPHANIM_H
#define RPHANIM_H

/**
 * Hierarchal animation plugin
 */

/* Doxygen plugin groups. */

/**
 * \defgroup rphanim RpHAnim
 * \ingroup objectframehanim
 *
 * Hierarchical Animation Plugin for RenderWare Graphics.
 */

/**
 * \defgroup rphanimchanges RpHAnim Changes
 * \ingroup rphanim
 *
 */

/****************************************************************************
 Includes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include <rpworld.h>

#include <rpcriter.h>          /* Note: each vendor can choose their own method for
                                * allocation of unique ID's. This file defines
                                * the ID's used by Criterion.
                                */
#include <rphanim.rpe>          /* automatically generated header file */
#include <rtquat.h>
#include <rtanim.h>

#define rpHANIMSTREAMCURRENTVERSION 0x100

#if (!defined(DOXYGEN))

typedef struct RpHAnimAtomicGlobalVars RpHAnimAtomicGlobalVars;

struct RpHAnimAtomicGlobalVars
{
        RwInt32   engineOffset;
        RwFreeList *HAnimFreeList;
};

#endif /* (!defined(DOXYGEN)) */

#define rpHANIMSTDKEYFRAMESIZE sizeof(RpHAnimKeyFrame)
#define rpHANIMSTDKEYFRAMETYPEID 0x1

#define RpV3dInterpolate(o,a,s,b)                            \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) + ((s)) * (((b)->x) - ((a)->x)));        \
    (o)->y = (((a)->y) + ((s)) * (((b)->y) - ((a)->y)));        \
    (o)->z = (((a)->z) + ((s)) * (((b)->z) - ((a)->z)));        \
}                                                               \
MACRO_STOP


/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrame
 * typedef for struct RpHAnimKeyFrame. Based on \ref RtAnimKeyFrameHeader.
 */
typedef struct RpHAnimKeyFrame RpHAnimKeyFrame;

/**
 * \ingroup rphanim
 * \struct RpHAnimKeyFrame
 * A structure representing the standard keyframe data. Sequences of
 * such keyframes in an \ref RtAnimAnimation defines the animation of each
 * node in a hierarchy.
 */
struct RpHAnimKeyFrame
{
    RpHAnimKeyFrame    *prevFrame;  /**< Pointer to the previous keyframe */
    RwReal              time;       /**< Time at keyframe */
    RtQuat              q;          /**< Quaternion rotation at keyframe  */
    RwV3d               t;          /**< Translation at keyframe  */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimInterpFrame
 * typedef for struct RpHAnimInterpFrame. Based on \ref RtAnimInterpFrameHeader.
 */
typedef struct RpHAnimInterpFrame RpHAnimInterpFrame;

/**
 * \ingroup rphanim
 * \struct RpHAnimInterpFrame
 * A structure representing an interpolated keyframe. The initial part of the
 * structure matches \ref RtAnimInterpFrameHeader.
 */
struct RpHAnimInterpFrame
{
    RpHAnimKeyFrame    *keyFrame1;
        /**< Pointer to 1st keyframe of current interpolation pair */
    RpHAnimKeyFrame    *keyFrame2;
        /**< Pointer to 2nd keyframe of current interpolation pair */
    RtQuat              q;          /**< Quaternion rotation */
    RwV3d               t;          /**< Translation */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchy typedef for struct RpHAnimHierarchy
 */
typedef struct RpHAnimHierarchy RpHAnimHierarchy;

/* Flags for FrameInfos */

#define rpHANIMPOPPARENTMATRIX      0x01
#define rpHANIMPUSHPARENTMATRIX     0x02

/**
 * \ingroup rphanim
 * \ref RpHAnimNodeInfo
 * typedef for struct RpHAnimNodeInfo
 */
typedef struct RpHAnimNodeInfo RpHAnimNodeInfo;

/**
 * \ingroup rphanim
 * \struct RpHAnimNodeInfo
 *
 * Used to describe a hierarchy toplogy.
 * It holds flags representing its position in the
 * hierarchy as well as a pointer to the matching \ref RwFrame if the
 * hierarchy has been attached to a \ref RwFrame hierarchy.
 *
 */
struct RpHAnimNodeInfo
{
    RwInt32     nodeID;     /**< User defined ID for this node  */
    RwInt32     nodeIndex;  /**< Array index of node  */
    RwInt32     flags;      /**< Matrix push/pop flags  */
    RwFrame *   pFrame;     /**< Pointer to an attached RwFrame (see \ref RpHAnimHierarchyAttach) */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchyFlag defines type and update modes in HAnimHierarchies
 */
enum RpHAnimHierarchyFlag
{
    /* creation flags */
    rpHANIMHIERARCHYSUBHIERARCHY =              0x01, /**< This hierarchy is a sub-hierarchy */
    rpHANIMHIERARCHYNOMATRICES =                0x02, /**< This hierarchy has no local matrices */

    /* update flags */
    rpHANIMHIERARCHYUPDATEMODELLINGMATRICES = 0x1000, /**< This hierarchy updates modeling matrices */
    rpHANIMHIERARCHYUPDATELTMS =              0x2000, /**< This hierarchy updates LTMs */
    rpHANIMHIERARCHYLOCALSPACEMATRICES =      0x4000, /**< This hierarchy calculates matrices in a space
                                                           relative to its root */

    rpHANIMHIERARCHYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/*
 * These flags are used to control the creation and
 * update status of the hierarchy
 */
typedef enum RpHAnimHierarchyFlag RpHAnimHierarchyFlag;

/**
 * \ingroup rphanim
 * \struct RpHAnimHierarchy
 * An RpHAnimHierarchy is used to "play back" an animation.
 *
 * The structure of a hierarchy is defined by an array
 * of \ref RpHAnimNodeInfo structures.
 *
 * The hierarchy is defined by running through the node array in order,
 * pushing the parent-node's matrix whenever a child is reached that has
 * more than one sibling, and popping the parent matrix when a "leaf"
 * node is encountered.
 *
 */
struct RpHAnimHierarchy
{
    RwInt32             flags;          /**< Flags for the hierarchy  */
    RwInt32             numNodes;      /**< Number of nodes in the hierarchy  */

    RwMatrix           *pMatrixArray;   /**< Pointer to node matrices*/
    void               *pMatrixArrayUnaligned; /**< Pointer to memory used for node matrices
                                                * from which the aligned pMatrixArray is allocated */
    RpHAnimNodeInfo    *pNodeInfo;     /**< Array of node information (push/pop flags etc) */
    RwFrame            *parentFrame;    /**< Pointer to the Root RwFrame of the hierarchy this
                                           * RpHAnimHierarchy represents */
    RpHAnimHierarchy   *parentHierarchy;                       /**< Internal use */
    RwInt32             rootParentOffset;                      /**< Internal use */

    RtAnimInterpolator   *currentAnim;                    /**< Internal use */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimFrameExtension typedef for struct RpHAnimFrameExtension
 */

typedef struct RpHAnimFrameExtension RpHAnimFrameExtension;

/**
 * \ingroup rphanim
 * \struct RpHAnimFrameExtension
 *
 * Used to extend \ref RwFrame objects, and thus
 * allow the mapping between animation hierarchy node ID and \ref RwFrame.
 *
 */
struct RpHAnimFrameExtension
{
    RwInt32          id;         /**< ID given to this RwFrame (default of -1) */
    RpHAnimHierarchy *hierarchy; /**< Pointer to Animation hierarchy attached to this RwFrame */
};

/*--- Plugin API Functions ---*/

#define RpHAnimHierarchySetFlagsMacro(hierarchy,_flags)        \
MACRO_START                                                     \
{                                                               \
    (hierarchy)->flags = _flags;                                \
}                                                               \
MACRO_STOP

#define RpHAnimHierarchyGetFlagsMacro(hierarchy) \
    ((hierarchy)->flags)

#define RpHAnimKeyFrameToMatrixMacro(_matrix,_voidIFrame)               \
MACRO_START                                                             \
{                                                                       \
    RpHAnimInterpFrame * iFrame = (RpHAnimInterpFrame *)(_voidIFrame);  \
                                                                        \
    /*                                                                  \
     * RpHAnim uses the same types of quaternion as RtQuat              \
     *  hence no conjugate call as in RpSkin                            \
     */                                                                 \
                                                                        \
    RtQuatUnitConvertToMatrix(&iFrame->q,(_matrix));                    \
                                                                        \
    (_matrix)->pos.x = iFrame->t.x;                                     \
    (_matrix)->pos.y = iFrame->t.y;                                     \
    (_matrix)->pos.z = iFrame->t.z;                                     \
}                                                                       \
MACRO_STOP



#if (! defined(RWDEBUG))

#define RpHAnimHierarchySetFlags(hierarchy,_flags) \
        RpHAnimHierarchySetFlagsMacro(hierarchy,_flags)

#define RpHAnimHierarchyGetFlags(hierarchy) \
        (RpHAnimHierarchyFlag)RpHAnimHierarchyGetFlagsMacro(hierarchy)
#endif /* (! defined(RWDEBUG)) */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RpHAnimAtomicGlobalVars RpHAnimAtomicGlobals;

#if (defined(RWDEBUG))

extern RpHAnimHierarchy *
RpHAnimHierarchySetFlags(RpHAnimHierarchy *hierarchy,
                         RpHAnimHierarchyFlag flags);

extern RpHAnimHierarchyFlag
RpHAnimHierarchyGetFlags(RpHAnimHierarchy *hierarchy);

#endif /* (defined(RWDEBUG))  */

/* Animation hierarchy creation */
extern void
RpHAnimHierarchySetFreeListCreateParams(RwInt32 blockSize,RwInt32 numBlocksToPrealloc);

extern RpHAnimHierarchy *
RpHAnimHierarchyCreate(RwInt32 numNodes,
                       RwUInt32 *nodeFlags,
                       RwInt32 *nodeIDs,
                       RpHAnimHierarchyFlag flags,
                       RwInt32 maxKeyFrameSize);

extern RpHAnimHierarchy *
RpHAnimHierarchyCreateFromHierarchy(RpHAnimHierarchy *hierarchy,
                                    RpHAnimHierarchyFlag flags,
                                    RwInt32 maxKeyFrameSize);

extern RpHAnimHierarchy *
RpHAnimHierarchyDestroy(RpHAnimHierarchy *hierarchy);

extern RpHAnimHierarchy *
RpHAnimHierarchyCreateSubHierarchy(RpHAnimHierarchy *parentHierarchy,
                                   RwInt32 startNode,
                                   RpHAnimHierarchyFlag flags,
                                   RwInt32 maxKeyFrameSize);

extern RpHAnimHierarchy *
RpHAnimHierarchyAttach(RpHAnimHierarchy *hierarchy);

extern RpHAnimHierarchy *
RpHAnimHierarchyDetach(RpHAnimHierarchy *hierarchy);

extern RpHAnimHierarchy *
RpHAnimHierarchyAttachFrameIndex(RpHAnimHierarchy *hierarchy,
                                 RwInt32 nodeIndex);

extern RpHAnimHierarchy *
RpHAnimHierarchyDetachFrameIndex(RpHAnimHierarchy *hierarchy,
                                 RwInt32 nodeIndex);

extern RwBool
RpHAnimFrameSetHierarchy(RwFrame *frame,
                         RpHAnimHierarchy *hierarchy);

extern RpHAnimHierarchy *
RpHAnimFrameGetHierarchy(RwFrame *frame);

/* Macros for legacy support of old function names */
#define RpHAnimSetHierarchy(frame,hierarchy) \
                        RpHAnimFrameSetHierarchy(frame,hierarchy)
#define RpHAnimGetHierarchy(frame) RpHAnimFrameGetHierarchy(frame)

extern RwMatrix *
RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy *hierarchy);

extern RwBool
RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy *hierarchy);

/* Macro for legacy support of old function name */
#define RpHAnimUpdateHierarchyMatrices RpHAnimHierarchyUpdateMatrices

extern RwInt32
RpHAnimIDGetIndex(RpHAnimHierarchy *hierarchy,
                  RwInt32 ID);

/* Plugin support */

extern RwBool
RpHAnimPluginAttach(void);

/* Hanim keyframe functions */

extern void
RpHAnimKeyFrameApply(void *matrix,
                     void *voidIFrame);

extern void
RpHAnimKeyFrameBlend(void *voidOut,
                        void *voidIn1,
                        void *voidIn2,
                        RwReal alpha);

extern void
RpHAnimKeyFrameInterpolate(void *voidOut,
                              void *voidIn1,
                              void *voidIn2,
                              RwReal time);

extern void
RpHAnimKeyFrameAdd(void *voidOut,
                      void *voidIn1,
                      void *voidIn2);

extern void
RpHAnimKeyFrameMulRecip(void *voidFrame,
                           void *voidStart);

extern RtAnimAnimation *
RpHAnimKeyFrameStreamRead(RwStream *stream,
                             RtAnimAnimation *animation);

extern RwBool
RpHAnimKeyFrameStreamWrite(RtAnimAnimation *animation,
                              RwStream *stream);

extern RwInt32
RpHAnimKeyFrameStreamGetSize(RtAnimAnimation *animation);

/* Access to RwFrame ID's */

extern RwBool
RpHAnimFrameSetID(RwFrame *frame,
                  RwInt32 id);

extern RwInt32
RpHAnimFrameGetID(RwFrame *frame);

/*
 * Utility Functions
 */
#define RpHAnimHierarchySetCurrentAnimMacro(hierarchy,anim)\
        RtAnimInterpolatorSetCurrentAnim((hierarchy)->currentAnim,anim)

#define RpHAnimHierarchyGetCurrentAnimMacro(hierarchy)\
        RtAnimInterpolatorGetCurrentAnim((hierarchy)->currentAnim)

#define RpHAnimHierarchySetCurrentAnimTimeMacro(hierarchy,time)\
        RtAnimInterpolatorSetCurrentTime((hierarchy)->currentAnim,time)

#define RpHAnimHierarchyAddAnimTimeMacro(hierarchy,time)\
        RtAnimInterpolatorAddAnimTime((hierarchy)->currentAnim,time)

#define RpHAnimHierarchySubAnimTimeMacro(hierarchy,time)\
        RtAnimInterpolatorSubAnimTime((hierarchy)->currentAnim,time)

#define RpHAnimHierarchySetKeyFrameCallBacksMacro(hierarchy,keyFrameTypeID)  \
        RtAnimInterpolatorSetKeyFrameCallBacks((hierarchy)->currentAnim,\
                                                    keyFrameTypeID)

#define RpHAnimHierarchyBlendMacro(outHierarchy,inHierarchy1,inHierarchy2,alpha)\
        RtAnimInterpolatorBlend((outHierarchy)->currentAnim,\
                                    (inHierarchy1)->currentAnim,\
                                    (inHierarchy2)->currentAnim,\
                                    alpha)

#define RpHAnimHierarchyAddTogetherMacro(outHierarchy,inHierarchy1,inHierarchy2)\
        RtAnimInterpolatorAddTogether((outHierarchy)->currentAnim,\
                                            (inHierarchy1)->currentAnim,\
                                            (inHierarchy2)->currentAnim)


#define RpHAnimHierarchySetAnimCallBackMacro(hierarchy,callBack,time,data)\
        RtAnimInterpolatorSetAnimCallBack((hierarchy)->currentAnim,callBack,time,data)

#define RpHAnimHierarchySetAnimLoopCallBackMacro(hierarchy,callBack,data)\
        RtAnimInterpolatorSetAnimLoopCallBack((hierarchy)->currentAnim,callBack,data)

#define RpHAnimHierarchyBlendSubHierarchyMacro(outHierarchy,inHierarchy1,inHierarchy2,alpha)\
        RtAnimInterpolatorBlendSubInterpolator((outHierarchy)->currentAnim,(inHierarchy1)->currentAnim,(inHierarchy2)->currentAnim,alpha)

#define RpHAnimHierarchyAddSubHierarchyMacro(outHierarchy,mainHierarchy,subHierarchy)\
        RtAnimInterpolatorAddSubInterpolator((outHierarchy)->currentAnim,(mainHierarchy)->currentAnim,(subHierarchy)->currentAnim)

#define RpHAnimHierarchyCopyMacro(outHierarchy,inHierarchy)\
        RtAnimInterpolatorCopy((outHierarchy)->currentAnim,(inHierarchy)->currentAnim)



#ifdef RWDEBUG
extern RwBool
RpHAnimHierarchySetCurrentAnim(RpHAnimHierarchy *hierarchy,
                                RtAnimAnimation *anim);

extern RtAnimAnimation *
RpHAnimHierarchyGetCurrentAnim(RpHAnimHierarchy *hierarchy);

extern RwBool
RpHAnimHierarchySetCurrentAnimTime(RpHAnimHierarchy *hierarchy,
                                RwReal time);

extern RwBool
RpHAnimHierarchyAddAnimTime(RpHAnimHierarchy *hierarchy,
                            RwReal time);

extern RwBool
RpHAnimHierarchySubAnimTime(RpHAnimHierarchy *hierarchy,
                            RwReal time);

extern RwBool
RpHAnimHierarchySetKeyFrameCallBacks(RpHAnimHierarchy *hierarchy,
                                     RwInt32 keyFrameTypeID);

extern void
RpHAnimHierarchySetAnimCallBack(RpHAnimHierarchy *hierarchy,
                                RtAnimCallBack callBack,
                                RwReal time,
                                void *data);

extern RwBool
RpHAnimHierarchyBlend(RpHAnimHierarchy *outHierarchy,
                      RpHAnimHierarchy *inHierarchy1,
                      RpHAnimHierarchy *inHierarchy2,
                      RwReal alpha);

extern RwBool
RpHAnimHierarchyAddTogether(RpHAnimHierarchy *outHierarchy,
                            RpHAnimHierarchy *inHierarchy1,
                            RpHAnimHierarchy *inHierarchy2);

extern void
RpHAnimHierarchySetAnimLoopCallBack(RpHAnimHierarchy *hierarchy,
                                    RtAnimCallBack callBack,
                                    void *data);
extern RwBool
RpHAnimHierarchyBlendSubHierarchy(RpHAnimHierarchy *outHierarchy,
                      RpHAnimHierarchy *inHierarchy1,
                      RpHAnimHierarchy *inHierarchy2,
                      RwReal alpha);
extern RwBool
RpHAnimHierarchyAddSubHierarchy(RpHAnimHierarchy *outHierarchy,
                      RpHAnimHierarchy *mainHierarchy1,
                      RpHAnimHierarchy *subHierarchy2);
extern RwBool
RpHAnimHierarchyCopy(RpHAnimHierarchy *outHierarchy,
                     RpHAnimHierarchy *inHierarchy);

#else

#define RpHAnimHierarchySetCurrentAnim(hierarchy,anim) \
        RpHAnimHierarchySetCurrentAnimMacro((hierarchy),(anim))

#define RpHAnimHierarchyGetCurrentAnim(hierarchy) \
        RpHAnimHierarchyGetCurrentAnimMacro((hierarchy))

#define RpHAnimHierarchySetCurrentAnimTime(hierarchy,time) \
        RpHAnimHierarchySetCurrentAnimTimeMacro((hierarchy),(time))

#define RpHAnimHierarchyAddAnimTime(hierarchy,time) \
        RpHAnimHierarchyAddAnimTimeMacro((hierarchy),(time))

#define RpHAnimHierarchySubAnimTime(hierarchy,time) \
        RpHAnimHierarchySubAnimTimeMacro((hierarchy),(time))

#define RpHAnimHierarchySetKeyFrameCallBacks(hierarchy,keyFrameTypeID) \
        RpHAnimHierarchySetKeyFrameCallBacksMacro((hierarchy),(keyFrameTypeID))

#define RpHAnimHierarchyBlend(outHierarchy,inHierarchy1,inHierarchy2,alpha) \
        RpHAnimHierarchyBlendMacro((outHierarchy),(inHierarchy1),(inHierarchy2),(alpha))

#define RpHAnimHierarchyAddTogether(outHierarchy,inHierarchy1,inHierarchy2) \
        RpHAnimHierarchyAddTogetherMacro((outHierarchy),(inHierarchy1),(inHierarchy2))

#define RpHAnimHierarchySetAnimCallBack(hierarchy,callBack,time,data)\
        RpHAnimHierarchySetAnimCallBackMacro((hierarchy),(callBack),(time),(data))

#define RpHAnimHierarchySetAnimLoopCallBack(hierarchy,callBack,data)\
        RpHAnimHierarchySetAnimLoopCallBackMacro((hierarchy),(callBack),(data))

#define RpHAnimHierarchyBlendSubHierarchy(outHierarchy,inHierarchy1,inHierarchy2,alpha)\
        RpHAnimHierarchyBlendSubHierarchyMacro((outHierarchy),(inHierarchy1),(inHierarchy2),(alpha))

#define RpHAnimHierarchyAddSubHierarchy(outHierarchy,mainHierarchy,subHierarchy)\
        RpHAnimHierarchyAddSubHierarchyMacro((outHierarchy),(mainHierarchy),(subHierarchy))

#define RpHAnimHierarchyCopy(outHierarchy,inHierarchy)\
        RpHAnimHierarchyCopyMacro((outHierarchy),(inHierarchy))

#endif /* RWDEBUG */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Legacy TypeDef */


typedef RtAnimAnimation RpHAnimAnimation;
typedef RpHAnimKeyFrame RpHAnimStdKeyFrame;

/* Legacy Macros */


/* Animations */


#define RpHAnimAnimationCreate(typeID,numFrames,flags,duration)\
        RtAnimAnimationCreate((typeID),(numFrames),(flags),(duration))


#define RpHAnimAnimationDestroy(animation)\
        RtAnimAnimationDestroy((animation))

#define RpHAnimAnimationGetTypeID(animation)\
        RtAnimAnimationGetTypeID((animation))


#define RpHAnimAnimationRead(filename)\
        RtAnimAnimationRead((filename))


#define RpHAnimAnimationWrite(animation,filename)\
        RtAnimAnimationWrite((animation),(filename))


#define RpHAnimAnimationStreamRead(stream)\
        RtAnimAnimationStreamRead((stream))


#define RpHAnimAnimationStreamWrite(animation,stream)\
        RtAnimAnimationStreamWrite((animation),(stream))


#define RpHAnimAnimationStreamGetSize(animation)\
        RtAnimAnimationStreamGetSize((animation))


#define RpHAnimAnimationMakeDelta(animation,numNodes,time)\
        RtAnimAnimationMakeDelta((animation),(numNodes),(time))


/* Animation Interpolator */

#define RpHAnimHierarchyStdKeyFrameAddAnimTime(hierarchy,time)\
        RpHAnimHierarchyHAnimKeyFrameAddAnimTime((hierarchy),(time))

#define RpHAnimHierarchyHAnimKeyFrameAddAnimTime(hierarchy,time)\
        RpHAnimHierarchyAddAnimTime((hierarchy),(time))

#endif                          /* RPHANIM_H */
