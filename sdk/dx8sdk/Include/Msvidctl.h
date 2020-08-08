
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for msvidctl.idl:
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

#ifndef __msvidctl_h__
#define __msvidctl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMSVidCtl_FWD_DEFINED__
#define __IMSVidCtl_FWD_DEFINED__
typedef interface IMSVidCtl IMSVidCtl;
#endif 	/* __IMSVidCtl_FWD_DEFINED__ */


#ifndef __IMSEventBinder_FWD_DEFINED__
#define __IMSEventBinder_FWD_DEFINED__
typedef interface IMSEventBinder IMSEventBinder;
#endif 	/* __IMSEventBinder_FWD_DEFINED__ */


#ifndef ___IMSVidCtlEvents_FWD_DEFINED__
#define ___IMSVidCtlEvents_FWD_DEFINED__
typedef interface _IMSVidCtlEvents _IMSVidCtlEvents;
#endif 	/* ___IMSVidCtlEvents_FWD_DEFINED__ */


#ifndef __MSVidAnalogTunerDevice_FWD_DEFINED__
#define __MSVidAnalogTunerDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogTunerDevice MSVidAnalogTunerDevice;
#else
typedef struct MSVidAnalogTunerDevice MSVidAnalogTunerDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogTunerDevice_FWD_DEFINED__ */


#ifndef __MSVidBDATunerDevice_FWD_DEFINED__
#define __MSVidBDATunerDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidBDATunerDevice MSVidBDATunerDevice;
#else
typedef struct MSVidBDATunerDevice MSVidBDATunerDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidBDATunerDevice_FWD_DEFINED__ */


#ifndef __MSVidFilePlaybackDevice_FWD_DEFINED__
#define __MSVidFilePlaybackDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidFilePlaybackDevice MSVidFilePlaybackDevice;
#else
typedef struct MSVidFilePlaybackDevice MSVidFilePlaybackDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidFilePlaybackDevice_FWD_DEFINED__ */


#ifndef __MSVidWebDVD_FWD_DEFINED__
#define __MSVidWebDVD_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidWebDVD MSVidWebDVD;
#else
typedef struct MSVidWebDVD MSVidWebDVD;
#endif /* __cplusplus */

#endif 	/* __MSVidWebDVD_FWD_DEFINED__ */


#ifndef __MSVidWebDVDAdm_FWD_DEFINED__
#define __MSVidWebDVDAdm_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidWebDVDAdm MSVidWebDVDAdm;
#else
typedef struct MSVidWebDVDAdm MSVidWebDVDAdm;
#endif /* __cplusplus */

#endif 	/* __MSVidWebDVDAdm_FWD_DEFINED__ */


#ifndef __MSVidVideoRenderer_FWD_DEFINED__
#define __MSVidVideoRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidVideoRenderer MSVidVideoRenderer;
#else
typedef struct MSVidVideoRenderer MSVidVideoRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidVideoRenderer_FWD_DEFINED__ */


#ifndef __MSVidAudioRenderer_FWD_DEFINED__
#define __MSVidAudioRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAudioRenderer MSVidAudioRenderer;
#else
typedef struct MSVidAudioRenderer MSVidAudioRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidAudioRenderer_FWD_DEFINED__ */


#ifndef __MSVidStreamBufferSink_FWD_DEFINED__
#define __MSVidStreamBufferSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidStreamBufferSink MSVidStreamBufferSink;
#else
typedef struct MSVidStreamBufferSink MSVidStreamBufferSink;
#endif /* __cplusplus */

#endif 	/* __MSVidStreamBufferSink_FWD_DEFINED__ */


#ifndef __MSVidStreamBufferSource_FWD_DEFINED__
#define __MSVidStreamBufferSource_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidStreamBufferSource MSVidStreamBufferSource;
#else
typedef struct MSVidStreamBufferSource MSVidStreamBufferSource;
#endif /* __cplusplus */

#endif 	/* __MSVidStreamBufferSource_FWD_DEFINED__ */


#ifndef __MSVidDataServices_FWD_DEFINED__
#define __MSVidDataServices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidDataServices MSVidDataServices;
#else
typedef struct MSVidDataServices MSVidDataServices;
#endif /* __cplusplus */

#endif 	/* __MSVidDataServices_FWD_DEFINED__ */


#ifndef __MSVidEncoder_FWD_DEFINED__
#define __MSVidEncoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidEncoder MSVidEncoder;
#else
typedef struct MSVidEncoder MSVidEncoder;
#endif /* __cplusplus */

#endif 	/* __MSVidEncoder_FWD_DEFINED__ */


#ifndef __MSVidXDS_FWD_DEFINED__
#define __MSVidXDS_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidXDS MSVidXDS;
#else
typedef struct MSVidXDS MSVidXDS;
#endif /* __cplusplus */

#endif 	/* __MSVidXDS_FWD_DEFINED__ */


#ifndef __MSVidClosedCaptioning_FWD_DEFINED__
#define __MSVidClosedCaptioning_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidClosedCaptioning MSVidClosedCaptioning;
#else
typedef struct MSVidClosedCaptioning MSVidClosedCaptioning;
#endif /* __cplusplus */

#endif 	/* __MSVidClosedCaptioning_FWD_DEFINED__ */


#ifndef __MSVidCtl_FWD_DEFINED__
#define __MSVidCtl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidCtl MSVidCtl;
#else
typedef struct MSVidCtl MSVidCtl;
#endif /* __cplusplus */

#endif 	/* __MSVidCtl_FWD_DEFINED__ */


#ifndef __MSVidInputDevices_FWD_DEFINED__
#define __MSVidInputDevices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidInputDevices MSVidInputDevices;
#else
typedef struct MSVidInputDevices MSVidInputDevices;
#endif /* __cplusplus */

#endif 	/* __MSVidInputDevices_FWD_DEFINED__ */


#ifndef __MSVidOutputDevices_FWD_DEFINED__
#define __MSVidOutputDevices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidOutputDevices MSVidOutputDevices;
#else
typedef struct MSVidOutputDevices MSVidOutputDevices;
#endif /* __cplusplus */

#endif 	/* __MSVidOutputDevices_FWD_DEFINED__ */


