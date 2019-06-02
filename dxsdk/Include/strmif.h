
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for strmif.idl:
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

#ifndef __strmif_h__
#define __strmif_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICreateDevEnum_FWD_DEFINED__
#define __ICreateDevEnum_FWD_DEFINED__
typedef interface ICreateDevEnum ICreateDevEnum;
#endif 	/* __ICreateDevEnum_FWD_DEFINED__ */


#ifndef __IPin_FWD_DEFINED__
#define __IPin_FWD_DEFINED__
typedef interface IPin IPin;
#endif 	/* __IPin_FWD_DEFINED__ */


#ifndef __IEnumPins_FWD_DEFINED__
#define __IEnumPins_FWD_DEFINED__
typedef interface IEnumPins IEnumPins;
#endif 	/* __IEnumPins_FWD_DEFINED__ */


#ifndef __IEnumMediaTypes_FWD_DEFINED__
#define __IEnumMediaTypes_FWD_DEFINED__
typedef interface IEnumMediaTypes IEnumMediaTypes;
#endif 	/* __IEnumMediaTypes_FWD_DEFINED__ */


#ifndef __IFilterGraph_FWD_DEFINED__
#define __IFilterGraph_FWD_DEFINED__
typedef interface IFilterGraph IFilterGraph;
#endif 	/* __IFilterGraph_FWD_DEFINED__ */


#ifndef __IEnumFilters_FWD_DEFINED__
#define __IEnumFilters_FWD_DEFINED__
typedef interface IEnumFilters IEnumFilters;
#endif 	/* __IEnumFilters_FWD_DEFINED__ */


#ifndef __IMediaFilter_FWD_DEFINED__
#define __IMediaFilter_FWD_DEFINED__
typedef interface IMediaFilter IMediaFilter;
#endif 	/* __IMediaFilter_FWD_DEFINED__ */


#ifndef __IBaseFilter_FWD_DEFINED__
#define __IBaseFilter_FWD_DEFINED__
typedef interface IBaseFilter IBaseFilter;
#endif 	/* __IBaseFilter_FWD_DEFINED__ */


#ifndef __IReferenceClock_FWD_DEFINED__
#define __IReferenceClock_FWD_DEFINED__
typedef interface IReferenceClock IReferenceClock;
#endif 	/* __IReferenceClock_FWD_DEFINED__ */


#ifndef __IReferenceClock2_FWD_DEFINED__
#define __IReferenceClock2_FWD_DEFINED__
typedef interface IReferenceClock2 IReferenceClock2;
#endif 	/* __IReferenceClock2_FWD_DEFINED__ */


#ifndef __IMediaSample_FWD_DEFINED__
#define __IMediaSample_FWD_DEFINED__
typedef interface IMediaSample IMediaSample;
#endif 	/* __IMediaSample_FWD_DEFINED__ */


#ifndef __IMediaSample2_FWD_DEFINED__
#define __IMediaSample2_FWD_DEFINED__
typedef interface IMediaSample2 IMediaSample2;
#endif 	/* __IMediaSample2_FWD_DEFINED__ */


#ifndef __IMemAllocator_FWD_DEFINED__
#define __IMemAllocator_FWD_DEFINED__
typedef interface IMemAllocator IMemAllocator;
#endif 	/* __IMemAllocator_FWD_DEFINED__ */


#ifndef __IMemAllocatorCallbackTemp_FWD_DEFINED__
#define __IMemAllocatorCallbackTemp_FWD_DEFINED__
typedef interface IMemAllocatorCallbackTemp IMemAllocatorCallbackTemp;
#endif 	/* __IMemAllocatorCallbackTemp_FWD_DEFINED__ */


#ifndef __IMemAllocatorNotifyCallbackTemp_FWD_DEFINED__
#define __IMemAllocatorNotifyCallbackTemp_FWD_DEFINED__
typedef interface IMemAllocatorNotifyCallbackTemp IMemAllocatorNotifyCallbackTemp;
#endif 	/* __IMemAllocatorNotifyCallbackTemp_FWD_DEFINED__ */


#ifndef __IMemInputPin_FWD_DEFINED__
#define __IMemInputPin_FWD_DEFINED__
typedef interface IMemInputPin IMemInputPin;
#endif 	/* __IMemInputPin_FWD_DEFINED__ */


#ifndef __IAMovieSetup_FWD_DEFINED__
#define __IAMovieSetup_FWD_DEFINED__
typedef interface IAMovieSetup IAMovieSetup;
#endif 	/* __IAMovieSetup_FWD_DEFINED__ */


#ifndef __IMediaSeeking_FWD_DEFINED__
#define __IMediaSeeking_FWD_DEFINED__
typedef interface IMediaSeeking IMediaSeeking;
#endif 	/* __IMediaSeeking_FWD_DEFINED__ */


#ifndef __IEnumRegFilters_FWD_DEFINED__
#define __IEnumRegFilters_FWD_DEFINED__
typedef interface IEnumRegFilters IEnumRegFilters;
#endif 	/* __IEnumRegFilters_FWD_DEFINED__ */


#ifndef __IFilterMapper_FWD_DEFINED__
#define __IFilterMapper_FWD_DEFINED__
typedef interface IFilterMapper IFilterMapper;
#endif 	/* __IFilterMapper_FWD_DEFINED__ */


#ifndef __IFilterMapper2_FWD_DEFINED__
#define __IFilterMapper2_FWD_DEFINED__
typedef interface IFilterMapper2 IFilterMapper2;
#endif 	/* __IFilterMapper2_FWD_DEFINED__ */


#ifndef __IFilterMapper3_FWD_DEFINED__
#define __IFilterMapper3_FWD_DEFINED__
typedef interface IFilterMapper3 IFilterMapper3;
#endif 	/* __IFilterMapper3_FWD_DEFINED__ */


#ifndef __IQualityControl_FWD_DEFINED__
#define __IQualityControl_FWD_DEFINED__
typedef interface IQualityControl IQualityControl;
#endif 	/* __IQualityControl_FWD_DEFINED__ */


#ifndef __IOverlayNotify_FWD_DEFINED__
#define __IOverlayNotify_FWD_DEFINED__
typedef interface IOverlayNotify IOverlayNotify;
#endif 	/* __IOverlayNotify_FWD_DEFINED__ */


#ifndef __IOverlayNotify2_FWD_DEFINED__
#define __IOverlayNotify2_FWD_DEFINED__
typedef interface IOverlayNotify2 IOverlayNotify2;
#endif 	/* __IOverlayNotify2_FWD_DEFINED__ */


#ifndef __IOverlay_FWD_DEFINED__
#define __IOverlay_FWD_DEFINED__
typedef interface IOverlay IOverlay;
#endif 	/* __IOverlay_FWD_DEFINED__ */


#ifndef __IMediaEventSink_FWD_DEFINED__
#define __IMediaEventSink_FWD_DEFINED__
typedef interface IMediaEventSink IMediaEventSink;
#endif 	/* __IMediaEventSink_FWD_DEFINED__ */


#ifndef __IFileSourceFilter_FWD_DEFINED__
#define __IFileSourceFilter_FWD_DEFINED__
typedef interface IFileSourceFilter IFileSourceFilter;
#endif 	/* __IFileSourceFilter_FWD_DEFINED__ */


#ifndef __IFileSinkFilter_FWD_DEFINED__
#define __IFileSinkFilter_FWD_DEFINED__
typedef interface IFileSinkFilter IFileSinkFilter;
#endif 	/* __IFileSinkFilter_FWD_DEFINED__ */


#ifndef __IFileSinkFilter2_FWD_DEFINED__
#define __IFileSinkFilter2_FWD_DEFINED__
typedef interface IFileSinkFilter2 IFileSinkFilter2;
#endif 	/* __IFileSinkFilter2_FWD_DEFINED__ */


#ifndef __IGraphBuilder_FWD_DEFINED__
#define __IGraphBuilder_FWD_DEFINED__
typedef interface IGraphBuilder IGraphBuilder;
#endif 	/* __IGraphBuilder_FWD_DEFINED__ */


#ifndef __ICaptureGraphBuilder_FWD_DEFINED__
#define __ICaptureGraphBuilder_FWD_DEFINED__
typedef interface ICaptureGraphBuilder ICaptureGraphBuilder;
#endif 	/* __ICaptureGraphBuilder_FWD_DEFINED__ */


#ifndef __IAMCopyCaptureFileProgress_FWD_DEFINED__
#define __IAMCopyCaptureFileProgress_FWD_DEFINED__
typedef interface IAMCopyCaptureFileProgress IAMCopyCaptureFileProgress;
#endif 	/* __IAMCopyCaptureFileProgress_FWD_DEFINED__ */


#ifndef __ICaptureGraphBuilder2_FWD_DEFINED__
#define __ICaptureGraphBuilder2_FWD_DEFINED__
typedef interface ICaptureGraphBuilder2 ICaptureGraphBuilder2;
#endif 	/* __ICaptureGraphBuilder2_FWD_DEFINED__ */


#ifndef __IFilterGraph2_FWD_DEFINED__
#define __IFilterGraph2_FWD_DEFINED__
typedef interface IFilterGraph2 IFilterGraph2;
#endif 	/* __IFilterGraph2_FWD_DEFINED__ */


#ifndef __IStreamBuilder_FWD_DEFINED__
#define __IStreamBuilder_FWD_DEFINED__
typedef interface IStreamBuilder IStreamBuilder;
#endif 	/* __IStreamBuilder_FWD_DEFINED__ */


#ifndef __IAsyncReader_FWD_DEFINED__
#define __IAsyncReader_FWD_DEFINED__
typedef interface IAsyncReader IAsyncReader;
#endif 	/* __IAsyncReader_FWD_DEFINED__ */


#ifndef __IGraphVersion_FWD_DEFINED__
#define __IGraphVersion_FWD_DEFINED__
typedef interface IGraphVersion IGraphVersion;
#endif 	/* __IGraphVersion_FWD_DEFINED__ */


#ifndef __IResourceConsumer_FWD_DEFINED__
#define __IResourceConsumer_FWD_DEFINED__
typedef interface IResourceConsumer IResourceConsumer;
#endif 	/* __IResourceConsumer_FWD_DEFINED__ */


#ifndef __IResourceManager_FWD_DEFINED__
#define __IResourceManager_FWD_DEFINED__
typedef interface IResourceManager IResourceManager;
#endif 	/* __IResourceManager_FWD_DEFINED__ */


#ifndef __IDistributorNotify_FWD_DEFINED__
#define __IDistributorNotify_FWD_DEFINED__
typedef interface IDistributorNotify IDistributorNotify;
#endif 	/* __IDistributorNotify_FWD_DEFINED__ */


#ifndef __IAMStreamControl_FWD_DEFINED__
#define __IAMStreamControl_FWD_DEFINED__
typedef interface IAMStreamControl IAMStreamControl;
#endif 	/* __IAMStreamControl_FWD_DEFINED__ */


#ifndef __ISeekingPassThru_FWD_DEFINED__
#define __ISeekingPassThru_FWD_DEFINED__
typedef interface ISeekingPassThru ISeekingPassThru;
#endif 	/* __ISeekingPassThru_FWD_DEFINED__ */


#ifndef __IAMStreamConfig_FWD_DEFINED__
#define __IAMStreamConfig_FWD_DEFINED__
typedef interface IAMStreamConfig IAMStreamConfig;
#endif 	/* __IAMStreamConfig_FWD_DEFINED__ */


#ifndef __IConfigInterleaving_FWD_DEFINED__
#define __IConfigInterleaving_FWD_DEFINED__
typedef interface IConfigInterleaving IConfigInterleaving;
#endif 	/* __IConfigInterleaving_FWD_DEFINED__ */


#ifndef __IConfigAviMux_FWD_DEFINED__
#define __IConfigAviMux_FWD_DEFINED__
typedef interface IConfigAviMux IConfigAviMux;
#endif 	/* __IConfigAviMux_FWD_DEFINED__ */


#ifndef __IAMVideoCompression_FWD_DEFINED__
#define __IAMVideoCompression_FWD_DEFINED__
typedef interface IAMVideoCompression IAMVideoCompression;
#endif 	/* __IAMVideoCompression_FWD_DEFINED__ */


#ifndef __IAMVfwCaptureDialogs_FWD_DEFINED__
#define __IAMVfwCaptureDialogs_FWD_DEFINED__
typedef interface IAMVfwCaptureDialogs IAMVfwCaptureDialogs;
#endif 	/* __IAMVfwCaptureDialogs_FWD_DEFINED__ */


#ifndef __IAMVfwCompressDialogs_FWD_DEFINED__
#define __IAMVfwCompressDialogs_FWD_DEFINED__
typedef interface IAMVfwCompressDialogs IAMVfwCompressDialogs;
#endif 	/* __IAMVfwCompressDialogs_FWD_DEFINED__ */


#ifndef __IAMDroppedFrames_FWD_DEFINED__
#define __IAMDroppedFrames_FWD_DEFINED__
typedef interface IAMDroppedFrames IAMDroppedFrames;
#endif 	/* __IAMDroppedFrames_FWD_DEFINED__ */


#ifndef __IAMAudioInputMixer_FWD_DEFINED__
#define __IAMAudioInputMixer_FWD_DEFINED__
typedef interface IAMAudioInputMixer IAMAudioInputMixer;
#endif 	/* __IAMAudioInputMixer_FWD_DEFINED__ */


#ifndef __IAMBufferNegotiation_FWD_DEFINED__
#define __IAMBufferNegotiation_FWD_DEFINED__
typedef interface IAMBufferNegotiation IAMBufferNegotiation;
#endif 	/* __IAMBufferNegotiation_FWD_DEFINED__ */


#ifndef __IAMAnalogVideoDecoder_FWD_DEFINED__
#define __IAMAnalogVideoDecoder_FWD_DEFINED__
typedef interface IAMAnalogVideoDecoder IAMAnalogVideoDecoder;
#endif 	/* __IAMAnalogVideoDecoder_FWD_DEFINED__ */


#ifndef __IAMVideoProcAmp_FWD_DEFINED__
#define __IAMVideoProcAmp_FWD_DEFINED__
typedef interface IAMVideoProcAmp IAMVideoProcAmp;
#endif 	/* __IAMVideoProcAmp_FWD_DEFINED__ */


#ifndef __IAMCameraControl_FWD_DEFINED__
#define __IAMCameraControl_FWD_DEFINED__
typedef interface IAMCameraControl IAMCameraControl;
#endif 	/* __IAMCameraControl_FWD_DEFINED__ */


#ifndef __IAMVideoControl_FWD_DEFINED__
#define __IAMVideoControl_FWD_DEFINED__
typedef interface IAMVideoControl IAMVideoControl;
#endif 	/* __IAMVideoControl_FWD_DEFINED__ */


#ifndef __IAMCrossbar_FWD_DEFINED__
#define __IAMCrossbar_FWD_DEFINED__
typedef interface IAMCrossbar IAMCrossbar;
#endif 	/* __IAMCrossbar_FWD_DEFINED__ */


#ifndef __IAMTuner_FWD_DEFINED__
#define __IAMTuner_FWD_DEFINED__
typedef interface IAMTuner IAMTuner;
#endif 	/* __IAMTuner_FWD_DEFINED__ */


#ifndef __IAMTunerNotification_FWD_DEFINED__
#define __IAMTunerNotification_FWD_DEFINED__
typedef interface IAMTunerNotification IAMTunerNotification;
#endif 	/* __IAMTunerNotification_FWD_DEFINED__ */


#ifndef __IAMTVTuner_FWD_DEFINED__
#define __IAMTVTuner_FWD_DEFINED__
typedef interface IAMTVTuner IAMTVTuner;
#endif 	/* __IAMTVTuner_FWD_DEFINED__ */


#ifndef __IBPCSatelliteTuner_FWD_DEFINED__
#define __IBPCSatelliteTuner_FWD_DEFINED__
typedef interface IBPCSatelliteTuner IBPCSatelliteTuner;
#endif 	/* __IBPCSatelliteTuner_FWD_DEFINED__ */


#ifndef __IAMTVAudio_FWD_DEFINED__
#define __IAMTVAudio_FWD_DEFINED__
typedef interface IAMTVAudio IAMTVAudio;
#endif 	/* __IAMTVAudio_FWD_DEFINED__ */


#ifndef __IAMTVAudioNotification_FWD_DEFINED__
#define __IAMTVAudioNotification_FWD_DEFINED__
typedef interface IAMTVAudioNotification IAMTVAudioNotification;
#endif 	/* __IAMTVAudioNotification_FWD_DEFINED__ */


#ifndef __IAMAnalogVideoEncoder_FWD_DEFINED__
#define __IAMAnalogVideoEncoder_FWD_DEFINED__
typedef interface IAMAnalogVideoEncoder IAMAnalogVideoEncoder;
#endif 	/* __IAMAnalogVideoEncoder_FWD_DEFINED__ */


#ifndef __IKsPropertySet_FWD_DEFINED__
#define __IKsPropertySet_FWD_DEFINED__
typedef interface IKsPropertySet IKsPropertySet;
#endif 	/* __IKsPropertySet_FWD_DEFINED__ */


#ifndef __IMediaPropertyBag_FWD_DEFINED__
#define __IMediaPropertyBag_FWD_DEFINED__
typedef interface IMediaPropertyBag IMediaPropertyBag;
#endif 	/* __IMediaPropertyBag_FWD_DEFINED__ */


#ifndef __IPersistMediaPropertyBag_FWD_DEFINED__
#define __IPersistMediaPropertyBag_FWD_DEFINED__
typedef interface IPersistMediaPropertyBag IPersistMediaPropertyBag;
#endif 	/* __IPersistMediaPropertyBag_FWD_DEFINED__ */


#ifndef __IAMPhysicalPinInfo_FWD_DEFINED__
#define __IAMPhysicalPinInfo_FWD_DEFINED__
typedef interface IAMPhysicalPinInfo IAMPhysicalPinInfo;
#endif 	/* __IAMPhysicalPinInfo_FWD_DEFINED__ */


#ifndef __IAMExtDevice_FWD_DEFINED__
#define __IAMExtDevice_FWD_DEFINED__
typedef interface IAMExtDevice IAMExtDevice;
#endif 	/* __IAMExtDevice_FWD_DEFINED__ */


#ifndef __IAMExtTransport_FWD_DEFINED__
#define __IAMExtTransport_FWD_DEFINED__
typedef interface IAMExtTransport IAMExtTransport;
#endif 	/* __IAMExtTransport_FWD_DEFINED__ */


#ifndef __IAMTimecodeReader_FWD_DEFINED__
#define __IAMTimecodeReader_FWD_DEFINED__
typedef interface IAMTimecodeReader IAMTimecodeReader;
#endif 	/* __IAMTimecodeReader_FWD_DEFINED__ */


#ifndef __IAMTimecodeGenerator_FWD_DEFINED__
#define __IAMTimecodeGenerator_FWD_DEFINED__
typedef interface IAMTimecodeGenerator IAMTimecodeGenerator;
#endif 	/* __IAMTimecodeGenerator_FWD_DEFINED__ */


#ifndef __IAMTimecodeDisplay_FWD_DEFINED__
#define __IAMTimecodeDisplay_FWD_DEFINED__
typedef interface IAMTimecodeDisplay IAMTimecodeDisplay;
#endif 	/* __IAMTimecodeDisplay_FWD_DEFINED__ */


#ifndef __IAMDevMemoryAllocator_FWD_DEFINED__
#define __IAMDevMemoryAllocator_FWD_DEFINED__
typedef interface IAMDevMemoryAllocator IAMDevMemoryAllocator;
#endif 	/* __IAMDevMemoryAllocator_FWD_DEFINED__ */


#ifndef __IAMDevMemoryControl_FWD_DEFINED__
#define __IAMDevMemoryControl_FWD_DEFINED__
typedef interface IAMDevMemoryControl IAMDevMemoryControl;
#endif 	/* __IAMDevMemoryControl_FWD_DEFINED__ */


#ifndef __IAMStreamSelect_FWD_DEFINED__
#define __IAMStreamSelect_FWD_DEFINED__
typedef interface IAMStreamSelect IAMStreamSelect;
#endif 	/* __IAMStreamSelect_FWD_DEFINED__ */


#ifndef __IAMResourceControl_FWD_DEFINED__
#define __IAMResourceControl_FWD_DEFINED__
typedef interface IAMResourceControl IAMResourceControl;
#endif 	/* __IAMResourceControl_FWD_DEFINED__ */


#ifndef __IAMClockAdjust_FWD_DEFINED__
#define __IAMClockAdjust_FWD_DEFINED__
typedef interface IAMClockAdjust IAMClockAdjust;
#endif 	/* __IAMClockAdjust_FWD_DEFINED__ */


#ifndef __IAMFilterMiscFlags_FWD_DEFINED__
#define __IAMFilterMiscFlags_FWD_DEFINED__
typedef interface IAMFilterMiscFlags IAMFilterMiscFlags;
#endif 	/* __IAMFilterMiscFlags_FWD_DEFINED__ */


#ifndef __IDrawVideoImage_FWD_DEFINED__
#define __IDrawVideoImage_FWD_DEFINED__
typedef interface IDrawVideoImage IDrawVideoImage;
#endif 	/* __IDrawVideoImage_FWD_DEFINED__ */


#ifndef __IDecimateVideoImage_FWD_DEFINED__
#define __IDecimateVideoImage_FWD_DEFINED__
typedef interface IDecimateVideoImage IDecimateVideoImage;
#endif 	/* __IDecimateVideoImage_FWD_DEFINED__ */


#ifndef __IAMVideoDecimationProperties_FWD_DEFINED__
#define __IAMVideoDecimationProperties_FWD_DEFINED__
typedef interface IAMVideoDecimationProperties IAMVideoDecimationProperties;
#endif 	/* __IAMVideoDecimationProperties_FWD_DEFINED__ */


#ifndef __IVideoFrameStep_FWD_DEFINED__
#define __IVideoFrameStep_FWD_DEFINED__
typedef interface IVideoFrameStep IVideoFrameStep;
#endif 	/* __IVideoFrameStep_FWD_DEFINED__ */


#ifndef __IAMLatency_FWD_DEFINED__
#define __IAMLatency_FWD_DEFINED__
typedef interface IAMLatency IAMLatency;
#endif 	/* __IAMLatency_FWD_DEFINED__ */


#ifndef __IAMPushSource_FWD_DEFINED__
#define __IAMPushSource_FWD_DEFINED__
typedef interface IAMPushSource IAMPushSource;
#endif 	/* __IAMPushSource_FWD_DEFINED__ */


#ifndef __IAMDeviceRemoval_FWD_DEFINED__
#define __IAMDeviceRemoval_FWD_DEFINED__
typedef interface IAMDeviceRemoval IAMDeviceRemoval;
#endif 	/* __IAMDeviceRemoval_FWD_DEFINED__ */


#ifndef __IDVEnc_FWD_DEFINED__
#define __IDVEnc_FWD_DEFINED__
typedef interface IDVEnc IDVEnc;
#endif 	/* __IDVEnc_FWD_DEFINED__ */


#ifndef __IIPDVDec_FWD_DEFINED__
#define __IIPDVDec_FWD_DEFINED__
typedef interface IIPDVDec IIPDVDec;
#endif 	/* __IIPDVDec_FWD_DEFINED__ */


#ifndef __IDVRGB219_FWD_DEFINED__
#define __IDVRGB219_FWD_DEFINED__
typedef interface IDVRGB219 IDVRGB219;
#endif 	/* __IDVRGB219_FWD_DEFINED__ */


#ifndef __IDVSplitter_FWD_DEFINED__
#define __IDVSplitter_FWD_DEFINED__
typedef interface IDVSplitter IDVSplitter;
#endif 	/* __IDVSplitter_FWD_DEFINED__ */


#ifndef __IAMAudioRendererStats_FWD_DEFINED__
#define __IAMAudioRendererStats_FWD_DEFINED__
typedef interface IAMAudioRendererStats IAMAudioRendererStats;
#endif 	/* __IAMAudioRendererStats_FWD_DEFINED__ */


#ifndef __IAMGraphStreams_FWD_DEFINED__
#define __IAMGraphStreams_FWD_DEFINED__
typedef interface IAMGraphStreams IAMGraphStreams;
#endif 	/* __IAMGraphStreams_FWD_DEFINED__ */


#ifndef __IAMOverlayFX_FWD_DEFINED__
#define __IAMOverlayFX_FWD_DEFINED__
typedef interface IAMOverlayFX IAMOverlayFX;
#endif 	/* __IAMOverlayFX_FWD_DEFINED__ */


#ifndef __IAMOpenProgress_FWD_DEFINED__
#define __IAMOpenProgress_FWD_DEFINED__
typedef interface IAMOpenProgress IAMOpenProgress;
#endif 	/* __IAMOpenProgress_FWD_DEFINED__ */


#ifndef __IMpeg2Demultiplexer_FWD_DEFINED__
#define __IMpeg2Demultiplexer_FWD_DEFINED__
typedef interface IMpeg2Demultiplexer IMpeg2Demultiplexer;
#endif 	/* __IMpeg2Demultiplexer_FWD_DEFINED__ */


#ifndef __IEnumStreamIdMap_FWD_DEFINED__
#define __IEnumStreamIdMap_FWD_DEFINED__
typedef interface IEnumStreamIdMap IEnumStreamIdMap;
#endif 	/* __IEnumStreamIdMap_FWD_DEFINED__ */


#ifndef __IMPEG2StreamIdMap_FWD_DEFINED__
#define __IMPEG2StreamIdMap_FWD_DEFINED__
typedef interface IMPEG2StreamIdMap IMPEG2StreamIdMap;
#endif 	/* __IMPEG2StreamIdMap_FWD_DEFINED__ */


#ifndef __IRegisterServiceProvider_FWD_DEFINED__
#define __IRegisterServiceProvider_FWD_DEFINED__
typedef interface IRegisterServiceProvider IRegisterServiceProvider;
#endif 	/* __IRegisterServiceProvider_FWD_DEFINED__ */


#ifndef __IAMClockSlave_FWD_DEFINED__
#define __IAMClockSlave_FWD_DEFINED__
typedef interface IAMClockSlave IAMClockSlave;
#endif 	/* __IAMClockSlave_FWD_DEFINED__ */


#ifndef __IAMGraphBuilderCallback_FWD_DEFINED__
#define __IAMGraphBuilderCallback_FWD_DEFINED__
typedef interface IAMGraphBuilderCallback IAMGraphBuilderCallback;
#endif 	/* __IAMGraphBuilderCallback_FWD_DEFINED__ */


#ifndef __ICodecAPI_FWD_DEFINED__
#define __ICodecAPI_FWD_DEFINED__
typedef interface ICodecAPI ICodecAPI;
#endif 	/* __ICodecAPI_FWD_DEFINED__ */


#ifndef __IGetCapabilitiesKey_FWD_DEFINED__
#define __IGetCapabilitiesKey_FWD_DEFINED__
typedef interface IGetCapabilitiesKey IGetCapabilitiesKey;
#endif 	/* __IGetCapabilitiesKey_FWD_DEFINED__ */


#ifndef __IEncoderAPI_FWD_DEFINED__
#define __IEncoderAPI_FWD_DEFINED__
typedef interface IEncoderAPI IEncoderAPI;
#endif 	/* __IEncoderAPI_FWD_DEFINED__ */


#ifndef __IVideoEncoder_FWD_DEFINED__
#define __IVideoEncoder_FWD_DEFINED__
typedef interface IVideoEncoder IVideoEncoder;
#endif 	/* __IVideoEncoder_FWD_DEFINED__ */


#ifndef __IAMDecoderCaps_FWD_DEFINED__
#define __IAMDecoderCaps_FWD_DEFINED__
typedef interface IAMDecoderCaps IAMDecoderCaps;
#endif 	/* __IAMDecoderCaps_FWD_DEFINED__ */


#ifndef __IDvdControl_FWD_DEFINED__
#define __IDvdControl_FWD_DEFINED__
typedef interface IDvdControl IDvdControl;
#endif 	/* __IDvdControl_FWD_DEFINED__ */


#ifndef __IDvdInfo_FWD_DEFINED__
#define __IDvdInfo_FWD_DEFINED__
typedef interface IDvdInfo IDvdInfo;
#endif 	/* __IDvdInfo_FWD_DEFINED__ */


#ifndef __IDvdCmd_FWD_DEFINED__
#define __IDvdCmd_FWD_DEFINED__
typedef interface IDvdCmd IDvdCmd;
#endif 	/* __IDvdCmd_FWD_DEFINED__ */


#ifndef __IDvdState_FWD_DEFINED__
#define __IDvdState_FWD_DEFINED__
typedef interface IDvdState IDvdState;
#endif 	/* __IDvdState_FWD_DEFINED__ */


#ifndef __IDvdControl2_FWD_DEFINED__
#define __IDvdControl2_FWD_DEFINED__
typedef interface IDvdControl2 IDvdControl2;
#endif 	/* __IDvdControl2_FWD_DEFINED__ */


#ifndef __IDvdInfo2_FWD_DEFINED__
#define __IDvdInfo2_FWD_DEFINED__
typedef interface IDvdInfo2 IDvdInfo2;
#endif 	/* __IDvdInfo2_FWD_DEFINED__ */


#ifndef __IDvdGraphBuilder_FWD_DEFINED__
#define __IDvdGraphBuilder_FWD_DEFINED__
typedef interface IDvdGraphBuilder IDvdGraphBuilder;
#endif 	/* __IDvdGraphBuilder_FWD_DEFINED__ */


#ifndef __IDDrawExclModeVideo_FWD_DEFINED__
#define __IDDrawExclModeVideo_FWD_DEFINED__
typedef interface IDDrawExclModeVideo IDDrawExclModeVideo;
#endif 	/* __IDDrawExclModeVideo_FWD_DEFINED__ */


#ifndef __IDDrawExclModeVideoCallback_FWD_DEFINED__
#define __IDDrawExclModeVideoCallback_FWD_DEFINED__
typedef interface IDDrawExclModeVideoCallback IDDrawExclModeVideoCallback;
#endif 	/* __IDDrawExclModeVideoCallback_FWD_DEFINED__ */


#ifndef __IPinConnection_FWD_DEFINED__
#define __IPinConnection_FWD_DEFINED__
typedef interface IPinConnection IPinConnection;
#endif 	/* __IPinConnection_FWD_DEFINED__ */


#ifndef __IPinFlowControl_FWD_DEFINED__
#define __IPinFlowControl_FWD_DEFINED__
typedef interface IPinFlowControl IPinFlowControl;
#endif 	/* __IPinFlowControl_FWD_DEFINED__ */


#ifndef __IGraphConfig_FWD_DEFINED__
#define __IGraphConfig_FWD_DEFINED__
typedef interface IGraphConfig IGraphConfig;
#endif 	/* __IGraphConfig_FWD_DEFINED__ */


#ifndef __IGraphConfigCallback_FWD_DEFINED__
#define __IGraphConfigCallback_FWD_DEFINED__
typedef interface IGraphConfigCallback IGraphConfigCallback;
#endif 	/* __IGraphConfigCallback_FWD_DEFINED__ */


#ifndef __IFilterChain_FWD_DEFINED__
#define __IFilterChain_FWD_DEFINED__
typedef interface IFilterChain IFilterChain;
#endif 	/* __IFilterChain_FWD_DEFINED__ */


#ifndef __IVMRImagePresenter_FWD_DEFINED__
#define __IVMRImagePresenter_FWD_DEFINED__
typedef interface IVMRImagePresenter IVMRImagePresenter;
#endif 	/* __IVMRImagePresenter_FWD_DEFINED__ */


#ifndef __IVMRSurfaceAllocator_FWD_DEFINED__
#define __IVMRSurfaceAllocator_FWD_DEFINED__
typedef interface IVMRSurfaceAllocator IVMRSurfaceAllocator;
#endif 	/* __IVMRSurfaceAllocator_FWD_DEFINED__ */


#ifndef __IVMRSurfaceAllocatorNotify_FWD_DEFINED__
#define __IVMRSurfaceAllocatorNotify_FWD_DEFINED__
typedef interface IVMRSurfaceAllocatorNotify IVMRSurfaceAllocatorNotify;
#endif 	/* __IVMRSurfaceAllocatorNotify_FWD_DEFINED__ */


#ifndef __IVMRWindowlessControl_FWD_DEFINED__
#define __IVMRWindowlessControl_FWD_DEFINED__
typedef interface IVMRWindowlessControl IVMRWindowlessControl;
#endif 	/* __IVMRWindowlessControl_FWD_DEFINED__ */


#ifndef __IVMRMixerControl_FWD_DEFINED__
#define __IVMRMixerControl_FWD_DEFINED__
typedef interface IVMRMixerControl IVMRMixerControl;
#endif 	/* __IVMRMixerControl_FWD_DEFINED__ */


#ifndef __IVMRMonitorConfig_FWD_DEFINED__
#define __IVMRMonitorConfig_FWD_DEFINED__
typedef interface IVMRMonitorConfig IVMRMonitorConfig;
#endif 	/* __IVMRMonitorConfig_FWD_DEFINED__ */


#ifndef __IVMRFilterConfig_FWD_DEFINED__
#define __IVMRFilterConfig_FWD_DEFINED__
typedef interface IVMRFilterConfig IVMRFilterConfig;
#endif 	/* __IVMRFilterConfig_FWD_DEFINED__ */


#ifndef __IVMRAspectRatioControl_FWD_DEFINED__
#define __IVMRAspectRatioControl_FWD_DEFINED__
typedef interface IVMRAspectRatioControl IVMRAspectRatioControl;
#endif 	/* __IVMRAspectRatioControl_FWD_DEFINED__ */


#ifndef __IVMRDeinterlaceControl_FWD_DEFINED__
#define __IVMRDeinterlaceControl_FWD_DEFINED__
typedef interface IVMRDeinterlaceControl IVMRDeinterlaceControl;
#endif 	/* __IVMRDeinterlaceControl_FWD_DEFINED__ */


#ifndef __IVMRMixerBitmap_FWD_DEFINED__
#define __IVMRMixerBitmap_FWD_DEFINED__
typedef interface IVMRMixerBitmap IVMRMixerBitmap;
#endif 	/* __IVMRMixerBitmap_FWD_DEFINED__ */


#ifndef __IVMRImageCompositor_FWD_DEFINED__
#define __IVMRImageCompositor_FWD_DEFINED__
typedef interface IVMRImageCompositor IVMRImageCompositor;
#endif 	/* __IVMRImageCompositor_FWD_DEFINED__ */


#ifndef __IVMRVideoStreamControl_FWD_DEFINED__
#define __IVMRVideoStreamControl_FWD_DEFINED__
typedef interface IVMRVideoStreamControl IVMRVideoStreamControl;
#endif 	/* __IVMRVideoStreamControl_FWD_DEFINED__ */


#ifndef __IVMRSurface_FWD_DEFINED__
#define __IVMRSurface_FWD_DEFINED__
typedef interface IVMRSurface IVMRSurface;
#endif 	/* __IVMRSurface_FWD_DEFINED__ */


#ifndef __IVMRImagePresenterConfig_FWD_DEFINED__
#define __IVMRImagePresenterConfig_FWD_DEFINED__
typedef interface IVMRImagePresenterConfig IVMRImagePresenterConfig;
#endif 	/* __IVMRImagePresenterConfig_FWD_DEFINED__ */


#ifndef __IVMRImagePresenterExclModeConfig_FWD_DEFINED__
#define __IVMRImagePresenterExclModeConfig_FWD_DEFINED__
typedef interface IVMRImagePresenterExclModeConfig IVMRImagePresenterExclModeConfig;
#endif 	/* __IVMRImagePresenterExclModeConfig_FWD_DEFINED__ */


#ifndef __IVPManager_FWD_DEFINED__
#define __IVPManager_FWD_DEFINED__
typedef interface IVPManager IVPManager;
#endif 	/* __IVPManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_strmif_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Copyright (C) Microsoft Corporation, 1999-2002.
//
//--------------------------------------------------------------------------
// Disable /W4 compiler warning C4201: nameless struct/union
#pragma warning(push)
#pragma warning(disable:4201)  // Disable C4201: nameless struct/union
  
#define CDEF_CLASS_DEFAULT      0x0001
#define CDEF_BYPASS_CLASS_MANAGER   0x0002
#define CDEF_MERIT_ABOVE_DO_NOT_USE  0x0008
#define CDEF_DEVMON_CMGR_DEVICE  0x0010
#define CDEF_DEVMON_DMO  0x0020
#define CDEF_DEVMON_PNP_DEVICE  0x0040
#define CDEF_DEVMON_FILTER  0x0080
#define CDEF_DEVMON_SELECTIVE_MASK  0x00f0


extern RPC_IF_HANDLE __MIDL_itf_strmif_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0000_v0_0_s_ifspec;

#ifndef __ICreateDevEnum_INTERFACE_DEFINED__
#define __ICreateDevEnum_INTERFACE_DEFINED__

/* interface ICreateDevEnum */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICreateDevEnum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29840822-5B84-11D0-BD3B-00A0C911CE86")
    ICreateDevEnum : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateClassEnumerator( 
            /* [in] */ REFCLSID clsidDeviceClass,
            /* [out] */ IEnumMoniker **ppEnumMoniker,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateDevEnumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICreateDevEnum * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICreateDevEnum * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICreateDevEnum * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateClassEnumerator )( 
            ICreateDevEnum * This,
            /* [in] */ REFCLSID clsidDeviceClass,
            /* [out] */ IEnumMoniker **ppEnumMoniker,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } ICreateDevEnumVtbl;

    interface ICreateDevEnum
    {
        CONST_VTBL struct ICreateDevEnumVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateDevEnum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateDevEnum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateDevEnum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateDevEnum_CreateClassEnumerator(This,clsidDeviceClass,ppEnumMoniker,dwFlags)	\
    (This)->lpVtbl -> CreateClassEnumerator(This,clsidDeviceClass,ppEnumMoniker,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICreateDevEnum_CreateClassEnumerator_Proxy( 
    ICreateDevEnum * This,
    /* [in] */ REFCLSID clsidDeviceClass,
    /* [out] */ IEnumMoniker **ppEnumMoniker,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ICreateDevEnum_CreateClassEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICreateDevEnum_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0113 */
/* [local] */ 

#define CHARS_IN_GUID     39
typedef struct _AMMediaType
    {
    GUID majortype;
    GUID subtype;
    BOOL bFixedSizeSamples;
    BOOL bTemporalCompression;
    ULONG lSampleSize;
    GUID formattype;
    IUnknown *pUnk;
    ULONG cbFormat;
    /* [size_is] */ BYTE *pbFormat;
    } 	AM_MEDIA_TYPE;

typedef 
enum _PinDirection
    {	PINDIR_INPUT	= 0,
	PINDIR_OUTPUT	= PINDIR_INPUT + 1
    } 	PIN_DIRECTION;

#define MAX_PIN_NAME     128
#define MAX_FILTER_NAME  128
typedef LONGLONG REFERENCE_TIME;

typedef double REFTIME;

typedef DWORD_PTR HSEMAPHORE;

typedef DWORD_PTR HEVENT;

typedef struct _AllocatorProperties
    {
    long cBuffers;
    long cbBuffer;
    long cbAlign;
    long cbPrefix;
    } 	ALLOCATOR_PROPERTIES;

















extern RPC_IF_HANDLE __MIDL_itf_strmif_0113_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0113_v0_0_s_ifspec;

#ifndef __IPin_INTERFACE_DEFINED__
#define __IPin_INTERFACE_DEFINED__

/* interface IPin */
/* [unique][uuid][object] */ 

typedef struct _PinInfo
    {
    IBaseFilter *pFilter;
    PIN_DIRECTION dir;
    WCHAR achName[ 128 ];
    } 	PIN_INFO;


EXTERN_C const IID IID_IPin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86891-0ad4-11ce-b03a-0020af0ba770")
    IPin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ IPin *pReceivePin,
            /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveConnection( 
            /* [in] */ IPin *pConnector,
            /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectedTo( 
            /* [out] */ IPin **pPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectionMediaType( 
            /* [out] */ AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryPinInfo( 
            /* [out] */ PIN_INFO *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryDirection( 
            /* [out] */ PIN_DIRECTION *pPinDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryId( 
            /* [out] */ LPWSTR *Id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryAccept( 
            /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMediaTypes( 
            /* [out] */ IEnumMediaTypes **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryInternalConnections( 
            /* [out] */ IPin **apPin,
            /* [out][in] */ ULONG *nPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndOfStream( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NewSegment( 
            /* [in] */ REFERENCE_TIME tStart,
            /* [in] */ REFERENCE_TIME tStop,
            /* [in] */ double dRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IPin * This,
            /* [in] */ IPin *pReceivePin,
            /* [in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *ReceiveConnection )( 
            IPin * This,
            /* [in] */ IPin *pConnector,
            /* [in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *ConnectedTo )( 
            IPin * This,
            /* [out] */ IPin **pPin);
        
        HRESULT ( STDMETHODCALLTYPE *ConnectionMediaType )( 
            IPin * This,
            /* [out] */ AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *QueryPinInfo )( 
            IPin * This,
            /* [out] */ PIN_INFO *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE *QueryDirection )( 
            IPin * This,
            /* [out] */ PIN_DIRECTION *pPinDir);
        
        HRESULT ( STDMETHODCALLTYPE *QueryId )( 
            IPin * This,
            /* [out] */ LPWSTR *Id);
        
        HRESULT ( STDMETHODCALLTYPE *QueryAccept )( 
            IPin * This,
            /* [in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMediaTypes )( 
            IPin * This,
            /* [out] */ IEnumMediaTypes **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *QueryInternalConnections )( 
            IPin * This,
            /* [out] */ IPin **apPin,
            /* [out][in] */ ULONG *nPin);
        
        HRESULT ( STDMETHODCALLTYPE *EndOfStream )( 
            IPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *BeginFlush )( 
            IPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *EndFlush )( 
            IPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *NewSegment )( 
            IPin * This,
            /* [in] */ REFERENCE_TIME tStart,
            /* [in] */ REFERENCE_TIME tStop,
            /* [in] */ double dRate);
        
        END_INTERFACE
    } IPinVtbl;

    interface IPin
    {
        CONST_VTBL struct IPinVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPin_Connect(This,pReceivePin,pmt)	\
    (This)->lpVtbl -> Connect(This,pReceivePin,pmt)

#define IPin_ReceiveConnection(This,pConnector,pmt)	\
    (This)->lpVtbl -> ReceiveConnection(This,pConnector,pmt)

#define IPin_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IPin_ConnectedTo(This,pPin)	\
    (This)->lpVtbl -> ConnectedTo(This,pPin)

#define IPin_ConnectionMediaType(This,pmt)	\
    (This)->lpVtbl -> ConnectionMediaType(This,pmt)

#define IPin_QueryPinInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryPinInfo(This,pInfo)

#define IPin_QueryDirection(This,pPinDir)	\
    (This)->lpVtbl -> QueryDirection(This,pPinDir)

#define IPin_QueryId(This,Id)	\
    (This)->lpVtbl -> QueryId(This,Id)

#define IPin_QueryAccept(This,pmt)	\
    (This)->lpVtbl -> QueryAccept(This,pmt)

#define IPin_EnumMediaTypes(This,ppEnum)	\
    (This)->lpVtbl -> EnumMediaTypes(This,ppEnum)

#define IPin_QueryInternalConnections(This,apPin,nPin)	\
    (This)->lpVtbl -> QueryInternalConnections(This,apPin,nPin)

#define IPin_EndOfStream(This)	\
    (This)->lpVtbl -> EndOfStream(This)

#define IPin_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IPin_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IPin_NewSegment(This,tStart,tStop,dRate)	\
    (This)->lpVtbl -> NewSegment(This,tStart,tStop,dRate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPin_Connect_Proxy( 
    IPin * This,
    /* [in] */ IPin *pReceivePin,
    /* [in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IPin_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ReceiveConnection_Proxy( 
    IPin * This,
    /* [in] */ IPin *pConnector,
    /* [in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IPin_ReceiveConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_Disconnect_Proxy( 
    IPin * This);


void __RPC_STUB IPin_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ConnectedTo_Proxy( 
    IPin * This,
    /* [out] */ IPin **pPin);


void __RPC_STUB IPin_ConnectedTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ConnectionMediaType_Proxy( 
    IPin * This,
    /* [out] */ AM_MEDIA_TYPE *pmt);


void __RPC_STUB IPin_ConnectionMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryPinInfo_Proxy( 
    IPin * This,
    /* [out] */ PIN_INFO *pInfo);


void __RPC_STUB IPin_QueryPinInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryDirection_Proxy( 
    IPin * This,
    /* [out] */ PIN_DIRECTION *pPinDir);


void __RPC_STUB IPin_QueryDirection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryId_Proxy( 
    IPin * This,
    /* [out] */ LPWSTR *Id);


void __RPC_STUB IPin_QueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryAccept_Proxy( 
    IPin * This,
    /* [in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IPin_QueryAccept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EnumMediaTypes_Proxy( 
    IPin * This,
    /* [out] */ IEnumMediaTypes **ppEnum);


void __RPC_STUB IPin_EnumMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryInternalConnections_Proxy( 
    IPin * This,
    /* [out] */ IPin **apPin,
    /* [out][in] */ ULONG *nPin);


void __RPC_STUB IPin_QueryInternalConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EndOfStream_Proxy( 
    IPin * This);


void __RPC_STUB IPin_EndOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_BeginFlush_Proxy( 
    IPin * This);


void __RPC_STUB IPin_BeginFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EndFlush_Proxy( 
    IPin * This);


void __RPC_STUB IPin_EndFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_NewSegment_Proxy( 
    IPin * This,
    /* [in] */ REFERENCE_TIME tStart,
    /* [in] */ REFERENCE_TIME tStop,
    /* [in] */ double dRate);


void __RPC_STUB IPin_NewSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPin_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0114 */
/* [local] */ 

typedef IPin *PPIN;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0114_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0114_v0_0_s_ifspec;

#ifndef __IEnumPins_INTERFACE_DEFINED__
#define __IEnumPins_INTERFACE_DEFINED__

/* interface IEnumPins */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumPins;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86892-0ad4-11ce-b03a-0020af0ba770")
    IEnumPins : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cPins,
            /* [size_is][out] */ IPin **ppPins,
            /* [out] */ ULONG *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cPins) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPins **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumPinsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPins * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPins * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPins * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPins * This,
            /* [in] */ ULONG cPins,
            /* [size_is][out] */ IPin **ppPins,
            /* [out] */ ULONG *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPins * This,
            /* [in] */ ULONG cPins);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPins * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPins * This,
            /* [out] */ IEnumPins **ppEnum);
        
        END_INTERFACE
    } IEnumPinsVtbl;

    interface IEnumPins
    {
        CONST_VTBL struct IEnumPinsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPins_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumPins_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumPins_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumPins_Next(This,cPins,ppPins,pcFetched)	\
    (This)->lpVtbl -> Next(This,cPins,ppPins,pcFetched)

#define IEnumPins_Skip(This,cPins)	\
    (This)->lpVtbl -> Skip(This,cPins)

#define IEnumPins_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumPins_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumPins_Next_Proxy( 
    IEnumPins * This,
    /* [in] */ ULONG cPins,
    /* [size_is][out] */ IPin **ppPins,
    /* [out] */ ULONG *pcFetched);


void __RPC_STUB IEnumPins_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Skip_Proxy( 
    IEnumPins * This,
    /* [in] */ ULONG cPins);


void __RPC_STUB IEnumPins_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Reset_Proxy( 
    IEnumPins * This);


void __RPC_STUB IEnumPins_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Clone_Proxy( 
    IEnumPins * This,
    /* [out] */ IEnumPins **ppEnum);


void __RPC_STUB IEnumPins_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumPins_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0115 */
/* [local] */ 

typedef IEnumPins *PENUMPINS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0115_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0115_v0_0_s_ifspec;

#ifndef __IEnumMediaTypes_INTERFACE_DEFINED__
#define __IEnumMediaTypes_INTERFACE_DEFINED__

/* interface IEnumMediaTypes */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumMediaTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89c31040-846b-11ce-97d3-00aa0055595a")
    IEnumMediaTypes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cMediaTypes,
            /* [size_is][out] */ AM_MEDIA_TYPE **ppMediaTypes,
            /* [out] */ ULONG *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cMediaTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMediaTypes **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMediaTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumMediaTypes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumMediaTypes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumMediaTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumMediaTypes * This,
            /* [in] */ ULONG cMediaTypes,
            /* [size_is][out] */ AM_MEDIA_TYPE **ppMediaTypes,
            /* [out] */ ULONG *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumMediaTypes * This,
            /* [in] */ ULONG cMediaTypes);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumMediaTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumMediaTypes * This,
            /* [out] */ IEnumMediaTypes **ppEnum);
        
        END_INTERFACE
    } IEnumMediaTypesVtbl;

    interface IEnumMediaTypes
    {
        CONST_VTBL struct IEnumMediaTypesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMediaTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMediaTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMediaTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMediaTypes_Next(This,cMediaTypes,ppMediaTypes,pcFetched)	\
    (This)->lpVtbl -> Next(This,cMediaTypes,ppMediaTypes,pcFetched)

#define IEnumMediaTypes_Skip(This,cMediaTypes)	\
    (This)->lpVtbl -> Skip(This,cMediaTypes)

#define IEnumMediaTypes_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMediaTypes_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Next_Proxy( 
    IEnumMediaTypes * This,
    /* [in] */ ULONG cMediaTypes,
    /* [size_is][out] */ AM_MEDIA_TYPE **ppMediaTypes,
    /* [out] */ ULONG *pcFetched);


void __RPC_STUB IEnumMediaTypes_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Skip_Proxy( 
    IEnumMediaTypes * This,
    /* [in] */ ULONG cMediaTypes);


void __RPC_STUB IEnumMediaTypes_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Reset_Proxy( 
    IEnumMediaTypes * This);


void __RPC_STUB IEnumMediaTypes_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Clone_Proxy( 
    IEnumMediaTypes * This,
    /* [out] */ IEnumMediaTypes **ppEnum);


void __RPC_STUB IEnumMediaTypes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMediaTypes_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0116 */
/* [local] */ 

typedef IEnumMediaTypes *PENUMMEDIATYPES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0116_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0116_v0_0_s_ifspec;

#ifndef __IFilterGraph_INTERFACE_DEFINED__
#define __IFilterGraph_INTERFACE_DEFINED__

/* interface IFilterGraph */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFilterGraph;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a8689f-0ad4-11ce-b03a-0020af0ba770")
    IFilterGraph : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddFilter( 
            /* [in] */ IBaseFilter *pFilter,
            /* [string][in] */ LPCWSTR pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveFilter( 
            /* [in] */ IBaseFilter *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumFilters( 
            /* [out] */ IEnumFilters **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindFilterByName( 
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter **ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectDirect( 
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reconnect( 
            /* [in] */ IPin *ppin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [in] */ IPin *ppin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultSyncSource( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterGraph * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterGraph * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterGraph * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddFilter )( 
            IFilterGraph * This,
            /* [in] */ IBaseFilter *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveFilter )( 
            IFilterGraph * This,
            /* [in] */ IBaseFilter *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *EnumFilters )( 
            IFilterGraph * This,
            /* [out] */ IEnumFilters **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *FindFilterByName )( 
            IFilterGraph * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *ConnectDirect )( 
            IFilterGraph * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *Reconnect )( 
            IFilterGraph * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IFilterGraph * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultSyncSource )( 
            IFilterGraph * This);
        
        END_INTERFACE
    } IFilterGraphVtbl;

    interface IFilterGraph
    {
        CONST_VTBL struct IFilterGraphVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterGraph_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterGraph_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterGraph_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterGraph_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IFilterGraph_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IFilterGraph_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IFilterGraph_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IFilterGraph_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IFilterGraph_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IFilterGraph_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IFilterGraph_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterGraph_AddFilter_Proxy( 
    IFilterGraph * This,
    /* [in] */ IBaseFilter *pFilter,
    /* [string][in] */ LPCWSTR pName);


void __RPC_STUB IFilterGraph_AddFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_RemoveFilter_Proxy( 
    IFilterGraph * This,
    /* [in] */ IBaseFilter *pFilter);


void __RPC_STUB IFilterGraph_RemoveFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_EnumFilters_Proxy( 
    IFilterGraph * This,
    /* [out] */ IEnumFilters **ppEnum);


void __RPC_STUB IFilterGraph_EnumFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_FindFilterByName_Proxy( 
    IFilterGraph * This,
    /* [string][in] */ LPCWSTR pName,
    /* [out] */ IBaseFilter **ppFilter);


void __RPC_STUB IFilterGraph_FindFilterByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_ConnectDirect_Proxy( 
    IFilterGraph * This,
    /* [in] */ IPin *ppinOut,
    /* [in] */ IPin *ppinIn,
    /* [unique][in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFilterGraph_ConnectDirect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_Reconnect_Proxy( 
    IFilterGraph * This,
    /* [in] */ IPin *ppin);


void __RPC_STUB IFilterGraph_Reconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_Disconnect_Proxy( 
    IFilterGraph * This,
    /* [in] */ IPin *ppin);


void __RPC_STUB IFilterGraph_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_SetDefaultSyncSource_Proxy( 
    IFilterGraph * This);


void __RPC_STUB IFilterGraph_SetDefaultSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterGraph_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0117 */
/* [local] */ 

typedef IFilterGraph *PFILTERGRAPH;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0117_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0117_v0_0_s_ifspec;

#ifndef __IEnumFilters_INTERFACE_DEFINED__
#define __IEnumFilters_INTERFACE_DEFINED__

/* interface IEnumFilters */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86893-0ad4-11ce-b03a-0020af0ba770")
    IEnumFilters : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cFilters,
            /* [out] */ IBaseFilter **ppFilter,
            /* [out] */ ULONG *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cFilters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumFilters **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumFilters * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumFilters * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumFilters * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumFilters * This,
            /* [in] */ ULONG cFilters,
            /* [out] */ IBaseFilter **ppFilter,
            /* [out] */ ULONG *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumFilters * This,
            /* [in] */ ULONG cFilters);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumFilters * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumFilters * This,
            /* [out] */ IEnumFilters **ppEnum);
        
        END_INTERFACE
    } IEnumFiltersVtbl;

    interface IEnumFilters
    {
        CONST_VTBL struct IEnumFiltersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumFilters_Next(This,cFilters,ppFilter,pcFetched)	\
    (This)->lpVtbl -> Next(This,cFilters,ppFilter,pcFetched)

#define IEnumFilters_Skip(This,cFilters)	\
    (This)->lpVtbl -> Skip(This,cFilters)

#define IEnumFilters_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumFilters_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumFilters_Next_Proxy( 
    IEnumFilters * This,
    /* [in] */ ULONG cFilters,
    /* [out] */ IBaseFilter **ppFilter,
    /* [out] */ ULONG *pcFetched);


void __RPC_STUB IEnumFilters_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Skip_Proxy( 
    IEnumFilters * This,
    /* [in] */ ULONG cFilters);


void __RPC_STUB IEnumFilters_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Reset_Proxy( 
    IEnumFilters * This);


void __RPC_STUB IEnumFilters_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Clone_Proxy( 
    IEnumFilters * This,
    /* [out] */ IEnumFilters **ppEnum);


void __RPC_STUB IEnumFilters_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumFilters_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0118 */
/* [local] */ 

typedef IEnumFilters *PENUMFILTERS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0118_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0118_v0_0_s_ifspec;

#ifndef __IMediaFilter_INTERFACE_DEFINED__
#define __IMediaFilter_INTERFACE_DEFINED__

/* interface IMediaFilter */
/* [unique][uuid][object] */ 

typedef 
enum _FilterState
    {	State_Stopped	= 0,
	State_Paused	= State_Stopped + 1,
	State_Running	= State_Paused + 1
    } 	FILTER_STATE;


EXTERN_C const IID IID_IMediaFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86899-0ad4-11ce-b03a-0020af0ba770")
    IMediaFilter : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( 
            REFERENCE_TIME tStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE *State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncSource( 
            /* [in] */ IReferenceClock *pClock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSyncSource( 
            /* [out] */ IReferenceClock **pClock) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IMediaFilter * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IMediaFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IMediaFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IMediaFilter * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IMediaFilter * This,
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE *State);
        
        HRESULT ( STDMETHODCALLTYPE *SetSyncSource )( 
            IMediaFilter * This,
            /* [in] */ IReferenceClock *pClock);
        
        HRESULT ( STDMETHODCALLTYPE *GetSyncSource )( 
            IMediaFilter * This,
            /* [out] */ IReferenceClock **pClock);
        
        END_INTERFACE
    } IMediaFilterVtbl;

    interface IMediaFilter
    {
        CONST_VTBL struct IMediaFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IMediaFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMediaFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMediaFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IMediaFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IMediaFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IMediaFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaFilter_Stop_Proxy( 
    IMediaFilter * This);


void __RPC_STUB IMediaFilter_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_Pause_Proxy( 
    IMediaFilter * This);


void __RPC_STUB IMediaFilter_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_Run_Proxy( 
    IMediaFilter * This,
    REFERENCE_TIME tStart);


void __RPC_STUB IMediaFilter_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_GetState_Proxy( 
    IMediaFilter * This,
    /* [in] */ DWORD dwMilliSecsTimeout,
    /* [out] */ FILTER_STATE *State);


void __RPC_STUB IMediaFilter_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_SetSyncSource_Proxy( 
    IMediaFilter * This,
    /* [in] */ IReferenceClock *pClock);


void __RPC_STUB IMediaFilter_SetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_GetSyncSource_Proxy( 
    IMediaFilter * This,
    /* [out] */ IReferenceClock **pClock);


void __RPC_STUB IMediaFilter_GetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0119 */
/* [local] */ 

typedef IMediaFilter *PMEDIAFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0119_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0119_v0_0_s_ifspec;

#ifndef __IBaseFilter_INTERFACE_DEFINED__
#define __IBaseFilter_INTERFACE_DEFINED__

/* interface IBaseFilter */
/* [unique][uuid][object] */ 

typedef struct _FilterInfo
    {
    WCHAR achName[ 128 ];
    IFilterGraph *pGraph;
    } 	FILTER_INFO;


EXTERN_C const IID IID_IBaseFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86895-0ad4-11ce-b03a-0020af0ba770")
    IBaseFilter : public IMediaFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumPins( 
            /* [out] */ IEnumPins **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindPin( 
            /* [string][in] */ LPCWSTR Id,
            /* [out] */ IPin **ppPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryFilterInfo( 
            /* [out] */ FILTER_INFO *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JoinFilterGraph( 
            /* [in] */ IFilterGraph *pGraph,
            /* [string][in] */ LPCWSTR pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryVendorInfo( 
            /* [string][out] */ LPWSTR *pVendorInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBaseFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBaseFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBaseFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBaseFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IBaseFilter * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IBaseFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IBaseFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IBaseFilter * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IBaseFilter * This,
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE *State);
        
        HRESULT ( STDMETHODCALLTYPE *SetSyncSource )( 
            IBaseFilter * This,
            /* [in] */ IReferenceClock *pClock);
        
        HRESULT ( STDMETHODCALLTYPE *GetSyncSource )( 
            IBaseFilter * This,
            /* [out] */ IReferenceClock **pClock);
        
        HRESULT ( STDMETHODCALLTYPE *EnumPins )( 
            IBaseFilter * This,
            /* [out] */ IEnumPins **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *FindPin )( 
            IBaseFilter * This,
            /* [string][in] */ LPCWSTR Id,
            /* [out] */ IPin **ppPin);
        
        HRESULT ( STDMETHODCALLTYPE *QueryFilterInfo )( 
            IBaseFilter * This,
            /* [out] */ FILTER_INFO *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE *JoinFilterGraph )( 
            IBaseFilter * This,
            /* [in] */ IFilterGraph *pGraph,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE *QueryVendorInfo )( 
            IBaseFilter * This,
            /* [string][out] */ LPWSTR *pVendorInfo);
        
        END_INTERFACE
    } IBaseFilterVtbl;

    interface IBaseFilter
    {
        CONST_VTBL struct IBaseFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBaseFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBaseFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBaseFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBaseFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IBaseFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IBaseFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IBaseFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IBaseFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IBaseFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IBaseFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)


#define IBaseFilter_EnumPins(This,ppEnum)	\
    (This)->lpVtbl -> EnumPins(This,ppEnum)

#define IBaseFilter_FindPin(This,Id,ppPin)	\
    (This)->lpVtbl -> FindPin(This,Id,ppPin)

#define IBaseFilter_QueryFilterInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryFilterInfo(This,pInfo)

#define IBaseFilter_JoinFilterGraph(This,pGraph,pName)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pGraph,pName)

#define IBaseFilter_QueryVendorInfo(This,pVendorInfo)	\
    (This)->lpVtbl -> QueryVendorInfo(This,pVendorInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBaseFilter_EnumPins_Proxy( 
    IBaseFilter * This,
    /* [out] */ IEnumPins **ppEnum);


void __RPC_STUB IBaseFilter_EnumPins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_FindPin_Proxy( 
    IBaseFilter * This,
    /* [string][in] */ LPCWSTR Id,
    /* [out] */ IPin **ppPin);


void __RPC_STUB IBaseFilter_FindPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_QueryFilterInfo_Proxy( 
    IBaseFilter * This,
    /* [out] */ FILTER_INFO *pInfo);


void __RPC_STUB IBaseFilter_QueryFilterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_JoinFilterGraph_Proxy( 
    IBaseFilter * This,
    /* [in] */ IFilterGraph *pGraph,
    /* [string][in] */ LPCWSTR pName);


void __RPC_STUB IBaseFilter_JoinFilterGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_QueryVendorInfo_Proxy( 
    IBaseFilter * This,
    /* [string][out] */ LPWSTR *pVendorInfo);


void __RPC_STUB IBaseFilter_QueryVendorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBaseFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0120 */
/* [local] */ 

typedef IBaseFilter *PFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0120_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0120_v0_0_s_ifspec;

#ifndef __IReferenceClock_INTERFACE_DEFINED__
#define __IReferenceClock_INTERFACE_DEFINED__

/* interface IReferenceClock */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IReferenceClock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a86897-0ad4-11ce-b03a-0020af0ba770")
    IReferenceClock : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ REFERENCE_TIME *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdviseTime( 
            /* [in] */ REFERENCE_TIME baseTime,
            /* [in] */ REFERENCE_TIME streamTime,
            /* [in] */ HEVENT hEvent,
            /* [out] */ DWORD_PTR *pdwAdviseCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdvisePeriodic( 
            /* [in] */ REFERENCE_TIME startTime,
            /* [in] */ REFERENCE_TIME periodTime,
            /* [in] */ HSEMAPHORE hSemaphore,
            /* [out] */ DWORD_PTR *pdwAdviseCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD_PTR dwAdviseCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReferenceClockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReferenceClock * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReferenceClock * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReferenceClock * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IReferenceClock * This,
            /* [out] */ REFERENCE_TIME *pTime);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseTime )( 
            IReferenceClock * This,
            /* [in] */ REFERENCE_TIME baseTime,
            /* [in] */ REFERENCE_TIME streamTime,
            /* [in] */ HEVENT hEvent,
            /* [out] */ DWORD_PTR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE *AdvisePeriodic )( 
            IReferenceClock * This,
            /* [in] */ REFERENCE_TIME startTime,
            /* [in] */ REFERENCE_TIME periodTime,
            /* [in] */ HSEMAPHORE hSemaphore,
            /* [out] */ DWORD_PTR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IReferenceClock * This,
            /* [in] */ DWORD_PTR dwAdviseCookie);
        
        END_INTERFACE
    } IReferenceClockVtbl;

    interface IReferenceClock
    {
        CONST_VTBL struct IReferenceClockVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReferenceClock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReferenceClock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReferenceClock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReferenceClock_GetTime(This,pTime)	\
    (This)->lpVtbl -> GetTime(This,pTime)

#define IReferenceClock_AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)

#define IReferenceClock_AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)

#define IReferenceClock_Unadvise(This,dwAdviseCookie)	\
    (This)->lpVtbl -> Unadvise(This,dwAdviseCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IReferenceClock_GetTime_Proxy( 
    IReferenceClock * This,
    /* [out] */ REFERENCE_TIME *pTime);


void __RPC_STUB IReferenceClock_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_AdviseTime_Proxy( 
    IReferenceClock * This,
    /* [in] */ REFERENCE_TIME baseTime,
    /* [in] */ REFERENCE_TIME streamTime,
    /* [in] */ HEVENT hEvent,
    /* [out] */ DWORD_PTR *pdwAdviseCookie);


void __RPC_STUB IReferenceClock_AdviseTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_AdvisePeriodic_Proxy( 
    IReferenceClock * This,
    /* [in] */ REFERENCE_TIME startTime,
    /* [in] */ REFERENCE_TIME periodTime,
    /* [in] */ HSEMAPHORE hSemaphore,
    /* [out] */ DWORD_PTR *pdwAdviseCookie);


void __RPC_STUB IReferenceClock_AdvisePeriodic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_Unadvise_Proxy( 
    IReferenceClock * This,
    /* [in] */ DWORD_PTR dwAdviseCookie);


void __RPC_STUB IReferenceClock_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReferenceClock_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0121 */
/* [local] */ 

typedef IReferenceClock *PREFERENCECLOCK;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0121_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0121_v0_0_s_ifspec;

#ifndef __IReferenceClock2_INTERFACE_DEFINED__
#define __IReferenceClock2_INTERFACE_DEFINED__

/* interface IReferenceClock2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IReferenceClock2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73885-c2c8-11cf-8b46-00805f6cef60")
    IReferenceClock2 : public IReferenceClock
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IReferenceClock2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReferenceClock2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReferenceClock2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReferenceClock2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IReferenceClock2 * This,
            /* [out] */ REFERENCE_TIME *pTime);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseTime )( 
            IReferenceClock2 * This,
            /* [in] */ REFERENCE_TIME baseTime,
            /* [in] */ REFERENCE_TIME streamTime,
            /* [in] */ HEVENT hEvent,
            /* [out] */ DWORD_PTR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE *AdvisePeriodic )( 
            IReferenceClock2 * This,
            /* [in] */ REFERENCE_TIME startTime,
            /* [in] */ REFERENCE_TIME periodTime,
            /* [in] */ HSEMAPHORE hSemaphore,
            /* [out] */ DWORD_PTR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IReferenceClock2 * This,
            /* [in] */ DWORD_PTR dwAdviseCookie);
        
        END_INTERFACE
    } IReferenceClock2Vtbl;

    interface IReferenceClock2
    {
        CONST_VTBL struct IReferenceClock2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReferenceClock2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReferenceClock2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReferenceClock2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReferenceClock2_GetTime(This,pTime)	\
    (This)->lpVtbl -> GetTime(This,pTime)

#define IReferenceClock2_AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)

#define IReferenceClock2_AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)

#define IReferenceClock2_Unadvise(This,dwAdviseCookie)	\
    (This)->lpVtbl -> Unadvise(This,dwAdviseCookie)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReferenceClock2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0122 */
/* [local] */ 

typedef IReferenceClock2 *PREFERENCECLOCK2;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0122_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0122_v0_0_s_ifspec;

#ifndef __IMediaSample_INTERFACE_DEFINED__
#define __IMediaSample_INTERFACE_DEFINED__

/* interface IMediaSample */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IMediaSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a8689a-0ad4-11ce-b03a-0020af0ba770")
    IMediaSample : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPointer( 
            /* [out] */ BYTE **ppBuffer) = 0;
        
        virtual long STDMETHODCALLTYPE GetSize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ REFERENCE_TIME *pTimeStart,
            /* [out] */ REFERENCE_TIME *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTime( 
            /* [in] */ REFERENCE_TIME *pTimeStart,
            /* [in] */ REFERENCE_TIME *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSyncPoint( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncPoint( 
            BOOL bIsSyncPoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsPreroll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPreroll( 
            BOOL bIsPreroll) = 0;
        
        virtual long STDMETHODCALLTYPE GetActualDataLength( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetActualDataLength( 
            long __MIDL_0010) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaType( 
            AM_MEDIA_TYPE **ppMediaType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaType( 
            AM_MEDIA_TYPE *pMediaType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsDiscontinuity( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDiscontinuity( 
            BOOL bDiscontinuity) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaTime( 
            /* [out] */ LONGLONG *pTimeStart,
            /* [out] */ LONGLONG *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaTime( 
            /* [in] */ LONGLONG *pTimeStart,
            /* [in] */ LONGLONG *pTimeEnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaSample * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaSample * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPointer )( 
            IMediaSample * This,
            /* [out] */ BYTE **ppBuffer);
        
        long ( STDMETHODCALLTYPE *GetSize )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IMediaSample * This,
            /* [out] */ REFERENCE_TIME *pTimeStart,
            /* [out] */ REFERENCE_TIME *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetTime )( 
            IMediaSample * This,
            /* [in] */ REFERENCE_TIME *pTimeStart,
            /* [in] */ REFERENCE_TIME *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *IsSyncPoint )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetSyncPoint )( 
            IMediaSample * This,
            BOOL bIsSyncPoint);
        
        HRESULT ( STDMETHODCALLTYPE *IsPreroll )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPreroll )( 
            IMediaSample * This,
            BOOL bIsPreroll);
        
        long ( STDMETHODCALLTYPE *GetActualDataLength )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetActualDataLength )( 
            IMediaSample * This,
            long __MIDL_0010);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaType )( 
            IMediaSample * This,
            AM_MEDIA_TYPE **ppMediaType);
        
        HRESULT ( STDMETHODCALLTYPE *SetMediaType )( 
            IMediaSample * This,
            AM_MEDIA_TYPE *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE *IsDiscontinuity )( 
            IMediaSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDiscontinuity )( 
            IMediaSample * This,
            BOOL bDiscontinuity);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaTime )( 
            IMediaSample * This,
            /* [out] */ LONGLONG *pTimeStart,
            /* [out] */ LONGLONG *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetMediaTime )( 
            IMediaSample * This,
            /* [in] */ LONGLONG *pTimeStart,
            /* [in] */ LONGLONG *pTimeEnd);
        
        END_INTERFACE
    } IMediaSampleVtbl;

    interface IMediaSample
    {
        CONST_VTBL struct IMediaSampleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSample_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IMediaSample_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IMediaSample_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IMediaSample_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IMediaSample_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IMediaSample_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IMediaSample_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IMediaSample_SetActualDataLength(This,__MIDL_0010)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0010)

#define IMediaSample_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IMediaSample_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IMediaSample_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IMediaSample_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IMediaSample_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSample_GetPointer_Proxy( 
    IMediaSample * This,
    /* [out] */ BYTE **ppBuffer);


void __RPC_STUB IMediaSample_GetPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IMediaSample_GetSize_Proxy( 
    IMediaSample * This);


void __RPC_STUB IMediaSample_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetTime_Proxy( 
    IMediaSample * This,
    /* [out] */ REFERENCE_TIME *pTimeStart,
    /* [out] */ REFERENCE_TIME *pTimeEnd);


void __RPC_STUB IMediaSample_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetTime_Proxy( 
    IMediaSample * This,
    /* [in] */ REFERENCE_TIME *pTimeStart,
    /* [in] */ REFERENCE_TIME *pTimeEnd);


void __RPC_STUB IMediaSample_SetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsSyncPoint_Proxy( 
    IMediaSample * This);


void __RPC_STUB IMediaSample_IsSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetSyncPoint_Proxy( 
    IMediaSample * This,
    BOOL bIsSyncPoint);


void __RPC_STUB IMediaSample_SetSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsPreroll_Proxy( 
    IMediaSample * This);


void __RPC_STUB IMediaSample_IsPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetPreroll_Proxy( 
    IMediaSample * This,
    BOOL bIsPreroll);


void __RPC_STUB IMediaSample_SetPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IMediaSample_GetActualDataLength_Proxy( 
    IMediaSample * This);


void __RPC_STUB IMediaSample_GetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetActualDataLength_Proxy( 
    IMediaSample * This,
    long __MIDL_0010);


void __RPC_STUB IMediaSample_SetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetMediaType_Proxy( 
    IMediaSample * This,
    AM_MEDIA_TYPE **ppMediaType);


void __RPC_STUB IMediaSample_GetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetMediaType_Proxy( 
    IMediaSample * This,
    AM_MEDIA_TYPE *pMediaType);


void __RPC_STUB IMediaSample_SetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsDiscontinuity_Proxy( 
    IMediaSample * This);


void __RPC_STUB IMediaSample_IsDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetDiscontinuity_Proxy( 
    IMediaSample * This,
    BOOL bDiscontinuity);


void __RPC_STUB IMediaSample_SetDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetMediaTime_Proxy( 
    IMediaSample * This,
    /* [out] */ LONGLONG *pTimeStart,
    /* [out] */ LONGLONG *pTimeEnd);


void __RPC_STUB IMediaSample_GetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetMediaTime_Proxy( 
    IMediaSample * This,
    /* [in] */ LONGLONG *pTimeStart,
    /* [in] */ LONGLONG *pTimeEnd);


void __RPC_STUB IMediaSample_SetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSample_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0123 */
/* [local] */ 

typedef IMediaSample *PMEDIASAMPLE;


enum tagAM_SAMPLE_PROPERTY_FLAGS
    {	AM_SAMPLE_SPLICEPOINT	= 0x1,
	AM_SAMPLE_PREROLL	= 0x2,
	AM_SAMPLE_DATADISCONTINUITY	= 0x4,
	AM_SAMPLE_TYPECHANGED	= 0x8,
	AM_SAMPLE_TIMEVALID	= 0x10,
	AM_SAMPLE_TIMEDISCONTINUITY	= 0x40,
	AM_SAMPLE_FLUSH_ON_PAUSE	= 0x80,
	AM_SAMPLE_STOPVALID	= 0x100,
	AM_SAMPLE_ENDOFSTREAM	= 0x200,
	AM_STREAM_MEDIA	= 0,
	AM_STREAM_CONTROL	= 1
    } ;
typedef struct tagAM_SAMPLE2_PROPERTIES
    {
    DWORD cbData;
    DWORD dwTypeSpecificFlags;
    DWORD dwSampleFlags;
    LONG lActual;
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD dwStreamId;
    AM_MEDIA_TYPE *pMediaType;
    BYTE *pbBuffer;
    LONG cbBuffer;
    } 	AM_SAMPLE2_PROPERTIES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0123_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0123_v0_0_s_ifspec;

#ifndef __IMediaSample2_INTERFACE_DEFINED__
#define __IMediaSample2_INTERFACE_DEFINED__

/* interface IMediaSample2 */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IMediaSample2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73884-c2c8-11cf-8b46-00805f6cef60")
    IMediaSample2 : public IMediaSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ DWORD cbProperties,
            /* [size_is][out] */ BYTE *pbProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ DWORD cbProperties,
            /* [size_is][in] */ const BYTE *pbProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSample2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaSample2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaSample2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPointer )( 
            IMediaSample2 * This,
            /* [out] */ BYTE **ppBuffer);
        
        long ( STDMETHODCALLTYPE *GetSize )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IMediaSample2 * This,
            /* [out] */ REFERENCE_TIME *pTimeStart,
            /* [out] */ REFERENCE_TIME *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetTime )( 
            IMediaSample2 * This,
            /* [in] */ REFERENCE_TIME *pTimeStart,
            /* [in] */ REFERENCE_TIME *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *IsSyncPoint )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetSyncPoint )( 
            IMediaSample2 * This,
            BOOL bIsSyncPoint);
        
        HRESULT ( STDMETHODCALLTYPE *IsPreroll )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPreroll )( 
            IMediaSample2 * This,
            BOOL bIsPreroll);
        
        long ( STDMETHODCALLTYPE *GetActualDataLength )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetActualDataLength )( 
            IMediaSample2 * This,
            long __MIDL_0010);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaType )( 
            IMediaSample2 * This,
            AM_MEDIA_TYPE **ppMediaType);
        
        HRESULT ( STDMETHODCALLTYPE *SetMediaType )( 
            IMediaSample2 * This,
            AM_MEDIA_TYPE *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE *IsDiscontinuity )( 
            IMediaSample2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDiscontinuity )( 
            IMediaSample2 * This,
            BOOL bDiscontinuity);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaTime )( 
            IMediaSample2 * This,
            /* [out] */ LONGLONG *pTimeStart,
            /* [out] */ LONGLONG *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetMediaTime )( 
            IMediaSample2 * This,
            /* [in] */ LONGLONG *pTimeStart,
            /* [in] */ LONGLONG *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *GetProperties )( 
            IMediaSample2 * This,
            /* [in] */ DWORD cbProperties,
            /* [size_is][out] */ BYTE *pbProperties);
        
        HRESULT ( STDMETHODCALLTYPE *SetProperties )( 
            IMediaSample2 * This,
            /* [in] */ DWORD cbProperties,
            /* [size_is][in] */ const BYTE *pbProperties);
        
        END_INTERFACE
    } IMediaSample2Vtbl;

    interface IMediaSample2
    {
        CONST_VTBL struct IMediaSample2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSample2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSample2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSample2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSample2_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IMediaSample2_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IMediaSample2_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IMediaSample2_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IMediaSample2_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IMediaSample2_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IMediaSample2_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IMediaSample2_SetActualDataLength(This,__MIDL_0010)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0010)

#define IMediaSample2_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IMediaSample2_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IMediaSample2_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IMediaSample2_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IMediaSample2_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)


#define IMediaSample2_GetProperties(This,cbProperties,pbProperties)	\
    (This)->lpVtbl -> GetProperties(This,cbProperties,pbProperties)

#define IMediaSample2_SetProperties(This,cbProperties,pbProperties)	\
    (This)->lpVtbl -> SetProperties(This,cbProperties,pbProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSample2_GetProperties_Proxy( 
    IMediaSample2 * This,
    /* [in] */ DWORD cbProperties,
    /* [size_is][out] */ BYTE *pbProperties);


void __RPC_STUB IMediaSample2_GetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample2_SetProperties_Proxy( 
    IMediaSample2 * This,
    /* [in] */ DWORD cbProperties,
    /* [size_is][in] */ const BYTE *pbProperties);


void __RPC_STUB IMediaSample2_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSample2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0124 */
/* [local] */ 

typedef IMediaSample2 *PMEDIASAMPLE2;

#define AM_GBF_PREVFRAMESKIPPED 1
#define AM_GBF_NOTASYNCPOINT 2
#define AM_GBF_NOWAIT 4
#define AM_GBF_NODDSURFACELOCK 8


extern RPC_IF_HANDLE __MIDL_itf_strmif_0124_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0124_v0_0_s_ifspec;

#ifndef __IMemAllocator_INTERFACE_DEFINED__
#define __IMemAllocator_INTERFACE_DEFINED__

/* interface IMemAllocator */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMemAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a8689c-0ad4-11ce-b03a-0020af0ba770")
    IMemAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ ALLOCATOR_PROPERTIES *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES *pActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [out] */ ALLOCATOR_PROPERTIES *pProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Decommit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [out] */ IMediaSample **ppBuffer,
            /* [in] */ REFERENCE_TIME *pStartTime,
            /* [in] */ REFERENCE_TIME *pEndTime,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer( 
            /* [in] */ IMediaSample *pBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMemAllocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMemAllocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMemAllocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetProperties )( 
            IMemAllocator * This,
            /* [in] */ ALLOCATOR_PROPERTIES *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES *pActual);
        
        HRESULT ( STDMETHODCALLTYPE *GetProperties )( 
            IMemAllocator * This,
            /* [out] */ ALLOCATOR_PROPERTIES *pProps);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IMemAllocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *Decommit )( 
            IMemAllocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IMemAllocator * This,
            /* [out] */ IMediaSample **ppBuffer,
            /* [in] */ REFERENCE_TIME *pStartTime,
            /* [in] */ REFERENCE_TIME *pEndTime,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseBuffer )( 
            IMemAllocator * This,
            /* [in] */ IMediaSample *pBuffer);
        
        END_INTERFACE
    } IMemAllocatorVtbl;

    interface IMemAllocator
    {
        CONST_VTBL struct IMemAllocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemAllocator_SetProperties(This,pRequest,pActual)	\
    (This)->lpVtbl -> SetProperties(This,pRequest,pActual)

#define IMemAllocator_GetProperties(This,pProps)	\
    (This)->lpVtbl -> GetProperties(This,pProps)

#define IMemAllocator_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IMemAllocator_Decommit(This)	\
    (This)->lpVtbl -> Decommit(This)

#define IMemAllocator_GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)	\
    (This)->lpVtbl -> GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)

#define IMemAllocator_ReleaseBuffer(This,pBuffer)	\
    (This)->lpVtbl -> ReleaseBuffer(This,pBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemAllocator_SetProperties_Proxy( 
    IMemAllocator * This,
    /* [in] */ ALLOCATOR_PROPERTIES *pRequest,
    /* [out] */ ALLOCATOR_PROPERTIES *pActual);


void __RPC_STUB IMemAllocator_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_GetProperties_Proxy( 
    IMemAllocator * This,
    /* [out] */ ALLOCATOR_PROPERTIES *pProps);


void __RPC_STUB IMemAllocator_GetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_Commit_Proxy( 
    IMemAllocator * This);


void __RPC_STUB IMemAllocator_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_Decommit_Proxy( 
    IMemAllocator * This);


void __RPC_STUB IMemAllocator_Decommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_GetBuffer_Proxy( 
    IMemAllocator * This,
    /* [out] */ IMediaSample **ppBuffer,
    /* [in] */ REFERENCE_TIME *pStartTime,
    /* [in] */ REFERENCE_TIME *pEndTime,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMemAllocator_GetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_ReleaseBuffer_Proxy( 
    IMemAllocator * This,
    /* [in] */ IMediaSample *pBuffer);


void __RPC_STUB IMemAllocator_ReleaseBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemAllocator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0125 */
/* [local] */ 

typedef IMemAllocator *PMEMALLOCATOR;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0125_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0125_v0_0_s_ifspec;

#ifndef __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__
#define __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__

/* interface IMemAllocatorCallbackTemp */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMemAllocatorCallbackTemp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("379a0cf0-c1de-11d2-abf5-00a0c905f375")
    IMemAllocatorCallbackTemp : public IMemAllocator
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetNotify( 
            /* [in] */ IMemAllocatorNotifyCallbackTemp *pNotify) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreeCount( 
            /* [out] */ LONG *plBuffersFree) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemAllocatorCallbackTempVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMemAllocatorCallbackTemp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMemAllocatorCallbackTemp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMemAllocatorCallbackTemp * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetProperties )( 
            IMemAllocatorCallbackTemp * This,
            /* [in] */ ALLOCATOR_PROPERTIES *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES *pActual);
        
        HRESULT ( STDMETHODCALLTYPE *GetProperties )( 
            IMemAllocatorCallbackTemp * This,
            /* [out] */ ALLOCATOR_PROPERTIES *pProps);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IMemAllocatorCallbackTemp * This);
        
        HRESULT ( STDMETHODCALLTYPE *Decommit )( 
            IMemAllocatorCallbackTemp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IMemAllocatorCallbackTemp * This,
            /* [out] */ IMediaSample **ppBuffer,
            /* [in] */ REFERENCE_TIME *pStartTime,
            /* [in] */ REFERENCE_TIME *pEndTime,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseBuffer )( 
            IMemAllocatorCallbackTemp * This,
            /* [in] */ IMediaSample *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *SetNotify )( 
            IMemAllocatorCallbackTemp * This,
            /* [in] */ IMemAllocatorNotifyCallbackTemp *pNotify);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreeCount )( 
            IMemAllocatorCallbackTemp * This,
            /* [out] */ LONG *plBuffersFree);
        
        END_INTERFACE
    } IMemAllocatorCallbackTempVtbl;

    interface IMemAllocatorCallbackTemp
    {
        CONST_VTBL struct IMemAllocatorCallbackTempVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemAllocatorCallbackTemp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemAllocatorCallbackTemp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemAllocatorCallbackTemp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemAllocatorCallbackTemp_SetProperties(This,pRequest,pActual)	\
    (This)->lpVtbl -> SetProperties(This,pRequest,pActual)

#define IMemAllocatorCallbackTemp_GetProperties(This,pProps)	\
    (This)->lpVtbl -> GetProperties(This,pProps)

#define IMemAllocatorCallbackTemp_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IMemAllocatorCallbackTemp_Decommit(This)	\
    (This)->lpVtbl -> Decommit(This)

#define IMemAllocatorCallbackTemp_GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)	\
    (This)->lpVtbl -> GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)

#define IMemAllocatorCallbackTemp_ReleaseBuffer(This,pBuffer)	\
    (This)->lpVtbl -> ReleaseBuffer(This,pBuffer)


#define IMemAllocatorCallbackTemp_SetNotify(This,pNotify)	\
    (This)->lpVtbl -> SetNotify(This,pNotify)

#define IMemAllocatorCallbackTemp_GetFreeCount(This,plBuffersFree)	\
    (This)->lpVtbl -> GetFreeCount(This,plBuffersFree)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemAllocatorCallbackTemp_SetNotify_Proxy( 
    IMemAllocatorCallbackTemp * This,
    /* [in] */ IMemAllocatorNotifyCallbackTemp *pNotify);


void __RPC_STUB IMemAllocatorCallbackTemp_SetNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocatorCallbackTemp_GetFreeCount_Proxy( 
    IMemAllocatorCallbackTemp * This,
    /* [out] */ LONG *plBuffersFree);


void __RPC_STUB IMemAllocatorCallbackTemp_GetFreeCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemAllocatorCallbackTemp_INTERFACE_DEFINED__ */


#ifndef __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__
#define __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__

/* interface IMemAllocatorNotifyCallbackTemp */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMemAllocatorNotifyCallbackTemp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92980b30-c1de-11d2-abf5-00a0c905f375")
    IMemAllocatorNotifyCallbackTemp : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NotifyRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemAllocatorNotifyCallbackTempVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMemAllocatorNotifyCallbackTemp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMemAllocatorNotifyCallbackTemp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMemAllocatorNotifyCallbackTemp * This);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyRelease )( 
            IMemAllocatorNotifyCallbackTemp * This);
        
        END_INTERFACE
    } IMemAllocatorNotifyCallbackTempVtbl;

    interface IMemAllocatorNotifyCallbackTemp
    {
        CONST_VTBL struct IMemAllocatorNotifyCallbackTempVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemAllocatorNotifyCallbackTemp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemAllocatorNotifyCallbackTemp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemAllocatorNotifyCallbackTemp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemAllocatorNotifyCallbackTemp_NotifyRelease(This)	\
    (This)->lpVtbl -> NotifyRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemAllocatorNotifyCallbackTemp_NotifyRelease_Proxy( 
    IMemAllocatorNotifyCallbackTemp * This);


void __RPC_STUB IMemAllocatorNotifyCallbackTemp_NotifyRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemAllocatorNotifyCallbackTemp_INTERFACE_DEFINED__ */


#ifndef __IMemInputPin_INTERFACE_DEFINED__
#define __IMemInputPin_INTERFACE_DEFINED__

/* interface IMemInputPin */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMemInputPin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a8689d-0ad4-11ce-b03a-0020af0ba770")
    IMemInputPin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAllocator( 
            /* [out] */ IMemAllocator **ppAllocator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyAllocator( 
            /* [in] */ IMemAllocator *pAllocator,
            /* [in] */ BOOL bReadOnly) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllocatorRequirements( 
            /* [out] */ ALLOCATOR_PROPERTIES *pProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Receive( 
            /* [in] */ IMediaSample *pSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveMultiple( 
            /* [size_is][in] */ IMediaSample **pSamples,
            /* [in] */ long nSamples,
            /* [out] */ long *nSamplesProcessed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveCanBlock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemInputPinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMemInputPin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMemInputPin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMemInputPin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllocator )( 
            IMemInputPin * This,
            /* [out] */ IMemAllocator **ppAllocator);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyAllocator )( 
            IMemInputPin * This,
            /* [in] */ IMemAllocator *pAllocator,
            /* [in] */ BOOL bReadOnly);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllocatorRequirements )( 
            IMemInputPin * This,
            /* [out] */ ALLOCATOR_PROPERTIES *pProps);
        
        HRESULT ( STDMETHODCALLTYPE *Receive )( 
            IMemInputPin * This,
            /* [in] */ IMediaSample *pSample);
        
        HRESULT ( STDMETHODCALLTYPE *ReceiveMultiple )( 
            IMemInputPin * This,
            /* [size_is][in] */ IMediaSample **pSamples,
            /* [in] */ long nSamples,
            /* [out] */ long *nSamplesProcessed);
        
        HRESULT ( STDMETHODCALLTYPE *ReceiveCanBlock )( 
            IMemInputPin * This);
        
        END_INTERFACE
    } IMemInputPinVtbl;

    interface IMemInputPin
    {
        CONST_VTBL struct IMemInputPinVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemInputPin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemInputPin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemInputPin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemInputPin_GetAllocator(This,ppAllocator)	\
    (This)->lpVtbl -> GetAllocator(This,ppAllocator)

#define IMemInputPin_NotifyAllocator(This,pAllocator,bReadOnly)	\
    (This)->lpVtbl -> NotifyAllocator(This,pAllocator,bReadOnly)

#define IMemInputPin_GetAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> GetAllocatorRequirements(This,pProps)

#define IMemInputPin_Receive(This,pSample)	\
    (This)->lpVtbl -> Receive(This,pSample)

#define IMemInputPin_ReceiveMultiple(This,pSamples,nSamples,nSamplesProcessed)	\
    (This)->lpVtbl -> ReceiveMultiple(This,pSamples,nSamples,nSamplesProcessed)

#define IMemInputPin_ReceiveCanBlock(This)	\
    (This)->lpVtbl -> ReceiveCanBlock(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemInputPin_GetAllocator_Proxy( 
    IMemInputPin * This,
    /* [out] */ IMemAllocator **ppAllocator);


void __RPC_STUB IMemInputPin_GetAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_NotifyAllocator_Proxy( 
    IMemInputPin * This,
    /* [in] */ IMemAllocator *pAllocator,
    /* [in] */ BOOL bReadOnly);


void __RPC_STUB IMemInputPin_NotifyAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_GetAllocatorRequirements_Proxy( 
    IMemInputPin * This,
    /* [out] */ ALLOCATOR_PROPERTIES *pProps);


void __RPC_STUB IMemInputPin_GetAllocatorRequirements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_Receive_Proxy( 
    IMemInputPin * This,
    /* [in] */ IMediaSample *pSample);


void __RPC_STUB IMemInputPin_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_ReceiveMultiple_Proxy( 
    IMemInputPin * This,
    /* [size_is][in] */ IMediaSample **pSamples,
    /* [in] */ long nSamples,
    /* [out] */ long *nSamplesProcessed);


void __RPC_STUB IMemInputPin_ReceiveMultiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_ReceiveCanBlock_Proxy( 
    IMemInputPin * This);


void __RPC_STUB IMemInputPin_ReceiveCanBlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemInputPin_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0128 */
/* [local] */ 

typedef IMemInputPin *PMEMINPUTPIN;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0128_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0128_v0_0_s_ifspec;

#ifndef __IAMovieSetup_INTERFACE_DEFINED__
#define __IAMovieSetup_INTERFACE_DEFINED__

/* interface IAMovieSetup */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMovieSetup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a3d8cec0-7e5a-11cf-bbc5-00805f6cef20")
    IAMovieSetup : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Register( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unregister( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMovieSetupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMovieSetup * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMovieSetup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMovieSetup * This);
        
        HRESULT ( STDMETHODCALLTYPE *Register )( 
            IAMovieSetup * This);
        
        HRESULT ( STDMETHODCALLTYPE *Unregister )( 
            IAMovieSetup * This);
        
        END_INTERFACE
    } IAMovieSetupVtbl;

    interface IAMovieSetup
    {
        CONST_VTBL struct IAMovieSetupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMovieSetup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMovieSetup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMovieSetup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMovieSetup_Register(This)	\
    (This)->lpVtbl -> Register(This)

#define IAMovieSetup_Unregister(This)	\
    (This)->lpVtbl -> Unregister(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMovieSetup_Register_Proxy( 
    IAMovieSetup * This);


void __RPC_STUB IAMovieSetup_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMovieSetup_Unregister_Proxy( 
    IAMovieSetup * This);


void __RPC_STUB IAMovieSetup_Unregister_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMovieSetup_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0129 */
/* [local] */ 

typedef IAMovieSetup *PAMOVIESETUP;

typedef 
enum AM_SEEKING_SeekingFlags
    {	AM_SEEKING_NoPositioning	= 0,
	AM_SEEKING_AbsolutePositioning	= 0x1,
	AM_SEEKING_RelativePositioning	= 0x2,
	AM_SEEKING_IncrementalPositioning	= 0x3,
	AM_SEEKING_PositioningBitsMask	= 0x3,
	AM_SEEKING_SeekToKeyFrame	= 0x4,
	AM_SEEKING_ReturnTime	= 0x8,
	AM_SEEKING_Segment	= 0x10,
	AM_SEEKING_NoFlush	= 0x20
    } 	AM_SEEKING_SEEKING_FLAGS;

typedef 
enum AM_SEEKING_SeekingCapabilities
    {	AM_SEEKING_CanSeekAbsolute	= 0x1,
	AM_SEEKING_CanSeekForwards	= 0x2,
	AM_SEEKING_CanSeekBackwards	= 0x4,
	AM_SEEKING_CanGetCurrentPos	= 0x8,
	AM_SEEKING_CanGetStopPos	= 0x10,
	AM_SEEKING_CanGetDuration	= 0x20,
	AM_SEEKING_CanPlayBackwards	= 0x40,
	AM_SEEKING_CanDoSegments	= 0x80,
	AM_SEEKING_Source	= 0x100
    } 	AM_SEEKING_SEEKING_CAPABILITIES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0129_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0129_v0_0_s_ifspec;

#ifndef __IMediaSeeking_INTERFACE_DEFINED__
#define __IMediaSeeking_INTERFACE_DEFINED__

/* interface IMediaSeeking */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMediaSeeking;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73880-c2c8-11cf-8b46-00805f6cef60")
    IMediaSeeking : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCapabilities( 
            /* [out] */ DWORD *pCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckCapabilities( 
            /* [out][in] */ DWORD *pCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsFormatSupported( 
            /* [in] */ const GUID *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryPreferredFormat( 
            /* [out] */ GUID *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimeFormat( 
            /* [out] */ GUID *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingTimeFormat( 
            /* [in] */ const GUID *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimeFormat( 
            /* [in] */ const GUID *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDuration( 
            /* [out] */ LONGLONG *pDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStopPosition( 
            /* [out] */ LONGLONG *pStop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentPosition( 
            /* [out] */ LONGLONG *pCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertTimeFormat( 
            /* [out] */ LONGLONG *pTarget,
            /* [in] */ const GUID *pTargetFormat,
            /* [in] */ LONGLONG Source,
            /* [in] */ const GUID *pSourceFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPositions( 
            /* [out][in] */ LONGLONG *pCurrent,
            /* [in] */ DWORD dwCurrentFlags,
            /* [out][in] */ LONGLONG *pStop,
            /* [in] */ DWORD dwStopFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPositions( 
            /* [out] */ LONGLONG *pCurrent,
            /* [out] */ LONGLONG *pStop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailable( 
            /* [out] */ LONGLONG *pEarliest,
            /* [out] */ LONGLONG *pLatest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRate( 
            /* [in] */ double dRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRate( 
            /* [out] */ double *pdRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPreroll( 
            /* [out] */ LONGLONG *pllPreroll) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSeekingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaSeeking * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaSeeking * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaSeeking * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCapabilities )( 
            IMediaSeeking * This,
            /* [out] */ DWORD *pCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *CheckCapabilities )( 
            IMediaSeeking * This,
            /* [out][in] */ DWORD *pCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *IsFormatSupported )( 
            IMediaSeeking * This,
            /* [in] */ const GUID *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *QueryPreferredFormat )( 
            IMediaSeeking * This,
            /* [out] */ GUID *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimeFormat )( 
            IMediaSeeking * This,
            /* [out] */ GUID *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *IsUsingTimeFormat )( 
            IMediaSeeking * This,
            /* [in] */ const GUID *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimeFormat )( 
            IMediaSeeking * This,
            /* [in] */ const GUID *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetDuration )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pDuration);
        
        HRESULT ( STDMETHODCALLTYPE *GetStopPosition )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pStop);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentPosition )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *ConvertTimeFormat )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pTarget,
            /* [in] */ const GUID *pTargetFormat,
            /* [in] */ LONGLONG Source,
            /* [in] */ const GUID *pSourceFormat);
        
        HRESULT ( STDMETHODCALLTYPE *SetPositions )( 
            IMediaSeeking * This,
            /* [out][in] */ LONGLONG *pCurrent,
            /* [in] */ DWORD dwCurrentFlags,
            /* [out][in] */ LONGLONG *pStop,
            /* [in] */ DWORD dwStopFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetPositions )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pCurrent,
            /* [out] */ LONGLONG *pStop);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailable )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pEarliest,
            /* [out] */ LONGLONG *pLatest);
        
        HRESULT ( STDMETHODCALLTYPE *SetRate )( 
            IMediaSeeking * This,
            /* [in] */ double dRate);
        
        HRESULT ( STDMETHODCALLTYPE *GetRate )( 
            IMediaSeeking * This,
            /* [out] */ double *pdRate);
        
        HRESULT ( STDMETHODCALLTYPE *GetPreroll )( 
            IMediaSeeking * This,
            /* [out] */ LONGLONG *pllPreroll);
        
        END_INTERFACE
    } IMediaSeekingVtbl;

    interface IMediaSeeking
    {
        CONST_VTBL struct IMediaSeekingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSeeking_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSeeking_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSeeking_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSeeking_GetCapabilities(This,pCapabilities)	\
    (This)->lpVtbl -> GetCapabilities(This,pCapabilities)

#define IMediaSeeking_CheckCapabilities(This,pCapabilities)	\
    (This)->lpVtbl -> CheckCapabilities(This,pCapabilities)

#define IMediaSeeking_IsFormatSupported(This,pFormat)	\
    (This)->lpVtbl -> IsFormatSupported(This,pFormat)

#define IMediaSeeking_QueryPreferredFormat(This,pFormat)	\
    (This)->lpVtbl -> QueryPreferredFormat(This,pFormat)

#define IMediaSeeking_GetTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> GetTimeFormat(This,pFormat)

#define IMediaSeeking_IsUsingTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> IsUsingTimeFormat(This,pFormat)

#define IMediaSeeking_SetTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> SetTimeFormat(This,pFormat)

#define IMediaSeeking_GetDuration(This,pDuration)	\
    (This)->lpVtbl -> GetDuration(This,pDuration)

#define IMediaSeeking_GetStopPosition(This,pStop)	\
    (This)->lpVtbl -> GetStopPosition(This,pStop)

#define IMediaSeeking_GetCurrentPosition(This,pCurrent)	\
    (This)->lpVtbl -> GetCurrentPosition(This,pCurrent)

#define IMediaSeeking_ConvertTimeFormat(This,pTarget,pTargetFormat,Source,pSourceFormat)	\
    (This)->lpVtbl -> ConvertTimeFormat(This,pTarget,pTargetFormat,Source,pSourceFormat)

#define IMediaSeeking_SetPositions(This,pCurrent,dwCurrentFlags,pStop,dwStopFlags)	\
    (This)->lpVtbl -> SetPositions(This,pCurrent,dwCurrentFlags,pStop,dwStopFlags)

#define IMediaSeeking_GetPositions(This,pCurrent,pStop)	\
    (This)->lpVtbl -> GetPositions(This,pCurrent,pStop)

#define IMediaSeeking_GetAvailable(This,pEarliest,pLatest)	\
    (This)->lpVtbl -> GetAvailable(This,pEarliest,pLatest)

#define IMediaSeeking_SetRate(This,dRate)	\
    (This)->lpVtbl -> SetRate(This,dRate)

#define IMediaSeeking_GetRate(This,pdRate)	\
    (This)->lpVtbl -> GetRate(This,pdRate)

#define IMediaSeeking_GetPreroll(This,pllPreroll)	\
    (This)->lpVtbl -> GetPreroll(This,pllPreroll)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSeeking_GetCapabilities_Proxy( 
    IMediaSeeking * This,
    /* [out] */ DWORD *pCapabilities);


void __RPC_STUB IMediaSeeking_GetCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_CheckCapabilities_Proxy( 
    IMediaSeeking * This,
    /* [out][in] */ DWORD *pCapabilities);


void __RPC_STUB IMediaSeeking_CheckCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_IsFormatSupported_Proxy( 
    IMediaSeeking * This,
    /* [in] */ const GUID *pFormat);


void __RPC_STUB IMediaSeeking_IsFormatSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_QueryPreferredFormat_Proxy( 
    IMediaSeeking * This,
    /* [out] */ GUID *pFormat);


void __RPC_STUB IMediaSeeking_QueryPreferredFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetTimeFormat_Proxy( 
    IMediaSeeking * This,
    /* [out] */ GUID *pFormat);


void __RPC_STUB IMediaSeeking_GetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_IsUsingTimeFormat_Proxy( 
    IMediaSeeking * This,
    /* [in] */ const GUID *pFormat);


void __RPC_STUB IMediaSeeking_IsUsingTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetTimeFormat_Proxy( 
    IMediaSeeking * This,
    /* [in] */ const GUID *pFormat);


void __RPC_STUB IMediaSeeking_SetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetDuration_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pDuration);


void __RPC_STUB IMediaSeeking_GetDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetStopPosition_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pStop);


void __RPC_STUB IMediaSeeking_GetStopPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetCurrentPosition_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pCurrent);


void __RPC_STUB IMediaSeeking_GetCurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_ConvertTimeFormat_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pTarget,
    /* [in] */ const GUID *pTargetFormat,
    /* [in] */ LONGLONG Source,
    /* [in] */ const GUID *pSourceFormat);


void __RPC_STUB IMediaSeeking_ConvertTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetPositions_Proxy( 
    IMediaSeeking * This,
    /* [out][in] */ LONGLONG *pCurrent,
    /* [in] */ DWORD dwCurrentFlags,
    /* [out][in] */ LONGLONG *pStop,
    /* [in] */ DWORD dwStopFlags);


void __RPC_STUB IMediaSeeking_SetPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetPositions_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pCurrent,
    /* [out] */ LONGLONG *pStop);


void __RPC_STUB IMediaSeeking_GetPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetAvailable_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pEarliest,
    /* [out] */ LONGLONG *pLatest);


void __RPC_STUB IMediaSeeking_GetAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetRate_Proxy( 
    IMediaSeeking * This,
    /* [in] */ double dRate);


void __RPC_STUB IMediaSeeking_SetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetRate_Proxy( 
    IMediaSeeking * This,
    /* [out] */ double *pdRate);


void __RPC_STUB IMediaSeeking_GetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetPreroll_Proxy( 
    IMediaSeeking * This,
    /* [out] */ LONGLONG *pllPreroll);


void __RPC_STUB IMediaSeeking_GetPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSeeking_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0130 */
/* [local] */ 

typedef IMediaSeeking *PMEDIASEEKING;

enum tagAM_MEDIAEVENT_FLAGS
{
    AM_MEDIAEVENT_NONOTIFY = 0x01
};
























































typedef /* [public][public] */ struct __MIDL___MIDL_itf_strmif_0130_0001
    {
    CLSID Clsid;
    LPWSTR Name;
    } 	REGFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0130_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0130_v0_0_s_ifspec;

#ifndef __IEnumRegFilters_INTERFACE_DEFINED__
#define __IEnumRegFilters_INTERFACE_DEFINED__

/* interface IEnumRegFilters */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumRegFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a4-0ad4-11ce-b03a-0020af0ba770")
    IEnumRegFilters : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cFilters,
            /* [out] */ REGFILTER **apRegFilter,
            /* [out] */ ULONG *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cFilters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRegFilters **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumRegFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumRegFilters * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumRegFilters * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumRegFilters * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumRegFilters * This,
            /* [in] */ ULONG cFilters,
            /* [out] */ REGFILTER **apRegFilter,
            /* [out] */ ULONG *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumRegFilters * This,
            /* [in] */ ULONG cFilters);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumRegFilters * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumRegFilters * This,
            /* [out] */ IEnumRegFilters **ppEnum);
        
        END_INTERFACE
    } IEnumRegFiltersVtbl;

    interface IEnumRegFilters
    {
        CONST_VTBL struct IEnumRegFiltersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRegFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumRegFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumRegFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumRegFilters_Next(This,cFilters,apRegFilter,pcFetched)	\
    (This)->lpVtbl -> Next(This,cFilters,apRegFilter,pcFetched)

#define IEnumRegFilters_Skip(This,cFilters)	\
    (This)->lpVtbl -> Skip(This,cFilters)

#define IEnumRegFilters_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumRegFilters_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumRegFilters_Next_Proxy( 
    IEnumRegFilters * This,
    /* [in] */ ULONG cFilters,
    /* [out] */ REGFILTER **apRegFilter,
    /* [out] */ ULONG *pcFetched);


void __RPC_STUB IEnumRegFilters_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Skip_Proxy( 
    IEnumRegFilters * This,
    /* [in] */ ULONG cFilters);


void __RPC_STUB IEnumRegFilters_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Reset_Proxy( 
    IEnumRegFilters * This);


void __RPC_STUB IEnumRegFilters_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Clone_Proxy( 
    IEnumRegFilters * This,
    /* [out] */ IEnumRegFilters **ppEnum);


void __RPC_STUB IEnumRegFilters_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumRegFilters_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0132 */
/* [local] */ 

typedef IEnumRegFilters *PENUMREGFILTERS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0132_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0132_v0_0_s_ifspec;

#ifndef __IFilterMapper_INTERFACE_DEFINED__
#define __IFilterMapper_INTERFACE_DEFINED__

/* interface IFilterMapper */
/* [unique][uuid][object] */ 


enum __MIDL_IFilterMapper_0001
    {	MERIT_PREFERRED	= 0x800000,
	MERIT_NORMAL	= 0x600000,
	MERIT_UNLIKELY	= 0x400000,
	MERIT_DO_NOT_USE	= 0x200000,
	MERIT_SW_COMPRESSOR	= 0x100000,
	MERIT_HW_COMPRESSOR	= 0x100050
    } ;

EXTERN_C const IID IID_IFilterMapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a3-0ad4-11ce-b03a-0020af0ba770")
    IFilterMapper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterFilter( 
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [in] */ DWORD dwMerit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterFilterInstance( 
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [out] */ CLSID *MRId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterPin( 
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name,
            /* [in] */ BOOL bRendered,
            /* [in] */ BOOL bOutput,
            /* [in] */ BOOL bZero,
            /* [in] */ BOOL bMany,
            /* [in] */ CLSID ConnectsToFilter,
            /* [in] */ LPCWSTR ConnectsToPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterPinType( 
            /* [in] */ CLSID clsFilter,
            /* [in] */ LPCWSTR strName,
            /* [in] */ CLSID clsMajorType,
            /* [in] */ CLSID clsSubType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterFilter( 
            /* [in] */ CLSID Filter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterFilterInstance( 
            /* [in] */ CLSID MRId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterPin( 
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMatchingFilters( 
            /* [out] */ IEnumRegFilters **ppEnum,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ CLSID clsInMaj,
            /* [in] */ CLSID clsInSub,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOututNeeded,
            /* [in] */ CLSID clsOutMaj,
            /* [in] */ CLSID clsOutSub) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterMapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterMapper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterMapper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterMapper * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterFilter )( 
            IFilterMapper * This,
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [in] */ DWORD dwMerit);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterFilterInstance )( 
            IFilterMapper * This,
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [out] */ CLSID *MRId);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterPin )( 
            IFilterMapper * This,
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name,
            /* [in] */ BOOL bRendered,
            /* [in] */ BOOL bOutput,
            /* [in] */ BOOL bZero,
            /* [in] */ BOOL bMany,
            /* [in] */ CLSID ConnectsToFilter,
            /* [in] */ LPCWSTR ConnectsToPin);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterPinType )( 
            IFilterMapper * This,
            /* [in] */ CLSID clsFilter,
            /* [in] */ LPCWSTR strName,
            /* [in] */ CLSID clsMajorType,
            /* [in] */ CLSID clsSubType);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterFilter )( 
            IFilterMapper * This,
            /* [in] */ CLSID Filter);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterFilterInstance )( 
            IFilterMapper * This,
            /* [in] */ CLSID MRId);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterPin )( 
            IFilterMapper * This,
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMatchingFilters )( 
            IFilterMapper * This,
            /* [out] */ IEnumRegFilters **ppEnum,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ CLSID clsInMaj,
            /* [in] */ CLSID clsInSub,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOututNeeded,
            /* [in] */ CLSID clsOutMaj,
            /* [in] */ CLSID clsOutSub);
        
        END_INTERFACE
    } IFilterMapperVtbl;

    interface IFilterMapper
    {
        CONST_VTBL struct IFilterMapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterMapper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterMapper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterMapper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterMapper_RegisterFilter(This,clsid,Name,dwMerit)	\
    (This)->lpVtbl -> RegisterFilter(This,clsid,Name,dwMerit)

#define IFilterMapper_RegisterFilterInstance(This,clsid,Name,MRId)	\
    (This)->lpVtbl -> RegisterFilterInstance(This,clsid,Name,MRId)

#define IFilterMapper_RegisterPin(This,Filter,Name,bRendered,bOutput,bZero,bMany,ConnectsToFilter,ConnectsToPin)	\
    (This)->lpVtbl -> RegisterPin(This,Filter,Name,bRendered,bOutput,bZero,bMany,ConnectsToFilter,ConnectsToPin)

#define IFilterMapper_RegisterPinType(This,clsFilter,strName,clsMajorType,clsSubType)	\
    (This)->lpVtbl -> RegisterPinType(This,clsFilter,strName,clsMajorType,clsSubType)

#define IFilterMapper_UnregisterFilter(This,Filter)	\
    (This)->lpVtbl -> UnregisterFilter(This,Filter)

#define IFilterMapper_UnregisterFilterInstance(This,MRId)	\
    (This)->lpVtbl -> UnregisterFilterInstance(This,MRId)

#define IFilterMapper_UnregisterPin(This,Filter,Name)	\
    (This)->lpVtbl -> UnregisterPin(This,Filter,Name)

#define IFilterMapper_EnumMatchingFilters(This,ppEnum,dwMerit,bInputNeeded,clsInMaj,clsInSub,bRender,bOututNeeded,clsOutMaj,clsOutSub)	\
    (This)->lpVtbl -> EnumMatchingFilters(This,ppEnum,dwMerit,bInputNeeded,clsInMaj,clsInSub,bRender,bOututNeeded,clsOutMaj,clsOutSub)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterFilter_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID clsid,
    /* [in] */ LPCWSTR Name,
    /* [in] */ DWORD dwMerit);


void __RPC_STUB IFilterMapper_RegisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterFilterInstance_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID clsid,
    /* [in] */ LPCWSTR Name,
    /* [out] */ CLSID *MRId);


void __RPC_STUB IFilterMapper_RegisterFilterInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterPin_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID Filter,
    /* [in] */ LPCWSTR Name,
    /* [in] */ BOOL bRendered,
    /* [in] */ BOOL bOutput,
    /* [in] */ BOOL bZero,
    /* [in] */ BOOL bMany,
    /* [in] */ CLSID ConnectsToFilter,
    /* [in] */ LPCWSTR ConnectsToPin);


void __RPC_STUB IFilterMapper_RegisterPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterPinType_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID clsFilter,
    /* [in] */ LPCWSTR strName,
    /* [in] */ CLSID clsMajorType,
    /* [in] */ CLSID clsSubType);


void __RPC_STUB IFilterMapper_RegisterPinType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterFilter_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID Filter);


void __RPC_STUB IFilterMapper_UnregisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterFilterInstance_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID MRId);


void __RPC_STUB IFilterMapper_UnregisterFilterInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterPin_Proxy( 
    IFilterMapper * This,
    /* [in] */ CLSID Filter,
    /* [in] */ LPCWSTR Name);


void __RPC_STUB IFilterMapper_UnregisterPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_EnumMatchingFilters_Proxy( 
    IFilterMapper * This,
    /* [out] */ IEnumRegFilters **ppEnum,
    /* [in] */ DWORD dwMerit,
    /* [in] */ BOOL bInputNeeded,
    /* [in] */ CLSID clsInMaj,
    /* [in] */ CLSID clsInSub,
    /* [in] */ BOOL bRender,
    /* [in] */ BOOL bOututNeeded,
    /* [in] */ CLSID clsOutMaj,
    /* [in] */ CLSID clsOutSub);


void __RPC_STUB IFilterMapper_EnumMatchingFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterMapper_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0134 */
/* [local] */ 

typedef /* [public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_strmif_0134_0001
    {
    const CLSID *clsMajorType;
    const CLSID *clsMinorType;
    } 	REGPINTYPES;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_strmif_0134_0002
    {
    LPWSTR strName;
    BOOL bRendered;
    BOOL bOutput;
    BOOL bZero;
    BOOL bMany;
    const CLSID *clsConnectsToFilter;
    const WCHAR *strConnectsToPin;
    UINT nMediaTypes;
    const REGPINTYPES *lpMediaType;
    } 	REGFILTERPINS;

typedef /* [public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_strmif_0134_0003
    {
    CLSID clsMedium;
    DWORD dw1;
    DWORD dw2;
    } 	REGPINMEDIUM;


enum __MIDL___MIDL_itf_strmif_0134_0004
    {	REG_PINFLAG_B_ZERO	= 0x1,
	REG_PINFLAG_B_RENDERER	= 0x2,
	REG_PINFLAG_B_MANY	= 0x4,
	REG_PINFLAG_B_OUTPUT	= 0x8
    } ;
typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_strmif_0134_0005
    {
    DWORD dwFlags;
    UINT cInstances;
    UINT nMediaTypes;
    /* [size_is] */ const REGPINTYPES *lpMediaType;
    UINT nMediums;
    /* [size_is] */ const REGPINMEDIUM *lpMedium;
    const CLSID *clsPinCategory;
    } 	REGFILTERPINS2;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_strmif_0134_0006
    {
    DWORD dwVersion;
    DWORD dwMerit;
    /* [switch_type][switch_is] */ union 
        {
        /* [case()] */ struct 
            {
            ULONG cPins;
            /* [size_is] */ const REGFILTERPINS *rgPins;
            } 	;
        /* [case()] */ struct 
            {
            ULONG cPins2;
            /* [size_is] */ const REGFILTERPINS2 *rgPins2;
            } 	;
        /* [default] */  /* Empty union arm */ 
        } 	;
    } 	REGFILTER2;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0134_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0134_v0_0_s_ifspec;

#ifndef __IFilterMapper2_INTERFACE_DEFINED__
#define __IFilterMapper2_INTERFACE_DEFINED__

/* interface IFilterMapper2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFilterMapper2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b79bb0b0-33c1-11d1-abe1-00a0c905f375")
    IFilterMapper2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateCategory( 
            /* [in] */ REFCLSID clsidCategory,
            /* [in] */ DWORD dwCategoryMerit,
            /* [in] */ LPCWSTR Description) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterFilter( 
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ REFCLSID Filter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterFilter( 
            /* [in] */ REFCLSID clsidFilter,
            /* [in] */ LPCWSTR Name,
            /* [out][in] */ IMoniker **ppMoniker,
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ const REGFILTER2 *prf2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMatchingFilters( 
            /* [out] */ IEnumMoniker **ppEnum,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL bExactMatch,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ DWORD cInputTypes,
            /* [size_is] */ const GUID *pInputTypes,
            /* [in] */ const REGPINMEDIUM *pMedIn,
            /* [in] */ const CLSID *pPinCategoryIn,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOutputNeeded,
            /* [in] */ DWORD cOutputTypes,
            /* [size_is] */ const GUID *pOutputTypes,
            /* [in] */ const REGPINMEDIUM *pMedOut,
            /* [in] */ const CLSID *pPinCategoryOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterMapper2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterMapper2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterMapper2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterMapper2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateCategory )( 
            IFilterMapper2 * This,
            /* [in] */ REFCLSID clsidCategory,
            /* [in] */ DWORD dwCategoryMerit,
            /* [in] */ LPCWSTR Description);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterFilter )( 
            IFilterMapper2 * This,
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ REFCLSID Filter);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterFilter )( 
            IFilterMapper2 * This,
            /* [in] */ REFCLSID clsidFilter,
            /* [in] */ LPCWSTR Name,
            /* [out][in] */ IMoniker **ppMoniker,
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ const REGFILTER2 *prf2);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMatchingFilters )( 
            IFilterMapper2 * This,
            /* [out] */ IEnumMoniker **ppEnum,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL bExactMatch,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ DWORD cInputTypes,
            /* [size_is] */ const GUID *pInputTypes,
            /* [in] */ const REGPINMEDIUM *pMedIn,
            /* [in] */ const CLSID *pPinCategoryIn,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOutputNeeded,
            /* [in] */ DWORD cOutputTypes,
            /* [size_is] */ const GUID *pOutputTypes,
            /* [in] */ const REGPINMEDIUM *pMedOut,
            /* [in] */ const CLSID *pPinCategoryOut);
        
        END_INTERFACE
    } IFilterMapper2Vtbl;

    interface IFilterMapper2
    {
        CONST_VTBL struct IFilterMapper2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterMapper2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterMapper2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterMapper2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterMapper2_CreateCategory(This,clsidCategory,dwCategoryMerit,Description)	\
    (This)->lpVtbl -> CreateCategory(This,clsidCategory,dwCategoryMerit,Description)

#define IFilterMapper2_UnregisterFilter(This,pclsidCategory,szInstance,Filter)	\
    (This)->lpVtbl -> UnregisterFilter(This,pclsidCategory,szInstance,Filter)

#define IFilterMapper2_RegisterFilter(This,clsidFilter,Name,ppMoniker,pclsidCategory,szInstance,prf2)	\
    (This)->lpVtbl -> RegisterFilter(This,clsidFilter,Name,ppMoniker,pclsidCategory,szInstance,prf2)

#define IFilterMapper2_EnumMatchingFilters(This,ppEnum,dwFlags,bExactMatch,dwMerit,bInputNeeded,cInputTypes,pInputTypes,pMedIn,pPinCategoryIn,bRender,bOutputNeeded,cOutputTypes,pOutputTypes,pMedOut,pPinCategoryOut)	\
    (This)->lpVtbl -> EnumMatchingFilters(This,ppEnum,dwFlags,bExactMatch,dwMerit,bInputNeeded,cInputTypes,pInputTypes,pMedIn,pPinCategoryIn,bRender,bOutputNeeded,cOutputTypes,pOutputTypes,pMedOut,pPinCategoryOut)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterMapper2_CreateCategory_Proxy( 
    IFilterMapper2 * This,
    /* [in] */ REFCLSID clsidCategory,
    /* [in] */ DWORD dwCategoryMerit,
    /* [in] */ LPCWSTR Description);


void __RPC_STUB IFilterMapper2_CreateCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper2_UnregisterFilter_Proxy( 
    IFilterMapper2 * This,
    /* [in] */ const CLSID *pclsidCategory,
    /* [in] */ const OLECHAR *szInstance,
    /* [in] */ REFCLSID Filter);


void __RPC_STUB IFilterMapper2_UnregisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper2_RegisterFilter_Proxy( 
    IFilterMapper2 * This,
    /* [in] */ REFCLSID clsidFilter,
    /* [in] */ LPCWSTR Name,
    /* [out][in] */ IMoniker **ppMoniker,
    /* [in] */ const CLSID *pclsidCategory,
    /* [in] */ const OLECHAR *szInstance,
    /* [in] */ const REGFILTER2 *prf2);


void __RPC_STUB IFilterMapper2_RegisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper2_EnumMatchingFilters_Proxy( 
    IFilterMapper2 * This,
    /* [out] */ IEnumMoniker **ppEnum,
    /* [in] */ DWORD dwFlags,
    /* [in] */ BOOL bExactMatch,
    /* [in] */ DWORD dwMerit,
    /* [in] */ BOOL bInputNeeded,
    /* [in] */ DWORD cInputTypes,
    /* [size_is] */ const GUID *pInputTypes,
    /* [in] */ const REGPINMEDIUM *pMedIn,
    /* [in] */ const CLSID *pPinCategoryIn,
    /* [in] */ BOOL bRender,
    /* [in] */ BOOL bOutputNeeded,
    /* [in] */ DWORD cOutputTypes,
    /* [size_is] */ const GUID *pOutputTypes,
    /* [in] */ const REGPINMEDIUM *pMedOut,
    /* [in] */ const CLSID *pPinCategoryOut);


void __RPC_STUB IFilterMapper2_EnumMatchingFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterMapper2_INTERFACE_DEFINED__ */


#ifndef __IFilterMapper3_INTERFACE_DEFINED__
#define __IFilterMapper3_INTERFACE_DEFINED__

/* interface IFilterMapper3 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFilterMapper3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b79bb0b1-33c1-11d1-abe1-00a0c905f375")
    IFilterMapper3 : public IFilterMapper2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetICreateDevEnum( 
            /* [out] */ ICreateDevEnum **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterMapper3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterMapper3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterMapper3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterMapper3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateCategory )( 
            IFilterMapper3 * This,
            /* [in] */ REFCLSID clsidCategory,
            /* [in] */ DWORD dwCategoryMerit,
            /* [in] */ LPCWSTR Description);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterFilter )( 
            IFilterMapper3 * This,
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ REFCLSID Filter);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterFilter )( 
            IFilterMapper3 * This,
            /* [in] */ REFCLSID clsidFilter,
            /* [in] */ LPCWSTR Name,
            /* [out][in] */ IMoniker **ppMoniker,
            /* [in] */ const CLSID *pclsidCategory,
            /* [in] */ const OLECHAR *szInstance,
            /* [in] */ const REGFILTER2 *prf2);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMatchingFilters )( 
            IFilterMapper3 * This,
            /* [out] */ IEnumMoniker **ppEnum,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL bExactMatch,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ DWORD cInputTypes,
            /* [size_is] */ const GUID *pInputTypes,
            /* [in] */ const REGPINMEDIUM *pMedIn,
            /* [in] */ const CLSID *pPinCategoryIn,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOutputNeeded,
            /* [in] */ DWORD cOutputTypes,
            /* [size_is] */ const GUID *pOutputTypes,
            /* [in] */ const REGPINMEDIUM *pMedOut,
            /* [in] */ const CLSID *pPinCategoryOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetICreateDevEnum )( 
            IFilterMapper3 * This,
            /* [out] */ ICreateDevEnum **ppEnum);
        
        END_INTERFACE
    } IFilterMapper3Vtbl;

    interface IFilterMapper3
    {
        CONST_VTBL struct IFilterMapper3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterMapper3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterMapper3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterMapper3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterMapper3_CreateCategory(This,clsidCategory,dwCategoryMerit,Description)	\
    (This)->lpVtbl -> CreateCategory(This,clsidCategory,dwCategoryMerit,Description)

#define IFilterMapper3_UnregisterFilter(This,pclsidCategory,szInstance,Filter)	\
    (This)->lpVtbl -> UnregisterFilter(This,pclsidCategory,szInstance,Filter)

#define IFilterMapper3_RegisterFilter(This,clsidFilter,Name,ppMoniker,pclsidCategory,szInstance,prf2)	\
    (This)->lpVtbl -> RegisterFilter(This,clsidFilter,Name,ppMoniker,pclsidCategory,szInstance,prf2)

#define IFilterMapper3_EnumMatchingFilters(This,ppEnum,dwFlags,bExactMatch,dwMerit,bInputNeeded,cInputTypes,pInputTypes,pMedIn,pPinCategoryIn,bRender,bOutputNeeded,cOutputTypes,pOutputTypes,pMedOut,pPinCategoryOut)	\
    (This)->lpVtbl -> EnumMatchingFilters(This,ppEnum,dwFlags,bExactMatch,dwMerit,bInputNeeded,cInputTypes,pInputTypes,pMedIn,pPinCategoryIn,bRender,bOutputNeeded,cOutputTypes,pOutputTypes,pMedOut,pPinCategoryOut)


#define IFilterMapper3_GetICreateDevEnum(This,ppEnum)	\
    (This)->lpVtbl -> GetICreateDevEnum(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterMapper3_GetICreateDevEnum_Proxy( 
    IFilterMapper3 * This,
    /* [out] */ ICreateDevEnum **ppEnum);


void __RPC_STUB IFilterMapper3_GetICreateDevEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterMapper3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0137 */
/* [local] */ 

typedef 
enum tagQualityMessageType
    {	Famine	= 0,
	Flood	= Famine + 1
    } 	QualityMessageType;

typedef struct tagQuality
    {
    QualityMessageType Type;
    long Proportion;
    REFERENCE_TIME Late;
    REFERENCE_TIME TimeStamp;
    } 	Quality;

typedef IQualityControl *PQUALITYCONTROL;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0137_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0137_v0_0_s_ifspec;

#ifndef __IQualityControl_INTERFACE_DEFINED__
#define __IQualityControl_INTERFACE_DEFINED__

/* interface IQualityControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IQualityControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a5-0ad4-11ce-b03a-0020af0ba770")
    IQualityControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ IBaseFilter *pSelf,
            /* [in] */ Quality q) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSink( 
            /* [in] */ IQualityControl *piqc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQualityControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQualityControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQualityControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQualityControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            IQualityControl * This,
            /* [in] */ IBaseFilter *pSelf,
            /* [in] */ Quality q);
        
        HRESULT ( STDMETHODCALLTYPE *SetSink )( 
            IQualityControl * This,
            /* [in] */ IQualityControl *piqc);
        
        END_INTERFACE
    } IQualityControlVtbl;

    interface IQualityControl
    {
        CONST_VTBL struct IQualityControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQualityControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IQualityControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IQualityControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IQualityControl_Notify(This,pSelf,q)	\
    (This)->lpVtbl -> Notify(This,pSelf,q)

#define IQualityControl_SetSink(This,piqc)	\
    (This)->lpVtbl -> SetSink(This,piqc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQualityControl_Notify_Proxy( 
    IQualityControl * This,
    /* [in] */ IBaseFilter *pSelf,
    /* [in] */ Quality q);


void __RPC_STUB IQualityControl_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IQualityControl_SetSink_Proxy( 
    IQualityControl * This,
    /* [in] */ IQualityControl *piqc);


void __RPC_STUB IQualityControl_SetSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQualityControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0138 */
/* [local] */ 


enum __MIDL___MIDL_itf_strmif_0138_0001
    {	CK_NOCOLORKEY	= 0,
	CK_INDEX	= 0x1,
	CK_RGB	= 0x2
    } ;
typedef struct tagCOLORKEY
    {
    DWORD KeyType;
    DWORD PaletteIndex;
    COLORREF LowColorValue;
    COLORREF HighColorValue;
    } 	COLORKEY;


enum __MIDL___MIDL_itf_strmif_0138_0002
    {	ADVISE_NONE	= 0,
	ADVISE_CLIPPING	= 0x1,
	ADVISE_PALETTE	= 0x2,
	ADVISE_COLORKEY	= 0x4,
	ADVISE_POSITION	= 0x8,
	ADVISE_DISPLAY_CHANGE	= 0x10
    } ;
#define	ADVISE_ALL	( ADVISE_CLIPPING | ADVISE_PALETTE | ADVISE_COLORKEY | ADVISE_POSITION )

#define	ADVISE_ALL2	( ADVISE_ALL | ADVISE_DISPLAY_CHANGE )

#ifndef _WINGDI_
typedef struct _RGNDATAHEADER
    {
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT rcBound;
    } 	RGNDATAHEADER;

typedef struct _RGNDATA
    {
    RGNDATAHEADER rdh;
    char Buffer[ 1 ];
    } 	RGNDATA;

#endif


extern RPC_IF_HANDLE __MIDL_itf_strmif_0138_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0138_v0_0_s_ifspec;

#ifndef __IOverlayNotify_INTERFACE_DEFINED__
#define __IOverlayNotify_INTERFACE_DEFINED__

/* interface IOverlayNotify */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IOverlayNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a0-0ad4-11ce-b03a-0020af0ba770")
    IOverlayNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPaletteChange( 
            /* [in] */ DWORD dwColors,
            /* [in] */ const PALETTEENTRY *pPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnClipChange( 
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect,
            /* [in] */ const RGNDATA *pRgnData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnColorKeyChange( 
            /* [in] */ const COLORKEY *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPositionChange( 
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOverlayNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOverlayNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOverlayNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnPaletteChange )( 
            IOverlayNotify * This,
            /* [in] */ DWORD dwColors,
            /* [in] */ const PALETTEENTRY *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE *OnClipChange )( 
            IOverlayNotify * This,
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect,
            /* [in] */ const RGNDATA *pRgnData);
        
        HRESULT ( STDMETHODCALLTYPE *OnColorKeyChange )( 
            IOverlayNotify * This,
            /* [in] */ const COLORKEY *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE *OnPositionChange )( 
            IOverlayNotify * This,
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect);
        
        END_INTERFACE
    } IOverlayNotifyVtbl;

    interface IOverlayNotify
    {
        CONST_VTBL struct IOverlayNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlayNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlayNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlayNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlayNotify_OnPaletteChange(This,dwColors,pPalette)	\
    (This)->lpVtbl -> OnPaletteChange(This,dwColors,pPalette)

#define IOverlayNotify_OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)	\
    (This)->lpVtbl -> OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)

#define IOverlayNotify_OnColorKeyChange(This,pColorKey)	\
    (This)->lpVtbl -> OnColorKeyChange(This,pColorKey)

#define IOverlayNotify_OnPositionChange(This,pSourceRect,pDestinationRect)	\
    (This)->lpVtbl -> OnPositionChange(This,pSourceRect,pDestinationRect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlayNotify_OnPaletteChange_Proxy( 
    IOverlayNotify * This,
    /* [in] */ DWORD dwColors,
    /* [in] */ const PALETTEENTRY *pPalette);


void __RPC_STUB IOverlayNotify_OnPaletteChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnClipChange_Proxy( 
    IOverlayNotify * This,
    /* [in] */ const RECT *pSourceRect,
    /* [in] */ const RECT *pDestinationRect,
    /* [in] */ const RGNDATA *pRgnData);


void __RPC_STUB IOverlayNotify_OnClipChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnColorKeyChange_Proxy( 
    IOverlayNotify * This,
    /* [in] */ const COLORKEY *pColorKey);


void __RPC_STUB IOverlayNotify_OnColorKeyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnPositionChange_Proxy( 
    IOverlayNotify * This,
    /* [in] */ const RECT *pSourceRect,
    /* [in] */ const RECT *pDestinationRect);


void __RPC_STUB IOverlayNotify_OnPositionChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlayNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0139 */
/* [local] */ 

typedef IOverlayNotify *POVERLAYNOTIFY;

#if !defined(HMONITOR_DECLARED) && !defined(HMONITOR) && (WINVER < 0x0500)
#define HMONITOR_DECLARED
#if 0
typedef HANDLE HMONITOR;

#endif
DECLARE_HANDLE(HMONITOR);
#endif


extern RPC_IF_HANDLE __MIDL_itf_strmif_0139_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0139_v0_0_s_ifspec;

#ifndef __IOverlayNotify2_INTERFACE_DEFINED__
#define __IOverlayNotify2_INTERFACE_DEFINED__

/* interface IOverlayNotify2 */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IOverlayNotify2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("680EFA10-D535-11D1-87C8-00A0C9223196")
    IOverlayNotify2 : public IOverlayNotify
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnDisplayChange( 
            HMONITOR hMonitor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayNotify2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOverlayNotify2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOverlayNotify2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOverlayNotify2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnPaletteChange )( 
            IOverlayNotify2 * This,
            /* [in] */ DWORD dwColors,
            /* [in] */ const PALETTEENTRY *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE *OnClipChange )( 
            IOverlayNotify2 * This,
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect,
            /* [in] */ const RGNDATA *pRgnData);
        
        HRESULT ( STDMETHODCALLTYPE *OnColorKeyChange )( 
            IOverlayNotify2 * This,
            /* [in] */ const COLORKEY *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE *OnPositionChange )( 
            IOverlayNotify2 * This,
            /* [in] */ const RECT *pSourceRect,
            /* [in] */ const RECT *pDestinationRect);
        
        HRESULT ( STDMETHODCALLTYPE *OnDisplayChange )( 
            IOverlayNotify2 * This,
            HMONITOR hMonitor);
        
        END_INTERFACE
    } IOverlayNotify2Vtbl;

    interface IOverlayNotify2
    {
        CONST_VTBL struct IOverlayNotify2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlayNotify2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlayNotify2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlayNotify2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlayNotify2_OnPaletteChange(This,dwColors,pPalette)	\
    (This)->lpVtbl -> OnPaletteChange(This,dwColors,pPalette)

#define IOverlayNotify2_OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)	\
    (This)->lpVtbl -> OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)

#define IOverlayNotify2_OnColorKeyChange(This,pColorKey)	\
    (This)->lpVtbl -> OnColorKeyChange(This,pColorKey)

#define IOverlayNotify2_OnPositionChange(This,pSourceRect,pDestinationRect)	\
    (This)->lpVtbl -> OnPositionChange(This,pSourceRect,pDestinationRect)


#define IOverlayNotify2_OnDisplayChange(This,hMonitor)	\
    (This)->lpVtbl -> OnDisplayChange(This,hMonitor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlayNotify2_OnDisplayChange_Proxy( 
    IOverlayNotify2 * This,
    HMONITOR hMonitor);


void __RPC_STUB IOverlayNotify2_OnDisplayChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlayNotify2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0140 */
/* [local] */ 

typedef IOverlayNotify2 *POVERLAYNOTIFY2;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0140_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0140_v0_0_s_ifspec;

#ifndef __IOverlay_INTERFACE_DEFINED__
#define __IOverlay_INTERFACE_DEFINED__

/* interface IOverlay */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IOverlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a1-0ad4-11ce-b03a-0020af0ba770")
    IOverlay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPalette( 
            /* [out] */ DWORD *pdwColors,
            /* [out] */ PALETTEENTRY **ppPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPalette( 
            /* [in] */ DWORD dwColors,
            /* [in] */ PALETTEENTRY *pPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultColorKey( 
            /* [out] */ COLORKEY *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColorKey( 
            /* [out] */ COLORKEY *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetColorKey( 
            /* [out][in] */ COLORKEY *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWindowHandle( 
            /* [out] */ HWND *pHwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetClipList( 
            /* [out] */ RECT *pSourceRect,
            /* [out] */ RECT *pDestinationRect,
            /* [out] */ RGNDATA **ppRgnData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoPosition( 
            /* [out] */ RECT *pSourceRect,
            /* [out] */ RECT *pDestinationRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IOverlayNotify *pOverlayNotify,
            /* [in] */ DWORD dwInterests) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOverlay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOverlay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOverlay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPalette )( 
            IOverlay * This,
            /* [out] */ DWORD *pdwColors,
            /* [out] */ PALETTEENTRY **ppPalette);
        
        HRESULT ( STDMETHODCALLTYPE *SetPalette )( 
            IOverlay * This,
            /* [in] */ DWORD dwColors,
            /* [in] */ PALETTEENTRY *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultColorKey )( 
            IOverlay * This,
            /* [out] */ COLORKEY *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE *GetColorKey )( 
            IOverlay * This,
            /* [out] */ COLORKEY *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE *SetColorKey )( 
            IOverlay * This,
            /* [out][in] */ COLORKEY *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE *GetWindowHandle )( 
            IOverlay * This,
            /* [out] */ HWND *pHwnd);
        
        HRESULT ( STDMETHODCALLTYPE *GetClipList )( 
            IOverlay * This,
            /* [out] */ RECT *pSourceRect,
            /* [out] */ RECT *pDestinationRect,
            /* [out] */ RGNDATA **ppRgnData);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoPosition )( 
            IOverlay * This,
            /* [out] */ RECT *pSourceRect,
            /* [out] */ RECT *pDestinationRect);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IOverlay * This,
            /* [in] */ IOverlayNotify *pOverlayNotify,
            /* [in] */ DWORD dwInterests);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IOverlay * This);
        
        END_INTERFACE
    } IOverlayVtbl;

    interface IOverlay
    {
        CONST_VTBL struct IOverlayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlay_GetPalette(This,pdwColors,ppPalette)	\
    (This)->lpVtbl -> GetPalette(This,pdwColors,ppPalette)

#define IOverlay_SetPalette(This,dwColors,pPalette)	\
    (This)->lpVtbl -> SetPalette(This,dwColors,pPalette)

#define IOverlay_GetDefaultColorKey(This,pColorKey)	\
    (This)->lpVtbl -> GetDefaultColorKey(This,pColorKey)

#define IOverlay_GetColorKey(This,pColorKey)	\
    (This)->lpVtbl -> GetColorKey(This,pColorKey)

#define IOverlay_SetColorKey(This,pColorKey)	\
    (This)->lpVtbl -> SetColorKey(This,pColorKey)

#define IOverlay_GetWindowHandle(This,pHwnd)	\
    (This)->lpVtbl -> GetWindowHandle(This,pHwnd)

#define IOverlay_GetClipList(This,pSourceRect,pDestinationRect,ppRgnData)	\
    (This)->lpVtbl -> GetClipList(This,pSourceRect,pDestinationRect,ppRgnData)

#define IOverlay_GetVideoPosition(This,pSourceRect,pDestinationRect)	\
    (This)->lpVtbl -> GetVideoPosition(This,pSourceRect,pDestinationRect)

#define IOverlay_Advise(This,pOverlayNotify,dwInterests)	\
    (This)->lpVtbl -> Advise(This,pOverlayNotify,dwInterests)

#define IOverlay_Unadvise(This)	\
    (This)->lpVtbl -> Unadvise(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlay_GetPalette_Proxy( 
    IOverlay * This,
    /* [out] */ DWORD *pdwColors,
    /* [out] */ PALETTEENTRY **ppPalette);


void __RPC_STUB IOverlay_GetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_SetPalette_Proxy( 
    IOverlay * This,
    /* [in] */ DWORD dwColors,
    /* [in] */ PALETTEENTRY *pPalette);


void __RPC_STUB IOverlay_SetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetDefaultColorKey_Proxy( 
    IOverlay * This,
    /* [out] */ COLORKEY *pColorKey);


void __RPC_STUB IOverlay_GetDefaultColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetColorKey_Proxy( 
    IOverlay * This,
    /* [out] */ COLORKEY *pColorKey);


void __RPC_STUB IOverlay_GetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_SetColorKey_Proxy( 
    IOverlay * This,
    /* [out][in] */ COLORKEY *pColorKey);


void __RPC_STUB IOverlay_SetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetWindowHandle_Proxy( 
    IOverlay * This,
    /* [out] */ HWND *pHwnd);


void __RPC_STUB IOverlay_GetWindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetClipList_Proxy( 
    IOverlay * This,
    /* [out] */ RECT *pSourceRect,
    /* [out] */ RECT *pDestinationRect,
    /* [out] */ RGNDATA **ppRgnData);


void __RPC_STUB IOverlay_GetClipList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetVideoPosition_Proxy( 
    IOverlay * This,
    /* [out] */ RECT *pSourceRect,
    /* [out] */ RECT *pDestinationRect);


void __RPC_STUB IOverlay_GetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_Advise_Proxy( 
    IOverlay * This,
    /* [in] */ IOverlayNotify *pOverlayNotify,
    /* [in] */ DWORD dwInterests);


void __RPC_STUB IOverlay_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_Unadvise_Proxy( 
    IOverlay * This);


void __RPC_STUB IOverlay_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlay_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0141 */
/* [local] */ 

typedef IOverlay *POVERLAY;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0141_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0141_v0_0_s_ifspec;

#ifndef __IMediaEventSink_INTERFACE_DEFINED__
#define __IMediaEventSink_INTERFACE_DEFINED__

/* interface IMediaEventSink */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMediaEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a2-0ad4-11ce-b03a-0020af0ba770")
    IMediaEventSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ long EventCode,
            /* [in] */ LONG_PTR EventParam1,
            /* [in] */ LONG_PTR EventParam2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaEventSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaEventSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            IMediaEventSink * This,
            /* [in] */ long EventCode,
            /* [in] */ LONG_PTR EventParam1,
            /* [in] */ LONG_PTR EventParam2);
        
        END_INTERFACE
    } IMediaEventSinkVtbl;

    interface IMediaEventSink
    {
        CONST_VTBL struct IMediaEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaEventSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaEventSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaEventSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaEventSink_Notify(This,EventCode,EventParam1,EventParam2)	\
    (This)->lpVtbl -> Notify(This,EventCode,EventParam1,EventParam2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaEventSink_Notify_Proxy( 
    IMediaEventSink * This,
    /* [in] */ long EventCode,
    /* [in] */ LONG_PTR EventParam1,
    /* [in] */ LONG_PTR EventParam2);


void __RPC_STUB IMediaEventSink_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaEventSink_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0142 */
/* [local] */ 

typedef IMediaEventSink *PMEDIAEVENTSINK;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0142_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0142_v0_0_s_ifspec;

#ifndef __IFileSourceFilter_INTERFACE_DEFINED__
#define __IFileSourceFilter_INTERFACE_DEFINED__

/* interface IFileSourceFilter */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFileSourceFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a6-0ad4-11ce-b03a-0020af0ba770")
    IFileSourceFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ LPCOLESTR pszFileName,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurFile( 
            /* [out] */ LPOLESTR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE *pmt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileSourceFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSourceFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSourceFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSourceFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Load )( 
            IFileSourceFilter * This,
            /* [in] */ LPCOLESTR pszFileName,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurFile )( 
            IFileSourceFilter * This,
            /* [out] */ LPOLESTR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE *pmt);
        
        END_INTERFACE
    } IFileSourceFilterVtbl;

    interface IFileSourceFilter
    {
        CONST_VTBL struct IFileSourceFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSourceFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileSourceFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileSourceFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileSourceFilter_Load(This,pszFileName,pmt)	\
    (This)->lpVtbl -> Load(This,pszFileName,pmt)

#define IFileSourceFilter_GetCurFile(This,ppszFileName,pmt)	\
    (This)->lpVtbl -> GetCurFile(This,ppszFileName,pmt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileSourceFilter_Load_Proxy( 
    IFileSourceFilter * This,
    /* [in] */ LPCOLESTR pszFileName,
    /* [unique][in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFileSourceFilter_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileSourceFilter_GetCurFile_Proxy( 
    IFileSourceFilter * This,
    /* [out] */ LPOLESTR *ppszFileName,
    /* [out] */ AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFileSourceFilter_GetCurFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileSourceFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0143 */
/* [local] */ 

typedef IFileSourceFilter *PFILTERFILESOURCE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0143_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0143_v0_0_s_ifspec;

#ifndef __IFileSinkFilter_INTERFACE_DEFINED__
#define __IFileSinkFilter_INTERFACE_DEFINED__

/* interface IFileSinkFilter */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFileSinkFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a2104830-7c70-11cf-8bce-00aa00a3f1a6")
    IFileSinkFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFileName( 
            /* [in] */ LPCOLESTR pszFileName,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurFile( 
            /* [out] */ LPOLESTR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE *pmt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileSinkFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSinkFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSinkFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSinkFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileName )( 
            IFileSinkFilter * This,
            /* [in] */ LPCOLESTR pszFileName,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurFile )( 
            IFileSinkFilter * This,
            /* [out] */ LPOLESTR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE *pmt);
        
        END_INTERFACE
    } IFileSinkFilterVtbl;

    interface IFileSinkFilter
    {
        CONST_VTBL struct IFileSinkFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSinkFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileSinkFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileSinkFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileSinkFilter_SetFileName(This,pszFileName,pmt)	\
    (This)->lpVtbl -> SetFileName(This,pszFileName,pmt)

#define IFileSinkFilter_GetCurFile(This,ppszFileName,pmt)	\
    (This)->lpVtbl -> GetCurFile(This,ppszFileName,pmt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileSinkFilter_SetFileName_Proxy( 
    IFileSinkFilter * This,
    /* [in] */ LPCOLESTR pszFileName,
    /* [unique][in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFileSinkFilter_SetFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileSinkFilter_GetCurFile_Proxy( 
    IFileSinkFilter * This,
    /* [out] */ LPOLESTR *ppszFileName,
    /* [out] */ AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFileSinkFilter_GetCurFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileSinkFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0144 */
/* [local] */ 

typedef IFileSinkFilter *PFILTERFILESINK;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0144_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0144_v0_0_s_ifspec;

#ifndef __IFileSinkFilter2_INTERFACE_DEFINED__
#define __IFileSinkFilter2_INTERFACE_DEFINED__

/* interface IFileSinkFilter2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFileSinkFilter2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00855B90-CE1B-11d0-BD4F-00A0C911CE86")
    IFileSinkFilter2 : public IFileSinkFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMode( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMode( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileSinkFilter2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSinkFilter2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSinkFilter2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSinkFilter2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileName )( 
            IFileSinkFilter2 * This,
            /* [in] */ LPCOLESTR pszFileName,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurFile )( 
            IFileSinkFilter2 * This,
            /* [out] */ LPOLESTR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *SetMode )( 
            IFileSinkFilter2 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetMode )( 
            IFileSinkFilter2 * This,
            /* [out] */ DWORD *pdwFlags);
        
        END_INTERFACE
    } IFileSinkFilter2Vtbl;

    interface IFileSinkFilter2
    {
        CONST_VTBL struct IFileSinkFilter2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSinkFilter2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileSinkFilter2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileSinkFilter2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileSinkFilter2_SetFileName(This,pszFileName,pmt)	\
    (This)->lpVtbl -> SetFileName(This,pszFileName,pmt)

#define IFileSinkFilter2_GetCurFile(This,ppszFileName,pmt)	\
    (This)->lpVtbl -> GetCurFile(This,ppszFileName,pmt)


#define IFileSinkFilter2_SetMode(This,dwFlags)	\
    (This)->lpVtbl -> SetMode(This,dwFlags)

#define IFileSinkFilter2_GetMode(This,pdwFlags)	\
    (This)->lpVtbl -> GetMode(This,pdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileSinkFilter2_SetMode_Proxy( 
    IFileSinkFilter2 * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IFileSinkFilter2_SetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileSinkFilter2_GetMode_Proxy( 
    IFileSinkFilter2 * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IFileSinkFilter2_GetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileSinkFilter2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0145 */
/* [local] */ 

typedef IFileSinkFilter2 *PFILESINKFILTER2;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0145_0001
    {	AM_FILE_OVERWRITE	= 0x1
    } 	AM_FILESINK_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0145_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0145_v0_0_s_ifspec;

#ifndef __IGraphBuilder_INTERFACE_DEFINED__
#define __IGraphBuilder_INTERFACE_DEFINED__

/* interface IGraphBuilder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IGraphBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868a9-0ad4-11ce-b03a-0020af0ba770")
    IGraphBuilder : public IFilterGraph
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IPin *ppinOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderFile( 
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [unique][in] */ LPCWSTR lpcwstrPlayList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddSourceFilter( 
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [unique][in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter **ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLogFile( 
            /* [in] */ DWORD_PTR hFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShouldOperationContinue( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGraphBuilder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGraphBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGraphBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddFilter )( 
            IGraphBuilder * This,
            /* [in] */ IBaseFilter *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveFilter )( 
            IGraphBuilder * This,
            /* [in] */ IBaseFilter *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *EnumFilters )( 
            IGraphBuilder * This,
            /* [out] */ IEnumFilters **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *FindFilterByName )( 
            IGraphBuilder * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *ConnectDirect )( 
            IGraphBuilder * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *Reconnect )( 
            IGraphBuilder * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IGraphBuilder * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultSyncSource )( 
            IGraphBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IGraphBuilder * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IGraphBuilder * This,
            /* [in] */ IPin *ppinOut);
        
        HRESULT ( STDMETHODCALLTYPE *RenderFile )( 
            IGraphBuilder * This,
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [unique][in] */ LPCWSTR lpcwstrPlayList);
        
        HRESULT ( STDMETHODCALLTYPE *AddSourceFilter )( 
            IGraphBuilder * This,
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [unique][in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *SetLogFile )( 
            IGraphBuilder * This,
            /* [in] */ DWORD_PTR hFile);
        
        HRESULT ( STDMETHODCALLTYPE *Abort )( 
            IGraphBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShouldOperationContinue )( 
            IGraphBuilder * This);
        
        END_INTERFACE
    } IGraphBuilderVtbl;

    interface IGraphBuilder
    {
        CONST_VTBL struct IGraphBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphBuilder_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IGraphBuilder_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IGraphBuilder_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IGraphBuilder_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IGraphBuilder_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IGraphBuilder_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IGraphBuilder_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IGraphBuilder_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)


#define IGraphBuilder_Connect(This,ppinOut,ppinIn)	\
    (This)->lpVtbl -> Connect(This,ppinOut,ppinIn)

#define IGraphBuilder_Render(This,ppinOut)	\
    (This)->lpVtbl -> Render(This,ppinOut)

#define IGraphBuilder_RenderFile(This,lpcwstrFile,lpcwstrPlayList)	\
    (This)->lpVtbl -> RenderFile(This,lpcwstrFile,lpcwstrPlayList)

#define IGraphBuilder_AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)

#define IGraphBuilder_SetLogFile(This,hFile)	\
    (This)->lpVtbl -> SetLogFile(This,hFile)

#define IGraphBuilder_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IGraphBuilder_ShouldOperationContinue(This)	\
    (This)->lpVtbl -> ShouldOperationContinue(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphBuilder_Connect_Proxy( 
    IGraphBuilder * This,
    /* [in] */ IPin *ppinOut,
    /* [in] */ IPin *ppinIn);


void __RPC_STUB IGraphBuilder_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_Render_Proxy( 
    IGraphBuilder * This,
    /* [in] */ IPin *ppinOut);


void __RPC_STUB IGraphBuilder_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_RenderFile_Proxy( 
    IGraphBuilder * This,
    /* [in] */ LPCWSTR lpcwstrFile,
    /* [unique][in] */ LPCWSTR lpcwstrPlayList);


void __RPC_STUB IGraphBuilder_RenderFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_AddSourceFilter_Proxy( 
    IGraphBuilder * This,
    /* [in] */ LPCWSTR lpcwstrFileName,
    /* [unique][in] */ LPCWSTR lpcwstrFilterName,
    /* [out] */ IBaseFilter **ppFilter);


void __RPC_STUB IGraphBuilder_AddSourceFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_SetLogFile_Proxy( 
    IGraphBuilder * This,
    /* [in] */ DWORD_PTR hFile);


void __RPC_STUB IGraphBuilder_SetLogFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_Abort_Proxy( 
    IGraphBuilder * This);


void __RPC_STUB IGraphBuilder_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_ShouldOperationContinue_Proxy( 
    IGraphBuilder * This);


void __RPC_STUB IGraphBuilder_ShouldOperationContinue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphBuilder_INTERFACE_DEFINED__ */


#ifndef __ICaptureGraphBuilder_INTERFACE_DEFINED__
#define __ICaptureGraphBuilder_INTERFACE_DEFINED__

/* interface ICaptureGraphBuilder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICaptureGraphBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bf87b6e0-8c27-11d0-b3f0-00aa003761c5")
    ICaptureGraphBuilder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFiltergraph( 
            /* [in] */ IGraphBuilder *pfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFiltergraph( 
            /* [out] */ IGraphBuilder **ppfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputFileName( 
            /* [in] */ const GUID *pType,
            /* [in] */ LPCOLESTR lpstrFile,
            /* [out] */ IBaseFilter **ppf,
            /* [out] */ IFileSinkFilter **ppSink) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE FindInterface( 
            /* [unique][in] */ const GUID *pCategory,
            /* [in] */ IBaseFilter *pf,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderStream( 
            /* [in] */ const GUID *pCategory,
            /* [in] */ IUnknown *pSource,
            /* [in] */ IBaseFilter *pfCompressor,
            /* [in] */ IBaseFilter *pfRenderer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ControlStream( 
            /* [in] */ const GUID *pCategory,
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ REFERENCE_TIME *pstart,
            /* [in] */ REFERENCE_TIME *pstop,
            /* [in] */ WORD wStartCookie,
            /* [in] */ WORD wStopCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocCapFile( 
            /* [in] */ LPCOLESTR lpstr,
            /* [in] */ DWORDLONG dwlSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyCaptureFile( 
            /* [in] */ LPOLESTR lpwstrOld,
            /* [in] */ LPOLESTR lpwstrNew,
            /* [in] */ int fAllowEscAbort,
            /* [in] */ IAMCopyCaptureFileProgress *pCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICaptureGraphBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICaptureGraphBuilder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICaptureGraphBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICaptureGraphBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFiltergraph )( 
            ICaptureGraphBuilder * This,
            /* [in] */ IGraphBuilder *pfg);
        
        HRESULT ( STDMETHODCALLTYPE *GetFiltergraph )( 
            ICaptureGraphBuilder * This,
            /* [out] */ IGraphBuilder **ppfg);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputFileName )( 
            ICaptureGraphBuilder * This,
            /* [in] */ const GUID *pType,
            /* [in] */ LPCOLESTR lpstrFile,
            /* [out] */ IBaseFilter **ppf,
            /* [out] */ IFileSinkFilter **ppSink);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *FindInterface )( 
            ICaptureGraphBuilder * This,
            /* [unique][in] */ const GUID *pCategory,
            /* [in] */ IBaseFilter *pf,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppint);
        
        HRESULT ( STDMETHODCALLTYPE *RenderStream )( 
            ICaptureGraphBuilder * This,
            /* [in] */ const GUID *pCategory,
            /* [in] */ IUnknown *pSource,
            /* [in] */ IBaseFilter *pfCompressor,
            /* [in] */ IBaseFilter *pfRenderer);
        
        HRESULT ( STDMETHODCALLTYPE *ControlStream )( 
            ICaptureGraphBuilder * This,
            /* [in] */ const GUID *pCategory,
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ REFERENCE_TIME *pstart,
            /* [in] */ REFERENCE_TIME *pstop,
            /* [in] */ WORD wStartCookie,
            /* [in] */ WORD wStopCookie);
        
        HRESULT ( STDMETHODCALLTYPE *AllocCapFile )( 
            ICaptureGraphBuilder * This,
            /* [in] */ LPCOLESTR lpstr,
            /* [in] */ DWORDLONG dwlSize);
        
        HRESULT ( STDMETHODCALLTYPE *CopyCaptureFile )( 
            ICaptureGraphBuilder * This,
            /* [in] */ LPOLESTR lpwstrOld,
            /* [in] */ LPOLESTR lpwstrNew,
            /* [in] */ int fAllowEscAbort,
            /* [in] */ IAMCopyCaptureFileProgress *pCallback);
        
        END_INTERFACE
    } ICaptureGraphBuilderVtbl;

    interface ICaptureGraphBuilder
    {
        CONST_VTBL struct ICaptureGraphBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICaptureGraphBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICaptureGraphBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICaptureGraphBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICaptureGraphBuilder_SetFiltergraph(This,pfg)	\
    (This)->lpVtbl -> SetFiltergraph(This,pfg)

#define ICaptureGraphBuilder_GetFiltergraph(This,ppfg)	\
    (This)->lpVtbl -> GetFiltergraph(This,ppfg)

#define ICaptureGraphBuilder_SetOutputFileName(This,pType,lpstrFile,ppf,ppSink)	\
    (This)->lpVtbl -> SetOutputFileName(This,pType,lpstrFile,ppf,ppSink)

#define ICaptureGraphBuilder_FindInterface(This,pCategory,pf,riid,ppint)	\
    (This)->lpVtbl -> FindInterface(This,pCategory,pf,riid,ppint)

#define ICaptureGraphBuilder_RenderStream(This,pCategory,pSource,pfCompressor,pfRenderer)	\
    (This)->lpVtbl -> RenderStream(This,pCategory,pSource,pfCompressor,pfRenderer)

#define ICaptureGraphBuilder_ControlStream(This,pCategory,pFilter,pstart,pstop,wStartCookie,wStopCookie)	\
    (This)->lpVtbl -> ControlStream(This,pCategory,pFilter,pstart,pstop,wStartCookie,wStopCookie)

#define ICaptureGraphBuilder_AllocCapFile(This,lpstr,dwlSize)	\
    (This)->lpVtbl -> AllocCapFile(This,lpstr,dwlSize)

#define ICaptureGraphBuilder_CopyCaptureFile(This,lpwstrOld,lpwstrNew,fAllowEscAbort,pCallback)	\
    (This)->lpVtbl -> CopyCaptureFile(This,lpwstrOld,lpwstrNew,fAllowEscAbort,pCallback)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_SetFiltergraph_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ IGraphBuilder *pfg);


void __RPC_STUB ICaptureGraphBuilder_SetFiltergraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_GetFiltergraph_Proxy( 
    ICaptureGraphBuilder * This,
    /* [out] */ IGraphBuilder **ppfg);


void __RPC_STUB ICaptureGraphBuilder_GetFiltergraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_SetOutputFileName_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ const GUID *pType,
    /* [in] */ LPCOLESTR lpstrFile,
    /* [out] */ IBaseFilter **ppf,
    /* [out] */ IFileSinkFilter **ppSink);


void __RPC_STUB ICaptureGraphBuilder_SetOutputFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_RemoteFindInterface_Proxy( 
    ICaptureGraphBuilder * This,
    /* [unique][in] */ const GUID *pCategory,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppint);


void __RPC_STUB ICaptureGraphBuilder_RemoteFindInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_RenderStream_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ IUnknown *pSource,
    /* [in] */ IBaseFilter *pfCompressor,
    /* [in] */ IBaseFilter *pfRenderer);


void __RPC_STUB ICaptureGraphBuilder_RenderStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_ControlStream_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ IBaseFilter *pFilter,
    /* [in] */ REFERENCE_TIME *pstart,
    /* [in] */ REFERENCE_TIME *pstop,
    /* [in] */ WORD wStartCookie,
    /* [in] */ WORD wStopCookie);


void __RPC_STUB ICaptureGraphBuilder_ControlStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_AllocCapFile_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ LPCOLESTR lpstr,
    /* [in] */ DWORDLONG dwlSize);


void __RPC_STUB ICaptureGraphBuilder_AllocCapFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_CopyCaptureFile_Proxy( 
    ICaptureGraphBuilder * This,
    /* [in] */ LPOLESTR lpwstrOld,
    /* [in] */ LPOLESTR lpwstrNew,
    /* [in] */ int fAllowEscAbort,
    /* [in] */ IAMCopyCaptureFileProgress *pCallback);


void __RPC_STUB ICaptureGraphBuilder_CopyCaptureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICaptureGraphBuilder_INTERFACE_DEFINED__ */


#ifndef __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__
#define __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__

/* interface IAMCopyCaptureFileProgress */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMCopyCaptureFileProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("670d1d20-a068-11d0-b3f0-00aa003761c5")
    IAMCopyCaptureFileProgress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Progress( 
            /* [in] */ int iProgress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMCopyCaptureFileProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMCopyCaptureFileProgress * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMCopyCaptureFileProgress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMCopyCaptureFileProgress * This);
        
        HRESULT ( STDMETHODCALLTYPE *Progress )( 
            IAMCopyCaptureFileProgress * This,
            /* [in] */ int iProgress);
        
        END_INTERFACE
    } IAMCopyCaptureFileProgressVtbl;

    interface IAMCopyCaptureFileProgress
    {
        CONST_VTBL struct IAMCopyCaptureFileProgressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMCopyCaptureFileProgress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMCopyCaptureFileProgress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMCopyCaptureFileProgress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMCopyCaptureFileProgress_Progress(This,iProgress)	\
    (This)->lpVtbl -> Progress(This,iProgress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMCopyCaptureFileProgress_Progress_Proxy( 
    IAMCopyCaptureFileProgress * This,
    /* [in] */ int iProgress);


void __RPC_STUB IAMCopyCaptureFileProgress_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMCopyCaptureFileProgress_INTERFACE_DEFINED__ */


#ifndef __ICaptureGraphBuilder2_INTERFACE_DEFINED__
#define __ICaptureGraphBuilder2_INTERFACE_DEFINED__

/* interface ICaptureGraphBuilder2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICaptureGraphBuilder2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93E5A4E0-2D50-11d2-ABFA-00A0C9C6E38D")
    ICaptureGraphBuilder2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFiltergraph( 
            /* [in] */ IGraphBuilder *pfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFiltergraph( 
            /* [out] */ IGraphBuilder **ppfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputFileName( 
            /* [in] */ const GUID *pType,
            /* [in] */ LPCOLESTR lpstrFile,
            /* [out] */ IBaseFilter **ppf,
            /* [out] */ IFileSinkFilter **ppSink) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE FindInterface( 
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IBaseFilter *pf,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderStream( 
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IUnknown *pSource,
            /* [in] */ IBaseFilter *pfCompressor,
            /* [in] */ IBaseFilter *pfRenderer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ControlStream( 
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ REFERENCE_TIME *pstart,
            /* [in] */ REFERENCE_TIME *pstop,
            /* [in] */ WORD wStartCookie,
            /* [in] */ WORD wStopCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocCapFile( 
            /* [in] */ LPCOLESTR lpstr,
            /* [in] */ DWORDLONG dwlSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyCaptureFile( 
            /* [in] */ LPOLESTR lpwstrOld,
            /* [in] */ LPOLESTR lpwstrNew,
            /* [in] */ int fAllowEscAbort,
            /* [in] */ IAMCopyCaptureFileProgress *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindPin( 
            /* [in] */ IUnknown *pSource,
            /* [in] */ PIN_DIRECTION pindir,
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ BOOL fUnconnected,
            /* [in] */ int num,
            /* [out] */ IPin **ppPin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICaptureGraphBuilder2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICaptureGraphBuilder2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICaptureGraphBuilder2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFiltergraph )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ IGraphBuilder *pfg);
        
        HRESULT ( STDMETHODCALLTYPE *GetFiltergraph )( 
            ICaptureGraphBuilder2 * This,
            /* [out] */ IGraphBuilder **ppfg);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputFileName )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ const GUID *pType,
            /* [in] */ LPCOLESTR lpstrFile,
            /* [out] */ IBaseFilter **ppf,
            /* [out] */ IFileSinkFilter **ppSink);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *FindInterface )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IBaseFilter *pf,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppint);
        
        HRESULT ( STDMETHODCALLTYPE *RenderStream )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IUnknown *pSource,
            /* [in] */ IBaseFilter *pfCompressor,
            /* [in] */ IBaseFilter *pfRenderer);
        
        HRESULT ( STDMETHODCALLTYPE *ControlStream )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ REFERENCE_TIME *pstart,
            /* [in] */ REFERENCE_TIME *pstop,
            /* [in] */ WORD wStartCookie,
            /* [in] */ WORD wStopCookie);
        
        HRESULT ( STDMETHODCALLTYPE *AllocCapFile )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ LPCOLESTR lpstr,
            /* [in] */ DWORDLONG dwlSize);
        
        HRESULT ( STDMETHODCALLTYPE *CopyCaptureFile )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ LPOLESTR lpwstrOld,
            /* [in] */ LPOLESTR lpwstrNew,
            /* [in] */ int fAllowEscAbort,
            /* [in] */ IAMCopyCaptureFileProgress *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE *FindPin )( 
            ICaptureGraphBuilder2 * This,
            /* [in] */ IUnknown *pSource,
            /* [in] */ PIN_DIRECTION pindir,
            /* [in] */ const GUID *pCategory,
            /* [in] */ const GUID *pType,
            /* [in] */ BOOL fUnconnected,
            /* [in] */ int num,
            /* [out] */ IPin **ppPin);
        
        END_INTERFACE
    } ICaptureGraphBuilder2Vtbl;

    interface ICaptureGraphBuilder2
    {
        CONST_VTBL struct ICaptureGraphBuilder2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICaptureGraphBuilder2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICaptureGraphBuilder2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICaptureGraphBuilder2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICaptureGraphBuilder2_SetFiltergraph(This,pfg)	\
    (This)->lpVtbl -> SetFiltergraph(This,pfg)

#define ICaptureGraphBuilder2_GetFiltergraph(This,ppfg)	\
    (This)->lpVtbl -> GetFiltergraph(This,ppfg)

#define ICaptureGraphBuilder2_SetOutputFileName(This,pType,lpstrFile,ppf,ppSink)	\
    (This)->lpVtbl -> SetOutputFileName(This,pType,lpstrFile,ppf,ppSink)

#define ICaptureGraphBuilder2_FindInterface(This,pCategory,pType,pf,riid,ppint)	\
    (This)->lpVtbl -> FindInterface(This,pCategory,pType,pf,riid,ppint)

#define ICaptureGraphBuilder2_RenderStream(This,pCategory,pType,pSource,pfCompressor,pfRenderer)	\
    (This)->lpVtbl -> RenderStream(This,pCategory,pType,pSource,pfCompressor,pfRenderer)

#define ICaptureGraphBuilder2_ControlStream(This,pCategory,pType,pFilter,pstart,pstop,wStartCookie,wStopCookie)	\
    (This)->lpVtbl -> ControlStream(This,pCategory,pType,pFilter,pstart,pstop,wStartCookie,wStopCookie)

#define ICaptureGraphBuilder2_AllocCapFile(This,lpstr,dwlSize)	\
    (This)->lpVtbl -> AllocCapFile(This,lpstr,dwlSize)

#define ICaptureGraphBuilder2_CopyCaptureFile(This,lpwstrOld,lpwstrNew,fAllowEscAbort,pCallback)	\
    (This)->lpVtbl -> CopyCaptureFile(This,lpwstrOld,lpwstrNew,fAllowEscAbort,pCallback)

#define ICaptureGraphBuilder2_FindPin(This,pSource,pindir,pCategory,pType,fUnconnected,num,ppPin)	\
    (This)->lpVtbl -> FindPin(This,pSource,pindir,pCategory,pType,fUnconnected,num,ppPin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_SetFiltergraph_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ IGraphBuilder *pfg);


void __RPC_STUB ICaptureGraphBuilder2_SetFiltergraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_GetFiltergraph_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [out] */ IGraphBuilder **ppfg);


void __RPC_STUB ICaptureGraphBuilder2_GetFiltergraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_SetOutputFileName_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pType,
    /* [in] */ LPCOLESTR lpstrFile,
    /* [out] */ IBaseFilter **ppf,
    /* [out] */ IFileSinkFilter **ppSink);


void __RPC_STUB ICaptureGraphBuilder2_SetOutputFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_RemoteFindInterface_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppint);


void __RPC_STUB ICaptureGraphBuilder2_RemoteFindInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_RenderStream_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ IUnknown *pSource,
    /* [in] */ IBaseFilter *pfCompressor,
    /* [in] */ IBaseFilter *pfRenderer);


void __RPC_STUB ICaptureGraphBuilder2_RenderStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_ControlStream_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ IBaseFilter *pFilter,
    /* [in] */ REFERENCE_TIME *pstart,
    /* [in] */ REFERENCE_TIME *pstop,
    /* [in] */ WORD wStartCookie,
    /* [in] */ WORD wStopCookie);


void __RPC_STUB ICaptureGraphBuilder2_ControlStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_AllocCapFile_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ LPCOLESTR lpstr,
    /* [in] */ DWORDLONG dwlSize);


void __RPC_STUB ICaptureGraphBuilder2_AllocCapFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_CopyCaptureFile_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ LPOLESTR lpwstrOld,
    /* [in] */ LPOLESTR lpwstrNew,
    /* [in] */ int fAllowEscAbort,
    /* [in] */ IAMCopyCaptureFileProgress *pCallback);


void __RPC_STUB ICaptureGraphBuilder2_CopyCaptureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_FindPin_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ IUnknown *pSource,
    /* [in] */ PIN_DIRECTION pindir,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ BOOL fUnconnected,
    /* [in] */ int num,
    /* [out] */ IPin **ppPin);


void __RPC_STUB ICaptureGraphBuilder2_FindPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICaptureGraphBuilder2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0149 */
/* [local] */ 


enum _AM_RENSDEREXFLAGS
    {	AM_RENDEREX_RENDERTOEXISTINGRENDERERS	= 0x1
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0149_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0149_v0_0_s_ifspec;

#ifndef __IFilterGraph2_INTERFACE_DEFINED__
#define __IFilterGraph2_INTERFACE_DEFINED__

/* interface IFilterGraph2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFilterGraph2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73882-c2c8-11cf-8b46-00805f6cef60")
    IFilterGraph2 : public IGraphBuilder
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddSourceFilterForMoniker( 
            /* [in] */ IMoniker *pMoniker,
            /* [in] */ IBindCtx *pCtx,
            /* [unique][in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter **ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReconnectEx( 
            /* [in] */ IPin *ppin,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderEx( 
            /* [in] */ IPin *pPinOut,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ DWORD *pvContext) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterGraph2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterGraph2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterGraph2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterGraph2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddFilter )( 
            IFilterGraph2 * This,
            /* [in] */ IBaseFilter *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveFilter )( 
            IFilterGraph2 * This,
            /* [in] */ IBaseFilter *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *EnumFilters )( 
            IFilterGraph2 * This,
            /* [out] */ IEnumFilters **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *FindFilterByName )( 
            IFilterGraph2 * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *ConnectDirect )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *Reconnect )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppin);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultSyncSource )( 
            IFilterGraph2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IPin *ppinIn);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppinOut);
        
        HRESULT ( STDMETHODCALLTYPE *RenderFile )( 
            IFilterGraph2 * This,
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [unique][in] */ LPCWSTR lpcwstrPlayList);
        
        HRESULT ( STDMETHODCALLTYPE *AddSourceFilter )( 
            IFilterGraph2 * This,
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [unique][in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *SetLogFile )( 
            IFilterGraph2 * This,
            /* [in] */ DWORD_PTR hFile);
        
        HRESULT ( STDMETHODCALLTYPE *Abort )( 
            IFilterGraph2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShouldOperationContinue )( 
            IFilterGraph2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddSourceFilterForMoniker )( 
            IFilterGraph2 * This,
            /* [in] */ IMoniker *pMoniker,
            /* [in] */ IBindCtx *pCtx,
            /* [unique][in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *ReconnectEx )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *ppin,
            /* [unique][in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *RenderEx )( 
            IFilterGraph2 * This,
            /* [in] */ IPin *pPinOut,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ DWORD *pvContext);
        
        END_INTERFACE
    } IFilterGraph2Vtbl;

    interface IFilterGraph2
    {
        CONST_VTBL struct IFilterGraph2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterGraph2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterGraph2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterGraph2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterGraph2_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IFilterGraph2_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IFilterGraph2_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IFilterGraph2_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IFilterGraph2_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IFilterGraph2_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IFilterGraph2_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IFilterGraph2_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)


#define IFilterGraph2_Connect(This,ppinOut,ppinIn)	\
    (This)->lpVtbl -> Connect(This,ppinOut,ppinIn)

#define IFilterGraph2_Render(This,ppinOut)	\
    (This)->lpVtbl -> Render(This,ppinOut)

#define IFilterGraph2_RenderFile(This,lpcwstrFile,lpcwstrPlayList)	\
    (This)->lpVtbl -> RenderFile(This,lpcwstrFile,lpcwstrPlayList)

#define IFilterGraph2_AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)

#define IFilterGraph2_SetLogFile(This,hFile)	\
    (This)->lpVtbl -> SetLogFile(This,hFile)

#define IFilterGraph2_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IFilterGraph2_ShouldOperationContinue(This)	\
    (This)->lpVtbl -> ShouldOperationContinue(This)


#define IFilterGraph2_AddSourceFilterForMoniker(This,pMoniker,pCtx,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilterForMoniker(This,pMoniker,pCtx,lpcwstrFilterName,ppFilter)

#define IFilterGraph2_ReconnectEx(This,ppin,pmt)	\
    (This)->lpVtbl -> ReconnectEx(This,ppin,pmt)

#define IFilterGraph2_RenderEx(This,pPinOut,dwFlags,pvContext)	\
    (This)->lpVtbl -> RenderEx(This,pPinOut,dwFlags,pvContext)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterGraph2_AddSourceFilterForMoniker_Proxy( 
    IFilterGraph2 * This,
    /* [in] */ IMoniker *pMoniker,
    /* [in] */ IBindCtx *pCtx,
    /* [unique][in] */ LPCWSTR lpcwstrFilterName,
    /* [out] */ IBaseFilter **ppFilter);


void __RPC_STUB IFilterGraph2_AddSourceFilterForMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph2_ReconnectEx_Proxy( 
    IFilterGraph2 * This,
    /* [in] */ IPin *ppin,
    /* [unique][in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IFilterGraph2_ReconnectEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph2_RenderEx_Proxy( 
    IFilterGraph2 * This,
    /* [in] */ IPin *pPinOut,
    /* [in] */ DWORD dwFlags,
    /* [out][in] */ DWORD *pvContext);


void __RPC_STUB IFilterGraph2_RenderEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterGraph2_INTERFACE_DEFINED__ */


#ifndef __IStreamBuilder_INTERFACE_DEFINED__
#define __IStreamBuilder_INTERFACE_DEFINED__

/* interface IStreamBuilder */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IStreamBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868bf-0ad4-11ce-b03a-0020af0ba770")
    IStreamBuilder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IPin *ppinOut,
            /* [in] */ IGraphBuilder *pGraph) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Backout( 
            /* [in] */ IPin *ppinOut,
            /* [in] */ IGraphBuilder *pGraph) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStreamBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStreamBuilder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStreamBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStreamBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IStreamBuilder * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IGraphBuilder *pGraph);
        
        HRESULT ( STDMETHODCALLTYPE *Backout )( 
            IStreamBuilder * This,
            /* [in] */ IPin *ppinOut,
            /* [in] */ IGraphBuilder *pGraph);
        
        END_INTERFACE
    } IStreamBuilderVtbl;

    interface IStreamBuilder
    {
        CONST_VTBL struct IStreamBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStreamBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStreamBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStreamBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStreamBuilder_Render(This,ppinOut,pGraph)	\
    (This)->lpVtbl -> Render(This,ppinOut,pGraph)

#define IStreamBuilder_Backout(This,ppinOut,pGraph)	\
    (This)->lpVtbl -> Backout(This,ppinOut,pGraph)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStreamBuilder_Render_Proxy( 
    IStreamBuilder * This,
    /* [in] */ IPin *ppinOut,
    /* [in] */ IGraphBuilder *pGraph);


void __RPC_STUB IStreamBuilder_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamBuilder_Backout_Proxy( 
    IStreamBuilder * This,
    /* [in] */ IPin *ppinOut,
    /* [in] */ IGraphBuilder *pGraph);


void __RPC_STUB IStreamBuilder_Backout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStreamBuilder_INTERFACE_DEFINED__ */


#ifndef __IAsyncReader_INTERFACE_DEFINED__
#define __IAsyncReader_INTERFACE_DEFINED__

/* interface IAsyncReader */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAsyncReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868aa-0ad4-11ce-b03a-0020af0ba770")
    IAsyncReader : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RequestAllocator( 
            /* [in] */ IMemAllocator *pPreferred,
            /* [in] */ ALLOCATOR_PROPERTIES *pProps,
            /* [out] */ IMemAllocator **ppActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Request( 
            /* [in] */ IMediaSample *pSample,
            /* [in] */ DWORD_PTR dwUser) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForNext( 
            /* [in] */ DWORD dwTimeout,
            /* [out] */ IMediaSample **ppSample,
            /* [out] */ DWORD_PTR *pdwUser) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncReadAligned( 
            /* [in] */ IMediaSample *pSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncRead( 
            /* [in] */ LONGLONG llPosition,
            /* [in] */ LONG lLength,
            /* [size_is][out] */ BYTE *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Length( 
            /* [out] */ LONGLONG *pTotal,
            /* [out] */ LONGLONG *pAvailable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAsyncReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAsyncReader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAsyncReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAsyncReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *RequestAllocator )( 
            IAsyncReader * This,
            /* [in] */ IMemAllocator *pPreferred,
            /* [in] */ ALLOCATOR_PROPERTIES *pProps,
            /* [out] */ IMemAllocator **ppActual);
        
        HRESULT ( STDMETHODCALLTYPE *Request )( 
            IAsyncReader * This,
            /* [in] */ IMediaSample *pSample,
            /* [in] */ DWORD_PTR dwUser);
        
        HRESULT ( STDMETHODCALLTYPE *WaitForNext )( 
            IAsyncReader * This,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ IMediaSample **ppSample,
            /* [out] */ DWORD_PTR *pdwUser);
        
        HRESULT ( STDMETHODCALLTYPE *SyncReadAligned )( 
            IAsyncReader * This,
            /* [in] */ IMediaSample *pSample);
        
        HRESULT ( STDMETHODCALLTYPE *SyncRead )( 
            IAsyncReader * This,
            /* [in] */ LONGLONG llPosition,
            /* [in] */ LONG lLength,
            /* [size_is][out] */ BYTE *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *Length )( 
            IAsyncReader * This,
            /* [out] */ LONGLONG *pTotal,
            /* [out] */ LONGLONG *pAvailable);
        
        HRESULT ( STDMETHODCALLTYPE *BeginFlush )( 
            IAsyncReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *EndFlush )( 
            IAsyncReader * This);
        
        END_INTERFACE
    } IAsyncReaderVtbl;

    interface IAsyncReader
    {
        CONST_VTBL struct IAsyncReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsyncReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAsyncReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAsyncReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAsyncReader_RequestAllocator(This,pPreferred,pProps,ppActual)	\
    (This)->lpVtbl -> RequestAllocator(This,pPreferred,pProps,ppActual)

#define IAsyncReader_Request(This,pSample,dwUser)	\
    (This)->lpVtbl -> Request(This,pSample,dwUser)

#define IAsyncReader_WaitForNext(This,dwTimeout,ppSample,pdwUser)	\
    (This)->lpVtbl -> WaitForNext(This,dwTimeout,ppSample,pdwUser)

#define IAsyncReader_SyncReadAligned(This,pSample)	\
    (This)->lpVtbl -> SyncReadAligned(This,pSample)

#define IAsyncReader_SyncRead(This,llPosition,lLength,pBuffer)	\
    (This)->lpVtbl -> SyncRead(This,llPosition,lLength,pBuffer)

#define IAsyncReader_Length(This,pTotal,pAvailable)	\
    (This)->lpVtbl -> Length(This,pTotal,pAvailable)

#define IAsyncReader_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IAsyncReader_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAsyncReader_RequestAllocator_Proxy( 
    IAsyncReader * This,
    /* [in] */ IMemAllocator *pPreferred,
    /* [in] */ ALLOCATOR_PROPERTIES *pProps,
    /* [out] */ IMemAllocator **ppActual);


void __RPC_STUB IAsyncReader_RequestAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_Request_Proxy( 
    IAsyncReader * This,
    /* [in] */ IMediaSample *pSample,
    /* [in] */ DWORD_PTR dwUser);


void __RPC_STUB IAsyncReader_Request_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_WaitForNext_Proxy( 
    IAsyncReader * This,
    /* [in] */ DWORD dwTimeout,
    /* [out] */ IMediaSample **ppSample,
    /* [out] */ DWORD_PTR *pdwUser);


void __RPC_STUB IAsyncReader_WaitForNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_SyncReadAligned_Proxy( 
    IAsyncReader * This,
    /* [in] */ IMediaSample *pSample);


void __RPC_STUB IAsyncReader_SyncReadAligned_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_SyncRead_Proxy( 
    IAsyncReader * This,
    /* [in] */ LONGLONG llPosition,
    /* [in] */ LONG lLength,
    /* [size_is][out] */ BYTE *pBuffer);


void __RPC_STUB IAsyncReader_SyncRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_Length_Proxy( 
    IAsyncReader * This,
    /* [out] */ LONGLONG *pTotal,
    /* [out] */ LONGLONG *pAvailable);


void __RPC_STUB IAsyncReader_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_BeginFlush_Proxy( 
    IAsyncReader * This);


void __RPC_STUB IAsyncReader_BeginFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_EndFlush_Proxy( 
    IAsyncReader * This);


void __RPC_STUB IAsyncReader_EndFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAsyncReader_INTERFACE_DEFINED__ */


#ifndef __IGraphVersion_INTERFACE_DEFINED__
#define __IGraphVersion_INTERFACE_DEFINED__

/* interface IGraphVersion */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IGraphVersion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868ab-0ad4-11ce-b03a-0020af0ba770")
    IGraphVersion : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryVersion( 
            LONG *pVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphVersionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGraphVersion * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGraphVersion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGraphVersion * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryVersion )( 
            IGraphVersion * This,
            LONG *pVersion);
        
        END_INTERFACE
    } IGraphVersionVtbl;

    interface IGraphVersion
    {
        CONST_VTBL struct IGraphVersionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphVersion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphVersion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphVersion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphVersion_QueryVersion(This,pVersion)	\
    (This)->lpVtbl -> QueryVersion(This,pVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphVersion_QueryVersion_Proxy( 
    IGraphVersion * This,
    LONG *pVersion);


void __RPC_STUB IGraphVersion_QueryVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphVersion_INTERFACE_DEFINED__ */


#ifndef __IResourceConsumer_INTERFACE_DEFINED__
#define __IResourceConsumer_INTERFACE_DEFINED__

/* interface IResourceConsumer */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IResourceConsumer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868ad-0ad4-11ce-b03a-0020af0ba770")
    IResourceConsumer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AcquireResource( 
            /* [in] */ LONG idResource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseResource( 
            /* [in] */ LONG idResource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceConsumerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResourceConsumer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResourceConsumer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResourceConsumer * This);
        
        HRESULT ( STDMETHODCALLTYPE *AcquireResource )( 
            IResourceConsumer * This,
            /* [in] */ LONG idResource);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseResource )( 
            IResourceConsumer * This,
            /* [in] */ LONG idResource);
        
        END_INTERFACE
    } IResourceConsumerVtbl;

    interface IResourceConsumer
    {
        CONST_VTBL struct IResourceConsumerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceConsumer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceConsumer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceConsumer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceConsumer_AcquireResource(This,idResource)	\
    (This)->lpVtbl -> AcquireResource(This,idResource)

#define IResourceConsumer_ReleaseResource(This,idResource)	\
    (This)->lpVtbl -> ReleaseResource(This,idResource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResourceConsumer_AcquireResource_Proxy( 
    IResourceConsumer * This,
    /* [in] */ LONG idResource);


void __RPC_STUB IResourceConsumer_AcquireResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceConsumer_ReleaseResource_Proxy( 
    IResourceConsumer * This,
    /* [in] */ LONG idResource);


void __RPC_STUB IResourceConsumer_ReleaseResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceConsumer_INTERFACE_DEFINED__ */


#ifndef __IResourceManager_INTERFACE_DEFINED__
#define __IResourceManager_INTERFACE_DEFINED__

/* interface IResourceManager */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IResourceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868ac-0ad4-11ce-b03a-0020af0ba770")
    IResourceManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ LPCWSTR pName,
            /* [in] */ LONG cResource,
            /* [out] */ LONG *plToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterGroup( 
            /* [in] */ LPCWSTR pName,
            /* [in] */ LONG cResource,
            /* [size_is][in] */ LONG *palTokens,
            /* [out] */ LONG *plToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestResource( 
            /* [in] */ LONG idResource,
            /* [in] */ IUnknown *pFocusObject,
            /* [in] */ IResourceConsumer *pConsumer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyAcquire( 
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer,
            /* [in] */ HRESULT hr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyRelease( 
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer,
            /* [in] */ BOOL bStillWant) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelRequest( 
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFocus( 
            /* [in] */ IUnknown *pFocusObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseFocus( 
            /* [in] */ IUnknown *pFocusObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResourceManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResourceManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResourceManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *Register )( 
            IResourceManager * This,
            /* [in] */ LPCWSTR pName,
            /* [in] */ LONG cResource,
            /* [out] */ LONG *plToken);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterGroup )( 
            IResourceManager * This,
            /* [in] */ LPCWSTR pName,
            /* [in] */ LONG cResource,
            /* [size_is][in] */ LONG *palTokens,
            /* [out] */ LONG *plToken);
        
        HRESULT ( STDMETHODCALLTYPE *RequestResource )( 
            IResourceManager * This,
            /* [in] */ LONG idResource,
            /* [in] */ IUnknown *pFocusObject,
            /* [in] */ IResourceConsumer *pConsumer);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyAcquire )( 
            IResourceManager * This,
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyRelease )( 
            IResourceManager * This,
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer,
            /* [in] */ BOOL bStillWant);
        
        HRESULT ( STDMETHODCALLTYPE *CancelRequest )( 
            IResourceManager * This,
            /* [in] */ LONG idResource,
            /* [in] */ IResourceConsumer *pConsumer);
        
        HRESULT ( STDMETHODCALLTYPE *SetFocus )( 
            IResourceManager * This,
            /* [in] */ IUnknown *pFocusObject);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseFocus )( 
            IResourceManager * This,
            /* [in] */ IUnknown *pFocusObject);
        
        END_INTERFACE
    } IResourceManagerVtbl;

    interface IResourceManager
    {
        CONST_VTBL struct IResourceManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceManager_Register(This,pName,cResource,plToken)	\
    (This)->lpVtbl -> Register(This,pName,cResource,plToken)

#define IResourceManager_RegisterGroup(This,pName,cResource,palTokens,plToken)	\
    (This)->lpVtbl -> RegisterGroup(This,pName,cResource,palTokens,plToken)

#define IResourceManager_RequestResource(This,idResource,pFocusObject,pConsumer)	\
    (This)->lpVtbl -> RequestResource(This,idResource,pFocusObject,pConsumer)

#define IResourceManager_NotifyAcquire(This,idResource,pConsumer,hr)	\
    (This)->lpVtbl -> NotifyAcquire(This,idResource,pConsumer,hr)

#define IResourceManager_NotifyRelease(This,idResource,pConsumer,bStillWant)	\
    (This)->lpVtbl -> NotifyRelease(This,idResource,pConsumer,bStillWant)

#define IResourceManager_CancelRequest(This,idResource,pConsumer)	\
    (This)->lpVtbl -> CancelRequest(This,idResource,pConsumer)

#define IResourceManager_SetFocus(This,pFocusObject)	\
    (This)->lpVtbl -> SetFocus(This,pFocusObject)

#define IResourceManager_ReleaseFocus(This,pFocusObject)	\
    (This)->lpVtbl -> ReleaseFocus(This,pFocusObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResourceManager_Register_Proxy( 
    IResourceManager * This,
    /* [in] */ LPCWSTR pName,
    /* [in] */ LONG cResource,
    /* [out] */ LONG *plToken);


void __RPC_STUB IResourceManager_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_RegisterGroup_Proxy( 
    IResourceManager * This,
    /* [in] */ LPCWSTR pName,
    /* [in] */ LONG cResource,
    /* [size_is][in] */ LONG *palTokens,
    /* [out] */ LONG *plToken);


void __RPC_STUB IResourceManager_RegisterGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_RequestResource_Proxy( 
    IResourceManager * This,
    /* [in] */ LONG idResource,
    /* [in] */ IUnknown *pFocusObject,
    /* [in] */ IResourceConsumer *pConsumer);


void __RPC_STUB IResourceManager_RequestResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_NotifyAcquire_Proxy( 
    IResourceManager * This,
    /* [in] */ LONG idResource,
    /* [in] */ IResourceConsumer *pConsumer,
    /* [in] */ HRESULT hr);


void __RPC_STUB IResourceManager_NotifyAcquire_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_NotifyRelease_Proxy( 
    IResourceManager * This,
    /* [in] */ LONG idResource,
    /* [in] */ IResourceConsumer *pConsumer,
    /* [in] */ BOOL bStillWant);


void __RPC_STUB IResourceManager_NotifyRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_CancelRequest_Proxy( 
    IResourceManager * This,
    /* [in] */ LONG idResource,
    /* [in] */ IResourceConsumer *pConsumer);


void __RPC_STUB IResourceManager_CancelRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_SetFocus_Proxy( 
    IResourceManager * This,
    /* [in] */ IUnknown *pFocusObject);


void __RPC_STUB IResourceManager_SetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_ReleaseFocus_Proxy( 
    IResourceManager * This,
    /* [in] */ IUnknown *pFocusObject);


void __RPC_STUB IResourceManager_ReleaseFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceManager_INTERFACE_DEFINED__ */


#ifndef __IDistributorNotify_INTERFACE_DEFINED__
#define __IDistributorNotify_INTERFACE_DEFINED__

/* interface IDistributorNotify */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDistributorNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868af-0ad4-11ce-b03a-0020af0ba770")
    IDistributorNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( 
            REFERENCE_TIME tStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncSource( 
            /* [in] */ IReferenceClock *pClock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyGraphChange( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDistributorNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDistributorNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDistributorNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDistributorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IDistributorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IDistributorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IDistributorNotify * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE *SetSyncSource )( 
            IDistributorNotify * This,
            /* [in] */ IReferenceClock *pClock);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyGraphChange )( 
            IDistributorNotify * This);
        
        END_INTERFACE
    } IDistributorNotifyVtbl;

    interface IDistributorNotify
    {
        CONST_VTBL struct IDistributorNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributorNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDistributorNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDistributorNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDistributorNotify_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IDistributorNotify_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IDistributorNotify_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IDistributorNotify_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IDistributorNotify_NotifyGraphChange(This)	\
    (This)->lpVtbl -> NotifyGraphChange(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDistributorNotify_Stop_Proxy( 
    IDistributorNotify * This);


void __RPC_STUB IDistributorNotify_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_Pause_Proxy( 
    IDistributorNotify * This);


void __RPC_STUB IDistributorNotify_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_Run_Proxy( 
    IDistributorNotify * This,
    REFERENCE_TIME tStart);


void __RPC_STUB IDistributorNotify_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_SetSyncSource_Proxy( 
    IDistributorNotify * This,
    /* [in] */ IReferenceClock *pClock);


void __RPC_STUB IDistributorNotify_SetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_NotifyGraphChange_Proxy( 
    IDistributorNotify * This);


void __RPC_STUB IDistributorNotify_NotifyGraphChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDistributorNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0156 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0156_0001
    {	AM_STREAM_INFO_START_DEFINED	= 0x1,
	AM_STREAM_INFO_STOP_DEFINED	= 0x2,
	AM_STREAM_INFO_DISCARDING	= 0x4,
	AM_STREAM_INFO_STOP_SEND_EXTRA	= 0x10
    } 	AM_STREAM_INFO_FLAGS;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_strmif_0156_0002
    {
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD dwStartCookie;
    DWORD dwStopCookie;
    DWORD dwFlags;
    } 	AM_STREAM_INFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0156_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0156_v0_0_s_ifspec;

#ifndef __IAMStreamControl_INTERFACE_DEFINED__
#define __IAMStreamControl_INTERFACE_DEFINED__

/* interface IAMStreamControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMStreamControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73881-c2c8-11cf-8b46-00805f6cef60")
    IAMStreamControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartAt( 
            /* [in] */ const REFERENCE_TIME *ptStart,
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAt( 
            /* [in] */ const REFERENCE_TIME *ptStop,
            /* [in] */ BOOL bSendExtra,
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ AM_STREAM_INFO *pInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMStreamControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMStreamControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMStreamControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMStreamControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartAt )( 
            IAMStreamControl * This,
            /* [in] */ const REFERENCE_TIME *ptStart,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *StopAt )( 
            IAMStreamControl * This,
            /* [in] */ const REFERENCE_TIME *ptStop,
            /* [in] */ BOOL bSendExtra,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            IAMStreamControl * This,
            /* [out] */ AM_STREAM_INFO *pInfo);
        
        END_INTERFACE
    } IAMStreamControlVtbl;

    interface IAMStreamControl
    {
        CONST_VTBL struct IAMStreamControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMStreamControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMStreamControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMStreamControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMStreamControl_StartAt(This,ptStart,dwCookie)	\
    (This)->lpVtbl -> StartAt(This,ptStart,dwCookie)

#define IAMStreamControl_StopAt(This,ptStop,bSendExtra,dwCookie)	\
    (This)->lpVtbl -> StopAt(This,ptStop,bSendExtra,dwCookie)

#define IAMStreamControl_GetInfo(This,pInfo)	\
    (This)->lpVtbl -> GetInfo(This,pInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMStreamControl_StartAt_Proxy( 
    IAMStreamControl * This,
    /* [in] */ const REFERENCE_TIME *ptStart,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IAMStreamControl_StartAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamControl_StopAt_Proxy( 
    IAMStreamControl * This,
    /* [in] */ const REFERENCE_TIME *ptStop,
    /* [in] */ BOOL bSendExtra,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IAMStreamControl_StopAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamControl_GetInfo_Proxy( 
    IAMStreamControl * This,
    /* [out] */ AM_STREAM_INFO *pInfo);


void __RPC_STUB IAMStreamControl_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMStreamControl_INTERFACE_DEFINED__ */


#ifndef __ISeekingPassThru_INTERFACE_DEFINED__
#define __ISeekingPassThru_INTERFACE_DEFINED__

/* interface ISeekingPassThru */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISeekingPassThru;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b73883-c2c8-11cf-8b46-00805f6cef60")
    ISeekingPassThru : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BOOL bSupportRendering,
            /* [in] */ IPin *pPin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISeekingPassThruVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISeekingPassThru * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISeekingPassThru * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISeekingPassThru * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISeekingPassThru * This,
            /* [in] */ BOOL bSupportRendering,
            /* [in] */ IPin *pPin);
        
        END_INTERFACE
    } ISeekingPassThruVtbl;

    interface ISeekingPassThru
    {
        CONST_VTBL struct ISeekingPassThruVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISeekingPassThru_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISeekingPassThru_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISeekingPassThru_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISeekingPassThru_Init(This,bSupportRendering,pPin)	\
    (This)->lpVtbl -> Init(This,bSupportRendering,pPin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISeekingPassThru_Init_Proxy( 
    ISeekingPassThru * This,
    /* [in] */ BOOL bSupportRendering,
    /* [in] */ IPin *pPin);


void __RPC_STUB ISeekingPassThru_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISeekingPassThru_INTERFACE_DEFINED__ */


#ifndef __IAMStreamConfig_INTERFACE_DEFINED__
#define __IAMStreamConfig_INTERFACE_DEFINED__

/* interface IAMStreamConfig */
/* [unique][uuid][object] */ 

typedef struct _VIDEO_STREAM_CONFIG_CAPS
    {
    GUID guid;
    ULONG VideoStandard;
    SIZE InputSize;
    SIZE MinCroppingSize;
    SIZE MaxCroppingSize;
    int CropGranularityX;
    int CropGranularityY;
    int CropAlignX;
    int CropAlignY;
    SIZE MinOutputSize;
    SIZE MaxOutputSize;
    int OutputGranularityX;
    int OutputGranularityY;
    int StretchTapsX;
    int StretchTapsY;
    int ShrinkTapsX;
    int ShrinkTapsY;
    LONGLONG MinFrameInterval;
    LONGLONG MaxFrameInterval;
    LONG MinBitsPerSecond;
    LONG MaxBitsPerSecond;
    } 	VIDEO_STREAM_CONFIG_CAPS;

typedef struct _AUDIO_STREAM_CONFIG_CAPS
    {
    GUID guid;
    ULONG MinimumChannels;
    ULONG MaximumChannels;
    ULONG ChannelsGranularity;
    ULONG MinimumBitsPerSample;
    ULONG MaximumBitsPerSample;
    ULONG BitsPerSampleGranularity;
    ULONG MinimumSampleFrequency;
    ULONG MaximumSampleFrequency;
    ULONG SampleFrequencyGranularity;
    } 	AUDIO_STREAM_CONFIG_CAPS;


EXTERN_C const IID IID_IAMStreamConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13340-30AC-11d0-A18C-00A0C9118956")
    IAMStreamConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [out] */ AM_MEDIA_TYPE **ppmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfCapabilities( 
            /* [out] */ int *piCount,
            /* [out] */ int *piSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamCaps( 
            /* [in] */ int iIndex,
            /* [out] */ AM_MEDIA_TYPE **ppmt,
            /* [out] */ BYTE *pSCC) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMStreamConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMStreamConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMStreamConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMStreamConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFormat )( 
            IAMStreamConfig * This,
            /* [in] */ AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IAMStreamConfig * This,
            /* [out] */ AM_MEDIA_TYPE **ppmt);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfCapabilities )( 
            IAMStreamConfig * This,
            /* [out] */ int *piCount,
            /* [out] */ int *piSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetStreamCaps )( 
            IAMStreamConfig * This,
            /* [in] */ int iIndex,
            /* [out] */ AM_MEDIA_TYPE **ppmt,
            /* [out] */ BYTE *pSCC);
        
        END_INTERFACE
    } IAMStreamConfigVtbl;

    interface IAMStreamConfig
    {
        CONST_VTBL struct IAMStreamConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMStreamConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMStreamConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMStreamConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMStreamConfig_SetFormat(This,pmt)	\
    (This)->lpVtbl -> SetFormat(This,pmt)

#define IAMStreamConfig_GetFormat(This,ppmt)	\
    (This)->lpVtbl -> GetFormat(This,ppmt)

#define IAMStreamConfig_GetNumberOfCapabilities(This,piCount,piSize)	\
    (This)->lpVtbl -> GetNumberOfCapabilities(This,piCount,piSize)

#define IAMStreamConfig_GetStreamCaps(This,iIndex,ppmt,pSCC)	\
    (This)->lpVtbl -> GetStreamCaps(This,iIndex,ppmt,pSCC)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMStreamConfig_SetFormat_Proxy( 
    IAMStreamConfig * This,
    /* [in] */ AM_MEDIA_TYPE *pmt);


void __RPC_STUB IAMStreamConfig_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamConfig_GetFormat_Proxy( 
    IAMStreamConfig * This,
    /* [out] */ AM_MEDIA_TYPE **ppmt);


void __RPC_STUB IAMStreamConfig_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamConfig_GetNumberOfCapabilities_Proxy( 
    IAMStreamConfig * This,
    /* [out] */ int *piCount,
    /* [out] */ int *piSize);


void __RPC_STUB IAMStreamConfig_GetNumberOfCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamConfig_GetStreamCaps_Proxy( 
    IAMStreamConfig * This,
    /* [in] */ int iIndex,
    /* [out] */ AM_MEDIA_TYPE **ppmt,
    /* [out] */ BYTE *pSCC);


void __RPC_STUB IAMStreamConfig_GetStreamCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMStreamConfig_INTERFACE_DEFINED__ */


#ifndef __IConfigInterleaving_INTERFACE_DEFINED__
#define __IConfigInterleaving_INTERFACE_DEFINED__

/* interface IConfigInterleaving */
/* [unique][uuid][object] */ 

typedef /* [public][public][public] */ 
enum __MIDL_IConfigInterleaving_0001
    {	INTERLEAVE_NONE	= 0,
	INTERLEAVE_CAPTURE	= INTERLEAVE_NONE + 1,
	INTERLEAVE_FULL	= INTERLEAVE_CAPTURE + 1,
	INTERLEAVE_NONE_BUFFERED	= INTERLEAVE_FULL + 1
    } 	InterleavingMode;


EXTERN_C const IID IID_IConfigInterleaving;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BEE3D220-157B-11d0-BD23-00A0C911CE86")
    IConfigInterleaving : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ InterleavingMode mode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [out] */ InterleavingMode *pMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Interleaving( 
            /* [in] */ const REFERENCE_TIME *prtInterleave,
            /* [in] */ const REFERENCE_TIME *prtPreroll) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Interleaving( 
            /* [out] */ REFERENCE_TIME *prtInterleave,
            /* [out] */ REFERENCE_TIME *prtPreroll) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigInterleavingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigInterleaving * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigInterleaving * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigInterleaving * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IConfigInterleaving * This,
            /* [in] */ InterleavingMode mode);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IConfigInterleaving * This,
            /* [out] */ InterleavingMode *pMode);
        
        HRESULT ( STDMETHODCALLTYPE *put_Interleaving )( 
            IConfigInterleaving * This,
            /* [in] */ const REFERENCE_TIME *prtInterleave,
            /* [in] */ const REFERENCE_TIME *prtPreroll);
        
        HRESULT ( STDMETHODCALLTYPE *get_Interleaving )( 
            IConfigInterleaving * This,
            /* [out] */ REFERENCE_TIME *prtInterleave,
            /* [out] */ REFERENCE_TIME *prtPreroll);
        
        END_INTERFACE
    } IConfigInterleavingVtbl;

    interface IConfigInterleaving
    {
        CONST_VTBL struct IConfigInterleavingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigInterleaving_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigInterleaving_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigInterleaving_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigInterleaving_put_Mode(This,mode)	\
    (This)->lpVtbl -> put_Mode(This,mode)

#define IConfigInterleaving_get_Mode(This,pMode)	\
    (This)->lpVtbl -> get_Mode(This,pMode)

#define IConfigInterleaving_put_Interleaving(This,prtInterleave,prtPreroll)	\
    (This)->lpVtbl -> put_Interleaving(This,prtInterleave,prtPreroll)

#define IConfigInterleaving_get_Interleaving(This,prtInterleave,prtPreroll)	\
    (This)->lpVtbl -> get_Interleaving(This,prtInterleave,prtPreroll)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IConfigInterleaving_put_Mode_Proxy( 
    IConfigInterleaving * This,
    /* [in] */ InterleavingMode mode);


void __RPC_STUB IConfigInterleaving_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigInterleaving_get_Mode_Proxy( 
    IConfigInterleaving * This,
    /* [out] */ InterleavingMode *pMode);


void __RPC_STUB IConfigInterleaving_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigInterleaving_put_Interleaving_Proxy( 
    IConfigInterleaving * This,
    /* [in] */ const REFERENCE_TIME *prtInterleave,
    /* [in] */ const REFERENCE_TIME *prtPreroll);


void __RPC_STUB IConfigInterleaving_put_Interleaving_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigInterleaving_get_Interleaving_Proxy( 
    IConfigInterleaving * This,
    /* [out] */ REFERENCE_TIME *prtInterleave,
    /* [out] */ REFERENCE_TIME *prtPreroll);


void __RPC_STUB IConfigInterleaving_get_Interleaving_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigInterleaving_INTERFACE_DEFINED__ */


#ifndef __IConfigAviMux_INTERFACE_DEFINED__
#define __IConfigAviMux_INTERFACE_DEFINED__

/* interface IConfigAviMux */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IConfigAviMux;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5ACD6AA0-F482-11ce-8B67-00AA00A3F1A6")
    IConfigAviMux : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMasterStream( 
            /* [in] */ LONG iStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMasterStream( 
            /* [out] */ LONG *pStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputCompatibilityIndex( 
            /* [in] */ BOOL fOldIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputCompatibilityIndex( 
            /* [out] */ BOOL *pfOldIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigAviMuxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigAviMux * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigAviMux * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigAviMux * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMasterStream )( 
            IConfigAviMux * This,
            /* [in] */ LONG iStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetMasterStream )( 
            IConfigAviMux * This,
            /* [out] */ LONG *pStream);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputCompatibilityIndex )( 
            IConfigAviMux * This,
            /* [in] */ BOOL fOldIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutputCompatibilityIndex )( 
            IConfigAviMux * This,
            /* [out] */ BOOL *pfOldIndex);
        
        END_INTERFACE
    } IConfigAviMuxVtbl;

    interface IConfigAviMux
    {
        CONST_VTBL struct IConfigAviMuxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigAviMux_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigAviMux_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigAviMux_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigAviMux_SetMasterStream(This,iStream)	\
    (This)->lpVtbl -> SetMasterStream(This,iStream)

#define IConfigAviMux_GetMasterStream(This,pStream)	\
    (This)->lpVtbl -> GetMasterStream(This,pStream)

#define IConfigAviMux_SetOutputCompatibilityIndex(This,fOldIndex)	\
    (This)->lpVtbl -> SetOutputCompatibilityIndex(This,fOldIndex)

#define IConfigAviMux_GetOutputCompatibilityIndex(This,pfOldIndex)	\
    (This)->lpVtbl -> GetOutputCompatibilityIndex(This,pfOldIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IConfigAviMux_SetMasterStream_Proxy( 
    IConfigAviMux * This,
    /* [in] */ LONG iStream);


void __RPC_STUB IConfigAviMux_SetMasterStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAviMux_GetMasterStream_Proxy( 
    IConfigAviMux * This,
    /* [out] */ LONG *pStream);


void __RPC_STUB IConfigAviMux_GetMasterStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAviMux_SetOutputCompatibilityIndex_Proxy( 
    IConfigAviMux * This,
    /* [in] */ BOOL fOldIndex);


void __RPC_STUB IConfigAviMux_SetOutputCompatibilityIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAviMux_GetOutputCompatibilityIndex_Proxy( 
    IConfigAviMux * This,
    /* [out] */ BOOL *pfOldIndex);


void __RPC_STUB IConfigAviMux_GetOutputCompatibilityIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigAviMux_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0163 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0163_0001
    {	CompressionCaps_CanQuality	= 0x1,
	CompressionCaps_CanCrunch	= 0x2,
	CompressionCaps_CanKeyFrame	= 0x4,
	CompressionCaps_CanBFrame	= 0x8,
	CompressionCaps_CanWindow	= 0x10
    } 	CompressionCaps;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0163_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0163_v0_0_s_ifspec;

#ifndef __IAMVideoCompression_INTERFACE_DEFINED__
#define __IAMVideoCompression_INTERFACE_DEFINED__

/* interface IAMVideoCompression */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMVideoCompression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13343-30AC-11d0-A18C-00A0C9118956")
    IAMVideoCompression : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_KeyFrameRate( 
            /* [in] */ long KeyFrameRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_KeyFrameRate( 
            /* [out] */ long *pKeyFrameRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_PFramesPerKeyFrame( 
            /* [in] */ long PFramesPerKeyFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_PFramesPerKeyFrame( 
            /* [out] */ long *pPFramesPerKeyFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Quality( 
            /* [in] */ double Quality) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Quality( 
            /* [out] */ double *pQuality) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_WindowSize( 
            /* [in] */ DWORDLONG WindowSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_WindowSize( 
            /* [out] */ DWORDLONG *pWindowSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [size_is][out] */ WCHAR *pszVersion,
            /* [out][in] */ int *pcbVersion,
            /* [size_is][out] */ LPWSTR pszDescription,
            /* [out][in] */ int *pcbDescription,
            /* [out] */ long *pDefaultKeyFrameRate,
            /* [out] */ long *pDefaultPFramesPerKey,
            /* [out] */ double *pDefaultQuality,
            /* [out] */ long *pCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OverrideKeyFrame( 
            /* [in] */ long FrameNumber) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OverrideFrameSize( 
            /* [in] */ long FrameNumber,
            /* [in] */ long Size) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoCompressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoCompression * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoCompression * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoCompression * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_KeyFrameRate )( 
            IAMVideoCompression * This,
            /* [in] */ long KeyFrameRate);
        
        HRESULT ( STDMETHODCALLTYPE *get_KeyFrameRate )( 
            IAMVideoCompression * This,
            /* [out] */ long *pKeyFrameRate);
        
        HRESULT ( STDMETHODCALLTYPE *put_PFramesPerKeyFrame )( 
            IAMVideoCompression * This,
            /* [in] */ long PFramesPerKeyFrame);
        
        HRESULT ( STDMETHODCALLTYPE *get_PFramesPerKeyFrame )( 
            IAMVideoCompression * This,
            /* [out] */ long *pPFramesPerKeyFrame);
        
        HRESULT ( STDMETHODCALLTYPE *put_Quality )( 
            IAMVideoCompression * This,
            /* [in] */ double Quality);
        
        HRESULT ( STDMETHODCALLTYPE *get_Quality )( 
            IAMVideoCompression * This,
            /* [out] */ double *pQuality);
        
        HRESULT ( STDMETHODCALLTYPE *put_WindowSize )( 
            IAMVideoCompression * This,
            /* [in] */ DWORDLONG WindowSize);
        
        HRESULT ( STDMETHODCALLTYPE *get_WindowSize )( 
            IAMVideoCompression * This,
            /* [out] */ DWORDLONG *pWindowSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            IAMVideoCompression * This,
            /* [size_is][out] */ WCHAR *pszVersion,
            /* [out][in] */ int *pcbVersion,
            /* [size_is][out] */ LPWSTR pszDescription,
            /* [out][in] */ int *pcbDescription,
            /* [out] */ long *pDefaultKeyFrameRate,
            /* [out] */ long *pDefaultPFramesPerKey,
            /* [out] */ double *pDefaultQuality,
            /* [out] */ long *pCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *OverrideKeyFrame )( 
            IAMVideoCompression * This,
            /* [in] */ long FrameNumber);
        
        HRESULT ( STDMETHODCALLTYPE *OverrideFrameSize )( 
            IAMVideoCompression * This,
            /* [in] */ long FrameNumber,
            /* [in] */ long Size);
        
        END_INTERFACE
    } IAMVideoCompressionVtbl;

    interface IAMVideoCompression
    {
        CONST_VTBL struct IAMVideoCompressionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoCompression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoCompression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoCompression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoCompression_put_KeyFrameRate(This,KeyFrameRate)	\
    (This)->lpVtbl -> put_KeyFrameRate(This,KeyFrameRate)

#define IAMVideoCompression_get_KeyFrameRate(This,pKeyFrameRate)	\
    (This)->lpVtbl -> get_KeyFrameRate(This,pKeyFrameRate)

#define IAMVideoCompression_put_PFramesPerKeyFrame(This,PFramesPerKeyFrame)	\
    (This)->lpVtbl -> put_PFramesPerKeyFrame(This,PFramesPerKeyFrame)

#define IAMVideoCompression_get_PFramesPerKeyFrame(This,pPFramesPerKeyFrame)	\
    (This)->lpVtbl -> get_PFramesPerKeyFrame(This,pPFramesPerKeyFrame)

#define IAMVideoCompression_put_Quality(This,Quality)	\
    (This)->lpVtbl -> put_Quality(This,Quality)

#define IAMVideoCompression_get_Quality(This,pQuality)	\
    (This)->lpVtbl -> get_Quality(This,pQuality)

#define IAMVideoCompression_put_WindowSize(This,WindowSize)	\
    (This)->lpVtbl -> put_WindowSize(This,WindowSize)

#define IAMVideoCompression_get_WindowSize(This,pWindowSize)	\
    (This)->lpVtbl -> get_WindowSize(This,pWindowSize)

#define IAMVideoCompression_GetInfo(This,pszVersion,pcbVersion,pszDescription,pcbDescription,pDefaultKeyFrameRate,pDefaultPFramesPerKey,pDefaultQuality,pCapabilities)	\
    (This)->lpVtbl -> GetInfo(This,pszVersion,pcbVersion,pszDescription,pcbDescription,pDefaultKeyFrameRate,pDefaultPFramesPerKey,pDefaultQuality,pCapabilities)

#define IAMVideoCompression_OverrideKeyFrame(This,FrameNumber)	\
    (This)->lpVtbl -> OverrideKeyFrame(This,FrameNumber)

#define IAMVideoCompression_OverrideFrameSize(This,FrameNumber,Size)	\
    (This)->lpVtbl -> OverrideFrameSize(This,FrameNumber,Size)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoCompression_put_KeyFrameRate_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ long KeyFrameRate);


void __RPC_STUB IAMVideoCompression_put_KeyFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_get_KeyFrameRate_Proxy( 
    IAMVideoCompression * This,
    /* [out] */ long *pKeyFrameRate);


void __RPC_STUB IAMVideoCompression_get_KeyFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_put_PFramesPerKeyFrame_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ long PFramesPerKeyFrame);


void __RPC_STUB IAMVideoCompression_put_PFramesPerKeyFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_get_PFramesPerKeyFrame_Proxy( 
    IAMVideoCompression * This,
    /* [out] */ long *pPFramesPerKeyFrame);


void __RPC_STUB IAMVideoCompression_get_PFramesPerKeyFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_put_Quality_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ double Quality);


void __RPC_STUB IAMVideoCompression_put_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_get_Quality_Proxy( 
    IAMVideoCompression * This,
    /* [out] */ double *pQuality);


void __RPC_STUB IAMVideoCompression_get_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_put_WindowSize_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ DWORDLONG WindowSize);


void __RPC_STUB IAMVideoCompression_put_WindowSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_get_WindowSize_Proxy( 
    IAMVideoCompression * This,
    /* [out] */ DWORDLONG *pWindowSize);


void __RPC_STUB IAMVideoCompression_get_WindowSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_GetInfo_Proxy( 
    IAMVideoCompression * This,
    /* [size_is][out] */ WCHAR *pszVersion,
    /* [out][in] */ int *pcbVersion,
    /* [size_is][out] */ LPWSTR pszDescription,
    /* [out][in] */ int *pcbDescription,
    /* [out] */ long *pDefaultKeyFrameRate,
    /* [out] */ long *pDefaultPFramesPerKey,
    /* [out] */ double *pDefaultQuality,
    /* [out] */ long *pCapabilities);


void __RPC_STUB IAMVideoCompression_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_OverrideKeyFrame_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ long FrameNumber);


void __RPC_STUB IAMVideoCompression_OverrideKeyFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoCompression_OverrideFrameSize_Proxy( 
    IAMVideoCompression * This,
    /* [in] */ long FrameNumber,
    /* [in] */ long Size);


void __RPC_STUB IAMVideoCompression_OverrideFrameSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoCompression_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0164 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0164_0001
    {	VfwCaptureDialog_Source	= 0x1,
	VfwCaptureDialog_Format	= 0x2,
	VfwCaptureDialog_Display	= 0x4
    } 	VfwCaptureDialogs;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0164_0002
    {	VfwCompressDialog_Config	= 0x1,
	VfwCompressDialog_About	= 0x2,
	VfwCompressDialog_QueryConfig	= 0x4,
	VfwCompressDialog_QueryAbout	= 0x8
    } 	VfwCompressDialogs;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0164_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0164_v0_0_s_ifspec;

#ifndef __IAMVfwCaptureDialogs_INTERFACE_DEFINED__
#define __IAMVfwCaptureDialogs_INTERFACE_DEFINED__

/* interface IAMVfwCaptureDialogs */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMVfwCaptureDialogs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8D715A0-6E5E-11D0-B3F0-00AA003761C5")
    IAMVfwCaptureDialogs : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HasDialog( 
            /* [in] */ int iDialog) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowDialog( 
            /* [in] */ int iDialog,
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDriverMessage( 
            /* [in] */ int iDialog,
            /* [in] */ int uMsg,
            /* [in] */ long dw1,
            /* [in] */ long dw2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVfwCaptureDialogsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVfwCaptureDialogs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVfwCaptureDialogs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVfwCaptureDialogs * This);
        
        HRESULT ( STDMETHODCALLTYPE *HasDialog )( 
            IAMVfwCaptureDialogs * This,
            /* [in] */ int iDialog);
        
        HRESULT ( STDMETHODCALLTYPE *ShowDialog )( 
            IAMVfwCaptureDialogs * This,
            /* [in] */ int iDialog,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *SendDriverMessage )( 
            IAMVfwCaptureDialogs * This,
            /* [in] */ int iDialog,
            /* [in] */ int uMsg,
            /* [in] */ long dw1,
            /* [in] */ long dw2);
        
        END_INTERFACE
    } IAMVfwCaptureDialogsVtbl;

    interface IAMVfwCaptureDialogs
    {
        CONST_VTBL struct IAMVfwCaptureDialogsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVfwCaptureDialogs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVfwCaptureDialogs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVfwCaptureDialogs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVfwCaptureDialogs_HasDialog(This,iDialog)	\
    (This)->lpVtbl -> HasDialog(This,iDialog)

#define IAMVfwCaptureDialogs_ShowDialog(This,iDialog,hwnd)	\
    (This)->lpVtbl -> ShowDialog(This,iDialog,hwnd)

#define IAMVfwCaptureDialogs_SendDriverMessage(This,iDialog,uMsg,dw1,dw2)	\
    (This)->lpVtbl -> SendDriverMessage(This,iDialog,uMsg,dw1,dw2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVfwCaptureDialogs_HasDialog_Proxy( 
    IAMVfwCaptureDialogs * This,
    /* [in] */ int iDialog);


void __RPC_STUB IAMVfwCaptureDialogs_HasDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVfwCaptureDialogs_ShowDialog_Proxy( 
    IAMVfwCaptureDialogs * This,
    /* [in] */ int iDialog,
    /* [in] */ HWND hwnd);


void __RPC_STUB IAMVfwCaptureDialogs_ShowDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVfwCaptureDialogs_SendDriverMessage_Proxy( 
    IAMVfwCaptureDialogs * This,
    /* [in] */ int iDialog,
    /* [in] */ int uMsg,
    /* [in] */ long dw1,
    /* [in] */ long dw2);


void __RPC_STUB IAMVfwCaptureDialogs_SendDriverMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVfwCaptureDialogs_INTERFACE_DEFINED__ */


#ifndef __IAMVfwCompressDialogs_INTERFACE_DEFINED__
#define __IAMVfwCompressDialogs_INTERFACE_DEFINED__

/* interface IAMVfwCompressDialogs */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMVfwCompressDialogs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8D715A3-6E5E-11D0-B3F0-00AA003761C5")
    IAMVfwCompressDialogs : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShowDialog( 
            /* [in] */ int iDialog,
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [size_is][out] */ LPVOID pState,
            /* [out][in] */ int *pcbState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetState( 
            /* [size_is][in] */ LPVOID pState,
            /* [in] */ int cbState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDriverMessage( 
            /* [in] */ int uMsg,
            /* [in] */ long dw1,
            /* [in] */ long dw2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVfwCompressDialogsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVfwCompressDialogs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVfwCompressDialogs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVfwCompressDialogs * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShowDialog )( 
            IAMVfwCompressDialogs * This,
            /* [in] */ int iDialog,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IAMVfwCompressDialogs * This,
            /* [size_is][out] */ LPVOID pState,
            /* [out][in] */ int *pcbState);
        
        HRESULT ( STDMETHODCALLTYPE *SetState )( 
            IAMVfwCompressDialogs * This,
            /* [size_is][in] */ LPVOID pState,
            /* [in] */ int cbState);
        
        HRESULT ( STDMETHODCALLTYPE *SendDriverMessage )( 
            IAMVfwCompressDialogs * This,
            /* [in] */ int uMsg,
            /* [in] */ long dw1,
            /* [in] */ long dw2);
        
        END_INTERFACE
    } IAMVfwCompressDialogsVtbl;

    interface IAMVfwCompressDialogs
    {
        CONST_VTBL struct IAMVfwCompressDialogsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVfwCompressDialogs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVfwCompressDialogs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVfwCompressDialogs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVfwCompressDialogs_ShowDialog(This,iDialog,hwnd)	\
    (This)->lpVtbl -> ShowDialog(This,iDialog,hwnd)

#define IAMVfwCompressDialogs_GetState(This,pState,pcbState)	\
    (This)->lpVtbl -> GetState(This,pState,pcbState)

#define IAMVfwCompressDialogs_SetState(This,pState,cbState)	\
    (This)->lpVtbl -> SetState(This,pState,cbState)

#define IAMVfwCompressDialogs_SendDriverMessage(This,uMsg,dw1,dw2)	\
    (This)->lpVtbl -> SendDriverMessage(This,uMsg,dw1,dw2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVfwCompressDialogs_ShowDialog_Proxy( 
    IAMVfwCompressDialogs * This,
    /* [in] */ int iDialog,
    /* [in] */ HWND hwnd);


void __RPC_STUB IAMVfwCompressDialogs_ShowDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVfwCompressDialogs_GetState_Proxy( 
    IAMVfwCompressDialogs * This,
    /* [size_is][out] */ LPVOID pState,
    /* [out][in] */ int *pcbState);


void __RPC_STUB IAMVfwCompressDialogs_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVfwCompressDialogs_SetState_Proxy( 
    IAMVfwCompressDialogs * This,
    /* [size_is][in] */ LPVOID pState,
    /* [in] */ int cbState);


void __RPC_STUB IAMVfwCompressDialogs_SetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVfwCompressDialogs_SendDriverMessage_Proxy( 
    IAMVfwCompressDialogs * This,
    /* [in] */ int uMsg,
    /* [in] */ long dw1,
    /* [in] */ long dw2);


void __RPC_STUB IAMVfwCompressDialogs_SendDriverMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVfwCompressDialogs_INTERFACE_DEFINED__ */


#ifndef __IAMDroppedFrames_INTERFACE_DEFINED__
#define __IAMDroppedFrames_INTERFACE_DEFINED__

/* interface IAMDroppedFrames */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMDroppedFrames;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13344-30AC-11d0-A18C-00A0C9118956")
    IAMDroppedFrames : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNumDropped( 
            /* [out] */ long *plDropped) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumNotDropped( 
            /* [out] */ long *plNotDropped) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDroppedInfo( 
            /* [in] */ long lSize,
            /* [out] */ long *plArray,
            /* [out] */ long *plNumCopied) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAverageFrameSize( 
            /* [out] */ long *plAverageSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDroppedFramesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMDroppedFrames * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMDroppedFrames * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMDroppedFrames * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumDropped )( 
            IAMDroppedFrames * This,
            /* [out] */ long *plDropped);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumNotDropped )( 
            IAMDroppedFrames * This,
            /* [out] */ long *plNotDropped);
        
        HRESULT ( STDMETHODCALLTYPE *GetDroppedInfo )( 
            IAMDroppedFrames * This,
            /* [in] */ long lSize,
            /* [out] */ long *plArray,
            /* [out] */ long *plNumCopied);
        
        HRESULT ( STDMETHODCALLTYPE *GetAverageFrameSize )( 
            IAMDroppedFrames * This,
            /* [out] */ long *plAverageSize);
        
        END_INTERFACE
    } IAMDroppedFramesVtbl;

    interface IAMDroppedFrames
    {
        CONST_VTBL struct IAMDroppedFramesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDroppedFrames_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDroppedFrames_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDroppedFrames_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDroppedFrames_GetNumDropped(This,plDropped)	\
    (This)->lpVtbl -> GetNumDropped(This,plDropped)

#define IAMDroppedFrames_GetNumNotDropped(This,plNotDropped)	\
    (This)->lpVtbl -> GetNumNotDropped(This,plNotDropped)

#define IAMDroppedFrames_GetDroppedInfo(This,lSize,plArray,plNumCopied)	\
    (This)->lpVtbl -> GetDroppedInfo(This,lSize,plArray,plNumCopied)

#define IAMDroppedFrames_GetAverageFrameSize(This,plAverageSize)	\
    (This)->lpVtbl -> GetAverageFrameSize(This,plAverageSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDroppedFrames_GetNumDropped_Proxy( 
    IAMDroppedFrames * This,
    /* [out] */ long *plDropped);


void __RPC_STUB IAMDroppedFrames_GetNumDropped_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDroppedFrames_GetNumNotDropped_Proxy( 
    IAMDroppedFrames * This,
    /* [out] */ long *plNotDropped);


void __RPC_STUB IAMDroppedFrames_GetNumNotDropped_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDroppedFrames_GetDroppedInfo_Proxy( 
    IAMDroppedFrames * This,
    /* [in] */ long lSize,
    /* [out] */ long *plArray,
    /* [out] */ long *plNumCopied);


void __RPC_STUB IAMDroppedFrames_GetDroppedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDroppedFrames_GetAverageFrameSize_Proxy( 
    IAMDroppedFrames * This,
    /* [out] */ long *plAverageSize);


void __RPC_STUB IAMDroppedFrames_GetAverageFrameSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDroppedFrames_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0167 */
/* [local] */ 

#define AMF_AUTOMATICGAIN -1.0


extern RPC_IF_HANDLE __MIDL_itf_strmif_0167_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0167_v0_0_s_ifspec;

#ifndef __IAMAudioInputMixer_INTERFACE_DEFINED__
#define __IAMAudioInputMixer_INTERFACE_DEFINED__

/* interface IAMAudioInputMixer */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMAudioInputMixer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54C39221-8380-11d0-B3F0-00AA003761C5")
    IAMAudioInputMixer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_Enable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Enable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Mono( 
            /* [in] */ BOOL fMono) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Mono( 
            /* [out] */ BOOL *pfMono) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_MixLevel( 
            /* [in] */ double Level) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MixLevel( 
            /* [out] */ double *pLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Pan( 
            /* [in] */ double Pan) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Pan( 
            /* [out] */ double *pPan) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Loudness( 
            /* [in] */ BOOL fLoudness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Loudness( 
            /* [out] */ BOOL *pfLoudness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Treble( 
            /* [in] */ double Treble) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Treble( 
            /* [out] */ double *pTreble) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TrebleRange( 
            /* [out] */ double *pRange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Bass( 
            /* [in] */ double Bass) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Bass( 
            /* [out] */ double *pBass) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_BassRange( 
            /* [out] */ double *pRange) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMAudioInputMixerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMAudioInputMixer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMAudioInputMixer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMAudioInputMixer * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_Enable )( 
            IAMAudioInputMixer * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *get_Enable )( 
            IAMAudioInputMixer * This,
            /* [out] */ BOOL *pfEnable);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mono )( 
            IAMAudioInputMixer * This,
            /* [in] */ BOOL fMono);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mono )( 
            IAMAudioInputMixer * This,
            /* [out] */ BOOL *pfMono);
        
        HRESULT ( STDMETHODCALLTYPE *put_MixLevel )( 
            IAMAudioInputMixer * This,
            /* [in] */ double Level);
        
        HRESULT ( STDMETHODCALLTYPE *get_MixLevel )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pLevel);
        
        HRESULT ( STDMETHODCALLTYPE *put_Pan )( 
            IAMAudioInputMixer * This,
            /* [in] */ double Pan);
        
        HRESULT ( STDMETHODCALLTYPE *get_Pan )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pPan);
        
        HRESULT ( STDMETHODCALLTYPE *put_Loudness )( 
            IAMAudioInputMixer * This,
            /* [in] */ BOOL fLoudness);
        
        HRESULT ( STDMETHODCALLTYPE *get_Loudness )( 
            IAMAudioInputMixer * This,
            /* [out] */ BOOL *pfLoudness);
        
        HRESULT ( STDMETHODCALLTYPE *put_Treble )( 
            IAMAudioInputMixer * This,
            /* [in] */ double Treble);
        
        HRESULT ( STDMETHODCALLTYPE *get_Treble )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pTreble);
        
        HRESULT ( STDMETHODCALLTYPE *get_TrebleRange )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pRange);
        
        HRESULT ( STDMETHODCALLTYPE *put_Bass )( 
            IAMAudioInputMixer * This,
            /* [in] */ double Bass);
        
        HRESULT ( STDMETHODCALLTYPE *get_Bass )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pBass);
        
        HRESULT ( STDMETHODCALLTYPE *get_BassRange )( 
            IAMAudioInputMixer * This,
            /* [out] */ double *pRange);
        
        END_INTERFACE
    } IAMAudioInputMixerVtbl;

    interface IAMAudioInputMixer
    {
        CONST_VTBL struct IAMAudioInputMixerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMAudioInputMixer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMAudioInputMixer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMAudioInputMixer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMAudioInputMixer_put_Enable(This,fEnable)	\
    (This)->lpVtbl -> put_Enable(This,fEnable)

#define IAMAudioInputMixer_get_Enable(This,pfEnable)	\
    (This)->lpVtbl -> get_Enable(This,pfEnable)

#define IAMAudioInputMixer_put_Mono(This,fMono)	\
    (This)->lpVtbl -> put_Mono(This,fMono)

#define IAMAudioInputMixer_get_Mono(This,pfMono)	\
    (This)->lpVtbl -> get_Mono(This,pfMono)

#define IAMAudioInputMixer_put_MixLevel(This,Level)	\
    (This)->lpVtbl -> put_MixLevel(This,Level)

#define IAMAudioInputMixer_get_MixLevel(This,pLevel)	\
    (This)->lpVtbl -> get_MixLevel(This,pLevel)

#define IAMAudioInputMixer_put_Pan(This,Pan)	\
    (This)->lpVtbl -> put_Pan(This,Pan)

#define IAMAudioInputMixer_get_Pan(This,pPan)	\
    (This)->lpVtbl -> get_Pan(This,pPan)

#define IAMAudioInputMixer_put_Loudness(This,fLoudness)	\
    (This)->lpVtbl -> put_Loudness(This,fLoudness)

#define IAMAudioInputMixer_get_Loudness(This,pfLoudness)	\
    (This)->lpVtbl -> get_Loudness(This,pfLoudness)

#define IAMAudioInputMixer_put_Treble(This,Treble)	\
    (This)->lpVtbl -> put_Treble(This,Treble)

#define IAMAudioInputMixer_get_Treble(This,pTreble)	\
    (This)->lpVtbl -> get_Treble(This,pTreble)

#define IAMAudioInputMixer_get_TrebleRange(This,pRange)	\
    (This)->lpVtbl -> get_TrebleRange(This,pRange)

#define IAMAudioInputMixer_put_Bass(This,Bass)	\
    (This)->lpVtbl -> put_Bass(This,Bass)

#define IAMAudioInputMixer_get_Bass(This,pBass)	\
    (This)->lpVtbl -> get_Bass(This,pBass)

#define IAMAudioInputMixer_get_BassRange(This,pRange)	\
    (This)->lpVtbl -> get_BassRange(This,pRange)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Enable_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IAMAudioInputMixer_put_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Enable_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IAMAudioInputMixer_get_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Mono_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ BOOL fMono);


void __RPC_STUB IAMAudioInputMixer_put_Mono_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Mono_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ BOOL *pfMono);


void __RPC_STUB IAMAudioInputMixer_get_Mono_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_MixLevel_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ double Level);


void __RPC_STUB IAMAudioInputMixer_put_MixLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_MixLevel_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pLevel);


void __RPC_STUB IAMAudioInputMixer_get_MixLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Pan_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ double Pan);


void __RPC_STUB IAMAudioInputMixer_put_Pan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Pan_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pPan);


void __RPC_STUB IAMAudioInputMixer_get_Pan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Loudness_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ BOOL fLoudness);


void __RPC_STUB IAMAudioInputMixer_put_Loudness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Loudness_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ BOOL *pfLoudness);


void __RPC_STUB IAMAudioInputMixer_get_Loudness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Treble_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ double Treble);


void __RPC_STUB IAMAudioInputMixer_put_Treble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Treble_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pTreble);


void __RPC_STUB IAMAudioInputMixer_get_Treble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_TrebleRange_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pRange);


void __RPC_STUB IAMAudioInputMixer_get_TrebleRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_put_Bass_Proxy( 
    IAMAudioInputMixer * This,
    /* [in] */ double Bass);


void __RPC_STUB IAMAudioInputMixer_put_Bass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_Bass_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pBass);


void __RPC_STUB IAMAudioInputMixer_get_Bass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAudioInputMixer_get_BassRange_Proxy( 
    IAMAudioInputMixer * This,
    /* [out] */ double *pRange);


void __RPC_STUB IAMAudioInputMixer_get_BassRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMAudioInputMixer_INTERFACE_DEFINED__ */


#ifndef __IAMBufferNegotiation_INTERFACE_DEFINED__
#define __IAMBufferNegotiation_INTERFACE_DEFINED__

/* interface IAMBufferNegotiation */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMBufferNegotiation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56ED71A0-AF5F-11D0-B3F0-00AA003761C5")
    IAMBufferNegotiation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SuggestAllocatorProperties( 
            /* [in] */ const ALLOCATOR_PROPERTIES *pprop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllocatorProperties( 
            /* [out] */ ALLOCATOR_PROPERTIES *pprop) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMBufferNegotiationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMBufferNegotiation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMBufferNegotiation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMBufferNegotiation * This);
        
        HRESULT ( STDMETHODCALLTYPE *SuggestAllocatorProperties )( 
            IAMBufferNegotiation * This,
            /* [in] */ const ALLOCATOR_PROPERTIES *pprop);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllocatorProperties )( 
            IAMBufferNegotiation * This,
            /* [out] */ ALLOCATOR_PROPERTIES *pprop);
        
        END_INTERFACE
    } IAMBufferNegotiationVtbl;

    interface IAMBufferNegotiation
    {
        CONST_VTBL struct IAMBufferNegotiationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMBufferNegotiation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMBufferNegotiation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMBufferNegotiation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMBufferNegotiation_SuggestAllocatorProperties(This,pprop)	\
    (This)->lpVtbl -> SuggestAllocatorProperties(This,pprop)

#define IAMBufferNegotiation_GetAllocatorProperties(This,pprop)	\
    (This)->lpVtbl -> GetAllocatorProperties(This,pprop)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMBufferNegotiation_SuggestAllocatorProperties_Proxy( 
    IAMBufferNegotiation * This,
    /* [in] */ const ALLOCATOR_PROPERTIES *pprop);


void __RPC_STUB IAMBufferNegotiation_SuggestAllocatorProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMBufferNegotiation_GetAllocatorProperties_Proxy( 
    IAMBufferNegotiation * This,
    /* [out] */ ALLOCATOR_PROPERTIES *pprop);


void __RPC_STUB IAMBufferNegotiation_GetAllocatorProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMBufferNegotiation_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0169 */
/* [local] */ 

typedef 
enum tagAnalogVideoStandard
    {	AnalogVideo_None	= 0,
	AnalogVideo_NTSC_M	= 0x1,
	AnalogVideo_NTSC_M_J	= 0x2,
	AnalogVideo_NTSC_433	= 0x4,
	AnalogVideo_PAL_B	= 0x10,
	AnalogVideo_PAL_D	= 0x20,
	AnalogVideo_PAL_G	= 0x40,
	AnalogVideo_PAL_H	= 0x80,
	AnalogVideo_PAL_I	= 0x100,
	AnalogVideo_PAL_M	= 0x200,
	AnalogVideo_PAL_N	= 0x400,
	AnalogVideo_PAL_60	= 0x800,
	AnalogVideo_SECAM_B	= 0x1000,
	AnalogVideo_SECAM_D	= 0x2000,
	AnalogVideo_SECAM_G	= 0x4000,
	AnalogVideo_SECAM_H	= 0x8000,
	AnalogVideo_SECAM_K	= 0x10000,
	AnalogVideo_SECAM_K1	= 0x20000,
	AnalogVideo_SECAM_L	= 0x40000,
	AnalogVideo_SECAM_L1	= 0x80000,
	AnalogVideo_PAL_N_COMBO	= 0x100000
    } 	AnalogVideoStandard;

#define AnalogVideo_NTSC_Mask  0x00000007
#define AnalogVideo_PAL_Mask   0x00100FF0
#define AnalogVideo_SECAM_Mask 0x000FF000
typedef 
enum tagTunerInputType
    {	TunerInputCable	= 0,
	TunerInputAntenna	= TunerInputCable + 1
    } 	TunerInputType;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0169_0001
    {	VideoCopyProtectionMacrovisionBasic	= 0,
	VideoCopyProtectionMacrovisionCBI	= VideoCopyProtectionMacrovisionBasic + 1
    } 	VideoCopyProtectionType;

typedef 
enum tagPhysicalConnectorType
    {	PhysConn_Video_Tuner	= 1,
	PhysConn_Video_Composite	= PhysConn_Video_Tuner + 1,
	PhysConn_Video_SVideo	= PhysConn_Video_Composite + 1,
	PhysConn_Video_RGB	= PhysConn_Video_SVideo + 1,
	PhysConn_Video_YRYBY	= PhysConn_Video_RGB + 1,
	PhysConn_Video_SerialDigital	= PhysConn_Video_YRYBY + 1,
	PhysConn_Video_ParallelDigital	= PhysConn_Video_SerialDigital + 1,
	PhysConn_Video_SCSI	= PhysConn_Video_ParallelDigital + 1,
	PhysConn_Video_AUX	= PhysConn_Video_SCSI + 1,
	PhysConn_Video_1394	= PhysConn_Video_AUX + 1,
	PhysConn_Video_USB	= PhysConn_Video_1394 + 1,
	PhysConn_Video_VideoDecoder	= PhysConn_Video_USB + 1,
	PhysConn_Video_VideoEncoder	= PhysConn_Video_VideoDecoder + 1,
	PhysConn_Video_SCART	= PhysConn_Video_VideoEncoder + 1,
	PhysConn_Video_Black	= PhysConn_Video_SCART + 1,
	PhysConn_Audio_Tuner	= 0x1000,
	PhysConn_Audio_Line	= PhysConn_Audio_Tuner + 1,
	PhysConn_Audio_Mic	= PhysConn_Audio_Line + 1,
	PhysConn_Audio_AESDigital	= PhysConn_Audio_Mic + 1,
	PhysConn_Audio_SPDIFDigital	= PhysConn_Audio_AESDigital + 1,
	PhysConn_Audio_SCSI	= PhysConn_Audio_SPDIFDigital + 1,
	PhysConn_Audio_AUX	= PhysConn_Audio_SCSI + 1,
	PhysConn_Audio_1394	= PhysConn_Audio_AUX + 1,
	PhysConn_Audio_USB	= PhysConn_Audio_1394 + 1,
	PhysConn_Audio_AudioDecoder	= PhysConn_Audio_USB + 1
    } 	PhysicalConnectorType;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0169_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0169_v0_0_s_ifspec;

#ifndef __IAMAnalogVideoDecoder_INTERFACE_DEFINED__
#define __IAMAnalogVideoDecoder_INTERFACE_DEFINED__

/* interface IAMAnalogVideoDecoder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMAnalogVideoDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13350-30AC-11d0-A18C-00A0C9118956")
    IAMAnalogVideoDecoder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_AvailableTVFormats( 
            /* [out] */ long *lAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_TVFormat( 
            /* [in] */ long lAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TVFormat( 
            /* [out] */ long *plAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_HorizontalLocked( 
            /* [out] */ long *plLocked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VCRHorizontalLocking( 
            /* [in] */ long lVCRHorizontalLocking) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VCRHorizontalLocking( 
            /* [out] */ long *plVCRHorizontalLocking) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NumberOfLines( 
            /* [out] */ long *plNumberOfLines) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_OutputEnable( 
            /* [in] */ long lOutputEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_OutputEnable( 
            /* [out] */ long *plOutputEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMAnalogVideoDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMAnalogVideoDecoder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMAnalogVideoDecoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMAnalogVideoDecoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_AvailableTVFormats )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *lAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *put_TVFormat )( 
            IAMAnalogVideoDecoder * This,
            /* [in] */ long lAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *get_TVFormat )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *plAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *get_HorizontalLocked )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *plLocked);
        
        HRESULT ( STDMETHODCALLTYPE *put_VCRHorizontalLocking )( 
            IAMAnalogVideoDecoder * This,
            /* [in] */ long lVCRHorizontalLocking);
        
        HRESULT ( STDMETHODCALLTYPE *get_VCRHorizontalLocking )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *plVCRHorizontalLocking);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumberOfLines )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *plNumberOfLines);
        
        HRESULT ( STDMETHODCALLTYPE *put_OutputEnable )( 
            IAMAnalogVideoDecoder * This,
            /* [in] */ long lOutputEnable);
        
        HRESULT ( STDMETHODCALLTYPE *get_OutputEnable )( 
            IAMAnalogVideoDecoder * This,
            /* [out] */ long *plOutputEnable);
        
        END_INTERFACE
    } IAMAnalogVideoDecoderVtbl;

    interface IAMAnalogVideoDecoder
    {
        CONST_VTBL struct IAMAnalogVideoDecoderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMAnalogVideoDecoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMAnalogVideoDecoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMAnalogVideoDecoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMAnalogVideoDecoder_get_AvailableTVFormats(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> get_AvailableTVFormats(This,lAnalogVideoStandard)

#define IAMAnalogVideoDecoder_put_TVFormat(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> put_TVFormat(This,lAnalogVideoStandard)

#define IAMAnalogVideoDecoder_get_TVFormat(This,plAnalogVideoStandard)	\
    (This)->lpVtbl -> get_TVFormat(This,plAnalogVideoStandard)

#define IAMAnalogVideoDecoder_get_HorizontalLocked(This,plLocked)	\
    (This)->lpVtbl -> get_HorizontalLocked(This,plLocked)

#define IAMAnalogVideoDecoder_put_VCRHorizontalLocking(This,lVCRHorizontalLocking)	\
    (This)->lpVtbl -> put_VCRHorizontalLocking(This,lVCRHorizontalLocking)

#define IAMAnalogVideoDecoder_get_VCRHorizontalLocking(This,plVCRHorizontalLocking)	\
    (This)->lpVtbl -> get_VCRHorizontalLocking(This,plVCRHorizontalLocking)

#define IAMAnalogVideoDecoder_get_NumberOfLines(This,plNumberOfLines)	\
    (This)->lpVtbl -> get_NumberOfLines(This,plNumberOfLines)

#define IAMAnalogVideoDecoder_put_OutputEnable(This,lOutputEnable)	\
    (This)->lpVtbl -> put_OutputEnable(This,lOutputEnable)

#define IAMAnalogVideoDecoder_get_OutputEnable(This,plOutputEnable)	\
    (This)->lpVtbl -> get_OutputEnable(This,plOutputEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_AvailableTVFormats_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *lAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoDecoder_get_AvailableTVFormats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_put_TVFormat_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [in] */ long lAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoDecoder_put_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_TVFormat_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *plAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoDecoder_get_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_HorizontalLocked_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *plLocked);


void __RPC_STUB IAMAnalogVideoDecoder_get_HorizontalLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_put_VCRHorizontalLocking_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [in] */ long lVCRHorizontalLocking);


void __RPC_STUB IAMAnalogVideoDecoder_put_VCRHorizontalLocking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_VCRHorizontalLocking_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *plVCRHorizontalLocking);


void __RPC_STUB IAMAnalogVideoDecoder_get_VCRHorizontalLocking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_NumberOfLines_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *plNumberOfLines);


void __RPC_STUB IAMAnalogVideoDecoder_get_NumberOfLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_put_OutputEnable_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [in] */ long lOutputEnable);


void __RPC_STUB IAMAnalogVideoDecoder_put_OutputEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoDecoder_get_OutputEnable_Proxy( 
    IAMAnalogVideoDecoder * This,
    /* [out] */ long *plOutputEnable);


void __RPC_STUB IAMAnalogVideoDecoder_get_OutputEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMAnalogVideoDecoder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0170 */
/* [local] */ 

typedef 
enum tagVideoProcAmpProperty
    {	VideoProcAmp_Brightness	= 0,
	VideoProcAmp_Contrast	= VideoProcAmp_Brightness + 1,
	VideoProcAmp_Hue	= VideoProcAmp_Contrast + 1,
	VideoProcAmp_Saturation	= VideoProcAmp_Hue + 1,
	VideoProcAmp_Sharpness	= VideoProcAmp_Saturation + 1,
	VideoProcAmp_Gamma	= VideoProcAmp_Sharpness + 1,
	VideoProcAmp_ColorEnable	= VideoProcAmp_Gamma + 1,
	VideoProcAmp_WhiteBalance	= VideoProcAmp_ColorEnable + 1,
	VideoProcAmp_BacklightCompensation	= VideoProcAmp_WhiteBalance + 1,
	VideoProcAmp_Gain	= VideoProcAmp_BacklightCompensation + 1
    } 	VideoProcAmpProperty;

typedef 
enum tagVideoProcAmpFlags
    {	VideoProcAmp_Flags_Auto	= 0x1,
	VideoProcAmp_Flags_Manual	= 0x2
    } 	VideoProcAmpFlags;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0170_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0170_v0_0_s_ifspec;

#ifndef __IAMVideoProcAmp_INTERFACE_DEFINED__
#define __IAMVideoProcAmp_INTERFACE_DEFINED__

/* interface IAMVideoProcAmp */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMVideoProcAmp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13360-30AC-11d0-A18C-00A0C9118956")
    IAMVideoProcAmp : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRange( 
            /* [in] */ long Property,
            /* [out] */ long *pMin,
            /* [out] */ long *pMax,
            /* [out] */ long *pSteppingDelta,
            /* [out] */ long *pDefault,
            /* [out] */ long *pCapsFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ long Property,
            /* [in] */ long lValue,
            /* [in] */ long Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ long Property,
            /* [out] */ long *lValue,
            /* [out] */ long *Flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoProcAmpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoProcAmp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoProcAmp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoProcAmp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetRange )( 
            IAMVideoProcAmp * This,
            /* [in] */ long Property,
            /* [out] */ long *pMin,
            /* [out] */ long *pMax,
            /* [out] */ long *pSteppingDelta,
            /* [out] */ long *pDefault,
            /* [out] */ long *pCapsFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Set )( 
            IAMVideoProcAmp * This,
            /* [in] */ long Property,
            /* [in] */ long lValue,
            /* [in] */ long Flags);
        
        HRESULT ( STDMETHODCALLTYPE *Get )( 
            IAMVideoProcAmp * This,
            /* [in] */ long Property,
            /* [out] */ long *lValue,
            /* [out] */ long *Flags);
        
        END_INTERFACE
    } IAMVideoProcAmpVtbl;

    interface IAMVideoProcAmp
    {
        CONST_VTBL struct IAMVideoProcAmpVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoProcAmp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoProcAmp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoProcAmp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoProcAmp_GetRange(This,Property,pMin,pMax,pSteppingDelta,pDefault,pCapsFlags)	\
    (This)->lpVtbl -> GetRange(This,Property,pMin,pMax,pSteppingDelta,pDefault,pCapsFlags)

#define IAMVideoProcAmp_Set(This,Property,lValue,Flags)	\
    (This)->lpVtbl -> Set(This,Property,lValue,Flags)

#define IAMVideoProcAmp_Get(This,Property,lValue,Flags)	\
    (This)->lpVtbl -> Get(This,Property,lValue,Flags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoProcAmp_GetRange_Proxy( 
    IAMVideoProcAmp * This,
    /* [in] */ long Property,
    /* [out] */ long *pMin,
    /* [out] */ long *pMax,
    /* [out] */ long *pSteppingDelta,
    /* [out] */ long *pDefault,
    /* [out] */ long *pCapsFlags);


void __RPC_STUB IAMVideoProcAmp_GetRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoProcAmp_Set_Proxy( 
    IAMVideoProcAmp * This,
    /* [in] */ long Property,
    /* [in] */ long lValue,
    /* [in] */ long Flags);


void __RPC_STUB IAMVideoProcAmp_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoProcAmp_Get_Proxy( 
    IAMVideoProcAmp * This,
    /* [in] */ long Property,
    /* [out] */ long *lValue,
    /* [out] */ long *Flags);


void __RPC_STUB IAMVideoProcAmp_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoProcAmp_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0171 */
/* [local] */ 

typedef 
enum tagCameraControlProperty
    {	CameraControl_Pan	= 0,
	CameraControl_Tilt	= CameraControl_Pan + 1,
	CameraControl_Roll	= CameraControl_Tilt + 1,
	CameraControl_Zoom	= CameraControl_Roll + 1,
	CameraControl_Exposure	= CameraControl_Zoom + 1,
	CameraControl_Iris	= CameraControl_Exposure + 1,
	CameraControl_Focus	= CameraControl_Iris + 1
    } 	CameraControlProperty;

typedef 
enum tagCameraControlFlags
    {	CameraControl_Flags_Auto	= 0x1,
	CameraControl_Flags_Manual	= 0x2
    } 	CameraControlFlags;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0171_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0171_v0_0_s_ifspec;

#ifndef __IAMCameraControl_INTERFACE_DEFINED__
#define __IAMCameraControl_INTERFACE_DEFINED__

/* interface IAMCameraControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMCameraControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13370-30AC-11d0-A18C-00A0C9118956")
    IAMCameraControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRange( 
            /* [in] */ long Property,
            /* [out] */ long *pMin,
            /* [out] */ long *pMax,
            /* [out] */ long *pSteppingDelta,
            /* [out] */ long *pDefault,
            /* [out] */ long *pCapsFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ long Property,
            /* [in] */ long lValue,
            /* [in] */ long Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ long Property,
            /* [out] */ long *lValue,
            /* [out] */ long *Flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMCameraControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMCameraControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMCameraControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMCameraControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetRange )( 
            IAMCameraControl * This,
            /* [in] */ long Property,
            /* [out] */ long *pMin,
            /* [out] */ long *pMax,
            /* [out] */ long *pSteppingDelta,
            /* [out] */ long *pDefault,
            /* [out] */ long *pCapsFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Set )( 
            IAMCameraControl * This,
            /* [in] */ long Property,
            /* [in] */ long lValue,
            /* [in] */ long Flags);
        
        HRESULT ( STDMETHODCALLTYPE *Get )( 
            IAMCameraControl * This,
            /* [in] */ long Property,
            /* [out] */ long *lValue,
            /* [out] */ long *Flags);
        
        END_INTERFACE
    } IAMCameraControlVtbl;

    interface IAMCameraControl
    {
        CONST_VTBL struct IAMCameraControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMCameraControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMCameraControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMCameraControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMCameraControl_GetRange(This,Property,pMin,pMax,pSteppingDelta,pDefault,pCapsFlags)	\
    (This)->lpVtbl -> GetRange(This,Property,pMin,pMax,pSteppingDelta,pDefault,pCapsFlags)

#define IAMCameraControl_Set(This,Property,lValue,Flags)	\
    (This)->lpVtbl -> Set(This,Property,lValue,Flags)

#define IAMCameraControl_Get(This,Property,lValue,Flags)	\
    (This)->lpVtbl -> Get(This,Property,lValue,Flags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMCameraControl_GetRange_Proxy( 
    IAMCameraControl * This,
    /* [in] */ long Property,
    /* [out] */ long *pMin,
    /* [out] */ long *pMax,
    /* [out] */ long *pSteppingDelta,
    /* [out] */ long *pDefault,
    /* [out] */ long *pCapsFlags);


void __RPC_STUB IAMCameraControl_GetRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCameraControl_Set_Proxy( 
    IAMCameraControl * This,
    /* [in] */ long Property,
    /* [in] */ long lValue,
    /* [in] */ long Flags);


void __RPC_STUB IAMCameraControl_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCameraControl_Get_Proxy( 
    IAMCameraControl * This,
    /* [in] */ long Property,
    /* [out] */ long *lValue,
    /* [out] */ long *Flags);


void __RPC_STUB IAMCameraControl_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMCameraControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0172 */
/* [local] */ 

typedef 
enum tagVideoControlFlags
    {	VideoControlFlag_FlipHorizontal	= 0x1,
	VideoControlFlag_FlipVertical	= 0x2,
	VideoControlFlag_ExternalTriggerEnable	= 0x4,
	VideoControlFlag_Trigger	= 0x8
    } 	VideoControlFlags;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0172_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0172_v0_0_s_ifspec;

#ifndef __IAMVideoControl_INTERFACE_DEFINED__
#define __IAMVideoControl_INTERFACE_DEFINED__

/* interface IAMVideoControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMVideoControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6a2e0670-28e4-11d0-a18c-00a0c9118956")
    IAMVideoControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCaps( 
            /* [in] */ IPin *pPin,
            /* [out] */ long *pCapsFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMode( 
            /* [in] */ IPin *pPin,
            /* [in] */ long Mode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMode( 
            /* [in] */ IPin *pPin,
            /* [out] */ long *Mode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentActualFrameRate( 
            /* [in] */ IPin *pPin,
            /* [out] */ LONGLONG *ActualFrameRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxAvailableFrameRate( 
            /* [in] */ IPin *pPin,
            /* [in] */ long iIndex,
            /* [in] */ SIZE Dimensions,
            /* [out] */ LONGLONG *MaxAvailableFrameRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameRateList( 
            /* [in] */ IPin *pPin,
            /* [in] */ long iIndex,
            /* [in] */ SIZE Dimensions,
            /* [out] */ long *ListSize,
            /* [out] */ LONGLONG **FrameRates) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [out] */ long *pCapsFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetMode )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [in] */ long Mode);
        
        HRESULT ( STDMETHODCALLTYPE *GetMode )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [out] */ long *Mode);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentActualFrameRate )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [out] */ LONGLONG *ActualFrameRate);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxAvailableFrameRate )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [in] */ long iIndex,
            /* [in] */ SIZE Dimensions,
            /* [out] */ LONGLONG *MaxAvailableFrameRate);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameRateList )( 
            IAMVideoControl * This,
            /* [in] */ IPin *pPin,
            /* [in] */ long iIndex,
            /* [in] */ SIZE Dimensions,
            /* [out] */ long *ListSize,
            /* [out] */ LONGLONG **FrameRates);
        
        END_INTERFACE
    } IAMVideoControlVtbl;

    interface IAMVideoControl
    {
        CONST_VTBL struct IAMVideoControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoControl_GetCaps(This,pPin,pCapsFlags)	\
    (This)->lpVtbl -> GetCaps(This,pPin,pCapsFlags)

#define IAMVideoControl_SetMode(This,pPin,Mode)	\
    (This)->lpVtbl -> SetMode(This,pPin,Mode)

#define IAMVideoControl_GetMode(This,pPin,Mode)	\
    (This)->lpVtbl -> GetMode(This,pPin,Mode)

#define IAMVideoControl_GetCurrentActualFrameRate(This,pPin,ActualFrameRate)	\
    (This)->lpVtbl -> GetCurrentActualFrameRate(This,pPin,ActualFrameRate)

#define IAMVideoControl_GetMaxAvailableFrameRate(This,pPin,iIndex,Dimensions,MaxAvailableFrameRate)	\
    (This)->lpVtbl -> GetMaxAvailableFrameRate(This,pPin,iIndex,Dimensions,MaxAvailableFrameRate)

#define IAMVideoControl_GetFrameRateList(This,pPin,iIndex,Dimensions,ListSize,FrameRates)	\
    (This)->lpVtbl -> GetFrameRateList(This,pPin,iIndex,Dimensions,ListSize,FrameRates)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoControl_GetCaps_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [out] */ long *pCapsFlags);


void __RPC_STUB IAMVideoControl_GetCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoControl_SetMode_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [in] */ long Mode);


void __RPC_STUB IAMVideoControl_SetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoControl_GetMode_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [out] */ long *Mode);


void __RPC_STUB IAMVideoControl_GetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoControl_GetCurrentActualFrameRate_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [out] */ LONGLONG *ActualFrameRate);


void __RPC_STUB IAMVideoControl_GetCurrentActualFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoControl_GetMaxAvailableFrameRate_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [in] */ long iIndex,
    /* [in] */ SIZE Dimensions,
    /* [out] */ LONGLONG *MaxAvailableFrameRate);


void __RPC_STUB IAMVideoControl_GetMaxAvailableFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoControl_GetFrameRateList_Proxy( 
    IAMVideoControl * This,
    /* [in] */ IPin *pPin,
    /* [in] */ long iIndex,
    /* [in] */ SIZE Dimensions,
    /* [out] */ long *ListSize,
    /* [out] */ LONGLONG **FrameRates);


void __RPC_STUB IAMVideoControl_GetFrameRateList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoControl_INTERFACE_DEFINED__ */


#ifndef __IAMCrossbar_INTERFACE_DEFINED__
#define __IAMCrossbar_INTERFACE_DEFINED__

/* interface IAMCrossbar */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMCrossbar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E13380-30AC-11d0-A18C-00A0C9118956")
    IAMCrossbar : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_PinCounts( 
            /* [out] */ long *OutputPinCount,
            /* [out] */ long *InputPinCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanRoute( 
            /* [in] */ long OutputPinIndex,
            /* [in] */ long InputPinIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Route( 
            /* [in] */ long OutputPinIndex,
            /* [in] */ long InputPinIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_IsRoutedTo( 
            /* [in] */ long OutputPinIndex,
            /* [out] */ long *InputPinIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CrossbarPinInfo( 
            /* [in] */ BOOL IsInputPin,
            /* [in] */ long PinIndex,
            /* [out] */ long *PinIndexRelated,
            /* [out] */ long *PhysicalType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMCrossbarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMCrossbar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMCrossbar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMCrossbar * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_PinCounts )( 
            IAMCrossbar * This,
            /* [out] */ long *OutputPinCount,
            /* [out] */ long *InputPinCount);
        
        HRESULT ( STDMETHODCALLTYPE *CanRoute )( 
            IAMCrossbar * This,
            /* [in] */ long OutputPinIndex,
            /* [in] */ long InputPinIndex);
        
        HRESULT ( STDMETHODCALLTYPE *Route )( 
            IAMCrossbar * This,
            /* [in] */ long OutputPinIndex,
            /* [in] */ long InputPinIndex);
        
        HRESULT ( STDMETHODCALLTYPE *get_IsRoutedTo )( 
            IAMCrossbar * This,
            /* [in] */ long OutputPinIndex,
            /* [out] */ long *InputPinIndex);
        
        HRESULT ( STDMETHODCALLTYPE *get_CrossbarPinInfo )( 
            IAMCrossbar * This,
            /* [in] */ BOOL IsInputPin,
            /* [in] */ long PinIndex,
            /* [out] */ long *PinIndexRelated,
            /* [out] */ long *PhysicalType);
        
        END_INTERFACE
    } IAMCrossbarVtbl;

    interface IAMCrossbar
    {
        CONST_VTBL struct IAMCrossbarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMCrossbar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMCrossbar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMCrossbar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMCrossbar_get_PinCounts(This,OutputPinCount,InputPinCount)	\
    (This)->lpVtbl -> get_PinCounts(This,OutputPinCount,InputPinCount)

#define IAMCrossbar_CanRoute(This,OutputPinIndex,InputPinIndex)	\
    (This)->lpVtbl -> CanRoute(This,OutputPinIndex,InputPinIndex)

#define IAMCrossbar_Route(This,OutputPinIndex,InputPinIndex)	\
    (This)->lpVtbl -> Route(This,OutputPinIndex,InputPinIndex)

#define IAMCrossbar_get_IsRoutedTo(This,OutputPinIndex,InputPinIndex)	\
    (This)->lpVtbl -> get_IsRoutedTo(This,OutputPinIndex,InputPinIndex)

#define IAMCrossbar_get_CrossbarPinInfo(This,IsInputPin,PinIndex,PinIndexRelated,PhysicalType)	\
    (This)->lpVtbl -> get_CrossbarPinInfo(This,IsInputPin,PinIndex,PinIndexRelated,PhysicalType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMCrossbar_get_PinCounts_Proxy( 
    IAMCrossbar * This,
    /* [out] */ long *OutputPinCount,
    /* [out] */ long *InputPinCount);


void __RPC_STUB IAMCrossbar_get_PinCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCrossbar_CanRoute_Proxy( 
    IAMCrossbar * This,
    /* [in] */ long OutputPinIndex,
    /* [in] */ long InputPinIndex);


void __RPC_STUB IAMCrossbar_CanRoute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCrossbar_Route_Proxy( 
    IAMCrossbar * This,
    /* [in] */ long OutputPinIndex,
    /* [in] */ long InputPinIndex);


void __RPC_STUB IAMCrossbar_Route_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCrossbar_get_IsRoutedTo_Proxy( 
    IAMCrossbar * This,
    /* [in] */ long OutputPinIndex,
    /* [out] */ long *InputPinIndex);


void __RPC_STUB IAMCrossbar_get_IsRoutedTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMCrossbar_get_CrossbarPinInfo_Proxy( 
    IAMCrossbar * This,
    /* [in] */ BOOL IsInputPin,
    /* [in] */ long PinIndex,
    /* [out] */ long *PinIndexRelated,
    /* [out] */ long *PhysicalType);


void __RPC_STUB IAMCrossbar_get_CrossbarPinInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMCrossbar_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0174 */
/* [local] */ 

typedef 
enum tagAMTunerSubChannel
    {	AMTUNER_SUBCHAN_NO_TUNE	= -2,
	AMTUNER_SUBCHAN_DEFAULT	= -1
    } 	AMTunerSubChannel;

typedef 
enum tagAMTunerSignalStrength
    {	AMTUNER_HASNOSIGNALSTRENGTH	= -1,
	AMTUNER_NOSIGNAL	= 0,
	AMTUNER_SIGNALPRESENT	= 1
    } 	AMTunerSignalStrength;

typedef 
enum tagAMTunerModeType
    {	AMTUNER_MODE_DEFAULT	= 0,
	AMTUNER_MODE_TV	= 0x1,
	AMTUNER_MODE_FM_RADIO	= 0x2,
	AMTUNER_MODE_AM_RADIO	= 0x4,
	AMTUNER_MODE_DSS	= 0x8
    } 	AMTunerModeType;

typedef 
enum tagAMTunerEventType
    {	AMTUNER_EVENT_CHANGED	= 0x1
    } 	AMTunerEventType;




extern RPC_IF_HANDLE __MIDL_itf_strmif_0174_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0174_v0_0_s_ifspec;

#ifndef __IAMTuner_INTERFACE_DEFINED__
#define __IAMTuner_INTERFACE_DEFINED__

/* interface IAMTuner */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTuner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("211A8761-03AC-11d1-8D13-00AA00BD8339")
    IAMTuner : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_Channel( 
            /* [in] */ long lChannel,
            /* [in] */ long lVideoSubChannel,
            /* [in] */ long lAudioSubChannel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Channel( 
            /* [out] */ long *plChannel,
            /* [out] */ long *plVideoSubChannel,
            /* [out] */ long *plAudioSubChannel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChannelMinMax( 
            /* [out] */ long *lChannelMin,
            /* [out] */ long *lChannelMax) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_CountryCode( 
            /* [in] */ long lCountryCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CountryCode( 
            /* [out] */ long *plCountryCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_TuningSpace( 
            /* [in] */ long lTuningSpace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TuningSpace( 
            /* [out] */ long *plTuningSpace) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Logon( 
            /* [in] */ HANDLE hCurrentUser) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Logout( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SignalPresent( 
            /* [out] */ long *plSignalStrength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ AMTunerModeType lMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [out] */ AMTunerModeType *plMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailableModes( 
            /* [out] */ long *plModes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterNotificationCallBack( 
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterNotificationCallBack( 
            /* [in] */ IAMTunerNotification *pNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTunerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTuner * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTuner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IAMTuner * This,
            /* [in] */ long lChannel,
            /* [in] */ long lVideoSubChannel,
            /* [in] */ long lAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IAMTuner * This,
            /* [out] */ long *plChannel,
            /* [out] */ long *plVideoSubChannel,
            /* [out] */ long *plAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *ChannelMinMax )( 
            IAMTuner * This,
            /* [out] */ long *lChannelMin,
            /* [out] */ long *lChannelMax);
        
        HRESULT ( STDMETHODCALLTYPE *put_CountryCode )( 
            IAMTuner * This,
            /* [in] */ long lCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *get_CountryCode )( 
            IAMTuner * This,
            /* [out] */ long *plCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *put_TuningSpace )( 
            IAMTuner * This,
            /* [in] */ long lTuningSpace);
        
        HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IAMTuner * This,
            /* [out] */ long *plTuningSpace);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Logon )( 
            IAMTuner * This,
            /* [in] */ HANDLE hCurrentUser);
        
        HRESULT ( STDMETHODCALLTYPE *Logout )( 
            IAMTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SignalPresent )( 
            IAMTuner * This,
            /* [out] */ long *plSignalStrength);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IAMTuner * This,
            /* [in] */ AMTunerModeType lMode);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IAMTuner * This,
            /* [out] */ AMTunerModeType *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableModes )( 
            IAMTuner * This,
            /* [out] */ long *plModes);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterNotificationCallBack )( 
            IAMTuner * This,
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterNotificationCallBack )( 
            IAMTuner * This,
            /* [in] */ IAMTunerNotification *pNotify);
        
        END_INTERFACE
    } IAMTunerVtbl;

    interface IAMTuner
    {
        CONST_VTBL struct IAMTunerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTuner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTuner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTuner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTuner_put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)	\
    (This)->lpVtbl -> put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)

#define IAMTuner_get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)	\
    (This)->lpVtbl -> get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)

#define IAMTuner_ChannelMinMax(This,lChannelMin,lChannelMax)	\
    (This)->lpVtbl -> ChannelMinMax(This,lChannelMin,lChannelMax)

#define IAMTuner_put_CountryCode(This,lCountryCode)	\
    (This)->lpVtbl -> put_CountryCode(This,lCountryCode)

#define IAMTuner_get_CountryCode(This,plCountryCode)	\
    (This)->lpVtbl -> get_CountryCode(This,plCountryCode)

#define IAMTuner_put_TuningSpace(This,lTuningSpace)	\
    (This)->lpVtbl -> put_TuningSpace(This,lTuningSpace)

#define IAMTuner_get_TuningSpace(This,plTuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,plTuningSpace)

#define IAMTuner_Logon(This,hCurrentUser)	\
    (This)->lpVtbl -> Logon(This,hCurrentUser)

#define IAMTuner_Logout(This)	\
    (This)->lpVtbl -> Logout(This)

#define IAMTuner_SignalPresent(This,plSignalStrength)	\
    (This)->lpVtbl -> SignalPresent(This,plSignalStrength)

#define IAMTuner_put_Mode(This,lMode)	\
    (This)->lpVtbl -> put_Mode(This,lMode)

#define IAMTuner_get_Mode(This,plMode)	\
    (This)->lpVtbl -> get_Mode(This,plMode)

#define IAMTuner_GetAvailableModes(This,plModes)	\
    (This)->lpVtbl -> GetAvailableModes(This,plModes)

#define IAMTuner_RegisterNotificationCallBack(This,pNotify,lEvents)	\
    (This)->lpVtbl -> RegisterNotificationCallBack(This,pNotify,lEvents)

#define IAMTuner_UnRegisterNotificationCallBack(This,pNotify)	\
    (This)->lpVtbl -> UnRegisterNotificationCallBack(This,pNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTuner_put_Channel_Proxy( 
    IAMTuner * This,
    /* [in] */ long lChannel,
    /* [in] */ long lVideoSubChannel,
    /* [in] */ long lAudioSubChannel);


void __RPC_STUB IAMTuner_put_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_get_Channel_Proxy( 
    IAMTuner * This,
    /* [out] */ long *plChannel,
    /* [out] */ long *plVideoSubChannel,
    /* [out] */ long *plAudioSubChannel);


void __RPC_STUB IAMTuner_get_Channel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_ChannelMinMax_Proxy( 
    IAMTuner * This,
    /* [out] */ long *lChannelMin,
    /* [out] */ long *lChannelMax);


void __RPC_STUB IAMTuner_ChannelMinMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_put_CountryCode_Proxy( 
    IAMTuner * This,
    /* [in] */ long lCountryCode);


void __RPC_STUB IAMTuner_put_CountryCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_get_CountryCode_Proxy( 
    IAMTuner * This,
    /* [out] */ long *plCountryCode);


void __RPC_STUB IAMTuner_get_CountryCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_put_TuningSpace_Proxy( 
    IAMTuner * This,
    /* [in] */ long lTuningSpace);


void __RPC_STUB IAMTuner_put_TuningSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_get_TuningSpace_Proxy( 
    IAMTuner * This,
    /* [out] */ long *plTuningSpace);


void __RPC_STUB IAMTuner_get_TuningSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IAMTuner_Logon_Proxy( 
    IAMTuner * This,
    /* [in] */ HANDLE hCurrentUser);


void __RPC_STUB IAMTuner_Logon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_Logout_Proxy( 
    IAMTuner * This);


void __RPC_STUB IAMTuner_Logout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_SignalPresent_Proxy( 
    IAMTuner * This,
    /* [out] */ long *plSignalStrength);


void __RPC_STUB IAMTuner_SignalPresent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_put_Mode_Proxy( 
    IAMTuner * This,
    /* [in] */ AMTunerModeType lMode);


void __RPC_STUB IAMTuner_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_get_Mode_Proxy( 
    IAMTuner * This,
    /* [out] */ AMTunerModeType *plMode);


void __RPC_STUB IAMTuner_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_GetAvailableModes_Proxy( 
    IAMTuner * This,
    /* [out] */ long *plModes);


void __RPC_STUB IAMTuner_GetAvailableModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_RegisterNotificationCallBack_Proxy( 
    IAMTuner * This,
    /* [in] */ IAMTunerNotification *pNotify,
    /* [in] */ long lEvents);


void __RPC_STUB IAMTuner_RegisterNotificationCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTuner_UnRegisterNotificationCallBack_Proxy( 
    IAMTuner * This,
    /* [in] */ IAMTunerNotification *pNotify);


void __RPC_STUB IAMTuner_UnRegisterNotificationCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTuner_INTERFACE_DEFINED__ */


#ifndef __IAMTunerNotification_INTERFACE_DEFINED__
#define __IAMTunerNotification_INTERFACE_DEFINED__

/* interface IAMTunerNotification */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTunerNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("211A8760-03AC-11d1-8D13-00AA00BD8339")
    IAMTunerNotification : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ AMTunerEventType Event) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTunerNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTunerNotification * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTunerNotification * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTunerNotification * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            IAMTunerNotification * This,
            /* [in] */ AMTunerEventType Event);
        
        END_INTERFACE
    } IAMTunerNotificationVtbl;

    interface IAMTunerNotification
    {
        CONST_VTBL struct IAMTunerNotificationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTunerNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTunerNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTunerNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTunerNotification_OnEvent(This,Event)	\
    (This)->lpVtbl -> OnEvent(This,Event)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTunerNotification_OnEvent_Proxy( 
    IAMTunerNotification * This,
    /* [in] */ AMTunerEventType Event);


void __RPC_STUB IAMTunerNotification_OnEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTunerNotification_INTERFACE_DEFINED__ */


#ifndef __IAMTVTuner_INTERFACE_DEFINED__
#define __IAMTVTuner_INTERFACE_DEFINED__

/* interface IAMTVTuner */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTVTuner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("211A8766-03AC-11d1-8D13-00AA00BD8339")
    IAMTVTuner : public IAMTuner
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_AvailableTVFormats( 
            /* [out] */ long *lAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TVFormat( 
            /* [out] */ long *plAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AutoTune( 
            /* [in] */ long lChannel,
            /* [out] */ long *plFoundSignal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StoreAutoTune( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NumInputConnections( 
            /* [out] */ long *plNumInputConnections) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_InputType( 
            /* [in] */ long lIndex,
            /* [in] */ TunerInputType InputType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_InputType( 
            /* [in] */ long lIndex,
            /* [out] */ TunerInputType *pInputType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_ConnectInput( 
            /* [in] */ long lIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ConnectInput( 
            /* [out] */ long *plIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VideoFrequency( 
            /* [out] */ long *lFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_AudioFrequency( 
            /* [out] */ long *lFreq) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTVTunerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTVTuner * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTVTuner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTVTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IAMTVTuner * This,
            /* [in] */ long lChannel,
            /* [in] */ long lVideoSubChannel,
            /* [in] */ long lAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IAMTVTuner * This,
            /* [out] */ long *plChannel,
            /* [out] */ long *plVideoSubChannel,
            /* [out] */ long *plAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *ChannelMinMax )( 
            IAMTVTuner * This,
            /* [out] */ long *lChannelMin,
            /* [out] */ long *lChannelMax);
        
        HRESULT ( STDMETHODCALLTYPE *put_CountryCode )( 
            IAMTVTuner * This,
            /* [in] */ long lCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *get_CountryCode )( 
            IAMTVTuner * This,
            /* [out] */ long *plCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *put_TuningSpace )( 
            IAMTVTuner * This,
            /* [in] */ long lTuningSpace);
        
        HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IAMTVTuner * This,
            /* [out] */ long *plTuningSpace);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Logon )( 
            IAMTVTuner * This,
            /* [in] */ HANDLE hCurrentUser);
        
        HRESULT ( STDMETHODCALLTYPE *Logout )( 
            IAMTVTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SignalPresent )( 
            IAMTVTuner * This,
            /* [out] */ long *plSignalStrength);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IAMTVTuner * This,
            /* [in] */ AMTunerModeType lMode);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IAMTVTuner * This,
            /* [out] */ AMTunerModeType *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableModes )( 
            IAMTVTuner * This,
            /* [out] */ long *plModes);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterNotificationCallBack )( 
            IAMTVTuner * This,
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterNotificationCallBack )( 
            IAMTVTuner * This,
            /* [in] */ IAMTunerNotification *pNotify);
        
        HRESULT ( STDMETHODCALLTYPE *get_AvailableTVFormats )( 
            IAMTVTuner * This,
            /* [out] */ long *lAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *get_TVFormat )( 
            IAMTVTuner * This,
            /* [out] */ long *plAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *AutoTune )( 
            IAMTVTuner * This,
            /* [in] */ long lChannel,
            /* [out] */ long *plFoundSignal);
        
        HRESULT ( STDMETHODCALLTYPE *StoreAutoTune )( 
            IAMTVTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumInputConnections )( 
            IAMTVTuner * This,
            /* [out] */ long *plNumInputConnections);
        
        HRESULT ( STDMETHODCALLTYPE *put_InputType )( 
            IAMTVTuner * This,
            /* [in] */ long lIndex,
            /* [in] */ TunerInputType InputType);
        
        HRESULT ( STDMETHODCALLTYPE *get_InputType )( 
            IAMTVTuner * This,
            /* [in] */ long lIndex,
            /* [out] */ TunerInputType *pInputType);
        
        HRESULT ( STDMETHODCALLTYPE *put_ConnectInput )( 
            IAMTVTuner * This,
            /* [in] */ long lIndex);
        
        HRESULT ( STDMETHODCALLTYPE *get_ConnectInput )( 
            IAMTVTuner * This,
            /* [out] */ long *plIndex);
        
        HRESULT ( STDMETHODCALLTYPE *get_VideoFrequency )( 
            IAMTVTuner * This,
            /* [out] */ long *lFreq);
        
        HRESULT ( STDMETHODCALLTYPE *get_AudioFrequency )( 
            IAMTVTuner * This,
            /* [out] */ long *lFreq);
        
        END_INTERFACE
    } IAMTVTunerVtbl;

    interface IAMTVTuner
    {
        CONST_VTBL struct IAMTVTunerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTVTuner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTVTuner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTVTuner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTVTuner_put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)	\
    (This)->lpVtbl -> put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)

#define IAMTVTuner_get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)	\
    (This)->lpVtbl -> get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)

#define IAMTVTuner_ChannelMinMax(This,lChannelMin,lChannelMax)	\
    (This)->lpVtbl -> ChannelMinMax(This,lChannelMin,lChannelMax)

#define IAMTVTuner_put_CountryCode(This,lCountryCode)	\
    (This)->lpVtbl -> put_CountryCode(This,lCountryCode)

#define IAMTVTuner_get_CountryCode(This,plCountryCode)	\
    (This)->lpVtbl -> get_CountryCode(This,plCountryCode)

#define IAMTVTuner_put_TuningSpace(This,lTuningSpace)	\
    (This)->lpVtbl -> put_TuningSpace(This,lTuningSpace)

#define IAMTVTuner_get_TuningSpace(This,plTuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,plTuningSpace)

#define IAMTVTuner_Logon(This,hCurrentUser)	\
    (This)->lpVtbl -> Logon(This,hCurrentUser)

#define IAMTVTuner_Logout(This)	\
    (This)->lpVtbl -> Logout(This)

#define IAMTVTuner_SignalPresent(This,plSignalStrength)	\
    (This)->lpVtbl -> SignalPresent(This,plSignalStrength)

#define IAMTVTuner_put_Mode(This,lMode)	\
    (This)->lpVtbl -> put_Mode(This,lMode)

#define IAMTVTuner_get_Mode(This,plMode)	\
    (This)->lpVtbl -> get_Mode(This,plMode)

#define IAMTVTuner_GetAvailableModes(This,plModes)	\
    (This)->lpVtbl -> GetAvailableModes(This,plModes)

#define IAMTVTuner_RegisterNotificationCallBack(This,pNotify,lEvents)	\
    (This)->lpVtbl -> RegisterNotificationCallBack(This,pNotify,lEvents)

#define IAMTVTuner_UnRegisterNotificationCallBack(This,pNotify)	\
    (This)->lpVtbl -> UnRegisterNotificationCallBack(This,pNotify)


#define IAMTVTuner_get_AvailableTVFormats(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> get_AvailableTVFormats(This,lAnalogVideoStandard)

#define IAMTVTuner_get_TVFormat(This,plAnalogVideoStandard)	\
    (This)->lpVtbl -> get_TVFormat(This,plAnalogVideoStandard)

#define IAMTVTuner_AutoTune(This,lChannel,plFoundSignal)	\
    (This)->lpVtbl -> AutoTune(This,lChannel,plFoundSignal)

#define IAMTVTuner_StoreAutoTune(This)	\
    (This)->lpVtbl -> StoreAutoTune(This)

#define IAMTVTuner_get_NumInputConnections(This,plNumInputConnections)	\
    (This)->lpVtbl -> get_NumInputConnections(This,plNumInputConnections)

#define IAMTVTuner_put_InputType(This,lIndex,InputType)	\
    (This)->lpVtbl -> put_InputType(This,lIndex,InputType)

#define IAMTVTuner_get_InputType(This,lIndex,pInputType)	\
    (This)->lpVtbl -> get_InputType(This,lIndex,pInputType)

#define IAMTVTuner_put_ConnectInput(This,lIndex)	\
    (This)->lpVtbl -> put_ConnectInput(This,lIndex)

#define IAMTVTuner_get_ConnectInput(This,plIndex)	\
    (This)->lpVtbl -> get_ConnectInput(This,plIndex)

#define IAMTVTuner_get_VideoFrequency(This,lFreq)	\
    (This)->lpVtbl -> get_VideoFrequency(This,lFreq)

#define IAMTVTuner_get_AudioFrequency(This,lFreq)	\
    (This)->lpVtbl -> get_AudioFrequency(This,lFreq)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTVTuner_get_AvailableTVFormats_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *lAnalogVideoStandard);


void __RPC_STUB IAMTVTuner_get_AvailableTVFormats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_TVFormat_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *plAnalogVideoStandard);


void __RPC_STUB IAMTVTuner_get_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_AutoTune_Proxy( 
    IAMTVTuner * This,
    /* [in] */ long lChannel,
    /* [out] */ long *plFoundSignal);


void __RPC_STUB IAMTVTuner_AutoTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_StoreAutoTune_Proxy( 
    IAMTVTuner * This);


void __RPC_STUB IAMTVTuner_StoreAutoTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_NumInputConnections_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *plNumInputConnections);


void __RPC_STUB IAMTVTuner_get_NumInputConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_put_InputType_Proxy( 
    IAMTVTuner * This,
    /* [in] */ long lIndex,
    /* [in] */ TunerInputType InputType);


void __RPC_STUB IAMTVTuner_put_InputType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_InputType_Proxy( 
    IAMTVTuner * This,
    /* [in] */ long lIndex,
    /* [out] */ TunerInputType *pInputType);


void __RPC_STUB IAMTVTuner_get_InputType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_put_ConnectInput_Proxy( 
    IAMTVTuner * This,
    /* [in] */ long lIndex);


void __RPC_STUB IAMTVTuner_put_ConnectInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_ConnectInput_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *plIndex);


void __RPC_STUB IAMTVTuner_get_ConnectInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_VideoFrequency_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *lFreq);


void __RPC_STUB IAMTVTuner_get_VideoFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVTuner_get_AudioFrequency_Proxy( 
    IAMTVTuner * This,
    /* [out] */ long *lFreq);


void __RPC_STUB IAMTVTuner_get_AudioFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTVTuner_INTERFACE_DEFINED__ */


#ifndef __IBPCSatelliteTuner_INTERFACE_DEFINED__
#define __IBPCSatelliteTuner_INTERFACE_DEFINED__

/* interface IBPCSatelliteTuner */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IBPCSatelliteTuner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("211A8765-03AC-11d1-8D13-00AA00BD8339")
    IBPCSatelliteTuner : public IAMTuner
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_DefaultSubChannelTypes( 
            /* [out] */ long *plDefaultVideoType,
            /* [out] */ long *plDefaultAudioType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_DefaultSubChannelTypes( 
            /* [in] */ long lDefaultVideoType,
            /* [in] */ long lDefaultAudioType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsTapingPermitted( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBPCSatelliteTunerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBPCSatelliteTuner * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBPCSatelliteTuner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBPCSatelliteTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_Channel )( 
            IBPCSatelliteTuner * This,
            /* [in] */ long lChannel,
            /* [in] */ long lVideoSubChannel,
            /* [in] */ long lAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *get_Channel )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plChannel,
            /* [out] */ long *plVideoSubChannel,
            /* [out] */ long *plAudioSubChannel);
        
        HRESULT ( STDMETHODCALLTYPE *ChannelMinMax )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *lChannelMin,
            /* [out] */ long *lChannelMax);
        
        HRESULT ( STDMETHODCALLTYPE *put_CountryCode )( 
            IBPCSatelliteTuner * This,
            /* [in] */ long lCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *get_CountryCode )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *put_TuningSpace )( 
            IBPCSatelliteTuner * This,
            /* [in] */ long lTuningSpace);
        
        HRESULT ( STDMETHODCALLTYPE *get_TuningSpace )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plTuningSpace);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Logon )( 
            IBPCSatelliteTuner * This,
            /* [in] */ HANDLE hCurrentUser);
        
        HRESULT ( STDMETHODCALLTYPE *Logout )( 
            IBPCSatelliteTuner * This);
        
        HRESULT ( STDMETHODCALLTYPE *SignalPresent )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plSignalStrength);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IBPCSatelliteTuner * This,
            /* [in] */ AMTunerModeType lMode);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IBPCSatelliteTuner * This,
            /* [out] */ AMTunerModeType *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableModes )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plModes);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterNotificationCallBack )( 
            IBPCSatelliteTuner * This,
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterNotificationCallBack )( 
            IBPCSatelliteTuner * This,
            /* [in] */ IAMTunerNotification *pNotify);
        
        HRESULT ( STDMETHODCALLTYPE *get_DefaultSubChannelTypes )( 
            IBPCSatelliteTuner * This,
            /* [out] */ long *plDefaultVideoType,
            /* [out] */ long *plDefaultAudioType);
        
        HRESULT ( STDMETHODCALLTYPE *put_DefaultSubChannelTypes )( 
            IBPCSatelliteTuner * This,
            /* [in] */ long lDefaultVideoType,
            /* [in] */ long lDefaultAudioType);
        
        HRESULT ( STDMETHODCALLTYPE *IsTapingPermitted )( 
            IBPCSatelliteTuner * This);
        
        END_INTERFACE
    } IBPCSatelliteTunerVtbl;

    interface IBPCSatelliteTuner
    {
        CONST_VTBL struct IBPCSatelliteTunerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBPCSatelliteTuner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBPCSatelliteTuner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBPCSatelliteTuner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBPCSatelliteTuner_put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)	\
    (This)->lpVtbl -> put_Channel(This,lChannel,lVideoSubChannel,lAudioSubChannel)

#define IBPCSatelliteTuner_get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)	\
    (This)->lpVtbl -> get_Channel(This,plChannel,plVideoSubChannel,plAudioSubChannel)

#define IBPCSatelliteTuner_ChannelMinMax(This,lChannelMin,lChannelMax)	\
    (This)->lpVtbl -> ChannelMinMax(This,lChannelMin,lChannelMax)

#define IBPCSatelliteTuner_put_CountryCode(This,lCountryCode)	\
    (This)->lpVtbl -> put_CountryCode(This,lCountryCode)

#define IBPCSatelliteTuner_get_CountryCode(This,plCountryCode)	\
    (This)->lpVtbl -> get_CountryCode(This,plCountryCode)

#define IBPCSatelliteTuner_put_TuningSpace(This,lTuningSpace)	\
    (This)->lpVtbl -> put_TuningSpace(This,lTuningSpace)

#define IBPCSatelliteTuner_get_TuningSpace(This,plTuningSpace)	\
    (This)->lpVtbl -> get_TuningSpace(This,plTuningSpace)

#define IBPCSatelliteTuner_Logon(This,hCurrentUser)	\
    (This)->lpVtbl -> Logon(This,hCurrentUser)

#define IBPCSatelliteTuner_Logout(This)	\
    (This)->lpVtbl -> Logout(This)

#define IBPCSatelliteTuner_SignalPresent(This,plSignalStrength)	\
    (This)->lpVtbl -> SignalPresent(This,plSignalStrength)

#define IBPCSatelliteTuner_put_Mode(This,lMode)	\
    (This)->lpVtbl -> put_Mode(This,lMode)

#define IBPCSatelliteTuner_get_Mode(This,plMode)	\
    (This)->lpVtbl -> get_Mode(This,plMode)

#define IBPCSatelliteTuner_GetAvailableModes(This,plModes)	\
    (This)->lpVtbl -> GetAvailableModes(This,plModes)

#define IBPCSatelliteTuner_RegisterNotificationCallBack(This,pNotify,lEvents)	\
    (This)->lpVtbl -> RegisterNotificationCallBack(This,pNotify,lEvents)

#define IBPCSatelliteTuner_UnRegisterNotificationCallBack(This,pNotify)	\
    (This)->lpVtbl -> UnRegisterNotificationCallBack(This,pNotify)


#define IBPCSatelliteTuner_get_DefaultSubChannelTypes(This,plDefaultVideoType,plDefaultAudioType)	\
    (This)->lpVtbl -> get_DefaultSubChannelTypes(This,plDefaultVideoType,plDefaultAudioType)

#define IBPCSatelliteTuner_put_DefaultSubChannelTypes(This,lDefaultVideoType,lDefaultAudioType)	\
    (This)->lpVtbl -> put_DefaultSubChannelTypes(This,lDefaultVideoType,lDefaultAudioType)

#define IBPCSatelliteTuner_IsTapingPermitted(This)	\
    (This)->lpVtbl -> IsTapingPermitted(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBPCSatelliteTuner_get_DefaultSubChannelTypes_Proxy( 
    IBPCSatelliteTuner * This,
    /* [out] */ long *plDefaultVideoType,
    /* [out] */ long *plDefaultAudioType);


void __RPC_STUB IBPCSatelliteTuner_get_DefaultSubChannelTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBPCSatelliteTuner_put_DefaultSubChannelTypes_Proxy( 
    IBPCSatelliteTuner * This,
    /* [in] */ long lDefaultVideoType,
    /* [in] */ long lDefaultAudioType);


void __RPC_STUB IBPCSatelliteTuner_put_DefaultSubChannelTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBPCSatelliteTuner_IsTapingPermitted_Proxy( 
    IBPCSatelliteTuner * This);


void __RPC_STUB IBPCSatelliteTuner_IsTapingPermitted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBPCSatelliteTuner_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0178 */
/* [local] */ 

typedef 
enum tagTVAudioMode
    {	AMTVAUDIO_MODE_MONO	= 0x1,
	AMTVAUDIO_MODE_STEREO	= 0x2,
	AMTVAUDIO_MODE_LANG_A	= 0x10,
	AMTVAUDIO_MODE_LANG_B	= 0x20,
	AMTVAUDIO_MODE_LANG_C	= 0x40
    } 	TVAudioMode;

typedef 
enum tagAMTVAudioEventType
    {	AMTVAUDIO_EVENT_CHANGED	= 0x1
    } 	AMTVAudioEventType;




extern RPC_IF_HANDLE __MIDL_itf_strmif_0178_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0178_v0_0_s_ifspec;

#ifndef __IAMTVAudio_INTERFACE_DEFINED__
#define __IAMTVAudio_INTERFACE_DEFINED__

/* interface IAMTVAudio */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMTVAudio;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83EC1C30-23D1-11d1-99E6-00A0C9560266")
    IAMTVAudio : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetHardwareSupportedTVAudioModes( 
            /* [out] */ long *plModes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailableTVAudioModes( 
            /* [out] */ long *plModes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TVAudioMode( 
            /* [out] */ long *plMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_TVAudioMode( 
            /* [in] */ long lMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterNotificationCallBack( 
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterNotificationCallBack( 
            IAMTunerNotification *pNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTVAudioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTVAudio * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTVAudio * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTVAudio * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetHardwareSupportedTVAudioModes )( 
            IAMTVAudio * This,
            /* [out] */ long *plModes);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableTVAudioModes )( 
            IAMTVAudio * This,
            /* [out] */ long *plModes);
        
        HRESULT ( STDMETHODCALLTYPE *get_TVAudioMode )( 
            IAMTVAudio * This,
            /* [out] */ long *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *put_TVAudioMode )( 
            IAMTVAudio * This,
            /* [in] */ long lMode);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterNotificationCallBack )( 
            IAMTVAudio * This,
            /* [in] */ IAMTunerNotification *pNotify,
            /* [in] */ long lEvents);
        
        HRESULT ( STDMETHODCALLTYPE *UnRegisterNotificationCallBack )( 
            IAMTVAudio * This,
            IAMTunerNotification *pNotify);
        
        END_INTERFACE
    } IAMTVAudioVtbl;

    interface IAMTVAudio
    {
        CONST_VTBL struct IAMTVAudioVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTVAudio_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTVAudio_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTVAudio_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTVAudio_GetHardwareSupportedTVAudioModes(This,plModes)	\
    (This)->lpVtbl -> GetHardwareSupportedTVAudioModes(This,plModes)

#define IAMTVAudio_GetAvailableTVAudioModes(This,plModes)	\
    (This)->lpVtbl -> GetAvailableTVAudioModes(This,plModes)

#define IAMTVAudio_get_TVAudioMode(This,plMode)	\
    (This)->lpVtbl -> get_TVAudioMode(This,plMode)

#define IAMTVAudio_put_TVAudioMode(This,lMode)	\
    (This)->lpVtbl -> put_TVAudioMode(This,lMode)

#define IAMTVAudio_RegisterNotificationCallBack(This,pNotify,lEvents)	\
    (This)->lpVtbl -> RegisterNotificationCallBack(This,pNotify,lEvents)

#define IAMTVAudio_UnRegisterNotificationCallBack(This,pNotify)	\
    (This)->lpVtbl -> UnRegisterNotificationCallBack(This,pNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTVAudio_GetHardwareSupportedTVAudioModes_Proxy( 
    IAMTVAudio * This,
    /* [out] */ long *plModes);


void __RPC_STUB IAMTVAudio_GetHardwareSupportedTVAudioModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVAudio_GetAvailableTVAudioModes_Proxy( 
    IAMTVAudio * This,
    /* [out] */ long *plModes);


void __RPC_STUB IAMTVAudio_GetAvailableTVAudioModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVAudio_get_TVAudioMode_Proxy( 
    IAMTVAudio * This,
    /* [out] */ long *plMode);


void __RPC_STUB IAMTVAudio_get_TVAudioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVAudio_put_TVAudioMode_Proxy( 
    IAMTVAudio * This,
    /* [in] */ long lMode);


void __RPC_STUB IAMTVAudio_put_TVAudioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVAudio_RegisterNotificationCallBack_Proxy( 
    IAMTVAudio * This,
    /* [in] */ IAMTunerNotification *pNotify,
    /* [in] */ long lEvents);


void __RPC_STUB IAMTVAudio_RegisterNotificationCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTVAudio_UnRegisterNotificationCallBack_Proxy( 
    IAMTVAudio * This,
    IAMTunerNotification *pNotify);


void __RPC_STUB IAMTVAudio_UnRegisterNotificationCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTVAudio_INTERFACE_DEFINED__ */


#ifndef __IAMTVAudioNotification_INTERFACE_DEFINED__
#define __IAMTVAudioNotification_INTERFACE_DEFINED__

/* interface IAMTVAudioNotification */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMTVAudioNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83EC1C33-23D1-11d1-99E6-00A0C9560266")
    IAMTVAudioNotification : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ AMTVAudioEventType Event) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTVAudioNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTVAudioNotification * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTVAudioNotification * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTVAudioNotification * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            IAMTVAudioNotification * This,
            /* [in] */ AMTVAudioEventType Event);
        
        END_INTERFACE
    } IAMTVAudioNotificationVtbl;

    interface IAMTVAudioNotification
    {
        CONST_VTBL struct IAMTVAudioNotificationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTVAudioNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTVAudioNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTVAudioNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTVAudioNotification_OnEvent(This,Event)	\
    (This)->lpVtbl -> OnEvent(This,Event)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTVAudioNotification_OnEvent_Proxy( 
    IAMTVAudioNotification * This,
    /* [in] */ AMTVAudioEventType Event);


void __RPC_STUB IAMTVAudioNotification_OnEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTVAudioNotification_INTERFACE_DEFINED__ */


#ifndef __IAMAnalogVideoEncoder_INTERFACE_DEFINED__
#define __IAMAnalogVideoEncoder_INTERFACE_DEFINED__

/* interface IAMAnalogVideoEncoder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMAnalogVideoEncoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6E133B0-30AC-11d0-A18C-00A0C9118956")
    IAMAnalogVideoEncoder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_AvailableTVFormats( 
            /* [out] */ long *lAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_TVFormat( 
            /* [in] */ long lAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_TVFormat( 
            /* [out] */ long *plAnalogVideoStandard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_CopyProtection( 
            /* [in] */ long lVideoCopyProtection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CopyProtection( 
            /* [out] */ long *lVideoCopyProtection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_CCEnable( 
            /* [in] */ long lCCEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_CCEnable( 
            /* [out] */ long *lCCEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMAnalogVideoEncoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMAnalogVideoEncoder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMAnalogVideoEncoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMAnalogVideoEncoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_AvailableTVFormats )( 
            IAMAnalogVideoEncoder * This,
            /* [out] */ long *lAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *put_TVFormat )( 
            IAMAnalogVideoEncoder * This,
            /* [in] */ long lAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *get_TVFormat )( 
            IAMAnalogVideoEncoder * This,
            /* [out] */ long *plAnalogVideoStandard);
        
        HRESULT ( STDMETHODCALLTYPE *put_CopyProtection )( 
            IAMAnalogVideoEncoder * This,
            /* [in] */ long lVideoCopyProtection);
        
        HRESULT ( STDMETHODCALLTYPE *get_CopyProtection )( 
            IAMAnalogVideoEncoder * This,
            /* [out] */ long *lVideoCopyProtection);
        
        HRESULT ( STDMETHODCALLTYPE *put_CCEnable )( 
            IAMAnalogVideoEncoder * This,
            /* [in] */ long lCCEnable);
        
        HRESULT ( STDMETHODCALLTYPE *get_CCEnable )( 
            IAMAnalogVideoEncoder * This,
            /* [out] */ long *lCCEnable);
        
        END_INTERFACE
    } IAMAnalogVideoEncoderVtbl;

    interface IAMAnalogVideoEncoder
    {
        CONST_VTBL struct IAMAnalogVideoEncoderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMAnalogVideoEncoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMAnalogVideoEncoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMAnalogVideoEncoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMAnalogVideoEncoder_get_AvailableTVFormats(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> get_AvailableTVFormats(This,lAnalogVideoStandard)

#define IAMAnalogVideoEncoder_put_TVFormat(This,lAnalogVideoStandard)	\
    (This)->lpVtbl -> put_TVFormat(This,lAnalogVideoStandard)

#define IAMAnalogVideoEncoder_get_TVFormat(This,plAnalogVideoStandard)	\
    (This)->lpVtbl -> get_TVFormat(This,plAnalogVideoStandard)

#define IAMAnalogVideoEncoder_put_CopyProtection(This,lVideoCopyProtection)	\
    (This)->lpVtbl -> put_CopyProtection(This,lVideoCopyProtection)

#define IAMAnalogVideoEncoder_get_CopyProtection(This,lVideoCopyProtection)	\
    (This)->lpVtbl -> get_CopyProtection(This,lVideoCopyProtection)

#define IAMAnalogVideoEncoder_put_CCEnable(This,lCCEnable)	\
    (This)->lpVtbl -> put_CCEnable(This,lCCEnable)

#define IAMAnalogVideoEncoder_get_CCEnable(This,lCCEnable)	\
    (This)->lpVtbl -> get_CCEnable(This,lCCEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_get_AvailableTVFormats_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [out] */ long *lAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoEncoder_get_AvailableTVFormats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_put_TVFormat_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [in] */ long lAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoEncoder_put_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_get_TVFormat_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [out] */ long *plAnalogVideoStandard);


void __RPC_STUB IAMAnalogVideoEncoder_get_TVFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_put_CopyProtection_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [in] */ long lVideoCopyProtection);


void __RPC_STUB IAMAnalogVideoEncoder_put_CopyProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_get_CopyProtection_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [out] */ long *lVideoCopyProtection);


void __RPC_STUB IAMAnalogVideoEncoder_get_CopyProtection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_put_CCEnable_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [in] */ long lCCEnable);


void __RPC_STUB IAMAnalogVideoEncoder_put_CCEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMAnalogVideoEncoder_get_CCEnable_Proxy( 
    IAMAnalogVideoEncoder * This,
    /* [out] */ long *lCCEnable);


void __RPC_STUB IAMAnalogVideoEncoder_get_CCEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMAnalogVideoEncoder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0181 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0181_0001
    {	AMPROPERTY_PIN_CATEGORY	= 0,
	AMPROPERTY_PIN_MEDIUM	= AMPROPERTY_PIN_CATEGORY + 1
    } 	AMPROPERTY_PIN;

#ifndef _IKsPropertySet_
#define _IKsPropertySet_
#define KSPROPERTY_SUPPORT_GET  1
#define KSPROPERTY_SUPPORT_SET  2


extern RPC_IF_HANDLE __MIDL_itf_strmif_0181_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0181_v0_0_s_ifspec;

#ifndef __IKsPropertySet_INTERFACE_DEFINED__
#define __IKsPropertySet_INTERFACE_DEFINED__

/* interface IKsPropertySet */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IKsPropertySet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31EFAC30-515C-11d0-A9AA-00AA0061BE93")
    IKsPropertySet : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [size_is][in] */ LPVOID pInstanceData,
            /* [in] */ DWORD cbInstanceData,
            /* [size_is][in] */ LPVOID pPropData,
            /* [in] */ DWORD cbPropData) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [size_is][in] */ LPVOID pInstanceData,
            /* [in] */ DWORD cbInstanceData,
            /* [size_is][out] */ LPVOID pPropData,
            /* [in] */ DWORD cbPropData,
            /* [out] */ DWORD *pcbReturned) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QuerySupported( 
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [out] */ DWORD *pTypeSupport) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKsPropertySetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKsPropertySet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKsPropertySet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKsPropertySet * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Set )( 
            IKsPropertySet * This,
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [size_is][in] */ LPVOID pInstanceData,
            /* [in] */ DWORD cbInstanceData,
            /* [size_is][in] */ LPVOID pPropData,
            /* [in] */ DWORD cbPropData);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Get )( 
            IKsPropertySet * This,
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [size_is][in] */ LPVOID pInstanceData,
            /* [in] */ DWORD cbInstanceData,
            /* [size_is][out] */ LPVOID pPropData,
            /* [in] */ DWORD cbPropData,
            /* [out] */ DWORD *pcbReturned);
        
        HRESULT ( STDMETHODCALLTYPE *QuerySupported )( 
            IKsPropertySet * This,
            /* [in] */ REFGUID guidPropSet,
            /* [in] */ DWORD dwPropID,
            /* [out] */ DWORD *pTypeSupport);
        
        END_INTERFACE
    } IKsPropertySetVtbl;

    interface IKsPropertySet
    {
        CONST_VTBL struct IKsPropertySetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKsPropertySet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKsPropertySet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKsPropertySet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKsPropertySet_Set(This,guidPropSet,dwPropID,pInstanceData,cbInstanceData,pPropData,cbPropData)	\
    (This)->lpVtbl -> Set(This,guidPropSet,dwPropID,pInstanceData,cbInstanceData,pPropData,cbPropData)

#define IKsPropertySet_Get(This,guidPropSet,dwPropID,pInstanceData,cbInstanceData,pPropData,cbPropData,pcbReturned)	\
    (This)->lpVtbl -> Get(This,guidPropSet,dwPropID,pInstanceData,cbInstanceData,pPropData,cbPropData,pcbReturned)

#define IKsPropertySet_QuerySupported(This,guidPropSet,dwPropID,pTypeSupport)	\
    (This)->lpVtbl -> QuerySupported(This,guidPropSet,dwPropID,pTypeSupport)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_RemoteSet_Proxy( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ byte *pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][in] */ byte *pPropData,
    /* [in] */ DWORD cbPropData);


void __RPC_STUB IKsPropertySet_RemoteSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_RemoteGet_Proxy( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ byte *pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][out] */ byte *pPropData,
    /* [in] */ DWORD cbPropData,
    /* [out] */ DWORD *pcbReturned);


void __RPC_STUB IKsPropertySet_RemoteGet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsPropertySet_QuerySupported_Proxy( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [out] */ DWORD *pTypeSupport);


void __RPC_STUB IKsPropertySet_QuerySupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKsPropertySet_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0182 */
/* [local] */ 

#endif // _IKsPropertySet_


extern RPC_IF_HANDLE __MIDL_itf_strmif_0182_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0182_v0_0_s_ifspec;

#ifndef __IMediaPropertyBag_INTERFACE_DEFINED__
#define __IMediaPropertyBag_INTERFACE_DEFINED__

/* interface IMediaPropertyBag */
/* [unique][uuid][object] */ 

typedef IMediaPropertyBag *LPMEDIAPROPERTYBAG;


EXTERN_C const IID IID_IMediaPropertyBag;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6025A880-C0D5-11d0-BD4E-00A0C911CE86")
    IMediaPropertyBag : public IPropertyBag
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumProperty( 
            /* [in] */ ULONG iProperty,
            /* [out][in] */ VARIANT *pvarPropertyName,
            /* [out][in] */ VARIANT *pvarPropertyValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaPropertyBagVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaPropertyBag * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaPropertyBag * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaPropertyBag * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IMediaPropertyBag * This,
            /* [in] */ LPCOLESTR pszPropName,
            /* [out][in] */ VARIANT *pVar,
            /* [in] */ IErrorLog *pErrorLog);
        
        HRESULT ( STDMETHODCALLTYPE *Write )( 
            IMediaPropertyBag * This,
            /* [in] */ LPCOLESTR pszPropName,
            /* [in] */ VARIANT *pVar);
        
        HRESULT ( STDMETHODCALLTYPE *EnumProperty )( 
            IMediaPropertyBag * This,
            /* [in] */ ULONG iProperty,
            /* [out][in] */ VARIANT *pvarPropertyName,
            /* [out][in] */ VARIANT *pvarPropertyValue);
        
        END_INTERFACE
    } IMediaPropertyBagVtbl;

    interface IMediaPropertyBag
    {
        CONST_VTBL struct IMediaPropertyBagVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaPropertyBag_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaPropertyBag_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaPropertyBag_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaPropertyBag_Read(This,pszPropName,pVar,pErrorLog)	\
    (This)->lpVtbl -> Read(This,pszPropName,pVar,pErrorLog)

#define IMediaPropertyBag_Write(This,pszPropName,pVar)	\
    (This)->lpVtbl -> Write(This,pszPropName,pVar)


#define IMediaPropertyBag_EnumProperty(This,iProperty,pvarPropertyName,pvarPropertyValue)	\
    (This)->lpVtbl -> EnumProperty(This,iProperty,pvarPropertyName,pvarPropertyValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaPropertyBag_EnumProperty_Proxy( 
    IMediaPropertyBag * This,
    /* [in] */ ULONG iProperty,
    /* [out][in] */ VARIANT *pvarPropertyName,
    /* [out][in] */ VARIANT *pvarPropertyValue);


void __RPC_STUB IMediaPropertyBag_EnumProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaPropertyBag_INTERFACE_DEFINED__ */


#ifndef __IPersistMediaPropertyBag_INTERFACE_DEFINED__
#define __IPersistMediaPropertyBag_INTERFACE_DEFINED__

/* interface IPersistMediaPropertyBag */
/* [unique][uuid][object] */ 

typedef IPersistMediaPropertyBag *LPPERSISTMEDIAPROPERTYBAG;


EXTERN_C const IID IID_IPersistMediaPropertyBag;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5738E040-B67F-11d0-BD4D-00A0C911CE86")
    IPersistMediaPropertyBag : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitNew( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IMediaPropertyBag *pPropBag,
            /* [in] */ IErrorLog *pErrorLog) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IMediaPropertyBag *pPropBag,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ BOOL fSaveAllProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistMediaPropertyBagVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistMediaPropertyBag * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistMediaPropertyBag * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistMediaPropertyBag * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistMediaPropertyBag * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *InitNew )( 
            IPersistMediaPropertyBag * This);
        
        HRESULT ( STDMETHODCALLTYPE *Load )( 
            IPersistMediaPropertyBag * This,
            /* [in] */ IMediaPropertyBag *pPropBag,
            /* [in] */ IErrorLog *pErrorLog);
        
        HRESULT ( STDMETHODCALLTYPE *Save )( 
            IPersistMediaPropertyBag * This,
            /* [in] */ IMediaPropertyBag *pPropBag,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ BOOL fSaveAllProperties);
        
        END_INTERFACE
    } IPersistMediaPropertyBagVtbl;

    interface IPersistMediaPropertyBag
    {
        CONST_VTBL struct IPersistMediaPropertyBagVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistMediaPropertyBag_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPersistMediaPropertyBag_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPersistMediaPropertyBag_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPersistMediaPropertyBag_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IPersistMediaPropertyBag_InitNew(This)	\
    (This)->lpVtbl -> InitNew(This)

#define IPersistMediaPropertyBag_Load(This,pPropBag,pErrorLog)	\
    (This)->lpVtbl -> Load(This,pPropBag,pErrorLog)

#define IPersistMediaPropertyBag_Save(This,pPropBag,fClearDirty,fSaveAllProperties)	\
    (This)->lpVtbl -> Save(This,pPropBag,fClearDirty,fSaveAllProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistMediaPropertyBag_InitNew_Proxy( 
    IPersistMediaPropertyBag * This);


void __RPC_STUB IPersistMediaPropertyBag_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistMediaPropertyBag_Load_Proxy( 
    IPersistMediaPropertyBag * This,
    /* [in] */ IMediaPropertyBag *pPropBag,
    /* [in] */ IErrorLog *pErrorLog);


void __RPC_STUB IPersistMediaPropertyBag_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistMediaPropertyBag_Save_Proxy( 
    IPersistMediaPropertyBag * This,
    /* [in] */ IMediaPropertyBag *pPropBag,
    /* [in] */ BOOL fClearDirty,
    /* [in] */ BOOL fSaveAllProperties);


void __RPC_STUB IPersistMediaPropertyBag_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistMediaPropertyBag_INTERFACE_DEFINED__ */


#ifndef __IAMPhysicalPinInfo_INTERFACE_DEFINED__
#define __IAMPhysicalPinInfo_INTERFACE_DEFINED__

/* interface IAMPhysicalPinInfo */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMPhysicalPinInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F938C991-3029-11cf-8C44-00AA006B6814")
    IAMPhysicalPinInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPhysicalType( 
            /* [out] */ long *pType,
            /* [out] */ LPOLESTR *ppszType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPhysicalPinInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMPhysicalPinInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMPhysicalPinInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMPhysicalPinInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhysicalType )( 
            IAMPhysicalPinInfo * This,
            /* [out] */ long *pType,
            /* [out] */ LPOLESTR *ppszType);
        
        END_INTERFACE
    } IAMPhysicalPinInfoVtbl;

    interface IAMPhysicalPinInfo
    {
        CONST_VTBL struct IAMPhysicalPinInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPhysicalPinInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPhysicalPinInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPhysicalPinInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPhysicalPinInfo_GetPhysicalType(This,pType,ppszType)	\
    (This)->lpVtbl -> GetPhysicalType(This,pType,ppszType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPhysicalPinInfo_GetPhysicalType_Proxy( 
    IAMPhysicalPinInfo * This,
    /* [out] */ long *pType,
    /* [out] */ LPOLESTR *ppszType);


void __RPC_STUB IAMPhysicalPinInfo_GetPhysicalType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPhysicalPinInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0329 */
/* [local] */ 

typedef IAMPhysicalPinInfo *PAMPHYSICALPININFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0329_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0329_v0_0_s_ifspec;

#ifndef __IAMExtDevice_INTERFACE_DEFINED__
#define __IAMExtDevice_INTERFACE_DEFINED__

/* interface IAMExtDevice */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMExtDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5730A90-1A2C-11cf-8C23-00AA006B6814")
    IAMExtDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCapability( 
            /* [in] */ long Capability,
            /* [out] */ long *pValue,
            /* [out] */ double *pdblValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ExternalDeviceID( 
            /* [out] */ LPOLESTR *ppszData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ExternalDeviceVersion( 
            /* [out] */ LPOLESTR *ppszData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_DevicePower( 
            /* [in] */ long PowerMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_DevicePower( 
            /* [out] */ long *pPowerMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Calibrate( 
            /* [in] */ HEVENT hEvent,
            /* [in] */ long Mode,
            /* [out] */ long *pStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_DevicePort( 
            /* [in] */ long DevicePort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_DevicePort( 
            /* [out] */ long *pDevicePort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMExtDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMExtDevice * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMExtDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMExtDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCapability )( 
            IAMExtDevice * This,
            /* [in] */ long Capability,
            /* [out] */ long *pValue,
            /* [out] */ double *pdblValue);
        
        HRESULT ( STDMETHODCALLTYPE *get_ExternalDeviceID )( 
            IAMExtDevice * This,
            /* [out] */ LPOLESTR *ppszData);
        
        HRESULT ( STDMETHODCALLTYPE *get_ExternalDeviceVersion )( 
            IAMExtDevice * This,
            /* [out] */ LPOLESTR *ppszData);
        
        HRESULT ( STDMETHODCALLTYPE *put_DevicePower )( 
            IAMExtDevice * This,
            /* [in] */ long PowerMode);
        
        HRESULT ( STDMETHODCALLTYPE *get_DevicePower )( 
            IAMExtDevice * This,
            /* [out] */ long *pPowerMode);
        
        HRESULT ( STDMETHODCALLTYPE *Calibrate )( 
            IAMExtDevice * This,
            /* [in] */ HEVENT hEvent,
            /* [in] */ long Mode,
            /* [out] */ long *pStatus);
        
        HRESULT ( STDMETHODCALLTYPE *put_DevicePort )( 
            IAMExtDevice * This,
            /* [in] */ long DevicePort);
        
        HRESULT ( STDMETHODCALLTYPE *get_DevicePort )( 
            IAMExtDevice * This,
            /* [out] */ long *pDevicePort);
        
        END_INTERFACE
    } IAMExtDeviceVtbl;

    interface IAMExtDevice
    {
        CONST_VTBL struct IAMExtDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMExtDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMExtDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMExtDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMExtDevice_GetCapability(This,Capability,pValue,pdblValue)	\
    (This)->lpVtbl -> GetCapability(This,Capability,pValue,pdblValue)

#define IAMExtDevice_get_ExternalDeviceID(This,ppszData)	\
    (This)->lpVtbl -> get_ExternalDeviceID(This,ppszData)

#define IAMExtDevice_get_ExternalDeviceVersion(This,ppszData)	\
    (This)->lpVtbl -> get_ExternalDeviceVersion(This,ppszData)

#define IAMExtDevice_put_DevicePower(This,PowerMode)	\
    (This)->lpVtbl -> put_DevicePower(This,PowerMode)

#define IAMExtDevice_get_DevicePower(This,pPowerMode)	\
    (This)->lpVtbl -> get_DevicePower(This,pPowerMode)

#define IAMExtDevice_Calibrate(This,hEvent,Mode,pStatus)	\
    (This)->lpVtbl -> Calibrate(This,hEvent,Mode,pStatus)

#define IAMExtDevice_put_DevicePort(This,DevicePort)	\
    (This)->lpVtbl -> put_DevicePort(This,DevicePort)

#define IAMExtDevice_get_DevicePort(This,pDevicePort)	\
    (This)->lpVtbl -> get_DevicePort(This,pDevicePort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMExtDevice_GetCapability_Proxy( 
    IAMExtDevice * This,
    /* [in] */ long Capability,
    /* [out] */ long *pValue,
    /* [out] */ double *pdblValue);


void __RPC_STUB IAMExtDevice_GetCapability_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_get_ExternalDeviceID_Proxy( 
    IAMExtDevice * This,
    /* [out] */ LPOLESTR *ppszData);


void __RPC_STUB IAMExtDevice_get_ExternalDeviceID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_get_ExternalDeviceVersion_Proxy( 
    IAMExtDevice * This,
    /* [out] */ LPOLESTR *ppszData);


void __RPC_STUB IAMExtDevice_get_ExternalDeviceVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_put_DevicePower_Proxy( 
    IAMExtDevice * This,
    /* [in] */ long PowerMode);


void __RPC_STUB IAMExtDevice_put_DevicePower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_get_DevicePower_Proxy( 
    IAMExtDevice * This,
    /* [out] */ long *pPowerMode);


void __RPC_STUB IAMExtDevice_get_DevicePower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_Calibrate_Proxy( 
    IAMExtDevice * This,
    /* [in] */ HEVENT hEvent,
    /* [in] */ long Mode,
    /* [out] */ long *pStatus);


void __RPC_STUB IAMExtDevice_Calibrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_put_DevicePort_Proxy( 
    IAMExtDevice * This,
    /* [in] */ long DevicePort);


void __RPC_STUB IAMExtDevice_put_DevicePort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtDevice_get_DevicePort_Proxy( 
    IAMExtDevice * This,
    /* [out] */ long *pDevicePort);


void __RPC_STUB IAMExtDevice_get_DevicePort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMExtDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0330 */
/* [local] */ 

typedef IAMExtDevice *PEXTDEVICE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0330_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0330_v0_0_s_ifspec;

#ifndef __IAMExtTransport_INTERFACE_DEFINED__
#define __IAMExtTransport_INTERFACE_DEFINED__

/* interface IAMExtTransport */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMExtTransport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A03CD5F0-3045-11cf-8C44-00AA006B6814")
    IAMExtTransport : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCapability( 
            /* [in] */ long Capability,
            /* [out] */ long *pValue,
            /* [out] */ double *pdblValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_MediaState( 
            /* [in] */ long State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_MediaState( 
            /* [out] */ long *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_LocalControl( 
            /* [in] */ long State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_LocalControl( 
            /* [out] */ long *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [in] */ long StatusItem,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTransportBasicParameters( 
            /* [in] */ long Param,
            /* [out] */ long *pValue,
            /* [out] */ LPOLESTR *ppszData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTransportBasicParameters( 
            /* [in] */ long Param,
            /* [in] */ long Value,
            /* [in] */ LPCOLESTR pszData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTransportVideoParameters( 
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTransportVideoParameters( 
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTransportAudioParameters( 
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTransportAudioParameters( 
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ long Mode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [out] */ long *pMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_Rate( 
            /* [in] */ double dblRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Rate( 
            /* [out] */ double *pdblRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetChase( 
            /* [out] */ long *pEnabled,
            /* [out] */ long *pOffset,
            /* [out] */ HEVENT *phEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetChase( 
            /* [in] */ long Enable,
            /* [in] */ long Offset,
            /* [in] */ HEVENT hEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBump( 
            /* [out] */ long *pSpeed,
            /* [out] */ long *pDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBump( 
            /* [in] */ long Speed,
            /* [in] */ long Duration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_AntiClogControl( 
            /* [out] */ long *pEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_AntiClogControl( 
            /* [in] */ long Enable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditPropertySet( 
            /* [in] */ long EditID,
            /* [out] */ long *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEditPropertySet( 
            /* [out][in] */ long *pEditID,
            /* [in] */ long State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditProperty( 
            /* [in] */ long EditID,
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEditProperty( 
            /* [in] */ long EditID,
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_EditStart( 
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_EditStart( 
            /* [in] */ long Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMExtTransportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMExtTransport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMExtTransport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMExtTransport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCapability )( 
            IAMExtTransport * This,
            /* [in] */ long Capability,
            /* [out] */ long *pValue,
            /* [out] */ double *pdblValue);
        
        HRESULT ( STDMETHODCALLTYPE *put_MediaState )( 
            IAMExtTransport * This,
            /* [in] */ long State);
        
        HRESULT ( STDMETHODCALLTYPE *get_MediaState )( 
            IAMExtTransport * This,
            /* [out] */ long *pState);
        
        HRESULT ( STDMETHODCALLTYPE *put_LocalControl )( 
            IAMExtTransport * This,
            /* [in] */ long State);
        
        HRESULT ( STDMETHODCALLTYPE *get_LocalControl )( 
            IAMExtTransport * This,
            /* [out] */ long *pState);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            IAMExtTransport * This,
            /* [in] */ long StatusItem,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetTransportBasicParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue,
            /* [out] */ LPOLESTR *ppszData);
        
        HRESULT ( STDMETHODCALLTYPE *SetTransportBasicParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [in] */ long Value,
            /* [in] */ LPCOLESTR pszData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTransportVideoParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetTransportVideoParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetTransportAudioParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetTransportAudioParameters )( 
            IAMExtTransport * This,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            IAMExtTransport * This,
            /* [in] */ long Mode);
        
        HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            IAMExtTransport * This,
            /* [out] */ long *pMode);
        
        HRESULT ( STDMETHODCALLTYPE *put_Rate )( 
            IAMExtTransport * This,
            /* [in] */ double dblRate);
        
        HRESULT ( STDMETHODCALLTYPE *get_Rate )( 
            IAMExtTransport * This,
            /* [out] */ double *pdblRate);
        
        HRESULT ( STDMETHODCALLTYPE *GetChase )( 
            IAMExtTransport * This,
            /* [out] */ long *pEnabled,
            /* [out] */ long *pOffset,
            /* [out] */ HEVENT *phEvent);
        
        HRESULT ( STDMETHODCALLTYPE *SetChase )( 
            IAMExtTransport * This,
            /* [in] */ long Enable,
            /* [in] */ long Offset,
            /* [in] */ HEVENT hEvent);
        
        HRESULT ( STDMETHODCALLTYPE *GetBump )( 
            IAMExtTransport * This,
            /* [out] */ long *pSpeed,
            /* [out] */ long *pDuration);
        
        HRESULT ( STDMETHODCALLTYPE *SetBump )( 
            IAMExtTransport * This,
            /* [in] */ long Speed,
            /* [in] */ long Duration);
        
        HRESULT ( STDMETHODCALLTYPE *get_AntiClogControl )( 
            IAMExtTransport * This,
            /* [out] */ long *pEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *put_AntiClogControl )( 
            IAMExtTransport * This,
            /* [in] */ long Enable);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditPropertySet )( 
            IAMExtTransport * This,
            /* [in] */ long EditID,
            /* [out] */ long *pState);
        
        HRESULT ( STDMETHODCALLTYPE *SetEditPropertySet )( 
            IAMExtTransport * This,
            /* [out][in] */ long *pEditID,
            /* [in] */ long State);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditProperty )( 
            IAMExtTransport * This,
            /* [in] */ long EditID,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetEditProperty )( 
            IAMExtTransport * This,
            /* [in] */ long EditID,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *get_EditStart )( 
            IAMExtTransport * This,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *put_EditStart )( 
            IAMExtTransport * This,
            /* [in] */ long Value);
        
        END_INTERFACE
    } IAMExtTransportVtbl;

    interface IAMExtTransport
    {
        CONST_VTBL struct IAMExtTransportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMExtTransport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMExtTransport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMExtTransport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMExtTransport_GetCapability(This,Capability,pValue,pdblValue)	\
    (This)->lpVtbl -> GetCapability(This,Capability,pValue,pdblValue)

#define IAMExtTransport_put_MediaState(This,State)	\
    (This)->lpVtbl -> put_MediaState(This,State)

#define IAMExtTransport_get_MediaState(This,pState)	\
    (This)->lpVtbl -> get_MediaState(This,pState)

#define IAMExtTransport_put_LocalControl(This,State)	\
    (This)->lpVtbl -> put_LocalControl(This,State)

#define IAMExtTransport_get_LocalControl(This,pState)	\
    (This)->lpVtbl -> get_LocalControl(This,pState)

#define IAMExtTransport_GetStatus(This,StatusItem,pValue)	\
    (This)->lpVtbl -> GetStatus(This,StatusItem,pValue)

#define IAMExtTransport_GetTransportBasicParameters(This,Param,pValue,ppszData)	\
    (This)->lpVtbl -> GetTransportBasicParameters(This,Param,pValue,ppszData)

#define IAMExtTransport_SetTransportBasicParameters(This,Param,Value,pszData)	\
    (This)->lpVtbl -> SetTransportBasicParameters(This,Param,Value,pszData)

#define IAMExtTransport_GetTransportVideoParameters(This,Param,pValue)	\
    (This)->lpVtbl -> GetTransportVideoParameters(This,Param,pValue)

#define IAMExtTransport_SetTransportVideoParameters(This,Param,Value)	\
    (This)->lpVtbl -> SetTransportVideoParameters(This,Param,Value)

#define IAMExtTransport_GetTransportAudioParameters(This,Param,pValue)	\
    (This)->lpVtbl -> GetTransportAudioParameters(This,Param,pValue)

#define IAMExtTransport_SetTransportAudioParameters(This,Param,Value)	\
    (This)->lpVtbl -> SetTransportAudioParameters(This,Param,Value)

#define IAMExtTransport_put_Mode(This,Mode)	\
    (This)->lpVtbl -> put_Mode(This,Mode)

#define IAMExtTransport_get_Mode(This,pMode)	\
    (This)->lpVtbl -> get_Mode(This,pMode)

#define IAMExtTransport_put_Rate(This,dblRate)	\
    (This)->lpVtbl -> put_Rate(This,dblRate)

#define IAMExtTransport_get_Rate(This,pdblRate)	\
    (This)->lpVtbl -> get_Rate(This,pdblRate)

#define IAMExtTransport_GetChase(This,pEnabled,pOffset,phEvent)	\
    (This)->lpVtbl -> GetChase(This,pEnabled,pOffset,phEvent)

#define IAMExtTransport_SetChase(This,Enable,Offset,hEvent)	\
    (This)->lpVtbl -> SetChase(This,Enable,Offset,hEvent)

#define IAMExtTransport_GetBump(This,pSpeed,pDuration)	\
    (This)->lpVtbl -> GetBump(This,pSpeed,pDuration)

#define IAMExtTransport_SetBump(This,Speed,Duration)	\
    (This)->lpVtbl -> SetBump(This,Speed,Duration)

#define IAMExtTransport_get_AntiClogControl(This,pEnabled)	\
    (This)->lpVtbl -> get_AntiClogControl(This,pEnabled)

#define IAMExtTransport_put_AntiClogControl(This,Enable)	\
    (This)->lpVtbl -> put_AntiClogControl(This,Enable)

#define IAMExtTransport_GetEditPropertySet(This,EditID,pState)	\
    (This)->lpVtbl -> GetEditPropertySet(This,EditID,pState)

#define IAMExtTransport_SetEditPropertySet(This,pEditID,State)	\
    (This)->lpVtbl -> SetEditPropertySet(This,pEditID,State)

#define IAMExtTransport_GetEditProperty(This,EditID,Param,pValue)	\
    (This)->lpVtbl -> GetEditProperty(This,EditID,Param,pValue)

#define IAMExtTransport_SetEditProperty(This,EditID,Param,Value)	\
    (This)->lpVtbl -> SetEditProperty(This,EditID,Param,Value)

#define IAMExtTransport_get_EditStart(This,pValue)	\
    (This)->lpVtbl -> get_EditStart(This,pValue)

#define IAMExtTransport_put_EditStart(This,Value)	\
    (This)->lpVtbl -> put_EditStart(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMExtTransport_GetCapability_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Capability,
    /* [out] */ long *pValue,
    /* [out] */ double *pdblValue);


void __RPC_STUB IAMExtTransport_GetCapability_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_MediaState_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long State);


void __RPC_STUB IAMExtTransport_put_MediaState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_MediaState_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pState);


void __RPC_STUB IAMExtTransport_get_MediaState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_LocalControl_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long State);


void __RPC_STUB IAMExtTransport_put_LocalControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_LocalControl_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pState);


void __RPC_STUB IAMExtTransport_get_LocalControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetStatus_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long StatusItem,
    /* [out] */ long *pValue);


void __RPC_STUB IAMExtTransport_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetTransportBasicParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue,
    /* [out] */ LPOLESTR *ppszData);


void __RPC_STUB IAMExtTransport_GetTransportBasicParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetTransportBasicParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [in] */ long Value,
    /* [in] */ LPCOLESTR pszData);


void __RPC_STUB IAMExtTransport_SetTransportBasicParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetTransportVideoParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMExtTransport_GetTransportVideoParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetTransportVideoParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMExtTransport_SetTransportVideoParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetTransportAudioParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMExtTransport_GetTransportAudioParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetTransportAudioParameters_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMExtTransport_SetTransportAudioParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_Mode_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Mode);


void __RPC_STUB IAMExtTransport_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_Mode_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pMode);


void __RPC_STUB IAMExtTransport_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_Rate_Proxy( 
    IAMExtTransport * This,
    /* [in] */ double dblRate);


void __RPC_STUB IAMExtTransport_put_Rate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_Rate_Proxy( 
    IAMExtTransport * This,
    /* [out] */ double *pdblRate);


void __RPC_STUB IAMExtTransport_get_Rate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetChase_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pEnabled,
    /* [out] */ long *pOffset,
    /* [out] */ HEVENT *phEvent);


void __RPC_STUB IAMExtTransport_GetChase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetChase_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Enable,
    /* [in] */ long Offset,
    /* [in] */ HEVENT hEvent);


void __RPC_STUB IAMExtTransport_SetChase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetBump_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pSpeed,
    /* [out] */ long *pDuration);


void __RPC_STUB IAMExtTransport_GetBump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetBump_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Speed,
    /* [in] */ long Duration);


void __RPC_STUB IAMExtTransport_SetBump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_AntiClogControl_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pEnabled);


void __RPC_STUB IAMExtTransport_get_AntiClogControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_AntiClogControl_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Enable);


void __RPC_STUB IAMExtTransport_put_AntiClogControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetEditPropertySet_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long EditID,
    /* [out] */ long *pState);


void __RPC_STUB IAMExtTransport_GetEditPropertySet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetEditPropertySet_Proxy( 
    IAMExtTransport * This,
    /* [out][in] */ long *pEditID,
    /* [in] */ long State);


void __RPC_STUB IAMExtTransport_SetEditPropertySet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_GetEditProperty_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long EditID,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMExtTransport_GetEditProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_SetEditProperty_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long EditID,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMExtTransport_SetEditProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_get_EditStart_Proxy( 
    IAMExtTransport * This,
    /* [out] */ long *pValue);


void __RPC_STUB IAMExtTransport_get_EditStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMExtTransport_put_EditStart_Proxy( 
    IAMExtTransport * This,
    /* [in] */ long Value);


void __RPC_STUB IAMExtTransport_put_EditStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMExtTransport_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0331 */
/* [local] */ 

typedef IAMExtTransport *PIAMEXTTRANSPORT;

#if 0
/* the following is what MIDL knows how to remote */
typedef struct tagTIMECODE
    {
    WORD wFrameRate;
    WORD wFrameFract;
    DWORD dwFrames;
    } 	TIMECODE;

#else /* 0 */
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

#endif /* TIMECODE_DEFINED */
#endif /* 0 */
typedef TIMECODE *PTIMECODE;

typedef struct tagTIMECODE_SAMPLE
    {
    LONGLONG qwTick;
    TIMECODE timecode;
    DWORD dwUser;
    DWORD dwFlags;
    } 	TIMECODE_SAMPLE;

typedef TIMECODE_SAMPLE *PTIMECODE_SAMPLE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0331_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0331_v0_0_s_ifspec;

#ifndef __IAMTimecodeReader_INTERFACE_DEFINED__
#define __IAMTimecodeReader_INTERFACE_DEFINED__

/* interface IAMTimecodeReader */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTimecodeReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B496CE1-811B-11cf-8C77-00AA006B6814")
    IAMTimecodeReader : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTCRMode( 
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTCRMode( 
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VITCLine( 
            /* [in] */ long Line) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VITCLine( 
            /* [out] */ long *pLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimecode( 
            /* [out] */ PTIMECODE_SAMPLE pTimecodeSample) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTimecodeReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTimecodeReader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTimecodeReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTimecodeReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCRMode )( 
            IAMTimecodeReader * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetTCRMode )( 
            IAMTimecodeReader * This,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *put_VITCLine )( 
            IAMTimecodeReader * This,
            /* [in] */ long Line);
        
        HRESULT ( STDMETHODCALLTYPE *get_VITCLine )( 
            IAMTimecodeReader * This,
            /* [out] */ long *pLine);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimecode )( 
            IAMTimecodeReader * This,
            /* [out] */ PTIMECODE_SAMPLE pTimecodeSample);
        
        END_INTERFACE
    } IAMTimecodeReaderVtbl;

    interface IAMTimecodeReader
    {
        CONST_VTBL struct IAMTimecodeReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTimecodeReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTimecodeReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTimecodeReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTimecodeReader_GetTCRMode(This,Param,pValue)	\
    (This)->lpVtbl -> GetTCRMode(This,Param,pValue)

#define IAMTimecodeReader_SetTCRMode(This,Param,Value)	\
    (This)->lpVtbl -> SetTCRMode(This,Param,Value)

#define IAMTimecodeReader_put_VITCLine(This,Line)	\
    (This)->lpVtbl -> put_VITCLine(This,Line)

#define IAMTimecodeReader_get_VITCLine(This,pLine)	\
    (This)->lpVtbl -> get_VITCLine(This,pLine)

#define IAMTimecodeReader_GetTimecode(This,pTimecodeSample)	\
    (This)->lpVtbl -> GetTimecode(This,pTimecodeSample)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTimecodeReader_GetTCRMode_Proxy( 
    IAMTimecodeReader * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMTimecodeReader_GetTCRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeReader_SetTCRMode_Proxy( 
    IAMTimecodeReader * This,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMTimecodeReader_SetTCRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeReader_put_VITCLine_Proxy( 
    IAMTimecodeReader * This,
    /* [in] */ long Line);


void __RPC_STUB IAMTimecodeReader_put_VITCLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeReader_get_VITCLine_Proxy( 
    IAMTimecodeReader * This,
    /* [out] */ long *pLine);


void __RPC_STUB IAMTimecodeReader_get_VITCLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeReader_GetTimecode_Proxy( 
    IAMTimecodeReader * This,
    /* [out] */ PTIMECODE_SAMPLE pTimecodeSample);


void __RPC_STUB IAMTimecodeReader_GetTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTimecodeReader_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0332 */
/* [local] */ 

typedef IAMTimecodeReader *PIAMTIMECODEREADER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0332_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0332_v0_0_s_ifspec;

#ifndef __IAMTimecodeGenerator_INTERFACE_DEFINED__
#define __IAMTimecodeGenerator_INTERFACE_DEFINED__

/* interface IAMTimecodeGenerator */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTimecodeGenerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B496CE0-811B-11cf-8C77-00AA006B6814")
    IAMTimecodeGenerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTCGMode( 
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTCGMode( 
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_VITCLine( 
            /* [in] */ long Line) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_VITCLine( 
            /* [out] */ long *pLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimecode( 
            /* [in] */ PTIMECODE_SAMPLE pTimecodeSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimecode( 
            /* [out] */ PTIMECODE_SAMPLE pTimecodeSample) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTimecodeGeneratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTimecodeGenerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTimecodeGenerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTimecodeGenerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCGMode )( 
            IAMTimecodeGenerator * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetTCGMode )( 
            IAMTimecodeGenerator * This,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        HRESULT ( STDMETHODCALLTYPE *put_VITCLine )( 
            IAMTimecodeGenerator * This,
            /* [in] */ long Line);
        
        HRESULT ( STDMETHODCALLTYPE *get_VITCLine )( 
            IAMTimecodeGenerator * This,
            /* [out] */ long *pLine);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimecode )( 
            IAMTimecodeGenerator * This,
            /* [in] */ PTIMECODE_SAMPLE pTimecodeSample);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimecode )( 
            IAMTimecodeGenerator * This,
            /* [out] */ PTIMECODE_SAMPLE pTimecodeSample);
        
        END_INTERFACE
    } IAMTimecodeGeneratorVtbl;

    interface IAMTimecodeGenerator
    {
        CONST_VTBL struct IAMTimecodeGeneratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTimecodeGenerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTimecodeGenerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTimecodeGenerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTimecodeGenerator_GetTCGMode(This,Param,pValue)	\
    (This)->lpVtbl -> GetTCGMode(This,Param,pValue)

#define IAMTimecodeGenerator_SetTCGMode(This,Param,Value)	\
    (This)->lpVtbl -> SetTCGMode(This,Param,Value)

#define IAMTimecodeGenerator_put_VITCLine(This,Line)	\
    (This)->lpVtbl -> put_VITCLine(This,Line)

#define IAMTimecodeGenerator_get_VITCLine(This,pLine)	\
    (This)->lpVtbl -> get_VITCLine(This,pLine)

#define IAMTimecodeGenerator_SetTimecode(This,pTimecodeSample)	\
    (This)->lpVtbl -> SetTimecode(This,pTimecodeSample)

#define IAMTimecodeGenerator_GetTimecode(This,pTimecodeSample)	\
    (This)->lpVtbl -> GetTimecode(This,pTimecodeSample)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_GetTCGMode_Proxy( 
    IAMTimecodeGenerator * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMTimecodeGenerator_GetTCGMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_SetTCGMode_Proxy( 
    IAMTimecodeGenerator * This,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMTimecodeGenerator_SetTCGMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_put_VITCLine_Proxy( 
    IAMTimecodeGenerator * This,
    /* [in] */ long Line);


void __RPC_STUB IAMTimecodeGenerator_put_VITCLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_get_VITCLine_Proxy( 
    IAMTimecodeGenerator * This,
    /* [out] */ long *pLine);


void __RPC_STUB IAMTimecodeGenerator_get_VITCLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_SetTimecode_Proxy( 
    IAMTimecodeGenerator * This,
    /* [in] */ PTIMECODE_SAMPLE pTimecodeSample);


void __RPC_STUB IAMTimecodeGenerator_SetTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeGenerator_GetTimecode_Proxy( 
    IAMTimecodeGenerator * This,
    /* [out] */ PTIMECODE_SAMPLE pTimecodeSample);


void __RPC_STUB IAMTimecodeGenerator_GetTimecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTimecodeGenerator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0333 */
/* [local] */ 

typedef IAMTimecodeGenerator *PIAMTIMECODEGENERATOR;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0333_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0333_v0_0_s_ifspec;

#ifndef __IAMTimecodeDisplay_INTERFACE_DEFINED__
#define __IAMTimecodeDisplay_INTERFACE_DEFINED__

/* interface IAMTimecodeDisplay */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMTimecodeDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B496CE2-811B-11cf-8C77-00AA006B6814")
    IAMTimecodeDisplay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTCDisplayEnable( 
            /* [out] */ long *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTCDisplayEnable( 
            /* [in] */ long State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTCDisplay( 
            /* [in] */ long Param,
            /* [out] */ long *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTCDisplay( 
            /* [in] */ long Param,
            /* [in] */ long Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMTimecodeDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMTimecodeDisplay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMTimecodeDisplay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMTimecodeDisplay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCDisplayEnable )( 
            IAMTimecodeDisplay * This,
            /* [out] */ long *pState);
        
        HRESULT ( STDMETHODCALLTYPE *SetTCDisplayEnable )( 
            IAMTimecodeDisplay * This,
            /* [in] */ long State);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCDisplay )( 
            IAMTimecodeDisplay * This,
            /* [in] */ long Param,
            /* [out] */ long *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetTCDisplay )( 
            IAMTimecodeDisplay * This,
            /* [in] */ long Param,
            /* [in] */ long Value);
        
        END_INTERFACE
    } IAMTimecodeDisplayVtbl;

    interface IAMTimecodeDisplay
    {
        CONST_VTBL struct IAMTimecodeDisplayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMTimecodeDisplay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMTimecodeDisplay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMTimecodeDisplay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMTimecodeDisplay_GetTCDisplayEnable(This,pState)	\
    (This)->lpVtbl -> GetTCDisplayEnable(This,pState)

#define IAMTimecodeDisplay_SetTCDisplayEnable(This,State)	\
    (This)->lpVtbl -> SetTCDisplayEnable(This,State)

#define IAMTimecodeDisplay_GetTCDisplay(This,Param,pValue)	\
    (This)->lpVtbl -> GetTCDisplay(This,Param,pValue)

#define IAMTimecodeDisplay_SetTCDisplay(This,Param,Value)	\
    (This)->lpVtbl -> SetTCDisplay(This,Param,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMTimecodeDisplay_GetTCDisplayEnable_Proxy( 
    IAMTimecodeDisplay * This,
    /* [out] */ long *pState);


void __RPC_STUB IAMTimecodeDisplay_GetTCDisplayEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeDisplay_SetTCDisplayEnable_Proxy( 
    IAMTimecodeDisplay * This,
    /* [in] */ long State);


void __RPC_STUB IAMTimecodeDisplay_SetTCDisplayEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeDisplay_GetTCDisplay_Proxy( 
    IAMTimecodeDisplay * This,
    /* [in] */ long Param,
    /* [out] */ long *pValue);


void __RPC_STUB IAMTimecodeDisplay_GetTCDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMTimecodeDisplay_SetTCDisplay_Proxy( 
    IAMTimecodeDisplay * This,
    /* [in] */ long Param,
    /* [in] */ long Value);


void __RPC_STUB IAMTimecodeDisplay_SetTCDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMTimecodeDisplay_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0334 */
/* [local] */ 

typedef IAMTimecodeDisplay *PIAMTIMECODEDISPLAY;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0334_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0334_v0_0_s_ifspec;

#ifndef __IAMDevMemoryAllocator_INTERFACE_DEFINED__
#define __IAMDevMemoryAllocator_INTERFACE_DEFINED__

/* interface IAMDevMemoryAllocator */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMDevMemoryAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c6545bf0-e76b-11d0-bd52-00a0c911ce86")
    IAMDevMemoryAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ DWORD *pdwcbTotalFree,
            /* [out] */ DWORD *pdwcbLargestFree,
            /* [out] */ DWORD *pdwcbTotalMemory,
            /* [out] */ DWORD *pdwcbMinimumChunk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckMemory( 
            /* [in] */ const BYTE *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Alloc( 
            /* [out] */ BYTE **ppBuffer,
            /* [out][in] */ DWORD *pdwcbBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Free( 
            /* [in] */ BYTE *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDevMemoryObject( 
            /* [out] */ IUnknown **ppUnkInnner,
            /* [in] */ IUnknown *pUnkOuter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDevMemoryAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMDevMemoryAllocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMDevMemoryAllocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMDevMemoryAllocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            IAMDevMemoryAllocator * This,
            /* [out] */ DWORD *pdwcbTotalFree,
            /* [out] */ DWORD *pdwcbLargestFree,
            /* [out] */ DWORD *pdwcbTotalMemory,
            /* [out] */ DWORD *pdwcbMinimumChunk);
        
        HRESULT ( STDMETHODCALLTYPE *CheckMemory )( 
            IAMDevMemoryAllocator * This,
            /* [in] */ const BYTE *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *Alloc )( 
            IAMDevMemoryAllocator * This,
            /* [out] */ BYTE **ppBuffer,
            /* [out][in] */ DWORD *pdwcbBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *Free )( 
            IAMDevMemoryAllocator * This,
            /* [in] */ BYTE *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevMemoryObject )( 
            IAMDevMemoryAllocator * This,
            /* [out] */ IUnknown **ppUnkInnner,
            /* [in] */ IUnknown *pUnkOuter);
        
        END_INTERFACE
    } IAMDevMemoryAllocatorVtbl;

    interface IAMDevMemoryAllocator
    {
        CONST_VTBL struct IAMDevMemoryAllocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDevMemoryAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDevMemoryAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDevMemoryAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDevMemoryAllocator_GetInfo(This,pdwcbTotalFree,pdwcbLargestFree,pdwcbTotalMemory,pdwcbMinimumChunk)	\
    (This)->lpVtbl -> GetInfo(This,pdwcbTotalFree,pdwcbLargestFree,pdwcbTotalMemory,pdwcbMinimumChunk)

#define IAMDevMemoryAllocator_CheckMemory(This,pBuffer)	\
    (This)->lpVtbl -> CheckMemory(This,pBuffer)

#define IAMDevMemoryAllocator_Alloc(This,ppBuffer,pdwcbBuffer)	\
    (This)->lpVtbl -> Alloc(This,ppBuffer,pdwcbBuffer)

#define IAMDevMemoryAllocator_Free(This,pBuffer)	\
    (This)->lpVtbl -> Free(This,pBuffer)

#define IAMDevMemoryAllocator_GetDevMemoryObject(This,ppUnkInnner,pUnkOuter)	\
    (This)->lpVtbl -> GetDevMemoryObject(This,ppUnkInnner,pUnkOuter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_GetInfo_Proxy( 
    IAMDevMemoryAllocator * This,
    /* [out] */ DWORD *pdwcbTotalFree,
    /* [out] */ DWORD *pdwcbLargestFree,
    /* [out] */ DWORD *pdwcbTotalMemory,
    /* [out] */ DWORD *pdwcbMinimumChunk);


void __RPC_STUB IAMDevMemoryAllocator_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_CheckMemory_Proxy( 
    IAMDevMemoryAllocator * This,
    /* [in] */ const BYTE *pBuffer);


void __RPC_STUB IAMDevMemoryAllocator_CheckMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_Alloc_Proxy( 
    IAMDevMemoryAllocator * This,
    /* [out] */ BYTE **ppBuffer,
    /* [out][in] */ DWORD *pdwcbBuffer);


void __RPC_STUB IAMDevMemoryAllocator_Alloc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_Free_Proxy( 
    IAMDevMemoryAllocator * This,
    /* [in] */ BYTE *pBuffer);


void __RPC_STUB IAMDevMemoryAllocator_Free_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_GetDevMemoryObject_Proxy( 
    IAMDevMemoryAllocator * This,
    /* [out] */ IUnknown **ppUnkInnner,
    /* [in] */ IUnknown *pUnkOuter);


void __RPC_STUB IAMDevMemoryAllocator_GetDevMemoryObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDevMemoryAllocator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0335 */
/* [local] */ 

typedef IAMDevMemoryAllocator *PAMDEVMEMORYALLOCATOR;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0335_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0335_v0_0_s_ifspec;

#ifndef __IAMDevMemoryControl_INTERFACE_DEFINED__
#define __IAMDevMemoryControl_INTERFACE_DEFINED__

/* interface IAMDevMemoryControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMDevMemoryControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c6545bf1-e76b-11d0-bd52-00a0c911ce86")
    IAMDevMemoryControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryWriteSync( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSync( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDevId( 
            /* [out] */ DWORD *pdwDevId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDevMemoryControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMDevMemoryControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMDevMemoryControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMDevMemoryControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryWriteSync )( 
            IAMDevMemoryControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *WriteSync )( 
            IAMDevMemoryControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevId )( 
            IAMDevMemoryControl * This,
            /* [out] */ DWORD *pdwDevId);
        
        END_INTERFACE
    } IAMDevMemoryControlVtbl;

    interface IAMDevMemoryControl
    {
        CONST_VTBL struct IAMDevMemoryControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDevMemoryControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDevMemoryControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDevMemoryControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDevMemoryControl_QueryWriteSync(This)	\
    (This)->lpVtbl -> QueryWriteSync(This)

#define IAMDevMemoryControl_WriteSync(This)	\
    (This)->lpVtbl -> WriteSync(This)

#define IAMDevMemoryControl_GetDevId(This,pdwDevId)	\
    (This)->lpVtbl -> GetDevId(This,pdwDevId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_QueryWriteSync_Proxy( 
    IAMDevMemoryControl * This);


void __RPC_STUB IAMDevMemoryControl_QueryWriteSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_WriteSync_Proxy( 
    IAMDevMemoryControl * This);


void __RPC_STUB IAMDevMemoryControl_WriteSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_GetDevId_Proxy( 
    IAMDevMemoryControl * This,
    /* [out] */ DWORD *pdwDevId);


void __RPC_STUB IAMDevMemoryControl_GetDevId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDevMemoryControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0336 */
/* [local] */ 

typedef IAMDevMemoryControl *PAMDEVMEMORYCONTROL;


enum _AMSTREAMSELECTINFOFLAGS
    {	AMSTREAMSELECTINFO_ENABLED	= 0x1,
	AMSTREAMSELECTINFO_EXCLUSIVE	= 0x2
    } ;

enum _AMSTREAMSELECTENABLEFLAGS
    {	AMSTREAMSELECTENABLE_ENABLE	= 0x1,
	AMSTREAMSELECTENABLE_ENABLEALL	= 0x2
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0336_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0336_v0_0_s_ifspec;

#ifndef __IAMStreamSelect_INTERFACE_DEFINED__
#define __IAMStreamSelect_INTERFACE_DEFINED__

/* interface IAMStreamSelect */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMStreamSelect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c1960960-17f5-11d1-abe1-00a0c905f375")
    IAMStreamSelect : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Count( 
            /* [out] */ DWORD *pcStreams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Info( 
            /* [in] */ long lIndex,
            /* [out] */ AM_MEDIA_TYPE **ppmt,
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ LCID *plcid,
            /* [out] */ DWORD *pdwGroup,
            /* [out] */ WCHAR **ppszName,
            /* [out] */ IUnknown **ppObject,
            /* [out] */ IUnknown **ppUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Enable( 
            /* [in] */ long lIndex,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMStreamSelectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMStreamSelect * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMStreamSelect * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMStreamSelect * This);
        
        HRESULT ( STDMETHODCALLTYPE *Count )( 
            IAMStreamSelect * This,
            /* [out] */ DWORD *pcStreams);
        
        HRESULT ( STDMETHODCALLTYPE *Info )( 
            IAMStreamSelect * This,
            /* [in] */ long lIndex,
            /* [out] */ AM_MEDIA_TYPE **ppmt,
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ LCID *plcid,
            /* [out] */ DWORD *pdwGroup,
            /* [out] */ WCHAR **ppszName,
            /* [out] */ IUnknown **ppObject,
            /* [out] */ IUnknown **ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE *Enable )( 
            IAMStreamSelect * This,
            /* [in] */ long lIndex,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IAMStreamSelectVtbl;

    interface IAMStreamSelect
    {
        CONST_VTBL struct IAMStreamSelectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMStreamSelect_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMStreamSelect_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMStreamSelect_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMStreamSelect_Count(This,pcStreams)	\
    (This)->lpVtbl -> Count(This,pcStreams)

#define IAMStreamSelect_Info(This,lIndex,ppmt,pdwFlags,plcid,pdwGroup,ppszName,ppObject,ppUnk)	\
    (This)->lpVtbl -> Info(This,lIndex,ppmt,pdwFlags,plcid,pdwGroup,ppszName,ppObject,ppUnk)

#define IAMStreamSelect_Enable(This,lIndex,dwFlags)	\
    (This)->lpVtbl -> Enable(This,lIndex,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMStreamSelect_Count_Proxy( 
    IAMStreamSelect * This,
    /* [out] */ DWORD *pcStreams);


void __RPC_STUB IAMStreamSelect_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamSelect_Info_Proxy( 
    IAMStreamSelect * This,
    /* [in] */ long lIndex,
    /* [out] */ AM_MEDIA_TYPE **ppmt,
    /* [out] */ DWORD *pdwFlags,
    /* [out] */ LCID *plcid,
    /* [out] */ DWORD *pdwGroup,
    /* [out] */ WCHAR **ppszName,
    /* [out] */ IUnknown **ppObject,
    /* [out] */ IUnknown **ppUnk);


void __RPC_STUB IAMStreamSelect_Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamSelect_Enable_Proxy( 
    IAMStreamSelect * This,
    /* [in] */ long lIndex,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMStreamSelect_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMStreamSelect_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0337 */
/* [local] */ 

typedef IAMStreamSelect *PAMSTREAMSELECT;


enum _AMRESCTL_RESERVEFLAGS
    {	AMRESCTL_RESERVEFLAGS_RESERVE	= 0,
	AMRESCTL_RESERVEFLAGS_UNRESERVE	= 0x1
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0337_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0337_v0_0_s_ifspec;

#ifndef __IAMResourceControl_INTERFACE_DEFINED__
#define __IAMResourceControl_INTERFACE_DEFINED__

/* interface IAMResourceControl */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IAMResourceControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8389d2d0-77d7-11d1-abe6-00a0c905f375")
    IAMResourceControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reserve( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ PVOID pvReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMResourceControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMResourceControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMResourceControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMResourceControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reserve )( 
            IAMResourceControl * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ PVOID pvReserved);
        
        END_INTERFACE
    } IAMResourceControlVtbl;

    interface IAMResourceControl
    {
        CONST_VTBL struct IAMResourceControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMResourceControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMResourceControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMResourceControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMResourceControl_Reserve(This,dwFlags,pvReserved)	\
    (This)->lpVtbl -> Reserve(This,dwFlags,pvReserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMResourceControl_Reserve_Proxy( 
    IAMResourceControl * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ PVOID pvReserved);


void __RPC_STUB IAMResourceControl_Reserve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMResourceControl_INTERFACE_DEFINED__ */


#ifndef __IAMClockAdjust_INTERFACE_DEFINED__
#define __IAMClockAdjust_INTERFACE_DEFINED__

/* interface IAMClockAdjust */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IAMClockAdjust;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4d5466b0-a49c-11d1-abe8-00a0c905f375")
    IAMClockAdjust : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetClockDelta( 
            /* [in] */ REFERENCE_TIME rtDelta) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMClockAdjustVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMClockAdjust * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMClockAdjust * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMClockAdjust * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetClockDelta )( 
            IAMClockAdjust * This,
            /* [in] */ REFERENCE_TIME rtDelta);
        
        END_INTERFACE
    } IAMClockAdjustVtbl;

    interface IAMClockAdjust
    {
        CONST_VTBL struct IAMClockAdjustVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMClockAdjust_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMClockAdjust_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMClockAdjust_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMClockAdjust_SetClockDelta(This,rtDelta)	\
    (This)->lpVtbl -> SetClockDelta(This,rtDelta)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMClockAdjust_SetClockDelta_Proxy( 
    IAMClockAdjust * This,
    /* [in] */ REFERENCE_TIME rtDelta);


void __RPC_STUB IAMClockAdjust_SetClockDelta_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMClockAdjust_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0339 */
/* [local] */ 


enum _AM_FILTER_MISC_FLAGS
    {	AM_FILTER_MISC_FLAGS_IS_RENDERER	= 0x1,
	AM_FILTER_MISC_FLAGS_IS_SOURCE	= 0x2
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0339_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0339_v0_0_s_ifspec;

#ifndef __IAMFilterMiscFlags_INTERFACE_DEFINED__
#define __IAMFilterMiscFlags_INTERFACE_DEFINED__

/* interface IAMFilterMiscFlags */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IAMFilterMiscFlags;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2dd74950-a890-11d1-abe8-00a0c905f375")
    IAMFilterMiscFlags : public IUnknown
    {
    public:
        virtual ULONG STDMETHODCALLTYPE GetMiscFlags( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMFilterMiscFlagsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMFilterMiscFlags * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMFilterMiscFlags * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMFilterMiscFlags * This);
        
        ULONG ( STDMETHODCALLTYPE *GetMiscFlags )( 
            IAMFilterMiscFlags * This);
        
        END_INTERFACE
    } IAMFilterMiscFlagsVtbl;

    interface IAMFilterMiscFlags
    {
        CONST_VTBL struct IAMFilterMiscFlagsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMFilterMiscFlags_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMFilterMiscFlags_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMFilterMiscFlags_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMFilterMiscFlags_GetMiscFlags(This)	\
    (This)->lpVtbl -> GetMiscFlags(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



ULONG STDMETHODCALLTYPE IAMFilterMiscFlags_GetMiscFlags_Proxy( 
    IAMFilterMiscFlags * This);


void __RPC_STUB IAMFilterMiscFlags_GetMiscFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMFilterMiscFlags_INTERFACE_DEFINED__ */


#ifndef __IDrawVideoImage_INTERFACE_DEFINED__
#define __IDrawVideoImage_INTERFACE_DEFINED__

/* interface IDrawVideoImage */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDrawVideoImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48efb120-ab49-11d2-aed2-00a0c995e8d5")
    IDrawVideoImage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DrawVideoImageBegin( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawVideoImageEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawVideoImageDraw( 
            /* [in] */ HDC hdc,
            /* [in] */ LPRECT lprcSrc,
            /* [in] */ LPRECT lprcDst) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDrawVideoImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDrawVideoImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDrawVideoImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDrawVideoImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *DrawVideoImageBegin )( 
            IDrawVideoImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *DrawVideoImageEnd )( 
            IDrawVideoImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *DrawVideoImageDraw )( 
            IDrawVideoImage * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPRECT lprcSrc,
            /* [in] */ LPRECT lprcDst);
        
        END_INTERFACE
    } IDrawVideoImageVtbl;

    interface IDrawVideoImage
    {
        CONST_VTBL struct IDrawVideoImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDrawVideoImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDrawVideoImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDrawVideoImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDrawVideoImage_DrawVideoImageBegin(This)	\
    (This)->lpVtbl -> DrawVideoImageBegin(This)

#define IDrawVideoImage_DrawVideoImageEnd(This)	\
    (This)->lpVtbl -> DrawVideoImageEnd(This)

#define IDrawVideoImage_DrawVideoImageDraw(This,hdc,lprcSrc,lprcDst)	\
    (This)->lpVtbl -> DrawVideoImageDraw(This,hdc,lprcSrc,lprcDst)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDrawVideoImage_DrawVideoImageBegin_Proxy( 
    IDrawVideoImage * This);


void __RPC_STUB IDrawVideoImage_DrawVideoImageBegin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDrawVideoImage_DrawVideoImageEnd_Proxy( 
    IDrawVideoImage * This);


void __RPC_STUB IDrawVideoImage_DrawVideoImageEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDrawVideoImage_DrawVideoImageDraw_Proxy( 
    IDrawVideoImage * This,
    /* [in] */ HDC hdc,
    /* [in] */ LPRECT lprcSrc,
    /* [in] */ LPRECT lprcDst);


void __RPC_STUB IDrawVideoImage_DrawVideoImageDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDrawVideoImage_INTERFACE_DEFINED__ */


#ifndef __IDecimateVideoImage_INTERFACE_DEFINED__
#define __IDecimateVideoImage_INTERFACE_DEFINED__

/* interface IDecimateVideoImage */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDecimateVideoImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2e5ea3e0-e924-11d2-b6da-00a0c995e8df")
    IDecimateVideoImage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDecimationImageSize( 
            /* [in] */ long lWidth,
            /* [in] */ long lHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetDecimationImageSize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDecimateVideoImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDecimateVideoImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDecimateVideoImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDecimateVideoImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDecimationImageSize )( 
            IDecimateVideoImage * This,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight);
        
        HRESULT ( STDMETHODCALLTYPE *ResetDecimationImageSize )( 
            IDecimateVideoImage * This);
        
        END_INTERFACE
    } IDecimateVideoImageVtbl;

    interface IDecimateVideoImage
    {
        CONST_VTBL struct IDecimateVideoImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDecimateVideoImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDecimateVideoImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDecimateVideoImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDecimateVideoImage_SetDecimationImageSize(This,lWidth,lHeight)	\
    (This)->lpVtbl -> SetDecimationImageSize(This,lWidth,lHeight)

#define IDecimateVideoImage_ResetDecimationImageSize(This)	\
    (This)->lpVtbl -> ResetDecimationImageSize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDecimateVideoImage_SetDecimationImageSize_Proxy( 
    IDecimateVideoImage * This,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight);


void __RPC_STUB IDecimateVideoImage_SetDecimationImageSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDecimateVideoImage_ResetDecimationImageSize_Proxy( 
    IDecimateVideoImage * This);


void __RPC_STUB IDecimateVideoImage_ResetDecimationImageSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDecimateVideoImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0342 */
/* [local] */ 

typedef 
enum _DECIMATION_USAGE
    {	DECIMATION_LEGACY	= 0,
	DECIMATION_USE_DECODER_ONLY	= DECIMATION_LEGACY + 1,
	DECIMATION_USE_VIDEOPORT_ONLY	= DECIMATION_USE_DECODER_ONLY + 1,
	DECIMATION_USE_OVERLAY_ONLY	= DECIMATION_USE_VIDEOPORT_ONLY + 1,
	DECIMATION_DEFAULT	= DECIMATION_USE_OVERLAY_ONLY + 1
    } 	DECIMATION_USAGE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0342_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0342_v0_0_s_ifspec;

#ifndef __IAMVideoDecimationProperties_INTERFACE_DEFINED__
#define __IAMVideoDecimationProperties_INTERFACE_DEFINED__

/* interface IAMVideoDecimationProperties */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMVideoDecimationProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("60d32930-13da-11d3-9ec6-c4fcaef5c7be")
    IAMVideoDecimationProperties : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryDecimationUsage( 
            /* [out] */ DECIMATION_USAGE *lpUsage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDecimationUsage( 
            /* [in] */ DECIMATION_USAGE Usage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoDecimationPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoDecimationProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoDecimationProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoDecimationProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryDecimationUsage )( 
            IAMVideoDecimationProperties * This,
            /* [out] */ DECIMATION_USAGE *lpUsage);
        
        HRESULT ( STDMETHODCALLTYPE *SetDecimationUsage )( 
            IAMVideoDecimationProperties * This,
            /* [in] */ DECIMATION_USAGE Usage);
        
        END_INTERFACE
    } IAMVideoDecimationPropertiesVtbl;

    interface IAMVideoDecimationProperties
    {
        CONST_VTBL struct IAMVideoDecimationPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoDecimationProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoDecimationProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoDecimationProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoDecimationProperties_QueryDecimationUsage(This,lpUsage)	\
    (This)->lpVtbl -> QueryDecimationUsage(This,lpUsage)

#define IAMVideoDecimationProperties_SetDecimationUsage(This,Usage)	\
    (This)->lpVtbl -> SetDecimationUsage(This,Usage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoDecimationProperties_QueryDecimationUsage_Proxy( 
    IAMVideoDecimationProperties * This,
    /* [out] */ DECIMATION_USAGE *lpUsage);


void __RPC_STUB IAMVideoDecimationProperties_QueryDecimationUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoDecimationProperties_SetDecimationUsage_Proxy( 
    IAMVideoDecimationProperties * This,
    /* [in] */ DECIMATION_USAGE Usage);


void __RPC_STUB IAMVideoDecimationProperties_SetDecimationUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoDecimationProperties_INTERFACE_DEFINED__ */


#ifndef __IVideoFrameStep_INTERFACE_DEFINED__
#define __IVideoFrameStep_INTERFACE_DEFINED__

/* interface IVideoFrameStep */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideoFrameStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e46a9787-2b71-444d-a4b5-1fab7b708d6a")
    IVideoFrameStep : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Step( 
            DWORD dwFrames,
            /* [unique] */ IUnknown *pStepObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanStep( 
            long bMultiple,
            /* [unique] */ IUnknown *pStepObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelStep( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoFrameStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideoFrameStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideoFrameStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideoFrameStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *Step )( 
            IVideoFrameStep * This,
            DWORD dwFrames,
            /* [unique] */ IUnknown *pStepObject);
        
        HRESULT ( STDMETHODCALLTYPE *CanStep )( 
            IVideoFrameStep * This,
            long bMultiple,
            /* [unique] */ IUnknown *pStepObject);
        
        HRESULT ( STDMETHODCALLTYPE *CancelStep )( 
            IVideoFrameStep * This);
        
        END_INTERFACE
    } IVideoFrameStepVtbl;

    interface IVideoFrameStep
    {
        CONST_VTBL struct IVideoFrameStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoFrameStep_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoFrameStep_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoFrameStep_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoFrameStep_Step(This,dwFrames,pStepObject)	\
    (This)->lpVtbl -> Step(This,dwFrames,pStepObject)

#define IVideoFrameStep_CanStep(This,bMultiple,pStepObject)	\
    (This)->lpVtbl -> CanStep(This,bMultiple,pStepObject)

#define IVideoFrameStep_CancelStep(This)	\
    (This)->lpVtbl -> CancelStep(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVideoFrameStep_Step_Proxy( 
    IVideoFrameStep * This,
    DWORD dwFrames,
    /* [unique] */ IUnknown *pStepObject);


void __RPC_STUB IVideoFrameStep_Step_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoFrameStep_CanStep_Proxy( 
    IVideoFrameStep * This,
    long bMultiple,
    /* [unique] */ IUnknown *pStepObject);


void __RPC_STUB IVideoFrameStep_CanStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoFrameStep_CancelStep_Proxy( 
    IVideoFrameStep * This);


void __RPC_STUB IVideoFrameStep_CancelStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoFrameStep_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0344 */
/* [local] */ 


enum _AM_PUSHSOURCE_FLAGS
    {	AM_PUSHSOURCECAPS_INTERNAL_RM	= 0x1,
	AM_PUSHSOURCECAPS_NOT_LIVE	= 0x2,
	AM_PUSHSOURCECAPS_PRIVATE_CLOCK	= 0x4,
	AM_PUSHSOURCEREQS_USE_STREAM_CLOCK	= 0x10000
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0344_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0344_v0_0_s_ifspec;

#ifndef __IAMLatency_INTERFACE_DEFINED__
#define __IAMLatency_INTERFACE_DEFINED__

/* interface IAMLatency */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMLatency;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62EA93BA-EC62-11d2-B770-00C04FB6BD3D")
    IAMLatency : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLatency( 
            /* [in] */ REFERENCE_TIME *prtLatency) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMLatencyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMLatency * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMLatency * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMLatency * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLatency )( 
            IAMLatency * This,
            /* [in] */ REFERENCE_TIME *prtLatency);
        
        END_INTERFACE
    } IAMLatencyVtbl;

    interface IAMLatency
    {
        CONST_VTBL struct IAMLatencyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMLatency_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMLatency_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMLatency_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMLatency_GetLatency(This,prtLatency)	\
    (This)->lpVtbl -> GetLatency(This,prtLatency)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMLatency_GetLatency_Proxy( 
    IAMLatency * This,
    /* [in] */ REFERENCE_TIME *prtLatency);


void __RPC_STUB IAMLatency_GetLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMLatency_INTERFACE_DEFINED__ */


#ifndef __IAMPushSource_INTERFACE_DEFINED__
#define __IAMPushSource_INTERFACE_DEFINED__

/* interface IAMPushSource */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMPushSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F185FE76-E64E-11d2-B76E-00C04FB6BD3D")
    IAMPushSource : public IAMLatency
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPushSourceFlags( 
            /* [out] */ ULONG *pFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPushSourceFlags( 
            /* [in] */ ULONG Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStreamOffset( 
            /* [in] */ REFERENCE_TIME rtOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamOffset( 
            /* [out] */ REFERENCE_TIME *prtOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxStreamOffset( 
            /* [out] */ REFERENCE_TIME *prtMaxOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxStreamOffset( 
            /* [in] */ REFERENCE_TIME rtMaxOffset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPushSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMPushSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMPushSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMPushSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLatency )( 
            IAMPushSource * This,
            /* [in] */ REFERENCE_TIME *prtLatency);
        
        HRESULT ( STDMETHODCALLTYPE *GetPushSourceFlags )( 
            IAMPushSource * This,
            /* [out] */ ULONG *pFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetPushSourceFlags )( 
            IAMPushSource * This,
            /* [in] */ ULONG Flags);
        
        HRESULT ( STDMETHODCALLTYPE *SetStreamOffset )( 
            IAMPushSource * This,
            /* [in] */ REFERENCE_TIME rtOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetStreamOffset )( 
            IAMPushSource * This,
            /* [out] */ REFERENCE_TIME *prtOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxStreamOffset )( 
            IAMPushSource * This,
            /* [out] */ REFERENCE_TIME *prtMaxOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetMaxStreamOffset )( 
            IAMPushSource * This,
            /* [in] */ REFERENCE_TIME rtMaxOffset);
        
        END_INTERFACE
    } IAMPushSourceVtbl;

    interface IAMPushSource
    {
        CONST_VTBL struct IAMPushSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPushSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPushSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPushSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPushSource_GetLatency(This,prtLatency)	\
    (This)->lpVtbl -> GetLatency(This,prtLatency)


#define IAMPushSource_GetPushSourceFlags(This,pFlags)	\
    (This)->lpVtbl -> GetPushSourceFlags(This,pFlags)

#define IAMPushSource_SetPushSourceFlags(This,Flags)	\
    (This)->lpVtbl -> SetPushSourceFlags(This,Flags)

#define IAMPushSource_SetStreamOffset(This,rtOffset)	\
    (This)->lpVtbl -> SetStreamOffset(This,rtOffset)

#define IAMPushSource_GetStreamOffset(This,prtOffset)	\
    (This)->lpVtbl -> GetStreamOffset(This,prtOffset)

#define IAMPushSource_GetMaxStreamOffset(This,prtMaxOffset)	\
    (This)->lpVtbl -> GetMaxStreamOffset(This,prtMaxOffset)

#define IAMPushSource_SetMaxStreamOffset(This,rtMaxOffset)	\
    (This)->lpVtbl -> SetMaxStreamOffset(This,rtMaxOffset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPushSource_GetPushSourceFlags_Proxy( 
    IAMPushSource * This,
    /* [out] */ ULONG *pFlags);


void __RPC_STUB IAMPushSource_GetPushSourceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPushSource_SetPushSourceFlags_Proxy( 
    IAMPushSource * This,
    /* [in] */ ULONG Flags);


void __RPC_STUB IAMPushSource_SetPushSourceFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPushSource_SetStreamOffset_Proxy( 
    IAMPushSource * This,
    /* [in] */ REFERENCE_TIME rtOffset);


void __RPC_STUB IAMPushSource_SetStreamOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPushSource_GetStreamOffset_Proxy( 
    IAMPushSource * This,
    /* [out] */ REFERENCE_TIME *prtOffset);


void __RPC_STUB IAMPushSource_GetStreamOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPushSource_GetMaxStreamOffset_Proxy( 
    IAMPushSource * This,
    /* [out] */ REFERENCE_TIME *prtMaxOffset);


void __RPC_STUB IAMPushSource_GetMaxStreamOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPushSource_SetMaxStreamOffset_Proxy( 
    IAMPushSource * This,
    /* [in] */ REFERENCE_TIME rtMaxOffset);


void __RPC_STUB IAMPushSource_SetMaxStreamOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPushSource_INTERFACE_DEFINED__ */


#ifndef __IAMDeviceRemoval_INTERFACE_DEFINED__
#define __IAMDeviceRemoval_INTERFACE_DEFINED__

/* interface IAMDeviceRemoval */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMDeviceRemoval;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f90a6130-b658-11d2-ae49-0000f8754b99")
    IAMDeviceRemoval : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DeviceInfo( 
            /* [out] */ CLSID *pclsidInterfaceClass,
            /* [out] */ WCHAR **pwszSymbolicLink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reassociate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disassociate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDeviceRemovalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMDeviceRemoval * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMDeviceRemoval * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMDeviceRemoval * This);
        
        HRESULT ( STDMETHODCALLTYPE *DeviceInfo )( 
            IAMDeviceRemoval * This,
            /* [out] */ CLSID *pclsidInterfaceClass,
            /* [out] */ WCHAR **pwszSymbolicLink);
        
        HRESULT ( STDMETHODCALLTYPE *Reassociate )( 
            IAMDeviceRemoval * This);
        
        HRESULT ( STDMETHODCALLTYPE *Disassociate )( 
            IAMDeviceRemoval * This);
        
        END_INTERFACE
    } IAMDeviceRemovalVtbl;

    interface IAMDeviceRemoval
    {
        CONST_VTBL struct IAMDeviceRemovalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDeviceRemoval_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDeviceRemoval_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDeviceRemoval_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDeviceRemoval_DeviceInfo(This,pclsidInterfaceClass,pwszSymbolicLink)	\
    (This)->lpVtbl -> DeviceInfo(This,pclsidInterfaceClass,pwszSymbolicLink)

#define IAMDeviceRemoval_Reassociate(This)	\
    (This)->lpVtbl -> Reassociate(This)

#define IAMDeviceRemoval_Disassociate(This)	\
    (This)->lpVtbl -> Disassociate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDeviceRemoval_DeviceInfo_Proxy( 
    IAMDeviceRemoval * This,
    /* [out] */ CLSID *pclsidInterfaceClass,
    /* [out] */ WCHAR **pwszSymbolicLink);


void __RPC_STUB IAMDeviceRemoval_DeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDeviceRemoval_Reassociate_Proxy( 
    IAMDeviceRemoval * This);


void __RPC_STUB IAMDeviceRemoval_Reassociate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDeviceRemoval_Disassociate_Proxy( 
    IAMDeviceRemoval * This);


void __RPC_STUB IAMDeviceRemoval_Disassociate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDeviceRemoval_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0346 */
/* [local] */ 

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_strmif_0346_0001
    {
    DWORD dwDVAAuxSrc;
    DWORD dwDVAAuxCtl;
    DWORD dwDVAAuxSrc1;
    DWORD dwDVAAuxCtl1;
    DWORD dwDVVAuxSrc;
    DWORD dwDVVAuxCtl;
    DWORD dwDVReserved[ 2 ];
    } 	DVINFO;

typedef struct __MIDL___MIDL_itf_strmif_0346_0001 *PDVINFO;


enum _DVENCODERRESOLUTION
    {	DVENCODERRESOLUTION_720x480	= 2012,
	DVENCODERRESOLUTION_360x240	= 2013,
	DVENCODERRESOLUTION_180x120	= 2014,
	DVENCODERRESOLUTION_88x60	= 2015
    } ;

enum _DVENCODERVIDEOFORMAT
    {	DVENCODERVIDEOFORMAT_NTSC	= 2000,
	DVENCODERVIDEOFORMAT_PAL	= 2001
    } ;

enum _DVENCODERFORMAT
    {	DVENCODERFORMAT_DVSD	= 2007,
	DVENCODERFORMAT_DVHD	= 2008,
	DVENCODERFORMAT_DVSL	= 2009
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0346_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0346_v0_0_s_ifspec;

#ifndef __IDVEnc_INTERFACE_DEFINED__
#define __IDVEnc_INTERFACE_DEFINED__

/* interface IDVEnc */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDVEnc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d18e17a0-aacb-11d0-afb0-00aa00b67a42")
    IDVEnc : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_IFormatResolution( 
            /* [out] */ int *VideoFormat,
            /* [out] */ int *DVFormat,
            /* [out] */ int *Resolution,
            /* [in] */ BYTE fDVInfo,
            /* [out] */ DVINFO *sDVInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_IFormatResolution( 
            /* [in] */ int VideoFormat,
            /* [in] */ int DVFormat,
            /* [in] */ int Resolution,
            /* [in] */ BYTE fDVInfo,
            /* [in] */ DVINFO *sDVInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVEncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVEnc * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVEnc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVEnc * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_IFormatResolution )( 
            IDVEnc * This,
            /* [out] */ int *VideoFormat,
            /* [out] */ int *DVFormat,
            /* [out] */ int *Resolution,
            /* [in] */ BYTE fDVInfo,
            /* [out] */ DVINFO *sDVInfo);
        
        HRESULT ( STDMETHODCALLTYPE *put_IFormatResolution )( 
            IDVEnc * This,
            /* [in] */ int VideoFormat,
            /* [in] */ int DVFormat,
            /* [in] */ int Resolution,
            /* [in] */ BYTE fDVInfo,
            /* [in] */ DVINFO *sDVInfo);
        
        END_INTERFACE
    } IDVEncVtbl;

    interface IDVEnc
    {
        CONST_VTBL struct IDVEncVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVEnc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVEnc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVEnc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVEnc_get_IFormatResolution(This,VideoFormat,DVFormat,Resolution,fDVInfo,sDVInfo)	\
    (This)->lpVtbl -> get_IFormatResolution(This,VideoFormat,DVFormat,Resolution,fDVInfo,sDVInfo)

#define IDVEnc_put_IFormatResolution(This,VideoFormat,DVFormat,Resolution,fDVInfo,sDVInfo)	\
    (This)->lpVtbl -> put_IFormatResolution(This,VideoFormat,DVFormat,Resolution,fDVInfo,sDVInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDVEnc_get_IFormatResolution_Proxy( 
    IDVEnc * This,
    /* [out] */ int *VideoFormat,
    /* [out] */ int *DVFormat,
    /* [out] */ int *Resolution,
    /* [in] */ BYTE fDVInfo,
    /* [out] */ DVINFO *sDVInfo);


void __RPC_STUB IDVEnc_get_IFormatResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDVEnc_put_IFormatResolution_Proxy( 
    IDVEnc * This,
    /* [in] */ int VideoFormat,
    /* [in] */ int DVFormat,
    /* [in] */ int Resolution,
    /* [in] */ BYTE fDVInfo,
    /* [in] */ DVINFO *sDVInfo);


void __RPC_STUB IDVEnc_put_IFormatResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVEnc_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0347 */
/* [local] */ 


enum _DVDECODERRESOLUTION
    {	DVDECODERRESOLUTION_720x480	= 1000,
	DVDECODERRESOLUTION_360x240	= 1001,
	DVDECODERRESOLUTION_180x120	= 1002,
	DVDECODERRESOLUTION_88x60	= 1003
    } ;

enum _DVRESOLUTION
    {	DVRESOLUTION_FULL	= 1000,
	DVRESOLUTION_HALF	= 1001,
	DVRESOLUTION_QUARTER	= 1002,
	DVRESOLUTION_DC	= 1003
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0347_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0347_v0_0_s_ifspec;

#ifndef __IIPDVDec_INTERFACE_DEFINED__
#define __IIPDVDec_INTERFACE_DEFINED__

/* interface IIPDVDec */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IIPDVDec;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b8e8bd60-0bfe-11d0-af91-00aa00b67a42")
    IIPDVDec : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_IPDisplay( 
            /* [out] */ int *displayPix) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_IPDisplay( 
            /* [in] */ int displayPix) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIPDVDecVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIPDVDec * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIPDVDec * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIPDVDec * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_IPDisplay )( 
            IIPDVDec * This,
            /* [out] */ int *displayPix);
        
        HRESULT ( STDMETHODCALLTYPE *put_IPDisplay )( 
            IIPDVDec * This,
            /* [in] */ int displayPix);
        
        END_INTERFACE
    } IIPDVDecVtbl;

    interface IIPDVDec
    {
        CONST_VTBL struct IIPDVDecVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPDVDec_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIPDVDec_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIPDVDec_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIPDVDec_get_IPDisplay(This,displayPix)	\
    (This)->lpVtbl -> get_IPDisplay(This,displayPix)

#define IIPDVDec_put_IPDisplay(This,displayPix)	\
    (This)->lpVtbl -> put_IPDisplay(This,displayPix)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IIPDVDec_get_IPDisplay_Proxy( 
    IIPDVDec * This,
    /* [out] */ int *displayPix);


void __RPC_STUB IIPDVDec_get_IPDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IIPDVDec_put_IPDisplay_Proxy( 
    IIPDVDec * This,
    /* [in] */ int displayPix);


void __RPC_STUB IIPDVDec_put_IPDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIPDVDec_INTERFACE_DEFINED__ */


#ifndef __IDVRGB219_INTERFACE_DEFINED__
#define __IDVRGB219_INTERFACE_DEFINED__

/* interface IDVRGB219 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDVRGB219;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58473A19-2BC8-4663-8012-25F81BABDDD1")
    IDVRGB219 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRGB219( 
            /* [in] */ BOOL bState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVRGB219Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVRGB219 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVRGB219 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVRGB219 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRGB219 )( 
            IDVRGB219 * This,
            /* [in] */ BOOL bState);
        
        END_INTERFACE
    } IDVRGB219Vtbl;

    interface IDVRGB219
    {
        CONST_VTBL struct IDVRGB219Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVRGB219_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVRGB219_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVRGB219_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVRGB219_SetRGB219(This,bState)	\
    (This)->lpVtbl -> SetRGB219(This,bState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDVRGB219_SetRGB219_Proxy( 
    IDVRGB219 * This,
    /* [in] */ BOOL bState);


void __RPC_STUB IDVRGB219_SetRGB219_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVRGB219_INTERFACE_DEFINED__ */


#ifndef __IDVSplitter_INTERFACE_DEFINED__
#define __IDVSplitter_INTERFACE_DEFINED__

/* interface IDVSplitter */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDVSplitter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92a3a302-da7c-4a1f-ba7e-1802bb5d2d02")
    IDVSplitter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DiscardAlternateVideoFrames( 
            /* [in] */ int nDiscard) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVSplitterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVSplitter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVSplitter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVSplitter * This);
        
        HRESULT ( STDMETHODCALLTYPE *DiscardAlternateVideoFrames )( 
            IDVSplitter * This,
            /* [in] */ int nDiscard);
        
        END_INTERFACE
    } IDVSplitterVtbl;

    interface IDVSplitter
    {
        CONST_VTBL struct IDVSplitterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVSplitter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDVSplitter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDVSplitter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDVSplitter_DiscardAlternateVideoFrames(This,nDiscard)	\
    (This)->lpVtbl -> DiscardAlternateVideoFrames(This,nDiscard)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDVSplitter_DiscardAlternateVideoFrames_Proxy( 
    IDVSplitter * This,
    /* [in] */ int nDiscard);


void __RPC_STUB IDVSplitter_DiscardAlternateVideoFrames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVSplitter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0350 */
/* [local] */ 


enum _AM_AUDIO_RENDERER_STAT_PARAM
    {	AM_AUDREND_STAT_PARAM_BREAK_COUNT	= 1,
	AM_AUDREND_STAT_PARAM_SLAVE_MODE	= AM_AUDREND_STAT_PARAM_BREAK_COUNT + 1,
	AM_AUDREND_STAT_PARAM_SILENCE_DUR	= AM_AUDREND_STAT_PARAM_SLAVE_MODE + 1,
	AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR	= AM_AUDREND_STAT_PARAM_SILENCE_DUR + 1,
	AM_AUDREND_STAT_PARAM_DISCONTINUITIES	= AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR + 1,
	AM_AUDREND_STAT_PARAM_SLAVE_RATE	= AM_AUDREND_STAT_PARAM_DISCONTINUITIES + 1,
	AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR	= AM_AUDREND_STAT_PARAM_SLAVE_RATE + 1,
	AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR	= AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR + 1,
	AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR	= AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR + 1,
	AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR	= AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR + 1,
	AM_AUDREND_STAT_PARAM_BUFFERFULLNESS	= AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR + 1,
	AM_AUDREND_STAT_PARAM_JITTER	= AM_AUDREND_STAT_PARAM_BUFFERFULLNESS + 1
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0350_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0350_v0_0_s_ifspec;

#ifndef __IAMAudioRendererStats_INTERFACE_DEFINED__
#define __IAMAudioRendererStats_INTERFACE_DEFINED__

/* interface IAMAudioRendererStats */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMAudioRendererStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22320CB2-D41A-11d2-BF7C-D7CB9DF0BF93")
    IAMAudioRendererStats : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetStatParam( 
            /* [in] */ DWORD dwParam,
            /* [out] */ DWORD *pdwParam1,
            /* [out] */ DWORD *pdwParam2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMAudioRendererStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMAudioRendererStats * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMAudioRendererStats * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMAudioRendererStats * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatParam )( 
            IAMAudioRendererStats * This,
            /* [in] */ DWORD dwParam,
            /* [out] */ DWORD *pdwParam1,
            /* [out] */ DWORD *pdwParam2);
        
        END_INTERFACE
    } IAMAudioRendererStatsVtbl;

    interface IAMAudioRendererStats
    {
        CONST_VTBL struct IAMAudioRendererStatsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMAudioRendererStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMAudioRendererStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMAudioRendererStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMAudioRendererStats_GetStatParam(This,dwParam,pdwParam1,pdwParam2)	\
    (This)->lpVtbl -> GetStatParam(This,dwParam,pdwParam1,pdwParam2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMAudioRendererStats_GetStatParam_Proxy( 
    IAMAudioRendererStats * This,
    /* [in] */ DWORD dwParam,
    /* [out] */ DWORD *pdwParam1,
    /* [out] */ DWORD *pdwParam2);


void __RPC_STUB IAMAudioRendererStats_GetStatParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMAudioRendererStats_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0352 */
/* [local] */ 


enum _AM_INTF_SEARCH_FLAGS
    {	AM_INTF_SEARCH_INPUT_PIN	= 0x1,
	AM_INTF_SEARCH_OUTPUT_PIN	= 0x2,
	AM_INTF_SEARCH_FILTER	= 0x4
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0352_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0352_v0_0_s_ifspec;

#ifndef __IAMGraphStreams_INTERFACE_DEFINED__
#define __IAMGraphStreams_INTERFACE_DEFINED__

/* interface IAMGraphStreams */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMGraphStreams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("632105FA-072E-11d3-8AF9-00C04FB6BD3D")
    IAMGraphStreams : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FindUpstreamInterface( 
            /* [in] */ IPin *pPin,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvInterface,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncUsingStreamOffset( 
            /* [in] */ BOOL bUseStreamOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxGraphLatency( 
            /* [in] */ REFERENCE_TIME rtMaxGraphLatency) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMGraphStreamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMGraphStreams * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMGraphStreams * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMGraphStreams * This);
        
        HRESULT ( STDMETHODCALLTYPE *FindUpstreamInterface )( 
            IAMGraphStreams * This,
            /* [in] */ IPin *pPin,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvInterface,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SyncUsingStreamOffset )( 
            IAMGraphStreams * This,
            /* [in] */ BOOL bUseStreamOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetMaxGraphLatency )( 
            IAMGraphStreams * This,
            /* [in] */ REFERENCE_TIME rtMaxGraphLatency);
        
        END_INTERFACE
    } IAMGraphStreamsVtbl;

    interface IAMGraphStreams
    {
        CONST_VTBL struct IAMGraphStreamsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMGraphStreams_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMGraphStreams_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMGraphStreams_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMGraphStreams_FindUpstreamInterface(This,pPin,riid,ppvInterface,dwFlags)	\
    (This)->lpVtbl -> FindUpstreamInterface(This,pPin,riid,ppvInterface,dwFlags)

#define IAMGraphStreams_SyncUsingStreamOffset(This,bUseStreamOffset)	\
    (This)->lpVtbl -> SyncUsingStreamOffset(This,bUseStreamOffset)

#define IAMGraphStreams_SetMaxGraphLatency(This,rtMaxGraphLatency)	\
    (This)->lpVtbl -> SetMaxGraphLatency(This,rtMaxGraphLatency)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMGraphStreams_FindUpstreamInterface_Proxy( 
    IAMGraphStreams * This,
    /* [in] */ IPin *pPin,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppvInterface,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMGraphStreams_FindUpstreamInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMGraphStreams_SyncUsingStreamOffset_Proxy( 
    IAMGraphStreams * This,
    /* [in] */ BOOL bUseStreamOffset);


void __RPC_STUB IAMGraphStreams_SyncUsingStreamOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMGraphStreams_SetMaxGraphLatency_Proxy( 
    IAMGraphStreams * This,
    /* [in] */ REFERENCE_TIME rtMaxGraphLatency);


void __RPC_STUB IAMGraphStreams_SetMaxGraphLatency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMGraphStreams_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0353 */
/* [local] */ 


enum AMOVERLAYFX
    {	AMOVERFX_NOFX	= 0,
	AMOVERFX_MIRRORLEFTRIGHT	= 0x2,
	AMOVERFX_MIRRORUPDOWN	= 0x4,
	AMOVERFX_DEINTERLACE	= 0x8
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0353_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0353_v0_0_s_ifspec;

#ifndef __IAMOverlayFX_INTERFACE_DEFINED__
#define __IAMOverlayFX_INTERFACE_DEFINED__

/* interface IAMOverlayFX */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMOverlayFX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62fae250-7e65-4460-bfc9-6398b322073c")
    IAMOverlayFX : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryOverlayFXCaps( 
            /* [out] */ DWORD *lpdwOverlayFXCaps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOverlayFX( 
            /* [in] */ DWORD dwOverlayFX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOverlayFX( 
            /* [out] */ DWORD *lpdwOverlayFX) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMOverlayFXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMOverlayFX * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMOverlayFX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMOverlayFX * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryOverlayFXCaps )( 
            IAMOverlayFX * This,
            /* [out] */ DWORD *lpdwOverlayFXCaps);
        
        HRESULT ( STDMETHODCALLTYPE *SetOverlayFX )( 
            IAMOverlayFX * This,
            /* [in] */ DWORD dwOverlayFX);
        
        HRESULT ( STDMETHODCALLTYPE *GetOverlayFX )( 
            IAMOverlayFX * This,
            /* [out] */ DWORD *lpdwOverlayFX);
        
        END_INTERFACE
    } IAMOverlayFXVtbl;

    interface IAMOverlayFX
    {
        CONST_VTBL struct IAMOverlayFXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMOverlayFX_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMOverlayFX_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMOverlayFX_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMOverlayFX_QueryOverlayFXCaps(This,lpdwOverlayFXCaps)	\
    (This)->lpVtbl -> QueryOverlayFXCaps(This,lpdwOverlayFXCaps)

#define IAMOverlayFX_SetOverlayFX(This,dwOverlayFX)	\
    (This)->lpVtbl -> SetOverlayFX(This,dwOverlayFX)

#define IAMOverlayFX_GetOverlayFX(This,lpdwOverlayFX)	\
    (This)->lpVtbl -> GetOverlayFX(This,lpdwOverlayFX)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMOverlayFX_QueryOverlayFXCaps_Proxy( 
    IAMOverlayFX * This,
    /* [out] */ DWORD *lpdwOverlayFXCaps);


void __RPC_STUB IAMOverlayFX_QueryOverlayFXCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMOverlayFX_SetOverlayFX_Proxy( 
    IAMOverlayFX * This,
    /* [in] */ DWORD dwOverlayFX);


void __RPC_STUB IAMOverlayFX_SetOverlayFX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMOverlayFX_GetOverlayFX_Proxy( 
    IAMOverlayFX * This,
    /* [out] */ DWORD *lpdwOverlayFX);


void __RPC_STUB IAMOverlayFX_GetOverlayFX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMOverlayFX_INTERFACE_DEFINED__ */


#ifndef __IAMOpenProgress_INTERFACE_DEFINED__
#define __IAMOpenProgress_INTERFACE_DEFINED__

/* interface IAMOpenProgress */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMOpenProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E1C39A1-DE53-11cf-AA63-0080C744528D")
    IAMOpenProgress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryProgress( 
            /* [out] */ LONGLONG *pllTotal,
            /* [out] */ LONGLONG *pllCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AbortOperation( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMOpenProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMOpenProgress * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMOpenProgress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMOpenProgress * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryProgress )( 
            IAMOpenProgress * This,
            /* [out] */ LONGLONG *pllTotal,
            /* [out] */ LONGLONG *pllCurrent);
        
        HRESULT ( STDMETHODCALLTYPE *AbortOperation )( 
            IAMOpenProgress * This);
        
        END_INTERFACE
    } IAMOpenProgressVtbl;

    interface IAMOpenProgress
    {
        CONST_VTBL struct IAMOpenProgressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMOpenProgress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMOpenProgress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMOpenProgress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMOpenProgress_QueryProgress(This,pllTotal,pllCurrent)	\
    (This)->lpVtbl -> QueryProgress(This,pllTotal,pllCurrent)

#define IAMOpenProgress_AbortOperation(This)	\
    (This)->lpVtbl -> AbortOperation(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMOpenProgress_QueryProgress_Proxy( 
    IAMOpenProgress * This,
    /* [out] */ LONGLONG *pllTotal,
    /* [out] */ LONGLONG *pllCurrent);


void __RPC_STUB IAMOpenProgress_QueryProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMOpenProgress_AbortOperation_Proxy( 
    IAMOpenProgress * This);


void __RPC_STUB IAMOpenProgress_AbortOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMOpenProgress_INTERFACE_DEFINED__ */


#ifndef __IMpeg2Demultiplexer_INTERFACE_DEFINED__
#define __IMpeg2Demultiplexer_INTERFACE_DEFINED__

/* interface IMpeg2Demultiplexer */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IMpeg2Demultiplexer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("436eee9c-264f-4242-90e1-4e330c107512")
    IMpeg2Demultiplexer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateOutputPin( 
            /* [in] */ AM_MEDIA_TYPE *pMediaType,
            /* [in] */ LPWSTR pszPinName,
            /* [out] */ IPin **ppIPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputPinMediaType( 
            /* [in] */ LPWSTR pszPinName,
            /* [in] */ AM_MEDIA_TYPE *pMediaType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteOutputPin( 
            /* [in] */ LPWSTR pszPinName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMpeg2DemultiplexerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMpeg2Demultiplexer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMpeg2Demultiplexer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMpeg2Demultiplexer * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateOutputPin )( 
            IMpeg2Demultiplexer * This,
            /* [in] */ AM_MEDIA_TYPE *pMediaType,
            /* [in] */ LPWSTR pszPinName,
            /* [out] */ IPin **ppIPin);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputPinMediaType )( 
            IMpeg2Demultiplexer * This,
            /* [in] */ LPWSTR pszPinName,
            /* [in] */ AM_MEDIA_TYPE *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteOutputPin )( 
            IMpeg2Demultiplexer * This,
            /* [in] */ LPWSTR pszPinName);
        
        END_INTERFACE
    } IMpeg2DemultiplexerVtbl;

    interface IMpeg2Demultiplexer
    {
        CONST_VTBL struct IMpeg2DemultiplexerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMpeg2Demultiplexer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMpeg2Demultiplexer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMpeg2Demultiplexer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMpeg2Demultiplexer_CreateOutputPin(This,pMediaType,pszPinName,ppIPin)	\
    (This)->lpVtbl -> CreateOutputPin(This,pMediaType,pszPinName,ppIPin)

#define IMpeg2Demultiplexer_SetOutputPinMediaType(This,pszPinName,pMediaType)	\
    (This)->lpVtbl -> SetOutputPinMediaType(This,pszPinName,pMediaType)

#define IMpeg2Demultiplexer_DeleteOutputPin(This,pszPinName)	\
    (This)->lpVtbl -> DeleteOutputPin(This,pszPinName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMpeg2Demultiplexer_CreateOutputPin_Proxy( 
    IMpeg2Demultiplexer * This,
    /* [in] */ AM_MEDIA_TYPE *pMediaType,
    /* [in] */ LPWSTR pszPinName,
    /* [out] */ IPin **ppIPin);


void __RPC_STUB IMpeg2Demultiplexer_CreateOutputPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMpeg2Demultiplexer_SetOutputPinMediaType_Proxy( 
    IMpeg2Demultiplexer * This,
    /* [in] */ LPWSTR pszPinName,
    /* [in] */ AM_MEDIA_TYPE *pMediaType);


void __RPC_STUB IMpeg2Demultiplexer_SetOutputPinMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMpeg2Demultiplexer_DeleteOutputPin_Proxy( 
    IMpeg2Demultiplexer * This,
    /* [in] */ LPWSTR pszPinName);


void __RPC_STUB IMpeg2Demultiplexer_DeleteOutputPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMpeg2Demultiplexer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0356 */
/* [local] */ 

#define MPEG2_PROGRAM_STREAM_MAP                 0x00000000
#define MPEG2_PROGRAM_ELEMENTARY_STREAM          0x00000001
#define MPEG2_PROGRAM_DIRECTORY_PES_PACKET       0x00000002
#define MPEG2_PROGRAM_PACK_HEADER                0x00000003
#define MPEG2_PROGRAM_PES_STREAM                 0x00000004
#define MPEG2_PROGRAM_SYSTEM_HEADER              0x00000005
#define SUBSTREAM_FILTER_VAL_NONE                0x10000000
typedef /* [public][public] */ struct __MIDL___MIDL_itf_strmif_0356_0001
    {
    ULONG stream_id;
    DWORD dwMediaSampleContent;
    ULONG ulSubstreamFilterValue;
    int iDataOffset;
    } 	STREAM_ID_MAP;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0356_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0356_v0_0_s_ifspec;

#ifndef __IEnumStreamIdMap_INTERFACE_DEFINED__
#define __IEnumStreamIdMap_INTERFACE_DEFINED__

/* interface IEnumStreamIdMap */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IEnumStreamIdMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("945C1566-6202-46fc-96C7-D87F289C6534")
    IEnumStreamIdMap : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cRequest,
            /* [size_is][out][in] */ STREAM_ID_MAP *pStreamIdMap,
            /* [out] */ ULONG *pcReceived) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumStreamIdMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumStreamIdMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumStreamIdMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumStreamIdMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumStreamIdMap * This,
            /* [in] */ ULONG cRequest,
            /* [size_is][out][in] */ STREAM_ID_MAP *pStreamIdMap,
            /* [out] */ ULONG *pcReceived);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumStreamIdMap * This,
            /* [in] */ ULONG cRecords);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumStreamIdMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumStreamIdMap * This,
            /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap);
        
        END_INTERFACE
    } IEnumStreamIdMapVtbl;

    interface IEnumStreamIdMap
    {
        CONST_VTBL struct IEnumStreamIdMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumStreamIdMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumStreamIdMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumStreamIdMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumStreamIdMap_Next(This,cRequest,pStreamIdMap,pcReceived)	\
    (This)->lpVtbl -> Next(This,cRequest,pStreamIdMap,pcReceived)

#define IEnumStreamIdMap_Skip(This,cRecords)	\
    (This)->lpVtbl -> Skip(This,cRecords)

#define IEnumStreamIdMap_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumStreamIdMap_Clone(This,ppIEnumStreamIdMap)	\
    (This)->lpVtbl -> Clone(This,ppIEnumStreamIdMap)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumStreamIdMap_Next_Proxy( 
    IEnumStreamIdMap * This,
    /* [in] */ ULONG cRequest,
    /* [size_is][out][in] */ STREAM_ID_MAP *pStreamIdMap,
    /* [out] */ ULONG *pcReceived);


void __RPC_STUB IEnumStreamIdMap_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumStreamIdMap_Skip_Proxy( 
    IEnumStreamIdMap * This,
    /* [in] */ ULONG cRecords);


void __RPC_STUB IEnumStreamIdMap_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumStreamIdMap_Reset_Proxy( 
    IEnumStreamIdMap * This);


void __RPC_STUB IEnumStreamIdMap_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumStreamIdMap_Clone_Proxy( 
    IEnumStreamIdMap * This,
    /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap);


void __RPC_STUB IEnumStreamIdMap_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumStreamIdMap_INTERFACE_DEFINED__ */


#ifndef __IMPEG2StreamIdMap_INTERFACE_DEFINED__
#define __IMPEG2StreamIdMap_INTERFACE_DEFINED__

/* interface IMPEG2StreamIdMap */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IMPEG2StreamIdMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0E04C47-25B8-4369-925A-362A01D95444")
    IMPEG2StreamIdMap : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MapStreamId( 
            /* [in] */ ULONG ulStreamId,
            /* [in] */ DWORD MediaSampleContent,
            /* [in] */ ULONG ulSubstreamFilterValue,
            /* [in] */ int iDataOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnmapStreamId( 
            /* [in] */ ULONG culStreamId,
            /* [in] */ ULONG *pulStreamId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumStreamIdMap( 
            /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2StreamIdMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2StreamIdMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2StreamIdMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2StreamIdMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *MapStreamId )( 
            IMPEG2StreamIdMap * This,
            /* [in] */ ULONG ulStreamId,
            /* [in] */ DWORD MediaSampleContent,
            /* [in] */ ULONG ulSubstreamFilterValue,
            /* [in] */ int iDataOffset);
        
        HRESULT ( STDMETHODCALLTYPE *UnmapStreamId )( 
            IMPEG2StreamIdMap * This,
            /* [in] */ ULONG culStreamId,
            /* [in] */ ULONG *pulStreamId);
        
        HRESULT ( STDMETHODCALLTYPE *EnumStreamIdMap )( 
            IMPEG2StreamIdMap * This,
            /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap);
        
        END_INTERFACE
    } IMPEG2StreamIdMapVtbl;

    interface IMPEG2StreamIdMap
    {
        CONST_VTBL struct IMPEG2StreamIdMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2StreamIdMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2StreamIdMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2StreamIdMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2StreamIdMap_MapStreamId(This,ulStreamId,MediaSampleContent,ulSubstreamFilterValue,iDataOffset)	\
    (This)->lpVtbl -> MapStreamId(This,ulStreamId,MediaSampleContent,ulSubstreamFilterValue,iDataOffset)

#define IMPEG2StreamIdMap_UnmapStreamId(This,culStreamId,pulStreamId)	\
    (This)->lpVtbl -> UnmapStreamId(This,culStreamId,pulStreamId)

#define IMPEG2StreamIdMap_EnumStreamIdMap(This,ppIEnumStreamIdMap)	\
    (This)->lpVtbl -> EnumStreamIdMap(This,ppIEnumStreamIdMap)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMPEG2StreamIdMap_MapStreamId_Proxy( 
    IMPEG2StreamIdMap * This,
    /* [in] */ ULONG ulStreamId,
    /* [in] */ DWORD MediaSampleContent,
    /* [in] */ ULONG ulSubstreamFilterValue,
    /* [in] */ int iDataOffset);


void __RPC_STUB IMPEG2StreamIdMap_MapStreamId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMPEG2StreamIdMap_UnmapStreamId_Proxy( 
    IMPEG2StreamIdMap * This,
    /* [in] */ ULONG culStreamId,
    /* [in] */ ULONG *pulStreamId);


void __RPC_STUB IMPEG2StreamIdMap_UnmapStreamId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMPEG2StreamIdMap_EnumStreamIdMap_Proxy( 
    IMPEG2StreamIdMap * This,
    /* [out] */ IEnumStreamIdMap **ppIEnumStreamIdMap);


void __RPC_STUB IMPEG2StreamIdMap_EnumStreamIdMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2StreamIdMap_INTERFACE_DEFINED__ */


#ifndef __IRegisterServiceProvider_INTERFACE_DEFINED__
#define __IRegisterServiceProvider_INTERFACE_DEFINED__

/* interface IRegisterServiceProvider */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IRegisterServiceProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B3A2F01-0751-48DD-B556-004785171C54")
    IRegisterServiceProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterService( 
            /* [in] */ REFGUID guidService,
            /* [in] */ IUnknown *pUnkObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRegisterServiceProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRegisterServiceProvider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRegisterServiceProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRegisterServiceProvider * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterService )( 
            IRegisterServiceProvider * This,
            /* [in] */ REFGUID guidService,
            /* [in] */ IUnknown *pUnkObject);
        
        END_INTERFACE
    } IRegisterServiceProviderVtbl;

    interface IRegisterServiceProvider
    {
        CONST_VTBL struct IRegisterServiceProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRegisterServiceProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRegisterServiceProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRegisterServiceProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRegisterServiceProvider_RegisterService(This,guidService,pUnkObject)	\
    (This)->lpVtbl -> RegisterService(This,guidService,pUnkObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRegisterServiceProvider_RegisterService_Proxy( 
    IRegisterServiceProvider * This,
    /* [in] */ REFGUID guidService,
    /* [in] */ IUnknown *pUnkObject);


void __RPC_STUB IRegisterServiceProvider_RegisterService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRegisterServiceProvider_INTERFACE_DEFINED__ */


#ifndef __IAMClockSlave_INTERFACE_DEFINED__
#define __IAMClockSlave_INTERFACE_DEFINED__

/* interface IAMClockSlave */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMClockSlave;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9FD52741-176D-4b36-8F51-CA8F933223BE")
    IAMClockSlave : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetErrorTolerance( 
            /* [in] */ DWORD dwTolerance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorTolerance( 
            /* [out] */ DWORD *pdwTolerance) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMClockSlaveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMClockSlave * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMClockSlave * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMClockSlave * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorTolerance )( 
            IAMClockSlave * This,
            /* [in] */ DWORD dwTolerance);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorTolerance )( 
            IAMClockSlave * This,
            /* [out] */ DWORD *pdwTolerance);
        
        END_INTERFACE
    } IAMClockSlaveVtbl;

    interface IAMClockSlave
    {
        CONST_VTBL struct IAMClockSlaveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMClockSlave_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMClockSlave_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMClockSlave_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMClockSlave_SetErrorTolerance(This,dwTolerance)	\
    (This)->lpVtbl -> SetErrorTolerance(This,dwTolerance)

#define IAMClockSlave_GetErrorTolerance(This,pdwTolerance)	\
    (This)->lpVtbl -> GetErrorTolerance(This,pdwTolerance)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMClockSlave_SetErrorTolerance_Proxy( 
    IAMClockSlave * This,
    /* [in] */ DWORD dwTolerance);


void __RPC_STUB IAMClockSlave_SetErrorTolerance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMClockSlave_GetErrorTolerance_Proxy( 
    IAMClockSlave * This,
    /* [out] */ DWORD *pdwTolerance);


void __RPC_STUB IAMClockSlave_GetErrorTolerance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMClockSlave_INTERFACE_DEFINED__ */


#ifndef __IAMGraphBuilderCallback_INTERFACE_DEFINED__
#define __IAMGraphBuilderCallback_INTERFACE_DEFINED__

/* interface IAMGraphBuilderCallback */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IAMGraphBuilderCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4995f511-9ddb-4f12-bd3b-f04611807b79")
    IAMGraphBuilderCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SelectedFilter( 
            /* [in] */ IMoniker *pMon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreatedFilter( 
            /* [in] */ IBaseFilter *pFil) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMGraphBuilderCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMGraphBuilderCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMGraphBuilderCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMGraphBuilderCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectedFilter )( 
            IAMGraphBuilderCallback * This,
            /* [in] */ IMoniker *pMon);
        
        HRESULT ( STDMETHODCALLTYPE *CreatedFilter )( 
            IAMGraphBuilderCallback * This,
            /* [in] */ IBaseFilter *pFil);
        
        END_INTERFACE
    } IAMGraphBuilderCallbackVtbl;

    interface IAMGraphBuilderCallback
    {
        CONST_VTBL struct IAMGraphBuilderCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMGraphBuilderCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMGraphBuilderCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMGraphBuilderCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMGraphBuilderCallback_SelectedFilter(This,pMon)	\
    (This)->lpVtbl -> SelectedFilter(This,pMon)

#define IAMGraphBuilderCallback_CreatedFilter(This,pFil)	\
    (This)->lpVtbl -> CreatedFilter(This,pFil)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMGraphBuilderCallback_SelectedFilter_Proxy( 
    IAMGraphBuilderCallback * This,
    /* [in] */ IMoniker *pMon);


void __RPC_STUB IAMGraphBuilderCallback_SelectedFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMGraphBuilderCallback_CreatedFilter_Proxy( 
    IAMGraphBuilderCallback * This,
    /* [in] */ IBaseFilter *pFil);


void __RPC_STUB IAMGraphBuilderCallback_CreatedFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMGraphBuilderCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0361 */
/* [local] */ 

#ifdef __cplusplus
#ifndef _IAMFilterGraphCallback_
#define _IAMFilterGraphCallback_
// Note: Because this interface was not defined as a proper interface it is
//       supported under C++ only. Methods aren't stdcall.
EXTERN_GUID(IID_IAMFilterGraphCallback,0x56a868fd,0x0ad4,0x11ce,0xb0,0xa3,0x0,0x20,0xaf,0x0b,0xa7,0x70);
interface IAMFilterGraphCallback : public IUnknown
{
    // S_OK means rendering complete, S_FALSE means retry now.
    virtual HRESULT UnableToRender(IPin *pPin) = 0;
 
};
#endif // _IAMFilterGraphCallback_
#endif
struct CodecAPIEventData
    {
    GUID guid;
    DWORD dataLength;
    DWORD reserved[ 3 ];
    } ;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0361_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0361_v0_0_s_ifspec;

#ifndef __ICodecAPI_INTERFACE_DEFINED__
#define __ICodecAPI_INTERFACE_DEFINED__

/* interface ICodecAPI */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICodecAPI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("901db4c7-31ce-41a2-85dc-8fa0bf41b8da")
    ICodecAPI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsSupported( 
            /* [in] */ const GUID *Api) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsModifiable( 
            /* [in] */ const GUID *Api) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameterRange( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *ValueMin,
            /* [out] */ VARIANT *ValueMax,
            /* [out] */ VARIANT *SteppingDelta) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameterValues( 
            /* [in] */ const GUID *Api,
            /* [size_is][size_is][out] */ VARIANT **Values,
            /* [out] */ ULONG *ValuesCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultValue( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterForEvent( 
            /* [in] */ const GUID *Api,
            /* [in] */ LONG_PTR userData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterForEvent( 
            /* [in] */ const GUID *Api) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAllDefaults( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValueWithNotify( 
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value,
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAllDefaultsWithNotify( 
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllSettings( 
            /* [in] */ IStream *__MIDL_0016) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAllSettings( 
            /* [in] */ IStream *__MIDL_0017) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAllSettingsWithNotify( 
            IStream *__MIDL_0018,
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICodecAPIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICodecAPI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICodecAPI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICodecAPI * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSupported )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *IsModifiable )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterRange )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *ValueMin,
            /* [out] */ VARIANT *ValueMax,
            /* [out] */ VARIANT *SteppingDelta);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterValues )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [size_is][size_is][out] */ VARIANT **Values,
            /* [out] */ ULONG *ValuesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultValue )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterForEvent )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [in] */ LONG_PTR userData);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterForEvent )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *SetAllDefaults )( 
            ICodecAPI * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetValueWithNotify )( 
            ICodecAPI * This,
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value,
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetAllDefaultsWithNotify )( 
            ICodecAPI * This,
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllSettings )( 
            ICodecAPI * This,
            /* [in] */ IStream *__MIDL_0016);
        
        HRESULT ( STDMETHODCALLTYPE *SetAllSettings )( 
            ICodecAPI * This,
            /* [in] */ IStream *__MIDL_0017);
        
        HRESULT ( STDMETHODCALLTYPE *SetAllSettingsWithNotify )( 
            ICodecAPI * This,
            IStream *__MIDL_0018,
            /* [size_is][size_is][out] */ GUID **ChangedParam,
            /* [out] */ ULONG *ChangedParamCount);
        
        END_INTERFACE
    } ICodecAPIVtbl;

    interface ICodecAPI
    {
        CONST_VTBL struct ICodecAPIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICodecAPI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICodecAPI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICodecAPI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICodecAPI_IsSupported(This,Api)	\
    (This)->lpVtbl -> IsSupported(This,Api)

#define ICodecAPI_IsModifiable(This,Api)	\
    (This)->lpVtbl -> IsModifiable(This,Api)

#define ICodecAPI_GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)	\
    (This)->lpVtbl -> GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)

#define ICodecAPI_GetParameterValues(This,Api,Values,ValuesCount)	\
    (This)->lpVtbl -> GetParameterValues(This,Api,Values,ValuesCount)

#define ICodecAPI_GetDefaultValue(This,Api,Value)	\
    (This)->lpVtbl -> GetDefaultValue(This,Api,Value)

#define ICodecAPI_GetValue(This,Api,Value)	\
    (This)->lpVtbl -> GetValue(This,Api,Value)

#define ICodecAPI_SetValue(This,Api,Value)	\
    (This)->lpVtbl -> SetValue(This,Api,Value)

#define ICodecAPI_RegisterForEvent(This,Api,userData)	\
    (This)->lpVtbl -> RegisterForEvent(This,Api,userData)

#define ICodecAPI_UnregisterForEvent(This,Api)	\
    (This)->lpVtbl -> UnregisterForEvent(This,Api)

#define ICodecAPI_SetAllDefaults(This)	\
    (This)->lpVtbl -> SetAllDefaults(This)

#define ICodecAPI_SetValueWithNotify(This,Api,Value,ChangedParam,ChangedParamCount)	\
    (This)->lpVtbl -> SetValueWithNotify(This,Api,Value,ChangedParam,ChangedParamCount)

#define ICodecAPI_SetAllDefaultsWithNotify(This,ChangedParam,ChangedParamCount)	\
    (This)->lpVtbl -> SetAllDefaultsWithNotify(This,ChangedParam,ChangedParamCount)

#define ICodecAPI_GetAllSettings(This,__MIDL_0016)	\
    (This)->lpVtbl -> GetAllSettings(This,__MIDL_0016)

#define ICodecAPI_SetAllSettings(This,__MIDL_0017)	\
    (This)->lpVtbl -> SetAllSettings(This,__MIDL_0017)

#define ICodecAPI_SetAllSettingsWithNotify(This,__MIDL_0018,ChangedParam,ChangedParamCount)	\
    (This)->lpVtbl -> SetAllSettingsWithNotify(This,__MIDL_0018,ChangedParam,ChangedParamCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICodecAPI_IsSupported_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api);


void __RPC_STUB ICodecAPI_IsSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_IsModifiable_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api);


void __RPC_STUB ICodecAPI_IsModifiable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_GetParameterRange_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *ValueMin,
    /* [out] */ VARIANT *ValueMax,
    /* [out] */ VARIANT *SteppingDelta);


void __RPC_STUB ICodecAPI_GetParameterRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_GetParameterValues_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [size_is][size_is][out] */ VARIANT **Values,
    /* [out] */ ULONG *ValuesCount);


void __RPC_STUB ICodecAPI_GetParameterValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_GetDefaultValue_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *Value);


void __RPC_STUB ICodecAPI_GetDefaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_GetValue_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *Value);


void __RPC_STUB ICodecAPI_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetValue_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [in] */ VARIANT *Value);


void __RPC_STUB ICodecAPI_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_RegisterForEvent_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [in] */ LONG_PTR userData);


void __RPC_STUB ICodecAPI_RegisterForEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_UnregisterForEvent_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api);


void __RPC_STUB ICodecAPI_UnregisterForEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetAllDefaults_Proxy( 
    ICodecAPI * This);


void __RPC_STUB ICodecAPI_SetAllDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetValueWithNotify_Proxy( 
    ICodecAPI * This,
    /* [in] */ const GUID *Api,
    /* [in] */ VARIANT *Value,
    /* [size_is][size_is][out] */ GUID **ChangedParam,
    /* [out] */ ULONG *ChangedParamCount);


void __RPC_STUB ICodecAPI_SetValueWithNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetAllDefaultsWithNotify_Proxy( 
    ICodecAPI * This,
    /* [size_is][size_is][out] */ GUID **ChangedParam,
    /* [out] */ ULONG *ChangedParamCount);


void __RPC_STUB ICodecAPI_SetAllDefaultsWithNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_GetAllSettings_Proxy( 
    ICodecAPI * This,
    /* [in] */ IStream *__MIDL_0016);


void __RPC_STUB ICodecAPI_GetAllSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetAllSettings_Proxy( 
    ICodecAPI * This,
    /* [in] */ IStream *__MIDL_0017);


void __RPC_STUB ICodecAPI_SetAllSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICodecAPI_SetAllSettingsWithNotify_Proxy( 
    ICodecAPI * This,
    IStream *__MIDL_0018,
    /* [size_is][size_is][out] */ GUID **ChangedParam,
    /* [out] */ ULONG *ChangedParamCount);


void __RPC_STUB ICodecAPI_SetAllSettingsWithNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICodecAPI_INTERFACE_DEFINED__ */


#ifndef __IGetCapabilitiesKey_INTERFACE_DEFINED__
#define __IGetCapabilitiesKey_INTERFACE_DEFINED__

/* interface IGetCapabilitiesKey */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IGetCapabilitiesKey;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a8809222-07bb-48ea-951c-33158100625b")
    IGetCapabilitiesKey : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCapabilitiesKey( 
            /* [out] */ HKEY *pHKey) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetCapabilitiesKeyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetCapabilitiesKey * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetCapabilitiesKey * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetCapabilitiesKey * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCapabilitiesKey )( 
            IGetCapabilitiesKey * This,
            /* [out] */ HKEY *pHKey);
        
        END_INTERFACE
    } IGetCapabilitiesKeyVtbl;

    interface IGetCapabilitiesKey
    {
        CONST_VTBL struct IGetCapabilitiesKeyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetCapabilitiesKey_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGetCapabilitiesKey_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGetCapabilitiesKey_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGetCapabilitiesKey_GetCapabilitiesKey(This,pHKey)	\
    (This)->lpVtbl -> GetCapabilitiesKey(This,pHKey)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGetCapabilitiesKey_GetCapabilitiesKey_Proxy( 
    IGetCapabilitiesKey * This,
    /* [out] */ HKEY *pHKey);


void __RPC_STUB IGetCapabilitiesKey_GetCapabilitiesKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGetCapabilitiesKey_INTERFACE_DEFINED__ */


#ifndef __IEncoderAPI_INTERFACE_DEFINED__
#define __IEncoderAPI_INTERFACE_DEFINED__

/* interface IEncoderAPI */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEncoderAPI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70423839-6ACC-4b23-B079-21DBF08156A5")
    IEncoderAPI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsSupported( 
            /* [in] */ const GUID *Api) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsAvailable( 
            /* [in] */ const GUID *Api) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameterRange( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *ValueMin,
            /* [out] */ VARIANT *ValueMax,
            /* [out] */ VARIANT *SteppingDelta) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParameterValues( 
            /* [in] */ const GUID *Api,
            /* [size_is][size_is][out] */ VARIANT **Values,
            /* [out] */ ULONG *ValuesCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultValue( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEncoderAPIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEncoderAPI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEncoderAPI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEncoderAPI * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSupported )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *IsAvailable )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterRange )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *ValueMin,
            /* [out] */ VARIANT *ValueMax,
            /* [out] */ VARIANT *SteppingDelta);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterValues )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api,
            /* [size_is][size_is][out] */ VARIANT **Values,
            /* [out] */ ULONG *ValuesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultValue )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IEncoderAPI * This,
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value);
        
        END_INTERFACE
    } IEncoderAPIVtbl;

    interface IEncoderAPI
    {
        CONST_VTBL struct IEncoderAPIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEncoderAPI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEncoderAPI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEncoderAPI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEncoderAPI_IsSupported(This,Api)	\
    (This)->lpVtbl -> IsSupported(This,Api)

#define IEncoderAPI_IsAvailable(This,Api)	\
    (This)->lpVtbl -> IsAvailable(This,Api)

#define IEncoderAPI_GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)	\
    (This)->lpVtbl -> GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)

#define IEncoderAPI_GetParameterValues(This,Api,Values,ValuesCount)	\
    (This)->lpVtbl -> GetParameterValues(This,Api,Values,ValuesCount)

#define IEncoderAPI_GetDefaultValue(This,Api,Value)	\
    (This)->lpVtbl -> GetDefaultValue(This,Api,Value)

#define IEncoderAPI_GetValue(This,Api,Value)	\
    (This)->lpVtbl -> GetValue(This,Api,Value)

#define IEncoderAPI_SetValue(This,Api,Value)	\
    (This)->lpVtbl -> SetValue(This,Api,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEncoderAPI_IsSupported_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api);


void __RPC_STUB IEncoderAPI_IsSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_IsAvailable_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api);


void __RPC_STUB IEncoderAPI_IsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_GetParameterRange_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *ValueMin,
    /* [out] */ VARIANT *ValueMax,
    /* [out] */ VARIANT *SteppingDelta);


void __RPC_STUB IEncoderAPI_GetParameterRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_GetParameterValues_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api,
    /* [size_is][size_is][out] */ VARIANT **Values,
    /* [out] */ ULONG *ValuesCount);


void __RPC_STUB IEncoderAPI_GetParameterValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_GetDefaultValue_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *Value);


void __RPC_STUB IEncoderAPI_GetDefaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_GetValue_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api,
    /* [out] */ VARIANT *Value);


void __RPC_STUB IEncoderAPI_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEncoderAPI_SetValue_Proxy( 
    IEncoderAPI * This,
    /* [in] */ const GUID *Api,
    /* [in] */ VARIANT *Value);


void __RPC_STUB IEncoderAPI_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEncoderAPI_INTERFACE_DEFINED__ */


#ifndef __IVideoEncoder_INTERFACE_DEFINED__
#define __IVideoEncoder_INTERFACE_DEFINED__

/* interface IVideoEncoder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideoEncoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("02997C3B-8E1B-460e-9270-545E0DE9563E")
    IVideoEncoder : public IEncoderAPI
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IVideoEncoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideoEncoder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideoEncoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideoEncoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSupported )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *IsAvailable )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterRange )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *ValueMin,
            /* [out] */ VARIANT *ValueMax,
            /* [out] */ VARIANT *SteppingDelta);
        
        HRESULT ( STDMETHODCALLTYPE *GetParameterValues )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api,
            /* [size_is][size_is][out] */ VARIANT **Values,
            /* [out] */ ULONG *ValuesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultValue )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api,
            /* [out] */ VARIANT *Value);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IVideoEncoder * This,
            /* [in] */ const GUID *Api,
            /* [in] */ VARIANT *Value);
        
        END_INTERFACE
    } IVideoEncoderVtbl;

    interface IVideoEncoder
    {
        CONST_VTBL struct IVideoEncoderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoEncoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoEncoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoEncoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoEncoder_IsSupported(This,Api)	\
    (This)->lpVtbl -> IsSupported(This,Api)

#define IVideoEncoder_IsAvailable(This,Api)	\
    (This)->lpVtbl -> IsAvailable(This,Api)

#define IVideoEncoder_GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)	\
    (This)->lpVtbl -> GetParameterRange(This,Api,ValueMin,ValueMax,SteppingDelta)

#define IVideoEncoder_GetParameterValues(This,Api,Values,ValuesCount)	\
    (This)->lpVtbl -> GetParameterValues(This,Api,Values,ValuesCount)

#define IVideoEncoder_GetDefaultValue(This,Api,Value)	\
    (This)->lpVtbl -> GetDefaultValue(This,Api,Value)

#define IVideoEncoder_GetValue(This,Api,Value)	\
    (This)->lpVtbl -> GetValue(This,Api,Value)

#define IVideoEncoder_SetValue(This,Api,Value)	\
    (This)->lpVtbl -> SetValue(This,Api,Value)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideoEncoder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0365 */
/* [local] */ 

#ifndef __ENCODER_API_DEFINES__
#define __ENCODER_API_DEFINES__
typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0365_0001
    {	ConstantBitRate	= 0,
	VariableBitRateAverage	= ConstantBitRate + 1,
	VariableBitRatePeak	= VariableBitRateAverage + 1
    } 	VIDEOENCODER_BITRATE_MODE;

#endif // __ENCODER_API_DEFINES__
#define AM_GETDECODERCAP_QUERY_VMR_SUPPORT   0x00000001
#define      VMR_NOTSUPPORTED                0x00000000
#define      VMR_SUPPORTED                   0x00000001
#define AM_QUERY_DECODER_VMR_SUPPORT         0x00000001
#define AM_QUERY_DECODER_DXVA_1_SUPPORT      0x00000002
#define AM_QUERY_DECODER_DVD_SUPPORT         0x00000003
#define AM_QUERY_DECODER_ATSC_SD_SUPPORT     0x00000004
#define AM_QUERY_DECODER_ATSC_HD_SUPPORT     0x00000005
#define AM_GETDECODERCAP_QUERY_VMR9_SUPPORT  0x00000006
#define      DECODER_CAP_NOTSUPPORTED        0x00000000
#define      DECODER_CAP_SUPPORTED           0x00000001


extern RPC_IF_HANDLE __MIDL_itf_strmif_0365_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0365_v0_0_s_ifspec;

#ifndef __IAMDecoderCaps_INTERFACE_DEFINED__
#define __IAMDecoderCaps_INTERFACE_DEFINED__

/* interface IAMDecoderCaps */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IAMDecoderCaps;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c0dff467-d499-4986-972b-e1d9090fa941")
    IAMDecoderCaps : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDecoderCaps( 
            /* [in] */ DWORD dwCapIndex,
            /* [out] */ DWORD *lpdwCap) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDecoderCapsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMDecoderCaps * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMDecoderCaps * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMDecoderCaps * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDecoderCaps )( 
            IAMDecoderCaps * This,
            /* [in] */ DWORD dwCapIndex,
            /* [out] */ DWORD *lpdwCap);
        
        END_INTERFACE
    } IAMDecoderCapsVtbl;

    interface IAMDecoderCaps
    {
        CONST_VTBL struct IAMDecoderCapsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDecoderCaps_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDecoderCaps_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDecoderCaps_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDecoderCaps_GetDecoderCaps(This,dwCapIndex,lpdwCap)	\
    (This)->lpVtbl -> GetDecoderCaps(This,dwCapIndex,lpdwCap)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDecoderCaps_GetDecoderCaps_Proxy( 
    IAMDecoderCaps * This,
    /* [in] */ DWORD dwCapIndex,
    /* [out] */ DWORD *lpdwCap);


void __RPC_STUB IAMDecoderCaps_GetDecoderCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDecoderCaps_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0366 */
/* [local] */ 

#include <ddraw.h>









typedef 
enum tagDVD_DOMAIN
    {	DVD_DOMAIN_FirstPlay	= 1,
	DVD_DOMAIN_VideoManagerMenu	= DVD_DOMAIN_FirstPlay + 1,
	DVD_DOMAIN_VideoTitleSetMenu	= DVD_DOMAIN_VideoManagerMenu + 1,
	DVD_DOMAIN_Title	= DVD_DOMAIN_VideoTitleSetMenu + 1,
	DVD_DOMAIN_Stop	= DVD_DOMAIN_Title + 1
    } 	DVD_DOMAIN;

typedef 
enum tagDVD_MENU_ID
    {	DVD_MENU_Title	= 2,
	DVD_MENU_Root	= 3,
	DVD_MENU_Subpicture	= 4,
	DVD_MENU_Audio	= 5,
	DVD_MENU_Angle	= 6,
	DVD_MENU_Chapter	= 7
    } 	DVD_MENU_ID;

typedef 
enum tagDVD_DISC_SIDE
    {	DVD_SIDE_A	= 1,
	DVD_SIDE_B	= 2
    } 	DVD_DISC_SIDE;

typedef 
enum tagDVD_PREFERRED_DISPLAY_MODE
    {	DISPLAY_CONTENT_DEFAULT	= 0,
	DISPLAY_16x9	= 1,
	DISPLAY_4x3_PANSCAN_PREFERRED	= 2,
	DISPLAY_4x3_LETTERBOX_PREFERRED	= 3
    } 	DVD_PREFERRED_DISPLAY_MODE;

typedef WORD DVD_REGISTER;

typedef DVD_REGISTER GPRMARRAY[ 16 ];

typedef DVD_REGISTER SPRMARRAY[ 24 ];

typedef struct tagDVD_ATR
    {
    ULONG ulCAT;
    BYTE pbATRI[ 768 ];
    } 	DVD_ATR;

typedef BYTE DVD_VideoATR[ 2 ];

typedef BYTE DVD_AudioATR[ 8 ];

typedef BYTE DVD_SubpictureATR[ 6 ];

typedef 
enum tagDVD_FRAMERATE
    {	DVD_FPS_25	= 1,
	DVD_FPS_30NonDrop	= 3
    } 	DVD_FRAMERATE;

typedef struct tagDVD_TIMECODE
{
   ULONG Hours1    :4; // Hours
   ULONG Hours10  :4; // Tens of Hours 

   ULONG Minutes1  :4; // Minutes 
   ULONG Minutes10:4; // Tens of Minutes 

   ULONG Seconds1  :4; // Seconds 
   ULONG Seconds10:4; // Tens of Seconds 

   ULONG Frames1   :4; // Frames 
   ULONG Frames10 :2; // Tens of Frames 

   ULONG FrameRateCode: 2; // use DVD_FRAMERATE to indicate frames/sec and drop/non-drop
} DVD_TIMECODE;
typedef 
enum tagDVD_TIMECODE_FLAGS
    {	DVD_TC_FLAG_25fps	= 0x1,
	DVD_TC_FLAG_30fps	= 0x2,
	DVD_TC_FLAG_DropFrame	= 0x4,
	DVD_TC_FLAG_Interpolated	= 0x8
    } 	DVD_TIMECODE_FLAGS;

typedef struct tagDVD_HMSF_TIMECODE
    {
    BYTE bHours;
    BYTE bMinutes;
    BYTE bSeconds;
    BYTE bFrames;
    } 	DVD_HMSF_TIMECODE;

typedef struct tagDVD_PLAYBACK_LOCATION2
    {
    ULONG TitleNum;
    ULONG ChapterNum;
    DVD_HMSF_TIMECODE TimeCode;
    ULONG TimeCodeFlags;
    } 	DVD_PLAYBACK_LOCATION2;

typedef struct tagDVD_PLAYBACK_LOCATION
    {
    ULONG TitleNum;
    ULONG ChapterNum;
    ULONG TimeCode;
    } 	DVD_PLAYBACK_LOCATION;

typedef DWORD VALID_UOP_SOMTHING_OR_OTHER;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0366_0001
    {	UOP_FLAG_Play_Title_Or_AtTime	= 0x1,
	UOP_FLAG_Play_Chapter	= 0x2,
	UOP_FLAG_Play_Title	= 0x4,
	UOP_FLAG_Stop	= 0x8,
	UOP_FLAG_ReturnFromSubMenu	= 0x10,
	UOP_FLAG_Play_Chapter_Or_AtTime	= 0x20,
	UOP_FLAG_PlayPrev_Or_Replay_Chapter	= 0x40,
	UOP_FLAG_PlayNext_Chapter	= 0x80,
	UOP_FLAG_Play_Forwards	= 0x100,
	UOP_FLAG_Play_Backwards	= 0x200,
	UOP_FLAG_ShowMenu_Title	= 0x400,
	UOP_FLAG_ShowMenu_Root	= 0x800,
	UOP_FLAG_ShowMenu_SubPic	= 0x1000,
	UOP_FLAG_ShowMenu_Audio	= 0x2000,
	UOP_FLAG_ShowMenu_Angle	= 0x4000,
	UOP_FLAG_ShowMenu_Chapter	= 0x8000,
	UOP_FLAG_Resume	= 0x10000,
	UOP_FLAG_Select_Or_Activate_Button	= 0x20000,
	UOP_FLAG_Still_Off	= 0x40000,
	UOP_FLAG_Pause_On	= 0x80000,
	UOP_FLAG_Select_Audio_Stream	= 0x100000,
	UOP_FLAG_Select_SubPic_Stream	= 0x200000,
	UOP_FLAG_Select_Angle	= 0x400000,
	UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode	= 0x800000,
	UOP_FLAG_Select_Video_Mode_Preference	= 0x1000000
    } 	VALID_UOP_FLAG;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0366_0002
    {	DVD_CMD_FLAG_None	= 0,
	DVD_CMD_FLAG_Flush	= 0x1,
	DVD_CMD_FLAG_SendEvents	= 0x2,
	DVD_CMD_FLAG_Block	= 0x4,
	DVD_CMD_FLAG_StartWhenRendered	= 0x8,
	DVD_CMD_FLAG_EndAfterRendered	= 0x10
    } 	DVD_CMD_FLAGS;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_strmif_0366_0003
    {	DVD_ResetOnStop	= 1,
	DVD_NotifyParentalLevelChange	= 2,
	DVD_HMSF_TimeCodeEvents	= 3,
	DVD_AudioDuringFFwdRew	= 4
    } 	DVD_OPTION_FLAG;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_strmif_0366_0004
    {	DVD_Relative_Upper	= 1,
	DVD_Relative_Lower	= 2,
	DVD_Relative_Left	= 3,
	DVD_Relative_Right	= 4
    } 	DVD_RELATIVE_BUTTON;

typedef 
enum tagDVD_PARENTAL_LEVEL
    {	DVD_PARENTAL_LEVEL_8	= 0x8000,
	DVD_PARENTAL_LEVEL_7	= 0x4000,
	DVD_PARENTAL_LEVEL_6	= 0x2000,
	DVD_PARENTAL_LEVEL_5	= 0x1000,
	DVD_PARENTAL_LEVEL_4	= 0x800,
	DVD_PARENTAL_LEVEL_3	= 0x400,
	DVD_PARENTAL_LEVEL_2	= 0x200,
	DVD_PARENTAL_LEVEL_1	= 0x100
    } 	DVD_PARENTAL_LEVEL;

typedef 
enum tagDVD_AUDIO_LANG_EXT
    {	DVD_AUD_EXT_NotSpecified	= 0,
	DVD_AUD_EXT_Captions	= 1,
	DVD_AUD_EXT_VisuallyImpaired	= 2,
	DVD_AUD_EXT_DirectorComments1	= 3,
	DVD_AUD_EXT_DirectorComments2	= 4
    } 	DVD_AUDIO_LANG_EXT;

typedef 
enum tagDVD_SUBPICTURE_LANG_EXT
    {	DVD_SP_EXT_NotSpecified	= 0,
	DVD_SP_EXT_Caption_Normal	= 1,
	DVD_SP_EXT_Caption_Big	= 2,
	DVD_SP_EXT_Caption_Children	= 3,
	DVD_SP_EXT_CC_Normal	= 5,
	DVD_SP_EXT_CC_Big	= 6,
	DVD_SP_EXT_CC_Children	= 7,
	DVD_SP_EXT_Forced	= 9,
	DVD_SP_EXT_DirectorComments_Normal	= 13,
	DVD_SP_EXT_DirectorComments_Big	= 14,
	DVD_SP_EXT_DirectorComments_Children	= 15
    } 	DVD_SUBPICTURE_LANG_EXT;

typedef 
enum tagDVD_AUDIO_APPMODE
    {	DVD_AudioMode_None	= 0,
	DVD_AudioMode_Karaoke	= 1,
	DVD_AudioMode_Surround	= 2,
	DVD_AudioMode_Other	= 3
    } 	DVD_AUDIO_APPMODE;

typedef 
enum tagDVD_AUDIO_FORMAT
    {	DVD_AudioFormat_AC3	= 0,
	DVD_AudioFormat_MPEG1	= 1,
	DVD_AudioFormat_MPEG1_DRC	= 2,
	DVD_AudioFormat_MPEG2	= 3,
	DVD_AudioFormat_MPEG2_DRC	= 4,
	DVD_AudioFormat_LPCM	= 5,
	DVD_AudioFormat_DTS	= 6,
	DVD_AudioFormat_SDDS	= 7,
	DVD_AudioFormat_Other	= 8
    } 	DVD_AUDIO_FORMAT;

typedef 
enum tagDVD_KARAOKE_DOWNMIX
    {	DVD_Mix_0to0	= 0x1,
	DVD_Mix_1to0	= 0x2,
	DVD_Mix_2to0	= 0x4,
	DVD_Mix_3to0	= 0x8,
	DVD_Mix_4to0	= 0x10,
	DVD_Mix_Lto0	= 0x20,
	DVD_Mix_Rto0	= 0x40,
	DVD_Mix_0to1	= 0x100,
	DVD_Mix_1to1	= 0x200,
	DVD_Mix_2to1	= 0x400,
	DVD_Mix_3to1	= 0x800,
	DVD_Mix_4to1	= 0x1000,
	DVD_Mix_Lto1	= 0x2000,
	DVD_Mix_Rto1	= 0x4000
    } 	DVD_KARAOKE_DOWNMIX;

typedef struct tagDVD_AudioAttributes
    {
    DVD_AUDIO_APPMODE AppMode;
    BYTE AppModeData;
    DVD_AUDIO_FORMAT AudioFormat;
    LCID Language;
    DVD_AUDIO_LANG_EXT LanguageExtension;
    BOOL fHasMultichannelInfo;
    DWORD dwFrequency;
    BYTE bQuantization;
    BYTE bNumberOfChannels;
    DWORD dwReserved[ 2 ];
    } 	DVD_AudioAttributes;

typedef struct tagDVD_MUA_MixingInfo
    {
    BOOL fMixTo0;
    BOOL fMixTo1;
    BOOL fMix0InPhase;
    BOOL fMix1InPhase;
    DWORD dwSpeakerPosition;
    } 	DVD_MUA_MixingInfo;

typedef struct tagDVD_MUA_Coeff
    {
    double log2_alpha;
    double log2_beta;
    } 	DVD_MUA_Coeff;

typedef struct tagDVD_MultichannelAudioAttributes
    {
    DVD_MUA_MixingInfo Info[ 8 ];
    DVD_MUA_Coeff Coeff[ 8 ];
    } 	DVD_MultichannelAudioAttributes;

typedef 
enum tagDVD_KARAOKE_CONTENTS
    {	DVD_Karaoke_GuideVocal1	= 0x1,
	DVD_Karaoke_GuideVocal2	= 0x2,
	DVD_Karaoke_GuideMelody1	= 0x4,
	DVD_Karaoke_GuideMelody2	= 0x8,
	DVD_Karaoke_GuideMelodyA	= 0x10,
	DVD_Karaoke_GuideMelodyB	= 0x20,
	DVD_Karaoke_SoundEffectA	= 0x40,
	DVD_Karaoke_SoundEffectB	= 0x80
    } 	DVD_KARAOKE_CONTENTS;

typedef 
enum tagDVD_KARAOKE_ASSIGNMENT
    {	DVD_Assignment_reserved0	= 0,
	DVD_Assignment_reserved1	= 1,
	DVD_Assignment_LR	= 2,
	DVD_Assignment_LRM	= 3,
	DVD_Assignment_LR1	= 4,
	DVD_Assignment_LRM1	= 5,
	DVD_Assignment_LR12	= 6,
	DVD_Assignment_LRM12	= 7
    } 	DVD_KARAOKE_ASSIGNMENT;

typedef struct tagDVD_KaraokeAttributes
    {
    BYTE bVersion;
    BOOL fMasterOfCeremoniesInGuideVocal1;
    BOOL fDuet;
    DVD_KARAOKE_ASSIGNMENT ChannelAssignment;
    WORD wChannelContents[ 8 ];
    } 	DVD_KaraokeAttributes;

typedef 
enum tagDVD_VIDEO_COMPRESSION
    {	DVD_VideoCompression_Other	= 0,
	DVD_VideoCompression_MPEG1	= 1,
	DVD_VideoCompression_MPEG2	= 2
    } 	DVD_VIDEO_COMPRESSION;

typedef struct tagDVD_VideoAttributes
    {
    BOOL fPanscanPermitted;
    BOOL fLetterboxPermitted;
    ULONG ulAspectX;
    ULONG ulAspectY;
    ULONG ulFrameRate;
    ULONG ulFrameHeight;
    DVD_VIDEO_COMPRESSION Compression;
    BOOL fLine21Field1InGOP;
    BOOL fLine21Field2InGOP;
    ULONG ulSourceResolutionX;
    ULONG ulSourceResolutionY;
    BOOL fIsSourceLetterboxed;
    BOOL fIsFilmMode;
    } 	DVD_VideoAttributes;

typedef 
enum tagDVD_SUBPICTURE_TYPE
    {	DVD_SPType_NotSpecified	= 0,
	DVD_SPType_Language	= 1,
	DVD_SPType_Other	= 2
    } 	DVD_SUBPICTURE_TYPE;

typedef 
enum tagDVD_SUBPICTURE_CODING
    {	DVD_SPCoding_RunLength	= 0,
	DVD_SPCoding_Extended	= 1,
	DVD_SPCoding_Other	= 2
    } 	DVD_SUBPICTURE_CODING;

typedef struct tagDVD_SubpictureAttributes
    {
    DVD_SUBPICTURE_TYPE Type;
    DVD_SUBPICTURE_CODING CodingMode;
    LCID Language;
    DVD_SUBPICTURE_LANG_EXT LanguageExtension;
    } 	DVD_SubpictureAttributes;

typedef 
enum tagDVD_TITLE_APPMODE
    {	DVD_AppMode_Not_Specified	= 0,
	DVD_AppMode_Karaoke	= 1,
	DVD_AppMode_Other	= 3
    } 	DVD_TITLE_APPMODE;

typedef struct tagDVD_TitleMainAttributes
    {
    DVD_TITLE_APPMODE AppMode;
    DVD_VideoAttributes VideoAttributes;
    ULONG ulNumberOfAudioStreams;
    DVD_AudioAttributes AudioAttributes[ 8 ];
    DVD_MultichannelAudioAttributes MultichannelAudioAttributes[ 8 ];
    ULONG ulNumberOfSubpictureStreams;
    DVD_SubpictureAttributes SubpictureAttributes[ 32 ];
    } 	DVD_TitleAttributes;

typedef struct tagDVD_MenuAttributes
    {
    BOOL fCompatibleRegion[ 8 ];
    DVD_VideoAttributes VideoAttributes;
    BOOL fAudioPresent;
    DVD_AudioAttributes AudioAttributes;
    BOOL fSubpicturePresent;
    DVD_SubpictureAttributes SubpictureAttributes;
    } 	DVD_MenuAttributes;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0366_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0366_v0_0_s_ifspec;

#ifndef __IDvdControl_INTERFACE_DEFINED__
#define __IDvdControl_INTERFACE_DEFINED__

/* interface IDvdControl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A70EFE61-E2A3-11d0-A9BE-00AA0061BE93")
    IDvdControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TitlePlay( 
            /* [in] */ ULONG ulTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChapterPlay( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TimePlay( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG bcdTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopForResume( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GoUp( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TimeSearch( 
            /* [in] */ ULONG bcdTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChapterSearch( 
            /* [in] */ ULONG ulChapter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrevPGSearch( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TopPGSearch( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NextPGSearch( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ForwardScan( 
            /* [in] */ double dwSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackwardScan( 
            /* [in] */ double dwSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MenuCall( 
            /* [in] */ DVD_MENU_ID MenuID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpperButtonSelect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LowerButtonSelect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LeftButtonSelect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RightButtonSelect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ButtonActivate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ButtonSelectAndActivate( 
            /* [in] */ ULONG ulButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StillOff( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseOn( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseOff( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MenuLanguageSelect( 
            /* [in] */ LCID Language) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioStreamChange( 
            /* [in] */ ULONG ulAudio) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubpictureStreamChange( 
            /* [in] */ ULONG ulSubPicture,
            /* [in] */ BOOL bDisplay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AngleChange( 
            /* [in] */ ULONG ulAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParentalLevelSelect( 
            /* [in] */ ULONG ulParentalLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParentalCountrySelect( 
            /* [in] */ WORD wCountry) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE KaraokeAudioPresentationModeChange( 
            /* [in] */ ULONG ulMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VideoModePreferrence( 
            /* [in] */ ULONG ulPreferredDisplayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRoot( 
            /* [in] */ LPCWSTR pszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MouseActivate( 
            /* [in] */ POINT point) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MouseSelect( 
            /* [in] */ POINT point) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChapterPlayAutoStop( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ ULONG ulChaptersToPlay) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *TitlePlay )( 
            IDvdControl * This,
            /* [in] */ ULONG ulTitle);
        
        HRESULT ( STDMETHODCALLTYPE *ChapterPlay )( 
            IDvdControl * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter);
        
        HRESULT ( STDMETHODCALLTYPE *TimePlay )( 
            IDvdControl * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG bcdTime);
        
        HRESULT ( STDMETHODCALLTYPE *StopForResume )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GoUp )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *TimeSearch )( 
            IDvdControl * This,
            /* [in] */ ULONG bcdTime);
        
        HRESULT ( STDMETHODCALLTYPE *ChapterSearch )( 
            IDvdControl * This,
            /* [in] */ ULONG ulChapter);
        
        HRESULT ( STDMETHODCALLTYPE *PrevPGSearch )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *TopPGSearch )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *NextPGSearch )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *ForwardScan )( 
            IDvdControl * This,
            /* [in] */ double dwSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *BackwardScan )( 
            IDvdControl * This,
            /* [in] */ double dwSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *MenuCall )( 
            IDvdControl * This,
            /* [in] */ DVD_MENU_ID MenuID);
        
        HRESULT ( STDMETHODCALLTYPE *Resume )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *UpperButtonSelect )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *LowerButtonSelect )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *LeftButtonSelect )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *RightButtonSelect )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *ButtonActivate )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *ButtonSelectAndActivate )( 
            IDvdControl * This,
            /* [in] */ ULONG ulButton);
        
        HRESULT ( STDMETHODCALLTYPE *StillOff )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseOn )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseOff )( 
            IDvdControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *MenuLanguageSelect )( 
            IDvdControl * This,
            /* [in] */ LCID Language);
        
        HRESULT ( STDMETHODCALLTYPE *AudioStreamChange )( 
            IDvdControl * This,
            /* [in] */ ULONG ulAudio);
        
        HRESULT ( STDMETHODCALLTYPE *SubpictureStreamChange )( 
            IDvdControl * This,
            /* [in] */ ULONG ulSubPicture,
            /* [in] */ BOOL bDisplay);
        
        HRESULT ( STDMETHODCALLTYPE *AngleChange )( 
            IDvdControl * This,
            /* [in] */ ULONG ulAngle);
        
        HRESULT ( STDMETHODCALLTYPE *ParentalLevelSelect )( 
            IDvdControl * This,
            /* [in] */ ULONG ulParentalLevel);
        
        HRESULT ( STDMETHODCALLTYPE *ParentalCountrySelect )( 
            IDvdControl * This,
            /* [in] */ WORD wCountry);
        
        HRESULT ( STDMETHODCALLTYPE *KaraokeAudioPresentationModeChange )( 
            IDvdControl * This,
            /* [in] */ ULONG ulMode);
        
        HRESULT ( STDMETHODCALLTYPE *VideoModePreferrence )( 
            IDvdControl * This,
            /* [in] */ ULONG ulPreferredDisplayMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetRoot )( 
            IDvdControl * This,
            /* [in] */ LPCWSTR pszPath);
        
        HRESULT ( STDMETHODCALLTYPE *MouseActivate )( 
            IDvdControl * This,
            /* [in] */ POINT point);
        
        HRESULT ( STDMETHODCALLTYPE *MouseSelect )( 
            IDvdControl * This,
            /* [in] */ POINT point);
        
        HRESULT ( STDMETHODCALLTYPE *ChapterPlayAutoStop )( 
            IDvdControl * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ ULONG ulChaptersToPlay);
        
        END_INTERFACE
    } IDvdControlVtbl;

    interface IDvdControl
    {
        CONST_VTBL struct IDvdControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdControl_TitlePlay(This,ulTitle)	\
    (This)->lpVtbl -> TitlePlay(This,ulTitle)

#define IDvdControl_ChapterPlay(This,ulTitle,ulChapter)	\
    (This)->lpVtbl -> ChapterPlay(This,ulTitle,ulChapter)

#define IDvdControl_TimePlay(This,ulTitle,bcdTime)	\
    (This)->lpVtbl -> TimePlay(This,ulTitle,bcdTime)

#define IDvdControl_StopForResume(This)	\
    (This)->lpVtbl -> StopForResume(This)

#define IDvdControl_GoUp(This)	\
    (This)->lpVtbl -> GoUp(This)

#define IDvdControl_TimeSearch(This,bcdTime)	\
    (This)->lpVtbl -> TimeSearch(This,bcdTime)

#define IDvdControl_ChapterSearch(This,ulChapter)	\
    (This)->lpVtbl -> ChapterSearch(This,ulChapter)

#define IDvdControl_PrevPGSearch(This)	\
    (This)->lpVtbl -> PrevPGSearch(This)

#define IDvdControl_TopPGSearch(This)	\
    (This)->lpVtbl -> TopPGSearch(This)

#define IDvdControl_NextPGSearch(This)	\
    (This)->lpVtbl -> NextPGSearch(This)

#define IDvdControl_ForwardScan(This,dwSpeed)	\
    (This)->lpVtbl -> ForwardScan(This,dwSpeed)

#define IDvdControl_BackwardScan(This,dwSpeed)	\
    (This)->lpVtbl -> BackwardScan(This,dwSpeed)

#define IDvdControl_MenuCall(This,MenuID)	\
    (This)->lpVtbl -> MenuCall(This,MenuID)

#define IDvdControl_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define IDvdControl_UpperButtonSelect(This)	\
    (This)->lpVtbl -> UpperButtonSelect(This)

#define IDvdControl_LowerButtonSelect(This)	\
    (This)->lpVtbl -> LowerButtonSelect(This)

#define IDvdControl_LeftButtonSelect(This)	\
    (This)->lpVtbl -> LeftButtonSelect(This)

#define IDvdControl_RightButtonSelect(This)	\
    (This)->lpVtbl -> RightButtonSelect(This)

#define IDvdControl_ButtonActivate(This)	\
    (This)->lpVtbl -> ButtonActivate(This)

#define IDvdControl_ButtonSelectAndActivate(This,ulButton)	\
    (This)->lpVtbl -> ButtonSelectAndActivate(This,ulButton)

#define IDvdControl_StillOff(This)	\
    (This)->lpVtbl -> StillOff(This)

#define IDvdControl_PauseOn(This)	\
    (This)->lpVtbl -> PauseOn(This)

#define IDvdControl_PauseOff(This)	\
    (This)->lpVtbl -> PauseOff(This)

#define IDvdControl_MenuLanguageSelect(This,Language)	\
    (This)->lpVtbl -> MenuLanguageSelect(This,Language)

#define IDvdControl_AudioStreamChange(This,ulAudio)	\
    (This)->lpVtbl -> AudioStreamChange(This,ulAudio)

#define IDvdControl_SubpictureStreamChange(This,ulSubPicture,bDisplay)	\
    (This)->lpVtbl -> SubpictureStreamChange(This,ulSubPicture,bDisplay)

#define IDvdControl_AngleChange(This,ulAngle)	\
    (This)->lpVtbl -> AngleChange(This,ulAngle)

#define IDvdControl_ParentalLevelSelect(This,ulParentalLevel)	\
    (This)->lpVtbl -> ParentalLevelSelect(This,ulParentalLevel)

#define IDvdControl_ParentalCountrySelect(This,wCountry)	\
    (This)->lpVtbl -> ParentalCountrySelect(This,wCountry)

#define IDvdControl_KaraokeAudioPresentationModeChange(This,ulMode)	\
    (This)->lpVtbl -> KaraokeAudioPresentationModeChange(This,ulMode)

#define IDvdControl_VideoModePreferrence(This,ulPreferredDisplayMode)	\
    (This)->lpVtbl -> VideoModePreferrence(This,ulPreferredDisplayMode)

#define IDvdControl_SetRoot(This,pszPath)	\
    (This)->lpVtbl -> SetRoot(This,pszPath)

#define IDvdControl_MouseActivate(This,point)	\
    (This)->lpVtbl -> MouseActivate(This,point)

#define IDvdControl_MouseSelect(This,point)	\
    (This)->lpVtbl -> MouseSelect(This,point)

#define IDvdControl_ChapterPlayAutoStop(This,ulTitle,ulChapter,ulChaptersToPlay)	\
    (This)->lpVtbl -> ChapterPlayAutoStop(This,ulTitle,ulChapter,ulChaptersToPlay)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdControl_TitlePlay_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulTitle);


void __RPC_STUB IDvdControl_TitlePlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ChapterPlay_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ ULONG ulChapter);


void __RPC_STUB IDvdControl_ChapterPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_TimePlay_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ ULONG bcdTime);


void __RPC_STUB IDvdControl_TimePlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_StopForResume_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_StopForResume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_GoUp_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_GoUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_TimeSearch_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG bcdTime);


void __RPC_STUB IDvdControl_TimeSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ChapterSearch_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulChapter);


void __RPC_STUB IDvdControl_ChapterSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_PrevPGSearch_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_PrevPGSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_TopPGSearch_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_TopPGSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_NextPGSearch_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_NextPGSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ForwardScan_Proxy( 
    IDvdControl * This,
    /* [in] */ double dwSpeed);


void __RPC_STUB IDvdControl_ForwardScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_BackwardScan_Proxy( 
    IDvdControl * This,
    /* [in] */ double dwSpeed);


void __RPC_STUB IDvdControl_BackwardScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_MenuCall_Proxy( 
    IDvdControl * This,
    /* [in] */ DVD_MENU_ID MenuID);


void __RPC_STUB IDvdControl_MenuCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_Resume_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_UpperButtonSelect_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_UpperButtonSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_LowerButtonSelect_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_LowerButtonSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_LeftButtonSelect_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_LeftButtonSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_RightButtonSelect_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_RightButtonSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ButtonActivate_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_ButtonActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ButtonSelectAndActivate_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulButton);


void __RPC_STUB IDvdControl_ButtonSelectAndActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_StillOff_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_StillOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_PauseOn_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_PauseOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_PauseOff_Proxy( 
    IDvdControl * This);


void __RPC_STUB IDvdControl_PauseOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_MenuLanguageSelect_Proxy( 
    IDvdControl * This,
    /* [in] */ LCID Language);


void __RPC_STUB IDvdControl_MenuLanguageSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_AudioStreamChange_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulAudio);


void __RPC_STUB IDvdControl_AudioStreamChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_SubpictureStreamChange_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulSubPicture,
    /* [in] */ BOOL bDisplay);


void __RPC_STUB IDvdControl_SubpictureStreamChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_AngleChange_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulAngle);


void __RPC_STUB IDvdControl_AngleChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ParentalLevelSelect_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulParentalLevel);


void __RPC_STUB IDvdControl_ParentalLevelSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ParentalCountrySelect_Proxy( 
    IDvdControl * This,
    /* [in] */ WORD wCountry);


void __RPC_STUB IDvdControl_ParentalCountrySelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_KaraokeAudioPresentationModeChange_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulMode);


void __RPC_STUB IDvdControl_KaraokeAudioPresentationModeChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_VideoModePreferrence_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulPreferredDisplayMode);


void __RPC_STUB IDvdControl_VideoModePreferrence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_SetRoot_Proxy( 
    IDvdControl * This,
    /* [in] */ LPCWSTR pszPath);


void __RPC_STUB IDvdControl_SetRoot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_MouseActivate_Proxy( 
    IDvdControl * This,
    /* [in] */ POINT point);


void __RPC_STUB IDvdControl_MouseActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_MouseSelect_Proxy( 
    IDvdControl * This,
    /* [in] */ POINT point);


void __RPC_STUB IDvdControl_MouseSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl_ChapterPlayAutoStop_Proxy( 
    IDvdControl * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ ULONG ulChapter,
    /* [in] */ ULONG ulChaptersToPlay);


void __RPC_STUB IDvdControl_ChapterPlayAutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdControl_INTERFACE_DEFINED__ */


#ifndef __IDvdInfo_INTERFACE_DEFINED__
#define __IDvdInfo_INTERFACE_DEFINED__

/* interface IDvdInfo */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A70EFE60-E2A3-11d0-A9BE-00AA0061BE93")
    IDvdInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCurrentDomain( 
            /* [out] */ DVD_DOMAIN *pDomain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentLocation( 
            /* [out] */ DVD_PLAYBACK_LOCATION *pLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTotalTitleTime( 
            /* [out] */ ULONG *pulTotalTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentButton( 
            /* [out] */ ULONG *pulButtonsAvailable,
            /* [out] */ ULONG *pulCurrentButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentAngle( 
            /* [out] */ ULONG *pulAnglesAvailable,
            /* [out] */ ULONG *pulCurrentAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentAudio( 
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentSubpicture( 
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream,
            /* [out] */ BOOL *pIsDisabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentUOPS( 
            /* [out] */ VALID_UOP_SOMTHING_OR_OTHER *pUOP) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllSPRMs( 
            /* [out] */ SPRMARRAY *pRegisterArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllGPRMs( 
            /* [out] */ GPRMARRAY *pRegisterArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioLanguage( 
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubpictureLanguage( 
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTitleAttributes( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ DVD_ATR *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVMGAttributes( 
            /* [out] */ DVD_ATR *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentVideoAttributes( 
            /* [out] */ DVD_VideoATR *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentAudioAttributes( 
            /* [out] */ DVD_AudioATR *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentSubpictureAttributes( 
            /* [out] */ DVD_SubpictureATR *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentVolumeInfo( 
            /* [out] */ ULONG *pulNumOfVol,
            /* [out] */ ULONG *pulThisVolNum,
            /* [out] */ DVD_DISC_SIDE *pSide,
            /* [out] */ ULONG *pulNumOfTitles) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDTextInfo( 
            /* [size_is][out] */ BYTE *pTextManager,
            /* [in] */ ULONG ulBufSize,
            /* [out] */ ULONG *pulActualSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPlayerParentalLevel( 
            /* [out] */ ULONG *pulParentalLevel,
            /* [out] */ ULONG *pulCountryCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfChapters( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulNumberOfChapters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTitleParentalLevels( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulParentalLevels) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRoot( 
            /* [size_is][out] */ LPSTR pRoot,
            /* [in] */ ULONG ulBufSize,
            /* [out] */ ULONG *pulActualSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentDomain )( 
            IDvdInfo * This,
            /* [out] */ DVD_DOMAIN *pDomain);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentLocation )( 
            IDvdInfo * This,
            /* [out] */ DVD_PLAYBACK_LOCATION *pLocation);
        
        HRESULT ( STDMETHODCALLTYPE *GetTotalTitleTime )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulTotalTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentButton )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulButtonsAvailable,
            /* [out] */ ULONG *pulCurrentButton);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentAngle )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulAnglesAvailable,
            /* [out] */ ULONG *pulCurrentAngle);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentAudio )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSubpicture )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream,
            /* [out] */ BOOL *pIsDisabled);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentUOPS )( 
            IDvdInfo * This,
            /* [out] */ VALID_UOP_SOMTHING_OR_OTHER *pUOP);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllSPRMs )( 
            IDvdInfo * This,
            /* [out] */ SPRMARRAY *pRegisterArray);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllGPRMs )( 
            IDvdInfo * This,
            /* [out] */ GPRMARRAY *pRegisterArray);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioLanguage )( 
            IDvdInfo * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage);
        
        HRESULT ( STDMETHODCALLTYPE *GetSubpictureLanguage )( 
            IDvdInfo * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage);
        
        HRESULT ( STDMETHODCALLTYPE *GetTitleAttributes )( 
            IDvdInfo * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ DVD_ATR *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetVMGAttributes )( 
            IDvdInfo * This,
            /* [out] */ DVD_ATR *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentVideoAttributes )( 
            IDvdInfo * This,
            /* [out] */ DVD_VideoATR *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentAudioAttributes )( 
            IDvdInfo * This,
            /* [out] */ DVD_AudioATR *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSubpictureAttributes )( 
            IDvdInfo * This,
            /* [out] */ DVD_SubpictureATR *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentVolumeInfo )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulNumOfVol,
            /* [out] */ ULONG *pulThisVolNum,
            /* [out] */ DVD_DISC_SIDE *pSide,
            /* [out] */ ULONG *pulNumOfTitles);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDTextInfo )( 
            IDvdInfo * This,
            /* [size_is][out] */ BYTE *pTextManager,
            /* [in] */ ULONG ulBufSize,
            /* [out] */ ULONG *pulActualSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetPlayerParentalLevel )( 
            IDvdInfo * This,
            /* [out] */ ULONG *pulParentalLevel,
            /* [out] */ ULONG *pulCountryCode);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfChapters )( 
            IDvdInfo * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulNumberOfChapters);
        
        HRESULT ( STDMETHODCALLTYPE *GetTitleParentalLevels )( 
            IDvdInfo * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulParentalLevels);
        
        HRESULT ( STDMETHODCALLTYPE *GetRoot )( 
            IDvdInfo * This,
            /* [size_is][out] */ LPSTR pRoot,
            /* [in] */ ULONG ulBufSize,
            /* [out] */ ULONG *pulActualSize);
        
        END_INTERFACE
    } IDvdInfoVtbl;

    interface IDvdInfo
    {
        CONST_VTBL struct IDvdInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdInfo_GetCurrentDomain(This,pDomain)	\
    (This)->lpVtbl -> GetCurrentDomain(This,pDomain)

#define IDvdInfo_GetCurrentLocation(This,pLocation)	\
    (This)->lpVtbl -> GetCurrentLocation(This,pLocation)

#define IDvdInfo_GetTotalTitleTime(This,pulTotalTime)	\
    (This)->lpVtbl -> GetTotalTitleTime(This,pulTotalTime)

#define IDvdInfo_GetCurrentButton(This,pulButtonsAvailable,pulCurrentButton)	\
    (This)->lpVtbl -> GetCurrentButton(This,pulButtonsAvailable,pulCurrentButton)

#define IDvdInfo_GetCurrentAngle(This,pulAnglesAvailable,pulCurrentAngle)	\
    (This)->lpVtbl -> GetCurrentAngle(This,pulAnglesAvailable,pulCurrentAngle)

#define IDvdInfo_GetCurrentAudio(This,pulStreamsAvailable,pulCurrentStream)	\
    (This)->lpVtbl -> GetCurrentAudio(This,pulStreamsAvailable,pulCurrentStream)

#define IDvdInfo_GetCurrentSubpicture(This,pulStreamsAvailable,pulCurrentStream,pIsDisabled)	\
    (This)->lpVtbl -> GetCurrentSubpicture(This,pulStreamsAvailable,pulCurrentStream,pIsDisabled)

#define IDvdInfo_GetCurrentUOPS(This,pUOP)	\
    (This)->lpVtbl -> GetCurrentUOPS(This,pUOP)

#define IDvdInfo_GetAllSPRMs(This,pRegisterArray)	\
    (This)->lpVtbl -> GetAllSPRMs(This,pRegisterArray)

#define IDvdInfo_GetAllGPRMs(This,pRegisterArray)	\
    (This)->lpVtbl -> GetAllGPRMs(This,pRegisterArray)

#define IDvdInfo_GetAudioLanguage(This,ulStream,pLanguage)	\
    (This)->lpVtbl -> GetAudioLanguage(This,ulStream,pLanguage)

#define IDvdInfo_GetSubpictureLanguage(This,ulStream,pLanguage)	\
    (This)->lpVtbl -> GetSubpictureLanguage(This,ulStream,pLanguage)

#define IDvdInfo_GetTitleAttributes(This,ulTitle,pATR)	\
    (This)->lpVtbl -> GetTitleAttributes(This,ulTitle,pATR)

#define IDvdInfo_GetVMGAttributes(This,pATR)	\
    (This)->lpVtbl -> GetVMGAttributes(This,pATR)

#define IDvdInfo_GetCurrentVideoAttributes(This,pATR)	\
    (This)->lpVtbl -> GetCurrentVideoAttributes(This,pATR)

#define IDvdInfo_GetCurrentAudioAttributes(This,pATR)	\
    (This)->lpVtbl -> GetCurrentAudioAttributes(This,pATR)

#define IDvdInfo_GetCurrentSubpictureAttributes(This,pATR)	\
    (This)->lpVtbl -> GetCurrentSubpictureAttributes(This,pATR)

#define IDvdInfo_GetCurrentVolumeInfo(This,pulNumOfVol,pulThisVolNum,pSide,pulNumOfTitles)	\
    (This)->lpVtbl -> GetCurrentVolumeInfo(This,pulNumOfVol,pulThisVolNum,pSide,pulNumOfTitles)

#define IDvdInfo_GetDVDTextInfo(This,pTextManager,ulBufSize,pulActualSize)	\
    (This)->lpVtbl -> GetDVDTextInfo(This,pTextManager,ulBufSize,pulActualSize)

#define IDvdInfo_GetPlayerParentalLevel(This,pulParentalLevel,pulCountryCode)	\
    (This)->lpVtbl -> GetPlayerParentalLevel(This,pulParentalLevel,pulCountryCode)

#define IDvdInfo_GetNumberOfChapters(This,ulTitle,pulNumberOfChapters)	\
    (This)->lpVtbl -> GetNumberOfChapters(This,ulTitle,pulNumberOfChapters)

#define IDvdInfo_GetTitleParentalLevels(This,ulTitle,pulParentalLevels)	\
    (This)->lpVtbl -> GetTitleParentalLevels(This,ulTitle,pulParentalLevels)

#define IDvdInfo_GetRoot(This,pRoot,ulBufSize,pulActualSize)	\
    (This)->lpVtbl -> GetRoot(This,pRoot,ulBufSize,pulActualSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentDomain_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_DOMAIN *pDomain);


void __RPC_STUB IDvdInfo_GetCurrentDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentLocation_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_PLAYBACK_LOCATION *pLocation);


void __RPC_STUB IDvdInfo_GetCurrentLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetTotalTitleTime_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulTotalTime);


void __RPC_STUB IDvdInfo_GetTotalTitleTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentButton_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulButtonsAvailable,
    /* [out] */ ULONG *pulCurrentButton);


void __RPC_STUB IDvdInfo_GetCurrentButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentAngle_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulAnglesAvailable,
    /* [out] */ ULONG *pulCurrentAngle);


void __RPC_STUB IDvdInfo_GetCurrentAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentAudio_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulStreamsAvailable,
    /* [out] */ ULONG *pulCurrentStream);


void __RPC_STUB IDvdInfo_GetCurrentAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentSubpicture_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulStreamsAvailable,
    /* [out] */ ULONG *pulCurrentStream,
    /* [out] */ BOOL *pIsDisabled);


void __RPC_STUB IDvdInfo_GetCurrentSubpicture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentUOPS_Proxy( 
    IDvdInfo * This,
    /* [out] */ VALID_UOP_SOMTHING_OR_OTHER *pUOP);


void __RPC_STUB IDvdInfo_GetCurrentUOPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetAllSPRMs_Proxy( 
    IDvdInfo * This,
    /* [out] */ SPRMARRAY *pRegisterArray);


void __RPC_STUB IDvdInfo_GetAllSPRMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetAllGPRMs_Proxy( 
    IDvdInfo * This,
    /* [out] */ GPRMARRAY *pRegisterArray);


void __RPC_STUB IDvdInfo_GetAllGPRMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetAudioLanguage_Proxy( 
    IDvdInfo * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ LCID *pLanguage);


void __RPC_STUB IDvdInfo_GetAudioLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetSubpictureLanguage_Proxy( 
    IDvdInfo * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ LCID *pLanguage);


void __RPC_STUB IDvdInfo_GetSubpictureLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetTitleAttributes_Proxy( 
    IDvdInfo * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ DVD_ATR *pATR);


void __RPC_STUB IDvdInfo_GetTitleAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetVMGAttributes_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_ATR *pATR);


void __RPC_STUB IDvdInfo_GetVMGAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentVideoAttributes_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_VideoATR *pATR);


void __RPC_STUB IDvdInfo_GetCurrentVideoAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentAudioAttributes_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_AudioATR *pATR);


void __RPC_STUB IDvdInfo_GetCurrentAudioAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentSubpictureAttributes_Proxy( 
    IDvdInfo * This,
    /* [out] */ DVD_SubpictureATR *pATR);


void __RPC_STUB IDvdInfo_GetCurrentSubpictureAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetCurrentVolumeInfo_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulNumOfVol,
    /* [out] */ ULONG *pulThisVolNum,
    /* [out] */ DVD_DISC_SIDE *pSide,
    /* [out] */ ULONG *pulNumOfTitles);


void __RPC_STUB IDvdInfo_GetCurrentVolumeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetDVDTextInfo_Proxy( 
    IDvdInfo * This,
    /* [size_is][out] */ BYTE *pTextManager,
    /* [in] */ ULONG ulBufSize,
    /* [out] */ ULONG *pulActualSize);


void __RPC_STUB IDvdInfo_GetDVDTextInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetPlayerParentalLevel_Proxy( 
    IDvdInfo * This,
    /* [out] */ ULONG *pulParentalLevel,
    /* [out] */ ULONG *pulCountryCode);


void __RPC_STUB IDvdInfo_GetPlayerParentalLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetNumberOfChapters_Proxy( 
    IDvdInfo * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ ULONG *pulNumberOfChapters);


void __RPC_STUB IDvdInfo_GetNumberOfChapters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetTitleParentalLevels_Proxy( 
    IDvdInfo * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ ULONG *pulParentalLevels);


void __RPC_STUB IDvdInfo_GetTitleParentalLevels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo_GetRoot_Proxy( 
    IDvdInfo * This,
    /* [size_is][out] */ LPSTR pRoot,
    /* [in] */ ULONG ulBufSize,
    /* [out] */ ULONG *pulActualSize);


void __RPC_STUB IDvdInfo_GetRoot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdInfo_INTERFACE_DEFINED__ */


#ifndef __IDvdCmd_INTERFACE_DEFINED__
#define __IDvdCmd_INTERFACE_DEFINED__

/* interface IDvdCmd */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdCmd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5a4a97e4-94ee-4a55-9751-74b5643aa27d")
    IDvdCmd : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE WaitForStart( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForEnd( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdCmdVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdCmd * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdCmd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdCmd * This);
        
        HRESULT ( STDMETHODCALLTYPE *WaitForStart )( 
            IDvdCmd * This);
        
        HRESULT ( STDMETHODCALLTYPE *WaitForEnd )( 
            IDvdCmd * This);
        
        END_INTERFACE
    } IDvdCmdVtbl;

    interface IDvdCmd
    {
        CONST_VTBL struct IDvdCmdVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdCmd_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdCmd_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdCmd_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdCmd_WaitForStart(This)	\
    (This)->lpVtbl -> WaitForStart(This)

#define IDvdCmd_WaitForEnd(This)	\
    (This)->lpVtbl -> WaitForEnd(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdCmd_WaitForStart_Proxy( 
    IDvdCmd * This);


void __RPC_STUB IDvdCmd_WaitForStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdCmd_WaitForEnd_Proxy( 
    IDvdCmd * This);


void __RPC_STUB IDvdCmd_WaitForEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdCmd_INTERFACE_DEFINED__ */


#ifndef __IDvdState_INTERFACE_DEFINED__
#define __IDvdState_INTERFACE_DEFINED__

/* interface IDvdState */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdState;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86303d6d-1c4a-4087-ab42-f711167048ef")
    IDvdState : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDiscID( 
            /* [out] */ ULONGLONG *pullUniqueID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParentalLevel( 
            /* [out] */ ULONG *pulParentalLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdStateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdState * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdState * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdState * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDiscID )( 
            IDvdState * This,
            /* [out] */ ULONGLONG *pullUniqueID);
        
        HRESULT ( STDMETHODCALLTYPE *GetParentalLevel )( 
            IDvdState * This,
            /* [out] */ ULONG *pulParentalLevel);
        
        END_INTERFACE
    } IDvdStateVtbl;

    interface IDvdState
    {
        CONST_VTBL struct IDvdStateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdState_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdState_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdState_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdState_GetDiscID(This,pullUniqueID)	\
    (This)->lpVtbl -> GetDiscID(This,pullUniqueID)

#define IDvdState_GetParentalLevel(This,pulParentalLevel)	\
    (This)->lpVtbl -> GetParentalLevel(This,pulParentalLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdState_GetDiscID_Proxy( 
    IDvdState * This,
    /* [out] */ ULONGLONG *pullUniqueID);


void __RPC_STUB IDvdState_GetDiscID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdState_GetParentalLevel_Proxy( 
    IDvdState * This,
    /* [out] */ ULONG *pulParentalLevel);


void __RPC_STUB IDvdState_GetParentalLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdState_INTERFACE_DEFINED__ */


#ifndef __IDvdControl2_INTERFACE_DEFINED__
#define __IDvdControl2_INTERFACE_DEFINED__

/* interface IDvdControl2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdControl2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33BC7430-EEC0-11D2-8201-00A0C9D74842")
    IDvdControl2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PlayTitle( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayChapterInTitle( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayAtTimeInTitle( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReturnFromSubmenu( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayAtTime( 
            /* [in] */ DVD_HMSF_TIMECODE *pTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayChapter( 
            /* [in] */ ULONG ulChapter,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayPrevChapter( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplayChapter( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayNextChapter( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayForwards( 
            /* [in] */ double dSpeed,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayBackwards( 
            /* [in] */ double dSpeed,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowMenu( 
            /* [in] */ DVD_MENU_ID MenuID,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resume( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectRelativeButton( 
            DVD_RELATIVE_BUTTON buttonDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateButton( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectButton( 
            /* [in] */ ULONG ulButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAndActivateButton( 
            /* [in] */ ULONG ulButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StillOff( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( 
            /* [in] */ BOOL bState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAudioStream( 
            /* [in] */ ULONG ulAudio,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectSubpictureStream( 
            /* [in] */ ULONG ulSubPicture,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSubpictureState( 
            /* [in] */ BOOL bState,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAngle( 
            /* [in] */ ULONG ulAngle,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectParentalLevel( 
            /* [in] */ ULONG ulParentalLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectParentalCountry( 
            /* [in] */ BYTE bCountry[ 2 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectKaraokeAudioPresentationMode( 
            /* [in] */ ULONG ulMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectVideoModePreference( 
            /* [in] */ ULONG ulPreferredDisplayMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDVDDirectory( 
            /* [in] */ LPCWSTR pszwPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateAtPosition( 
            /* [in] */ POINT point) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAtPosition( 
            /* [in] */ POINT point) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayChaptersAutoStop( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ ULONG ulChaptersToPlay,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AcceptParentalLevelChange( 
            /* [in] */ BOOL bAccept) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOption( 
            /* [in] */ DVD_OPTION_FLAG flag,
            /* [in] */ BOOL fState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetState( 
            /* [in] */ IDvdState *pState,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayPeriodInTitleAutoStop( 
            /* [in] */ ULONG ulTitle,
            /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
            /* [in] */ DVD_HMSF_TIMECODE *pEndTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGPRM( 
            /* [in] */ ULONG ulIndex,
            /* [in] */ WORD wValue,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectDefaultMenuLanguage( 
            /* [in] */ LCID Language) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectDefaultAudioLanguage( 
            /* [in] */ LCID Language,
            /* [in] */ DVD_AUDIO_LANG_EXT audioExtension) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectDefaultSubpictureLanguage( 
            /* [in] */ LCID Language,
            /* [in] */ DVD_SUBPICTURE_LANG_EXT subpictureExtension) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdControl2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdControl2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdControl2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdControl2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *PlayTitle )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayChapterInTitle )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayAtTimeInTitle )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IDvdControl2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReturnFromSubmenu )( 
            IDvdControl2 * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayAtTime )( 
            IDvdControl2 * This,
            /* [in] */ DVD_HMSF_TIMECODE *pTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayChapter )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulChapter,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayPrevChapter )( 
            IDvdControl2 * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *ReplayChapter )( 
            IDvdControl2 * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayNextChapter )( 
            IDvdControl2 * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayForwards )( 
            IDvdControl2 * This,
            /* [in] */ double dSpeed,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayBackwards )( 
            IDvdControl2 * This,
            /* [in] */ double dSpeed,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *ShowMenu )( 
            IDvdControl2 * This,
            /* [in] */ DVD_MENU_ID MenuID,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *Resume )( 
            IDvdControl2 * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectRelativeButton )( 
            IDvdControl2 * This,
            DVD_RELATIVE_BUTTON buttonDir);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateButton )( 
            IDvdControl2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectButton )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulButton);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAndActivateButton )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulButton);
        
        HRESULT ( STDMETHODCALLTYPE *StillOff )( 
            IDvdControl2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IDvdControl2 * This,
            /* [in] */ BOOL bState);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAudioStream )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulAudio,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectSubpictureStream )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulSubPicture,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SetSubpictureState )( 
            IDvdControl2 * This,
            /* [in] */ BOOL bState,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAngle )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulAngle,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectParentalLevel )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulParentalLevel);
        
        HRESULT ( STDMETHODCALLTYPE *SelectParentalCountry )( 
            IDvdControl2 * This,
            /* [in] */ BYTE bCountry[ 2 ]);
        
        HRESULT ( STDMETHODCALLTYPE *SelectKaraokeAudioPresentationMode )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulMode);
        
        HRESULT ( STDMETHODCALLTYPE *SelectVideoModePreference )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulPreferredDisplayMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetDVDDirectory )( 
            IDvdControl2 * This,
            /* [in] */ LPCWSTR pszwPath);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateAtPosition )( 
            IDvdControl2 * This,
            /* [in] */ POINT point);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAtPosition )( 
            IDvdControl2 * This,
            /* [in] */ POINT point);
        
        HRESULT ( STDMETHODCALLTYPE *PlayChaptersAutoStop )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ ULONG ulChapter,
            /* [in] */ ULONG ulChaptersToPlay,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *AcceptParentalLevelChange )( 
            IDvdControl2 * This,
            /* [in] */ BOOL bAccept);
        
        HRESULT ( STDMETHODCALLTYPE *SetOption )( 
            IDvdControl2 * This,
            /* [in] */ DVD_OPTION_FLAG flag,
            /* [in] */ BOOL fState);
        
        HRESULT ( STDMETHODCALLTYPE *SetState )( 
            IDvdControl2 * This,
            /* [in] */ IDvdState *pState,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *PlayPeriodInTitleAutoStop )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulTitle,
            /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
            /* [in] */ DVD_HMSF_TIMECODE *pEndTime,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SetGPRM )( 
            IDvdControl2 * This,
            /* [in] */ ULONG ulIndex,
            /* [in] */ WORD wValue,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDvdCmd **ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectDefaultMenuLanguage )( 
            IDvdControl2 * This,
            /* [in] */ LCID Language);
        
        HRESULT ( STDMETHODCALLTYPE *SelectDefaultAudioLanguage )( 
            IDvdControl2 * This,
            /* [in] */ LCID Language,
            /* [in] */ DVD_AUDIO_LANG_EXT audioExtension);
        
        HRESULT ( STDMETHODCALLTYPE *SelectDefaultSubpictureLanguage )( 
            IDvdControl2 * This,
            /* [in] */ LCID Language,
            /* [in] */ DVD_SUBPICTURE_LANG_EXT subpictureExtension);
        
        END_INTERFACE
    } IDvdControl2Vtbl;

    interface IDvdControl2
    {
        CONST_VTBL struct IDvdControl2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdControl2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdControl2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdControl2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdControl2_PlayTitle(This,ulTitle,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayTitle(This,ulTitle,dwFlags,ppCmd)

#define IDvdControl2_PlayChapterInTitle(This,ulTitle,ulChapter,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayChapterInTitle(This,ulTitle,ulChapter,dwFlags,ppCmd)

#define IDvdControl2_PlayAtTimeInTitle(This,ulTitle,pStartTime,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayAtTimeInTitle(This,ulTitle,pStartTime,dwFlags,ppCmd)

#define IDvdControl2_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IDvdControl2_ReturnFromSubmenu(This,dwFlags,ppCmd)	\
    (This)->lpVtbl -> ReturnFromSubmenu(This,dwFlags,ppCmd)

#define IDvdControl2_PlayAtTime(This,pTime,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayAtTime(This,pTime,dwFlags,ppCmd)

#define IDvdControl2_PlayChapter(This,ulChapter,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayChapter(This,ulChapter,dwFlags,ppCmd)

#define IDvdControl2_PlayPrevChapter(This,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayPrevChapter(This,dwFlags,ppCmd)

#define IDvdControl2_ReplayChapter(This,dwFlags,ppCmd)	\
    (This)->lpVtbl -> ReplayChapter(This,dwFlags,ppCmd)

#define IDvdControl2_PlayNextChapter(This,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayNextChapter(This,dwFlags,ppCmd)

#define IDvdControl2_PlayForwards(This,dSpeed,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayForwards(This,dSpeed,dwFlags,ppCmd)

#define IDvdControl2_PlayBackwards(This,dSpeed,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayBackwards(This,dSpeed,dwFlags,ppCmd)

#define IDvdControl2_ShowMenu(This,MenuID,dwFlags,ppCmd)	\
    (This)->lpVtbl -> ShowMenu(This,MenuID,dwFlags,ppCmd)

#define IDvdControl2_Resume(This,dwFlags,ppCmd)	\
    (This)->lpVtbl -> Resume(This,dwFlags,ppCmd)

#define IDvdControl2_SelectRelativeButton(This,buttonDir)	\
    (This)->lpVtbl -> SelectRelativeButton(This,buttonDir)

#define IDvdControl2_ActivateButton(This)	\
    (This)->lpVtbl -> ActivateButton(This)

#define IDvdControl2_SelectButton(This,ulButton)	\
    (This)->lpVtbl -> SelectButton(This,ulButton)

#define IDvdControl2_SelectAndActivateButton(This,ulButton)	\
    (This)->lpVtbl -> SelectAndActivateButton(This,ulButton)

#define IDvdControl2_StillOff(This)	\
    (This)->lpVtbl -> StillOff(This)

#define IDvdControl2_Pause(This,bState)	\
    (This)->lpVtbl -> Pause(This,bState)

#define IDvdControl2_SelectAudioStream(This,ulAudio,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SelectAudioStream(This,ulAudio,dwFlags,ppCmd)

#define IDvdControl2_SelectSubpictureStream(This,ulSubPicture,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SelectSubpictureStream(This,ulSubPicture,dwFlags,ppCmd)

#define IDvdControl2_SetSubpictureState(This,bState,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SetSubpictureState(This,bState,dwFlags,ppCmd)

#define IDvdControl2_SelectAngle(This,ulAngle,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SelectAngle(This,ulAngle,dwFlags,ppCmd)

#define IDvdControl2_SelectParentalLevel(This,ulParentalLevel)	\
    (This)->lpVtbl -> SelectParentalLevel(This,ulParentalLevel)

#define IDvdControl2_SelectParentalCountry(This,bCountry)	\
    (This)->lpVtbl -> SelectParentalCountry(This,bCountry)

#define IDvdControl2_SelectKaraokeAudioPresentationMode(This,ulMode)	\
    (This)->lpVtbl -> SelectKaraokeAudioPresentationMode(This,ulMode)

#define IDvdControl2_SelectVideoModePreference(This,ulPreferredDisplayMode)	\
    (This)->lpVtbl -> SelectVideoModePreference(This,ulPreferredDisplayMode)

#define IDvdControl2_SetDVDDirectory(This,pszwPath)	\
    (This)->lpVtbl -> SetDVDDirectory(This,pszwPath)

#define IDvdControl2_ActivateAtPosition(This,point)	\
    (This)->lpVtbl -> ActivateAtPosition(This,point)

#define IDvdControl2_SelectAtPosition(This,point)	\
    (This)->lpVtbl -> SelectAtPosition(This,point)

#define IDvdControl2_PlayChaptersAutoStop(This,ulTitle,ulChapter,ulChaptersToPlay,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayChaptersAutoStop(This,ulTitle,ulChapter,ulChaptersToPlay,dwFlags,ppCmd)

#define IDvdControl2_AcceptParentalLevelChange(This,bAccept)	\
    (This)->lpVtbl -> AcceptParentalLevelChange(This,bAccept)

#define IDvdControl2_SetOption(This,flag,fState)	\
    (This)->lpVtbl -> SetOption(This,flag,fState)

#define IDvdControl2_SetState(This,pState,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SetState(This,pState,dwFlags,ppCmd)

#define IDvdControl2_PlayPeriodInTitleAutoStop(This,ulTitle,pStartTime,pEndTime,dwFlags,ppCmd)	\
    (This)->lpVtbl -> PlayPeriodInTitleAutoStop(This,ulTitle,pStartTime,pEndTime,dwFlags,ppCmd)

#define IDvdControl2_SetGPRM(This,ulIndex,wValue,dwFlags,ppCmd)	\
    (This)->lpVtbl -> SetGPRM(This,ulIndex,wValue,dwFlags,ppCmd)

#define IDvdControl2_SelectDefaultMenuLanguage(This,Language)	\
    (This)->lpVtbl -> SelectDefaultMenuLanguage(This,Language)

#define IDvdControl2_SelectDefaultAudioLanguage(This,Language,audioExtension)	\
    (This)->lpVtbl -> SelectDefaultAudioLanguage(This,Language,audioExtension)

#define IDvdControl2_SelectDefaultSubpictureLanguage(This,Language,subpictureExtension)	\
    (This)->lpVtbl -> SelectDefaultSubpictureLanguage(This,Language,subpictureExtension)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdControl2_PlayTitle_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayChapterInTitle_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ ULONG ulChapter,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayChapterInTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayAtTimeInTitle_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayAtTimeInTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_Stop_Proxy( 
    IDvdControl2 * This);


void __RPC_STUB IDvdControl2_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_ReturnFromSubmenu_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_ReturnFromSubmenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayAtTime_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DVD_HMSF_TIMECODE *pTime,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayAtTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayChapter_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulChapter,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayPrevChapter_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayPrevChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_ReplayChapter_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_ReplayChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayNextChapter_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayNextChapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayForwards_Proxy( 
    IDvdControl2 * This,
    /* [in] */ double dSpeed,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayForwards_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayBackwards_Proxy( 
    IDvdControl2 * This,
    /* [in] */ double dSpeed,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayBackwards_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_ShowMenu_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DVD_MENU_ID MenuID,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_ShowMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_Resume_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectRelativeButton_Proxy( 
    IDvdControl2 * This,
    DVD_RELATIVE_BUTTON buttonDir);


void __RPC_STUB IDvdControl2_SelectRelativeButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_ActivateButton_Proxy( 
    IDvdControl2 * This);


void __RPC_STUB IDvdControl2_ActivateButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectButton_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulButton);


void __RPC_STUB IDvdControl2_SelectButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectAndActivateButton_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulButton);


void __RPC_STUB IDvdControl2_SelectAndActivateButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_StillOff_Proxy( 
    IDvdControl2 * This);


void __RPC_STUB IDvdControl2_StillOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_Pause_Proxy( 
    IDvdControl2 * This,
    /* [in] */ BOOL bState);


void __RPC_STUB IDvdControl2_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectAudioStream_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulAudio,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SelectAudioStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectSubpictureStream_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulSubPicture,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SelectSubpictureStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SetSubpictureState_Proxy( 
    IDvdControl2 * This,
    /* [in] */ BOOL bState,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SetSubpictureState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectAngle_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulAngle,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SelectAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectParentalLevel_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulParentalLevel);


void __RPC_STUB IDvdControl2_SelectParentalLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectParentalCountry_Proxy( 
    IDvdControl2 * This,
    /* [in] */ BYTE bCountry[ 2 ]);


void __RPC_STUB IDvdControl2_SelectParentalCountry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectKaraokeAudioPresentationMode_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulMode);


void __RPC_STUB IDvdControl2_SelectKaraokeAudioPresentationMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectVideoModePreference_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulPreferredDisplayMode);


void __RPC_STUB IDvdControl2_SelectVideoModePreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SetDVDDirectory_Proxy( 
    IDvdControl2 * This,
    /* [in] */ LPCWSTR pszwPath);


void __RPC_STUB IDvdControl2_SetDVDDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_ActivateAtPosition_Proxy( 
    IDvdControl2 * This,
    /* [in] */ POINT point);


void __RPC_STUB IDvdControl2_ActivateAtPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectAtPosition_Proxy( 
    IDvdControl2 * This,
    /* [in] */ POINT point);


void __RPC_STUB IDvdControl2_SelectAtPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayChaptersAutoStop_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ ULONG ulChapter,
    /* [in] */ ULONG ulChaptersToPlay,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayChaptersAutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_AcceptParentalLevelChange_Proxy( 
    IDvdControl2 * This,
    /* [in] */ BOOL bAccept);


void __RPC_STUB IDvdControl2_AcceptParentalLevelChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SetOption_Proxy( 
    IDvdControl2 * This,
    /* [in] */ DVD_OPTION_FLAG flag,
    /* [in] */ BOOL fState);


void __RPC_STUB IDvdControl2_SetOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SetState_Proxy( 
    IDvdControl2 * This,
    /* [in] */ IDvdState *pState,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_PlayPeriodInTitleAutoStop_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulTitle,
    /* [in] */ DVD_HMSF_TIMECODE *pStartTime,
    /* [in] */ DVD_HMSF_TIMECODE *pEndTime,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_PlayPeriodInTitleAutoStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SetGPRM_Proxy( 
    IDvdControl2 * This,
    /* [in] */ ULONG ulIndex,
    /* [in] */ WORD wValue,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDvdCmd **ppCmd);


void __RPC_STUB IDvdControl2_SetGPRM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectDefaultMenuLanguage_Proxy( 
    IDvdControl2 * This,
    /* [in] */ LCID Language);


void __RPC_STUB IDvdControl2_SelectDefaultMenuLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectDefaultAudioLanguage_Proxy( 
    IDvdControl2 * This,
    /* [in] */ LCID Language,
    /* [in] */ DVD_AUDIO_LANG_EXT audioExtension);


void __RPC_STUB IDvdControl2_SelectDefaultAudioLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdControl2_SelectDefaultSubpictureLanguage_Proxy( 
    IDvdControl2 * This,
    /* [in] */ LCID Language,
    /* [in] */ DVD_SUBPICTURE_LANG_EXT subpictureExtension);


void __RPC_STUB IDvdControl2_SelectDefaultSubpictureLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdControl2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0377 */
/* [local] */ 


enum DVD_TextStringType
    {	DVD_Struct_Volume	= 0x1,
	DVD_Struct_Title	= 0x2,
	DVD_Struct_ParentalID	= 0x3,
	DVD_Struct_PartOfTitle	= 0x4,
	DVD_Struct_Cell	= 0x5,
	DVD_Stream_Audio	= 0x10,
	DVD_Stream_Subpicture	= 0x11,
	DVD_Stream_Angle	= 0x12,
	DVD_Channel_Audio	= 0x20,
	DVD_General_Name	= 0x30,
	DVD_General_Comments	= 0x31,
	DVD_Title_Series	= 0x38,
	DVD_Title_Movie	= 0x39,
	DVD_Title_Video	= 0x3a,
	DVD_Title_Album	= 0x3b,
	DVD_Title_Song	= 0x3c,
	DVD_Title_Other	= 0x3f,
	DVD_Title_Sub_Series	= 0x40,
	DVD_Title_Sub_Movie	= 0x41,
	DVD_Title_Sub_Video	= 0x42,
	DVD_Title_Sub_Album	= 0x43,
	DVD_Title_Sub_Song	= 0x44,
	DVD_Title_Sub_Other	= 0x47,
	DVD_Title_Orig_Series	= 0x48,
	DVD_Title_Orig_Movie	= 0x49,
	DVD_Title_Orig_Video	= 0x4a,
	DVD_Title_Orig_Album	= 0x4b,
	DVD_Title_Orig_Song	= 0x4c,
	DVD_Title_Orig_Other	= 0x4f,
	DVD_Other_Scene	= 0x50,
	DVD_Other_Cut	= 0x51,
	DVD_Other_Take	= 0x52
    } ;

enum DVD_TextCharSet
    {	DVD_CharSet_Unicode	= 0,
	DVD_CharSet_ISO646	= 1,
	DVD_CharSet_JIS_Roman_Kanji	= 2,
	DVD_CharSet_ISO8859_1	= 3,
	DVD_CharSet_ShiftJIS_Kanji_Roman_Katakana	= 4
    } ;
#define DVD_TITLE_MENU				0x000
#define DVD_STREAM_DATA_CURRENT     0x800
#define DVD_STREAM_DATA_VMGM        0x400
#define DVD_STREAM_DATA_VTSM        0x401
#define DVD_DEFAULT_AUDIO_STREAM	0x0f
typedef struct tagDVD_DECODER_CAPS
    {
    DWORD dwSize;
    DWORD dwAudioCaps;
    double dFwdMaxRateVideo;
    double dFwdMaxRateAudio;
    double dFwdMaxRateSP;
    double dBwdMaxRateVideo;
    double dBwdMaxRateAudio;
    double dBwdMaxRateSP;
    DWORD dwRes1;
    DWORD dwRes2;
    DWORD dwRes3;
    DWORD dwRes4;
    } 	DVD_DECODER_CAPS;

#define DVD_AUDIO_CAPS_AC3		0x00000001
#define DVD_AUDIO_CAPS_MPEG2	0x00000002
#define DVD_AUDIO_CAPS_LPCM		0x00000004
#define DVD_AUDIO_CAPS_DTS		0x00000008
#define DVD_AUDIO_CAPS_SDDS		0x00000010


extern RPC_IF_HANDLE __MIDL_itf_strmif_0377_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0377_v0_0_s_ifspec;

#ifndef __IDvdInfo2_INTERFACE_DEFINED__
#define __IDvdInfo2_INTERFACE_DEFINED__

/* interface IDvdInfo2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDvdInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("34151510-EEC0-11D2-8201-00A0C9D74842")
    IDvdInfo2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCurrentDomain( 
            /* [out] */ DVD_DOMAIN *pDomain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentLocation( 
            /* [out] */ DVD_PLAYBACK_LOCATION2 *pLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTotalTitleTime( 
            /* [out] */ DVD_HMSF_TIMECODE *pTotalTime,
            /* [out] */ ULONG *ulTimeCodeFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentButton( 
            /* [out] */ ULONG *pulButtonsAvailable,
            /* [out] */ ULONG *pulCurrentButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentAngle( 
            /* [out] */ ULONG *pulAnglesAvailable,
            /* [out] */ ULONG *pulCurrentAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentAudio( 
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentSubpicture( 
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream,
            /* [out] */ BOOL *pbIsDisabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentUOPS( 
            /* [out] */ ULONG *pulUOPs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllSPRMs( 
            /* [out] */ SPRMARRAY *pRegisterArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllGPRMs( 
            /* [out] */ GPRMARRAY *pRegisterArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioLanguage( 
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubpictureLanguage( 
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTitleAttributes( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ DVD_MenuAttributes *pMenu,
            /* [out] */ DVD_TitleAttributes *pTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVMGAttributes( 
            /* [out] */ DVD_MenuAttributes *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentVideoAttributes( 
            /* [out] */ DVD_VideoAttributes *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioAttributes( 
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_AudioAttributes *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetKaraokeAttributes( 
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_KaraokeAttributes *pAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubpictureAttributes( 
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_SubpictureAttributes *pATR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDVolumeInfo( 
            /* [out] */ ULONG *pulNumOfVolumes,
            /* [out] */ ULONG *pulVolume,
            /* [out] */ DVD_DISC_SIDE *pSide,
            /* [out] */ ULONG *pulNumOfTitles) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDTextNumberOfLanguages( 
            /* [out] */ ULONG *pulNumOfLangs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDTextLanguageInfo( 
            /* [in] */ ULONG ulLangIndex,
            /* [out] */ ULONG *pulNumOfStrings,
            /* [out] */ LCID *pLangCode,
            /* [out] */ enum DVD_TextCharSet *pbCharacterSet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDTextStringAsNative( 
            /* [in] */ ULONG ulLangIndex,
            /* [in] */ ULONG ulStringIndex,
            /* [out] */ BYTE *pbBuffer,
            /* [in] */ ULONG ulMaxBufferSize,
            /* [out] */ ULONG *pulActualSize,
            /* [out] */ enum DVD_TextStringType *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDTextStringAsUnicode( 
            /* [in] */ ULONG ulLangIndex,
            /* [in] */ ULONG ulStringIndex,
            /* [out] */ WCHAR *pchwBuffer,
            /* [in] */ ULONG ulMaxBufferSize,
            /* [out] */ ULONG *pulActualSize,
            /* [out] */ enum DVD_TextStringType *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPlayerParentalLevel( 
            /* [out] */ ULONG *pulParentalLevel,
            /* [out] */ BYTE pbCountryCode[ 2 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfChapters( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulNumOfChapters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTitleParentalLevels( 
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulParentalLevels) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDVDDirectory( 
            /* [size_is][out] */ LPWSTR pszwPath,
            /* [in] */ ULONG ulMaxSize,
            /* [out] */ ULONG *pulActualSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsAudioStreamEnabled( 
            /* [in] */ ULONG ulStreamNum,
            /* [out] */ BOOL *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDiscID( 
            /* [in] */ LPCWSTR pszwPath,
            /* [out] */ ULONGLONG *pullDiscID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ IDvdState **pStateData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMenuLanguages( 
            /* [out] */ LCID *pLanguages,
            /* [in] */ ULONG ulMaxLanguages,
            /* [out] */ ULONG *pulActualLanguages) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetButtonAtPosition( 
            /* [in] */ POINT point,
            /* [out] */ ULONG *pulButtonIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCmdFromEvent( 
            /* [in] */ LONG_PTR lParam1,
            /* [out] */ IDvdCmd **pCmdObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultMenuLanguage( 
            /* [out] */ LCID *pLanguage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultAudioLanguage( 
            /* [out] */ LCID *pLanguage,
            /* [out] */ DVD_AUDIO_LANG_EXT *pAudioExtension) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultSubpictureLanguage( 
            /* [out] */ LCID *pLanguage,
            /* [out] */ DVD_SUBPICTURE_LANG_EXT *pSubpictureExtension) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDecoderCaps( 
            /* [out] */ DVD_DECODER_CAPS *pCaps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetButtonRect( 
            /* [in] */ ULONG ulButton,
            /* [out] */ RECT *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSubpictureStreamEnabled( 
            /* [in] */ ULONG ulStreamNum,
            /* [out] */ BOOL *pbEnabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdInfo2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdInfo2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdInfo2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentDomain )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_DOMAIN *pDomain);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentLocation )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_PLAYBACK_LOCATION2 *pLocation);
        
        HRESULT ( STDMETHODCALLTYPE *GetTotalTitleTime )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_HMSF_TIMECODE *pTotalTime,
            /* [out] */ ULONG *ulTimeCodeFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentButton )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulButtonsAvailable,
            /* [out] */ ULONG *pulCurrentButton);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentAngle )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulAnglesAvailable,
            /* [out] */ ULONG *pulCurrentAngle);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentAudio )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSubpicture )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulStreamsAvailable,
            /* [out] */ ULONG *pulCurrentStream,
            /* [out] */ BOOL *pbIsDisabled);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentUOPS )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulUOPs);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllSPRMs )( 
            IDvdInfo2 * This,
            /* [out] */ SPRMARRAY *pRegisterArray);
        
        HRESULT ( STDMETHODCALLTYPE *GetAllGPRMs )( 
            IDvdInfo2 * This,
            /* [out] */ GPRMARRAY *pRegisterArray);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioLanguage )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage);
        
        HRESULT ( STDMETHODCALLTYPE *GetSubpictureLanguage )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ LCID *pLanguage);
        
        HRESULT ( STDMETHODCALLTYPE *GetTitleAttributes )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ DVD_MenuAttributes *pMenu,
            /* [out] */ DVD_TitleAttributes *pTitle);
        
        HRESULT ( STDMETHODCALLTYPE *GetVMGAttributes )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_MenuAttributes *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentVideoAttributes )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_VideoAttributes *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioAttributes )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_AudioAttributes *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetKaraokeAttributes )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_KaraokeAttributes *pAttributes);
        
        HRESULT ( STDMETHODCALLTYPE *GetSubpictureAttributes )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStream,
            /* [out] */ DVD_SubpictureAttributes *pATR);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDVolumeInfo )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulNumOfVolumes,
            /* [out] */ ULONG *pulVolume,
            /* [out] */ DVD_DISC_SIDE *pSide,
            /* [out] */ ULONG *pulNumOfTitles);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDTextNumberOfLanguages )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulNumOfLangs);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDTextLanguageInfo )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulLangIndex,
            /* [out] */ ULONG *pulNumOfStrings,
            /* [out] */ LCID *pLangCode,
            /* [out] */ enum DVD_TextCharSet *pbCharacterSet);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDTextStringAsNative )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulLangIndex,
            /* [in] */ ULONG ulStringIndex,
            /* [out] */ BYTE *pbBuffer,
            /* [in] */ ULONG ulMaxBufferSize,
            /* [out] */ ULONG *pulActualSize,
            /* [out] */ enum DVD_TextStringType *pType);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDTextStringAsUnicode )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulLangIndex,
            /* [in] */ ULONG ulStringIndex,
            /* [out] */ WCHAR *pchwBuffer,
            /* [in] */ ULONG ulMaxBufferSize,
            /* [out] */ ULONG *pulActualSize,
            /* [out] */ enum DVD_TextStringType *pType);
        
        HRESULT ( STDMETHODCALLTYPE *GetPlayerParentalLevel )( 
            IDvdInfo2 * This,
            /* [out] */ ULONG *pulParentalLevel,
            /* [out] */ BYTE pbCountryCode[ 2 ]);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfChapters )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulNumOfChapters);
        
        HRESULT ( STDMETHODCALLTYPE *GetTitleParentalLevels )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulTitle,
            /* [out] */ ULONG *pulParentalLevels);
        
        HRESULT ( STDMETHODCALLTYPE *GetDVDDirectory )( 
            IDvdInfo2 * This,
            /* [size_is][out] */ LPWSTR pszwPath,
            /* [in] */ ULONG ulMaxSize,
            /* [out] */ ULONG *pulActualSize);
        
        HRESULT ( STDMETHODCALLTYPE *IsAudioStreamEnabled )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStreamNum,
            /* [out] */ BOOL *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *GetDiscID )( 
            IDvdInfo2 * This,
            /* [in] */ LPCWSTR pszwPath,
            /* [out] */ ULONGLONG *pullDiscID);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IDvdInfo2 * This,
            /* [out] */ IDvdState **pStateData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMenuLanguages )( 
            IDvdInfo2 * This,
            /* [out] */ LCID *pLanguages,
            /* [in] */ ULONG ulMaxLanguages,
            /* [out] */ ULONG *pulActualLanguages);
        
        HRESULT ( STDMETHODCALLTYPE *GetButtonAtPosition )( 
            IDvdInfo2 * This,
            /* [in] */ POINT point,
            /* [out] */ ULONG *pulButtonIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetCmdFromEvent )( 
            IDvdInfo2 * This,
            /* [in] */ LONG_PTR lParam1,
            /* [out] */ IDvdCmd **pCmdObj);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultMenuLanguage )( 
            IDvdInfo2 * This,
            /* [out] */ LCID *pLanguage);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultAudioLanguage )( 
            IDvdInfo2 * This,
            /* [out] */ LCID *pLanguage,
            /* [out] */ DVD_AUDIO_LANG_EXT *pAudioExtension);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultSubpictureLanguage )( 
            IDvdInfo2 * This,
            /* [out] */ LCID *pLanguage,
            /* [out] */ DVD_SUBPICTURE_LANG_EXT *pSubpictureExtension);
        
        HRESULT ( STDMETHODCALLTYPE *GetDecoderCaps )( 
            IDvdInfo2 * This,
            /* [out] */ DVD_DECODER_CAPS *pCaps);
        
        HRESULT ( STDMETHODCALLTYPE *GetButtonRect )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulButton,
            /* [out] */ RECT *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *IsSubpictureStreamEnabled )( 
            IDvdInfo2 * This,
            /* [in] */ ULONG ulStreamNum,
            /* [out] */ BOOL *pbEnabled);
        
        END_INTERFACE
    } IDvdInfo2Vtbl;

    interface IDvdInfo2
    {
        CONST_VTBL struct IDvdInfo2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdInfo2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdInfo2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdInfo2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdInfo2_GetCurrentDomain(This,pDomain)	\
    (This)->lpVtbl -> GetCurrentDomain(This,pDomain)

#define IDvdInfo2_GetCurrentLocation(This,pLocation)	\
    (This)->lpVtbl -> GetCurrentLocation(This,pLocation)

#define IDvdInfo2_GetTotalTitleTime(This,pTotalTime,ulTimeCodeFlags)	\
    (This)->lpVtbl -> GetTotalTitleTime(This,pTotalTime,ulTimeCodeFlags)

#define IDvdInfo2_GetCurrentButton(This,pulButtonsAvailable,pulCurrentButton)	\
    (This)->lpVtbl -> GetCurrentButton(This,pulButtonsAvailable,pulCurrentButton)

#define IDvdInfo2_GetCurrentAngle(This,pulAnglesAvailable,pulCurrentAngle)	\
    (This)->lpVtbl -> GetCurrentAngle(This,pulAnglesAvailable,pulCurrentAngle)

#define IDvdInfo2_GetCurrentAudio(This,pulStreamsAvailable,pulCurrentStream)	\
    (This)->lpVtbl -> GetCurrentAudio(This,pulStreamsAvailable,pulCurrentStream)

#define IDvdInfo2_GetCurrentSubpicture(This,pulStreamsAvailable,pulCurrentStream,pbIsDisabled)	\
    (This)->lpVtbl -> GetCurrentSubpicture(This,pulStreamsAvailable,pulCurrentStream,pbIsDisabled)

#define IDvdInfo2_GetCurrentUOPS(This,pulUOPs)	\
    (This)->lpVtbl -> GetCurrentUOPS(This,pulUOPs)

#define IDvdInfo2_GetAllSPRMs(This,pRegisterArray)	\
    (This)->lpVtbl -> GetAllSPRMs(This,pRegisterArray)

#define IDvdInfo2_GetAllGPRMs(This,pRegisterArray)	\
    (This)->lpVtbl -> GetAllGPRMs(This,pRegisterArray)

#define IDvdInfo2_GetAudioLanguage(This,ulStream,pLanguage)	\
    (This)->lpVtbl -> GetAudioLanguage(This,ulStream,pLanguage)

#define IDvdInfo2_GetSubpictureLanguage(This,ulStream,pLanguage)	\
    (This)->lpVtbl -> GetSubpictureLanguage(This,ulStream,pLanguage)

#define IDvdInfo2_GetTitleAttributes(This,ulTitle,pMenu,pTitle)	\
    (This)->lpVtbl -> GetTitleAttributes(This,ulTitle,pMenu,pTitle)

#define IDvdInfo2_GetVMGAttributes(This,pATR)	\
    (This)->lpVtbl -> GetVMGAttributes(This,pATR)

#define IDvdInfo2_GetCurrentVideoAttributes(This,pATR)	\
    (This)->lpVtbl -> GetCurrentVideoAttributes(This,pATR)

#define IDvdInfo2_GetAudioAttributes(This,ulStream,pATR)	\
    (This)->lpVtbl -> GetAudioAttributes(This,ulStream,pATR)

#define IDvdInfo2_GetKaraokeAttributes(This,ulStream,pAttributes)	\
    (This)->lpVtbl -> GetKaraokeAttributes(This,ulStream,pAttributes)

#define IDvdInfo2_GetSubpictureAttributes(This,ulStream,pATR)	\
    (This)->lpVtbl -> GetSubpictureAttributes(This,ulStream,pATR)

#define IDvdInfo2_GetDVDVolumeInfo(This,pulNumOfVolumes,pulVolume,pSide,pulNumOfTitles)	\
    (This)->lpVtbl -> GetDVDVolumeInfo(This,pulNumOfVolumes,pulVolume,pSide,pulNumOfTitles)

#define IDvdInfo2_GetDVDTextNumberOfLanguages(This,pulNumOfLangs)	\
    (This)->lpVtbl -> GetDVDTextNumberOfLanguages(This,pulNumOfLangs)

#define IDvdInfo2_GetDVDTextLanguageInfo(This,ulLangIndex,pulNumOfStrings,pLangCode,pbCharacterSet)	\
    (This)->lpVtbl -> GetDVDTextLanguageInfo(This,ulLangIndex,pulNumOfStrings,pLangCode,pbCharacterSet)

#define IDvdInfo2_GetDVDTextStringAsNative(This,ulLangIndex,ulStringIndex,pbBuffer,ulMaxBufferSize,pulActualSize,pType)	\
    (This)->lpVtbl -> GetDVDTextStringAsNative(This,ulLangIndex,ulStringIndex,pbBuffer,ulMaxBufferSize,pulActualSize,pType)

#define IDvdInfo2_GetDVDTextStringAsUnicode(This,ulLangIndex,ulStringIndex,pchwBuffer,ulMaxBufferSize,pulActualSize,pType)	\
    (This)->lpVtbl -> GetDVDTextStringAsUnicode(This,ulLangIndex,ulStringIndex,pchwBuffer,ulMaxBufferSize,pulActualSize,pType)

#define IDvdInfo2_GetPlayerParentalLevel(This,pulParentalLevel,pbCountryCode)	\
    (This)->lpVtbl -> GetPlayerParentalLevel(This,pulParentalLevel,pbCountryCode)

#define IDvdInfo2_GetNumberOfChapters(This,ulTitle,pulNumOfChapters)	\
    (This)->lpVtbl -> GetNumberOfChapters(This,ulTitle,pulNumOfChapters)

#define IDvdInfo2_GetTitleParentalLevels(This,ulTitle,pulParentalLevels)	\
    (This)->lpVtbl -> GetTitleParentalLevels(This,ulTitle,pulParentalLevels)

#define IDvdInfo2_GetDVDDirectory(This,pszwPath,ulMaxSize,pulActualSize)	\
    (This)->lpVtbl -> GetDVDDirectory(This,pszwPath,ulMaxSize,pulActualSize)

#define IDvdInfo2_IsAudioStreamEnabled(This,ulStreamNum,pbEnabled)	\
    (This)->lpVtbl -> IsAudioStreamEnabled(This,ulStreamNum,pbEnabled)

#define IDvdInfo2_GetDiscID(This,pszwPath,pullDiscID)	\
    (This)->lpVtbl -> GetDiscID(This,pszwPath,pullDiscID)

#define IDvdInfo2_GetState(This,pStateData)	\
    (This)->lpVtbl -> GetState(This,pStateData)

#define IDvdInfo2_GetMenuLanguages(This,pLanguages,ulMaxLanguages,pulActualLanguages)	\
    (This)->lpVtbl -> GetMenuLanguages(This,pLanguages,ulMaxLanguages,pulActualLanguages)

#define IDvdInfo2_GetButtonAtPosition(This,point,pulButtonIndex)	\
    (This)->lpVtbl -> GetButtonAtPosition(This,point,pulButtonIndex)

#define IDvdInfo2_GetCmdFromEvent(This,lParam1,pCmdObj)	\
    (This)->lpVtbl -> GetCmdFromEvent(This,lParam1,pCmdObj)

#define IDvdInfo2_GetDefaultMenuLanguage(This,pLanguage)	\
    (This)->lpVtbl -> GetDefaultMenuLanguage(This,pLanguage)

#define IDvdInfo2_GetDefaultAudioLanguage(This,pLanguage,pAudioExtension)	\
    (This)->lpVtbl -> GetDefaultAudioLanguage(This,pLanguage,pAudioExtension)

#define IDvdInfo2_GetDefaultSubpictureLanguage(This,pLanguage,pSubpictureExtension)	\
    (This)->lpVtbl -> GetDefaultSubpictureLanguage(This,pLanguage,pSubpictureExtension)

#define IDvdInfo2_GetDecoderCaps(This,pCaps)	\
    (This)->lpVtbl -> GetDecoderCaps(This,pCaps)

#define IDvdInfo2_GetButtonRect(This,ulButton,pRect)	\
    (This)->lpVtbl -> GetButtonRect(This,ulButton,pRect)

#define IDvdInfo2_IsSubpictureStreamEnabled(This,ulStreamNum,pbEnabled)	\
    (This)->lpVtbl -> IsSubpictureStreamEnabled(This,ulStreamNum,pbEnabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentDomain_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_DOMAIN *pDomain);


void __RPC_STUB IDvdInfo2_GetCurrentDomain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentLocation_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_PLAYBACK_LOCATION2 *pLocation);


void __RPC_STUB IDvdInfo2_GetCurrentLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetTotalTitleTime_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_HMSF_TIMECODE *pTotalTime,
    /* [out] */ ULONG *ulTimeCodeFlags);


void __RPC_STUB IDvdInfo2_GetTotalTitleTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentButton_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulButtonsAvailable,
    /* [out] */ ULONG *pulCurrentButton);


void __RPC_STUB IDvdInfo2_GetCurrentButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentAngle_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulAnglesAvailable,
    /* [out] */ ULONG *pulCurrentAngle);


void __RPC_STUB IDvdInfo2_GetCurrentAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentAudio_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulStreamsAvailable,
    /* [out] */ ULONG *pulCurrentStream);


void __RPC_STUB IDvdInfo2_GetCurrentAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentSubpicture_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulStreamsAvailable,
    /* [out] */ ULONG *pulCurrentStream,
    /* [out] */ BOOL *pbIsDisabled);


void __RPC_STUB IDvdInfo2_GetCurrentSubpicture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentUOPS_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulUOPs);


void __RPC_STUB IDvdInfo2_GetCurrentUOPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetAllSPRMs_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ SPRMARRAY *pRegisterArray);


void __RPC_STUB IDvdInfo2_GetAllSPRMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetAllGPRMs_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ GPRMARRAY *pRegisterArray);


void __RPC_STUB IDvdInfo2_GetAllGPRMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetAudioLanguage_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ LCID *pLanguage);


void __RPC_STUB IDvdInfo2_GetAudioLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetSubpictureLanguage_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ LCID *pLanguage);


void __RPC_STUB IDvdInfo2_GetSubpictureLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetTitleAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ DVD_MenuAttributes *pMenu,
    /* [out] */ DVD_TitleAttributes *pTitle);


void __RPC_STUB IDvdInfo2_GetTitleAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetVMGAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_MenuAttributes *pATR);


void __RPC_STUB IDvdInfo2_GetVMGAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCurrentVideoAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_VideoAttributes *pATR);


void __RPC_STUB IDvdInfo2_GetCurrentVideoAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetAudioAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ DVD_AudioAttributes *pATR);


void __RPC_STUB IDvdInfo2_GetAudioAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetKaraokeAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ DVD_KaraokeAttributes *pAttributes);


void __RPC_STUB IDvdInfo2_GetKaraokeAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetSubpictureAttributes_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStream,
    /* [out] */ DVD_SubpictureAttributes *pATR);


void __RPC_STUB IDvdInfo2_GetSubpictureAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDVolumeInfo_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulNumOfVolumes,
    /* [out] */ ULONG *pulVolume,
    /* [out] */ DVD_DISC_SIDE *pSide,
    /* [out] */ ULONG *pulNumOfTitles);


void __RPC_STUB IDvdInfo2_GetDVDVolumeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDTextNumberOfLanguages_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulNumOfLangs);


void __RPC_STUB IDvdInfo2_GetDVDTextNumberOfLanguages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDTextLanguageInfo_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulLangIndex,
    /* [out] */ ULONG *pulNumOfStrings,
    /* [out] */ LCID *pLangCode,
    /* [out] */ enum DVD_TextCharSet *pbCharacterSet);


void __RPC_STUB IDvdInfo2_GetDVDTextLanguageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDTextStringAsNative_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulLangIndex,
    /* [in] */ ULONG ulStringIndex,
    /* [out] */ BYTE *pbBuffer,
    /* [in] */ ULONG ulMaxBufferSize,
    /* [out] */ ULONG *pulActualSize,
    /* [out] */ enum DVD_TextStringType *pType);


void __RPC_STUB IDvdInfo2_GetDVDTextStringAsNative_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDTextStringAsUnicode_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulLangIndex,
    /* [in] */ ULONG ulStringIndex,
    /* [out] */ WCHAR *pchwBuffer,
    /* [in] */ ULONG ulMaxBufferSize,
    /* [out] */ ULONG *pulActualSize,
    /* [out] */ enum DVD_TextStringType *pType);


void __RPC_STUB IDvdInfo2_GetDVDTextStringAsUnicode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetPlayerParentalLevel_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ ULONG *pulParentalLevel,
    /* [out] */ BYTE pbCountryCode[ 2 ]);


void __RPC_STUB IDvdInfo2_GetPlayerParentalLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetNumberOfChapters_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ ULONG *pulNumOfChapters);


void __RPC_STUB IDvdInfo2_GetNumberOfChapters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetTitleParentalLevels_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulTitle,
    /* [out] */ ULONG *pulParentalLevels);


void __RPC_STUB IDvdInfo2_GetTitleParentalLevels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDVDDirectory_Proxy( 
    IDvdInfo2 * This,
    /* [size_is][out] */ LPWSTR pszwPath,
    /* [in] */ ULONG ulMaxSize,
    /* [out] */ ULONG *pulActualSize);


void __RPC_STUB IDvdInfo2_GetDVDDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_IsAudioStreamEnabled_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStreamNum,
    /* [out] */ BOOL *pbEnabled);


void __RPC_STUB IDvdInfo2_IsAudioStreamEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDiscID_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ LPCWSTR pszwPath,
    /* [out] */ ULONGLONG *pullDiscID);


void __RPC_STUB IDvdInfo2_GetDiscID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetState_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ IDvdState **pStateData);


void __RPC_STUB IDvdInfo2_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetMenuLanguages_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ LCID *pLanguages,
    /* [in] */ ULONG ulMaxLanguages,
    /* [out] */ ULONG *pulActualLanguages);


void __RPC_STUB IDvdInfo2_GetMenuLanguages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetButtonAtPosition_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ POINT point,
    /* [out] */ ULONG *pulButtonIndex);


void __RPC_STUB IDvdInfo2_GetButtonAtPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetCmdFromEvent_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ LONG_PTR lParam1,
    /* [out] */ IDvdCmd **pCmdObj);


void __RPC_STUB IDvdInfo2_GetCmdFromEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDefaultMenuLanguage_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ LCID *pLanguage);


void __RPC_STUB IDvdInfo2_GetDefaultMenuLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDefaultAudioLanguage_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ LCID *pLanguage,
    /* [out] */ DVD_AUDIO_LANG_EXT *pAudioExtension);


void __RPC_STUB IDvdInfo2_GetDefaultAudioLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDefaultSubpictureLanguage_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ LCID *pLanguage,
    /* [out] */ DVD_SUBPICTURE_LANG_EXT *pSubpictureExtension);


void __RPC_STUB IDvdInfo2_GetDefaultSubpictureLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetDecoderCaps_Proxy( 
    IDvdInfo2 * This,
    /* [out] */ DVD_DECODER_CAPS *pCaps);


void __RPC_STUB IDvdInfo2_GetDecoderCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_GetButtonRect_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulButton,
    /* [out] */ RECT *pRect);


void __RPC_STUB IDvdInfo2_GetButtonRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdInfo2_IsSubpictureStreamEnabled_Proxy( 
    IDvdInfo2 * This,
    /* [in] */ ULONG ulStreamNum,
    /* [out] */ BOOL *pbEnabled);


void __RPC_STUB IDvdInfo2_IsSubpictureStreamEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdInfo2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0379 */
/* [local] */ 

typedef 
enum _AM_DVD_GRAPH_FLAGS
    {	AM_DVD_HWDEC_PREFER	= 0x1,
	AM_DVD_HWDEC_ONLY	= 0x2,
	AM_DVD_SWDEC_PREFER	= 0x4,
	AM_DVD_SWDEC_ONLY	= 0x8,
	AM_DVD_NOVPE	= 0x100,
	AM_DVD_VMR9_ONLY	= 0x800
    } 	AM_DVD_GRAPH_FLAGS;

typedef 
enum _AM_DVD_STREAM_FLAGS
    {	AM_DVD_STREAM_VIDEO	= 0x1,
	AM_DVD_STREAM_AUDIO	= 0x2,
	AM_DVD_STREAM_SUBPIC	= 0x4
    } 	AM_DVD_STREAM_FLAGS;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_strmif_0379_0001
    {
    HRESULT hrVPEStatus;
    BOOL bDvdVolInvalid;
    BOOL bDvdVolUnknown;
    BOOL bNoLine21In;
    BOOL bNoLine21Out;
    int iNumStreams;
    int iNumStreamsFailed;
    DWORD dwFailedStreamsFlag;
    } 	AM_DVD_RENDERSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0379_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0379_v0_0_s_ifspec;

#ifndef __IDvdGraphBuilder_INTERFACE_DEFINED__
#define __IDvdGraphBuilder_INTERFACE_DEFINED__

/* interface IDvdGraphBuilder */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDvdGraphBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FCC152B6-F372-11d0-8E00-00C04FD7C08B")
    IDvdGraphBuilder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFiltergraph( 
            /* [out] */ IGraphBuilder **ppGB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDvdInterface( 
            /* [in] */ REFIID riid,
            /* [out] */ void **ppvIF) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderDvdVideoVolume( 
            /* [in] */ LPCWSTR lpcwszPathName,
            /* [in] */ DWORD dwFlags,
            /* [out] */ AM_DVD_RENDERSTATUS *pStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDvdGraphBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDvdGraphBuilder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDvdGraphBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDvdGraphBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFiltergraph )( 
            IDvdGraphBuilder * This,
            /* [out] */ IGraphBuilder **ppGB);
        
        HRESULT ( STDMETHODCALLTYPE *GetDvdInterface )( 
            IDvdGraphBuilder * This,
            /* [in] */ REFIID riid,
            /* [out] */ void **ppvIF);
        
        HRESULT ( STDMETHODCALLTYPE *RenderDvdVideoVolume )( 
            IDvdGraphBuilder * This,
            /* [in] */ LPCWSTR lpcwszPathName,
            /* [in] */ DWORD dwFlags,
            /* [out] */ AM_DVD_RENDERSTATUS *pStatus);
        
        END_INTERFACE
    } IDvdGraphBuilderVtbl;

    interface IDvdGraphBuilder
    {
        CONST_VTBL struct IDvdGraphBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDvdGraphBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDvdGraphBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDvdGraphBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDvdGraphBuilder_GetFiltergraph(This,ppGB)	\
    (This)->lpVtbl -> GetFiltergraph(This,ppGB)

#define IDvdGraphBuilder_GetDvdInterface(This,riid,ppvIF)	\
    (This)->lpVtbl -> GetDvdInterface(This,riid,ppvIF)

#define IDvdGraphBuilder_RenderDvdVideoVolume(This,lpcwszPathName,dwFlags,pStatus)	\
    (This)->lpVtbl -> RenderDvdVideoVolume(This,lpcwszPathName,dwFlags,pStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDvdGraphBuilder_GetFiltergraph_Proxy( 
    IDvdGraphBuilder * This,
    /* [out] */ IGraphBuilder **ppGB);


void __RPC_STUB IDvdGraphBuilder_GetFiltergraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdGraphBuilder_GetDvdInterface_Proxy( 
    IDvdGraphBuilder * This,
    /* [in] */ REFIID riid,
    /* [out] */ void **ppvIF);


void __RPC_STUB IDvdGraphBuilder_GetDvdInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDvdGraphBuilder_RenderDvdVideoVolume_Proxy( 
    IDvdGraphBuilder * This,
    /* [in] */ LPCWSTR lpcwszPathName,
    /* [in] */ DWORD dwFlags,
    /* [out] */ AM_DVD_RENDERSTATUS *pStatus);


void __RPC_STUB IDvdGraphBuilder_RenderDvdVideoVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDvdGraphBuilder_INTERFACE_DEFINED__ */


#ifndef __IDDrawExclModeVideo_INTERFACE_DEFINED__
#define __IDDrawExclModeVideo_INTERFACE_DEFINED__

/* interface IDDrawExclModeVideo */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDDrawExclModeVideo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("153ACC21-D83B-11d1-82BF-00A0C9696C8F")
    IDDrawExclModeVideo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDDrawObject( 
            /* [in] */ IDirectDraw *pDDrawObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDDrawObject( 
            /* [out] */ IDirectDraw **ppDDrawObject,
            /* [out] */ BOOL *pbUsingExternal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDDrawSurface( 
            /* [in] */ IDirectDrawSurface *pDDrawSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDDrawSurface( 
            /* [out] */ IDirectDrawSurface **ppDDrawSurface,
            /* [out] */ BOOL *pbUsingExternal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDrawParameters( 
            /* [in] */ const RECT *prcSource,
            /* [in] */ const RECT *prcTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNativeVideoProps( 
            /* [out] */ DWORD *pdwVideoWidth,
            /* [out] */ DWORD *pdwVideoHeight,
            /* [out] */ DWORD *pdwPictAspectRatioX,
            /* [out] */ DWORD *pdwPictAspectRatioY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCallbackInterface( 
            /* [in] */ IDDrawExclModeVideoCallback *pCallback,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDDrawExclModeVideoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDDrawExclModeVideo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDDrawExclModeVideo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDDrawExclModeVideo * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDDrawObject )( 
            IDDrawExclModeVideo * This,
            /* [in] */ IDirectDraw *pDDrawObject);
        
        HRESULT ( STDMETHODCALLTYPE *GetDDrawObject )( 
            IDDrawExclModeVideo * This,
            /* [out] */ IDirectDraw **ppDDrawObject,
            /* [out] */ BOOL *pbUsingExternal);
        
        HRESULT ( STDMETHODCALLTYPE *SetDDrawSurface )( 
            IDDrawExclModeVideo * This,
            /* [in] */ IDirectDrawSurface *pDDrawSurface);
        
        HRESULT ( STDMETHODCALLTYPE *GetDDrawSurface )( 
            IDDrawExclModeVideo * This,
            /* [out] */ IDirectDrawSurface **ppDDrawSurface,
            /* [out] */ BOOL *pbUsingExternal);
        
        HRESULT ( STDMETHODCALLTYPE *SetDrawParameters )( 
            IDDrawExclModeVideo * This,
            /* [in] */ const RECT *prcSource,
            /* [in] */ const RECT *prcTarget);
        
        HRESULT ( STDMETHODCALLTYPE *GetNativeVideoProps )( 
            IDDrawExclModeVideo * This,
            /* [out] */ DWORD *pdwVideoWidth,
            /* [out] */ DWORD *pdwVideoHeight,
            /* [out] */ DWORD *pdwPictAspectRatioX,
            /* [out] */ DWORD *pdwPictAspectRatioY);
        
        HRESULT ( STDMETHODCALLTYPE *SetCallbackInterface )( 
            IDDrawExclModeVideo * This,
            /* [in] */ IDDrawExclModeVideoCallback *pCallback,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IDDrawExclModeVideoVtbl;

    interface IDDrawExclModeVideo
    {
        CONST_VTBL struct IDDrawExclModeVideoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDDrawExclModeVideo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDDrawExclModeVideo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDDrawExclModeVideo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDDrawExclModeVideo_SetDDrawObject(This,pDDrawObject)	\
    (This)->lpVtbl -> SetDDrawObject(This,pDDrawObject)

#define IDDrawExclModeVideo_GetDDrawObject(This,ppDDrawObject,pbUsingExternal)	\
    (This)->lpVtbl -> GetDDrawObject(This,ppDDrawObject,pbUsingExternal)

#define IDDrawExclModeVideo_SetDDrawSurface(This,pDDrawSurface)	\
    (This)->lpVtbl -> SetDDrawSurface(This,pDDrawSurface)

#define IDDrawExclModeVideo_GetDDrawSurface(This,ppDDrawSurface,pbUsingExternal)	\
    (This)->lpVtbl -> GetDDrawSurface(This,ppDDrawSurface,pbUsingExternal)

#define IDDrawExclModeVideo_SetDrawParameters(This,prcSource,prcTarget)	\
    (This)->lpVtbl -> SetDrawParameters(This,prcSource,prcTarget)

#define IDDrawExclModeVideo_GetNativeVideoProps(This,pdwVideoWidth,pdwVideoHeight,pdwPictAspectRatioX,pdwPictAspectRatioY)	\
    (This)->lpVtbl -> GetNativeVideoProps(This,pdwVideoWidth,pdwVideoHeight,pdwPictAspectRatioX,pdwPictAspectRatioY)

#define IDDrawExclModeVideo_SetCallbackInterface(This,pCallback,dwFlags)	\
    (This)->lpVtbl -> SetCallbackInterface(This,pCallback,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_SetDDrawObject_Proxy( 
    IDDrawExclModeVideo * This,
    /* [in] */ IDirectDraw *pDDrawObject);


void __RPC_STUB IDDrawExclModeVideo_SetDDrawObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_GetDDrawObject_Proxy( 
    IDDrawExclModeVideo * This,
    /* [out] */ IDirectDraw **ppDDrawObject,
    /* [out] */ BOOL *pbUsingExternal);


void __RPC_STUB IDDrawExclModeVideo_GetDDrawObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_SetDDrawSurface_Proxy( 
    IDDrawExclModeVideo * This,
    /* [in] */ IDirectDrawSurface *pDDrawSurface);


void __RPC_STUB IDDrawExclModeVideo_SetDDrawSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_GetDDrawSurface_Proxy( 
    IDDrawExclModeVideo * This,
    /* [out] */ IDirectDrawSurface **ppDDrawSurface,
    /* [out] */ BOOL *pbUsingExternal);


void __RPC_STUB IDDrawExclModeVideo_GetDDrawSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_SetDrawParameters_Proxy( 
    IDDrawExclModeVideo * This,
    /* [in] */ const RECT *prcSource,
    /* [in] */ const RECT *prcTarget);


void __RPC_STUB IDDrawExclModeVideo_SetDrawParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_GetNativeVideoProps_Proxy( 
    IDDrawExclModeVideo * This,
    /* [out] */ DWORD *pdwVideoWidth,
    /* [out] */ DWORD *pdwVideoHeight,
    /* [out] */ DWORD *pdwPictAspectRatioX,
    /* [out] */ DWORD *pdwPictAspectRatioY);


void __RPC_STUB IDDrawExclModeVideo_GetNativeVideoProps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideo_SetCallbackInterface_Proxy( 
    IDDrawExclModeVideo * This,
    /* [in] */ IDDrawExclModeVideoCallback *pCallback,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IDDrawExclModeVideo_SetCallbackInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDDrawExclModeVideo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0381 */
/* [local] */ 


enum _AM_OVERLAY_NOTIFY_FLAGS
    {	AM_OVERLAY_NOTIFY_VISIBLE_CHANGE	= 0x1,
	AM_OVERLAY_NOTIFY_SOURCE_CHANGE	= 0x2,
	AM_OVERLAY_NOTIFY_DEST_CHANGE	= 0x4
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0381_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0381_v0_0_s_ifspec;

#ifndef __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__
#define __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__

/* interface IDDrawExclModeVideoCallback */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDDrawExclModeVideoCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("913c24a0-20ab-11d2-9038-00a0c9697298")
    IDDrawExclModeVideoCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnUpdateOverlay( 
            /* [in] */ BOOL bBefore,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL bOldVisible,
            /* [in] */ const RECT *prcOldSrc,
            /* [in] */ const RECT *prcOldDest,
            /* [in] */ BOOL bNewVisible,
            /* [in] */ const RECT *prcNewSrc,
            /* [in] */ const RECT *prcNewDest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnUpdateColorKey( 
            /* [in] */ const COLORKEY *pKey,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnUpdateSize( 
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight,
            /* [in] */ DWORD dwARWidth,
            /* [in] */ DWORD dwARHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDDrawExclModeVideoCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDDrawExclModeVideoCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDDrawExclModeVideoCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDDrawExclModeVideoCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnUpdateOverlay )( 
            IDDrawExclModeVideoCallback * This,
            /* [in] */ BOOL bBefore,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL bOldVisible,
            /* [in] */ const RECT *prcOldSrc,
            /* [in] */ const RECT *prcOldDest,
            /* [in] */ BOOL bNewVisible,
            /* [in] */ const RECT *prcNewSrc,
            /* [in] */ const RECT *prcNewDest);
        
        HRESULT ( STDMETHODCALLTYPE *OnUpdateColorKey )( 
            IDDrawExclModeVideoCallback * This,
            /* [in] */ const COLORKEY *pKey,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *OnUpdateSize )( 
            IDDrawExclModeVideoCallback * This,
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight,
            /* [in] */ DWORD dwARWidth,
            /* [in] */ DWORD dwARHeight);
        
        END_INTERFACE
    } IDDrawExclModeVideoCallbackVtbl;

    interface IDDrawExclModeVideoCallback
    {
        CONST_VTBL struct IDDrawExclModeVideoCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDDrawExclModeVideoCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDDrawExclModeVideoCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDDrawExclModeVideoCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDDrawExclModeVideoCallback_OnUpdateOverlay(This,bBefore,dwFlags,bOldVisible,prcOldSrc,prcOldDest,bNewVisible,prcNewSrc,prcNewDest)	\
    (This)->lpVtbl -> OnUpdateOverlay(This,bBefore,dwFlags,bOldVisible,prcOldSrc,prcOldDest,bNewVisible,prcNewSrc,prcNewDest)

#define IDDrawExclModeVideoCallback_OnUpdateColorKey(This,pKey,dwColor)	\
    (This)->lpVtbl -> OnUpdateColorKey(This,pKey,dwColor)

#define IDDrawExclModeVideoCallback_OnUpdateSize(This,dwWidth,dwHeight,dwARWidth,dwARHeight)	\
    (This)->lpVtbl -> OnUpdateSize(This,dwWidth,dwHeight,dwARWidth,dwARHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDDrawExclModeVideoCallback_OnUpdateOverlay_Proxy( 
    IDDrawExclModeVideoCallback * This,
    /* [in] */ BOOL bBefore,
    /* [in] */ DWORD dwFlags,
    /* [in] */ BOOL bOldVisible,
    /* [in] */ const RECT *prcOldSrc,
    /* [in] */ const RECT *prcOldDest,
    /* [in] */ BOOL bNewVisible,
    /* [in] */ const RECT *prcNewSrc,
    /* [in] */ const RECT *prcNewDest);


void __RPC_STUB IDDrawExclModeVideoCallback_OnUpdateOverlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideoCallback_OnUpdateColorKey_Proxy( 
    IDDrawExclModeVideoCallback * This,
    /* [in] */ const COLORKEY *pKey,
    /* [in] */ DWORD dwColor);


void __RPC_STUB IDDrawExclModeVideoCallback_OnUpdateColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDDrawExclModeVideoCallback_OnUpdateSize_Proxy( 
    IDDrawExclModeVideoCallback * This,
    /* [in] */ DWORD dwWidth,
    /* [in] */ DWORD dwHeight,
    /* [in] */ DWORD dwARWidth,
    /* [in] */ DWORD dwARHeight);


void __RPC_STUB IDDrawExclModeVideoCallback_OnUpdateSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDDrawExclModeVideoCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0382 */
/* [local] */ 







extern RPC_IF_HANDLE __MIDL_itf_strmif_0382_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0382_v0_0_s_ifspec;

#ifndef __IPinConnection_INTERFACE_DEFINED__
#define __IPinConnection_INTERFACE_DEFINED__

/* interface IPinConnection */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IPinConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4a9a62d3-27d4-403d-91e9-89f540e55534")
    IPinConnection : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DynamicQueryAccept( 
            /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyEndOfStream( 
            /* [in] */ HANDLE hNotifyEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsEndPin( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DynamicDisconnect( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPinConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPinConnection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPinConnection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPinConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *DynamicQueryAccept )( 
            IPinConnection * This,
            /* [in] */ const AM_MEDIA_TYPE *pmt);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyEndOfStream )( 
            IPinConnection * This,
            /* [in] */ HANDLE hNotifyEvent);
        
        HRESULT ( STDMETHODCALLTYPE *IsEndPin )( 
            IPinConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *DynamicDisconnect )( 
            IPinConnection * This);
        
        END_INTERFACE
    } IPinConnectionVtbl;

    interface IPinConnection
    {
        CONST_VTBL struct IPinConnectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPinConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPinConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPinConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPinConnection_DynamicQueryAccept(This,pmt)	\
    (This)->lpVtbl -> DynamicQueryAccept(This,pmt)

#define IPinConnection_NotifyEndOfStream(This,hNotifyEvent)	\
    (This)->lpVtbl -> NotifyEndOfStream(This,hNotifyEvent)

#define IPinConnection_IsEndPin(This)	\
    (This)->lpVtbl -> IsEndPin(This)

#define IPinConnection_DynamicDisconnect(This)	\
    (This)->lpVtbl -> DynamicDisconnect(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPinConnection_DynamicQueryAccept_Proxy( 
    IPinConnection * This,
    /* [in] */ const AM_MEDIA_TYPE *pmt);


void __RPC_STUB IPinConnection_DynamicQueryAccept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPinConnection_NotifyEndOfStream_Proxy( 
    IPinConnection * This,
    /* [in] */ HANDLE hNotifyEvent);


void __RPC_STUB IPinConnection_NotifyEndOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPinConnection_IsEndPin_Proxy( 
    IPinConnection * This);


void __RPC_STUB IPinConnection_IsEndPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPinConnection_DynamicDisconnect_Proxy( 
    IPinConnection * This);


void __RPC_STUB IPinConnection_DynamicDisconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPinConnection_INTERFACE_DEFINED__ */


#ifndef __IPinFlowControl_INTERFACE_DEFINED__
#define __IPinFlowControl_INTERFACE_DEFINED__

/* interface IPinFlowControl */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IPinFlowControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c56e9858-dbf3-4f6b-8119-384af2060deb")
    IPinFlowControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Block( 
            /* [in] */ DWORD dwBlockFlags,
            /* [in] */ HANDLE hEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPinFlowControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPinFlowControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPinFlowControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPinFlowControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *Block )( 
            IPinFlowControl * This,
            /* [in] */ DWORD dwBlockFlags,
            /* [in] */ HANDLE hEvent);
        
        END_INTERFACE
    } IPinFlowControlVtbl;

    interface IPinFlowControl
    {
        CONST_VTBL struct IPinFlowControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPinFlowControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPinFlowControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPinFlowControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPinFlowControl_Block(This,dwBlockFlags,hEvent)	\
    (This)->lpVtbl -> Block(This,dwBlockFlags,hEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPinFlowControl_Block_Proxy( 
    IPinFlowControl * This,
    /* [in] */ DWORD dwBlockFlags,
    /* [in] */ HANDLE hEvent);


void __RPC_STUB IPinFlowControl_Block_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPinFlowControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0384 */
/* [local] */ 


enum _AM_PIN_FLOW_CONTROL_BLOCK_FLAGS
    {	AM_PIN_FLOW_CONTROL_BLOCK	= 0x1
    } ;
typedef 
enum _AM_GRAPH_CONFIG_RECONNECT_FLAGS
    {	AM_GRAPH_CONFIG_RECONNECT_DIRECTCONNECT	= 0x1,
	AM_GRAPH_CONFIG_RECONNECT_CACHE_REMOVED_FILTERS	= 0x2,
	AM_GRAPH_CONFIG_RECONNECT_USE_ONLY_CACHED_FILTERS	= 0x4
    } 	AM_GRAPH_CONFIG_RECONNECT_FLAGS;


enum _REM_FILTER_FLAGS
    {	REMFILTERF_LEAVECONNECTED	= 0x1
    } ;
typedef 
enum _AM_FILTER_FLAGS
    {	AM_FILTER_FLAGS_REMOVABLE	= 0x1
    } 	AM_FILTER_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0384_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0384_v0_0_s_ifspec;

#ifndef __IGraphConfig_INTERFACE_DEFINED__
#define __IGraphConfig_INTERFACE_DEFINED__

/* interface IGraphConfig */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IGraphConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("03A1EB8E-32BF-4245-8502-114D08A9CB88")
    IGraphConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reconnect( 
            /* [in] */ IPin *pOutputPin,
            /* [in] */ IPin *pInputPin,
            /* [in] */ const AM_MEDIA_TYPE *pmtFirstConnection,
            /* [in] */ IBaseFilter *pUsingFilter,
            /* [in] */ HANDLE hAbortEvent,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reconfigure( 
            /* [in] */ IGraphConfigCallback *pCallback,
            /* [in] */ PVOID pvContext,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HANDLE hAbortEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddFilterToCache( 
            /* [in] */ IBaseFilter *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumCacheFilter( 
            /* [out] */ IEnumFilters **pEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveFilterFromCache( 
            /* [in] */ IBaseFilter *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStartTime( 
            /* [out] */ REFERENCE_TIME *prtStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushThroughData( 
            /* [in] */ IPin *pOutputPin,
            /* [in] */ IPinConnection *pConnection,
            /* [in] */ HANDLE hEventAbort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFilterFlags( 
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFilterFlags( 
            /* [in] */ IBaseFilter *pFilter,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveFilterEx( 
            /* [in] */ IBaseFilter *pFilter,
            DWORD Flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGraphConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGraphConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGraphConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reconnect )( 
            IGraphConfig * This,
            /* [in] */ IPin *pOutputPin,
            /* [in] */ IPin *pInputPin,
            /* [in] */ const AM_MEDIA_TYPE *pmtFirstConnection,
            /* [in] */ IBaseFilter *pUsingFilter,
            /* [in] */ HANDLE hAbortEvent,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Reconfigure )( 
            IGraphConfig * This,
            /* [in] */ IGraphConfigCallback *pCallback,
            /* [in] */ PVOID pvContext,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HANDLE hAbortEvent);
        
        HRESULT ( STDMETHODCALLTYPE *AddFilterToCache )( 
            IGraphConfig * This,
            /* [in] */ IBaseFilter *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *EnumCacheFilter )( 
            IGraphConfig * This,
            /* [out] */ IEnumFilters **pEnum);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveFilterFromCache )( 
            IGraphConfig * This,
            /* [in] */ IBaseFilter *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetStartTime )( 
            IGraphConfig * This,
            /* [out] */ REFERENCE_TIME *prtStart);
        
        HRESULT ( STDMETHODCALLTYPE *PushThroughData )( 
            IGraphConfig * This,
            /* [in] */ IPin *pOutputPin,
            /* [in] */ IPinConnection *pConnection,
            /* [in] */ HANDLE hEventAbort);
        
        HRESULT ( STDMETHODCALLTYPE *SetFilterFlags )( 
            IGraphConfig * This,
            /* [in] */ IBaseFilter *pFilter,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetFilterFlags )( 
            IGraphConfig * This,
            /* [in] */ IBaseFilter *pFilter,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveFilterEx )( 
            IGraphConfig * This,
            /* [in] */ IBaseFilter *pFilter,
            DWORD Flags);
        
        END_INTERFACE
    } IGraphConfigVtbl;

    interface IGraphConfig
    {
        CONST_VTBL struct IGraphConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphConfig_Reconnect(This,pOutputPin,pInputPin,pmtFirstConnection,pUsingFilter,hAbortEvent,dwFlags)	\
    (This)->lpVtbl -> Reconnect(This,pOutputPin,pInputPin,pmtFirstConnection,pUsingFilter,hAbortEvent,dwFlags)

#define IGraphConfig_Reconfigure(This,pCallback,pvContext,dwFlags,hAbortEvent)	\
    (This)->lpVtbl -> Reconfigure(This,pCallback,pvContext,dwFlags,hAbortEvent)

#define IGraphConfig_AddFilterToCache(This,pFilter)	\
    (This)->lpVtbl -> AddFilterToCache(This,pFilter)

#define IGraphConfig_EnumCacheFilter(This,pEnum)	\
    (This)->lpVtbl -> EnumCacheFilter(This,pEnum)

#define IGraphConfig_RemoveFilterFromCache(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilterFromCache(This,pFilter)

#define IGraphConfig_GetStartTime(This,prtStart)	\
    (This)->lpVtbl -> GetStartTime(This,prtStart)

#define IGraphConfig_PushThroughData(This,pOutputPin,pConnection,hEventAbort)	\
    (This)->lpVtbl -> PushThroughData(This,pOutputPin,pConnection,hEventAbort)

#define IGraphConfig_SetFilterFlags(This,pFilter,dwFlags)	\
    (This)->lpVtbl -> SetFilterFlags(This,pFilter,dwFlags)

#define IGraphConfig_GetFilterFlags(This,pFilter,pdwFlags)	\
    (This)->lpVtbl -> GetFilterFlags(This,pFilter,pdwFlags)

#define IGraphConfig_RemoveFilterEx(This,pFilter,Flags)	\
    (This)->lpVtbl -> RemoveFilterEx(This,pFilter,Flags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphConfig_Reconnect_Proxy( 
    IGraphConfig * This,
    /* [in] */ IPin *pOutputPin,
    /* [in] */ IPin *pInputPin,
    /* [in] */ const AM_MEDIA_TYPE *pmtFirstConnection,
    /* [in] */ IBaseFilter *pUsingFilter,
    /* [in] */ HANDLE hAbortEvent,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IGraphConfig_Reconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_Reconfigure_Proxy( 
    IGraphConfig * This,
    /* [in] */ IGraphConfigCallback *pCallback,
    /* [in] */ PVOID pvContext,
    /* [in] */ DWORD dwFlags,
    /* [in] */ HANDLE hAbortEvent);


void __RPC_STUB IGraphConfig_Reconfigure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_AddFilterToCache_Proxy( 
    IGraphConfig * This,
    /* [in] */ IBaseFilter *pFilter);


void __RPC_STUB IGraphConfig_AddFilterToCache_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_EnumCacheFilter_Proxy( 
    IGraphConfig * This,
    /* [out] */ IEnumFilters **pEnum);


void __RPC_STUB IGraphConfig_EnumCacheFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_RemoveFilterFromCache_Proxy( 
    IGraphConfig * This,
    /* [in] */ IBaseFilter *pFilter);


void __RPC_STUB IGraphConfig_RemoveFilterFromCache_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_GetStartTime_Proxy( 
    IGraphConfig * This,
    /* [out] */ REFERENCE_TIME *prtStart);


void __RPC_STUB IGraphConfig_GetStartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_PushThroughData_Proxy( 
    IGraphConfig * This,
    /* [in] */ IPin *pOutputPin,
    /* [in] */ IPinConnection *pConnection,
    /* [in] */ HANDLE hEventAbort);


void __RPC_STUB IGraphConfig_PushThroughData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_SetFilterFlags_Proxy( 
    IGraphConfig * This,
    /* [in] */ IBaseFilter *pFilter,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IGraphConfig_SetFilterFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_GetFilterFlags_Proxy( 
    IGraphConfig * This,
    /* [in] */ IBaseFilter *pFilter,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IGraphConfig_GetFilterFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphConfig_RemoveFilterEx_Proxy( 
    IGraphConfig * This,
    /* [in] */ IBaseFilter *pFilter,
    DWORD Flags);


void __RPC_STUB IGraphConfig_RemoveFilterEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphConfig_INTERFACE_DEFINED__ */


#ifndef __IGraphConfigCallback_INTERFACE_DEFINED__
#define __IGraphConfigCallback_INTERFACE_DEFINED__

/* interface IGraphConfigCallback */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IGraphConfigCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ade0fd60-d19d-11d2-abf6-00a0c905f375")
    IGraphConfigCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reconfigure( 
            PVOID pvContext,
            DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphConfigCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGraphConfigCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGraphConfigCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGraphConfigCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reconfigure )( 
            IGraphConfigCallback * This,
            PVOID pvContext,
            DWORD dwFlags);
        
        END_INTERFACE
    } IGraphConfigCallbackVtbl;

    interface IGraphConfigCallback
    {
        CONST_VTBL struct IGraphConfigCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphConfigCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphConfigCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphConfigCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphConfigCallback_Reconfigure(This,pvContext,dwFlags)	\
    (This)->lpVtbl -> Reconfigure(This,pvContext,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphConfigCallback_Reconfigure_Proxy( 
    IGraphConfigCallback * This,
    PVOID pvContext,
    DWORD dwFlags);


void __RPC_STUB IGraphConfigCallback_Reconfigure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphConfigCallback_INTERFACE_DEFINED__ */


#ifndef __IFilterChain_INTERFACE_DEFINED__
#define __IFilterChain_INTERFACE_DEFINED__

/* interface IFilterChain */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_IFilterChain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DCFBDCF6-0DC2-45f5-9AB2-7C330EA09C29")
    IFilterChain : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartChain( 
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseChain( 
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopChain( 
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveChain( 
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterChainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFilterChain * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFilterChain * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFilterChain * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartChain )( 
            IFilterChain * This,
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter);
        
        HRESULT ( STDMETHODCALLTYPE *PauseChain )( 
            IFilterChain * This,
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter);
        
        HRESULT ( STDMETHODCALLTYPE *StopChain )( 
            IFilterChain * This,
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveChain )( 
            IFilterChain * This,
            /* [in] */ IBaseFilter *pStartFilter,
            /* [in] */ IBaseFilter *pEndFilter);
        
        END_INTERFACE
    } IFilterChainVtbl;

    interface IFilterChain
    {
        CONST_VTBL struct IFilterChainVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterChain_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterChain_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterChain_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterChain_StartChain(This,pStartFilter,pEndFilter)	\
    (This)->lpVtbl -> StartChain(This,pStartFilter,pEndFilter)

#define IFilterChain_PauseChain(This,pStartFilter,pEndFilter)	\
    (This)->lpVtbl -> PauseChain(This,pStartFilter,pEndFilter)

#define IFilterChain_StopChain(This,pStartFilter,pEndFilter)	\
    (This)->lpVtbl -> StopChain(This,pStartFilter,pEndFilter)

#define IFilterChain_RemoveChain(This,pStartFilter,pEndFilter)	\
    (This)->lpVtbl -> RemoveChain(This,pStartFilter,pEndFilter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterChain_StartChain_Proxy( 
    IFilterChain * This,
    /* [in] */ IBaseFilter *pStartFilter,
    /* [in] */ IBaseFilter *pEndFilter);


void __RPC_STUB IFilterChain_StartChain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterChain_PauseChain_Proxy( 
    IFilterChain * This,
    /* [in] */ IBaseFilter *pStartFilter,
    /* [in] */ IBaseFilter *pEndFilter);


void __RPC_STUB IFilterChain_PauseChain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterChain_StopChain_Proxy( 
    IFilterChain * This,
    /* [in] */ IBaseFilter *pStartFilter,
    /* [in] */ IBaseFilter *pEndFilter);


void __RPC_STUB IFilterChain_StopChain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterChain_RemoveChain_Proxy( 
    IFilterChain * This,
    /* [in] */ IBaseFilter *pStartFilter,
    /* [in] */ IBaseFilter *pEndFilter);


void __RPC_STUB IFilterChain_RemoveChain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterChain_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0387 */
/* [local] */ 

#if 0
typedef DWORD *LPDIRECTDRAW7;

typedef DWORD *LPDIRECTDRAWSURFACE7;

typedef DWORD *LPDDPIXELFORMAT;

typedef DWORD *LPBITMAPINFOHEADER;

typedef /* [public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_strmif_0387_0001
    {
    DWORD dw1;
    DWORD dw2;
    } 	DDCOLORKEY;

typedef DDCOLORKEY *LPDDCOLORKEY;

#endif
#include <ddraw.h>














typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0387_0002
    {	VMRSample_SyncPoint	= 0x1,
	VMRSample_Preroll	= 0x2,
	VMRSample_Discontinuity	= 0x4,
	VMRSample_TimeValid	= 0x8
    } 	VMRPresentationFlags;

typedef struct tagVMRPRESENTATIONINFO
    {
    DWORD dwFlags;
    LPDIRECTDRAWSURFACE7 lpSurf;
    REFERENCE_TIME rtStart;
    REFERENCE_TIME rtEnd;
    SIZE szAspectRatio;
    RECT rcSrc;
    RECT rcDst;
    DWORD dwTypeSpecificFlags;
    DWORD dwInterlaceFlags;
    } 	VMRPRESENTATIONINFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0387_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0387_v0_0_s_ifspec;

#ifndef __IVMRImagePresenter_INTERFACE_DEFINED__
#define __IVMRImagePresenter_INTERFACE_DEFINED__

/* interface IVMRImagePresenter */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImagePresenter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE704FE7-E71E-41fb-BAA2-C4403E1182F5")
    IVMRImagePresenter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartPresenting( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopPresenting( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PresentImage( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMRPRESENTATIONINFO *lpPresInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImagePresenterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImagePresenter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImagePresenter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImagePresenter * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartPresenting )( 
            IVMRImagePresenter * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *StopPresenting )( 
            IVMRImagePresenter * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *PresentImage )( 
            IVMRImagePresenter * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMRPRESENTATIONINFO *lpPresInfo);
        
        END_INTERFACE
    } IVMRImagePresenterVtbl;

    interface IVMRImagePresenter
    {
        CONST_VTBL struct IVMRImagePresenterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImagePresenter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImagePresenter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImagePresenter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImagePresenter_StartPresenting(This,dwUserID)	\
    (This)->lpVtbl -> StartPresenting(This,dwUserID)

#define IVMRImagePresenter_StopPresenting(This,dwUserID)	\
    (This)->lpVtbl -> StopPresenting(This,dwUserID)

#define IVMRImagePresenter_PresentImage(This,dwUserID,lpPresInfo)	\
    (This)->lpVtbl -> PresentImage(This,dwUserID,lpPresInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImagePresenter_StartPresenting_Proxy( 
    IVMRImagePresenter * This,
    /* [in] */ DWORD_PTR dwUserID);


void __RPC_STUB IVMRImagePresenter_StartPresenting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenter_StopPresenting_Proxy( 
    IVMRImagePresenter * This,
    /* [in] */ DWORD_PTR dwUserID);


void __RPC_STUB IVMRImagePresenter_StopPresenting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenter_PresentImage_Proxy( 
    IVMRImagePresenter * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ VMRPRESENTATIONINFO *lpPresInfo);


void __RPC_STUB IVMRImagePresenter_PresentImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImagePresenter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0388 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0388_0001
    {	AMAP_PIXELFORMAT_VALID	= 0x1,
	AMAP_3D_TARGET	= 0x2,
	AMAP_ALLOW_SYSMEM	= 0x4,
	AMAP_FORCE_SYSMEM	= 0x8,
	AMAP_DIRECTED_FLIP	= 0x10,
	AMAP_DXVA_TARGET	= 0x20
    } 	VMRSurfaceAllocationFlags;

typedef struct tagVMRALLOCATIONINFO
    {
    DWORD dwFlags;
    LPBITMAPINFOHEADER lpHdr;
    LPDDPIXELFORMAT lpPixFmt;
    SIZE szAspectRatio;
    DWORD dwMinBuffers;
    DWORD dwMaxBuffers;
    DWORD dwInterlaceFlags;
    SIZE szNativeSize;
    } 	VMRALLOCATIONINFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0388_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0388_v0_0_s_ifspec;

#ifndef __IVMRSurfaceAllocator_INTERFACE_DEFINED__
#define __IVMRSurfaceAllocator_INTERFACE_DEFINED__

/* interface IVMRSurfaceAllocator */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurfaceAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31ce832e-4484-458b-8cca-f4d7e3db0b52")
    IVMRSurfaceAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AllocateSurface( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMRALLOCATIONINFO *lpAllocInfo,
            /* [out][in] */ DWORD *lpdwActualBuffers,
            /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeSurface( 
            /* [in] */ DWORD_PTR dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrepareSurface( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ LPDIRECTDRAWSURFACE7 lpSurface,
            /* [in] */ DWORD dwSurfaceFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdviseNotify( 
            /* [in] */ IVMRSurfaceAllocatorNotify *lpIVMRSurfAllocNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurfaceAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurfaceAllocator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurfaceAllocator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurfaceAllocator * This);
        
        HRESULT ( STDMETHODCALLTYPE *AllocateSurface )( 
            IVMRSurfaceAllocator * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMRALLOCATIONINFO *lpAllocInfo,
            /* [out][in] */ DWORD *lpdwActualBuffers,
            /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface);
        
        HRESULT ( STDMETHODCALLTYPE *FreeSurface )( 
            IVMRSurfaceAllocator * This,
            /* [in] */ DWORD_PTR dwID);
        
        HRESULT ( STDMETHODCALLTYPE *PrepareSurface )( 
            IVMRSurfaceAllocator * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ LPDIRECTDRAWSURFACE7 lpSurface,
            /* [in] */ DWORD dwSurfaceFlags);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseNotify )( 
            IVMRSurfaceAllocator * This,
            /* [in] */ IVMRSurfaceAllocatorNotify *lpIVMRSurfAllocNotify);
        
        END_INTERFACE
    } IVMRSurfaceAllocatorVtbl;

    interface IVMRSurfaceAllocator
    {
        CONST_VTBL struct IVMRSurfaceAllocatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurfaceAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurfaceAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurfaceAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurfaceAllocator_AllocateSurface(This,dwUserID,lpAllocInfo,lpdwActualBuffers,lplpSurface)	\
    (This)->lpVtbl -> AllocateSurface(This,dwUserID,lpAllocInfo,lpdwActualBuffers,lplpSurface)

#define IVMRSurfaceAllocator_FreeSurface(This,dwID)	\
    (This)->lpVtbl -> FreeSurface(This,dwID)

#define IVMRSurfaceAllocator_PrepareSurface(This,dwUserID,lpSurface,dwSurfaceFlags)	\
    (This)->lpVtbl -> PrepareSurface(This,dwUserID,lpSurface,dwSurfaceFlags)

#define IVMRSurfaceAllocator_AdviseNotify(This,lpIVMRSurfAllocNotify)	\
    (This)->lpVtbl -> AdviseNotify(This,lpIVMRSurfAllocNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator_AllocateSurface_Proxy( 
    IVMRSurfaceAllocator * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ VMRALLOCATIONINFO *lpAllocInfo,
    /* [out][in] */ DWORD *lpdwActualBuffers,
    /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface);


void __RPC_STUB IVMRSurfaceAllocator_AllocateSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator_FreeSurface_Proxy( 
    IVMRSurfaceAllocator * This,
    /* [in] */ DWORD_PTR dwID);


void __RPC_STUB IVMRSurfaceAllocator_FreeSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator_PrepareSurface_Proxy( 
    IVMRSurfaceAllocator * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ LPDIRECTDRAWSURFACE7 lpSurface,
    /* [in] */ DWORD dwSurfaceFlags);


void __RPC_STUB IVMRSurfaceAllocator_PrepareSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator_AdviseNotify_Proxy( 
    IVMRSurfaceAllocator * This,
    /* [in] */ IVMRSurfaceAllocatorNotify *lpIVMRSurfAllocNotify);


void __RPC_STUB IVMRSurfaceAllocator_AdviseNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurfaceAllocator_INTERFACE_DEFINED__ */


#ifndef __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__
#define __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__

/* interface IVMRSurfaceAllocatorNotify */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurfaceAllocatorNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aada05a8-5a4e-4729-af0b-cea27aed51e2")
    IVMRSurfaceAllocatorNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AdviseSurfaceAllocator( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ IVMRSurfaceAllocator *lpIVRMSurfaceAllocator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDDrawDevice( 
            /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
            /* [in] */ HMONITOR hMonitor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeDDrawDevice( 
            /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
            /* [in] */ HMONITOR hMonitor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreDDrawSurfaces( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyEvent( 
            /* [in] */ LONG EventCode,
            /* [in] */ LONG_PTR Param1,
            /* [in] */ LONG_PTR Param2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBorderColor( 
            /* [in] */ COLORREF clrBorder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurfaceAllocatorNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurfaceAllocatorNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurfaceAllocatorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseSurfaceAllocator )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ IVMRSurfaceAllocator *lpIVRMSurfaceAllocator);
        
        HRESULT ( STDMETHODCALLTYPE *SetDDrawDevice )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
            /* [in] */ HMONITOR hMonitor);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeDDrawDevice )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
            /* [in] */ HMONITOR hMonitor);
        
        HRESULT ( STDMETHODCALLTYPE *RestoreDDrawSurfaces )( 
            IVMRSurfaceAllocatorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyEvent )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ LONG EventCode,
            /* [in] */ LONG_PTR Param1,
            /* [in] */ LONG_PTR Param2);
        
        HRESULT ( STDMETHODCALLTYPE *SetBorderColor )( 
            IVMRSurfaceAllocatorNotify * This,
            /* [in] */ COLORREF clrBorder);
        
        END_INTERFACE
    } IVMRSurfaceAllocatorNotifyVtbl;

    interface IVMRSurfaceAllocatorNotify
    {
        CONST_VTBL struct IVMRSurfaceAllocatorNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurfaceAllocatorNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurfaceAllocatorNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurfaceAllocatorNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurfaceAllocatorNotify_AdviseSurfaceAllocator(This,dwUserID,lpIVRMSurfaceAllocator)	\
    (This)->lpVtbl -> AdviseSurfaceAllocator(This,dwUserID,lpIVRMSurfaceAllocator)

#define IVMRSurfaceAllocatorNotify_SetDDrawDevice(This,lpDDrawDevice,hMonitor)	\
    (This)->lpVtbl -> SetDDrawDevice(This,lpDDrawDevice,hMonitor)

#define IVMRSurfaceAllocatorNotify_ChangeDDrawDevice(This,lpDDrawDevice,hMonitor)	\
    (This)->lpVtbl -> ChangeDDrawDevice(This,lpDDrawDevice,hMonitor)

#define IVMRSurfaceAllocatorNotify_RestoreDDrawSurfaces(This)	\
    (This)->lpVtbl -> RestoreDDrawSurfaces(This)

#define IVMRSurfaceAllocatorNotify_NotifyEvent(This,EventCode,Param1,Param2)	\
    (This)->lpVtbl -> NotifyEvent(This,EventCode,Param1,Param2)

#define IVMRSurfaceAllocatorNotify_SetBorderColor(This,clrBorder)	\
    (This)->lpVtbl -> SetBorderColor(This,clrBorder)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_AdviseSurfaceAllocator_Proxy( 
    IVMRSurfaceAllocatorNotify * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ IVMRSurfaceAllocator *lpIVRMSurfaceAllocator);


void __RPC_STUB IVMRSurfaceAllocatorNotify_AdviseSurfaceAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_SetDDrawDevice_Proxy( 
    IVMRSurfaceAllocatorNotify * This,
    /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
    /* [in] */ HMONITOR hMonitor);


void __RPC_STUB IVMRSurfaceAllocatorNotify_SetDDrawDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_ChangeDDrawDevice_Proxy( 
    IVMRSurfaceAllocatorNotify * This,
    /* [in] */ LPDIRECTDRAW7 lpDDrawDevice,
    /* [in] */ HMONITOR hMonitor);


void __RPC_STUB IVMRSurfaceAllocatorNotify_ChangeDDrawDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_RestoreDDrawSurfaces_Proxy( 
    IVMRSurfaceAllocatorNotify * This);


void __RPC_STUB IVMRSurfaceAllocatorNotify_RestoreDDrawSurfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_NotifyEvent_Proxy( 
    IVMRSurfaceAllocatorNotify * This,
    /* [in] */ LONG EventCode,
    /* [in] */ LONG_PTR Param1,
    /* [in] */ LONG_PTR Param2);


void __RPC_STUB IVMRSurfaceAllocatorNotify_NotifyEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify_SetBorderColor_Proxy( 
    IVMRSurfaceAllocatorNotify * This,
    /* [in] */ COLORREF clrBorder);


void __RPC_STUB IVMRSurfaceAllocatorNotify_SetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurfaceAllocatorNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0390 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0390_0001
    {	VMR_ARMODE_NONE	= 0,
	VMR_ARMODE_LETTER_BOX	= VMR_ARMODE_NONE + 1
    } 	VMR_ASPECT_RATIO_MODE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0390_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0390_v0_0_s_ifspec;

#ifndef __IVMRWindowlessControl_INTERFACE_DEFINED__
#define __IVMRWindowlessControl_INTERFACE_DEFINED__

/* interface IVMRWindowlessControl */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRWindowlessControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0eb1088c-4dcd-46f0-878f-39dae86a51b7")
    IVMRWindowlessControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNativeVideoSize( 
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight,
            /* [out] */ LONG *lpARWidth,
            /* [out] */ LONG *lpARHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinIdealVideoSize( 
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxIdealVideoSize( 
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoPosition( 
            /* [in] */ const LPRECT lpSRCRect,
            /* [in] */ const LPRECT lpDSTRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoPosition( 
            /* [out] */ LPRECT lpSRCRect,
            /* [out] */ LPRECT lpDSTRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAspectRatioMode( 
            /* [out] */ DWORD *lpAspectRatioMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAspectRatioMode( 
            /* [in] */ DWORD AspectRatioMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoClippingWindow( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RepaintVideo( 
            /* [in] */ HWND hwnd,
            /* [in] */ HDC hdc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisplayModeChanged( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentImage( 
            /* [out] */ BYTE **lpDib) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBorderColor( 
            /* [in] */ COLORREF Clr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBorderColor( 
            /* [out] */ COLORREF *lpClr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetColorKey( 
            /* [in] */ COLORREF Clr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColorKey( 
            /* [out] */ COLORREF *lpClr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRWindowlessControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRWindowlessControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRWindowlessControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRWindowlessControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNativeVideoSize )( 
            IVMRWindowlessControl * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight,
            /* [out] */ LONG *lpARWidth,
            /* [out] */ LONG *lpARHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinIdealVideoSize )( 
            IVMRWindowlessControl * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxIdealVideoSize )( 
            IVMRWindowlessControl * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight);
        
        HRESULT ( STDMETHODCALLTYPE *SetVideoPosition )( 
            IVMRWindowlessControl * This,
            /* [in] */ const LPRECT lpSRCRect,
            /* [in] */ const LPRECT lpDSTRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoPosition )( 
            IVMRWindowlessControl * This,
            /* [out] */ LPRECT lpSRCRect,
            /* [out] */ LPRECT lpDSTRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetAspectRatioMode )( 
            IVMRWindowlessControl * This,
            /* [out] */ DWORD *lpAspectRatioMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetAspectRatioMode )( 
            IVMRWindowlessControl * This,
            /* [in] */ DWORD AspectRatioMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetVideoClippingWindow )( 
            IVMRWindowlessControl * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *RepaintVideo )( 
            IVMRWindowlessControl * This,
            /* [in] */ HWND hwnd,
            /* [in] */ HDC hdc);
        
        HRESULT ( STDMETHODCALLTYPE *DisplayModeChanged )( 
            IVMRWindowlessControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentImage )( 
            IVMRWindowlessControl * This,
            /* [out] */ BYTE **lpDib);
        
        HRESULT ( STDMETHODCALLTYPE *SetBorderColor )( 
            IVMRWindowlessControl * This,
            /* [in] */ COLORREF Clr);
        
        HRESULT ( STDMETHODCALLTYPE *GetBorderColor )( 
            IVMRWindowlessControl * This,
            /* [out] */ COLORREF *lpClr);
        
        HRESULT ( STDMETHODCALLTYPE *SetColorKey )( 
            IVMRWindowlessControl * This,
            /* [in] */ COLORREF Clr);
        
        HRESULT ( STDMETHODCALLTYPE *GetColorKey )( 
            IVMRWindowlessControl * This,
            /* [out] */ COLORREF *lpClr);
        
        END_INTERFACE
    } IVMRWindowlessControlVtbl;

    interface IVMRWindowlessControl
    {
        CONST_VTBL struct IVMRWindowlessControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRWindowlessControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRWindowlessControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRWindowlessControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRWindowlessControl_GetNativeVideoSize(This,lpWidth,lpHeight,lpARWidth,lpARHeight)	\
    (This)->lpVtbl -> GetNativeVideoSize(This,lpWidth,lpHeight,lpARWidth,lpARHeight)

#define IVMRWindowlessControl_GetMinIdealVideoSize(This,lpWidth,lpHeight)	\
    (This)->lpVtbl -> GetMinIdealVideoSize(This,lpWidth,lpHeight)

#define IVMRWindowlessControl_GetMaxIdealVideoSize(This,lpWidth,lpHeight)	\
    (This)->lpVtbl -> GetMaxIdealVideoSize(This,lpWidth,lpHeight)

#define IVMRWindowlessControl_SetVideoPosition(This,lpSRCRect,lpDSTRect)	\
    (This)->lpVtbl -> SetVideoPosition(This,lpSRCRect,lpDSTRect)

#define IVMRWindowlessControl_GetVideoPosition(This,lpSRCRect,lpDSTRect)	\
    (This)->lpVtbl -> GetVideoPosition(This,lpSRCRect,lpDSTRect)

#define IVMRWindowlessControl_GetAspectRatioMode(This,lpAspectRatioMode)	\
    (This)->lpVtbl -> GetAspectRatioMode(This,lpAspectRatioMode)

#define IVMRWindowlessControl_SetAspectRatioMode(This,AspectRatioMode)	\
    (This)->lpVtbl -> SetAspectRatioMode(This,AspectRatioMode)

#define IVMRWindowlessControl_SetVideoClippingWindow(This,hwnd)	\
    (This)->lpVtbl -> SetVideoClippingWindow(This,hwnd)

#define IVMRWindowlessControl_RepaintVideo(This,hwnd,hdc)	\
    (This)->lpVtbl -> RepaintVideo(This,hwnd,hdc)

#define IVMRWindowlessControl_DisplayModeChanged(This)	\
    (This)->lpVtbl -> DisplayModeChanged(This)

#define IVMRWindowlessControl_GetCurrentImage(This,lpDib)	\
    (This)->lpVtbl -> GetCurrentImage(This,lpDib)

#define IVMRWindowlessControl_SetBorderColor(This,Clr)	\
    (This)->lpVtbl -> SetBorderColor(This,Clr)

#define IVMRWindowlessControl_GetBorderColor(This,lpClr)	\
    (This)->lpVtbl -> GetBorderColor(This,lpClr)

#define IVMRWindowlessControl_SetColorKey(This,Clr)	\
    (This)->lpVtbl -> SetColorKey(This,Clr)

#define IVMRWindowlessControl_GetColorKey(This,lpClr)	\
    (This)->lpVtbl -> GetColorKey(This,lpClr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetNativeVideoSize_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight,
    /* [out] */ LONG *lpARWidth,
    /* [out] */ LONG *lpARHeight);


void __RPC_STUB IVMRWindowlessControl_GetNativeVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetMinIdealVideoSize_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight);


void __RPC_STUB IVMRWindowlessControl_GetMinIdealVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetMaxIdealVideoSize_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight);


void __RPC_STUB IVMRWindowlessControl_GetMaxIdealVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_SetVideoPosition_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ const LPRECT lpSRCRect,
    /* [in] */ const LPRECT lpDSTRect);


void __RPC_STUB IVMRWindowlessControl_SetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetVideoPosition_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ LPRECT lpSRCRect,
    /* [out] */ LPRECT lpDSTRect);


void __RPC_STUB IVMRWindowlessControl_GetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetAspectRatioMode_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ DWORD *lpAspectRatioMode);


void __RPC_STUB IVMRWindowlessControl_GetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_SetAspectRatioMode_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ DWORD AspectRatioMode);


void __RPC_STUB IVMRWindowlessControl_SetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_SetVideoClippingWindow_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB IVMRWindowlessControl_SetVideoClippingWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_RepaintVideo_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ HWND hwnd,
    /* [in] */ HDC hdc);


void __RPC_STUB IVMRWindowlessControl_RepaintVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_DisplayModeChanged_Proxy( 
    IVMRWindowlessControl * This);


void __RPC_STUB IVMRWindowlessControl_DisplayModeChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetCurrentImage_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ BYTE **lpDib);


void __RPC_STUB IVMRWindowlessControl_GetCurrentImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_SetBorderColor_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ COLORREF Clr);


void __RPC_STUB IVMRWindowlessControl_SetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetBorderColor_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ COLORREF *lpClr);


void __RPC_STUB IVMRWindowlessControl_GetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_SetColorKey_Proxy( 
    IVMRWindowlessControl * This,
    /* [in] */ COLORREF Clr);


void __RPC_STUB IVMRWindowlessControl_SetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl_GetColorKey_Proxy( 
    IVMRWindowlessControl * This,
    /* [out] */ COLORREF *lpClr);


void __RPC_STUB IVMRWindowlessControl_GetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRWindowlessControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0391 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0391_0001
    {	MixerPref_NoDecimation	= 0x1,
	MixerPref_DecimateOutput	= 0x2,
	MixerPref_DecimateMask	= 0xf,
	MixerPref_BiLinearFiltering	= 0x10,
	MixerPref_PointFiltering	= 0x20,
	MixerPref_FilteringMask	= 0xf0,
	MixerPref_RenderTargetRGB	= 0x100,
	MixerPref_RenderTargetYUV420	= 0x200,
	MixerPref_RenderTargetYUV422	= 0x400,
	MixerPref_RenderTargetYUV444	= 0x800,
	MixerPref_RenderTargetReserved	= 0xf000,
	MixerPref_RenderTargetMask	= 0xff00
    } 	VMRMixerPrefs;

typedef struct _NORMALIZEDRECT
    {
    float left;
    float top;
    float right;
    float bottom;
    } 	NORMALIZEDRECT;

typedef struct _NORMALIZEDRECT *PNORMALIZEDRECT;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0391_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0391_v0_0_s_ifspec;

#ifndef __IVMRMixerControl_INTERFACE_DEFINED__
#define __IVMRMixerControl_INTERFACE_DEFINED__

/* interface IVMRMixerControl */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRMixerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1c1a17b0-bed0-415d-974b-dc6696131599")
    IVMRMixerControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ DWORD dwStreamID,
            /* [in] */ float Alpha) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ float *pAlpha) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetZOrder( 
            /* [in] */ DWORD dwStreamID,
            /* [in] */ DWORD dwZ) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetZOrder( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ DWORD *pZ) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputRect( 
            /* [in] */ DWORD dwStreamID,
            /* [in] */ const NORMALIZEDRECT *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputRect( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ NORMALIZEDRECT *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBackgroundClr( 
            /* [in] */ COLORREF ClrBkg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackgroundClr( 
            /* [in] */ COLORREF *lpClrBkg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMixingPrefs( 
            /* [in] */ DWORD dwMixerPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMixingPrefs( 
            /* [out] */ DWORD *pdwMixerPrefs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMixerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMixerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMixerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMixerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlpha )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ float Alpha);
        
        HRESULT ( STDMETHODCALLTYPE *GetAlpha )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ float *pAlpha);
        
        HRESULT ( STDMETHODCALLTYPE *SetZOrder )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ DWORD dwZ);
        
        HRESULT ( STDMETHODCALLTYPE *GetZOrder )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ DWORD *pZ);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputRect )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ const NORMALIZEDRECT *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutputRect )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ NORMALIZEDRECT *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *SetBackgroundClr )( 
            IVMRMixerControl * This,
            /* [in] */ COLORREF ClrBkg);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackgroundClr )( 
            IVMRMixerControl * This,
            /* [in] */ COLORREF *lpClrBkg);
        
        HRESULT ( STDMETHODCALLTYPE *SetMixingPrefs )( 
            IVMRMixerControl * This,
            /* [in] */ DWORD dwMixerPrefs);
        
        HRESULT ( STDMETHODCALLTYPE *GetMixingPrefs )( 
            IVMRMixerControl * This,
            /* [out] */ DWORD *pdwMixerPrefs);
        
        END_INTERFACE
    } IVMRMixerControlVtbl;

    interface IVMRMixerControl
    {
        CONST_VTBL struct IVMRMixerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMixerControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMixerControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMixerControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMixerControl_SetAlpha(This,dwStreamID,Alpha)	\
    (This)->lpVtbl -> SetAlpha(This,dwStreamID,Alpha)

#define IVMRMixerControl_GetAlpha(This,dwStreamID,pAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,dwStreamID,pAlpha)

#define IVMRMixerControl_SetZOrder(This,dwStreamID,dwZ)	\
    (This)->lpVtbl -> SetZOrder(This,dwStreamID,dwZ)

#define IVMRMixerControl_GetZOrder(This,dwStreamID,pZ)	\
    (This)->lpVtbl -> GetZOrder(This,dwStreamID,pZ)

#define IVMRMixerControl_SetOutputRect(This,dwStreamID,pRect)	\
    (This)->lpVtbl -> SetOutputRect(This,dwStreamID,pRect)

#define IVMRMixerControl_GetOutputRect(This,dwStreamID,pRect)	\
    (This)->lpVtbl -> GetOutputRect(This,dwStreamID,pRect)

#define IVMRMixerControl_SetBackgroundClr(This,ClrBkg)	\
    (This)->lpVtbl -> SetBackgroundClr(This,ClrBkg)

#define IVMRMixerControl_GetBackgroundClr(This,lpClrBkg)	\
    (This)->lpVtbl -> GetBackgroundClr(This,lpClrBkg)

#define IVMRMixerControl_SetMixingPrefs(This,dwMixerPrefs)	\
    (This)->lpVtbl -> SetMixingPrefs(This,dwMixerPrefs)

#define IVMRMixerControl_GetMixingPrefs(This,pdwMixerPrefs)	\
    (This)->lpVtbl -> GetMixingPrefs(This,pdwMixerPrefs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMixerControl_SetAlpha_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ float Alpha);


void __RPC_STUB IVMRMixerControl_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_GetAlpha_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ float *pAlpha);


void __RPC_STUB IVMRMixerControl_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_SetZOrder_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ DWORD dwZ);


void __RPC_STUB IVMRMixerControl_SetZOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_GetZOrder_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ DWORD *pZ);


void __RPC_STUB IVMRMixerControl_GetZOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_SetOutputRect_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ const NORMALIZEDRECT *pRect);


void __RPC_STUB IVMRMixerControl_SetOutputRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_GetOutputRect_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ NORMALIZEDRECT *pRect);


void __RPC_STUB IVMRMixerControl_GetOutputRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_SetBackgroundClr_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ COLORREF ClrBkg);


void __RPC_STUB IVMRMixerControl_SetBackgroundClr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_GetBackgroundClr_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ COLORREF *lpClrBkg);


void __RPC_STUB IVMRMixerControl_GetBackgroundClr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_SetMixingPrefs_Proxy( 
    IVMRMixerControl * This,
    /* [in] */ DWORD dwMixerPrefs);


void __RPC_STUB IVMRMixerControl_SetMixingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl_GetMixingPrefs_Proxy( 
    IVMRMixerControl * This,
    /* [out] */ DWORD *pdwMixerPrefs);


void __RPC_STUB IVMRMixerControl_GetMixingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMixerControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0392 */
/* [local] */ 

typedef struct tagVMRGUID
    {
    GUID *pGUID;
    GUID GUID;
    } 	VMRGUID;

typedef struct tagVMRMONITORINFO
    {
    VMRGUID guid;
    RECT rcMonitor;
    HMONITOR hMon;
    DWORD dwFlags;
    wchar_t szDevice[ 32 ];
    wchar_t szDescription[ 256 ];
    LARGE_INTEGER liDriverVersion;
    DWORD dwVendorId;
    DWORD dwDeviceId;
    DWORD dwSubSysId;
    DWORD dwRevision;
    } 	VMRMONITORINFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0392_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0392_v0_0_s_ifspec;

#ifndef __IVMRMonitorConfig_INTERFACE_DEFINED__
#define __IVMRMonitorConfig_INTERFACE_DEFINED__

/* interface IVMRMonitorConfig */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRMonitorConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9cf0b1b6-fbaa-4b7f-88cf-cf1f130a0dce")
    IVMRMonitorConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMonitor( 
            /* [in] */ const VMRGUID *pGUID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMonitor( 
            /* [out] */ VMRGUID *pGUID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultMonitor( 
            /* [in] */ const VMRGUID *pGUID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultMonitor( 
            /* [out] */ VMRGUID *pGUID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailableMonitors( 
            /* [size_is][out] */ VMRMONITORINFO *pInfo,
            /* [in] */ DWORD dwMaxInfoArraySize,
            /* [out] */ DWORD *pdwNumDevices) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMonitorConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMonitorConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMonitorConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMonitorConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMonitor )( 
            IVMRMonitorConfig * This,
            /* [in] */ const VMRGUID *pGUID);
        
        HRESULT ( STDMETHODCALLTYPE *GetMonitor )( 
            IVMRMonitorConfig * This,
            /* [out] */ VMRGUID *pGUID);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultMonitor )( 
            IVMRMonitorConfig * This,
            /* [in] */ const VMRGUID *pGUID);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultMonitor )( 
            IVMRMonitorConfig * This,
            /* [out] */ VMRGUID *pGUID);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableMonitors )( 
            IVMRMonitorConfig * This,
            /* [size_is][out] */ VMRMONITORINFO *pInfo,
            /* [in] */ DWORD dwMaxInfoArraySize,
            /* [out] */ DWORD *pdwNumDevices);
        
        END_INTERFACE
    } IVMRMonitorConfigVtbl;

    interface IVMRMonitorConfig
    {
        CONST_VTBL struct IVMRMonitorConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMonitorConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMonitorConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMonitorConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMonitorConfig_SetMonitor(This,pGUID)	\
    (This)->lpVtbl -> SetMonitor(This,pGUID)

#define IVMRMonitorConfig_GetMonitor(This,pGUID)	\
    (This)->lpVtbl -> GetMonitor(This,pGUID)

#define IVMRMonitorConfig_SetDefaultMonitor(This,pGUID)	\
    (This)->lpVtbl -> SetDefaultMonitor(This,pGUID)

#define IVMRMonitorConfig_GetDefaultMonitor(This,pGUID)	\
    (This)->lpVtbl -> GetDefaultMonitor(This,pGUID)

#define IVMRMonitorConfig_GetAvailableMonitors(This,pInfo,dwMaxInfoArraySize,pdwNumDevices)	\
    (This)->lpVtbl -> GetAvailableMonitors(This,pInfo,dwMaxInfoArraySize,pdwNumDevices)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMonitorConfig_SetMonitor_Proxy( 
    IVMRMonitorConfig * This,
    /* [in] */ const VMRGUID *pGUID);


void __RPC_STUB IVMRMonitorConfig_SetMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig_GetMonitor_Proxy( 
    IVMRMonitorConfig * This,
    /* [out] */ VMRGUID *pGUID);


void __RPC_STUB IVMRMonitorConfig_GetMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig_SetDefaultMonitor_Proxy( 
    IVMRMonitorConfig * This,
    /* [in] */ const VMRGUID *pGUID);


void __RPC_STUB IVMRMonitorConfig_SetDefaultMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig_GetDefaultMonitor_Proxy( 
    IVMRMonitorConfig * This,
    /* [out] */ VMRGUID *pGUID);


void __RPC_STUB IVMRMonitorConfig_GetDefaultMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig_GetAvailableMonitors_Proxy( 
    IVMRMonitorConfig * This,
    /* [size_is][out] */ VMRMONITORINFO *pInfo,
    /* [in] */ DWORD dwMaxInfoArraySize,
    /* [out] */ DWORD *pdwNumDevices);


void __RPC_STUB IVMRMonitorConfig_GetAvailableMonitors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMonitorConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0393 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0393_0001
    {	RenderPrefs_RestrictToInitialMonitor	= 0,
	RenderPrefs_ForceOffscreen	= 0x1,
	RenderPrefs_ForceOverlays	= 0x2,
	RenderPrefs_AllowOverlays	= 0,
	RenderPrefs_AllowOffscreen	= 0,
	RenderPrefs_DoNotRenderColorKeyAndBorder	= 0x8,
	RenderPrefs_Reserved	= 0x10,
	RenderPrefs_PreferAGPMemWhenMixing	= 0x20,
	RenderPrefs_Mask	= 0x3f
    } 	VMRRenderPrefs;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0393_0002
    {	VMRMode_Windowed	= 0x1,
	VMRMode_Windowless	= 0x2,
	VMRMode_Renderless	= 0x4,
	VMRMode_Mask	= 0x7
    } 	VMRMode;


enum __MIDL___MIDL_itf_strmif_0393_0003
    {	MAX_NUMBER_OF_STREAMS	= 16
    } ;


extern RPC_IF_HANDLE __MIDL_itf_strmif_0393_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0393_v0_0_s_ifspec;

#ifndef __IVMRFilterConfig_INTERFACE_DEFINED__
#define __IVMRFilterConfig_INTERFACE_DEFINED__

/* interface IVMRFilterConfig */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRFilterConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9e5530c5-7034-48b4-bb46-0b8a6efc8e36")
    IVMRFilterConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetImageCompositor( 
            /* [in] */ IVMRImageCompositor *lpVMRImgCompositor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNumberOfStreams( 
            /* [in] */ DWORD dwMaxStreams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfStreams( 
            /* [out] */ DWORD *pdwMaxStreams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRenderingPrefs( 
            /* [in] */ DWORD dwRenderFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderingPrefs( 
            /* [out] */ DWORD *pdwRenderFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRenderingMode( 
            /* [in] */ DWORD Mode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderingMode( 
            /* [out] */ DWORD *pMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRFilterConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRFilterConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRFilterConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRFilterConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageCompositor )( 
            IVMRFilterConfig * This,
            /* [in] */ IVMRImageCompositor *lpVMRImgCompositor);
        
        HRESULT ( STDMETHODCALLTYPE *SetNumberOfStreams )( 
            IVMRFilterConfig * This,
            /* [in] */ DWORD dwMaxStreams);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfStreams )( 
            IVMRFilterConfig * This,
            /* [out] */ DWORD *pdwMaxStreams);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingPrefs )( 
            IVMRFilterConfig * This,
            /* [in] */ DWORD dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingPrefs )( 
            IVMRFilterConfig * This,
            /* [out] */ DWORD *pdwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingMode )( 
            IVMRFilterConfig * This,
            /* [in] */ DWORD Mode);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingMode )( 
            IVMRFilterConfig * This,
            /* [out] */ DWORD *pMode);
        
        END_INTERFACE
    } IVMRFilterConfigVtbl;

    interface IVMRFilterConfig
    {
        CONST_VTBL struct IVMRFilterConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRFilterConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRFilterConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRFilterConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRFilterConfig_SetImageCompositor(This,lpVMRImgCompositor)	\
    (This)->lpVtbl -> SetImageCompositor(This,lpVMRImgCompositor)

#define IVMRFilterConfig_SetNumberOfStreams(This,dwMaxStreams)	\
    (This)->lpVtbl -> SetNumberOfStreams(This,dwMaxStreams)

#define IVMRFilterConfig_GetNumberOfStreams(This,pdwMaxStreams)	\
    (This)->lpVtbl -> GetNumberOfStreams(This,pdwMaxStreams)

#define IVMRFilterConfig_SetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> SetRenderingPrefs(This,dwRenderFlags)

#define IVMRFilterConfig_GetRenderingPrefs(This,pdwRenderFlags)	\
    (This)->lpVtbl -> GetRenderingPrefs(This,pdwRenderFlags)

#define IVMRFilterConfig_SetRenderingMode(This,Mode)	\
    (This)->lpVtbl -> SetRenderingMode(This,Mode)

#define IVMRFilterConfig_GetRenderingMode(This,pMode)	\
    (This)->lpVtbl -> GetRenderingMode(This,pMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRFilterConfig_SetImageCompositor_Proxy( 
    IVMRFilterConfig * This,
    /* [in] */ IVMRImageCompositor *lpVMRImgCompositor);


void __RPC_STUB IVMRFilterConfig_SetImageCompositor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_SetNumberOfStreams_Proxy( 
    IVMRFilterConfig * This,
    /* [in] */ DWORD dwMaxStreams);


void __RPC_STUB IVMRFilterConfig_SetNumberOfStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_GetNumberOfStreams_Proxy( 
    IVMRFilterConfig * This,
    /* [out] */ DWORD *pdwMaxStreams);


void __RPC_STUB IVMRFilterConfig_GetNumberOfStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_SetRenderingPrefs_Proxy( 
    IVMRFilterConfig * This,
    /* [in] */ DWORD dwRenderFlags);


void __RPC_STUB IVMRFilterConfig_SetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_GetRenderingPrefs_Proxy( 
    IVMRFilterConfig * This,
    /* [out] */ DWORD *pdwRenderFlags);


void __RPC_STUB IVMRFilterConfig_GetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_SetRenderingMode_Proxy( 
    IVMRFilterConfig * This,
    /* [in] */ DWORD Mode);


void __RPC_STUB IVMRFilterConfig_SetRenderingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig_GetRenderingMode_Proxy( 
    IVMRFilterConfig * This,
    /* [out] */ DWORD *pMode);


void __RPC_STUB IVMRFilterConfig_GetRenderingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRFilterConfig_INTERFACE_DEFINED__ */


#ifndef __IVMRAspectRatioControl_INTERFACE_DEFINED__
#define __IVMRAspectRatioControl_INTERFACE_DEFINED__

/* interface IVMRAspectRatioControl */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRAspectRatioControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ede80b5c-bad6-4623-b537-65586c9f8dfd")
    IVMRAspectRatioControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAspectRatioMode( 
            /* [out] */ LPDWORD lpdwARMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAspectRatioMode( 
            /* [in] */ DWORD dwARMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRAspectRatioControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRAspectRatioControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRAspectRatioControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRAspectRatioControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAspectRatioMode )( 
            IVMRAspectRatioControl * This,
            /* [out] */ LPDWORD lpdwARMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetAspectRatioMode )( 
            IVMRAspectRatioControl * This,
            /* [in] */ DWORD dwARMode);
        
        END_INTERFACE
    } IVMRAspectRatioControlVtbl;

    interface IVMRAspectRatioControl
    {
        CONST_VTBL struct IVMRAspectRatioControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRAspectRatioControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRAspectRatioControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRAspectRatioControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRAspectRatioControl_GetAspectRatioMode(This,lpdwARMode)	\
    (This)->lpVtbl -> GetAspectRatioMode(This,lpdwARMode)

#define IVMRAspectRatioControl_SetAspectRatioMode(This,dwARMode)	\
    (This)->lpVtbl -> SetAspectRatioMode(This,dwARMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRAspectRatioControl_GetAspectRatioMode_Proxy( 
    IVMRAspectRatioControl * This,
    /* [out] */ LPDWORD lpdwARMode);


void __RPC_STUB IVMRAspectRatioControl_GetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRAspectRatioControl_SetAspectRatioMode_Proxy( 
    IVMRAspectRatioControl * This,
    /* [in] */ DWORD dwARMode);


void __RPC_STUB IVMRAspectRatioControl_SetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRAspectRatioControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0395 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0395_0001
    {	DeinterlacePref_NextBest	= 0x1,
	DeinterlacePref_BOB	= 0x2,
	DeinterlacePref_Weave	= 0x4,
	DeinterlacePref_Mask	= 0x7
    } 	VMRDeinterlacePrefs;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_strmif_0395_0002
    {	DeinterlaceTech_Unknown	= 0,
	DeinterlaceTech_BOBLineReplicate	= 0x1,
	DeinterlaceTech_BOBVerticalStretch	= 0x2,
	DeinterlaceTech_MedianFiltering	= 0x4,
	DeinterlaceTech_EdgeFiltering	= 0x10,
	DeinterlaceTech_FieldAdaptive	= 0x20,
	DeinterlaceTech_PixelAdaptive	= 0x40,
	DeinterlaceTech_MotionVectorSteered	= 0x80
    } 	VMRDeinterlaceTech;

typedef struct _VMRFrequency
    {
    DWORD dwNumerator;
    DWORD dwDenominator;
    } 	VMRFrequency;

typedef struct _VMRVideoDesc
    {
    DWORD dwSize;
    DWORD dwSampleWidth;
    DWORD dwSampleHeight;
    BOOL SingleFieldPerSample;
    DWORD dwFourCC;
    VMRFrequency InputSampleFreq;
    VMRFrequency OutputFrameFreq;
    } 	VMRVideoDesc;

typedef struct _VMRDeinterlaceCaps
    {
    DWORD dwSize;
    DWORD dwNumPreviousOutputFrames;
    DWORD dwNumForwardRefSamples;
    DWORD dwNumBackwardRefSamples;
    VMRDeinterlaceTech DeinterlaceTechnology;
    } 	VMRDeinterlaceCaps;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0395_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0395_v0_0_s_ifspec;

#ifndef __IVMRDeinterlaceControl_INTERFACE_DEFINED__
#define __IVMRDeinterlaceControl_INTERFACE_DEFINED__

/* interface IVMRDeinterlaceControl */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRDeinterlaceControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bb057577-0db8-4e6a-87a7-1a8c9a505a0f")
    IVMRDeinterlaceControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfDeinterlaceModes( 
            /* [in] */ VMRVideoDesc *lpVideoDescription,
            /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
            /* [out] */ LPGUID lpDeinterlaceModes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeinterlaceModeCaps( 
            /* [in] */ LPGUID lpDeinterlaceMode,
            /* [in] */ VMRVideoDesc *lpVideoDescription,
            /* [out][in] */ VMRDeinterlaceCaps *lpDeinterlaceCaps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeinterlaceMode( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDeinterlaceMode( 
            /* [in] */ DWORD dwStreamID,
            /* [in] */ LPGUID lpDeinterlaceMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeinterlacePrefs( 
            /* [out] */ LPDWORD lpdwDeinterlacePrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDeinterlacePrefs( 
            /* [in] */ DWORD dwDeinterlacePrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetActualDeinterlaceMode( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRDeinterlaceControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRDeinterlaceControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRDeinterlaceControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfDeinterlaceModes )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ VMRVideoDesc *lpVideoDescription,
            /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
            /* [out] */ LPGUID lpDeinterlaceModes);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlaceModeCaps )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ LPGUID lpDeinterlaceMode,
            /* [in] */ VMRVideoDesc *lpVideoDescription,
            /* [out][in] */ VMRDeinterlaceCaps *lpDeinterlaceCaps);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlaceMode )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetDeinterlaceMode )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ LPGUID lpDeinterlaceMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlacePrefs )( 
            IVMRDeinterlaceControl * This,
            /* [out] */ LPDWORD lpdwDeinterlacePrefs);
        
        HRESULT ( STDMETHODCALLTYPE *SetDeinterlacePrefs )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ DWORD dwDeinterlacePrefs);
        
        HRESULT ( STDMETHODCALLTYPE *GetActualDeinterlaceMode )( 
            IVMRDeinterlaceControl * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode);
        
        END_INTERFACE
    } IVMRDeinterlaceControlVtbl;

    interface IVMRDeinterlaceControl
    {
        CONST_VTBL struct IVMRDeinterlaceControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRDeinterlaceControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRDeinterlaceControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRDeinterlaceControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRDeinterlaceControl_GetNumberOfDeinterlaceModes(This,lpVideoDescription,lpdwNumDeinterlaceModes,lpDeinterlaceModes)	\
    (This)->lpVtbl -> GetNumberOfDeinterlaceModes(This,lpVideoDescription,lpdwNumDeinterlaceModes,lpDeinterlaceModes)

#define IVMRDeinterlaceControl_GetDeinterlaceModeCaps(This,lpDeinterlaceMode,lpVideoDescription,lpDeinterlaceCaps)	\
    (This)->lpVtbl -> GetDeinterlaceModeCaps(This,lpDeinterlaceMode,lpVideoDescription,lpDeinterlaceCaps)

#define IVMRDeinterlaceControl_GetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> GetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#define IVMRDeinterlaceControl_SetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> SetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#define IVMRDeinterlaceControl_GetDeinterlacePrefs(This,lpdwDeinterlacePrefs)	\
    (This)->lpVtbl -> GetDeinterlacePrefs(This,lpdwDeinterlacePrefs)

#define IVMRDeinterlaceControl_SetDeinterlacePrefs(This,dwDeinterlacePrefs)	\
    (This)->lpVtbl -> SetDeinterlacePrefs(This,dwDeinterlacePrefs)

#define IVMRDeinterlaceControl_GetActualDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> GetActualDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_GetNumberOfDeinterlaceModes_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ VMRVideoDesc *lpVideoDescription,
    /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
    /* [out] */ LPGUID lpDeinterlaceModes);


void __RPC_STUB IVMRDeinterlaceControl_GetNumberOfDeinterlaceModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_GetDeinterlaceModeCaps_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ LPGUID lpDeinterlaceMode,
    /* [in] */ VMRVideoDesc *lpVideoDescription,
    /* [out][in] */ VMRDeinterlaceCaps *lpDeinterlaceCaps);


void __RPC_STUB IVMRDeinterlaceControl_GetDeinterlaceModeCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_GetDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl_GetDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_SetDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl_SetDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_GetDeinterlacePrefs_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [out] */ LPDWORD lpdwDeinterlacePrefs);


void __RPC_STUB IVMRDeinterlaceControl_GetDeinterlacePrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_SetDeinterlacePrefs_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ DWORD dwDeinterlacePrefs);


void __RPC_STUB IVMRDeinterlaceControl_SetDeinterlacePrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl_GetActualDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl_GetActualDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRDeinterlaceControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0396 */
/* [local] */ 

typedef struct _VMRALPHABITMAP
    {
    DWORD dwFlags;
    HDC hdc;
    LPDIRECTDRAWSURFACE7 pDDS;
    RECT rSrc;
    NORMALIZEDRECT rDest;
    FLOAT fAlpha;
    COLORREF clrSrcKey;
    } 	VMRALPHABITMAP;

typedef struct _VMRALPHABITMAP *PVMRALPHABITMAP;

#define VMRBITMAP_DISABLE            0x00000001
#define VMRBITMAP_HDC                0x00000002
#define VMRBITMAP_ENTIREDDS          0x00000004
#define VMRBITMAP_SRCCOLORKEY        0x00000008
#define VMRBITMAP_SRCRECT            0x00000010


extern RPC_IF_HANDLE __MIDL_itf_strmif_0396_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0396_v0_0_s_ifspec;

#ifndef __IVMRMixerBitmap_INTERFACE_DEFINED__
#define __IVMRMixerBitmap_INTERFACE_DEFINED__

/* interface IVMRMixerBitmap */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRMixerBitmap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1E673275-0257-40aa-AF20-7C608D4A0428")
    IVMRMixerBitmap : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAlphaBitmap( 
            /* [in] */ const VMRALPHABITMAP *pBmpParms) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateAlphaBitmapParameters( 
            /* [in] */ PVMRALPHABITMAP pBmpParms) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlphaBitmapParameters( 
            /* [out] */ PVMRALPHABITMAP pBmpParms) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMixerBitmapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMixerBitmap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMixerBitmap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMixerBitmap * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlphaBitmap )( 
            IVMRMixerBitmap * This,
            /* [in] */ const VMRALPHABITMAP *pBmpParms);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateAlphaBitmapParameters )( 
            IVMRMixerBitmap * This,
            /* [in] */ PVMRALPHABITMAP pBmpParms);
        
        HRESULT ( STDMETHODCALLTYPE *GetAlphaBitmapParameters )( 
            IVMRMixerBitmap * This,
            /* [out] */ PVMRALPHABITMAP pBmpParms);
        
        END_INTERFACE
    } IVMRMixerBitmapVtbl;

    interface IVMRMixerBitmap
    {
        CONST_VTBL struct IVMRMixerBitmapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMixerBitmap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMixerBitmap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMixerBitmap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMixerBitmap_SetAlphaBitmap(This,pBmpParms)	\
    (This)->lpVtbl -> SetAlphaBitmap(This,pBmpParms)

#define IVMRMixerBitmap_UpdateAlphaBitmapParameters(This,pBmpParms)	\
    (This)->lpVtbl -> UpdateAlphaBitmapParameters(This,pBmpParms)

#define IVMRMixerBitmap_GetAlphaBitmapParameters(This,pBmpParms)	\
    (This)->lpVtbl -> GetAlphaBitmapParameters(This,pBmpParms)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMixerBitmap_SetAlphaBitmap_Proxy( 
    IVMRMixerBitmap * This,
    /* [in] */ const VMRALPHABITMAP *pBmpParms);


void __RPC_STUB IVMRMixerBitmap_SetAlphaBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerBitmap_UpdateAlphaBitmapParameters_Proxy( 
    IVMRMixerBitmap * This,
    /* [in] */ PVMRALPHABITMAP pBmpParms);


void __RPC_STUB IVMRMixerBitmap_UpdateAlphaBitmapParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerBitmap_GetAlphaBitmapParameters_Proxy( 
    IVMRMixerBitmap * This,
    /* [out] */ PVMRALPHABITMAP pBmpParms);


void __RPC_STUB IVMRMixerBitmap_GetAlphaBitmapParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMixerBitmap_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0397 */
/* [local] */ 

typedef struct _VMRVIDEOSTREAMINFO
    {
    LPDIRECTDRAWSURFACE7 pddsVideoSurface;
    DWORD dwWidth;
    DWORD dwHeight;
    DWORD dwStrmID;
    FLOAT fAlpha;
    DDCOLORKEY ddClrKey;
    NORMALIZEDRECT rNormal;
    } 	VMRVIDEOSTREAMINFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0397_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0397_v0_0_s_ifspec;

#ifndef __IVMRImageCompositor_INTERFACE_DEFINED__
#define __IVMRImageCompositor_INTERFACE_DEFINED__

/* interface IVMRImageCompositor */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImageCompositor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7a4fb5af-479f-4074-bb40-ce6722e43c82")
    IVMRImageCompositor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitCompositionTarget( 
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TermCompositionTarget( 
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStreamMediaType( 
            /* [in] */ DWORD dwStrmID,
            /* [in] */ AM_MEDIA_TYPE *pmt,
            /* [in] */ BOOL fTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompositeImage( 
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget,
            /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd,
            /* [in] */ DWORD dwClrBkGnd,
            /* [in] */ VMRVIDEOSTREAMINFO *pVideoStreamInfo,
            /* [in] */ UINT cStreams) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImageCompositorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImageCompositor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImageCompositor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImageCompositor * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitCompositionTarget )( 
            IVMRImageCompositor * This,
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget);
        
        HRESULT ( STDMETHODCALLTYPE *TermCompositionTarget )( 
            IVMRImageCompositor * This,
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget);
        
        HRESULT ( STDMETHODCALLTYPE *SetStreamMediaType )( 
            IVMRImageCompositor * This,
            /* [in] */ DWORD dwStrmID,
            /* [in] */ AM_MEDIA_TYPE *pmt,
            /* [in] */ BOOL fTexture);
        
        HRESULT ( STDMETHODCALLTYPE *CompositeImage )( 
            IVMRImageCompositor * This,
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget,
            /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd,
            /* [in] */ DWORD dwClrBkGnd,
            /* [in] */ VMRVIDEOSTREAMINFO *pVideoStreamInfo,
            /* [in] */ UINT cStreams);
        
        END_INTERFACE
    } IVMRImageCompositorVtbl;

    interface IVMRImageCompositor
    {
        CONST_VTBL struct IVMRImageCompositorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImageCompositor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImageCompositor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImageCompositor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImageCompositor_InitCompositionTarget(This,pD3DDevice,pddsRenderTarget)	\
    (This)->lpVtbl -> InitCompositionTarget(This,pD3DDevice,pddsRenderTarget)

#define IVMRImageCompositor_TermCompositionTarget(This,pD3DDevice,pddsRenderTarget)	\
    (This)->lpVtbl -> TermCompositionTarget(This,pD3DDevice,pddsRenderTarget)

#define IVMRImageCompositor_SetStreamMediaType(This,dwStrmID,pmt,fTexture)	\
    (This)->lpVtbl -> SetStreamMediaType(This,dwStrmID,pmt,fTexture)

#define IVMRImageCompositor_CompositeImage(This,pD3DDevice,pddsRenderTarget,pmtRenderTarget,rtStart,rtEnd,dwClrBkGnd,pVideoStreamInfo,cStreams)	\
    (This)->lpVtbl -> CompositeImage(This,pD3DDevice,pddsRenderTarget,pmtRenderTarget,rtStart,rtEnd,dwClrBkGnd,pVideoStreamInfo,cStreams)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImageCompositor_InitCompositionTarget_Proxy( 
    IVMRImageCompositor * This,
    /* [in] */ IUnknown *pD3DDevice,
    /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget);


void __RPC_STUB IVMRImageCompositor_InitCompositionTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor_TermCompositionTarget_Proxy( 
    IVMRImageCompositor * This,
    /* [in] */ IUnknown *pD3DDevice,
    /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget);


void __RPC_STUB IVMRImageCompositor_TermCompositionTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor_SetStreamMediaType_Proxy( 
    IVMRImageCompositor * This,
    /* [in] */ DWORD dwStrmID,
    /* [in] */ AM_MEDIA_TYPE *pmt,
    /* [in] */ BOOL fTexture);


void __RPC_STUB IVMRImageCompositor_SetStreamMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor_CompositeImage_Proxy( 
    IVMRImageCompositor * This,
    /* [in] */ IUnknown *pD3DDevice,
    /* [in] */ LPDIRECTDRAWSURFACE7 pddsRenderTarget,
    /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
    /* [in] */ REFERENCE_TIME rtStart,
    /* [in] */ REFERENCE_TIME rtEnd,
    /* [in] */ DWORD dwClrBkGnd,
    /* [in] */ VMRVIDEOSTREAMINFO *pVideoStreamInfo,
    /* [in] */ UINT cStreams);


void __RPC_STUB IVMRImageCompositor_CompositeImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImageCompositor_INTERFACE_DEFINED__ */


#ifndef __IVMRVideoStreamControl_INTERFACE_DEFINED__
#define __IVMRVideoStreamControl_INTERFACE_DEFINED__

/* interface IVMRVideoStreamControl */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRVideoStreamControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("058d1f11-2a54-4bef-bd54-df706626b727")
    IVMRVideoStreamControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetColorKey( 
            /* [in] */ LPDDCOLORKEY lpClrKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColorKey( 
            /* [out] */ LPDDCOLORKEY lpClrKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStreamActiveState( 
            /* [in] */ BOOL fActive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamActiveState( 
            /* [out] */ BOOL *lpfActive) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRVideoStreamControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRVideoStreamControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRVideoStreamControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRVideoStreamControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetColorKey )( 
            IVMRVideoStreamControl * This,
            /* [in] */ LPDDCOLORKEY lpClrKey);
        
        HRESULT ( STDMETHODCALLTYPE *GetColorKey )( 
            IVMRVideoStreamControl * This,
            /* [out] */ LPDDCOLORKEY lpClrKey);
        
        HRESULT ( STDMETHODCALLTYPE *SetStreamActiveState )( 
            IVMRVideoStreamControl * This,
            /* [in] */ BOOL fActive);
        
        HRESULT ( STDMETHODCALLTYPE *GetStreamActiveState )( 
            IVMRVideoStreamControl * This,
            /* [out] */ BOOL *lpfActive);
        
        END_INTERFACE
    } IVMRVideoStreamControlVtbl;

    interface IVMRVideoStreamControl
    {
        CONST_VTBL struct IVMRVideoStreamControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRVideoStreamControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRVideoStreamControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRVideoStreamControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRVideoStreamControl_SetColorKey(This,lpClrKey)	\
    (This)->lpVtbl -> SetColorKey(This,lpClrKey)

#define IVMRVideoStreamControl_GetColorKey(This,lpClrKey)	\
    (This)->lpVtbl -> GetColorKey(This,lpClrKey)

#define IVMRVideoStreamControl_SetStreamActiveState(This,fActive)	\
    (This)->lpVtbl -> SetStreamActiveState(This,fActive)

#define IVMRVideoStreamControl_GetStreamActiveState(This,lpfActive)	\
    (This)->lpVtbl -> GetStreamActiveState(This,lpfActive)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl_SetColorKey_Proxy( 
    IVMRVideoStreamControl * This,
    /* [in] */ LPDDCOLORKEY lpClrKey);


void __RPC_STUB IVMRVideoStreamControl_SetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl_GetColorKey_Proxy( 
    IVMRVideoStreamControl * This,
    /* [out] */ LPDDCOLORKEY lpClrKey);


void __RPC_STUB IVMRVideoStreamControl_GetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl_SetStreamActiveState_Proxy( 
    IVMRVideoStreamControl * This,
    /* [in] */ BOOL fActive);


void __RPC_STUB IVMRVideoStreamControl_SetStreamActiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl_GetStreamActiveState_Proxy( 
    IVMRVideoStreamControl * This,
    /* [out] */ BOOL *lpfActive);


void __RPC_STUB IVMRVideoStreamControl_GetStreamActiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRVideoStreamControl_INTERFACE_DEFINED__ */


#ifndef __IVMRSurface_INTERFACE_DEFINED__
#define __IVMRSurface_INTERFACE_DEFINED__

/* interface IVMRSurface */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a9849bbe-9ec8-4263-b764-62730f0d15d0")
    IVMRSurface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsSurfaceLocked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LockSurface( 
            /* [out] */ BYTE **lpSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnlockSurface( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSurfaceLocked )( 
            IVMRSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *LockSurface )( 
            IVMRSurface * This,
            /* [out] */ BYTE **lpSurface);
        
        HRESULT ( STDMETHODCALLTYPE *UnlockSurface )( 
            IVMRSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            IVMRSurface * This,
            /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface);
        
        END_INTERFACE
    } IVMRSurfaceVtbl;

    interface IVMRSurface
    {
        CONST_VTBL struct IVMRSurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurface_IsSurfaceLocked(This)	\
    (This)->lpVtbl -> IsSurfaceLocked(This)

#define IVMRSurface_LockSurface(This,lpSurface)	\
    (This)->lpVtbl -> LockSurface(This,lpSurface)

#define IVMRSurface_UnlockSurface(This)	\
    (This)->lpVtbl -> UnlockSurface(This)

#define IVMRSurface_GetSurface(This,lplpSurface)	\
    (This)->lpVtbl -> GetSurface(This,lplpSurface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurface_IsSurfaceLocked_Proxy( 
    IVMRSurface * This);


void __RPC_STUB IVMRSurface_IsSurfaceLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface_LockSurface_Proxy( 
    IVMRSurface * This,
    /* [out] */ BYTE **lpSurface);


void __RPC_STUB IVMRSurface_LockSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface_UnlockSurface_Proxy( 
    IVMRSurface * This);


void __RPC_STUB IVMRSurface_UnlockSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface_GetSurface_Proxy( 
    IVMRSurface * This,
    /* [out] */ LPDIRECTDRAWSURFACE7 *lplpSurface);


void __RPC_STUB IVMRSurface_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurface_INTERFACE_DEFINED__ */


#ifndef __IVMRImagePresenterConfig_INTERFACE_DEFINED__
#define __IVMRImagePresenterConfig_INTERFACE_DEFINED__

/* interface IVMRImagePresenterConfig */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImagePresenterConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9f3a1c85-8555-49ba-935f-be5b5b29d178")
    IVMRImagePresenterConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRenderingPrefs( 
            /* [in] */ DWORD dwRenderFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderingPrefs( 
            /* [out] */ DWORD *dwRenderFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImagePresenterConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImagePresenterConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImagePresenterConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImagePresenterConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingPrefs )( 
            IVMRImagePresenterConfig * This,
            /* [in] */ DWORD dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingPrefs )( 
            IVMRImagePresenterConfig * This,
            /* [out] */ DWORD *dwRenderFlags);
        
        END_INTERFACE
    } IVMRImagePresenterConfigVtbl;

    interface IVMRImagePresenterConfig
    {
        CONST_VTBL struct IVMRImagePresenterConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImagePresenterConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImagePresenterConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImagePresenterConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImagePresenterConfig_SetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> SetRenderingPrefs(This,dwRenderFlags)

#define IVMRImagePresenterConfig_GetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> GetRenderingPrefs(This,dwRenderFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImagePresenterConfig_SetRenderingPrefs_Proxy( 
    IVMRImagePresenterConfig * This,
    /* [in] */ DWORD dwRenderFlags);


void __RPC_STUB IVMRImagePresenterConfig_SetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenterConfig_GetRenderingPrefs_Proxy( 
    IVMRImagePresenterConfig * This,
    /* [out] */ DWORD *dwRenderFlags);


void __RPC_STUB IVMRImagePresenterConfig_GetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImagePresenterConfig_INTERFACE_DEFINED__ */


#ifndef __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__
#define __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__

/* interface IVMRImagePresenterExclModeConfig */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImagePresenterExclModeConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e6f7ce40-4673-44f1-8f77-5499d68cb4ea")
    IVMRImagePresenterExclModeConfig : public IVMRImagePresenterConfig
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetXlcModeDDObjAndPrimarySurface( 
            /* [in] */ LPDIRECTDRAW7 lpDDObj,
            /* [in] */ LPDIRECTDRAWSURFACE7 lpPrimarySurf) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetXlcModeDDObjAndPrimarySurface( 
            /* [out] */ LPDIRECTDRAW7 *lpDDObj,
            /* [out] */ LPDIRECTDRAWSURFACE7 *lpPrimarySurf) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImagePresenterExclModeConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImagePresenterExclModeConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImagePresenterExclModeConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImagePresenterExclModeConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingPrefs )( 
            IVMRImagePresenterExclModeConfig * This,
            /* [in] */ DWORD dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingPrefs )( 
            IVMRImagePresenterExclModeConfig * This,
            /* [out] */ DWORD *dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetXlcModeDDObjAndPrimarySurface )( 
            IVMRImagePresenterExclModeConfig * This,
            /* [in] */ LPDIRECTDRAW7 lpDDObj,
            /* [in] */ LPDIRECTDRAWSURFACE7 lpPrimarySurf);
        
        HRESULT ( STDMETHODCALLTYPE *GetXlcModeDDObjAndPrimarySurface )( 
            IVMRImagePresenterExclModeConfig * This,
            /* [out] */ LPDIRECTDRAW7 *lpDDObj,
            /* [out] */ LPDIRECTDRAWSURFACE7 *lpPrimarySurf);
        
        END_INTERFACE
    } IVMRImagePresenterExclModeConfigVtbl;

    interface IVMRImagePresenterExclModeConfig
    {
        CONST_VTBL struct IVMRImagePresenterExclModeConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImagePresenterExclModeConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImagePresenterExclModeConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImagePresenterExclModeConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImagePresenterExclModeConfig_SetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> SetRenderingPrefs(This,dwRenderFlags)

#define IVMRImagePresenterExclModeConfig_GetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> GetRenderingPrefs(This,dwRenderFlags)


#define IVMRImagePresenterExclModeConfig_SetXlcModeDDObjAndPrimarySurface(This,lpDDObj,lpPrimarySurf)	\
    (This)->lpVtbl -> SetXlcModeDDObjAndPrimarySurface(This,lpDDObj,lpPrimarySurf)

#define IVMRImagePresenterExclModeConfig_GetXlcModeDDObjAndPrimarySurface(This,lpDDObj,lpPrimarySurf)	\
    (This)->lpVtbl -> GetXlcModeDDObjAndPrimarySurface(This,lpDDObj,lpPrimarySurf)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImagePresenterExclModeConfig_SetXlcModeDDObjAndPrimarySurface_Proxy( 
    IVMRImagePresenterExclModeConfig * This,
    /* [in] */ LPDIRECTDRAW7 lpDDObj,
    /* [in] */ LPDIRECTDRAWSURFACE7 lpPrimarySurf);


void __RPC_STUB IVMRImagePresenterExclModeConfig_SetXlcModeDDObjAndPrimarySurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenterExclModeConfig_GetXlcModeDDObjAndPrimarySurface_Proxy( 
    IVMRImagePresenterExclModeConfig * This,
    /* [out] */ LPDIRECTDRAW7 *lpDDObj,
    /* [out] */ LPDIRECTDRAWSURFACE7 *lpPrimarySurf);


void __RPC_STUB IVMRImagePresenterExclModeConfig_GetXlcModeDDObjAndPrimarySurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImagePresenterExclModeConfig_INTERFACE_DEFINED__ */


#ifndef __IVPManager_INTERFACE_DEFINED__
#define __IVPManager_INTERFACE_DEFINED__

/* interface IVPManager */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVPManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aac18c18-e186-46d2-825d-a1f8dc8e395a")
    IVPManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetVideoPortIndex( 
            /* [in] */ DWORD dwVideoPortIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoPortIndex( 
            /* [out] */ DWORD *pdwVideoPortIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVPManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVPManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVPManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVPManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetVideoPortIndex )( 
            IVPManager * This,
            /* [in] */ DWORD dwVideoPortIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoPortIndex )( 
            IVPManager * This,
            /* [out] */ DWORD *pdwVideoPortIndex);
        
        END_INTERFACE
    } IVPManagerVtbl;

    interface IVPManager
    {
        CONST_VTBL struct IVPManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVPManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVPManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVPManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVPManager_SetVideoPortIndex(This,dwVideoPortIndex)	\
    (This)->lpVtbl -> SetVideoPortIndex(This,dwVideoPortIndex)

#define IVPManager_GetVideoPortIndex(This,pdwVideoPortIndex)	\
    (This)->lpVtbl -> GetVideoPortIndex(This,pdwVideoPortIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVPManager_SetVideoPortIndex_Proxy( 
    IVPManager * This,
    /* [in] */ DWORD dwVideoPortIndex);


void __RPC_STUB IVPManager_SetVideoPortIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVPManager_GetVideoPortIndex_Proxy( 
    IVPManager * This,
    /* [out] */ DWORD *pdwVideoPortIndex);


void __RPC_STUB IVPManager_GetVideoPortIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVPManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_strmif_0403 */
/* [local] */ 

// Restore the previous setting for C4201 compiler warning
#pragma warning(pop)


extern RPC_IF_HANDLE __MIDL_itf_strmif_0403_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0403_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* [local] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_FindInterface_Proxy( 
    ICaptureGraphBuilder * This,
    /* [unique][in] */ const GUID *pCategory,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ void **ppint);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder_FindInterface_Stub( 
    ICaptureGraphBuilder * This,
    /* [unique][in] */ const GUID *pCategory,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppint);

/* [local] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_FindInterface_Proxy( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ void **ppint);


/* [call_as] */ HRESULT STDMETHODCALLTYPE ICaptureGraphBuilder2_FindInterface_Stub( 
    ICaptureGraphBuilder2 * This,
    /* [in] */ const GUID *pCategory,
    /* [in] */ const GUID *pType,
    /* [in] */ IBaseFilter *pf,
    /* [in] */ REFIID riid,
    /* [out] */ IUnknown **ppint);

/* [local] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_Set_Proxy( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ LPVOID pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][in] */ LPVOID pPropData,
    /* [in] */ DWORD cbPropData);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_Set_Stub( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ byte *pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][in] */ byte *pPropData,
    /* [in] */ DWORD cbPropData);

/* [local] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_Get_Proxy( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ LPVOID pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][out] */ LPVOID pPropData,
    /* [in] */ DWORD cbPropData,
    /* [out] */ DWORD *pcbReturned);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IKsPropertySet_Get_Stub( 
    IKsPropertySet * This,
    /* [in] */ REFGUID guidPropSet,
    /* [in] */ DWORD dwPropID,
    /* [size_is][in] */ byte *pInstanceData,
    /* [in] */ DWORD cbInstanceData,
    /* [size_is][out] */ byte *pPropData,
    /* [in] */ DWORD cbPropData,
    /* [out] */ DWORD *pcbReturned);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


