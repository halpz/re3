/************************************************************************
*                                                                       *
*   dmusicf.h -- This module defines the DirectMusic file formats       *
*                                                                       *
*   Copyright (c) Microsoft Corporation.  All rights reserved.          *
*                                                                       *
************************************************************************/

#ifndef _DMUSICF_
#define _DMUSICF_


#include <windows.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#include <mmsystem.h>

#include <pshpack8.h>

#ifdef __cplusplus
extern "C" {
#endif

interface IDirectMusicCollection;
#ifndef __cplusplus 
typedef interface IDirectMusicCollection IDirectMusicCollection;
#endif

/* Common chunks */

#define DMUS_FOURCC_GUID_CHUNK        mmioFOURCC('g','u','i','d')
#define DMUS_FOURCC_INFO_LIST         mmioFOURCC('I','N','F','O')
#define DMUS_FOURCC_UNFO_LIST         mmioFOURCC('U','N','F','O')
#define DMUS_FOURCC_UNAM_CHUNK        mmioFOURCC('U','N','A','M')
#define DMUS_FOURCC_UART_CHUNK        mmioFOURCC('U','A','R','T')
#define DMUS_FOURCC_UCOP_CHUNK        mmioFOURCC('U','C','O','P')
#define DMUS_FOURCC_USBJ_CHUNK        mmioFOURCC('U','S','B','J')
#define DMUS_FOURCC_UCMT_CHUNK        mmioFOURCC('U','C','M','T')
#define DMUS_FOURCC_CATEGORY_CHUNK    mmioFOURCC('c','a','t','g')
#define DMUS_FOURCC_VERSION_CHUNK     mmioFOURCC('v','e','r','s')

/* The following structures are used by the Tracks, and are the packed structures */
/* that are passed to the Tracks inside the IStream. */


typedef struct _DMUS_IO_SEQ_ITEM
{
    MUSIC_TIME    mtTime;
    MUSIC_TIME    mtDuration;
    DWORD         dwPChannel;
    short         nOffset; 
    BYTE          bStatus;
    BYTE          bByte1;
    BYTE          bByte2;
} DMUS_IO_SEQ_ITEM;


typedef struct _DMUS_IO_CURVE_ITEM
{
    MUSIC_TIME  mtStart;
    MUSIC_TIME  mtDuration;
    MUSIC_TIME  mtResetDuration;
    DWORD       dwPChannel;
    short       nOffset;
    short       nStartValue;
    short       nEndValue;
    short       nResetValue;
    BYTE        bType;
    BYTE        bCurveShape;
    BYTE        bCCData;
    BYTE        bFlags;
    /* Following was added for DX8. */
    WORD        wParamType;      /* RPN or NRPN parameter number. */
    WORD        wMergeIndex;     /* Allows multiple parameters to be merged (pitchbend, volume, and expression.) */
} DMUS_IO_CURVE_ITEM;


typedef struct _DMUS_IO_TEMPO_ITEM
{
    MUSIC_TIME    lTime;
    double        dblTempo;
} DMUS_IO_TEMPO_ITEM;


typedef struct _DMUS_IO_SYSEX_ITEM
{
    MUSIC_TIME    mtTime;
    DWORD         dwPChannel;
    DWORD         dwSysExLength;
} DMUS_IO_SYSEX_ITEM;

typedef DMUS_CHORD_KEY DMUS_CHORD_PARAM; /* DMUS_CHORD_KEY defined in dmusici.h */

typedef struct _DMUS_RHYTHM_PARAM
{
    DMUS_TIMESIGNATURE  TimeSig;
    DWORD               dwRhythmPattern;
} DMUS_RHYTHM_PARAM;

typedef struct _DMUS_TEMPO_PARAM
{
    MUSIC_TIME  mtTime;
    double      dblTempo;
} DMUS_TEMPO_PARAM;


typedef struct _DMUS_MUTE_PARAM
{
    DWORD   dwPChannel;
    DWORD   dwPChannelMap;
    BOOL    fMute;
} DMUS_MUTE_PARAM;

/* Style chunks */

#define DMUS_FOURCC_STYLE_FORM            mmioFOURCC('D','M','S','T')
#define DMUS_FOURCC_STYLE_CHUNK           mmioFOURCC('s','t','y','h')
#define DMUS_FOURCC_PART_LIST             mmioFOURCC('p','a','r','t')
#define DMUS_FOURCC_PART_CHUNK            mmioFOURCC('p','r','t','h')
#define DMUS_FOURCC_NOTE_CHUNK            mmioFOURCC('n','o','t','e')
#define DMUS_FOURCC_CURVE_CHUNK           mmioFOURCC('c','r','v','e')
#define DMUS_FOURCC_MARKER_CHUNK          mmioFOURCC('m','r','k','r')
#define DMUS_FOURCC_RESOLUTION_CHUNK      mmioFOURCC('r','s','l','n')
#define DMUS_FOURCC_ANTICIPATION_CHUNK    mmioFOURCC('a','n','p','n')
#define DMUS_FOURCC_PATTERN_LIST          mmioFOURCC('p','t','t','n')
#define DMUS_FOURCC_PATTERN_CHUNK         mmioFOURCC('p','t','n','h')
#define DMUS_FOURCC_RHYTHM_CHUNK          mmioFOURCC('r','h','t','m')
#define DMUS_FOURCC_PARTREF_LIST          mmioFOURCC('p','r','e','f')
#define DMUS_FOURCC_PARTREF_CHUNK         mmioFOURCC('p','r','f','c')
#define DMUS_FOURCC_STYLE_PERS_REF_LIST   mmioFOURCC('p','r','r','f')
#define DMUS_FOURCC_MOTIFSETTINGS_CHUNK   mmioFOURCC('m','t','f','s')

/* Flags used by variations: these make up the DWORDs in dwVariationChoices.               */

/* These flags determine the types of chords supported by a given variation in DirectMusic */
/* mode.  The first seven flags (bits 1-7) are set if the variation supports major chords  */
/* rooted in scale positions, so, e.g., if bits 1, 2, and 4 are set, the variation         */
/* supports major chords rooted in the tonic, second, and fourth scale positions.  The     */
/* next seven flags serve the same purpose, but for minor chords, and the following seven  */
/* flags serve the same purpose for chords that are not major or minor (e.g., SUS 4        */
/* chords).  Bits 22, 23, and 24 are set if the variation supports chords rooted in the    */
/* scale, chords rooted sharp of scale tones, and chords rooted flat of scale tones,       */
/* respectively.  For example, to support a C# minor chord in the scale of C Major,        */
/* bits 8 (for tonic minor) and 24 (for sharp) need to be set.  Bits 25, 26, an 27 handle  */
/* chords that are triads, 6th or 7th chords, and chords with extensions, respectively.    */
/* bits 28 and 29 handle chords that are followed by tonic and dominant chords,            */
/* respectively.                                                                           */
#define DMUS_VARIATIONF_MAJOR        0x0000007F /* Seven positions in the scale - major chords. */    
#define DMUS_VARIATIONF_MINOR        0x00003F80 /* Seven positions in the scale - minor chords. */    
#define DMUS_VARIATIONF_OTHER        0x001FC000 /* Seven positions in the scale - other chords. */    
#define DMUS_VARIATIONF_ROOT_SCALE   0x00200000 /* Handles chord roots in the scale. */         
#define DMUS_VARIATIONF_ROOT_FLAT    0x00400000 /* Handles flat chord roots (based on scale notes). */         
#define DMUS_VARIATIONF_ROOT_SHARP   0x00800000 /* Handles sharp chord roots (based on scale notes). */         
#define DMUS_VARIATIONF_TYPE_TRIAD   0x01000000 /* Handles simple chords - triads. */  
#define DMUS_VARIATIONF_TYPE_6AND7   0x02000000 /* Handles simple chords - 6 and 7. */  
#define DMUS_VARIATIONF_TYPE_COMPLEX 0x04000000 /* Handles complex chords. */  
#define DMUS_VARIATIONF_DEST_TO1     0x08000000 /* Handles transitions to 1 chord. */  
#define DMUS_VARIATIONF_DEST_TO5     0x10000000 /* Handles transitions to 5 chord. */  
#define DMUS_VARIATIONF_DEST_OTHER   0x40000000 /* Handles transitions to chords other than 1 . */  

/* legacy mask for variation modes */
#define DMUS_VARIATIONF_MODES        0xE0000000
/* Bits 29 and 31 of the variation flags are the Mode bits.  If both are 0, it's IMA. */  
/* If bit 29 is 1, it's Direct Music. */
#define DMUS_VARIATIONF_MODES_EX     (0x20000000 | 0x80000000)
#define DMUS_VARIATIONF_IMA25_MODE   0x00000000
#define DMUS_VARIATIONF_DMUS_MODE    0x20000000

/* Set this if the part uses marker events */
#define DMUS_PARTF_USE_MARKERS       0x1
/* Set this if the part is allowed to switch only on chord-aligned markers */
#define DMUS_PARTF_ALIGN_CHORDS      0x2

/* These specify if the marker event signals whether to stop a variation or start a 
pattern/variation (or both), and whether new variations must align with a chord */
#define DMUS_MARKERF_START            0x1
#define DMUS_MARKERF_STOP             0x2
#define DMUS_MARKERF_CHORD_ALIGN      0x4

/* if this flag is set, variation settings in a playing pattern-based track's state data will 
persist in the track after it stops playing */
#define DMUS_PATTERNF_PERSIST_CONTROL 0x1

/* These specify possible values for DMUS_IO_PARTREF.bRandomVariation
   all but DMUS_VARIATIONT_SEQUENTIAL and DMUS_VARIATIONT_RANDOM are dx8. */
typedef enum enumDMUS_VARIATIONT_TYPES
{
    DMUS_VARIATIONT_SEQUENTIAL       = 0, /* Play sequential starting with variation 1. */
    DMUS_VARIATIONT_RANDOM           = 1, /* Play randomly. */
    DMUS_VARIATIONT_RANDOM_START     = 2, /* Play sequential starting with a random variation. */
    DMUS_VARIATIONT_NO_REPEAT        = 3, /* Play randomly, but don't play the same variation twice. */
    DMUS_VARIATIONT_RANDOM_ROW       = 4  /* Play randomly as a row: don't repeat any variation until all have played. */
} DMUS_VARIATIONT_TYPES;

/* These specify possible values for DMUS_IO_PATTERN.wEmbellishment (dx8) */
typedef enum enumDMUS_EMBELLISHT_TYPES
{
    DMUS_EMBELLISHT_NORMAL          = 0,
    DMUS_EMBELLISHT_FILL            = 1,
    DMUS_EMBELLISHT_BREAK           = 2,
    DMUS_EMBELLISHT_INTRO           = 4,
    DMUS_EMBELLISHT_END             = 8,
    DMUS_EMBELLISHT_MOTIF           = 16,
    DMUS_EMBELLISHT_ALL             = 0xFFFF
} DMUS_EMBELLISHT_TYPES;

#pragma pack(2)

typedef struct _DMUS_IO_TIMESIG
{
    /* Time signatures define how many beats per measure, which note receives */
    /* the beat, and the grid resolution. */
    BYTE    bBeatsPerMeasure;   /* beats per measure (top of time sig) */
    BYTE    bBeat;              /* what note receives the beat (bottom of time sig.) */
                                /* we can assume that 0 means 256th note */
    WORD    wGridsPerBeat;      /* grids per beat */
} DMUS_IO_TIMESIG;

typedef struct _DMUS_IO_STYLE
{
    DMUS_IO_TIMESIG     timeSig;        /* Styles have a default Time Signature */
    double              dblTempo;   
} DMUS_IO_STYLE;

typedef struct _DMUS_IO_VERSION
{
    DWORD               dwVersionMS;        /* Version # high-order 32 bits */
    DWORD               dwVersionLS;        /* Version # low-order 32 bits  */
} DMUS_IO_VERSION;

typedef struct _DMUS_IO_PATTERN
{
    DMUS_IO_TIMESIG     timeSig;           /* Patterns can override the Style's Time sig. */
    BYTE                bGrooveBottom;     /* bottom of groove range */
    BYTE                bGrooveTop;        /* top of groove range */
    WORD                wEmbellishment;    /* Fill, Break, Intro, End, Normal, Motif */
    WORD                wNbrMeasures;      /* length in measures */
    BYTE                bDestGrooveBottom; /* bottom of groove range for next pattern */
    BYTE                bDestGrooveTop;    /* top of groove range for next pattern */
    DWORD               dwFlags;           /* various flags */
} DMUS_IO_PATTERN;

typedef struct _DMUS_IO_STYLEPART
{
    DMUS_IO_TIMESIG     timeSig;        /* can override pattern's */
    DWORD               dwVariationChoices[32]; /* MOAW choice bitfield */
    GUID                guidPartID;     /* identifies the part */
    WORD                wNbrMeasures;   /* length of the Part */
    BYTE                bPlayModeFlags; /* see PLAYMODE flags */
    BYTE                bInvertUpper;   /* inversion upper limit */
    BYTE                bInvertLower;   /* inversion lower limit */
    BYTE                bPad[3];        /* for DWORD alignment */
    DWORD               dwFlags;        /* various flags */ 
} DMUS_IO_STYLEPART;

typedef struct _DMUS_IO_PARTREF
{
    GUID    guidPartID;         /* unique ID for matching up with parts */
    WORD    wLogicalPartID;     /* corresponds to port/device/midi channel OBSOLETE */
    BYTE    bVariationLockID;   /* parts with the same ID lock variations. */
                                /* high bit is used to identify master Part */
    BYTE    bSubChordLevel;     /* tells which sub chord level this part wants */
    BYTE    bPriority;          /* 256 priority levels. Parts with lower priority */
                                /* aren't played first when a device runs out of */
                                /* notes */
    BYTE    bRandomVariation;   /* when set, matching variations play in random order */
                                /* when clear, matching variations play sequentially */
    WORD    wPad;               /* not used */
    DWORD   dwPChannel;         /* replaces wLogicalPartID */
} DMUS_IO_PARTREF;

typedef struct _DMUS_IO_STYLENOTE
{
    MUSIC_TIME  mtGridStart;    /* when this note occurs */
    DWORD       dwVariation;    /* variation bits */
    MUSIC_TIME  mtDuration;     /* how long this note lasts */
    short       nTimeOffset;    /* offset from mtGridStart */
    WORD        wMusicValue;    /* Position in scale. */
    BYTE        bVelocity;      /* Note velocity. */
    BYTE        bTimeRange;     /* Range to randomize start time. */
    BYTE        bDurRange;      /* Range to randomize duration. */
    BYTE        bVelRange;      /* Range to randomize velocity. */
    BYTE        bInversionID;   /* Identifies inversion group to which this note belongs */
    BYTE        bPlayModeFlags; /* Can override part */
    /* Following exists only under DX8 and on */
    BYTE        bNoteFlags;     /* values from DMUS_NOTEF_FLAGS */
} DMUS_IO_STYLENOTE;

typedef struct _DMUS_IO_STYLECURVE
{
    MUSIC_TIME  mtGridStart;    /* when this curve occurs */
    DWORD       dwVariation;    /* variation bits */
    MUSIC_TIME  mtDuration;     /* how long this curve lasts */
    MUSIC_TIME  mtResetDuration;/* how long after the end of the curve to reset the curve */
    short       nTimeOffset;    /* offset from mtGridStart */
    short       nStartValue;    /* curve's start value */
    short       nEndValue;      /* curve's end value */
    short       nResetValue;    /* the value to which to reset the curve */
    BYTE        bEventType;     /* type of curve */
    BYTE        bCurveShape;    /* shape of curve */
    BYTE        bCCData;        /* CC# */
    BYTE        bFlags;         /* Bit 1=TRUE means to send nResetValue. Otherwise, don't.
                                   Other bits are reserved. */
    /*  Following was added for DX8. */
    WORD        wParamType;      /* RPN or NRPN parameter number. */
    WORD        wMergeIndex;     /* Allows multiple parameters to be merged (pitchbend, volume, and expression.) */
} DMUS_IO_STYLECURVE;

typedef struct _DMUS_IO_STYLEMARKER
{
    MUSIC_TIME  mtGridStart;    /* when this marker occurs */
    DWORD       dwVariation;    /* variation bits */
    WORD        wMarkerFlags;   /* how the marker is used */
} DMUS_IO_STYLEMARKER;

typedef struct _DMUS_IO_STYLERESOLUTION
{
    DWORD    dwVariation;       /* variation bits */
    WORD     wMusicValue;       /* Position in scale. */
    BYTE     bInversionID;      /* Identifies inversion group to which this note belongs */
    BYTE     bPlayModeFlags;    /* Can override part */
} DMUS_IO_STYLERESOLUTION;

typedef struct _DMUS_IO_STYLE_ANTICIPATION
{
    MUSIC_TIME    mtGridStart;   /* when this anticipation occurs */
    DWORD         dwVariation;   /* variation bits */
    short         nTimeOffset;   /* offset from mtGridStart */
    BYTE          bTimeRange;    /* Range to randomize start time. */
} DMUS_IO_STYLE_ANTICIPATION;

typedef struct _DMUS_IO_MOTIFSETTINGS
{
    DWORD       dwRepeats;      /* Number of repeats. By default, 0. */
    MUSIC_TIME  mtPlayStart;    /* Start of playback. By default, 0. */
    MUSIC_TIME  mtLoopStart;    /* Start of looping portion. By default, 0. */
    MUSIC_TIME  mtLoopEnd;      /* End of loop. Must be greater than mtLoopStart. Or, 0, indicating loop full motif.  */
    DWORD       dwResolution;   /* Default resolution. */
} DMUS_IO_MOTIFSETTINGS;

#pragma pack()


/*
RIFF
(
    'DMST'          // Style
    <styh-ck>       // Style header chunk
    <guid-ck>       // Every Style has a GUID
    [<UNFO-list>]   // Name, author, copyright info., comments
    [<vers-ck>]     // version chunk
    <part-list>...  // Array of parts in the Style, used by patterns
    <pttn-list>...  // Array of patterns in the Style
    <DMBD-form>...  // Array of bands in the Style
    [<prrf-list>]...// Optional array of chord map references in the Style
)

    // <styh-ck>
    styh
    (
        <DMUS_IO_STYLE>
    )

    // <guid-ck>
    guid
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <part-list>
    LIST
    (
        'part'
        <prth-ck>       // Part header chunk
        [<UNFO-list>]   // Name, author, copyright info., comments
        [<note-ck>]     // Optional chunk containing an array of notes in Part
        [<crve-ck>]     // Optional chunk containing an array of curves in Part
        [<mrkr-ck>]     // Optional chunk containing an array of markers in Part
        [<rsln-ck>]     // Optional chunk containing an array of variation resolutions in Part
        [<anpn-ck>]     // Optional chunk containing an array of resolution anticipations in Part
    )

        // <orth-ck>
        prth
        (
            <DMUS_IO_STYLEPART>
        )

        // <note-ck>
        'note'
        (
            // sizeof DMUS_IO_STYLENOTE:DWORD
            <DMUS_IO_STYLENOTE>...
        )

        // <crve-ck>
        'crve'
        (
            // sizeof DMUS_IO_STYLECURVE:DWORD
            <DMUS_IO_STYLECURVE>...
        )

        // <mrkr-ck>
        'mrkr'
        (
            // sizeof DMUS_IO_STYLEMARKER:DWORD
            <DMUS_IO_STYLEMARKER>...
        )

        // <rsln-ck>
        'rsln'
        (
            // sizeof DMUS_IO_STYLERESOLUTION:DWORD
            <DMUS_IO_STYLERESOLUTION>...
        )

        // <anpn-ck>
        'anpn'
        (
            // sizeof DMUS_IO_STYLE_ANTICIPATION:DWORD
            <DMUS_IO_STYLE_ANTICIPATION>...
        )

    // <pttn-list>
    LIST
    (
        'pttn'
        <ptnh-ck>       // Pattern header chunk
        <rhtm-ck>       // Chunk containing an array of rhythms for chord matching
        [<UNFO-list>]   // Name, author, copyright info., comments
        [<mtfs-ck>]     // Motif settings chunk
        [<DMBD-form>]   // Optional band to be associated with the pattern (for motifs)
        <pref-list>...  // Array of part reference id's
    )

        // <ptnh-ck>
        ptnh
        (
            <DMUS_IO_PATTERN>
        )

        // <rhtm-ck>
        'rhtm'
        (
            // DWORD's representing rhythms for chord matching based on number
            // of measures in the pattern
        )


        // pref-list
        LIST
        (
            'pref'
            <prfc-ck>   // part ref chunk
        )

        // <prfc-ck>
        prfc
        (
            <DMUS_IO_PARTREF>
        )

        // <mtfs-ck>
        mtfs
        (
            <DMUS_IO_MOTIFSETTINGS>
        )

    // <prrf-list>
    LIST
    (
        'prrf'
        <DMRF-list>... // Array of Chordmap references
    )
*/

/* Pattern chunk, for use in Pattern tracks */

#define DMUS_FOURCC_PATTERN_FORM        mmioFOURCC('D','M','P','T')

/*
RIFF
(
    'DMPT'          // Pattern
    <styh-ck>       // Style header chunk
    <pttn-list>     // The pattern, in single pattern format (includes DMUS_FOURCC_PART_LIST chunks)
)
*/


/* Chord and command file formats */

/* These specify possible values for DMUS_IO_COMMAND.bRepeatMode (dx8) */
typedef enum enumDMUS_PATTERNT_TYPES
{
    DMUS_PATTERNT_RANDOM           = 0, /* Play randomly. (dx7 behavior) */
    DMUS_PATTERNT_REPEAT           = 1, /* Repeat last pattern. */
    DMUS_PATTERNT_SEQUENTIAL       = 2, /* Play sequential starting with first matching pattern. */
    DMUS_PATTERNT_RANDOM_START     = 3, /* Play sequential starting with a random pattern. */
    DMUS_PATTERNT_NO_REPEAT        = 4, /* Play randomly, but don't play the same pattern twice. */
    DMUS_PATTERNT_RANDOM_ROW       = 5  /* Play randomly as a row: don't repeat any pattern until all have played. */
} DMUS_PATTERNT_TYPES;


#define DMUS_FOURCC_CHORDTRACK_LIST         mmioFOURCC('c','o','r','d')
#define DMUS_FOURCC_CHORDTRACKHEADER_CHUNK  mmioFOURCC('c','r','d','h')
#define DMUS_FOURCC_CHORDTRACKBODY_CHUNK    mmioFOURCC('c','r','d','b')

#define DMUS_FOURCC_COMMANDTRACK_CHUNK      mmioFOURCC('c','m','n','d')

typedef struct _DMUS_IO_CHORD
{
    WCHAR       wszName[16];    /* Name of the chord */
    MUSIC_TIME  mtTime;         /* Time of this chord */
    WORD        wMeasure;       /* Measure this falls on */
    BYTE        bBeat;          /* Beat this falls on */
    BYTE        bFlags;         /* Various flags */
} DMUS_IO_CHORD;

typedef struct _DMUS_IO_SUBCHORD
{
    DWORD   dwChordPattern;     /* Notes in the subchord */
    DWORD   dwScalePattern;     /* Notes in the scale */
    DWORD   dwInversionPoints;  /* Where inversions can occur */
    DWORD   dwLevels;           /* Which levels are supported by this subchord */
    BYTE    bChordRoot;         /* Root of the subchord */
    BYTE    bScaleRoot;         /* Root of the scale */
} DMUS_IO_SUBCHORD;

typedef struct _DMUS_IO_COMMAND
{
    MUSIC_TIME  mtTime;         /* Time of this command */
    WORD        wMeasure;       /* Measure this falls on */
    BYTE        bBeat;          /* Beat this falls on */
    BYTE        bCommand;       /* Command type (see #defines below) */
    BYTE        bGrooveLevel;   /* Groove level (0 if command is not a groove) */
    BYTE        bGrooveRange;   /* Groove range  */
    BYTE        bRepeatMode;    /* Used to control selection of patterns with same groove level  */
} DMUS_IO_COMMAND;


/*

    // <cord-list>
    LIST
    (
        'cord'
        <crdh-ck>
        <crdb-ck>...    // Chord body chunks
    )

        // <crdh-ck>
        crdh
        (
            // Scale: dword (upper 8 bits for root, lower 24 for scale)
        )

        // <crdb-ck>
        crdb
        (
            // sizeof DMUS_IO_CHORD:dword
            <DMUS_IO_CHORD>
            // # of DMUS_IO_SUBCHORDS:dword
            // sizeof DMUS_IO_SUBCHORDS:dword
            // a number of <DMUS_IO_SUBCHORD>
        )


    // <cmnd-list>
    'cmnd'
    (
        //sizeof DMUS_IO_COMMAND: DWORD
        <DMUS_IO_COMMAND>...
    )

*/

/*  File io for DirectMusic Tool and ToolGraph objects
*/

/* RIFF ids: */

#define DMUS_FOURCC_TOOLGRAPH_FORM  mmioFOURCC('D','M','T','G')
#define DMUS_FOURCC_TOOL_LIST       mmioFOURCC('t','o','l','l')
#define DMUS_FOURCC_TOOL_FORM       mmioFOURCC('D','M','T','L')
#define DMUS_FOURCC_TOOL_CHUNK      mmioFOURCC('t','o','l','h')

/* io structures: */

typedef struct _DMUS_IO_TOOL_HEADER
{
    GUID        guidClassID;    /* Class id of tool. */
    long        lIndex;         /* Position in graph. */
    DWORD       cPChannels;     /* Number of items in channels array. */
    FOURCC      ckid;           /* chunk ID of tool's data chunk if 0 fccType valid. */
    FOURCC      fccType;        /* list type if NULL ckid valid. */
    DWORD       dwPChannels[1]; /* Array of PChannels, size determined by cPChannels. */
} DMUS_IO_TOOL_HEADER;

/*
RIFF
(
    'DMTG'          // DirectMusic ToolGraph chunk
    [<guid-ck>]     // GUID for ToolGraph
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    <toll-list>     // List of Tools
)

    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <toll-list>
    LIST
    (
        'toll'          // Array of tools
        <DMTL-form>...  // Each tool is encapsulated in a RIFF chunk
    )

// <DMTL-form>      Tools are embedded in a graph. Theoretically, they can be saved as individual files too.
RIFF
(
    'DMTL'
    <tolh-ck>
    [<data>]        // Tool data. Must be a RIFF readable chunk.
)

    // <tolh-ck>            // Tool header chunk
    (
        'tolh'
        <DMUS_IO_TOOL_HEADER>   // Tool header
    )
*/

/*  The AudioPath file carries everything for describing a specific audio path,
    including Tool Graph and Buffer Descriptor.
    This can even be used for configuring a complete performance.
*/

#define DMUS_FOURCC_AUDIOPATH_FORM  mmioFOURCC('D','M','A','P')

/*
RIFF
(
    'DMAP'          // DirectMusic AudioPath chunk
    [<guid-ck>]     // GUID for this Audio Path configuration
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    [<DMTG-form>]   // Optional ToolGraph
    [<pcsl-list>]   // Optional list of port configurations
    [<dbfl-list>]...// Optional array of Dsound buffer descriptors
)
*/

#define DMUS_FOURCC_PORTCONFIGS_LIST    mmioFOURCC('p','c','s','l')
#define DMUS_FOURCC_PORTCONFIG_LIST     mmioFOURCC('p','c','f','l')
#define DMUS_FOURCC_PORTCONFIG_ITEM     mmioFOURCC('p','c','f','h')
#define DMUS_FOURCC_PORTPARAMS_ITEM     mmioFOURCC('p','p','r','h')
#define DMUS_FOURCC_DSBUFFER_LIST       mmioFOURCC('d','b','f','l')
#define DMUS_FOURCC_DSBUFFATTR_ITEM     mmioFOURCC('d','d','a','h')
#define DMUS_FOURCC_PCHANNELS_LIST      mmioFOURCC('p','c','h','l')
#define DMUS_FOURCC_PCHANNELS_ITEM      mmioFOURCC('p','c','h','h')

typedef struct _DMUS_IO_PORTCONFIG_HEADER
{
    GUID    guidPort;           /* GUID of requested port. */
    DWORD   dwPChannelBase;     /* PChannel that this should start on. */
    DWORD   dwPChannelCount;    /* How many channels. */
    DWORD   dwFlags;            /* Various flags. */
} DMUS_IO_PORTCONFIG_HEADER;

#define DMUS_PORTCONFIGF_DRUMSON10  1   /* This port configured for drums on channel 10. */
#define DMUS_PORTCONFIGF_USEDEFAULT 2   /* Use the default port. */

/* Each portconfig has one or more pchannel to buffer mappings. Each buffer
   is identified by a guid. Each pchannel can map to one or more buffers.
   This is defined with one or more DMUS_IO_PCHANNELTOBUFFER_HEADER
   structures. Each defines a range of PChannels and the set of buffers
   that they connect to. 
*/

typedef struct _DMUS_IO_PCHANNELTOBUFFER_HEADER
{
    DWORD   dwPChannelBase;     /* PChannel that this should start on. */
    DWORD   dwPChannelCount;    /* How many PChannels. */
    DWORD   dwBufferCount;      /* How many buffers do these connect to. */
    DWORD   dwFlags;            /* Various flags. Currently reserved for future use. Must be 0. */
} DMUS_IO_PCHANNELTOBUFFER_HEADER;

/* Each buffer is represented by an DSBC form. This is wrapped by the 
   DMUS_IO_BUFFER_ATTRIBUTES_HEADER which identifies how to use the
   buffer. In particular, it indicates whether this gets dynamically duplicated
   or all references to this should share the same instance. 
   To resolve references, the unique GUID of the buffer is also stored
   in this structure. 
*/
   
typedef struct _DMUS_IO_BUFFER_ATTRIBUTES_HEADER
{
    GUID    guidBufferID;       /* Each buffer config has a unique ID. */
    DWORD   dwFlags;            /* Various flags. */
} DMUS_IO_BUFFER_ATTRIBUTES_HEADER;

/* DMUS_IO_BUFFER_ATTRIBUTES_HEADER.dwFlags: */
#define DMUS_BUFFERF_SHARED     1   /* Share this with other audio paths, instead of creating unique copies. */
#define DMUS_BUFFERF_DEFINED    2   /* Use one of the standard predefined buffers (see GUID_Buffer... in dmusici.h.) */
#define DMUS_BUFFERF_MIXIN      8   /* This is a mixin buffer. */

/*

LIST
(
    'pcsl'          // Array of port configurations
    <pcfl-list>...  // One or more port configurations, each in a list chunk
)

LIST
(
    'pcfl'          // List container for one port configuration.
    <pcfh-ck>       // Portconfig header chunk.
    <pprh-ck>       // Port params, to be used to create the port.
    [<dbfl-list>]...// Optional array of Dsound buffer descriptors
    [<pchl-list>]   // Optional list of pchannel to buffer assignments

)

    // <pcfh-ck>            // Port config header chunk
    (
        'pcfh'
        <DMUS_IO_PORTCONFIG_HEADER>   // Port config header
    )

    // <pprh-ck>            // Port params header chunk
    (
        'pprh'
        <DMUS_PORTPARAMS8>   // Port params header
    )

LIST
(
    'pchl'          // List container for one or more pchannel to buffer assignments.
    <pchh-ck>...    // One or more pchannel to buffer assignment headers and data.

    // <pchh-ck>
    (
        'pchh'
        <DMUS_IO_PCHANNELTOBUFFER_HEADER>   // Description of PChannels
        <GUID>...                           // Array of GUIDs defining the buffers they all connect to.
    )
)

LIST
(
    'dbfl'          // List container for one buffer and buffer attributes header.
    <ddah-ck>       // Buffer attributes header. 
    [<DSBC-form>]   // Buffer configuration. Not required when header uses a predefined buffer type.

    // <ddah-ck>
    (
        'ddah'
        <DMUS_IO_BUFFER_ATTRIBUTES_HEADER>   // Buffer attributes.
    )
)
*/

/*  File io for DirectMusic Band Track object */


/* RIFF ids: */
#define DMUS_FOURCC_BANDTRACK_FORM  mmioFOURCC('D','M','B','T')
#define DMUS_FOURCC_BANDTRACK_CHUNK mmioFOURCC('b','d','t','h')
#define DMUS_FOURCC_BANDS_LIST      mmioFOURCC('l','b','d','l')
#define DMUS_FOURCC_BAND_LIST       mmioFOURCC('l','b','n','d')
#define DMUS_FOURCC_BANDITEM_CHUNK  mmioFOURCC('b','d','i','h')
#define DMUS_FOURCC_BANDITEM_CHUNK2 mmioFOURCC('b','d','2','h')

/* io structures */
typedef struct _DMUS_IO_BAND_TRACK_HEADER
{
    BOOL bAutoDownload;     /* Determines if Auto-Download is enabled. */
} DMUS_IO_BAND_TRACK_HEADER;

typedef struct _DMUS_IO_BAND_ITEM_HEADER
{
    MUSIC_TIME lBandTime;   /* Position in track list. */
} DMUS_IO_BAND_ITEM_HEADER;

typedef struct _DMUS_IO_BAND_ITEM_HEADER2
{
    MUSIC_TIME lBandTimeLogical;   /* Position in track list. Time in the music with which band change is associated. */
    MUSIC_TIME lBandTimePhysical;  /* Precise time band change will take effect. Should be close to logical time. */
} DMUS_IO_BAND_ITEM_HEADER2;

/*
RIFF
(
    'DMBT'          // DirectMusic Band Track form-type
    [<bdth-ck>]     // Band track header
    [<guid-ck>]     // GUID for band track
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    <lbdl-list>     // List of Band items
)

    // <bnth-ck>
    'bdth'
    (
        <DMUS_IO_BAND_TRACK_HEADER>
    )

    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <lbdl-list>
    LIST
    (
        'lbdl'
        <lbnd-list>...  // Array of bands, each encapsulated in a list chunk
    )

        // <lbnd-list>
        LIST
        (
            'lbnd'
            <bdih-ck> or <bd2h-ck>  // bdih is a legacy format.  bd2h is preferred for new content.
            <DMBD-form> // Band
        )

            // <bdih-ck> or <bd2h-ck>       // band item header
            (
                <DMUS_IO_BAND_ITEM_HEADER> or <DMUS_IO_BAND_ITEM_HEADER2> // Band item header
            )
*/      


/*  File io for DirectMusic Band object
*/

/* RIFF ids: */

#define DMUS_FOURCC_BAND_FORM           mmioFOURCC('D','M','B','D')
#define DMUS_FOURCC_INSTRUMENTS_LIST    mmioFOURCC('l','b','i','l')
#define DMUS_FOURCC_INSTRUMENT_LIST     mmioFOURCC('l','b','i','n')
#define DMUS_FOURCC_INSTRUMENT_CHUNK    mmioFOURCC('b','i','n','s')

/* Flags for DMUS_IO_INSTRUMENT
 */
#define DMUS_IO_INST_PATCH          (1 << 0)        /* dwPatch is valid. */
#define DMUS_IO_INST_BANKSELECT     (1 << 1)        /* dwPatch contains a valid Bank Select MSB and LSB part */
#define DMUS_IO_INST_ASSIGN_PATCH   (1 << 3)        /* dwAssignPatch is valid */
#define DMUS_IO_INST_NOTERANGES     (1 << 4)        /* dwNoteRanges is valid */
#define DMUS_IO_INST_PAN            (1 << 5)        /* bPan is valid */
#define DMUS_IO_INST_VOLUME         (1 << 6 )       /* bVolume is valid */
#define DMUS_IO_INST_TRANSPOSE      (1 << 7)        /* nTranspose is valid */
#define DMUS_IO_INST_GM             (1 << 8)        /* Instrument is from GM collection */
#define DMUS_IO_INST_GS             (1 << 9)        /* Instrument is from GS collection */
#define DMUS_IO_INST_XG             (1 << 10)       /* Instrument is from XG collection */
#define DMUS_IO_INST_CHANNEL_PRIORITY (1 << 11)     /* dwChannelPriority is valid */
#define DMUS_IO_INST_USE_DEFAULT_GM_SET (1 << 12)   /* Always use the default GM set for this patch,  */
                                                    /* don't rely on the synth caps stating GM or GS in hardware. */
#define DMUS_IO_INST_PITCHBENDRANGE (1 << 13)     /* nPitchBendRange is valid */

/* io structures */
typedef struct _DMUS_IO_INSTRUMENT
{
    DWORD   dwPatch;            /* MSB, LSB and Program change to define instrument */
    DWORD   dwAssignPatch;      /* MSB, LSB and Program change to assign to instrument when downloading */
    DWORD   dwNoteRanges[4];    /* 128 bits; one for each MIDI note instrument needs to able to play */
    DWORD   dwPChannel;         /* PChannel instrument plays on */
    DWORD   dwFlags;            /* DMUS_IO_INST_ flags */
    BYTE    bPan;               /* Pan for instrument */
    BYTE    bVolume;            /* Volume for instrument */
    short   nTranspose;         /* Number of semitones to transpose notes */
    DWORD   dwChannelPriority;  /* Channel priority */
    short   nPitchBendRange;    /* Number of semitones shifted by pitch bend */
} DMUS_IO_INSTRUMENT;

/*
// <DMBD-form> bands can be embedded in other forms
RIFF
(
    'DMBD'          // DirectMusic Band chunk
    [<guid-ck>]     // GUID for band
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    <lbil-list>     // List of Instruments
)

    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <lbil-list>
    LIST
    (
        'lbil'          // Array of instruments
        <lbin-list>...  // Each instrument is encapsulated in a list
    )

        // <lbin-list>
        LIST
        (
            'lbin'
            <bins-ck>
            [<DMRF-list>]       // Optional reference to DLS Collection file.
        )

            // <bins-ck>            // Instrument chunk
            (
                'bins'
                <DMUS_IO_INSTRUMENT>    // Instrument header
            )
*/      

/* This RIFF id and io struct have been added to allow wave files (and the wave object) to 
   differentiate between streaming and one-shot waves, and to give a prefetch for streaming
   waves  */

#define DMUS_FOURCC_WAVEHEADER_CHUNK   mmioFOURCC('w','a','v','h')

typedef struct _DMUS_IO_WAVE_HEADER
{
    REFERENCE_TIME  rtReadAhead;    /* How far ahead in the stream wave data will be read (in REFERENCE_TIME).  Ignored for one-shot waves.  */
    DWORD           dwFlags;        /* Various flags, including whether this is a streaming wave and whether it can be invalidated. */
} DMUS_IO_WAVE_HEADER;


/*  File io for Wave track */

/* RIFF ids: */

#define DMUS_FOURCC_WAVETRACK_LIST      mmioFOURCC('w','a','v','t')
#define DMUS_FOURCC_WAVETRACK_CHUNK     mmioFOURCC('w','a','t','h')
#define DMUS_FOURCC_WAVEPART_LIST       mmioFOURCC('w','a','v','p')
#define DMUS_FOURCC_WAVEPART_CHUNK      mmioFOURCC('w','a','p','h')
#define DMUS_FOURCC_WAVEITEM_LIST       mmioFOURCC('w','a','v','i')
#define DMUS_FOURCC_WAVE_LIST           mmioFOURCC('w','a','v','e')
#define DMUS_FOURCC_WAVEITEM_CHUNK      mmioFOURCC('w','a','i','h')

/* This flag is included in DMUS_IO_WAVE_TRACK_HEADER.dwFlags.  If set, the track will get its 
   variations from a pattern track, via GetParam(GUID_Variations). */
#define DMUS_WAVETRACKF_SYNC_VAR   0x1
/* This is also included in DMUS_IO_WAVE_TRACK_HEADER.dwFlags.  If set, variation control 
   information will persist from one playback instance to the next.*/
#define DMUS_WAVETRACKF_PERSIST_CONTROL 0x2

typedef struct _DMUS_IO_WAVE_TRACK_HEADER
{
    long        lVolume;        /* Gain, in 1/100th of dB, to be applied to all waves.  Note:  All gain values should be negative. */
    DWORD       dwFlags;        /* Flags, including whether this track syncs to a pattern track for its variations. */
} DMUS_IO_WAVE_TRACK_HEADER;

typedef struct _DMUS_IO_WAVE_PART_HEADER
{
    long            lVolume;        /* Gain, in 1/100th of dB, to be applied to all waves in wave part.  Note:  All gain values should be negative. */
    DWORD           dwVariations;   /* Variation mask for which of 32 variations */
    DWORD           dwPChannel;     /* PChannel */
    DWORD           dwLockToPart;   /* Part ID to lock to. */
    DWORD           dwFlags;        /* Flags, including stuff for managing how variations are chosen (in low-order nibble) */
    DWORD           dwIndex;        /* Index for distinguishing multiple parts on the same PChannel*/
} DMUS_IO_WAVE_PART_HEADER;

typedef struct _DMUS_IO_WAVE_ITEM_HEADER
{
    long            lVolume;        /* Gain, in 1/100th of dB.  Note:  All gain values should be negative. */
    long            lPitch;         /* Pitch offset in 1/100th of a semitone. */
    DWORD           dwVariations;   /* Variation flags for which of 32 variations this wave belongs to. */
    REFERENCE_TIME  rtTime;         /* Start time, in REFERENCE_TIME, if clock time track, or MUSIC_TIME for music time track. */
    REFERENCE_TIME  rtStartOffset;  /* Distance into wave to start playback, in reference time units. */
    REFERENCE_TIME  rtReserved;     /* Reserved field. */
    REFERENCE_TIME  rtDuration;     /* Duration, in REFERENCE_TIME or MUSIC_TIME, depending on track timing format. */
    MUSIC_TIME      mtLogicalTime;  /* If in music track format, this indicates the musical boundary where this belongs. Otherwise, ignored. */
    DWORD           dwLoopStart;    /* Start point for a looping wave. */
    DWORD           dwLoopEnd;      /* End point for a looping wave. */
    DWORD           dwFlags;        /* Various flags, including whether this is a streaming wave and whether it can be invalidated. */
    WORD            wVolumeRange;   /* Random range for volume. */
    WORD            wPitchRange;    /* Random range for pitch. */
} DMUS_IO_WAVE_ITEM_HEADER;

/*
LIST
{
    'wavt'          // Wave track chunk
    <wath-ck>       // Wave track header
    <wavp-list>...  // Array of Wave Parts
}
    // <wath-ck>
    'wath'
    {
        <DMUS_IO_WAVE_TRACK_HEADER>
    }

    //  <wavp-list>
    LIST
    {
        'wavp'
        <waph-ck>       //  Wave Part Header
        <wavi-list>     //  List of wave items
    }

        //  <waph-ck>
        'waph'
        {
            <DMUS_IO_WAVE_PART_HEADER>
        }

        //  <wavi-list>
        LIST
        {
            'wavi'
            <wave-list>...  //  Array of waves; each wave is encapsulated in a list
        }

            //  <wave-list>
            LIST
            {
                'wave'
                <waih-ck>       //  Wave item header
                <DMRF-list>     //  Reference to wave object
            }

                //  <waih-ck>
                'waih'
                {
                    <DMUS_IO_WAVE_ITEM_HEADER>
                }

*/

/*  File io for DirectMusic Container file. This embeds a set of related files. And,
    in turn, it can be embedded within a segment or script file.
*/

#define DMUS_FOURCC_CONTAINER_FORM          mmioFOURCC('D','M','C','N')
#define DMUS_FOURCC_CONTAINER_CHUNK         mmioFOURCC('c','o','n','h')
#define DMUS_FOURCC_CONTAINED_ALIAS_CHUNK   mmioFOURCC('c','o','b','a')
#define DMUS_FOURCC_CONTAINED_OBJECT_CHUNK  mmioFOURCC('c','o','b','h')
#define DMUS_FOURCC_CONTAINED_OBJECTS_LIST  mmioFOURCC('c','o','s','l')
#define DMUS_FOURCC_CONTAINED_OBJECT_LIST   mmioFOURCC('c','o','b','l')

typedef struct _DMUS_IO_CONTAINER_HEADER
{
    DWORD       dwFlags;        /* Flags. */
} DMUS_IO_CONTAINER_HEADER;

#define DMUS_CONTAINER_NOLOADS  (1 << 1)   /* Contained items are not loaded when the container is loaded.
                                              Entries will be created in the loader (via SetObject) but
                                              the actual objects will not be created until they are
                                              specifically loaded at a later time. */

typedef struct _DMUS_IO_CONTAINED_OBJECT_HEADER
{
    GUID        guidClassID;    /* Class id of object. */
    DWORD       dwFlags;        /* Flags, for example DMUS_CONTAINED_OBJF_KEEP. */
    FOURCC      ckid;           /* chunk ID of track's data chunk if 0 fccType valid. */
    FOURCC      fccType;        /* list type if NULL ckid valid */
        /* Note that LIST:DMRF may be used for ckid and fccType in order to reference an
           object instead of embedding it within the container. */
} DMUS_IO_CONTAINED_OBJECT_HEADER;

#define DMUS_CONTAINED_OBJF_KEEP    1   /* Keep the object cached in the loader after the container is released. */

/*
RIFF
(
    'DMCN'          // DirectMusic Container chunk
    <conh-ck>       // Container header chunk
    [<guid-ck>]     // GUID for container
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    <cosl-list>     // List of objects.
)

    // <conh-ck>        
    'conh'
    (
        <DMUS_IO_CONTAINER_HEADER>
    )
    
    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    LIST
    (
        'cosl'          // Array of embedded objects.
        <cobl-list>...  // Each object is encapsulated in a LIST chunk
    )

    // <cobl-list>      // Encapsulates one object
    LIST
    (
        'cobl'
        [<coba-ck>]         // Alias.  An alternative name by which this object is known
                            // within the container.
        <cobh-ck>           // Required header, includes CLASS ID for object.
        [<data>] or <DMRF>  // Object data of the type specified in <cobh-ck>.
                            // If DMRF, it is a reference of where to find the object.
                            // Otherwise, it could be any RIFF readable chunk in the
                            //    exact same format as a file.  The object will load
                            //    itself from this data.
    )

    // <coba-ck>
    'coba'
    (
        // Alias, stored as NULL terminated string of WCHARs
    )

    // <cobh-ck>
    'cobh'
    (
        <DMUS_IO_CONTAINED_OBJECT_HEADER>
    )
*/

/*  File io for DirectMusic Segment object */

/* RIFF ids: */

#define DMUS_FOURCC_SEGMENT_FORM        mmioFOURCC('D','M','S','G')
#define DMUS_FOURCC_SEGMENT_CHUNK       mmioFOURCC('s','e','g','h')
#define DMUS_FOURCC_TRACK_LIST          mmioFOURCC('t','r','k','l')
#define DMUS_FOURCC_TRACK_FORM          mmioFOURCC('D','M','T','K')
#define DMUS_FOURCC_TRACK_CHUNK         mmioFOURCC('t','r','k','h')
#define DMUS_FOURCC_TRACK_EXTRAS_CHUNK  mmioFOURCC('t','r','k','x')

/* io structures:*/

typedef struct _DMUS_IO_SEGMENT_HEADER
{
    DWORD       dwRepeats;      /* Number of repeats. By default, 0. */
    MUSIC_TIME  mtLength;       /* Length, in music time. */
    MUSIC_TIME  mtPlayStart;    /* Start of playback. By default, 0. */
    MUSIC_TIME  mtLoopStart;    /* Start of looping portion. By default, 0. */
    MUSIC_TIME  mtLoopEnd;      /* End of loop. Must be greater than dwPlayStart. Or, 0, indicating loop full segment. */
    DWORD       dwResolution;   /* Default resolution. */
    /* Following added for DX8: */
    REFERENCE_TIME rtLength;    /* Length, in reference time (overrides music time length.) */
    DWORD       dwFlags;
    DWORD       dwReserved;     /* Reserved. */
    /* Added for DX9. */
    REFERENCE_TIME rtLoopStart; /* Clock time loop start. */
    REFERENCE_TIME rtLoopEnd;   /* Clock time loop end. */
    REFERENCE_TIME rtPlayStart; /* Start of playback in clock time. */
} DMUS_IO_SEGMENT_HEADER;

#define DMUS_SEGIOF_REFLENGTH   1  /* Use the time in rtLength for the segment length. */
#define DMUS_SEGIOF_CLOCKTIME   2  /* This is a clock time segment. */

typedef struct _DMUS_IO_TRACK_HEADER
{
    GUID        guidClassID;    /* Class id of track. */
    DWORD       dwPosition;     /* Position in track list. */
    DWORD       dwGroup;        /* Group bits for track. */
    FOURCC      ckid;           /* chunk ID of track's data chunk. */
    FOURCC      fccType;        /* list type if ckid is RIFF or LIST */ 
} DMUS_IO_TRACK_HEADER;

/*  Additional parameters for the track header chunk, introduced in DX8 and
    on, are stored in a separate chunk. */

typedef struct _DMUS_IO_TRACK_EXTRAS_HEADER
{
    DWORD       dwFlags;        /* DX8 Added flags for control tracks. */
    DWORD       dwPriority;     /* Priority for composition. */
} DMUS_IO_TRACK_EXTRAS_HEADER;

/*
RIFF
(
    'DMSG'          // DirectMusic Segment chunk
    <segh-ck>       // Segment header chunk
    [<guid-ck>]     // GUID for segment
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    [<DMCN-form>]   // Optional container of objects embedded in file. Must precede tracklist.
    <trkl-list>     // List of Tracks
    [<DMTG-form>]   // Optional ToolGraph
    [<DMAP-form>]   // Optional Audio Path
)

    // <segh-ck>        
    'segh'
    (
        <DMUS_IO_SEGMENT_HEADER>
    )
    
    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <trkl-list>
    LIST
    (
        'trkl'          // Array of tracks
        <DMTK-form>...  // Each track is encapsulated in a RIFF chunk
    )

    // <DMTK-form>      // Tracks can be embedded in a segment or stored as separate files.
    RIFF
    (
        'DMTK'
        <trkh-ck>
        [<trkx-ck>]     // Optional track flags. 
        [<guid-ck>]     // Optional GUID for track object instance (not to be confused with Class id in track header)
        [<vers-ck>]     // Optional version info
        [<UNFO-list>]   // Optional name, author, copyright info., comments
        [<data>]        // Track data. Must be a RIFF readable chunk.
    )

    // <trkh-ck>            // Track header chunk
    (
        'trkh'
        <DMUS_IO_TRACK_HEADER>  // Track header
    )

    // <trkx-ck>            // Track flags chunk
    (
        'trkx'
        <DMUS_IO_TRACK_EXTRAS_HEADER>  // DX8 Track flags header
    )
*/

/*  File io for DirectMusic reference chunk. 
    This is used to embed a reference to an object.
*/

/*  RIFF ids: */

#define DMUS_FOURCC_REF_LIST        mmioFOURCC('D','M','R','F')
#define DMUS_FOURCC_REF_CHUNK       mmioFOURCC('r','e','f','h')
#define DMUS_FOURCC_DATE_CHUNK      mmioFOURCC('d','a','t','e')
#define DMUS_FOURCC_NAME_CHUNK      mmioFOURCC('n','a','m','e')
#define DMUS_FOURCC_FILE_CHUNK      mmioFOURCC('f','i','l','e')

typedef struct _DMUS_IO_REFERENCE
{
    GUID    guidClassID;    /* Class id is always required. */
    DWORD   dwValidData;    /* Flags. */
} DMUS_IO_REFERENCE;

/*
LIST
(
    'DMRF'          // DirectMusic Reference chunk
    <refh-ck>       // Reference header chunk
    [<guid-ck>]     // Optional object GUID.
    [<date-ck>]     // Optional file date.
    [<name-ck>]     // Optional name.
    [<file-ck>]     // Optional file name.
    [<catg-ck>]     // Optional category name.
    [<vers-ck>]     // Optional version info.
)

    // <refh-ck>
    'refh'
    (
        <DMUS_IO_REFERENCE>
    )

    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <date-ck>
    date
    (
        <FILETIME>
    )

    // <name-ck>
    name
    (
        // Name, stored as NULL terminated string of WCHARs
    )

    // <file-ck>
    file
    (
        // File name, stored as NULL terminated string of WCHARs
    )

    // <catg-ck>
    catg
    (
        // Category name, stored as NULL terminated string of WCHARs
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )
*/

/* Chord Maps */

/* runtime chunks */
#define DMUS_FOURCC_CHORDMAP_FORM       mmioFOURCC('D','M','P','R')
#define DMUS_FOURCC_IOCHORDMAP_CHUNK    mmioFOURCC('p','e','r','h')
#define DMUS_FOURCC_SUBCHORD_CHUNK      mmioFOURCC('c','h','d','t')
#define DMUS_FOURCC_CHORDENTRY_CHUNK    mmioFOURCC('c','h','e','h')
#define DMUS_FOURCC_SUBCHORDID_CHUNK    mmioFOURCC('s','b','c','n')
#define DMUS_FOURCC_IONEXTCHORD_CHUNK   mmioFOURCC('n','c','r','d')
#define DMUS_FOURCC_NEXTCHORDSEQ_CHUNK  mmioFOURCC('n','c','s','q')
#define DMUS_FOURCC_IOSIGNPOST_CHUNK    mmioFOURCC('s','p','s','h')
#define DMUS_FOURCC_CHORDNAME_CHUNK     mmioFOURCC('I','N','A','M')

/* runtime list chunks */
#define DMUS_FOURCC_CHORDENTRY_LIST     mmioFOURCC('c','h','o','e')
#define DMUS_FOURCC_CHORDMAP_LIST       mmioFOURCC('c','m','a','p')
#define DMUS_FOURCC_CHORD_LIST          mmioFOURCC('c','h','r','d')
#define DMUS_FOURCC_CHORDPALETTE_LIST   mmioFOURCC('c','h','p','l')
#define DMUS_FOURCC_CADENCE_LIST        mmioFOURCC('c','a','d','e')
#define DMUS_FOURCC_SIGNPOSTITEM_LIST   mmioFOURCC('s','p','s','t')

#define DMUS_FOURCC_SIGNPOST_LIST       mmioFOURCC('s','p','s','q')

/* values for dwChord field of DMUS_IO_PERS_SIGNPOST */
/* DMUS_SIGNPOSTF_ flags are also used in templates (DMUS_IO_SIGNPOST) */
#define DMUS_SIGNPOSTF_A        1      
#define DMUS_SIGNPOSTF_B        2
#define DMUS_SIGNPOSTF_C        4
#define DMUS_SIGNPOSTF_D        8
#define DMUS_SIGNPOSTF_E        0x10
#define DMUS_SIGNPOSTF_F        0x20
#define DMUS_SIGNPOSTF_LETTER   (DMUS_SIGNPOSTF_A | DMUS_SIGNPOSTF_B | DMUS_SIGNPOSTF_C | DMUS_SIGNPOSTF_D | DMUS_SIGNPOSTF_E | DMUS_SIGNPOSTF_F)
#define DMUS_SIGNPOSTF_1        0x100
#define DMUS_SIGNPOSTF_2        0x200
#define DMUS_SIGNPOSTF_3        0x400
#define DMUS_SIGNPOSTF_4        0x800
#define DMUS_SIGNPOSTF_5        0x1000
#define DMUS_SIGNPOSTF_6        0x2000
#define DMUS_SIGNPOSTF_7        0x4000
#define DMUS_SIGNPOSTF_ROOT     (DMUS_SIGNPOSTF_1 | DMUS_SIGNPOSTF_2 | DMUS_SIGNPOSTF_3 | DMUS_SIGNPOSTF_4 | DMUS_SIGNPOSTF_5 | DMUS_SIGNPOSTF_6 | DMUS_SIGNPOSTF_7)
#define DMUS_SIGNPOSTF_CADENCE  0x8000

/* values for dwFlags field of DMUS_IO_CHORDMAP */
#define DMUS_CHORDMAPF_VERSION8  1   /* Chordmap is version 8 or above. */

/* values for dwChord field of DMUS_IO_PERS_SIGNPOST */
#define DMUS_SPOSTCADENCEF_1  2   /* Use the first cadence chord. */
#define DMUS_SPOSTCADENCEF_2  4   /* Use the second cadence chord. */

/* run time data structs */
typedef struct _DMUS_IO_CHORDMAP
{
    WCHAR   wszLoadName[20];
    DWORD   dwScalePattern;
    DWORD   dwFlags;           /* Various flags. Only lower 16 bits are significant. */
} DMUS_IO_CHORDMAP;

typedef struct _DMUS_IO_CHORDMAP_SUBCHORD
{
    DWORD   dwChordPattern;
    DWORD   dwScalePattern;
    DWORD   dwInvertPattern;
    BYTE    bChordRoot;
    BYTE    bScaleRoot;
    WORD    wCFlags;
    DWORD   dwLevels;   /* parts or which subchord levels this chord supports */
} DMUS_IO_CHORDMAP_SUBCHORD;

/* Legacy name... */
typedef DMUS_IO_CHORDMAP_SUBCHORD DMUS_IO_PERS_SUBCHORD;

typedef struct _DMUS_IO_CHORDENTRY
{
    DWORD   dwFlags;
    WORD    wConnectionID;  /* replaces runtime "pointer to this" */
} DMUS_IO_CHORDENTRY;

typedef struct _DMUS_IO_NEXTCHORD
{
    DWORD   dwFlags;
    WORD    nWeight;
    WORD    wMinBeats;
    WORD    wMaxBeats;
    WORD    wConnectionID;  /* points to an ioChordEntry */
} DMUS_IO_NEXTCHORD;

typedef struct _DMUS_IO_CHORDMAP_SIGNPOST
{
    DWORD   dwChords;   /* 1bit per group */
    DWORD   dwFlags;
} DMUS_IO_CHORDMAP_SIGNPOST;

/* Legacy name... */
typedef DMUS_IO_CHORDMAP_SIGNPOST DMUS_IO_PERS_SIGNPOST;

/*
RIFF
(
    'DMPR'
    <perh-ck>           // Chord map header chunk
    [<guid-ck>]         // guid chunk
    [<vers-ck>]         // version chunk (two DWORDS)
    [<UNFO-list>]       // Unfo chunk
    <chdt-ck>           // subchord database
    <chpl-list>         // chord palette
    <cmap-list>         // chord map
    <spsq-list>         // signpost list
 )

<cmap-list> ::= LIST('cmap' <choe-list> )

<choe-list> ::= LIST('choe'
                                <cheh-ck>   // chord entry data
                                <chrd-list> // chord definition
                                <ncsq-ck>   // connecting(next) chords
                     )

<chrd-list> ::= LIST('chrd' 
                                <INAM-ck>   // name of chord in wide char format
                                <sbcn-ck>   // list of subchords composing chord
                    )

<chpl-list> ::= LIST('chpl' 
                                <chrd-list> ... // chord definition
                    )

<spsq-list> ::== LIST('spsq' <spst-list> ... )

<spst-list> ::= LIST('spst'
                             <spsh-ck>
                             <chrd-list>
                             [<cade-list>]
                    )

<cade-list> ::= LIST('cade' <chrd-list> ...)

<perh-ck> ::= perh(<DMUS_IO_CHORDMAP>)

<chdt-ck> ::= chdt(<cbChordSize::WORD>
                   <DMUS_IO_PERS_SUBCHORD> ... )

<cheh-ck> ::= cheh(<DMUS_IO_CHORDENTRY>)

<sbcn-ck> ::= sbcn(<cSubChordID:WORD> ...)

<ncsq-ck> ::= ncsq(<wNextChordSize:WORD> 
                   <DMUS_IO_NEXTCHORD>...)

<spsh-ck> ::= spsh(<DMUS_IO_PERS_SIGNPOST>)

*/

/*  File io for DirectMusic Script object */

/* RIFF ids: */

#define DMUS_FOURCC_SCRIPT_FORM             mmioFOURCC('D','M','S','C')
#define DMUS_FOURCC_SCRIPT_CHUNK            mmioFOURCC('s','c','h','d')
#define DMUS_FOURCC_SCRIPTVERSION_CHUNK     mmioFOURCC('s','c','v','e')
#define DMUS_FOURCC_SCRIPTLANGUAGE_CHUNK    mmioFOURCC('s','c','l','a')
#define DMUS_FOURCC_SCRIPTSOURCE_CHUNK      mmioFOURCC('s','c','s','r')

/* io structures:*/

typedef struct _DMUS_IO_SCRIPT_HEADER
{
    DWORD       dwFlags; /* DMUS_SCRIPTIOF_ flags */
} DMUS_IO_SCRIPT_HEADER;

#define DMUS_SCRIPTIOF_LOAD_ALL_CONTENT       (1 << 0)
    /* If set, when the script loads it will also load all the content in its container. */
#define DMUS_SCRIPTIOF_DOWNLOAD_ALL_SEGMENTS  (1 << 1)
    /* If set and LOAD_ALL_CONTENT is also set, when the script initializes it will also download all the segments in its container.
       If set and LOAD_ALL_CONTENT is not set, when the script calls segment.Load on a segment then the segment will also be downloaded.
       If not set, the script must manually download and unload by calling segment.DownloadSoundData and segment.UnloadSoundData. */

/*
RIFF
(
    'DMSC'              // DirectMusic Script chunk
    <schd-ck>           // Script header chunk
    [<guid-ck>]         // GUID for script
    [<vers-ck>]         // Optional version info
    [<UNFO-list>]       // Name, author, copyright info., comments
    <scve-ck>           // Version of DirectMusic this script was authored to run against
    <DMCN-form>         // Container of content referenced by the script.
    <scla-ck>           // ActiveX scripting language in which the script is written
    <scsr-ck> or <DMRF> // The script's source code.
                        // If scsr-ck, the source is embedding in the chunk.
                        // If DMRF, it is a reference of where to find a text file with the source.
                        //    Class id (guidClassID in DMUS_IO_REFERENCE) must be GUID_NULL because
                        //    this text file is not a DirectMusic object in its own right.
)

    // <schd-ck>
    'schd'
    (
        <DMUS_FOURCC_SCRIPT_CHUNK>
    )
    
    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    vers
    (
        <DMUS_IO_VERSION>
    )

    // <scve-ck>
    scve
    (
        <DMUS_IO_VERSION>
    )

    'scla'
    (
        // Language name, stored as NULL terminated string of WCHARs
    )

    'scsr'
    (
        // Source code, stored as NULL terminated string of WCHARs
    )
*/

/* Signpost tracks */

#define DMUS_FOURCC_SIGNPOST_TRACK_CHUNK     mmioFOURCC( 's', 'g', 'n', 'p' )


typedef struct _DMUS_IO_SIGNPOST
{
    MUSIC_TIME  mtTime;
    DWORD       dwChords;
    WORD        wMeasure;
} DMUS_IO_SIGNPOST;

/*

    // <sgnp-list>
    'sgnp'
    (
        //sizeof DMUS_IO_SIGNPOST: DWORD
        <DMUS_IO_SIGNPOST>...
    )

*/

#define DMUS_FOURCC_MUTE_CHUNK  mmioFOURCC('m','u','t','e')

typedef struct _DMUS_IO_MUTE
{
    MUSIC_TIME  mtTime;
    DWORD       dwPChannel;
    DWORD       dwPChannelMap;
} DMUS_IO_MUTE;

/*

    // <mute-list>
    'mute'
    (
        //sizeof DMUS_IO_MUTE:DWORD
        <DMUS_IO_MUTE>...
    )


*/

/* Used for both style and chord map tracks */

#define DMUS_FOURCC_TIME_STAMP_CHUNK    mmioFOURCC('s', 't', 'm', 'p')

/* Style tracks */

#define DMUS_FOURCC_STYLE_TRACK_LIST    mmioFOURCC('s', 't', 't', 'r')
#define DMUS_FOURCC_STYLE_REF_LIST      mmioFOURCC('s', 't', 'r', 'f')

/*

    // <sttr-list>
    LIST('sttr'
    (
        <strf-list>...  // Array of Style references
    )

    // <strf-list>
    LIST('strf'
    (
        <stmp-ck>
        <DMRF>
    )

  // <stmp-ck>
  'stmp'
  (
    // time:DWORD
  )

*/

/* Chord map tracks */

#define DMUS_FOURCC_PERS_TRACK_LIST mmioFOURCC('p', 'f', 't', 'r')
#define DMUS_FOURCC_PERS_REF_LIST   mmioFOURCC('p', 'f', 'r', 'f')

/*

    // <pftr-list>
    LIST('pftr'
    (
        <pfrf-list>...  // Array of Chord map references
    )

    // <pfrf-list>
    LIST('pfrf'
    (
        <stmp-ck>
        <DMRF>
    )

  // <stmp-ck>
  'stmp'
  (
    // time:DWORD
  )

*/

#define DMUS_FOURCC_TEMPO_TRACK     mmioFOURCC('t','e','t','r')

/*
    // tempo array
    'tetr'
    (
        // sizeof DMUS_IO_TEMPO_ITEM: DWORD
        <DMUS_IO_TEMPO_ITEM>...
    )
 */

#define DMUS_FOURCC_SEQ_TRACK       mmioFOURCC('s','e','q','t')
#define DMUS_FOURCC_SEQ_LIST        mmioFOURCC('e','v','t','l')
#define DMUS_FOURCC_CURVE_LIST      mmioFOURCC('c','u','r','l')

/*
    // sequence track
    'seqt'
    (
        // sequence array
        'evtl'
        (
            // sizeof DMUS_IO_SEQ_ITEM: DWORD
            <DMUS_IO_SEQ_ITEM>...
        )
        // curve array
        'curl'
        (
            // sizeof DMUS_IO_CURVE_ITEM: DWORD
            <DMUS_IO_CURVE_ITEM>...
        )
    )
*/

#define DMUS_FOURCC_SYSEX_TRACK     mmioFOURCC('s','y','e','x')

/*
    // sysex track
    'syex'
    (
        {
            <DMUS_IO_SYSEX_ITEM>
            <BYTE>...    // Array of bytes, length defined in the DMUS_IO_SYSEXITEM structure
        }...
    )
*/

#define DMUS_FOURCC_TIMESIGNATURE_TRACK mmioFOURCC('t','i','m','s')

typedef struct _DMUS_IO_TIMESIGNATURE_ITEM
{
    MUSIC_TIME    lTime;
    BYTE          bBeatsPerMeasure;   /* beats per measure (top of time sig) */
    BYTE          bBeat;              /* what note receives the beat (bottom of time sig.) */
                                      /* we can assume that 0 means 256th note */
    WORD          wGridsPerBeat;      /* grids per beat */
} DMUS_IO_TIMESIGNATURE_ITEM;

/*  DX6 time signature track
    
    'tims'
    (
        // size of DMUS_IO_TIMESIGNATURE_ITEM : DWORD
        <DMUS_IO_TIMESIGNATURE_ITEM>...
    )
*/

/*  DX8 Time signature track. The track has been updated from DX7 to support a list of
    RIFF chunks. This will allow the time signature track to expand in the future.
*/

#define DMUS_FOURCC_TIMESIGTRACK_LIST   mmioFOURCC('T','I','M','S')
#define DMUS_FOURCC_TIMESIG_CHUNK       DMUS_FOURCC_TIMESIGNATURE_TRACK

/*
LIST
(
    'TIMS'          // Time Signature Track list-type
    <tims-ck>       // Chunk containing an array of time signatures
)

    'tims'
    (
        // size of DMUS_IO_TIMESIGNATURE_ITEM : DWORD
        <DMUS_IO_TIMESIGNATURE_ITEM>...
    )
 
*/

/*  DX8 Marker track. This is used to store valid start points and other
    flow control parameters that may come later. For example, if we want
    to implement more sophisticated looping and branching constructs, they
    would live in this track.
*/

#define DMUS_FOURCC_MARKERTRACK_LIST    mmioFOURCC('M','A','R','K')
#define DMUS_FOURCC_VALIDSTART_CHUNK    mmioFOURCC('v','a','l','s')
#define DMUS_FOURCC_PLAYMARKER_CHUNK    mmioFOURCC('p','l','a','y')

/* io structures */
typedef struct _DMUS_IO_VALID_START
{
    MUSIC_TIME mtTime;      /* Time of a legal start. */
} DMUS_IO_VALID_START;

typedef struct _DMUS_IO_PLAY_MARKER
{
    MUSIC_TIME mtTime;      /* Time of a next legal play point marker. */
} DMUS_IO_PLAY_MARKER;

/*
LIST
(
    'MARK'          // Marker Track list-type
    [<vals-ck>]     // Chunk containing an array of start points
    [<play-ck>]     // Chunk containing an array of play start markers
)

    'vals'
    (
        // size of DMUS_IO_VALID_START : DWORD
        <DMUS_IO_VALID_START>...
    )

    'play'
    (
        // size of DMUS_IO_PLAY_MARKER : DWORD
        <DMUS_IO_PLAY_MARKER>...
    )
  
*/

/* segment trigger tracks */

/* RIFF ids: */
#define DMUS_FOURCC_SEGTRACK_LIST                   mmioFOURCC('s','e','g','t')
#define DMUS_FOURCC_SEGTRACK_CHUNK                  mmioFOURCC('s','g','t','h')
#define DMUS_FOURCC_SEGMENTS_LIST                   mmioFOURCC('l','s','g','l')
#define DMUS_FOURCC_SEGMENT_LIST                    mmioFOURCC('l','s','e','g')
#define DMUS_FOURCC_SEGMENTITEM_CHUNK               mmioFOURCC('s','g','i','h')
#define DMUS_FOURCC_SEGMENTITEMNAME_CHUNK           mmioFOURCC('s','n','a','m')

/* io structures */
typedef struct _DMUS_IO_SEGMENT_TRACK_HEADER
{
    DWORD dwFlags; /* Reserved leave as 0. */
} DMUS_IO_SEGMENT_TRACK_HEADER;

typedef struct _DMUS_IO_SEGMENT_ITEM_HEADER
{
    MUSIC_TIME      lTimeLogical;    /* Position in track list. Time in the music with which the event is associated. */
    MUSIC_TIME      lTimePhysical;   /* Precise time event will be triggered. Should be close to logical time. */
    DWORD           dwPlayFlags;     /* Flags for PlaySegment(). */
    DWORD           dwFlags;         /* Flags. */
} DMUS_IO_SEGMENT_ITEM_HEADER;

/* values for dwflags field of DMUS_IO_SEGMENT_ITEM_HEADER */
#define DMUS_SEGMENTTRACKF_MOTIF                 1        /* interpret DMRF as link to style, and use snam as the name of a motif within the style */

/*
LIST
(
    'segt'          // DirectMusic Segment Trigger Track form-type
    [<sgth-ck>]     // Segment track header
    <lsgl-list>     // List of Segment Lists
)

    // <sgth-ck>
    'sgth'
    (
        <DMUS_IO_SEGMENT_TRACK_HEADER>
    )

    // <lsgl-list>
    LIST
    (
        'lsgl'          // Array of segments
        <lseg-list>...  // Each segment is encapsulated in a list (that way it can still be riff parsed.)
    )

        // <lseg-list>
        LIST
        (
            'lseg'
            <sgih-ck>
            <DMRF-list>    // Link to a segment or style file.
            [<snam-ck>]    // Name field.  Used with DMUS_SEGMENTTRACKF_MOTIF flag.
        )

            // <sgih-ck>            // segment item header
            (
                <DMUS_IO_SEGMENT_ITEM_HEADER>  // Segment item header
            )

            // <snam-ck>
            (
                // Name, stored as NULL terminated string of WCHARs
            )
*/      

/* Script track. */

/* RIFF ids: */
#define DMUS_FOURCC_SCRIPTTRACK_LIST                mmioFOURCC('s','c','r','t')
#define DMUS_FOURCC_SCRIPTTRACKEVENTS_LIST          mmioFOURCC('s','c','r','l')
#define DMUS_FOURCC_SCRIPTTRACKEVENT_LIST           mmioFOURCC('s','c','r','e')
#define DMUS_FOURCC_SCRIPTTRACKEVENTHEADER_CHUNK    mmioFOURCC('s','c','r','h')
#define DMUS_FOURCC_SCRIPTTRACKEVENTNAME_CHUNK      mmioFOURCC('s','c','r','n')

/* Flags for DMUS_IO_SCRIPTTRACK_TIMING
 */
#define DMUS_IO_SCRIPTTRACKF_PREPARE (1 << 0)        /* Fire event in advance of time stamp, at Prepare time.  This is the default because it leaves the script time to change the music happening at the target time. */
#define DMUS_IO_SCRIPTTRACKF_QUEUE   (1 << 1)        /* Fire event just before time stamp, at Queue time. */
#define DMUS_IO_SCRIPTTRACKF_ATTIME  (1 << 2)        /* Fire event right at the time stamp. */

typedef struct _DMUS_IO_SCRIPTTRACK_EVENTHEADER
{
    DWORD dwFlags;              /* various bits (see DMUS_IO_SCRIPTTRACKF_*) */
    MUSIC_TIME lTimeLogical;    /* Position in track list. Time in the music with which the event is associated. */
    MUSIC_TIME lTimePhysical;   /* Precise time event will be triggered. Should be close to logical time. */
} DMUS_IO_SCRIPTTRACK_EVENTHEADER;

/*
    // Script Track

    // <scrt-list>
    LIST
    (
        <scrl-list>       // List of script events
    )

        // <scrl-list>
        LIST
        (
            <scre-list>...    // Array of event descriptions
        )

            // <scre-list>
            LIST
            (
                <scrh-ck>         // Event header chunk
                <DMRF>
                <scrn-ck>         // Routine name
            )

                'scrh'
                (
                    <DMUS_IO_SCRIPTTRACK_EVENTHEADER>
                )

                'scrn'
                (
                    // Name, stored as NULL terminated string of WCHARs
                )
*/

/* Lyrics/Notification track. */

/* RIFF ids: */
#define DMUS_FOURCC_LYRICSTRACK_LIST                mmioFOURCC('l','y','r','t')
#define DMUS_FOURCC_LYRICSTRACKEVENTS_LIST          mmioFOURCC('l','y','r','l')
#define DMUS_FOURCC_LYRICSTRACKEVENT_LIST           mmioFOURCC('l','y','r','e')
#define DMUS_FOURCC_LYRICSTRACKEVENTHEADER_CHUNK    mmioFOURCC('l','y','r','h')
#define DMUS_FOURCC_LYRICSTRACKEVENTTEXT_CHUNK      mmioFOURCC('l','y','r','n')

typedef struct _DMUS_IO_LYRICSTRACK_EVENTHEADER
{
    DWORD dwFlags;              /* Reserved leave as 0. */
    DWORD dwTimingFlags;        /* Combination DMUS_PMSGF_TOOL_* flags.  Determines the precise timing of when the notification happens. Invalid with the flag DMUS_PMSGF_REFTIME, DMUS_PMSGF_MUSICTIME, DMUS_PMSGF_TOOL_FLUSH, or DMUS_PMSGF_LOCKTOREFTIME. */
    MUSIC_TIME lTimeLogical;    /* Position in track list. Time in the music with which the event is associated. */
    MUSIC_TIME lTimePhysical;   /* Precise time event will be triggered. Should be close to logical time. */
} DMUS_IO_LYRICSTRACK_EVENTHEADER;

/*
    // Lyrics/Notification Track

    // <lyrt-list>
    LIST
    (
        <lyrl-list>       // List of notification events
    )

        // <lyrl-list>
        LIST
        (
            <lyre-list>...    // Array of event descriptions
        )

            // <lyre-list>
            LIST
            (
                <lyrh-ck>         // Event header chunk
                <lyrn-ck>         // Notification text
            )

                'lyrh'
                (
                    <DMUS_IO_LYRICSTRACK_EVENTHEADER>
                )

                'lyrn'
                (
                    // Name, stored as NULL terminated string of WCHARs
                )
*/

/* Parameter control track */

/* RIFF ids: */
#define DMUS_FOURCC_PARAMCONTROLTRACK_TRACK_LIST            mmioFOURCC('p','r','m','t')
#define DMUS_FOURCC_PARAMCONTROLTRACK_OBJECT_LIST           mmioFOURCC('p','r','o','l')
#define DMUS_FOURCC_PARAMCONTROLTRACK_OBJECT_CHUNK          mmioFOURCC('p','r','o','h')
#define DMUS_FOURCC_PARAMCONTROLTRACK_PARAM_LIST            mmioFOURCC('p','r','p','l')
#define DMUS_FOURCC_PARAMCONTROLTRACK_PARAM_CHUNK           mmioFOURCC('p','r','p','h')
#define DMUS_FOURCC_PARAMCONTROLTRACK_CURVES_CHUNK          mmioFOURCC('p','r','c','c')

typedef struct _DMUS_IO_PARAMCONTROLTRACK_OBJECTHEADER
{
    DWORD dwFlags;              /* Reserved.  Must be zero. */
    GUID guidTimeFormat;        /* Time format to set the object to.  Must be GUID_TIME_REFERNCE or GUID_TIME_MUSIC from medparam.h. */
    /* Path for finding the object. These fields correspond to the first five parameters of IDirectMusicSegmentState::GetObjectInPath. */
    DWORD dwPChannel;
    DWORD dwStage;
    DWORD dwBuffer;
    GUID guidObject;
    DWORD dwIndex;
} DMUS_IO_PARAMCONTROLTRACK_OBJECTHEADER;

typedef struct _DMUS_IO_PARAMCONTROLTRACK_PARAMHEADER
{
    DWORD dwFlags;              /* Reserved.  Must be zero. */
    DWORD dwIndex;              /* Index number of the parameter on the object */
} DMUS_IO_PARAMCONTROLTRACK_PARAMHEADER;

typedef struct _DMUS_IO_PARAMCONTROLTRACK_CURVEINFO
{
    MUSIC_TIME  mtStartTime;
    MUSIC_TIME  mtEndTime;
    float       fltStartValue;
    float       fltEndValue;
    DWORD       dwCurveType;   /* One of the items from the MP_CURVE_TYPE enum in medparam.h */
    DWORD       dwFlags;       /* A combination of the MPF_ENVLP_* constants in medparam.h */
} DMUS_IO_PARAMCONTROLTRACK_CURVEINFO;

/*
    // <prmt-list>
    LIST
    (
        <prol-list>...   // one for each object
    )

        // <prol-list>
        LIST
        (
            <proh-ck>       // object header chunk
            <prpl-list>...  // one for each parameter
        )

            // <proh-ck>
            proh
            (
                <DMUS_IO_PARAMCONTROLTRACK_OBJECTHEADER>
            )

            // <prpl-list>
            LIST
            (
                <prph-ck>       // parameter header chunk
                <prcc-ck>       // chunk containing an array of curves
            )

                // <prph-ck>
                prph
                (
                    <DMUS_IO_PARAMCONTROLTRACK_PARAMHEADER>
                )

                // <prcc-ck>
                prcc
                (
                    // sizeof DMUS_IO_PARAMCONTROLTRACK_CURVEINFO:DWORD
                    <DMUS_IO_PARAMCONTROLTRACK_CURVEINFO>... // curves, sorted in order of mtTime
                )
*/

#if (DIRECTSOUND_VERSION >= 0x0800)

/* DirectSoundBufferConfig FX Map */

/* RIFF ids: */

#define DMUS_FOURCC_DSBC_FORM       mmioFOURCC('D','S','B','C')
#define DMUS_FOURCC_DSBD_CHUNK      mmioFOURCC('d','s','b','d')
#define DMUS_FOURCC_BSID_CHUNK      mmioFOURCC('b','s','i','d')
#define DMUS_FOURCC_DS3D_CHUNK      mmioFOURCC('d','s','3','d')
#define DMUS_FOURCC_DSBC_LIST       mmioFOURCC('f','x','l','s')
#define DMUS_FOURCC_DSFX_FORM       mmioFOURCC('D','S','F','X')
#define DMUS_FOURCC_DSFX_CHUNK      mmioFOURCC('f','x','h','r')
#define DMUS_FOURCC_DSFX_DATA       mmioFOURCC('d','a','t','a')

/* io structures */

typedef struct _DSOUND_IO_DSBUFFERDESC
{
    DWORD dwFlags;        /* DirectSound buffer creation flags */
    WORD nChannels;       /* No. of channels (rest of buffer format is determined by owning sink) */
    LONG lVolume;         /* Initial pan; only used if CTRLVOLUME is specified */
    LONG lPan;            /* Initial pan; only used if CTRLPAN is specified */
    DWORD dwReserved;     /* Reserved - must be 0 */
} DSOUND_IO_DSBUFFERDESC;

typedef struct _DSOUND_IO_DSBUSID
{
    DWORD busid[1];       /* Array size determined from chunk size */
} DSOUND_IO_DSBUSID;

typedef struct _DSOUND_IO_3D
{
    GUID guid3DAlgorithm; /* GUID identifying the 3D algorithm to use (defined in dsound.h) */
    DS3DBUFFER ds3d;      /* Initial 3D parameters */
} DSOUND_IO_3D;

typedef struct _DSOUND_IO_DXDMO_HEADER
{
    DWORD dwEffectFlags;  /* Effect creation flags - equivalent to DSEFFECTDESC::dwFlags */
    GUID guidDSFXClass;   /* GUID identifying the effect to use - corresponds to a COM CLSID */
    GUID guidReserved;    /* Reserved - must be the null GUID */
    GUID guidSendBuffer;  /* GUID identifying the buffer to send to if this is a send effect */
    DWORD dwReserved;     /* Reserved - must be 0 */
} DSOUND_IO_DXDMO_HEADER;

typedef struct _DSOUND_IO_DXDMO_DATA
{
    DWORD data[1];      /* Array size determined by the DMO involved */
} DSOUND_IO_DXDMO_DATA;

/*
RIFF
(
    'DSBC'          // DirectSoundBufferConfig chunk
    [<guid-ck>]     // GUID identifier for this DirectSoundBufferConfig
    [<vers-ck>]     // Optional version info
    [<UNFO-list>]   // Name, author, copyright info., comments
    <dsbd-ck>       // DirectSound Buffer descriptor chunk
    [<bsid-ck>]     // Optional bus id array
    [<ds3d-ck>]     // Optional 3d Parameters
    [<fxls-list>]   // Optional list of FX descriptors
)

    // <guid-ck>
    'guid'
    (
        <GUID>
    )

    // <vers-ck>
    'vers'
    (
        <DMUS_IO_VERSION>
    )

    // <dsbd-ck>
    'dsbd'
    (
        <DSOUND_IO_DSBUFFERDESC>  // Creation parameters and initial settings for the buffer
    )

    // <bsid-ck>
    'bsid'
    (
        <DSOUND_IO_DSBUSID>  // The size of DSOUND_IO_DSBUSID is determined by the chunk size 
    )

    // <ds3d-ck>
    'ds3d'
    (
        <DSOUND_IO_3D>  // Initial 3D buffer parameters: position, etc.
    )

    // <fx-list>
    LIST
    (
        'fxls'          // Array of DMO creation parameter blocks
        <DSFX-form>...  // Each DMO is encapsulated in a RIFF chunk
    )

// <DSFX-form>          // DMOs can be embedded in a buffer configuration or stored as separate files
RIFF
(
    'DSFX'
    <fxhr-ck>           // FX header chunk
    [<data-ck>]         // FX initial settings chunk
)

    // <fxhr-ck>
    'fxhr'
    (
        <DSOUND_IO_DXDMO_HEADER>
    )

    // <data-ck>
    'data'
    (
        <DSOUND_IO_DXDMO_DATA>  // Opaque data block used by the DMO to load itself.
        // For our standard included DMOs, this is simply the structure accepted by
        // the DMO's SetAllParameters() method - e.g. struct DSFXChorus for Chorus.
    )
*/

#endif

#ifdef __cplusplus
}; /* extern "C" */
#endif

#include <poppack.h>

#endif /* #ifndef _DMUSICF_ */