#ifndef __MSVidVideoRendererDevices_FWD_DEFINED__
#define __MSVidVideoRendererDevices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidVideoRendererDevices MSVidVideoRendererDevices;
#else
typedef struct MSVidVideoRendererDevices MSVidVideoRendererDevices;
#endif /* __cplusplus */

#endif 	/* __MSVidVideoRendererDevices_FWD_DEFINED__ */


#ifndef __MSVidAudioRendererDevices_FWD_DEFINED__
#define __MSVidAudioRendererDevices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAudioRendererDevices MSVidAudioRendererDevices;
#else
typedef struct MSVidAudioRendererDevices MSVidAudioRendererDevices;
#endif /* __cplusplus */

#endif 	/* __MSVidAudioRendererDevices_FWD_DEFINED__ */


#ifndef __MSVidFeatures_FWD_DEFINED__
#define __MSVidFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidFeatures MSVidFeatures;
#else
typedef struct MSVidFeatures MSVidFeatures;
#endif /* __cplusplus */

#endif 	/* __MSVidFeatures_FWD_DEFINED__ */


#ifndef __MSVidGenericComposite_FWD_DEFINED__
#define __MSVidGenericComposite_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidGenericComposite MSVidGenericComposite;
#else
typedef struct MSVidGenericComposite MSVidGenericComposite;
#endif /* __cplusplus */

#endif 	/* __MSVidGenericComposite_FWD_DEFINED__ */


#ifndef __MSVidAnalogCaptureToOverlayMixer_FWD_DEFINED__
#define __MSVidAnalogCaptureToOverlayMixer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogCaptureToOverlayMixer MSVidAnalogCaptureToOverlayMixer;
#else
typedef struct MSVidAnalogCaptureToOverlayMixer MSVidAnalogCaptureToOverlayMixer;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogCaptureToOverlayMixer_FWD_DEFINED__ */


#ifndef __MSVidAnalogCaptureToDataServices_FWD_DEFINED__
#define __MSVidAnalogCaptureToDataServices_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogCaptureToDataServices MSVidAnalogCaptureToDataServices;
#else
typedef struct MSVidAnalogCaptureToDataServices MSVidAnalogCaptureToDataServices;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogCaptureToDataServices_FWD_DEFINED__ */


#ifndef __MSVidWebDVDToVideoRenderer_FWD_DEFINED__
#define __MSVidWebDVDToVideoRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidWebDVDToVideoRenderer MSVidWebDVDToVideoRenderer;
#else
typedef struct MSVidWebDVDToVideoRenderer MSVidWebDVDToVideoRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidWebDVDToVideoRenderer_FWD_DEFINED__ */


#ifndef __MSVidWebDVDToAudioRenderer_FWD_DEFINED__
#define __MSVidWebDVDToAudioRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidWebDVDToAudioRenderer MSVidWebDVDToAudioRenderer;
#else
typedef struct MSVidWebDVDToAudioRenderer MSVidWebDVDToAudioRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidWebDVDToAudioRenderer_FWD_DEFINED__ */


#ifndef __MSVidMPEG2DecoderToClosedCaptioning_FWD_DEFINED__
#define __MSVidMPEG2DecoderToClosedCaptioning_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidMPEG2DecoderToClosedCaptioning MSVidMPEG2DecoderToClosedCaptioning;
#else
typedef struct MSVidMPEG2DecoderToClosedCaptioning MSVidMPEG2DecoderToClosedCaptioning;
#endif /* __cplusplus */

#endif 	/* __MSVidMPEG2DecoderToClosedCaptioning_FWD_DEFINED__ */


#ifndef __MSVidAnalogCaptureToStreamBufferSink_FWD_DEFINED__
#define __MSVidAnalogCaptureToStreamBufferSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogCaptureToStreamBufferSink MSVidAnalogCaptureToStreamBufferSink;
#else
typedef struct MSVidAnalogCaptureToStreamBufferSink MSVidAnalogCaptureToStreamBufferSink;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogCaptureToStreamBufferSink_FWD_DEFINED__ */


#ifndef __MSVidDigitalCaptureToStreamBufferSink_FWD_DEFINED__
#define __MSVidDigitalCaptureToStreamBufferSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidDigitalCaptureToStreamBufferSink MSVidDigitalCaptureToStreamBufferSink;
#else
typedef struct MSVidDigitalCaptureToStreamBufferSink MSVidDigitalCaptureToStreamBufferSink;
#endif /* __cplusplus */

#endif 	/* __MSVidDigitalCaptureToStreamBufferSink_FWD_DEFINED__ */


#ifndef __MSVidDataServicesToStreamBufferSink_FWD_DEFINED__
#define __MSVidDataServicesToStreamBufferSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidDataServicesToStreamBufferSink MSVidDataServicesToStreamBufferSink;
#else
typedef struct MSVidDataServicesToStreamBufferSink MSVidDataServicesToStreamBufferSink;
#endif /* __cplusplus */

#endif 	/* __MSVidDataServicesToStreamBufferSink_FWD_DEFINED__ */


#ifndef __MSVidDataServicesToXDS_FWD_DEFINED__
#define __MSVidDataServicesToXDS_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidDataServicesToXDS MSVidDataServicesToXDS;
#else
typedef struct MSVidDataServicesToXDS MSVidDataServicesToXDS;
#endif /* __cplusplus */

#endif 	/* __MSVidDataServicesToXDS_FWD_DEFINED__ */


#ifndef __MSVidEncoderToStreamBufferSink_FWD_DEFINED__
#define __MSVidEncoderToStreamBufferSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidEncoderToStreamBufferSink MSVidEncoderToStreamBufferSink;
#else
typedef struct MSVidEncoderToStreamBufferSink MSVidEncoderToStreamBufferSink;
#endif /* __cplusplus */

#endif 	/* __MSVidEncoderToStreamBufferSink_FWD_DEFINED__ */


#ifndef __MSVidFilePlaybackToVideoRenderer_FWD_DEFINED__
#define __MSVidFilePlaybackToVideoRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidFilePlaybackToVideoRenderer MSVidFilePlaybackToVideoRenderer;
#else
typedef struct MSVidFilePlaybackToVideoRenderer MSVidFilePlaybackToVideoRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidFilePlaybackToVideoRenderer_FWD_DEFINED__ */


