
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for tuner.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __tuner_h__
#define __tuner_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITuningSpaces_FWD_DEFINED__
#define __ITuningSpaces_FWD_DEFINED__
typedef interface ITuningSpaces ITuningSpaces;
#endif 	/* __ITuningSpaces_FWD_DEFINED__ */


#ifndef __ITuningSpaceContainer_FWD_DEFINED__
#define __ITuningSpaceContainer_FWD_DEFINED__
typedef interface ITuningSpaceContainer ITuningSpaceContainer;
#endif 	/* __ITuningSpaceContainer_FWD_DEFINED__ */


#ifndef __ITuningSpace_FWD_DEFINED__
#define __ITuningSpace_FWD_DEFINED__
typedef interface ITuningSpace ITuningSpace;
#endif 	/* __ITuningSpace_FWD_DEFINED__ */


#ifndef __IEnumTuningSpaces_FWD_DEFINED__
#define __IEnumTuningSpaces_FWD_DEFINED__
typedef interface IEnumTuningSpaces IEnumTuningSpaces;
#endif 	/* __IEnumTuningSpaces_FWD_DEFINED__ */


#ifndef __IDVBTuningSpace_FWD_DEFINED__
#define __IDVBTuningSpace_FWD_DEFINED__
typedef interface IDVBTuningSpace IDVBTuningSpace;
#endif 	/* __IDVBTuningSpace_FWD_DEFINED__ */


#ifndef __IDVBTuningSpace2_FWD_DEFINED__
#define __IDVBTuningSpace2_FWD_DEFINED__
typedef interface IDVBTuningSpace2 IDVBTuningSpace2;
#endif 	/* __IDVBTuningSpace2_FWD_DEFINED__ */


#ifndef __IDVBSTuningSpace_FWD_DEFINED__
#define __IDVBSTuningSpace_FWD_DEFINED__
typedef interface IDVBSTuningSpace IDVBSTuningSpace;
#endif 	/* __IDVBSTuningSpace_FWD_DEFINED__ */


#ifndef __IAuxInTuningSpace_FWD_DEFINED__
#define __IAuxInTuningSpace_FWD_DEFINED__
typedef interface IAuxInTuningSpace IAuxInTuningSpace;
#endif 	/* __IAuxInTuningSpace_FWD_DEFINED__ */


#ifndef __IAnalogTVTuningSpace_FWD_DEFINED__
#define __IAnalogTVTuningSpace_FWD_DEFINED__
typedef interface IAnalogTVTuningSpace IAnalogTVTuningSpace;
#endif 	/* __IAnalogTVTuningSpace_FWD_DEFINED__ */


#ifndef __IATSCTuningSpace_FWD_DEFINED__
#define __IATSCTuningSpace_FWD_DEFINED__
typedef interface IATSCTuningSpace IATSCTuningSpace;
#endif 	/* __IATSCTuningSpace_FWD_DEFINED__ */


#ifndef __IAnalogRadioTuningSpace_FWD_DEFINED__
#define __IAnalogRadioTuningSpace_FWD_DEFINED__
typedef interface IAnalogRadioTuningSpace IAnalogRadioTuningSpace;
#endif 	/* __IAnalogRadioTuningSpace_FWD_DEFINED__ */


#ifndef __ITuneRequest_FWD_DEFINED__
#define __ITuneRequest_FWD_DEFINED__
typedef interface ITuneRequest ITuneRequest;
#endif 	/* __ITuneRequest_FWD_DEFINED__ */


#ifndef __IChannelTuneRequest_FWD_DEFINED__
#define __IChannelTuneRequest_FWD_DEFINED__
typedef interface IChannelTuneRequest IChannelTuneRequest;
#endif 	/* __IChannelTuneRequest_FWD_DEFINED__ */


#ifndef __IATSCChannelTuneRequest_FWD_DEFINED__
#define __IATSCChannelTuneRequest_FWD_DEFINED__
typedef interface IATSCChannelTuneRequest IATSCChannelTuneRequest;
#endif 	/* __IATSCChannelTuneRequest_FWD_DEFINED__ */


#ifndef __IDVBTuneRequest_FWD_DEFINED__
#define __IDVBTuneRequest_FWD_DEFINED__
typedef interface IDVBTuneRequest IDVBTuneRequest;
#endif 	/* __IDVBTuneRequest_FWD_DEFINED__ */


#ifndef __IMPEG2TuneRequest_FWD_DEFINED__
#define __IMPEG2TuneRequest_FWD_DEFINED__
typedef interface IMPEG2TuneRequest IMPEG2TuneRequest;
#endif 	/* __IMPEG2TuneRequest_FWD_DEFINED__ */


#ifndef __IMPEG2TuneRequestFactory_FWD_DEFINED__
#define __IMPEG2TuneRequestFactory_FWD_DEFINED__
typedef interface IMPEG2TuneRequestFactory IMPEG2TuneRequestFactory;
#endif 	/* __IMPEG2TuneRequestFactory_FWD_DEFINED__ */


#ifndef __IMPEG2TuneRequestSupport_FWD_DEFINED__
#define __IMPEG2TuneRequestSupport_FWD_DEFINED__
typedef interface IMPEG2TuneRequestSupport IMPEG2TuneRequestSupport;
#endif 	/* __IMPEG2TuneRequestSupport_FWD_DEFINED__ */


#ifndef __ITuner_FWD_DEFINED__
#define __ITuner_FWD_DEFINED__
typedef interface ITuner ITuner;
#endif 	/* __ITuner_FWD_DEFINED__ */


#ifndef __IScanningTuner_FWD_DEFINED__
#define __IScanningTuner_FWD_DEFINED__
typedef interface IScanningTuner IScanningTuner;
#endif 	/* __IScanningTuner_FWD_DEFINED__ */


#ifndef __IComponentType_FWD_DEFINED__
#define __IComponentType_FWD_DEFINED__
typedef interface IComponentType IComponentType;
#endif 	/* __IComponentType_FWD_DEFINED__ */


#ifndef __ILanguageComponentType_FWD_DEFINED__
#define __ILanguageComponentType_FWD_DEFINED__
typedef interface ILanguageComponentType ILanguageComponentType;
#endif 	/* __ILanguageComponentType_FWD_DEFINED__ */


#ifndef __IMPEG2ComponentType_FWD_DEFINED__
#define __IMPEG2ComponentType_FWD_DEFINED__
typedef interface IMPEG2ComponentType IMPEG2ComponentType;
#endif 	/* __IMPEG2ComponentType_FWD_DEFINED__ */


#ifndef __IATSCComponentType_FWD_DEFINED__
#define __IATSCComponentType_FWD_DEFINED__
typedef interface IATSCComponentType IATSCComponentType;
#endif 	/* __IATSCComponentType_FWD_DEFINED__ */


#ifndef __IEnumComponentTypes_FWD_DEFINED__
#define __IEnumComponentTypes_FWD_DEFINED__
typedef interface IEnumComponentTypes IEnumComponentTypes;
#endif 	/* __IEnumComponentTypes_FWD_DEFINED__ */


#ifndef __IComponentTypes_FWD_DEFINED__
#define __IComponentTypes_FWD_DEFINED__
typedef interface IComponentTypes IComponentTypes;
#endif 	/* __IComponentTypes_FWD_DEFINED__ */


#ifndef __IComponent_FWD_DEFINED__
#define __IComponent_FWD_DEFINED__
typedef interface IComponent IComponent;
#endif 	/* __IComponent_FWD_DEFINED__ */


#ifndef __IMPEG2Component_FWD_DEFINED__
#define __IMPEG2Component_FWD_DEFINED__
typedef interface IMPEG2Component IMPEG2Component;
#endif 	/* __IMPEG2Component_FWD_DEFINED__ */


#ifndef __IEnumComponents_FWD_DEFINED__
#define __IEnumComponents_FWD_DEFINED__
typedef interface IEnumComponents IEnumComponents;
#endif 	/* __IEnumComponents_FWD_DEFINED__ */


#ifndef __IComponents_FWD_DEFINED__
#define __IComponents_FWD_DEFINED__
typedef interface IComponents IComponents;
#endif 	/* __IComponents_FWD_DEFINED__ */


#ifndef __ILocator_FWD_DEFINED__
#define __ILocator_FWD_DEFINED__
typedef interface ILocator ILocator;
#endif 	/* __ILocator_FWD_DEFINED__ */


#ifndef __IATSCLocator_FWD_DEFINED__
#define __IATSCLocator_FWD_DEFINED__
typedef interface IATSCLocator IATSCLocator;
#endif 	/* __IATSCLocator_FWD_DEFINED__ */


#ifndef __IDVBTLocator_FWD_DEFINED__
#define __IDVBTLocator_FWD_DEFINED__
typedef interface IDVBTLocator IDVBTLocator;
#endif 	/* __IDVBTLocator_FWD_DEFINED__ */


#ifndef __IDVBSLocator_FWD_DEFINED__
#define __IDVBSLocator_FWD_DEFINED__
typedef interface IDVBSLocator IDVBSLocator;
#endif 	/* __IDVBSLocator_FWD_DEFINED__ */


#ifndef __IDVBCLocator_FWD_DEFINED__
#define __IDVBCLocator_FWD_DEFINED__
typedef interface IDVBCLocator IDVBCLocator;
#endif 	/* __IDVBCLocator_FWD_DEFINED__ */


#ifndef __IBroadcastEvent_FWD_DEFINED__
#define __IBroadcastEvent_FWD_DEFINED__
typedef interface IBroadcastEvent IBroadcastEvent;
#endif 	/* __IBroadcastEvent_FWD_DEFINED__ */


#ifndef __SystemTuningSpaces_FWD_DEFINED__
#define __SystemTuningSpaces_FWD_DEFINED__

#ifdef __cplusplus
typedef class SystemTuningSpaces SystemTuningSpaces;
#else
typedef struct SystemTuningSpaces SystemTuningSpaces;
#endif /* __cplusplus */

#endif 	/* __SystemTuningSpaces_FWD_DEFINED__ */


#ifndef __TuningSpace_FWD_DEFINED__
#define __TuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class TuningSpace TuningSpace;
#else
typedef struct TuningSpace TuningSpace;
#endif /* __cplusplus */

#endif 	/* __TuningSpace_FWD_DEFINED__ */


#ifndef __ATSCTuningSpace_FWD_DEFINED__
#define __ATSCTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATSCTuningSpace ATSCTuningSpace;
#else
typedef struct ATSCTuningSpace ATSCTuningSpace;
#endif /* __cplusplus */

#endif 	/* __ATSCTuningSpace_FWD_DEFINED__ */


#ifndef __AnalogRadioTuningSpace_FWD_DEFINED__
#define __AnalogRadioTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnalogRadioTuningSpace AnalogRadioTuningSpace;
#else
typedef struct AnalogRadioTuningSpace AnalogRadioTuningSpace;
#endif /* __cplusplus */

#endif 	/* __AnalogRadioTuningSpace_FWD_DEFINED__ */


#ifndef __AuxInTuningSpace_FWD_DEFINED__
#define __AuxInTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class AuxInTuningSpace AuxInTuningSpace;
#else
typedef struct AuxInTuningSpace AuxInTuningSpace;
#endif /* __cplusplus */

#endif 	/* __AuxInTuningSpace_FWD_DEFINED__ */


#ifndef __AnalogTVTuningSpace_FWD_DEFINED__
#define __AnalogTVTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnalogTVTuningSpace AnalogTVTuningSpace;
#else
typedef struct AnalogTVTuningSpace AnalogTVTuningSpace;
#endif /* __cplusplus */

#endif 	/* __AnalogTVTuningSpace_FWD_DEFINED__ */


#ifndef __DVBTuningSpace_FWD_DEFINED__
#define __DVBTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBTuningSpace DVBTuningSpace;
#else
typedef struct DVBTuningSpace DVBTuningSpace;
#endif /* __cplusplus */

#endif 	/* __DVBTuningSpace_FWD_DEFINED__ */


#ifndef __DVBSTuningSpace_FWD_DEFINED__
#define __DVBSTuningSpace_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBSTuningSpace DVBSTuningSpace;
#else
typedef struct DVBSTuningSpace DVBSTuningSpace;
#endif /* __cplusplus */

#endif 	/* __DVBSTuningSpace_FWD_DEFINED__ */


#ifndef __ComponentTypes_FWD_DEFINED__
#define __ComponentTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComponentTypes ComponentTypes;
#else
typedef struct ComponentTypes ComponentTypes;
#endif /* __cplusplus */

#endif 	/* __ComponentTypes_FWD_DEFINED__ */


#ifndef __ComponentType_FWD_DEFINED__
#define __ComponentType_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComponentType ComponentType;
#else
typedef struct ComponentType ComponentType;
#endif /* __cplusplus */

#endif 	/* __ComponentType_FWD_DEFINED__ */


#ifndef __LanguageComponentType_FWD_DEFINED__
#define __LanguageComponentType_FWD_DEFINED__

#ifdef __cplusplus
typedef class LanguageComponentType LanguageComponentType;
#else
typedef struct LanguageComponentType LanguageComponentType;
#endif /* __cplusplus */

#endif 	/* __LanguageComponentType_FWD_DEFINED__ */


#ifndef __MPEG2ComponentType_FWD_DEFINED__
#define __MPEG2ComponentType_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPEG2ComponentType MPEG2ComponentType;
#else
typedef struct MPEG2ComponentType MPEG2ComponentType;
#endif /* __cplusplus */

#endif 	/* __MPEG2ComponentType_FWD_DEFINED__ */


#ifndef __ATSCComponentType_FWD_DEFINED__
#define __ATSCComponentType_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATSCComponentType ATSCComponentType;
#else
typedef struct ATSCComponentType ATSCComponentType;
#endif /* __cplusplus */

#endif 	/* __ATSCComponentType_FWD_DEFINED__ */


#ifndef __Components_FWD_DEFINED__
#define __Components_FWD_DEFINED__

#ifdef __cplusplus
typedef class Components Components;
#else
typedef struct Components Components;
#endif /* __cplusplus */

#endif 	/* __Components_FWD_DEFINED__ */


#ifndef __Component_FWD_DEFINED__
#define __Component_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component Component;
#else
typedef struct Component Component;
#endif /* __cplusplus */

#endif 	/* __Component_FWD_DEFINED__ */


#ifndef __MPEG2Component_FWD_DEFINED__
#define __MPEG2Component_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPEG2Component MPEG2Component;
#else
typedef struct MPEG2Component MPEG2Component;
#endif /* __cplusplus */

#endif 	/* __MPEG2Component_FWD_DEFINED__ */


#ifndef __TuneRequest_FWD_DEFINED__
#define __TuneRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class TuneRequest TuneRequest;
#else
typedef struct TuneRequest TuneRequest;
#endif /* __cplusplus */

#endif 	/* __TuneRequest_FWD_DEFINED__ */


#ifndef __ChannelTuneRequest_FWD_DEFINED__
#define __ChannelTuneRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChannelTuneRequest ChannelTuneRequest;
#else
typedef struct ChannelTuneRequest ChannelTuneRequest;
#endif /* __cplusplus */

#endif 	/* __ChannelTuneRequest_FWD_DEFINED__ */


#ifndef __ATSCChannelTuneRequest_FWD_DEFINED__
#define __ATSCChannelTuneRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATSCChannelTuneRequest ATSCChannelTuneRequest;
#else
typedef struct ATSCChannelTuneRequest ATSCChannelTuneRequest;
#endif /* __cplusplus */

#endif 	/* __ATSCChannelTuneRequest_FWD_DEFINED__ */


#ifndef __MPEG2TuneRequest_FWD_DEFINED__
#define __MPEG2TuneRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPEG2TuneRequest MPEG2TuneRequest;
#else
typedef struct MPEG2TuneRequest MPEG2TuneRequest;
#endif /* __cplusplus */

#endif 	/* __MPEG2TuneRequest_FWD_DEFINED__ */


#ifndef __MPEG2TuneRequestFactory_FWD_DEFINED__
#define __MPEG2TuneRequestFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPEG2TuneRequestFactory MPEG2TuneRequestFactory;
#else
typedef struct MPEG2TuneRequestFactory MPEG2TuneRequestFactory;
#endif /* __cplusplus */

#endif 	/* __MPEG2TuneRequestFactory_FWD_DEFINED__ */


#ifndef __Locator_FWD_DEFINED__
#define __Locator_FWD_DEFINED__

#ifdef __cplusplus
typedef class Locator Locator;
#else
typedef struct Locator Locator;
#endif /* __cplusplus */

#endif 	/* __Locator_FWD_DEFINED__ */


#ifndef __ATSCLocator_FWD_DEFINED__
#define __ATSCLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATSCLocator ATSCLocator;
#else
typedef struct ATSCLocator ATSCLocator;
#endif /* __cplusplus */

#endif 	/* __ATSCLocator_FWD_DEFINED__ */


#ifndef __DVBTLocator_FWD_DEFINED__
#define __DVBTLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBTLocator DVBTLocator;
#else
typedef struct DVBTLocator DVBTLocator;
#endif /* __cplusplus */

#endif 	/* __DVBTLocator_FWD_DEFINED__ */


#ifndef __DVBSLocator_FWD_DEFINED__
#define __DVBSLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBSLocator DVBSLocator;
#else
typedef struct DVBSLocator DVBSLocator;
#endif /* __cplusplus */

#endif 	/* __DVBSLocator_FWD_DEFINED__ */


#ifndef __DVBCLocator_FWD_DEFINED__
#define __DVBCLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBCLocator DVBCLocator;
#else
typedef struct DVBCLocator DVBCLocator;
#endif /* __cplusplus */

#endif 	/* __DVBCLocator_FWD_DEFINED__ */


#ifndef __DVBTuneRequest_FWD_DEFINED__
#define __DVBTuneRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class DVBTuneRequest DVBTuneRequest;
#else
typedef struct DVBTuneRequest DVBTuneRequest;
#endif /* __cplusplus */

#endif 	/* __DVBTuneRequest_FWD_DEFINED__ */


#ifndef __CreatePropBagOnRegKey_FWD_DEFINED__
#define __CreatePropBagOnRegKey_FWD_DEFINED__

#ifdef __cplusplus
typedef class CreatePropBagOnRegKey CreatePropBagOnRegKey;
#else
typedef struct CreatePropBagOnRegKey CreatePropBagOnRegKey;
#endif /* __cplusplus */

#endif 	/* __CreatePropBagOnRegKey_FWD_DEFINED__ */


#ifndef __BroadcastEventService_FWD_DEFINED__
#define __BroadcastEventService_FWD_DEFINED__

#ifdef __cplusplus
typedef class BroadcastEventService BroadcastEventService;
#else
typedef struct BroadcastEventService BroadcastEventService;
#endif /* __cplusplus */

#endif 	/* __BroadcastEventService_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "comcat.h"
#include "strmif.h"
#include "bdatypes.h"
#include "regbag.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_tuner_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1999-2000.
//
//--------------------------------------------------------------------------
#pragma once
#include <bdatypes.h>





















enum __MIDL___MIDL_itf_tuner_0000_0001
    {	DISPID_TUNER_TS_UNIQUENAME	= 1,
	DISPID_TUNER_TS_FRIENDLYNAME	= 2,
	DISPID_TUNER_TS_CLSID	= 3,
	DISPID_TUNER_TS_NETWORKTYPE	= 4,
	DISPID_TUNER_TS__NETWORKTYPE	= 5,
	DISPID_TUNER_TS_CREATETUNEREQUEST	= 6,
	DISPID_TUNER_TS_ENUMCATEGORYGUIDS	= 7,
	DISPID_TUNER_TS_ENUMDEVICEMONIKERS	= 8,
	DISPID_TUNER_TS_DEFAULTPREFERREDCOMPONENTTYPES	= 9,
	DISPID_TUNER_TS_FREQMAP	= 10,
	DISPID_TUNER_TS_DEFLOCATOR	= 11,
	DISPID_TUNER_TS_CLONE	= 12,
	DISPID_TUNER_TR_TUNINGSPACE	= 1,
	DISPID_TUNER_TR_COMPONENTS	= 2,
	DISPID_TUNER_TR_CLONE	= 3,
	DISPID_TUNER_TR_LOCATOR	= 4,
	DISPID_TUNER_CT_CATEGORY	= 1,
	DISPID_TUNER_CT_MEDIAMAJORTYPE	= 2,
	DISPID_TUNER_CT__MEDIAMAJORTYPE	= 3,
	DISPID_TUNER_CT_MEDIASUBTYPE	= 4,
	DISPID_TUNER_CT__MEDIASUBTYPE	= 5,
	DISPID_TUNER_CT_MEDIAFORMATTYPE	= 6,
	DISPID_TUNER_CT__MEDIAFORMATTYPE	= 7,
	DISPID_TUNER_CT_MEDIATYPE	= 8,
	DISPID_TUNER_CT_CLONE	= 9,
	DISPID_TUNER_LCT_LANGID	= 100,
	DISPID_TUNER_MP2CT_TYPE	= 200,
	DISPID_TUNER_ATSCCT_FLAGS	= 300,
	DISPID_TUNER_L_CARRFREQ	= 1,
	DISPID_TUNER_L_INNERFECMETHOD	= 2,
	DISPID_TUNER_L_INNERFECRATE	= 3,
	DISPID_TUNER_L_OUTERFECMETHOD	= 4,
	DISPID_TUNER_L_OUTERFECRATE	= 5,
	DISPID_TUNER_L_MOD	= 6,
	DISPID_TUNER_L_SYMRATE	= 7,
	DISPID_TUNER_L_CLONE	= 8,
	DISPID_TUNER_L_ATSC_PHYS_CHANNEL	= 201,
	DISPID_TUNER_L_ATSC_TSID	= 202,
	DISPID_TUNER_L_DVBT_BANDWIDTH	= 301,
	DISPID_TUNER_L_DVBT_LPINNERFECMETHOD	= 302,
	DISPID_TUNER_L_DVBT_LPINNERFECRATE	= 303,
	DISPID_TUNER_L_DVBT_GUARDINTERVAL	= 304,
	DISPID_TUNER_L_DVBT_HALPHA	= 305,
	DISPID_TUNER_L_DVBT_TRANSMISSIONMODE	= 306,
	DISPID_TUNER_L_DVBT_INUSE	= 307,
	DISPID_TUNER_L_DVBS_POLARISATION	= 401,
	DISPID_TUNER_L_DVBS_WEST	= 402,
	DISPID_TUNER_L_DVBS_ORBITAL	= 403,
	DISPID_TUNER_L_DVBS_AZIMUTH	= 404,
	DISPID_TUNER_L_DVBS_ELEVATION	= 405,
	DISPID_TUNER_C_TYPE	= 1,
	DISPID_TUNER_C_STATUS	= 2,
	DISPID_TUNER_C_LANGID	= 3,
	DISPID_TUNER_C_DESCRIPTION	= 4,
	DISPID_TUNER_C_CLONE	= 5,
	DISPID_TUNER_C_MP2_PID	= 101,
	DISPID_TUNER_C_MP2_PCRPID	= 102,
	DISPID_TUNER_C_MP2_PROGNO	= 103,
	DISPID_TUNER_TS_DVB_SYSTEMTYPE	= 101,
	DISPID_TUNER_TS_DVB2_NETWORK_ID	= 102,
	DISPID_TUNER_TS_DVBS_LOW_OSC_FREQ	= 1001,
	DISPID_TUNER_TS_DVBS_HI_OSC_FREQ	= 1002,
	DISPID_TUNER_TS_DVBS_LNB_SWITCH_FREQ	= 1003,
	DISPID_TUNER_TS_DVBS_INPUT_RANGE	= 1004,
	DISPID_TUNER_TS_DVBS_SPECTRAL_INVERSION	= 1005,
	DISPID_TUNER_TS_AR_MINFREQUENCY	= 101,
	DISPID_TUNER_TS_AR_MAXFREQUENCY	= 102,
	DISPID_TUNER_TS_AR_STEP	= 103,
	DISPID_TUNER_TS_ATV_MINCHANNEL	= 101,
	DISPID_TUNER_TS_ATV_MAXCHANNEL	= 102,
	DISPID_TUNER_TS_ATV_INPUTTYPE	= 103,
	DISPID_TUNER_TS_ATV_COUNTRYCODE	= 104,
	DISPID_TUNER_TS_ATSC_MINMINORCHANNEL	= 201,
	DISPID_TUNER_TS_ATSC_MAXMINORCHANNEL	= 202,
	DISPID_TUNER_TS_ATSC_MINPHYSCHANNEL	= 203,
	DISPID_TUNER_TS_ATSC_MAXPHYSCHANNEL	= 204,
	DISPID_CHTUNER_ATVAC_CHANNEL	= 101,
	DISPID_CHTUNER_ATVDC_SYSTEM	= 101,
	DISPID_CHTUNER_ATVDC_CONTENT	= 102,
	DISPID_CHTUNER_CTR_CHANNEL	= 101,
	DISPID_CHTUNER_ACTR_MINOR_CHANNEL	= 201,
	DISPID_DVBTUNER_DVBC_ATTRIBUTESVALID	= 101,
	DISPID_DVBTUNER_DVBC_PID	= 102,
	DISPID_DVBTUNER_DVBC_TAG	= 103,
	DISPID_DVBTUNER_DVBC_COMPONENTTYPE	= 104,
	DISPID_DVBTUNER_ONID	= 101,
	DISPID_DVBTUNER_TSID	= 102,
	DISPID_DVBTUNER_SID	= 103,
	DISPID_MP2TUNER_TSID	= 101,
	DISPID_MP2TUNER_PROGNO	= 102,
	DISPID_MP2TUNERFACTORY_CREATETUNEREQUEST	= 1
    } ;


