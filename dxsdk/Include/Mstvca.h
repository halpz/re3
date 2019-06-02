
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for mstvca.idl:
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

#ifndef __mstvca_h__
#define __mstvca_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICAManagerInternal_FWD_DEFINED__
#define __ICAManagerInternal_FWD_DEFINED__
typedef interface ICAManagerInternal ICAManagerInternal;
#endif 	/* __ICAManagerInternal_FWD_DEFINED__ */


#ifndef __ICAManagerXProxy_FWD_DEFINED__
#define __ICAManagerXProxy_FWD_DEFINED__
typedef interface ICAManagerXProxy ICAManagerXProxy;
#endif 	/* __ICAManagerXProxy_FWD_DEFINED__ */


#ifndef __ICAPolicies_FWD_DEFINED__
#define __ICAPolicies_FWD_DEFINED__
typedef interface ICAPolicies ICAPolicies;
#endif 	/* __ICAPolicies_FWD_DEFINED__ */


#ifndef __ICAPoliciesInternal_FWD_DEFINED__
#define __ICAPoliciesInternal_FWD_DEFINED__
typedef interface ICAPoliciesInternal ICAPoliciesInternal;
#endif 	/* __ICAPoliciesInternal_FWD_DEFINED__ */


#ifndef __ICATolls_FWD_DEFINED__
#define __ICATolls_FWD_DEFINED__
typedef interface ICATolls ICATolls;
#endif 	/* __ICATolls_FWD_DEFINED__ */


#ifndef __ICATollsInternal_FWD_DEFINED__
#define __ICATollsInternal_FWD_DEFINED__
typedef interface ICATollsInternal ICATollsInternal;
#endif 	/* __ICATollsInternal_FWD_DEFINED__ */


#ifndef __ICADenials_FWD_DEFINED__
#define __ICADenials_FWD_DEFINED__
typedef interface ICADenials ICADenials;
#endif 	/* __ICADenials_FWD_DEFINED__ */


#ifndef __ICADenialsInternal_FWD_DEFINED__
#define __ICADenialsInternal_FWD_DEFINED__
typedef interface ICADenialsInternal ICADenialsInternal;
#endif 	/* __ICADenialsInternal_FWD_DEFINED__ */


#ifndef __ICAOffers_FWD_DEFINED__
#define __ICAOffers_FWD_DEFINED__
typedef interface ICAOffers ICAOffers;
#endif 	/* __ICAOffers_FWD_DEFINED__ */


#ifndef __ICAComponents_FWD_DEFINED__
#define __ICAComponents_FWD_DEFINED__
typedef interface ICAComponents ICAComponents;
#endif 	/* __ICAComponents_FWD_DEFINED__ */


#ifndef __ICAComponentInternal_FWD_DEFINED__
#define __ICAComponentInternal_FWD_DEFINED__
typedef interface ICAComponentInternal ICAComponentInternal;
#endif 	/* __ICAComponentInternal_FWD_DEFINED__ */


#ifndef __ICADefaultDlg_FWD_DEFINED__
#define __ICADefaultDlg_FWD_DEFINED__
typedef interface ICADefaultDlg ICADefaultDlg;
#endif 	/* __ICADefaultDlg_FWD_DEFINED__ */


#ifndef ___ICAResDenialTreeEvents_FWD_DEFINED__
#define ___ICAResDenialTreeEvents_FWD_DEFINED__
typedef interface _ICAResDenialTreeEvents _ICAResDenialTreeEvents;
#endif 	/* ___ICAResDenialTreeEvents_FWD_DEFINED__ */


#ifndef ___ICAManagerEvents_FWD_DEFINED__
#define ___ICAManagerEvents_FWD_DEFINED__
typedef interface _ICAManagerEvents _ICAManagerEvents;
#endif 	/* ___ICAManagerEvents_FWD_DEFINED__ */


#ifndef ___ICARequestEvents_FWD_DEFINED__
#define ___ICARequestEvents_FWD_DEFINED__
typedef interface _ICARequestEvents _ICARequestEvents;
#endif 	/* ___ICARequestEvents_FWD_DEFINED__ */


#ifndef ___ICAPoliciesEvents_FWD_DEFINED__
#define ___ICAPoliciesEvents_FWD_DEFINED__
typedef interface _ICAPoliciesEvents _ICAPoliciesEvents;
#endif 	/* ___ICAPoliciesEvents_FWD_DEFINED__ */


#ifndef ___ICATollsEvents_FWD_DEFINED__
#define ___ICATollsEvents_FWD_DEFINED__
typedef interface _ICATollsEvents _ICATollsEvents;
#endif 	/* ___ICATollsEvents_FWD_DEFINED__ */


#ifndef ___ICADenialsEvents_FWD_DEFINED__
#define ___ICADenialsEvents_FWD_DEFINED__
typedef interface _ICADenialsEvents _ICADenialsEvents;
#endif 	/* ___ICADenialsEvents_FWD_DEFINED__ */


#ifndef ___ICAOffersEvents_FWD_DEFINED__
#define ___ICAOffersEvents_FWD_DEFINED__
typedef interface _ICAOffersEvents _ICAOffersEvents;
#endif 	/* ___ICAOffersEvents_FWD_DEFINED__ */


#ifndef ___ICAComponentsEvents_FWD_DEFINED__
#define ___ICAComponentsEvents_FWD_DEFINED__
typedef interface _ICAComponentsEvents _ICAComponentsEvents;
#endif 	/* ___ICAComponentsEvents_FWD_DEFINED__ */


#ifndef __ICAManager_FWD_DEFINED__
#define __ICAManager_FWD_DEFINED__
typedef interface ICAManager ICAManager;
#endif 	/* __ICAManager_FWD_DEFINED__ */


#ifndef __ICARequest_FWD_DEFINED__
#define __ICARequest_FWD_DEFINED__
typedef interface ICARequest ICARequest;
#endif 	/* __ICARequest_FWD_DEFINED__ */


#ifndef __ICAPolicy_FWD_DEFINED__
#define __ICAPolicy_FWD_DEFINED__
typedef interface ICAPolicy ICAPolicy;
#endif 	/* __ICAPolicy_FWD_DEFINED__ */


#ifndef __ICAToll_FWD_DEFINED__
#define __ICAToll_FWD_DEFINED__
typedef interface ICAToll ICAToll;
#endif 	/* __ICAToll_FWD_DEFINED__ */


#ifndef __ICADenial_FWD_DEFINED__
#define __ICADenial_FWD_DEFINED__
typedef interface ICADenial ICADenial;
#endif 	/* __ICADenial_FWD_DEFINED__ */


#ifndef __ICAOffer_FWD_DEFINED__
#define __ICAOffer_FWD_DEFINED__
typedef interface ICAOffer ICAOffer;
#endif 	/* __ICAOffer_FWD_DEFINED__ */


#ifndef __ICAComponent_FWD_DEFINED__
#define __ICAComponent_FWD_DEFINED__
typedef interface ICAComponent ICAComponent;
#endif 	/* __ICAComponent_FWD_DEFINED__ */


#ifndef __CAManager_FWD_DEFINED__
#define __CAManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAManager CAManager;
#else
typedef struct CAManager CAManager;
#endif /* __cplusplus */

#endif 	/* __CAManager_FWD_DEFINED__ */


#ifndef __CAManagerProxy_FWD_DEFINED__
#define __CAManagerProxy_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAManagerProxy CAManagerProxy;
#else
typedef struct CAManagerProxy CAManagerProxy;
#endif /* __cplusplus */

#endif 	/* __CAManagerProxy_FWD_DEFINED__ */


#ifndef __CADenials_FWD_DEFINED__
#define __CADenials_FWD_DEFINED__

#ifdef __cplusplus
typedef class CADenials CADenials;
#else
typedef struct CADenials CADenials;
#endif /* __cplusplus */

#endif 	/* __CADenials_FWD_DEFINED__ */


#ifndef __CAOffer_FWD_DEFINED__
#define __CAOffer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAOffer CAOffer;
#else
typedef struct CAOffer CAOffer;
#endif /* __cplusplus */

#endif 	/* __CAOffer_FWD_DEFINED__ */


#ifndef __ICAResDenialTree_FWD_DEFINED__
#define __ICAResDenialTree_FWD_DEFINED__
typedef interface ICAResDenialTree ICAResDenialTree;
#endif 	/* __ICAResDenialTree_FWD_DEFINED__ */


#ifndef __CAResDenialTree_FWD_DEFINED__
#define __CAResDenialTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAResDenialTree CAResDenialTree;
#else
typedef struct CAResDenialTree CAResDenialTree;
#endif /* __cplusplus */

#endif 	/* __CAResDenialTree_FWD_DEFINED__ */


#ifndef ___ICADefaultDlgEvents_FWD_DEFINED__
#define ___ICADefaultDlgEvents_FWD_DEFINED__
typedef interface _ICADefaultDlgEvents _ICADefaultDlgEvents;
#endif 	/* ___ICADefaultDlgEvents_FWD_DEFINED__ */


#ifndef __CADefaultDlg_FWD_DEFINED__
#define __CADefaultDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class CADefaultDlg CADefaultDlg;
#else
typedef struct CADefaultDlg CADefaultDlg;
#endif /* __cplusplus */

#endif 	/* __CADefaultDlg_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "tuner.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mstvca_0000 */
/* [local] */ 