#ifndef __MSVidFilePlaybackToAudioRenderer_FWD_DEFINED__
#define __MSVidFilePlaybackToAudioRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidFilePlaybackToAudioRenderer MSVidFilePlaybackToAudioRenderer;
#else
typedef struct MSVidFilePlaybackToAudioRenderer MSVidFilePlaybackToAudioRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidFilePlaybackToAudioRenderer_FWD_DEFINED__ */


#ifndef __MSVidAnalogTVToEncoder_FWD_DEFINED__
#define __MSVidAnalogTVToEncoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogTVToEncoder MSVidAnalogTVToEncoder;
#else
typedef struct MSVidAnalogTVToEncoder MSVidAnalogTVToEncoder;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogTVToEncoder_FWD_DEFINED__ */


#ifndef __MSVidStreamBufferSourceToVideoRenderer_FWD_DEFINED__
#define __MSVidStreamBufferSourceToVideoRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidStreamBufferSourceToVideoRenderer MSVidStreamBufferSourceToVideoRenderer;
#else
typedef struct MSVidStreamBufferSourceToVideoRenderer MSVidStreamBufferSourceToVideoRenderer;
#endif /* __cplusplus */

#endif 	/* __MSVidStreamBufferSourceToVideoRenderer_FWD_DEFINED__ */


#ifndef __MSVidAnalogCaptureToXDS_FWD_DEFINED__
#define __MSVidAnalogCaptureToXDS_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidAnalogCaptureToXDS MSVidAnalogCaptureToXDS;
#else
typedef struct MSVidAnalogCaptureToXDS MSVidAnalogCaptureToXDS;
#endif /* __cplusplus */

#endif 	/* __MSVidAnalogCaptureToXDS_FWD_DEFINED__ */


#ifndef __MSVidSBESourceToCC_FWD_DEFINED__
#define __MSVidSBESourceToCC_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidSBESourceToCC MSVidSBESourceToCC;
#else
typedef struct MSVidSBESourceToCC MSVidSBESourceToCC;
#endif /* __cplusplus */

#endif 	/* __MSVidSBESourceToCC_FWD_DEFINED__ */


#ifndef __MSEventBinder_FWD_DEFINED__
#define __MSEventBinder_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSEventBinder MSEventBinder;
#else
typedef struct MSEventBinder MSEventBinder;
#endif /* __cplusplus */

#endif 	/* __MSEventBinder_FWD_DEFINED__ */


#ifndef __MSVidStreamBufferRecordingControl_FWD_DEFINED__
#define __MSVidStreamBufferRecordingControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidStreamBufferRecordingControl MSVidStreamBufferRecordingControl;
#else
typedef struct MSVidStreamBufferRecordingControl MSVidStreamBufferRecordingControl;
#endif /* __cplusplus */

#endif 	/* __MSVidStreamBufferRecordingControl_FWD_DEFINED__ */


#ifndef __MSVidRect_FWD_DEFINED__
#define __MSVidRect_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidRect MSVidRect;
#else
typedef struct MSVidRect MSVidRect;
#endif /* __cplusplus */

#endif 	/* __MSVidRect_FWD_DEFINED__ */


#ifndef __MSVidDevice_FWD_DEFINED__
#define __MSVidDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidDevice MSVidDevice;
#else
typedef struct MSVidDevice MSVidDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidDevice_FWD_DEFINED__ */


#ifndef __MSVidInputDevice_FWD_DEFINED__
#define __MSVidInputDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidInputDevice MSVidInputDevice;
#else
typedef struct MSVidInputDevice MSVidInputDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidInputDevice_FWD_DEFINED__ */


#ifndef __MSVidVideoInputDevice_FWD_DEFINED__
#define __MSVidVideoInputDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidVideoInputDevice MSVidVideoInputDevice;
#else
typedef struct MSVidVideoInputDevice MSVidVideoInputDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidVideoInputDevice_FWD_DEFINED__ */


#ifndef __MSVidVideoPlaybackDevice_FWD_DEFINED__
#define __MSVidVideoPlaybackDevice_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidVideoPlaybackDevice MSVidVideoPlaybackDevice;
#else
typedef struct MSVidVideoPlaybackDevice MSVidVideoPlaybackDevice;
#endif /* __cplusplus */

#endif 	/* __MSVidVideoPlaybackDevice_FWD_DEFINED__ */


#ifndef __MSVidFeature_FWD_DEFINED__
#define __MSVidFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidFeature MSVidFeature;
#else
typedef struct MSVidFeature MSVidFeature;
#endif /* __cplusplus */

#endif 	/* __MSVidFeature_FWD_DEFINED__ */


#ifndef __MSVidOutput_FWD_DEFINED__
#define __MSVidOutput_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSVidOutput MSVidOutput;
#else
typedef struct MSVidOutput MSVidOutput;
#endif /* __cplusplus */

#endif 	/* __MSVidOutput_FWD_DEFINED__ */


/* header files for imported files */
#include "mshtml.h"
#include "segment.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_msvidctl_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1999-2000.
//
//--------------------------------------------------------------------------
#pragma once
typedef /* [public] */ 
enum __MIDL___MIDL_itf_msvidctl_0000_0001
    {	dispidInputs	= 0,
	dispidOutputs	= dispidInputs + 1,
	dispid_Inputs	= dispidOutputs + 1,
	dispid_Outputs	= dispid_Inputs + 1,
	dispidVideoRenderers	= dispid_Outputs + 1,
	dispidAudioRenderers	= dispidVideoRenderers + 1,
	dispidFeatures	= dispidAudioRenderers + 1,
	dispidInput	= dispidFeatures + 1,
	dispidOutput	= dispidInput + 1,
	dispidVideoRenderer	= dispidOutput + 1,
	dispidAudioRenderer	= dispidVideoRenderer + 1,
	dispidSelectedFeatures	= dispidAudioRenderer + 1,
	dispidView	= dispidSelectedFeatures + 1,
	dispidBuild	= dispidView + 1,
	dispidPause	= dispidBuild + 1,
	dispidRun	= dispidPause + 1,
	dispidStop	= dispidRun + 1,
	dispidDecompose	= dispidStop + 1,
	dispidDisplaySize	= dispidDecompose + 1,
	dispidMaintainAspectRatio	= dispidDisplaySize + 1,
	dispidColorKey	= dispidMaintainAspectRatio + 1,
	dispidStateChange	= dispidColorKey + 1,
	dispidgetState	= dispidStateChange + 1,
	dispidunbind	= dispidgetState + 1,
	dispidbind	= dispidunbind + 1,
	dispidDisableVideo	= dispidbind + 1,
	dispidDisableAudio	= dispidDisableVideo + 1,
	dispidViewNext	= dispidDisableAudio + 1,
	dispidServiceP	= dispidViewNext + 1
    } 	MSViddispidList;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_msvidctl_0000_0002
    {	dslDefaultSize	= 0,
	dslSourceSize	= 0,
	dslHalfSourceSize	= dslSourceSize + 1,
	dslDoubleSourceSize	= dslHalfSourceSize + 1,
	dslFullScreen	= dslDoubleSourceSize + 1,
	dslHalfScreen	= dslFullScreen + 1,
	dslQuarterScreen	= dslHalfScreen + 1,
	dslSixteenthScreen	= dslQuarterScreen + 1
    } 	DisplaySizeList;