extern RPC_IF_HANDLE __MIDL_itf_tuner_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_tuner_0000_v0_0_s_ifspec;

#ifndef __ITuningSpaces_INTERFACE_DEFINED__
#define __ITuningSpaces_INTERFACE_DEFINED__

/* interface ITuningSpaces */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITuningSpaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("901284E4-33FE-4b69-8D63-634A596F3756")
    ITuningSpaces : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **NewEnum) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ITuningSpace **TuningSpace) = 0;
        
        virtual /* [helpstring][restricted][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_EnumTuningSpaces( 
            /* [retval][out] */ IEnumTuningSpaces **NewEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITuningSpacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuningSpaces * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuningSpaces * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuningSpaces * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITuningSpaces * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITuningSpaces * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITuningSpaces * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITuningSpaces * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITuningSpaces * This,
            /* [retval][out] */ long *Count);
        
        /* [restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITuningSpaces * This,
            /* [retval][out] */ IEnumVARIANT **NewEnum);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITuningSpaces * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][restricted][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnumTuningSpaces )( 
            ITuningSpaces * This,
            /* [retval][out] */ IEnumTuningSpaces **NewEnum);
        
        END_INTERFACE
    } ITuningSpacesVtbl;

    interface ITuningSpaces
    {
        CONST_VTBL struct ITuningSpacesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuningSpaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuningSpaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuningSpaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuningSpaces_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITuningSpaces_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITuningSpaces_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITuningSpaces_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITuningSpaces_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ITuningSpaces_get__NewEnum(This,NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,NewEnum)

#define ITuningSpaces_get_Item(This,varIndex,TuningSpace)	\
    (This)->lpVtbl -> get_Item(This,varIndex,TuningSpace)

#define ITuningSpaces_get_EnumTuningSpaces(This,NewEnum)	\
    (This)->lpVtbl -> get_EnumTuningSpaces(This,NewEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaces_get_Count_Proxy( 
    ITuningSpaces * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ITuningSpaces_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaces_get__NewEnum_Proxy( 
    ITuningSpaces * This,
    /* [retval][out] */ IEnumVARIANT **NewEnum);


void __RPC_STUB ITuningSpaces_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ITuningSpaces_get_Item_Proxy( 
    ITuningSpaces * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ITuningSpace **TuningSpace);


void __RPC_STUB ITuningSpaces_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaces_get_EnumTuningSpaces_Proxy( 
    ITuningSpaces * This,
    /* [retval][out] */ IEnumTuningSpaces **NewEnum);


void __RPC_STUB ITuningSpaces_get_EnumTuningSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuningSpaces_INTERFACE_DEFINED__ */


#ifndef __ITuningSpaceContainer_INTERFACE_DEFINED__
#define __ITuningSpaceContainer_INTERFACE_DEFINED__

/* interface ITuningSpaceContainer */
/* [unique][helpstring][nonextensible][hidden][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITuningSpaceContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B692E84-E2F1-11d2-9493-00C04F72D980")
    ITuningSpaceContainer : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **NewEnum) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ITuningSpace **TuningSpace) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT varIndex,
            /* [in] */ ITuningSpace *TuningSpace) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TuningSpacesForCLSID( 
            /* [in] */ BSTR SpaceCLSID,
            /* [retval][out] */ ITuningSpaces **NewColl) = 0;
        
        virtual /* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE _TuningSpacesForCLSID( 
            /* [in] */ REFCLSID SpaceCLSID,
            /* [retval][out] */ ITuningSpaces **NewColl) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TuningSpacesForName( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITuningSpaces **NewColl) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindID( 
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ long *ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ VARIANT *NewIndex) = 0;
        
        virtual /* [helpstring][restricted][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_EnumTuningSpaces( 
            /* [retval][out] */ IEnumTuningSpaces **ppEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MaxCount( 
            /* [retval][out] */ long *MaxCount) = 0;
        
        virtual /* [helpstring][restricted][hidden][propput] */ HRESULT STDMETHODCALLTYPE put_MaxCount( 
            /* [in] */ long MaxCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITuningSpaceContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuningSpaceContainer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuningSpaceContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuningSpaceContainer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITuningSpaceContainer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITuningSpaceContainer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITuningSpaceContainer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITuningSpaceContainer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITuningSpaceContainer * This,
            /* [retval][out] */ long *Count);
        
        /* [restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITuningSpaceContainer * This,
            /* [retval][out] */ IEnumVARIANT **NewEnum);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITuningSpaceContainer * This,
            /* [in] */ VARIANT varIndex,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            ITuningSpaceContainer * This,
            /* [in] */ VARIANT varIndex,
            /* [in] */ ITuningSpace *TuningSpace);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TuningSpacesForCLSID )( 
            ITuningSpaceContainer * This,
            /* [in] */ BSTR SpaceCLSID,
            /* [retval][out] */ ITuningSpaces **NewColl);
        
        /* [helpstring][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *_TuningSpacesForCLSID )( 
            ITuningSpaceContainer * This,
            /* [in] */ REFCLSID SpaceCLSID,
            /* [retval][out] */ ITuningSpaces **NewColl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TuningSpacesForName )( 
            ITuningSpaceContainer * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITuningSpaces **NewColl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindID )( 
            ITuningSpaceContainer * This,
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ long *ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITuningSpaceContainer * This,
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ VARIANT *NewIndex);
        
        /* [helpstring][restricted][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnumTuningSpaces )( 
            ITuningSpaceContainer * This,
            /* [retval][out] */ IEnumTuningSpaces **ppEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITuningSpaceContainer * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxCount )( 
            ITuningSpaceContainer * This,
            /* [retval][out] */ long *MaxCount);
        
        /* [helpstring][restricted][hidden][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxCount )( 
            ITuningSpaceContainer * This,
            /* [in] */ long MaxCount);
        
        END_INTERFACE
    } ITuningSpaceContainerVtbl;

    interface ITuningSpaceContainer
    {
        CONST_VTBL struct ITuningSpaceContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuningSpaceContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuningSpaceContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuningSpaceContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuningSpaceContainer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITuningSpaceContainer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITuningSpaceContainer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITuningSpaceContainer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITuningSpaceContainer_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ITuningSpaceContainer_get__NewEnum(This,NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,NewEnum)

#define ITuningSpaceContainer_get_Item(This,varIndex,TuningSpace)	\
    (This)->lpVtbl -> get_Item(This,varIndex,TuningSpace)

#define ITuningSpaceContainer_put_Item(This,varIndex,TuningSpace)	\
    (This)->lpVtbl -> put_Item(This,varIndex,TuningSpace)

#define ITuningSpaceContainer_TuningSpacesForCLSID(This,SpaceCLSID,NewColl)	\
    (This)->lpVtbl -> TuningSpacesForCLSID(This,SpaceCLSID,NewColl)

#define ITuningSpaceContainer__TuningSpacesForCLSID(This,SpaceCLSID,NewColl)	\
    (This)->lpVtbl -> _TuningSpacesForCLSID(This,SpaceCLSID,NewColl)

#define ITuningSpaceContainer_TuningSpacesForName(This,Name,NewColl)	\
    (This)->lpVtbl -> TuningSpacesForName(This,Name,NewColl)

#define ITuningSpaceContainer_FindID(This,TuningSpace,ID)	\
    (This)->lpVtbl -> FindID(This,TuningSpace,ID)

#define ITuningSpaceContainer_Add(This,TuningSpace,NewIndex)	\
    (This)->lpVtbl -> Add(This,TuningSpace,NewIndex)

#define ITuningSpaceContainer_get_EnumTuningSpaces(This,ppEnum)	\
    (This)->lpVtbl -> get_EnumTuningSpaces(This,ppEnum)

#define ITuningSpaceContainer_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITuningSpaceContainer_get_MaxCount(This,MaxCount)	\
    (This)->lpVtbl -> get_MaxCount(This,MaxCount)

#define ITuningSpaceContainer_put_MaxCount(This,MaxCount)	\
    (This)->lpVtbl -> put_MaxCount(This,MaxCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_get_Count_Proxy( 
    ITuningSpaceContainer * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ITuningSpaceContainer_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_get__NewEnum_Proxy( 
    ITuningSpaceContainer * This,
    /* [retval][out] */ IEnumVARIANT **NewEnum);


void __RPC_STUB ITuningSpaceContainer_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_get_Item_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ VARIANT varIndex,
    /* [retval][out] */ ITuningSpace **TuningSpace);


void __RPC_STUB ITuningSpaceContainer_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_put_Item_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ VARIANT varIndex,
    /* [in] */ ITuningSpace *TuningSpace);


void __RPC_STUB ITuningSpaceContainer_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_TuningSpacesForCLSID_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ BSTR SpaceCLSID,
    /* [retval][out] */ ITuningSpaces **NewColl);


void __RPC_STUB ITuningSpaceContainer_TuningSpacesForCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer__TuningSpacesForCLSID_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ REFCLSID SpaceCLSID,
    /* [retval][out] */ ITuningSpaces **NewColl);


void __RPC_STUB ITuningSpaceContainer__TuningSpacesForCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_TuningSpacesForName_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITuningSpaces **NewColl);


void __RPC_STUB ITuningSpaceContainer_TuningSpacesForName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_FindID_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ ITuningSpace *TuningSpace,
    /* [retval][out] */ long *ID);


void __RPC_STUB ITuningSpaceContainer_FindID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_Add_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ ITuningSpace *TuningSpace,
    /* [retval][out] */ VARIANT *NewIndex);


void __RPC_STUB ITuningSpaceContainer_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_get_EnumTuningSpaces_Proxy( 
    ITuningSpaceContainer * This,
    /* [retval][out] */ IEnumTuningSpaces **ppEnum);


void __RPC_STUB ITuningSpaceContainer_get_EnumTuningSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_Remove_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITuningSpaceContainer_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_get_MaxCount_Proxy( 
    ITuningSpaceContainer * This,
    /* [retval][out] */ long *MaxCount);


void __RPC_STUB ITuningSpaceContainer_get_MaxCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpaceContainer_put_MaxCount_Proxy( 
    ITuningSpaceContainer * This,
    /* [in] */ long MaxCount);


void __RPC_STUB ITuningSpaceContainer_put_MaxCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuningSpaceContainer_INTERFACE_DEFINED__ */


#ifndef __ITuningSpace_INTERFACE_DEFINED__
#define __ITuningSpace_INTERFACE_DEFINED__

