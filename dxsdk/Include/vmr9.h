
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for vmr9.idl:
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

#ifndef __vmr9_h__
#define __vmr9_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVMRImagePresenter9_FWD_DEFINED__
#define __IVMRImagePresenter9_FWD_DEFINED__
typedef interface IVMRImagePresenter9 IVMRImagePresenter9;
#endif 	/* __IVMRImagePresenter9_FWD_DEFINED__ */


#ifndef __IVMRSurfaceAllocator9_FWD_DEFINED__
#define __IVMRSurfaceAllocator9_FWD_DEFINED__
typedef interface IVMRSurfaceAllocator9 IVMRSurfaceAllocator9;
#endif 	/* __IVMRSurfaceAllocator9_FWD_DEFINED__ */


#ifndef __IVMRSurfaceAllocatorNotify9_FWD_DEFINED__
#define __IVMRSurfaceAllocatorNotify9_FWD_DEFINED__
typedef interface IVMRSurfaceAllocatorNotify9 IVMRSurfaceAllocatorNotify9;
#endif 	/* __IVMRSurfaceAllocatorNotify9_FWD_DEFINED__ */


#ifndef __IVMRWindowlessControl9_FWD_DEFINED__
#define __IVMRWindowlessControl9_FWD_DEFINED__
typedef interface IVMRWindowlessControl9 IVMRWindowlessControl9;
#endif 	/* __IVMRWindowlessControl9_FWD_DEFINED__ */


#ifndef __IVMRMixerControl9_FWD_DEFINED__
#define __IVMRMixerControl9_FWD_DEFINED__
typedef interface IVMRMixerControl9 IVMRMixerControl9;
#endif 	/* __IVMRMixerControl9_FWD_DEFINED__ */


#ifndef __IVMRMixerBitmap9_FWD_DEFINED__
#define __IVMRMixerBitmap9_FWD_DEFINED__
typedef interface IVMRMixerBitmap9 IVMRMixerBitmap9;
#endif 	/* __IVMRMixerBitmap9_FWD_DEFINED__ */


#ifndef __IVMRSurface9_FWD_DEFINED__
#define __IVMRSurface9_FWD_DEFINED__
typedef interface IVMRSurface9 IVMRSurface9;
#endif 	/* __IVMRSurface9_FWD_DEFINED__ */


#ifndef __IVMRImagePresenterConfig9_FWD_DEFINED__
#define __IVMRImagePresenterConfig9_FWD_DEFINED__
typedef interface IVMRImagePresenterConfig9 IVMRImagePresenterConfig9;
#endif 	/* __IVMRImagePresenterConfig9_FWD_DEFINED__ */


#ifndef __IVMRVideoStreamControl9_FWD_DEFINED__
#define __IVMRVideoStreamControl9_FWD_DEFINED__
typedef interface IVMRVideoStreamControl9 IVMRVideoStreamControl9;
#endif 	/* __IVMRVideoStreamControl9_FWD_DEFINED__ */


#ifndef __IVMRFilterConfig9_FWD_DEFINED__
#define __IVMRFilterConfig9_FWD_DEFINED__
typedef interface IVMRFilterConfig9 IVMRFilterConfig9;
#endif 	/* __IVMRFilterConfig9_FWD_DEFINED__ */


#ifndef __IVMRAspectRatioControl9_FWD_DEFINED__
#define __IVMRAspectRatioControl9_FWD_DEFINED__
typedef interface IVMRAspectRatioControl9 IVMRAspectRatioControl9;
#endif 	/* __IVMRAspectRatioControl9_FWD_DEFINED__ */


#ifndef __IVMRMonitorConfig9_FWD_DEFINED__
#define __IVMRMonitorConfig9_FWD_DEFINED__
typedef interface IVMRMonitorConfig9 IVMRMonitorConfig9;
#endif 	/* __IVMRMonitorConfig9_FWD_DEFINED__ */


#ifndef __IVMRDeinterlaceControl9_FWD_DEFINED__
#define __IVMRDeinterlaceControl9_FWD_DEFINED__
typedef interface IVMRDeinterlaceControl9 IVMRDeinterlaceControl9;
#endif 	/* __IVMRDeinterlaceControl9_FWD_DEFINED__ */


#ifndef __IVMRImageCompositor9_FWD_DEFINED__
#define __IVMRImageCompositor9_FWD_DEFINED__
typedef interface IVMRImageCompositor9 IVMRImageCompositor9;
#endif 	/* __IVMRImageCompositor9_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_vmr9_0000 */
/* [local] */ 

#if 0
typedef DWORD IDirect3DDevice9;

typedef DWORD IDirect3DSurface9;

typedef DWORD D3DFORMAT;

typedef DWORD D3DCOLOR;

typedef DWORD D3DPOOL;

typedef LONGLONG REFERENCE_TIME;

typedef DWORD *HMONITOR;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_vmr9_0000_0001
    {
    DWORD dw1;
    DWORD dw2;
    } 	AM_MEDIA_TYPE;

#endif













typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0000_0002
    {	VMR9Sample_SyncPoint	= 0x1,
	VMR9Sample_Preroll	= 0x2,
	VMR9Sample_Discontinuity	= 0x4,
	VMR9Sample_TimeValid	= 0x8
    } 	VMR9PresentationFlags;

typedef struct _VMR9PresentationInfo
    {
    DWORD dwFlags;
    IDirect3DSurface9 *lpSurf;
    REFERENCE_TIME rtStart;
    REFERENCE_TIME rtEnd;
    SIZE szAspectRatio;
    RECT rcSrc;
    RECT rcDst;
    DWORD dwReserved1;
    DWORD dwReserved2;
    } 	VMR9PresentationInfo;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0000_v0_0_s_ifspec;

#ifndef __IVMRImagePresenter9_INTERFACE_DEFINED__
#define __IVMRImagePresenter9_INTERFACE_DEFINED__

/* interface IVMRImagePresenter9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImagePresenter9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69188c61-12a3-40f0-8ffc-342e7b433fd7")
    IVMRImagePresenter9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartPresenting( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopPresenting( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PresentImage( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9PresentationInfo *lpPresInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImagePresenter9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImagePresenter9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImagePresenter9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImagePresenter9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartPresenting )( 
            IVMRImagePresenter9 * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *StopPresenting )( 
            IVMRImagePresenter9 * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *PresentImage )( 
            IVMRImagePresenter9 * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9PresentationInfo *lpPresInfo);
        
        END_INTERFACE
    } IVMRImagePresenter9Vtbl;

    interface IVMRImagePresenter9
    {
        CONST_VTBL struct IVMRImagePresenter9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImagePresenter9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImagePresenter9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImagePresenter9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImagePresenter9_StartPresenting(This,dwUserID)	\
    (This)->lpVtbl -> StartPresenting(This,dwUserID)

#define IVMRImagePresenter9_StopPresenting(This,dwUserID)	\
    (This)->lpVtbl -> StopPresenting(This,dwUserID)

#define IVMRImagePresenter9_PresentImage(This,dwUserID,lpPresInfo)	\
    (This)->lpVtbl -> PresentImage(This,dwUserID,lpPresInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImagePresenter9_StartPresenting_Proxy( 
    IVMRImagePresenter9 * This,
    /* [in] */ DWORD_PTR dwUserID);


void __RPC_STUB IVMRImagePresenter9_StartPresenting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenter9_StopPresenting_Proxy( 
    IVMRImagePresenter9 * This,
    /* [in] */ DWORD_PTR dwUserID);


void __RPC_STUB IVMRImagePresenter9_StopPresenting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenter9_PresentImage_Proxy( 
    IVMRImagePresenter9 * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ VMR9PresentationInfo *lpPresInfo);


void __RPC_STUB IVMRImagePresenter9_PresentImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImagePresenter9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0009 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0009_0001
    {	VMR9AllocFlag_3DRenderTarget	= 0x1,
	VMR9AllocFlag_DXVATarget	= 0x2,
	VMR9AllocFlag_TextureSurface	= 0x4,
	VMR9AllocFlag_OffscreenSurface	= 0x8,
	VMR9AllocFlag_UsageReserved	= 0xf0,
	VMR9AllocFlag_UsageMask	= 0xff
    } 	VMR9SurfaceAllocationFlags;

typedef struct _VMR9AllocationInfo
    {
    DWORD dwFlags;
    DWORD dwWidth;
    DWORD dwHeight;
    D3DFORMAT Format;
    D3DPOOL Pool;
    DWORD MinBuffers;
    SIZE szAspectRatio;
    SIZE szNativeSize;
    } 	VMR9AllocationInfo;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0009_v0_0_s_ifspec;

