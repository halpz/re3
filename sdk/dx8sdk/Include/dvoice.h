/*==========================================================================;
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dpvoice.h
 *  Content:    DirectPlayVoice include file
 ***************************************************************************/

#ifndef __DVOICE__
#define __DVOICE__

#include <ole2.h>			// for DECLARE_INTERFACE and HRESULT
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include "dsound.h"

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 *
 * DirectPlayVoice CLSIDs
 *
 ****************************************************************************/


// {B9F3EB85-B781-4ac1-8D90-93A05EE37D7D}
DEFINE_GUID(CLSID_DirectPlayVoiceClient, 
0xb9f3eb85, 0xb781, 0x4ac1, 0x8d, 0x90, 0x93, 0xa0, 0x5e, 0xe3, 0x7d, 0x7d);

// {D3F5B8E6-9B78-4a4c-94EA-CA2397B663D3}
DEFINE_GUID(CLSID_DirectPlayVoiceServer, 
0xd3f5b8e6, 0x9b78, 0x4a4c, 0x94, 0xea, 0xca, 0x23, 0x97, 0xb6, 0x63, 0xd3);

// {0F0F094B-B01C-4091-A14D-DD0CD807711A}
DEFINE_GUID(CLSID_DirectPlayVoiceTest, 
0xf0f094b, 0xb01c, 0x4091, 0xa1, 0x4d, 0xdd, 0xc, 0xd8, 0x7, 0x71, 0x1a);

/****************************************************************************
 *
 * DirectPlayVoice Interface IIDs
 *
 ****************************************************************************/


// {1DFDC8EA-BCF7-41d6-B295-AB64B3B23306}
DEFINE_GUID(IID_IDirectPlayVoiceClient, 
0x1dfdc8ea, 0xbcf7, 0x41d6, 0xb2, 0x95, 0xab, 0x64, 0xb3, 0xb2, 0x33, 0x6);

// {FAA1C173-0468-43b6-8A2A-EA8A4F2076C9}
DEFINE_GUID(IID_IDirectPlayVoiceServer, 
0xfaa1c173, 0x468, 0x43b6, 0x8a, 0x2a, 0xea, 0x8a, 0x4f, 0x20, 0x76, 0xc9);

// {D26AF734-208B-41da-8224-E0CE79810BE1}
DEFINE_GUID(IID_IDirectPlayVoiceTest,
0xd26af734, 0x208b, 0x41da, 0x82, 0x24, 0xe0, 0xce, 0x79, 0x81, 0xb, 0xe1);

/****************************************************************************
 *
 * DirectPlayVoice Compression Type GUIDs
 *
 ****************************************************************************/

// MS-ADPCM 32.8 kbit/s
//
// {699B52C1-A885-46a8-A308-97172419ADC7}
DEFINE_GUID(DPVCTGUID_ADPCM,
0x699b52c1, 0xa885, 0x46a8, 0xa3, 0x8, 0x97, 0x17, 0x24, 0x19, 0xad, 0xc7);

// Microsoft GSM 6.10 13 kbit/s
//
// {24768C60-5A0D-11d3-9BE4-525400D985E7}
DEFINE_GUID(DPVCTGUID_GSM,
0x24768c60, 0x5a0d, 0x11d3, 0x9b, 0xe4, 0x52, 0x54, 0x0, 0xd9, 0x85, 0xe7);

// MS-PCM 64 kbit/s
// 
// {8DE12FD4-7CB3-48ce-A7E8-9C47A22E8AC5}
DEFINE_GUID(DPVCTGUID_NONE,
0x8de12fd4, 0x7cb3, 0x48ce, 0xa7, 0xe8, 0x9c, 0x47, 0xa2, 0x2e, 0x8a, 0xc5);

// Voxware SC03 3.2kbit/s
//
// {7D82A29B-2242-4f82-8F39-5D1153DF3E41}
DEFINE_GUID(DPVCTGUID_SC03,
0x7d82a29b, 0x2242, 0x4f82, 0x8f, 0x39, 0x5d, 0x11, 0x53, 0xdf, 0x3e, 0x41);

// Voxware SC06 6.4kbit/s
//
// {53DEF900-7168-4633-B47F-D143916A13C7}
DEFINE_GUID(DPVCTGUID_SC06,
0x53def900, 0x7168, 0x4633, 0xb4, 0x7f, 0xd1, 0x43, 0x91, 0x6a, 0x13, 0xc7);

// TrueSpeech(TM) 8.6 kbit/s
//
// {D7954361-5A0B-11d3-9BE4-525400D985E7}
DEFINE_GUID(DPVCTGUID_TRUESPEECH,
0xd7954361, 0x5a0b, 0x11d3, 0x9b, 0xe4, 0x52, 0x54, 0x0, 0xd9, 0x85, 0xe7);

// Voxware VR12 1.4kbit/s
//
// {FE44A9FE-8ED4-48bf-9D66-1B1ADFF9FF6D}
DEFINE_GUID(DPVCTGUID_VR12,
0xfe44a9fe, 0x8ed4, 0x48bf, 0x9d, 0x66, 0x1b, 0x1a, 0xdf, 0xf9, 0xff, 0x6d);