/* interface ITuningSpace */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("061C6E30-E622-11d2-9493-00C04F72D980")
    ITuningSpace : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UniqueName( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UniqueName( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FriendlyName( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FriendlyName( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CLSID( 
            /* [retval][out] */ BSTR *SpaceCLSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetworkType( 
            /* [retval][out] */ BSTR *NetworkTypeGuid) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NetworkType( 
            /* [in] */ BSTR NetworkTypeGuid) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NetworkType( 
            /* [retval][out] */ GUID *NetworkTypeGuid) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put__NetworkType( 
            /* [in] */ REFCLSID NetworkTypeGuid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTuneRequest( 
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
        virtual /* [restricted][hidden][id] */ HRESULT STDMETHODCALLTYPE EnumCategoryGUIDs( 
            /* [retval][out] */ IEnumGUID **ppEnum) = 0;
        
        virtual /* [restricted][hidden][id] */ HRESULT STDMETHODCALLTYPE EnumDeviceMonikers( 
            /* [retval][out] */ IEnumMoniker **ppEnum) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultPreferredComponentTypes( 
            /* [retval][out] */ IComponentTypes **ComponentTypes) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultPreferredComponentTypes( 
            /* [in] */ IComponentTypes *NewComponentTypes) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FrequencyMapping( 
            /* [retval][out] */ BSTR *pMapping) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FrequencyMapping( 
            BSTR Mapping) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultLocator( 
            /* [retval][out] */ ILocator **LocatorVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultLocator( 
            /* [in] */ ILocator *LocatorVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITuningSpace **NewTS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            ITuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            ITuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            ITuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            ITuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            ITuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            ITuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            ITuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            ITuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            ITuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            ITuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            ITuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            ITuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            ITuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            ITuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            ITuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            ITuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            ITuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            ITuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        END_INTERFACE
    } ITuningSpaceVtbl;

    interface ITuningSpace
    {
        CONST_VTBL struct ITuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define ITuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define ITuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define ITuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define ITuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define ITuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define ITuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define ITuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define ITuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define ITuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define ITuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define ITuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define ITuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define ITuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define ITuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define ITuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define ITuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define ITuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define ITuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_UniqueName_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB ITuningSpace_get_UniqueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_UniqueName_Proxy( 
    ITuningSpace * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITuningSpace_put_UniqueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_FriendlyName_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB ITuningSpace_get_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_FriendlyName_Proxy( 
    ITuningSpace * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITuningSpace_put_FriendlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_CLSID_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ BSTR *SpaceCLSID);


void __RPC_STUB ITuningSpace_get_CLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_NetworkType_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ BSTR *NetworkTypeGuid);


void __RPC_STUB ITuningSpace_get_NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_NetworkType_Proxy( 
    ITuningSpace * This,
    /* [in] */ BSTR NetworkTypeGuid);


void __RPC_STUB ITuningSpace_put_NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get__NetworkType_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ GUID *NetworkTypeGuid);


void __RPC_STUB ITuningSpace_get__NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put__NetworkType_Proxy( 
    ITuningSpace * This,
    /* [in] */ REFCLSID NetworkTypeGuid);


void __RPC_STUB ITuningSpace_put__NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITuningSpace_CreateTuneRequest_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuningSpace_CreateTuneRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id] */ HRESULT STDMETHODCALLTYPE ITuningSpace_EnumCategoryGUIDs_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ IEnumGUID **ppEnum);


void __RPC_STUB ITuningSpace_EnumCategoryGUIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id] */ HRESULT STDMETHODCALLTYPE ITuningSpace_EnumDeviceMonikers_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ IEnumMoniker **ppEnum);


void __RPC_STUB ITuningSpace_EnumDeviceMonikers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_DefaultPreferredComponentTypes_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ IComponentTypes **ComponentTypes);


void __RPC_STUB ITuningSpace_get_DefaultPreferredComponentTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_DefaultPreferredComponentTypes_Proxy( 
    ITuningSpace * This,
    /* [in] */ IComponentTypes *NewComponentTypes);


void __RPC_STUB ITuningSpace_put_DefaultPreferredComponentTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_FrequencyMapping_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ BSTR *pMapping);


void __RPC_STUB ITuningSpace_get_FrequencyMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_FrequencyMapping_Proxy( 
    ITuningSpace * This,
    BSTR Mapping);


void __RPC_STUB ITuningSpace_put_FrequencyMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITuningSpace_get_DefaultLocator_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ ILocator **LocatorVal);


void __RPC_STUB ITuningSpace_get_DefaultLocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITuningSpace_put_DefaultLocator_Proxy( 
    ITuningSpace * This,
    /* [in] */ ILocator *LocatorVal);


void __RPC_STUB ITuningSpace_put_DefaultLocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITuningSpace_Clone_Proxy( 
    ITuningSpace * This,
    /* [retval][out] */ ITuningSpace **NewTS);


void __RPC_STUB ITuningSpace_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuningSpace_INTERFACE_DEFINED__ */


#ifndef __IEnumTuningSpaces_INTERFACE_DEFINED__
#define __IEnumTuningSpaces_INTERFACE_DEFINED__

/* interface IEnumTuningSpaces */
/* [unique][uuid][object][restricted][hidden] */ 


EXTERN_C const IID IID_IEnumTuningSpaces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B8EB248-FC2B-11d2-9D8C-00C04F72D980")
    IEnumTuningSpaces : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ITuningSpace **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTuningSpaces **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumTuningSpacesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTuningSpaces * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTuningSpaces * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTuningSpaces * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTuningSpaces * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ITuningSpace **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTuningSpaces * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTuningSpaces * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTuningSpaces * This,
            /* [out] */ IEnumTuningSpaces **ppEnum);
        
        END_INTERFACE
    } IEnumTuningSpacesVtbl;

    interface IEnumTuningSpaces
    {
        CONST_VTBL struct IEnumTuningSpacesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTuningSpaces_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumTuningSpaces_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumTuningSpaces_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumTuningSpaces_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumTuningSpaces_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumTuningSpaces_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumTuningSpaces_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumTuningSpaces_Next_Proxy( 
    IEnumTuningSpaces * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ITuningSpace **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumTuningSpaces_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuningSpaces_Skip_Proxy( 
    IEnumTuningSpaces * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumTuningSpaces_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuningSpaces_Reset_Proxy( 
    IEnumTuningSpaces * This);


void __RPC_STUB IEnumTuningSpaces_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuningSpaces_Clone_Proxy( 
    IEnumTuningSpaces * This,
    /* [out] */ IEnumTuningSpaces **ppEnum);


void __RPC_STUB IEnumTuningSpaces_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumTuningSpaces_INTERFACE_DEFINED__ */


#ifndef __IDVBTuningSpace_INTERFACE_DEFINED__
#define __IDVBTuningSpace_INTERFACE_DEFINED__

/* interface IDVBTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IDVBTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADA0B268-3B19-4e5b-ACC4-49F852BE13BA")
    IDVBTuningSpace : public ITuningSpace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemType( 
            /* [retval][out] */ DVBSystemType *SysType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SystemType( 
            /* [in] */ DVBSystemType SysType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IDVBTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IDVBTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IDVBTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IDVBTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IDVBTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IDVBTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IDVBTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemType )( 
            IDVBTuningSpace * This,
            /* [retval][out] */ DVBSystemType *SysType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SystemType )( 
            IDVBTuningSpace * This,
            /* [in] */ DVBSystemType SysType);
        
        END_INTERFACE
    } IDVBTuningSpaceVtbl;

    interface IDVBTuningSpace
    {
        CONST_VTBL struct IDVBTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IDVBTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IDVBTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IDVBTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IDVBTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IDVBTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IDVBTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IDVBTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IDVBTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IDVBTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IDVBTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IDVBTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IDVBTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IDVBTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IDVBTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IDVBTuningSpace_get_SystemType(This,SysType)	\
    (This)->lpVtbl -> get_SystemType(This,SysType)

#define IDVBTuningSpace_put_SystemType(This,SysType)	\
    (This)->lpVtbl -> put_SystemType(This,SysType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTuningSpace_get_SystemType_Proxy( 
    IDVBTuningSpace * This,
    /* [retval][out] */ DVBSystemType *SysType);


void __RPC_STUB IDVBTuningSpace_get_SystemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTuningSpace_put_SystemType_Proxy( 
    IDVBTuningSpace * This,
    /* [in] */ DVBSystemType SysType);


void __RPC_STUB IDVBTuningSpace_put_SystemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBTuningSpace_INTERFACE_DEFINED__ */


#ifndef __IDVBTuningSpace2_INTERFACE_DEFINED__
#define __IDVBTuningSpace2_INTERFACE_DEFINED__

/* interface IDVBTuningSpace2 */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IDVBTuningSpace2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("843188B4-CE62-43db-966B-8145A094E040")
    IDVBTuningSpace2 : public IDVBTuningSpace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetworkID( 
            /* [retval][out] */ long *NetworkID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NetworkID( 
            /* [in] */ long NetworkID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBTuningSpace2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBTuningSpace2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBTuningSpace2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBTuningSpace2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBTuningSpace2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBTuningSpace2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBTuningSpace2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBTuningSpace2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IDVBTuningSpace2 * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IDVBTuningSpace2 * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IDVBTuningSpace2 * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IDVBTuningSpace2 * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IDVBTuningSpace2 * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IDVBTuningSpace2 * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IDVBTuningSpace2 * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemType )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ DVBSystemType *SysType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SystemType )( 
            IDVBTuningSpace2 * This,
            /* [in] */ DVBSystemType SysType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkID )( 
            IDVBTuningSpace2 * This,
            /* [retval][out] */ long *NetworkID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkID )( 
            IDVBTuningSpace2 * This,
            /* [in] */ long NetworkID);
        
        END_INTERFACE
    } IDVBTuningSpace2Vtbl;

    interface IDVBTuningSpace2
    {
        CONST_VTBL struct IDVBTuningSpace2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBTuningSpace2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBTuningSpace2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBTuningSpace2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBTuningSpace2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBTuningSpace2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBTuningSpace2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBTuningSpace2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBTuningSpace2_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IDVBTuningSpace2_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IDVBTuningSpace2_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IDVBTuningSpace2_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IDVBTuningSpace2_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IDVBTuningSpace2_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace2_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace2_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace2_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IDVBTuningSpace2_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IDVBTuningSpace2_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IDVBTuningSpace2_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IDVBTuningSpace2_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IDVBTuningSpace2_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IDVBTuningSpace2_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IDVBTuningSpace2_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IDVBTuningSpace2_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IDVBTuningSpace2_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IDVBTuningSpace2_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IDVBTuningSpace2_get_SystemType(This,SysType)	\
    (This)->lpVtbl -> get_SystemType(This,SysType)

#define IDVBTuningSpace2_put_SystemType(This,SysType)	\
    (This)->lpVtbl -> put_SystemType(This,SysType)


#define IDVBTuningSpace2_get_NetworkID(This,NetworkID)	\
    (This)->lpVtbl -> get_NetworkID(This,NetworkID)

#define IDVBTuningSpace2_put_NetworkID(This,NetworkID)	\
    (This)->lpVtbl -> put_NetworkID(This,NetworkID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTuningSpace2_get_NetworkID_Proxy( 
    IDVBTuningSpace2 * This,
    /* [retval][out] */ long *NetworkID);


void __RPC_STUB IDVBTuningSpace2_get_NetworkID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTuningSpace2_put_NetworkID_Proxy( 
    IDVBTuningSpace2 * This,
    /* [in] */ long NetworkID);


void __RPC_STUB IDVBTuningSpace2_put_NetworkID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBTuningSpace2_INTERFACE_DEFINED__ */


#ifndef __IDVBSTuningSpace_INTERFACE_DEFINED__
#define __IDVBSTuningSpace_INTERFACE_DEFINED__

/* interface IDVBSTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IDVBSTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDF7BE60-D954-42fd-A972-78971958E470")
    IDVBSTuningSpace : public IDVBTuningSpace2
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LowOscillator( 
            /* [retval][out] */ long *LowOscillator) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LowOscillator( 
            /* [in] */ long LowOscillator) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HighOscillator( 
            /* [retval][out] */ long *HighOscillator) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HighOscillator( 
            /* [in] */ long HighOscillator) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LNBSwitch( 
            /* [retval][out] */ long *LNBSwitch) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LNBSwitch( 
            /* [in] */ long LNBSwitch) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputRange( 
            /* [retval][out] */ BSTR *InputRange) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputRange( 
            /* [in] */ BSTR InputRange) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SpectralInversion( 
            /* [retval][out] */ SpectralInversion *SpectralInversionVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SpectralInversion( 
            /* [in] */ SpectralInversion SpectralInversionVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBSTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBSTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBSTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBSTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBSTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBSTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBSTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBSTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IDVBSTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IDVBSTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IDVBSTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IDVBSTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IDVBSTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IDVBSTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IDVBSTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemType )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ DVBSystemType *SysType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SystemType )( 
            IDVBSTuningSpace * This,
            /* [in] */ DVBSystemType SysType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkID )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ long *NetworkID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkID )( 
            IDVBSTuningSpace * This,
            /* [in] */ long NetworkID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LowOscillator )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ long *LowOscillator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LowOscillator )( 
            IDVBSTuningSpace * This,
            /* [in] */ long LowOscillator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HighOscillator )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ long *HighOscillator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HighOscillator )( 
            IDVBSTuningSpace * This,
            /* [in] */ long HighOscillator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LNBSwitch )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ long *LNBSwitch);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LNBSwitch )( 
            IDVBSTuningSpace * This,
            /* [in] */ long LNBSwitch);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputRange )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ BSTR *InputRange);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputRange )( 
            IDVBSTuningSpace * This,
            /* [in] */ BSTR InputRange);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpectralInversion )( 
            IDVBSTuningSpace * This,
            /* [retval][out] */ SpectralInversion *SpectralInversionVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SpectralInversion )( 
            IDVBSTuningSpace * This,
            /* [in] */ SpectralInversion SpectralInversionVal);
        
        END_INTERFACE
    } IDVBSTuningSpaceVtbl;

    interface IDVBSTuningSpace
    {
        CONST_VTBL struct IDVBSTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBSTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBSTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBSTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBSTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBSTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBSTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBSTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBSTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IDVBSTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IDVBSTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IDVBSTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IDVBSTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IDVBSTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IDVBSTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IDVBSTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IDVBSTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IDVBSTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IDVBSTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IDVBSTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IDVBSTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IDVBSTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IDVBSTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IDVBSTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IDVBSTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IDVBSTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IDVBSTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IDVBSTuningSpace_get_SystemType(This,SysType)	\
    (This)->lpVtbl -> get_SystemType(This,SysType)

#define IDVBSTuningSpace_put_SystemType(This,SysType)	\
    (This)->lpVtbl -> put_SystemType(This,SysType)


#define IDVBSTuningSpace_get_NetworkID(This,NetworkID)	\
    (This)->lpVtbl -> get_NetworkID(This,NetworkID)

#define IDVBSTuningSpace_put_NetworkID(This,NetworkID)	\
    (This)->lpVtbl -> put_NetworkID(This,NetworkID)


#define IDVBSTuningSpace_get_LowOscillator(This,LowOscillator)	\
    (This)->lpVtbl -> get_LowOscillator(This,LowOscillator)

#define IDVBSTuningSpace_put_LowOscillator(This,LowOscillator)	\
    (This)->lpVtbl -> put_LowOscillator(This,LowOscillator)

#define IDVBSTuningSpace_get_HighOscillator(This,HighOscillator)	\
    (This)->lpVtbl -> get_HighOscillator(This,HighOscillator)

#define IDVBSTuningSpace_put_HighOscillator(This,HighOscillator)	\
    (This)->lpVtbl -> put_HighOscillator(This,HighOscillator)

#define IDVBSTuningSpace_get_LNBSwitch(This,LNBSwitch)	\
    (This)->lpVtbl -> get_LNBSwitch(This,LNBSwitch)

#define IDVBSTuningSpace_put_LNBSwitch(This,LNBSwitch)	\
    (This)->lpVtbl -> put_LNBSwitch(This,LNBSwitch)

#define IDVBSTuningSpace_get_InputRange(This,InputRange)	\
    (This)->lpVtbl -> get_InputRange(This,InputRange)

#define IDVBSTuningSpace_put_InputRange(This,InputRange)	\
    (This)->lpVtbl -> put_InputRange(This,InputRange)

#define IDVBSTuningSpace_get_SpectralInversion(This,SpectralInversionVal)	\
    (This)->lpVtbl -> get_SpectralInversion(This,SpectralInversionVal)

#define IDVBSTuningSpace_put_SpectralInversion(This,SpectralInversionVal)	\
    (This)->lpVtbl -> put_SpectralInversion(This,SpectralInversionVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_get_LowOscillator_Proxy( 
    IDVBSTuningSpace * This,
    /* [retval][out] */ long *LowOscillator);


void __RPC_STUB IDVBSTuningSpace_get_LowOscillator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_put_LowOscillator_Proxy( 
    IDVBSTuningSpace * This,
    /* [in] */ long LowOscillator);


void __RPC_STUB IDVBSTuningSpace_put_LowOscillator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_get_HighOscillator_Proxy( 
    IDVBSTuningSpace * This,
    /* [retval][out] */ long *HighOscillator);


void __RPC_STUB IDVBSTuningSpace_get_HighOscillator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_put_HighOscillator_Proxy( 
    IDVBSTuningSpace * This,
    /* [in] */ long HighOscillator);


void __RPC_STUB IDVBSTuningSpace_put_HighOscillator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_get_LNBSwitch_Proxy( 
    IDVBSTuningSpace * This,
    /* [retval][out] */ long *LNBSwitch);


void __RPC_STUB IDVBSTuningSpace_get_LNBSwitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_put_LNBSwitch_Proxy( 
    IDVBSTuningSpace * This,
    /* [in] */ long LNBSwitch);


void __RPC_STUB IDVBSTuningSpace_put_LNBSwitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_get_InputRange_Proxy( 
    IDVBSTuningSpace * This,
    /* [retval][out] */ BSTR *InputRange);


void __RPC_STUB IDVBSTuningSpace_get_InputRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_put_InputRange_Proxy( 
    IDVBSTuningSpace * This,
    /* [in] */ BSTR InputRange);


void __RPC_STUB IDVBSTuningSpace_put_InputRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_get_SpectralInversion_Proxy( 
    IDVBSTuningSpace * This,
    /* [retval][out] */ SpectralInversion *SpectralInversionVal);


void __RPC_STUB IDVBSTuningSpace_get_SpectralInversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSTuningSpace_put_SpectralInversion_Proxy( 
    IDVBSTuningSpace * This,
    /* [in] */ SpectralInversion SpectralInversionVal);


void __RPC_STUB IDVBSTuningSpace_put_SpectralInversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBSTuningSpace_INTERFACE_DEFINED__ */


#ifndef __IAuxInTuningSpace_INTERFACE_DEFINED__
#define __IAuxInTuningSpace_INTERFACE_DEFINED__

/* interface IAuxInTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IAuxInTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E48244B8-7E17-4f76-A763-5090FF1E2F30")
    IAuxInTuningSpace : public ITuningSpace
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAuxInTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAuxInTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAuxInTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAuxInTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAuxInTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAuxInTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAuxInTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAuxInTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IAuxInTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IAuxInTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IAuxInTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IAuxInTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IAuxInTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IAuxInTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IAuxInTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAuxInTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        END_INTERFACE
    } IAuxInTuningSpaceVtbl;

    interface IAuxInTuningSpace
    {
        CONST_VTBL struct IAuxInTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAuxInTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAuxInTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAuxInTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAuxInTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAuxInTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAuxInTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAuxInTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAuxInTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IAuxInTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IAuxInTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IAuxInTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IAuxInTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IAuxInTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IAuxInTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IAuxInTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IAuxInTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IAuxInTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IAuxInTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IAuxInTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IAuxInTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IAuxInTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IAuxInTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IAuxInTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IAuxInTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IAuxInTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IAuxInTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAuxInTuningSpace_INTERFACE_DEFINED__ */


#ifndef __IAnalogTVTuningSpace_INTERFACE_DEFINED__
#define __IAnalogTVTuningSpace_INTERFACE_DEFINED__

/* interface IAnalogTVTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IAnalogTVTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A6E293C-2595-11d3-B64C-00C04F79498E")
    IAnalogTVTuningSpace : public ITuningSpace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinChannel( 
            /* [retval][out] */ long *MinChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinChannel( 
            /* [in] */ long NewMinChannelVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxChannel( 
            /* [retval][out] */ long *MaxChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxChannel( 
            /* [in] */ long NewMaxChannelVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputType( 
            /* [retval][out] */ TunerInputType *InputTypeVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputType( 
            /* [in] */ TunerInputType NewInputTypeVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CountryCode( 
            /* [retval][out] */ long *CountryCodeVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CountryCode( 
            /* [in] */ long NewCountryCodeVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnalogTVTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnalogTVTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnalogTVTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAnalogTVTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IAnalogTVTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinChannel )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ long *MinChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinChannel )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ long NewMinChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxChannel )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ long *MaxChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxChannel )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ long NewMaxChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputType )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ TunerInputType *InputTypeVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputType )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ TunerInputType NewInputTypeVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountryCode )( 
            IAnalogTVTuningSpace * This,
            /* [retval][out] */ long *CountryCodeVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CountryCode )( 
            IAnalogTVTuningSpace * This,
            /* [in] */ long NewCountryCodeVal);
        
        END_INTERFACE
    } IAnalogTVTuningSpaceVtbl;

    interface IAnalogTVTuningSpace
    {
        CONST_VTBL struct IAnalogTVTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnalogTVTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnalogTVTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnalogTVTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnalogTVTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnalogTVTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnalogTVTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnalogTVTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnalogTVTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IAnalogTVTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IAnalogTVTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IAnalogTVTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IAnalogTVTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IAnalogTVTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IAnalogTVTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IAnalogTVTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IAnalogTVTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IAnalogTVTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IAnalogTVTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IAnalogTVTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IAnalogTVTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IAnalogTVTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IAnalogTVTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IAnalogTVTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IAnalogTVTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IAnalogTVTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IAnalogTVTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IAnalogTVTuningSpace_get_MinChannel(This,MinChannelVal)	\
    (This)->lpVtbl -> get_MinChannel(This,MinChannelVal)

#define IAnalogTVTuningSpace_put_MinChannel(This,NewMinChannelVal)	\
    (This)->lpVtbl -> put_MinChannel(This,NewMinChannelVal)

#define IAnalogTVTuningSpace_get_MaxChannel(This,MaxChannelVal)	\
    (This)->lpVtbl -> get_MaxChannel(This,MaxChannelVal)

#define IAnalogTVTuningSpace_put_MaxChannel(This,NewMaxChannelVal)	\
    (This)->lpVtbl -> put_MaxChannel(This,NewMaxChannelVal)

#define IAnalogTVTuningSpace_get_InputType(This,InputTypeVal)	\
    (This)->lpVtbl -> get_InputType(This,InputTypeVal)

#define IAnalogTVTuningSpace_put_InputType(This,NewInputTypeVal)	\
    (This)->lpVtbl -> put_InputType(This,NewInputTypeVal)

#define IAnalogTVTuningSpace_get_CountryCode(This,CountryCodeVal)	\
    (This)->lpVtbl -> get_CountryCode(This,CountryCodeVal)

#define IAnalogTVTuningSpace_put_CountryCode(This,NewCountryCodeVal)	\
    (This)->lpVtbl -> put_CountryCode(This,NewCountryCodeVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_get_MinChannel_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [retval][out] */ long *MinChannelVal);


void __RPC_STUB IAnalogTVTuningSpace_get_MinChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_put_MinChannel_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [in] */ long NewMinChannelVal);


void __RPC_STUB IAnalogTVTuningSpace_put_MinChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_get_MaxChannel_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [retval][out] */ long *MaxChannelVal);


void __RPC_STUB IAnalogTVTuningSpace_get_MaxChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_put_MaxChannel_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [in] */ long NewMaxChannelVal);


void __RPC_STUB IAnalogTVTuningSpace_put_MaxChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_get_InputType_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [retval][out] */ TunerInputType *InputTypeVal);


void __RPC_STUB IAnalogTVTuningSpace_get_InputType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_put_InputType_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [in] */ TunerInputType NewInputTypeVal);


void __RPC_STUB IAnalogTVTuningSpace_put_InputType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_get_CountryCode_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [retval][out] */ long *CountryCodeVal);


void __RPC_STUB IAnalogTVTuningSpace_get_CountryCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogTVTuningSpace_put_CountryCode_Proxy( 
    IAnalogTVTuningSpace * This,
    /* [in] */ long NewCountryCodeVal);


void __RPC_STUB IAnalogTVTuningSpace_put_CountryCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnalogTVTuningSpace_INTERFACE_DEFINED__ */


#ifndef __IATSCTuningSpace_INTERFACE_DEFINED__
#define __IATSCTuningSpace_INTERFACE_DEFINED__

/* interface IATSCTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IATSCTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0369B4E2-45B6-11d3-B650-00C04F79498E")
    IATSCTuningSpace : public IAnalogTVTuningSpace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinMinorChannel( 
            /* [retval][out] */ long *MinMinorChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinMinorChannel( 
            /* [in] */ long NewMinMinorChannelVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMinorChannel( 
            /* [retval][out] */ long *MaxMinorChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxMinorChannel( 
            /* [in] */ long NewMaxMinorChannelVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinPhysicalChannel( 
            /* [retval][out] */ long *MinPhysicalChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinPhysicalChannel( 
            /* [in] */ long NewMinPhysicalChannelVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxPhysicalChannel( 
            /* [retval][out] */ long *MaxPhysicalChannelVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxPhysicalChannel( 
            /* [in] */ long NewMaxPhysicalChannelVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATSCTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATSCTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATSCTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATSCTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATSCTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATSCTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATSCTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATSCTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IATSCTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IATSCTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IATSCTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IATSCTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IATSCTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IATSCTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IATSCTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MinChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMinChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MaxChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMaxChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputType )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ TunerInputType *InputTypeVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputType )( 
            IATSCTuningSpace * This,
            /* [in] */ TunerInputType NewInputTypeVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountryCode )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *CountryCodeVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CountryCode )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewCountryCodeVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinMinorChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MinMinorChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinMinorChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMinMinorChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxMinorChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MaxMinorChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxMinorChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMaxMinorChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinPhysicalChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MinPhysicalChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinPhysicalChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMinPhysicalChannelVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxPhysicalChannel )( 
            IATSCTuningSpace * This,
            /* [retval][out] */ long *MaxPhysicalChannelVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxPhysicalChannel )( 
            IATSCTuningSpace * This,
            /* [in] */ long NewMaxPhysicalChannelVal);
        
        END_INTERFACE
    } IATSCTuningSpaceVtbl;

    interface IATSCTuningSpace
    {
        CONST_VTBL struct IATSCTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATSCTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATSCTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATSCTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATSCTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATSCTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATSCTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATSCTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATSCTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IATSCTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IATSCTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IATSCTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IATSCTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IATSCTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IATSCTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IATSCTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IATSCTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IATSCTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IATSCTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IATSCTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IATSCTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IATSCTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IATSCTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IATSCTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IATSCTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IATSCTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IATSCTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IATSCTuningSpace_get_MinChannel(This,MinChannelVal)	\
    (This)->lpVtbl -> get_MinChannel(This,MinChannelVal)

#define IATSCTuningSpace_put_MinChannel(This,NewMinChannelVal)	\
    (This)->lpVtbl -> put_MinChannel(This,NewMinChannelVal)

#define IATSCTuningSpace_get_MaxChannel(This,MaxChannelVal)	\
    (This)->lpVtbl -> get_MaxChannel(This,MaxChannelVal)

#define IATSCTuningSpace_put_MaxChannel(This,NewMaxChannelVal)	\
    (This)->lpVtbl -> put_MaxChannel(This,NewMaxChannelVal)

#define IATSCTuningSpace_get_InputType(This,InputTypeVal)	\
    (This)->lpVtbl -> get_InputType(This,InputTypeVal)

#define IATSCTuningSpace_put_InputType(This,NewInputTypeVal)	\
    (This)->lpVtbl -> put_InputType(This,NewInputTypeVal)

#define IATSCTuningSpace_get_CountryCode(This,CountryCodeVal)	\
    (This)->lpVtbl -> get_CountryCode(This,CountryCodeVal)

#define IATSCTuningSpace_put_CountryCode(This,NewCountryCodeVal)	\
    (This)->lpVtbl -> put_CountryCode(This,NewCountryCodeVal)


#define IATSCTuningSpace_get_MinMinorChannel(This,MinMinorChannelVal)	\
    (This)->lpVtbl -> get_MinMinorChannel(This,MinMinorChannelVal)

#define IATSCTuningSpace_put_MinMinorChannel(This,NewMinMinorChannelVal)	\
    (This)->lpVtbl -> put_MinMinorChannel(This,NewMinMinorChannelVal)

#define IATSCTuningSpace_get_MaxMinorChannel(This,MaxMinorChannelVal)	\
    (This)->lpVtbl -> get_MaxMinorChannel(This,MaxMinorChannelVal)

#define IATSCTuningSpace_put_MaxMinorChannel(This,NewMaxMinorChannelVal)	\
    (This)->lpVtbl -> put_MaxMinorChannel(This,NewMaxMinorChannelVal)

#define IATSCTuningSpace_get_MinPhysicalChannel(This,MinPhysicalChannelVal)	\
    (This)->lpVtbl -> get_MinPhysicalChannel(This,MinPhysicalChannelVal)

#define IATSCTuningSpace_put_MinPhysicalChannel(This,NewMinPhysicalChannelVal)	\
    (This)->lpVtbl -> put_MinPhysicalChannel(This,NewMinPhysicalChannelVal)

#define IATSCTuningSpace_get_MaxPhysicalChannel(This,MaxPhysicalChannelVal)	\
    (This)->lpVtbl -> get_MaxPhysicalChannel(This,MaxPhysicalChannelVal)

#define IATSCTuningSpace_put_MaxPhysicalChannel(This,NewMaxPhysicalChannelVal)	\
    (This)->lpVtbl -> put_MaxPhysicalChannel(This,NewMaxPhysicalChannelVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_get_MinMinorChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [retval][out] */ long *MinMinorChannelVal);


void __RPC_STUB IATSCTuningSpace_get_MinMinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_put_MinMinorChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [in] */ long NewMinMinorChannelVal);


void __RPC_STUB IATSCTuningSpace_put_MinMinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_get_MaxMinorChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [retval][out] */ long *MaxMinorChannelVal);


void __RPC_STUB IATSCTuningSpace_get_MaxMinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_put_MaxMinorChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [in] */ long NewMaxMinorChannelVal);


void __RPC_STUB IATSCTuningSpace_put_MaxMinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_get_MinPhysicalChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [retval][out] */ long *MinPhysicalChannelVal);


void __RPC_STUB IATSCTuningSpace_get_MinPhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_put_MinPhysicalChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [in] */ long NewMinPhysicalChannelVal);


void __RPC_STUB IATSCTuningSpace_put_MinPhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_get_MaxPhysicalChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [retval][out] */ long *MaxPhysicalChannelVal);


void __RPC_STUB IATSCTuningSpace_get_MaxPhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCTuningSpace_put_MaxPhysicalChannel_Proxy( 
    IATSCTuningSpace * This,
    /* [in] */ long NewMaxPhysicalChannelVal);


void __RPC_STUB IATSCTuningSpace_put_MaxPhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATSCTuningSpace_INTERFACE_DEFINED__ */


#ifndef __IAnalogRadioTuningSpace_INTERFACE_DEFINED__
#define __IAnalogRadioTuningSpace_INTERFACE_DEFINED__

/* interface IAnalogRadioTuningSpace */
/* [unique][uuid][nonextensible][oleautomation][dual][hidden][object] */ 


