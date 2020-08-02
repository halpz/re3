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
 * \ingroup rpplugin
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

#define rpHANIMSTREAMCURRENTVERSION 0x100

/**
 * \ingroup rphanim
 * \ref RpHAnimAtomicGlobalVars typedef for struct RpHAnimAtomicGlobalVars
 */
typedef struct RpHAnimAtomicGlobalVars RpHAnimAtomicGlobalVars;

/**
 * \ingroup rphanim
 * \struct RpHAnimAtomicGlobalVars
 */
struct RpHAnimAtomicGlobalVars
{
        RwInt32   engineOffset     ;  /* Offset into global data */
        RwFreeList *HAnimFreeList;
        RwFreeList *HAnimAnimationFreeList;
};

extern RpHAnimAtomicGlobalVars RpHAnimAtomicGlobals;

#define rpHANIMSTDKEYFRAMESIZE sizeof(RpHAnimStdKeyFrame)
#define rpHANIMSTDKEYFRAMETYPEID 0x1

#define RwAnimMalloc()                                                  \
    RwFreeListAlloc(RpHAnimAtomicGlobals.HAnimFreeList)

#define RwAnimFree(_anim)                                               \
    RwFreeListFree(RpHAnimAtomicGlobals.HAnimFreeList, (_anim))

#define RwAnimAnimationMalloc()                                         \
    RwFreeListAlloc(RpHAnimAtomicGlobals.HAnimAnimationFreeList)

#define RwAnimAnimationFree(_animAnimation)                             \
    RwFreeListFree(RpHAnimAtomicGlobals.HAnimAnimationFreeList,         \
                   (_animAnimation))

#define RpV3dInterpolate(o, a, s, b)                            \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) + ((s)) * (((b)->x) - ((a)->x)));        \
    (o)->y = (((a)->y) + ((s)) * (((b)->y) - ((a)->y)));        \
    (o)->z = (((a)->z) + ((s)) * (((b)->z) - ((a)->z)));        \
}                                                               \
MACRO_STOP

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchy typedef for struct RpHAnimHierarchy
 */
typedef struct RpHAnimHierarchy RpHAnimHierarchy;

/**
 * \ingroup rphanim
 * \ref RpHAnimAnimation typedef for struct RpHAnimAnimation
 */
typedef struct RpHAnimAnimation RpHAnimAnimation;

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchyCallBack
 * This typedef defines a callback function for use with the
 * \ref RpHAnimHierarchySetAnimCallBack and
 * \ref RpHAnimHierarchySetAnimLoopCallBack functions.
 *
 * \param  hierarchy
 * A pointer to the AnimHierarchy structure.
 *
 * \param  data   User-defined data.
 * You can use this to pass your own data
 * structure(s) to the callback function.
 *
 * \see RpHAnimHierarchySetAnimCallBack
 * \see RpHAnimHierarchySetAnimLoopCallBack
 *
 */

typedef RpHAnimHierarchy * (*RpHAnimHierarchyCallBack) (RpHAnimHierarchy *hierarchy,
                                                        void *data);

/*
 *  The following CallBacks are needed for each overloaded interpolation
 *  scheme. See RpHAnimInterpolatorInfo.
 */

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameToMatrixCallBack
 * This typedef defines a callback function for converting
 * an animation keyframe into a modeling matrix. The output matrix will be
 * used to construct the array of world or local space matrices for the
 * hierarchy as obtained with \ref RpHAnimHierarchyGetMatrixArray, and
 * possibly used for updating an external \ref RwFrame hierarchy.
 *
 * \param matrix       This is the matrix to store the output of the conversion
 * \param voidIFrame   This is a void pointer to the keyframe and should be cast
 *                     to the keyframe type this callback is for.
 */
typedef void (*RpHAnimKeyFrameToMatrixCallBack) (RwMatrix *matrix, void *voidIFrame);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameBlendCallBack
 * This typedef defines a callback function for blending between two animation
 * keyframes by the given blend factor.
 *
 * \param voidOut      This is the void pointer for the output of the blend
 * \param voidIn1      First input keyframe
 * \param voidIn2      Second input keyframe
 * \param alpha        Blend factor
 */
