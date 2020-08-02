#ifndef RTANIM_H
#define RTANIM_H

#include <rtanim.rpe>          /* automatically generated header file */

#define rtANIMSTREAMCURRENTVERSION 0x100

/* Doxygen plugin groups. */

/**
 * \defgroup rtanim RtAnim
 * \ingroup animtools
 *
 * Animation Toolkit for RenderWare Graphics.
 */

/**
 * \ingroup rtanim
 * Typedef for struct \ref RtAnimAnimation.
 */
typedef struct RtAnimAnimation RtAnimAnimation;

/*
 *  The following CallBacks are needed for each interpolation scheme.
 *  See RtAnimInterpolatorInfo.
 */

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameApplyCallBack
 * defines a callback function for converting
 * an interpolated animation keyframe into the required result. 
 *
 * \param result       Void pointer to store the output of the conversion.
 * \param voidIFrame   Void pointer to the keyframe and should be cast
 *                     to the interpolated keyframe type this callback
 *                     is for.
 */
typedef void (*RtAnimKeyFrameApplyCallBack) (void *result, void *voidIFrame);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameBlendCallBack
 * defines a callback function for blending between two
 * interpolated keyframes by the given blend factor. This is used for
 * blending the states of two different \ref RtAnimInterpolator objects.
 * The \ref RtAnimKeyFrameInterpolateCallBack is used for interpolating
 * actual animation keyframes into an interpolated frame.
 *
 * \param voidOut      Void pointer to store the output of the blend.
 * \param voidIn1      Void pointer containing the first input 
 *                      interpolated keyframe.
 * \param voidIn2      Void pointer containing the second input 
 *                      interpolated keyframe.
 * \param alpha        \ref RwReal containing the blend factor.
 */
typedef void (*RtAnimKeyFrameBlendCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2, RwReal alpha);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameInterpolateCallBack
 * defines a callback function for interpolating between two
 * animation keyframes according to the given time. The output is
 * an interpolated frame object residing in an \ref RtAnimInterpolator
 * and will usually have the same structure as the keyframe apart from
 * the header data (\ref RtAnimInterpFrameHeader).
 *
 * \param voidOut      Void pointer for the output of the interpolation.
 * \param voidIn1      Void pointer containing the first input keyframe.
 * \param voidIn2      Void pointer containing the second input keyframe.
 * \param time         \ref RwReal containing the time at which to interpolate.
 */
typedef void (*RtAnimKeyFrameInterpolateCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2, RwReal time);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameAddCallBack
 * defines a callback function for adding two interpolated 
 * keyframes together. This is used when adding the states of two
 * \ref RtAnimInterpolator objects, such as when adding a delta animation
 * to a base animation.
 *
 * \param voidOut      Void pointer for the output interpolated frame.
 * \param voidIn1      Void pointer containing the first input 
 *                      interpoalted keyframe.
 * \param voidIn2      Void pointer containing the second input 
 *                      interpolated keyframe.
 */
typedef void (*RtAnimKeyFrameAddCallBack) (void *voidOut, void *voidIn1,
                                                    void *voidIn2);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameMulRecipCallBack
 * defines a callback function for multiplying a keyframe
 * by the inverse of another keyframe. This is used for creating delta
 * animations.
 *
 * \param voidFrame Void pointer for the keyframe to be modified.
 * \param voidStart Void pointer for the start keyframe to take the reciprocal of.
 */
typedef void (*RtAnimKeyFrameMulRecipCallBack) 
                                            (void *voidFrame, void *voidStart);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameStreamReadCallBack
 * defines a callback function for reading in keyframes
 * from an \ref RwStream for the given animation.
 *
 * \param stream      Pointer to the \ref RwStream to read the keyframes from.
 * \param animation   Pointer to the \ref RtAnimAnimation to read the keyframes into.
 *
 * \return Pointer to the \ref RtAnimAnimation.
 */
typedef RtAnimAnimation * (*RtAnimKeyFrameStreamReadCallBack) 
                                (RwStream *stream, RtAnimAnimation *animation);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameStreamWriteCallBack
 * defines a callback function for writing keyframes from the
 * given animation to an \ref RwStream.
 *
 * \param animation   Pointer to the \ref RtAnimAnimation to write out from.
 * \param stream      Pointer to the \ref RwStream to write the keyframes to.
 *
 * \return \ref RwBool, TRUE if successful.
 */