#ifndef __IVMRSurfaceAllocator9_INTERFACE_DEFINED__
#define __IVMRSurfaceAllocator9_INTERFACE_DEFINED__

/* interface IVMRSurfaceAllocator9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurfaceAllocator9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8d5148ea-3f5d-46cf-9df1-d1b896eedb1f")
    IVMRSurfaceAllocator9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitializeDevice( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TerminateDevice( 
            /* [in] */ DWORD_PTR dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ DWORD SurfaceIndex,
            /* [in] */ DWORD SurfaceFlags,
            /* [out] */ IDirect3DSurface9 **lplpSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdviseNotify( 
            /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurfaceAllocator9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurfaceAllocator9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurfaceAllocator9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurfaceAllocator9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeDevice )( 
            IVMRSurfaceAllocator9 * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers);
        
        HRESULT ( STDMETHODCALLTYPE *TerminateDevice )( 
            IVMRSurfaceAllocator9 * This,
            /* [in] */ DWORD_PTR dwID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            IVMRSurfaceAllocator9 * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ DWORD SurfaceIndex,
            /* [in] */ DWORD SurfaceFlags,
            /* [out] */ IDirect3DSurface9 **lplpSurface);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseNotify )( 
            IVMRSurfaceAllocator9 * This,
            /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify);
        
        END_INTERFACE
    } IVMRSurfaceAllocator9Vtbl;

    interface IVMRSurfaceAllocator9
    {
        CONST_VTBL struct IVMRSurfaceAllocator9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurfaceAllocator9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurfaceAllocator9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurfaceAllocator9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurfaceAllocator9_InitializeDevice(This,dwUserID,lpAllocInfo,lpNumBuffers)	\
    (This)->lpVtbl -> InitializeDevice(This,dwUserID,lpAllocInfo,lpNumBuffers)

#define IVMRSurfaceAllocator9_TerminateDevice(This,dwID)	\
    (This)->lpVtbl -> TerminateDevice(This,dwID)

#define IVMRSurfaceAllocator9_GetSurface(This,dwUserID,SurfaceIndex,SurfaceFlags,lplpSurface)	\
    (This)->lpVtbl -> GetSurface(This,dwUserID,SurfaceIndex,SurfaceFlags,lplpSurface)

#define IVMRSurfaceAllocator9_AdviseNotify(This,lpIVMRSurfAllocNotify)	\
    (This)->lpVtbl -> AdviseNotify(This,lpIVMRSurfAllocNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator9_InitializeDevice_Proxy( 
    IVMRSurfaceAllocator9 * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ VMR9AllocationInfo *lpAllocInfo,
    /* [out][in] */ DWORD *lpNumBuffers);


void __RPC_STUB IVMRSurfaceAllocator9_InitializeDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator9_TerminateDevice_Proxy( 
    IVMRSurfaceAllocator9 * This,
    /* [in] */ DWORD_PTR dwID);


void __RPC_STUB IVMRSurfaceAllocator9_TerminateDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator9_GetSurface_Proxy( 
    IVMRSurfaceAllocator9 * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ DWORD SurfaceIndex,
    /* [in] */ DWORD SurfaceFlags,
    /* [out] */ IDirect3DSurface9 **lplpSurface);


void __RPC_STUB IVMRSurfaceAllocator9_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocator9_AdviseNotify_Proxy( 
    IVMRSurfaceAllocator9 * This,
    /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify);


void __RPC_STUB IVMRSurfaceAllocator9_AdviseNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurfaceAllocator9_INTERFACE_DEFINED__ */


#ifndef __IVMRSurfaceAllocatorNotify9_INTERFACE_DEFINED__
#define __IVMRSurfaceAllocatorNotify9_INTERFACE_DEFINED__

/* interface IVMRSurfaceAllocatorNotify9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurfaceAllocatorNotify9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dca3f5df-bb3a-4d03-bd81-84614bfbfa0c")
    IVMRSurfaceAllocatorNotify9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AdviseSurfaceAllocator( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ IVMRSurfaceAllocator9 *lpIVRMSurfaceAllocator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetD3DDevice( 
            /* [in] */ IDirect3DDevice9 *lpD3DDevice,
            /* [in] */ HMONITOR hMonitor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeD3DDevice( 
            /* [in] */ IDirect3DDevice9 *lpD3DDevice,
            /* [in] */ HMONITOR hMonitor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocateSurfaceHelper( 
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers,
            /* [out] */ IDirect3DSurface9 **lplpSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyEvent( 
            /* [in] */ LONG EventCode,
            /* [in] */ LONG_PTR Param1,
            /* [in] */ LONG_PTR Param2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurfaceAllocatorNotify9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurfaceAllocatorNotify9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurfaceAllocatorNotify9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AdviseSurfaceAllocator )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ IVMRSurfaceAllocator9 *lpIVRMSurfaceAllocator);
        
        HRESULT ( STDMETHODCALLTYPE *SetD3DDevice )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ IDirect3DDevice9 *lpD3DDevice,
            /* [in] */ HMONITOR hMonitor);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeD3DDevice )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ IDirect3DDevice9 *lpD3DDevice,
            /* [in] */ HMONITOR hMonitor);
        
        HRESULT ( STDMETHODCALLTYPE *AllocateSurfaceHelper )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers,
            /* [out] */ IDirect3DSurface9 **lplpSurface);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyEvent )( 
            IVMRSurfaceAllocatorNotify9 * This,
            /* [in] */ LONG EventCode,
            /* [in] */ LONG_PTR Param1,
            /* [in] */ LONG_PTR Param2);
        
        END_INTERFACE
    } IVMRSurfaceAllocatorNotify9Vtbl;

    interface IVMRSurfaceAllocatorNotify9
    {
        CONST_VTBL struct IVMRSurfaceAllocatorNotify9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurfaceAllocatorNotify9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurfaceAllocatorNotify9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurfaceAllocatorNotify9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurfaceAllocatorNotify9_AdviseSurfaceAllocator(This,dwUserID,lpIVRMSurfaceAllocator)	\
    (This)->lpVtbl -> AdviseSurfaceAllocator(This,dwUserID,lpIVRMSurfaceAllocator)

#define IVMRSurfaceAllocatorNotify9_SetD3DDevice(This,lpD3DDevice,hMonitor)	\
    (This)->lpVtbl -> SetD3DDevice(This,lpD3DDevice,hMonitor)

#define IVMRSurfaceAllocatorNotify9_ChangeD3DDevice(This,lpD3DDevice,hMonitor)	\
    (This)->lpVtbl -> ChangeD3DDevice(This,lpD3DDevice,hMonitor)

#define IVMRSurfaceAllocatorNotify9_AllocateSurfaceHelper(This,lpAllocInfo,lpNumBuffers,lplpSurface)	\
    (This)->lpVtbl -> AllocateSurfaceHelper(This,lpAllocInfo,lpNumBuffers,lplpSurface)

#define IVMRSurfaceAllocatorNotify9_NotifyEvent(This,EventCode,Param1,Param2)	\
    (This)->lpVtbl -> NotifyEvent(This,EventCode,Param1,Param2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify9_AdviseSurfaceAllocator_Proxy( 
    IVMRSurfaceAllocatorNotify9 * This,
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ IVMRSurfaceAllocator9 *lpIVRMSurfaceAllocator);


void __RPC_STUB IVMRSurfaceAllocatorNotify9_AdviseSurfaceAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify9_SetD3DDevice_Proxy( 
    IVMRSurfaceAllocatorNotify9 * This,
    /* [in] */ IDirect3DDevice9 *lpD3DDevice,
    /* [in] */ HMONITOR hMonitor);


void __RPC_STUB IVMRSurfaceAllocatorNotify9_SetD3DDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify9_ChangeD3DDevice_Proxy( 
    IVMRSurfaceAllocatorNotify9 * This,
    /* [in] */ IDirect3DDevice9 *lpD3DDevice,
    /* [in] */ HMONITOR hMonitor);


void __RPC_STUB IVMRSurfaceAllocatorNotify9_ChangeD3DDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify9_AllocateSurfaceHelper_Proxy( 
    IVMRSurfaceAllocatorNotify9 * This,
    /* [in] */ VMR9AllocationInfo *lpAllocInfo,
    /* [out][in] */ DWORD *lpNumBuffers,
    /* [out] */ IDirect3DSurface9 **lplpSurface);


void __RPC_STUB IVMRSurfaceAllocatorNotify9_AllocateSurfaceHelper_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurfaceAllocatorNotify9_NotifyEvent_Proxy( 
    IVMRSurfaceAllocatorNotify9 * This,
    /* [in] */ LONG EventCode,
    /* [in] */ LONG_PTR Param1,
    /* [in] */ LONG_PTR Param2);


void __RPC_STUB IVMRSurfaceAllocatorNotify9_NotifyEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurfaceAllocatorNotify9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0011 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0011_0001
    {	VMR9ARMode_None	= 0,
	VMR9ARMode_LetterBox	= VMR9ARMode_None + 1
    } 	VMR9AspectRatioMode;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0011_v0_0_s_ifspec;

#ifndef __IVMRWindowlessControl9_INTERFACE_DEFINED__
#define __IVMRWindowlessControl9_INTERFACE_DEFINED__

/* interface IVMRWindowlessControl9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRWindowlessControl9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8f537d09-f85e-4414-b23b-502e54c79927")
    IVMRWindowlessControl9 : public IUnknown
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
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRWindowlessControl9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRWindowlessControl9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRWindowlessControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNativeVideoSize )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight,
            /* [out] */ LONG *lpARWidth,
            /* [out] */ LONG *lpARHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinIdealVideoSize )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxIdealVideoSize )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ LONG *lpWidth,
            /* [out] */ LONG *lpHeight);
        
        HRESULT ( STDMETHODCALLTYPE *SetVideoPosition )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ const LPRECT lpSRCRect,
            /* [in] */ const LPRECT lpDSTRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoPosition )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ LPRECT lpSRCRect,
            /* [out] */ LPRECT lpDSTRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetAspectRatioMode )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ DWORD *lpAspectRatioMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetAspectRatioMode )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ DWORD AspectRatioMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetVideoClippingWindow )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *RepaintVideo )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ HWND hwnd,
            /* [in] */ HDC hdc);
        
        HRESULT ( STDMETHODCALLTYPE *DisplayModeChanged )( 
            IVMRWindowlessControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentImage )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ BYTE **lpDib);
        
        HRESULT ( STDMETHODCALLTYPE *SetBorderColor )( 
            IVMRWindowlessControl9 * This,
            /* [in] */ COLORREF Clr);
        
        HRESULT ( STDMETHODCALLTYPE *GetBorderColor )( 
            IVMRWindowlessControl9 * This,
            /* [out] */ COLORREF *lpClr);
        
        END_INTERFACE
    } IVMRWindowlessControl9Vtbl;

    interface IVMRWindowlessControl9
    {
        CONST_VTBL struct IVMRWindowlessControl9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRWindowlessControl9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRWindowlessControl9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRWindowlessControl9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRWindowlessControl9_GetNativeVideoSize(This,lpWidth,lpHeight,lpARWidth,lpARHeight)	\
    (This)->lpVtbl -> GetNativeVideoSize(This,lpWidth,lpHeight,lpARWidth,lpARHeight)

#define IVMRWindowlessControl9_GetMinIdealVideoSize(This,lpWidth,lpHeight)	\
    (This)->lpVtbl -> GetMinIdealVideoSize(This,lpWidth,lpHeight)

#define IVMRWindowlessControl9_GetMaxIdealVideoSize(This,lpWidth,lpHeight)	\
    (This)->lpVtbl -> GetMaxIdealVideoSize(This,lpWidth,lpHeight)

#define IVMRWindowlessControl9_SetVideoPosition(This,lpSRCRect,lpDSTRect)	\
    (This)->lpVtbl -> SetVideoPosition(This,lpSRCRect,lpDSTRect)

#define IVMRWindowlessControl9_GetVideoPosition(This,lpSRCRect,lpDSTRect)	\
    (This)->lpVtbl -> GetVideoPosition(This,lpSRCRect,lpDSTRect)

#define IVMRWindowlessControl9_GetAspectRatioMode(This,lpAspectRatioMode)	\
    (This)->lpVtbl -> GetAspectRatioMode(This,lpAspectRatioMode)

#define IVMRWindowlessControl9_SetAspectRatioMode(This,AspectRatioMode)	\
    (This)->lpVtbl -> SetAspectRatioMode(This,AspectRatioMode)

#define IVMRWindowlessControl9_SetVideoClippingWindow(This,hwnd)	\
    (This)->lpVtbl -> SetVideoClippingWindow(This,hwnd)

#define IVMRWindowlessControl9_RepaintVideo(This,hwnd,hdc)	\
    (This)->lpVtbl -> RepaintVideo(This,hwnd,hdc)

#define IVMRWindowlessControl9_DisplayModeChanged(This)	\
    (This)->lpVtbl -> DisplayModeChanged(This)

#define IVMRWindowlessControl9_GetCurrentImage(This,lpDib)	\
    (This)->lpVtbl -> GetCurrentImage(This,lpDib)

#define IVMRWindowlessControl9_SetBorderColor(This,Clr)	\
    (This)->lpVtbl -> SetBorderColor(This,Clr)

#define IVMRWindowlessControl9_GetBorderColor(This,lpClr)	\
    (This)->lpVtbl -> GetBorderColor(This,lpClr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetNativeVideoSize_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight,
    /* [out] */ LONG *lpARWidth,
    /* [out] */ LONG *lpARHeight);


void __RPC_STUB IVMRWindowlessControl9_GetNativeVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetMinIdealVideoSize_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight);