EXTERN_C const IID IID_IAnalogRadioTuningSpace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A6E293B-2595-11d3-B64C-00C04F79498E")
    IAnalogRadioTuningSpace : public ITuningSpace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinFrequency( 
            /* [retval][out] */ long *MinFrequencyVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinFrequency( 
            /* [in] */ long NewMinFrequencyVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxFrequency( 
            /* [retval][out] */ long *MaxFrequencyVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxFrequency( 
            /* [in] */ long NewMaxFrequencyVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Step( 
            /* [retval][out] */ long *StepVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Step( 
            /* [in] */ long NewStepVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnalogRadioTuningSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnalogRadioTuningSpace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnalogRadioTuningSpace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAnalogRadioTuningSpace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueName )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UniqueName )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FriendlyName )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FriendlyName )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CLSID )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ BSTR *SpaceCLSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NetworkType )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ BSTR *NetworkTypeGuid);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetworkType )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ BSTR NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NetworkType )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ GUID *NetworkTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__NetworkType )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ REFCLSID NetworkTypeGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumCategoryGUIDs )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ IEnumGUID **ppEnum);
        
        /* [restricted][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceMonikers )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ IEnumMoniker **ppEnum);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPreferredComponentTypes )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPreferredComponentTypes )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ IComponentTypes *NewComponentTypes);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrequencyMapping )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ BSTR *pMapping);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrequencyMapping )( 
            IAnalogRadioTuningSpace * This,
            BSTR Mapping);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultLocator )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ ILocator **LocatorVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultLocator )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ ILocator *LocatorVal);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ ITuningSpace **NewTS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinFrequency )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ long *MinFrequencyVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinFrequency )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ long NewMinFrequencyVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxFrequency )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ long *MaxFrequencyVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxFrequency )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ long NewMaxFrequencyVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Step )( 
            IAnalogRadioTuningSpace * This,
            /* [retval][out] */ long *StepVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Step )( 
            IAnalogRadioTuningSpace * This,
            /* [in] */ long NewStepVal);
        
        END_INTERFACE
    } IAnalogRadioTuningSpaceVtbl;

    interface IAnalogRadioTuningSpace
    {
        CONST_VTBL struct IAnalogRadioTuningSpaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnalogRadioTuningSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnalogRadioTuningSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnalogRadioTuningSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnalogRadioTuningSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnalogRadioTuningSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnalogRadioTuningSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnalogRadioTuningSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnalogRadioTuningSpace_get_UniqueName(This,Name)	\
    (This)->lpVtbl -> get_UniqueName(This,Name)

#define IAnalogRadioTuningSpace_put_UniqueName(This,Name)	\
    (This)->lpVtbl -> put_UniqueName(This,Name)

#define IAnalogRadioTuningSpace_get_FriendlyName(This,Name)	\
    (This)->lpVtbl -> get_FriendlyName(This,Name)

#define IAnalogRadioTuningSpace_put_FriendlyName(This,Name)	\
    (This)->lpVtbl -> put_FriendlyName(This,Name)

#define IAnalogRadioTuningSpace_get_CLSID(This,SpaceCLSID)	\
    (This)->lpVtbl -> get_CLSID(This,SpaceCLSID)

#define IAnalogRadioTuningSpace_get_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get_NetworkType(This,NetworkTypeGuid)

#define IAnalogRadioTuningSpace_put_NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put_NetworkType(This,NetworkTypeGuid)

#define IAnalogRadioTuningSpace_get__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> get__NetworkType(This,NetworkTypeGuid)

#define IAnalogRadioTuningSpace_put__NetworkType(This,NetworkTypeGuid)	\
    (This)->lpVtbl -> put__NetworkType(This,NetworkTypeGuid)

#define IAnalogRadioTuningSpace_CreateTuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuneRequest)

#define IAnalogRadioTuningSpace_EnumCategoryGUIDs(This,ppEnum)	\
    (This)->lpVtbl -> EnumCategoryGUIDs(This,ppEnum)

#define IAnalogRadioTuningSpace_EnumDeviceMonikers(This,ppEnum)	\
    (This)->lpVtbl -> EnumDeviceMonikers(This,ppEnum)

#define IAnalogRadioTuningSpace_get_DefaultPreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_DefaultPreferredComponentTypes(This,ComponentTypes)

#define IAnalogRadioTuningSpace_put_DefaultPreferredComponentTypes(This,NewComponentTypes)	\
    (This)->lpVtbl -> put_DefaultPreferredComponentTypes(This,NewComponentTypes)

#define IAnalogRadioTuningSpace_get_FrequencyMapping(This,pMapping)	\
    (This)->lpVtbl -> get_FrequencyMapping(This,pMapping)

#define IAnalogRadioTuningSpace_put_FrequencyMapping(This,Mapping)	\
    (This)->lpVtbl -> put_FrequencyMapping(This,Mapping)

#define IAnalogRadioTuningSpace_get_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> get_DefaultLocator(This,LocatorVal)

#define IAnalogRadioTuningSpace_put_DefaultLocator(This,LocatorVal)	\
    (This)->lpVtbl -> put_DefaultLocator(This,LocatorVal)

#define IAnalogRadioTuningSpace_Clone(This,NewTS)	\
    (This)->lpVtbl -> Clone(This,NewTS)


#define IAnalogRadioTuningSpace_get_MinFrequency(This,MinFrequencyVal)	\
    (This)->lpVtbl -> get_MinFrequency(This,MinFrequencyVal)

#define IAnalogRadioTuningSpace_put_MinFrequency(This,NewMinFrequencyVal)	\
    (This)->lpVtbl -> put_MinFrequency(This,NewMinFrequencyVal)

#define IAnalogRadioTuningSpace_get_MaxFrequency(This,MaxFrequencyVal)	\
    (This)->lpVtbl -> get_MaxFrequency(This,MaxFrequencyVal)

#define IAnalogRadioTuningSpace_put_MaxFrequency(This,NewMaxFrequencyVal)	\
    (This)->lpVtbl -> put_MaxFrequency(This,NewMaxFrequencyVal)

#define IAnalogRadioTuningSpace_get_Step(This,StepVal)	\
    (This)->lpVtbl -> get_Step(This,StepVal)

#define IAnalogRadioTuningSpace_put_Step(This,NewStepVal)	\
    (This)->lpVtbl -> put_Step(This,NewStepVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_get_MinFrequency_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [retval][out] */ long *MinFrequencyVal);


void __RPC_STUB IAnalogRadioTuningSpace_get_MinFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_put_MinFrequency_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [in] */ long NewMinFrequencyVal);


void __RPC_STUB IAnalogRadioTuningSpace_put_MinFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_get_MaxFrequency_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [retval][out] */ long *MaxFrequencyVal);


void __RPC_STUB IAnalogRadioTuningSpace_get_MaxFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_put_MaxFrequency_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [in] */ long NewMaxFrequencyVal);


void __RPC_STUB IAnalogRadioTuningSpace_put_MaxFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_get_Step_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [retval][out] */ long *StepVal);


void __RPC_STUB IAnalogRadioTuningSpace_get_Step_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnalogRadioTuningSpace_put_Step_Proxy( 
    IAnalogRadioTuningSpace * This,
    /* [in] */ long NewStepVal);


void __RPC_STUB IAnalogRadioTuningSpace_put_Step_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnalogRadioTuningSpace_INTERFACE_DEFINED__ */


#ifndef __ITuneRequest_INTERFACE_DEFINED__
#define __ITuneRequest_INTERFACE_DEFINED__

/* interface ITuneRequest */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_ITuneRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07DDC146-FC3D-11d2-9D8C-00C04F72D980")
    ITuneRequest : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TuningSpace( 
            /* [retval][out] */ ITuningSpace **TuningSpace) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Components( 
            /* [retval][out] */ IComponents **Components) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITuneRequest **NewTuneRequest) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Locator( 
            /* [retval][out] */ ILocator **Locator) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Locator( 
            /* [in] */ ILocator *Locator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITuneRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuneRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuneRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuneRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITuneRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITuneRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITuneRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITuneRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            ITuneRequest * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            ITuneRequest * This,
            /* [retval][out] */ IComponents **Components);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITuneRequest * This,
            /* [retval][out] */ ITuneRequest **NewTuneRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locator )( 
            ITuneRequest * This,
            /* [retval][out] */ ILocator **Locator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locator )( 
            ITuneRequest * This,
            /* [in] */ ILocator *Locator);
        
        END_INTERFACE
    } ITuneRequestVtbl;

    interface ITuneRequest
    {
        CONST_VTBL struct ITuneRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuneRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuneRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuneRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuneRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITuneRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITuneRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITuneRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITuneRequest_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define ITuneRequest_get_Components(This,Components)	\
    (This)->lpVtbl -> get_Components(This,Components)

#define ITuneRequest_Clone(This,NewTuneRequest)	\
    (This)->lpVtbl -> Clone(This,NewTuneRequest)

#define ITuneRequest_get_Locator(This,Locator)	\
    (This)->lpVtbl -> get_Locator(This,Locator)

#define ITuneRequest_put_Locator(This,Locator)	\
    (This)->lpVtbl -> put_Locator(This,Locator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuneRequest_get_TuningSpace_Proxy( 
    ITuneRequest * This,
    /* [retval][out] */ ITuningSpace **TuningSpace);


void __RPC_STUB ITuneRequest_get_TuningSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuneRequest_get_Components_Proxy( 
    ITuneRequest * This,
    /* [retval][out] */ IComponents **Components);


void __RPC_STUB ITuneRequest_get_Components_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITuneRequest_Clone_Proxy( 
    ITuneRequest * This,
    /* [retval][out] */ ITuneRequest **NewTuneRequest);


void __RPC_STUB ITuneRequest_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITuneRequest_get_Locator_Proxy( 
    ITuneRequest * This,
    /* [retval][out] */ ILocator **Locator);


void __RPC_STUB ITuneRequest_get_Locator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITuneRequest_put_Locator_Proxy( 
    ITuneRequest * This,
    /* [in] */ ILocator *Locator);


void __RPC_STUB ITuneRequest_put_Locator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuneRequest_INTERFACE_DEFINED__ */


#ifndef __IChannelTuneRequest_INTERFACE_DEFINED__
#define __IChannelTuneRequest_INTERFACE_DEFINED__

/* interface IChannelTuneRequest */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IChannelTuneRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0369B4E0-45B6-11d3-B650-00C04F79498E")
    IChannelTuneRequest : public ITuneRequest
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Channel( 
            /* [retval][out] */ long *Channel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Channel( 
            /* [in] */ long Channel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChannelTuneRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChannelTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChannelTuneRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChannelTuneRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChannelTuneRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChannelTuneRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChannelTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChannelTuneRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IChannelTuneRequest * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            IChannelTuneRequest * This,
            /* [retval][out] */ IComponents **Components);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IChannelTuneRequest * This,
            /* [retval][out] */ ITuneRequest **NewTuneRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locator )( 
            IChannelTuneRequest * This,
            /* [retval][out] */ ILocator **Locator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locator )( 
            IChannelTuneRequest * This,
            /* [in] */ ILocator *Locator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IChannelTuneRequest * This,
            /* [retval][out] */ long *Channel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IChannelTuneRequest * This,
            /* [in] */ long Channel);
        
        END_INTERFACE
    } IChannelTuneRequestVtbl;

    interface IChannelTuneRequest
    {
        CONST_VTBL struct IChannelTuneRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChannelTuneRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChannelTuneRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChannelTuneRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChannelTuneRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IChannelTuneRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IChannelTuneRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IChannelTuneRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IChannelTuneRequest_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define IChannelTuneRequest_get_Components(This,Components)	\
    (This)->lpVtbl -> get_Components(This,Components)

#define IChannelTuneRequest_Clone(This,NewTuneRequest)	\
    (This)->lpVtbl -> Clone(This,NewTuneRequest)

#define IChannelTuneRequest_get_Locator(This,Locator)	\
    (This)->lpVtbl -> get_Locator(This,Locator)

#define IChannelTuneRequest_put_Locator(This,Locator)	\
    (This)->lpVtbl -> put_Locator(This,Locator)


#define IChannelTuneRequest_get_Channel(This,Channel)	\
    (This)->lpVtbl -> get_Channel(This,Channel)

#define IChannelTuneRequest_put_Channel(This,Channel)	\
    (This)->lpVtbl -> put_Channel(This,Channel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChannelTuneRequest_get_Channel_Proxy( 
    IChannelTuneRequest * This,
    /* [retval][out] */ long *Channel);


void __RPC_STUB IChannelTuneRequest_get_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChannelTuneRequest_put_Channel_Proxy( 
    IChannelTuneRequest * This,
    /* [in] */ long Channel);


void __RPC_STUB IChannelTuneRequest_put_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChannelTuneRequest_INTERFACE_DEFINED__ */


#ifndef __IATSCChannelTuneRequest_INTERFACE_DEFINED__
#define __IATSCChannelTuneRequest_INTERFACE_DEFINED__

/* interface IATSCChannelTuneRequest */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IATSCChannelTuneRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0369B4E1-45B6-11d3-B650-00C04F79498E")
    IATSCChannelTuneRequest : public IChannelTuneRequest
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinorChannel( 
            /* [retval][out] */ long *MinorChannel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinorChannel( 
            /* [in] */ long MinorChannel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATSCChannelTuneRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATSCChannelTuneRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATSCChannelTuneRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATSCChannelTuneRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ IComponents **Components);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ ITuneRequest **NewTuneRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locator )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ ILocator **Locator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locator )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ ILocator *Locator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ long *Channel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ long Channel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorChannel )( 
            IATSCChannelTuneRequest * This,
            /* [retval][out] */ long *MinorChannel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MinorChannel )( 
            IATSCChannelTuneRequest * This,
            /* [in] */ long MinorChannel);
        
        END_INTERFACE
    } IATSCChannelTuneRequestVtbl;

    interface IATSCChannelTuneRequest
    {
        CONST_VTBL struct IATSCChannelTuneRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATSCChannelTuneRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATSCChannelTuneRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATSCChannelTuneRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATSCChannelTuneRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATSCChannelTuneRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATSCChannelTuneRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATSCChannelTuneRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATSCChannelTuneRequest_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define IATSCChannelTuneRequest_get_Components(This,Components)	\
    (This)->lpVtbl -> get_Components(This,Components)

#define IATSCChannelTuneRequest_Clone(This,NewTuneRequest)	\
    (This)->lpVtbl -> Clone(This,NewTuneRequest)

#define IATSCChannelTuneRequest_get_Locator(This,Locator)	\
    (This)->lpVtbl -> get_Locator(This,Locator)

#define IATSCChannelTuneRequest_put_Locator(This,Locator)	\
    (This)->lpVtbl -> put_Locator(This,Locator)


#define IATSCChannelTuneRequest_get_Channel(This,Channel)	\
    (This)->lpVtbl -> get_Channel(This,Channel)

#define IATSCChannelTuneRequest_put_Channel(This,Channel)	\
    (This)->lpVtbl -> put_Channel(This,Channel)


#define IATSCChannelTuneRequest_get_MinorChannel(This,MinorChannel)	\
    (This)->lpVtbl -> get_MinorChannel(This,MinorChannel)

#define IATSCChannelTuneRequest_put_MinorChannel(This,MinorChannel)	\
    (This)->lpVtbl -> put_MinorChannel(This,MinorChannel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCChannelTuneRequest_get_MinorChannel_Proxy( 
    IATSCChannelTuneRequest * This,
    /* [retval][out] */ long *MinorChannel);


void __RPC_STUB IATSCChannelTuneRequest_get_MinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCChannelTuneRequest_put_MinorChannel_Proxy( 
    IATSCChannelTuneRequest * This,
    /* [in] */ long MinorChannel);


void __RPC_STUB IATSCChannelTuneRequest_put_MinorChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATSCChannelTuneRequest_INTERFACE_DEFINED__ */


#ifndef __IDVBTuneRequest_INTERFACE_DEFINED__
#define __IDVBTuneRequest_INTERFACE_DEFINED__

/* interface IDVBTuneRequest */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IDVBTuneRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D6F567E-A636-42bb-83BA-CE4C1704AFA2")
    IDVBTuneRequest : public ITuneRequest
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ONID( 
            /* [retval][out] */ long *ONID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ONID( 
            /* [in] */ long ONID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSID( 
            /* [retval][out] */ long *TSID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSID( 
            /* [in] */ long TSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SID( 
            /* [retval][out] */ long *SID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SID( 
            /* [in] */ long SID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBTuneRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBTuneRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBTuneRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBTuneRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBTuneRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBTuneRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBTuneRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ IComponents **Components);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ ITuneRequest **NewTuneRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locator )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ ILocator **Locator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locator )( 
            IDVBTuneRequest * This,
            /* [in] */ ILocator *Locator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ONID )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ long *ONID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ONID )( 
            IDVBTuneRequest * This,
            /* [in] */ long ONID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSID )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ long *TSID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSID )( 
            IDVBTuneRequest * This,
            /* [in] */ long TSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SID )( 
            IDVBTuneRequest * This,
            /* [retval][out] */ long *SID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SID )( 
            IDVBTuneRequest * This,
            /* [in] */ long SID);
        
        END_INTERFACE
    } IDVBTuneRequestVtbl;

    interface IDVBTuneRequest
    {
        CONST_VTBL struct IDVBTuneRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBTuneRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBTuneRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBTuneRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBTuneRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBTuneRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBTuneRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBTuneRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBTuneRequest_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define IDVBTuneRequest_get_Components(This,Components)	\
    (This)->lpVtbl -> get_Components(This,Components)

#define IDVBTuneRequest_Clone(This,NewTuneRequest)	\
    (This)->lpVtbl -> Clone(This,NewTuneRequest)

#define IDVBTuneRequest_get_Locator(This,Locator)	\
    (This)->lpVtbl -> get_Locator(This,Locator)

#define IDVBTuneRequest_put_Locator(This,Locator)	\
    (This)->lpVtbl -> put_Locator(This,Locator)


#define IDVBTuneRequest_get_ONID(This,ONID)	\
    (This)->lpVtbl -> get_ONID(This,ONID)

#define IDVBTuneRequest_put_ONID(This,ONID)	\
    (This)->lpVtbl -> put_ONID(This,ONID)

#define IDVBTuneRequest_get_TSID(This,TSID)	\
    (This)->lpVtbl -> get_TSID(This,TSID)

#define IDVBTuneRequest_put_TSID(This,TSID)	\
    (This)->lpVtbl -> put_TSID(This,TSID)

#define IDVBTuneRequest_get_SID(This,SID)	\
    (This)->lpVtbl -> get_SID(This,SID)

#define IDVBTuneRequest_put_SID(This,SID)	\
    (This)->lpVtbl -> put_SID(This,SID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_get_ONID_Proxy( 
    IDVBTuneRequest * This,
    /* [retval][out] */ long *ONID);


void __RPC_STUB IDVBTuneRequest_get_ONID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_put_ONID_Proxy( 
    IDVBTuneRequest * This,
    /* [in] */ long ONID);


void __RPC_STUB IDVBTuneRequest_put_ONID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_get_TSID_Proxy( 
    IDVBTuneRequest * This,
    /* [retval][out] */ long *TSID);


void __RPC_STUB IDVBTuneRequest_get_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_put_TSID_Proxy( 
    IDVBTuneRequest * This,
    /* [in] */ long TSID);


void __RPC_STUB IDVBTuneRequest_put_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_get_SID_Proxy( 
    IDVBTuneRequest * This,
    /* [retval][out] */ long *SID);


void __RPC_STUB IDVBTuneRequest_get_SID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTuneRequest_put_SID_Proxy( 
    IDVBTuneRequest * This,
    /* [in] */ long SID);


void __RPC_STUB IDVBTuneRequest_put_SID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBTuneRequest_INTERFACE_DEFINED__ */


#ifndef __IMPEG2TuneRequest_INTERFACE_DEFINED__
#define __IMPEG2TuneRequest_INTERFACE_DEFINED__

/* interface IMPEG2TuneRequest */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IMPEG2TuneRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB7D987F-8A01-42ad-B8AE-574DEEE44D1A")
    IMPEG2TuneRequest : public ITuneRequest
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSID( 
            /* [retval][out] */ long *TSID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSID( 
            /* [in] */ long TSID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgNo( 
            /* [retval][out] */ long *ProgNo) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProgNo( 
            /* [in] */ long ProgNo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2TuneRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2TuneRequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2TuneRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2TuneRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMPEG2TuneRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMPEG2TuneRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMPEG2TuneRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMPEG2TuneRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ IComponents **Components);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ ITuneRequest **NewTuneRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locator )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ ILocator **Locator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locator )( 
            IMPEG2TuneRequest * This,
            /* [in] */ ILocator *Locator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSID )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ long *TSID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSID )( 
            IMPEG2TuneRequest * This,
            /* [in] */ long TSID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgNo )( 
            IMPEG2TuneRequest * This,
            /* [retval][out] */ long *ProgNo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProgNo )( 
            IMPEG2TuneRequest * This,
            /* [in] */ long ProgNo);
        
        END_INTERFACE
    } IMPEG2TuneRequestVtbl;

    interface IMPEG2TuneRequest
    {
        CONST_VTBL struct IMPEG2TuneRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2TuneRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2TuneRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2TuneRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2TuneRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMPEG2TuneRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMPEG2TuneRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMPEG2TuneRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMPEG2TuneRequest_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define IMPEG2TuneRequest_get_Components(This,Components)	\
    (This)->lpVtbl -> get_Components(This,Components)

#define IMPEG2TuneRequest_Clone(This,NewTuneRequest)	\
    (This)->lpVtbl -> Clone(This,NewTuneRequest)

#define IMPEG2TuneRequest_get_Locator(This,Locator)	\
    (This)->lpVtbl -> get_Locator(This,Locator)

#define IMPEG2TuneRequest_put_Locator(This,Locator)	\
    (This)->lpVtbl -> put_Locator(This,Locator)


#define IMPEG2TuneRequest_get_TSID(This,TSID)	\
    (This)->lpVtbl -> get_TSID(This,TSID)

#define IMPEG2TuneRequest_put_TSID(This,TSID)	\
    (This)->lpVtbl -> put_TSID(This,TSID)

#define IMPEG2TuneRequest_get_ProgNo(This,ProgNo)	\
    (This)->lpVtbl -> get_ProgNo(This,ProgNo)

#define IMPEG2TuneRequest_put_ProgNo(This,ProgNo)	\
    (This)->lpVtbl -> put_ProgNo(This,ProgNo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2TuneRequest_get_TSID_Proxy( 
    IMPEG2TuneRequest * This,
    /* [retval][out] */ long *TSID);


void __RPC_STUB IMPEG2TuneRequest_get_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2TuneRequest_put_TSID_Proxy( 
    IMPEG2TuneRequest * This,
    /* [in] */ long TSID);


void __RPC_STUB IMPEG2TuneRequest_put_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2TuneRequest_get_ProgNo_Proxy( 
    IMPEG2TuneRequest * This,
    /* [retval][out] */ long *ProgNo);


void __RPC_STUB IMPEG2TuneRequest_get_ProgNo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2TuneRequest_put_ProgNo_Proxy( 
    IMPEG2TuneRequest * This,
    /* [in] */ long ProgNo);


void __RPC_STUB IMPEG2TuneRequest_put_ProgNo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2TuneRequest_INTERFACE_DEFINED__ */


#ifndef __IMPEG2TuneRequestFactory_INTERFACE_DEFINED__
#define __IMPEG2TuneRequestFactory_INTERFACE_DEFINED__

/* interface IMPEG2TuneRequestFactory */
/* [unique][helpstring][oleautomation][dual][uuid][hidden][nonextensible][object] */ 


EXTERN_C const IID IID_IMPEG2TuneRequestFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("14E11ABD-EE37-4893-9EA1-6964DE933E39")
    IMPEG2TuneRequestFactory : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTuneRequest( 
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ IMPEG2TuneRequest **TuneRequest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2TuneRequestFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2TuneRequestFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2TuneRequestFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2TuneRequestFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMPEG2TuneRequestFactory * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMPEG2TuneRequestFactory * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMPEG2TuneRequestFactory * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMPEG2TuneRequestFactory * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTuneRequest )( 
            IMPEG2TuneRequestFactory * This,
            /* [in] */ ITuningSpace *TuningSpace,
            /* [retval][out] */ IMPEG2TuneRequest **TuneRequest);
        
        END_INTERFACE
    } IMPEG2TuneRequestFactoryVtbl;

    interface IMPEG2TuneRequestFactory
    {
        CONST_VTBL struct IMPEG2TuneRequestFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2TuneRequestFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2TuneRequestFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2TuneRequestFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2TuneRequestFactory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMPEG2TuneRequestFactory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMPEG2TuneRequestFactory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMPEG2TuneRequestFactory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMPEG2TuneRequestFactory_CreateTuneRequest(This,TuningSpace,TuneRequest)	\
    (This)->lpVtbl -> CreateTuneRequest(This,TuningSpace,TuneRequest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMPEG2TuneRequestFactory_CreateTuneRequest_Proxy( 
    IMPEG2TuneRequestFactory * This,
    /* [in] */ ITuningSpace *TuningSpace,
    /* [retval][out] */ IMPEG2TuneRequest **TuneRequest);


void __RPC_STUB IMPEG2TuneRequestFactory_CreateTuneRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2TuneRequestFactory_INTERFACE_DEFINED__ */


#ifndef __IMPEG2TuneRequestSupport_INTERFACE_DEFINED__
#define __IMPEG2TuneRequestSupport_INTERFACE_DEFINED__

/* interface IMPEG2TuneRequestSupport */
/* [unique][helpstring][uuid][nonextensible][restricted][hidden][object] */ 


EXTERN_C const IID IID_IMPEG2TuneRequestSupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B9D5FC3-5BBC-4b6c-BB18-B9D10E3EEEBF")
    IMPEG2TuneRequestSupport : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2TuneRequestSupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2TuneRequestSupport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2TuneRequestSupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2TuneRequestSupport * This);
        
        END_INTERFACE
    } IMPEG2TuneRequestSupportVtbl;

    interface IMPEG2TuneRequestSupport
    {
        CONST_VTBL struct IMPEG2TuneRequestSupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2TuneRequestSupport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2TuneRequestSupport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2TuneRequestSupport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPEG2TuneRequestSupport_INTERFACE_DEFINED__ */


#ifndef __ITuner_INTERFACE_DEFINED__
#define __ITuner_INTERFACE_DEFINED__

/* interface ITuner */
/* [unique][helpstring][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_ITuner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28C52640-018A-11d3-9D8E-00C04F72D980")
    ITuner : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TuningSpace( 
            /* [retval][out] */ ITuningSpace **TuningSpace) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TuningSpace( 
            /* [in] */ ITuningSpace *TuningSpace) = 0;
        
        virtual /* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE EnumTuningSpaces( 
            /* [retval][out] */ IEnumTuningSpaces **ppEnum) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TuneRequest( 
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TuneRequest( 
            /* [in] */ ITuneRequest *TuneRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Validate( 
            /* [in] */ ITuneRequest *TuneRequest) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredComponentTypes( 
            /* [retval][out] */ IComponentTypes **ComponentTypes) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PreferredComponentTypes( 
            /* [in] */ IComponentTypes *ComponentTypes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SignalStrength( 
            /* [retval][out] */ long *Strength) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TriggerSignalEvents( 
            /* [in] */ long Interval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITunerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuner * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            ITuner * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuningSpace )( 
            ITuner * This,
            /* [in] */ ITuningSpace *TuningSpace);
        
        /* [helpstring][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *EnumTuningSpaces )( 
            ITuner * This,
            /* [retval][out] */ IEnumTuningSpaces **ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuneRequest )( 
            ITuner * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuneRequest )( 
            ITuner * This,
            /* [in] */ ITuneRequest *TuneRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Validate )( 
            ITuner * This,
            /* [in] */ ITuneRequest *TuneRequest);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreferredComponentTypes )( 
            ITuner * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreferredComponentTypes )( 
            ITuner * This,
            /* [in] */ IComponentTypes *ComponentTypes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignalStrength )( 
            ITuner * This,
            /* [retval][out] */ long *Strength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TriggerSignalEvents )( 
            ITuner * This,
            /* [in] */ long Interval);
        
        END_INTERFACE
    } ITunerVtbl;

    interface ITuner
    {
        CONST_VTBL struct ITunerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuner_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define ITuner_put_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> put_TuningSpace(This,TuningSpace)

#define ITuner_EnumTuningSpaces(This,ppEnum)	\
    (This)->lpVtbl -> EnumTuningSpaces(This,ppEnum)

#define ITuner_get_TuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> get_TuneRequest(This,TuneRequest)

#define ITuner_put_TuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> put_TuneRequest(This,TuneRequest)

#define ITuner_Validate(This,TuneRequest)	\
    (This)->lpVtbl -> Validate(This,TuneRequest)

#define ITuner_get_PreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_PreferredComponentTypes(This,ComponentTypes)

#define ITuner_put_PreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> put_PreferredComponentTypes(This,ComponentTypes)

#define ITuner_get_SignalStrength(This,Strength)	\
    (This)->lpVtbl -> get_SignalStrength(This,Strength)

#define ITuner_TriggerSignalEvents(This,Interval)	\
    (This)->lpVtbl -> TriggerSignalEvents(This,Interval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuner_get_TuningSpace_Proxy( 
    ITuner * This,
    /* [retval][out] */ ITuningSpace **TuningSpace);


void __RPC_STUB ITuner_get_TuningSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITuner_put_TuningSpace_Proxy( 
    ITuner * This,
    /* [in] */ ITuningSpace *TuningSpace);


void __RPC_STUB ITuner_put_TuningSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE ITuner_EnumTuningSpaces_Proxy( 
    ITuner * This,
    /* [retval][out] */ IEnumTuningSpaces **ppEnum);


void __RPC_STUB ITuner_EnumTuningSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuner_get_TuneRequest_Proxy( 
    ITuner * This,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuner_get_TuneRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITuner_put_TuneRequest_Proxy( 
    ITuner * This,
    /* [in] */ ITuneRequest *TuneRequest);


void __RPC_STUB ITuner_put_TuneRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuner_Validate_Proxy( 
    ITuner * This,
    /* [in] */ ITuneRequest *TuneRequest);


void __RPC_STUB ITuner_Validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuner_get_PreferredComponentTypes_Proxy( 
    ITuner * This,
    /* [retval][out] */ IComponentTypes **ComponentTypes);


void __RPC_STUB ITuner_get_PreferredComponentTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITuner_put_PreferredComponentTypes_Proxy( 
    ITuner * This,
    /* [in] */ IComponentTypes *ComponentTypes);


void __RPC_STUB ITuner_put_PreferredComponentTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITuner_get_SignalStrength_Proxy( 
    ITuner * This,
    /* [retval][out] */ long *Strength);


void __RPC_STUB ITuner_get_SignalStrength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuner_TriggerSignalEvents_Proxy( 
    ITuner * This,
    /* [in] */ long Interval);


void __RPC_STUB ITuner_TriggerSignalEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuner_INTERFACE_DEFINED__ */


#ifndef __IScanningTuner_INTERFACE_DEFINED__
#define __IScanningTuner_INTERFACE_DEFINED__

/* interface IScanningTuner */
/* [unique][helpstring][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IScanningTuner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1DFD0A5C-0284-11d3-9D8E-00C04F72D980")
    IScanningTuner : public ITuner
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SeekUp( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SeekDown( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScanUp( 
            /* [in] */ long MillisecondsPause) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScanDown( 
            /* [in] */ long MillisecondsPause) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AutoProgram( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScanningTunerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanningTuner * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanningTuner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanningTuner * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IScanningTuner * This,
            /* [retval][out] */ ITuningSpace **TuningSpace);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuningSpace )( 
            IScanningTuner * This,
            /* [in] */ ITuningSpace *TuningSpace);
        
        /* [helpstring][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *EnumTuningSpaces )( 
            IScanningTuner * This,
            /* [retval][out] */ IEnumTuningSpaces **ppEnum);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TuneRequest )( 
            IScanningTuner * This,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuneRequest )( 
            IScanningTuner * This,
            /* [in] */ ITuneRequest *TuneRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Validate )( 
            IScanningTuner * This,
            /* [in] */ ITuneRequest *TuneRequest);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreferredComponentTypes )( 
            IScanningTuner * This,
            /* [retval][out] */ IComponentTypes **ComponentTypes);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreferredComponentTypes )( 
            IScanningTuner * This,
            /* [in] */ IComponentTypes *ComponentTypes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignalStrength )( 
            IScanningTuner * This,
            /* [retval][out] */ long *Strength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TriggerSignalEvents )( 
            IScanningTuner * This,
            /* [in] */ long Interval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SeekUp )( 
            IScanningTuner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SeekDown )( 
            IScanningTuner * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScanUp )( 
            IScanningTuner * This,
            /* [in] */ long MillisecondsPause);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScanDown )( 
            IScanningTuner * This,
            /* [in] */ long MillisecondsPause);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AutoProgram )( 
            IScanningTuner * This);
        
        END_INTERFACE
    } IScanningTunerVtbl;

    interface IScanningTuner
    {
        CONST_VTBL struct IScanningTunerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanningTuner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScanningTuner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScanningTuner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScanningTuner_get_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,TuningSpace)

