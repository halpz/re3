
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for ddstream.idl:
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

#ifndef __ddstream_h__
#define __ddstream_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDirectDrawMediaStream_FWD_DEFINED__
#define __IDirectDrawMediaStream_FWD_DEFINED__
typedef interface IDirectDrawMediaStream IDirectDrawMediaStream;
#endif 	/* __IDirectDrawMediaStream_FWD_DEFINED__ */


#ifndef __IDirectDrawStreamSample_FWD_DEFINED__
#define __IDirectDrawStreamSample_FWD_DEFINED__
typedef interface IDirectDrawStreamSample IDirectDrawStreamSample;
#endif 	/* __IDirectDrawStreamSample_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "mmstream.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_ddstream_0000 */
/* [local] */ 

//
//   The following declarations within the 'if 0' block are dummy typedefs used to make
//   the ddstream.idl file build.  The actual definitions are contained in DDRAW.H
//
#if 0
typedef void *LPDDSURFACEDESC;

typedef struct tDDSURFACEDESC DDSURFACEDESC;

#endif
#include <ddraw.h>

enum __MIDL___MIDL_itf_ddstream_0000_0001
    {	DDSFF_PROGRESSIVERENDER	= 0x1
    } ;







extern RPC_IF_HANDLE __MIDL_itf_ddstream_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ddstream_0000_v0_0_s_ifspec;

#ifndef __IDirectDrawMediaStream_INTERFACE_DEFINED__
#define __IDirectDrawMediaStream_INTERFACE_DEFINED__

