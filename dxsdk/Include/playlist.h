
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Sat Jul 31 00:39:47 1999
 */
/* Compiler settings for playlist.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext, robust
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

#ifndef __playlist_h__
#define __playlist_h__

/* Forward Declarations */ 

#ifndef __IAMPlayListItem_FWD_DEFINED__
#define __IAMPlayListItem_FWD_DEFINED__
typedef interface IAMPlayListItem IAMPlayListItem;
#endif 	/* __IAMPlayListItem_FWD_DEFINED__ */


#ifndef __IAMPlayList_FWD_DEFINED__
#define __IAMPlayList_FWD_DEFINED__
typedef interface IAMPlayList IAMPlayList;
#endif 	/* __IAMPlayList_FWD_DEFINED__ */


#ifndef __ISpecifyParticularPages_FWD_DEFINED__
#define __ISpecifyParticularPages_FWD_DEFINED__
typedef interface ISpecifyParticularPages ISpecifyParticularPages;
#endif 	/* __ISpecifyParticularPages_FWD_DEFINED__ */


#ifndef __IAMRebuild_FWD_DEFINED__
#define __IAMRebuild_FWD_DEFINED__
typedef interface IAMRebuild IAMRebuild;
#endif 	/* __IAMRebuild_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_playlist_0000 */
/* [local] */ 


enum AMPlayListItemFlags
    {	AMPLAYLISTITEM_CANSKIP	= 0x1,
	AMPLAYLISTITEM_CANBIND	= 0x2
    };


extern RPC_IF_HANDLE __MIDL_itf_playlist_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_playlist_0000_v0_0_s_ifspec;

#ifndef __IAMPlayListItem_INTERFACE_DEFINED__
#define __IAMPlayListItem_INTERFACE_DEFINED__

/* interface IAMPlayListItem */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMPlayListItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868ff-0ad4-11ce-b03a-0020af0ba770")
    IAMPlayListItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceCount( 
            /* [out] */ DWORD __RPC_FAR *pdwSources) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceURL( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStart( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceDuration( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStartMarker( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceEndMarker( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceStartMarkerName( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrStartMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourceEndMarkerName( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrEndMarker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLinkURL( 
            /* [out] */ BSTR __RPC_FAR *pbstrURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScanDuration( 
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPlayListItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMPlayListItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMPlayListItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceCount )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceURL )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStart )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceDuration )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStartMarker )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceEndMarker )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ DWORD __RPC_FAR *pdwMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceStartMarkerName )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrStartMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourceEndMarkerName )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ BSTR __RPC_FAR *pbstrEndMarker);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLinkURL )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScanDuration )( 
            IAMPlayListItem __RPC_FAR * This,
            /* [in] */ DWORD dwSourceIndex,
            /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration);
        
        END_INTERFACE
    } IAMPlayListItemVtbl;

    interface IAMPlayListItem
    {
        CONST_VTBL struct IAMPlayListItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPlayListItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPlayListItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPlayListItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPlayListItem_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define IAMPlayListItem_GetSourceCount(This,pdwSources)	\
    (This)->lpVtbl -> GetSourceCount(This,pdwSources)

#define IAMPlayListItem_GetSourceURL(This,dwSourceIndex,pbstrURL)	\
    (This)->lpVtbl -> GetSourceURL(This,dwSourceIndex,pbstrURL)

#define IAMPlayListItem_GetSourceStart(This,dwSourceIndex,prtStart)	\
    (This)->lpVtbl -> GetSourceStart(This,dwSourceIndex,prtStart)

#define IAMPlayListItem_GetSourceDuration(This,dwSourceIndex,prtDuration)	\
    (This)->lpVtbl -> GetSourceDuration(This,dwSourceIndex,prtDuration)

#define IAMPlayListItem_GetSourceStartMarker(This,dwSourceIndex,pdwMarker)	\
    (This)->lpVtbl -> GetSourceStartMarker(This,dwSourceIndex,pdwMarker)

#define IAMPlayListItem_GetSourceEndMarker(This,dwSourceIndex,pdwMarker)	\
    (This)->lpVtbl -> GetSourceEndMarker(This,dwSourceIndex,pdwMarker)

#define IAMPlayListItem_GetSourceStartMarkerName(This,dwSourceIndex,pbstrStartMarker)	\
    (This)->lpVtbl -> GetSourceStartMarkerName(This,dwSourceIndex,pbstrStartMarker)

#define IAMPlayListItem_GetSourceEndMarkerName(This,dwSourceIndex,pbstrEndMarker)	\
    (This)->lpVtbl -> GetSourceEndMarkerName(This,dwSourceIndex,pbstrEndMarker)

#define IAMPlayListItem_GetLinkURL(This,pbstrURL)	\
    (This)->lpVtbl -> GetLinkURL(This,pbstrURL)

#define IAMPlayListItem_GetScanDuration(This,dwSourceIndex,prtScanDuration)	\
    (This)->lpVtbl -> GetScanDuration(This,dwSourceIndex,prtScanDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetFlags_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IAMPlayListItem_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceCount_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwSources);


void __RPC_STUB IAMPlayListItem_GetSourceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceURL_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrURL);


