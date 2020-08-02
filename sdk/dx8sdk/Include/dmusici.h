/************************************************************************
*                                                                       *
*   dmusici.h -- This module contains the API for the                   *
*                DirectMusic performance layer                          *
*                                                                       *
*   Copyright (c) Microsoft Corporation.  All rights reserved.          *
*                                                                       *
************************************************************************/

#ifndef _DMUSICI_
#define _DMUSICI_

#include <windows.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#include <mmsystem.h>
#include <dmusicc.h>
/* plugin (track and tool) interfaces.  This #include will eventually go away. */
#include <dmplugin.h>

#include <pshpack8.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef WORD            TRANSITION_TYPE;
typedef __int64         REFERENCE_TIME;
typedef long            MUSIC_TIME;

#define MT_MIN          0x80000000  /* Minimum music time value. */
#define MT_MAX          0x7FFFFFFF  /* Maximum music time value. */

#define DMUS_PPQ        768     /* parts per quarter note */

interface IDirectMusicTrack;
interface IDirectMusicPerformance;
interface IDirectMusicPerformance8;
interface IDirectMusicTool;
interface IDirectMusicSegment;
interface IDirectMusicSegment8;
interface IDirectMusicSegmentState;
interface IDirectMusicSegmentState8;
interface IDirectMusicGraph;
interface IDirectMusicBuffer;
interface IDirectMusicInstrument;
interface IDirectMusicDownloadedInstrument;
interface IDirectMusicBand;
interface IDirectMusicChordMap;
interface IDirectMusicLoader;
interface IDirectMusicLoader8;
interface IDirectMusicScript;
interface IDirectMusicObject;
interface IDirectMusicStyle8;
interface IDirectMusicPatternTrack;
interface IDirectMusicContainer;
interface IDirectMusicTool8;
interface IDirectMusicTrack8;
interface IDirectMusicAudioPath;
#ifndef __cplusplus 
typedef interface IDirectMusicTrack IDirectMusicTrack;
typedef interface IDirectMusicPerformance IDirectMusicPerformance;
typedef interface IDirectMusicPerformance8 IDirectMusicPerformance8;
typedef interface IDirectMusicTool IDirectMusicTool;
typedef interface IDirectMusicSegment IDirectMusicSegment;
typedef interface IDirectMusicSegment8 IDirectMusicSegment8;
typedef interface IDirectMusicSegmentState IDirectMusicSegmentState;
typedef interface IDirectMusicSegmentState8 IDirectMusicSegmentState8;
typedef interface IDirectMusicGraph IDirectMusicGraph;
typedef interface IDirectMusicBuffer IDirectMusicBuffer;
typedef interface IDirectMusicInstrument IDirectMusicInstrument;
typedef interface IDirectMusicDownloadedInstrument IDirectMusicDownloadedInstrument;
typedef interface IDirectMusicBand IDirectMusicBand;
typedef interface IDirectMusicChordMap IDirectMusicChordMap;
typedef interface IDirectMusicObject IDirectMusicObject;
typedef interface IDirectMusicLoader IDirectMusicLoader;
typedef interface IDirectMusicLoader8 IDirectMusicLoader8;
typedef interface IDirectMusicScript IDirectMusicScript;
typedef interface IDirectMusicStyle8 IDirectMusicStyle8;
typedef interface IDirectMusicPatternTrack IDirectMusicPatternTrack;
typedef interface IDirectMusicContainer IDirectMusicContainer;
typedef interface IDirectMusicTool8 IDirectMusicTool8;
typedef interface IDirectMusicTrack8 IDirectMusicTrack8;
typedef interface IDirectMusicAudioPath IDirectMusicAudioPath;
#endif

typedef enum enumDMUS_STYLET_TYPES
{
    DMUS_STYLET_PATTERN         = 0,
    DMUS_STYLET_MOTIF           = 1,
} DMUS_STYLET_TYPES;


typedef enum enumDMUS_COMMANDT_TYPES
{
    DMUS_COMMANDT_GROOVE            = 0,
    DMUS_COMMANDT_FILL              = 1,
    DMUS_COMMANDT_INTRO             = 2,
    DMUS_COMMANDT_BREAK             = 3,
    DMUS_COMMANDT_END               = 4,
    DMUS_COMMANDT_ENDANDINTRO       = 5
} DMUS_COMMANDT_TYPES;

typedef enum enumDMUS_SHAPET_TYPES
{
    DMUS_SHAPET_FALLING             = 0,
    DMUS_SHAPET_LEVEL               = 1,
    DMUS_SHAPET_LOOPABLE            = 2,
    DMUS_SHAPET_LOUD                = 3,
    DMUS_SHAPET_QUIET               = 4,
    DMUS_SHAPET_PEAKING             = 5,
    DMUS_SHAPET_RANDOM              = 6,
    DMUS_SHAPET_RISING              = 7,
    DMUS_SHAPET_SONG                = 8
}   DMUS_SHAPET_TYPES;

typedef enum enumDMUS_COMPOSEF_FLAGS
{       
    DMUS_COMPOSEF_NONE              = 0,
    DMUS_COMPOSEF_ALIGN             = 0x1,
    DMUS_COMPOSEF_OVERLAP           = 0x2,
    DMUS_COMPOSEF_IMMEDIATE         = 0x4,
    DMUS_COMPOSEF_GRID              = 0x8,
    DMUS_COMPOSEF_BEAT              = 0x10,
    DMUS_COMPOSEF_MEASURE           = 0x20,
    DMUS_COMPOSEF_AFTERPREPARETIME  = 0x40,
    DMUS_COMPOSEF_VALID_START_BEAT  = 0x80,   /* In conjunction with DMUS_COMPOSEF_ALIGN, allows the switch to occur on any beat. */
    DMUS_COMPOSEF_VALID_START_GRID  = 0x100,  /* In conjunction with DMUS_COMPOSEF_ALIGN, allows the switch to occur on any grid. */
    DMUS_COMPOSEF_VALID_START_TICK  = 0x200,  /* In conjunction with DMUS_COMPOSEF_ALIGN, allows the switch to occur any time. */
    DMUS_COMPOSEF_SEGMENTEND        = 0x400,  /* Play the transition at the end of the current segment. */
    DMUS_COMPOSEF_MARKER            = 0x800,  /* Play the transition at the next marker in the current segment. */
    DMUS_COMPOSEF_MODULATE          = 0x1000,
    DMUS_COMPOSEF_LONG              = 0x2000,
    DMUS_COMPOSEF_ENTIRE_TRANSITION = 0x4000,    /* play the entire transition pattern */
    DMUS_COMPOSEF_1BAR_TRANSITION   = 0x8000,    /* play one bar of the transition pattern */
    DMUS_COMPOSEF_ENTIRE_ADDITION   = 0x10000,   /* play the additional pattern in its entirety */
    DMUS_COMPOSEF_1BAR_ADDITION     = 0x20000,   /* play one bar of the additional pattern */
    DMUS_COMPOSEF_VALID_START_MEASURE = 0x40000, /* In conjunction with DMUS_COMPOSEF_ALIGN, allows the switch to occur on any bar. */
    DMUS_COMPOSEF_DEFAULT           = 0x80000,   /* Use segment's default boundary */
    DMUS_COMPOSEF_NOINVALIDATE      = 0x100000,  /* Play without invalidating the currently playing segment(s) */
    DMUS_COMPOSEF_USE_AUDIOPATH     = 0x200000,  /* Uses the audio paths that are embedded in the segments */
    DMUS_COMPOSEF_INVALIDATE_PRI    = 0x400000   /* Invalidate only the current primary seg state */
}   DMUS_COMPOSEF_FLAGS;

#define DMUS_PMSG_PART                                                                              \
    DWORD               dwSize;                                                                     \
    REFERENCE_TIME      rtTime;             /* real time (in 100 nanosecond increments) */          \
    MUSIC_TIME          mtTime;             /* music time */                                        \
    DWORD               dwFlags;            /* various bits (see DMUS_PMSGF_FLAGS enumeration) */    \
    DWORD               dwPChannel;         /* Performance Channel. The Performance can */          \
                                            /* use this to determine the port/channel. */           \
    DWORD               dwVirtualTrackID;   /* virtual track ID */                                  \
    IDirectMusicTool*   pTool;              /* tool interface pointer */                            \
    IDirectMusicGraph*  pGraph;             /* tool graph interface pointer */                      \
    DWORD               dwType;             /* PMSG type (see DMUS_PMSGT_TYPES defines) */              \
    DWORD               dwVoiceID;          /* unique voice id which allows synthesizers to */      \
                                            /* identify a specific event. For DirectX 6.0, */       \
                                            /* this field should always be 0. */                    \
    DWORD               dwGroupID;          /* Track group id */                                 \
    IUnknown*           punkUser;           /* user com pointer, auto released upon PMSG free */

/* every DMUS_PMSG is based off of this structure. The Performance needs 
   to access these members consistently in every PMSG that goes through it. */
typedef struct _DMUS_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

} DMUS_PMSG;

#define DMUS_PCHANNEL_BROADCAST_PERFORMANCE	0xFFFFFFFF  /* PMsg is sent on all PChannels of the performance. */
#define DMUS_PCHANNEL_BROADCAST_AUDIOPATH   0xFFFFFFFE  /* PMsg is sent on all PChannels of the audio path. */
#define DMUS_PCHANNEL_BROADCAST_SEGMENT	    0xFFFFFFFD  /* PMsg is sent on all PChannels of the segment. */
#define DMUS_PCHANNEL_BROADCAST_GROUPS  	0xFFFFFFFC  /* A duplicate PMsg is for each Channels Groups in the performance. */

/*  The DMUS_PATH constants are used in conjunction with GetObjectInPath to find a requested
    interface at a particular stage in the audio path. 
*/
#define DMUS_PATH_SEGMENT          0x1000      /* Get the segment itself (from a segment state.) */
#define DMUS_PATH_SEGMENT_TRACK    0x1100      /* Look in Track List of Segment. */
#define DMUS_PATH_SEGMENT_GRAPH    0x1200      /* Get the segment's tool graph. */
#define DMUS_PATH_SEGMENT_TOOL     0x1300      /* Look in Tool Graph of Segment. */
#define DMUS_PATH_AUDIOPATH        0x2000      /* Get the audiopath itself (from a segment state.) */
#define DMUS_PATH_AUDIOPATH_GRAPH  0x2200      /* Get the audiopath's tool graph. */
#define DMUS_PATH_AUDIOPATH_TOOL   0x2300      /* Look in Tool Graph of Audio Path. */
#define DMUS_PATH_PERFORMANCE      0x3000      /* Access the performance. */
#define DMUS_PATH_PERFORMANCE_GRAPH 0x3200     /* Get the performance's tool graph. */
#define DMUS_PATH_PERFORMANCE_TOOL 0x3300      /* Look in Tool Graph of Performance. */
#define DMUS_PATH_PORT             0x4000      /* Access the synth. */
#define DMUS_PATH_BUFFER           0x6000      /* Look in DirectSoundBuffer. */
#define DMUS_PATH_BUFFER_DMO       0x6100      /* Access a DMO in the buffer. */
#define DMUS_PATH_MIXIN_BUFFER     0x7000      /* Look in a global mixin buffer. */ 
#define DMUS_PATH_MIXIN_BUFFER_DMO 0x7100      /* Access a DMO in a global mixin buffer. */ 
#define DMUS_PATH_PRIMARY_BUFFER   0x8000      /* Access the primary buffer. */ 

/*  To ignore PChannels when calling GetObjectInPath(), use the DMUS_PCHANNEL_ALL constant. */
#define DMUS_PCHANNEL_ALL           0xFFFFFFFB      

/*  The DMUS_APATH types are used in conjunction with CreateStandardAudioPath to
    build default path types. _SHARED_ means the same buffer is shared across multiple
    instantiations of the audiopath type. _DYNAMIC_ means a unique buffer is created
    every time. 
*/

#define DMUS_APATH_SHARED_STEREOPLUSREVERB   1       /* A standard music set up with stereo outs and reverb. */
#define DMUS_APATH_DYNAMIC_3D                6       /* An audio path with one dynamic bus from the synth feeding to a dynamic 3d buffer. Does not send to env reverb. */
#define DMUS_APATH_DYNAMIC_MONO              7       /* An audio path with one dynamic bus from the synth feeding to a dynamic mono buffer. */
#define DMUS_APATH_DYNAMIC_STEREO            8       /* An audio path with two dynamic buses from the synth feeding to a dynamic stereo buffer. */

typedef struct _DMUS_AUDIOPARAMS
{
    DWORD   dwSize;             /* Size of this structure. */
    BOOL    fInitNow;           /* If true, the sink and synth are created immediately and results returned in this structure. */
    DWORD 	dwValidData;        /* Flags indicating which fields below are valid. */
    DWORD   dwFeatures;         /* Required DMUS_AUDIOF features. */
    DWORD   dwVoices;           /* Required number of voices. */
    DWORD   dwSampleRate;       /* Sample rate of synths and sink. */
    CLSID   clsidDefaultSynth;  /* Class ID of default synthesizer. */
} DMUS_AUDIOPARAMS;

