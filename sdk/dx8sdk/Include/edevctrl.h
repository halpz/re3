/*++

Copyright (C) Microsoft Corporation, 1998 - 1999

Module Name:

    EDevCtrl.h

Abstract:

    This header contain structures and peroperty sets for 
    interfacing to an external device, like a DV.
    The code is modeled after DirectShow's Vcrctrl Sample 
    (VCR Control Filter). It contain IAMExtDevice, 
    IAMExtTransport, and IAMTimecodeReader interfaces, and 
    a new interface IAMAdvancedAVControl() is added
    for additional advanced device controls.

    Note:  (From DShow DDK)
        The VCR control sample filter, Vcrctrl, is a simple 
        implementation of the external device control interfaces 
        that DirectShow provides. Vcrctrl provides basic transport 
        control and SMPTE timecode-reading capabilities for certain 
        Betacam and SVHS videocassette recorders with RS-422 or RS-232 
        serial interfaces (see source code for specific machine types 
        supported).

    Note:  some methods in IAM* interfaces may not be 
           used and will return not implemented.           

Created:

    September 23, 1998    

    Yee J. Wu


Revision:

   0.6

--*/

#ifndef __EDevCtrl__
#define __EDevCtrl__

#ifndef TIMECODE_DEFINED
#define TIMECODE_DEFINED
typedef union _timecode {
   struct {
	 WORD   wFrameRate;
	 WORD   wFrameFract;
	 DWORD  dwFrames;
	 };
   DWORDLONG  qw;
   } TIMECODE;



typedef TIMECODE *PTIMECODE;

typedef struct tagTIMECODE_SAMPLE
    {
    LONGLONG qwTick;
    TIMECODE timecode;
    DWORD dwUser;
    DWORD dwFlags;
    }	TIMECODE_SAMPLE;

typedef TIMECODE_SAMPLE *PTIMECODE_SAMPLE;

#endif /* TIMECODE_DEFINED */

// Device Capabilities
typedef struct tagDEVCAPS{
    long CanRecord;
    long CanRecordStrobe;
    long HasAudio;
    long HasVideo;
    long UsesFiles;
    long CanSave;
    long DeviceType;
    long TCRead;
    long TCWrite;
    long CTLRead;
    long IndexRead;
    long Preroll;
    long Postroll;
    long SyncAcc;
    long NormRate;
    long CanPreview;
    long CanMonitorSrc;
    long CanTest;
    long VideoIn;
    long AudioIn;
    long Calibrate;
    long SeekType;
    long SimulatedHardware;        // private
} DEVCAPS, *PDEVCAPS;

// transport status
typedef struct tagTRANSPORTSTATUS{
    long Mode;
    long LastError;
    long RecordInhibit;
    long ServoLock;
    long MediaPresent;
    long MediaLength;
    long MediaSize;
    long MediaTrackCount;
    long MediaTrackLength;
    long MediaTrackSide;
    long MediaType;
    long LinkMode;
    long NotifyOn;
} TRANSPORTSTATUS, *PTRANSPORTSTATUS;

// transport basic parameters
typedef struct tagTRANSPORTBASICPARMS{
    long TimeFormat;
    long TimeReference;
    long Superimpose;
    long EndStopAction;
    long RecordFormat;
    long StepFrames;
    long SetpField;
    long Preroll;
    long RecPreroll;
    long Postroll;
    long EditDelay;
    long PlayTCDelay;
    long RecTCDelay;
    long EditField;
    long FrameServo;
    long ColorFrameServo;
    long ServoRef;
    long WarnGenlock;
    long SetTracking;
    TCHAR VolumeName[40];
    long Ballistic[20];
    long Speed;
    long CounterFormat;
    long TunerChannel;
    long TunerNumber;
    long TimerEvent;
    long TimerStartDay;
    long TimerStartTime;
    long TimerStopDay;
    long TimerStopTime;
} TRANSPORTBASICPARMS, *PTRANSPORTBASICPARMS;

// transport video parameters
typedef struct tagTRANSPORTVIDEOPARMS{
    long OutputMode;
    long Input;
} TRANSPORTVIDEOPARMS, *PTRANSPORTVIDEOPARMS;

// transport audio parameters
typedef struct tagTRANSPORTAUDIOPARMS{
    long EnableOutput;
    long EnableRecord;
    long EnableSelsync;
    long Input;
    long MonitorSource;
} TRANSPORTAUDIOPARMS, *PTRANSPORTAUDIOPARMS;


