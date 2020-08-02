
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for videoacc.idl:
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

#ifndef __videoacc_h__
#define __videoacc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAMVideoAcceleratorNotify_FWD_DEFINED__
#define __IAMVideoAcceleratorNotify_FWD_DEFINED__
typedef interface IAMVideoAcceleratorNotify IAMVideoAcceleratorNotify;
#endif 	/* __IAMVideoAcceleratorNotify_FWD_DEFINED__ */


#ifndef __IAMVideoAccelerator_FWD_DEFINED__
#define __IAMVideoAccelerator_FWD_DEFINED__
typedef interface IAMVideoAccelerator IAMVideoAccelerator;
#endif 	/* __IAMVideoAccelerator_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_videoacc_0000 */
/* [local] */ 

//
//   The following declarations within the 'if 0' block are dummy typedefs used to make
//   the motncomp.idl file build.  The actual definitions are contained in ddraw.h and amva.h
//
#if 0
typedef void *LPVOID;

typedef void *LPGUID;

typedef void *LPDIRECTDRAWSURFACE;

typedef void *LPDDPIXELFORMAT;

typedef void *LPAMVAInternalMemInfo;

typedef void AMVAUncompDataInfo;

typedef void *LPAMVACompBufferInfo;

typedef void AMVABUFFERINFO;

typedef void AMVAEndFrameInfo;

typedef void *LPAMVAUncompBufferInfo;

typedef void AMVABeginFrameInfo;

typedef IUnknown *IMediaSample;

#endif
#include <ddraw.h>
#include <amva.h>


extern RPC_IF_HANDLE __MIDL_itf_videoacc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_videoacc_0000_v0_0_s_ifspec;

#ifndef __IAMVideoAcceleratorNotify_INTERFACE_DEFINED__
#define __IAMVideoAcceleratorNotify_INTERFACE_DEFINED__

