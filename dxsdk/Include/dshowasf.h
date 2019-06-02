
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0338 */
/* Compiler settings for dshowasf.idl:
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

#ifndef __dshowasf_h__
#define __dshowasf_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IConfigAsfWriter_FWD_DEFINED__
#define __IConfigAsfWriter_FWD_DEFINED__
typedef interface IConfigAsfWriter IConfigAsfWriter;
#endif 	/* __IConfigAsfWriter_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "strmif.h"
#include "wmsdkidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_dshowasf_0000 */
/* [local] */ 

EXTERN_GUID( IID_IConfigAsfWriter,0x45086030,0xF7E4,0x486a,0xB5,0x04,0x82,0x6B,0xB5,0x79,0x2A,0x3B );




extern RPC_IF_HANDLE __MIDL_itf_dshowasf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dshowasf_0000_v0_0_s_ifspec;

#ifndef __IConfigAsfWriter_INTERFACE_DEFINED__
#define __IConfigAsfWriter_INTERFACE_DEFINED__

/* interface IConfigAsfWriter */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IConfigAsfWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45086030-F7E4-486a-B504-826BB5792A3B")
    IConfigAsfWriter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConfigureFilterUsingProfileId( 
            /* [in] */ DWORD dwProfileId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentProfileId( 
            /* [out] */ DWORD *pdwProfileId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConfigureFilterUsingProfileGuid( 
            /* [in] */ REFGUID guidProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentProfileGuid( 
            /* [out] */ GUID *pProfileGuid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConfigureFilterUsingProfile( 
            /* [in] */ IWMProfile *pProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentProfile( 
            /* [out] */ IWMProfile **ppProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIndexMode( 
            /* [in] */ BOOL bIndexFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexMode( 
            /* [out] */ BOOL *pbIndexFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigAsfWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigAsfWriter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigAsfWriter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigAsfWriter * This);
        
        HRESULT ( STDMETHODCALLTYPE *ConfigureFilterUsingProfileId )( 
            IConfigAsfWriter * This,
            /* [in] */ DWORD dwProfileId);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentProfileId )( 
            IConfigAsfWriter * This,
            /* [out] */ DWORD *pdwProfileId);
        
        HRESULT ( STDMETHODCALLTYPE *ConfigureFilterUsingProfileGuid )( 
            IConfigAsfWriter * This,
            /* [in] */ REFGUID guidProfile);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentProfileGuid )( 
            IConfigAsfWriter * This,
            /* [out] */ GUID *pProfileGuid);
        
        HRESULT ( STDMETHODCALLTYPE *ConfigureFilterUsingProfile )( 
            IConfigAsfWriter * This,
            /* [in] */ IWMProfile *pProfile);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentProfile )( 
            IConfigAsfWriter * This,
            /* [out] */ IWMProfile **ppProfile);
        
        HRESULT ( STDMETHODCALLTYPE *SetIndexMode )( 
            IConfigAsfWriter * This,
            /* [in] */ BOOL bIndexFile);
        
        HRESULT ( STDMETHODCALLTYPE *GetIndexMode )( 
            IConfigAsfWriter * This,
            /* [out] */ BOOL *pbIndexFile);
        
        END_INTERFACE
    } IConfigAsfWriterVtbl;

    interface IConfigAsfWriter
    {
        CONST_VTBL struct IConfigAsfWriterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigAsfWriter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigAsfWriter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigAsfWriter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigAsfWriter_ConfigureFilterUsingProfileId(This,dwProfileId)	\
    (This)->lpVtbl -> ConfigureFilterUsingProfileId(This,dwProfileId)

#define IConfigAsfWriter_GetCurrentProfileId(This,pdwProfileId)	\
    (This)->lpVtbl -> GetCurrentProfileId(This,pdwProfileId)

#define IConfigAsfWriter_ConfigureFilterUsingProfileGuid(This,guidProfile)	\
    (This)->lpVtbl -> ConfigureFilterUsingProfileGuid(This,guidProfile)

#define IConfigAsfWriter_GetCurrentProfileGuid(This,pProfileGuid)	\
    (This)->lpVtbl -> GetCurrentProfileGuid(This,pProfileGuid)

#define IConfigAsfWriter_ConfigureFilterUsingProfile(This,pProfile)	\
    (This)->lpVtbl -> ConfigureFilterUsingProfile(This,pProfile)

#define IConfigAsfWriter_GetCurrentProfile(This,ppProfile)	\
    (This)->lpVtbl -> GetCurrentProfile(This,ppProfile)

#define IConfigAsfWriter_SetIndexMode(This,bIndexFile)	\
    (This)->lpVtbl -> SetIndexMode(This,bIndexFile)

#define IConfigAsfWriter_GetIndexMode(This,pbIndexFile)	\
    (This)->lpVtbl -> GetIndexMode(This,pbIndexFile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IConfigAsfWriter_ConfigureFilterUsingProfileId_Proxy( 
    IConfigAsfWriter * This,
    /* [in] */ DWORD dwProfileId);


void __RPC_STUB IConfigAsfWriter_ConfigureFilterUsingProfileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_GetCurrentProfileId_Proxy( 
    IConfigAsfWriter * This,
    /* [out] */ DWORD *pdwProfileId);


void __RPC_STUB IConfigAsfWriter_GetCurrentProfileId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_ConfigureFilterUsingProfileGuid_Proxy( 
    IConfigAsfWriter * This,
    /* [in] */ REFGUID guidProfile);


void __RPC_STUB IConfigAsfWriter_ConfigureFilterUsingProfileGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_GetCurrentProfileGuid_Proxy( 
    IConfigAsfWriter * This,
    /* [out] */ GUID *pProfileGuid);


void __RPC_STUB IConfigAsfWriter_GetCurrentProfileGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_ConfigureFilterUsingProfile_Proxy( 
    IConfigAsfWriter * This,
    /* [in] */ IWMProfile *pProfile);


void __RPC_STUB IConfigAsfWriter_ConfigureFilterUsingProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_GetCurrentProfile_Proxy( 
    IConfigAsfWriter * This,
    /* [out] */ IWMProfile **ppProfile);


void __RPC_STUB IConfigAsfWriter_GetCurrentProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_SetIndexMode_Proxy( 
    IConfigAsfWriter * This,
    /* [in] */ BOOL bIndexFile);


void __RPC_STUB IConfigAsfWriter_SetIndexMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IConfigAsfWriter_GetIndexMode_Proxy( 
    IConfigAsfWriter * This,
    /* [out] */ BOOL *pbIndexFile);


void __RPC_STUB IConfigAsfWriter_GetIndexMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigAsfWriter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


