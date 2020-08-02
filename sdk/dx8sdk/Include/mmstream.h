
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for mmstream.idl:
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

#ifndef __mmstream_h__
#define __mmstream_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMultiMediaStream_FWD_DEFINED__
#define __IMultiMediaStream_FWD_DEFINED__
typedef interface IMultiMediaStream IMultiMediaStream;
#endif 	/* __IMultiMediaStream_FWD_DEFINED__ */


#ifndef __IMediaStream_FWD_DEFINED__
#define __IMediaStream_FWD_DEFINED__
typedef interface IMediaStream IMediaStream;
#endif 	/* __IMediaStream_FWD_DEFINED__ */


#ifndef __IStreamSample_FWD_DEFINED__
#define __IStreamSample_FWD_DEFINED__
typedef interface IStreamSample IStreamSample;
#endif 	/* __IStreamSample_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mmstream_0000 */
/* [local] */ 

#define MS_ERROR_CODE(x) MAKE_HRESULT(1, FACILITY_ITF, (x) + 0x400)
#define MS_SUCCESS_CODE(x) MAKE_HRESULT(0, FACILITY_ITF, x)
#define MS_S_PENDING                  MS_SUCCESS_CODE(1)
#define MS_S_NOUPDATE                 MS_SUCCESS_CODE(2)
#define MS_S_ENDOFSTREAM              MS_SUCCESS_CODE(3)
#define MS_E_SAMPLEALLOC              MS_ERROR_CODE(1)
#define MS_E_PURPOSEID                MS_ERROR_CODE(2)
#define MS_E_NOSTREAM                 MS_ERROR_CODE(3)
#define MS_E_NOSEEKING                MS_ERROR_CODE(4)
#define MS_E_INCOMPATIBLE             MS_ERROR_CODE(5)
#define MS_E_BUSY                     MS_ERROR_CODE(6)
#define MS_E_NOTINIT                  MS_ERROR_CODE(7)
#define MS_E_SOURCEALREADYDEFINED     MS_ERROR_CODE(8)
#define MS_E_INVALIDSTREAMTYPE        MS_ERROR_CODE(9)
#define MS_E_NOTRUNNING               MS_ERROR_CODE(10)
// {A35FF56A-9FDA-11d0-8FDF-00C04FD9189D}
DEFINE_GUID(MSPID_PrimaryVideo, 
0xa35ff56a, 0x9fda, 0x11d0, 0x8f, 0xdf, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
// {A35FF56B-9FDA-11d0-8FDF-00C04FD9189D}
DEFINE_GUID(MSPID_PrimaryAudio,
0xa35ff56b, 0x9fda, 0x11d0, 0x8f, 0xdf, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
#if(_WIN32_WINNT < 0x0400)
typedef void ( __stdcall *PAPCFUNC )( 
    DWORD_PTR dwParam);

#endif
typedef LONGLONG STREAM_TIME;

typedef GUID MSPID;

typedef REFGUID REFMSPID;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_mmstream_0000_0001
    {	STREAMTYPE_READ	= 0,
	STREAMTYPE_WRITE	= 1,
	STREAMTYPE_TRANSFORM	= 2
    } 	STREAM_TYPE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_mmstream_0000_0002
    {	STREAMSTATE_STOP	= 0,
	STREAMSTATE_RUN	= 1
    } 	STREAM_STATE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_mmstream_0000_0003
    {	COMPSTAT_NOUPDATEOK	= 0x1,
	COMPSTAT_WAIT	= 0x2,
	COMPSTAT_ABORT	= 0x4
    } 	COMPLETION_STATUS_FLAGS;


enum __MIDL___MIDL_itf_mmstream_0000_0004
    {	MMSSF_HASCLOCK	= 0x1,
	MMSSF_SUPPORTSEEK	= 0x2,
	MMSSF_ASYNCHRONOUS	= 0x4
    } ;

enum __MIDL___MIDL_itf_mmstream_0000_0005
    {	SSUPDATE_ASYNC	= 0x1,
	SSUPDATE_CONTINUOUS	= 0x2
    } ;





extern RPC_IF_HANDLE __MIDL_itf_mmstream_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mmstream_0000_v0_0_s_ifspec;

#ifndef __IMultiMediaStream_INTERFACE_DEFINED__
#define __IMultiMediaStream_INTERFACE_DEFINED__

/* interface IMultiMediaStream */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IMultiMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B502D1BC-9A57-11d0-8FDE-00C04FD9189D")
    IMultiMediaStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInformation( 
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ STREAM_TYPE *pStreamType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaStream( 
            /* [in] */ REFMSPID idPurpose,
            /* [out] */ IMediaStream **ppMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMediaStreams( 
            /* [in] */ long Index,
            /* [out] */ IMediaStream **ppMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ STREAM_STATE *pCurrentState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetState( 
            /* [in] */ STREAM_STATE NewState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ STREAM_TIME *pCurrentTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDuration( 
            /* [out] */ STREAM_TIME *pDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ STREAM_TIME SeekTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEndOfStreamEventHandle( 
            /* [out] */ HANDLE *phEOS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiMediaStream * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiMediaStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiMediaStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInformation )( 
            IMultiMediaStream * This,
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ STREAM_TYPE *pStreamType);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaStream )( 
            IMultiMediaStream * This,
            /* [in] */ REFMSPID idPurpose,
            /* [out] */ IMediaStream **ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *EnumMediaStreams )( 
            IMultiMediaStream * This,
            /* [in] */ long Index,
            /* [out] */ IMediaStream **ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IMultiMediaStream * This,
            /* [out] */ STREAM_STATE *pCurrentState);
        
        HRESULT ( STDMETHODCALLTYPE *SetState )( 
            IMultiMediaStream * This,
            /* [in] */ STREAM_STATE NewState);
        
        HRESULT ( STDMETHODCALLTYPE *GetTime )( 
            IMultiMediaStream * This,
            /* [out] */ STREAM_TIME *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetDuration )( 
            IMultiMediaStream * This,
            /* [out] */ STREAM_TIME *pDuration);
        
        HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IMultiMediaStream * This,
            /* [in] */ STREAM_TIME SeekTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetEndOfStreamEventHandle )( 
            IMultiMediaStream * This,
            /* [out] */ HANDLE *phEOS);
        
        END_INTERFACE
    } IMultiMediaStreamVtbl;

    interface IMultiMediaStream
    {
        CONST_VTBL struct IMultiMediaStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultiMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultiMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultiMediaStream_GetInformation(This,pdwFlags,pStreamType)	\
    (This)->lpVtbl -> GetInformation(This,pdwFlags,pStreamType)

#define IMultiMediaStream_GetMediaStream(This,idPurpose,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,idPurpose,ppMediaStream)

#define IMultiMediaStream_EnumMediaStreams(This,Index,ppMediaStream)	\
    (This)->lpVtbl -> EnumMediaStreams(This,Index,ppMediaStream)

#define IMultiMediaStream_GetState(This,pCurrentState)	\
    (This)->lpVtbl -> GetState(This,pCurrentState)

#define IMultiMediaStream_SetState(This,NewState)	\
    (This)->lpVtbl -> SetState(This,NewState)

#define IMultiMediaStream_GetTime(This,pCurrentTime)	\
    (This)->lpVtbl -> GetTime(This,pCurrentTime)

#define IMultiMediaStream_GetDuration(This,pDuration)	\
    (This)->lpVtbl -> GetDuration(This,pDuration)

#define IMultiMediaStream_Seek(This,SeekTime)	\
    (This)->lpVtbl -> Seek(This,SeekTime)

#define IMultiMediaStream_GetEndOfStreamEventHandle(This,phEOS)	\
    (This)->lpVtbl -> GetEndOfStreamEventHandle(This,phEOS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetInformation_Proxy( 
    IMultiMediaStream * This,
    /* [out] */ DWORD *pdwFlags,
    /* [out] */ STREAM_TYPE *pStreamType);


void __RPC_STUB IMultiMediaStream_GetInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetMediaStream_Proxy( 
    IMultiMediaStream * This,
    /* [in] */ REFMSPID idPurpose,
    /* [out] */ IMediaStream **ppMediaStream);


void __RPC_STUB IMultiMediaStream_GetMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_EnumMediaStreams_Proxy( 
    IMultiMediaStream * This,
    /* [in] */ long Index,
    /* [out] */ IMediaStream **ppMediaStream);


void __RPC_STUB IMultiMediaStream_EnumMediaStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetState_Proxy( 
    IMultiMediaStream * This,
    /* [out] */ STREAM_STATE *pCurrentState);


void __RPC_STUB IMultiMediaStream_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_SetState_Proxy( 
    IMultiMediaStream * This,
    /* [in] */ STREAM_STATE NewState);


void __RPC_STUB IMultiMediaStream_SetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetTime_Proxy( 
    IMultiMediaStream * This,
    /* [out] */ STREAM_TIME *pCurrentTime);


void __RPC_STUB IMultiMediaStream_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetDuration_Proxy( 
    IMultiMediaStream * This,
    /* [out] */ STREAM_TIME *pDuration);


void __RPC_STUB IMultiMediaStream_GetDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_Seek_Proxy( 
    IMultiMediaStream * This,
    /* [in] */ STREAM_TIME SeekTime);


void __RPC_STUB IMultiMediaStream_Seek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiMediaStream_GetEndOfStreamEventHandle_Proxy( 
    IMultiMediaStream * This,
    /* [out] */ HANDLE *phEOS);


void __RPC_STUB IMultiMediaStream_GetEndOfStreamEventHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultiMediaStream_INTERFACE_DEFINED__ */


#ifndef __IMediaStream_INTERFACE_DEFINED__
#define __IMediaStream_INTERFACE_DEFINED__

/* interface IMediaStream */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B502D1BD-9A57-11d0-8FDE-00C04FD9189D")
    IMediaStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMultiMediaStream( 
            /* [out] */ IMultiMediaStream **ppMultiMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInformation( 
            /* [out] */ MSPID *pPurposeId,
            /* [out] */ STREAM_TYPE *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSameFormat( 
            /* [in] */ IMediaStream *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocateSample( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSharedSample( 
            /* [in] */ IStreamSample *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppNewSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendEndOfStream( 
            DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaStream * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMultiMediaStream )( 
            IMediaStream * This,
            /* [out] */ IMultiMediaStream **ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetInformation )( 
            IMediaStream * This,
            /* [out] */ MSPID *pPurposeId,
            /* [out] */ STREAM_TYPE *pType);
        
        HRESULT ( STDMETHODCALLTYPE *SetSameFormat )( 
            IMediaStream * This,
            /* [in] */ IMediaStream *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *AllocateSample )( 
            IMediaStream * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppSample);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSharedSample )( 
            IMediaStream * This,
            /* [in] */ IStreamSample *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE *SendEndOfStream )( 
            IMediaStream * This,
            DWORD dwFlags);
        
        END_INTERFACE
    } IMediaStreamVtbl;

    interface IMediaStream
    {
        CONST_VTBL struct IMediaStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaStream_GetMultiMediaStream_Proxy( 
    IMediaStream * This,
    /* [out] */ IMultiMediaStream **ppMultiMediaStream);


void __RPC_STUB IMediaStream_GetMultiMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStream_GetInformation_Proxy( 
    IMediaStream * This,
    /* [out] */ MSPID *pPurposeId,
    /* [out] */ STREAM_TYPE *pType);


void __RPC_STUB IMediaStream_GetInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStream_SetSameFormat_Proxy( 
    IMediaStream * This,
    /* [in] */ IMediaStream *pStreamThatHasDesiredFormat,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMediaStream_SetSameFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStream_AllocateSample_Proxy( 
    IMediaStream * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IStreamSample **ppSample);


void __RPC_STUB IMediaStream_AllocateSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStream_CreateSharedSample_Proxy( 
    IMediaStream * This,
    /* [in] */ IStreamSample *pExistingSample,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IStreamSample **ppNewSample);


void __RPC_STUB IMediaStream_CreateSharedSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStream_SendEndOfStream_Proxy( 
    IMediaStream * This,
    DWORD dwFlags);


void __RPC_STUB IMediaStream_SendEndOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaStream_INTERFACE_DEFINED__ */


#ifndef __IStreamSample_INTERFACE_DEFINED__
#define __IStreamSample_INTERFACE_DEFINED__

/* interface IStreamSample */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IStreamSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B502D1BE-9A57-11d0-8FDE-00C04FD9189D")
    IStreamSample : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMediaStream( 
            /* [in] */ IMediaStream **ppMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSampleTimes( 
            /* [out] */ STREAM_TIME *pStartTime,
            /* [out] */ STREAM_TIME *pEndTime,
            /* [out] */ STREAM_TIME *pCurrentTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSampleTimes( 
            /* [in] */ const STREAM_TIME *pStartTime,
            /* [in] */ const STREAM_TIME *pEndTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ HANDLE hEvent,
            /* [in] */ PAPCFUNC pfnAPC,
            /* [in] */ DWORD_PTR dwAPCData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompletionStatus( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD dwMilliseconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStreamSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStreamSample * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStreamSample * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStreamSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaStream )( 
            IStreamSample * This,
            /* [in] */ IMediaStream **ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetSampleTimes )( 
            IStreamSample * This,
            /* [out] */ STREAM_TIME *pStartTime,
            /* [out] */ STREAM_TIME *pEndTime,
            /* [out] */ STREAM_TIME *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE *SetSampleTimes )( 
            IStreamSample * This,
            /* [in] */ const STREAM_TIME *pStartTime,
            /* [in] */ const STREAM_TIME *pEndTime);
        
        HRESULT ( STDMETHODCALLTYPE *Update )( 
            IStreamSample * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HANDLE hEvent,
            /* [in] */ PAPCFUNC pfnAPC,
            /* [in] */ DWORD_PTR dwAPCData);
        
        HRESULT ( STDMETHODCALLTYPE *CompletionStatus )( 
            IStreamSample * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD dwMilliseconds);
        
        END_INTERFACE
    } IStreamSampleVtbl;

    interface IStreamSample
    {
        CONST_VTBL struct IStreamSampleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStreamSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStreamSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStreamSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStreamSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IStreamSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IStreamSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IStreamSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IStreamSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStreamSample_GetMediaStream_Proxy( 
    IStreamSample * This,
    /* [in] */ IMediaStream **ppMediaStream);


void __RPC_STUB IStreamSample_GetMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamSample_GetSampleTimes_Proxy( 
    IStreamSample * This,
    /* [out] */ STREAM_TIME *pStartTime,
    /* [out] */ STREAM_TIME *pEndTime,
    /* [out] */ STREAM_TIME *pCurrentTime);


void __RPC_STUB IStreamSample_GetSampleTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamSample_SetSampleTimes_Proxy( 
    IStreamSample * This,
    /* [in] */ const STREAM_TIME *pStartTime,
    /* [in] */ const STREAM_TIME *pEndTime);


void __RPC_STUB IStreamSample_SetSampleTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamSample_Update_Proxy( 
    IStreamSample * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ HANDLE hEvent,
    /* [in] */ PAPCFUNC pfnAPC,
    /* [in] */ DWORD_PTR dwAPCData);


void __RPC_STUB IStreamSample_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamSample_CompletionStatus_Proxy( 
    IStreamSample * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ DWORD dwMilliseconds);


void __RPC_STUB IStreamSample_CompletionStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStreamSample_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