typedef RwBool (*RtAnimKeyFrameStreamWriteCallBack) 
                                (RtAnimAnimation *animation, RwStream *stream);

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameStreamGetSizeCallBack
 * defines a callback function for calculating the binary stream
 * size of keyframe data within an animation.
 *
 * \param animation  Pointer to the \ref RtAnimAnimation to calculate sizes from.
 *
 * \return \ref RwInt32 containing the size, in bytes, of the keyframe data.
 */
typedef RwInt32 (*RtAnimKeyFrameStreamGetSizeCallBack) 
                                        (RtAnimAnimation *animation);

/**
 * \ingroup rtanim
 * \ref RtAnimInterpolatorInfo
 * Typedef for struct \ref RtAnimInterpolatorInfo
 */
typedef struct RtAnimInterpolatorInfo RtAnimInterpolatorInfo;

/**
 * \ingroup rtanim
 * \struct RtAnimInterpolatorInfo
 * This structure is used to hold information for a keyframe interpolation scheme.
 *
 * \see RtAnimRegisterInterpolationScheme
 * \see RtAnimGetInterpolatorInfo
 */
struct RtAnimInterpolatorInfo
{
    RwInt32                             typeID;
            /**< The ID of the interpolation scheme. */
    RwInt32                             keyFrameSize;
            /**< Size, in bytes, of the keyframe structure. */
    RtAnimKeyFrameApplyCallBack         keyFrameApplyCB;
            /**< Pointer to a function that converts a keyframe to the needed 
             * format. This function is never called from the \ref rtanim 
             * toolkit (as the toolit doesn't know the data layout of the 
             * results) but is stored to ease the creation of overloaded 
             * interpolators. */
    RtAnimKeyFrameBlendCallBack         keyFrameBlendCB;
            /**< Pointer to a function that blends between two
             *   interpolated keyframes, for the purpose of blending
             *   between the states of two \ref RtAnimInterpolator objects. */
    RtAnimKeyFrameInterpolateCallBack   keyFrameInterpolateCB;
            /**< Pointer to a function that interpolates between two keyframes 
             * for a given time in between. */
    RtAnimKeyFrameAddCallBack           keyFrameAddCB;
            /**< Pointer to a function that adds two interpolated keyframes 
             *   for the purpose of adding the states of two 
             *   \ref RtAnimInterpolator objects. */
    RtAnimKeyFrameMulRecipCallBack      keyFrameMulRecipCB;
            /**< Pointer to a function that multiplies a keyframe by the 
             * reciprocal of another. */
    RtAnimKeyFrameStreamReadCallBack    keyFrameStreamReadCB;
            /**< Pointer to a function that reads the keyframes from a stream 
             * for a given animation. */
    RtAnimKeyFrameStreamWriteCallBack   keyFrameStreamWriteCB;
            /**< Pointer to a function that writes the keyframes to a stream for
             *  a given animation. */
    RtAnimKeyFrameStreamGetSizeCallBack keyFrameStreamGetSizeCB;
            /**< Pointer to a function that returns the binary stream size of 
             * the keyframes for a given animation. */
};


/**
 * \ingroup rtanim
 * \struct RtAnimAnimation
 * A keyframed animation consists of an array of keyframe structures,
 * along with some flags and a duration.
 *
 * The keyframes should be presented in the order they are needed
 * to animate forwards through time. That is, the next keyframe
 * at some point in the sequence should correspond to the node whose
 * previous two keyframes are next to expire as an interpolation
 * pair.
 *
 * Put another way, the correct ordering can be achieved by sorting
 * an unordered keyframe array using the following primary and secondary
 * sort keys:-
 *
 * - time of previous keyframe for node
 * - node index
 *
 * An example is shown in the following diagram, where each vertical bar
 * indicates a keyframe point in time. The position of the keyframe
 * within the animation sequence is shown by an index to the left of 
 * each bar.
 *
 * \verbatim

                t=0                               t=duration
  node 0    kf0..|  kf3.......|  kf8....|  kf10....|
  node 1    kf1..|  kf4...|  kf6........|  kf11....|
  node 2    kf2..|  kf5.....|  kf7..|  kf9.........|

   \endverbatim
 *
 * Each node MUST have an initial keyframe at time = 0.0, and a terminal
 * keyframe at time = duration of the animation.
 *
 * Pointers link all of the keyframes for a particular node backwards
 * through time in a list.
 *
 * \see RtAnimAnimationCreate
 */