/* interface IDirectDrawMediaStream */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDirectDrawMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4104FCE-9A70-11d0-8FDE-00C04FD9189D")
    IDirectDrawMediaStream : public IMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [out] */ DDSURFACEDESC *pDDSDCurrent,
            /* [out] */ IDirectDrawPalette **ppDirectDrawPalette,
            /* [out] */ DDSURFACEDESC *pDDSDDesired,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ const DDSURFACEDESC *pDDSurfaceDesc,
            /* [in] */ IDirectDrawPalette *pDirectDrawPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirectDraw( 
            /* [out] */ IDirectDraw **ppDirectDraw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDirectDraw( 
            /* [in] */ IDirectDraw *pDirectDraw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSample( 
            /* [in] */ IDirectDrawSurface *pSurface,
            /* [in] */ const RECT *pRect,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDirectDrawStreamSample **ppSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimePerFrame( 
            /* [out] */ STREAM_TIME *pFrameTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDirectDrawMediaStream * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDirectDrawMediaStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDirectDrawMediaStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMultiMediaStream )( 
            IDirectDrawMediaStream * This,
            /* [out] */ IMultiMediaStream **ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetInformation )( 
            IDirectDrawMediaStream * This,
            /* [out] */ MSPID *pPurposeId,
            /* [out] */ STREAM_TYPE *pType);
        
        HRESULT ( STDMETHODCALLTYPE *SetSameFormat )( 
            IDirectDrawMediaStream * This,
            /* [in] */ IMediaStream *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *AllocateSample )( 
            IDirectDrawMediaStream * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppSample);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSharedSample )( 
            IDirectDrawMediaStream * This,
            /* [in] */ IStreamSample *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample **ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE *SendEndOfStream )( 
            IDirectDrawMediaStream * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IDirectDrawMediaStream * This,
            /* [out] */ DDSURFACEDESC *pDDSDCurrent,
            /* [out] */ IDirectDrawPalette **ppDirectDrawPalette,
            /* [out] */ DDSURFACEDESC *pDDSDDesired,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetFormat )( 
            IDirectDrawMediaStream * This,
            /* [in] */ const DDSURFACEDESC *pDDSurfaceDesc,
            /* [in] */ IDirectDrawPalette *pDirectDrawPalette);
        
        HRESULT ( STDMETHODCALLTYPE *GetDirectDraw )( 
            IDirectDrawMediaStream * This,
            /* [out] */ IDirectDraw **ppDirectDraw);
        
        HRESULT ( STDMETHODCALLTYPE *SetDirectDraw )( 
            IDirectDrawMediaStream * This,
            /* [in] */ IDirectDraw *pDirectDraw);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSample )( 
            IDirectDrawMediaStream * This,
            /* [in] */ IDirectDrawSurface *pSurface,
            /* [in] */ const RECT *pRect,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDirectDrawStreamSample **ppSample);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimePerFrame )( 
            IDirectDrawMediaStream * This,
            /* [out] */ STREAM_TIME *pFrameTime);
        
        END_INTERFACE
    } IDirectDrawMediaStreamVtbl;

    interface IDirectDrawMediaStream
    {
        CONST_VTBL struct IDirectDrawMediaStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IDirectDrawMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IDirectDrawMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IDirectDrawMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IDirectDrawMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IDirectDrawMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IDirectDrawMediaStream_GetFormat(This,pDDSDCurrent,ppDirectDrawPalette,pDDSDDesired,pdwFlags)	\
    (This)->lpVtbl -> GetFormat(This,pDDSDCurrent,ppDirectDrawPalette,pDDSDDesired,pdwFlags)

#define IDirectDrawMediaStream_SetFormat(This,pDDSurfaceDesc,pDirectDrawPalette)	\
    (This)->lpVtbl -> SetFormat(This,pDDSurfaceDesc,pDirectDrawPalette)

#define IDirectDrawMediaStream_GetDirectDraw(This,ppDirectDraw)	\
    (This)->lpVtbl -> GetDirectDraw(This,ppDirectDraw)

#define IDirectDrawMediaStream_SetDirectDraw(This,pDirectDraw)	\
    (This)->lpVtbl -> SetDirectDraw(This,pDirectDraw)

#define IDirectDrawMediaStream_CreateSample(This,pSurface,pRect,dwFlags,ppSample)	\
    (This)->lpVtbl -> CreateSample(This,pSurface,pRect,dwFlags,ppSample)

#define IDirectDrawMediaStream_GetTimePerFrame(This,pFrameTime)	\
    (This)->lpVtbl -> GetTimePerFrame(This,pFrameTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetFormat_Proxy( 
    IDirectDrawMediaStream * This,
    /* [out] */ DDSURFACEDESC *pDDSDCurrent,
    /* [out] */ IDirectDrawPalette **ppDirectDrawPalette,
    /* [out] */ DDSURFACEDESC *pDDSDDesired,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IDirectDrawMediaStream_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_SetFormat_Proxy( 
    IDirectDrawMediaStream * This,
    /* [in] */ const DDSURFACEDESC *pDDSurfaceDesc,
    /* [in] */ IDirectDrawPalette *pDirectDrawPalette);


void __RPC_STUB IDirectDrawMediaStream_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetDirectDraw_Proxy( 
    IDirectDrawMediaStream * This,
    /* [out] */ IDirectDraw **ppDirectDraw);


void __RPC_STUB IDirectDrawMediaStream_GetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_SetDirectDraw_Proxy( 
    IDirectDrawMediaStream * This,
    /* [in] */ IDirectDraw *pDirectDraw);


void __RPC_STUB IDirectDrawMediaStream_SetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_CreateSample_Proxy( 
    IDirectDrawMediaStream * This,
    /* [in] */ IDirectDrawSurface *pSurface,
    /* [in] */ const RECT *pRect,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDirectDrawStreamSample **ppSample);


void __RPC_STUB IDirectDrawMediaStream_CreateSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetTimePerFrame_Proxy( 
    IDirectDrawMediaStream * This,
    /* [out] */ STREAM_TIME *pFrameTime);


void __RPC_STUB IDirectDrawMediaStream_GetTimePerFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawMediaStream_INTERFACE_DEFINED__ */


#ifndef __IDirectDrawStreamSample_INTERFACE_DEFINED__
#define __IDirectDrawStreamSample_INTERFACE_DEFINED__

/* interface IDirectDrawStreamSample */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IDirectDrawStreamSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4104FCF-9A70-11d0-8FDE-00C04FD9189D")
    IDirectDrawStreamSample : public IStreamSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [out] */ IDirectDrawSurface **ppDirectDrawSurface,
            /* [out] */ RECT *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRect( 
            /* [in] */ const RECT *pRect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawStreamSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDirectDrawStreamSample * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDirectDrawStreamSample * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDirectDrawStreamSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaStream )( 
            IDirectDrawStreamSample * This,
            /* [in] */ IMediaStream **ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE *GetSampleTimes )( 
            IDirectDrawStreamSample * This,
            /* [out] */ STREAM_TIME *pStartTime,
            /* [out] */ STREAM_TIME *pEndTime,
            /* [out] */ STREAM_TIME *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE *SetSampleTimes )( 
            IDirectDrawStreamSample * This,
            /* [in] */ const STREAM_TIME *pStartTime,
            /* [in] */ const STREAM_TIME *pEndTime);
        
        HRESULT ( STDMETHODCALLTYPE *Update )( 
            IDirectDrawStreamSample * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HANDLE hEvent,
            /* [in] */ PAPCFUNC pfnAPC,
            /* [in] */ DWORD_PTR dwAPCData);
        
        HRESULT ( STDMETHODCALLTYPE *CompletionStatus )( 
            IDirectDrawStreamSample * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD dwMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            IDirectDrawStreamSample * This,
            /* [out] */ IDirectDrawSurface **ppDirectDrawSurface,
            /* [out] */ RECT *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *SetRect )( 
            IDirectDrawStreamSample * This,
            /* [in] */ const RECT *pRect);
        
        END_INTERFACE
    } IDirectDrawStreamSampleVtbl;

    interface IDirectDrawStreamSample
    {
        CONST_VTBL struct IDirectDrawStreamSampleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawStreamSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawStreamSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawStreamSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawStreamSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IDirectDrawStreamSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IDirectDrawStreamSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IDirectDrawStreamSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IDirectDrawStreamSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)


#define IDirectDrawStreamSample_GetSurface(This,ppDirectDrawSurface,pRect)	\
    (This)->lpVtbl -> GetSurface(This,ppDirectDrawSurface,pRect)

#define IDirectDrawStreamSample_SetRect(This,pRect)	\
    (This)->lpVtbl -> SetRect(This,pRect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawStreamSample_GetSurface_Proxy( 
    IDirectDrawStreamSample * This,
    /* [out] */ IDirectDrawSurface **ppDirectDrawSurface,
    /* [out] */ RECT *pRect);


void __RPC_STUB IDirectDrawStreamSample_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawStreamSample_SetRect_Proxy( 
    IDirectDrawStreamSample * This,
    /* [in] */ const RECT *pRect);


void __RPC_STUB IDirectDrawStreamSample_SetRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawStreamSample_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