typedef void (*RpHAnimKeyFrameBlendCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2, RwReal alpha);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameInterpolateCallBack
 * This typedef defines a callback function for interpolating between two
 * animation keyframes according to the given time.
 *
 * \param voidOut      This is the void pointer for the output of the
 *                     interpolation
 * \param voidIn1      First input keyframe
 * \param voidIn2      Second input keyframe
 * \param time         Time at which to interpolate
 */
typedef void (*RpHAnimKeyFrameInterpolateCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2, RwReal time);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameAddCallBack
 * This typedef defines a callback function for adding together two animation
 * keyframes. One of the keyframes would usually be a delta.
 *
 * \param voidOut      This is the void pointer for the output summed keyframe
 * \param voidIn1      First input keyframe
 * \param voidIn2      Second input keyframe
 */
typedef void (*RpHAnimKeyFrameAddCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameMulRecipCallBack
 * This typedef defines a callback function for multiplying a keyframe
 * by the inverse of another keyframe
 *
 * \param voidFrame This is the void pointer for the keyframe to be modified
 * \param voidStart First start keyframe to take the reciprocal of.
 */
typedef void (*RpHAnimKeyFrameMulRecipCallBack) (void *voidFrame, void *voidStart);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameStreamReadCallBack
 * This typedef defines a callback function for reading in keyframes
 * from an \ref RwStream for the given animation.
 *
 * \param stream        The stream to read the keyframes from
 * \param animation   The animation to read the keyframes into
 *
 * \return Pointer to the animation.
 */
typedef RpHAnimAnimation * (*RpHAnimKeyFrameStreamReadCallBack) (RwStream *stream, RpHAnimAnimation *animation);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameStreamWriteCallBack
 * This typedef defines a callback function for writing keyframes from the
 * given animation to an \ref RwStream.
 *
 * \param animation   The animation to write out from
 * \param stream        The stream to write the keyframes to
 *
 * \return TRUE if successful.
 */
typedef RwBool (*RpHAnimKeyFrameStreamWriteCallBack) (RpHAnimAnimation *animation, RwStream *stream);

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameStreamGetSizeCallBack
 * This typedef defines a callback function for calculating the binary stream
 * size of keyframe data within an animation.
 *
 * \param animation   The animation to calculate sizes of
 *
 * \return Size in bytes of the keyframe data.
 */
typedef RwInt32 (*RpHAnimKeyFrameStreamGetSizeCallBack) (RpHAnimAnimation *animation);

/**
 * \ingroup rphanim
 * \ref RpHAnimInterpolatorInfo
 * typedef for struct \ref RpHAnimInterpolatorInfo
 */
typedef struct RpHAnimInterpolatorInfo RpHAnimInterpolatorInfo;

/**
 * \ingroup rphanim
 * \struct RpHAnimInterpolatorInfo
 * This is used to hold information for a keyframe interpolation scheme.
 *
 * \see RpHAnimRegisterInterpolationScheme
 * \see RpHAnimGetInterpolatorInfo
 */
struct RpHAnimInterpolatorInfo
{
    RwInt32     typeID;         /**< The ID of the interpolation scheme */
    RwInt32     keyFrameSize;   /**< Size in bytes of the keyframe structure */
    RpHAnimKeyFrameToMatrixCallBack keyFrameToMatrixCB;     /**< Pointer to a function that converts a keyframe to a matrix */
    RpHAnimKeyFrameBlendCallBack keyFrameBlendCB;   /**< Pointer to a function that blends between a pair of keyframes for a given delta value */
    RpHAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;   /**< Pointer to a function that interpolates between two keyframes for a given time in between */
    RpHAnimKeyFrameAddCallBack keyFrameAddCB; /**< Pointer to a function that adds two keyframes (one of which may be a delta) */
    RpHAnimKeyFrameMulRecipCallBack keyFrameMulRecipCB;  /**< Pointer to a function that multiplies a keyframe by the reciprocal of another */
    RpHAnimKeyFrameStreamReadCallBack keyFrameStreamReadCB; /**< Pointer to a function that reads the keyframes from a stream for a given animation */
    RpHAnimKeyFrameStreamWriteCallBack keyFrameStreamWriteCB; /**< Pointer to a function that writes the keyframes to a stream for a given animation */
    RpHAnimKeyFrameStreamGetSizeCallBack keyFrameStreamGetSizeCB; /**< Pointer to a function that returns the binary stream size of the keyframes for a given animation */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimKeyFrameHeader
 * typedef for struct RpHAnimKeyFrameHeader
 */
typedef struct RpHAnimKeyFrameHeader RpHAnimKeyFrameHeader;

/**
 * \ingroup rphanim
 * \struct RpHAnimKeyFrameHeader
 * Holds header information for a keyframe. All keyframe structures used with
 * the overloadable interpolation system should start with this data.
 *
 * \see RpHAnimStdKeyFrame
 * \see RpHAnimRegisterInterpolationScheme
 */
struct RpHAnimKeyFrameHeader
{
    void   *prevFrame; /**< Previous keyframe for particular hierarchy node */
    RwReal time;       /**< Time at keyframe  */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimStdKeyFrame
 * typedef for struct RpHAnimStdKeyFrame
 */
typedef struct RpHAnimStdKeyFrame RpHAnimStdKeyFrame;

/**
 * \ingroup rphanim
 * \struct RpHAnimStdKeyFrame
 * A structure representing the standard keyframe data. Sequences of
 * such keyframes in an \ref RpHAnimAnimation defines the animation of each
 * node in a hierarchy.
 */
struct RpHAnimStdKeyFrame
{
    RpHAnimStdKeyFrame *prevFrame;  /**< Previous keyframe for particular hierarchy node  */
    RwReal              time;       /**< Time at keyframe  */
    RtQuat              q;          /**< Quaternion rotation at keyframe  */
    RwV3d               t;          /**< Translation at keyframe  */
};

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
 */
struct RpHAnimNodeInfo
{
    RwInt32     nodeID;    /**< User defined ID for this node  */
    RwInt32     nodeIndex; /**< Array index of node  */
    RwInt32     flags;      /**< Matrix push/pop flags  */
    RwFrame *   pFrame;     /**< Pointer to an attached RwFrame (see \ref RpHAnimHierarchyAttach) */
};

/**
 * \ingroup rphanim
 * \struct RpHAnimAnimation
 * A hierarchical animation consists of an array of keyframe structures,
 * along with some flags and a duration.
 *
 * The keyframes should be presented in the order they are needed
 * to animate forwards through time.  Pointers link all of the keyframes
 * for a particular node backwards through time in a list.
 *
 * For example, a 3 node animation, with keyframes at the following times:
 *
 * Node 1: 0.0, 1.0, 2.0, 3.0
 * Node 2: 0.0, 3.0
 * Node 3: 0.0, 2.0, 2.5, 3.0
 *
 * should be formatted in an RpHAnimAnimation animation like this:
 *
 * B1,0.0 B2,0.0 B3,0.0 B1,1.0, B2,3.0, B3,2.0, B1,2.0, B1,3.0, B3,2.5 B3,3.0
 *
 * Each node MUST start at time = 0.0, and each node must terminate with a keyframe
 * at time = duration of animation.
 *
 * \see RpHAnimAnimationCreate
 */
struct RpHAnimAnimation
{
    RpHAnimInterpolatorInfo    *interpInfo; /**< Pointer to interpolation scheme information */
    RwInt32                     numFrames;  /**< Number of keyframes in the animation  */
    RwInt32                     flags;      /**< Specifies details about animation, relative translation modes etc */
    RwReal                      duration;   /**< Duration of animation in seconds */
    void                       *pFrames;    /**< Pointer to the animation keyframes  */
};

/**
 * \ingroup rphanim
 * \ref RpHAnimHierarchyFlag defines type and update modes in HAnimHierarchies
 *
 * \see RpAnimHierarchyFlag
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

/**
 * \ingroup rphanim
 * \typedef RpHAnimHierarchyFlag
 * These flags are used to control the creation and
 * update status of the hierarchy
 */
typedef enum RpHAnimHierarchyFlag RpHAnimHierarchyFlag;

/**
 * \ingroup rphanim
 * \struct RpHAnimHierarchy
 * An RpHAnimHierarchy is used to "play back" an animation - it holds the
 * interpolated keyframe data for the current state of an animation
 * concatenated on the end of the structure.
 *
 * The rpHANIMHIERARCHYGETINTERPFRAME() macro can be used to access the current
 * interpolated data, for the current time or to write to this data to override
 * it with procedural animation.
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
    RpHAnimAnimation   *pCurrentAnim;  /**< Current animation applied to hierarchy  */
    RwReal              currentTime;    /**< Current animation time  */
    void               *pNextFrame;     /**< Next animation keyframe to be played  */
    RpHAnimHierarchyCallBack pAnimCallBack;  /**< Animation callback function pointer  */
    void               *pAnimCallBackData;  /**< Animation callback function user data  */
    RwReal              animCallBackTime;   /**< Trigger time for callback function  */
    RpHAnimHierarchyCallBack pAnimLoopCallBack; /**< Animation loop callback function pointer  */
    void               *pAnimLoopCallBackData; /**< Animation loop callback function data  */
    RwMatrix           *pMatrixArray;   /**< Pointer to node matrices*/
    void               *pMatrixArrayUnaligned; /**< Pointer to memory used for node matrices
                                                * from which the aligned pMatrixArray is allocated */
    RpHAnimNodeInfo    *pNodeInfo;     /**< Array of node information (push/pop flags etc) */
    RwFrame            *parentFrame;    /**< Pointer to the Root RwFrame of the hierarchy this
                                           * RpHAnimHierarchy represents */
    RwInt32             maxKeyFrameSize;    /**< Maximum size of keyframes usable on this hierarhcy
                                               * (set at creation time) */
    RwInt32             currentKeyFrameSize; /**< Size of keyframes in the current animation */
    RpHAnimKeyFrameToMatrixCallBack     keyFrameToMatrixCB;    /**< Internal use */
    RpHAnimKeyFrameBlendCallBack        keyFrameBlendCB;       /**< Internal use */
    RpHAnimKeyFrameInterpolateCallBack  keyFrameInterpolateCB; /**< Internal use */
    RpHAnimKeyFrameAddCallBack          keyFrameAddCB;         /**< Internal use */
    RpHAnimHierarchy   *parentHierarchy;                       /**< Internal use */
    RwInt32             offsetInParent;                        /**< Internal use */
    RwInt32             rootParentOffset;                      /**< Internal use */
};

#define rpHANIMHIERARCHYGETINTERPFRAME( hierarchy, nodeIndex )    \
        ( (void *)( ( (RwUInt8 *)&(hierarchy[1]) +                \
                      ((nodeIndex) *                               \
                       hierarchy->currentKeyFrameSize) ) ) )

#define rpHANIMHIERARCHYGETINTERPFRAME1( hierarchy, nodeIndex )   \
        ( (void *)( ( (RwUInt8 *)&(hierarchy[1]) +                \
                      ((hierarchy->numNodes +                     \
                        (nodeIndex)) *                             \
                       hierarchy->currentKeyFrameSize) ) ) )

#define rpHANIMHIERARCHYGETINTERPFRAME2( hierarchy, nodeIndex )   \
        ( (void *)( ( (RwUInt8 *)&(hierarchy[1]) +                \
                      ((hierarchy->numNodes * 2 +                 \
                        (nodeIndex)) *                             \
                       hierarchy->currentKeyFrameSize) ) ) )

/**
 * \ingroup rphanim
 * \ref RpHAnimFrameExtension typedef for struct RpHAnimFrameExtension
 */

typedef struct RpHAnimFrameExtension RpHAnimFrameExtension;

/**
 * \ingroup rphanim
 * \struct RpHAnimFrameExtension
 */
struct RpHAnimFrameExtension
{
    RwInt32          id;        /**< ID given to this RwFrame (default of -1) */
    RpHAnimHierarchy *hierarchy; /**< Pointer to Animation hierarchy attached to this RwFrame */
};

/*--- Plugin API Functions ---*/

#define RpHAnimHierarchySetFlagsMacro(hierarchy, _flags)       \
MACRO_START                                                     \
{                                                               \
    (hierarchy)->flags = _flags;                               \
}                                                               \
MACRO_STOP

#define RpHAnimHierarchyGetFlagsMacro(hierarchy) \
    ((hierarchy)->flags)

#define RpHAnimStdKeyFrameToMatrixMacro(_matrix, _voidIFrame)           \
MACRO_START                                                             \
{                                                                       \
    RpHAnimStdKeyFrame * iFrame = (RpHAnimStdKeyFrame *)(_voidIFrame);  \
                                                                        \
    /*                                                                  \
     * RpHAnim uses the same types of quaternion as RtQuat              \
     *  hence no conjugate call as in RpSkin                            \
     */                                                                 \
                                                                        \
    RtQuatUnitConvertToMatrix(&iFrame->q, (_matrix));                   \
                                                                        \
    (_matrix)->pos.x = iFrame->t.x;                                     \
    (_matrix)->pos.y = iFrame->t.y;                                     \
    (_matrix)->pos.z = iFrame->t.z;                                     \
}                                                                       \
MACRO_STOP


#if (! defined(RWDEBUG))

#define RpHAnimHierarchySetFlags(hierarchy, _flags) \
        RpHAnimHierarchySetFlagsMacro(hierarchy, _flags)

#define RpHAnimHierarchyGetFlags(hierarchy) \
        (RpHAnimHierarchyFlag)RpHAnimHierarchyGetFlagsMacro(hierarchy)

#endif /* (! defined(RWDEBUG)) */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

#if (defined(RWDEBUG))

extern RpHAnimHierarchy *
RpHAnimHierarchySetFlags(RpHAnimHierarchy *hierarchy,
                         RpHAnimHierarchyFlag flags);

extern RpHAnimHierarchyFlag
RpHAnimHierarchyGetFlags(RpHAnimHierarchy *hierarchy);

#endif /* (defined(RWDEBUG))  */

/* Keyframe Interpolator Types */

extern RwBool
RpHAnimRegisterInterpolationScheme(RpHAnimInterpolatorInfo *interpolatorInfo);

extern RpHAnimInterpolatorInfo *
RpHAnimGetInterpolatorInfo(RwInt32 typeID);

/* Animation hierarchy creation */

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
#define RpHAnimSetHierarchy(frame, hierarchy) \
                        RpHAnimFrameSetHierarchy(frame, hierarchy)
#define RpHAnimGetHierarchy(frame) RpHAnimFrameGetHierarchy(frame)

extern RwBool
RpHAnimHierarchySetKeyFrameCallBacks(RpHAnimHierarchy *hierarchy,
                                     RwInt32 keyFrameTypeID);

extern RwBool
RpHAnimHierarchySetCurrentAnim(RpHAnimHierarchy *hierarchy,
                               RpHAnimAnimation *anim);

extern RwBool
RpHAnimHierarchySetCurrentAnimTime(RpHAnimHierarchy *hierarchy,
                                   RwReal time);

extern RwBool
RpHAnimHierarchySubAnimTime(RpHAnimHierarchy *hierarchy,
                            RwReal time);

extern RwBool
RpHAnimHierarchyStdKeyFrameAddAnimTime(RpHAnimHierarchy *hierarchy,
                                       RwReal time);

extern RwBool
RpHAnimHierarchyAddAnimTime(RpHAnimHierarchy *hierarchy,
                            RwReal time);

extern RpHAnimHierarchy *
RpHAnimHierarchySetAnimCallBack(RpHAnimHierarchy *hierarchy,
                                RpHAnimHierarchyCallBack callBack,
                                RwReal time,
                                void *data );

extern RpHAnimHierarchy *
RpHAnimHierarchySetAnimLoopCallBack(RpHAnimHierarchy *hierarchy,
                                    RpHAnimHierarchyCallBack callBack,
                                    void *data );

extern RwMatrix *
RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy *hierarchy);

extern RwBool
RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy *hierarchy);

