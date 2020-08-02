/***************************************************************************
 *                                                                         *
 * Module  : rt2danim.h                                                    *
 *                                                                         *
 * Purpose : .                                                             *
 *                                                                         *
 **************************************************************************/

#ifndef RT2DANIM_H
#define RT2DANIM_H

/**
 * \defgroup rt2danim Rt2dAnim (inc. Maestro)
 * \ingroup 2dtools
 *
 * A toolkit to coordinate the display, storage and manipulation of 2D
 * animations.
 */

/**
 * \defgroup rt2danimsub Rt2dAnim
 * \ingroup rt2danim
 *
 * Animation functions
 */

/**
 * \defgroup rt2dmaestro Rt2dMaestro
 * \ingroup rt2danim
 *
 * Maestro functions
 */

/**
 * \defgroup rt2dstringlabel Rt2dStringLabel
 * \ingroup rt2danim
 *
 * String labels
 */

/**
 * \defgroup rt2dmessage Rt2dMessage
 * \ingroup rt2danim
 *
 * Messages
 */

/**
 * \defgroup rt2dbutton Rt2dButton
 * \ingroup rt2danim
 *
 * Buttons
 */

/**
 * \defgroup rt2dcel Rt2dCel
 * \ingroup rt2danim
 *
 * Cels
 */

/****************************************************************************
 Includes
 */

#include <rwcore.h>
#include "rt2danim.rpe"    /* automatically generated header file */
#include "rt2d.h"
#include "rpcriter.h"
/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

#define RT2D_BUTTON_MAX_STATES                  4
#define RT2D_BUTTON_MAX_STATE_TRANSITIONS       32

/* Button state flags. */

#define rt2dANIMBUTTONSTATEPICKREGION        0x0001
#define rt2dANIMBUTTONSTATEUP                0x0002
#define rt2dANIMBUTTONSTATEDOWN              0x0004
#define rt2dANIMBUTTONSTATEOVER              0x0008

#define rt2dANIMBUTTONSTATEIDLETOOVERUP      0x0010
#define rt2dANIMBUTTONSTATEOVERUPTOIDLE      0x0020
#define rt2dANIMBUTTONSTATEOVERUPTOOVERDOWN  0x0040
#define rt2dANIMBUTTONSTATEOVERDOWNTOOVERUP  0x0080
#define rt2dANIMBUTTONSTATEOVERDOWNTOOUTDOWN 0x0100
#define rt2dANIMBUTTONSTATEOUTDOWNTOOVERDOWN 0x0200
#define rt2dANIMBUTTONSTATEOUTDOWNTOIDLE     0x0400
#define rt2dANIMBUTTONSTATEIDLETOOVERDOWN    0x0800
#define rt2dANIMBUTTONSTATEOVERDOWNTOIDLE    0x1000


/* Mask to separate trans state in state flag. */
#define rt2dANIMBUTTONSTATEMASK                \
            (rt2dANIMBUTTONSTATEPICKREGION |   \
             rt2dANIMBUTTONSTATEPICKUP |       \
             rt2dANIMBUTTONSTATEPICKDOWN |     \
             rt2dANIMBUTTONSTATEPICKOVER)

/* Basic enumerations */

/**
 * \ingroup rt2dmessage
 * \ref Rt2dMessageType, this type represents the different types of
 * messages that are available.
 */