typedef /* [public][public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_mstvca_0000_0001
    {	Unselected	= 0,
	Selected	= 1
    } 	CATollState;

typedef /* [public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_mstvca_0000_0002
    {	Denied	= 0,
	Transient	= 1,
	DescriptionShort	= 10,
	DescriptionLong	= 11,
	DescriptionHTML	= 12,
	DescriptionXML	= 13
    } 	CADenialState;

typedef /* [public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_mstvca_0000_0003
    {	Short	= 0,
	Long	= 1,
	URL	= 2,
	HTML	= 3,
	XML	= 4,
	kDescEnd	= 5
    } 	CADescFormat;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_mstvca_0000_0004
    {	Request	= 1,
	ComponentX	= 2,
	Offers	= 4,
	PaidTolls	= 8,
	Policies	= 16,
	Standard	= 15,
	All	= 31
    } 	CAUIDisplayFields;



extern RPC_IF_HANDLE __MIDL_itf_mstvca_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstvca_0000_v0_0_s_ifspec;

#ifndef __ICAManagerInternal_INTERFACE_DEFINED__
#define __ICAManagerInternal_INTERFACE_DEFINED__

/* interface ICAManagerInternal */
/* [unique][helpstring][restricted][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAManagerInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166301-DF8A-463a-B620-7BEC23542010")
    ICAManagerInternal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkDirty( 
            /* [in] */ BOOL fDirty) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkDirty( 
            /* [retval][out] */ BOOL *pfDirty) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TuneRequest( 
            /* [in] */ ITuneRequest *ptunereq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDefaultUI( 
            /* [out] */ HWND *phwnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDefaultUI( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CAManagerMain( 
            /* [retval][out] */ ICAManager **ppManagerMain) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BroadcastEventService( 
            /* [in] */ IBroadcastEvent *pBroadcastEventService) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BroadcastEventService( 
            /* [retval][out] */ IBroadcastEvent **ppBroadcastEventService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayDefaultUI( 
            /* [in] */ VARIANT_BOOL fDisplay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableDefaultUIPayTollsButton( 
            /* [in] */ VARIANT_BOOL fEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDefaultUIForToll( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enState) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TuneRequestInt( 
            /* [in] */ ITuneRequest *ptunereq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDenialsFor( 
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveDenialsFor( 
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestActivated( 
            /* [in] */ ICARequest *pReq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDeactivated( 
            /* [in] */ ICARequest *pReq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferAdded( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferRemoved( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyAdded( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyRemoved( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialAdded( 
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialRemoved( 
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollAdded( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollRemoved( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialAdded( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialRemoved( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollAdded( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollRemoved( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollStateChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialStateChanged( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialAdded( 
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialRemoved( 
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAManagerInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAManagerInternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAManagerInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAManagerInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ICAManagerInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICAManagerInternal * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarkDirty )( 
            ICAManagerInternal * This,
            /* [in] */ BOOL fDirty);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarkDirty )( 
            ICAManagerInternal * This,
            /* [retval][out] */ BOOL *pfDirty);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuneRequest )( 
            ICAManagerInternal * This,
            /* [in] */ ITuneRequest *ptunereq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDefaultUI )( 
            ICAManagerInternal * This,
            /* [out] */ HWND *phwnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDefaultUI )( 
            ICAManagerInternal * This,
            /* [in] */ HWND hwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CAManagerMain )( 
            ICAManagerInternal * This,
            /* [retval][out] */ ICAManager **ppManagerMain);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BroadcastEventService )( 
            ICAManagerInternal * This,
            /* [in] */ IBroadcastEvent *pBroadcastEventService);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BroadcastEventService )( 
            ICAManagerInternal * This,
            /* [retval][out] */ IBroadcastEvent **ppBroadcastEventService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisplayDefaultUI )( 
            ICAManagerInternal * This,
            /* [in] */ VARIANT_BOOL fDisplay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableDefaultUIPayTollsButton )( 
            ICAManagerInternal * This,
            /* [in] */ VARIANT_BOOL fEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDefaultUIForToll )( 
            ICAManagerInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enState);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TuneRequestInt )( 
            ICAManagerInternal * This,
            /* [in] */ ITuneRequest *ptunereq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddDenialsFor )( 
            ICAManagerInternal * This,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveDenialsFor )( 
            ICAManagerInternal * This,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestActivated )( 
            ICAManagerInternal * This,
            /* [in] */ ICARequest *pReq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDeactivated )( 
            ICAManagerInternal * This,
            /* [in] */ ICARequest *pReq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollStateChanged )( 
            ICAManagerInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialStateChanged )( 
            ICAManagerInternal * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialAdded )( 
            ICAManagerInternal * This,
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialRemoved )( 
            ICAManagerInternal * This,
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        END_INTERFACE
    } ICAManagerInternalVtbl;

    interface ICAManagerInternal
    {
        CONST_VTBL struct ICAManagerInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAManagerInternal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAManagerInternal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAManagerInternal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAManagerInternal_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define ICAManagerInternal_Load(This)	\
    (This)->lpVtbl -> Load(This)

#define ICAManagerInternal_put_MarkDirty(This,fDirty)	\
    (This)->lpVtbl -> put_MarkDirty(This,fDirty)

#define ICAManagerInternal_get_MarkDirty(This,pfDirty)	\
    (This)->lpVtbl -> get_MarkDirty(This,pfDirty)

#define ICAManagerInternal_put_TuneRequest(This,ptunereq)	\
    (This)->lpVtbl -> put_TuneRequest(This,ptunereq)

#define ICAManagerInternal_GetDefaultUI(This,phwnd)	\
    (This)->lpVtbl -> GetDefaultUI(This,phwnd)

#define ICAManagerInternal_SetDefaultUI(This,hwnd)	\
    (This)->lpVtbl -> SetDefaultUI(This,hwnd)

#define ICAManagerInternal_get_CAManagerMain(This,ppManagerMain)	\
    (This)->lpVtbl -> get_CAManagerMain(This,ppManagerMain)

#define ICAManagerInternal_put_BroadcastEventService(This,pBroadcastEventService)	\
    (This)->lpVtbl -> put_BroadcastEventService(This,pBroadcastEventService)

#define ICAManagerInternal_get_BroadcastEventService(This,ppBroadcastEventService)	\
    (This)->lpVtbl -> get_BroadcastEventService(This,ppBroadcastEventService)

#define ICAManagerInternal_DisplayDefaultUI(This,fDisplay)	\
    (This)->lpVtbl -> DisplayDefaultUI(This,fDisplay)

#define ICAManagerInternal_EnableDefaultUIPayTollsButton(This,fEnabled)	\
    (This)->lpVtbl -> EnableDefaultUIPayTollsButton(This,fEnabled)

#define ICAManagerInternal_UpdateDefaultUIForToll(This,pToll,enState)	\
    (This)->lpVtbl -> UpdateDefaultUIForToll(This,pToll,enState)

#define ICAManagerInternal_put_TuneRequestInt(This,ptunereq)	\
    (This)->lpVtbl -> put_TuneRequestInt(This,ptunereq)

#define ICAManagerInternal_AddDenialsFor(This,pUnk)	\
    (This)->lpVtbl -> AddDenialsFor(This,pUnk)

#define ICAManagerInternal_RemoveDenialsFor(This,pUnk)	\
    (This)->lpVtbl -> RemoveDenialsFor(This,pUnk)

#define ICAManagerInternal_NotifyRequestActivated(This,pReq)	\
    (This)->lpVtbl -> NotifyRequestActivated(This,pReq)

#define ICAManagerInternal_NotifyRequestDeactivated(This,pReq)	\
    (This)->lpVtbl -> NotifyRequestDeactivated(This,pReq)

#define ICAManagerInternal_NotifyOfferAdded(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferAdded(This,pOffer,cOffers)

#define ICAManagerInternal_NotifyOfferRemoved(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferRemoved(This,pOffer,cOffers)

#define ICAManagerInternal_NotifyPolicyAdded(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyAdded(This,pPolicy,cPolicies)

#define ICAManagerInternal_NotifyPolicyRemoved(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyRemoved(This,pPolicy,cPolicies)

#define ICAManagerInternal_NotifyRequestDenialAdded(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialAdded(This,pReq,pDenial,cDenials)

#define ICAManagerInternal_NotifyRequestDenialRemoved(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialRemoved(This,pReq,pDenial,cDenials)

#define ICAManagerInternal_NotifyDenialTollAdded(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollAdded(This,pDenial,pToll,cTolls)

#define ICAManagerInternal_NotifyDenialTollRemoved(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollRemoved(This,pDenial,pToll,cTolls)

#define ICAManagerInternal_NotifyTollDenialAdded(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialAdded(This,pToll,pDenial,cDenials)

#define ICAManagerInternal_NotifyTollDenialRemoved(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialRemoved(This,pToll,pDenial,cDenials)

#define ICAManagerInternal_NotifyOfferTollAdded(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollAdded(This,pOffer,pToll,cTolls)

#define ICAManagerInternal_NotifyOfferTollRemoved(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollRemoved(This,pOffer,pToll,cTolls)

#define ICAManagerInternal_NotifyTollStateChanged(This,pToll,enStateLast)	\
    (This)->lpVtbl -> NotifyTollStateChanged(This,pToll,enStateLast)

#define ICAManagerInternal_NotifyDenialStateChanged(This,pDenial,enStateLast)	\
    (This)->lpVtbl -> NotifyDenialStateChanged(This,pDenial,enStateLast)

#define ICAManagerInternal_NotifyComponentDenialAdded(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialAdded(This,pReq,pDenial,cDenials)

#define ICAManagerInternal_NotifyComponentDenialRemoved(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialRemoved(This,pReq,pDenial,cDenials)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_Save_Proxy( 
    ICAManagerInternal * This);


void __RPC_STUB ICAManagerInternal_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_Load_Proxy( 
    ICAManagerInternal * This);


void __RPC_STUB ICAManagerInternal_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_put_MarkDirty_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ BOOL fDirty);


void __RPC_STUB ICAManagerInternal_put_MarkDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_get_MarkDirty_Proxy( 
    ICAManagerInternal * This,
    /* [retval][out] */ BOOL *pfDirty);


void __RPC_STUB ICAManagerInternal_get_MarkDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_put_TuneRequest_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ITuneRequest *ptunereq);


void __RPC_STUB ICAManagerInternal_put_TuneRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_GetDefaultUI_Proxy( 
    ICAManagerInternal * This,
    /* [out] */ HWND *phwnd);


void __RPC_STUB ICAManagerInternal_GetDefaultUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_SetDefaultUI_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ICAManagerInternal_SetDefaultUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_get_CAManagerMain_Proxy( 
    ICAManagerInternal * This,
    /* [retval][out] */ ICAManager **ppManagerMain);


void __RPC_STUB ICAManagerInternal_get_CAManagerMain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_put_BroadcastEventService_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ IBroadcastEvent *pBroadcastEventService);


void __RPC_STUB ICAManagerInternal_put_BroadcastEventService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_get_BroadcastEventService_Proxy( 
    ICAManagerInternal * This,
    /* [retval][out] */ IBroadcastEvent **ppBroadcastEventService);


void __RPC_STUB ICAManagerInternal_get_BroadcastEventService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_DisplayDefaultUI_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ VARIANT_BOOL fDisplay);


void __RPC_STUB ICAManagerInternal_DisplayDefaultUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_EnableDefaultUIPayTollsButton_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ VARIANT_BOOL fEnabled);


void __RPC_STUB ICAManagerInternal_EnableDefaultUIPayTollsButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_UpdateDefaultUIForToll_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enState);


void __RPC_STUB ICAManagerInternal_UpdateDefaultUIForToll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_put_TuneRequestInt_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ITuneRequest *ptunereq);


void __RPC_STUB ICAManagerInternal_put_TuneRequestInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_AddDenialsFor_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ICAManagerInternal_AddDenialsFor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_RemoveDenialsFor_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ICAManagerInternal_RemoveDenialsFor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyRequestActivated_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAManagerInternal_NotifyRequestActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyRequestDeactivated_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAManagerInternal_NotifyRequestDeactivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyOfferAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAManagerInternal_NotifyOfferAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyOfferRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAManagerInternal_NotifyOfferRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyPolicyAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAManagerInternal_NotifyPolicyAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyPolicyRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAManagerInternal_NotifyPolicyRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyRequestDenialAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICARequest *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyRequestDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyRequestDenialRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICARequest *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyRequestDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyDenialTollAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerInternal_NotifyDenialTollAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyDenialTollRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerInternal_NotifyDenialTollRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyTollDenialAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyTollDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyTollDenialRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyTollDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyOfferTollAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerInternal_NotifyOfferTollAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyOfferTollRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerInternal_NotifyOfferTollRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyTollStateChanged_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateLast);


void __RPC_STUB ICAManagerInternal_NotifyTollStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyDenialStateChanged_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ CADenialState enStateLast);


void __RPC_STUB ICAManagerInternal_NotifyDenialStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyComponentDenialAdded_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAComponent *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyComponentDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerInternal_NotifyComponentDenialRemoved_Proxy( 
    ICAManagerInternal * This,
    /* [in] */ ICAComponent *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerInternal_NotifyComponentDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAManagerInternal_INTERFACE_DEFINED__ */


#ifndef __ICAManagerXProxy_INTERFACE_DEFINED__
#define __ICAManagerXProxy_INTERFACE_DEFINED__

/* interface ICAManagerXProxy */
/* [unique][helpstring][restricted][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAManagerXProxy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166302-DF8A-463a-B620-7BEC23542010")
    ICAManagerXProxy : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PunkCAManagerProxy( 
            /* [retval][out] */ IUnknown **ppUnkCAManagerProxy) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestActivated_XProxy( 
            /* [in] */ ICARequest *pReq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDeactivated_XProxy( 
            /* [in] */ ICARequest *pReq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferAdded_XProxy( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferRemoved_XProxy( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyAdded_XProxy( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyRemoved_XProxy( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialAdded_XProxy( 
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialRemoved_XProxy( 
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollAdded_XProxy( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollRemoved_XProxy( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialAdded_XProxy( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialRemoved_XProxy( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollAdded_XProxy( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollRemoved_XProxy( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollStateChanged_XProxy( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialStateChanged_XProxy( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialAdded_XProxy( 
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialRemoved_XProxy( 
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAManagerXProxyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAManagerXProxy * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAManagerXProxy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAManagerXProxy * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PunkCAManagerProxy )( 
            ICAManagerXProxy * This,
            /* [retval][out] */ IUnknown **ppUnkCAManagerProxy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestActivated_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICARequest *pReq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDeactivated_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICARequest *pReq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICARequest *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollStateChanged_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialStateChanged_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialAdded_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialRemoved_XProxy )( 
            ICAManagerXProxy * This,
            /* [in] */ ICAComponent *pReq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        END_INTERFACE
    } ICAManagerXProxyVtbl;

    interface ICAManagerXProxy
    {
        CONST_VTBL struct ICAManagerXProxyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAManagerXProxy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAManagerXProxy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAManagerXProxy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAManagerXProxy_get_PunkCAManagerProxy(This,ppUnkCAManagerProxy)	\
    (This)->lpVtbl -> get_PunkCAManagerProxy(This,ppUnkCAManagerProxy)

#define ICAManagerXProxy_NotifyRequestActivated_XProxy(This,pReq)	\
    (This)->lpVtbl -> NotifyRequestActivated_XProxy(This,pReq)

#define ICAManagerXProxy_NotifyRequestDeactivated_XProxy(This,pReq)	\
    (This)->lpVtbl -> NotifyRequestDeactivated_XProxy(This,pReq)

#define ICAManagerXProxy_NotifyOfferAdded_XProxy(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferAdded_XProxy(This,pOffer,cOffers)

#define ICAManagerXProxy_NotifyOfferRemoved_XProxy(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferRemoved_XProxy(This,pOffer,cOffers)

#define ICAManagerXProxy_NotifyPolicyAdded_XProxy(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyAdded_XProxy(This,pPolicy,cPolicies)

#define ICAManagerXProxy_NotifyPolicyRemoved_XProxy(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyRemoved_XProxy(This,pPolicy,cPolicies)

#define ICAManagerXProxy_NotifyRequestDenialAdded_XProxy(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialAdded_XProxy(This,pReq,pDenial,cDenials)

#define ICAManagerXProxy_NotifyRequestDenialRemoved_XProxy(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialRemoved_XProxy(This,pReq,pDenial,cDenials)

#define ICAManagerXProxy_NotifyDenialTollAdded_XProxy(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollAdded_XProxy(This,pDenial,pToll,cTolls)

#define ICAManagerXProxy_NotifyDenialTollRemoved_XProxy(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollRemoved_XProxy(This,pDenial,pToll,cTolls)

#define ICAManagerXProxy_NotifyTollDenialAdded_XProxy(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialAdded_XProxy(This,pToll,pDenial,cDenials)

#define ICAManagerXProxy_NotifyTollDenialRemoved_XProxy(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialRemoved_XProxy(This,pToll,pDenial,cDenials)

#define ICAManagerXProxy_NotifyOfferTollAdded_XProxy(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollAdded_XProxy(This,pOffer,pToll,cTolls)

#define ICAManagerXProxy_NotifyOfferTollRemoved_XProxy(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollRemoved_XProxy(This,pOffer,pToll,cTolls)

#define ICAManagerXProxy_NotifyTollStateChanged_XProxy(This,pToll,enStateLast)	\
    (This)->lpVtbl -> NotifyTollStateChanged_XProxy(This,pToll,enStateLast)

#define ICAManagerXProxy_NotifyDenialStateChanged_XProxy(This,pDenial,enStateLast)	\
    (This)->lpVtbl -> NotifyDenialStateChanged_XProxy(This,pDenial,enStateLast)

#define ICAManagerXProxy_NotifyComponentDenialAdded_XProxy(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialAdded_XProxy(This,pReq,pDenial,cDenials)

#define ICAManagerXProxy_NotifyComponentDenialRemoved_XProxy(This,pReq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialRemoved_XProxy(This,pReq,pDenial,cDenials)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_get_PunkCAManagerProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [retval][out] */ IUnknown **ppUnkCAManagerProxy);


void __RPC_STUB ICAManagerXProxy_get_PunkCAManagerProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyRequestActivated_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAManagerXProxy_NotifyRequestActivated_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyRequestDeactivated_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAManagerXProxy_NotifyRequestDeactivated_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyOfferAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAManagerXProxy_NotifyOfferAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyOfferRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAManagerXProxy_NotifyOfferRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyPolicyAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAManagerXProxy_NotifyPolicyAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyPolicyRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAManagerXProxy_NotifyPolicyRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyRequestDenialAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICARequest *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyRequestDenialAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyRequestDenialRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICARequest *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyRequestDenialRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyDenialTollAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerXProxy_NotifyDenialTollAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyDenialTollRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerXProxy_NotifyDenialTollRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyTollDenialAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyTollDenialAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyTollDenialRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyTollDenialRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyOfferTollAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerXProxy_NotifyOfferTollAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyOfferTollRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAManagerXProxy_NotifyOfferTollRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyTollStateChanged_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateLast);


void __RPC_STUB ICAManagerXProxy_NotifyTollStateChanged_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyDenialStateChanged_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ CADenialState enStateLast);


void __RPC_STUB ICAManagerXProxy_NotifyDenialStateChanged_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyComponentDenialAdded_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAComponent *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyComponentDenialAdded_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAManagerXProxy_NotifyComponentDenialRemoved_XProxy_Proxy( 
    ICAManagerXProxy * This,
    /* [in] */ ICAComponent *pReq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAManagerXProxy_NotifyComponentDenialRemoved_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAManagerXProxy_INTERFACE_DEFINED__ */


#ifndef __ICAPolicies_INTERFACE_DEFINED__
#define __ICAPolicies_INTERFACE_DEFINED__

/* interface ICAPolicies */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAPolicies;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166420-DF8A-463a-B620-7BEC23542010")
    ICAPolicies : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAPolicy **ppPolicy) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICAPolicy *pPolicy) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAPoliciesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAPolicies * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAPolicies * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAPolicies * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAPolicies * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAPolicies * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAPolicies * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAPolicies * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICAPolicies * This,
            /* [retval][out] */ IUnknown **ppCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICAPolicies * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICAPolicies * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAPolicy **ppPolicy);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICAPolicies * This,
            /* [in] */ ICAPolicy *pPolicy);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICAPolicies * This,
            /* [in] */ VARIANT Index);
        
        END_INTERFACE
    } ICAPoliciesVtbl;

    interface ICAPolicies
    {
        CONST_VTBL struct ICAPoliciesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAPolicies_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAPolicies_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAPolicies_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAPolicies_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAPolicies_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAPolicies_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAPolicies_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAPolicies_get__NewEnum(This,ppCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,ppCollection)

#define ICAPolicies_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ICAPolicies_get_Item(This,Index,ppPolicy)	\
    (This)->lpVtbl -> get_Item(This,Index,ppPolicy)

#define ICAPolicies_Add(This,pPolicy)	\
    (This)->lpVtbl -> Add(This,pPolicy)

#define ICAPolicies_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicies_get__NewEnum_Proxy( 
    ICAPolicies * This,
    /* [retval][out] */ IUnknown **ppCollection);


void __RPC_STUB ICAPolicies_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicies_get_Count_Proxy( 
    ICAPolicies * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICAPolicies_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicies_get_Item_Proxy( 
    ICAPolicies * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ICAPolicy **ppPolicy);


void __RPC_STUB ICAPolicies_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICAPolicies_Add_Proxy( 
    ICAPolicies * This,
    /* [in] */ ICAPolicy *pPolicy);


void __RPC_STUB ICAPolicies_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICAPolicies_Remove_Proxy( 
    ICAPolicies * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ICAPolicies_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAPolicies_INTERFACE_DEFINED__ */


#ifndef __ICAPoliciesInternal_INTERFACE_DEFINED__
#define __ICAPoliciesInternal_INTERFACE_DEFINED__

/* interface ICAPoliciesInternal */
/* [unique][helpstring][restricted][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAPoliciesInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166421-DF8A-463a-B620-7BEC23542010")
    ICAPoliciesInternal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckRequest( 
            /* [in] */ ICARequest *pReq) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAPoliciesInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAPoliciesInternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAPoliciesInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAPoliciesInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCAManager )( 
            ICAPoliciesInternal * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckRequest )( 
            ICAPoliciesInternal * This,
            /* [in] */ ICARequest *pReq);
        
        END_INTERFACE
    } ICAPoliciesInternalVtbl;

    interface ICAPoliciesInternal
    {
        CONST_VTBL struct ICAPoliciesInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAPoliciesInternal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAPoliciesInternal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAPoliciesInternal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAPoliciesInternal_SetCAManager(This,pManager)	\
    (This)->lpVtbl -> SetCAManager(This,pManager)

#define ICAPoliciesInternal_CheckRequest(This,pReq)	\
    (This)->lpVtbl -> CheckRequest(This,pReq)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAPoliciesInternal_SetCAManager_Proxy( 
    ICAPoliciesInternal * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICAPoliciesInternal_SetCAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAPoliciesInternal_CheckRequest_Proxy( 
    ICAPoliciesInternal * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAPoliciesInternal_CheckRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAPoliciesInternal_INTERFACE_DEFINED__ */


#ifndef __ICATolls_INTERFACE_DEFINED__
#define __ICATolls_INTERFACE_DEFINED__

/* interface ICATolls */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICATolls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166430-DF8A-463a-B620-7BEC23542010")
    ICATolls : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAToll **ppToll) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICAToll *pToll) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICATollsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICATolls * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICATolls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICATolls * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICATolls * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICATolls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICATolls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICATolls * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICATolls * This,
            /* [retval][out] */ IUnknown **ppCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICATolls * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICATolls * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAToll **ppToll);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICATolls * This,
            /* [in] */ ICAToll *pToll);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICATolls * This,
            /* [in] */ VARIANT Index);
        
        END_INTERFACE
    } ICATollsVtbl;

    interface ICATolls
    {
        CONST_VTBL struct ICATollsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICATolls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICATolls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICATolls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICATolls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICATolls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICATolls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICATolls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICATolls_get__NewEnum(This,ppCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,ppCollection)

#define ICATolls_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ICATolls_get_Item(This,Index,ppToll)	\
    (This)->lpVtbl -> get_Item(This,Index,ppToll)

#define ICATolls_Add(This,pToll)	\
    (This)->lpVtbl -> Add(This,pToll)

#define ICATolls_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ICATolls_get__NewEnum_Proxy( 
    ICATolls * This,
    /* [retval][out] */ IUnknown **ppCollection);


void __RPC_STUB ICATolls_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICATolls_get_Count_Proxy( 
    ICATolls * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICATolls_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICATolls_get_Item_Proxy( 
    ICATolls * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ICAToll **ppToll);


void __RPC_STUB ICATolls_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICATolls_Add_Proxy( 
    ICATolls * This,
    /* [in] */ ICAToll *pToll);


void __RPC_STUB ICATolls_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICATolls_Remove_Proxy( 
    ICATolls * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ICATolls_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICATolls_INTERFACE_DEFINED__ */


#ifndef __ICATollsInternal_INTERFACE_DEFINED__
#define __ICATollsInternal_INTERFACE_DEFINED__

/* interface ICATollsInternal */
/* [unique][helpstring][restricted][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICATollsInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166431-DF8A-463a-B620-7BEC23542010")
    ICATollsInternal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCAManager( 
            /* [out] */ ICAManager **ppManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMustPersist( 
            /* [in] */ BOOL fMustPersist) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IStorage *pstore,
            /* [in] */ BSTR bstrPrefix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IStorage *pstore,
            /* [in] */ BSTR bstrPrefix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyStateChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollSelectionChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ BOOL fSelected) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICATollsInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICATollsInternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICATollsInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICATollsInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCAManager )( 
            ICATollsInternal * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCAManager )( 
            ICATollsInternal * This,
            /* [out] */ ICAManager **ppManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMustPersist )( 
            ICATollsInternal * This,
            /* [in] */ BOOL fMustPersist);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ICATollsInternal * This,
            /* [in] */ IStorage *pstore,
            /* [in] */ BSTR bstrPrefix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICATollsInternal * This,
            /* [in] */ IStorage *pstore,
            /* [in] */ BSTR bstrPrefix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyStateChanged )( 
            ICATollsInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollSelectionChanged )( 
            ICATollsInternal * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ BOOL fSelected);
        
        END_INTERFACE
    } ICATollsInternalVtbl;

    interface ICATollsInternal
    {
        CONST_VTBL struct ICATollsInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICATollsInternal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICATollsInternal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICATollsInternal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICATollsInternal_SetCAManager(This,pManager)	\
    (This)->lpVtbl -> SetCAManager(This,pManager)

#define ICATollsInternal_GetCAManager(This,ppManager)	\
    (This)->lpVtbl -> GetCAManager(This,ppManager)

#define ICATollsInternal_SetMustPersist(This,fMustPersist)	\
    (This)->lpVtbl -> SetMustPersist(This,fMustPersist)

#define ICATollsInternal_Save(This,pstore,bstrPrefix)	\
    (This)->lpVtbl -> Save(This,pstore,bstrPrefix)

#define ICATollsInternal_Load(This,pstore,bstrPrefix)	\
    (This)->lpVtbl -> Load(This,pstore,bstrPrefix)

#define ICATollsInternal_NotifyStateChanged(This,pToll,enStateFrom)	\
    (This)->lpVtbl -> NotifyStateChanged(This,pToll,enStateFrom)

#define ICATollsInternal_NotifyTollSelectionChanged(This,pToll,fSelected)	\
    (This)->lpVtbl -> NotifyTollSelectionChanged(This,pToll,fSelected)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_SetCAManager_Proxy( 
    ICATollsInternal * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICATollsInternal_SetCAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_GetCAManager_Proxy( 
    ICATollsInternal * This,
    /* [out] */ ICAManager **ppManager);


void __RPC_STUB ICATollsInternal_GetCAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_SetMustPersist_Proxy( 
    ICATollsInternal * This,
    /* [in] */ BOOL fMustPersist);


void __RPC_STUB ICATollsInternal_SetMustPersist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_Save_Proxy( 
    ICATollsInternal * This,
    /* [in] */ IStorage *pstore,
    /* [in] */ BSTR bstrPrefix);


void __RPC_STUB ICATollsInternal_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_Load_Proxy( 
    ICATollsInternal * This,
    /* [in] */ IStorage *pstore,
    /* [in] */ BSTR bstrPrefix);


void __RPC_STUB ICATollsInternal_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_NotifyStateChanged_Proxy( 
    ICATollsInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateFrom);


void __RPC_STUB ICATollsInternal_NotifyStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICATollsInternal_NotifyTollSelectionChanged_Proxy( 
    ICATollsInternal * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ BOOL fSelected);


void __RPC_STUB ICATollsInternal_NotifyTollSelectionChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICATollsInternal_INTERFACE_DEFINED__ */


#ifndef __ICADenials_INTERFACE_DEFINED__
#define __ICADenials_INTERFACE_DEFINED__

/* interface ICADenials */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICADenials;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166440-DF8A-463a-B620-7BEC23542010")
    ICADenials : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICADenial **ppDenial) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddNew( 
            /* [in] */ ICAPolicy *ppolicy,
            /* [in] */ BSTR bstrShortDesc,
            /* [in] */ IUnknown *pUnkDeniedObject,
            /* [in] */ long enDenialState,
            /* [retval][out] */ ICADenial **ppDenial) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CountDenied( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CountSelected( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PaySelectedTolls( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICADenialsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICADenials * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICADenials * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICADenials * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICADenials * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICADenials * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICADenials * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICADenials * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICADenials * This,
            /* [retval][out] */ IUnknown **ppCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICADenials * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICADenials * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICADenial **ppDenial);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AddNew )( 
            ICADenials * This,
            /* [in] */ ICAPolicy *ppolicy,
            /* [in] */ BSTR bstrShortDesc,
            /* [in] */ IUnknown *pUnkDeniedObject,
            /* [in] */ long enDenialState,
            /* [retval][out] */ ICADenial **ppDenial);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICADenials * This,
            /* [in] */ VARIANT Index);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountDenied )( 
            ICADenials * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountSelected )( 
            ICADenials * This,
            /* [retval][out] */ long *Count);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PaySelectedTolls )( 
            ICADenials * This);
        
        END_INTERFACE
    } ICADenialsVtbl;

    interface ICADenials
    {
        CONST_VTBL struct ICADenialsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICADenials_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICADenials_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICADenials_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICADenials_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICADenials_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICADenials_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICADenials_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICADenials_get__NewEnum(This,ppCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,ppCollection)

#define ICADenials_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ICADenials_get_Item(This,Index,ppDenial)	\
    (This)->lpVtbl -> get_Item(This,Index,ppDenial)

#define ICADenials_get_AddNew(This,ppolicy,bstrShortDesc,pUnkDeniedObject,enDenialState,ppDenial)	\
    (This)->lpVtbl -> get_AddNew(This,ppolicy,bstrShortDesc,pUnkDeniedObject,enDenialState,ppDenial)

#define ICADenials_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ICADenials_get_CountDenied(This,Count)	\
    (This)->lpVtbl -> get_CountDenied(This,Count)

#define ICADenials_get_CountSelected(This,Count)	\
    (This)->lpVtbl -> get_CountSelected(This,Count)

#define ICADenials_PaySelectedTolls(This)	\
    (This)->lpVtbl -> PaySelectedTolls(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get__NewEnum_Proxy( 
    ICADenials * This,
    /* [retval][out] */ IUnknown **ppCollection);


void __RPC_STUB ICADenials_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get_Count_Proxy( 
    ICADenials * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICADenials_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get_Item_Proxy( 
    ICADenials * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ICADenial **ppDenial);


void __RPC_STUB ICADenials_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get_AddNew_Proxy( 
    ICADenials * This,
    /* [in] */ ICAPolicy *ppolicy,
    /* [in] */ BSTR bstrShortDesc,
    /* [in] */ IUnknown *pUnkDeniedObject,
    /* [in] */ long enDenialState,
    /* [retval][out] */ ICADenial **ppDenial);


void __RPC_STUB ICADenials_get_AddNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICADenials_Remove_Proxy( 
    ICADenials * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ICADenials_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get_CountDenied_Proxy( 
    ICADenials * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICADenials_get_CountDenied_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADenials_get_CountSelected_Proxy( 
    ICADenials * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICADenials_get_CountSelected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICADenials_PaySelectedTolls_Proxy( 
    ICADenials * This);


void __RPC_STUB ICADenials_PaySelectedTolls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICADenials_INTERFACE_DEFINED__ */


#ifndef __ICADenialsInternal_INTERFACE_DEFINED__
#define __ICADenialsInternal_INTERFACE_DEFINED__

/* interface ICADenialsInternal */
/* [unique][helpstring][restricted][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICADenialsInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166441-DF8A-463a-B620-7BEC23542010")
    ICADenialsInternal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialStateChanged( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICADenialsInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICADenialsInternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICADenialsInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICADenialsInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCAManager )( 
            ICADenialsInternal * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialStateChanged )( 
            ICADenialsInternal * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast);
        
        END_INTERFACE
    } ICADenialsInternalVtbl;

    interface ICADenialsInternal
    {
        CONST_VTBL struct ICADenialsInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICADenialsInternal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICADenialsInternal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICADenialsInternal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICADenialsInternal_SetCAManager(This,pManager)	\
    (This)->lpVtbl -> SetCAManager(This,pManager)

#define ICADenialsInternal_NotifyDenialStateChanged(This,pDenial,enStateLast)	\
    (This)->lpVtbl -> NotifyDenialStateChanged(This,pDenial,enStateLast)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICADenialsInternal_SetCAManager_Proxy( 
    ICADenialsInternal * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICADenialsInternal_SetCAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICADenialsInternal_NotifyDenialStateChanged_Proxy( 
    ICADenialsInternal * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ CADenialState enStateLast);


void __RPC_STUB ICADenialsInternal_NotifyDenialStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICADenialsInternal_INTERFACE_DEFINED__ */


#ifndef __ICAOffers_INTERFACE_DEFINED__
#define __ICAOffers_INTERFACE_DEFINED__

/* interface ICAOffers */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAOffers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166450-DF8A-463a-B620-7BEC23542010")
    ICAOffers : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAOffer **ppOffer) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddNew( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ BSTR bstrName,
            /* [in] */ DATE dateStart,
            /* [in] */ DATE dateEnd,
            /* [retval][out] */ ICAOffer **ppOffer) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAOffersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAOffers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAOffers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAOffers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAOffers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAOffers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAOffers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAOffers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICAOffers * This,
            /* [retval][out] */ IUnknown **ppCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICAOffers * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICAOffers * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAOffer **ppOffer);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AddNew )( 
            ICAOffers * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ BSTR bstrName,
            /* [in] */ DATE dateStart,
            /* [in] */ DATE dateEnd,
            /* [retval][out] */ ICAOffer **ppOffer);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICAOffers * This,
            /* [in] */ VARIANT Index);
        
        END_INTERFACE
    } ICAOffersVtbl;

    interface ICAOffers
    {
        CONST_VTBL struct ICAOffersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAOffers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAOffers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAOffers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAOffers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAOffers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAOffers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAOffers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAOffers_get__NewEnum(This,ppCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,ppCollection)

#define ICAOffers_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ICAOffers_get_Item(This,Index,ppOffer)	\
    (This)->lpVtbl -> get_Item(This,Index,ppOffer)

#define ICAOffers_get_AddNew(This,pPolicy,bstrName,dateStart,dateEnd,ppOffer)	\
    (This)->lpVtbl -> get_AddNew(This,pPolicy,bstrName,dateStart,dateEnd,ppOffer)

#define ICAOffers_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffers_get__NewEnum_Proxy( 
    ICAOffers * This,
    /* [retval][out] */ IUnknown **ppCollection);


void __RPC_STUB ICAOffers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffers_get_Count_Proxy( 
    ICAOffers * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICAOffers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffers_get_Item_Proxy( 
    ICAOffers * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ICAOffer **ppOffer);


void __RPC_STUB ICAOffers_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffers_get_AddNew_Proxy( 
    ICAOffers * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ BSTR bstrName,
    /* [in] */ DATE dateStart,
    /* [in] */ DATE dateEnd,
    /* [retval][out] */ ICAOffer **ppOffer);


void __RPC_STUB ICAOffers_get_AddNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICAOffers_Remove_Proxy( 
    ICAOffers * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ICAOffers_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAOffers_INTERFACE_DEFINED__ */


#ifndef __ICAComponents_INTERFACE_DEFINED__
#define __ICAComponents_INTERFACE_DEFINED__

/* interface ICAComponents */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAComponents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166470-DF8A-463a-B620-7BEC23542010")
    ICAComponents : public IDispatch
    {
    public:
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppCollection) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAComponent **ppComponent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAComponentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAComponents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAComponents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAComponents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAComponents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAComponents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAComponents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAComponents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICAComponents * This,
            /* [retval][out] */ IUnknown **ppCollection);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICAComponents * This,
            /* [retval][out] */ long *Count);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICAComponents * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ICAComponent **ppComponent);
        
        END_INTERFACE
    } ICAComponentsVtbl;

    interface ICAComponents
    {
        CONST_VTBL struct ICAComponentsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAComponents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAComponents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAComponents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAComponents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAComponents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAComponents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAComponents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAComponents_get__NewEnum(This,ppCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,ppCollection)

#define ICAComponents_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define ICAComponents_get_Item(This,Index,ppComponent)	\
    (This)->lpVtbl -> get_Item(This,Index,ppComponent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponents_get__NewEnum_Proxy( 
    ICAComponents * This,
    /* [retval][out] */ IUnknown **ppCollection);


void __RPC_STUB ICAComponents_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponents_get_Count_Proxy( 
    ICAComponents * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB ICAComponents_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponents_get_Item_Proxy( 
    ICAComponents * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ICAComponent **ppComponent);


void __RPC_STUB ICAComponents_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAComponents_INTERFACE_DEFINED__ */


#ifndef __ICAComponentInternal_INTERFACE_DEFINED__
#define __ICAComponentInternal_INTERFACE_DEFINED__

/* interface ICAComponentInternal */
/* [unique][helpstring][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAComponentInternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166361-DF8A-463a-B620-7BEC23542010")
    ICAComponentInternal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllDenials( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstrDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAComponentInternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAComponentInternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAComponentInternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAComponentInternal * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllDenials )( 
            ICAComponentInternal * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICAComponentInternal * This,
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstrDescription);
        
        END_INTERFACE
    } ICAComponentInternalVtbl;

    interface ICAComponentInternal
    {
        CONST_VTBL struct ICAComponentInternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAComponentInternal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAComponentInternal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAComponentInternal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAComponentInternal_RemoveAllDenials(This)	\
    (This)->lpVtbl -> RemoveAllDenials(This)

#define ICAComponentInternal_get_Description(This,enFormat,pbstrDescription)	\
    (This)->lpVtbl -> get_Description(This,enFormat,pbstrDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAComponentInternal_RemoveAllDenials_Proxy( 
    ICAComponentInternal * This);


void __RPC_STUB ICAComponentInternal_RemoveAllDenials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponentInternal_get_Description_Proxy( 
    ICAComponentInternal * This,
    /* [in] */ CADescFormat enFormat,
    /* [retval][out] */ BSTR *pbstrDescription);


void __RPC_STUB ICAComponentInternal_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAComponentInternal_INTERFACE_DEFINED__ */


#ifndef __ICADefaultDlg_INTERFACE_DEFINED__
#define __ICADefaultDlg_INTERFACE_DEFINED__

/* interface ICADefaultDlg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICADefaultDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("860A3FE2-DED1-40E2-896C-057681A8A1A8")
    ICADefaultDlg : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoSize( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoSize( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackStyle( 
            /* [in] */ long style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackStyle( 
            /* [retval][out] */ long *pstyle) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderStyle( 
            /* [in] */ long style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStyle( 
            /* [retval][out] */ long *pstyle) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderWidth( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderWidth( 
            /* [retval][out] */ long *width) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DrawMode( 
            /* [in] */ long mode) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawMode( 
            /* [retval][out] */ long *pmode) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DrawStyle( 
            /* [in] */ long style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawStyle( 
            /* [retval][out] */ long *pstyle) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DrawWidth( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawWidth( 
            /* [retval][out] */ long *pwidth) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FillColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FillColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_FillStyle( 
            /* [in] */ long style) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FillStyle( 
            /* [retval][out] */ long *pstyle) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **ppFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ LONG_PTR *phwnd) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_TabStop( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TabStop( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR strText) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pstrText) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR strCaption) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR *pstrCaption) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderVisible( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderVisible( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Appearance( 
            /* [in] */ short appearance) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Appearance( 
            /* [retval][out] */ short *pappearance) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ long pointer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ long *ppointer) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *pMouseIcon) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *pMouseIcon) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **ppMouseIcon) = 0;
        
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ IPictureDisp **ppPicture) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Valid( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Valid( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICADefaultDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICADefaultDlg * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICADefaultDlg * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICADefaultDlg * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICADefaultDlg * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICADefaultDlg * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICADefaultDlg * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICADefaultDlg * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoSize )( 
            ICADefaultDlg * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoSize )( 
            ICADefaultDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            ICADefaultDlg * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            ICADefaultDlg * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackStyle )( 
            ICADefaultDlg * This,
            /* [in] */ long style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackStyle )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pstyle);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderColor )( 
            ICADefaultDlg * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderColor )( 
            ICADefaultDlg * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderStyle )( 
            ICADefaultDlg * This,
            /* [in] */ long style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStyle )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pstyle);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderWidth )( 
            ICADefaultDlg * This,
            /* [in] */ long width);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderWidth )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *width);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawMode )( 
            ICADefaultDlg * This,
            /* [in] */ long mode);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawMode )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pmode);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawStyle )( 
            ICADefaultDlg * This,
            /* [in] */ long style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawStyle )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pstyle);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawWidth )( 
            ICADefaultDlg * This,
            /* [in] */ long width);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawWidth )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pwidth);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillColor )( 
            ICADefaultDlg * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillColor )( 
            ICADefaultDlg * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FillStyle )( 
            ICADefaultDlg * This,
            /* [in] */ long style);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FillStyle )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *pstyle);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            ICADefaultDlg * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            ICADefaultDlg * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            ICADefaultDlg * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForeColor )( 
            ICADefaultDlg * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            ICADefaultDlg * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            ICADefaultDlg * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            ICADefaultDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            ICADefaultDlg * This,
            /* [retval][out] */ LONG_PTR *phwnd);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TabStop )( 
            ICADefaultDlg * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TabStop )( 
            ICADefaultDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            ICADefaultDlg * This,
            /* [in] */ BSTR strText);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            ICADefaultDlg * This,
            /* [retval][out] */ BSTR *pstrText);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Caption )( 
            ICADefaultDlg * This,
            /* [in] */ BSTR strCaption);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Caption )( 
            ICADefaultDlg * This,
            /* [retval][out] */ BSTR *pstrCaption);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderVisible )( 
            ICADefaultDlg * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderVisible )( 
            ICADefaultDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Appearance )( 
            ICADefaultDlg * This,
            /* [in] */ short appearance);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Appearance )( 
            ICADefaultDlg * This,
            /* [retval][out] */ short *pappearance);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            ICADefaultDlg * This,
            /* [in] */ long pointer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            ICADefaultDlg * This,
            /* [retval][out] */ long *ppointer);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            ICADefaultDlg * This,
            /* [in] */ IPictureDisp *pMouseIcon);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            ICADefaultDlg * This,
            /* [in] */ IPictureDisp *pMouseIcon);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            ICADefaultDlg * This,
            /* [retval][out] */ IPictureDisp **ppMouseIcon);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Picture )( 
            ICADefaultDlg * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Picture )( 
            ICADefaultDlg * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Picture )( 
            ICADefaultDlg * This,
            /* [retval][out] */ IPictureDisp **ppPicture);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Valid )( 
            ICADefaultDlg * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Valid )( 
            ICADefaultDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        END_INTERFACE
    } ICADefaultDlgVtbl;

    interface ICADefaultDlg
    {
        CONST_VTBL struct ICADefaultDlgVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICADefaultDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICADefaultDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICADefaultDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICADefaultDlg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICADefaultDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICADefaultDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICADefaultDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICADefaultDlg_put_AutoSize(This,vbool)	\
    (This)->lpVtbl -> put_AutoSize(This,vbool)

#define ICADefaultDlg_get_AutoSize(This,pbool)	\
    (This)->lpVtbl -> get_AutoSize(This,pbool)

#define ICADefaultDlg_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define ICADefaultDlg_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define ICADefaultDlg_put_BackStyle(This,style)	\
    (This)->lpVtbl -> put_BackStyle(This,style)

#define ICADefaultDlg_get_BackStyle(This,pstyle)	\
    (This)->lpVtbl -> get_BackStyle(This,pstyle)

#define ICADefaultDlg_put_BorderColor(This,clr)	\
    (This)->lpVtbl -> put_BorderColor(This,clr)

#define ICADefaultDlg_get_BorderColor(This,pclr)	\
    (This)->lpVtbl -> get_BorderColor(This,pclr)

#define ICADefaultDlg_put_BorderStyle(This,style)	\
    (This)->lpVtbl -> put_BorderStyle(This,style)

#define ICADefaultDlg_get_BorderStyle(This,pstyle)	\
    (This)->lpVtbl -> get_BorderStyle(This,pstyle)

#define ICADefaultDlg_put_BorderWidth(This,width)	\
    (This)->lpVtbl -> put_BorderWidth(This,width)

#define ICADefaultDlg_get_BorderWidth(This,width)	\
    (This)->lpVtbl -> get_BorderWidth(This,width)

#define ICADefaultDlg_put_DrawMode(This,mode)	\
    (This)->lpVtbl -> put_DrawMode(This,mode)

#define ICADefaultDlg_get_DrawMode(This,pmode)	\
    (This)->lpVtbl -> get_DrawMode(This,pmode)

#define ICADefaultDlg_put_DrawStyle(This,style)	\
    (This)->lpVtbl -> put_DrawStyle(This,style)

#define ICADefaultDlg_get_DrawStyle(This,pstyle)	\
    (This)->lpVtbl -> get_DrawStyle(This,pstyle)

#define ICADefaultDlg_put_DrawWidth(This,width)	\
    (This)->lpVtbl -> put_DrawWidth(This,width)

#define ICADefaultDlg_get_DrawWidth(This,pwidth)	\
    (This)->lpVtbl -> get_DrawWidth(This,pwidth)

#define ICADefaultDlg_put_FillColor(This,clr)	\
    (This)->lpVtbl -> put_FillColor(This,clr)

#define ICADefaultDlg_get_FillColor(This,pclr)	\
    (This)->lpVtbl -> get_FillColor(This,pclr)

#define ICADefaultDlg_put_FillStyle(This,style)	\
    (This)->lpVtbl -> put_FillStyle(This,style)

#define ICADefaultDlg_get_FillStyle(This,pstyle)	\
    (This)->lpVtbl -> get_FillStyle(This,pstyle)

#define ICADefaultDlg_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define ICADefaultDlg_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define ICADefaultDlg_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define ICADefaultDlg_put_ForeColor(This,clr)	\
    (This)->lpVtbl -> put_ForeColor(This,clr)

#define ICADefaultDlg_get_ForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ForeColor(This,pclr)

#define ICADefaultDlg_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define ICADefaultDlg_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define ICADefaultDlg_get_Window(This,phwnd)	\
    (This)->lpVtbl -> get_Window(This,phwnd)

#define ICADefaultDlg_put_TabStop(This,vbool)	\
    (This)->lpVtbl -> put_TabStop(This,vbool)

#define ICADefaultDlg_get_TabStop(This,pbool)	\
    (This)->lpVtbl -> get_TabStop(This,pbool)

#define ICADefaultDlg_put_Text(This,strText)	\
    (This)->lpVtbl -> put_Text(This,strText)

#define ICADefaultDlg_get_Text(This,pstrText)	\
    (This)->lpVtbl -> get_Text(This,pstrText)

#define ICADefaultDlg_put_Caption(This,strCaption)	\
    (This)->lpVtbl -> put_Caption(This,strCaption)

#define ICADefaultDlg_get_Caption(This,pstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pstrCaption)

#define ICADefaultDlg_put_BorderVisible(This,vbool)	\
    (This)->lpVtbl -> put_BorderVisible(This,vbool)

#define ICADefaultDlg_get_BorderVisible(This,pbool)	\
    (This)->lpVtbl -> get_BorderVisible(This,pbool)

#define ICADefaultDlg_put_Appearance(This,appearance)	\
    (This)->lpVtbl -> put_Appearance(This,appearance)

#define ICADefaultDlg_get_Appearance(This,pappearance)	\
    (This)->lpVtbl -> get_Appearance(This,pappearance)

#define ICADefaultDlg_put_MousePointer(This,pointer)	\
    (This)->lpVtbl -> put_MousePointer(This,pointer)

#define ICADefaultDlg_get_MousePointer(This,ppointer)	\
    (This)->lpVtbl -> get_MousePointer(This,ppointer)

#define ICADefaultDlg_putref_MouseIcon(This,pMouseIcon)	\
    (This)->lpVtbl -> putref_MouseIcon(This,pMouseIcon)

#define ICADefaultDlg_put_MouseIcon(This,pMouseIcon)	\
    (This)->lpVtbl -> put_MouseIcon(This,pMouseIcon)

#define ICADefaultDlg_get_MouseIcon(This,ppMouseIcon)	\
    (This)->lpVtbl -> get_MouseIcon(This,ppMouseIcon)

#define ICADefaultDlg_putref_Picture(This,pPicture)	\
    (This)->lpVtbl -> putref_Picture(This,pPicture)

#define ICADefaultDlg_put_Picture(This,pPicture)	\
    (This)->lpVtbl -> put_Picture(This,pPicture)

#define ICADefaultDlg_get_Picture(This,ppPicture)	\
    (This)->lpVtbl -> get_Picture(This,ppPicture)

#define ICADefaultDlg_put_Valid(This,vbool)	\
    (This)->lpVtbl -> put_Valid(This,vbool)

#define ICADefaultDlg_get_Valid(This,pbool)	\
    (This)->lpVtbl -> get_Valid(This,pbool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_AutoSize_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ICADefaultDlg_put_AutoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_AutoSize_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB ICADefaultDlg_get_AutoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BackColor_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ICADefaultDlg_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BackColor_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB ICADefaultDlg_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BackStyle_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long style);


void __RPC_STUB ICADefaultDlg_put_BackStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BackStyle_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pstyle);