struct RtAnimAnimation
{
    RtAnimInterpolatorInfo              *interpInfo; 
            /**< Pointer to interpolation scheme information */
    RwInt32                             numFrames;
            /**< Number of keyframes in the animation  */
    RwInt32                             flags;
            /**< Specifies details about animation, 
             * relative translation modes etc. */
    RwReal                              duration;
            /**< Duration of animation in seconds */
    void                                *pFrames;
            /**< Pointer to the animation keyframes  */
};

/**
 * \ingroup rtanim
 * \ref RtAnimKeyFrameHeader
 * Typedef for struct RtAnimKeyFrameHeader
 */
typedef struct RtAnimKeyFrameHeader RtAnimKeyFrameHeader;

/**
 * \ingroup rtanim
 * \struct RtAnimKeyFrameHeader
 * holds header information for a keyframe. All keyframe structures used with
 * the overloadable interpolation system should start with this data.
 *
 * \see RtAnimRegisterInterpolationScheme
 */
struct RtAnimKeyFrameHeader
{
    void                                *prevFrame;
            /**< Previous keyframe for particular hierarchy node */
    RwReal                              time;
            /**< Time at keyframe  */
};

/**
 * \ingroup rtanim
 * \ref RtAnimInterpFrameHeader
 * Typedef for struct RtAnimInterpFrameHeader
 */
typedef struct RtAnimInterpFrameHeader RtAnimInterpFrameHeader;

/**
 * \ingroup rtanim
 * \struct RtAnimInterpFrameHeader
 * is the header for an interpolated animation frame, intermediate
 * between a keyframe pair.  This structure is intentionally the same size as an 
 * \ref RtAnimKeyFrameHeader, so that an interpolated frame and key frame data
 * block can be otherwise identical. It relies on the
 * fact that the prevFrame and time fields of a keyframe header are not
 * relevant to an interpolated frame. These fields should therefore not be
 * be modified by a custom keyframe interpolator.
 *
 * \see RtAnimRegisterInterpolationScheme
 */
struct RtAnimInterpFrameHeader
{
    RtAnimKeyFrameHeader    *keyFrame1;
            /**< Pointer to the first of the current pair of keyframes in
                the associated \ref RtAnimAnimation */
    RtAnimKeyFrameHeader    *keyFrame2;
            /**< Pointer to the second of the current pair of keyframes in
                the associated \ref RtAnimAnimation */
};

/**
 * \ingroup rtanim
 * \ref RtAnimInterpolator
 * Typedef for struct \ref RtAnimInterpolator
 */
typedef struct RtAnimInterpolator RtAnimInterpolator;

/**
 * \ingroup rtanim
 * \ref RtAnimCallBack
 * defines a callback function for use with the
 * \ref RtAnimInterpolatorSetAnimCallBack and
 * \ref RtAnimInterpolatorSetAnimLoopCallBack functions.
 *
 * \param  animInstance
 * A pointer to the \ref RtAnimInterpolator structure.
 *
 * \param  data   Void pointer for user-defined data.
 * You can use this to pass your own data
 * structure(s) to the callback function.
 *
 * \see RtAnimInterpolatorSetAnimCallBack
 * \see RtAnimInterpolatorSetAnimLoopCallBack
 *
 */

typedef RtAnimInterpolator * (*RtAnimCallBack)
                                        (RtAnimInterpolator *animInstance,
                                        void *data);

/**
 * \ingroup rtanim
 * \struct RtAnimInterpolator
 * holds the current state for a particular instance of an animation, 
 * corresponding to a specific point in time.
 *
 * The current interpolated keyframes are stored in an array after the
 * end of this structure. For advanced use, these may be accessed 
 * using the macro rtANIMGETINTERPFRAME(interpolator, nodeIndex)
 * which takes a pointer to the interpolator and the node index
 * for the interpolated keyframe required.
 *
 * \see \ref RtAnimInterpolatorCreate
 * \see \ref RtAnimInterpolatorDestroy
 * \see \ref RtAnimInterpolatorSetCurrentAnim
 * \see \ref RtAnimInterpolatorGetCurrentAnim
 * \see \ref RtAnimInterpolatorSetKeyFrameCallBacks
 * \see \ref RtAnimInterpolatorSetAnimLoopCallBack
 * \see \ref RtAnimInterpolatorSetAnimCallBack
 * \see \ref RtAnimInterpolatorCopy
 * \see \ref RtAnimInterpolatorSubAnimTime
 * \see \ref RtAnimInterpolatorAddAnimTime
 * \see \ref RtAnimInterpolatorSetCurrentTime
 * \see \ref RtAnimCallBack
 */
