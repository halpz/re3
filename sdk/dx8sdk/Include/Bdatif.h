
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for bdatif.idl:
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

#ifndef __bdatif_h__
#define __bdatif_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBDA_TIF_REGISTRATION_FWD_DEFINED__
#define __IBDA_TIF_REGISTRATION_FWD_DEFINED__
typedef interface IBDA_TIF_REGISTRATION IBDA_TIF_REGISTRATION;
#endif 	/* __IBDA_TIF_REGISTRATION_FWD_DEFINED__ */


#ifndef __IMPEG2_TIF_CONTROL_FWD_DEFINED__
#define __IMPEG2_TIF_CONTROL_FWD_DEFINED__
typedef interface IMPEG2_TIF_CONTROL IMPEG2_TIF_CONTROL;
#endif 	/* __IMPEG2_TIF_CONTROL_FWD_DEFINED__ */


#ifndef __ITuneRequestInfo_FWD_DEFINED__
#define __ITuneRequestInfo_FWD_DEFINED__
typedef interface ITuneRequestInfo ITuneRequestInfo;
#endif 	/* __ITuneRequestInfo_FWD_DEFINED__ */


#ifndef __IGuideDataEvent_FWD_DEFINED__
#define __IGuideDataEvent_FWD_DEFINED__
typedef interface IGuideDataEvent IGuideDataEvent;
#endif 	/* __IGuideDataEvent_FWD_DEFINED__ */


#ifndef __IGuideDataProperty_FWD_DEFINED__
#define __IGuideDataProperty_FWD_DEFINED__
typedef interface IGuideDataProperty IGuideDataProperty;
#endif 	/* __IGuideDataProperty_FWD_DEFINED__ */


#ifndef __IEnumGuideDataProperties_FWD_DEFINED__
#define __IEnumGuideDataProperties_FWD_DEFINED__
typedef interface IEnumGuideDataProperties IEnumGuideDataProperties;
#endif 	/* __IEnumGuideDataProperties_FWD_DEFINED__ */


#ifndef __IEnumTuneRequests_FWD_DEFINED__
#define __IEnumTuneRequests_FWD_DEFINED__
typedef interface IEnumTuneRequests IEnumTuneRequests;
#endif 	/* __IEnumTuneRequests_FWD_DEFINED__ */


#ifndef __IGuideData_FWD_DEFINED__
#define __IGuideData_FWD_DEFINED__
typedef interface IGuideData IGuideData;
#endif 	/* __IGuideData_FWD_DEFINED__ */


#ifndef __IGuideDataLoader_FWD_DEFINED__
#define __IGuideDataLoader_FWD_DEFINED__
typedef interface IGuideDataLoader IGuideDataLoader;
#endif 	/* __IGuideDataLoader_FWD_DEFINED__ */


#ifndef __TIFLoad_FWD_DEFINED__
#define __TIFLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class TIFLoad TIFLoad;
#else
typedef struct TIFLoad TIFLoad;
#endif /* __cplusplus */

#endif 	/* __TIFLoad_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"
#include "tuner.h"
#include "bdaiface.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_bdatif_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1999-2002.
//
//--------------------------------------------------------------------------
#if ( _MSC_VER >= 800 )
#pragma warning(disable:4201)    /* Nameless struct/union */
#endif
#if ( _MSC_VER >= 1020 )
#pragma once
#endif





extern RPC_IF_HANDLE __MIDL_itf_bdatif_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_bdatif_0000_v0_0_s_ifspec;

#ifndef __IBDA_TIF_REGISTRATION_INTERFACE_DEFINED__
#define __IBDA_TIF_REGISTRATION_INTERFACE_DEFINED__