// Define the default compression type
#define DPVCTGUID_DEFAULT	DPVCTGUID_SC03

/****************************************************************************
 *
 * DirectPlayVoice Interface Pointer definitions
 *
 ****************************************************************************/

typedef struct IDirectPlayVoiceClient FAR *LPDIRECTPLAYVOICECLIENT, *PDIRECTPLAYVOICECLIENT;
typedef struct IDirectPlayVoiceServer FAR *LPDIRECTPLAYVOICESERVER, *PDIRECTPLAYVOICESERVER;
typedef struct IDirectPlayVoiceTest FAR *LPDIRECTPLAYVOICETEST, *PDIRECTPLAYVOICETEST;

/****************************************************************************
 *
 * DirectPlayVoice Callback Functions
 *
 ****************************************************************************/
typedef HRESULT (FAR PASCAL *PDVMESSAGEHANDLER)(
    PVOID   pvUserContext,
    DWORD   dwMessageType,
    LPVOID  lpMessage
);

typedef PDVMESSAGEHANDLER LPDVMESSAGEHANDLER;

/****************************************************************************
 *
 * DirectPlayVoice Datatypes (Non-Structure / Non-Message)
 *
 ****************************************************************************/

typedef DWORD DVID, *LPDVID, *PDVID;

/****************************************************************************
 *
 * DirectPlayVoice Message Types
 *
 ****************************************************************************/

#define DVMSGID_BASE                        0x0000

#define DVMSGID_MINBASE                     (DVMSGID_CREATEVOICEPLAYER)
#define DVMSGID_CREATEVOICEPLAYER           (DVMSGID_BASE+0x0001)
#define DVMSGID_DELETEVOICEPLAYER           (DVMSGID_BASE+0x0002)
#define DVMSGID_SESSIONLOST                 (DVMSGID_BASE+0x0003)
#define DVMSGID_PLAYERVOICESTART            (DVMSGID_BASE+0x0004)
#define DVMSGID_PLAYERVOICESTOP             (DVMSGID_BASE+0x0005)
#define DVMSGID_RECORDSTART                 (DVMSGID_BASE+0x0006)
#define DVMSGID_RECORDSTOP                  (DVMSGID_BASE+0x0007)
#define DVMSGID_CONNECTRESULT               (DVMSGID_BASE+0x0008)
#define DVMSGID_DISCONNECTRESULT            (DVMSGID_BASE+0x0009)
#define DVMSGID_INPUTLEVEL                  (DVMSGID_BASE+0x000A)
#define DVMSGID_OUTPUTLEVEL                 (DVMSGID_BASE+0x000B)
#define DVMSGID_HOSTMIGRATED                (DVMSGID_BASE+0x000C)
#define DVMSGID_SETTARGETS                  (DVMSGID_BASE+0x000D)
#define DVMSGID_PLAYEROUTPUTLEVEL           (DVMSGID_BASE+0x000E)
#define DVMSGID_LOSTFOCUS                   (DVMSGID_BASE+0x0010)
#define DVMSGID_GAINFOCUS                   (DVMSGID_BASE+0x0011)
#define DVMSGID_LOCALHOSTSETUP				(DVMSGID_BASE+0x0012)
#define DVMSGID_MAXBASE                     (DVMSGID_LOCALHOSTSETUP)

/****************************************************************************
 *
 * DirectPlayVoice Constants
 *
 ****************************************************************************/

//
// Buffer Aggresiveness Value Ranges
//
#define DVBUFFERAGGRESSIVENESS_MIN          0x00000001
#define DVBUFFERAGGRESSIVENESS_MAX          0x00000064
#define DVBUFFERAGGRESSIVENESS_DEFAULT      0x00000000

// 
// Buffer Quality Value Ranges
//
#define DVBUFFERQUALITY_MIN                 0x00000001
#define DVBUFFERQUALITY_MAX                 0x00000064
#define DVBUFFERQUALITY_DEFAULT             0x00000000

#define DVID_SYS                0

//
// Used to identify the session host in client/server
//
#define DVID_SERVERPLAYER       1

//
// Used to target all players
//
#define DVID_ALLPLAYERS         0

//
// Used to identify the main buffer
//
#define DVID_REMAINING          0xFFFFFFFF

// 
// Input level range
//
#define DVINPUTLEVEL_MIN                    0x00000000
#define DVINPUTLEVEL_MAX                    0x00000063	// 99 decimal

#define DVNOTIFYPERIOD_MINPERIOD            20


#define DVPLAYBACKVOLUME_DEFAULT            DSBVOLUME_MAX

#define DVRECORDVOLUME_LAST                 0x00000001


//
// Use the default value
//
#define DVTHRESHOLD_DEFAULT               0xFFFFFFFF

//
// Threshold Ranges
//
#define DVTHRESHOLD_MIN                   0x00000000
#define DVTHRESHOLD_MAX                   0x00000063	// 99 decimal

//
// Threshold field is not used 
//
#define DVTHRESHOLD_UNUSED                0xFFFFFFFE

//
// Session Types
//
#define DVSESSIONTYPE_PEER                  0x00000001
#define DVSESSIONTYPE_MIXING                0x00000002
#define DVSESSIONTYPE_FORWARDING            0x00000003
#define DVSESSIONTYPE_ECHO                  0x00000004