struct RtAnimInterpolator
{
    RtAnimAnimation                   *pCurrentAnim;
                                /**< Current \ref RtAnimAnimation applied */
    RwReal                              currentTime;    
                                /**< Current animation time  */
    void                                *pNextFrame;     
                                /**< Next animation keyframe to be played  */
    RtAnimCallBack                    pAnimCallBack;  
                                /**< Animation callback function pointer  */
    void                                *pAnimCallBackData;  
                                /**< Animation callback function user data  */
    RwReal                              animCallBackTime;   
                                /**< Trigger time for callback function  */
    RtAnimCallBack                    pAnimLoopCallBack; 
                                /**< Animation loop callback function pointer */
    void                                *pAnimLoopCallBackData; 
                                /**< Animation loop callback function data  */
    RwInt32                             maxKeyFrameSize;    
                                /**< Maximum size of keyframes usable on 
                                 * this animation (set at creation time) */
    RwInt32                             currentKeyFrameSize; 
                                /**< Size of keyframes in the current 
                                 * animation */
    RwInt32                             numNodes;
                                /**< Number of nodes driven by the animation */
    RwBool                              isSubInterpolator;
                                /**< Internal use */
    RwInt32                             offsetInParent;
                                /**< Internal use */
    RtAnimInterpolator           *parentAnimation;
                                /**< Internal use */

    RtAnimKeyFrameApplyCallBack       keyFrameApplyCB;    
                                /**< Internal use */
    RtAnimKeyFrameBlendCallBack       keyFrameBlendCB;       
                                /**< Internal use */
    RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB; 
                                /**< Internal use */
    RtAnimKeyFrameAddCallBack         keyFrameAddCB;         
                                /**< Internal use */
};                

/* Access to array of interpolated frames occupying a block of memory
 * after the end of the RtAnimInterpolator structure.
 */
#define rtANIMGETINTERPFRAME( anim, nodeIndex )                              \
        ( (void *)( ( (RwUInt8 *)&(anim[1]) +                                  \
                      ((nodeIndex) *                                           \
                       anim->currentKeyFrameSize) ) ) )

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */


/* Engine functions */
extern void
RtAnimAnimationFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern RwBool
RtAnimInitialize(void);

extern RwBool
RtAnimRegisterInterpolationScheme(RtAnimInterpolatorInfo *interpolatorInfo);

extern RtAnimInterpolatorInfo *
RtAnimGetInterpolatorInfo(RwInt32 typeID);

/* RtAnimAnimation */
extern RtAnimAnimation  *
RtAnimAnimationCreate(RwInt32 typeID,
                       RwInt32 numFrames,
                       RwInt32 flags,
                       RwReal duration);

extern RtAnimAnimation  *
RtAnimAnimationDestroy(RtAnimAnimation *animation);

extern RtAnimAnimation  *
RtAnimAnimationRead(const RwChar * filename);

extern              RwBool
RtAnimAnimationWrite(RtAnimAnimation *animation,
                      const RwChar * filename);

extern RtAnimAnimation  *
RtAnimAnimationStreamRead(RwStream *stream);

extern RwBool
RtAnimAnimationStreamWrite(RtAnimAnimation *animation,
                            RwStream *stream);

extern RwInt32
RtAnimAnimationStreamGetSize(RtAnimAnimation *animation);

extern RwUInt32
RtAnimAnimationGetNumNodes(RtAnimAnimation *animation);

#ifdef RWDEBUG

extern RwInt32
RtAnimAnimationGetTypeID(RtAnimAnimation *animation);

#else  /* RWDEBUG */

#define RtAnimAnimationGetTypeID(animation)  \
    (animation->interpInfo->typeID)

#endif /* RWDEBUG */

/* RtAnimInterpolator */
extern RtAnimInterpolator *
RtAnimInterpolatorCreate(RwInt32 numNodes, 
                                RwInt32 maxKeyFrameSize);

extern void
RtAnimInterpolatorDestroy(RtAnimInterpolator *anim);

extern RwBool
RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator *animI,
                               RtAnimAnimation *anim);


#ifdef RWDEBUG

extern RtAnimAnimation *
RtAnimInterpolatorGetCurrentAnim(RtAnimInterpolator *animI);

#else  /* RWDEBUG */

#define RtAnimInterpolatorGetCurrentAnim(animI)  \
    (animI->pCurrentAnim)

#endif /* RWDEBUG */


extern RwBool
RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator *anim,
                                     RwInt32 keyFrameTypeID);