/* Macro for legacy support of old function name */
#define RpHAnimUpdateHierarchyMatrices RpHAnimHierarchyUpdateMatrices

extern RwInt32
RpHAnimIDGetIndex(RpHAnimHierarchy *hierarchy,
                  RwInt32 ID);

/* Animations */

extern RpHAnimAnimation  *
RpHAnimAnimationCreate(RwInt32 typeID,
                       RwInt32 numFrames,
                       RwInt32 flags,
                       RwReal duration);

extern RpHAnimAnimation  *
RpHAnimAnimationDestroy(RpHAnimAnimation *animation);

#ifdef RWDEBUG

extern RwInt32
RpHAnimAnimationGetTypeID(RpHAnimAnimation *animation);

#else  /* RWDEBUG */

#define RpHAnimAnimationGetTypeID(animation)  \
    (animation->interpInfo->typeID)

#endif /* RWDEBUG */

extern RpHAnimAnimation  *
RpHAnimAnimationRead(const RwChar * filename);

extern              RwBool
RpHAnimAnimationWrite(RpHAnimAnimation *animation,
                      const RwChar * filename);

extern RpHAnimAnimation  *
RpHAnimAnimationStreamRead(RwStream *stream);

extern RwBool
RpHAnimAnimationStreamWrite(RpHAnimAnimation *animation,
                            RwStream *stream);