/****************************************************************************
 *
 * DirectPlayVoice Flags
 *
 ****************************************************************************/


// 
// Enable automatic adjustment of the recording volume
//
#define DVCLIENTCONFIG_AUTORECORDVOLUME     0x00000008

//
// Enable automatic voice activation
//
#define DVCLIENTCONFIG_AUTOVOICEACTIVATED   0x00000020

// 
// Enable echo suppression
//
#define DVCLIENTCONFIG_ECHOSUPPRESSION      0x08000000

// 
// Voice Activation manual mode
//
#define DVCLIENTCONFIG_MANUALVOICEACTIVATED 0x00000004

// 
// Only playback voices that have buffers created for them
//
#define DVCLIENTCONFIG_MUTEGLOBAL           0x00000010

// 
// Mute the playback
//
#define DVCLIENTCONFIG_PLAYBACKMUTE         0x00000002

//
// Mute the recording 
//
#define DVCLIENTCONFIG_RECORDMUTE           0x00000001

// 
// Complete the operation before returning
//
#define DVFLAGS_SYNC                        0x00000001

// 
// Just check to see if wizard has been run, and if so what it's results were
//
#define DVFLAGS_QUERYONLY                   0x00000002

//
// Shutdown the voice session without migrating the host
//
#define DVFLAGS_NOHOSTMIGRATE               0x00000008

// 
// Allow the back button to be enabled in the wizard
//
#define DVFLAGS_ALLOWBACK                   0x00000010

//
// Disable host migration in the voice session
//
#define DVSESSION_NOHOSTMIGRATION           0x00000001

// 
// Server controlled targetting
//
#define DVSESSION_SERVERCONTROLTARGET       0x00000002

//
// Use DirectSound Normal Mode instead of priority 
//
#define DVSOUNDCONFIG_NORMALMODE            0x00000001

//
// Automatically select the microphone
//
#define DVSOUNDCONFIG_AUTOSELECT            0x00000002

// 
// Run in half duplex mode
//
#define DVSOUNDCONFIG_HALFDUPLEX            0x00000004

// 
// No volume controls are available for the recording device
//
#define DVSOUNDCONFIG_NORECVOLAVAILABLE     0x00000010

// 
// Disable capture sharing
//
#define DVSOUNDCONFIG_NOFOCUS               0x20000000

// 
// Set system conversion quality to high
//
#define DVSOUNDCONFIG_SETCONVERSIONQUALITY	0x00000008

//
// Enable strict focus mode
// 
#define DVSOUNDCONFIG_STRICTFOCUS           0x40000000

//
// Player is in half duplex mode
//
#define DVPLAYERCAPS_HALFDUPLEX             0x00000001

// 
// Specifies that player is the local player
//
#define DVPLAYERCAPS_LOCAL                  0x00000002

/****************************************************************************
 *
 * DirectPlayVoice Structures (Non-Message)
 *
 ****************************************************************************/


//
// DirectPlayVoice Caps
// (GetCaps / SetCaps)
//
typedef struct
{
    DWORD   dwSize;                 // Size of this structure
    DWORD   dwFlags;                // Caps flags
} DVCAPS, *LPDVCAPS, *PDVCAPS;

//
// DirectPlayVoice Client Configuration
// (Connect / GetClientConfig)
//
typedef struct
{
    DWORD   dwSize;                 // Size of this structure
    DWORD   dwFlags;                // Flags for client config (DVCLIENTCONFIG_...)
    LONG    lRecordVolume;          // Recording volume 
    LONG    lPlaybackVolume;        // Playback volume
    DWORD   dwThreshold;          // Voice Activation Threshold
    DWORD   dwBufferQuality;        // Buffer quality
    DWORD   dwBufferAggressiveness; // Buffer aggressiveness
    DWORD   dwNotifyPeriod;         // Period of notification messages (ms)
} DVCLIENTCONFIG, *LPDVCLIENTCONFIG, *PDVCLIENTCONFIG;

//
// DirectPlayVoice Compression Type Information
// (GetCompressionTypes)
//
typedef struct
{
    DWORD   dwSize;                 // Size of this structure
    GUID    guidType;               // GUID that identifies this compression type
    LPWSTR  lpszName;               // String name of this compression type
    LPWSTR  lpszDescription;        // Description for this compression type
    DWORD   dwFlags;                // Flags for this compression type
    DWORD   dwMaxBitsPerSecond;		// Maximum # of bit/s this compression type uses
} DVCOMPRESSIONINFO, *LPDVCOMPRESSIONINFO, *PDVCOMPRESSIONINFO;

//
// DirectPlayVoice Session Description
// (Host / GetSessionDesc)
//
typedef struct
{
    DWORD   dwSize;                 // Size of this structure
    DWORD   dwFlags;                // Session flags (DVSESSION_...)
    DWORD   dwSessionType;          // Session type (DVSESSIONTYPE_...)
    GUID    guidCT;                 // Compression Type to use
    DWORD   dwBufferQuality;        // Buffer quality
    DWORD   dwBufferAggressiveness; // Buffer aggresiveness
} DVSESSIONDESC, *LPDVSESSIONDESC, *PDVSESSIONDESC;