typedef /* [public][public][public][public] */ 
enum __MIDL___MIDL_itf_msvidctl_0000_0003
    {	STATE_UNBUILT	= -1,
	STATE_STOP	= STATE_UNBUILT + 1,
	STATE_PAUSE	= STATE_STOP + 1,
	STATE_PLAY	= STATE_PAUSE + 1
    } 	MSVidCtlStateList;



extern RPC_IF_HANDLE __MIDL_itf_msvidctl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msvidctl_0000_v0_0_s_ifspec;

#ifndef __IMSVidCtl_INTERFACE_DEFINED__
#define __IMSVidCtl_INTERFACE_DEFINED__

/* interface IMSVidCtl */
/* [unique][helpstring][nonextensible][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_IMSVidCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0EDF162-910A-11D2-B632-00C04F79498E")
    IMSVidCtl : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoSize( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoSize( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *backcolor) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR backcolor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TabStop( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TabStop( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ HWND *phwnd) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplaySize( 
            /* [retval][out] */ DisplaySizeList *CurrentValue) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplaySize( 
            /* [in] */ DisplaySizeList NewValue) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MaintainAspectRatio( 
            /* [retval][out] */ VARIANT_BOOL *CurrentValue) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MaintainAspectRatio( 
            /* [in] */ VARIANT_BOOL NewValue) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ColorKey( 
            /* [retval][out] */ OLE_COLOR *CurrentValue) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ColorKey( 
            /* [in] */ OLE_COLOR NewValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputsAvailable( 
            /* [in] */ BSTR CategoryGuid,
            /* [retval][out] */ IMSVidInputDevices **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputsAvailable( 
            /* [in] */ BSTR CategoryGuid,
            /* [retval][out] */ IMSVidOutputDevices **pVal) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__InputsAvailable( 
            /* [in] */ LPCGUID CategoryGuid,
            /* [retval][out] */ IMSVidInputDevices **pVal) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__OutputsAvailable( 
            /* [in] */ LPCGUID CategoryGuid,
            /* [retval][out] */ IMSVidOutputDevices **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoRenderersAvailable( 
            /* [retval][out] */ IMSVidVideoRendererDevices **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioRenderersAvailable( 
            /* [retval][out] */ IMSVidAudioRendererDevices **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeaturesAvailable( 
            /* [retval][out] */ IMSVidFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputActive( 
            /* [retval][out] */ IMSVidInputDevice **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputActive( 
            /* [in] */ IMSVidInputDevice *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputsActive( 
            /* [retval][out] */ IMSVidOutputDevices **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputsActive( 
            /* [in] */ IMSVidOutputDevices *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoRendererActive( 
            /* [retval][out] */ IMSVidVideoRenderer **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoRendererActive( 
            /* [in] */ IMSVidVideoRenderer *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioRendererActive( 
            /* [retval][out] */ IMSVidAudioRenderer **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioRendererActive( 
            /* [in] */ IMSVidAudioRenderer *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeaturesActive( 
            /* [retval][out] */ IMSVidFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeaturesActive( 
            /* [in] */ IMSVidFeatures *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ MSVidCtlStateList *lState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE View( 
            /* [in] */ VARIANT *v) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Build( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Decompose( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableVideo( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableAudio( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewNext( 
            /* [in] */ VARIANT *v) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServiceProvider( 
            /* [in] */ IUnknown *pServiceP) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSVidCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSVidCtl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSVidCtl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSVidCtl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMSVidCtl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMSVidCtl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMSVidCtl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMSVidCtl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoSize )( 
            IMSVidCtl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoSize )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IMSVidCtl * This,
            /* [retval][out] */ OLE_COLOR *backcolor);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IMSVidCtl * This,
            /* [in] */ OLE_COLOR backcolor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IMSVidCtl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TabStop )( 
            IMSVidCtl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TabStop )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            IMSVidCtl * This,
            /* [retval][out] */ HWND *phwnd);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMSVidCtl * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplaySize )( 
            IMSVidCtl * This,
            /* [retval][out] */ DisplaySizeList *CurrentValue);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisplaySize )( 
            IMSVidCtl * This,
            /* [in] */ DisplaySizeList NewValue);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaintainAspectRatio )( 
            IMSVidCtl * This,
            /* [retval][out] */ VARIANT_BOOL *CurrentValue);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaintainAspectRatio )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT_BOOL NewValue);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColorKey )( 
            IMSVidCtl * This,
            /* [retval][out] */ OLE_COLOR *CurrentValue);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ColorKey )( 
            IMSVidCtl * This,
            /* [in] */ OLE_COLOR NewValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputsAvailable )( 
            IMSVidCtl * This,
            /* [in] */ BSTR CategoryGuid,
            /* [retval][out] */ IMSVidInputDevices **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputsAvailable )( 
            IMSVidCtl * This,
            /* [in] */ BSTR CategoryGuid,
            /* [retval][out] */ IMSVidOutputDevices **pVal);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__InputsAvailable )( 
            IMSVidCtl * This,
            /* [in] */ LPCGUID CategoryGuid,
            /* [retval][out] */ IMSVidInputDevices **pVal);
        
        /* [helpstring][restricted][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__OutputsAvailable )( 
            IMSVidCtl * This,
            /* [in] */ LPCGUID CategoryGuid,
            /* [retval][out] */ IMSVidOutputDevices **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoRenderersAvailable )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidVideoRendererDevices **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioRenderersAvailable )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidAudioRendererDevices **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FeaturesAvailable )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidFeatures **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputActive )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidInputDevice **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputActive )( 
            IMSVidCtl * This,
            /* [in] */ IMSVidInputDevice *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputsActive )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidOutputDevices **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputsActive )( 
            IMSVidCtl * This,
            /* [in] */ IMSVidOutputDevices *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoRendererActive )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidVideoRenderer **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoRendererActive )( 
            IMSVidCtl * This,
            /* [in] */ IMSVidVideoRenderer *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioRendererActive )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidAudioRenderer **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioRendererActive )( 
            IMSVidCtl * This,
            /* [in] */ IMSVidAudioRenderer *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FeaturesActive )( 
            IMSVidCtl * This,
            /* [retval][out] */ IMSVidFeatures **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FeaturesActive )( 
            IMSVidCtl * This,
            /* [in] */ IMSVidFeatures *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IMSVidCtl * This,
            /* [retval][out] */ MSVidCtlStateList *lState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *View )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT *v);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Build )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Decompose )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableVideo )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableAudio )( 
            IMSVidCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewNext )( 
            IMSVidCtl * This,
            /* [in] */ VARIANT *v);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceProvider )( 
            IMSVidCtl * This,
            /* [in] */ IUnknown *pServiceP);
        
        END_INTERFACE
    } IMSVidCtlVtbl;

    interface IMSVidCtl
    {
        CONST_VTBL struct IMSVidCtlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSVidCtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSVidCtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSVidCtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSVidCtl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMSVidCtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMSVidCtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMSVidCtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMSVidCtl_get_AutoSize(This,pbool)	\
    (This)->lpVtbl -> get_AutoSize(This,pbool)

#define IMSVidCtl_put_AutoSize(This,vbool)	\
    (This)->lpVtbl -> put_AutoSize(This,vbool)

#define IMSVidCtl_get_BackColor(This,backcolor)	\
    (This)->lpVtbl -> get_BackColor(This,backcolor)

#define IMSVidCtl_put_BackColor(This,backcolor)	\
    (This)->lpVtbl -> put_BackColor(This,backcolor)

#define IMSVidCtl_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IMSVidCtl_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IMSVidCtl_get_TabStop(This,pbool)	\
    (This)->lpVtbl -> get_TabStop(This,pbool)

#define IMSVidCtl_put_TabStop(This,vbool)	\
    (This)->lpVtbl -> put_TabStop(This,vbool)

#define IMSVidCtl_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define IMSVidCtl_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IMSVidCtl_get_DisplaySize(This,CurrentValue)	\
    (This)->lpVtbl -> get_DisplaySize(This,CurrentValue)

#define IMSVidCtl_put_DisplaySize(This,NewValue)	\
    (This)->lpVtbl -> put_DisplaySize(This,NewValue)

#define IMSVidCtl_get_MaintainAspectRatio(This,CurrentValue)	\
    (This)->lpVtbl -> get_MaintainAspectRatio(This,CurrentValue)

#define IMSVidCtl_put_MaintainAspectRatio(This,NewValue)	\
    (This)->lpVtbl -> put_MaintainAspectRatio(This,NewValue)

#define IMSVidCtl_get_ColorKey(This,CurrentValue)	\
    (This)->lpVtbl -> get_ColorKey(This,CurrentValue)

#define IMSVidCtl_put_ColorKey(This,NewValue)	\
    (This)->lpVtbl -> put_ColorKey(This,NewValue)

#define IMSVidCtl_get_InputsAvailable(This,CategoryGuid,pVal)	\
    (This)->lpVtbl -> get_InputsAvailable(This,CategoryGuid,pVal)

#define IMSVidCtl_get_OutputsAvailable(This,CategoryGuid,pVal)	\
    (This)->lpVtbl -> get_OutputsAvailable(This,CategoryGuid,pVal)

#define IMSVidCtl_get__InputsAvailable(This,CategoryGuid,pVal)	\
    (This)->lpVtbl -> get__InputsAvailable(This,CategoryGuid,pVal)

#define IMSVidCtl_get__OutputsAvailable(This,CategoryGuid,pVal)	\
    (This)->lpVtbl -> get__OutputsAvailable(This,CategoryGuid,pVal)

#define IMSVidCtl_get_VideoRenderersAvailable(This,pVal)	\
    (This)->lpVtbl -> get_VideoRenderersAvailable(This,pVal)

#define IMSVidCtl_get_AudioRenderersAvailable(This,pVal)	\
    (This)->lpVtbl -> get_AudioRenderersAvailable(This,pVal)

#define IMSVidCtl_get_FeaturesAvailable(This,pVal)	\
    (This)->lpVtbl -> get_FeaturesAvailable(This,pVal)

#define IMSVidCtl_get_InputActive(This,pVal)	\
    (This)->lpVtbl -> get_InputActive(This,pVal)

#define IMSVidCtl_put_InputActive(This,pVal)	\
    (This)->lpVtbl -> put_InputActive(This,pVal)

#define IMSVidCtl_get_OutputsActive(This,pVal)	\
    (This)->lpVtbl -> get_OutputsActive(This,pVal)

#define IMSVidCtl_put_OutputsActive(This,pVal)	\
    (This)->lpVtbl -> put_OutputsActive(This,pVal)

#define IMSVidCtl_get_VideoRendererActive(This,pVal)	\
    (This)->lpVtbl -> get_VideoRendererActive(This,pVal)

#define IMSVidCtl_put_VideoRendererActive(This,pVal)	\
    (This)->lpVtbl -> put_VideoRendererActive(This,pVal)

#define IMSVidCtl_get_AudioRendererActive(This,pVal)	\
    (This)->lpVtbl -> get_AudioRendererActive(This,pVal)

#define IMSVidCtl_put_AudioRendererActive(This,pVal)	\
    (This)->lpVtbl -> put_AudioRendererActive(This,pVal)

#define IMSVidCtl_get_FeaturesActive(This,pVal)	\
    (This)->lpVtbl -> get_FeaturesActive(This,pVal)

#define IMSVidCtl_put_FeaturesActive(This,pVal)	\
    (This)->lpVtbl -> put_FeaturesActive(This,pVal)

#define IMSVidCtl_get_State(This,lState)	\
    (This)->lpVtbl -> get_State(This,lState)

#define IMSVidCtl_View(This,v)	\
    (This)->lpVtbl -> View(This,v)

#define IMSVidCtl_Build(This)	\
    (This)->lpVtbl -> Build(This)

#define IMSVidCtl_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMSVidCtl_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IMSVidCtl_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMSVidCtl_Decompose(This)	\
    (This)->lpVtbl -> Decompose(This)

#define IMSVidCtl_DisableVideo(This)	\
    (This)->lpVtbl -> DisableVideo(This)

#define IMSVidCtl_DisableAudio(This)	\
    (This)->lpVtbl -> DisableAudio(This)

#define IMSVidCtl_ViewNext(This,v)	\
    (This)->lpVtbl -> ViewNext(This,v)

#define IMSVidCtl_put_ServiceProvider(This,pServiceP)	\
    (This)->lpVtbl -> put_ServiceProvider(This,pServiceP)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_AutoSize_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IMSVidCtl_get_AutoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_AutoSize_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IMSVidCtl_put_AutoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_BackColor_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ OLE_COLOR *backcolor);