/* interface IBDA_TIF_REGISTRATION */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IBDA_TIF_REGISTRATION;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DFEF4A68-EE61-415f-9CCB-CD95F2F98A3A")
    IBDA_TIF_REGISTRATION : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegisterTIFEx( 
            /* [in] */ IPin *pTIFInputPin,
            /* [out][in] */ ULONG *ppvRegistrationContext,
            /* [out][in] */ IUnknown **ppMpeg2DataControl) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnregisterTIF( 
            /* [in] */ ULONG pvRegistrationContext) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBDA_TIF_REGISTRATIONVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBDA_TIF_REGISTRATION * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBDA_TIF_REGISTRATION * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBDA_TIF_REGISTRATION * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegisterTIFEx )( 
            IBDA_TIF_REGISTRATION * This,
            /* [in] */ IPin *pTIFInputPin,
            /* [out][in] */ ULONG *ppvRegistrationContext,
            /* [out][in] */ IUnknown **ppMpeg2DataControl);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnregisterTIF )( 
            IBDA_TIF_REGISTRATION * This,
            /* [in] */ ULONG pvRegistrationContext);
        
        END_INTERFACE
    } IBDA_TIF_REGISTRATIONVtbl;

    interface IBDA_TIF_REGISTRATION
    {
        CONST_VTBL struct IBDA_TIF_REGISTRATIONVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBDA_TIF_REGISTRATION_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBDA_TIF_REGISTRATION_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBDA_TIF_REGISTRATION_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBDA_TIF_REGISTRATION_RegisterTIFEx(This,pTIFInputPin,ppvRegistrationContext,ppMpeg2DataControl)	\
    (This)->lpVtbl -> RegisterTIFEx(This,pTIFInputPin,ppvRegistrationContext,ppMpeg2DataControl)

#define IBDA_TIF_REGISTRATION_UnregisterTIF(This,pvRegistrationContext)	\
    (This)->lpVtbl -> UnregisterTIF(This,pvRegistrationContext)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBDA_TIF_REGISTRATION_RegisterTIFEx_Proxy( 
    IBDA_TIF_REGISTRATION * This,
    /* [in] */ IPin *pTIFInputPin,
    /* [out][in] */ ULONG *ppvRegistrationContext,
    /* [out][in] */ IUnknown **ppMpeg2DataControl);


void __RPC_STUB IBDA_TIF_REGISTRATION_RegisterTIFEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBDA_TIF_REGISTRATION_UnregisterTIF_Proxy( 
    IBDA_TIF_REGISTRATION * This,
    /* [in] */ ULONG pvRegistrationContext);


void __RPC_STUB IBDA_TIF_REGISTRATION_UnregisterTIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBDA_TIF_REGISTRATION_INTERFACE_DEFINED__ */


#ifndef __IMPEG2_TIF_CONTROL_INTERFACE_DEFINED__
#define __IMPEG2_TIF_CONTROL_INTERFACE_DEFINED__

/* interface IMPEG2_TIF_CONTROL */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPEG2_TIF_CONTROL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9BAC2F9-4149-4916-B2EF-FAA202326862")
    IMPEG2_TIF_CONTROL : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegisterTIF( 
            /* [in] */ IUnknown *pUnkTIF,
            /* [out][in] */ ULONG *ppvRegistrationContext) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnregisterTIF( 
            /* [in] */ ULONG pvRegistrationContext) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPIDs( 
            /* [in] */ ULONG ulcPIDs,
            /* [in] */ ULONG *pulPIDs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletePIDs( 
            /* [in] */ ULONG ulcPIDs,
            /* [in] */ ULONG *pulPIDs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPIDCount( 
            /* [out] */ ULONG *pulcPIDs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPIDs( 
            /* [out] */ ULONG *pulcPIDs,
            /* [out] */ ULONG *pulPIDs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEG2_TIF_CONTROLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPEG2_TIF_CONTROL * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPEG2_TIF_CONTROL * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPEG2_TIF_CONTROL * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RegisterTIF )( 
            IMPEG2_TIF_CONTROL * This,
            /* [in] */ IUnknown *pUnkTIF,
            /* [out][in] */ ULONG *ppvRegistrationContext);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnregisterTIF )( 
            IMPEG2_TIF_CONTROL * This,
            /* [in] */ ULONG pvRegistrationContext);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPIDs )( 
            IMPEG2_TIF_CONTROL * This,
            /* [in] */ ULONG ulcPIDs,
            /* [in] */ ULONG *pulPIDs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletePIDs )( 
            IMPEG2_TIF_CONTROL * This,
            /* [in] */ ULONG ulcPIDs,
            /* [in] */ ULONG *pulPIDs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPIDCount )( 
            IMPEG2_TIF_CONTROL * This,
            /* [out] */ ULONG *pulcPIDs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPIDs )( 
            IMPEG2_TIF_CONTROL * This,
            /* [out] */ ULONG *pulcPIDs,
            /* [out] */ ULONG *pulPIDs);
        
        END_INTERFACE
    } IMPEG2_TIF_CONTROLVtbl;

    interface IMPEG2_TIF_CONTROL
    {
        CONST_VTBL struct IMPEG2_TIF_CONTROLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEG2_TIF_CONTROL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEG2_TIF_CONTROL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEG2_TIF_CONTROL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEG2_TIF_CONTROL_RegisterTIF(This,pUnkTIF,ppvRegistrationContext)	\
    (This)->lpVtbl -> RegisterTIF(This,pUnkTIF,ppvRegistrationContext)

#define IMPEG2_TIF_CONTROL_UnregisterTIF(This,pvRegistrationContext)	\
    (This)->lpVtbl -> UnregisterTIF(This,pvRegistrationContext)

#define IMPEG2_TIF_CONTROL_AddPIDs(This,ulcPIDs,pulPIDs)	\
    (This)->lpVtbl -> AddPIDs(This,ulcPIDs,pulPIDs)

#define IMPEG2_TIF_CONTROL_DeletePIDs(This,ulcPIDs,pulPIDs)	\
    (This)->lpVtbl -> DeletePIDs(This,ulcPIDs,pulPIDs)

#define IMPEG2_TIF_CONTROL_GetPIDCount(This,pulcPIDs)	\
    (This)->lpVtbl -> GetPIDCount(This,pulcPIDs)

#define IMPEG2_TIF_CONTROL_GetPIDs(This,pulcPIDs,pulPIDs)	\
    (This)->lpVtbl -> GetPIDs(This,pulcPIDs,pulPIDs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_RegisterTIF_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [in] */ IUnknown *pUnkTIF,
    /* [out][in] */ ULONG *ppvRegistrationContext);


void __RPC_STUB IMPEG2_TIF_CONTROL_RegisterTIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_UnregisterTIF_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [in] */ ULONG pvRegistrationContext);


void __RPC_STUB IMPEG2_TIF_CONTROL_UnregisterTIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_AddPIDs_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [in] */ ULONG ulcPIDs,
    /* [in] */ ULONG *pulPIDs);


