/*==========================================================================
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       DPLobby.h
 *  Content:    DirectPlay8 Lobby Include File
 *
 ***************************************************************************/

#ifndef	__DPLOBBY_H__
#define	__DPLOBBY_H__

#include <ole2.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * DirectPlay8Lobby CLSIDs
 *
 ****************************************************************************/

// {667955AD-6B3B-43ca-B949-BC69B5BAFF7F}
DEFINE_GUID(CLSID_DirectPlay8LobbiedApplication, 
0x667955ad, 0x6b3b, 0x43ca, 0xb9, 0x49, 0xbc, 0x69, 0xb5, 0xba, 0xff, 0x7f);

// {3B2B6775-70B6-45af-8DEA-A209C69559F3}
DEFINE_GUID(CLSID_DirectPlay8LobbyClient, 
0x3b2b6775, 0x70b6, 0x45af, 0x8d, 0xea, 0xa2, 0x9, 0xc6, 0x95, 0x59, 0xf3);

/****************************************************************************
 *
 * DirectPlay8Lobby Interface IIDs
 *
 ****************************************************************************/

// {819074A3-016C-11d3-AE14-006097B01411}
DEFINE_GUID(IID_IDirectPlay8LobbiedApplication,
0x819074a3, 0x16c, 0x11d3, 0xae, 0x14, 0x0, 0x60, 0x97, 0xb0, 0x14, 0x11);

// {819074A2-016C-11d3-AE14-006097B01411}
DEFINE_GUID(IID_IDirectPlay8LobbyClient,
0x819074a2, 0x16c, 0x11d3, 0xae, 0x14, 0x0, 0x60, 0x97, 0xb0, 0x14, 0x11);

/****************************************************************************
 *
 * DirectPlay8Lobby Interface Pointer 
 *
 ****************************************************************************/

typedef struct IDirectPlay8LobbiedApplication	*PDIRECTPLAY8LOBBIEDAPPLICATION;
typedef struct IDirectPlay8LobbyClient		    *PDIRECTPLAY8LOBBYCLIENT;

/****************************************************************************
 *
 * DirectPlay8 Lobby Message IDs
 *
 ****************************************************************************/

#define	DPL_MSGID_LOBBY						0x8000
#define	DPL_MSGID_RECEIVE					(0x0001 | DPL_MSGID_LOBBY)
#define	DPL_MSGID_CONNECT					(0x0002 | DPL_MSGID_LOBBY)
#define DPL_MSGID_DISCONNECT				(0x0003 | DPL_MSGID_LOBBY)
#define	DPL_MSGID_SESSION_STATUS			(0x0004 | DPL_MSGID_LOBBY)
#define DPL_MSGID_CONNECTION_SETTINGS       (0x0005 | DPL_MSGID_LOBBY)

/****************************************************************************
 *
 * DirectPlay8Lobby Constants
 *
 ****************************************************************************/

//
// Specifies that operation should be performed on all open connections
//
#define DPLHANDLE_ALLCONNECTIONS			0xFFFFFFFF

// 
// The associated game session has suceeded in connecting / hosting
//
#define	DPLSESSION_CONNECTED				0x0001

// The associated game session failed connecting / hosting
//
#define	DPLSESSION_COULDNOTCONNECT			0x0002

//
// The associated game session has disconnected
//
#define	DPLSESSION_DISCONNECTED				0x0003

//
// The associated game session has terminated 
//
#define	DPLSESSION_TERMINATED				0x0004

// 
// The associated game session's host has migrated 
//
#define DPLSESSION_HOSTMIGRATED				0x0005

//
// The associated game session's host has migrated to the local client
//
#define DPLSESSION_HOSTMIGRATEDHERE			0x0006


/****************************************************************************
 *
 * DirectPlay8 Lobby Flags
 *
 ****************************************************************************/

//
// Do not automatically make the lobby app unavailable when a connection is established
//
#define DPLAVAILABLE_ALLOWMULTIPLECONNECT   0x0001

//
// Launch a new instance of the application to connect to
// 
#define	DPLCONNECT_LAUNCHNEW				0x0001

// 
// Launch a new instance of the application if one is not waiting
//
#define	DPLCONNECT_LAUNCHNOTFOUND			0x0002

//
// When starting the associated game session, start it as a host
//
#define DPLCONNECTSETTINGS_HOST             0x0001