/* dwFeatures flags. These indicate which features are required for the audio environment. */
#define DMUS_AUDIOF_3D          0x1   /* Require 3D buffers. */
#define DMUS_AUDIOF_ENVIRON     0x2   /* Require environmental modeling. */
#define DMUS_AUDIOF_EAX         0x4   /* Require use of EAX effects. */
#define DMUS_AUDIOF_DMOS        0x8   /* Require use of additional DMOs. */
#define DMUS_AUDIOF_STREAMING   0x10  /* Require support for streaming waves. */
#define DMUS_AUDIOF_BUFFERS     0x20  /* Require support for multiple buffers (all above cases need this.) */
#define DMUS_AUDIOF_ALL         0x3F  /* Requires everything. */

/* dwValidData flags. These indicate which fields in DMUS_AUDIOPARAMS have been filled in. If fInitNow is set, these also return what was allocated. */
#define DMUS_AUDIOPARAMS_FEATURES       0x00000001
#define DMUS_AUDIOPARAMS_VOICES         0x00000002
#define DMUS_AUDIOPARAMS_SAMPLERATE     0x00000004
#define DMUS_AUDIOPARAMS_DEFAULTSYNTH   0x00000008

/* DMUS_PMSGF_FLAGS fill the DMUS_PMSG's dwFlags member */
typedef enum enumDMUS_PMSGF_FLAGS
{
    DMUS_PMSGF_REFTIME          = 1,      /* if rtTime is valid */
    DMUS_PMSGF_MUSICTIME        = 2,      /* if mtTime is valid */
    DMUS_PMSGF_TOOL_IMMEDIATE   = 4,      /* if PMSG should be processed immediately */ 
    DMUS_PMSGF_TOOL_QUEUE       = 8,      /* if PMSG should be processed a little early, at Queue time */
    DMUS_PMSGF_TOOL_ATTIME      = 0x10,   /* if PMSG should be processed at the time stamp */
    DMUS_PMSGF_TOOL_FLUSH       = 0x20,   /* if PMSG is being flushed */
    DMUS_PMSGF_LOCKTOREFTIME    = 0x40,   /* if rtTime can not be overriden by a tempo change. */
    DMUS_PMSGF_DX8              = 0x80    /* if the message has DX8 or later extensions. */
    /* The values of DMUS_TIME_RESOLVE_FLAGS may also be used inside the */
    /* DMUS_PMSG's dwFlags member. */
} DMUS_PMSGF_FLAGS;

/* DMUS_PMSGT_TYPES fill the DMUS_PMSG's dwType member */
typedef enum enumDMUS_PMSGT_TYPES
{
    DMUS_PMSGT_MIDI             = 0,      /* MIDI short message */
    DMUS_PMSGT_NOTE             = 1,      /* Interactive Music Note */
    DMUS_PMSGT_SYSEX            = 2,      /* MIDI long message (system exclusive message) */
    DMUS_PMSGT_NOTIFICATION     = 3,      /* Notification message */
    DMUS_PMSGT_TEMPO            = 4,      /* Tempo message */
    DMUS_PMSGT_CURVE            = 5,      /* Control change / pitch bend, etc. curve */
    DMUS_PMSGT_TIMESIG          = 6,      /* Time signature */
    DMUS_PMSGT_PATCH            = 7,      /* Patch changes */
    DMUS_PMSGT_TRANSPOSE        = 8,      /* Transposition messages */
    DMUS_PMSGT_CHANNEL_PRIORITY = 9,      /* Channel priority */
    DMUS_PMSGT_STOP             = 10,     /* Stop message */
    DMUS_PMSGT_DIRTY            = 11,     /* Tells Tools that cache GetParam() info to refresh */
    DMUS_PMSGT_WAVE             = 12,     /* Carries control information for playing a wave. */
    DMUS_PMSGT_LYRIC            = 13,     /* Lyric message from lyric track. */
    DMUS_PMSGT_SCRIPTLYRIC      = 14,     /* Lyric message sent by a script with the Trace function. */
    DMUS_PMSGT_USER             = 255     /* User message */
} DMUS_PMSGT_TYPES;

/* DMUS_SEGF_FLAGS correspond to IDirectMusicPerformance::PlaySegment, and other API */
typedef enum enumDMUS_SEGF_FLAGS
{
    DMUS_SEGF_REFTIME           = 1<<6,   /* 0x40 Time parameter is in reference time  */
    DMUS_SEGF_SECONDARY         = 1<<7,   /* 0x80 Secondary segment */
    DMUS_SEGF_QUEUE             = 1<<8,   /* 0x100 Queue at the end of the primary segment queue (primary only) */
    DMUS_SEGF_CONTROL           = 1<<9,   /* 0x200 Play as a control track (secondary segments only) */
    DMUS_SEGF_AFTERPREPARETIME  = 1<<10,  /* 0x400 Play after the prepare time (See IDirectMusicPerformance::GetPrepareTime) */
    DMUS_SEGF_GRID              = 1<<11,  /* 0x800 Play on grid boundary */
    DMUS_SEGF_BEAT              = 1<<12,  /* 0x1000 Play on beat boundary */
    DMUS_SEGF_MEASURE           = 1<<13,  /* 0x2000 Play on measure boundary */
    DMUS_SEGF_DEFAULT           = 1<<14,  /* 0x4000 Use segment's default boundary */
    DMUS_SEGF_NOINVALIDATE      = 1<<15,  /* 0x8000 Play without invalidating the currently playing segment(s) */
    DMUS_SEGF_ALIGN             = 1<<16,  /* 0x10000 Align segment with requested boundary, but switch at first valid point */
    DMUS_SEGF_VALID_START_BEAT  = 1<<17,  /* 0x20000 In conjunction with DMUS_SEGF_ALIGN, allows the switch to occur on any beat. */
    DMUS_SEGF_VALID_START_GRID  = 1<<18,  /* 0x40000 In conjunction with DMUS_SEGF_ALIGN, allows the switch to occur on any grid. */
    DMUS_SEGF_VALID_START_TICK  = 1<<19,  /* 0x80000 In conjunction with DMUS_SEGF_ALIGN, allows the switch to occur any time. */
    DMUS_SEGF_AUTOTRANSITION    = 1<<20,  /* 0x100000 Compose and play a transition segment, using the transition template. */
    DMUS_SEGF_AFTERQUEUETIME    = 1<<21,  /* 0x200000 Make sure to play after the queue time. This is default for primary segments */
    DMUS_SEGF_AFTERLATENCYTIME  = 1<<22,  /* 0x400000 Make sure to play after the latency time. This is true for all segments, so this is a nop */
    DMUS_SEGF_SEGMENTEND        = 1<<23,  /* 0x800000 Play at the next end of segment. */
    DMUS_SEGF_MARKER            = 1<<24,  /* 0x1000000 Play at next marker in the primary segment. If there are no markers, default to any other resolution requests. */
    DMUS_SEGF_TIMESIG_ALWAYS    = 1<<25,  /* 0x2000000 Even if there is no primary segment, align start time with current time signature. */
    DMUS_SEGF_USE_AUDIOPATH     = 1<<26,  /* 0x4000000 Uses the audio path that is embedded in the segment. */
    DMUS_SEGF_VALID_START_MEASURE = 1<<27, /* 0x8000000 In conjunction with DMUS_SEGF_ALIGN, allows the switch to occur on any bar. */
    DMUS_SEGF_INVALIDATE_PRI    = 1<<28   /* 0x10000000 invalidate only the current primary seg state */
} DMUS_SEGF_FLAGS;

#define DMUS_SEG_REPEAT_INFINITE    0xFFFFFFFF  /* For IDirectMusicSegment::SetRepeat*/
#define DMUS_SEG_ALLTRACKS          0x80000000  /* For IDirectMusicSegment::SetParam() and SetTrackConfig() - selects all tracks instead on nth index. */
#define DMUS_SEG_ANYTRACK           0x80000000  /* For IDirectMusicSegment::GetParam() - checks each track until it finds one that returns data (not DMUS_E_NOT_FOUND.) */
                                                

/* DMUS_TIME_RESOLVE_FLAGS correspond to IDirectMusicPerformance::GetResolvedTime, and can */
/* also be used interchangeably with the corresponding DMUS_SEGF_FLAGS, since their values */
/* are intentionally the same */
typedef enum enumDMUS_TIME_RESOLVE_FLAGS
{
    DMUS_TIME_RESOLVE_AFTERPREPARETIME  = DMUS_SEGF_AFTERPREPARETIME,
    DMUS_TIME_RESOLVE_AFTERQUEUETIME    = DMUS_SEGF_AFTERQUEUETIME,
    DMUS_TIME_RESOLVE_AFTERLATENCYTIME  = DMUS_SEGF_AFTERLATENCYTIME,
    DMUS_TIME_RESOLVE_GRID              = DMUS_SEGF_GRID,
    DMUS_TIME_RESOLVE_BEAT              = DMUS_SEGF_BEAT,
    DMUS_TIME_RESOLVE_MEASURE           = DMUS_SEGF_MEASURE,
    DMUS_TIME_RESOLVE_MARKER            = DMUS_SEGF_MARKER,
    DMUS_TIME_RESOLVE_SEGMENTEND        = DMUS_SEGF_SEGMENTEND,
} DMUS_TIME_RESOLVE_FLAGS;

/* The following flags are sent inside the DMUS_CHORD_KEY.dwFlags parameter */
typedef enum enumDMUS_CHORDKEYF_FLAGS
{
    DMUS_CHORDKEYF_SILENT            = 1,      /* is the chord silent? */
} DMUS_CHORDKEYF_FLAGS;

#define DMUS_MAXSUBCHORD 8

typedef struct _DMUS_SUBCHORD
{
    DWORD   dwChordPattern;     /* Notes in the subchord */
    DWORD   dwScalePattern;     /* Notes in the scale */
    DWORD   dwInversionPoints;  /* Where inversions can occur */
    DWORD   dwLevels;           /* Which levels are supported by this subchord */
    BYTE    bChordRoot;         /* Root of the subchord */
    BYTE    bScaleRoot;         /* Root of the scale */
} DMUS_SUBCHORD;

typedef struct _DMUS_CHORD_KEY
{
    WCHAR           wszName[16];        /* Name of the chord */
    WORD            wMeasure;           /* Measure this falls on */
    BYTE            bBeat;              /* Beat this falls on */
    BYTE            bSubChordCount;     /* Number of chords in the list of subchords */
    DMUS_SUBCHORD   SubChordList[DMUS_MAXSUBCHORD]; /* List of sub chords */
    DWORD           dwScale;            /* Scale underlying the entire chord */
    BYTE            bKey;               /* Key underlying the entire chord */
    BYTE            bFlags;             /* Miscelaneous flags */
} DMUS_CHORD_KEY;

/* DMUS_NOTE_PMSG */
typedef struct _DMUS_NOTE_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    MUSIC_TIME mtDuration;     /* duration */
    WORD    wMusicValue;       /* Description of note in chord and key. */
    WORD    wMeasure;          /* Measure in which this note occurs */
    short   nOffset;           /* Offset from grid at which this note occurs */
    BYTE    bBeat;             /* Beat (in measure) at which this note occurs */
    BYTE    bGrid;             /* Grid offset from beat at which this note occurs */
    BYTE    bVelocity;         /* Note velocity */
    BYTE    bFlags;            /* see DMUS_NOTEF_FLAGS */
    BYTE    bTimeRange;        /* Range to randomize time. */
    BYTE    bDurRange;         /* Range to randomize duration. */
    BYTE    bVelRange;         /* Range to randomize velocity. */
    BYTE    bPlayModeFlags;    /* Play mode */
    BYTE    bSubChordLevel;    /* Which subchord level this note uses.  */
    BYTE    bMidiValue;        /* The MIDI note value, converted from wMusicValue */
    char    cTranspose;        /* Transposition to add to midi note value after converted from wMusicValue. */
} DMUS_NOTE_PMSG;

typedef enum enumDMUS_NOTEF_FLAGS
{
    DMUS_NOTEF_NOTEON = 1,              /* Set if this is a MIDI Note On. Otherwise, it is MIDI Note Off */
    /* DX8 flags: */
    DMUS_NOTEF_NOINVALIDATE = 2,        /* Don't invalidate this note off. */
    DMUS_NOTEF_NOINVALIDATE_INSCALE = 4,/* Don't invalidate if still within the scale. */
    DMUS_NOTEF_NOINVALIDATE_INCHORD = 8,/* Don't invalidate if still within the chord. */
    DMUS_NOTEF_REGENERATE = 0x10,       /* Regenerate the note on an invalidate. */
} DMUS_NOTEF_FLAGS;

/* The DMUS_PLAYMODE_FLAGS are used to determine how to convert wMusicValue
   into the appropriate bMidiValue.
*/

typedef enum enumDMUS_PLAYMODE_FLAGS
{
    DMUS_PLAYMODE_KEY_ROOT          = 1,  /* Transpose on top of the key root. */
    DMUS_PLAYMODE_CHORD_ROOT        = 2,  /* Transpose on top of the chord root. */
    DMUS_PLAYMODE_SCALE_INTERVALS   = 4,  /* Use scale intervals from scale pattern. */
    DMUS_PLAYMODE_CHORD_INTERVALS   = 8,  /* Use chord intervals from chord pattern. */
    DMUS_PLAYMODE_NONE              = 16, /* No mode. Indicates the parent part's mode should be used. */
} DMUS_PLAYMODE_FLAGS;

/* The following are playback modes that can be created by combining the DMUS_PLAYMODE_FLAGS
   in various ways:
*/