void __RPC_STUB IMPEG2_TIF_CONTROL_AddPIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_DeletePIDs_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [in] */ ULONG ulcPIDs,
    /* [in] */ ULONG *pulPIDs);


void __RPC_STUB IMPEG2_TIF_CONTROL_DeletePIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_GetPIDCount_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [out] */ ULONG *pulcPIDs);


void __RPC_STUB IMPEG2_TIF_CONTROL_GetPIDCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMPEG2_TIF_CONTROL_GetPIDs_Proxy( 
    IMPEG2_TIF_CONTROL * This,
    /* [out] */ ULONG *pulcPIDs,
    /* [out] */ ULONG *pulPIDs);


void __RPC_STUB IMPEG2_TIF_CONTROL_GetPIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEG2_TIF_CONTROL_INTERFACE_DEFINED__ */


#ifndef __ITuneRequestInfo_INTERFACE_DEFINED__
#define __ITuneRequestInfo_INTERFACE_DEFINED__

/* interface ITuneRequestInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITuneRequestInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3B152DF-7A90-4218-AC54-9830BEE8C0B6")
    ITuneRequestInfo : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLocatorData( 
            /* [in] */ ITuneRequest *Request) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetComponentData( 
            /* [in] */ ITuneRequest *CurrentRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateComponentList( 
            /* [in] */ ITuneRequest *CurrentRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNextProgram( 
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPreviousProgram( 
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNextLocator( 
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPreviousLocator( 
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITuneRequestInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITuneRequestInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITuneRequestInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITuneRequestInfo * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLocatorData )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *Request);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetComponentData )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateComponentList )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNextProgram )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPreviousProgram )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNextLocator )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPreviousLocator )( 
            ITuneRequestInfo * This,
            /* [in] */ ITuneRequest *CurrentRequest,
            /* [retval][out] */ ITuneRequest **TuneRequest);
        
        END_INTERFACE
    } ITuneRequestInfoVtbl;

    interface ITuneRequestInfo
    {
        CONST_VTBL struct ITuneRequestInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITuneRequestInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITuneRequestInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITuneRequestInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITuneRequestInfo_GetLocatorData(This,Request)	\
    (This)->lpVtbl -> GetLocatorData(This,Request)

#define ITuneRequestInfo_GetComponentData(This,CurrentRequest)	\
    (This)->lpVtbl -> GetComponentData(This,CurrentRequest)

#define ITuneRequestInfo_CreateComponentList(This,CurrentRequest)	\
    (This)->lpVtbl -> CreateComponentList(This,CurrentRequest)

#define ITuneRequestInfo_GetNextProgram(This,CurrentRequest,TuneRequest)	\
    (This)->lpVtbl -> GetNextProgram(This,CurrentRequest,TuneRequest)

#define ITuneRequestInfo_GetPreviousProgram(This,CurrentRequest,TuneRequest)	\
    (This)->lpVtbl -> GetPreviousProgram(This,CurrentRequest,TuneRequest)

#define ITuneRequestInfo_GetNextLocator(This,CurrentRequest,TuneRequest)	\
    (This)->lpVtbl -> GetNextLocator(This,CurrentRequest,TuneRequest)

#define ITuneRequestInfo_GetPreviousLocator(This,CurrentRequest,TuneRequest)	\
    (This)->lpVtbl -> GetPreviousLocator(This,CurrentRequest,TuneRequest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetLocatorData_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *Request);


void __RPC_STUB ITuneRequestInfo_GetLocatorData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetComponentData_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest);