extern void
RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator *anim,
                                    RtAnimCallBack callBack,
                                    void *data );

extern void
RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator *anim,
                                RtAnimCallBack callBack,
                                RwReal time,
                                void *data );

extern RwBool
RtAnimInterpolatorCopy(RtAnimInterpolator *outAnim,
                              RtAnimInterpolator *inAnim);

extern RwBool
RtAnimInterpolatorSubAnimTime(RtAnimInterpolator *anim,
                            RwReal time);

extern RwBool
RtAnimInterpolatorAddAnimTime(RtAnimInterpolator *anim,
                            RwReal time);

extern RwBool
RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator *anim,
                                   RwReal time);

extern RwBool
RtAnimAnimationMakeDelta(RtAnimAnimation *animation,
                          RwInt32 numNodes,
                          RwReal time);


extern RwBool
RtAnimInterpolatorBlend(RtAnimInterpolator *outAnim,
                                RtAnimInterpolator *inAnim1,
                                RtAnimInterpolator *inAnim2,
                                RwReal alpha);

extern RwBool
RtAnimInterpolatorAddTogether(RtAnimInterpolator *outAnim,
                                        RtAnimInterpolator *inAnim1,
                                        RtAnimInterpolator *inAnim2);
        
#define RtAnimKeyFrameApplyMacro(animation, out, in)                         \
MACRO_START                                                                    \
{                                                                              \
    (anim)->keyFrameApplyCB((out), (in1), (in2), (time));                      \
}                                                                              \
MACRO_STOP


#define RtAnimKeyFrameInterpolateMacro(anim, out, in1, in2, time)            \
MACRO_START                                                                    \
{                                                                              \
    (anim)->keyFrameInterpolateCB((out), (in1), (in2), (time));                \
}                                                                              \
MACRO_STOP

#define RtAnimKeyFrameBlendMacro(anim, out, in1, in2, fAlpha)                \
MACRO_START                                                                    \
{                                                                              \
    (anim)->keyFrameBlendCB((out), (in1), (in2), (fAlpha));                    \
}                                                                              \
MACRO_STOP

#define RtAnimKeyFrameAddTogetherMacro(anim, out, in1, in2)                  \
MACRO_START                                                                    \
{                                                                              \
    (anim)->keyFrameAddCB((out), (in1), (in2));                                \
}                                                                              \
MACRO_STOP

#ifdef RWDEBUG
extern void
RtAnimKeyFrameApply(RtAnimInterpolator *animation,
                     void *result, void *iFrame);

extern void
RtAnimKeyFrameInterpolate(RtAnimInterpolator *animation,
                        void *out, void *in1,
                        void *in2, RwReal time);

extern void
RtAnimKeyFrameBlend(RtAnimInterpolator *animation,
                  void *out,
                  void *in1,
                  void *in2,
                  RwReal alpha);

extern void
RtAnimKeyFrameAddTogether(RtAnimInterpolator *animation,
                        void *out, void *in1, void *in2);

#else /* RWDEBUG */
#define RtAnimKeyFrameApply(animation, out, in) \
        RtAnimKeyFrameApplyMacro(animation, out, in)
                
#define RtAnimKeyFrameInterpolate(animation, out, in1, in2, time) \
        RtAnimKeyFrameInterpolateMacro(animation, out, in1, in2, time)

#define RtAnimKeyFrameBlend(animation, out, in1, in2, alpha)    \
        RtAnimKeyFrameBlendMacro(animation, out, in1, in2, alpha)

#define RtAnimKeyFrameAddTogether(animation, out, in1, in2)      \
        RtAnimKeyFrameAddTogetherMacro(animation, out, in1, in2)
#endif /* RWDEBUG */

extern RtAnimInterpolator *
RtAnimInterpolatorCreateSubInterpolator(
                                        RtAnimInterpolator *parentAnim,
                                        RwInt32 startNode,
                                        RwInt32 numNodes,
                                        RwInt32 maxKeyFrameSize);

extern RwBool
RtAnimInterpolatorBlendSubInterpolator(RtAnimInterpolator *outAnim,
                                            RtAnimInterpolator *inAnim1,
                                            RtAnimInterpolator *inAnim2,
                                            RwReal alpha);

extern RwBool
RtAnimInterpolatorAddSubInterpolator(RtAnimInterpolator *outAnim,
                                RtAnimInterpolator *mainAnim,
                                RtAnimInterpolator *subAnim);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RTANIM_H */