/* interface IAMVideoAcceleratorNotify */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IAMVideoAcceleratorNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("256A6A21-FBAD-11d1-82BF-00A0C9696C8F")
    IAMVideoAcceleratorNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetUncompSurfacesInfo( 
            /* [in] */ const GUID *pGuid,
            /* [out][in] */ LPAMVAUncompBufferInfo pUncompBufferInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetUncompSurfacesInfo( 
            /* [in] */ DWORD dwActualUncompSurfacesAllocated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCreateVideoAcceleratorData( 
            /* [in] */ const GUID *pGuid,
            /* [out] */ LPDWORD pdwSizeMiscData,
            /* [out] */ LPVOID *ppMiscData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoAcceleratorNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoAcceleratorNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoAcceleratorNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoAcceleratorNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUncompSurfacesInfo )( 
            IAMVideoAcceleratorNotify * This,
            /* [in] */ const GUID *pGuid,
            /* [out][in] */ LPAMVAUncompBufferInfo pUncompBufferInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetUncompSurfacesInfo )( 
            IAMVideoAcceleratorNotify * This,
            /* [in] */ DWORD dwActualUncompSurfacesAllocated);
        
        HRESULT ( STDMETHODCALLTYPE *GetCreateVideoAcceleratorData )( 
            IAMVideoAcceleratorNotify * This,
            /* [in] */ const GUID *pGuid,
            /* [out] */ LPDWORD pdwSizeMiscData,
            /* [out] */ LPVOID *ppMiscData);
        
        END_INTERFACE
    } IAMVideoAcceleratorNotifyVtbl;

    interface IAMVideoAcceleratorNotify
    {
        CONST_VTBL struct IAMVideoAcceleratorNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoAcceleratorNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoAcceleratorNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoAcceleratorNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoAcceleratorNotify_GetUncompSurfacesInfo(This,pGuid,pUncompBufferInfo)	\
    (This)->lpVtbl -> GetUncompSurfacesInfo(This,pGuid,pUncompBufferInfo)

#define IAMVideoAcceleratorNotify_SetUncompSurfacesInfo(This,dwActualUncompSurfacesAllocated)	\
    (This)->lpVtbl -> SetUncompSurfacesInfo(This,dwActualUncompSurfacesAllocated)

#define IAMVideoAcceleratorNotify_GetCreateVideoAcceleratorData(This,pGuid,pdwSizeMiscData,ppMiscData)	\
    (This)->lpVtbl -> GetCreateVideoAcceleratorData(This,pGuid,pdwSizeMiscData,ppMiscData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoAcceleratorNotify_GetUncompSurfacesInfo_Proxy( 
    IAMVideoAcceleratorNotify * This,
    /* [in] */ const GUID *pGuid,
    /* [out][in] */ LPAMVAUncompBufferInfo pUncompBufferInfo);


void __RPC_STUB IAMVideoAcceleratorNotify_GetUncompSurfacesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAcceleratorNotify_SetUncompSurfacesInfo_Proxy( 
    IAMVideoAcceleratorNotify * This,
    /* [in] */ DWORD dwActualUncompSurfacesAllocated);


void __RPC_STUB IAMVideoAcceleratorNotify_SetUncompSurfacesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAcceleratorNotify_GetCreateVideoAcceleratorData_Proxy( 
    IAMVideoAcceleratorNotify * This,
    /* [in] */ const GUID *pGuid,
    /* [out] */ LPDWORD pdwSizeMiscData,
    /* [out] */ LPVOID *ppMiscData);


void __RPC_STUB IAMVideoAcceleratorNotify_GetCreateVideoAcceleratorData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoAcceleratorNotify_INTERFACE_DEFINED__ */


#ifndef __IAMVideoAccelerator_INTERFACE_DEFINED__
#define __IAMVideoAccelerator_INTERFACE_DEFINED__

/* interface IAMVideoAccelerator */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IAMVideoAccelerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("256A6A22-FBAD-11d1-82BF-00A0C9696C8F")
    IAMVideoAccelerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVideoAcceleratorGUIDs( 
            /* [out][in] */ LPDWORD pdwNumGuidsSupported,
            /* [out][in] */ LPGUID pGuidsSupported) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUncompFormatsSupported( 
            /* [in] */ const GUID *pGuid,
            /* [out][in] */ LPDWORD pdwNumFormatsSupported,
            /* [out][in] */ LPDDPIXELFORMAT pFormatsSupported) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInternalMemInfo( 
            /* [in] */ const GUID *pGuid,
            /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
            /* [out][in] */ LPAMVAInternalMemInfo pamvaInternalMemInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCompBufferInfo( 
            /* [in] */ const GUID *pGuid,
            /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
            /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
            /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInternalCompBufferInfo( 
            /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
            /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFrame( 
            /* [in] */ const AMVABeginFrameInfo *amvaBeginFrameInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFrame( 
            /* [in] */ const AMVAEndFrameInfo *pEndFrameInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex,
            /* [in] */ BOOL bReadOnly,
            /* [out] */ LPVOID *ppBuffer,
            /* [out] */ LONG *lpStride) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer( 
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ DWORD dwFunction,
            /* [in] */ LPVOID lpPrivateInputData,
            /* [in] */ DWORD cbPrivateInputData,
            /* [in] */ LPVOID lpPrivateOutputDat,
            /* [in] */ DWORD cbPrivateOutputData,
            /* [in] */ DWORD dwNumBuffers,
            /* [in] */ const AMVABUFFERINFO *pamvaBufferInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryRenderStatus( 
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisplayFrame( 
            /* [in] */ DWORD dwFlipToIndex,
            /* [in] */ IMediaSample *pMediaSample) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMVideoAcceleratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAMVideoAccelerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAMVideoAccelerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAMVideoAccelerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoAcceleratorGUIDs )( 
            IAMVideoAccelerator * This,
            /* [out][in] */ LPDWORD pdwNumGuidsSupported,
            /* [out][in] */ LPGUID pGuidsSupported);
        
        HRESULT ( STDMETHODCALLTYPE *GetUncompFormatsSupported )( 
            IAMVideoAccelerator * This,
            /* [in] */ const GUID *pGuid,
            /* [out][in] */ LPDWORD pdwNumFormatsSupported,
            /* [out][in] */ LPDDPIXELFORMAT pFormatsSupported);
        
        HRESULT ( STDMETHODCALLTYPE *GetInternalMemInfo )( 
            IAMVideoAccelerator * This,
            /* [in] */ const GUID *pGuid,
            /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
            /* [out][in] */ LPAMVAInternalMemInfo pamvaInternalMemInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCompBufferInfo )( 
            IAMVideoAccelerator * This,
            /* [in] */ const GUID *pGuid,
            /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
            /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
            /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetInternalCompBufferInfo )( 
            IAMVideoAccelerator * This,
            /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
            /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo);
        
        HRESULT ( STDMETHODCALLTYPE *BeginFrame )( 
            IAMVideoAccelerator * This,
            /* [in] */ const AMVABeginFrameInfo *amvaBeginFrameInfo);
        
        HRESULT ( STDMETHODCALLTYPE *EndFrame )( 
            IAMVideoAccelerator * This,
            /* [in] */ const AMVAEndFrameInfo *pEndFrameInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetBuffer )( 
            IAMVideoAccelerator * This,
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex,
            /* [in] */ BOOL bReadOnly,
            /* [out] */ LPVOID *ppBuffer,
            /* [out] */ LONG *lpStride);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseBuffer )( 
            IAMVideoAccelerator * This,
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex);
        
        HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IAMVideoAccelerator * This,
            /* [in] */ DWORD dwFunction,
            /* [in] */ LPVOID lpPrivateInputData,
            /* [in] */ DWORD cbPrivateInputData,
            /* [in] */ LPVOID lpPrivateOutputDat,
            /* [in] */ DWORD cbPrivateOutputData,
            /* [in] */ DWORD dwNumBuffers,
            /* [in] */ const AMVABUFFERINFO *pamvaBufferInfo);
        
        HRESULT ( STDMETHODCALLTYPE *QueryRenderStatus )( 
            IAMVideoAccelerator * This,
            /* [in] */ DWORD dwTypeIndex,
            /* [in] */ DWORD dwBufferIndex,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *DisplayFrame )( 
            IAMVideoAccelerator * This,
            /* [in] */ DWORD dwFlipToIndex,
            /* [in] */ IMediaSample *pMediaSample);
        
        END_INTERFACE
    } IAMVideoAcceleratorVtbl;

    interface IAMVideoAccelerator
    {
        CONST_VTBL struct IAMVideoAcceleratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMVideoAccelerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMVideoAccelerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMVideoAccelerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMVideoAccelerator_GetVideoAcceleratorGUIDs(This,pdwNumGuidsSupported,pGuidsSupported)	\
    (This)->lpVtbl -> GetVideoAcceleratorGUIDs(This,pdwNumGuidsSupported,pGuidsSupported)

#define IAMVideoAccelerator_GetUncompFormatsSupported(This,pGuid,pdwNumFormatsSupported,pFormatsSupported)	\
    (This)->lpVtbl -> GetUncompFormatsSupported(This,pGuid,pdwNumFormatsSupported,pFormatsSupported)

#define IAMVideoAccelerator_GetInternalMemInfo(This,pGuid,pamvaUncompDataInfo,pamvaInternalMemInfo)	\
    (This)->lpVtbl -> GetInternalMemInfo(This,pGuid,pamvaUncompDataInfo,pamvaInternalMemInfo)

#define IAMVideoAccelerator_GetCompBufferInfo(This,pGuid,pamvaUncompDataInfo,pdwNumTypesCompBuffers,pamvaCompBufferInfo)	\
    (This)->lpVtbl -> GetCompBufferInfo(This,pGuid,pamvaUncompDataInfo,pdwNumTypesCompBuffers,pamvaCompBufferInfo)

#define IAMVideoAccelerator_GetInternalCompBufferInfo(This,pdwNumTypesCompBuffers,pamvaCompBufferInfo)	\
    (This)->lpVtbl -> GetInternalCompBufferInfo(This,pdwNumTypesCompBuffers,pamvaCompBufferInfo)

#define IAMVideoAccelerator_BeginFrame(This,amvaBeginFrameInfo)	\
    (This)->lpVtbl -> BeginFrame(This,amvaBeginFrameInfo)

#define IAMVideoAccelerator_EndFrame(This,pEndFrameInfo)	\
    (This)->lpVtbl -> EndFrame(This,pEndFrameInfo)

#define IAMVideoAccelerator_GetBuffer(This,dwTypeIndex,dwBufferIndex,bReadOnly,ppBuffer,lpStride)	\
    (This)->lpVtbl -> GetBuffer(This,dwTypeIndex,dwBufferIndex,bReadOnly,ppBuffer,lpStride)

#define IAMVideoAccelerator_ReleaseBuffer(This,dwTypeIndex,dwBufferIndex)	\
    (This)->lpVtbl -> ReleaseBuffer(This,dwTypeIndex,dwBufferIndex)

#define IAMVideoAccelerator_Execute(This,dwFunction,lpPrivateInputData,cbPrivateInputData,lpPrivateOutputDat,cbPrivateOutputData,dwNumBuffers,pamvaBufferInfo)	\
    (This)->lpVtbl -> Execute(This,dwFunction,lpPrivateInputData,cbPrivateInputData,lpPrivateOutputDat,cbPrivateOutputData,dwNumBuffers,pamvaBufferInfo)

#define IAMVideoAccelerator_QueryRenderStatus(This,dwTypeIndex,dwBufferIndex,dwFlags)	\
    (This)->lpVtbl -> QueryRenderStatus(This,dwTypeIndex,dwBufferIndex,dwFlags)

#define IAMVideoAccelerator_DisplayFrame(This,dwFlipToIndex,pMediaSample)	\
    (This)->lpVtbl -> DisplayFrame(This,dwFlipToIndex,pMediaSample)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetVideoAcceleratorGUIDs_Proxy( 
    IAMVideoAccelerator * This,
    /* [out][in] */ LPDWORD pdwNumGuidsSupported,
    /* [out][in] */ LPGUID pGuidsSupported);


void __RPC_STUB IAMVideoAccelerator_GetVideoAcceleratorGUIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetUncompFormatsSupported_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ const GUID *pGuid,
    /* [out][in] */ LPDWORD pdwNumFormatsSupported,
    /* [out][in] */ LPDDPIXELFORMAT pFormatsSupported);


void __RPC_STUB IAMVideoAccelerator_GetUncompFormatsSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetInternalMemInfo_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ const GUID *pGuid,
    /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
    /* [out][in] */ LPAMVAInternalMemInfo pamvaInternalMemInfo);


void __RPC_STUB IAMVideoAccelerator_GetInternalMemInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetCompBufferInfo_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ const GUID *pGuid,
    /* [in] */ const AMVAUncompDataInfo *pamvaUncompDataInfo,
    /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
    /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo);


void __RPC_STUB IAMVideoAccelerator_GetCompBufferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetInternalCompBufferInfo_Proxy( 
    IAMVideoAccelerator * This,
    /* [out][in] */ LPDWORD pdwNumTypesCompBuffers,
    /* [out] */ LPAMVACompBufferInfo pamvaCompBufferInfo);


void __RPC_STUB IAMVideoAccelerator_GetInternalCompBufferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_BeginFrame_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ const AMVABeginFrameInfo *amvaBeginFrameInfo);


void __RPC_STUB IAMVideoAccelerator_BeginFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_EndFrame_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ const AMVAEndFrameInfo *pEndFrameInfo);


void __RPC_STUB IAMVideoAccelerator_EndFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_GetBuffer_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ DWORD dwTypeIndex,
    /* [in] */ DWORD dwBufferIndex,
    /* [in] */ BOOL bReadOnly,
    /* [out] */ LPVOID *ppBuffer,
    /* [out] */ LONG *lpStride);


void __RPC_STUB IAMVideoAccelerator_GetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_ReleaseBuffer_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ DWORD dwTypeIndex,
    /* [in] */ DWORD dwBufferIndex);


void __RPC_STUB IAMVideoAccelerator_ReleaseBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_Execute_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ DWORD dwFunction,
    /* [in] */ LPVOID lpPrivateInputData,
    /* [in] */ DWORD cbPrivateInputData,
    /* [in] */ LPVOID lpPrivateOutputDat,
    /* [in] */ DWORD cbPrivateOutputData,
    /* [in] */ DWORD dwNumBuffers,
    /* [in] */ const AMVABUFFERINFO *pamvaBufferInfo);


void __RPC_STUB IAMVideoAccelerator_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_QueryRenderStatus_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ DWORD dwTypeIndex,
    /* [in] */ DWORD dwBufferIndex,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMVideoAccelerator_QueryRenderStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMVideoAccelerator_DisplayFrame_Proxy( 
    IAMVideoAccelerator * This,
    /* [in] */ DWORD dwFlipToIndex,
    /* [in] */ IMediaSample *pMediaSample);


void __RPC_STUB IAMVideoAccelerator_DisplayFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMVideoAccelerator_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