// 
// Disable parameter validation
//
#define DPLINITIALIZE_DISABLEPARAMVAL		0x0001

/****************************************************************************
 *
 * DirectPlay8Lobby Structures (Non-Message)
 *
 ****************************************************************************/

// 
// Information on a registered game
//
typedef struct _DPL_APPLICATION_INFO {
	GUID	guidApplication;            // GUID of the application
	PWSTR	pwszApplicationName;        // Name of the application
	DWORD	dwNumRunning;               // # of instances of this application running
	DWORD	dwNumWaiting;               // # of instances of this application waiting 
	DWORD	dwFlags;                    // Flags
} DPL_APPLICATION_INFO,  *PDPL_APPLICATION_INFO;

//
// Settings to be used for connecting / hosting a game session
//
typedef struct _DPL_CONNECTION_SETTINGS {
    DWORD                   dwSize;                 // Size of this structure
    DWORD                   dwFlags;                // Connection settings flags (DPLCONNECTSETTINGS_...)
    DPN_APPLICATION_DESC    dpnAppDesc;             // Application desc for the associated DirectPlay session
    IDirectPlay8Address     *pdp8HostAddress;       // Address of host to connect to
    IDirectPlay8Address     **ppdp8DeviceAddresses; // Address of device to connect from / host on
    DWORD                   cNumDeviceAddresses;    // # of addresses specified in ppdp8DeviceAddresses
	PWSTR					pwszPlayerName;         // Name to give the player
} DPL_CONNECTION_SETTINGS, *PDPL_CONNECTION_SETTINGS;

//
// Information for performing a lobby connect
// (ConnectApplication)
//
typedef struct _DPL_CONNECT_INFO {
	DWORD	                    dwSize;             // Size of this structure
	DWORD	                    dwFlags;            // Flags (DPLCONNECT_...)
	GUID	                    guidApplication;    // GUID of application to launch
    PDPL_CONNECTION_SETTINGS	pdplConnectionSettings;
                                                    // Settings application should use
	PVOID	                    pvLobbyConnectData; // User defined data block
	DWORD	                    dwLobbyConnectDataSize;
                                                    // Size of user defined data block
} DPL_CONNECT_INFO,  *PDPL_CONNECT_INFO;

//
// Information for registering an application
// (RegisterApplication)
//
typedef struct  _DPL_PROGRAM_DESC {
	DWORD	dwSize;
	DWORD	dwFlags;
	GUID	guidApplication;		                // Application GUID
	PWSTR	pwszApplicationName;	                // Unicode application name
	PWSTR	pwszCommandLine;		                // Unicode command line arguments
	PWSTR	pwszCurrentDirectory;               	// Unicode current directory
	PWSTR	pwszDescription;		                // Unicode application description
	PWSTR	pwszExecutableFilename;	                // Unicode filename of application executable
	PWSTR	pwszExecutablePath;		                // Unicode path of application executable
	PWSTR	pwszLauncherFilename;	                // Unicode filename of launcher executable
	PWSTR	pwszLauncherPath;		                // Unicode path of launcher executable
} DPL_PROGRAM_DESC, *PDPL_PROGRAM_DESC;

/****************************************************************************
 *
 * DirectPlay8 Lobby Message Structures
 *
 ****************************************************************************/

//
// A connection was established 
// (DPL_MSGID_CONNECT)
//
typedef struct _DPL_MESSAGE_CONNECT
{
	DWORD		                dwSize;                     // Size of this structure
	DPNHANDLE	                hConnectId;                 // Handle of new connection
    PDPL_CONNECTION_SETTINGS	pdplConnectionSettings;	    // Connection settings for this connection
	PVOID		                pvLobbyConnectData;         // User defined lobby data block
	DWORD		                dwLobbyConnectDataSize;     // Size of user defined lobby data block
	PVOID						pvConnectionContext;        // Context value for this connection (user set)
} DPL_MESSAGE_CONNECT, *PDPL_MESSAGE_CONNECT;

// 
// Connection settings have been updated
// (DPL_MSGID_CONNECTION_SETTINGS)
//
typedef struct _DPL_MESSAGE_CONNECTION_SETTINGS
{
    DWORD                       dwSize;                     // Size of this structure
    DPNHANDLE                   hSender;                    // Handle of the connection for these settings
    PDPL_CONNECTION_SETTINGS    pdplConnectionSettings;     // Connection settings
	PVOID					    pvConnectionContext;        // Context value for this connection
} DPL_MESSAGE_CONNECTION_SETTINGS, *PDPL_MESSAGE_CONNECTION_SETTINGS;

