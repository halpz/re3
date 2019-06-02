
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for vidcap.idl:
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

#ifndef __vidcap_h__
#define __vidcap_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IKsTopologyInfo_FWD_DEFINED__
#define __IKsTopologyInfo_FWD_DEFINED__
typedef interface IKsTopologyInfo IKsTopologyInfo;
#endif 	/* __IKsTopologyInfo_FWD_DEFINED__ */


#ifndef __ISelector_FWD_DEFINED__
#define __ISelector_FWD_DEFINED__
typedef interface ISelector ISelector;
#endif 	/* __ISelector_FWD_DEFINED__ */


#ifndef __IKsNodeControl_FWD_DEFINED__
#define __IKsNodeControl_FWD_DEFINED__
typedef interface IKsNodeControl IKsNodeControl;
#endif 	/* __IKsNodeControl_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_vidcap_0000 */
/* [local] */ 

#include "ks.h"
#ifndef _KS_
typedef /* [public][public] */ struct __MIDL___MIDL_itf_vidcap_0000_0001
    {
    ULONG FromNode;
    ULONG FromNodePin;
    ULONG ToNode;
    ULONG ToNodePin;
    } 	KSTOPOLOGY_CONNECTION;

typedef struct __MIDL___MIDL_itf_vidcap_0000_0001 *PKSTOPOLOGY_CONNECTION;

#endif


extern RPC_IF_HANDLE __MIDL_itf_vidcap_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vidcap_0000_v0_0_s_ifspec;

#ifndef __IKsTopologyInfo_INTERFACE_DEFINED__
#define __IKsTopologyInfo_INTERFACE_DEFINED__