#define IScanningTuner_put_TuningSpace(This,TuningSpace)	\
    (This)->lpVtbl -> put_TuningSpace(This,TuningSpace)

#define IScanningTuner_EnumTuningSpaces(This,ppEnum)	\
    (This)->lpVtbl -> EnumTuningSpaces(This,ppEnum)

#define IScanningTuner_get_TuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> get_TuneRequest(This,TuneRequest)

#define IScanningTuner_put_TuneRequest(This,TuneRequest)	\
    (This)->lpVtbl -> put_TuneRequest(This,TuneRequest)

#define IScanningTuner_Validate(This,TuneRequest)	\
    (This)->lpVtbl -> Validate(This,TuneRequest)

#define IScanningTuner_get_PreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> get_PreferredComponentTypes(This,ComponentTypes)

#define IScanningTuner_put_PreferredComponentTypes(This,ComponentTypes)	\
    (This)->lpVtbl -> put_PreferredComponentTypes(This,ComponentTypes)

#define IScanningTuner_get_SignalStrength(This,Strength)	\
    (This)->lpVtbl -> get_SignalStrength(This,Strength)

#define IScanningTuner_TriggerSignalEvents(This,Interval)	\
    (This)->lpVtbl -> TriggerSignalEvents(This,Interval)


#define IScanningTuner_SeekUp(This)	\
    (This)->lpVtbl -> SeekUp(This)

#define IScanningTuner_SeekDown(This)	\
    (This)->lpVtbl -> SeekDown(This)

#define IScanningTuner_ScanUp(This,MillisecondsPause)	\
    (This)->lpVtbl -> ScanUp(This,MillisecondsPause)

#define IScanningTuner_ScanDown(This,MillisecondsPause)	\
    (This)->lpVtbl -> ScanDown(This,MillisecondsPause)

#define IScanningTuner_AutoProgram(This)	\
    (This)->lpVtbl -> AutoProgram(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IScanningTuner_SeekUp_Proxy( 
    IScanningTuner * This);


void __RPC_STUB IScanningTuner_SeekUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IScanningTuner_SeekDown_Proxy( 
    IScanningTuner * This);


void __RPC_STUB IScanningTuner_SeekDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IScanningTuner_ScanUp_Proxy( 
    IScanningTuner * This,
    /* [in] */ long MillisecondsPause);


void __RPC_STUB IScanningTuner_ScanUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IScanningTuner_ScanDown_Proxy( 
    IScanningTuner * This,
    /* [in] */ long MillisecondsPause);


void __RPC_STUB IScanningTuner_ScanDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IScanningTuner_AutoProgram_Proxy( 
    IScanningTuner * This);


void __RPC_STUB IScanningTuner_AutoProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScanningTuner_INTERFACE_DEFINED__ */


#ifndef __IComponentType_INTERFACE_DEFINED__
#define __IComponentType_INTERFACE_DEFINED__

/* interface IComponentType */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IComponentType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A340DC0-0311-11d3-9D8E-00C04F72D980")
    IComponentType : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Category( 
            /* [retval][out] */ ComponentCategory *Category) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Category( 
            /* [in] */ ComponentCategory Category) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaMajorType( 
            /* [retval][out] */ BSTR *MediaMajorType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaMajorType( 
            /* [in] */ BSTR MediaMajorType) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__MediaMajorType( 
            /* [retval][out] */ GUID *MediaMajorTypeGuid) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put__MediaMajorType( 
            /* [in] */ REFCLSID MediaMajorTypeGuid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaSubType( 
            /* [retval][out] */ BSTR *MediaSubType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaSubType( 
            /* [in] */ BSTR MediaSubType) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__MediaSubType( 
            /* [retval][out] */ GUID *MediaSubTypeGuid) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put__MediaSubType( 
            /* [in] */ REFCLSID MediaSubTypeGuid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFormatType( 
            /* [retval][out] */ BSTR *MediaFormatType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaFormatType( 
            /* [in] */ BSTR MediaFormatType) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__MediaFormatType( 
            /* [retval][out] */ GUID *MediaFormatTypeGuid) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put__MediaFormatType( 
            /* [in] */ REFCLSID MediaFormatTypeGuid) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [retval][out] */ AM_MEDIA_TYPE *MediaType) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaType( 
            /* [in] */ AM_MEDIA_TYPE *MediaType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IComponentType **NewCT) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComponentTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentType * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentType * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponentType * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponentType * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponentType * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponentType * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Category )( 
            IComponentType * This,
            /* [retval][out] */ ComponentCategory *Category);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Category )( 
            IComponentType * This,
            /* [in] */ ComponentCategory Category);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaMajorType )( 
            IComponentType * This,
            /* [retval][out] */ BSTR *MediaMajorType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaMajorType )( 
            IComponentType * This,
            /* [in] */ BSTR MediaMajorType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaMajorType )( 
            IComponentType * This,
            /* [retval][out] */ GUID *MediaMajorTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaMajorType )( 
            IComponentType * This,
            /* [in] */ REFCLSID MediaMajorTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaSubType )( 
            IComponentType * This,
            /* [retval][out] */ BSTR *MediaSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaSubType )( 
            IComponentType * This,
            /* [in] */ BSTR MediaSubType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaSubType )( 
            IComponentType * This,
            /* [retval][out] */ GUID *MediaSubTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaSubType )( 
            IComponentType * This,
            /* [in] */ REFCLSID MediaSubTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFormatType )( 
            IComponentType * This,
            /* [retval][out] */ BSTR *MediaFormatType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaFormatType )( 
            IComponentType * This,
            /* [in] */ BSTR MediaFormatType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaFormatType )( 
            IComponentType * This,
            /* [retval][out] */ GUID *MediaFormatTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaFormatType )( 
            IComponentType * This,
            /* [in] */ REFCLSID MediaFormatTypeGuid);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            IComponentType * This,
            /* [retval][out] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaType )( 
            IComponentType * This,
            /* [in] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IComponentType * This,
            /* [retval][out] */ IComponentType **NewCT);
        
        END_INTERFACE
    } IComponentTypeVtbl;

    interface IComponentType
    {
        CONST_VTBL struct IComponentTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComponentType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComponentType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComponentType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComponentType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComponentType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComponentType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComponentType_get_Category(This,Category)	\
    (This)->lpVtbl -> get_Category(This,Category)

#define IComponentType_put_Category(This,Category)	\
    (This)->lpVtbl -> put_Category(This,Category)

#define IComponentType_get_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> get_MediaMajorType(This,MediaMajorType)

#define IComponentType_put_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> put_MediaMajorType(This,MediaMajorType)

#define IComponentType_get__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> get__MediaMajorType(This,MediaMajorTypeGuid)

#define IComponentType_put__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> put__MediaMajorType(This,MediaMajorTypeGuid)

#define IComponentType_get_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> get_MediaSubType(This,MediaSubType)

#define IComponentType_put_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> put_MediaSubType(This,MediaSubType)

#define IComponentType_get__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> get__MediaSubType(This,MediaSubTypeGuid)

#define IComponentType_put__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> put__MediaSubType(This,MediaSubTypeGuid)

#define IComponentType_get_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> get_MediaFormatType(This,MediaFormatType)

#define IComponentType_put_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> put_MediaFormatType(This,MediaFormatType)

#define IComponentType_get__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> get__MediaFormatType(This,MediaFormatTypeGuid)

#define IComponentType_put__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> put__MediaFormatType(This,MediaFormatTypeGuid)

#define IComponentType_get_MediaType(This,MediaType)	\
    (This)->lpVtbl -> get_MediaType(This,MediaType)

#define IComponentType_put_MediaType(This,MediaType)	\
    (This)->lpVtbl -> put_MediaType(This,MediaType)

#define IComponentType_Clone(This,NewCT)	\
    (This)->lpVtbl -> Clone(This,NewCT)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get_Category_Proxy( 
    IComponentType * This,
    /* [retval][out] */ ComponentCategory *Category);


void __RPC_STUB IComponentType_get_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put_Category_Proxy( 
    IComponentType * This,
    /* [in] */ ComponentCategory Category);


void __RPC_STUB IComponentType_put_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get_MediaMajorType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ BSTR *MediaMajorType);


void __RPC_STUB IComponentType_get_MediaMajorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put_MediaMajorType_Proxy( 
    IComponentType * This,
    /* [in] */ BSTR MediaMajorType);


void __RPC_STUB IComponentType_put_MediaMajorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get__MediaMajorType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ GUID *MediaMajorTypeGuid);


void __RPC_STUB IComponentType_get__MediaMajorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put__MediaMajorType_Proxy( 
    IComponentType * This,
    /* [in] */ REFCLSID MediaMajorTypeGuid);


void __RPC_STUB IComponentType_put__MediaMajorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get_MediaSubType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ BSTR *MediaSubType);


void __RPC_STUB IComponentType_get_MediaSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put_MediaSubType_Proxy( 
    IComponentType * This,
    /* [in] */ BSTR MediaSubType);


void __RPC_STUB IComponentType_put_MediaSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get__MediaSubType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ GUID *MediaSubTypeGuid);


void __RPC_STUB IComponentType_get__MediaSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put__MediaSubType_Proxy( 
    IComponentType * This,
    /* [in] */ REFCLSID MediaSubTypeGuid);


void __RPC_STUB IComponentType_put__MediaSubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get_MediaFormatType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ BSTR *MediaFormatType);


void __RPC_STUB IComponentType_get_MediaFormatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put_MediaFormatType_Proxy( 
    IComponentType * This,
    /* [in] */ BSTR MediaFormatType);


void __RPC_STUB IComponentType_put_MediaFormatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get__MediaFormatType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ GUID *MediaFormatTypeGuid);


void __RPC_STUB IComponentType_get__MediaFormatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put__MediaFormatType_Proxy( 
    IComponentType * This,
    /* [in] */ REFCLSID MediaFormatTypeGuid);


void __RPC_STUB IComponentType_put__MediaFormatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentType_get_MediaType_Proxy( 
    IComponentType * This,
    /* [retval][out] */ AM_MEDIA_TYPE *MediaType);


void __RPC_STUB IComponentType_get_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IComponentType_put_MediaType_Proxy( 
    IComponentType * This,
    /* [in] */ AM_MEDIA_TYPE *MediaType);


void __RPC_STUB IComponentType_put_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponentType_Clone_Proxy( 
    IComponentType * This,
    /* [retval][out] */ IComponentType **NewCT);


void __RPC_STUB IComponentType_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComponentType_INTERFACE_DEFINED__ */


#ifndef __ILanguageComponentType_INTERFACE_DEFINED__
#define __ILanguageComponentType_INTERFACE_DEFINED__