//
// A connection has been disconnected
// (DPL_MSGID_DISCONNECT)
//
typedef struct _DPL_MESSAGE_DISCONNECT
{
	DWORD		dwSize;                                     // Size of this structure
	DPNHANDLE	hDisconnectId;                              // Handle of the connection that was terminated
	HRESULT     hrReason;                                   // Reason the connection was broken
	PVOID		pvConnectionContext;                        // Context value for this connection
} DPL_MESSAGE_DISCONNECT, *PDPL_MESSAGE_DISCONNECT;

//
// Data was received through a connection
// (DPL_MSGID_RECEIVE)
//
typedef struct _DPL_MESSAGE_RECEIVE
{
	DWORD		dwSize;                                     // Size of this structure
	DPNHANDLE	hSender;                                    // Handle of the connection that is from
	BYTE		*pBuffer;                                   // Contents of the message
	DWORD		dwBufferSize;                               // Size of the message context 
	PVOID		pvConnectionContext;                        // Context value for this connection
} DPL_MESSAGE_RECEIVE, *PDPL_MESSAGE_RECEIVE;

//
// Current status of the associated connection
// (DPL_MSGID_SESSION_STATUS)
//
typedef struct _DPL_MESSAGE_SESSION_STATUS
{
	DWORD		dwSize;                                     // Size of this structure
	DPNHANDLE	hSender;                                    // Handle of the connection that this is from
	DWORD		dwStatus;                                   // Status (DPLSESSION_...)
	PVOID		pvConnectionContext;                        // Context value for this connection
} DPL_MESSAGE_SESSION_STATUS, *PDPL_MESSAGE_SESSION_STATUS;

/****************************************************************************
 *
 * DirectPlay8Lobby Create
 *
 ****************************************************************************/
 
/*
 * This function is no longer supported.  It is recommended that CoCreateInstance be used to create 
 * DirectPlay8 lobby objects. 
 *
 * extern HRESULT WINAPI DirectPlay8LobbyCreate( const GUID * pcIID, void **ppvInterface, IUnknown *pUnknown);
 *
 */

/****************************************************************************
 *
 * DirectPlay8 Functions
 *
 ****************************************************************************/

//
// COM definition for DirectPlayLobbyClient
//
#undef INTERFACE				// External COM Implementation
#define INTERFACE IDirectPlay8LobbyClient
DECLARE_INTERFACE_(IDirectPlay8LobbyClient,IUnknown)
{
    // IUnknown methods
	STDMETHOD(QueryInterface)			(THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)			(THIS) PURE;
	STDMETHOD_(ULONG,Release)			(THIS) PURE;
    // IDirectPlayLobbyClient methods
	STDMETHOD(Initialize)	            (THIS_ const PVOID pvUserContext,const PFNDPNMESSAGEHANDLER pfn,const DWORD dwFlags) PURE;
	STDMETHOD(EnumLocalPrograms)		(THIS_ GUID *const pGuidApplication,BYTE *const pEnumData,DWORD *const pdwEnumData,DWORD *const pdwItems, const DWORD dwFlags) PURE;
	STDMETHOD(ConnectApplication)		(THIS_ DPL_CONNECT_INFO *const pdplConnectionInfo,const PVOID pvConnectionContext,DPNHANDLE *const hApplication,const DWORD dwTimeOut,const DWORD dwFlags) PURE;
	STDMETHOD(Send)						(THIS_ const DPNHANDLE hConnection,BYTE *const pBuffer,const DWORD pBufferSize,const DWORD dwFlags) PURE;
	STDMETHOD(ReleaseApplication)		(THIS_ const DPNHANDLE hConnection, const DWORD dwFlags ) PURE;
	STDMETHOD(Close)    				(THIS_ const DWORD dwFlags ) PURE;
	STDMETHOD(GetConnectionSettings)    (THIS_ const DPNHANDLE hConnection, DPL_CONNECTION_SETTINGS * const pdplSessionInfo, DWORD *pdwInfoSize, const DWORD dwFlags ) PURE;	
	STDMETHOD(SetConnectionSettings)    (THIS_ const DPNHANDLE hConnection, const DPL_CONNECTION_SETTINGS * const pdplSessionInfo, const DWORD dwFlags ) PURE;
};