extern RwInt32
RpHAnimAnimationStreamGetSize(RpHAnimAnimation *animation);

extern RwBool
RpHAnimAnimationMakeDelta(RpHAnimAnimation *animation,
                          RwInt32 numNodes,
                          RwReal time);

/* Plugin support */

extern RwBool
RpHAnimPluginAttach(void);

/* Overloadable keyframe functions */

#define RpHAnimFrameToMatrixMacro(hierarchy, matrix, iFrame)    \
MACRO_START                                                     \
{                                                               \
    const RpHAnimKeyFrameToMatrixCallBack keyFrameToMatrixCB =  \
        (hierarchy)->keyFrameToMatrixCB;                        \
                                                                \
    if (RpHAnimStdKeyFrameToMatrix == keyFrameToMatrixCB)       \
    {                                                           \
        RpHAnimStdKeyFrameToMatrixMacro((matrix), (iFrame));    \
    }                                                           \
    else                                                        \
    {                                                           \
        keyFrameToMatrixCB((matrix), (iFrame));                 \
    }                                                           \
}                                                               \
MACRO_STOP

#define RpHAnimFrameInterpolateMacro(hierarchy, out, in1, in2, time)    \
MACRO_START                                                             \
{                                                                       \
    (hierarchy)->keyFrameInterpolateCB((out), (in1), (in2), (time));    \
}                                                                       \
MACRO_STOP