/* interface ILanguageComponentType */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_ILanguageComponentType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B874C8BA-0FA2-11d3-9D8E-00C04F72D980")
    ILanguageComponentType : public IComponentType
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LangID( 
            /* [retval][out] */ long *LangID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LangID( 
            /* [in] */ long LangID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILanguageComponentTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILanguageComponentType * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILanguageComponentType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILanguageComponentType * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILanguageComponentType * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILanguageComponentType * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILanguageComponentType * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILanguageComponentType * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Category )( 
            ILanguageComponentType * This,
            /* [retval][out] */ ComponentCategory *Category);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Category )( 
            ILanguageComponentType * This,
            /* [in] */ ComponentCategory Category);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaMajorType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ BSTR *MediaMajorType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaMajorType )( 
            ILanguageComponentType * This,
            /* [in] */ BSTR MediaMajorType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaMajorType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ GUID *MediaMajorTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaMajorType )( 
            ILanguageComponentType * This,
            /* [in] */ REFCLSID MediaMajorTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaSubType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ BSTR *MediaSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaSubType )( 
            ILanguageComponentType * This,
            /* [in] */ BSTR MediaSubType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaSubType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ GUID *MediaSubTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaSubType )( 
            ILanguageComponentType * This,
            /* [in] */ REFCLSID MediaSubTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFormatType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ BSTR *MediaFormatType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaFormatType )( 
            ILanguageComponentType * This,
            /* [in] */ BSTR MediaFormatType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaFormatType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ GUID *MediaFormatTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaFormatType )( 
            ILanguageComponentType * This,
            /* [in] */ REFCLSID MediaFormatTypeGuid);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            ILanguageComponentType * This,
            /* [retval][out] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaType )( 
            ILanguageComponentType * This,
            /* [in] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILanguageComponentType * This,
            /* [retval][out] */ IComponentType **NewCT);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LangID )( 
            ILanguageComponentType * This,
            /* [retval][out] */ long *LangID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LangID )( 
            ILanguageComponentType * This,
            /* [in] */ long LangID);
        
        END_INTERFACE
    } ILanguageComponentTypeVtbl;

    interface ILanguageComponentType
    {
        CONST_VTBL struct ILanguageComponentTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILanguageComponentType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILanguageComponentType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILanguageComponentType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILanguageComponentType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILanguageComponentType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILanguageComponentType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILanguageComponentType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILanguageComponentType_get_Category(This,Category)	\
    (This)->lpVtbl -> get_Category(This,Category)

#define ILanguageComponentType_put_Category(This,Category)	\
    (This)->lpVtbl -> put_Category(This,Category)

#define ILanguageComponentType_get_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> get_MediaMajorType(This,MediaMajorType)

#define ILanguageComponentType_put_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> put_MediaMajorType(This,MediaMajorType)

#define ILanguageComponentType_get__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> get__MediaMajorType(This,MediaMajorTypeGuid)

#define ILanguageComponentType_put__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> put__MediaMajorType(This,MediaMajorTypeGuid)

#define ILanguageComponentType_get_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> get_MediaSubType(This,MediaSubType)

#define ILanguageComponentType_put_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> put_MediaSubType(This,MediaSubType)

#define ILanguageComponentType_get__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> get__MediaSubType(This,MediaSubTypeGuid)

#define ILanguageComponentType_put__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> put__MediaSubType(This,MediaSubTypeGuid)

#define ILanguageComponentType_get_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> get_MediaFormatType(This,MediaFormatType)

#define ILanguageComponentType_put_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> put_MediaFormatType(This,MediaFormatType)

#define ILanguageComponentType_get__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> get__MediaFormatType(This,MediaFormatTypeGuid)

#define ILanguageComponentType_put__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> put__MediaFormatType(This,MediaFormatTypeGuid)

#define ILanguageComponentType_get_MediaType(This,MediaType)	\
    (This)->lpVtbl -> get_MediaType(This,MediaType)

#define ILanguageComponentType_put_MediaType(This,MediaType)	\
    (This)->lpVtbl -> put_MediaType(This,MediaType)

#define ILanguageComponentType_Clone(This,NewCT)	\
    (This)->lpVtbl -> Clone(This,NewCT)


#define ILanguageComponentType_get_LangID(This,LangID)	\
    (This)->lpVtbl -> get_LangID(This,LangID)

#define ILanguageComponentType_put_LangID(This,LangID)	\
    (This)->lpVtbl -> put_LangID(This,LangID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILanguageComponentType_get_LangID_Proxy( 
    ILanguageComponentType * This,
    /* [retval][out] */ long *LangID);


void __RPC_STUB ILanguageComponentType_get_LangID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILanguageComponentType_put_LangID_Proxy( 
    ILanguageComponentType * This,
    /* [in] */ long LangID);


void __RPC_STUB ILanguageComponentType_put_LangID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILanguageComponentType_INTERFACE_DEFINED__ */


#ifndef __IMPEG2ComponentType_INTERFACE_DEFINED__
#define __IMPEG2ComponentType_INTERFACE_DEFINED__

/* interface IMPEG2ComponentType */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IMPEG2ComponentType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2C073D84-B51C-48c9-AA9F-68971E1F6E38")
    IMPEG2ComponentType : public ILanguageComponentType
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamType( 
            /* [retval][out] */ MPEG2StreamType *MP2StreamType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StreamType( 
            /* [in] */ MPEG2StreamType MP2StreamType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2ComponentTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2ComponentType * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2ComponentType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2ComponentType * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMPEG2ComponentType * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMPEG2ComponentType * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMPEG2ComponentType * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMPEG2ComponentType * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Category )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ ComponentCategory *Category);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Category )( 
            IMPEG2ComponentType * This,
            /* [in] */ ComponentCategory Category);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaMajorType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ BSTR *MediaMajorType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaMajorType )( 
            IMPEG2ComponentType * This,
            /* [in] */ BSTR MediaMajorType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaMajorType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ GUID *MediaMajorTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaMajorType )( 
            IMPEG2ComponentType * This,
            /* [in] */ REFCLSID MediaMajorTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaSubType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ BSTR *MediaSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaSubType )( 
            IMPEG2ComponentType * This,
            /* [in] */ BSTR MediaSubType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaSubType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ GUID *MediaSubTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaSubType )( 
            IMPEG2ComponentType * This,
            /* [in] */ REFCLSID MediaSubTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFormatType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ BSTR *MediaFormatType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaFormatType )( 
            IMPEG2ComponentType * This,
            /* [in] */ BSTR MediaFormatType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaFormatType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ GUID *MediaFormatTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaFormatType )( 
            IMPEG2ComponentType * This,
            /* [in] */ REFCLSID MediaFormatTypeGuid);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaType )( 
            IMPEG2ComponentType * This,
            /* [in] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ IComponentType **NewCT);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LangID )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ long *LangID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LangID )( 
            IMPEG2ComponentType * This,
            /* [in] */ long LangID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamType )( 
            IMPEG2ComponentType * This,
            /* [retval][out] */ MPEG2StreamType *MP2StreamType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StreamType )( 
            IMPEG2ComponentType * This,
            /* [in] */ MPEG2StreamType MP2StreamType);
        
        END_INTERFACE
    } IMPEG2ComponentTypeVtbl;

    interface IMPEG2ComponentType
    {
        CONST_VTBL struct IMPEG2ComponentTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2ComponentType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2ComponentType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2ComponentType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2ComponentType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMPEG2ComponentType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMPEG2ComponentType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMPEG2ComponentType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMPEG2ComponentType_get_Category(This,Category)	\
    (This)->lpVtbl -> get_Category(This,Category)

#define IMPEG2ComponentType_put_Category(This,Category)	\
    (This)->lpVtbl -> put_Category(This,Category)

#define IMPEG2ComponentType_get_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> get_MediaMajorType(This,MediaMajorType)

#define IMPEG2ComponentType_put_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> put_MediaMajorType(This,MediaMajorType)

#define IMPEG2ComponentType_get__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> get__MediaMajorType(This,MediaMajorTypeGuid)

#define IMPEG2ComponentType_put__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> put__MediaMajorType(This,MediaMajorTypeGuid)

#define IMPEG2ComponentType_get_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> get_MediaSubType(This,MediaSubType)

#define IMPEG2ComponentType_put_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> put_MediaSubType(This,MediaSubType)

#define IMPEG2ComponentType_get__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> get__MediaSubType(This,MediaSubTypeGuid)

#define IMPEG2ComponentType_put__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> put__MediaSubType(This,MediaSubTypeGuid)

#define IMPEG2ComponentType_get_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> get_MediaFormatType(This,MediaFormatType)

#define IMPEG2ComponentType_put_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> put_MediaFormatType(This,MediaFormatType)

#define IMPEG2ComponentType_get__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> get__MediaFormatType(This,MediaFormatTypeGuid)

#define IMPEG2ComponentType_put__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> put__MediaFormatType(This,MediaFormatTypeGuid)

#define IMPEG2ComponentType_get_MediaType(This,MediaType)	\
    (This)->lpVtbl -> get_MediaType(This,MediaType)

#define IMPEG2ComponentType_put_MediaType(This,MediaType)	\
    (This)->lpVtbl -> put_MediaType(This,MediaType)

#define IMPEG2ComponentType_Clone(This,NewCT)	\
    (This)->lpVtbl -> Clone(This,NewCT)


#define IMPEG2ComponentType_get_LangID(This,LangID)	\
    (This)->lpVtbl -> get_LangID(This,LangID)

#define IMPEG2ComponentType_put_LangID(This,LangID)	\
    (This)->lpVtbl -> put_LangID(This,LangID)


#define IMPEG2ComponentType_get_StreamType(This,MP2StreamType)	\
    (This)->lpVtbl -> get_StreamType(This,MP2StreamType)

#define IMPEG2ComponentType_put_StreamType(This,MP2StreamType)	\
    (This)->lpVtbl -> put_StreamType(This,MP2StreamType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2ComponentType_get_StreamType_Proxy( 
    IMPEG2ComponentType * This,
    /* [retval][out] */ MPEG2StreamType *MP2StreamType);


void __RPC_STUB IMPEG2ComponentType_get_StreamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2ComponentType_put_StreamType_Proxy( 
    IMPEG2ComponentType * This,
    /* [in] */ MPEG2StreamType MP2StreamType);


void __RPC_STUB IMPEG2ComponentType_put_StreamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2ComponentType_INTERFACE_DEFINED__ */


#ifndef __IATSCComponentType_INTERFACE_DEFINED__
#define __IATSCComponentType_INTERFACE_DEFINED__

/* interface IATSCComponentType */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IATSCComponentType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC189E4D-7BD4-4125-B3B3-3A76A332CC96")
    IATSCComponentType : public IMPEG2ComponentType
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ long *Flags) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Flags( 
            /* [in] */ long flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATSCComponentTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATSCComponentType * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATSCComponentType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATSCComponentType * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATSCComponentType * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATSCComponentType * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATSCComponentType * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATSCComponentType * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Category )( 
            IATSCComponentType * This,
            /* [retval][out] */ ComponentCategory *Category);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Category )( 
            IATSCComponentType * This,
            /* [in] */ ComponentCategory Category);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaMajorType )( 
            IATSCComponentType * This,
            /* [retval][out] */ BSTR *MediaMajorType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaMajorType )( 
            IATSCComponentType * This,
            /* [in] */ BSTR MediaMajorType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaMajorType )( 
            IATSCComponentType * This,
            /* [retval][out] */ GUID *MediaMajorTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaMajorType )( 
            IATSCComponentType * This,
            /* [in] */ REFCLSID MediaMajorTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaSubType )( 
            IATSCComponentType * This,
            /* [retval][out] */ BSTR *MediaSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaSubType )( 
            IATSCComponentType * This,
            /* [in] */ BSTR MediaSubType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaSubType )( 
            IATSCComponentType * This,
            /* [retval][out] */ GUID *MediaSubTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaSubType )( 
            IATSCComponentType * This,
            /* [in] */ REFCLSID MediaSubTypeGuid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFormatType )( 
            IATSCComponentType * This,
            /* [retval][out] */ BSTR *MediaFormatType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaFormatType )( 
            IATSCComponentType * This,
            /* [in] */ BSTR MediaFormatType);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__MediaFormatType )( 
            IATSCComponentType * This,
            /* [retval][out] */ GUID *MediaFormatTypeGuid);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put__MediaFormatType )( 
            IATSCComponentType * This,
            /* [in] */ REFCLSID MediaFormatTypeGuid);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            IATSCComponentType * This,
            /* [retval][out] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaType )( 
            IATSCComponentType * This,
            /* [in] */ AM_MEDIA_TYPE *MediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IATSCComponentType * This,
            /* [retval][out] */ IComponentType **NewCT);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LangID )( 
            IATSCComponentType * This,
            /* [retval][out] */ long *LangID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LangID )( 
            IATSCComponentType * This,
            /* [in] */ long LangID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamType )( 
            IATSCComponentType * This,
            /* [retval][out] */ MPEG2StreamType *MP2StreamType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StreamType )( 
            IATSCComponentType * This,
            /* [in] */ MPEG2StreamType MP2StreamType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Flags )( 
            IATSCComponentType * This,
            /* [retval][out] */ long *Flags);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Flags )( 
            IATSCComponentType * This,
            /* [in] */ long flags);
        
        END_INTERFACE
    } IATSCComponentTypeVtbl;

    interface IATSCComponentType
    {
        CONST_VTBL struct IATSCComponentTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATSCComponentType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATSCComponentType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATSCComponentType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATSCComponentType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATSCComponentType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATSCComponentType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATSCComponentType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATSCComponentType_get_Category(This,Category)	\
    (This)->lpVtbl -> get_Category(This,Category)

#define IATSCComponentType_put_Category(This,Category)	\
    (This)->lpVtbl -> put_Category(This,Category)

#define IATSCComponentType_get_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> get_MediaMajorType(This,MediaMajorType)

#define IATSCComponentType_put_MediaMajorType(This,MediaMajorType)	\
    (This)->lpVtbl -> put_MediaMajorType(This,MediaMajorType)

#define IATSCComponentType_get__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> get__MediaMajorType(This,MediaMajorTypeGuid)

#define IATSCComponentType_put__MediaMajorType(This,MediaMajorTypeGuid)	\
    (This)->lpVtbl -> put__MediaMajorType(This,MediaMajorTypeGuid)

#define IATSCComponentType_get_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> get_MediaSubType(This,MediaSubType)

#define IATSCComponentType_put_MediaSubType(This,MediaSubType)	\
    (This)->lpVtbl -> put_MediaSubType(This,MediaSubType)

#define IATSCComponentType_get__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> get__MediaSubType(This,MediaSubTypeGuid)

#define IATSCComponentType_put__MediaSubType(This,MediaSubTypeGuid)	\
    (This)->lpVtbl -> put__MediaSubType(This,MediaSubTypeGuid)

#define IATSCComponentType_get_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> get_MediaFormatType(This,MediaFormatType)

#define IATSCComponentType_put_MediaFormatType(This,MediaFormatType)	\
    (This)->lpVtbl -> put_MediaFormatType(This,MediaFormatType)

#define IATSCComponentType_get__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> get__MediaFormatType(This,MediaFormatTypeGuid)

#define IATSCComponentType_put__MediaFormatType(This,MediaFormatTypeGuid)	\
    (This)->lpVtbl -> put__MediaFormatType(This,MediaFormatTypeGuid)

#define IATSCComponentType_get_MediaType(This,MediaType)	\
    (This)->lpVtbl -> get_MediaType(This,MediaType)

#define IATSCComponentType_put_MediaType(This,MediaType)	\
    (This)->lpVtbl -> put_MediaType(This,MediaType)

#define IATSCComponentType_Clone(This,NewCT)	\
    (This)->lpVtbl -> Clone(This,NewCT)


#define IATSCComponentType_get_LangID(This,LangID)	\
    (This)->lpVtbl -> get_LangID(This,LangID)

#define IATSCComponentType_put_LangID(This,LangID)	\
    (This)->lpVtbl -> put_LangID(This,LangID)


#define IATSCComponentType_get_StreamType(This,MP2StreamType)	\
    (This)->lpVtbl -> get_StreamType(This,MP2StreamType)

#define IATSCComponentType_put_StreamType(This,MP2StreamType)	\
    (This)->lpVtbl -> put_StreamType(This,MP2StreamType)


#define IATSCComponentType_get_Flags(This,Flags)	\
    (This)->lpVtbl -> get_Flags(This,Flags)

#define IATSCComponentType_put_Flags(This,flags)	\
    (This)->lpVtbl -> put_Flags(This,flags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCComponentType_get_Flags_Proxy( 
    IATSCComponentType * This,
    /* [retval][out] */ long *Flags);


void __RPC_STUB IATSCComponentType_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCComponentType_put_Flags_Proxy( 
    IATSCComponentType * This,
    /* [in] */ long flags);


void __RPC_STUB IATSCComponentType_put_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATSCComponentType_INTERFACE_DEFINED__ */


#ifndef __IEnumComponentTypes_INTERFACE_DEFINED__
#define __IEnumComponentTypes_INTERFACE_DEFINED__

/* interface IEnumComponentTypes */
/* [unique][uuid][object][restricted][hidden] */ 


EXTERN_C const IID IID_IEnumComponentTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8A674B4A-1F63-11d3-B64C-00C04F79498E")
    IEnumComponentTypes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IComponentType **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumComponentTypes **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumComponentTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumComponentTypes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumComponentTypes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumComponentTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumComponentTypes * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IComponentType **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumComponentTypes * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumComponentTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumComponentTypes * This,
            /* [out] */ IEnumComponentTypes **ppEnum);
        
        END_INTERFACE
    } IEnumComponentTypesVtbl;

    interface IEnumComponentTypes
    {
        CONST_VTBL struct IEnumComponentTypesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumComponentTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumComponentTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumComponentTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumComponentTypes_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumComponentTypes_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumComponentTypes_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumComponentTypes_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumComponentTypes_Next_Proxy( 
    IEnumComponentTypes * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IComponentType **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumComponentTypes_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponentTypes_Skip_Proxy( 
    IEnumComponentTypes * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumComponentTypes_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponentTypes_Reset_Proxy( 
    IEnumComponentTypes * This);


void __RPC_STUB IEnumComponentTypes_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponentTypes_Clone_Proxy( 
    IEnumComponentTypes * This,
    /* [out] */ IEnumComponentTypes **ppEnum);


void __RPC_STUB IEnumComponentTypes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumComponentTypes_INTERFACE_DEFINED__ */


#ifndef __IComponentTypes_INTERFACE_DEFINED__
#define __IComponentTypes_INTERFACE_DEFINED__

/* interface IComponentTypes */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IComponentTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0DC13D4A-0313-11d3-9D8E-00C04F72D980")
    IComponentTypes : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **ppNewEnum) = 0;
        
        virtual /* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE EnumComponentTypes( 
            /* [retval][out] */ IEnumComponentTypes **ppNewEnum) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IComponentType **ComponentType) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT Index,
            /* [in] */ IComponentType *ComponentType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IComponentType *ComponentType,
            /* [retval][out] */ VARIANT *NewIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IComponentTypes **NewList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComponentTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentTypes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentTypes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponentTypes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponentTypes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponentTypes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponentTypes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IComponentTypes * This,
            /* [retval][out] */ long *Count);
        
        /* [restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IComponentTypes * This,
            /* [retval][out] */ IEnumVARIANT **ppNewEnum);
        
        /* [helpstring][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *EnumComponentTypes )( 
            IComponentTypes * This,
            /* [retval][out] */ IEnumComponentTypes **ppNewEnum);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IComponentTypes * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IComponentType **ComponentType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IComponentTypes * This,
            /* [in] */ VARIANT Index,
            /* [in] */ IComponentType *ComponentType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IComponentTypes * This,
            /* [in] */ IComponentType *ComponentType,
            /* [retval][out] */ VARIANT *NewIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IComponentTypes * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IComponentTypes * This,
            /* [retval][out] */ IComponentTypes **NewList);
        
        END_INTERFACE
    } IComponentTypesVtbl;

    interface IComponentTypes
    {
        CONST_VTBL struct IComponentTypesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComponentTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComponentTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComponentTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComponentTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComponentTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComponentTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComponentTypes_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IComponentTypes_get__NewEnum(This,ppNewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppNewEnum)

#define IComponentTypes_EnumComponentTypes(This,ppNewEnum)	\
    (This)->lpVtbl -> EnumComponentTypes(This,ppNewEnum)

#define IComponentTypes_get_Item(This,Index,ComponentType)	\
    (This)->lpVtbl -> get_Item(This,Index,ComponentType)

#define IComponentTypes_put_Item(This,Index,ComponentType)	\
    (This)->lpVtbl -> put_Item(This,Index,ComponentType)

#define IComponentTypes_Add(This,ComponentType,NewIndex)	\
    (This)->lpVtbl -> Add(This,ComponentType,NewIndex)

#define IComponentTypes_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define IComponentTypes_Clone(This,NewList)	\
    (This)->lpVtbl -> Clone(This,NewList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IComponentTypes_get_Count_Proxy( 
    IComponentTypes * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IComponentTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IComponentTypes_get__NewEnum_Proxy( 
    IComponentTypes * This,
    /* [retval][out] */ IEnumVARIANT **ppNewEnum);


void __RPC_STUB IComponentTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE IComponentTypes_EnumComponentTypes_Proxy( 
    IComponentTypes * This,
    /* [retval][out] */ IEnumComponentTypes **ppNewEnum);


void __RPC_STUB IComponentTypes_EnumComponentTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IComponentTypes_get_Item_Proxy( 
    IComponentTypes * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IComponentType **ComponentType);


void __RPC_STUB IComponentTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IComponentTypes_put_Item_Proxy( 
    IComponentTypes * This,
    /* [in] */ VARIANT Index,
    /* [in] */ IComponentType *ComponentType);


void __RPC_STUB IComponentTypes_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponentTypes_Add_Proxy( 
    IComponentTypes * This,
    /* [in] */ IComponentType *ComponentType,
    /* [retval][out] */ VARIANT *NewIndex);


void __RPC_STUB IComponentTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponentTypes_Remove_Proxy( 
    IComponentTypes * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB IComponentTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IComponentTypes_Clone_Proxy( 
    IComponentTypes * This,
    /* [retval][out] */ IComponentTypes **NewList);


void __RPC_STUB IComponentTypes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComponentTypes_INTERFACE_DEFINED__ */


#ifndef __IComponent_INTERFACE_DEFINED__
#define __IComponent_INTERFACE_DEFINED__

/* interface IComponent */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IComponent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1A5576FC-0E19-11d3-9D8E-00C04F72D980")
    IComponent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ IComponentType **CT) = 0;
        
        virtual /* [helpstring][id][propput][restricted][hidden] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ IComponentType *CT) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DescLangID( 
            /* [retval][out] */ long *LangID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DescLangID( 
            /* [in] */ long LangID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ ComponentStatus *Status) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Status( 
            /* [in] */ ComponentStatus Status) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *Description) = 0;
        
        virtual /* [helpstring][id][propput][restricted][hidden] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR Description) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IComponent **NewComponent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComponentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IComponent * This,
            /* [retval][out] */ IComponentType **CT);
        
        /* [helpstring][id][propput][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IComponent * This,
            /* [in] */ IComponentType *CT);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DescLangID )( 
            IComponent * This,
            /* [retval][out] */ long *LangID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DescLangID )( 
            IComponent * This,
            /* [in] */ long LangID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IComponent * This,
            /* [retval][out] */ ComponentStatus *Status);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Status )( 
            IComponent * This,
            /* [in] */ ComponentStatus Status);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IComponent * This,
            /* [retval][out] */ BSTR *Description);
        
        /* [helpstring][id][propput][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IComponent * This,
            /* [in] */ BSTR Description);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IComponent * This,
            /* [retval][out] */ IComponent **NewComponent);
        
        END_INTERFACE
    } IComponentVtbl;

    interface IComponent
    {
        CONST_VTBL struct IComponentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComponent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComponent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComponent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComponent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComponent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComponent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComponent_get_Type(This,CT)	\
    (This)->lpVtbl -> get_Type(This,CT)

#define IComponent_put_Type(This,CT)	\
    (This)->lpVtbl -> put_Type(This,CT)

#define IComponent_get_DescLangID(This,LangID)	\
    (This)->lpVtbl -> get_DescLangID(This,LangID)

#define IComponent_put_DescLangID(This,LangID)	\
    (This)->lpVtbl -> put_DescLangID(This,LangID)

#define IComponent_get_Status(This,Status)	\
    (This)->lpVtbl -> get_Status(This,Status)

#define IComponent_put_Status(This,Status)	\
    (This)->lpVtbl -> put_Status(This,Status)

#define IComponent_get_Description(This,Description)	\
    (This)->lpVtbl -> get_Description(This,Description)

#define IComponent_put_Description(This,Description)	\
    (This)->lpVtbl -> put_Description(This,Description)

#define IComponent_Clone(This,NewComponent)	\
    (This)->lpVtbl -> Clone(This,NewComponent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponent_get_Type_Proxy( 
    IComponent * This,
    /* [retval][out] */ IComponentType **CT);


void __RPC_STUB IComponent_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput][restricted][hidden] */ HRESULT STDMETHODCALLTYPE IComponent_put_Type_Proxy( 
    IComponent * This,
    /* [in] */ IComponentType *CT);


void __RPC_STUB IComponent_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponent_get_DescLangID_Proxy( 
    IComponent * This,
    /* [retval][out] */ long *LangID);


void __RPC_STUB IComponent_get_DescLangID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponent_put_DescLangID_Proxy( 
    IComponent * This,
    /* [in] */ long LangID);


void __RPC_STUB IComponent_put_DescLangID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponent_get_Status_Proxy( 
    IComponent * This,
    /* [retval][out] */ ComponentStatus *Status);


void __RPC_STUB IComponent_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IComponent_put_Status_Proxy( 
    IComponent * This,
    /* [in] */ ComponentStatus Status);


void __RPC_STUB IComponent_put_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComponent_get_Description_Proxy( 
    IComponent * This,
    /* [retval][out] */ BSTR *Description);


void __RPC_STUB IComponent_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput][restricted][hidden] */ HRESULT STDMETHODCALLTYPE IComponent_put_Description_Proxy( 
    IComponent * This,
    /* [in] */ BSTR Description);


void __RPC_STUB IComponent_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponent_Clone_Proxy( 
    IComponent * This,
    /* [retval][out] */ IComponent **NewComponent);


void __RPC_STUB IComponent_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComponent_INTERFACE_DEFINED__ */


#ifndef __IMPEG2Component_INTERFACE_DEFINED__
#define __IMPEG2Component_INTERFACE_DEFINED__