//
// COM definition for DirectPlayLobbiedApplication
//
#undef INTERFACE				// External COM Implementation
#define INTERFACE IDirectPlay8LobbiedApplication
DECLARE_INTERFACE_(IDirectPlay8LobbiedApplication,IUnknown)
{
    // IUnknown methods
	STDMETHOD(QueryInterface)			(THIS_ REFIID riid,LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)			(THIS) PURE;
	STDMETHOD_(ULONG,Release)			(THIS) PURE;
    // IDirectPlayLobbiedApplication methods
	STDMETHOD(Initialize)	            (THIS_ const PVOID pvUserContext,const PFNDPNMESSAGEHANDLER pfn,DPNHANDLE * const pdpnhConnection, const DWORD dwFlags) PURE;
	STDMETHOD(RegisterProgram)			(THIS_ PDPL_PROGRAM_DESC pdplProgramDesc,const DWORD dwFlags) PURE;
	STDMETHOD(UnRegisterProgram)		(THIS_ GUID *pguidApplication,const DWORD dwFlags) PURE;
	STDMETHOD(Send)						(THIS_ const DPNHANDLE hConnection,BYTE *const pBuffer,const DWORD pBufferSize,const DWORD dwFlags) PURE;
	STDMETHOD(SetAppAvailable)			(THIS_ const BOOL fAvailable, const DWORD dwFlags ) PURE;
	STDMETHOD(UpdateStatus)				(THIS_ const DPNHANDLE hConnection, const DWORD dwStatus, const DWORD dwFlags ) PURE;
	STDMETHOD(Close)				    (THIS_ const DWORD dwFlags ) PURE;
	STDMETHOD(GetConnectionSettings)    (THIS_ const DPNHANDLE hConnection, DPL_CONNECTION_SETTINGS * const pdplSessionInfo, DWORD *pdwInfoSize, const DWORD dwFlags ) PURE;
	STDMETHOD(SetConnectionSettings)    (THIS_ const DPNHANDLE hConnection, const DPL_CONNECTION_SETTINGS * const pdplSessionInfo, const DWORD dwFlags ) PURE;
};


/****************************************************************************
 *
 * DirectPlayLobby Interface Macros
 *
 ****************************************************************************/

#if !defined(__cplusplus) || defined(CINTERFACE)

#define IDirectPlay8LobbyClient_QueryInterface(p,a,b)    		        (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlay8LobbyClient_AddRef(p)                		        (p)->lpVtbl->AddRef(p)
#define IDirectPlay8LobbyClient_Release(p)						        (p)->lpVtbl->Release(p)
#define IDirectPlay8LobbyClient_Initialize(p,a,b,c)	                    (p)->lpVtbl->Initialize(p,a,b,c)
#define IDirectPlay8LobbyClient_EnumLocalPrograms(p,a,b,c,d,e)	        (p)->lpVtbl->EnumLocalPrograms(p,a,b,c,d,e)
#define IDirectPlay8LobbyClient_ConnectApplication(p,a,b,c,d,e)	        (p)->lpVtbl->ConnectApplication(p,a,b,c,d,e)
#define IDirectPlay8LobbyClient_Send(p,a,b,c,d)					        (p)->lpVtbl->Send(p,a,b,c,d)
#define IDirectPlay8LobbyClient_ReleaseApplication(p,a,b)		        (p)->lpVtbl->ReleaseApplication(p,a,b)
#define IDirectPlay8LobbyClient_Close(p,a)						        (p)->lpVtbl->Close(p,a)
#define IDirectPlay8LobbyClient_GetConnectionSettings(p,a,b,c,d)        (p)->lpVtbl->GetConnectionSettings(p,a,b,c,d)
#define IDirectPlay8LobbyClient_SetConnectionSettings(p,a,b,c)          (p)->lpVtbl->SetConnectionSettings(p,a,b,c)