void __RPC_STUB IAMPlayListItem_GetSourceURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStart_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtStart);


void __RPC_STUB IAMPlayListItem_GetSourceStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceDuration_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtDuration);


void __RPC_STUB IAMPlayListItem_GetSourceDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStartMarker_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ DWORD __RPC_FAR *pdwMarker);


void __RPC_STUB IAMPlayListItem_GetSourceStartMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceEndMarker_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ DWORD __RPC_FAR *pdwMarker);


void __RPC_STUB IAMPlayListItem_GetSourceEndMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceStartMarkerName_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrStartMarker);


void __RPC_STUB IAMPlayListItem_GetSourceStartMarkerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetSourceEndMarkerName_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ BSTR __RPC_FAR *pbstrEndMarker);


void __RPC_STUB IAMPlayListItem_GetSourceEndMarkerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetLinkURL_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrURL);


void __RPC_STUB IAMPlayListItem_GetLinkURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayListItem_GetScanDuration_Proxy( 
    IAMPlayListItem __RPC_FAR * This,
    /* [in] */ DWORD dwSourceIndex,
    /* [out] */ REFERENCE_TIME __RPC_FAR *prtScanDuration);


void __RPC_STUB IAMPlayListItem_GetScanDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPlayListItem_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_playlist_0348 */
/* [local] */ 


enum AMPlayListFlags
    {	AMPLAYLIST_STARTINSCANMODE	= 0x1,
	AMPLAYLIST_FORCEBANNER	= 0x2
    };

enum AMPlayListEventFlags
    {	AMPLAYLISTEVENT_RESUME	= 0,
	AMPLAYLISTEVENT_BREAK	= 0x1,
	AMPLAYLISTEVENT_NEXT	= 0x2,
	AMPLAYLISTEVENT_MASK	= 0xf,
	AMPLAYLISTEVENT_REFRESH	= 0x10
    };


extern RPC_IF_HANDLE __MIDL_itf_playlist_0348_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_playlist_0348_v0_0_s_ifspec;

#ifndef __IAMPlayList_INTERFACE_DEFINED__
#define __IAMPlayList_INTERFACE_DEFINED__

/* interface IAMPlayList */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAMPlayList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56a868fe-0ad4-11ce-b03a-0020af0ba770")
    IAMPlayList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemCount( 
            /* [out] */ DWORD __RPC_FAR *pdwItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItem( 
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNamedEvent( 
            /* [in] */ WCHAR __RPC_FAR *pwszEventName,
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem,
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRepeatInfo( 
            /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMPlayListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMPlayList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMPlayList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMPlayList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemCount )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwItems);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItem )( 
            IAMPlayList __RPC_FAR * This,
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedEvent )( 
            IAMPlayList __RPC_FAR * This,
            /* [in] */ WCHAR __RPC_FAR *pwszEventName,
            /* [in] */ DWORD dwItemIndex,
            /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRepeatInfo )( 
            IAMPlayList __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
            /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd);
        
        END_INTERFACE
    } IAMPlayListVtbl;

    interface IAMPlayList
    {
        CONST_VTBL struct IAMPlayListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMPlayList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMPlayList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMPlayList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMPlayList_GetFlags(This,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,pdwFlags)

#define IAMPlayList_GetItemCount(This,pdwItems)	\
    (This)->lpVtbl -> GetItemCount(This,pdwItems)

#define IAMPlayList_GetItem(This,dwItemIndex,ppItem)	\
    (This)->lpVtbl -> GetItem(This,dwItemIndex,ppItem)

#define IAMPlayList_GetNamedEvent(This,pwszEventName,dwItemIndex,ppItem,pdwFlags)	\
    (This)->lpVtbl -> GetNamedEvent(This,pwszEventName,dwItemIndex,ppItem,pdwFlags)

#define IAMPlayList_GetRepeatInfo(This,pdwRepeatCount,pdwRepeatStart,pdwRepeatEnd)	\
    (This)->lpVtbl -> GetRepeatInfo(This,pdwRepeatCount,pdwRepeatStart,pdwRepeatEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMPlayList_GetFlags_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IAMPlayList_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetItemCount_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwItems);


void __RPC_STUB IAMPlayList_GetItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetItem_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [in] */ DWORD dwItemIndex,
    /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem);