void __RPC_STUB ITuneRequestInfo_GetComponentData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_CreateComponentList_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest);


void __RPC_STUB ITuneRequestInfo_CreateComponentList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetNextProgram_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuneRequestInfo_GetNextProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetPreviousProgram_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuneRequestInfo_GetPreviousProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetNextLocator_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuneRequestInfo_GetNextLocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITuneRequestInfo_GetPreviousLocator_Proxy( 
    ITuneRequestInfo * This,
    /* [in] */ ITuneRequest *CurrentRequest,
    /* [retval][out] */ ITuneRequest **TuneRequest);


void __RPC_STUB ITuneRequestInfo_GetPreviousLocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITuneRequestInfo_INTERFACE_DEFINED__ */


#ifndef __IGuideDataEvent_INTERFACE_DEFINED__
#define __IGuideDataEvent_INTERFACE_DEFINED__

/* interface IGuideDataEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGuideDataEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EFDA0C80-F395-42c3-9B3C-56B37DEC7BB7")
    IGuideDataEvent : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GuideDataAcquired( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProgramChanged( 
            /* [in] */ VARIANT varProgramDescriptionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ServiceChanged( 
            /* [in] */ VARIANT varServiceDescriptionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScheduleEntryChanged( 
            /* [in] */ VARIANT varScheduleEntryDescriptionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProgramDeleted( 
            /* [in] */ VARIANT varProgramDescriptionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ServiceDeleted( 
            /* [in] */ VARIANT varServiceDescriptionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScheduleDeleted( 
            /* [in] */ VARIANT varScheduleEntryDescriptionID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGuideDataEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGuideDataEvent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGuideDataEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGuideDataEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GuideDataAcquired )( 
            IGuideDataEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *ProgramChanged )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varProgramDescriptionID);
        
        HRESULT ( STDMETHODCALLTYPE *ServiceChanged )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varServiceDescriptionID);
        
        HRESULT ( STDMETHODCALLTYPE *ScheduleEntryChanged )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varScheduleEntryDescriptionID);
        
        HRESULT ( STDMETHODCALLTYPE *ProgramDeleted )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varProgramDescriptionID);
        
        HRESULT ( STDMETHODCALLTYPE *ServiceDeleted )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varServiceDescriptionID);
        
        HRESULT ( STDMETHODCALLTYPE *ScheduleDeleted )( 
            IGuideDataEvent * This,
            /* [in] */ VARIANT varScheduleEntryDescriptionID);
        
        END_INTERFACE
    } IGuideDataEventVtbl;

    interface IGuideDataEvent
    {
        CONST_VTBL struct IGuideDataEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGuideDataEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGuideDataEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGuideDataEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGuideDataEvent_GuideDataAcquired(This)	\
    (This)->lpVtbl -> GuideDataAcquired(This)

#define IGuideDataEvent_ProgramChanged(This,varProgramDescriptionID)	\
    (This)->lpVtbl -> ProgramChanged(This,varProgramDescriptionID)

#define IGuideDataEvent_ServiceChanged(This,varServiceDescriptionID)	\
    (This)->lpVtbl -> ServiceChanged(This,varServiceDescriptionID)

#define IGuideDataEvent_ScheduleEntryChanged(This,varScheduleEntryDescriptionID)	\
    (This)->lpVtbl -> ScheduleEntryChanged(This,varScheduleEntryDescriptionID)

#define IGuideDataEvent_ProgramDeleted(This,varProgramDescriptionID)	\
    (This)->lpVtbl -> ProgramDeleted(This,varProgramDescriptionID)

#define IGuideDataEvent_ServiceDeleted(This,varServiceDescriptionID)	\
    (This)->lpVtbl -> ServiceDeleted(This,varServiceDescriptionID)

#define IGuideDataEvent_ScheduleDeleted(This,varScheduleEntryDescriptionID)	\
    (This)->lpVtbl -> ScheduleDeleted(This,varScheduleEntryDescriptionID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGuideDataEvent_GuideDataAcquired_Proxy( 
    IGuideDataEvent * This);


void __RPC_STUB IGuideDataEvent_GuideDataAcquired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ProgramChanged_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varProgramDescriptionID);


void __RPC_STUB IGuideDataEvent_ProgramChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ServiceChanged_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varServiceDescriptionID);