void __RPC_STUB IMSVidCtl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_BackColor_Proxy( 
    IMSVidCtl * This,
    /* [in] */ OLE_COLOR backcolor);


void __RPC_STUB IMSVidCtl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_Enabled_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IMSVidCtl_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_Enabled_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IMSVidCtl_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_TabStop_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IMSVidCtl_get_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_TabStop_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IMSVidCtl_put_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_Window_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ HWND *phwnd);


void __RPC_STUB IMSVidCtl_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Refresh_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_DisplaySize_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ DisplaySizeList *CurrentValue);


void __RPC_STUB IMSVidCtl_get_DisplaySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_DisplaySize_Proxy( 
    IMSVidCtl * This,
    /* [in] */ DisplaySizeList NewValue);


void __RPC_STUB IMSVidCtl_put_DisplaySize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_MaintainAspectRatio_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ VARIANT_BOOL *CurrentValue);


void __RPC_STUB IMSVidCtl_get_MaintainAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_MaintainAspectRatio_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT_BOOL NewValue);


void __RPC_STUB IMSVidCtl_put_MaintainAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_ColorKey_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ OLE_COLOR *CurrentValue);


void __RPC_STUB IMSVidCtl_get_ColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_ColorKey_Proxy( 
    IMSVidCtl * This,
    /* [in] */ OLE_COLOR NewValue);


