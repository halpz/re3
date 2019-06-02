/***************************************************************************
 *
 *  Copyright (C) 2001-2002 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:		dpnathlp.h
 *
 *  Content:	Header for using DirectPlayNATHelp interface.
 *
 *
 *  NOTE: This interface is deprecated and should no longer be used.
 *
 *
 ***************************************************************************/



#ifndef __DPNATHLP_H__
#define __DPNATHLP_H__



#include <ole2.h>	// for DECLARE_INTERFACE and HRESULT



#ifndef DPNATHLP_EXPORTS
#define DPNATHLPAPI DECLSPEC_IMPORT
#else
#define DPNATHLPAPI
#endif



#ifdef __cplusplus
extern "C" {
#endif





/****************************************************************************
 *
 * DirectPlay NAT Helper object class IDs
 *
 ****************************************************************************/

// {B9C2E9C4-68C1-4d42-A7A1-E76A26982AD6}
DEFINE_GUID(CLSID_DirectPlayNATHelpUPnP,
0xb9c2e9c4, 0x68c1, 0x4d42, 0xa7, 0xa1, 0xe7, 0x6a, 0x26, 0x98, 0x2a, 0xd6);

// {963AB779-16A1-477c-A36D-CB5E711938F7}
DEFINE_GUID(CLSID_DirectPlayNATHelpPAST,
0x963ab779, 0x16a1, 0x477c, 0xa3, 0x6d, 0xcb, 0x5e, 0x71, 0x19, 0x38, 0xf7);


/****************************************************************************
 *
 * DirectPlay NAT Helper interface ID
 *
 ****************************************************************************/

// {154940B6-2278-4a2f-9101-9BA9F431F603}
DEFINE_GUID(IID_IDirectPlayNATHelp, 
0x154940b6, 0x2278, 0x4a2f, 0x91, 0x1, 0x9b, 0xa9, 0xf4, 0x31, 0xf6, 0x3);

/****************************************************************************
 *
 * DirectPlay NAT Helper interface pointer definitions
 *
 ****************************************************************************/

typedef	struct IDirectPlayNATHelp     *PDIRECTPLAYNATHELP;




/****************************************************************************
 *
 * DirectPlay NAT Helper data types
 *
 ****************************************************************************/

//
// Handles used to identify specific port binding groups.  If multiple ports
// are registered at the same time, the DPNHHANDLE refers to all ports.
//
typedef DWORD_PTR	DPNHHANDLE,	* PDPNHHANDLE;




/****************************************************************************
 *
 * DirectPlay NAT Helper constants
 *
 ****************************************************************************/

#define DPNH_MAX_SIMULTANEOUS_PORTS		16	// up to 16 ports may be specified in a single RegisterPorts call




/****************************************************************************
 *
 * DirectPlay NAT Helper API flags
 *
 ****************************************************************************/

//
// Flags that can be passed to Initialize
//
#define DPNHINITIALIZE_DISABLEGATEWAYSUPPORT				0x01	// disables Internet gateway traversal support (cannot be specified with DPNHINITIALIZE_DISABLELOCALFIREWALLSUPPORT)
#define DPNHINITIALIZE_DISABLELOCALFIREWALLSUPPORT			0x02	// disables local firewall traversal support (cannot be specified with DPNHINITIALIZE_DISABLEGATEWAYSUPPORT)

//
// Flags that can be passed to GetCaps.
//
#define DPNHGETCAPS_UPDATESERVERSTATUS						0x01	// automatically extend expiring leases and detect changes in server status

//
// Flags that can be passed to RegisterPorts.
//
#define DPNHREGISTERPORTS_TCP								0x01	// request TCP ports instead of UDP
#define DPNHREGISTERPORTS_FIXEDPORTS						0x02	// asks the server to use the same port numbers on the public interface
#define DPNHREGISTERPORTS_SHAREDPORTS						0x04	// requests that the server allow the UDP fixed ports to be shared with other clients (must be specified with DPNHREGISTERPORTS_FIXEDPORTS and cannot be specified with DPNHREGISTERPORTS_TCP)

//
// Flags that can be passed to GetRegisteredAddresses.
//
#define DPNHGETREGISTEREDADDRESSES_LOCALFIREWALLREMAPONLY	0x01	// retrieve the public address for the local firewall only, even if mapped on remote Internet gateway

//
// Flags that can be passed to QueryAddress.
//
#define DPNHQUERYADDRESS_TCP								0x01	// request a TCP port instead of UDP
#define DPNHQUERYADDRESS_CACHEFOUND							0x02	// cache the discovered address if found
#define DPNHQUERYADDRESS_CACHENOTFOUND						0x04	// cache the fact that no address was found, if that is the case
#define DPNHQUERYADDRESS_CHECKFORPRIVATEBUTUNMAPPED			0x08	// determine if the address is behind the same Internet gateway, but not mapped on that Internet gateway

/****************************************************************************
 *
 * DirectPlay NAT Helper structure flags
 *
 ****************************************************************************/

//
// DPNHCAPS flags
//
#define DPNHCAPSFLAG_LOCALFIREWALLPRESENT		0x01	// at least one network connection has a local firewall present
#define DPNHCAPSFLAG_GATEWAYPRESENT				0x02	// at least one network connection has an Internet gateway present
#define DPNHCAPSFLAG_GATEWAYISLOCAL				0x04	// a detected Internet gateway is local (i.e. the public address is another network interface on the same machine)
#define DPNHCAPSFLAG_PUBLICADDRESSAVAILABLE		0x08	// at least one server has a valid public address for registered mappings
#define DPNHCAPSFLAG_NOTALLSUPPORTACTIVENOTIFY	0x10	// at least one available server does not support an active-notification mechanisms and must be polled



/****************************************************************************
 *
 * DirectPlay NAT Helper structures
 *
 ****************************************************************************/
 
typedef struct _DPNHCAPS
{
	DWORD	dwSize;							// size of this structure, must be filled in prior to calling GetCaps
	DWORD	dwFlags;						// flags indicating capabilities of Internet gateway server(s)
	DWORD	dwNumRegisteredPorts;			// number of ports currently registered, including multiple ports registered at the same time (so this may not be equal to the number of DPNHHANDLEs given out)
	DWORD	dwMinLeaseTimeRemaining;		// approximate time remaining, in milliseconds, for the lease that will expire soonest
	DWORD	dwRecommendedGetCapsInterval;	// recommended time, in milliseconds, after which GetCaps should be called again (with DPNHGETCAPS_UPDATESERVERSTATUS flag)
} DPNHCAPS, * PDPNHCAPS;



/****************************************************************************
 *
 * Address type flags (returned by GetRegisteredAddresses)
 *
 ****************************************************************************/

#define DPNHADDRESSTYPE_TCP				0x01	// the mappings are for TCP ports instead of UDP
#define DPNHADDRESSTYPE_FIXEDPORTS		0x02	// the mappings are for ports which are the same on the Internet gateway 
#define DPNHADDRESSTYPE_SHAREDPORTS		0x04	// the mappings are for shared UDP fixed ports
#define DPNHADDRESSTYPE_LOCALFIREWALL	0x08	// the addresses are opened on a local firewall
#define DPNHADDRESSTYPE_GATEWAY			0x10	// the addresses are registered with an Internet gateway
#define DPNHADDRESSTYPE_GATEWAYISLOCAL	0x20	// the Internet gateway is local (i.e. the public address is another network interface on the same machine)




/****************************************************************************
 *
 * DirectPlay NAT Helper DLL exported functions
 *
 ****************************************************************************/

typedef HRESULT (WINAPI * PFN_DIRECTPLAYNATHELPCREATE)(const GUID * pIID, void ** ppvInterface);





/****************************************************************************
 *
 * DirectPlay NAT Helper application interfaces
 *
 ****************************************************************************/

#undef INTERFACE
#define INTERFACE IDirectPlayNATHelp
DECLARE_INTERFACE_(IDirectPlayNATHelp, IUnknown)
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)				(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef)				(THIS) PURE;
	STDMETHOD_(ULONG,Release)				(THIS) PURE;

	/*** IDirectPlayNATHelp methods ***/
	STDMETHOD(Initialize)					(THIS_ const DWORD dwFlags) PURE;
	STDMETHOD(Close)						(THIS_ const DWORD dwFlags) PURE;
	STDMETHOD(GetCaps)						(THIS_ DPNHCAPS * const dpnhcaps, const DWORD dwFlags) PURE;
	STDMETHOD(RegisterPorts)				(THIS_ const SOCKADDR * const aLocalAddresses, const DWORD dwAddressesSize, const DWORD dwNumAddresses, const DWORD dwLeaseTime, DPNHHANDLE * const phRegisteredPorts, const DWORD dwFlags) PURE;
	STDMETHOD(GetRegisteredAddresses)		(THIS_ const DPNHHANDLE hRegisteredPorts, SOCKADDR * const paPublicAddresses, DWORD * const pdwPublicAddressesSize, DWORD * const pdwAddressTypeFlags, DWORD * const pdwLeaseTimeRemaining, const DWORD dwFlags) PURE;
	STDMETHOD(DeregisterPorts)				(THIS_ const DPNHHANDLE hRegisteredPorts, const DWORD dwFlags) PURE;
	STDMETHOD(QueryAddress)					(THIS_ const SOCKADDR * const pSourceAddress, const SOCKADDR * const pQueryAddress, SOCKADDR * const pResponseAddress, const int iAddressesSize, const DWORD dwFlags) PURE;
	STDMETHOD(SetAlertEvent)				(THIS_ const HANDLE hEvent, const DWORD dwFlags) PURE;
	STDMETHOD(SetAlertIOCompletionPort)		(THIS_ const HANDLE hIOCompletionPort, const DWORD dwCompletionKey, const DWORD dwNumConcurrentThreads, const DWORD dwFlags) PURE;
	STDMETHOD(ExtendRegisteredPortsLease)	(THIS_ const DPNHHANDLE hRegisteredPorts, const DWORD dwLeaseTime, const DWORD dwFlags) PURE;
};