#define RpHAnimFrameBlendMacro(hierarchy, out, in1, in2, fAlpha)        \
MACRO_START                                                             \
{                                                                       \
    (hierarchy)->keyFrameBlendCB((out), (in1), (in2), (fAlpha));        \
}                                                                       \
MACRO_STOP

#define RpHAnimFrameAddTogetherMacro(hierarchy, out, in1, in2)          \
MACRO_START                                                             \
{                                                                       \
    (hierarchy)->keyFrameAddCB((out), (in1), (in2));                    \
}                                                                       \
MACRO_STOP

#ifdef RWDEBUG
void
RpHAnimFrameInterpolate(RpHAnimHierarchy *hierarchy,
                        void *out, void *in1,
                        void *in2, RwReal time);

void
RpHAnimFrameBlend(RpHAnimHierarchy *hierarchy,
                  void *out,
                  void *in1,
                  void *in2,
                  RwReal alpha);

void
RpHAnimFrameToMatrix(RpHAnimHierarchy *hierarchy,
                     RwMatrix *matrix, void *iFrame);

void
RpHAnimFrameAddTogether(RpHAnimHierarchy *hierarchy,
                        void *out, void *in1, void *in2);

#else /* RWDEBUG */

#define RpHAnimFrameToMatrix(hierarchy, matrix, iFrame) \
        RpHAnimFrameToMatrixMacro(hierarchy, matrix, iFrame)