/* interface IKsTopologyInfo */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IKsTopologyInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("720D4AC0-7533-11D0-A5D6-28DB04C10000")
    IKsTopologyInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_NumCategories( 
            /* [out] */ DWORD *pdwNumCategories) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_Category( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ GUID *pCategory) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NumConnections( 
            /* [out] */ DWORD *pdwNumConnections) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_ConnectionInfo( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ KSTOPOLOGY_CONNECTION *pConnectionInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NodeName( 
            /* [in] */ DWORD dwNodeId,
            /* [out] */ WCHAR *pwchNodeName,
            /* [in] */ DWORD dwBufSize,
            /* [out] */ DWORD *pdwNameLen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NumNodes( 
            /* [out] */ DWORD *pdwNumNodes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_NodeType( 
            /* [in] */ DWORD dwNodeId,
            /* [out] */ GUID *pNodeType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateNodeInstance( 
            /* [in] */ DWORD dwNodeId,
            /* [in] */ REFIID iid,
            /* [out] */ void **ppvObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKsTopologyInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKsTopologyInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKsTopologyInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKsTopologyInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumCategories )( 
            IKsTopologyInfo * This,
            /* [out] */ DWORD *pdwNumCategories);
        
        HRESULT ( STDMETHODCALLTYPE *get_Category )( 
            IKsTopologyInfo * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ GUID *pCategory);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumConnections )( 
            IKsTopologyInfo * This,
            /* [out] */ DWORD *pdwNumConnections);
        
        HRESULT ( STDMETHODCALLTYPE *get_ConnectionInfo )( 
            IKsTopologyInfo * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ KSTOPOLOGY_CONNECTION *pConnectionInfo);
        
        HRESULT ( STDMETHODCALLTYPE *get_NodeName )( 
            IKsTopologyInfo * This,
            /* [in] */ DWORD dwNodeId,
            /* [out] */ WCHAR *pwchNodeName,
            /* [in] */ DWORD dwBufSize,
            /* [out] */ DWORD *pdwNameLen);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumNodes )( 
            IKsTopologyInfo * This,
            /* [out] */ DWORD *pdwNumNodes);
        
        HRESULT ( STDMETHODCALLTYPE *get_NodeType )( 
            IKsTopologyInfo * This,
            /* [in] */ DWORD dwNodeId,
            /* [out] */ GUID *pNodeType);
        
        HRESULT ( STDMETHODCALLTYPE *CreateNodeInstance )( 
            IKsTopologyInfo * This,
            /* [in] */ DWORD dwNodeId,
            /* [in] */ REFIID iid,
            /* [out] */ void **ppvObject);
        
        END_INTERFACE
    } IKsTopologyInfoVtbl;

    interface IKsTopologyInfo
    {
        CONST_VTBL struct IKsTopologyInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKsTopologyInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKsTopologyInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKsTopologyInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKsTopologyInfo_get_NumCategories(This,pdwNumCategories)	\
    (This)->lpVtbl -> get_NumCategories(This,pdwNumCategories)

#define IKsTopologyInfo_get_Category(This,dwIndex,pCategory)	\
    (This)->lpVtbl -> get_Category(This,dwIndex,pCategory)

#define IKsTopologyInfo_get_NumConnections(This,pdwNumConnections)	\
    (This)->lpVtbl -> get_NumConnections(This,pdwNumConnections)

#define IKsTopologyInfo_get_ConnectionInfo(This,dwIndex,pConnectionInfo)	\
    (This)->lpVtbl -> get_ConnectionInfo(This,dwIndex,pConnectionInfo)

#define IKsTopologyInfo_get_NodeName(This,dwNodeId,pwchNodeName,dwBufSize,pdwNameLen)	\
    (This)->lpVtbl -> get_NodeName(This,dwNodeId,pwchNodeName,dwBufSize,pdwNameLen)

#define IKsTopologyInfo_get_NumNodes(This,pdwNumNodes)	\
    (This)->lpVtbl -> get_NumNodes(This,pdwNumNodes)

#define IKsTopologyInfo_get_NodeType(This,dwNodeId,pNodeType)	\
    (This)->lpVtbl -> get_NodeType(This,dwNodeId,pNodeType)

#define IKsTopologyInfo_CreateNodeInstance(This,dwNodeId,iid,ppvObject)	\
    (This)->lpVtbl -> CreateNodeInstance(This,dwNodeId,iid,ppvObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_NumCategories_Proxy( 
    IKsTopologyInfo * This,
    /* [out] */ DWORD *pdwNumCategories);


void __RPC_STUB IKsTopologyInfo_get_NumCategories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_Category_Proxy( 
    IKsTopologyInfo * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ GUID *pCategory);


void __RPC_STUB IKsTopologyInfo_get_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_NumConnections_Proxy( 
    IKsTopologyInfo * This,
    /* [out] */ DWORD *pdwNumConnections);


void __RPC_STUB IKsTopologyInfo_get_NumConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_ConnectionInfo_Proxy( 
    IKsTopologyInfo * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ KSTOPOLOGY_CONNECTION *pConnectionInfo);


void __RPC_STUB IKsTopologyInfo_get_ConnectionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_NodeName_Proxy( 
    IKsTopologyInfo * This,
    /* [in] */ DWORD dwNodeId,
    /* [out] */ WCHAR *pwchNodeName,
    /* [in] */ DWORD dwBufSize,
    /* [out] */ DWORD *pdwNameLen);


void __RPC_STUB IKsTopologyInfo_get_NodeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_NumNodes_Proxy( 
    IKsTopologyInfo * This,
    /* [out] */ DWORD *pdwNumNodes);


void __RPC_STUB IKsTopologyInfo_get_NumNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_get_NodeType_Proxy( 
    IKsTopologyInfo * This,
    /* [in] */ DWORD dwNodeId,
    /* [out] */ GUID *pNodeType);


void __RPC_STUB IKsTopologyInfo_get_NodeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsTopologyInfo_CreateNodeInstance_Proxy( 
    IKsTopologyInfo * This,
    /* [in] */ DWORD dwNodeId,
    /* [in] */ REFIID iid,
    /* [out] */ void **ppvObject);


void __RPC_STUB IKsTopologyInfo_CreateNodeInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKsTopologyInfo_INTERFACE_DEFINED__ */


#ifndef __ISelector_INTERFACE_DEFINED__
#define __ISelector_INTERFACE_DEFINED__

/* interface ISelector */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_ISelector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ABDAECA-68B6-4F83-9371-B413907C7B9F")
    ISelector : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_NumSources( 
            /* [out] */ DWORD *pdwNumSources) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_SourceNodeId( 
            /* [out] */ DWORD *pdwPinId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_SourceNodeId( 
            /* [in] */ DWORD dwPinId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISelectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISelector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISelector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISelector * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_NumSources )( 
            ISelector * This,
            /* [out] */ DWORD *pdwNumSources);
        
        HRESULT ( STDMETHODCALLTYPE *get_SourceNodeId )( 
            ISelector * This,
            /* [out] */ DWORD *pdwPinId);
        
        HRESULT ( STDMETHODCALLTYPE *put_SourceNodeId )( 
            ISelector * This,
            /* [in] */ DWORD dwPinId);
        
        END_INTERFACE
    } ISelectorVtbl;

    interface ISelector
    {
        CONST_VTBL struct ISelectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISelector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISelector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISelector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISelector_get_NumSources(This,pdwNumSources)	\
    (This)->lpVtbl -> get_NumSources(This,pdwNumSources)

#define ISelector_get_SourceNodeId(This,pdwPinId)	\
    (This)->lpVtbl -> get_SourceNodeId(This,pdwPinId)

#define ISelector_put_SourceNodeId(This,dwPinId)	\
    (This)->lpVtbl -> put_SourceNodeId(This,dwPinId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISelector_get_NumSources_Proxy( 
    ISelector * This,
    /* [out] */ DWORD *pdwNumSources);


void __RPC_STUB ISelector_get_NumSources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelector_get_SourceNodeId_Proxy( 
    ISelector * This,
    /* [out] */ DWORD *pdwPinId);


void __RPC_STUB ISelector_get_SourceNodeId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISelector_put_SourceNodeId_Proxy( 
    ISelector * This,
    /* [in] */ DWORD dwPinId);


void __RPC_STUB ISelector_put_SourceNodeId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISelector_INTERFACE_DEFINED__ */


#ifndef __IKsNodeControl_INTERFACE_DEFINED__
#define __IKsNodeControl_INTERFACE_DEFINED__

/* interface IKsNodeControl */
/* [unique][uuid][local][object] */ 


EXTERN_C const IID IID_IKsNodeControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11737C14-24A7-4bb5-81A0-0D003813B0C4")
    IKsNodeControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_NodeId( 
            /* [in] */ DWORD dwNodeId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE put_KsControl( 
            /* [in] */ PVOID pKsControl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKsNodeControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKsNodeControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKsNodeControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKsNodeControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_NodeId )( 
            IKsNodeControl * This,
            /* [in] */ DWORD dwNodeId);
        
        HRESULT ( STDMETHODCALLTYPE *put_KsControl )( 
            IKsNodeControl * This,
            /* [in] */ PVOID pKsControl);
        
        END_INTERFACE
    } IKsNodeControlVtbl;

    interface IKsNodeControl
    {
        CONST_VTBL struct IKsNodeControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKsNodeControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKsNodeControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKsNodeControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKsNodeControl_put_NodeId(This,dwNodeId)	\
    (This)->lpVtbl -> put_NodeId(This,dwNodeId)

#define IKsNodeControl_put_KsControl(This,pKsControl)	\
    (This)->lpVtbl -> put_KsControl(This,pKsControl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IKsNodeControl_put_NodeId_Proxy( 
    IKsNodeControl * This,
    /* [in] */ DWORD dwNodeId);


void __RPC_STUB IKsNodeControl_put_NodeId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKsNodeControl_put_KsControl_Proxy( 
    IKsNodeControl * This,
    /* [in] */ PVOID pKsControl);


void __RPC_STUB IKsNodeControl_put_KsControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKsNodeControl_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