void __RPC_STUB IVMRWindowlessControl9_GetMinIdealVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetMaxIdealVideoSize_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ LONG *lpWidth,
    /* [out] */ LONG *lpHeight);


void __RPC_STUB IVMRWindowlessControl9_GetMaxIdealVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_SetVideoPosition_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [in] */ const LPRECT lpSRCRect,
    /* [in] */ const LPRECT lpDSTRect);


void __RPC_STUB IVMRWindowlessControl9_SetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetVideoPosition_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ LPRECT lpSRCRect,
    /* [out] */ LPRECT lpDSTRect);


void __RPC_STUB IVMRWindowlessControl9_GetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetAspectRatioMode_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ DWORD *lpAspectRatioMode);


void __RPC_STUB IVMRWindowlessControl9_GetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_SetAspectRatioMode_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [in] */ DWORD AspectRatioMode);


void __RPC_STUB IVMRWindowlessControl9_SetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_SetVideoClippingWindow_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB IVMRWindowlessControl9_SetVideoClippingWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_RepaintVideo_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [in] */ HWND hwnd,
    /* [in] */ HDC hdc);


void __RPC_STUB IVMRWindowlessControl9_RepaintVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_DisplayModeChanged_Proxy( 
    IVMRWindowlessControl9 * This);


void __RPC_STUB IVMRWindowlessControl9_DisplayModeChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetCurrentImage_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ BYTE **lpDib);


void __RPC_STUB IVMRWindowlessControl9_GetCurrentImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_SetBorderColor_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [in] */ COLORREF Clr);


void __RPC_STUB IVMRWindowlessControl9_SetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRWindowlessControl9_GetBorderColor_Proxy( 
    IVMRWindowlessControl9 * This,
    /* [out] */ COLORREF *lpClr);


void __RPC_STUB IVMRWindowlessControl9_GetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRWindowlessControl9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0012 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0012_0001
    {	MixerPref9_NoDecimation	= 0x1,
	MixerPref9_DecimateOutput	= 0x2,
	MixerPref9_DecimationReserved	= 0xc,
	MixerPref9_DecimateMask	= 0xf,
	MixerPref9_BiLinearFiltering	= 0x10,
	MixerPref9_PointFiltering	= 0x20,
	MixerPref9_AnisotropicFiltering	= 0x40,
	MixerPref9_PyramidalQuadFiltering	= 0x80,
	MixerPref9_GaussianQuadFiltering	= 0x100,
	MixerPref9_FilteringReserved	= 0xe00,
	MixerPref9_FilteringMask	= 0xff0,
	MixerPref9_RenderTargetRGB	= 0x1000,
	MixerPref9_RenderTargetReserved	= 0xfe000,
	MixerPref9_RenderTargetMask	= 0xff000
    } 	VMR9MixerPrefs;

typedef struct _VMR9NormalizedRect
    {
    float left;
    float top;
    float right;
    float bottom;
    } 	VMR9NormalizedRect;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_vmr9_0012_0002
    {	ProcAmpControl9_Brightness	= 0x1,
	ProcAmpControl9_Contrast	= 0x2,
	ProcAmpControl9_Hue	= 0x4,
	ProcAmpControl9_Saturation	= 0x8,
	ProcAmpControl9_Mask	= 0xf
    } 	VMR9ProcAmpControlFlags;