// 
// DirectPlayVoice Client Sound Device Configuration
// (Connect / GetSoundDeviceConfig)
//
typedef struct
{
    DWORD                   dwSize;                 // Size of this structure
    DWORD                   dwFlags;                // Flags for sound config (DVSOUNDCONFIG_...)
    GUID                    guidPlaybackDevice;     // GUID of the playback device to use
    LPDIRECTSOUND           lpdsPlaybackDevice;     // DirectSound Object to use (optional)
    GUID                    guidCaptureDevice;      // GUID of the capture device to use
    LPDIRECTSOUNDCAPTURE    lpdsCaptureDevice;      // DirectSoundCapture Object to use (optional)
    HWND                    hwndAppWindow;          // HWND of your application's top-level window
    LPDIRECTSOUNDBUFFER     lpdsMainBuffer;         // DirectSoundBuffer to use for playback (optional)
    DWORD                   dwMainBufferFlags;      // Flags to pass to Play() on the main buffer
    DWORD                   dwMainBufferPriority;   // Priority to set when calling Play() on the main buffer
} DVSOUNDDEVICECONFIG, *LPDVSOUNDDEVICECONFIG, *PDVSOUNDDEVICECONFIG;

/****************************************************************************
 *
 * DirectPlayVoice message handler call back structures
 *
 ****************************************************************************/

//
// Result of the Connect() call.  (If it wasn't called Async)
// (DVMSGID_CONNECTRESULT)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    HRESULT hrResult;                       // Result of the Connect() call
} DVMSG_CONNECTRESULT, *LPDVMSG_CONNECTRESULT, *PDVMSG_CONNECTRESULT;

//
// A new player has entered the voice session
// (DVMSGID_CREATEVOICEPLAYER)
// 
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DVID    dvidPlayer;                     // DVID of the player who joined
    DWORD   dwFlags;                        // Player flags (DVPLAYERCAPS_...)
    PVOID	pvPlayerContext;                // Context value for this player (user set)
} DVMSG_CREATEVOICEPLAYER, *LPDVMSG_CREATEVOICEPLAYER, *PDVMSG_CREATEVOICEPLAYER;

//
// A player has left the voice session
// (DVMSGID_DELETEVOICEPLAYER)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DVID    dvidPlayer;                     // DVID of the player who left
    PVOID	pvPlayerContext;                // Context value for the player
} DVMSG_DELETEVOICEPLAYER, *LPDVMSG_DELETEVOICEPLAYER, *PDVMSG_DELETEVOICEPLAYER;

//
// Result of the Disconnect() call.  (If it wasn't called Async)
// (DVMSGID_DISCONNECTRESULT)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    HRESULT hrResult;                       // Result of the Disconnect() call
} DVMSG_DISCONNECTRESULT, *LPDVMSG_DISCONNECTRESULT, *PDVMSG_DISCONNECTRESULT;

// 
// The voice session host has migrated.
// (DVMSGID_HOSTMIGRATED) 
//
typedef struct
{
    DWORD                   dwSize;         // Size of this structure
    DVID                    dvidNewHostID;  // DVID of the player who is now the host
    LPDIRECTPLAYVOICESERVER pdvServerInterface;
                                            // Pointer to the new host object (if local player is now host)
} DVMSG_HOSTMIGRATED, *LPDVMSG_HOSTMIGRATED, *PDVMSG_HOSTMIGRATED;

//
// The current input level / recording volume on the local machine
// (DVMSGID_INPUTLEVEL)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DWORD   dwPeakLevel;                    // Current peak level of the audio
    LONG    lRecordVolume;                  // Current recording volume
    PVOID	pvLocalPlayerContext;           // Context value for the local player
} DVMSG_INPUTLEVEL, *LPDVMSG_INPUTLEVEL, *PDVMSG_INPUTLEVEL;

//
// The local client is about to become the new host
// (DVMSGID_LOCALHOSTSETUP)
//
typedef struct
{
	DWORD				dwSize;             // Size of this structure
	PVOID				pvContext;			// Context value to be passed to Initialize() of new host object
	PDVMESSAGEHANDLER	pMessageHandler;	// Message handler to be used by new host object
} DVMSG_LOCALHOSTSETUP, *LPDVMSG_LOCALHOSTSETUP, *PDVMSG_LOCALHOSTSETUP;

//
// The current output level for the combined output of all incoming streams.
// (DVMSGID_OUTPUTLEVEL)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DWORD   dwPeakLevel;                    // Current peak level of the output
    LONG    lOutputVolume;                  // Current playback volume
    PVOID	pvLocalPlayerContext;           // Context value for the local player
} DVMSG_OUTPUTLEVEL, *LPDVMSG_OUTPUTLEVEL, *PDVMSG_OUTPUTLEVEL;

//
// The current peak level of an individual player's incoming audio stream as it is
// being played back.
// (DVMSGID_PLAYEROUTPUTLEVEL)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DVID    dvidSourcePlayerID;                   // DVID of the player
    DWORD   dwPeakLevel;                    // Peak level of the player's stream
    PVOID	pvPlayerContext;                // Context value for the player
} DVMSG_PLAYEROUTPUTLEVEL, *LPDVMSG_PLAYEROUTPUTLEVEL, *PDVMSG_PLAYEROUTPUTLEVEL;