// low level machine status structure filled in after
// REQUEST_STATUS command from above.  This structure would
// grow in a full implementation
typedef struct tagVCRSTATUS{
	BOOL bCassetteOut;	// OATRUE means no cassette
	BOOL bLocal;		// OATRUE means front panel switch in local
} VCRSTATUS;

typedef VCRSTATUS far *PVCRSTATUS;



//---------------------------------------------------------
// STATIC_PROPSETID_VIDCAP_EXT_DEVICE
//---------------------------------------------------------
// This guid and interface is defined in strmif.h 
#define STATIC_PROPSETID_EXT_DEVICE\
    0xB5730A90L, 0x1A2C, 0x11cf, 0x8c, 0x23, 0x00, 0xAA, 0x00, 0x6B, 0x68, 0x14
DEFINE_GUIDSTRUCT("B5730A90-1A2C-11cf-8C23-00AA006B6814", PROPSETID_EXT_DEVICE);
#define PROPSETID_EXT_DEVICE DEFINE_GUIDNAMED(PROPSETID_EXT_DEVICE)


// KS properties and structure for this interface
typedef enum {
    KSPROPERTY_EXTDEVICE_ID,           // ID (such as Symbolic Lin) that can uniquely idenfy this device
    KSPROPERTY_EXTDEVICE_VERSION,      // Device model number and version (such AV/C VCR Subunit Spec. 2.01)
    KSPROPERTY_EXTDEVICE_POWER_STATE,  // Return current device power state.
    KSPROPERTY_EXTDEVICE_PORT,         // Can use this to return DEV_PORT_1394
    KSPROPERTY_EXTDEVICE_CAPABILITIES, // Device specific capabilities  

} KSPROPERTY_EXTDEVICE;


typedef struct {
    KSPROPERTY Property;
 
    union {
        // Client is responsible for allocating this.
        DEVCAPS  Capabilities;          // May need to expand on the existing structure
		ULONG    DevPort;               // 
        ULONG    PowerState;            // On, off standby
        WCHAR    pawchString[MAX_PATH]; // ID and version
        DWORD    NodeUniqueID[2];       // Unique NodeID
    } u;

} KSPROPERTY_EXTDEVICE_S, *PKSPROPERTY_EXTDEVICE_S;


//---------------------------------------------------------
// STATIC_PROPSETID_VIDCAP_EXT_TRANSPORT
//---------------------------------------------------------
// This guid and interface is defined in strmif.h 
#define STATIC_PROPSETID_EXT_TRANSPORT\
    0xA03CD5F0L, 0x3045, 0x11cf, 0x8c, 0x44, 0x00, 0xAA, 0x00, 0x6B, 0x68, 0x14
DEFINE_GUIDSTRUCT("A03CD5F0-3045-11cf-8C44-00AA006B6814", PROPSETID_EXT_TRANSPORT);
#define PROPSETID_EXT_TRANSPORT DEFINE_GUIDNAMED(PROPSETID_EXT_TRANSPORT)



// KS properties and structure for this interface
typedef enum {
    KSPROPERTY_EXTXPORT_CAPABILITIES,       // Transport specific capability 
    KSPROPERTY_EXTXPORT_INPUT_SIGNAL_MODE,  // MPEG, D-VHS, Analog VHS etc. 
    KSPROPERTY_EXTXPORT_OUTPUT_SIGNAL_MODE, // MPEG, D-VHS, Analog VHS etc. 
    KSPROPERTY_EXTXPORT_LOAD_MEDIUM,        // Eject, open tray, close tray
    KSPROPERTY_EXTXPORT_MEDIUM_INFO,        // cassettte_type and tape_grade_and_write_protect    
    KSPROPERTY_EXTXPORT_STATE,              // Get/Set transport mode and state
    KSPROPERTY_EXTXPORT_STATE_NOTIFY,       // NOTIFY: Mode + State (Table 4-8) 
    KSPROPERTY_EXTXPORT_TIMECODE_SEARCH,    // Request VCR subunit to search for a specific timecode on the medium
    KSPROPERTY_EXTXPORT_ATN_SEARCH,         // Request VCR subunit to search for a specific ATN on the medium
    KSPROPERTY_EXTXPORT_RTC_SEARCH,         // Request VCR subunit to search for a specific RelativeTimeCounter on the medium

    //
    // Implemented for testing purpose
    // Will remove this later...
    //
    KSPROPERTY_RAW_AVC_CMD,                 // Send/Rcv raw AVC commnad with a FCP packet.

} KSPROPERTY_EXTXPORT;