void __RPC_STUB ICADefaultDlg_get_BackStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BorderColor_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ICADefaultDlg_put_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BorderColor_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB ICADefaultDlg_get_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BorderStyle_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long style);


void __RPC_STUB ICADefaultDlg_put_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BorderStyle_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pstyle);


void __RPC_STUB ICADefaultDlg_get_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BorderWidth_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long width);


void __RPC_STUB ICADefaultDlg_put_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BorderWidth_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *width);


void __RPC_STUB ICADefaultDlg_get_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_DrawMode_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long mode);


void __RPC_STUB ICADefaultDlg_put_DrawMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_DrawMode_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pmode);


void __RPC_STUB ICADefaultDlg_get_DrawMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_DrawStyle_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long style);


void __RPC_STUB ICADefaultDlg_put_DrawStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_DrawStyle_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pstyle);


void __RPC_STUB ICADefaultDlg_get_DrawStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_DrawWidth_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long width);


void __RPC_STUB ICADefaultDlg_put_DrawWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_DrawWidth_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pwidth);


void __RPC_STUB ICADefaultDlg_get_DrawWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_FillColor_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ICADefaultDlg_put_FillColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_FillColor_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB ICADefaultDlg_get_FillColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_FillStyle_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long style);


void __RPC_STUB ICADefaultDlg_put_FillStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_FillStyle_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *pstyle);