void __RPC_STUB IGuideDataEvent_ServiceChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ScheduleEntryChanged_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varScheduleEntryDescriptionID);


void __RPC_STUB IGuideDataEvent_ScheduleEntryChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ProgramDeleted_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varProgramDescriptionID);


void __RPC_STUB IGuideDataEvent_ProgramDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ServiceDeleted_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varServiceDescriptionID);


void __RPC_STUB IGuideDataEvent_ServiceDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataEvent_ScheduleDeleted_Proxy( 
    IGuideDataEvent * This,
    /* [in] */ VARIANT varScheduleEntryDescriptionID);


void __RPC_STUB IGuideDataEvent_ScheduleDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGuideDataEvent_INTERFACE_DEFINED__ */


#ifndef __IGuideDataProperty_INTERFACE_DEFINED__
#define __IGuideDataProperty_INTERFACE_DEFINED__

/* interface IGuideDataProperty */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGuideDataProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88EC5E58-BB73-41d6-99CE-66C524B8B591")
    IGuideDataProperty : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [out] */ BSTR *pbstrName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Language( 
            /* [out] */ long *idLang) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [out] */ VARIANT *pvar) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGuideDataPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGuideDataProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGuideDataProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGuideDataProperty * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGuideDataProperty * This,
            /* [out] */ BSTR *pbstrName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Language )( 
            IGuideDataProperty * This,
            /* [out] */ long *idLang);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IGuideDataProperty * This,
            /* [out] */ VARIANT *pvar);
        
        END_INTERFACE
    } IGuideDataPropertyVtbl;

    interface IGuideDataProperty
    {
        CONST_VTBL struct IGuideDataPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGuideDataProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGuideDataProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGuideDataProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGuideDataProperty_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IGuideDataProperty_get_Language(This,idLang)	\
    (This)->lpVtbl -> get_Language(This,idLang)

#define IGuideDataProperty_get_Value(This,pvar)	\
    (This)->lpVtbl -> get_Value(This,pvar)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IGuideDataProperty_get_Name_Proxy( 
    IGuideDataProperty * This,
    /* [out] */ BSTR *pbstrName);


void __RPC_STUB IGuideDataProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGuideDataProperty_get_Language_Proxy( 
    IGuideDataProperty * This,
    /* [out] */ long *idLang);


void __RPC_STUB IGuideDataProperty_get_Language_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGuideDataProperty_get_Value_Proxy( 
    IGuideDataProperty * This,
    /* [out] */ VARIANT *pvar);


void __RPC_STUB IGuideDataProperty_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGuideDataProperty_INTERFACE_DEFINED__ */


#ifndef __IEnumGuideDataProperties_INTERFACE_DEFINED__
#define __IEnumGuideDataProperties_INTERFACE_DEFINED__

/* interface IEnumGuideDataProperties */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumGuideDataProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE44423B-4571-475c-AD2C-F40A771D80EF")
    IEnumGuideDataProperties : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ unsigned long celt,
            /* [out] */ IGuideDataProperty **ppprop,
            /* [out] */ unsigned long *pcelt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ unsigned long celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumGuideDataProperties **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumGuideDataPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumGuideDataProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumGuideDataProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumGuideDataProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumGuideDataProperties * This,
            /* [in] */ unsigned long celt,
            /* [out] */ IGuideDataProperty **ppprop,
            /* [out] */ unsigned long *pcelt);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumGuideDataProperties * This,
            /* [in] */ unsigned long celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumGuideDataProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumGuideDataProperties * This,
            /* [out] */ IEnumGuideDataProperties **ppenum);
        
        END_INTERFACE
    } IEnumGuideDataPropertiesVtbl;

    interface IEnumGuideDataProperties
    {
        CONST_VTBL struct IEnumGuideDataPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumGuideDataProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumGuideDataProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumGuideDataProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumGuideDataProperties_Next(This,celt,ppprop,pcelt)	\
    (This)->lpVtbl -> Next(This,celt,ppprop,pcelt)

#define IEnumGuideDataProperties_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumGuideDataProperties_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumGuideDataProperties_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumGuideDataProperties_Next_Proxy( 
    IEnumGuideDataProperties * This,
    /* [in] */ unsigned long celt,
    /* [out] */ IGuideDataProperty **ppprop,
    /* [out] */ unsigned long *pcelt);