#define IDirectPlay8LobbiedApplication_QueryInterface(p,a,b)			(p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlay8LobbiedApplication_AddRef(p)						(p)->lpVtbl->AddRef(p)
#define IDirectPlay8LobbiedApplication_Release(p)						(p)->lpVtbl->Release(p)
#define IDirectPlay8LobbiedApplication_Initialize(p,a,b,c,d)            (p)->lpVtbl->Initialize(p,a,b,c,d)
#define IDirectPlay8LobbiedApplication_RegisterProgram(p,a,b)			(p)->lpVtbl->RegisterProgram(p,a,b)
#define IDirectPlay8LobbiedApplication_UnRegisterProgram(p,a,b)			(p)->lpVtbl->UnRegisterProgram(p,a,b)
#define IDirectPlay8LobbiedApplication_Send(p,a,b,c,d)					(p)->lpVtbl->Send(p,a,b,c,d)
#define IDirectPlay8LobbiedApplication_SetAppAvailable(p,a,b)			(p)->lpVtbl->SetAppAvailable(p,a,b)
#define IDirectPlay8LobbiedApplication_UpdateStatus(p,a,b,c)			(p)->lpVtbl->UpdateStatus(p,a,b,c)
#define IDirectPlay8LobbiedApplication_Close(p,a)						(p)->lpVtbl->Close(p,a)
#define IDirectPlay8LobbiedApplication_GetConnectionSettings(p,a,b,c,d) (p)->lpVtbl->GetConnectionSettings(p,a,b,c,d)
#define IDirectPlay8LobbiedApplication_SetConnectionSettings(p,a,b,c)   (p)->lpVtbl->SetConnectionSettings(p,a,b,c)

#else	/* C++ */

#define IDirectPlay8LobbyClient_QueryInterface(p,a,b)    		        (p)->QueryInterface(a,b)
#define IDirectPlay8LobbyClient_AddRef(p)                		        (p)->AddRef()
#define IDirectPlay8LobbyClient_Release(p)						        (p)->Release()
#define IDirectPlay8LobbyClient_Initialize(p,a,b,c)	                    (p)->Initialize(a,b,c)
#define IDirectPlay8LobbyClient_EnumLocalPrograms(p,a,b,c,d,e)	        (p)->EnumLocalPrograms(a,b,c,d,e)
#define IDirectPlay8LobbyClient_ConnectApplication(p,a,b,c,d,e)	        (p)->ConnectApplication(a,b,c,d,e)
#define IDirectPlay8LobbyClient_Send(p,a,b,c,d)					        (p)->Send(a,b,c,d)
#define IDirectPlay8LobbyClient_ReleaseApplication(p,a,b)		        (p)->ReleaseApplication(a,b)
#define IDirectPlay8LobbyClient_Close(p,a)						        (p)->Close(a)
#define IDirectPlay8LobbyClient_GetConnectionSettings(p,a,b,c,d)        (p)->GetConnectionSettings(a,b,c,d)
#define IDirectPlay8LobbyClient_SetConnectionSettings(p,a,b,c)          (p)->SetConnectionSettings(a,b,c)

#define IDirectPlay8LobbiedApplication_QueryInterface(p,a,b)			(p)->QueryInterface(a,b)
#define IDirectPlay8LobbiedApplication_AddRef(p)						(p)->AddRef()
#define IDirectPlay8LobbiedApplication_Release(p)						(p)->Release()
#define IDirectPlay8LobbiedApplication_Initialize(p,a,b,c,d)            (p)->Initialize(a,b,c,d)
#define IDirectPlay8LobbiedApplication_RegisterProgram(p,a,b)			(p)->RegisterProgram(a,b)
#define IDirectPlay8LobbiedApplication_UnRegisterProgram(p,a,b)			(p)->UnRegisterProgram(a,b)
#define IDirectPlay8LobbiedApplication_Send(p,a,b,c,d)					(p)->Send(a,b,c,d)
#define IDirectPlay8LobbiedApplication_SetAppAvailable(p,a,b)			(p)->SetAppAvailable(a,b)
#define IDirectPlay8LobbiedApplication_UpdateStatus(p,a,b,c)			(p)->UpdateStatus(a,b,c)
#define IDirectPlay8LobbiedApplication_Close(p,a)						(p)->Close(a)
#define IDirectPlay8LobbiedApplication_GetConnectionSettings(p,a,b,c,d) (p)->GetConnectionSettings(a,b,c,d)
#define IDirectPlay8LobbiedApplication_SetConnectionSettings(p,a,b,c)   (p)->SetConnectionSettings(a,b,c)

#endif

#ifdef __cplusplus
}
#endif

#endif	// __DPLOBBY_H__