void __RPC_STUB ICADefaultDlg_get_FillStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_putref_Font_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB ICADefaultDlg_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Font_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB ICADefaultDlg_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Font_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB ICADefaultDlg_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_ForeColor_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ICADefaultDlg_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_ForeColor_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB ICADefaultDlg_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Enabled_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ICADefaultDlg_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Enabled_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB ICADefaultDlg_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Window_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ LONG_PTR *phwnd);


void __RPC_STUB ICADefaultDlg_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_TabStop_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ICADefaultDlg_put_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_TabStop_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB ICADefaultDlg_get_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Text_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ BSTR strText);


void __RPC_STUB ICADefaultDlg_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Text_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ BSTR *pstrText);


void __RPC_STUB ICADefaultDlg_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Caption_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ BSTR strCaption);


void __RPC_STUB ICADefaultDlg_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Caption_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ BSTR *pstrCaption);


void __RPC_STUB ICADefaultDlg_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_BorderVisible_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ICADefaultDlg_put_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_BorderVisible_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB ICADefaultDlg_get_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Appearance_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ short appearance);


void __RPC_STUB ICADefaultDlg_put_Appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Appearance_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ short *pappearance);


void __RPC_STUB ICADefaultDlg_get_Appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_MousePointer_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ long pointer);


void __RPC_STUB ICADefaultDlg_put_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_MousePointer_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ long *ppointer);