/* interface IMPEG2Component */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IMPEG2Component;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1493E353-1EB6-473c-802D-8E6B8EC9D2A9")
    IMPEG2Component : public IComponent
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PID( 
            /* [retval][out] */ long *PID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PID( 
            /* [in] */ long PID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PCRPID( 
            /* [retval][out] */ long *PCRPID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PCRPID( 
            /* [in] */ long PCRPID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgramNumber( 
            /* [retval][out] */ long *ProgramNumber) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProgramNumber( 
            /* [in] */ long ProgramNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2ComponentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2Component * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2Component * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2Component * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMPEG2Component * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMPEG2Component * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMPEG2Component * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMPEG2Component * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IMPEG2Component * This,
            /* [retval][out] */ IComponentType **CT);
        
        /* [helpstring][id][propput][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IMPEG2Component * This,
            /* [in] */ IComponentType *CT);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DescLangID )( 
            IMPEG2Component * This,
            /* [retval][out] */ long *LangID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DescLangID )( 
            IMPEG2Component * This,
            /* [in] */ long LangID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IMPEG2Component * This,
            /* [retval][out] */ ComponentStatus *Status);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Status )( 
            IMPEG2Component * This,
            /* [in] */ ComponentStatus Status);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IMPEG2Component * This,
            /* [retval][out] */ BSTR *Description);
        
        /* [helpstring][id][propput][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IMPEG2Component * This,
            /* [in] */ BSTR Description);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IMPEG2Component * This,
            /* [retval][out] */ IComponent **NewComponent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PID )( 
            IMPEG2Component * This,
            /* [retval][out] */ long *PID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PID )( 
            IMPEG2Component * This,
            /* [in] */ long PID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PCRPID )( 
            IMPEG2Component * This,
            /* [retval][out] */ long *PCRPID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PCRPID )( 
            IMPEG2Component * This,
            /* [in] */ long PCRPID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProgramNumber )( 
            IMPEG2Component * This,
            /* [retval][out] */ long *ProgramNumber);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProgramNumber )( 
            IMPEG2Component * This,
            /* [in] */ long ProgramNumber);
        
        END_INTERFACE
    } IMPEG2ComponentVtbl;

    interface IMPEG2Component
    {
        CONST_VTBL struct IMPEG2ComponentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2Component_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2Component_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2Component_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2Component_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMPEG2Component_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMPEG2Component_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMPEG2Component_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMPEG2Component_get_Type(This,CT)	\
    (This)->lpVtbl -> get_Type(This,CT)

#define IMPEG2Component_put_Type(This,CT)	\
    (This)->lpVtbl -> put_Type(This,CT)

#define IMPEG2Component_get_DescLangID(This,LangID)	\
    (This)->lpVtbl -> get_DescLangID(This,LangID)

#define IMPEG2Component_put_DescLangID(This,LangID)	\
    (This)->lpVtbl -> put_DescLangID(This,LangID)

#define IMPEG2Component_get_Status(This,Status)	\
    (This)->lpVtbl -> get_Status(This,Status)

#define IMPEG2Component_put_Status(This,Status)	\
    (This)->lpVtbl -> put_Status(This,Status)

#define IMPEG2Component_get_Description(This,Description)	\
    (This)->lpVtbl -> get_Description(This,Description)

#define IMPEG2Component_put_Description(This,Description)	\
    (This)->lpVtbl -> put_Description(This,Description)

#define IMPEG2Component_Clone(This,NewComponent)	\
    (This)->lpVtbl -> Clone(This,NewComponent)


#define IMPEG2Component_get_PID(This,PID)	\
    (This)->lpVtbl -> get_PID(This,PID)

#define IMPEG2Component_put_PID(This,PID)	\
    (This)->lpVtbl -> put_PID(This,PID)

#define IMPEG2Component_get_PCRPID(This,PCRPID)	\
    (This)->lpVtbl -> get_PCRPID(This,PCRPID)

#define IMPEG2Component_put_PCRPID(This,PCRPID)	\
    (This)->lpVtbl -> put_PCRPID(This,PCRPID)

#define IMPEG2Component_get_ProgramNumber(This,ProgramNumber)	\
    (This)->lpVtbl -> get_ProgramNumber(This,ProgramNumber)

#define IMPEG2Component_put_ProgramNumber(This,ProgramNumber)	\
    (This)->lpVtbl -> put_ProgramNumber(This,ProgramNumber)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_get_PID_Proxy( 
    IMPEG2Component * This,
    /* [retval][out] */ long *PID);


void __RPC_STUB IMPEG2Component_get_PID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_put_PID_Proxy( 
    IMPEG2Component * This,
    /* [in] */ long PID);


void __RPC_STUB IMPEG2Component_put_PID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_get_PCRPID_Proxy( 
    IMPEG2Component * This,
    /* [retval][out] */ long *PCRPID);


void __RPC_STUB IMPEG2Component_get_PCRPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_put_PCRPID_Proxy( 
    IMPEG2Component * This,
    /* [in] */ long PCRPID);


void __RPC_STUB IMPEG2Component_put_PCRPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_get_ProgramNumber_Proxy( 
    IMPEG2Component * This,
    /* [retval][out] */ long *ProgramNumber);


void __RPC_STUB IMPEG2Component_get_ProgramNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEG2Component_put_ProgramNumber_Proxy( 
    IMPEG2Component * This,
    /* [in] */ long ProgramNumber);


void __RPC_STUB IMPEG2Component_put_ProgramNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2Component_INTERFACE_DEFINED__ */


#ifndef __IEnumComponents_INTERFACE_DEFINED__
#define __IEnumComponents_INTERFACE_DEFINED__

/* interface IEnumComponents */
/* [unique][uuid][object][restricted][hidden] */ 


EXTERN_C const IID IID_IEnumComponents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A6E2939-2595-11d3-B64C-00C04F79498E")
    IEnumComponents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IComponent **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumComponents **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumComponentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumComponents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumComponents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumComponents * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumComponents * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IComponent **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumComponents * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumComponents * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumComponents * This,
            /* [out] */ IEnumComponents **ppEnum);
        
        END_INTERFACE
    } IEnumComponentsVtbl;

    interface IEnumComponents
    {
        CONST_VTBL struct IEnumComponentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumComponents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumComponents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumComponents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumComponents_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumComponents_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumComponents_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumComponents_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumComponents_Next_Proxy( 
    IEnumComponents * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IComponent **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumComponents_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponents_Skip_Proxy( 
    IEnumComponents * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumComponents_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponents_Reset_Proxy( 
    IEnumComponents * This);


void __RPC_STUB IEnumComponents_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumComponents_Clone_Proxy( 
    IEnumComponents * This,
    /* [out] */ IEnumComponents **ppEnum);


void __RPC_STUB IEnumComponents_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumComponents_INTERFACE_DEFINED__ */


#ifndef __IComponents_INTERFACE_DEFINED__
#define __IComponents_INTERFACE_DEFINED__

/* interface IComponents */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_IComponents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FCD01846-0E19-11d3-9D8E-00C04F72D980")
    IComponents : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **ppNewEnum) = 0;
        
        virtual /* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE EnumComponents( 
            /* [retval][out] */ IEnumComponents **ppNewEnum) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IComponent **ppComponent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IComponent *Component,
            /* [retval][out] */ VARIANT *NewIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IComponents **NewList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComponentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IComponents * This,
            /* [retval][out] */ long *Count);
        
        /* [restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IComponents * This,
            /* [retval][out] */ IEnumVARIANT **ppNewEnum);
        
        /* [helpstring][restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE *EnumComponents )( 
            IComponents * This,
            /* [retval][out] */ IEnumComponents **ppNewEnum);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IComponents * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IComponent **ppComponent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IComponents * This,
            /* [in] */ IComponent *Component,
            /* [retval][out] */ VARIANT *NewIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IComponents * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IComponents * This,
            /* [retval][out] */ IComponents **NewList);
        
        END_INTERFACE
    } IComponentsVtbl;

    interface IComponents
    {
        CONST_VTBL struct IComponentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComponents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComponents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComponents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComponents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComponents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComponents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComponents_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IComponents_get__NewEnum(This,ppNewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppNewEnum)

#define IComponents_EnumComponents(This,ppNewEnum)	\
    (This)->lpVtbl -> EnumComponents(This,ppNewEnum)

#define IComponents_get_Item(This,Index,ppComponent)	\
    (This)->lpVtbl -> get_Item(This,Index,ppComponent)

#define IComponents_Add(This,Component,NewIndex)	\
    (This)->lpVtbl -> Add(This,Component,NewIndex)

#define IComponents_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define IComponents_Clone(This,NewList)	\
    (This)->lpVtbl -> Clone(This,NewList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IComponents_get_Count_Proxy( 
    IComponents * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IComponents_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IComponents_get__NewEnum_Proxy( 
    IComponents * This,
    /* [retval][out] */ IEnumVARIANT **ppNewEnum);


void __RPC_STUB IComponents_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden] */ HRESULT STDMETHODCALLTYPE IComponents_EnumComponents_Proxy( 
    IComponents * This,
    /* [retval][out] */ IEnumComponents **ppNewEnum);


void __RPC_STUB IComponents_EnumComponents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IComponents_get_Item_Proxy( 
    IComponents * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IComponent **ppComponent);


void __RPC_STUB IComponents_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponents_Add_Proxy( 
    IComponents * This,
    /* [in] */ IComponent *Component,
    /* [retval][out] */ VARIANT *NewIndex);


void __RPC_STUB IComponents_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComponents_Remove_Proxy( 
    IComponents * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB IComponents_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IComponents_Clone_Proxy( 
    IComponents * This,
    /* [retval][out] */ IComponents **NewList);


void __RPC_STUB IComponents_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComponents_INTERFACE_DEFINED__ */


#ifndef __ILocator_INTERFACE_DEFINED__
#define __ILocator_INTERFACE_DEFINED__

/* interface ILocator */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][object] */ 


EXTERN_C const IID IID_ILocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("286D7F89-760C-4F89-80C4-66841D2507AA")
    ILocator : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CarrierFrequency( 
            /* [retval][out] */ long *Frequency) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CarrierFrequency( 
            /* [in] */ long Frequency) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InnerFEC( 
            /* [retval][out] */ FECMethod *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InnerFEC( 
            /* [in] */ FECMethod FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InnerFECRate( 
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InnerFECRate( 
            /* [in] */ BinaryConvolutionCodeRate FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OuterFEC( 
            /* [retval][out] */ FECMethod *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OuterFEC( 
            /* [in] */ FECMethod FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OuterFECRate( 
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OuterFECRate( 
            /* [in] */ BinaryConvolutionCodeRate FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Modulation( 
            /* [retval][out] */ ModulationType *Modulation) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Modulation( 
            /* [in] */ ModulationType Modulation) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SymbolRate( 
            /* [retval][out] */ long *Rate) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SymbolRate( 
            /* [in] */ long Rate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ILocator **NewLocator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILocator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILocator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILocator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILocator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CarrierFrequency )( 
            ILocator * This,
            /* [retval][out] */ long *Frequency);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CarrierFrequency )( 
            ILocator * This,
            /* [in] */ long Frequency);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFEC )( 
            ILocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFEC )( 
            ILocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFECRate )( 
            ILocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFECRate )( 
            ILocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFEC )( 
            ILocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFEC )( 
            ILocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFECRate )( 
            ILocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFECRate )( 
            ILocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modulation )( 
            ILocator * This,
            /* [retval][out] */ ModulationType *Modulation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Modulation )( 
            ILocator * This,
            /* [in] */ ModulationType Modulation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolRate )( 
            ILocator * This,
            /* [retval][out] */ long *Rate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SymbolRate )( 
            ILocator * This,
            /* [in] */ long Rate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILocator * This,
            /* [retval][out] */ ILocator **NewLocator);
        
        END_INTERFACE
    } ILocatorVtbl;

    interface ILocator
    {
        CONST_VTBL struct ILocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILocator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILocator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILocator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILocator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILocator_get_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> get_CarrierFrequency(This,Frequency)

#define ILocator_put_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> put_CarrierFrequency(This,Frequency)

#define ILocator_get_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_InnerFEC(This,FEC)

#define ILocator_put_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_InnerFEC(This,FEC)

#define ILocator_get_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_InnerFECRate(This,FEC)

#define ILocator_put_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_InnerFECRate(This,FEC)

#define ILocator_get_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> get_OuterFEC(This,FEC)

#define ILocator_put_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> put_OuterFEC(This,FEC)

#define ILocator_get_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> get_OuterFECRate(This,FEC)

#define ILocator_put_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> put_OuterFECRate(This,FEC)

#define ILocator_get_Modulation(This,Modulation)	\
    (This)->lpVtbl -> get_Modulation(This,Modulation)

#define ILocator_put_Modulation(This,Modulation)	\
    (This)->lpVtbl -> put_Modulation(This,Modulation)

#define ILocator_get_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> get_SymbolRate(This,Rate)

#define ILocator_put_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> put_SymbolRate(This,Rate)

#define ILocator_Clone(This,NewLocator)	\
    (This)->lpVtbl -> Clone(This,NewLocator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_CarrierFrequency_Proxy( 
    ILocator * This,
    /* [retval][out] */ long *Frequency);


void __RPC_STUB ILocator_get_CarrierFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_CarrierFrequency_Proxy( 
    ILocator * This,
    /* [in] */ long Frequency);


void __RPC_STUB ILocator_put_CarrierFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_InnerFEC_Proxy( 
    ILocator * This,
    /* [retval][out] */ FECMethod *FEC);


void __RPC_STUB ILocator_get_InnerFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_InnerFEC_Proxy( 
    ILocator * This,
    /* [in] */ FECMethod FEC);


void __RPC_STUB ILocator_put_InnerFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_InnerFECRate_Proxy( 
    ILocator * This,
    /* [retval][out] */ BinaryConvolutionCodeRate *FEC);


void __RPC_STUB ILocator_get_InnerFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_InnerFECRate_Proxy( 
    ILocator * This,
    /* [in] */ BinaryConvolutionCodeRate FEC);


void __RPC_STUB ILocator_put_InnerFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_OuterFEC_Proxy( 
    ILocator * This,
    /* [retval][out] */ FECMethod *FEC);


void __RPC_STUB ILocator_get_OuterFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_OuterFEC_Proxy( 
    ILocator * This,
    /* [in] */ FECMethod FEC);


void __RPC_STUB ILocator_put_OuterFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_OuterFECRate_Proxy( 
    ILocator * This,
    /* [retval][out] */ BinaryConvolutionCodeRate *FEC);


void __RPC_STUB ILocator_get_OuterFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_OuterFECRate_Proxy( 
    ILocator * This,
    /* [in] */ BinaryConvolutionCodeRate FEC);


void __RPC_STUB ILocator_put_OuterFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_Modulation_Proxy( 
    ILocator * This,
    /* [retval][out] */ ModulationType *Modulation);


void __RPC_STUB ILocator_get_Modulation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_Modulation_Proxy( 
    ILocator * This,
    /* [in] */ ModulationType Modulation);


void __RPC_STUB ILocator_put_Modulation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILocator_get_SymbolRate_Proxy( 
    ILocator * This,
    /* [retval][out] */ long *Rate);


void __RPC_STUB ILocator_get_SymbolRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILocator_put_SymbolRate_Proxy( 
    ILocator * This,
    /* [in] */ long Rate);


void __RPC_STUB ILocator_put_SymbolRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILocator_Clone_Proxy( 
    ILocator * This,
    /* [retval][out] */ ILocator **NewLocator);


void __RPC_STUB ILocator_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILocator_INTERFACE_DEFINED__ */


#ifndef __IATSCLocator_INTERFACE_DEFINED__
#define __IATSCLocator_INTERFACE_DEFINED__

/* interface IATSCLocator */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IATSCLocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF8D986F-8C2B-4131-94D7-4D3D9FCC21EF")
    IATSCLocator : public ILocator
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PhysicalChannel( 
            /* [retval][out] */ long *PhysicalChannel) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PhysicalChannel( 
            /* [in] */ long PhysicalChannel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSID( 
            /* [retval][out] */ long *TSID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSID( 
            /* [in] */ long TSID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATSCLocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATSCLocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATSCLocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATSCLocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATSCLocator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATSCLocator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATSCLocator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATSCLocator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CarrierFrequency )( 
            IATSCLocator * This,
            /* [retval][out] */ long *Frequency);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CarrierFrequency )( 
            IATSCLocator * This,
            /* [in] */ long Frequency);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFEC )( 
            IATSCLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFEC )( 
            IATSCLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFECRate )( 
            IATSCLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFECRate )( 
            IATSCLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFEC )( 
            IATSCLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFEC )( 
            IATSCLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFECRate )( 
            IATSCLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFECRate )( 
            IATSCLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modulation )( 
            IATSCLocator * This,
            /* [retval][out] */ ModulationType *Modulation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Modulation )( 
            IATSCLocator * This,
            /* [in] */ ModulationType Modulation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolRate )( 
            IATSCLocator * This,
            /* [retval][out] */ long *Rate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SymbolRate )( 
            IATSCLocator * This,
            /* [in] */ long Rate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IATSCLocator * This,
            /* [retval][out] */ ILocator **NewLocator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PhysicalChannel )( 
            IATSCLocator * This,
            /* [retval][out] */ long *PhysicalChannel);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PhysicalChannel )( 
            IATSCLocator * This,
            /* [in] */ long PhysicalChannel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSID )( 
            IATSCLocator * This,
            /* [retval][out] */ long *TSID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSID )( 
            IATSCLocator * This,
            /* [in] */ long TSID);
        
        END_INTERFACE
    } IATSCLocatorVtbl;

    interface IATSCLocator
    {
        CONST_VTBL struct IATSCLocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATSCLocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATSCLocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATSCLocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATSCLocator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATSCLocator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATSCLocator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATSCLocator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATSCLocator_get_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> get_CarrierFrequency(This,Frequency)

#define IATSCLocator_put_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> put_CarrierFrequency(This,Frequency)

#define IATSCLocator_get_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_InnerFEC(This,FEC)

#define IATSCLocator_put_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_InnerFEC(This,FEC)

#define IATSCLocator_get_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_InnerFECRate(This,FEC)

#define IATSCLocator_put_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_InnerFECRate(This,FEC)

#define IATSCLocator_get_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> get_OuterFEC(This,FEC)

#define IATSCLocator_put_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> put_OuterFEC(This,FEC)

#define IATSCLocator_get_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> get_OuterFECRate(This,FEC)

#define IATSCLocator_put_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> put_OuterFECRate(This,FEC)

#define IATSCLocator_get_Modulation(This,Modulation)	\
    (This)->lpVtbl -> get_Modulation(This,Modulation)

#define IATSCLocator_put_Modulation(This,Modulation)	\
    (This)->lpVtbl -> put_Modulation(This,Modulation)

#define IATSCLocator_get_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> get_SymbolRate(This,Rate)

#define IATSCLocator_put_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> put_SymbolRate(This,Rate)

#define IATSCLocator_Clone(This,NewLocator)	\
    (This)->lpVtbl -> Clone(This,NewLocator)


#define IATSCLocator_get_PhysicalChannel(This,PhysicalChannel)	\
    (This)->lpVtbl -> get_PhysicalChannel(This,PhysicalChannel)

#define IATSCLocator_put_PhysicalChannel(This,PhysicalChannel)	\
    (This)->lpVtbl -> put_PhysicalChannel(This,PhysicalChannel)

#define IATSCLocator_get_TSID(This,TSID)	\
    (This)->lpVtbl -> get_TSID(This,TSID)

#define IATSCLocator_put_TSID(This,TSID)	\
    (This)->lpVtbl -> put_TSID(This,TSID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCLocator_get_PhysicalChannel_Proxy( 
    IATSCLocator * This,
    /* [retval][out] */ long *PhysicalChannel);


void __RPC_STUB IATSCLocator_get_PhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCLocator_put_PhysicalChannel_Proxy( 
    IATSCLocator * This,
    /* [in] */ long PhysicalChannel);


void __RPC_STUB IATSCLocator_put_PhysicalChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATSCLocator_get_TSID_Proxy( 
    IATSCLocator * This,
    /* [retval][out] */ long *TSID);


void __RPC_STUB IATSCLocator_get_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATSCLocator_put_TSID_Proxy( 
    IATSCLocator * This,
    /* [in] */ long TSID);


void __RPC_STUB IATSCLocator_put_TSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATSCLocator_INTERFACE_DEFINED__ */


#ifndef __IDVBTLocator_INTERFACE_DEFINED__
#define __IDVBTLocator_INTERFACE_DEFINED__

/* interface IDVBTLocator */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IDVBTLocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8664DA16-DDA2-42ac-926A-C18F9127C302")
    IDVBTLocator : public ILocator
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bandwidth( 
            /* [retval][out] */ long *BandWidthVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bandwidth( 
            /* [in] */ long BandwidthVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LPInnerFEC( 
            /* [retval][out] */ FECMethod *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LPInnerFEC( 
            /* [in] */ FECMethod FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LPInnerFECRate( 
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LPInnerFECRate( 
            /* [in] */ BinaryConvolutionCodeRate FEC) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HAlpha( 
            /* [retval][out] */ HierarchyAlpha *Alpha) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HAlpha( 
            /* [in] */ HierarchyAlpha Alpha) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Guard( 
            /* [retval][out] */ GuardInterval *GI) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Guard( 
            /* [in] */ GuardInterval GI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [retval][out] */ TransmissionMode *mode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ TransmissionMode mode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OtherFrequencyInUse( 
            /* [retval][out] */ VARIANT_BOOL *OtherFrequencyInUseVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OtherFrequencyInUse( 
            /* [in] */ VARIANT_BOOL OtherFrequencyInUseVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBTLocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBTLocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBTLocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBTLocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBTLocator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBTLocator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBTLocator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBTLocator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CarrierFrequency )( 
            IDVBTLocator * This,
            /* [retval][out] */ long *Frequency);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CarrierFrequency )( 
            IDVBTLocator * This,
            /* [in] */ long Frequency);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFEC )( 
            IDVBTLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFEC )( 
            IDVBTLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFECRate )( 
            IDVBTLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFECRate )( 
            IDVBTLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFEC )( 
            IDVBTLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFEC )( 
            IDVBTLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFECRate )( 
            IDVBTLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFECRate )( 
            IDVBTLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modulation )( 
            IDVBTLocator * This,
            /* [retval][out] */ ModulationType *Modulation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Modulation )( 
            IDVBTLocator * This,
            /* [in] */ ModulationType Modulation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolRate )( 
            IDVBTLocator * This,
            /* [retval][out] */ long *Rate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SymbolRate )( 
            IDVBTLocator * This,
            /* [in] */ long Rate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBTLocator * This,
            /* [retval][out] */ ILocator **NewLocator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bandwidth )( 
            IDVBTLocator * This,
            /* [retval][out] */ long *BandWidthVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bandwidth )( 
            IDVBTLocator * This,
            /* [in] */ long BandwidthVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LPInnerFEC )( 
            IDVBTLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LPInnerFEC )( 
            IDVBTLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LPInnerFECRate )( 
            IDVBTLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LPInnerFECRate )( 
            IDVBTLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HAlpha )( 
            IDVBTLocator * This,
            /* [retval][out] */ HierarchyAlpha *Alpha);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HAlpha )( 
            IDVBTLocator * This,
            /* [in] */ HierarchyAlpha Alpha);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Guard )( 
            IDVBTLocator * This,
            /* [retval][out] */ GuardInterval *GI);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Guard )( 
            IDVBTLocator * This,
            /* [in] */ GuardInterval GI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IDVBTLocator * This,
            /* [retval][out] */ TransmissionMode *mode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IDVBTLocator * This,
            /* [in] */ TransmissionMode mode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OtherFrequencyInUse )( 
            IDVBTLocator * This,
            /* [retval][out] */ VARIANT_BOOL *OtherFrequencyInUseVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OtherFrequencyInUse )( 
            IDVBTLocator * This,
            /* [in] */ VARIANT_BOOL OtherFrequencyInUseVal);
        
        END_INTERFACE
    } IDVBTLocatorVtbl;

    interface IDVBTLocator
    {
        CONST_VTBL struct IDVBTLocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBTLocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBTLocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBTLocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBTLocator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBTLocator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBTLocator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBTLocator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBTLocator_get_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> get_CarrierFrequency(This,Frequency)

#define IDVBTLocator_put_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> put_CarrierFrequency(This,Frequency)

#define IDVBTLocator_get_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_InnerFEC(This,FEC)

#define IDVBTLocator_put_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_InnerFEC(This,FEC)

#define IDVBTLocator_get_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_InnerFECRate(This,FEC)

#define IDVBTLocator_put_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_InnerFECRate(This,FEC)

#define IDVBTLocator_get_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> get_OuterFEC(This,FEC)

#define IDVBTLocator_put_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> put_OuterFEC(This,FEC)

#define IDVBTLocator_get_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> get_OuterFECRate(This,FEC)

#define IDVBTLocator_put_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> put_OuterFECRate(This,FEC)

#define IDVBTLocator_get_Modulation(This,Modulation)	\
    (This)->lpVtbl -> get_Modulation(This,Modulation)

#define IDVBTLocator_put_Modulation(This,Modulation)	\
    (This)->lpVtbl -> put_Modulation(This,Modulation)

#define IDVBTLocator_get_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> get_SymbolRate(This,Rate)

#define IDVBTLocator_put_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> put_SymbolRate(This,Rate)

#define IDVBTLocator_Clone(This,NewLocator)	\
    (This)->lpVtbl -> Clone(This,NewLocator)


#define IDVBTLocator_get_Bandwidth(This,BandWidthVal)	\
    (This)->lpVtbl -> get_Bandwidth(This,BandWidthVal)

#define IDVBTLocator_put_Bandwidth(This,BandwidthVal)	\
    (This)->lpVtbl -> put_Bandwidth(This,BandwidthVal)

#define IDVBTLocator_get_LPInnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_LPInnerFEC(This,FEC)

#define IDVBTLocator_put_LPInnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_LPInnerFEC(This,FEC)

#define IDVBTLocator_get_LPInnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_LPInnerFECRate(This,FEC)

#define IDVBTLocator_put_LPInnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_LPInnerFECRate(This,FEC)

#define IDVBTLocator_get_HAlpha(This,Alpha)	\
    (This)->lpVtbl -> get_HAlpha(This,Alpha)

#define IDVBTLocator_put_HAlpha(This,Alpha)	\
    (This)->lpVtbl -> put_HAlpha(This,Alpha)

#define IDVBTLocator_get_Guard(This,GI)	\
    (This)->lpVtbl -> get_Guard(This,GI)

#define IDVBTLocator_put_Guard(This,GI)	\
    (This)->lpVtbl -> put_Guard(This,GI)

#define IDVBTLocator_get_Mode(This,mode)	\
    (This)->lpVtbl -> get_Mode(This,mode)

#define IDVBTLocator_put_Mode(This,mode)	\
    (This)->lpVtbl -> put_Mode(This,mode)

#define IDVBTLocator_get_OtherFrequencyInUse(This,OtherFrequencyInUseVal)	\
    (This)->lpVtbl -> get_OtherFrequencyInUse(This,OtherFrequencyInUseVal)

#define IDVBTLocator_put_OtherFrequencyInUse(This,OtherFrequencyInUseVal)	\
    (This)->lpVtbl -> put_OtherFrequencyInUse(This,OtherFrequencyInUseVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_Bandwidth_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ long *BandWidthVal);


void __RPC_STUB IDVBTLocator_get_Bandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_Bandwidth_Proxy( 
    IDVBTLocator * This,
    /* [in] */ long BandwidthVal);


void __RPC_STUB IDVBTLocator_put_Bandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_LPInnerFEC_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ FECMethod *FEC);


void __RPC_STUB IDVBTLocator_get_LPInnerFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_LPInnerFEC_Proxy( 
    IDVBTLocator * This,
    /* [in] */ FECMethod FEC);


void __RPC_STUB IDVBTLocator_put_LPInnerFEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_LPInnerFECRate_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ BinaryConvolutionCodeRate *FEC);


void __RPC_STUB IDVBTLocator_get_LPInnerFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_LPInnerFECRate_Proxy( 
    IDVBTLocator * This,
    /* [in] */ BinaryConvolutionCodeRate FEC);


void __RPC_STUB IDVBTLocator_put_LPInnerFECRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_HAlpha_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ HierarchyAlpha *Alpha);


void __RPC_STUB IDVBTLocator_get_HAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_HAlpha_Proxy( 
    IDVBTLocator * This,
    /* [in] */ HierarchyAlpha Alpha);


void __RPC_STUB IDVBTLocator_put_HAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_Guard_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ GuardInterval *GI);


void __RPC_STUB IDVBTLocator_get_Guard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_Guard_Proxy( 
    IDVBTLocator * This,
    /* [in] */ GuardInterval GI);


void __RPC_STUB IDVBTLocator_put_Guard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_Mode_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ TransmissionMode *mode);


void __RPC_STUB IDVBTLocator_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_Mode_Proxy( 
    IDVBTLocator * This,
    /* [in] */ TransmissionMode mode);


void __RPC_STUB IDVBTLocator_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_get_OtherFrequencyInUse_Proxy( 
    IDVBTLocator * This,
    /* [retval][out] */ VARIANT_BOOL *OtherFrequencyInUseVal);


void __RPC_STUB IDVBTLocator_get_OtherFrequencyInUse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBTLocator_put_OtherFrequencyInUse_Proxy( 
    IDVBTLocator * This,
    /* [in] */ VARIANT_BOOL OtherFrequencyInUseVal);


void __RPC_STUB IDVBTLocator_put_OtherFrequencyInUse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBTLocator_INTERFACE_DEFINED__ */


#ifndef __IDVBSLocator_INTERFACE_DEFINED__
#define __IDVBSLocator_INTERFACE_DEFINED__

/* interface IDVBSLocator */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IDVBSLocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D7C353C-0D04-45f1-A742-F97CC1188DC8")
    IDVBSLocator : public ILocator
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignalPolarisation( 
            /* [retval][out] */ Polarisation *PolarisationVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignalPolarisation( 
            /* [in] */ Polarisation PolarisationVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WestPosition( 
            /* [retval][out] */ VARIANT_BOOL *WestLongitude) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WestPosition( 
            /* [in] */ VARIANT_BOOL WestLongitude) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrbitalPosition( 
            /* [retval][out] */ long *longitude) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OrbitalPosition( 
            /* [in] */ long longitude) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Azimuth( 
            /* [retval][out] */ long *Azimuth) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Azimuth( 
            /* [in] */ long Azimuth) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Elevation( 
            /* [retval][out] */ long *Elevation) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Elevation( 
            /* [in] */ long Elevation) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVBSLocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBSLocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBSLocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBSLocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBSLocator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBSLocator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBSLocator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBSLocator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CarrierFrequency )( 
            IDVBSLocator * This,
            /* [retval][out] */ long *Frequency);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CarrierFrequency )( 
            IDVBSLocator * This,
            /* [in] */ long Frequency);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFEC )( 
            IDVBSLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFEC )( 
            IDVBSLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFECRate )( 
            IDVBSLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFECRate )( 
            IDVBSLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFEC )( 
            IDVBSLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFEC )( 
            IDVBSLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFECRate )( 
            IDVBSLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFECRate )( 
            IDVBSLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modulation )( 
            IDVBSLocator * This,
            /* [retval][out] */ ModulationType *Modulation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Modulation )( 
            IDVBSLocator * This,
            /* [in] */ ModulationType Modulation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolRate )( 
            IDVBSLocator * This,
            /* [retval][out] */ long *Rate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SymbolRate )( 
            IDVBSLocator * This,
            /* [in] */ long Rate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBSLocator * This,
            /* [retval][out] */ ILocator **NewLocator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignalPolarisation )( 
            IDVBSLocator * This,
            /* [retval][out] */ Polarisation *PolarisationVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SignalPolarisation )( 
            IDVBSLocator * This,
            /* [in] */ Polarisation PolarisationVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WestPosition )( 
            IDVBSLocator * This,
            /* [retval][out] */ VARIANT_BOOL *WestLongitude);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WestPosition )( 
            IDVBSLocator * This,
            /* [in] */ VARIANT_BOOL WestLongitude);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrbitalPosition )( 
            IDVBSLocator * This,
            /* [retval][out] */ long *longitude);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OrbitalPosition )( 
            IDVBSLocator * This,
            /* [in] */ long longitude);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Azimuth )( 
            IDVBSLocator * This,
            /* [retval][out] */ long *Azimuth);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Azimuth )( 
            IDVBSLocator * This,
            /* [in] */ long Azimuth);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Elevation )( 
            IDVBSLocator * This,
            /* [retval][out] */ long *Elevation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Elevation )( 
            IDVBSLocator * This,
            /* [in] */ long Elevation);
        
        END_INTERFACE
    } IDVBSLocatorVtbl;

    interface IDVBSLocator
    {
        CONST_VTBL struct IDVBSLocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBSLocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBSLocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBSLocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBSLocator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBSLocator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBSLocator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBSLocator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBSLocator_get_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> get_CarrierFrequency(This,Frequency)

#define IDVBSLocator_put_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> put_CarrierFrequency(This,Frequency)

#define IDVBSLocator_get_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_InnerFEC(This,FEC)

#define IDVBSLocator_put_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_InnerFEC(This,FEC)

#define IDVBSLocator_get_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_InnerFECRate(This,FEC)

#define IDVBSLocator_put_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_InnerFECRate(This,FEC)

#define IDVBSLocator_get_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> get_OuterFEC(This,FEC)

#define IDVBSLocator_put_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> put_OuterFEC(This,FEC)

#define IDVBSLocator_get_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> get_OuterFECRate(This,FEC)

#define IDVBSLocator_put_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> put_OuterFECRate(This,FEC)

#define IDVBSLocator_get_Modulation(This,Modulation)	\
    (This)->lpVtbl -> get_Modulation(This,Modulation)

#define IDVBSLocator_put_Modulation(This,Modulation)	\
    (This)->lpVtbl -> put_Modulation(This,Modulation)

#define IDVBSLocator_get_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> get_SymbolRate(This,Rate)

#define IDVBSLocator_put_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> put_SymbolRate(This,Rate)

#define IDVBSLocator_Clone(This,NewLocator)	\
    (This)->lpVtbl -> Clone(This,NewLocator)


#define IDVBSLocator_get_SignalPolarisation(This,PolarisationVal)	\
    (This)->lpVtbl -> get_SignalPolarisation(This,PolarisationVal)

#define IDVBSLocator_put_SignalPolarisation(This,PolarisationVal)	\
    (This)->lpVtbl -> put_SignalPolarisation(This,PolarisationVal)

#define IDVBSLocator_get_WestPosition(This,WestLongitude)	\
    (This)->lpVtbl -> get_WestPosition(This,WestLongitude)

#define IDVBSLocator_put_WestPosition(This,WestLongitude)	\
    (This)->lpVtbl -> put_WestPosition(This,WestLongitude)

#define IDVBSLocator_get_OrbitalPosition(This,longitude)	\
    (This)->lpVtbl -> get_OrbitalPosition(This,longitude)

#define IDVBSLocator_put_OrbitalPosition(This,longitude)	\
    (This)->lpVtbl -> put_OrbitalPosition(This,longitude)

#define IDVBSLocator_get_Azimuth(This,Azimuth)	\
    (This)->lpVtbl -> get_Azimuth(This,Azimuth)

#define IDVBSLocator_put_Azimuth(This,Azimuth)	\
    (This)->lpVtbl -> put_Azimuth(This,Azimuth)

#define IDVBSLocator_get_Elevation(This,Elevation)	\
    (This)->lpVtbl -> get_Elevation(This,Elevation)

#define IDVBSLocator_put_Elevation(This,Elevation)	\
    (This)->lpVtbl -> put_Elevation(This,Elevation)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_get_SignalPolarisation_Proxy( 
    IDVBSLocator * This,
    /* [retval][out] */ Polarisation *PolarisationVal);


void __RPC_STUB IDVBSLocator_get_SignalPolarisation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_put_SignalPolarisation_Proxy( 
    IDVBSLocator * This,
    /* [in] */ Polarisation PolarisationVal);


void __RPC_STUB IDVBSLocator_put_SignalPolarisation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_get_WestPosition_Proxy( 
    IDVBSLocator * This,
    /* [retval][out] */ VARIANT_BOOL *WestLongitude);


void __RPC_STUB IDVBSLocator_get_WestPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_put_WestPosition_Proxy( 
    IDVBSLocator * This,
    /* [in] */ VARIANT_BOOL WestLongitude);


void __RPC_STUB IDVBSLocator_put_WestPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_get_OrbitalPosition_Proxy( 
    IDVBSLocator * This,
    /* [retval][out] */ long *longitude);


void __RPC_STUB IDVBSLocator_get_OrbitalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_put_OrbitalPosition_Proxy( 
    IDVBSLocator * This,
    /* [in] */ long longitude);


void __RPC_STUB IDVBSLocator_put_OrbitalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_get_Azimuth_Proxy( 
    IDVBSLocator * This,
    /* [retval][out] */ long *Azimuth);


void __RPC_STUB IDVBSLocator_get_Azimuth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_put_Azimuth_Proxy( 
    IDVBSLocator * This,
    /* [in] */ long Azimuth);


void __RPC_STUB IDVBSLocator_put_Azimuth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_get_Elevation_Proxy( 
    IDVBSLocator * This,
    /* [retval][out] */ long *Elevation);


void __RPC_STUB IDVBSLocator_get_Elevation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDVBSLocator_put_Elevation_Proxy( 
    IDVBSLocator * This,
    /* [in] */ long Elevation);


void __RPC_STUB IDVBSLocator_put_Elevation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVBSLocator_INTERFACE_DEFINED__ */


#ifndef __IDVBCLocator_INTERFACE_DEFINED__
#define __IDVBCLocator_INTERFACE_DEFINED__

/* interface IDVBCLocator */
/* [unique][helpstring][oleautomation][dual][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IDVBCLocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E42F36E-1DD2-43c4-9F78-69D25AE39034")
    IDVBCLocator : public ILocator
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDVBCLocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVBCLocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVBCLocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVBCLocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDVBCLocator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDVBCLocator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDVBCLocator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDVBCLocator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CarrierFrequency )( 
            IDVBCLocator * This,
            /* [retval][out] */ long *Frequency);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CarrierFrequency )( 
            IDVBCLocator * This,
            /* [in] */ long Frequency);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFEC )( 
            IDVBCLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFEC )( 
            IDVBCLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InnerFECRate )( 
            IDVBCLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InnerFECRate )( 
            IDVBCLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFEC )( 
            IDVBCLocator * This,
            /* [retval][out] */ FECMethod *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFEC )( 
            IDVBCLocator * This,
            /* [in] */ FECMethod FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OuterFECRate )( 
            IDVBCLocator * This,
            /* [retval][out] */ BinaryConvolutionCodeRate *FEC);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OuterFECRate )( 
            IDVBCLocator * This,
            /* [in] */ BinaryConvolutionCodeRate FEC);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modulation )( 
            IDVBCLocator * This,
            /* [retval][out] */ ModulationType *Modulation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Modulation )( 
            IDVBCLocator * This,
            /* [in] */ ModulationType Modulation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolRate )( 
            IDVBCLocator * This,
            /* [retval][out] */ long *Rate);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SymbolRate )( 
            IDVBCLocator * This,
            /* [in] */ long Rate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IDVBCLocator * This,
            /* [retval][out] */ ILocator **NewLocator);
        
        END_INTERFACE
    } IDVBCLocatorVtbl;

    interface IDVBCLocator
    {
        CONST_VTBL struct IDVBCLocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVBCLocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVBCLocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVBCLocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVBCLocator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDVBCLocator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDVBCLocator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDVBCLocator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDVBCLocator_get_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> get_CarrierFrequency(This,Frequency)

#define IDVBCLocator_put_CarrierFrequency(This,Frequency)	\
    (This)->lpVtbl -> put_CarrierFrequency(This,Frequency)

#define IDVBCLocator_get_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> get_InnerFEC(This,FEC)

#define IDVBCLocator_put_InnerFEC(This,FEC)	\
    (This)->lpVtbl -> put_InnerFEC(This,FEC)

#define IDVBCLocator_get_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> get_InnerFECRate(This,FEC)

#define IDVBCLocator_put_InnerFECRate(This,FEC)	\
    (This)->lpVtbl -> put_InnerFECRate(This,FEC)

#define IDVBCLocator_get_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> get_OuterFEC(This,FEC)

#define IDVBCLocator_put_OuterFEC(This,FEC)	\
    (This)->lpVtbl -> put_OuterFEC(This,FEC)

#define IDVBCLocator_get_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> get_OuterFECRate(This,FEC)

#define IDVBCLocator_put_OuterFECRate(This,FEC)	\
    (This)->lpVtbl -> put_OuterFECRate(This,FEC)

#define IDVBCLocator_get_Modulation(This,Modulation)	\
    (This)->lpVtbl -> get_Modulation(This,Modulation)

#define IDVBCLocator_put_Modulation(This,Modulation)	\
    (This)->lpVtbl -> put_Modulation(This,Modulation)

#define IDVBCLocator_get_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> get_SymbolRate(This,Rate)

#define IDVBCLocator_put_SymbolRate(This,Rate)	\
    (This)->lpVtbl -> put_SymbolRate(This,Rate)

#define IDVBCLocator_Clone(This,NewLocator)	\
    (This)->lpVtbl -> Clone(This,NewLocator)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDVBCLocator_INTERFACE_DEFINED__ */


#ifndef __IBroadcastEvent_INTERFACE_DEFINED__
#define __IBroadcastEvent_INTERFACE_DEFINED__

/* interface IBroadcastEvent */
/* [unique][helpstring][uuid][nonextensible][hidden][object] */ 


EXTERN_C const IID IID_IBroadcastEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B21263F-26E8-489d-AAC4-924F7EFD9511")
    IBroadcastEvent : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Fire( 
            GUID EventID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBroadcastEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBroadcastEvent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBroadcastEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBroadcastEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *Fire )( 
            IBroadcastEvent * This,
            GUID EventID);
        
        END_INTERFACE
    } IBroadcastEventVtbl;

    interface IBroadcastEvent
    {
        CONST_VTBL struct IBroadcastEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBroadcastEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBroadcastEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBroadcastEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBroadcastEvent_Fire(This,EventID)	\
    (This)->lpVtbl -> Fire(This,EventID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBroadcastEvent_Fire_Proxy( 
    IBroadcastEvent * This,
    GUID EventID);


void __RPC_STUB IBroadcastEvent_Fire_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBroadcastEvent_INTERFACE_DEFINED__ */



#ifndef __TunerLib_LIBRARY_DEFINED__
#define __TunerLib_LIBRARY_DEFINED__

/* library TunerLib */
/* [helpstring][version][uuid] */ 

#define SID_SBroadcastEventService CLSID_BroadcastEventService

EXTERN_C const IID LIBID_TunerLib;

EXTERN_C const CLSID CLSID_SystemTuningSpaces;

#ifdef __cplusplus

class DECLSPEC_UUID("D02AAC50-027E-11d3-9D8E-00C04F72D980")
SystemTuningSpaces;
#endif

EXTERN_C const CLSID CLSID_TuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("5FFDC5E6-B83A-4b55-B6E8-C69E765FE9DB")
TuningSpace;
#endif

EXTERN_C const CLSID CLSID_ATSCTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("A2E30750-6C3D-11d3-B653-00C04F79498E")
ATSCTuningSpace;
#endif

EXTERN_C const CLSID CLSID_AnalogRadioTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("8A674B4C-1F63-11d3-B64C-00C04F79498E")
AnalogRadioTuningSpace;
#endif

EXTERN_C const CLSID CLSID_AuxInTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("F9769A06-7ACA-4e39-9CFB-97BB35F0E77E")
AuxInTuningSpace;
#endif

EXTERN_C const CLSID CLSID_AnalogTVTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("8A674B4D-1F63-11d3-B64C-00C04F79498E")
AnalogTVTuningSpace;
#endif

EXTERN_C const CLSID CLSID_DVBTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("C6B14B32-76AA-4a86-A7AC-5C79AAF58DA7")
DVBTuningSpace;
#endif

EXTERN_C const CLSID CLSID_DVBSTuningSpace;

#ifdef __cplusplus

class DECLSPEC_UUID("B64016F3-C9A2-4066-96F0-BD9563314726")
DVBSTuningSpace;
#endif

EXTERN_C const CLSID CLSID_ComponentTypes;

#ifdef __cplusplus

class DECLSPEC_UUID("A1A2B1C4-0E3A-11d3-9D8E-00C04F72D980")
ComponentTypes;
#endif

EXTERN_C const CLSID CLSID_ComponentType;

#ifdef __cplusplus

class DECLSPEC_UUID("823535A0-0318-11d3-9D8E-00C04F72D980")
ComponentType;
#endif

EXTERN_C const CLSID CLSID_LanguageComponentType;

#ifdef __cplusplus

class DECLSPEC_UUID("1BE49F30-0E1B-11d3-9D8E-00C04F72D980")
LanguageComponentType;
#endif

EXTERN_C const CLSID CLSID_MPEG2ComponentType;

#ifdef __cplusplus

class DECLSPEC_UUID("418008F3-CF67-4668-9628-10DC52BE1D08")
MPEG2ComponentType;
#endif

EXTERN_C const CLSID CLSID_ATSCComponentType;

#ifdef __cplusplus

class DECLSPEC_UUID("A8DCF3D5-0780-4ef4-8A83-2CFFAACB8ACE")
ATSCComponentType;
#endif

EXTERN_C const CLSID CLSID_Components;

#ifdef __cplusplus

class DECLSPEC_UUID("809B6661-94C4-49e6-B6EC-3F0F862215AA")
Components;
#endif

EXTERN_C const CLSID CLSID_Component;

#ifdef __cplusplus

class DECLSPEC_UUID("59DC47A8-116C-11d3-9D8E-00C04F72D980")
Component;
#endif

EXTERN_C const CLSID CLSID_MPEG2Component;

#ifdef __cplusplus

class DECLSPEC_UUID("055CB2D7-2969-45cd-914B-76890722F112")
MPEG2Component;
#endif

EXTERN_C const CLSID CLSID_TuneRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("B46E0D38-AB35-4a06-A137-70576B01B39F")
TuneRequest;
#endif

EXTERN_C const CLSID CLSID_ChannelTuneRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("0369B4E5-45B6-11d3-B650-00C04F79498E")
ChannelTuneRequest;
#endif

EXTERN_C const CLSID CLSID_ATSCChannelTuneRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("0369B4E6-45B6-11d3-B650-00C04F79498E")
ATSCChannelTuneRequest;
#endif

EXTERN_C const CLSID CLSID_MPEG2TuneRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("0955AC62-BF2E-4cba-A2B9-A63F772D46CF")
MPEG2TuneRequest;
#endif

EXTERN_C const CLSID CLSID_MPEG2TuneRequestFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("2C63E4EB-4CEA-41b8-919C-E947EA19A77C")
MPEG2TuneRequestFactory;
#endif

EXTERN_C const CLSID CLSID_Locator;

#ifdef __cplusplus

class DECLSPEC_UUID("0888C883-AC4F-4943-B516-2C38D9B34562")
Locator;
#endif

EXTERN_C const CLSID CLSID_ATSCLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("8872FF1B-98FA-4d7a-8D93-C9F1055F85BB")
ATSCLocator;
#endif

EXTERN_C const CLSID CLSID_DVBTLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("9CD64701-BDF3-4d14-8E03-F12983D86664")
DVBTLocator;
#endif

EXTERN_C const CLSID CLSID_DVBSLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("1DF7D126-4050-47f0-A7CF-4C4CA9241333")
DVBSLocator;
#endif

EXTERN_C const CLSID CLSID_DVBCLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("C531D9FD-9685-4028-8B68-6E1232079F1E")
DVBCLocator;
#endif

EXTERN_C const CLSID CLSID_DVBTuneRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("15D6504A-5494-499c-886C-973C9E53B9F1")
DVBTuneRequest;
#endif

EXTERN_C const CLSID CLSID_CreatePropBagOnRegKey;

#ifdef __cplusplus

class DECLSPEC_UUID("8A674B49-1F63-11d3-B64C-00C04F79498E")
CreatePropBagOnRegKey;
#endif

EXTERN_C const CLSID CLSID_BroadcastEventService;

#ifdef __cplusplus

class DECLSPEC_UUID("0B3FFB92-0919-4934-9D5B-619C719D0202")
BroadcastEventService;
#endif
#endif /* __TunerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