// 
// An audio stream from the specified player has started playing back on the local client.
// (DVMSGID_PLAYERVOICESTART).
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DVID    dvidSourcePlayerID;             // DVID of the Player 
    PVOID	pvPlayerContext;                // Context value for this player
} DVMSG_PLAYERVOICESTART, *LPDVMSG_PLAYERVOICESTART, *PDVMSG_PLAYERVOICESTART;

//
// The audio stream from the specified player has stopped playing back on the local client.
// (DVMSGID_PLAYERVOICESTOP)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DVID    dvidSourcePlayerID;             // DVID of the player
    PVOID	pvPlayerContext;                // Context value for this player
} DVMSG_PLAYERVOICESTOP, *LPDVMSG_PLAYERVOICESTOP, *PDVMSG_PLAYERVOICESTOP;

// 
// Transmission has started on the local machine
// (DVMSGID_RECORDSTART)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DWORD   dwPeakLevel;                    // Peak level that caused transmission to start
    PVOID	pvLocalPlayerContext;           // Context value for the local player
} DVMSG_RECORDSTART, *LPDVMSG_RECORDSTART, *PDVMSG_RECORDSTART;

// 
// Transmission has stopped on the local machine
// (DVMSGID_RECORDSTOP)
// 
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DWORD   dwPeakLevel;                    // Peak level that caused transmission to stop
    PVOID	pvLocalPlayerContext;           // Context value for the local player
} DVMSG_RECORDSTOP, *LPDVMSG_RECORDSTOP, *PDVMSG_RECORDSTOP;

// 
// The voice session has been lost
// (DVMSGID_SESSIONLOST)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    HRESULT hrResult;	                    // Reason the session was disconnected
} DVMSG_SESSIONLOST, *LPDVMSG_SESSIONLOST, *PDVMSG_SESSIONLOST;

//
// The target list has been updated for the local client
// (DVMSGID_SETTARGETS)
//
typedef struct
{
    DWORD   dwSize;                         // Size of this structure
    DWORD   dwNumTargets;                   // # of targets 
    PDVID   pdvidTargets;                   // An array of DVIDs specifying the current targets
} DVMSG_SETTARGETS, *LPDVMSG_SETTARGETS, *PDVMSG_SETTARGETS;


/****************************************************************************
 *
 * DirectPlayVoice Functions
 *
 ****************************************************************************/

/*
 * 
 * This function is no longer supported.  It is recommended that CoCreateInstance be used to create 
 * DirectPlay voice objects.  
 *
 * extern HRESULT WINAPI DirectPlayVoiceCreate( const GUID * pcIID, void **ppvInterface, IUnknown *pUnknown); 
 *
 */

/****************************************************************************
 *
 * DirectPlay8 Application Interfaces
 *
 ****************************************************************************/

#undef INTERFACE
#define INTERFACE IDirectPlayVoiceClient
DECLARE_INTERFACE_( IDirectPlayVoiceClient, IUnknown )
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, PVOID *ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirectPlayVoiceClient methods ***/
    STDMETHOD_(HRESULT, Initialize)   (THIS_ LPUNKNOWN, PDVMESSAGEHANDLER, PVOID, PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, Connect)      (THIS_ PDVSOUNDDEVICECONFIG, PDVCLIENTCONFIG, DWORD ) PURE;
    STDMETHOD_(HRESULT, Disconnect)   (THIS_ DWORD ) PURE;
    STDMETHOD_(HRESULT, GetSessionDesc)(THIS_ PDVSESSIONDESC ) PURE;
    STDMETHOD_(HRESULT, GetClientConfig)(THIS_ PDVCLIENTCONFIG ) PURE;
    STDMETHOD_(HRESULT, SetClientConfig)(THIS_ PDVCLIENTCONFIG ) PURE;
    STDMETHOD_(HRESULT, GetCaps) 		(THIS_ PDVCAPS ) PURE;
    STDMETHOD_(HRESULT, GetCompressionTypes)( THIS_ PVOID, PDWORD, PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, SetTransmitTargets)( THIS_ PDVID, DWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, GetTransmitTargets)( THIS_ PDVID, PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, Create3DSoundBuffer)( THIS_ DVID, LPDIRECTSOUNDBUFFER, DWORD, DWORD, LPDIRECTSOUND3DBUFFER * ) PURE;
    STDMETHOD_(HRESULT, Delete3DSoundBuffer)( THIS_ DVID, LPDIRECTSOUND3DBUFFER * ) PURE;
    STDMETHOD_(HRESULT, SetNotifyMask)( THIS_ PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, GetSoundDeviceConfig)( THIS_ PDVSOUNDDEVICECONFIG, PDWORD ) PURE;
};