void __RPC_STUB ICADefaultDlg_get_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_putref_MouseIcon_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IPictureDisp *pMouseIcon);


void __RPC_STUB ICADefaultDlg_putref_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_MouseIcon_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IPictureDisp *pMouseIcon);


void __RPC_STUB ICADefaultDlg_put_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_MouseIcon_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ IPictureDisp **ppMouseIcon);


void __RPC_STUB ICADefaultDlg_get_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propputref] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_putref_Picture_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB ICADefaultDlg_putref_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Picture_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB ICADefaultDlg_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Picture_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ IPictureDisp **ppPicture);


void __RPC_STUB ICADefaultDlg_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_put_Valid_Proxy( 
    ICADefaultDlg * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB ICADefaultDlg_put_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ICADefaultDlg_get_Valid_Proxy( 
    ICADefaultDlg * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB ICADefaultDlg_get_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICADefaultDlg_INTERFACE_DEFINED__ */



#ifndef __MSTvCALib_LIBRARY_DEFINED__
#define __MSTvCALib_LIBRARY_DEFINED__

/* library MSTvCALib */
/* [helpstring][version][uuid] */ 

#define SID_CAManager CLSID_CAManager

EXTERN_C const IID LIBID_MSTvCALib;

#ifndef ___ICAResDenialTreeEvents_DISPINTERFACE_DEFINED__
#define ___ICAResDenialTreeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICAResDenialTreeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICAResDenialTreeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166298-DF8A-463A-B620-7BEC23542010")
    _ICAResDenialTreeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICAResDenialTreeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICAResDenialTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICAResDenialTreeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICAResDenialTreeEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICAResDenialTreeEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICAResDenialTreeEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICAResDenialTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICAResDenialTreeEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICAResDenialTreeEventsVtbl;

    interface _ICAResDenialTreeEvents
    {
        CONST_VTBL struct _ICAResDenialTreeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICAResDenialTreeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICAResDenialTreeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICAResDenialTreeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICAResDenialTreeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICAResDenialTreeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICAResDenialTreeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICAResDenialTreeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICAResDenialTreeEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICAManagerEvents_DISPINTERFACE_DEFINED__
#define ___ICAManagerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICAManagerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICAManagerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166200-DF8A-463A-B620-7BEC23542010")
    _ICAManagerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICAManagerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICAManagerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICAManagerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICAManagerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICAManagerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICAManagerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICAManagerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICAManagerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICAManagerEventsVtbl;

    interface _ICAManagerEvents
    {
        CONST_VTBL struct _ICAManagerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICAManagerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICAManagerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICAManagerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICAManagerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICAManagerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICAManagerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICAManagerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICAManagerEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICARequestEvents_DISPINTERFACE_DEFINED__
#define ___ICARequestEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICARequestEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICARequestEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166210-DF8A-463A-B620-7BEC23542010")
    _ICARequestEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICARequestEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICARequestEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICARequestEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICARequestEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICARequestEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICARequestEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICARequestEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICARequestEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICARequestEventsVtbl;

    interface _ICARequestEvents
    {
        CONST_VTBL struct _ICARequestEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICARequestEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICARequestEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICARequestEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICARequestEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICARequestEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICARequestEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICARequestEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICARequestEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICAPoliciesEvents_DISPINTERFACE_DEFINED__
#define ___ICAPoliciesEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICAPoliciesEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICAPoliciesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166220-DF8A-463A-B620-7BEC23542010")
    _ICAPoliciesEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICAPoliciesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICAPoliciesEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICAPoliciesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICAPoliciesEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICAPoliciesEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICAPoliciesEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICAPoliciesEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICAPoliciesEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICAPoliciesEventsVtbl;

    interface _ICAPoliciesEvents
    {
        CONST_VTBL struct _ICAPoliciesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICAPoliciesEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICAPoliciesEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICAPoliciesEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICAPoliciesEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICAPoliciesEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICAPoliciesEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICAPoliciesEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICAPoliciesEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICATollsEvents_DISPINTERFACE_DEFINED__
#define ___ICATollsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICATollsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICATollsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166230-DF8A-463A-B620-7BEC23542010")
    _ICATollsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICATollsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICATollsEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICATollsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICATollsEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICATollsEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICATollsEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICATollsEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICATollsEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICATollsEventsVtbl;

    interface _ICATollsEvents
    {
        CONST_VTBL struct _ICATollsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICATollsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICATollsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICATollsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICATollsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICATollsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICATollsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICATollsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICATollsEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICADenialsEvents_DISPINTERFACE_DEFINED__
#define ___ICADenialsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICADenialsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICADenialsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166240-DF8A-463A-B620-7BEC23542010")
    _ICADenialsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICADenialsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICADenialsEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICADenialsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICADenialsEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICADenialsEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICADenialsEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICADenialsEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICADenialsEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICADenialsEventsVtbl;

    interface _ICADenialsEvents
    {
        CONST_VTBL struct _ICADenialsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICADenialsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICADenialsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICADenialsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICADenialsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICADenialsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICADenialsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICADenialsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICADenialsEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICAOffersEvents_DISPINTERFACE_DEFINED__
#define ___ICAOffersEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICAOffersEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICAOffersEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166250-DF8A-463A-B620-7BEC23542010")
    _ICAOffersEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICAOffersEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICAOffersEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICAOffersEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICAOffersEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICAOffersEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICAOffersEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICAOffersEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICAOffersEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICAOffersEventsVtbl;

    interface _ICAOffersEvents
    {
        CONST_VTBL struct _ICAOffersEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICAOffersEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICAOffersEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICAOffersEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICAOffersEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICAOffersEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICAOffersEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICAOffersEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICAOffersEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ICAComponentsEvents_DISPINTERFACE_DEFINED__
#define ___ICAComponentsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICAComponentsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICAComponentsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166260-DF8A-463A-B620-7BEC23542010")
    _ICAComponentsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICAComponentsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICAComponentsEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICAComponentsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICAComponentsEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICAComponentsEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICAComponentsEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICAComponentsEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICAComponentsEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICAComponentsEventsVtbl;

    interface _ICAComponentsEvents
    {
        CONST_VTBL struct _ICAComponentsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICAComponentsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICAComponentsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICAComponentsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICAComponentsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICAComponentsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICAComponentsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICAComponentsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICAComponentsEvents_DISPINTERFACE_DEFINED__ */


#ifndef __ICAManager_INTERFACE_DEFINED__
#define __ICAManager_INTERFACE_DEFINED__

/* interface ICAManager */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_ICAManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166300-DF8A-463a-B620-7BEC23542010")
    ICAManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Policies( 
            /* [retval][out] */ ICAPolicies **ppPolicies) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveRequest( 
            /* [retval][out] */ ICARequest **ppRequest) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Offers( 
            /* [retval][out] */ ICAOffers **ppOffers) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PaidTolls( 
            /* [retval][out] */ ICATolls **ppTolls) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseDefaultUI( 
            /* [in] */ long fUseDefaultUI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseDefaultUI( 
            /* [retval][out] */ long *pfUseDefaultUI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DenialsFor( 
            /* [in] */ IUnknown *pUnk,
            /* [retval][out] */ ICADenials **ppDenials) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Policies )( 
            ICAManager * This,
            /* [retval][out] */ ICAPolicies **ppPolicies);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveRequest )( 
            ICAManager * This,
            /* [retval][out] */ ICARequest **ppRequest);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Offers )( 
            ICAManager * This,
            /* [retval][out] */ ICAOffers **ppOffers);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PaidTolls )( 
            ICAManager * This,
            /* [retval][out] */ ICATolls **ppTolls);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseDefaultUI )( 
            ICAManager * This,
            /* [in] */ long fUseDefaultUI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseDefaultUI )( 
            ICAManager * This,
            /* [retval][out] */ long *pfUseDefaultUI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DenialsFor )( 
            ICAManager * This,
            /* [in] */ IUnknown *pUnk,
            /* [retval][out] */ ICADenials **ppDenials);
        
        END_INTERFACE
    } ICAManagerVtbl;

    interface ICAManager
    {
        CONST_VTBL struct ICAManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAManager_get_Policies(This,ppPolicies)	\
    (This)->lpVtbl -> get_Policies(This,ppPolicies)

#define ICAManager_get_ActiveRequest(This,ppRequest)	\
    (This)->lpVtbl -> get_ActiveRequest(This,ppRequest)

#define ICAManager_get_Offers(This,ppOffers)	\
    (This)->lpVtbl -> get_Offers(This,ppOffers)

#define ICAManager_get_PaidTolls(This,ppTolls)	\
    (This)->lpVtbl -> get_PaidTolls(This,ppTolls)

#define ICAManager_put_UseDefaultUI(This,fUseDefaultUI)	\
    (This)->lpVtbl -> put_UseDefaultUI(This,fUseDefaultUI)

#define ICAManager_get_UseDefaultUI(This,pfUseDefaultUI)	\
    (This)->lpVtbl -> get_UseDefaultUI(This,pfUseDefaultUI)

#define ICAManager_get_DenialsFor(This,pUnk,ppDenials)	\
    (This)->lpVtbl -> get_DenialsFor(This,pUnk,ppDenials)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_Policies_Proxy( 
    ICAManager * This,
    /* [retval][out] */ ICAPolicies **ppPolicies);


void __RPC_STUB ICAManager_get_Policies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_ActiveRequest_Proxy( 
    ICAManager * This,
    /* [retval][out] */ ICARequest **ppRequest);


void __RPC_STUB ICAManager_get_ActiveRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_Offers_Proxy( 
    ICAManager * This,
    /* [retval][out] */ ICAOffers **ppOffers);


void __RPC_STUB ICAManager_get_Offers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_PaidTolls_Proxy( 
    ICAManager * This,
    /* [retval][out] */ ICATolls **ppTolls);


void __RPC_STUB ICAManager_get_PaidTolls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAManager_put_UseDefaultUI_Proxy( 
    ICAManager * This,
    /* [in] */ long fUseDefaultUI);


void __RPC_STUB ICAManager_put_UseDefaultUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_UseDefaultUI_Proxy( 
    ICAManager * This,
    /* [retval][out] */ long *pfUseDefaultUI);


void __RPC_STUB ICAManager_get_UseDefaultUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAManager_get_DenialsFor_Proxy( 
    ICAManager * This,
    /* [in] */ IUnknown *pUnk,
    /* [retval][out] */ ICADenials **ppDenials);


void __RPC_STUB ICAManager_get_DenialsFor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAManager_INTERFACE_DEFINED__ */


#ifndef __ICARequest_INTERFACE_DEFINED__
#define __ICARequest_INTERFACE_DEFINED__

/* interface ICARequest */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICARequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166310-DF8A-463a-B620-7BEC23542010")
    ICARequest : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RequestedItem( 
            /* [retval][out] */ IUnknown **ppTunereq) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CAManager( 
            /* [retval][out] */ ICAManager **ppManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScheduleEntry( 
            /* [retval][out] */ IUnknown **ppUnkScheduleEntry) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Denials( 
            /* [retval][out] */ ICADenials **ppDenials) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Components( 
            /* [retval][out] */ ICAComponents **pComponents) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Check( 
            /* [retval][out] */ long *pcDenials) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResolveDenials( 
            /* [retval][out] */ long *pcDenials) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CountDeniedComponents( 
            /* [retval][out] */ long *pcDeniedComponents) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICARequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICARequest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICARequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICARequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICARequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICARequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICARequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICARequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RequestedItem )( 
            ICARequest * This,
            /* [retval][out] */ IUnknown **ppTunereq);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CAManager )( 
            ICARequest * This,
            /* [retval][out] */ ICAManager **ppManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScheduleEntry )( 
            ICARequest * This,
            /* [retval][out] */ IUnknown **ppUnkScheduleEntry);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Denials )( 
            ICARequest * This,
            /* [retval][out] */ ICADenials **ppDenials);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Components )( 
            ICARequest * This,
            /* [retval][out] */ ICAComponents **pComponents);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Check )( 
            ICARequest * This,
            /* [retval][out] */ long *pcDenials);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ResolveDenials )( 
            ICARequest * This,
            /* [retval][out] */ long *pcDenials);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountDeniedComponents )( 
            ICARequest * This,
            /* [retval][out] */ long *pcDeniedComponents);
        
        END_INTERFACE
    } ICARequestVtbl;

    interface ICARequest
    {
        CONST_VTBL struct ICARequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICARequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICARequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICARequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICARequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICARequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICARequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICARequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICARequest_get_RequestedItem(This,ppTunereq)	\
    (This)->lpVtbl -> get_RequestedItem(This,ppTunereq)

#define ICARequest_get_CAManager(This,ppManager)	\
    (This)->lpVtbl -> get_CAManager(This,ppManager)

#define ICARequest_get_ScheduleEntry(This,ppUnkScheduleEntry)	\
    (This)->lpVtbl -> get_ScheduleEntry(This,ppUnkScheduleEntry)

#define ICARequest_get_Denials(This,ppDenials)	\
    (This)->lpVtbl -> get_Denials(This,ppDenials)

#define ICARequest_get_Components(This,pComponents)	\
    (This)->lpVtbl -> get_Components(This,pComponents)

#define ICARequest_get_Check(This,pcDenials)	\
    (This)->lpVtbl -> get_Check(This,pcDenials)

#define ICARequest_get_ResolveDenials(This,pcDenials)	\
    (This)->lpVtbl -> get_ResolveDenials(This,pcDenials)

#define ICARequest_get_CountDeniedComponents(This,pcDeniedComponents)	\
    (This)->lpVtbl -> get_CountDeniedComponents(This,pcDeniedComponents)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_RequestedItem_Proxy( 
    ICARequest * This,
    /* [retval][out] */ IUnknown **ppTunereq);


void __RPC_STUB ICARequest_get_RequestedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_CAManager_Proxy( 
    ICARequest * This,
    /* [retval][out] */ ICAManager **ppManager);


void __RPC_STUB ICARequest_get_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_ScheduleEntry_Proxy( 
    ICARequest * This,
    /* [retval][out] */ IUnknown **ppUnkScheduleEntry);


void __RPC_STUB ICARequest_get_ScheduleEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_Denials_Proxy( 
    ICARequest * This,
    /* [retval][out] */ ICADenials **ppDenials);


void __RPC_STUB ICARequest_get_Denials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_Components_Proxy( 
    ICARequest * This,
    /* [retval][out] */ ICAComponents **pComponents);


void __RPC_STUB ICARequest_get_Components_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_Check_Proxy( 
    ICARequest * This,
    /* [retval][out] */ long *pcDenials);


void __RPC_STUB ICARequest_get_Check_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_ResolveDenials_Proxy( 
    ICARequest * This,
    /* [retval][out] */ long *pcDenials);


void __RPC_STUB ICARequest_get_ResolveDenials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICARequest_get_CountDeniedComponents_Proxy( 
    ICARequest * This,
    /* [retval][out] */ long *pcDeniedComponents);


void __RPC_STUB ICARequest_get_CountDeniedComponents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICARequest_INTERFACE_DEFINED__ */


#ifndef __ICAPolicy_INTERFACE_DEFINED__
#define __ICAPolicy_INTERFACE_DEFINED__

/* interface ICAPolicy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICAPolicy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166320-DF8A-463a-B620-7BEC23542010")
    ICAPolicy : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckRequest( 
            /* [in] */ ICARequest *pReq) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OkToPersist( 
            /* [retval][out] */ BOOL *pfOkToPersist) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OkToRemove( 
            /* [retval][out] */ BOOL *pfOkToRemove) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OkToRemoveDenial( 
            ICADenial *pDenial,
            /* [retval][out] */ BOOL *pfOk) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OkToRemoveOffer( 
            ICAOffer *pOffer,
            /* [retval][out] */ BOOL *pfOk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAPolicy * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAPolicy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAPolicy * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ICAPolicy * This,
            /* [retval][out] */ BSTR *pbstr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckRequest )( 
            ICAPolicy * This,
            /* [in] */ ICARequest *pReq);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CAManager )( 
            ICAPolicy * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OkToPersist )( 
            ICAPolicy * This,
            /* [retval][out] */ BOOL *pfOkToPersist);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OkToRemove )( 
            ICAPolicy * This,
            /* [retval][out] */ BOOL *pfOkToRemove);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OkToRemoveDenial )( 
            ICAPolicy * This,
            ICADenial *pDenial,
            /* [retval][out] */ BOOL *pfOk);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OkToRemoveOffer )( 
            ICAPolicy * This,
            ICAOffer *pOffer,
            /* [retval][out] */ BOOL *pfOk);
        
        END_INTERFACE
    } ICAPolicyVtbl;

    interface ICAPolicy
    {
        CONST_VTBL struct ICAPolicyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAPolicy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAPolicy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAPolicy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAPolicy_get_Name(This,pbstr)	\
    (This)->lpVtbl -> get_Name(This,pbstr)

#define ICAPolicy_CheckRequest(This,pReq)	\
    (This)->lpVtbl -> CheckRequest(This,pReq)

#define ICAPolicy_put_CAManager(This,pManager)	\
    (This)->lpVtbl -> put_CAManager(This,pManager)

#define ICAPolicy_get_OkToPersist(This,pfOkToPersist)	\
    (This)->lpVtbl -> get_OkToPersist(This,pfOkToPersist)

#define ICAPolicy_get_OkToRemove(This,pfOkToRemove)	\
    (This)->lpVtbl -> get_OkToRemove(This,pfOkToRemove)

#define ICAPolicy_get_OkToRemoveDenial(This,pDenial,pfOk)	\
    (This)->lpVtbl -> get_OkToRemoveDenial(This,pDenial,pfOk)

#define ICAPolicy_get_OkToRemoveOffer(This,pOffer,pfOk)	\
    (This)->lpVtbl -> get_OkToRemoveOffer(This,pOffer,pfOk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicy_get_Name_Proxy( 
    ICAPolicy * This,
    /* [retval][out] */ BSTR *pbstr);


void __RPC_STUB ICAPolicy_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAPolicy_CheckRequest_Proxy( 
    ICAPolicy * This,
    /* [in] */ ICARequest *pReq);


void __RPC_STUB ICAPolicy_CheckRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAPolicy_put_CAManager_Proxy( 
    ICAPolicy * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICAPolicy_put_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicy_get_OkToPersist_Proxy( 
    ICAPolicy * This,
    /* [retval][out] */ BOOL *pfOkToPersist);


void __RPC_STUB ICAPolicy_get_OkToPersist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicy_get_OkToRemove_Proxy( 
    ICAPolicy * This,
    /* [retval][out] */ BOOL *pfOkToRemove);


void __RPC_STUB ICAPolicy_get_OkToRemove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicy_get_OkToRemoveDenial_Proxy( 
    ICAPolicy * This,
    ICADenial *pDenial,
    /* [retval][out] */ BOOL *pfOk);


void __RPC_STUB ICAPolicy_get_OkToRemoveDenial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAPolicy_get_OkToRemoveOffer_Proxy( 
    ICAPolicy * This,
    ICAOffer *pOffer,
    /* [retval][out] */ BOOL *pfOk);


void __RPC_STUB ICAPolicy_get_OkToRemoveOffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAPolicy_INTERFACE_DEFINED__ */


#ifndef __ICAToll_INTERFACE_DEFINED__
#define __ICAToll_INTERFACE_DEFINED__

/* interface ICAToll */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAToll;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166330-DF8A-463a-B620-7BEC23542010")
    ICAToll : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ BOOL fSelect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PayToll( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Refundable( 
            /* [retval][out] */ BOOL *pfRefundable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefundToll( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TolledObject( 
            /* [retval][out] */ IUnknown **ppUnkTolled) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Denials( 
            /* [retval][out] */ ICADenials **ppDenials) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Policy( 
            /* [retval][out] */ ICAPolicy **ppPolicy) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimePaid( 
            /* [retval][out] */ DATE *pdtPaid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CATollState *penState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICATollVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAToll * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAToll * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAToll * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CAManager )( 
            ICAToll * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            ICAToll * This,
            /* [in] */ BOOL fSelect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PayToll )( 
            ICAToll * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Refundable )( 
            ICAToll * This,
            /* [retval][out] */ BOOL *pfRefundable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RefundToll )( 
            ICAToll * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TolledObject )( 
            ICAToll * This,
            /* [retval][out] */ IUnknown **ppUnkTolled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Denials )( 
            ICAToll * This,
            /* [retval][out] */ ICADenials **ppDenials);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Policy )( 
            ICAToll * This,
            /* [retval][out] */ ICAPolicy **ppPolicy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICAToll * This,
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimePaid )( 
            ICAToll * This,
            /* [retval][out] */ DATE *pdtPaid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            ICAToll * This,
            /* [retval][out] */ CATollState *penState);
        
        END_INTERFACE
    } ICATollVtbl;

    interface ICAToll
    {
        CONST_VTBL struct ICATollVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAToll_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAToll_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAToll_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAToll_put_CAManager(This,pManager)	\
    (This)->lpVtbl -> put_CAManager(This,pManager)

#define ICAToll_Select(This,fSelect)	\
    (This)->lpVtbl -> Select(This,fSelect)

#define ICAToll_PayToll(This)	\
    (This)->lpVtbl -> PayToll(This)

#define ICAToll_get_Refundable(This,pfRefundable)	\
    (This)->lpVtbl -> get_Refundable(This,pfRefundable)

#define ICAToll_RefundToll(This)	\
    (This)->lpVtbl -> RefundToll(This)

#define ICAToll_get_TolledObject(This,ppUnkTolled)	\
    (This)->lpVtbl -> get_TolledObject(This,ppUnkTolled)

#define ICAToll_get_Denials(This,ppDenials)	\
    (This)->lpVtbl -> get_Denials(This,ppDenials)

#define ICAToll_get_Policy(This,ppPolicy)	\
    (This)->lpVtbl -> get_Policy(This,ppPolicy)

#define ICAToll_get_Description(This,enFormat,pbstr)	\
    (This)->lpVtbl -> get_Description(This,enFormat,pbstr)

#define ICAToll_get_TimePaid(This,pdtPaid)	\
    (This)->lpVtbl -> get_TimePaid(This,pdtPaid)

#define ICAToll_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAToll_put_CAManager_Proxy( 
    ICAToll * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICAToll_put_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAToll_Select_Proxy( 
    ICAToll * This,
    /* [in] */ BOOL fSelect);


void __RPC_STUB ICAToll_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAToll_PayToll_Proxy( 
    ICAToll * This);


void __RPC_STUB ICAToll_PayToll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_Refundable_Proxy( 
    ICAToll * This,
    /* [retval][out] */ BOOL *pfRefundable);


void __RPC_STUB ICAToll_get_Refundable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAToll_RefundToll_Proxy( 
    ICAToll * This);


void __RPC_STUB ICAToll_RefundToll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_TolledObject_Proxy( 
    ICAToll * This,
    /* [retval][out] */ IUnknown **ppUnkTolled);


void __RPC_STUB ICAToll_get_TolledObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_Denials_Proxy( 
    ICAToll * This,
    /* [retval][out] */ ICADenials **ppDenials);


void __RPC_STUB ICAToll_get_Denials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_Policy_Proxy( 
    ICAToll * This,
    /* [retval][out] */ ICAPolicy **ppPolicy);


void __RPC_STUB ICAToll_get_Policy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_Description_Proxy( 
    ICAToll * This,
    /* [in] */ CADescFormat enFormat,
    /* [retval][out] */ BSTR *pbstr);


void __RPC_STUB ICAToll_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_TimePaid_Proxy( 
    ICAToll * This,
    /* [retval][out] */ DATE *pdtPaid);


void __RPC_STUB ICAToll_get_TimePaid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAToll_get_State_Proxy( 
    ICAToll * This,
    /* [retval][out] */ CATollState *penState);


void __RPC_STUB ICAToll_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAToll_INTERFACE_DEFINED__ */


#ifndef __ICADenial_INTERFACE_DEFINED__
#define __ICADenial_INTERFACE_DEFINED__

/* interface ICADenial */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICADenial;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166340-DF8A-463a-B620-7BEC23542010")
    ICADenial : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeniedObject( 
            /* [retval][out] */ IUnknown **ppUnkDenied) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Policy( 
            /* [retval][out] */ ICAPolicy **ppPolicy) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [in] */ BSTR bstr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CADenialState *penState) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_State( 
            /* [in] */ CADenialState enState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tolls( 
            /* [retval][out] */ ICATolls **ppTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollStateChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICADenialVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICADenial * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICADenial * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICADenial * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICADenial * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICADenial * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICADenial * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICADenial * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeniedObject )( 
            ICADenial * This,
            /* [retval][out] */ IUnknown **ppUnkDenied);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Policy )( 
            ICADenial * This,
            /* [retval][out] */ ICAPolicy **ppPolicy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICADenial * This,
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ICADenial * This,
            /* [in] */ CADescFormat enFormat,
            /* [in] */ BSTR bstr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            ICADenial * This,
            /* [retval][out] */ CADenialState *penState);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_State )( 
            ICADenial * This,
            /* [in] */ CADenialState enState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tolls )( 
            ICADenial * This,
            /* [retval][out] */ ICATolls **ppTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollStateChanged )( 
            ICADenial * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom);
        
        END_INTERFACE
    } ICADenialVtbl;

    interface ICADenial
    {
        CONST_VTBL struct ICADenialVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICADenial_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICADenial_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICADenial_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICADenial_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICADenial_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICADenial_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICADenial_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICADenial_get_DeniedObject(This,ppUnkDenied)	\
    (This)->lpVtbl -> get_DeniedObject(This,ppUnkDenied)

#define ICADenial_get_Policy(This,ppPolicy)	\
    (This)->lpVtbl -> get_Policy(This,ppPolicy)

#define ICADenial_get_Description(This,enFormat,pbstr)	\
    (This)->lpVtbl -> get_Description(This,enFormat,pbstr)

#define ICADenial_put_Description(This,enFormat,bstr)	\
    (This)->lpVtbl -> put_Description(This,enFormat,bstr)

#define ICADenial_get_State(This,penState)	\
    (This)->lpVtbl -> get_State(This,penState)

#define ICADenial_put_State(This,enState)	\
    (This)->lpVtbl -> put_State(This,enState)

#define ICADenial_get_Tolls(This,ppTolls)	\
    (This)->lpVtbl -> get_Tolls(This,ppTolls)

#define ICADenial_NotifyTollStateChanged(This,pToll,enStateFrom)	\
    (This)->lpVtbl -> NotifyTollStateChanged(This,pToll,enStateFrom)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenial_get_DeniedObject_Proxy( 
    ICADenial * This,
    /* [retval][out] */ IUnknown **ppUnkDenied);


void __RPC_STUB ICADenial_get_DeniedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenial_get_Policy_Proxy( 
    ICADenial * This,
    /* [retval][out] */ ICAPolicy **ppPolicy);


void __RPC_STUB ICADenial_get_Policy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenial_get_Description_Proxy( 
    ICADenial * This,
    /* [in] */ CADescFormat enFormat,
    /* [retval][out] */ BSTR *pbstr);


void __RPC_STUB ICADenial_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICADenial_put_Description_Proxy( 
    ICADenial * This,
    /* [in] */ CADescFormat enFormat,
    /* [in] */ BSTR bstr);


void __RPC_STUB ICADenial_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenial_get_State_Proxy( 
    ICADenial * This,
    /* [retval][out] */ CADenialState *penState);


void __RPC_STUB ICADenial_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICADenial_put_State_Proxy( 
    ICADenial * This,
    /* [in] */ CADenialState enState);


void __RPC_STUB ICADenial_put_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICADenial_get_Tolls_Proxy( 
    ICADenial * This,
    /* [retval][out] */ ICATolls **ppTolls);


void __RPC_STUB ICADenial_get_Tolls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICADenial_NotifyTollStateChanged_Proxy( 
    ICADenial * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateFrom);


void __RPC_STUB ICADenial_NotifyTollStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICADenial_INTERFACE_DEFINED__ */


#ifndef __ICAOffer_INTERFACE_DEFINED__
#define __ICAOffer_INTERFACE_DEFINED__

/* interface ICAOffer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAOffer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166350-DF8A-463a-B620-7BEC23542010")
    ICAOffer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CAManager( 
            /* [retval][out] */ ICAManager **ppManager) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CAManager( 
            /* [in] */ ICAManager *pManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Policy( 
            /* [retval][out] */ ICAPolicy **pppolicy) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ CADescFormat enFormat,
            /* [in] */ BSTR bstr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ DATE *pdtStart) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndTime( 
            /* [retval][out] */ DATE *pdtEnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tolls( 
            /* [retval][out] */ ICATolls **ppTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollStateChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAOfferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAOffer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAOffer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAOffer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAOffer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAOffer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAOffer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAOffer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CAManager )( 
            ICAOffer * This,
            /* [retval][out] */ ICAManager **ppManager);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CAManager )( 
            ICAOffer * This,
            /* [in] */ ICAManager *pManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Policy )( 
            ICAOffer * This,
            /* [retval][out] */ ICAPolicy **pppolicy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICAOffer * This,
            /* [in] */ CADescFormat enFormat,
            /* [retval][out] */ BSTR *pbstr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ICAOffer * This,
            /* [in] */ CADescFormat enFormat,
            /* [in] */ BSTR bstr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            ICAOffer * This,
            /* [retval][out] */ DATE *pdtStart);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndTime )( 
            ICAOffer * This,
            /* [retval][out] */ DATE *pdtEnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tolls )( 
            ICAOffer * This,
            /* [retval][out] */ ICATolls **ppTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollStateChanged )( 
            ICAOffer * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateFrom);
        
        END_INTERFACE
    } ICAOfferVtbl;

    interface ICAOffer
    {
        CONST_VTBL struct ICAOfferVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAOffer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAOffer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAOffer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAOffer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAOffer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAOffer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAOffer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAOffer_get_CAManager(This,ppManager)	\
    (This)->lpVtbl -> get_CAManager(This,ppManager)

#define ICAOffer_put_CAManager(This,pManager)	\
    (This)->lpVtbl -> put_CAManager(This,pManager)

#define ICAOffer_get_Policy(This,pppolicy)	\
    (This)->lpVtbl -> get_Policy(This,pppolicy)

#define ICAOffer_get_Description(This,enFormat,pbstr)	\
    (This)->lpVtbl -> get_Description(This,enFormat,pbstr)

#define ICAOffer_put_Description(This,enFormat,bstr)	\
    (This)->lpVtbl -> put_Description(This,enFormat,bstr)

#define ICAOffer_get_StartTime(This,pdtStart)	\
    (This)->lpVtbl -> get_StartTime(This,pdtStart)

#define ICAOffer_get_EndTime(This,pdtEnd)	\
    (This)->lpVtbl -> get_EndTime(This,pdtEnd)

#define ICAOffer_get_Tolls(This,ppTolls)	\
    (This)->lpVtbl -> get_Tolls(This,ppTolls)

#define ICAOffer_NotifyTollStateChanged(This,pToll,enStateFrom)	\
    (This)->lpVtbl -> NotifyTollStateChanged(This,pToll,enStateFrom)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_CAManager_Proxy( 
    ICAOffer * This,
    /* [retval][out] */ ICAManager **ppManager);


void __RPC_STUB ICAOffer_get_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAOffer_put_CAManager_Proxy( 
    ICAOffer * This,
    /* [in] */ ICAManager *pManager);


void __RPC_STUB ICAOffer_put_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_Policy_Proxy( 
    ICAOffer * This,
    /* [retval][out] */ ICAPolicy **pppolicy);


void __RPC_STUB ICAOffer_get_Policy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_Description_Proxy( 
    ICAOffer * This,
    /* [in] */ CADescFormat enFormat,
    /* [retval][out] */ BSTR *pbstr);


void __RPC_STUB ICAOffer_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAOffer_put_Description_Proxy( 
    ICAOffer * This,
    /* [in] */ CADescFormat enFormat,
    /* [in] */ BSTR bstr);


void __RPC_STUB ICAOffer_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_StartTime_Proxy( 
    ICAOffer * This,
    /* [retval][out] */ DATE *pdtStart);


void __RPC_STUB ICAOffer_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_EndTime_Proxy( 
    ICAOffer * This,
    /* [retval][out] */ DATE *pdtEnd);


void __RPC_STUB ICAOffer_get_EndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAOffer_get_Tolls_Proxy( 
    ICAOffer * This,
    /* [retval][out] */ ICATolls **ppTolls);


void __RPC_STUB ICAOffer_get_Tolls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAOffer_NotifyTollStateChanged_Proxy( 
    ICAOffer * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateFrom);


void __RPC_STUB ICAOffer_NotifyTollStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAOffer_INTERFACE_DEFINED__ */


#ifndef __ICAComponent_INTERFACE_DEFINED__
#define __ICAComponent_INTERFACE_DEFINED__

/* interface ICAComponent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAComponent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166360-DF8A-463a-B620-7BEC23542010")
    ICAComponent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Component( 
            /* [retval][out] */ IComponent **ppComponent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Denials( 
            /* [retval][out] */ ICADenials **ppDenials) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Request( 
            /* [retval][out] */ ICARequest **ppComponent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAComponentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAComponent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAComponent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAComponent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAComponent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAComponent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAComponent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAComponent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Component )( 
            ICAComponent * This,
            /* [retval][out] */ IComponent **ppComponent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Denials )( 
            ICAComponent * This,
            /* [retval][out] */ ICADenials **ppDenials);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Request )( 
            ICAComponent * This,
            /* [retval][out] */ ICARequest **ppComponent);
        
        END_INTERFACE
    } ICAComponentVtbl;

    interface ICAComponent
    {
        CONST_VTBL struct ICAComponentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAComponent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAComponent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAComponent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAComponent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAComponent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAComponent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAComponent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAComponent_get_Component(This,ppComponent)	\
    (This)->lpVtbl -> get_Component(This,ppComponent)

#define ICAComponent_get_Denials(This,ppDenials)	\
    (This)->lpVtbl -> get_Denials(This,ppDenials)

#define ICAComponent_get_Request(This,ppComponent)	\
    (This)->lpVtbl -> get_Request(This,ppComponent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponent_get_Component_Proxy( 
    ICAComponent * This,
    /* [retval][out] */ IComponent **ppComponent);


void __RPC_STUB ICAComponent_get_Component_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponent_get_Denials_Proxy( 
    ICAComponent * This,
    /* [retval][out] */ ICADenials **ppDenials);


void __RPC_STUB ICAComponent_get_Denials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAComponent_get_Request_Proxy( 
    ICAComponent * This,
    /* [retval][out] */ ICARequest **ppComponent);


void __RPC_STUB ICAComponent_get_Request_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAComponent_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAManager;

#ifdef __cplusplus

class DECLSPEC_UUID("11166100-DF8A-463a-B620-7BEC23542010")
CAManager;
#endif

EXTERN_C const CLSID CLSID_CAManagerProxy;

#ifdef __cplusplus

class DECLSPEC_UUID("11166101-DF8A-463a-B620-7BEC23542010")
CAManagerProxy;
#endif

EXTERN_C const CLSID CLSID_CADenials;

#ifdef __cplusplus

class DECLSPEC_UUID("11166540-DF8A-463a-B620-7BEC23542010")
CADenials;
#endif

EXTERN_C const CLSID CLSID_CAOffer;

#ifdef __cplusplus

class DECLSPEC_UUID("11166550-DF8A-463a-B620-7BEC23542010")
CAOffer;
#endif

#ifndef __ICAResDenialTree_INTERFACE_DEFINED__
#define __ICAResDenialTree_INTERFACE_DEFINED__

/* interface ICAResDenialTree */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICAResDenialTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11166898-DF8A-463a-B620-7BEC23542010")
    ICAResDenialTree : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CAManager( 
            /* [retval][out] */ ICAManager **ppCAManager) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CAManager( 
            /* [in] */ ICAManager *pCAManager) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayFields( 
            /* [retval][out] */ long *penFields) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisplayFields( 
            /* [in] */ long enFields) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateView( 
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestActivated( 
            /* [in] */ ICARequest *preq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDeactivated( 
            /* [in] */ ICARequest *preq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferAdded( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferRemoved( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyAdded( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPolicyRemoved( 
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialAdded( 
            /* [in] */ ICARequest *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyRequestDenialRemoved( 
            /* [in] */ ICARequest *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollAdded( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialTollRemoved( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialAdded( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollDenialRemoved( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollAdded( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOfferTollRemoved( 
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTollStateChanged( 
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDenialStateChanged( 
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialAdded( 
            /* [in] */ ICAComponent *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyComponentDenialRemoved( 
            /* [in] */ ICAComponent *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICAResDenialTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAResDenialTree * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAResDenialTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAResDenialTree * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAResDenialTree * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAResDenialTree * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAResDenialTree * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAResDenialTree * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CAManager )( 
            ICAResDenialTree * This,
            /* [retval][out] */ ICAManager **ppCAManager);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CAManager )( 
            ICAResDenialTree * This,
            /* [in] */ ICAManager *pCAManager);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayFields )( 
            ICAResDenialTree * This,
            /* [retval][out] */ long *penFields);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisplayFields )( 
            ICAResDenialTree * This,
            /* [in] */ long enFields);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateView )( 
            ICAResDenialTree * This,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestActivated )( 
            ICAResDenialTree * This,
            /* [in] */ ICARequest *preq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDeactivated )( 
            ICAResDenialTree * This,
            /* [in] */ ICARequest *preq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ long cOffers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPolicyRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICAPolicy *pPolicy,
            /* [in] */ long cPolicies);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICARequest *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyRequestDenialRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICARequest *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialTollRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollDenialRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOfferTollRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICAOffer *pOffer,
            /* [in] */ ICAToll *pToll,
            /* [in] */ long cTolls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTollStateChanged )( 
            ICAResDenialTree * This,
            /* [in] */ ICAToll *pToll,
            /* [in] */ CATollState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDenialStateChanged )( 
            ICAResDenialTree * This,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ CADenialState enStateLast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialAdded )( 
            ICAResDenialTree * This,
            /* [in] */ ICAComponent *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyComponentDenialRemoved )( 
            ICAResDenialTree * This,
            /* [in] */ ICAComponent *preq,
            /* [in] */ ICADenial *pDenial,
            /* [in] */ long cDenials);
        
        END_INTERFACE
    } ICAResDenialTreeVtbl;

    interface ICAResDenialTree
    {
        CONST_VTBL struct ICAResDenialTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAResDenialTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICAResDenialTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICAResDenialTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICAResDenialTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICAResDenialTree_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICAResDenialTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICAResDenialTree_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICAResDenialTree_get_CAManager(This,ppCAManager)	\
    (This)->lpVtbl -> get_CAManager(This,ppCAManager)

#define ICAResDenialTree_put_CAManager(This,pCAManager)	\
    (This)->lpVtbl -> put_CAManager(This,pCAManager)

#define ICAResDenialTree_get_DisplayFields(This,penFields)	\
    (This)->lpVtbl -> get_DisplayFields(This,penFields)

#define ICAResDenialTree_put_DisplayFields(This,enFields)	\
    (This)->lpVtbl -> put_DisplayFields(This,enFields)

#define ICAResDenialTree_UpdateView(This,pUnk)	\
    (This)->lpVtbl -> UpdateView(This,pUnk)

#define ICAResDenialTree_NotifyRequestActivated(This,preq)	\
    (This)->lpVtbl -> NotifyRequestActivated(This,preq)

#define ICAResDenialTree_NotifyRequestDeactivated(This,preq)	\
    (This)->lpVtbl -> NotifyRequestDeactivated(This,preq)

#define ICAResDenialTree_NotifyOfferAdded(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferAdded(This,pOffer,cOffers)

#define ICAResDenialTree_NotifyOfferRemoved(This,pOffer,cOffers)	\
    (This)->lpVtbl -> NotifyOfferRemoved(This,pOffer,cOffers)

#define ICAResDenialTree_NotifyPolicyAdded(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyAdded(This,pPolicy,cPolicies)

#define ICAResDenialTree_NotifyPolicyRemoved(This,pPolicy,cPolicies)	\
    (This)->lpVtbl -> NotifyPolicyRemoved(This,pPolicy,cPolicies)

#define ICAResDenialTree_NotifyRequestDenialAdded(This,preq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialAdded(This,preq,pDenial,cDenials)

#define ICAResDenialTree_NotifyRequestDenialRemoved(This,preq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyRequestDenialRemoved(This,preq,pDenial,cDenials)

#define ICAResDenialTree_NotifyDenialTollAdded(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollAdded(This,pDenial,pToll,cTolls)

#define ICAResDenialTree_NotifyDenialTollRemoved(This,pDenial,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyDenialTollRemoved(This,pDenial,pToll,cTolls)

#define ICAResDenialTree_NotifyTollDenialAdded(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialAdded(This,pToll,pDenial,cDenials)

#define ICAResDenialTree_NotifyTollDenialRemoved(This,pToll,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyTollDenialRemoved(This,pToll,pDenial,cDenials)

#define ICAResDenialTree_NotifyOfferTollAdded(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollAdded(This,pOffer,pToll,cTolls)

#define ICAResDenialTree_NotifyOfferTollRemoved(This,pOffer,pToll,cTolls)	\
    (This)->lpVtbl -> NotifyOfferTollRemoved(This,pOffer,pToll,cTolls)

#define ICAResDenialTree_NotifyTollStateChanged(This,pToll,enStateLast)	\
    (This)->lpVtbl -> NotifyTollStateChanged(This,pToll,enStateLast)

#define ICAResDenialTree_NotifyDenialStateChanged(This,pDenial,enStateLast)	\
    (This)->lpVtbl -> NotifyDenialStateChanged(This,pDenial,enStateLast)

#define ICAResDenialTree_NotifyComponentDenialAdded(This,preq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialAdded(This,preq,pDenial,cDenials)

#define ICAResDenialTree_NotifyComponentDenialRemoved(This,preq,pDenial,cDenials)	\
    (This)->lpVtbl -> NotifyComponentDenialRemoved(This,preq,pDenial,cDenials)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_get_CAManager_Proxy( 
    ICAResDenialTree * This,
    /* [retval][out] */ ICAManager **ppCAManager);


void __RPC_STUB ICAResDenialTree_get_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_put_CAManager_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAManager *pCAManager);


void __RPC_STUB ICAResDenialTree_put_CAManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_get_DisplayFields_Proxy( 
    ICAResDenialTree * This,
    /* [retval][out] */ long *penFields);


void __RPC_STUB ICAResDenialTree_get_DisplayFields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_put_DisplayFields_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ long enFields);


void __RPC_STUB ICAResDenialTree_put_DisplayFields_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_UpdateView_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ICAResDenialTree_UpdateView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyRequestActivated_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICARequest *preq);


void __RPC_STUB ICAResDenialTree_NotifyRequestActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyRequestDeactivated_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICARequest *preq);


void __RPC_STUB ICAResDenialTree_NotifyRequestDeactivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyOfferAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAResDenialTree_NotifyOfferAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyOfferRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ long cOffers);


void __RPC_STUB ICAResDenialTree_NotifyOfferRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyPolicyAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAResDenialTree_NotifyPolicyAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyPolicyRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAPolicy *pPolicy,
    /* [in] */ long cPolicies);


void __RPC_STUB ICAResDenialTree_NotifyPolicyRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyRequestDenialAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICARequest *preq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyRequestDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyRequestDenialRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICARequest *preq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyRequestDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyDenialTollAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAResDenialTree_NotifyDenialTollAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyDenialTollRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAResDenialTree_NotifyDenialTollRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyTollDenialAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyTollDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyTollDenialRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyTollDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyOfferTollAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAResDenialTree_NotifyOfferTollAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyOfferTollRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAOffer *pOffer,
    /* [in] */ ICAToll *pToll,
    /* [in] */ long cTolls);


void __RPC_STUB ICAResDenialTree_NotifyOfferTollRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyTollStateChanged_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAToll *pToll,
    /* [in] */ CATollState enStateLast);


void __RPC_STUB ICAResDenialTree_NotifyTollStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyDenialStateChanged_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ CADenialState enStateLast);


void __RPC_STUB ICAResDenialTree_NotifyDenialStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyComponentDenialAdded_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAComponent *preq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyComponentDenialAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICAResDenialTree_NotifyComponentDenialRemoved_Proxy( 
    ICAResDenialTree * This,
    /* [in] */ ICAComponent *preq,
    /* [in] */ ICADenial *pDenial,
    /* [in] */ long cDenials);


void __RPC_STUB ICAResDenialTree_NotifyComponentDenialRemoved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICAResDenialTree_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAResDenialTree;

#ifdef __cplusplus

class DECLSPEC_UUID("11166998-DF8A-463a-B620-7BEC23542010")
CAResDenialTree;
#endif

#ifndef ___ICADefaultDlgEvents_DISPINTERFACE_DEFINED__
#define ___ICADefaultDlgEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICADefaultDlgEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICADefaultDlgEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11166991-DF8A-463a-B620-7BEC23542010")
    _ICADefaultDlgEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICADefaultDlgEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICADefaultDlgEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICADefaultDlgEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICADefaultDlgEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICADefaultDlgEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICADefaultDlgEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICADefaultDlgEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICADefaultDlgEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICADefaultDlgEventsVtbl;

    interface _ICADefaultDlgEvents
    {
        CONST_VTBL struct _ICADefaultDlgEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICADefaultDlgEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ICADefaultDlgEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ICADefaultDlgEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ICADefaultDlgEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ICADefaultDlgEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ICADefaultDlgEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ICADefaultDlgEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICADefaultDlgEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CADefaultDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("11166990-DF8A-463a-B620-7BEC23542010")
CADefaultDlg;
#endif
#endif /* __MSTvCALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