typedef struct _VMR9ProcAmpControl
    {
    DWORD dwSize;
    DWORD dwFlags;
    float Brightness;
    float Contrast;
    float Hue;
    float Saturation;
    } 	VMR9ProcAmpControl;

typedef struct _VMR9ProcAmpControlRange
    {
    DWORD dwSize;
    VMR9ProcAmpControlFlags dwProperty;
    float MinValue;
    float MaxValue;
    float DefaultValue;
    float StepSize;
    } 	VMR9ProcAmpControlRange;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0012_v0_0_s_ifspec;

#ifndef __IVMRMixerControl9_INTERFACE_DEFINED__
#define __IVMRMixerControl9_INTERFACE_DEFINED__

/* interface IVMRMixerControl9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRMixerControl9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1a777eaa-47c8-4930-b2c9-8fee1c1b0f3b")
    IVMRMixerControl9 : public IUnknown
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
            /* [in] */ const VMR9NormalizedRect *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputRect( 
            /* [in] */ DWORD dwStreamID,
            /* [out] */ VMR9NormalizedRect *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBackgroundClr( 
            /* [in] */ COLORREF ClrBkg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackgroundClr( 
            /* [in] */ COLORREF *lpClrBkg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMixingPrefs( 
            /* [in] */ DWORD dwMixerPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMixingPrefs( 
            /* [out] */ DWORD *pdwMixerPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProcAmpControl( 
            /* [in] */ DWORD dwStreamID,
            /* [in] */ VMR9ProcAmpControl *lpClrControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProcAmpControl( 
            /* [in] */ DWORD dwStreamID,
            /* [out][in] */ VMR9ProcAmpControl *lpClrControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProcAmpControlRange( 
            /* [in] */ DWORD dwStreamID,
            /* [out][in] */ VMR9ProcAmpControlRange *lpClrControl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMixerControl9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMixerControl9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMixerControl9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMixerControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlpha )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ float Alpha);
        
        HRESULT ( STDMETHODCALLTYPE *GetAlpha )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ float *pAlpha);
        
        HRESULT ( STDMETHODCALLTYPE *SetZOrder )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ DWORD dwZ);
        
        HRESULT ( STDMETHODCALLTYPE *GetZOrder )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ DWORD *pZ);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputRect )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ const VMR9NormalizedRect *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutputRect )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ VMR9NormalizedRect *pRect);
        
        HRESULT ( STDMETHODCALLTYPE *SetBackgroundClr )( 
            IVMRMixerControl9 * This,
            /* [in] */ COLORREF ClrBkg);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackgroundClr )( 
            IVMRMixerControl9 * This,
            /* [in] */ COLORREF *lpClrBkg);
        
        HRESULT ( STDMETHODCALLTYPE *SetMixingPrefs )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwMixerPrefs);
        
        HRESULT ( STDMETHODCALLTYPE *GetMixingPrefs )( 
            IVMRMixerControl9 * This,
            /* [out] */ DWORD *pdwMixerPrefs);
        
        HRESULT ( STDMETHODCALLTYPE *SetProcAmpControl )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ VMR9ProcAmpControl *lpClrControl);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcAmpControl )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out][in] */ VMR9ProcAmpControl *lpClrControl);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcAmpControlRange )( 
            IVMRMixerControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out][in] */ VMR9ProcAmpControlRange *lpClrControl);
        
        END_INTERFACE
    } IVMRMixerControl9Vtbl;

    interface IVMRMixerControl9
    {
        CONST_VTBL struct IVMRMixerControl9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMixerControl9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMixerControl9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMixerControl9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMixerControl9_SetAlpha(This,dwStreamID,Alpha)	\
    (This)->lpVtbl -> SetAlpha(This,dwStreamID,Alpha)

#define IVMRMixerControl9_GetAlpha(This,dwStreamID,pAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,dwStreamID,pAlpha)

#define IVMRMixerControl9_SetZOrder(This,dwStreamID,dwZ)	\
    (This)->lpVtbl -> SetZOrder(This,dwStreamID,dwZ)

#define IVMRMixerControl9_GetZOrder(This,dwStreamID,pZ)	\
    (This)->lpVtbl -> GetZOrder(This,dwStreamID,pZ)

#define IVMRMixerControl9_SetOutputRect(This,dwStreamID,pRect)	\
    (This)->lpVtbl -> SetOutputRect(This,dwStreamID,pRect)

#define IVMRMixerControl9_GetOutputRect(This,dwStreamID,pRect)	\
    (This)->lpVtbl -> GetOutputRect(This,dwStreamID,pRect)

#define IVMRMixerControl9_SetBackgroundClr(This,ClrBkg)	\
    (This)->lpVtbl -> SetBackgroundClr(This,ClrBkg)

#define IVMRMixerControl9_GetBackgroundClr(This,lpClrBkg)	\
    (This)->lpVtbl -> GetBackgroundClr(This,lpClrBkg)

#define IVMRMixerControl9_SetMixingPrefs(This,dwMixerPrefs)	\
    (This)->lpVtbl -> SetMixingPrefs(This,dwMixerPrefs)

#define IVMRMixerControl9_GetMixingPrefs(This,pdwMixerPrefs)	\
    (This)->lpVtbl -> GetMixingPrefs(This,pdwMixerPrefs)

#define IVMRMixerControl9_SetProcAmpControl(This,dwStreamID,lpClrControl)	\
    (This)->lpVtbl -> SetProcAmpControl(This,dwStreamID,lpClrControl)

#define IVMRMixerControl9_GetProcAmpControl(This,dwStreamID,lpClrControl)	\
    (This)->lpVtbl -> GetProcAmpControl(This,dwStreamID,lpClrControl)

#define IVMRMixerControl9_GetProcAmpControlRange(This,dwStreamID,lpClrControl)	\
    (This)->lpVtbl -> GetProcAmpControlRange(This,dwStreamID,lpClrControl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetAlpha_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ float Alpha);


void __RPC_STUB IVMRMixerControl9_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetAlpha_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ float *pAlpha);


void __RPC_STUB IVMRMixerControl9_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetZOrder_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ DWORD dwZ);


void __RPC_STUB IVMRMixerControl9_SetZOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetZOrder_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ DWORD *pZ);


void __RPC_STUB IVMRMixerControl9_GetZOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetOutputRect_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ const VMR9NormalizedRect *pRect);


void __RPC_STUB IVMRMixerControl9_SetOutputRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetOutputRect_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ VMR9NormalizedRect *pRect);


void __RPC_STUB IVMRMixerControl9_GetOutputRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetBackgroundClr_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ COLORREF ClrBkg);


void __RPC_STUB IVMRMixerControl9_SetBackgroundClr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetBackgroundClr_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ COLORREF *lpClrBkg);


void __RPC_STUB IVMRMixerControl9_GetBackgroundClr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetMixingPrefs_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwMixerPrefs);


void __RPC_STUB IVMRMixerControl9_SetMixingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetMixingPrefs_Proxy( 
    IVMRMixerControl9 * This,
    /* [out] */ DWORD *pdwMixerPrefs);


void __RPC_STUB IVMRMixerControl9_GetMixingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_SetProcAmpControl_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ VMR9ProcAmpControl *lpClrControl);


void __RPC_STUB IVMRMixerControl9_SetProcAmpControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetProcAmpControl_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out][in] */ VMR9ProcAmpControl *lpClrControl);


void __RPC_STUB IVMRMixerControl9_GetProcAmpControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerControl9_GetProcAmpControlRange_Proxy( 
    IVMRMixerControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out][in] */ VMR9ProcAmpControlRange *lpClrControl);


void __RPC_STUB IVMRMixerControl9_GetProcAmpControlRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMixerControl9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0013 */
/* [local] */ 

typedef struct _VMR9AlphaBitmap
    {
    DWORD dwFlags;
    HDC hdc;
    IDirect3DSurface9 *pDDS;
    RECT rSrc;
    VMR9NormalizedRect rDest;
    FLOAT fAlpha;
    COLORREF clrSrcKey;
    DWORD dwFilterMode;
    } 	VMR9AlphaBitmap;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0013_0001
    {	VMR9AlphaBitmap_Disable	= 0x1,
	VMR9AlphaBitmap_hDC	= 0x2,
	VMR9AlphaBitmap_EntireDDS	= 0x4,
	VMR9AlphaBitmap_SrcColorKey	= 0x8,
	VMR9AlphaBitmap_SrcRect	= 0x10,
	VMR9AlphaBitmap_FilterMode	= 0x20
    } 	VMR9AlphaBitmapFlags;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0013_v0_0_s_ifspec;