/****************************************************************************
 *
 * DirectPlay NAT Helper application interface macros
 *
 ****************************************************************************/

#if (! defined(__cplusplus) || defined(CINTERFACE))

#define	IDirectPlayNATHelp_QueryInterface(p,a,b)					(p)->lpVtbl->QueryInterface(p,a,b)
#define	IDirectPlayNATHelp_AddRef(p)								(p)->lpVtbl->AddRef(p)
#define	IDirectPlayNATHelp_Release(p)								(p)->lpVtbl->Release(p)
#define	IDirectPlayNATHelp_Initialize(p,a)							(p)->lpVtbl->Initialize(p,a)
#define	IDirectPlayNATHelp_Close(p,a)								(p)->lpVtbl->Close(p,a)
#define	IDirectPlayNATHelp_GetCaps(p,a,b)							(p)->lpVtbl->GetCaps(p,a,b)
#define	IDirectPlayNATHelp_RegisterPorts(p,a,b,c,d,e,f)				(p)->lpVtbl->RegisterPorts(p,a,b,c,d,e,f)
#define	IDirectPlayNATHelp_GetRegisteredAddresses(p,a,b,c,d,e,f)	(p)->lpVtbl->GetRegisteredAddresses(p,a,b,c,d,e,f)
#define	IDirectPlayNATHelp_DeregisterPorts(p,a,b)					(p)->lpVtbl->DeregisterPorts(p,a,b)
#define	IDirectPlayNATHelp_QueryAddress(p,a,b,c,d,e)				(p)->lpVtbl->QueryAddress(p,a,b,c,d,e)
#define	IDirectPlayNATHelp_SetAlertEvent(p,a,b)						(p)->lpVtbl->SetAlertEvent(p,a,b)
#define	IDirectPlayNATHelp_SetAlertIOCompletionPort(p,a,b,c,d)		(p)->lpVtbl->SetAlertIOCompletionPort(p,a,b,c,d)
#define	IDirectPlayNATHelp_ExtendRegisteredPortsLease(p,a,b,c)		(p)->lpVtbl->ExtendRegisteredPortsLease(p,a,b,c)