void __RPC_STUB IEnumGuideDataProperties_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumGuideDataProperties_Skip_Proxy( 
    IEnumGuideDataProperties * This,
    /* [in] */ unsigned long celt);


void __RPC_STUB IEnumGuideDataProperties_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumGuideDataProperties_Reset_Proxy( 
    IEnumGuideDataProperties * This);


void __RPC_STUB IEnumGuideDataProperties_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumGuideDataProperties_Clone_Proxy( 
    IEnumGuideDataProperties * This,
    /* [out] */ IEnumGuideDataProperties **ppenum);


void __RPC_STUB IEnumGuideDataProperties_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumGuideDataProperties_INTERFACE_DEFINED__ */


#ifndef __IEnumTuneRequests_INTERFACE_DEFINED__
#define __IEnumTuneRequests_INTERFACE_DEFINED__

/* interface IEnumTuneRequests */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumTuneRequests;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1993299C-CED6-4788-87A3-420067DCE0C7")
    IEnumTuneRequests : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ unsigned long celt,
            /* [out] */ ITuneRequest **ppprop,
            /* [out] */ unsigned long *pcelt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ unsigned long celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumTuneRequests **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumTuneRequestsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumTuneRequests * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumTuneRequests * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumTuneRequests * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumTuneRequests * This,
            /* [in] */ unsigned long celt,
            /* [out] */ ITuneRequest **ppprop,
            /* [out] */ unsigned long *pcelt);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumTuneRequests * This,
            /* [in] */ unsigned long celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumTuneRequests * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumTuneRequests * This,
            /* [out] */ IEnumTuneRequests **ppenum);
        
        END_INTERFACE
    } IEnumTuneRequestsVtbl;

    interface IEnumTuneRequests
    {
        CONST_VTBL struct IEnumTuneRequestsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTuneRequests_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumTuneRequests_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumTuneRequests_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumTuneRequests_Next(This,celt,ppprop,pcelt)	\
    (This)->lpVtbl -> Next(This,celt,ppprop,pcelt)

#define IEnumTuneRequests_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumTuneRequests_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumTuneRequests_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumTuneRequests_Next_Proxy( 
    IEnumTuneRequests * This,
    /* [in] */ unsigned long celt,
    /* [out] */ ITuneRequest **ppprop,
    /* [out] */ unsigned long *pcelt);