/* Fixed. wMusicValue holds final MIDI note value. This is used for drums, sound effects, and sequenced
   notes that should not be transposed by the chord or scale.
*/
#define DMUS_PLAYMODE_FIXED             0  
/* In fixed to key, the musicvalue is again a fixed MIDI value, but it
   is transposed on top of the key root. 
*/
#define DMUS_PLAYMODE_FIXEDTOKEY        DMUS_PLAYMODE_KEY_ROOT
/* In fixed to chord, the musicvalue is also a fixed MIDI value, but it
   is transposed on top of the chord root. 
*/
#define DMUS_PLAYMODE_FIXEDTOCHORD      DMUS_PLAYMODE_CHORD_ROOT
/* In Pedalpoint, the key root is used and the notes only track the intervals in
   the scale. The chord root and intervals are completely ignored. This is useful
   for melodic lines that play relative to the key root.
*/
#define DMUS_PLAYMODE_PEDALPOINT        (DMUS_PLAYMODE_KEY_ROOT | DMUS_PLAYMODE_SCALE_INTERVALS)
/* In the Melodic mode, the chord root is used but the notes only track the intervals in
   the scale. The key root and chord intervals are completely ignored. This is useful
   for melodic lines that play relative to the chord root. 
*/
#define DMUS_PLAYMODE_MELODIC           (DMUS_PLAYMODE_CHORD_ROOT | DMUS_PLAYMODE_SCALE_INTERVALS)
/* Normal chord mode is the prevalent playback mode. 
   The notes track the intervals in the chord, which is based on the chord root. 
   If there is a scale component to the MusicValue, the additional intervals 
   are pulled from the scale and added.
   If the chord does not have an interval to match the chord component of
   the MusicValue, the note is silent.
*/
#define DMUS_PLAYMODE_NORMALCHORD       (DMUS_PLAYMODE_CHORD_ROOT | DMUS_PLAYMODE_CHORD_INTERVALS)
/* If it is desirable to play a note that is above the top of the chord, the
   always play mode (known as "purpleized" in a former life) finds a position
   for the note by using intervals from the scale. Essentially, this mode is
   a combination of the Normal and Melodic playback modes, where a failure
   in Normal causes a second try in Melodic mode.
*/
#define DMUS_PLAYMODE_ALWAYSPLAY        (DMUS_PLAYMODE_MELODIC | DMUS_PLAYMODE_NORMALCHORD)

/* These playmodes are new for dx8. */
/* In PedalpointChord, the key root is used and the notes only track the intervals in
   the chord. The chord root and scale intervals are completely ignored. This is useful
   for chordal lines that play relative to the key root.
*/
#define DMUS_PLAYMODE_PEDALPOINTCHORD   (DMUS_PLAYMODE_KEY_ROOT | DMUS_PLAYMODE_CHORD_INTERVALS)

/* For completeness, here's a mode that tries for pedalpointchord, but if it fails
   uses scale intervals
*/
#define DMUS_PLAYMODE_PEDALPOINTALWAYS  (DMUS_PLAYMODE_PEDALPOINT | DMUS_PLAYMODE_PEDALPOINTCHORD)


/*  Legacy names for modes... */
#define DMUS_PLAYMODE_PURPLEIZED        DMUS_PLAYMODE_ALWAYSPLAY
#define DMUS_PLAYMODE_SCALE_ROOT        DMUS_PLAYMODE_KEY_ROOT
#define DMUS_PLAYMODE_FIXEDTOSCALE      DMUS_PLAYMODE_FIXEDTOKEY


/* DMUS_MIDI_PMSG */
typedef struct _DMUS_MIDI_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    BYTE    bStatus;
    BYTE    bByte1;
    BYTE    bByte2;
    BYTE    bPad[1];
} DMUS_MIDI_PMSG;

/* DMUS_PATCH_PMSG */
typedef struct _DMUS_PATCH_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    BYTE    byInstrument;
    BYTE    byMSB;
    BYTE    byLSB;
    BYTE    byPad[1];
} DMUS_PATCH_PMSG;

/* DMUS_TRANSPOSE_PMSG */
typedef struct _DMUS_TRANSPOSE_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    short   nTranspose;
    /* Following exists only under DX8 and on (check dwFlags for DMUS_PMSGF_DX8) */
    WORD            wMergeIndex;     /* Allows multiple parameters to be merged (pitchbend, volume, and expression.)*/
} DMUS_TRANSPOSE_PMSG;

/* DMUS_CHANNEL_PRIORITY_PMSG */
typedef struct _DMUS_CHANNEL_PRIORITY_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    DWORD   dwChannelPriority;
} DMUS_CHANNEL_PRIORITY_PMSG;

/* DMUS_TEMPO_PMSG */
typedef struct _DMUS_TEMPO_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    double  dblTempo;                       /* the tempo */
} DMUS_TEMPO_PMSG;

#define DMUS_TEMPO_MAX          1000
#define DMUS_TEMPO_MIN          1

#define DMUS_MASTERTEMPO_MAX    100.0f
#define DMUS_MASTERTEMPO_MIN    0.01f

/* DMUS_SYSEX_PMSG */
typedef struct _DMUS_SYSEX_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    DWORD   dwLen;          /* length of the data */
    BYTE    abData[1];      /* array of data, length equal to dwLen */
} DMUS_SYSEX_PMSG;

/* DMUS_CURVE_PMSG */
typedef struct _DMUS_CURVE_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    MUSIC_TIME      mtDuration;      /* how long this curve lasts */
    MUSIC_TIME      mtOriginalStart; /* must be set to either zero when this PMSG is created or to the original mtTime of the curve */
    MUSIC_TIME      mtResetDuration; /* how long after the curve is finished to allow a flush or
                                        invalidation to reset to the reset value, nResetValue */
    short           nStartValue;     /* curve's start value */
    short           nEndValue;       /* curve's end value */
    short           nResetValue;     /* curve's reset value, set when a flush or invalidation
                                        occurs within mtDuration + mtResetDuration */
    WORD            wMeasure;        /* Measure in which this curve occurs */
    short           nOffset;         /* Offset from grid at which this curve occurs */
    BYTE            bBeat;           /* Beat (in measure) at which this curve occurs */
    BYTE            bGrid;           /* Grid offset from beat at which this curve occurs */
    BYTE            bType;           /* type of curve */
    BYTE            bCurveShape;     /* shape of curve */
    BYTE            bCCData;         /* CC# if this is a control change type */
    BYTE            bFlags;          /* Curve reset and start from current value flags. */
    /* Following exists only under DX8 and on (check dwFlags for DMUS_PMSGF_DX8) */
    WORD            wParamType;      /* RPN or NRPN parameter number. */
    WORD            wMergeIndex;     /* Allows multiple parameters to be merged (pitchbend, volume, and expression.)*/
} DMUS_CURVE_PMSG;

typedef enum enumDMUS_CURVE_FLAGS
{
    DMUS_CURVE_RESET = 1,            /* When set, the nResetValue must be sent when the 
                                        time is reached or an invalidate occurs because
                                        of a transition. If not set, the curve stays
                                        permanently stuck at the new value. */
    DMUS_CURVE_START_FROM_CURRENT = 2/* Ignore Start, start the curve at the current value. 
                                        This only works for volume, expression, and pitchbend. */
} DMUS_CURVE_FLAGS;


#define DMUS_CURVE_RESET    1        

/* Curve shapes */
enum
{ 
    DMUS_CURVES_LINEAR  = 0,
    DMUS_CURVES_INSTANT = 1,
    DMUS_CURVES_EXP     = 2,
    DMUS_CURVES_LOG     = 3,
    DMUS_CURVES_SINE    = 4
};
/* curve types */
#define DMUS_CURVET_PBCURVE      0x03   /* Pitch bend curve. */
#define DMUS_CURVET_CCCURVE      0x04   /* Control change curve. */
#define DMUS_CURVET_MATCURVE     0x05   /* Mono aftertouch curve. */
#define DMUS_CURVET_PATCURVE     0x06   /* Poly aftertouch curve. */
#define DMUS_CURVET_RPNCURVE     0x07   /* RPN curve with curve type in wParamType. */
#define DMUS_CURVET_NRPNCURVE    0x08   /* NRPN curve with curve type in wParamType. */

/* DMUS_TIMESIG_PMSG */
typedef struct _DMUS_TIMESIG_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    /* Time signatures define how many beats per measure, which note receives */
    /* the beat, and the grid resolution. */
    BYTE    bBeatsPerMeasure;       /* beats per measure (top of time sig) */
    BYTE    bBeat;                  /* what note receives the beat (bottom of time sig.) */
                                    /* we can assume that 0 means 256th note */
    WORD    wGridsPerBeat;          /* grids per beat */
} DMUS_TIMESIG_PMSG;



/* notification type values */
/* The following correspond to GUID_NOTIFICATION_SEGMENT */
#define DMUS_NOTIFICATION_SEGSTART       0
#define DMUS_NOTIFICATION_SEGEND         1
#define DMUS_NOTIFICATION_SEGALMOSTEND   2
#define DMUS_NOTIFICATION_SEGLOOP        3
#define DMUS_NOTIFICATION_SEGABORT       4
/* The following correspond to GUID_NOTIFICATION_PERFORMANCE */
#define DMUS_NOTIFICATION_MUSICSTARTED   0
#define DMUS_NOTIFICATION_MUSICSTOPPED   1
#define DMUS_NOTIFICATION_MUSICALMOSTEND 2
/* The following corresponds to GUID_NOTIFICATION_MEASUREANDBEAT */
#define DMUS_NOTIFICATION_MEASUREBEAT    0
/* The following corresponds to GUID_NOTIFICATION_CHORD */
#define DMUS_NOTIFICATION_CHORD          0
/* The following correspond to GUID_NOTIFICATION_COMMAND */
#define DMUS_NOTIFICATION_GROOVE         0
#define DMUS_NOTIFICATION_EMBELLISHMENT  1
/* The following corresponds to GUID_NOTIFICATION_RECOMPOSE */
#define DMUS_NOTIFICATION_RECOMPOSE          0

/* DMUS_NOTIFICATION_PMSG */
typedef struct _DMUS_NOTIFICATION_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */

    GUID    guidNotificationType;
    DWORD   dwNotificationOption;
    DWORD   dwField1;
    DWORD   dwField2;
} DMUS_NOTIFICATION_PMSG;

/* DMUS_WAVE_PMSG */
typedef struct _DMUS_WAVE_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */
    
    REFERENCE_TIME rtStartOffset;   /* How far into the wave to start, in reference time units only. */
    REFERENCE_TIME rtDuration;      /* Duration of the wave, in either reference time or music time. */  
    long    lOffset;                /* Offset from actual time to logical time, in music or ref time. */
    long    lVolume;		        /* Initial volume, in 100ths of a dB. */
    long    lPitch;			        /* Initial pitch, in 100ths of a semitone. */
    BYTE    bFlags;                 /* Flags, including DMUS_WAVEF_OFF... */
} DMUS_WAVE_PMSG;

#define DMUS_WAVEF_OFF           1       /* If wave is playing and this is the off message. */
#define DMUS_WAVEF_STREAMING     2       /* If wave is streaming. */
#define DMUS_WAVEF_NOINVALIDATE  4       /* Don't invalidate this wave. */
#define DMUS_WAVEF_NOPREROLL     8       /* Don't preroll any wave data. */   
#define DMUS_WAVEF_IGNORELOOPS   0x20    /* Ignore segment looping. */

/* DMUS_LYRIC_PMSG */
typedef struct _DMUS_LYRIC_PMSG
{
    /* begin DMUS_PMSG_PART */
    DMUS_PMSG_PART
    /* end DMUS_PMSG_PART */
    
    WCHAR    wszString[1];      /* null-terminated Unicode lyric string (structure is actually larger than size 1) */
} DMUS_LYRIC_PMSG;

#define DMUS_MAX_NAME           64         /* Maximum object name length. */
#define DMUS_MAX_CATEGORY       64         /* Maximum object category name length. */
#define DMUS_MAX_FILENAME       MAX_PATH

typedef struct _DMUS_VERSION {
  DWORD    dwVersionMS;
  DWORD    dwVersionLS;
}DMUS_VERSION, FAR *LPDMUS_VERSION;

/* Time Signature structure, used by IDirectMusicStyle */
/* Also used as a parameter for GetParam() and SetParam */
typedef struct _DMUS_TIMESIGNATURE
{
    MUSIC_TIME mtTime;
    BYTE    bBeatsPerMeasure;       /* beats per measure (top of time sig) */
    BYTE    bBeat;                  /* what note receives the beat (bottom of time sig.) */
                                    /* we can assume that 0 means 256th note */
    WORD    wGridsPerBeat;          /* grids per beat */
} DMUS_TIMESIGNATURE;

typedef struct _DMUS_VALID_START_PARAM
{
    MUSIC_TIME mtTime;                      /* Time of the first legal start 
                                               point after (or including) the requested time. 
                                               This is a returned value.
                                               Time format is the relative offset from requested time. */
} DMUS_VALID_START_PARAM;

typedef struct _DMUS_PLAY_MARKER_PARAM
{
    MUSIC_TIME mtTime;                      /* Time of the first legal segment play 
                                               marker before (or including) the requested time. 
                                               This is a returned value.
                                               Time format is the relative offset from requested time. */
} DMUS_PLAY_MARKER_PARAM;

/*      The DMUSOBJECTDESC structure is used to communicate everything you could */
/*      possibly use to describe a DirectMusic object.  */