#else // C++

#define	IDirectPlayNATHelp_QueryInterface(p,a,b)					(p)->QueryInterface(a,b)
#define	IDirectPlayNATHelp_AddRef(p)								(p)->AddRef()
#define	IDirectPlayNATHelp_Release(p)								(p)->Release()
#define	IDirectPlayNATHelp_Initialize(p,a)							(p)->Initialize(a)
#define	IDirectPlayNATHelp_Close(p,a)								(p)->Close(a)
#define	IDirectPlayNATHelp_GetCaps(p,a,b)							(p)->GetCaps(a,b)
#define	IDirectPlayNATHelp_RegisterPorts(p,a,b,c,d,e,f)				(p)->RegisterPorts(a,b,c,d,e,f)
#define	IDirectPlayNATHelp_GetRegisteredAddresses(p,a,b,c,d,e,f)	(p)->GetRegisteredAddresses(a,b,c,d,e,f)
#define	IDirectPlayNATHelp_DeregisterPorts(p,a,b)					(p)->DeregisterPorts(a,b)
#define	IDirectPlayNATHelp_QueryAddress(p,a,b,c,d,e)				(p)->QueryAddress(a,b,c,d,e)
#define	IDirectPlayNATHelp_SetAlertEvent(p,a,b)						(p)->SetAlertEvent(a,b)
#define	IDirectPlayNATHelp_SetAlertIOCompletionPort(p,a,b,c,d)		(p)->SetAlertIOCompletionPort(a,b,c,d)
#define	IDirectPlayNATHelp_ExtendRegisteredPortsLease(p,a,b,c)		(p)->ExtendRegisteredPortsLease(a,b,c)