void __RPC_STUB IEnumTuneRequests_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuneRequests_Skip_Proxy( 
    IEnumTuneRequests * This,
    /* [in] */ unsigned long celt);


void __RPC_STUB IEnumTuneRequests_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuneRequests_Reset_Proxy( 
    IEnumTuneRequests * This);


void __RPC_STUB IEnumTuneRequests_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTuneRequests_Clone_Proxy( 
    IEnumTuneRequests * This,
    /* [out] */ IEnumTuneRequests **ppenum);


void __RPC_STUB IEnumTuneRequests_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumTuneRequests_INTERFACE_DEFINED__ */


#ifndef __IGuideData_INTERFACE_DEFINED__
#define __IGuideData_INTERFACE_DEFINED__

/* interface IGuideData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGuideData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("61571138-5B01-43cd-AEAF-60B784A0BF93")
    IGuideData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetServices( 
            /* [retval][out] */ IEnumTuneRequests **ppEnumTuneRequests) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetServiceProperties( 
            /* [in] */ ITuneRequest *pTuneRequest,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGuideProgramIDs( 
            /* [retval][out] */ IEnumVARIANT **pEnumPrograms) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProgramProperties( 
            /* [in] */ VARIANT varProgramDescriptionID,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScheduleEntryIDs( 
            /* [retval][out] */ IEnumVARIANT **pEnumScheduleEntries) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScheduleEntryProperties( 
            /* [in] */ VARIANT varScheduleEntryDescriptionID,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGuideDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGuideData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGuideData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGuideData * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetServices )( 
            IGuideData * This,
            /* [retval][out] */ IEnumTuneRequests **ppEnumTuneRequests);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetServiceProperties )( 
            IGuideData * This,
            /* [in] */ ITuneRequest *pTuneRequest,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetGuideProgramIDs )( 
            IGuideData * This,
            /* [retval][out] */ IEnumVARIANT **pEnumPrograms);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetProgramProperties )( 
            IGuideData * This,
            /* [in] */ VARIANT varProgramDescriptionID,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetScheduleEntryIDs )( 
            IGuideData * This,
            /* [retval][out] */ IEnumVARIANT **pEnumScheduleEntries);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetScheduleEntryProperties )( 
            IGuideData * This,
            /* [in] */ VARIANT varScheduleEntryDescriptionID,
            /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);
        
        END_INTERFACE
    } IGuideDataVtbl;

    interface IGuideData
    {
        CONST_VTBL struct IGuideDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGuideData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGuideData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGuideData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGuideData_GetServices(This,ppEnumTuneRequests)	\
    (This)->lpVtbl -> GetServices(This,ppEnumTuneRequests)

#define IGuideData_GetServiceProperties(This,pTuneRequest,ppEnumProperties)	\
    (This)->lpVtbl -> GetServiceProperties(This,pTuneRequest,ppEnumProperties)

#define IGuideData_GetGuideProgramIDs(This,pEnumPrograms)	\
    (This)->lpVtbl -> GetGuideProgramIDs(This,pEnumPrograms)

#define IGuideData_GetProgramProperties(This,varProgramDescriptionID,ppEnumProperties)	\
    (This)->lpVtbl -> GetProgramProperties(This,varProgramDescriptionID,ppEnumProperties)

#define IGuideData_GetScheduleEntryIDs(This,pEnumScheduleEntries)	\
    (This)->lpVtbl -> GetScheduleEntryIDs(This,pEnumScheduleEntries)

#define IGuideData_GetScheduleEntryProperties(This,varScheduleEntryDescriptionID,ppEnumProperties)	\
    (This)->lpVtbl -> GetScheduleEntryProperties(This,varScheduleEntryDescriptionID,ppEnumProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetServices_Proxy( 
    IGuideData * This,
    /* [retval][out] */ IEnumTuneRequests **ppEnumTuneRequests);


void __RPC_STUB IGuideData_GetServices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetServiceProperties_Proxy( 
    IGuideData * This,
    /* [in] */ ITuneRequest *pTuneRequest,
    /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);


void __RPC_STUB IGuideData_GetServiceProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetGuideProgramIDs_Proxy( 
    IGuideData * This,
    /* [retval][out] */ IEnumVARIANT **pEnumPrograms);


void __RPC_STUB IGuideData_GetGuideProgramIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetProgramProperties_Proxy( 
    IGuideData * This,
    /* [in] */ VARIANT varProgramDescriptionID,
    /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);


void __RPC_STUB IGuideData_GetProgramProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetScheduleEntryIDs_Proxy( 
    IGuideData * This,
    /* [retval][out] */ IEnumVARIANT **pEnumScheduleEntries);


void __RPC_STUB IGuideData_GetScheduleEntryIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGuideData_GetScheduleEntryProperties_Proxy( 
    IGuideData * This,
    /* [in] */ VARIANT varScheduleEntryDescriptionID,
    /* [retval][out] */ IEnumGuideDataProperties **ppEnumProperties);


void __RPC_STUB IGuideData_GetScheduleEntryProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGuideData_INTERFACE_DEFINED__ */


#ifndef __IGuideDataLoader_INTERFACE_DEFINED__
#define __IGuideDataLoader_INTERFACE_DEFINED__

/* interface IGuideDataLoader */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGuideDataLoader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4764ff7c-fa95-4525-af4d-d32236db9e38")
    IGuideDataLoader : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IGuideData *pGuideStore) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGuideDataLoaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGuideDataLoader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGuideDataLoader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGuideDataLoader * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IGuideDataLoader * This,
            /* [in] */ IGuideData *pGuideStore);
        
        HRESULT ( STDMETHODCALLTYPE *Terminate )( 
            IGuideDataLoader * This);
        
        END_INTERFACE
    } IGuideDataLoaderVtbl;

    interface IGuideDataLoader
    {
        CONST_VTBL struct IGuideDataLoaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGuideDataLoader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGuideDataLoader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGuideDataLoader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGuideDataLoader_Init(This,pGuideStore)	\
    (This)->lpVtbl -> Init(This,pGuideStore)

#define IGuideDataLoader_Terminate(This)	\
    (This)->lpVtbl -> Terminate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGuideDataLoader_Init_Proxy( 
    IGuideDataLoader * This,
    /* [in] */ IGuideData *pGuideStore);


void __RPC_STUB IGuideDataLoader_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGuideDataLoader_Terminate_Proxy( 
    IGuideDataLoader * This);


void __RPC_STUB IGuideDataLoader_Terminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGuideDataLoader_INTERFACE_DEFINED__ */



#ifndef __PSISLOADLib_LIBRARY_DEFINED__
#define __PSISLOADLib_LIBRARY_DEFINED__

/* library PSISLOADLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PSISLOADLib;

EXTERN_C const CLSID CLSID_TIFLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("14EB8748-1753-4393-95AE-4F7E7A87AAD6")
TIFLoad;
#endif
#endif /* __PSISLOADLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_bdatif_0489 */
/* [local] */ 

#if ( _MSC_VER >= 800 )
#pragma warning(default:4201)    /* Nameless struct/union */
#endif


extern RPC_IF_HANDLE __MIDL_itf_bdatif_0489_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_bdatif_0489_v0_0_s_ifspec;

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