enum Rt2dMessageType
{
    rt2dMESSAGETYPENULL = 0,            /**< Empty message. */
    rt2dMESSAGETYPEPLAY,                /**< Play animation. */
    rt2dMESSAGETYPESTOP,                /**< Stop animation. */
    rt2dMESSAGETYPENEXTFRAME,           /**< Advance to next frame. */
    rt2dMESSAGETYPEPREVFRAME,           /**< Rewind to previouse frame. */
    rt2dMESSAGETYPEGOTOFRAME,           /**< Advance to frame by index. */
    rt2dMESSAGETYPEGOTOLABEL,           /**< Advance to frame by label. */
    rt2dMESSAGETYPEGETURL,              /**< Get URL */
    rt2dMESSAGETYPEDOACTION,            /*   Perform action. */
    rt2dMESSAGETYPEFOREIGN,             /**< Application specific message. */
    rt2dMESSAGETYPEMOUSEMOVETO,         /**< Move mouse. */
    rt2dMESSAGETYPEMOUSEBUTTONSTATE,    /**< Mouse button up or down. */
    rt2dMESSAGETYPESPECIALTELLTARGET,   /*   Change target while queueing */
    rt2dMESSAGETYPEBUTTONBYLABEL,       /**< Mouse button transition by label */
    rt2dMESSAGETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef enum Rt2dMessageType Rt2dMessageType;

/**
 * \ingroup rt2dstringlabel
 * \ref Rt2dStringLabelType, this type represents the different types of
 * object that can be labelled in the maestro's label table.
 */

enum Rt2dStringLabelType
{
    rt2dANIMLABELTYPENONE = 0,
    rt2dANIMLABELTYPEANIM,              /**< Animation label. */
    rt2dANIMLABELTYPEFRAME,             /**< Frame or cel label. */
    rt2dANIMLABELTYPEBUTTON,            /**< Button label. */
    rt2dANIMLABELTYPEFOREIGN,           /**< Application specific. */
    rt2dANIMLABELTYPESHAPE,             /**< Shape label. */
    rt2dANIMLABELTYPEURL,               /**< URL label. */
    rt2dANIMLABELTYPEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef enum Rt2dStringLabelType Rt2dStringLabelType;

/* Basic animation structures */

/**
 * \ingroup rt2danimsub
 * \struct Rt2dAnimProps
 * Structure describing the current state of a scene.
 * This should be considered an opaque type. Use the 
 * Rt2dAnim API functions to access.
 */
typedef struct Rt2dAnimProps Rt2dAnimProps;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameList
 * Structure describing an entire list of keyframes
 * This should be considered an opaque type. Use the 
 * Rt2dKeyFrameList API functions to access.
 */
typedef struct Rt2dKeyFrameList Rt2dKeyFrameList;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameSet
 *  structure describing a set of keyframe actions to be applied to a 2D object.
 * This should be considered an opaque type. Use the 
 * Rt2dAnim API functions to access.
 */
typedef struct Rt2dKeyFrameSet Rt2dKeyFrameSet;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dAnimObjectUpdate
 * Structure describing an unoptimized update to an object
 * This should be considered an opaque type. Use the 
 * Rt2dAnim API functions to access.
 */
typedef struct Rt2dAnimObjectUpdate Rt2dAnimObjectUpdate;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameTransform
 * Structure describing a transform change to a 2d object.
 * This should be considered an opaque type. Use the 
 * Rt2dAnim API functions to access.
 */
typedef struct Rt2dKeyFrameTransform Rt2dKeyFrameTransform;

/*
 * Typedef for struct Rt2dKeyFrameColor describing a color 
 * change to a 2d object.
 */
typedef struct Rt2dKeyFrameColor Rt2dKeyFrameColor;

/*
 * Structure describing a displayable or depth change to a 2d object.
 */
typedef struct Rt2dKeyFrameShow Rt2dKeyFrameShow;

/*
 * Structure describing a morph change to a 2d object.
 */
typedef struct Rt2dKeyFrameMorph Rt2dKeyFrameMorph;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dAnim
 * Structure describing a 2d animation.
 * This should be considered an opaque type. Use the 
 * Rt2dAnim API functions to access.
 */
typedef struct Rt2dAnim Rt2dAnim;

/**
 * \ingroup rt2dbutton
 * \struct Rt2dButton
 * Structure describing a button.
 * This should be considered an opaque type. Use the 
 * Rt2dButton API functions to access.
 */
typedef struct Rt2dButton Rt2dButton;

/**
 * \ingroup rt2dcel
 * \struct Rt2dCel
 * Structure describing a cel.
 * This should be considered an opaque type. Use the 
 * Rt2dCel API functions to access.
 */
typedef struct Rt2dCel Rt2dCel;

/**
 * \ingroup rt2dcel
 * \struct Rt2dCelList
 * Structure describing a cel list.
 * This should be considered an opaque type. Use the 
 * Rt2dCel API functions to access.
 */
typedef struct Rt2dCelList Rt2dCelList;

/**
 * \ingroup rt2dmaestro
 * \struct Rt2dMaestro
 * Structure describing a maestro.
 * This should be considered an opaque type. Use the 
 * Rt2dMaestro API functions to access.
 */
typedef struct Rt2dMaestro Rt2dMaestro;

/*
 * Structure describing a message.
 */
typedef struct Rt2dMessage Rt2dMessage;

/**
 * \ingroup rt2dmessage
 * \struct Rt2dMessageList
 * Structure describing a message.
 * This should be considered an opaque type. Use the 
 * Rt2dMessage API functions to access.
 */
typedef struct Rt2dMessageList Rt2dMessageList;

/**
 * \ingroup rt2dstringlabel
 * \struct Rt2dStringLabel
 * Structure used to store and access named data, either internal or user. 
 * A type and a name may be used to access internal and user data.
 *
 * This should be considered an opaque type. Use the 
 * Rt2dStringLabel API functions to access.
 */
typedef struct Rt2dStringLabel Rt2dStringLabel;

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrame 
 *  structure describing a transforming action
 */
struct Rt2dKeyFrameTransform
{
    RwMatrix matrix;         /**< Transform to be applied */ /*64*/
};

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameColor
 * Structure describing a color 
 * change to a 2d object.
 */
struct Rt2dKeyFrameColor
{
    RwRGBAReal color;     /**< Color value for a keyframe */ /*16*/
};

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameShow
 * Structure describing a show/hide change and a depth change to a 2d object.
 */
struct Rt2dKeyFrameShow
{
    RwBool      show;          /**< visibility flag */                /*4*/ 
    RwInt32     depth;         /**< Depth order (reverse-z) */        /*4*/ 
    RwUInt8     pad1[8];       /**< Alignment padding */              /*8*/
};

/**
 * \ingroup rt2danimsub
 * \struct Rt2dKeyFrameMorph
 * Structure describing a morph change to a 2d object.
 */
struct Rt2dKeyFrameMorph
{
    Rt2dObject *source;         /**< start object */                        /*4*/ 
    Rt2dObject *destination;    /**< end object */                          /*4*/ 
    RwReal      alpha;          /**< interpolation value (0.0f-1.0f) */     /*4*/ 
    RwInt32     pad1;           /**< Alignment padding */                   /*4*/ 
};

/**
 * \ingroup rt2dmessage
 * \struct Rt2dMessage
 * Structure describing a message. A message must have a valid message type, (\ref Rt2dMessageType)
 * and animation index. The animation index identifies which animation the message applies to.
 * A -1 indicates the currently active animation. A message can have none, one or two additional
 * \ref RwInt32 parameters, depending on the message type.
 */
struct Rt2dMessage
{
    RwUInt32               messageType;   /**< message identifier
                                               (\ref Rt2dMessageType) */
    RwInt32                index;         /**< animation to apply any
                                               actions to */
    RwInt32                intParam1;     /**< first param (message dependant) */
    RwInt32                intParam2;     /**< second param (message dependant) */
};

#define _rt2dMessageGetMessageTypeMacro(_message) \
    ((_message)->messageType);

#define _rt2dMessageSetMessageTypeMacro(_message, _messageType) \
    ((_message)->messageType = (_messageType));

#define _rt2dMessageGetIndexMacro(_message) \
    ((_message)->index);

#define _rt2dMessageSetIndexMacro(_message, _index) \
    ((_message)->index = (_index));

#define _rt2dMessageSetParamMacro(_message, _param1, _param2) \
MACRO_START \
{ \
    ((_message)->intParam1 = (_param1)); \
    ((_message)->intParam2 = (_param2)); \
} \
MACRO_STOP

#define _rt2dMessageGetParamMacro(_message, _param1, _param2) \
MACRO_START \
{ \
    (*(_param1) = (_message)->intParam1); \
    (*(_param2) = (_message)->intParam2); \
} \
MACRO_STOP

/*
 * structure containing label information. The entityType identifies the type
 * of the label. The label's name is stored as an index
 * in common storage area. The entityType and name of the label are used as keys
 * during a search. Additional internal and user data can be stored with the
 * label.
 */

#if (!defined(DOXYGEN))
struct Rt2dStringLabel
{
    RwUInt32                entityType;  /* type of the label
                                              (see Rt2dStringLabelType) */
    RwInt32                 nameIndex;   /* index of name in internal data 
                                              area */
    void                    *internalData; /* internal data */
    void                    *userData;     /* customizable data */
    
};

#endif /* (!defined(DOXYGEN)) */

#define _rt2dStringLabelGetStringLabelTypeMacro(_strLabel) \
    ((_strLabel)->entityType)

#define _rt2dStringLabelSetStringLabelTypeMacro(_strLabel, _entityType) \
    ((_strLabel)->entityType = (_entityType))

#define _rt2dStringLabelGetNameIndexMacro(_strLabel) \
    ((_strLabel)->nameIndex)

#define _rt2dStringLabelSetNameIndexMacro(_strLabel, _index) \
    ((_strLabel)->nameIndex = (_index))

#define _rt2dStringLabelGetInternalDataMacro(_strLabel) \
    ((_strLabel)->internalData)

#define _rt2dStringLabelSetInternalDataMacro(_strLabel, _internalData) \
    ((_strLabel)->internalData = (_internalData))

#define _rt2dStringLabelGetUserDataMacro(_strLabel) \
    ((_strLabel)->userData)

#define _rt2dStringLabelSetUserDataMacro(_strLabel, _userData) \
    ((_strLabel)->userData = (_userData))

/*
 *  structure containing cel information. The name of the cel is stored as an
 * index into a label table. The buttons in the cel are stored as indices. These
 * reference a list of buttons held by the cel's parent maestro. Any messages
 * to be process when the cel is active is stored as index into the parent's
 * maestro's message storage area.
 */

#if (!defined(DOXYGEN))
struct Rt2dCel
{
    RwInt32                 strLabelIndex;      /* Frame label */
    RwInt32                 celIndex;           /* Frame number */
    RwSList                 *buttonIndices;     /* List of buttons active in 
                                                   this frame */
    RwInt32                 messageListIndex;   /* Messages to be posted after
                                                   displaying this frame */
};

#endif /* (!defined(DOXYGEN)) */

#define _rt2dCelGetStringLabelIndexMacro(_cel) \
    ((_cel)->strLabelIndex);

#define _rt2dCelSetStringLabelIndexMacro(_cel, _index) \
    ((_cel)->strLabelIndex = (_index));

#define _rt2dCelGetCelIndexMacro(_cel) \
    ((_cel)->celIndex);

#define _rt2dCelSetCelIndexMacro(_cel, _index) \
    ((_cel)->celIndex = (_index));

#define _rt2dCelGetMessageListIndexMacro(_cel) \
    ((_cel)->messageListIndex);

#define _rt2dCelSetMessageListIndexMacro(_cel, _index) \
    ((_cel)->messageListIndex = (_index));

/* Callback typedefs */

typedef Rt2dAnim *(*Rt2dAnimCallBack)(Rt2dAnim *object,
                                             Rt2dAnimProps *props,
					                         void *data);
/**
 * \ingroup rt2danimsub
 * \ref Rt2dKeyFrameListCallBack
 * This typedef defines a callback function to apply to a frame list.
 *
 * \param anim             Pointer to the animation
 * \param props            Pointer to the props that the animation acts upon
 * \param keyframeList     The key frame list
 * \param keyframeListTime The key frame list time
 * \param data             User defined data
 *
 * \return return value is ignored
 */
typedef Rt2dKeyFrameList *(Rt2dKeyFrameListCallBack)(
                                           Rt2dAnim *anim,
                                           Rt2dAnimProps *props,
                                           Rt2dKeyFrameList *keyframeList,
                                           RwReal keyframeListTime,
                                           void *data);

/**
 * \ingroup rt2danimsub
 * \ref Rt2dAnimOnEndReachedCallBack
 * This typedef defines a callback function called at the end of an animation.
 *
 * \param anim               Pointer to the animation ending
 * \param props              Pointer to the props that the animation acts upon
 * \param remainingDeltaTime Remaining time
 *
 * \return return value is ignored
 */
typedef Rt2dAnim *(*Rt2dAnimOnEndReachedCallBack)(Rt2dAnim *anim,
                                                 Rt2dAnimProps *props,
						                         RwReal remainingDeltaTime);

/**
 * \ingroup rt2dmaestro
 * \ref Rt2dMaestroAnimationsCallBack
 * \ref Rt2dMaestroAnimationsCallBack represents the function called from
 * \ref Rt2dMaestroForAllAnimations for all animations in the maestro.
 * This function
 * should return the current maestro to indicate success. The callback may
 * return NULL to terminate further callbacks on the maestro.
 *
 * \param maestro           Pointer to parent maestro.
 * \param anim              Pointer to the animation.
 * \param props             Pointer to the anim's props.
 * \param pData             Pointer to private data.
 *
 * \return Pointer to the maestro.
 */

typedef Rt2dMaestro *(*Rt2dMaestroAnimationsCallBack)
        (Rt2dMaestro *maestro, Rt2dAnim *anim, Rt2dAnimProps *props, void * pData);

/**
 * \ingroup rt2dmessage
 * \ref Rt2dMessageHandlerCallBack represents the function called from
 * \ref Rt2dMaestroProcessMessages for all messages in the maestro's
 * process message queue. The maestro does not filter any messages. The
 * handler may process or ignore any messages it is given.
 *
 * This function should return the current message to indicate success. The
 * callback may return NULL to terminate further callbacks on the maestro.
 *
 * \param maestro          Pointer to parent maestro.
 * \param message          Pointer to the message.
 *
 * \return Pointer to the message.
 */

typedef Rt2dMessage *(*Rt2dMessageHandlerCallBack)
        (Rt2dMaestro *maestro, Rt2dMessage *message);

/* Message streaming call backs. */

typedef RwInt32
(*Rt2dMessageStreamGetSizeCallBack)
    (Rt2dMaestro *maestro, Rt2dMessage *message);

typedef Rt2dMessage *
(*Rt2dMessageStreamReadCallBack)
    (Rt2dMaestro *maestro, Rt2dMessage *message, RwStream *stream);

typedef Rt2dMessage *
(*Rt2dMessageStreamWriteCallBack)
    (Rt2dMaestro *maestro, Rt2dMessage *message, RwStream *stream);

/*
 * Data access macros.
 */

/*
 * Toolkit-level initialization / finalization
 */
/*
 * INITIALIZE
 */
extern void
Rt2dAnimOpen(void);

extern void
Rt2dAnimClose(void);
 
/*
 * Rt2dAnim
 */

/* General */

extern Rt2dAnimOnEndReachedCallBack
Rt2dAnimSetOnEndReachedCallBack(Rt2dAnimOnEndReachedCallBack callback);

extern Rt2dAnimOnEndReachedCallBack
Rt2dAnimGetOnEndReachedCallBack(void);


extern Rt2dAnim *
Rt2dAnimOnEndReachedCallBackLoop(Rt2dAnim *anim, Rt2dAnimProps *props,
                          RwReal remainingDeltaTime);

extern Rt2dAnim *
Rt2dAnimOnEndReachedCallBackStop(Rt2dAnim *anim, Rt2dAnimProps *props,
                          RwReal remainingDeltaTime);

/* Management */
extern Rt2dAnim *
Rt2dAnimCreate(void);

extern RwBool
Rt2dAnimDestroy(Rt2dAnim *anim, Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimLock(Rt2dAnim *anim, Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimUnlock(Rt2dAnim *anim, Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimAddKeyFrameList(Rt2dAnim *anim,
                        Rt2dKeyFrameList *keyframeList,
                        RwReal time);


extern Rt2dAnim *
Rt2dAnimCopy(Rt2dAnim *srcAnim, Rt2dAnimProps *srcProps);

/* Streaming */
extern RwUInt32
Rt2dAnimStreamGetSize(  Rt2dAnim *anim,
                            Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimStreamRead(RwStream *stream,
                   Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimStreamReadTo(RwStream *dest,
                     RwStream *stream,
                     Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimStreamWrite(Rt2dAnim *anim, RwStream *stream,
                        Rt2dAnimProps *data);

/* Playback */
extern RwBool
Rt2dAnimIsInterpolated(Rt2dAnim *anim);

extern Rt2dAnim *
Rt2dAnimSetInterpolate(Rt2dAnim *anim, RwBool interpolate);

extern Rt2dAnim *
Rt2dAnimReset(Rt2dAnim *anim, Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimSetDeltaTimeScale(Rt2dAnim *anim, RwReal timeScale);

extern Rt2dAnim *
Rt2dAnimAddDeltaTime(Rt2dAnim *anim, Rt2dAnimProps *props,
                         RwReal deltaTime);

extern Rt2dAnim *
Rt2dAnimAddDeltaFrameIndex(Rt2dAnim *anim, Rt2dAnimProps *props,
                           RwInt32 deltaFrame);

extern Rt2dAnim *
Rt2dAnimTimeUpdate(Rt2dAnim *anim, Rt2dAnimProps *props);

extern Rt2dAnim *
Rt2dAnimGotoKeyFrameListByTime(Rt2dAnim *anim, Rt2dAnimProps *props,
                               RwReal time);

extern Rt2dAnim *
Rt2dAnimGotoKeyFrameListByIndex(Rt2dAnim *anim, Rt2dAnimProps *props,
                                RwInt32 frameIndex);

/* Utilities */
extern Rt2dAnim *
Rt2dAnimForAllKeyFrameLists(Rt2dAnim *anim, Rt2dKeyFrameListCallBack callBack,
                            Rt2dAnimProps *props, void *data);

/* Interrogation */
extern RwInt32
Rt2dAnimGetNumberOfKeyFrames(Rt2dAnim *anim);

extern Rt2dKeyFrameList *
Rt2dAnimGetKeyFrameListByIndex(Rt2dAnim *anim, RwUInt32 frameIndex);

extern RwReal
Rt2dAnimGetCurrentTime(Rt2dAnim *anim);

extern RwReal
Rt2dAnimGetFinalKeyFrameListTime(Rt2dAnim *anim);

extern RwInt32
Rt2dAnimGetPrevFrameIndex(Rt2dAnim *anim);

extern RwReal
Rt2dAnimGetPrevFrameTime(Rt2dAnim *anim);

extern RwInt32
Rt2dAnimGetNextFrameIndex(Rt2dAnim *anim);

extern RwReal
Rt2dAnimGetNextFrameTime(Rt2dAnim *anim);

/* KeyFrameList Management */
extern Rt2dKeyFrameList *
Rt2dKeyFrameListCreate(Rt2dAnimProps *props);

extern RwBool
Rt2dKeyFrameListDestroy(Rt2dKeyFrameList *keyframeList);

extern Rt2dKeyFrameList *
Rt2dKeyFrameListLock(Rt2dKeyFrameList *keyframeList, Rt2dAnimProps *props);

extern Rt2dKeyFrameList *
Rt2dKeyFrameListUnlock(Rt2dKeyFrameList *keyframeList,
                          Rt2dAnimProps *props);

extern Rt2dKeyFrameList*
Rt2dKeyFrameListAddUpdateObject(Rt2dKeyFrameList *keyframeList,
                                Rt2dAnimObjectUpdate *update);

/* KeyFrameList Streaming */
extern Rt2dKeyFrameList *
Rt2dKeyFrameListStreamRead(RwStream *stream);

extern RwUInt32
Rt2dKeyFrameListStreamGetSize(Rt2dKeyFrameList *keyframeList);

extern Rt2dKeyFrameList *
Rt2dKeyFrameListStreamWrite(Rt2dKeyFrameList *keyframeList,
                               RwStream *stream);

/* KeyFrameList Playback */
extern Rt2dKeyFrameList *
Rt2dKeyFrameListAdvance(Rt2dKeyFrameList *keyframeList,
                        Rt2dAnimProps *props);

extern Rt2dKeyFrameList *
Rt2dKeyFrameListApply(Rt2dKeyFrameList *keyframeList, Rt2dAnimProps *props,
                      RwReal alpha);

/* KeyFrameList edition object */
extern Rt2dAnimObjectUpdate *
Rt2dAnimObjectUpdateCreate(Rt2dObject *object);

extern RwBool
Rt2dAnimObjectUpdateDestroy(Rt2dAnimObjectUpdate *update);

extern Rt2dAnimObjectUpdate *
Rt2dAnimObjectUpdateClear(Rt2dAnimObjectUpdate *update);

extern Rt2dAnimObjectUpdate*
Rt2dAnimObjectUpdateSetTransform(Rt2dAnimObjectUpdate *update,
                                 Rt2dKeyFrameTransform *transform);

extern Rt2dAnimObjectUpdate*
Rt2dAnimObjectUpdateSetColorOffs(Rt2dAnimObjectUpdate *update,
                            Rt2dKeyFrameColor *colorOffs);

extern Rt2dAnimObjectUpdate*
Rt2dAnimObjectUpdateSetColorMult(Rt2dAnimObjectUpdate *update,
                            Rt2dKeyFrameColor *colorMult);

extern Rt2dAnimObjectUpdate*
Rt2dAnimObjectUpdateSetShow(Rt2dAnimObjectUpdate *update,
                            Rt2dKeyFrameShow *show);

extern Rt2dAnimObjectUpdate*
Rt2dAnimObjectUpdateSetMorph(Rt2dAnimObjectUpdate *update,
                             Rt2dKeyFrameMorph *morph);

extern Rt2dAnimObjectUpdate *
Rt2dAnimObjectUpdateSetObject(Rt2dAnimObjectUpdate *update,
                              Rt2dObject *object);

/* Props management */
extern Rt2dAnimProps *
Rt2dAnimPropsCreate(Rt2dObject *scene);

extern RwBool
Rt2dAnimPropsDestroy(Rt2dAnimProps *props);

/*
 * Rt2dButton
 */

extern Rt2dMaestro *
Rt2dMaestroAddButton(Rt2dMaestro *maestro, RwInt32 strLabelIdx, RwInt32 objectIdx,
                      RwUInt32 stateFlag, RwInt32 *actionListIdx,
                      RwInt32 *index);

/*
 * Rt2dCel & Rt2dCelList
 */

extern Rt2dCel *
Rt2dCelCreate(Rt2dMaestro *maestro,
              const RwChar *name,
              RwInt32 celIndex, RwInt32 messageListIndex);

extern Rt2dCelList *
Rt2dCelListCreate( void );

extern RwBool
Rt2dCelDestroy(Rt2dMaestro *maestro, Rt2dCel *cel);

extern Rt2dCel *
Rt2dCelAddButtonIndex(Rt2dCel * cel, RwInt32 buttonIndex, RwInt32 *index);

#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define Rt2dCelGetStringLabelIndex(_cel) \
    _rt2dCelGetStringLabelIndexMacro((_cel));

#define Rt2dCelSetStringLabelIndex(_cel, _index) \
    _rt2dCelSetStringLabelIndexMacro((_cel), (_index));

#define Rt2dCelGetCelIndex(_cel) \
    _rt2dCelGetCelIndexMacro((_cel));

#define Rt2dCelSetCelIndex(_cel, _index) \
    _rt2dCelSetCelIndexMacro((_cel), (_index));

#define Rt2dCelGetMessageListIndex(_cel) \
    _rt2dCelGetMessageListIndexMacro((_cel));

#define Rt2dCelSetMessageListIndex(_cel, _index) \
    _rt2dCelSetMessageListIndexMacro((_cel), (_index));

#else /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern RwInt32
Rt2dCelGetStringLabelIndex(Rt2dCel *cel);

extern void
Rt2dCelSetStringLabelIndex(Rt2dCel *cel, RwInt32 index);

extern RwInt32
Rt2dCelGetCelIndex(Rt2dCel *cel);

extern void
Rt2dCelSetCelIndex(Rt2dCel *cel, RwInt32 index);

extern RwInt32
Rt2dCelGetMessageListIndex(Rt2dCel *cel);

extern void
Rt2dCelSetMessageListIndex(Rt2dCel *cel, RwInt32 index);

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern RwBool
Rt2dCelListDestroy(Rt2dCelList *celList);

extern Rt2dCelList *
Rt2dCelListLock(Rt2dCelList *celList);

extern Rt2dCelList *
Rt2dCelListUnlock(Rt2dCelList * celList);

extern Rt2dCelList *
Rt2dCelListCopy(Rt2dCelList *srcCelList);

extern Rt2dCelList *
Rt2dCelListAddCel(Rt2dCelList *celList, Rt2dCel *cel, RwInt32 *index);

extern Rt2dCelList *
Rt2dCelListCelGetStringLabelIndex(Rt2dCelList *celList, RwInt32 celIndex, RwInt32 *index);

extern Rt2dCelList *
Rt2dCelListCelButtonGetDisplayVersion(Rt2dMaestro *maestro, Rt2dCelList * celList,
                                      RwInt32 celIndex, RwInt32 celButtonIndex, RwInt32 *index);

/*
 * Rt2dMaestro
 */
extern Rt2dMaestro *
Rt2dMaestroCreate(void);

extern RwBool
Rt2dMaestroDestroy(Rt2dMaestro *maestro);

extern RwUInt32
Rt2dMaestroStreamGetSize(Rt2dMaestro *maestro);

extern Rt2dMaestro *
Rt2dMaestroStreamRead(Rt2dMaestro *maestro, RwStream *stream);

extern Rt2dMaestro *
Rt2dMaestroStreamWrite(Rt2dMaestro *maestro, RwStream *stream);


extern Rt2dMaestro *
Rt2dMaestroForAllAnimations(Rt2dMaestro *maestro,
                             Rt2dMaestroAnimationsCallBack callback, void *data);

extern Rt2dMaestro *
Rt2dMaestroForAllVisibleAnimations(Rt2dMaestro *maestro,
                             Rt2dMaestroAnimationsCallBack callback, void *data);

extern Rt2dMaestro *
Rt2dMaestroAddAnimations(Rt2dMaestro *maestro,
                          RwInt32 parent, RwInt32 posInParentScene,
                          Rt2dAnim *anim, Rt2dAnimProps *animProps, Rt2dCelList *celList,
                          RwInt32 *index);

extern Rt2dAnim *
Rt2dMaestroGetAnimationsByIndex(Rt2dMaestro *maestro, RwInt32 index);

extern Rt2dAnimProps *
Rt2dMaestroGetAnimPropsByIndex(Rt2dMaestro *maestro, RwInt32 index);

extern Rt2dMaestro *
Rt2dMaestroUpdateAnimations(Rt2dMaestro *maestro);

extern Rt2dMaestro *
Rt2dMaestroAddDeltaTime(Rt2dMaestro *maestro, RwReal deltaTime);

extern Rt2dMaestro *
Rt2dMaestroLock(Rt2dMaestro * maestro);

extern Rt2dMaestro *
Rt2dMaestroUnlock(Rt2dMaestro *maestro);

extern Rt2dObject *
Rt2dMaestroGetScene(Rt2dMaestro *maestro);

extern Rt2dMaestro *
Rt2dMaestroSetScene(Rt2dMaestro *maestro, Rt2dObject *scene);

extern Rt2dObject *
Rt2dMaestroGetAnimSceneByIndex(Rt2dMaestro *maestro, RwInt32 index);

extern Rt2dMaestro *
Rt2dMaestroRender(Rt2dMaestro *maestro);

extern Rt2dBBox *
Rt2dMaestroGetBBox(Rt2dMaestro *maestro);

extern Rt2dMaestro *
Rt2dMaestroSetBBox(Rt2dMaestro *maestro, Rt2dBBox *bbox);


/*
 * Message & Message handlers.
 */
extern Rt2dMessageHandlerCallBack
Rt2dMaestroGetMessageHandler(Rt2dMaestro *maestro);

extern Rt2dMaestro *
Rt2dMaestroSetMessageHandler(Rt2dMaestro *maestro, Rt2dMessageHandlerCallBack handler);

extern Rt2dMaestro *
Rt2dMaestroAddMessageList(Rt2dMaestro *maestro,
                           Rt2dMessage *message, RwInt32 num, RwInt32 *index);

extern Rt2dMaestro *
Rt2dMaestroPostMessages(Rt2dMaestro *maestro, Rt2dMessage *message, RwInt32 num);

extern Rt2dMaestro *
Rt2dMaestroProcessMessages(Rt2dMaestro *maestro);

#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define Rt2dMessageGetMessageType(_message) \
    _rt2dMessageGetMessageTypeMacro((_message));

#define Rt2dMessageSetMessageTypeMacro(_message, _messageType) \
    _rt2dMessageSetMessageTypeMacro((_message), (_messageType));

#define Rt2dMessageGetIndex(_message) \
    _rt2dMessageGetIndexMacro((_message));

#define Rt2dMessageSetIndex(_message, _index) \
    _rt2dMessageSetIndexMarco((_message), (_index));

#define Rt2dMessageSetParam(_message, _param1, _param2) \
    _rt2dMessageSetParamMacro((_message), (_param1), (_param2));

#define Rt2dMessageGetParam(_message, _param1, _param2) \
    _rt2dMessageGetParamMacro((_message), (_param1), (_param2));

#else /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern Rt2dMessageType
Rt2dMessageGetMessageType(Rt2dMessage *message);

extern void
Rt2dMessageSetMessageType(Rt2dMessage *message, Rt2dMessageType messageType);

extern RwInt32
Rt2dMessageGetIndex(Rt2dMessage *message);

extern void
Rt2dMessageSetIndex(Rt2dMessage *message, RwInt32 index);

extern void
Rt2dMessageGetParam(Rt2dMessage *message, RwInt32 *param1, RwInt32 *param2);

extern void
Rt2dMessageSetParam(Rt2dMessage *message, RwInt32 param1, RwInt32 param2);

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/*
 * Default message handler.
 */
extern Rt2dMessage *
Rt2dMessageHandlerDefaultCallBack(Rt2dMaestro *maestro, Rt2dMessage *message);


/*
 * Labels.
 */
extern Rt2dStringLabel *
Rt2dMaestroFindStringLabel(Rt2dMaestro *maestro,
                            Rt2dStringLabelType entityType, const RwChar *lookupName,
                            RwInt32 *index);

extern Rt2dStringLabel *
Rt2dMaestroGetStringLabelByIndex(Rt2dMaestro *maestro, RwInt32 index);

extern Rt2dMaestro *
Rt2dMaestroAddStringLabel(Rt2dMaestro *maestro,
                           Rt2dStringLabelType entityType, const RwChar *name,
                           void *internalData, RwInt32 *index);

extern const RwChar *
Rt2dMaestroGetStringLabelName(Rt2dMaestro *maestro,
                                Rt2dStringLabel *strLabel);


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define Rt2dStringLabelGetStringLabelType(_strLabel) \
    _rt2dStringLabelGetStringLabelTypeMacro((_strLabel))

#define Rt2dStringLabelSetStringLabelType(_strLabel, _entityType) \
    _rt2dStringLabelSetStringLabelTypeMacro((_strLabel), (_entityType))

#define Rt2dStringLabelGetNameIndex(_strLabel) \
    _rt2dStringLabelGetNameIndexMacro((_strLabel))

#define Rt2dStringLabelSetNameIndex(_strLabel, _index) \
    _rt2dStringLabelSetNameIndexMacro((_strLabel), (_index))

#define Rt2dStringLabelGetInternalData(_strLabel) \
    _rt2dStringLabelGetInternalDataMacro((_strLabel))

#define Rt2dStringLabelSetInternalData(_strLabel, _internalData) \
    _rt2dStringLabelSetInternalDataMacro((_strLabel), (_internalData))

#define Rt2dStringLabelGetUserData(_strLabel) \
    _rt2dStringLabelGetUserDataMacro((_strLabel))

#define Rt2dStringLabelSetUserData(_strLabel, _userData) \
    _rt2dStringLabelSetUserDataMacro((_strLabel), (_userData))

#else /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

extern Rt2dStringLabelType
Rt2dStringLabelGetStringLabelType(Rt2dStringLabel *strLabel);

extern void
Rt2dStringLabelSetStringLabelType(Rt2dStringLabel *strLabel,
                                  Rt2dStringLabelType entityType);

extern RwInt32
Rt2dStringLabelGetNameIndex(Rt2dStringLabel *strLabel);

extern void
Rt2dStringLabelSetNameIndex(Rt2dStringLabel *strLabel, RwInt32 index);

extern void *
Rt2dStringLabelGetInternalData(Rt2dStringLabel *strLabel);

extern void
Rt2dStringLabelSetInternalData(Rt2dStringLabel *strLabel, void *internalData);

extern void *
Rt2dStringLabelGetUserData(Rt2dStringLabel *strLabel);

extern void
Rt2dStringLabelSetUserData(Rt2dStringLabel *strLabel, void *userData);

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */




/*
 * Cels & Cel Lists
 */
extern Rt2dCelList *
Rt2dMaestroGetCelListByIndex(Rt2dMaestro *maestro, RwInt32 index);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RT2DANIM_H*/