#endif



/****************************************************************************
 *
 * DirectPlay NAT Helper return codes
 *
 * Errors are represented by negative values and cannot be combined.
 *
 ****************************************************************************/

#define _DPNH_FACILITY_CODE					0x015
#define _DPNH_HRESULT_BASE					0xF000

#define MAKE_DPNHSUCCESS(code)				MAKE_HRESULT(0, _DPNH_FACILITY_CODE, (code + _DPNH_HRESULT_BASE))
#define MAKE_DPNHFAILURE(code)				MAKE_HRESULT(1, _DPNH_FACILITY_CODE, (code + _DPNH_HRESULT_BASE))



#define DPNH_OK								S_OK

#define DPNHSUCCESS_ADDRESSESCHANGED		MAKE_DPNHSUCCESS(0x10)

#define DPNHERR_ALREADYINITIALIZED			MAKE_DPNHFAILURE(0x10)
#define DPNHERR_BUFFERTOOSMALL				MAKE_DPNHFAILURE(0x20)
#define DPNHERR_GENERIC						E_FAIL
#define DPNHERR_INVALIDFLAGS				MAKE_DPNHFAILURE(0x30)
#define DPNHERR_INVALIDOBJECT				MAKE_DPNHFAILURE(0x40)
#define DPNHERR_INVALIDPARAM				E_INVALIDARG
#define DPNHERR_INVALIDPOINTER				E_POINTER
#define DPNHERR_NOMAPPING					MAKE_DPNHFAILURE(0x50)
#define DPNHERR_NOMAPPINGBUTPRIVATE			MAKE_DPNHFAILURE(0x60)
#define DPNHERR_NOTINITIALIZED				MAKE_DPNHFAILURE(0x70)
#define DPNHERR_OUTOFMEMORY					E_OUTOFMEMORY
#define DPNHERR_PORTALREADYREGISTERED		MAKE_DPNHFAILURE(0x80)
#define DPNHERR_PORTUNAVAILABLE				MAKE_DPNHFAILURE(0x90)
#define DPNHERR_REENTRANT					MAKE_DPNHFAILURE(0x95)
#define DPNHERR_SERVERNOTAVAILABLE			MAKE_DPNHFAILURE(0xA0)
#define DPNHERR_UPDATESERVERSTATUS			MAKE_DPNHFAILURE(0xC0)

#ifdef __cplusplus
}
#endif

#endif // __DPNATHLP_H__