void __RPC_STUB IMSVidCtl_put_ColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_InputsAvailable_Proxy( 
    IMSVidCtl * This,
    /* [in] */ BSTR CategoryGuid,
    /* [retval][out] */ IMSVidInputDevices **pVal);


void __RPC_STUB IMSVidCtl_get_InputsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_OutputsAvailable_Proxy( 
    IMSVidCtl * This,
    /* [in] */ BSTR CategoryGuid,
    /* [retval][out] */ IMSVidOutputDevices **pVal);


void __RPC_STUB IMSVidCtl_get_OutputsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get__InputsAvailable_Proxy( 
    IMSVidCtl * This,
    /* [in] */ LPCGUID CategoryGuid,
    /* [retval][out] */ IMSVidInputDevices **pVal);


void __RPC_STUB IMSVidCtl_get__InputsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get__OutputsAvailable_Proxy( 
    IMSVidCtl * This,
    /* [in] */ LPCGUID CategoryGuid,
    /* [retval][out] */ IMSVidOutputDevices **pVal);


void __RPC_STUB IMSVidCtl_get__OutputsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_VideoRenderersAvailable_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidVideoRendererDevices **pVal);


void __RPC_STUB IMSVidCtl_get_VideoRenderersAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_AudioRenderersAvailable_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidAudioRendererDevices **pVal);


void __RPC_STUB IMSVidCtl_get_AudioRenderersAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_FeaturesAvailable_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidFeatures **pVal);


void __RPC_STUB IMSVidCtl_get_FeaturesAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_InputActive_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidInputDevice **pVal);


void __RPC_STUB IMSVidCtl_get_InputActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_InputActive_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IMSVidInputDevice *pVal);


void __RPC_STUB IMSVidCtl_put_InputActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_OutputsActive_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidOutputDevices **pVal);


void __RPC_STUB IMSVidCtl_get_OutputsActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_OutputsActive_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IMSVidOutputDevices *pVal);


void __RPC_STUB IMSVidCtl_put_OutputsActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_VideoRendererActive_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidVideoRenderer **pVal);


void __RPC_STUB IMSVidCtl_get_VideoRendererActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_VideoRendererActive_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IMSVidVideoRenderer *pVal);


void __RPC_STUB IMSVidCtl_put_VideoRendererActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_AudioRendererActive_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidAudioRenderer **pVal);


void __RPC_STUB IMSVidCtl_get_AudioRendererActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_AudioRendererActive_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IMSVidAudioRenderer *pVal);


void __RPC_STUB IMSVidCtl_put_AudioRendererActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_FeaturesActive_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ IMSVidFeatures **pVal);


void __RPC_STUB IMSVidCtl_get_FeaturesActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_FeaturesActive_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IMSVidFeatures *pVal);


void __RPC_STUB IMSVidCtl_put_FeaturesActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_get_State_Proxy( 
    IMSVidCtl * This,
    /* [retval][out] */ MSVidCtlStateList *lState);


void __RPC_STUB IMSVidCtl_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_View_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT *v);


void __RPC_STUB IMSVidCtl_View_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Build_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Build_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Pause_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Run_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Stop_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_Decompose_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_Decompose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_DisableVideo_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_DisableVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_DisableAudio_Proxy( 
    IMSVidCtl * This);


void __RPC_STUB IMSVidCtl_DisableAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_ViewNext_Proxy( 
    IMSVidCtl * This,
    /* [in] */ VARIANT *v);


void __RPC_STUB IMSVidCtl_ViewNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMSVidCtl_put_ServiceProvider_Proxy( 
    IMSVidCtl * This,
    /* [in] */ IUnknown *pServiceP);


void __RPC_STUB IMSVidCtl_put_ServiceProvider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSVidCtl_INTERFACE_DEFINED__ */


#ifndef __IMSEventBinder_INTERFACE_DEFINED__
#define __IMSEventBinder_INTERFACE_DEFINED__