#define RpHAnimFrameInterpolate(hierarchy, out, in1, in2, time) \
        RpHAnimFrameInterpolateMacro(hierarchy, out, in1, in2, time)

#define RpHAnimFrameBlend(hierarchy, out, in1, in2, alpha)    \
        RpHAnimFrameBlendMacro(hierarchy, out, in1, in2, alpha)

#define RpHAnimFrameAddTogether(hierarchy, out, in1, in2)      \
        RpHAnimFrameAddTogetherMacro(hierarchy, out, in1, in2)

#endif /* RWDEBUG */

/* Standard keyframe functions */

extern void
RpHAnimStdKeyFrameToMatrix(RwMatrix *matrix,
                           void * voidIFrame);

extern void
RpHAnimStdKeyFrameBlend(void *voidOut,
                        void *voidIn1,
                        void *voidIn2,
                        RwReal alpha);

extern void
RpHAnimStdKeyFrameInterpolate(void *voidOut,
                              void *voidIn1,
                              void *voidIn2,
                              RwReal time);

extern void
RpHAnimStdKeyFrameAdd(void *voidOut,
                      void *voidIn1,
                      void *voidIn2);

extern void
RpHAnimStdKeyFrameMulRecip(void *voidFrame,
                           void *voidStart);

extern RpHAnimAnimation *
RpHAnimStdKeyFrameStreamRead(RwStream *stream,
                             RpHAnimAnimation *animation);