#ifndef __IVMRMixerBitmap9_INTERFACE_DEFINED__
#define __IVMRMixerBitmap9_INTERFACE_DEFINED__

/* interface IVMRMixerBitmap9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRMixerBitmap9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ced175e5-1935-4820-81bd-ff6ad00c9108")
    IVMRMixerBitmap9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAlphaBitmap( 
            /* [in] */ const VMR9AlphaBitmap *pBmpParms) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateAlphaBitmapParameters( 
            /* [in] */ const VMR9AlphaBitmap *pBmpParms) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlphaBitmapParameters( 
            /* [out] */ VMR9AlphaBitmap *pBmpParms) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMixerBitmap9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMixerBitmap9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMixerBitmap9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMixerBitmap9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlphaBitmap )( 
            IVMRMixerBitmap9 * This,
            /* [in] */ const VMR9AlphaBitmap *pBmpParms);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateAlphaBitmapParameters )( 
            IVMRMixerBitmap9 * This,
            /* [in] */ const VMR9AlphaBitmap *pBmpParms);
        
        HRESULT ( STDMETHODCALLTYPE *GetAlphaBitmapParameters )( 
            IVMRMixerBitmap9 * This,
            /* [out] */ VMR9AlphaBitmap *pBmpParms);
        
        END_INTERFACE
    } IVMRMixerBitmap9Vtbl;

    interface IVMRMixerBitmap9
    {
        CONST_VTBL struct IVMRMixerBitmap9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMixerBitmap9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMixerBitmap9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMixerBitmap9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMixerBitmap9_SetAlphaBitmap(This,pBmpParms)	\
    (This)->lpVtbl -> SetAlphaBitmap(This,pBmpParms)

#define IVMRMixerBitmap9_UpdateAlphaBitmapParameters(This,pBmpParms)	\
    (This)->lpVtbl -> UpdateAlphaBitmapParameters(This,pBmpParms)

#define IVMRMixerBitmap9_GetAlphaBitmapParameters(This,pBmpParms)	\
    (This)->lpVtbl -> GetAlphaBitmapParameters(This,pBmpParms)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMixerBitmap9_SetAlphaBitmap_Proxy( 
    IVMRMixerBitmap9 * This,
    /* [in] */ const VMR9AlphaBitmap *pBmpParms);


void __RPC_STUB IVMRMixerBitmap9_SetAlphaBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerBitmap9_UpdateAlphaBitmapParameters_Proxy( 
    IVMRMixerBitmap9 * This,
    /* [in] */ const VMR9AlphaBitmap *pBmpParms);


void __RPC_STUB IVMRMixerBitmap9_UpdateAlphaBitmapParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMixerBitmap9_GetAlphaBitmapParameters_Proxy( 
    IVMRMixerBitmap9 * This,
    /* [out] */ VMR9AlphaBitmap *pBmpParms);


void __RPC_STUB IVMRMixerBitmap9_GetAlphaBitmapParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMixerBitmap9_INTERFACE_DEFINED__ */


#ifndef __IVMRSurface9_INTERFACE_DEFINED__
#define __IVMRSurface9_INTERFACE_DEFINED__

/* interface IVMRSurface9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRSurface9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dfc581a1-6e1f-4c3a-8d0a-5e9792ea2afc")
    IVMRSurface9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsSurfaceLocked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LockSurface( 
            /* [out] */ BYTE **lpSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnlockSurface( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [out] */ IDirect3DSurface9 **lplpSurface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRSurface9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRSurface9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRSurface9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRSurface9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSurfaceLocked )( 
            IVMRSurface9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *LockSurface )( 
            IVMRSurface9 * This,
            /* [out] */ BYTE **lpSurface);
        
        HRESULT ( STDMETHODCALLTYPE *UnlockSurface )( 
            IVMRSurface9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSurface )( 
            IVMRSurface9 * This,
            /* [out] */ IDirect3DSurface9 **lplpSurface);
        
        END_INTERFACE
    } IVMRSurface9Vtbl;

    interface IVMRSurface9
    {
        CONST_VTBL struct IVMRSurface9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRSurface9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRSurface9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRSurface9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRSurface9_IsSurfaceLocked(This)	\
    (This)->lpVtbl -> IsSurfaceLocked(This)

#define IVMRSurface9_LockSurface(This,lpSurface)	\
    (This)->lpVtbl -> LockSurface(This,lpSurface)

#define IVMRSurface9_UnlockSurface(This)	\
    (This)->lpVtbl -> UnlockSurface(This)

#define IVMRSurface9_GetSurface(This,lplpSurface)	\
    (This)->lpVtbl -> GetSurface(This,lplpSurface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRSurface9_IsSurfaceLocked_Proxy( 
    IVMRSurface9 * This);


void __RPC_STUB IVMRSurface9_IsSurfaceLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface9_LockSurface_Proxy( 
    IVMRSurface9 * This,
    /* [out] */ BYTE **lpSurface);


void __RPC_STUB IVMRSurface9_LockSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface9_UnlockSurface_Proxy( 
    IVMRSurface9 * This);


void __RPC_STUB IVMRSurface9_UnlockSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRSurface9_GetSurface_Proxy( 
    IVMRSurface9 * This,
    /* [out] */ IDirect3DSurface9 **lplpSurface);


void __RPC_STUB IVMRSurface9_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRSurface9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0015 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0015_0001
    {	RenderPrefs9_DoNotRenderBorder	= 0x1,
	RenderPrefs9_Mask	= 0x1
    } 	VMR9RenderPrefs;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0015_v0_0_s_ifspec;

#ifndef __IVMRImagePresenterConfig9_INTERFACE_DEFINED__
#define __IVMRImagePresenterConfig9_INTERFACE_DEFINED__

/* interface IVMRImagePresenterConfig9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImagePresenterConfig9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45c15cab-6e22-420a-8043-ae1f0ac02c7d")
    IVMRImagePresenterConfig9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRenderingPrefs( 
            /* [in] */ DWORD dwRenderFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderingPrefs( 
            /* [out] */ DWORD *dwRenderFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImagePresenterConfig9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImagePresenterConfig9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImagePresenterConfig9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImagePresenterConfig9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingPrefs )( 
            IVMRImagePresenterConfig9 * This,
            /* [in] */ DWORD dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingPrefs )( 
            IVMRImagePresenterConfig9 * This,
            /* [out] */ DWORD *dwRenderFlags);
        
        END_INTERFACE
    } IVMRImagePresenterConfig9Vtbl;

    interface IVMRImagePresenterConfig9
    {
        CONST_VTBL struct IVMRImagePresenterConfig9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImagePresenterConfig9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImagePresenterConfig9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImagePresenterConfig9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImagePresenterConfig9_SetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> SetRenderingPrefs(This,dwRenderFlags)

#define IVMRImagePresenterConfig9_GetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> GetRenderingPrefs(This,dwRenderFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImagePresenterConfig9_SetRenderingPrefs_Proxy( 
    IVMRImagePresenterConfig9 * This,
    /* [in] */ DWORD dwRenderFlags);


void __RPC_STUB IVMRImagePresenterConfig9_SetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImagePresenterConfig9_GetRenderingPrefs_Proxy( 
    IVMRImagePresenterConfig9 * This,
    /* [out] */ DWORD *dwRenderFlags);


void __RPC_STUB IVMRImagePresenterConfig9_GetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImagePresenterConfig9_INTERFACE_DEFINED__ */


#ifndef __IVMRVideoStreamControl9_INTERFACE_DEFINED__
#define __IVMRVideoStreamControl9_INTERFACE_DEFINED__

/* interface IVMRVideoStreamControl9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRVideoStreamControl9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d0cfe38b-93e7-4772-8957-0400c49a4485")
    IVMRVideoStreamControl9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetStreamActiveState( 
            /* [in] */ BOOL fActive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamActiveState( 
            /* [out] */ BOOL *lpfActive) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRVideoStreamControl9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRVideoStreamControl9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRVideoStreamControl9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRVideoStreamControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetStreamActiveState )( 
            IVMRVideoStreamControl9 * This,
            /* [in] */ BOOL fActive);
        
        HRESULT ( STDMETHODCALLTYPE *GetStreamActiveState )( 
            IVMRVideoStreamControl9 * This,
            /* [out] */ BOOL *lpfActive);
        
        END_INTERFACE
    } IVMRVideoStreamControl9Vtbl;

    interface IVMRVideoStreamControl9
    {
        CONST_VTBL struct IVMRVideoStreamControl9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRVideoStreamControl9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRVideoStreamControl9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRVideoStreamControl9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRVideoStreamControl9_SetStreamActiveState(This,fActive)	\
    (This)->lpVtbl -> SetStreamActiveState(This,fActive)

#define IVMRVideoStreamControl9_GetStreamActiveState(This,lpfActive)	\
    (This)->lpVtbl -> GetStreamActiveState(This,lpfActive)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl9_SetStreamActiveState_Proxy( 
    IVMRVideoStreamControl9 * This,
    /* [in] */ BOOL fActive);


void __RPC_STUB IVMRVideoStreamControl9_SetStreamActiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRVideoStreamControl9_GetStreamActiveState_Proxy( 
    IVMRVideoStreamControl9 * This,
    /* [out] */ BOOL *lpfActive);


void __RPC_STUB IVMRVideoStreamControl9_GetStreamActiveState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRVideoStreamControl9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0017 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0017_0001
    {	VMR9Mode_Windowed	= 0x1,
	VMR9Mode_Windowless	= 0x2,
	VMR9Mode_Renderless	= 0x4,
	VMR9Mode_Mask	= 0x7
    } 	VMR9Mode;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0017_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0017_v0_0_s_ifspec;

#ifndef __IVMRFilterConfig9_INTERFACE_DEFINED__
#define __IVMRFilterConfig9_INTERFACE_DEFINED__

/* interface IVMRFilterConfig9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRFilterConfig9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5a804648-4f66-4867-9c43-4f5c822cf1b8")
    IVMRFilterConfig9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetImageCompositor( 
            /* [in] */ IVMRImageCompositor9 *lpVMRImgCompositor) = 0;
        
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

    typedef struct IVMRFilterConfig9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRFilterConfig9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRFilterConfig9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRFilterConfig9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageCompositor )( 
            IVMRFilterConfig9 * This,
            /* [in] */ IVMRImageCompositor9 *lpVMRImgCompositor);
        
        HRESULT ( STDMETHODCALLTYPE *SetNumberOfStreams )( 
            IVMRFilterConfig9 * This,
            /* [in] */ DWORD dwMaxStreams);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfStreams )( 
            IVMRFilterConfig9 * This,
            /* [out] */ DWORD *pdwMaxStreams);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingPrefs )( 
            IVMRFilterConfig9 * This,
            /* [in] */ DWORD dwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingPrefs )( 
            IVMRFilterConfig9 * This,
            /* [out] */ DWORD *pdwRenderFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderingMode )( 
            IVMRFilterConfig9 * This,
            /* [in] */ DWORD Mode);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderingMode )( 
            IVMRFilterConfig9 * This,
            /* [out] */ DWORD *pMode);
        
        END_INTERFACE
    } IVMRFilterConfig9Vtbl;

    interface IVMRFilterConfig9
    {
        CONST_VTBL struct IVMRFilterConfig9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRFilterConfig9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRFilterConfig9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRFilterConfig9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRFilterConfig9_SetImageCompositor(This,lpVMRImgCompositor)	\
    (This)->lpVtbl -> SetImageCompositor(This,lpVMRImgCompositor)

#define IVMRFilterConfig9_SetNumberOfStreams(This,dwMaxStreams)	\
    (This)->lpVtbl -> SetNumberOfStreams(This,dwMaxStreams)

#define IVMRFilterConfig9_GetNumberOfStreams(This,pdwMaxStreams)	\
    (This)->lpVtbl -> GetNumberOfStreams(This,pdwMaxStreams)

#define IVMRFilterConfig9_SetRenderingPrefs(This,dwRenderFlags)	\
    (This)->lpVtbl -> SetRenderingPrefs(This,dwRenderFlags)

#define IVMRFilterConfig9_GetRenderingPrefs(This,pdwRenderFlags)	\
    (This)->lpVtbl -> GetRenderingPrefs(This,pdwRenderFlags)

#define IVMRFilterConfig9_SetRenderingMode(This,Mode)	\
    (This)->lpVtbl -> SetRenderingMode(This,Mode)

#define IVMRFilterConfig9_GetRenderingMode(This,pMode)	\
    (This)->lpVtbl -> GetRenderingMode(This,pMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_SetImageCompositor_Proxy( 
    IVMRFilterConfig9 * This,
    /* [in] */ IVMRImageCompositor9 *lpVMRImgCompositor);


void __RPC_STUB IVMRFilterConfig9_SetImageCompositor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_SetNumberOfStreams_Proxy( 
    IVMRFilterConfig9 * This,
    /* [in] */ DWORD dwMaxStreams);


void __RPC_STUB IVMRFilterConfig9_SetNumberOfStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_GetNumberOfStreams_Proxy( 
    IVMRFilterConfig9 * This,
    /* [out] */ DWORD *pdwMaxStreams);


void __RPC_STUB IVMRFilterConfig9_GetNumberOfStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_SetRenderingPrefs_Proxy( 
    IVMRFilterConfig9 * This,
    /* [in] */ DWORD dwRenderFlags);


void __RPC_STUB IVMRFilterConfig9_SetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_GetRenderingPrefs_Proxy( 
    IVMRFilterConfig9 * This,
    /* [out] */ DWORD *pdwRenderFlags);


void __RPC_STUB IVMRFilterConfig9_GetRenderingPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_SetRenderingMode_Proxy( 
    IVMRFilterConfig9 * This,
    /* [in] */ DWORD Mode);


void __RPC_STUB IVMRFilterConfig9_SetRenderingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRFilterConfig9_GetRenderingMode_Proxy( 
    IVMRFilterConfig9 * This,
    /* [out] */ DWORD *pMode);


void __RPC_STUB IVMRFilterConfig9_GetRenderingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRFilterConfig9_INTERFACE_DEFINED__ */


#ifndef __IVMRAspectRatioControl9_INTERFACE_DEFINED__
#define __IVMRAspectRatioControl9_INTERFACE_DEFINED__

/* interface IVMRAspectRatioControl9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRAspectRatioControl9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00d96c29-bbde-4efc-9901-bb5036392146")
    IVMRAspectRatioControl9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAspectRatioMode( 
            /* [out] */ LPDWORD lpdwARMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAspectRatioMode( 
            /* [in] */ DWORD dwARMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRAspectRatioControl9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRAspectRatioControl9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRAspectRatioControl9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRAspectRatioControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAspectRatioMode )( 
            IVMRAspectRatioControl9 * This,
            /* [out] */ LPDWORD lpdwARMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetAspectRatioMode )( 
            IVMRAspectRatioControl9 * This,
            /* [in] */ DWORD dwARMode);
        
        END_INTERFACE
    } IVMRAspectRatioControl9Vtbl;

    interface IVMRAspectRatioControl9
    {
        CONST_VTBL struct IVMRAspectRatioControl9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRAspectRatioControl9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRAspectRatioControl9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRAspectRatioControl9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRAspectRatioControl9_GetAspectRatioMode(This,lpdwARMode)	\
    (This)->lpVtbl -> GetAspectRatioMode(This,lpdwARMode)

#define IVMRAspectRatioControl9_SetAspectRatioMode(This,dwARMode)	\
    (This)->lpVtbl -> SetAspectRatioMode(This,dwARMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRAspectRatioControl9_GetAspectRatioMode_Proxy( 
    IVMRAspectRatioControl9 * This,
    /* [out] */ LPDWORD lpdwARMode);


void __RPC_STUB IVMRAspectRatioControl9_GetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRAspectRatioControl9_SetAspectRatioMode_Proxy( 
    IVMRAspectRatioControl9 * This,
    /* [in] */ DWORD dwARMode);


void __RPC_STUB IVMRAspectRatioControl9_SetAspectRatioMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRAspectRatioControl9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0019 */
/* [local] */ 

typedef struct _VMR9MonitorInfo
    {
    UINT uDevID;
    RECT rcMonitor;
    HMONITOR hMon;
    DWORD dwFlags;
    wchar_t szDevice[ 32 ];
    wchar_t szDescription[ 512 ];
    LARGE_INTEGER liDriverVersion;
    DWORD dwVendorId;
    DWORD dwDeviceId;
    DWORD dwSubSysId;
    DWORD dwRevision;
    } 	VMR9MonitorInfo;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0019_v0_0_s_ifspec;

#ifndef __IVMRMonitorConfig9_INTERFACE_DEFINED__
#define __IVMRMonitorConfig9_INTERFACE_DEFINED__

/* interface IVMRMonitorConfig9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRMonitorConfig9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("46c2e457-8ba0-4eef-b80b-0680f0978749")
    IVMRMonitorConfig9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMonitor( 
            /* [in] */ UINT uDev) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMonitor( 
            /* [out] */ UINT *puDev) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultMonitor( 
            /* [in] */ UINT uDev) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultMonitor( 
            /* [out] */ UINT *puDev) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailableMonitors( 
            /* [size_is][out] */ VMR9MonitorInfo *pInfo,
            /* [in] */ DWORD dwMaxInfoArraySize,
            /* [out] */ DWORD *pdwNumDevices) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRMonitorConfig9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRMonitorConfig9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRMonitorConfig9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRMonitorConfig9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMonitor )( 
            IVMRMonitorConfig9 * This,
            /* [in] */ UINT uDev);
        
        HRESULT ( STDMETHODCALLTYPE *GetMonitor )( 
            IVMRMonitorConfig9 * This,
            /* [out] */ UINT *puDev);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultMonitor )( 
            IVMRMonitorConfig9 * This,
            /* [in] */ UINT uDev);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultMonitor )( 
            IVMRMonitorConfig9 * This,
            /* [out] */ UINT *puDev);
        
        HRESULT ( STDMETHODCALLTYPE *GetAvailableMonitors )( 
            IVMRMonitorConfig9 * This,
            /* [size_is][out] */ VMR9MonitorInfo *pInfo,
            /* [in] */ DWORD dwMaxInfoArraySize,
            /* [out] */ DWORD *pdwNumDevices);
        
        END_INTERFACE
    } IVMRMonitorConfig9Vtbl;

    interface IVMRMonitorConfig9
    {
        CONST_VTBL struct IVMRMonitorConfig9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRMonitorConfig9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRMonitorConfig9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRMonitorConfig9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRMonitorConfig9_SetMonitor(This,uDev)	\
    (This)->lpVtbl -> SetMonitor(This,uDev)

#define IVMRMonitorConfig9_GetMonitor(This,puDev)	\
    (This)->lpVtbl -> GetMonitor(This,puDev)

#define IVMRMonitorConfig9_SetDefaultMonitor(This,uDev)	\
    (This)->lpVtbl -> SetDefaultMonitor(This,uDev)

#define IVMRMonitorConfig9_GetDefaultMonitor(This,puDev)	\
    (This)->lpVtbl -> GetDefaultMonitor(This,puDev)

#define IVMRMonitorConfig9_GetAvailableMonitors(This,pInfo,dwMaxInfoArraySize,pdwNumDevices)	\
    (This)->lpVtbl -> GetAvailableMonitors(This,pInfo,dwMaxInfoArraySize,pdwNumDevices)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRMonitorConfig9_SetMonitor_Proxy( 
    IVMRMonitorConfig9 * This,
    /* [in] */ UINT uDev);


void __RPC_STUB IVMRMonitorConfig9_SetMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig9_GetMonitor_Proxy( 
    IVMRMonitorConfig9 * This,
    /* [out] */ UINT *puDev);


void __RPC_STUB IVMRMonitorConfig9_GetMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig9_SetDefaultMonitor_Proxy( 
    IVMRMonitorConfig9 * This,
    /* [in] */ UINT uDev);


void __RPC_STUB IVMRMonitorConfig9_SetDefaultMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig9_GetDefaultMonitor_Proxy( 
    IVMRMonitorConfig9 * This,
    /* [out] */ UINT *puDev);


void __RPC_STUB IVMRMonitorConfig9_GetDefaultMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRMonitorConfig9_GetAvailableMonitors_Proxy( 
    IVMRMonitorConfig9 * This,
    /* [size_is][out] */ VMR9MonitorInfo *pInfo,
    /* [in] */ DWORD dwMaxInfoArraySize,
    /* [out] */ DWORD *pdwNumDevices);


void __RPC_STUB IVMRMonitorConfig9_GetAvailableMonitors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRMonitorConfig9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0020 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_vmr9_0020_0001
    {	DeinterlacePref9_NextBest	= 0x1,
	DeinterlacePref9_BOB	= 0x2,
	DeinterlacePref9_Weave	= 0x4,
	DeinterlacePref9_Mask	= 0x7
    } 	VMR9DeinterlacePrefs;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_vmr9_0020_0002
    {	DeinterlaceTech9_Unknown	= 0,
	DeinterlaceTech9_BOBLineReplicate	= 0x1,
	DeinterlaceTech9_BOBVerticalStretch	= 0x2,
	DeinterlaceTech9_MedianFiltering	= 0x4,
	DeinterlaceTech9_EdgeFiltering	= 0x10,
	DeinterlaceTech9_FieldAdaptive	= 0x20,
	DeinterlaceTech9_PixelAdaptive	= 0x40,
	DeinterlaceTech9_MotionVectorSteered	= 0x80
    } 	VMR9DeinterlaceTech;

typedef struct _VMR9Frequency
    {
    DWORD dwNumerator;
    DWORD dwDenominator;
    } 	VMR9Frequency;

typedef 
enum _VMR9_SampleFormat
    {	VMR9_SampleReserved	= 1,
	VMR9_SampleProgressiveFrame	= 2,
	VMR9_SampleFieldInterleavedEvenFirst	= 3,
	VMR9_SampleFieldInterleavedOddFirst	= 4,
	VMR9_SampleFieldSingleEven	= 5,
	VMR9_SampleFieldSingleOdd	= 6
    } 	VMR9_SampleFormat;

typedef struct _VMR9VideoDesc
    {
    DWORD dwSize;
    DWORD dwSampleWidth;
    DWORD dwSampleHeight;
    VMR9_SampleFormat SampleFormat;
    DWORD dwFourCC;
    VMR9Frequency InputSampleFreq;
    VMR9Frequency OutputFrameFreq;
    } 	VMR9VideoDesc;

typedef struct _VMR9DeinterlaceCaps
    {
    DWORD dwSize;
    DWORD dwNumPreviousOutputFrames;
    DWORD dwNumForwardRefSamples;
    DWORD dwNumBackwardRefSamples;
    VMR9DeinterlaceTech DeinterlaceTechnology;
    } 	VMR9DeinterlaceCaps;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0020_v0_0_s_ifspec;

#ifndef __IVMRDeinterlaceControl9_INTERFACE_DEFINED__
#define __IVMRDeinterlaceControl9_INTERFACE_DEFINED__

/* interface IVMRDeinterlaceControl9 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_IVMRDeinterlaceControl9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a215fb8d-13c2-4f7f-993c-003d6271a459")
    IVMRDeinterlaceControl9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfDeinterlaceModes( 
            /* [in] */ VMR9VideoDesc *lpVideoDescription,
            /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
            /* [out] */ LPGUID lpDeinterlaceModes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeinterlaceModeCaps( 
            /* [in] */ LPGUID lpDeinterlaceMode,
            /* [in] */ VMR9VideoDesc *lpVideoDescription,
            /* [out] */ VMR9DeinterlaceCaps *lpDeinterlaceCaps) = 0;
        
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

    typedef struct IVMRDeinterlaceControl9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRDeinterlaceControl9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRDeinterlaceControl9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfDeinterlaceModes )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ VMR9VideoDesc *lpVideoDescription,
            /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
            /* [out] */ LPGUID lpDeinterlaceModes);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlaceModeCaps )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ LPGUID lpDeinterlaceMode,
            /* [in] */ VMR9VideoDesc *lpVideoDescription,
            /* [out] */ VMR9DeinterlaceCaps *lpDeinterlaceCaps);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlaceMode )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetDeinterlaceMode )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [in] */ LPGUID lpDeinterlaceMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetDeinterlacePrefs )( 
            IVMRDeinterlaceControl9 * This,
            /* [out] */ LPDWORD lpdwDeinterlacePrefs);
        
        HRESULT ( STDMETHODCALLTYPE *SetDeinterlacePrefs )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ DWORD dwDeinterlacePrefs);
        
        HRESULT ( STDMETHODCALLTYPE *GetActualDeinterlaceMode )( 
            IVMRDeinterlaceControl9 * This,
            /* [in] */ DWORD dwStreamID,
            /* [out] */ LPGUID lpDeinterlaceMode);
        
        END_INTERFACE
    } IVMRDeinterlaceControl9Vtbl;

    interface IVMRDeinterlaceControl9
    {
        CONST_VTBL struct IVMRDeinterlaceControl9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRDeinterlaceControl9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRDeinterlaceControl9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRDeinterlaceControl9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRDeinterlaceControl9_GetNumberOfDeinterlaceModes(This,lpVideoDescription,lpdwNumDeinterlaceModes,lpDeinterlaceModes)	\
    (This)->lpVtbl -> GetNumberOfDeinterlaceModes(This,lpVideoDescription,lpdwNumDeinterlaceModes,lpDeinterlaceModes)

#define IVMRDeinterlaceControl9_GetDeinterlaceModeCaps(This,lpDeinterlaceMode,lpVideoDescription,lpDeinterlaceCaps)	\
    (This)->lpVtbl -> GetDeinterlaceModeCaps(This,lpDeinterlaceMode,lpVideoDescription,lpDeinterlaceCaps)

#define IVMRDeinterlaceControl9_GetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> GetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#define IVMRDeinterlaceControl9_SetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> SetDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#define IVMRDeinterlaceControl9_GetDeinterlacePrefs(This,lpdwDeinterlacePrefs)	\
    (This)->lpVtbl -> GetDeinterlacePrefs(This,lpdwDeinterlacePrefs)

#define IVMRDeinterlaceControl9_SetDeinterlacePrefs(This,dwDeinterlacePrefs)	\
    (This)->lpVtbl -> SetDeinterlacePrefs(This,dwDeinterlacePrefs)

#define IVMRDeinterlaceControl9_GetActualDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)	\
    (This)->lpVtbl -> GetActualDeinterlaceMode(This,dwStreamID,lpDeinterlaceMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_GetNumberOfDeinterlaceModes_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ VMR9VideoDesc *lpVideoDescription,
    /* [out][in] */ LPDWORD lpdwNumDeinterlaceModes,
    /* [out] */ LPGUID lpDeinterlaceModes);


void __RPC_STUB IVMRDeinterlaceControl9_GetNumberOfDeinterlaceModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_GetDeinterlaceModeCaps_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ LPGUID lpDeinterlaceMode,
    /* [in] */ VMR9VideoDesc *lpVideoDescription,
    /* [out] */ VMR9DeinterlaceCaps *lpDeinterlaceCaps);