/* interface IMSEventBinder */
/* [helpstring][uuid][unique][nonextensible][hidden][oleautomation][dual][object] */ 


EXTERN_C const IID IID_IMSEventBinder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3A9F406-2222-436D-86D5-BA3229279EFB")
    IMSEventBinder : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bind( 
            /* [in] */ LPDISPATCH pEventObject,
            /* [in] */ BSTR EventName,
            /* [in] */ BSTR EventHandler,
            /* [retval][out] */ LONG *CancelID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unbind( 
            /* [in] */ DWORD CancelCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSEventBinderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSEventBinder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSEventBinder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSEventBinder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMSEventBinder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMSEventBinder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMSEventBinder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMSEventBinder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bind )( 
            IMSEventBinder * This,
            /* [in] */ LPDISPATCH pEventObject,
            /* [in] */ BSTR EventName,
            /* [in] */ BSTR EventHandler,
            /* [retval][out] */ LONG *CancelID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unbind )( 
            IMSEventBinder * This,
            /* [in] */ DWORD CancelCookie);
        
        END_INTERFACE
    } IMSEventBinderVtbl;

    interface IMSEventBinder
    {
        CONST_VTBL struct IMSEventBinderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSEventBinder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSEventBinder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSEventBinder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSEventBinder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMSEventBinder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMSEventBinder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMSEventBinder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMSEventBinder_Bind(This,pEventObject,EventName,EventHandler,CancelID)	\
    (This)->lpVtbl -> Bind(This,pEventObject,EventName,EventHandler,CancelID)

#define IMSEventBinder_Unbind(This,CancelCookie)	\
    (This)->lpVtbl -> Unbind(This,CancelCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSEventBinder_Bind_Proxy( 
    IMSEventBinder * This,
    /* [in] */ LPDISPATCH pEventObject,
    /* [in] */ BSTR EventName,
    /* [in] */ BSTR EventHandler,
    /* [retval][out] */ LONG *CancelID);


void __RPC_STUB IMSEventBinder_Bind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMSEventBinder_Unbind_Proxy( 
    IMSEventBinder * This,
    /* [in] */ DWORD CancelCookie);


void __RPC_STUB IMSEventBinder_Unbind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSEventBinder_INTERFACE_DEFINED__ */



#ifndef __MSVidCtlLib_LIBRARY_DEFINED__
#define __MSVidCtlLib_LIBRARY_DEFINED__

/* library MSVidCtlLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MSVidCtlLib;

#ifndef ___IMSVidCtlEvents_DISPINTERFACE_DEFINED__
#define ___IMSVidCtlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMSVidCtlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMSVidCtlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B0EDF164-910A-11D2-B632-00C04F79498E")
    _IMSVidCtlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMSVidCtlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IMSVidCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IMSVidCtlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IMSVidCtlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IMSVidCtlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IMSVidCtlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IMSVidCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IMSVidCtlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IMSVidCtlEventsVtbl;

    interface _IMSVidCtlEvents
    {
        CONST_VTBL struct _IMSVidCtlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMSVidCtlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMSVidCtlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMSVidCtlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMSVidCtlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMSVidCtlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMSVidCtlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMSVidCtlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMSVidCtlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MSVidAnalogTunerDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("1C15D484-911D-11d2-B632-00C04F79498E")
MSVidAnalogTunerDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidBDATunerDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("A2E3074E-6C3D-11d3-B653-00C04F79498E")
MSVidBDATunerDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidFilePlaybackDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("37B0353C-A4C8-11d2-B634-00C04F79498E")
MSVidFilePlaybackDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidWebDVD;

#ifdef __cplusplus

class DECLSPEC_UUID("011B3619-FE63-4814-8A84-15A194CE9CE3")
MSVidWebDVD;
#endif

EXTERN_C const CLSID CLSID_MSVidWebDVDAdm;

#ifdef __cplusplus

class DECLSPEC_UUID("FA7C375B-66A7-4280-879D-FD459C84BB02")
MSVidWebDVDAdm;
#endif

EXTERN_C const CLSID CLSID_MSVidVideoRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("37B03543-A4C8-11d2-B634-00C04F79498E")
MSVidVideoRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidAudioRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("37B03544-A4C8-11d2-B634-00C04F79498E")
MSVidAudioRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidStreamBufferSink;

#ifdef __cplusplus

class DECLSPEC_UUID("9E77AAC4-35E5-42a1-BDC2-8F3FF399847C")
MSVidStreamBufferSink;
#endif

EXTERN_C const CLSID CLSID_MSVidStreamBufferSource;

#ifdef __cplusplus

class DECLSPEC_UUID("AD8E510D-217F-409b-8076-29C5E73B98E8")
MSVidStreamBufferSource;
#endif

EXTERN_C const CLSID CLSID_MSVidDataServices;

#ifdef __cplusplus

class DECLSPEC_UUID("334125C0-77E5-11d3-B653-00C04F79498E")
MSVidDataServices;
#endif

EXTERN_C const CLSID CLSID_MSVidEncoder;

#ifdef __cplusplus

class DECLSPEC_UUID("BB530C63-D9DF-4b49-9439-63453962E598")
MSVidEncoder;
#endif

EXTERN_C const CLSID CLSID_MSVidXDS;

#ifdef __cplusplus

class DECLSPEC_UUID("0149EEDF-D08F-4142-8D73-D23903D21E90")
MSVidXDS;
#endif

EXTERN_C const CLSID CLSID_MSVidClosedCaptioning;

#ifdef __cplusplus

class DECLSPEC_UUID("7F9CB14D-48E4-43b6-9346-1AEBC39C64D3")
MSVidClosedCaptioning;
#endif

EXTERN_C const CLSID CLSID_MSVidCtl;

#ifdef __cplusplus

class DECLSPEC_UUID("B0EDF163-910A-11D2-B632-00C04F79498E")
MSVidCtl;
#endif

EXTERN_C const CLSID CLSID_MSVidInputDevices;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CCC-9B79-11d3-B654-00C04F79498E")
MSVidInputDevices;
#endif

EXTERN_C const CLSID CLSID_MSVidOutputDevices;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CCD-9B79-11d3-B654-00C04F79498E")
MSVidOutputDevices;
#endif

EXTERN_C const CLSID CLSID_MSVidVideoRendererDevices;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CCE-9B79-11d3-B654-00C04F79498E")
MSVidVideoRendererDevices;
#endif

EXTERN_C const CLSID CLSID_MSVidAudioRendererDevices;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CCF-9B79-11d3-B654-00C04F79498E")
MSVidAudioRendererDevices;
#endif

EXTERN_C const CLSID CLSID_MSVidFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CD0-9B79-11d3-B654-00C04F79498E")
MSVidFeatures;
#endif

EXTERN_C const CLSID CLSID_MSVidGenericComposite;

#ifdef __cplusplus

class DECLSPEC_UUID("2764BCE5-CC39-11D2-B639-00C04F79498E")
MSVidGenericComposite;
#endif

EXTERN_C const CLSID CLSID_MSVidAnalogCaptureToOverlayMixer;

#ifdef __cplusplus

class DECLSPEC_UUID("E18AF75A-08AF-11d3-B64A-00C04F79498E")
MSVidAnalogCaptureToOverlayMixer;
#endif

EXTERN_C const CLSID CLSID_MSVidAnalogCaptureToDataServices;

#ifdef __cplusplus

class DECLSPEC_UUID("C5702CD6-9B79-11d3-B654-00C04F79498E")
MSVidAnalogCaptureToDataServices;
#endif

EXTERN_C const CLSID CLSID_MSVidWebDVDToVideoRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("267db0b3-55e3-4902-949b-df8f5cec0191")
MSVidWebDVDToVideoRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidWebDVDToAudioRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("8D04238E-9FD1-41c6-8DE3-9E1EE309E935")
MSVidWebDVDToAudioRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidMPEG2DecoderToClosedCaptioning;

#ifdef __cplusplus

class DECLSPEC_UUID("6AD28EE1-5002-4e71-AAF7-BD077907B1A4")
MSVidMPEG2DecoderToClosedCaptioning;
#endif

EXTERN_C const CLSID CLSID_MSVidAnalogCaptureToStreamBufferSink;

#ifdef __cplusplus

class DECLSPEC_UUID("9F50E8B1-9530-4ddc-825E-1AF81D47AED6")
MSVidAnalogCaptureToStreamBufferSink;
#endif

EXTERN_C const CLSID CLSID_MSVidDigitalCaptureToStreamBufferSink;

#ifdef __cplusplus

class DECLSPEC_UUID("ABE40035-27C3-4a2f-8153-6624471608AF")
MSVidDigitalCaptureToStreamBufferSink;
#endif

EXTERN_C const CLSID CLSID_MSVidDataServicesToStreamBufferSink;

#ifdef __cplusplus

class DECLSPEC_UUID("38F03426-E83B-4e68-B65B-DCAE73304838")
MSVidDataServicesToStreamBufferSink;
#endif

EXTERN_C const CLSID CLSID_MSVidDataServicesToXDS;

#ifdef __cplusplus

class DECLSPEC_UUID("0429EC6E-1144-4bed-B88B-2FB9899A4A3D")
MSVidDataServicesToXDS;
#endif

EXTERN_C const CLSID CLSID_MSVidEncoderToStreamBufferSink;

#ifdef __cplusplus

class DECLSPEC_UUID("A0B9B497-AFBC-45ad-A8A6-9B077C40D4F2")
MSVidEncoderToStreamBufferSink;
#endif

EXTERN_C const CLSID CLSID_MSVidFilePlaybackToVideoRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("B401C5EB-8457-427f-84EA-A4D2363364B0")
MSVidFilePlaybackToVideoRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidFilePlaybackToAudioRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("CC23F537-18D4-4ece-93BD-207A84726979")
MSVidFilePlaybackToAudioRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidAnalogTVToEncoder;

#ifdef __cplusplus

class DECLSPEC_UUID("28953661-0231-41db-8986-21FF4388EE9B")
MSVidAnalogTVToEncoder;
#endif

EXTERN_C const CLSID CLSID_MSVidStreamBufferSourceToVideoRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("3C4708DC-B181-46a8-8DA8-4AB0371758CD")
MSVidStreamBufferSourceToVideoRenderer;
#endif

EXTERN_C const CLSID CLSID_MSVidAnalogCaptureToXDS;

#ifdef __cplusplus

class DECLSPEC_UUID("3540D440-5B1D-49cb-821A-E84B8CF065A7")
MSVidAnalogCaptureToXDS;
#endif

EXTERN_C const CLSID CLSID_MSVidSBESourceToCC;

#ifdef __cplusplus

class DECLSPEC_UUID("9193A8F9-0CBA-400e-AA97-EB4709164576")
MSVidSBESourceToCC;
#endif

EXTERN_C const CLSID CLSID_MSEventBinder;

#ifdef __cplusplus

class DECLSPEC_UUID("577FAA18-4518-445E-8F70-1473F8CF4BA4")
MSEventBinder;
#endif

EXTERN_C const CLSID CLSID_MSVidStreamBufferRecordingControl;

#ifdef __cplusplus

class DECLSPEC_UUID("CAAFDD83-CEFC-4e3d-BA03-175F17A24F91")
MSVidStreamBufferRecordingControl;
#endif

EXTERN_C const CLSID CLSID_MSVidRect;

#ifdef __cplusplus

class DECLSPEC_UUID("CB4276E6-7D5F-4cf1-9727-629C5E6DB6AE")
MSVidRect;
#endif

EXTERN_C const CLSID CLSID_MSVidDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("6E40476F-9C49-4c3e-8BB9-8587958EFF74")
MSVidDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidInputDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("AC1972F2-138A-4ca3-90DA-AE51112EDA28")
MSVidInputDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidVideoInputDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("95F4820B-BB3A-4e2d-BC64-5B817BC2C30E")
MSVidVideoInputDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidVideoPlaybackDevice;

#ifdef __cplusplus

class DECLSPEC_UUID("1990D634-1A5E-4071-A34A-53AAFFCE9F36")
MSVidVideoPlaybackDevice;
#endif

EXTERN_C const CLSID CLSID_MSVidFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("7748530B-C08A-47ea-B24C-BE8695FF405F")
MSVidFeature;
#endif

EXTERN_C const CLSID CLSID_MSVidOutput;

#ifdef __cplusplus

class DECLSPEC_UUID("87EB890D-03AD-4e9d-9866-376E5EC572ED")
MSVidOutput;
#endif
#endif /* __MSVidCtlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