#undef INTERFACE
#define INTERFACE IDirectPlayVoiceServer
DECLARE_INTERFACE_( IDirectPlayVoiceServer, IUnknown )
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;
    /*** IDirectPlayVoiceServer methods ***/
    STDMETHOD_(HRESULT, Initialize)   (THIS_ LPUNKNOWN, PDVMESSAGEHANDLER, PVOID, LPDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, StartSession)  (THIS_ PDVSESSIONDESC, DWORD ) PURE;
    STDMETHOD_(HRESULT, StopSession)   (THIS_ DWORD ) PURE;
    STDMETHOD_(HRESULT, GetSessionDesc)(THIS_ PDVSESSIONDESC ) PURE;
    STDMETHOD_(HRESULT, SetSessionDesc)(THIS_ PDVSESSIONDESC ) PURE;
    STDMETHOD_(HRESULT, GetCaps) 		(THIS_ PDVCAPS ) PURE;
    STDMETHOD_(HRESULT, GetCompressionTypes)( THIS_ PVOID, PDWORD, PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, SetTransmitTargets)( THIS_ DVID, PDVID, DWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, GetTransmitTargets)( THIS_ DVID, PDVID, PDWORD, DWORD ) PURE;
    STDMETHOD_(HRESULT, SetNotifyMask)( THIS_ PDWORD, DWORD ) PURE;
};

#undef INTERFACE
#define INTERFACE IDirectPlayVoiceTest
DECLARE_INTERFACE_( IDirectPlayVoiceTest, IUnknown )
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, PVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;
    /*** IDirectPlayVoiceTest methods ***/
    STDMETHOD_(HRESULT, CheckAudioSetup) (THIS_ const GUID *,  const GUID * , HWND, DWORD ) PURE;
};

#if !defined(__cplusplus) || defined(CINTERFACE)

#define IDirectPlayVoiceClient_QueryInterface(p,a,b)        (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlayVoiceClient_AddRef(p)                    (p)->lpVtbl->AddRef(p)
#define IDirectPlayVoiceClient_Release(p)                   (p)->lpVtbl->Release(p)

#define IDirectPlayVoiceClient_Initialize(p,a,b,c,d,e)      (p)->lpVtbl->Initialize(p,a,b,c,d,e)
#define IDirectPlayVoiceClient_Connect(p,a,b,c)             (p)->lpVtbl->Connect(p,a,b,c)
#define IDirectPlayVoiceClient_Disconnect(p,a)              (p)->lpVtbl->Disconnect(p,a)
#define IDirectPlayVoiceClient_GetSessionDesc(p,a)          (p)->lpVtbl->GetSessionDesc(p,a)
#define IDirectPlayVoiceClient_GetClientConfig(p,a)         (p)->lpVtbl->GetClientConfig(p,a)
#define IDirectPlayVoiceClient_SetClientConfig(p,a)         (p)->lpVtbl->SetClientConfig(p,a)
#define IDirectPlayVoiceClient_GetCaps(p,a)                 (p)->lpVtbl->GetCaps(p,a)
#define IDirectPlayVoiceClient_GetCompressionTypes(p,a,b,c,d) (p)->lpVtbl->GetCompressionTypes(p,a,b,c,d)
#define IDirectPlayVoiceClient_SetTransmitTargets(p,a,b,c)  (p)->lpVtbl->SetTransmitTargets(p,a,b,c)
#define IDirectPlayVoiceClient_GetTransmitTargets(p,a,b,c)  (p)->lpVtbl->GetTransmitTargets(p,a,b,c)
#define IDirectPlayVoiceClient_Create3DSoundBuffer(p,a,b,c,d,e)   (p)->lpVtbl->Create3DSoundBuffer(p,a,b,c,d,e)
#define IDirectPlayVoiceClient_Delete3DSoundBuffer(p,a,b)   (p)->lpVtbl->Delete3DSoundBuffer(p,a,b)
#define IDirectPlayVoiceClient_SetNotifyMask(p,a,b)         (p)->lpVtbl->SetNotifyMask(p,a,b)
#define IDirectPlayVoiceClient_GetSoundDeviceConfig(p,a,b)  (p)->lpVtbl->GetSoundDeviceConfig(p,a,b)

#define IDirectPlayVoiceServer_QueryInterface(p,a,b)        (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlayVoiceServer_AddRef(p)                    (p)->lpVtbl->AddRef(p)
#define IDirectPlayVoiceServer_Release(p)                   (p)->lpVtbl->Release(p)

#define IDirectPlayVoiceServer_Initialize(p,a,b,c,d,e)      (p)->lpVtbl->Initialize(p,a,b,c,d,e)
#define IDirectPlayVoiceServer_StartSession(p,a,b)          (p)->lpVtbl->StartSession(p,a,b)
#define IDirectPlayVoiceServer_StopSession(p,a)             (p)->lpVtbl->StopSession(p,a)
#define IDirectPlayVoiceServer_GetSessionDesc(p,a)          (p)->lpVtbl->GetSessionDesc(p,a)
#define IDirectPlayVoiceServer_SetSessionDesc(p,a)          (p)->lpVtbl->SetSessionDesc(p,a)
#define IDirectPlayVoiceServer_GetCaps(p,a)                 (p)->lpVtbl->GetCaps(p,a)
#define IDirectPlayVoiceServer_GetCompressionTypes(p,a,b,c,d) (p)->lpVtbl->GetCompressionTypes(p,a,b,c,d)
#define IDirectPlayVoiceServer_SetTransmitTargets(p,a,b,c,d)	(p)->lpVtbl->SetTransmitTargets(p,a,b,c,d)
#define IDirectPlayVoiceServer_GetTransmitTargets(p,a,b,c,d)	(p)->lpVtbl->GetTransmitTargets(p,a,b,c,d)
#define IDirectPlayVoiceServer_SetNotifyMask(p,a,b)         (p)->lpVtbl->SetNotifyMask(p,a,b)
#define IDirectPlayVoiceTest_QueryInterface(p,a,b)          (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlayVoiceTest_AddRef(p)                      (p)->lpVtbl->AddRef(p)
#define IDirectPlayVoiceTest_Release(p)                	    (p)->lpVtbl->Release(p)
#define IDirectPlayVoiceTest_CheckAudioSetup(p,a,b,c,d)     (p)->lpVtbl->CheckAudioSetup(p,a,b,c,d)