void __RPC_STUB IVMRDeinterlaceControl9_GetDeinterlaceModeCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_GetDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl9_GetDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_SetDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [in] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl9_SetDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_GetDeinterlacePrefs_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [out] */ LPDWORD lpdwDeinterlacePrefs);


void __RPC_STUB IVMRDeinterlaceControl9_GetDeinterlacePrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_SetDeinterlacePrefs_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ DWORD dwDeinterlacePrefs);


void __RPC_STUB IVMRDeinterlaceControl9_SetDeinterlacePrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRDeinterlaceControl9_GetActualDeinterlaceMode_Proxy( 
    IVMRDeinterlaceControl9 * This,
    /* [in] */ DWORD dwStreamID,
    /* [out] */ LPGUID lpDeinterlaceMode);


void __RPC_STUB IVMRDeinterlaceControl9_GetActualDeinterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRDeinterlaceControl9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_vmr9_0021 */
/* [local] */ 

typedef struct _VMR9VideoStreamInfo
    {
    IDirect3DSurface9 *pddsVideoSurface;
    DWORD dwWidth;
    DWORD dwHeight;
    DWORD dwStrmID;
    FLOAT fAlpha;
    VMR9NormalizedRect rNormal;
    REFERENCE_TIME rtStart;
    REFERENCE_TIME rtEnd;
    VMR9_SampleFormat SampleFormat;
    } 	VMR9VideoStreamInfo;