void __RPC_STUB IAMPlayList_GetItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetNamedEvent_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [in] */ WCHAR __RPC_FAR *pwszEventName,
    /* [in] */ DWORD dwItemIndex,
    /* [out] */ IAMPlayListItem __RPC_FAR *__RPC_FAR *ppItem,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IAMPlayList_GetNamedEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMPlayList_GetRepeatInfo_Proxy( 
    IAMPlayList __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatCount,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatStart,
    /* [out] */ DWORD __RPC_FAR *pdwRepeatEnd);


void __RPC_STUB IAMPlayList_GetRepeatInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMPlayList_INTERFACE_DEFINED__ */


#ifndef __ISpecifyParticularPages_INTERFACE_DEFINED__
#define __ISpecifyParticularPages_INTERFACE_DEFINED__

/* interface ISpecifyParticularPages */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_ISpecifyParticularPages;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C437B91-6E9E-11d1-A704-006097C4E476")
    ISpecifyParticularPages : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPages( 
            /* [in] */ REFGUID guidWhatPages,
            /* [out] */ CAUUID __RPC_FAR *pPages) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpecifyParticularPagesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpecifyParticularPages __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpecifyParticularPages __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpecifyParticularPages __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPages )( 
            ISpecifyParticularPages __RPC_FAR * This,
            /* [in] */ REFGUID guidWhatPages,
            /* [out] */ CAUUID __RPC_FAR *pPages);
        
        END_INTERFACE
    } ISpecifyParticularPagesVtbl;

    interface ISpecifyParticularPages
    {
        CONST_VTBL struct ISpecifyParticularPagesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpecifyParticularPages_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpecifyParticularPages_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpecifyParticularPages_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpecifyParticularPages_GetPages(This,guidWhatPages,pPages)	\
    (This)->lpVtbl -> GetPages(This,guidWhatPages,pPages)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpecifyParticularPages_GetPages_Proxy( 
    ISpecifyParticularPages __RPC_FAR * This,
    /* [in] */ REFGUID guidWhatPages,
    /* [out] */ CAUUID __RPC_FAR *pPages);


void __RPC_STUB ISpecifyParticularPages_GetPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpecifyParticularPages_INTERFACE_DEFINED__ */


#ifndef __IAMRebuild_INTERFACE_DEFINED__
#define __IAMRebuild_INTERFACE_DEFINED__

/* interface IAMRebuild */
/* [object][helpstring][uuid][local] */ 


EXTERN_C const IID IID_IAMRebuild;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("02EF04DD-7580-11d1-BECE-00C04FB6E937")
    IAMRebuild : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RebuildNow( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMRebuildVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMRebuild __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMRebuild __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMRebuild __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RebuildNow )( 
            IAMRebuild __RPC_FAR * This);
        
        END_INTERFACE
    } IAMRebuildVtbl;

    interface IAMRebuild
    {
        CONST_VTBL struct IAMRebuildVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMRebuild_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMRebuild_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMRebuild_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMRebuild_RebuildNow(This)	\
    (This)->lpVtbl -> RebuildNow(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMRebuild_RebuildNow_Proxy( 
    IAMRebuild __RPC_FAR * This);


void __RPC_STUB IAMRebuild_RebuildNow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMRebuild_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_playlist_0351 */
/* [local] */ 

EXTERN_GUID(IID_IAMPlayListItem,0x56a868ff,0x0ad4,0x11ce,0xb0,0xa3,0x0,0x20,0xaf,0x0b,0xa7,0x70);
EXTERN_GUID(IID_IAMRebuild,0x2ef04dd,0x7580,0x11d1,0xbe,0xce,0x0,0xc0,0x4f,0xb6,0xe9,0x37);
EXTERN_GUID(IID_IAMPlayList,0x56a868fe,0x0ad4,0x11ce,0xb0,0xa3,0x0,0x20,0xaf,0x0b,0xa7,0x70);
EXTERN_GUID(SPECIFYPAGES_STATISTICS,0x4c437b92,0x6e9e,0x11d1,0xa7,0x4,0x0,0x60,0x97,0xc4,0xe4,0x76);
EXTERN_GUID(IID_ISpecifyParticularPages,0x4c437b91,0x6e9e,0x11d1,0xa7,0x4,0x0,0x60,0x97,0xc4,0xe4,0x76);


extern RPC_IF_HANDLE __MIDL_itf_playlist_0351_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_playlist_0351_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