#else /* C++ */

#define IDirectPlayVoiceClient_QueryInterface(p,a,b)        (p)->QueryInterface(a,b)
#define IDirectPlayVoiceClient_AddRef(p)                    (p)->AddRef()
#define IDirectPlayVoiceClient_Release(p)               	(p)->Release()

#define IDirectPlayVoiceClient_Initialize(p,a,b,c,d,e)      (p)->Initialize(a,b,c,d,e)
#define IDirectPlayVoiceClient_Connect(p,a,b,c)             (p)->Connect(a,b,c)
#define IDirectPlayVoiceClient_Disconnect(p,a)              (p)->Disconnect(a)
#define IDirectPlayVoiceClient_GetSessionDesc(p,a)          (p)->GetSessionDesc(a)
#define IDirectPlayVoiceClient_GetClientConfig(p,a)         (p)->GetClientConfig(a)
#define IDirectPlayVoiceClient_SetClientConfig(p,a)         (p)->SetClientConfig(a)
#define IDirectPlayVoiceClient_GetCaps(p,a)                 (p)->GetCaps(a)
#define IDirectPlayVoiceClient_GetCompressionTypes(p,a,b,c,d) (p)->GetCompressionTypes(a,b,c,d)
#define IDirectPlayVoiceClient_SetTransmitTargets(p,a,b,c)  (p)->SetTransmitTargets(a,b,c)
#define IDirectPlayVoiceClient_GetTransmitTargets(p,a,b,c)  (p)->GetTransmitTargets(a,b,c)
#define IDirectPlayVoiceClient_Create3DSoundBuffer(p,a,b,c,d,e)   (p)->Create3DSoundBuffer(a,b,c,d,e)
#define IDirectPlayVoiceClient_Delete3DSoundBuffer(p,a,b)   (p)->Delete3DSoundBuffer(a,b)
#define IDirectPlayVoiceClient_SetNotifyMask(p,a,b)         (p)->SetNotifyMask(a,b)
#define IDirectPlayVoiceClient_GetSoundDeviceConfig(p,a,b)    (p)->GetSoundDeviceConfig(a,b)

#define IDirectPlayVoiceServer_QueryInterface(p,a,b)        (p)->QueryInterface(a,b)
#define IDirectPlayVoiceServer_AddRef(p)                    (p)->AddRef()
#define IDirectPlayVoiceServer_Release(p)                   (p)->Release()

#define IDirectPlayVoiceServer_Initialize(p,a,b,c,d,e)      (p)->Initialize(a,b,c,d,e)
#define IDirectPlayVoiceServer_StartSession(p,a,b)          (p)->StartSession(a,b)
#define IDirectPlayVoiceServer_StopSession(p,a)             (p)->StopSession(a)
#define IDirectPlayVoiceServer_GetSessionDesc(p,a)            (p)->GetSessionDesc(a)
#define IDirectPlayVoiceServer_SetSessionDesc(p,a)            (p)->SetSessionDesc(a)
#define IDirectPlayVoiceServer_GetCaps(p,a)                 (p)->GetCaps(a)
#define IDirectPlayVoiceServer_GetCompressionTypes(p,a,b,c,d) (p)->GetCompressionTypes(a,b,c,d)
#define IDirectPlayVoiceServer_SetTransmitTargets(p,a,b,c,d) (p)->SetTransmitTargets(a,b,c,d)
#define IDirectPlayVoiceServer_GetTransmitTargets(p,a,b,c,d) (p)->GetTransmitTargets(a,b,c,d)
#define IDirectPlayVoiceServer_SetNotifyMask(p,a,b)         (p)->SetNotifyMask(a,b)

#define IDirectPlayVoiceTest_QueryInterface(p,a,b)          (p)->QueryInterface(a,b)
#define IDirectPlayVoiceTest_AddRef(p)                      (p)->AddRef()
#define IDirectPlayVoiceTest_Release(p)                     (p)->Release()
#define IDirectPlayVoiceTest_CheckAudioSetup(p,a,b,c,d)     (p)->CheckAudioSetup(a,b,c,d)


#endif


/****************************************************************************
 *
 * DIRECTPLAYVOICE ERRORS
 *
 * Errors are represented by negative values and cannot be combined.
 *
 ****************************************************************************/

#define _FACDPV  0x15
#define MAKE_DVHRESULT( code )          MAKE_HRESULT( 1, _FACDPV, code )