typedef struct _DMUS_OBJECTDESC
{
    DWORD          dwSize;                 /* Size of this structure. */
    DWORD          dwValidData;            /* Flags indicating which fields below are valid. */
    GUID           guidObject;             /* Unique ID for this object. */
    GUID           guidClass;              /* GUID for the class of object. */
    FILETIME       ftDate;                 /* Last edited date of object. */
    DMUS_VERSION   vVersion;               /* Version. */
    WCHAR          wszName[DMUS_MAX_NAME]; /* Name of object. */
    WCHAR          wszCategory[DMUS_MAX_CATEGORY]; /* Category for object (optional). */
    WCHAR          wszFileName[DMUS_MAX_FILENAME]; /* File path. */
    LONGLONG       llMemLength;            /* Size of Memory data. */
    LPBYTE         pbMemData;              /* Memory pointer for data. */
    IStream *      pStream;                /* Stream with data. */
} DMUS_OBJECTDESC;

typedef DMUS_OBJECTDESC *LPDMUS_OBJECTDESC;

/*      Flags for dwValidData. When set, a flag indicates that the  */
/*      corresponding field in DMUSOBJECTDESC holds valid data. */

#define DMUS_OBJ_OBJECT         (1 << 0)     /* Object GUID is valid. */
#define DMUS_OBJ_CLASS          (1 << 1)     /* Class GUID is valid. */
#define DMUS_OBJ_NAME           (1 << 2)     /* Name is valid. */
#define DMUS_OBJ_CATEGORY       (1 << 3)     /* Category is valid. */
#define DMUS_OBJ_FILENAME       (1 << 4)     /* File path is valid. */
#define DMUS_OBJ_FULLPATH       (1 << 5)     /* Path is full path. */
#define DMUS_OBJ_URL            (1 << 6)     /* Path is URL. */
#define DMUS_OBJ_VERSION        (1 << 7)     /* Version is valid. */
#define DMUS_OBJ_DATE           (1 << 8)     /* Date is valid. */
#define DMUS_OBJ_LOADED         (1 << 9)     /* Object is currently loaded in memory. */
#define DMUS_OBJ_MEMORY         (1 << 10)    /* Object is pointed to by pbMemData. */
#define DMUS_OBJ_STREAM         (1 << 11)    /* Object is stored in pStream. */

/*      The DMUS_SCRIPT_ERRORINFO structure describes an error that occurred in a script.
        It is returned by methods in IDirectMusicScript. */
typedef struct _DMUS_SCRIPT_ERRORINFO
{
    DWORD dwSize; /* Size of this structure. */
    HRESULT hr;
    ULONG ulLineNumber;
    LONG ichCharPosition;
    WCHAR wszSourceFile[DMUS_MAX_FILENAME];
    WCHAR wszSourceComponent[DMUS_MAX_FILENAME];
    WCHAR wszDescription[DMUS_MAX_FILENAME];
    WCHAR wszSourceLineText[DMUS_MAX_FILENAME];
} DMUS_SCRIPT_ERRORINFO;

/*  Track configuration flags, used with IDirectMusicSegment8::SetTrackConfig() */

#define DMUS_TRACKCONFIG_OVERRIDE_ALL           1	  /* This track should get parameters from this segment before controlling and primary tracks. */
#define DMUS_TRACKCONFIG_OVERRIDE_PRIMARY       2	  /* This track should get parameters from this segment before the primary segment tracks. */
#define DMUS_TRACKCONFIG_FALLBACK               4  	  /* This track should get parameters from this segment if the primary and controlling segments don't succeed. */
#define DMUS_TRACKCONFIG_CONTROL_ENABLED        8     /* GetParam() enabled for this track. */
#define DMUS_TRACKCONFIG_PLAY_ENABLED           0x10  /* Play() enabled for this track. */
#define DMUS_TRACKCONFIG_NOTIFICATION_ENABLED	0x20  /* Notifications enabled for this track. */
#define DMUS_TRACKCONFIG_PLAY_CLOCKTIME         0x40  /* This track plays in clock time, not music time. */
#define DMUS_TRACKCONFIG_PLAY_COMPOSE 	        0x80  /* This track should regenerate data each time it starts playing. */
#define DMUS_TRACKCONFIG_LOOP_COMPOSE           0x100 /* This track should regenerate data each time it repeats. */
#define DMUS_TRACKCONFIG_COMPOSING              0x200 /* This track is used to compose other tracks. */
#define DMUS_TRACKCONFIG_CONTROL_PLAY           0x10000 /* This track, when played in a controlling segment, overrides playback of primary segment tracks. */
#define DMUS_TRACKCONFIG_CONTROL_NOTIFICATION   0x20000 /* This track, when played in a controlling segment, overrides notification of primary segment tracks. */
/* Additional track config flags for composing transitions */
#define DMUS_TRACKCONFIG_TRANS1_FROMSEGSTART    0x400  /* Get track info from start of From segment */
#define DMUS_TRACKCONFIG_TRANS1_FROMSEGCURRENT  0x800  /* Get track info from current place in From segment */
#define DMUS_TRACKCONFIG_TRANS1_TOSEGSTART      0x1000 /* Get track info from start of To segment */
#define DMUS_TRACKCONFIG_DEFAULT    (DMUS_TRACKCONFIG_CONTROL_ENABLED | DMUS_TRACKCONFIG_PLAY_ENABLED | DMUS_TRACKCONFIG_NOTIFICATION_ENABLED)

/* Get/SetParam structs for commands */
/* PARAM structures, used by GetParam() and SetParam() */
typedef struct _DMUS_COMMAND_PARAM
{
    BYTE bCommand;
    BYTE bGrooveLevel;
    BYTE bGrooveRange;
    BYTE bRepeatMode;
} DMUS_COMMAND_PARAM;

typedef struct _DMUS_COMMAND_PARAM_2
{
	MUSIC_TIME mtTime;
    BYTE bCommand;
    BYTE bGrooveLevel;
    BYTE bGrooveRange;
    BYTE bRepeatMode;
} DMUS_COMMAND_PARAM_2;

typedef IDirectMusicObject __RPC_FAR *LPDMUS_OBJECT;
typedef IDirectMusicLoader __RPC_FAR *LPDMUS_LOADER;
typedef IDirectMusicBand __RPC_FAR *LPDMUS_BAND;

#define DMUSB_LOADED    (1 << 0)        /* Set when band has been loaded */
#define DMUSB_DEFAULT   (1 << 1)        /* Set when band is default band for a style */

