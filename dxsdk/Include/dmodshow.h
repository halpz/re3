
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for dmodshow.idl:
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

#ifndef __dmodshow_h__
#define __dmodshow_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDMOWrapperFilter_FWD_DEFINED__
#define __IDMOWrapperFilter_FWD_DEFINED__
typedef interface IDMOWrapperFilter IDMOWrapperFilter;
#endif 	/* __IDMOWrapperFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "mediaobj.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_dmodshow_0000 */
/* [local] */ 

DEFINE_GUID(CLSID_DMOWrapperFilter, 0x94297043,0xbd82,0x4dfd,0xb0,0xde,0x81,0x77,0x73,0x9c,0x6d,0x20);
DEFINE_GUID(CLSID_DMOFilterCategory,0xbcd5796c,0xbd52,0x4d30,0xab,0x76,0x70,0xf9,0x75,0xb8,0x91,0x99);


extern RPC_IF_HANDLE __MIDL_itf_dmodshow_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dmodshow_0000_v0_0_s_ifspec;

#ifndef __IDMOWrapperFilter_INTERFACE_DEFINED__
#define __IDMOWrapperFilter_INTERFACE_DEFINED__

/* interface IDMOWrapperFilter */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDMOWrapperFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52d6f586-9f0f-4824-8fc8-e32ca04930c2")
    IDMOWrapperFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            REFCLSID clsidDMO,
            REFCLSID catDMO) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDMOWrapperFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDMOWrapperFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDMOWrapperFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDMOWrapperFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IDMOWrapperFilter * This,
            REFCLSID clsidDMO,
            REFCLSID catDMO);
        
        END_INTERFACE
    } IDMOWrapperFilterVtbl;

    interface IDMOWrapperFilter
    {
        CONST_VTBL struct IDMOWrapperFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDMOWrapperFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDMOWrapperFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDMOWrapperFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDMOWrapperFilter_Init(This,clsidDMO,catDMO)	\
    (This)->lpVtbl -> Init(This,clsidDMO,catDMO)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDMOWrapperFilter_Init_Proxy( 
    IDMOWrapperFilter * This,
    REFCLSID clsidDMO,
    REFCLSID catDMO);


void __RPC_STUB IDMOWrapperFilter_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDMOWrapperFilter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