extern RPC_IF_HANDLE __MIDL_itf_vmr9_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vmr9_0021_v0_0_s_ifspec;

#ifndef __IVMRImageCompositor9_INTERFACE_DEFINED__
#define __IVMRImageCompositor9_INTERFACE_DEFINED__

/* interface IVMRImageCompositor9 */
/* [unique][helpstring][uuid][local][object][local] */ 


EXTERN_C const IID IID_IVMRImageCompositor9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4a5c89eb-df51-4654-ac2a-e48e02bbabf6")
    IVMRImageCompositor9 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitCompositionDevice( 
            /* [in] */ IUnknown *pD3DDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TermCompositionDevice( 
            /* [in] */ IUnknown *pD3DDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStreamMediaType( 
            /* [in] */ DWORD dwStrmID,
            /* [in] */ AM_MEDIA_TYPE *pmt,
            /* [in] */ BOOL fTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompositeImage( 
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ IDirect3DSurface9 *pddsRenderTarget,
            /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd,
            /* [in] */ D3DCOLOR dwClrBkGnd,
            /* [in] */ VMR9VideoStreamInfo *pVideoStreamInfo,
            /* [in] */ UINT cStreams) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMRImageCompositor9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVMRImageCompositor9 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVMRImageCompositor9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVMRImageCompositor9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitCompositionDevice )( 
            IVMRImageCompositor9 * This,
            /* [in] */ IUnknown *pD3DDevice);
        
        HRESULT ( STDMETHODCALLTYPE *TermCompositionDevice )( 
            IVMRImageCompositor9 * This,
            /* [in] */ IUnknown *pD3DDevice);
        
        HRESULT ( STDMETHODCALLTYPE *SetStreamMediaType )( 
            IVMRImageCompositor9 * This,
            /* [in] */ DWORD dwStrmID,
            /* [in] */ AM_MEDIA_TYPE *pmt,
            /* [in] */ BOOL fTexture);
        
        HRESULT ( STDMETHODCALLTYPE *CompositeImage )( 
            IVMRImageCompositor9 * This,
            /* [in] */ IUnknown *pD3DDevice,
            /* [in] */ IDirect3DSurface9 *pddsRenderTarget,
            /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd,
            /* [in] */ D3DCOLOR dwClrBkGnd,
            /* [in] */ VMR9VideoStreamInfo *pVideoStreamInfo,
            /* [in] */ UINT cStreams);
        
        END_INTERFACE
    } IVMRImageCompositor9Vtbl;

    interface IVMRImageCompositor9
    {
        CONST_VTBL struct IVMRImageCompositor9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMRImageCompositor9_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMRImageCompositor9_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMRImageCompositor9_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMRImageCompositor9_InitCompositionDevice(This,pD3DDevice)	\
    (This)->lpVtbl -> InitCompositionDevice(This,pD3DDevice)

#define IVMRImageCompositor9_TermCompositionDevice(This,pD3DDevice)	\
    (This)->lpVtbl -> TermCompositionDevice(This,pD3DDevice)

#define IVMRImageCompositor9_SetStreamMediaType(This,dwStrmID,pmt,fTexture)	\
    (This)->lpVtbl -> SetStreamMediaType(This,dwStrmID,pmt,fTexture)

#define IVMRImageCompositor9_CompositeImage(This,pD3DDevice,pddsRenderTarget,pmtRenderTarget,rtStart,rtEnd,dwClrBkGnd,pVideoStreamInfo,cStreams)	\
    (This)->lpVtbl -> CompositeImage(This,pD3DDevice,pddsRenderTarget,pmtRenderTarget,rtStart,rtEnd,dwClrBkGnd,pVideoStreamInfo,cStreams)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVMRImageCompositor9_InitCompositionDevice_Proxy( 
    IVMRImageCompositor9 * This,
    /* [in] */ IUnknown *pD3DDevice);


void __RPC_STUB IVMRImageCompositor9_InitCompositionDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor9_TermCompositionDevice_Proxy( 
    IVMRImageCompositor9 * This,
    /* [in] */ IUnknown *pD3DDevice);


void __RPC_STUB IVMRImageCompositor9_TermCompositionDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor9_SetStreamMediaType_Proxy( 
    IVMRImageCompositor9 * This,
    /* [in] */ DWORD dwStrmID,
    /* [in] */ AM_MEDIA_TYPE *pmt,
    /* [in] */ BOOL fTexture);


void __RPC_STUB IVMRImageCompositor9_SetStreamMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVMRImageCompositor9_CompositeImage_Proxy( 
    IVMRImageCompositor9 * This,
    /* [in] */ IUnknown *pD3DDevice,
    /* [in] */ IDirect3DSurface9 *pddsRenderTarget,
    /* [in] */ AM_MEDIA_TYPE *pmtRenderTarget,
    /* [in] */ REFERENCE_TIME rtStart,
    /* [in] */ REFERENCE_TIME rtEnd,
    /* [in] */ D3DCOLOR dwClrBkGnd,
    /* [in] */ VMR9VideoStreamInfo *pVideoStreamInfo,
    /* [in] */ UINT cStreams);


void __RPC_STUB IVMRImageCompositor9_CompositeImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMRImageCompositor9_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