/*////////////////////////////////////////////////////////////////////
// IDirectMusicBand */
#undef  INTERFACE
#define INTERFACE  IDirectMusicBand
DECLARE_INTERFACE_(IDirectMusicBand, IUnknown)
{
    /* IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /* IDirectMusicBand */
    STDMETHOD(CreateSegment)        (THIS_ IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(Download)             (THIS_ IDirectMusicPerformance* pPerformance) PURE;     
    STDMETHOD(Unload)               (THIS_ IDirectMusicPerformance* pPerformance) PURE;     
};

typedef IDirectMusicBand IDirectMusicBand8;

/*////////////////////////////////////////////////////////////////////
// IDirectMusicObject */
#undef  INTERFACE
#define INTERFACE  IDirectMusicObject
DECLARE_INTERFACE_(IDirectMusicObject, IUnknown)
{
    /* IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /* IDirectMusicObject */
    STDMETHOD(GetDescriptor)        (THIS_ LPDMUS_OBJECTDESC pDesc) PURE;
    STDMETHOD(SetDescriptor)        (THIS_ LPDMUS_OBJECTDESC pDesc) PURE;
    STDMETHOD(ParseDescriptor)      (THIS_ LPSTREAM pStream, 
                                           LPDMUS_OBJECTDESC pDesc) PURE;
};

typedef IDirectMusicObject IDirectMusicObject8;

/*////////////////////////////////////////////////////////////////////
// IDirectMusicLoader */
#undef  INTERFACE
#define INTERFACE  IDirectMusicLoader
DECLARE_INTERFACE_(IDirectMusicLoader, IUnknown)
{
    /* IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /* IDirectMusicLoader */
    STDMETHOD(GetObject)            (THIS_ LPDMUS_OBJECTDESC pDesc,
                                           REFIID riid,
                                           LPVOID FAR *ppv) PURE;
    STDMETHOD(SetObject)            (THIS_ LPDMUS_OBJECTDESC pDesc) PURE;
    STDMETHOD(SetSearchDirectory)   (THIS_ REFGUID rguidClass, 
                                           WCHAR *pwzPath, 
                                           BOOL fClear) PURE;
    STDMETHOD(ScanDirectory)        (THIS_ REFGUID rguidClass, 
                                           WCHAR *pwzFileExtension, 
                                           WCHAR *pwzScanFileName) PURE;
    STDMETHOD(CacheObject)          (THIS_ IDirectMusicObject * pObject) PURE;
    STDMETHOD(ReleaseObject)        (THIS_ IDirectMusicObject * pObject) PURE;
    STDMETHOD(ClearCache)           (THIS_ REFGUID rguidClass) PURE;
    STDMETHOD(EnableCache)          (THIS_ REFGUID rguidClass, 
                                           BOOL fEnable) PURE;
    STDMETHOD(EnumObject)           (THIS_ REFGUID rguidClass, 
                                           DWORD dwIndex, 
                                           LPDMUS_OBJECTDESC pDesc) PURE;
};                                  

/*////////////////////////////////////////////////////////////////////
// IDirectMusicLoader8 */
#undef  INTERFACE
#define INTERFACE  IDirectMusicLoader8
DECLARE_INTERFACE_(IDirectMusicLoader8, IDirectMusicLoader)
{
    /* IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /* IDirectMusicLoader */
    STDMETHOD(GetObject)            (THIS_ LPDMUS_OBJECTDESC pDesc,
                                           REFIID riid,
                                           LPVOID FAR *ppv) PURE;
    STDMETHOD(SetObject)            (THIS_ LPDMUS_OBJECTDESC pDesc) PURE;
    STDMETHOD(SetSearchDirectory)   (THIS_ REFGUID rguidClass, 
                                           WCHAR *pwzPath, 
                                           BOOL fClear) PURE;
    STDMETHOD(ScanDirectory)        (THIS_ REFGUID rguidClass, 
                                           WCHAR *pwzFileExtension, 
                                           WCHAR *pwzScanFileName) PURE;
    STDMETHOD(CacheObject)          (THIS_ IDirectMusicObject * pObject) PURE;
    STDMETHOD(ReleaseObject)        (THIS_ IDirectMusicObject * pObject) PURE;
    STDMETHOD(ClearCache)           (THIS_ REFGUID rguidClass) PURE;
    STDMETHOD(EnableCache)          (THIS_ REFGUID rguidClass, 
                                           BOOL fEnable) PURE;
    STDMETHOD(EnumObject)           (THIS_ REFGUID rguidClass, 
                                           DWORD dwIndex, 
                                           LPDMUS_OBJECTDESC pDesc) PURE;

    /* IDirectMusicLoader8 */
    STDMETHOD_(void, CollectGarbage)                (THIS) PURE;
    STDMETHOD(ReleaseObjectByUnknown)               (THIS_ IUnknown *pObject) PURE;
    STDMETHOD(LoadObjectFromFile)                   (THIS_ REFGUID rguidClassID, 
                                                           REFIID iidInterfaceID, 
                                                           WCHAR *pwzFilePath, 
                                                           void ** ppObject) PURE;
};

/*  Stream object supports IDirectMusicGetLoader interface to access loader while file parsing. */

#undef  INTERFACE
#define INTERFACE  IDirectMusicGetLoader
DECLARE_INTERFACE_(IDirectMusicGetLoader, IUnknown)
{
    /* IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /* IDirectMusicGetLoader */
    STDMETHOD(GetLoader)            (THIS_ IDirectMusicLoader ** ppLoader) PURE;
};

typedef IDirectMusicGetLoader IDirectMusicGetLoader8;

/*////////////////////////////////////////////////////////////////////
// IDirectMusicSegment */
#undef  INTERFACE
#define INTERFACE  IDirectMusicSegment
DECLARE_INTERFACE_(IDirectMusicSegment, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicSegment */
    STDMETHOD(GetLength)                (THIS_ MUSIC_TIME* pmtLength) PURE;
    STDMETHOD(SetLength)                (THIS_ MUSIC_TIME mtLength) PURE;
    STDMETHOD(GetRepeats)               (THIS_ DWORD* pdwRepeats) PURE;
    STDMETHOD(SetRepeats)               (THIS_ DWORD  dwRepeats) PURE;
    STDMETHOD(GetDefaultResolution)     (THIS_ DWORD* pdwResolution) PURE;
    STDMETHOD(SetDefaultResolution)     (THIS_ DWORD  dwResolution) PURE;
    STDMETHOD(GetTrack)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               IDirectMusicTrack** ppTrack) PURE;
    STDMETHOD(GetTrackGroup)            (THIS_ IDirectMusicTrack* pTrack, 
                                               DWORD* pdwGroupBits) PURE;
    STDMETHOD(InsertTrack)              (THIS_ IDirectMusicTrack* pTrack, 
                                               DWORD dwGroupBits) PURE;
    STDMETHOD(RemoveTrack)              (THIS_ IDirectMusicTrack* pTrack) PURE;
    STDMETHOD(InitPlay)                 (THIS_ IDirectMusicSegmentState** ppSegState, 
                                               IDirectMusicPerformance* pPerformance,
                                               DWORD dwFlags) PURE;
    STDMETHOD(GetGraph)                 (THIS_ IDirectMusicGraph** ppGraph) PURE;
    STDMETHOD(SetGraph)                 (THIS_ IDirectMusicGraph* pGraph) PURE;
    STDMETHOD(AddNotificationType)      (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(RemoveNotificationType)   (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(GetParam)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               MUSIC_TIME mtTime, 
                                               MUSIC_TIME* pmtNext, 
                                               void* pParam) PURE; 
    STDMETHOD(SetParam)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               MUSIC_TIME mtTime, 
                                               void* pParam) PURE;
    STDMETHOD(Clone)                    (THIS_ MUSIC_TIME mtStart, 
                                               MUSIC_TIME mtEnd, 
                                               IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(SetStartPoint)            (THIS_ MUSIC_TIME mtStart) PURE;
    STDMETHOD(GetStartPoint)            (THIS_ MUSIC_TIME* pmtStart) PURE;
    STDMETHOD(SetLoopPoints)            (THIS_ MUSIC_TIME mtStart, 
                                               MUSIC_TIME mtEnd) PURE;
    STDMETHOD(GetLoopPoints)            (THIS_ MUSIC_TIME* pmtStart, 
                                               MUSIC_TIME* pmtEnd) PURE;
    STDMETHOD(SetPChannelsUsed)         (THIS_ DWORD dwNumPChannels, 
                                               DWORD* paPChannels) PURE;
};

/*////////////////////////////////////////////////////////////////////
// IDirectMusicSegment8 */
#undef  INTERFACE
#define INTERFACE  IDirectMusicSegment8
DECLARE_INTERFACE_(IDirectMusicSegment8, IDirectMusicSegment)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicSegment */
    STDMETHOD(GetLength)                (THIS_ MUSIC_TIME* pmtLength) PURE;
    STDMETHOD(SetLength)                (THIS_ MUSIC_TIME mtLength) PURE;
    STDMETHOD(GetRepeats)               (THIS_ DWORD* pdwRepeats) PURE;
    STDMETHOD(SetRepeats)               (THIS_ DWORD  dwRepeats) PURE;
    STDMETHOD(GetDefaultResolution)     (THIS_ DWORD* pdwResolution) PURE;
    STDMETHOD(SetDefaultResolution)     (THIS_ DWORD  dwResolution) PURE;
    STDMETHOD(GetTrack)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               IDirectMusicTrack** ppTrack) PURE;
    STDMETHOD(GetTrackGroup)            (THIS_ IDirectMusicTrack* pTrack, 
                                               DWORD* pdwGroupBits) PURE;
    STDMETHOD(InsertTrack)              (THIS_ IDirectMusicTrack* pTrack, 
                                               DWORD dwGroupBits) PURE;
    STDMETHOD(RemoveTrack)              (THIS_ IDirectMusicTrack* pTrack) PURE;
    STDMETHOD(InitPlay)                 (THIS_ IDirectMusicSegmentState** ppSegState, 
                                               IDirectMusicPerformance* pPerformance,
                                               DWORD dwFlags) PURE;
    STDMETHOD(GetGraph)                 (THIS_ IDirectMusicGraph** ppGraph) PURE;
    STDMETHOD(SetGraph)                 (THIS_ IDirectMusicGraph* pGraph) PURE;
    STDMETHOD(AddNotificationType)      (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(RemoveNotificationType)   (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(GetParam)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               MUSIC_TIME mtTime, 
                                               MUSIC_TIME* pmtNext, 
                                               void* pParam) PURE; 
    STDMETHOD(SetParam)                 (THIS_ REFGUID rguidType, 
                                               DWORD dwGroupBits, 
                                               DWORD dwIndex, 
                                               MUSIC_TIME mtTime, 
                                               void* pParam) PURE;
    STDMETHOD(Clone)                    (THIS_ MUSIC_TIME mtStart, 
                                               MUSIC_TIME mtEnd, 
                                               IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(SetStartPoint)            (THIS_ MUSIC_TIME mtStart) PURE;
    STDMETHOD(GetStartPoint)            (THIS_ MUSIC_TIME* pmtStart) PURE;
    STDMETHOD(SetLoopPoints)            (THIS_ MUSIC_TIME mtStart, 
                                               MUSIC_TIME mtEnd) PURE;
    STDMETHOD(GetLoopPoints)            (THIS_ MUSIC_TIME* pmtStart, 
                                               MUSIC_TIME* pmtEnd) PURE;
    STDMETHOD(SetPChannelsUsed)         (THIS_ DWORD dwNumPChannels, 
                                               DWORD* paPChannels) PURE;
    /*  IDirectMusicSegment8 */
    STDMETHOD(SetTrackConfig)           (THIS_ REFGUID rguidTrackClassID,   /* Class ID of the type of track on which to set the configuration flags. */
                                               DWORD dwGroupBits,           /* Group bits. */
                                               DWORD dwIndex,               /* Nth track (or DMUS_SEG_ALLTRACKS) that matches class id and group id. */
                                               DWORD dwFlagsOn,             /* DMUS_TRACKCONFIG_ flags to enable. */
                                               DWORD dwFlagsOff) PURE;      /* DMUS_TRACKCONFIG_ flags to disable. */
    STDMETHOD(GetAudioPathConfig)       (THIS_ IUnknown ** ppAudioPathConfig) PURE;
    STDMETHOD(Compose)                  (THIS_ MUSIC_TIME mtTime,
                                               IDirectMusicSegment* pFromSegment,
                                               IDirectMusicSegment* pToSegment,
                                               IDirectMusicSegment** ppComposedSegment) PURE;
    STDMETHOD(Download)                 (THIS_ IUnknown *pAudioPath) PURE;
    STDMETHOD(Unload)                   (THIS_ IUnknown *pAudioPath) PURE;
};

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicSegmentState */
#undef  INTERFACE
#define INTERFACE  IDirectMusicSegmentState
DECLARE_INTERFACE_(IDirectMusicSegmentState, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicSegmentState */
    STDMETHOD(GetRepeats)           (THIS_ DWORD* pdwRepeats) PURE;
    STDMETHOD(GetSegment )          (THIS_ IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(GetStartTime)         (THIS_ MUSIC_TIME* pmtStart) PURE;
    STDMETHOD(GetSeek)              (THIS_ MUSIC_TIME* pmtSeek) PURE;
    STDMETHOD(GetStartPoint)        (THIS_ MUSIC_TIME* pmtStart) PURE;
};

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicSegmentState8 */
#undef  INTERFACE
#define INTERFACE  IDirectMusicSegmentState8
DECLARE_INTERFACE_(IDirectMusicSegmentState8, IDirectMusicSegmentState)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicSegmentState */
    STDMETHOD(GetRepeats)           (THIS_ DWORD* pdwRepeats) PURE;
    STDMETHOD(GetSegment )          (THIS_ IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(GetStartTime)         (THIS_ MUSIC_TIME* pmtStart) PURE;
    STDMETHOD(GetSeek)              (THIS_ MUSIC_TIME* pmtSeek) PURE;
    STDMETHOD(GetStartPoint)        (THIS_ MUSIC_TIME* pmtStart) PURE;

    /* IDirectMusicSegmentState8 */
    STDMETHOD(SetTrackConfig)       (THIS_ REFGUID rguidTrackClassID,   /* Class ID of the type of track on which to set the configuration flags. */
                                           DWORD dwGroupBits,           /* Group bits. */
                                           DWORD dwIndex,               /* Nth track (or DMUS_SEG_ALLTRACKS) that matches class id and group id. */
                                           DWORD dwFlagsOn,             /* DMUS_TRACKCONFIG_ flags to enable. */
                                           DWORD dwFlagsOff) PURE;      /* DMUS_TRACKCONFIG_ flags to disable. */
    STDMETHOD(GetObjectInPath)      (THIS_ DWORD dwPChannel,    /* PChannel to search. */
                                           DWORD dwStage,       /* Which stage in the path. */
                                           DWORD dwBuffer,      /* Which buffer to address, if more than one. */
                                           REFGUID guidObject,  /* ClassID of object. */
                                           DWORD dwIndex,       /* Which object of that class. */
                                           REFGUID iidInterface,/* Requested COM interface. */
                                           void ** ppObject) PURE; /* Pointer to interface. */
};

/*////////////////////////////////////////////////////////////////////
// IDirectMusicAudioPath */
#undef  INTERFACE
#define INTERFACE  IDirectMusicAudioPath
DECLARE_INTERFACE_(IDirectMusicAudioPath, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicAudioPath */
    STDMETHOD(GetObjectInPath)      (THIS_ DWORD dwPChannel,    /* PChannel to search. */
                                           DWORD dwStage,       /* Which stage in the path. */
                                           DWORD dwBuffer,      /* Which buffer to address, if more than one. */
                                           REFGUID guidObject,  /* ClassID of object. */
                                           DWORD dwIndex,       /* Which object of that class. */
                                           REFGUID iidInterface,/* Requested COM interface. */
                                           void ** ppObject) PURE; /* Pointer to interface. */
    STDMETHOD(Activate)             (THIS_ BOOL fActivate) PURE;/* True to activate, False to deactivate. */
    STDMETHOD(SetVolume)            (THIS_ long lVolume,        /* Gain, in 100ths of a dB. This must be negative (0 represents full volume.) */
                                           DWORD dwDuration) PURE;/* Duration of volume ramp in  milliseconds. Note that 0 is more efficient. */
    STDMETHOD(ConvertPChannel)      (THIS_ DWORD dwPChannelIn,   /* Pchannel of source. */
                                           DWORD *pdwPChannelOut) PURE; /* Equivalent pchannel on performance. */
};

typedef IDirectMusicAudioPath IDirectMusicAudioPath8;

/*////////////////////////////////////////////////////////////////////
// IDirectMusicPerformance */
#undef  INTERFACE
#define INTERFACE  IDirectMusicPerformance
DECLARE_INTERFACE_(IDirectMusicPerformance, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicPerformance */
    STDMETHOD(Init)                 (THIS_ IDirectMusic** ppDirectMusic,
                                           LPDIRECTSOUND pDirectSound,
                                           HWND hWnd) PURE;
    STDMETHOD(PlaySegment)          (THIS_ IDirectMusicSegment* pSegment, 
                                           DWORD dwFlags, 
                                           __int64 i64StartTime, 
                                           IDirectMusicSegmentState** ppSegmentState) PURE;
    STDMETHOD(Stop)                 (THIS_ IDirectMusicSegment* pSegment, 
                                           IDirectMusicSegmentState* pSegmentState, 
                                           MUSIC_TIME mtTime, 
                                           DWORD dwFlags) PURE;
    STDMETHOD(GetSegmentState)      (THIS_ IDirectMusicSegmentState** ppSegmentState, 
                                           MUSIC_TIME mtTime) PURE;
    STDMETHOD(SetPrepareTime)       (THIS_ DWORD dwMilliSeconds) PURE;
    STDMETHOD(GetPrepareTime)       (THIS_ DWORD* pdwMilliSeconds) PURE;
    STDMETHOD(SetBumperLength)      (THIS_ DWORD dwMilliSeconds) PURE;
    STDMETHOD(GetBumperLength)      (THIS_ DWORD* pdwMilliSeconds) PURE;
    STDMETHOD(SendPMsg)             (THIS_ DMUS_PMSG* pPMSG) PURE;
    STDMETHOD(MusicToReferenceTime) (THIS_ MUSIC_TIME mtTime, 
                                           REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(ReferenceToMusicTime) (THIS_ REFERENCE_TIME rtTime, 
                                           MUSIC_TIME* pmtTime) PURE;
    STDMETHOD(IsPlaying)            (THIS_ IDirectMusicSegment* pSegment, 
                                           IDirectMusicSegmentState* pSegState) PURE;
    STDMETHOD(GetTime)              (THIS_ REFERENCE_TIME* prtNow, 
                                           MUSIC_TIME* pmtNow) PURE;
    STDMETHOD(AllocPMsg)            (THIS_ ULONG cb, 
                                           DMUS_PMSG** ppPMSG) PURE;
    STDMETHOD(FreePMsg)             (THIS_ DMUS_PMSG* pPMSG) PURE;
    STDMETHOD(GetGraph)             (THIS_ IDirectMusicGraph** ppGraph) PURE;
    STDMETHOD(SetGraph)             (THIS_ IDirectMusicGraph* pGraph) PURE;
    STDMETHOD(SetNotificationHandle)(THIS_ HANDLE hNotification, 
                                           REFERENCE_TIME rtMinimum) PURE;
    STDMETHOD(GetNotificationPMsg)  (THIS_ DMUS_NOTIFICATION_PMSG** ppNotificationPMsg) PURE;
    STDMETHOD(AddNotificationType)  (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(RemoveNotificationType)(THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(AddPort)              (THIS_ IDirectMusicPort* pPort) PURE;
    STDMETHOD(RemovePort)           (THIS_ IDirectMusicPort* pPort ) PURE;
    STDMETHOD(AssignPChannelBlock)  (THIS_ DWORD dwBlockNum, 
                                           IDirectMusicPort* pPort, 
                                           DWORD dwGroup ) PURE;
    STDMETHOD(AssignPChannel)       (THIS_ DWORD dwPChannel, 
                                           IDirectMusicPort* pPort, 
                                           DWORD dwGroup, 
                                           DWORD dwMChannel ) PURE;
    STDMETHOD(PChannelInfo)         (THIS_ DWORD dwPChannel, 
                                           IDirectMusicPort** ppPort, 
                                           DWORD* pdwGroup, 
                                           DWORD* pdwMChannel ) PURE;
    STDMETHOD(DownloadInstrument)   (THIS_ IDirectMusicInstrument* pInst, 
                                           DWORD dwPChannel, 
                                           IDirectMusicDownloadedInstrument** ppDownInst, 
                                           DMUS_NOTERANGE* pNoteRanges, 
                                           DWORD dwNumNoteRanges, 
                                           IDirectMusicPort** ppPort, 
                                           DWORD* pdwGroup, 
                                           DWORD* pdwMChannel ) PURE;
    STDMETHOD(Invalidate)           (THIS_ MUSIC_TIME mtTime, 
                                           DWORD dwFlags) PURE;
    STDMETHOD(GetParam)             (THIS_ REFGUID rguidType, 
                                           DWORD dwGroupBits, 
                                           DWORD dwIndex, 
                                           MUSIC_TIME mtTime, 
                                           MUSIC_TIME* pmtNext, 
                                           void* pParam) PURE; 
    STDMETHOD(SetParam)             (THIS_ REFGUID rguidType, 
                                           DWORD dwGroupBits, 
                                           DWORD dwIndex, 
                                           MUSIC_TIME mtTime, 
                                           void* pParam) PURE;
    STDMETHOD(GetGlobalParam)       (THIS_ REFGUID rguidType, 
                                           void* pParam, 
                                           DWORD dwSize) PURE;
    STDMETHOD(SetGlobalParam)       (THIS_ REFGUID rguidType, 
                                           void* pParam, 
                                           DWORD dwSize) PURE;
    STDMETHOD(GetLatencyTime)       (THIS_ REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(GetQueueTime)         (THIS_ REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(AdjustTime)           (THIS_ REFERENCE_TIME rtAmount) PURE;
    STDMETHOD(CloseDown)            (THIS) PURE;
    STDMETHOD(GetResolvedTime)      (THIS_ REFERENCE_TIME rtTime,
                                           REFERENCE_TIME* prtResolved,
                                           DWORD dwTimeResolveFlags) PURE;
    STDMETHOD(MIDIToMusic)          (THIS_ BYTE bMIDIValue,
                                           DMUS_CHORD_KEY* pChord,
                                           BYTE bPlayMode,
                                           BYTE bChordLevel,
                                           WORD *pwMusicValue) PURE;
    STDMETHOD(MusicToMIDI)          (THIS_ WORD wMusicValue,
                                           DMUS_CHORD_KEY* pChord,
                                           BYTE bPlayMode,
                                           BYTE bChordLevel,
                                           BYTE *pbMIDIValue) PURE;
    STDMETHOD(TimeToRhythm)         (THIS_ MUSIC_TIME mtTime,
                                           DMUS_TIMESIGNATURE *pTimeSig,
                                           WORD *pwMeasure,
                                           BYTE *pbBeat,
                                           BYTE *pbGrid,
                                           short *pnOffset) PURE;
    STDMETHOD(RhythmToTime)         (THIS_ WORD wMeasure,
                                           BYTE bBeat,
                                           BYTE bGrid,
                                           short nOffset,
                                           DMUS_TIMESIGNATURE *pTimeSig,
                                           MUSIC_TIME *pmtTime) PURE;                                        
};

/*////////////////////////////////////////////////////////////////////
// IDirectMusicPerformance8 */
#undef  INTERFACE
#define INTERFACE  IDirectMusicPerformance8
DECLARE_INTERFACE_(IDirectMusicPerformance8, IDirectMusicPerformance)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicPerformance */
    STDMETHOD(Init)                 (THIS_ IDirectMusic** ppDirectMusic,
                                           LPDIRECTSOUND pDirectSound,
                                           HWND hWnd) PURE;
    STDMETHOD(PlaySegment)          (THIS_ IDirectMusicSegment* pSegment, 
                                           DWORD dwFlags, 
                                           __int64 i64StartTime, 
                                           IDirectMusicSegmentState** ppSegmentState) PURE;
    STDMETHOD(Stop)                 (THIS_ IDirectMusicSegment* pSegment, 
                                           IDirectMusicSegmentState* pSegmentState, 
                                           MUSIC_TIME mtTime, 
                                           DWORD dwFlags) PURE;
    STDMETHOD(GetSegmentState)      (THIS_ IDirectMusicSegmentState** ppSegmentState, 
                                           MUSIC_TIME mtTime) PURE;
    STDMETHOD(SetPrepareTime)       (THIS_ DWORD dwMilliSeconds) PURE;
    STDMETHOD(GetPrepareTime)       (THIS_ DWORD* pdwMilliSeconds) PURE;
    STDMETHOD(SetBumperLength)      (THIS_ DWORD dwMilliSeconds) PURE;
    STDMETHOD(GetBumperLength)      (THIS_ DWORD* pdwMilliSeconds) PURE;
    STDMETHOD(SendPMsg)             (THIS_ DMUS_PMSG* pPMSG) PURE;
    STDMETHOD(MusicToReferenceTime) (THIS_ MUSIC_TIME mtTime, 
                                           REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(ReferenceToMusicTime) (THIS_ REFERENCE_TIME rtTime, 
                                           MUSIC_TIME* pmtTime) PURE;
    STDMETHOD(IsPlaying)            (THIS_ IDirectMusicSegment* pSegment, 
                                           IDirectMusicSegmentState* pSegState) PURE;
    STDMETHOD(GetTime)              (THIS_ REFERENCE_TIME* prtNow, 
                                           MUSIC_TIME* pmtNow) PURE;
    STDMETHOD(AllocPMsg)            (THIS_ ULONG cb, 
                                           DMUS_PMSG** ppPMSG) PURE;
    STDMETHOD(FreePMsg)             (THIS_ DMUS_PMSG* pPMSG) PURE;
    STDMETHOD(GetGraph)             (THIS_ IDirectMusicGraph** ppGraph) PURE;
    STDMETHOD(SetGraph)             (THIS_ IDirectMusicGraph* pGraph) PURE;
    STDMETHOD(SetNotificationHandle)(THIS_ HANDLE hNotification, 
                                           REFERENCE_TIME rtMinimum) PURE;
    STDMETHOD(GetNotificationPMsg)  (THIS_ DMUS_NOTIFICATION_PMSG** ppNotificationPMsg) PURE;
    STDMETHOD(AddNotificationType)  (THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(RemoveNotificationType)(THIS_ REFGUID rguidNotificationType) PURE;
    STDMETHOD(AddPort)              (THIS_ IDirectMusicPort* pPort) PURE;
    STDMETHOD(RemovePort)           (THIS_ IDirectMusicPort* pPort ) PURE;
    STDMETHOD(AssignPChannelBlock)  (THIS_ DWORD dwBlockNum, 
                                           IDirectMusicPort* pPort, 
                                           DWORD dwGroup ) PURE;
    STDMETHOD(AssignPChannel)       (THIS_ DWORD dwPChannel, 
                                           IDirectMusicPort* pPort, 
                                           DWORD dwGroup, 
                                           DWORD dwMChannel ) PURE;
    STDMETHOD(PChannelInfo)         (THIS_ DWORD dwPChannel, 
                                           IDirectMusicPort** ppPort, 
                                           DWORD* pdwGroup, 
                                           DWORD* pdwMChannel ) PURE;
    STDMETHOD(DownloadInstrument)   (THIS_ IDirectMusicInstrument* pInst, 
                                           DWORD dwPChannel, 
                                           IDirectMusicDownloadedInstrument** ppDownInst, 
                                           DMUS_NOTERANGE* pNoteRanges, 
                                           DWORD dwNumNoteRanges, 
                                           IDirectMusicPort** ppPort, 
                                           DWORD* pdwGroup, 
                                           DWORD* pdwMChannel ) PURE;
    STDMETHOD(Invalidate)           (THIS_ MUSIC_TIME mtTime, 
                                           DWORD dwFlags) PURE;
    STDMETHOD(GetParam)             (THIS_ REFGUID rguidType, 
                                           DWORD dwGroupBits, 
                                           DWORD dwIndex, 
                                           MUSIC_TIME mtTime, 
                                           MUSIC_TIME* pmtNext, 
                                           void* pParam) PURE; 
    STDMETHOD(SetParam)             (THIS_ REFGUID rguidType, 
                                           DWORD dwGroupBits, 
                                           DWORD dwIndex, 
                                           MUSIC_TIME mtTime, 
                                           void* pParam) PURE;
    STDMETHOD(GetGlobalParam)       (THIS_ REFGUID rguidType, 
                                           void* pParam, 
                                           DWORD dwSize) PURE;
    STDMETHOD(SetGlobalParam)       (THIS_ REFGUID rguidType, 
                                           void* pParam, 
                                           DWORD dwSize) PURE;
    STDMETHOD(GetLatencyTime)       (THIS_ REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(GetQueueTime)         (THIS_ REFERENCE_TIME* prtTime) PURE;
    STDMETHOD(AdjustTime)           (THIS_ REFERENCE_TIME rtAmount) PURE;
    STDMETHOD(CloseDown)            (THIS) PURE;
    STDMETHOD(GetResolvedTime)      (THIS_ REFERENCE_TIME rtTime,
                                           REFERENCE_TIME* prtResolved,
                                           DWORD dwTimeResolveFlags) PURE;
    STDMETHOD(MIDIToMusic)          (THIS_ BYTE bMIDIValue,
                                           DMUS_CHORD_KEY* pChord,
                                           BYTE bPlayMode,
                                           BYTE bChordLevel,
                                           WORD *pwMusicValue) PURE;
    STDMETHOD(MusicToMIDI)          (THIS_ WORD wMusicValue,
                                           DMUS_CHORD_KEY* pChord,
                                           BYTE bPlayMode,
                                           BYTE bChordLevel,
                                           BYTE *pbMIDIValue) PURE;
    STDMETHOD(TimeToRhythm)         (THIS_ MUSIC_TIME mtTime,
                                           DMUS_TIMESIGNATURE *pTimeSig,
                                           WORD *pwMeasure,
                                           BYTE *pbBeat,
                                           BYTE *pbGrid,
                                           short *pnOffset) PURE;
    STDMETHOD(RhythmToTime)         (THIS_ WORD wMeasure,
                                           BYTE bBeat,
                                           BYTE bGrid,
                                           short nOffset,
                                           DMUS_TIMESIGNATURE *pTimeSig,
                                           MUSIC_TIME *pmtTime) PURE;  
    /*  IDirectMusicPerformance8 */
    STDMETHOD(InitAudio)            (THIS_ IDirectMusic** ppDirectMusic,            /* Optional DMusic pointer. */
                                           IDirectSound** ppDirectSound,            /* Optional DSound pointer. */
                                           HWND hWnd,                               /* HWND for DSound. */
                                           DWORD dwDefaultPathType,                 /* Requested default audio path type, also optional. */
                                           DWORD dwPChannelCount,                   /* Number of PChannels, if default audio path to be created. */
                                           DWORD dwFlags,                           /* DMUS_AUDIOF flags, if no pParams structure. */
                                           DMUS_AUDIOPARAMS *pParams) PURE;         /* Optional initialization structure, defining required voices, buffers, etc. */
    STDMETHOD(PlaySegmentEx)        (THIS_ IUnknown* pSource,                       /* Segment to play. */
                                           WCHAR *pwzSegmentName,                   /* Not supported in DX8. */
                                           IUnknown* pTransition,                   /* Optional template segment to compose transition with. */
                                           DWORD dwFlags,                           /* DMUS_SEGF_ flags. */ 
                                           __int64 i64StartTime,                    /* Time to start playback. */
                                           IDirectMusicSegmentState** ppSegmentState, /* Returned Segment State. */
                                           IUnknown *pFrom,                         /* Optional segmentstate or audiopath to replace. */
                                           IUnknown *pAudioPath) PURE;              /* Optional audioPath to play on. */
    STDMETHOD(StopEx)               (THIS_ IUnknown *pObjectToStop,                 /* Segstate, AudioPath, or Segment. */ 
                                           __int64 i64StopTime, 
                                           DWORD dwFlags) PURE;
    STDMETHOD(ClonePMsg)            (THIS_ DMUS_PMSG* pSourcePMSG,
                                           DMUS_PMSG** ppCopyPMSG) PURE;
    STDMETHOD(CreateAudioPath)      (THIS_ IUnknown *pSourceConfig,                 /* Source configuration, from AudioPathConfig file. */
                                           BOOL fActivate,                          /* TRUE to activate on creation. */
                                           IDirectMusicAudioPath **ppNewPath) PURE; /* Returns created audiopath. */                                           
    STDMETHOD(CreateStandardAudioPath)(THIS_ DWORD dwType,                          /* Type of path to create. */
                                           DWORD dwPChannelCount,                   /* How many PChannels to allocate for it. */
                                           BOOL fActivate,                          /* TRUE to activate on creation. */
                                           IDirectMusicAudioPath **ppNewPath) PURE; /* Returns created audiopath. */
    STDMETHOD(SetDefaultAudioPath)  (THIS_ IDirectMusicAudioPath *pAudioPath) PURE;
    STDMETHOD(GetDefaultAudioPath)  (THIS_ IDirectMusicAudioPath **ppAudioPath) PURE;
    STDMETHOD(GetParamEx)           (THIS_ REFGUID rguidType,                       /* GetParam command ID. */
                                           DWORD dwTrackID,                         /* Virtual track ID of caller. */
                                           DWORD dwGroupBits,                       /* Group bits of caller. */
                                           DWORD dwIndex,                           /* Index to Nth parameter. */
                                           MUSIC_TIME mtTime,                       /* Time of requested parameter. */
                                           MUSIC_TIME* pmtNext,                     /* Returned delta to next parameter. */
                                           void* pParam) PURE;                      /* Data structure to fill with parameter. */
};



/*////////////////////////////////////////////////////////////////////
// IDirectMusicGraph */
#undef  INTERFACE
#define INTERFACE  IDirectMusicGraph
DECLARE_INTERFACE_(IDirectMusicGraph, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicGraph */
    STDMETHOD(StampPMsg)            (THIS_ DMUS_PMSG* pPMSG) PURE;
    STDMETHOD(InsertTool)           (THIS_ IDirectMusicTool* pTool, 
                                           DWORD* pdwPChannels, 
                                           DWORD cPChannels, 
                                           LONG lIndex) PURE;
    STDMETHOD(GetTool)              (THIS_ DWORD dwIndex, 
                                           IDirectMusicTool** ppTool) PURE;
    STDMETHOD(RemoveTool)           (THIS_ IDirectMusicTool* pTool) PURE;
};

typedef IDirectMusicGraph IDirectMusicGraph8;


/*/////////////////////////////////////////////////////////////////////
// IDirectMusicStyle */
#undef  INTERFACE
#define INTERFACE  IDirectMusicStyle
DECLARE_INTERFACE_(IDirectMusicStyle, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)         (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG,Release)         (THIS) PURE;

    /*  IDirectMusicStyle */
    STDMETHOD(GetBand)                (THIS_ WCHAR* pwszName, 
                                             IDirectMusicBand** ppBand) PURE;
    STDMETHOD(EnumBand)               (THIS_ DWORD dwIndex, 
                                             WCHAR *pwszName) PURE;
    STDMETHOD(GetDefaultBand)         (THIS_ IDirectMusicBand** ppBand) PURE;
    STDMETHOD(EnumMotif)              (THIS_ DWORD dwIndex, 
                                             WCHAR* pwszName) PURE;
    STDMETHOD(GetMotif)               (THIS_ WCHAR* pwszName, 
                                             IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(GetDefaultChordMap)     (THIS_ IDirectMusicChordMap** ppChordMap) PURE;
    STDMETHOD(EnumChordMap)           (THIS_ DWORD dwIndex, 
                                             WCHAR *pwszName) PURE;
    STDMETHOD(GetChordMap)            (THIS_ WCHAR* pwszName, 
                                             IDirectMusicChordMap** ppChordMap) PURE;
    STDMETHOD(GetTimeSignature)       (THIS_ DMUS_TIMESIGNATURE* pTimeSig) PURE;
    STDMETHOD(GetEmbellishmentLength) (THIS_ DWORD dwType, 
                                             DWORD dwLevel, 
                                             DWORD* pdwMin, 
                                             DWORD* pdwMax) PURE;
    STDMETHOD(GetTempo)               (THIS_ double* pTempo) PURE;
};

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicStyle8 */
#undef  INTERFACE
#define INTERFACE  IDirectMusicStyle8
DECLARE_INTERFACE_(IDirectMusicStyle8, IDirectMusicStyle)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)               (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)                (THIS) PURE;
    STDMETHOD_(ULONG,Release)               (THIS) PURE;

    /*  IDirectMusicStyle */
    STDMETHOD(GetBand)                (THIS_ WCHAR* pwszName, 
                                             IDirectMusicBand** ppBand) PURE;
    STDMETHOD(EnumBand)               (THIS_ DWORD dwIndex, 
                                             WCHAR *pwszName) PURE;
    STDMETHOD(GetDefaultBand)         (THIS_ IDirectMusicBand** ppBand) PURE;
    STDMETHOD(EnumMotif)              (THIS_ DWORD dwIndex, 
                                             WCHAR* pwszName) PURE;
    STDMETHOD(GetMotif)               (THIS_ WCHAR* pwszName, 
                                             IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(GetDefaultChordMap)     (THIS_ IDirectMusicChordMap** ppChordMap) PURE;
    STDMETHOD(EnumChordMap)           (THIS_ DWORD dwIndex, 
                                             WCHAR *pwszName) PURE;
    STDMETHOD(GetChordMap)            (THIS_ WCHAR* pwszName, 
                                             IDirectMusicChordMap** ppChordMap) PURE;
    STDMETHOD(GetTimeSignature)       (THIS_ DMUS_TIMESIGNATURE* pTimeSig) PURE;
    STDMETHOD(GetEmbellishmentLength) (THIS_ DWORD dwType, 
                                             DWORD dwLevel, 
                                             DWORD* pdwMin, 
                                             DWORD* pdwMax) PURE;
    STDMETHOD(GetTempo)               (THIS_ double* pTempo) PURE;

    /*  IDirectMusicStyle8 */
    STDMETHOD(EnumPattern)            (THIS_ DWORD dwIndex, 
                                             DWORD dwPatternType,
                                             WCHAR* pwszName) PURE;
};

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicChordMap */
#undef  INTERFACE
#define INTERFACE  IDirectMusicChordMap
DECLARE_INTERFACE_(IDirectMusicChordMap, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicChordMap */
    STDMETHOD(GetScale)             (THIS_ DWORD* pdwScale) PURE;
};

typedef IDirectMusicChordMap IDirectMusicChordMap8;

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicComposer */
#undef  INTERFACE
#define INTERFACE  IDirectMusicComposer
DECLARE_INTERFACE_(IDirectMusicComposer, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)               (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)                (THIS) PURE;
    STDMETHOD_(ULONG,Release)               (THIS) PURE;

    /*  IDirectMusicComposer */
    STDMETHOD(ComposeSegmentFromTemplate)   (THIS_ IDirectMusicStyle* pStyle, 
                                                   IDirectMusicSegment* pTemplate, 
                                                   WORD wActivity, 
                                                   IDirectMusicChordMap* pChordMap, 
                                                   IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(ComposeSegmentFromShape)      (THIS_ IDirectMusicStyle* pStyle, 
                                                   WORD wNumMeasures, 
                                                   WORD wShape, 
                                                   WORD wActivity, 
                                                   BOOL fIntro, 
                                                   BOOL fEnd, 
                                                   IDirectMusicChordMap* pChordMap, 
                                                   IDirectMusicSegment** ppSegment ) PURE;
    STDMETHOD(ComposeTransition)            (THIS_ IDirectMusicSegment* pFromSeg, 
                                                   IDirectMusicSegment* pToSeg, 
                                                   MUSIC_TIME mtTime, 
                                                   WORD wCommand, 
                                                   DWORD dwFlags, 
                                                   IDirectMusicChordMap* pChordMap, 
                                                   IDirectMusicSegment** ppTransSeg) PURE;
    STDMETHOD(AutoTransition)               (THIS_ IDirectMusicPerformance* pPerformance, 
                                                   IDirectMusicSegment* pToSeg, 
                                                   WORD wCommand, 
                                                   DWORD dwFlags, 
                                                   IDirectMusicChordMap* pChordMap, 
                                                   IDirectMusicSegment** ppTransSeg, 
                                                   IDirectMusicSegmentState** ppToSegState, 
                                                   IDirectMusicSegmentState** ppTransSegState) PURE;
    STDMETHOD(ComposeTemplateFromShape)     (THIS_ WORD wNumMeasures, 
                                                   WORD wShape, 
                                                   BOOL fIntro, 
                                                   BOOL fEnd, 
                                                   WORD wEndLength, 
                                                   IDirectMusicSegment** ppTemplate) PURE;
    STDMETHOD(ChangeChordMap)            (THIS_ IDirectMusicSegment* pSegment, 
                                                   BOOL fTrackScale, 
                                                   IDirectMusicChordMap* pChordMap) PURE;
};

typedef IDirectMusicComposer IDirectMusicComposer8;

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicPatternTrack */

#undef  INTERFACE
#define INTERFACE  IDirectMusicPatternTrack
DECLARE_INTERFACE_(IDirectMusicPatternTrack, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)               (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)                (THIS) PURE;
    STDMETHOD_(ULONG,Release)               (THIS) PURE;

    /*  IDirectMusicPatternTrack */
    STDMETHOD(CreateSegment)             (THIS_ IDirectMusicStyle* pStyle,
                                                IDirectMusicSegment** ppSegment) PURE;
    STDMETHOD(SetVariation)              (THIS_ IDirectMusicSegmentState* pSegState,
                                                DWORD dwVariationFlags,
                                                DWORD dwPart) PURE;
    STDMETHOD(SetPatternByName)          (THIS_ IDirectMusicSegmentState* pSegState,
                                                WCHAR* wszName,
                                                IDirectMusicStyle* pStyle,
                                                DWORD dwPatternType,
                                                DWORD* pdwLength) PURE;
};

typedef IDirectMusicPatternTrack IDirectMusicPatternTrack8;

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicScript */

#undef  INTERFACE
#define INTERFACE  IDirectMusicScript
DECLARE_INTERFACE_(IDirectMusicScript, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)       (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectMusicScript */
    STDMETHOD(Init)                     (THIS_ IDirectMusicPerformance *pPerformance,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(CallRoutine)              (THIS_ WCHAR *pwszRoutineName,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(SetVariableVariant)       (THIS_ WCHAR *pwszVariableName,
                                               VARIANT varValue,
                                               BOOL fSetRef,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(GetVariableVariant)       (THIS_ WCHAR *pwszVariableName,
                                               VARIANT *pvarValue,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(SetVariableNumber)        (THIS_ WCHAR *pwszVariableName,
                                               LONG lValue,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(GetVariableNumber)        (THIS_ WCHAR *pwszVariableName,
                                               LONG *plValue,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(SetVariableObject)        (THIS_ WCHAR *pwszVariableName,
                                               IUnknown *punkValue,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(GetVariableObject)        (THIS_ WCHAR *pwszVariableName,
                                               REFIID riid,
                                               LPVOID FAR *ppv,
                                               DMUS_SCRIPT_ERRORINFO *pErrorInfo) PURE;
    STDMETHOD(EnumRoutine)              (THIS_ DWORD dwIndex, 
                                               WCHAR *pwszName) PURE;
    STDMETHOD(EnumVariable)             (THIS_ DWORD dwIndex, 
                                               WCHAR *pwszName) PURE;
};

typedef IDirectMusicScript IDirectMusicScript8;

/*/////////////////////////////////////////////////////////////////////
// IDirectMusicContainer */

#undef  INTERFACE
#define INTERFACE  IDirectMusicContainer
DECLARE_INTERFACE_(IDirectMusicContainer, IUnknown)
{
    /*  IUnknown */
    STDMETHOD(QueryInterface)               (THIS_ REFIID, LPVOID FAR *) PURE;
    STDMETHOD_(ULONG,AddRef)                (THIS) PURE;
    STDMETHOD_(ULONG,Release)               (THIS) PURE;

    /*  IDirectMusicContainer */
    STDMETHOD(EnumObject)           (THIS_ REFGUID rguidClass, 
                                           DWORD dwIndex, 
                                           LPDMUS_OBJECTDESC pDesc,
                                           WCHAR *pwszAlias) PURE;
};

typedef IDirectMusicContainer IDirectMusicContainer8;

/* CLSID's */
DEFINE_GUID(CLSID_DirectMusicPerformance,0xd2ac2881, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicSegment,0xd2ac2882, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicSegmentState,0xd2ac2883, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicGraph,0xd2ac2884, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicStyle,0xd2ac288a, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicChordMap,0xd2ac288f, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicComposer,0xd2ac2890, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicLoader,0xd2ac2892, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicBand,0x79ba9e00, 0xb6ee, 0x11d1, 0x86, 0xbe, 0x0, 0xc0, 0x4f, 0xbf, 0x8f, 0xef);

/* New CLSID's for DX8 */
DEFINE_GUID(CLSID_DirectMusicPatternTrack,0xd2ac2897, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(CLSID_DirectMusicScript,0x810b5013, 0xe88d, 0x11d2, 0x8b, 0xc1, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xb6); /* {810B5013-E88D-11d2-8BC1-00600893B1B6} */
DEFINE_GUID(CLSID_DirectMusicContainer,0x9301e380, 0x1f22, 0x11d3, 0x82, 0x26, 0xd2, 0xfa, 0x76, 0x25, 0x5d, 0x47);
DEFINE_GUID(CLSID_DirectSoundWave,0x8a667154, 0xf9cb, 0x11d2, 0xad, 0x8a, 0x0, 0x60, 0xb0, 0x57, 0x5a, 0xbc);
DEFINE_GUID(CLSID_DirectMusicAudioPathConfig,0xee0b9ca0, 0xa81e, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);

/* Special GUID for all object types. This is used by the loader. */
DEFINE_GUID(GUID_DirectMusicAllTypes,0xd2ac2893, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Notification guids */
DEFINE_GUID(GUID_NOTIFICATION_SEGMENT,0xd2ac2899, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_NOTIFICATION_PERFORMANCE,0x81f75bc5, 0x4e5d, 0x11d2, 0xbc, 0xc7, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(GUID_NOTIFICATION_MEASUREANDBEAT,0xd2ac289a, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_NOTIFICATION_CHORD,0xd2ac289b, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_NOTIFICATION_COMMAND,0xd2ac289c, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_NOTIFICATION_RECOMPOSE, 0xd348372b, 0x945b, 0x45ae, 0xa5, 0x22, 0x45, 0xf, 0x12, 0x5b, 0x84, 0xa5);

/* Track param type guids */
/* Use to get/set a DMUS_COMMAND_PARAM param in the Command track */
DEFINE_GUID(GUID_CommandParam,0xd2ac289d, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get a DMUS_COMMAND_PARAM_2 param in the Command track */
DEFINE_GUID(GUID_CommandParam2, 0x28f97ef7, 0x9538, 0x11d2, 0x97, 0xa9, 0x0, 0xc0, 0x4f, 0xa3, 0x6e, 0x58);

/* Use to get/set a DMUS_COMMAND_PARAM_2 param to be used as the command following all commands in
the Command track (this information can't be saved) */
DEFINE_GUID(GUID_CommandParamNext, 0x472afe7a, 0x281b, 0x11d3, 0x81, 0x7d, 0x0, 0xc0, 0x4f, 0xa3, 0x6e, 0x58);

/* Use to get/set a DMUS_CHORD_PARAM param in the Chord track */
DEFINE_GUID(GUID_ChordParam,0xd2ac289e, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get a DMUS_RHYTHM_PARAM param in the Chord track */
DEFINE_GUID(GUID_RhythmParam,0xd2ac289f, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get/set an IDirectMusicStyle param in the Style track */
DEFINE_GUID(GUID_IDirectMusicStyle,0xd2ac28a1, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get a DMUS_TIMESIGNATURE param in the Style and TimeSig tracks */
DEFINE_GUID(GUID_TimeSignature,0xd2ac28a4, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get/set a DMUS_TEMPO_PARAM param in the Tempo track */
DEFINE_GUID(GUID_TempoParam,0xd2ac28a5, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get the next valid point in a segment at which it may start */
DEFINE_GUID(GUID_Valid_Start_Time,0x7f6b1760, 0x1fdb, 0x11d3, 0x82, 0x26, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);

/* Use to get the next point in the currently playing primary segment at which a new segment may start */
DEFINE_GUID(GUID_Play_Marker,0xd8761a41, 0x801a, 0x11d3, 0x9b, 0xd1, 0xda, 0xf7, 0xe1, 0xc3, 0xd8, 0x34);

/* Use to get (GetParam) or add (SetParam) bands in the Band track */
DEFINE_GUID(GUID_BandParam,0x2bb1938, 0xcb8b, 0x11d2, 0x8b, 0xb9, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xb6);
typedef struct _DMUS_BAND_PARAM
{
    MUSIC_TIME  mtTimePhysical; /* Note: If this is a clock-time track, then this field is interpreted in the track's internal time format, which is the number of milliseconds after the beginning of playback. */
    IDirectMusicBand *pBand;
} DMUS_BAND_PARAM;

/* Obsolete -- doesn't distinguish physical and logical time.  Use GUID_BandParam instead. */
DEFINE_GUID(GUID_IDirectMusicBand,0xd2ac28ac, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get/set an IDirectMusicChordMap param in the ChordMap track */
DEFINE_GUID(GUID_IDirectMusicChordMap,0xd2ac28ad, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Use to get/set a DMUS_MUTE_PARAM param in the Mute track */
DEFINE_GUID(GUID_MuteParam,0xd2ac28af, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* These guids are used in IDirectMusicSegment::SetParam to tell the band track to perform various actions.
   Some of these guids (where noted) also apply to wave tracks.
 */
/* Download bands/waves for the IDirectMusicSegment */
DEFINE_GUID(GUID_Download,0xd2ac28a7, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Unload bands/waves for the IDirectMusicSegment */
DEFINE_GUID(GUID_Unload,0xd2ac28a8, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Connect segment's bands to an IDirectMusicCollection */
DEFINE_GUID(GUID_ConnectToDLSCollection, 0x1db1ae6b, 0xe92e, 0x11d1, 0xa8, 0xc5, 0x0, 0xc0, 0x4f, 0xa3, 0x72, 0x6e);

/* Enable/disable autodownloading of bands/waves */
DEFINE_GUID(GUID_Enable_Auto_Download,0xd2ac28a9, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_Disable_Auto_Download,0xd2ac28aa, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Clear all bands */
DEFINE_GUID(GUID_Clear_All_Bands,0xd2ac28ab, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Set segment to manage all program changes, bank selects, etc. for simple playback of a standard MIDI file */
DEFINE_GUID(GUID_StandardMIDIFile, 0x6621075, 0xe92e, 0x11d1, 0xa8, 0xc5, 0x0, 0xc0, 0x4f, 0xa3, 0x72, 0x6e);
/* For compatibility with beta releases... */
#define GUID_IgnoreBankSelectForGM 	GUID_StandardMIDIFile

/* Disable/enable param guids. Use these in SetParam calls to disable or enable sending
 * specific PMsg types.
 */
DEFINE_GUID(GUID_DisableTimeSig, 0x45fc707b, 0x1db4, 0x11d2, 0xbc, 0xac, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(GUID_EnableTimeSig, 0x45fc707c, 0x1db4, 0x11d2, 0xbc, 0xac, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(GUID_DisableTempo, 0x45fc707d, 0x1db4, 0x11d2, 0xbc, 0xac, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(GUID_EnableTempo, 0x45fc707e, 0x1db4, 0x11d2, 0xbc, 0xac, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);

/* Used in SetParam calls for pattern-based tracks.  A nonzero value seeds the random number 
generator for variation selection; a value of zero reverts to the default behavior of 
getting the seed from the system clock.
*/
DEFINE_GUID(GUID_SeedVariations, 0x65b76fa5, 0xff37, 0x11d2, 0x81, 0x4e, 0x0, 0xc0, 0x4f, 0xa3, 0x6e, 0x58);

/* Used to get the variations currently in effect across PChannels */
DEFINE_GUID(GUID_Variations, 0x11f72cce, 0x26e6, 0x4ecd, 0xaf, 0x2e, 0xd6, 0x68, 0xe6, 0x67, 0x7, 0xd8);
typedef struct _DMUS_VARIATIONS_PARAM
{
    DWORD   dwPChannelsUsed; /* number of PChannels in use */
    DWORD*  padwPChannels;   /* array of PChannels in use */
    DWORD*  padwVariations;  /* array of variations in effect for each PChannel */
} DMUS_VARIATIONS_PARAM;

/* Download bands/waves for the IDirectMusicSegment, passed an IDirectMusicAudioPath instead of an IDirectMusicPerformance */
DEFINE_GUID(GUID_DownloadToAudioPath,0x9f2c0341, 0xc5c4, 0x11d3, 0x9b, 0xd1, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);

/* Unload bands/waves for the IDirectMusicSegment, passed an IDirectMusicAudioPath instead of an IDirectMusicPerformance */
DEFINE_GUID(GUID_UnloadFromAudioPath,0x9f2c0342, 0xc5c4, 0x11d3, 0x9b, 0xd1, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);


/* Global data guids */
DEFINE_GUID(GUID_PerfMasterTempo,0xd2ac28b0, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_PerfMasterVolume,0xd2ac28b1, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_PerfMasterGrooveLevel,0xd2ac28b2, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(GUID_PerfAutoDownload, 0xfb09565b, 0x3631, 0x11d2, 0xbc, 0xb8, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);

/* GUID for default GM/GS dls collection. */
DEFINE_GUID(GUID_DefaultGMCollection, 0xf17e8673, 0xc3b4, 0x11d1, 0x87, 0xb, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* GUID to define default synth, placed in AudioPath configuration file. */
DEFINE_GUID(GUID_Synth_Default,0x26bb9432, 0x45fe, 0x48d3, 0xa3, 0x75, 0x24, 0x72, 0xc5, 0xe3, 0xe7, 0x86);

/* GUIDs to define default buffer configurations to place in AudioPath configuration file. */
DEFINE_GUID(GUID_Buffer_Reverb,0x186cc541, 0xdb29, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);
DEFINE_GUID(GUID_Buffer_EnvReverb,0x186cc542, 0xdb29, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);
DEFINE_GUID(GUID_Buffer_Stereo,0x186cc545, 0xdb29, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);
DEFINE_GUID(GUID_Buffer_3D_Dry,0x186cc546, 0xdb29, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);
DEFINE_GUID(GUID_Buffer_Mono,0x186cc547, 0xdb29, 0x11d3, 0x9b, 0xd1, 0x0, 0x80, 0xc7, 0x15, 0xa, 0x74);

/* IID's */
DEFINE_GUID(IID_IDirectMusicLoader, 0x2ffaaca2, 0x5dca, 0x11d2, 0xaf, 0xa6, 0x0, 0xaa, 0x0, 0x24, 0xd8, 0xb6);
DEFINE_GUID(IID_IDirectMusicGetLoader,0x68a04844, 0xd13d, 0x11d1, 0xaf, 0xa6, 0x0, 0xaa, 0x0, 0x24, 0xd8, 0xb6);
DEFINE_GUID(IID_IDirectMusicObject,0xd2ac28b5, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicSegment, 0xf96029a2, 0x4282, 0x11d2, 0x87, 0x17, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicSegmentState, 0xa3afdcc7, 0xd3ee, 0x11d1, 0xbc, 0x8d, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(IID_IDirectMusicPerformance,0x7d43d03, 0x6523, 0x11d2, 0x87, 0x1d, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicGraph,0x2befc277, 0x5497, 0x11d2, 0xbc, 0xcb, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xeb);
DEFINE_GUID(IID_IDirectMusicStyle,0xd2ac28bd, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicChordMap,0xd2ac28be, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicComposer,0xd2ac28bf, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);
DEFINE_GUID(IID_IDirectMusicBand,0xd2ac28c0, 0xb39b, 0x11d1, 0x87, 0x4, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Alternate interface IDs, available in DX7 release and after. */
DEFINE_GUID(IID_IDirectMusicPerformance2,0x6fc2cae0, 0xbc78, 0x11d2, 0xaf, 0xa6, 0x0, 0xaa, 0x0, 0x24, 0xd8, 0xb6);
DEFINE_GUID(IID_IDirectMusicSegment2, 0xd38894d1, 0xc052, 0x11d2, 0x87, 0x2f, 0x0, 0x60, 0x8, 0x93, 0xb1, 0xbd);

/* Interface IDs for DX8 */
/* changed interfaces (GUID only) */
DEFINE_GUID(IID_IDirectMusicLoader8, 0x19e7c08c, 0xa44, 0x4e6a, 0xa1, 0x16, 0x59, 0x5a, 0x7c, 0xd5, 0xde, 0x8c);
DEFINE_GUID(IID_IDirectMusicPerformance8, 0x679c4137, 0xc62e, 0x4147, 0xb2, 0xb4, 0x9d, 0x56, 0x9a, 0xcb, 0x25, 0x4c);
DEFINE_GUID(IID_IDirectMusicSegment8,0xc6784488, 0x41a3, 0x418f, 0xaa, 0x15, 0xb3, 0x50, 0x93, 0xba, 0x42, 0xd4);
DEFINE_GUID(IID_IDirectMusicSegmentState8, 0xa50e4730, 0xae4, 0x48a7, 0x98, 0x39, 0xbc, 0x4, 0xbf, 0xe0, 0x77, 0x72);
DEFINE_GUID(IID_IDirectMusicStyle8, 0xfd24ad8a, 0xa260, 0x453d, 0xbf, 0x50, 0x6f, 0x93, 0x84, 0xf7, 0x9, 0x85);
/* new interfaces (GUID + alias) */
DEFINE_GUID(IID_IDirectMusicPatternTrack, 0x51c22e10, 0xb49f, 0x46fc, 0xbe, 0xc2, 0xe6, 0x28, 0x8f, 0xb9, 0xed, 0xe6);
#define IID_IDirectMusicPatternTrack8 IID_IDirectMusicPatternTrack
DEFINE_GUID(IID_IDirectMusicScript, 0x2252373a, 0x5814, 0x489b, 0x82, 0x9, 0x31, 0xfe, 0xde, 0xba, 0xf1, 0x37); /* {2252373A-5814-489b-8209-31FEDEBAF137} */
#define IID_IDirectMusicScript8 IID_IDirectMusicScript
DEFINE_GUID(IID_IDirectMusicContainer, 0x9301e386, 0x1f22, 0x11d3, 0x82, 0x26, 0xd2, 0xfa, 0x76, 0x25, 0x5d, 0x47);
#define IID_IDirectMusicContainer8 IID_IDirectMusicContainer
DEFINE_GUID(IID_IDirectMusicAudioPath,0xc87631f5, 0x23be, 0x4986, 0x88, 0x36, 0x5, 0x83, 0x2f, 0xcc, 0x48, 0xf9);
#define IID_IDirectMusicAudioPath8 IID_IDirectMusicAudioPath
/* unchanged interfaces (alias only) */
#define IID_IDirectMusicGetLoader8 IID_IDirectMusicGetLoader
#define IID_IDirectMusicChordMap8 IID_IDirectMusicChordMap
#define IID_IDirectMusicGraph8 IID_IDirectMusicGraph
#define IID_IDirectMusicBand8 IID_IDirectMusicBand
#define IID_IDirectMusicObject8 IID_IDirectMusicObject
#define IID_IDirectMusicComposer8 IID_IDirectMusicComposer


#ifdef __cplusplus
}; /* extern "C" */
#endif

#include <poppack.h>

#endif /* #ifndef _DMUSICI_ */