#define DV_OK                           S_OK
#define DV_FULLDUPLEX                   MAKE_HRESULT( 0, _FACDPV,  0x0005 )
#define DV_HALFDUPLEX                   MAKE_HRESULT( 0, _FACDPV,  0x000A )
#define DV_PENDING						MAKE_HRESULT( 0, _FACDPV,  0x0010 )

#define DVERR_BUFFERTOOSMALL            MAKE_DVHRESULT(  0x001E )
#define DVERR_EXCEPTION                 MAKE_DVHRESULT(  0x004A )
#define DVERR_GENERIC                   E_FAIL
#define DVERR_INVALIDFLAGS              MAKE_DVHRESULT( 0x0078 )
#define DVERR_INVALIDOBJECT             MAKE_DVHRESULT( 0x0082 )
#define DVERR_INVALIDPARAM              E_INVALIDARG
#define DVERR_INVALIDPLAYER             MAKE_DVHRESULT( 0x0087 )
#define DVERR_INVALIDGROUP              MAKE_DVHRESULT( 0x0091 )
#define DVERR_INVALIDHANDLE             MAKE_DVHRESULT( 0x0096 )
#define DVERR_OUTOFMEMORY               E_OUTOFMEMORY
#define DVERR_PENDING                   DV_PENDING
#define DVERR_NOTSUPPORTED              E_NOTIMPL
#define DVERR_NOINTERFACE               E_NOINTERFACE
#define DVERR_SESSIONLOST               MAKE_DVHRESULT( 0x012C )
#define DVERR_NOVOICESESSION            MAKE_DVHRESULT( 0x012E )
#define DVERR_CONNECTIONLOST            MAKE_DVHRESULT( 0x0168 )
#define DVERR_NOTINITIALIZED            MAKE_DVHRESULT( 0x0169 )
#define DVERR_CONNECTED                 MAKE_DVHRESULT( 0x016A )
#define DVERR_NOTCONNECTED              MAKE_DVHRESULT( 0x016B )
#define DVERR_CONNECTABORTING           MAKE_DVHRESULT( 0x016E )
#define DVERR_NOTALLOWED                MAKE_DVHRESULT( 0x016F )
#define DVERR_INVALIDTARGET             MAKE_DVHRESULT( 0x0170 )
#define DVERR_TRANSPORTNOTHOST          MAKE_DVHRESULT( 0x0171 )
#define DVERR_COMPRESSIONNOTSUPPORTED   MAKE_DVHRESULT( 0x0172 )
#define DVERR_ALREADYPENDING            MAKE_DVHRESULT( 0x0173 )
#define DVERR_SOUNDINITFAILURE          MAKE_DVHRESULT( 0x0174 )
#define DVERR_TIMEOUT                   MAKE_DVHRESULT( 0x0175 )
#define DVERR_CONNECTABORTED            MAKE_DVHRESULT( 0x0176 )
#define DVERR_NO3DSOUND                 MAKE_DVHRESULT( 0x0177 )
#define DVERR_ALREADYBUFFERED	        MAKE_DVHRESULT( 0x0178 )
#define DVERR_NOTBUFFERED               MAKE_DVHRESULT( 0x0179 )
#define DVERR_HOSTING                   MAKE_DVHRESULT( 0x017A )
#define DVERR_NOTHOSTING                MAKE_DVHRESULT( 0x017B )
#define DVERR_INVALIDDEVICE             MAKE_DVHRESULT( 0x017C )
#define DVERR_RECORDSYSTEMERROR         MAKE_DVHRESULT( 0x017D )
#define DVERR_PLAYBACKSYSTEMERROR       MAKE_DVHRESULT( 0x017E )
#define DVERR_SENDERROR                 MAKE_DVHRESULT( 0x017F )
#define DVERR_USERCANCEL                MAKE_DVHRESULT( 0x0180 )
#define DVERR_RUNSETUP                  MAKE_DVHRESULT( 0x0183 )
#define DVERR_INCOMPATIBLEVERSION       MAKE_DVHRESULT( 0x0184 )
#define DVERR_INITIALIZED               MAKE_DVHRESULT( 0x0187 )
#define DVERR_INVALIDPOINTER            E_POINTER
#define DVERR_NOTRANSPORT               MAKE_DVHRESULT( 0x0188 )
#define DVERR_NOCALLBACK                MAKE_DVHRESULT( 0x0189 )
#define DVERR_TRANSPORTNOTINIT          MAKE_DVHRESULT( 0x018A )
#define DVERR_TRANSPORTNOSESSION        MAKE_DVHRESULT( 0x018B )
#define DVERR_TRANSPORTNOPLAYER         MAKE_DVHRESULT( 0x018C )
#define DVERR_USERBACK                  MAKE_DVHRESULT( 0x018D )
#define DVERR_NORECVOLAVAILABLE         MAKE_DVHRESULT( 0x018E )
#define DVERR_INVALIDBUFFER				MAKE_DVHRESULT( 0x018F )
#define DVERR_LOCKEDBUFFER				MAKE_DVHRESULT( 0x0190 )

#ifdef __cplusplus
}
#endif

#endif