typedef struct {
    BOOL  MediaPresent;      // TRUE/FALSE
    ULONG MediaType;         // DVCR standard, small, medium; VHS; VHS-C; unknown
    BOOL  RecordInhibit;     // TRUE/FALSE
} MEDIUM_INFO, *PMEDIUM_INFO;


typedef struct {
    ULONG Mode;              // LOAD MEDIUM, RECORD, PLAY or WIND
    ULONG State;             // Vary depend on mode (Table 4-8) 
} TRANSPORT_STATE, *PTRANSPORT_STATE;

typedef struct {
    KSPROPERTY Property;

    union {    
        ULONG      Capabilities;     // May need to expand on the existing structure
        ULONG      SignalMode;       // MPEG, D-VHS, Analog VHS etc.
        ULONG      LoadMedium;       // Eject, open tray, close tray
        MEDIUM_INFO MediumInfo;
        TRANSPORT_STATE XPrtState;

        struct {
          BYTE frame;        
          BYTE second;
          BYTE minute;
          BYTE hour;
        } Timecode;
        DWORD dwTimecode;       // hour:minute:second:frame
        DWORD dwAbsTrackNumber; // absolute track number


       //
       // Implemented for testing purpose
       // Will remove this later or will keep this for 
       // packet specific command.
       //
       struct {
           ULONG   PayloadSize;
           BYTE    Payload[512];  // This is only for testing sending AVC command from User mode.
       } RawAVC;

     } u;
     
} KSPROPERTY_EXTXPORT_S, *PKSPROPERTY_EXTXPORT_S;



//---------------------------------------------------------
// PROPSETID_TIMECODE
//---------------------------------------------------------
// This guid and interface is defined in strmif.h 
#define STATIC_PROPSETID_TIMECODE_READER\
    0x9B496CE1L, 0x811B, 0x11cf, 0x8C, 0x77, 0x00, 0xAA, 0x00, 0x6B, 0x68, 0x14
DEFINE_GUIDSTRUCT("9B496CE1-811B-11cf-8C77-00AA006B6814", PROPSETID_TIMECODE_READER);
#define PROPSETID_TIMECODE_READER DEFINE_GUIDNAMED(PROPSETID_TIMECODE_READER)


// KS properties and structure for this interface
typedef enum {
    KSPROPERTY_TIMECODE_READER,  // Timecode for the current medium position
    KSPROPERTY_ATN_READER,       // Absolute track number the current medium position
    KSPROPERTY_RTC_READER,       // Relative time counter for the current medium position

} KSPROPERTY_TIMECODE;


typedef struct {
    KSPROPERTY Property;

    TIMECODE_SAMPLE TimecodeSamp;
     
} KSPROPERTY_TIMECODE_S, *PKSPROPERTY_TIMECODE_S;



//---------------------------------------------------------
//  External Device Command event notification
//---------------------------------------------------------

#define STATIC_KSEVENTSETID_EXTDEV_Command\
    0x109c7988L, 0xb3cb, 0x11d2, 0xb4, 0x8e, 0x00, 0x60, 0x97, 0xb3, 0x39, 0x1b
DEFINE_GUIDSTRUCT("109c7988-b3cb-11d2-b48e-006097b3391b", KSEVENTSETID_EXTDEV_Command);
#define KSEVENTSETID_EXTDEV_Command DEFINE_GUIDNAMED(KSEVENTSETID_EXTDEV_Command)

typedef enum {
    KSEVENT_EXTDEV_COMMAND_NOTIFY_INTERIM_READY,
    KSEVENT_EXTDEV_COMMAND_CONTROL_INTERIM_READY,
    KSEVENT_EXTDEV_COMMAND_BUSRESET,
    KSEVENT_EXTDEV_TIMECODE_UPDATE,
    KSEVENT_EXTDEV_OPERATION_MODE_UPDATE,    // Notify mode of operation change (VCR,OFF,Camera)
    KSEVENT_EXTDEV_TRANSPORT_STATE_UPDATE,   // XPrt state change
    KSEVENT_EXTDEV_NOTIFY_REMOVAL,           // Notify device removal
    KSEVENT_EXTDEV_NOTIFY_MEDIUM_CHANGE,     // Notify medium (tape) is removed or added

} KSEVENT_DEVCMD;


#endif // __EDevCTrl__