extern RwBool
RpHAnimStdKeyFrameStreamWrite(RpHAnimAnimation *animation,
                              RwStream *stream);

extern RwInt32
RpHAnimStdKeyFrameStreamGetSize(RpHAnimAnimation *animation);

/* Hierarchy blending/combination functions */

extern RwBool
RpHAnimHierarchyBlend(RpHAnimHierarchy *outHierarchy,
                      RpHAnimHierarchy *inHierarchy1,
                      RpHAnimHierarchy *inHierarchy2,
                      RwReal alpha);
extern RwBool
RpHAnimHierarchyAddTogether(RpHAnimHierarchy *outHierarchy,
                            RpHAnimHierarchy *inHierarchy1,
                            RpHAnimHierarchy *inHierarchy2);

extern RwBool
RpHAnimHierarchyBlendSubHierarchy(RpHAnimHierarchy *outHierarchy,
                                  RpHAnimHierarchy *inHierarchy1,
                                  RpHAnimHierarchy *inHierarchy2,
                                  RwReal alpha);
extern RwBool
RpHAnimHierarchyAddSubHierarchy(RpHAnimHierarchy *outHierarchy,
                                RpHAnimHierarchy *mainHierarchy,
                                RpHAnimHierarchy *subHierarchy);

extern RwBool
RpHAnimHierarchyCopy(RpHAnimHierarchy *outHierarchy,
                     RpHAnimHierarchy *inHierarchy);

/* Access to RwFrame ID's */

extern RwBool
RpHAnimFrameSetID(RwFrame *frame,
                  RwInt32 id);

extern RwInt32
RpHAnimFrameGetID(RwFrame *frame);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#endif                          /* RPHANIM_H */
