
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for mstve.idl:
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

#ifndef __mstve_h__
#define __mstve_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITVETrigger_FWD_DEFINED__
#define __ITVETrigger_FWD_DEFINED__
typedef interface ITVETrigger ITVETrigger;
#endif 	/* __ITVETrigger_FWD_DEFINED__ */


#ifndef __ITVETrigger_Helper_FWD_DEFINED__
#define __ITVETrigger_Helper_FWD_DEFINED__
typedef interface ITVETrigger_Helper ITVETrigger_Helper;
#endif 	/* __ITVETrigger_Helper_FWD_DEFINED__ */


#ifndef __ITVETrack_FWD_DEFINED__
#define __ITVETrack_FWD_DEFINED__
typedef interface ITVETrack ITVETrack;
#endif 	/* __ITVETrack_FWD_DEFINED__ */


#ifndef __ITVETrack_Helper_FWD_DEFINED__
#define __ITVETrack_Helper_FWD_DEFINED__
typedef interface ITVETrack_Helper ITVETrack_Helper;
#endif 	/* __ITVETrack_Helper_FWD_DEFINED__ */


#ifndef __ITVETracks_FWD_DEFINED__
#define __ITVETracks_FWD_DEFINED__
typedef interface ITVETracks ITVETracks;
#endif 	/* __ITVETracks_FWD_DEFINED__ */


#ifndef __ITVEVariation_FWD_DEFINED__
#define __ITVEVariation_FWD_DEFINED__
typedef interface ITVEVariation ITVEVariation;
#endif 	/* __ITVEVariation_FWD_DEFINED__ */


#ifndef __ITVEVariation_Helper_FWD_DEFINED__
#define __ITVEVariation_Helper_FWD_DEFINED__
typedef interface ITVEVariation_Helper ITVEVariation_Helper;
#endif 	/* __ITVEVariation_Helper_FWD_DEFINED__ */


#ifndef __ITVEVariations_FWD_DEFINED__
#define __ITVEVariations_FWD_DEFINED__
typedef interface ITVEVariations ITVEVariations;
#endif 	/* __ITVEVariations_FWD_DEFINED__ */


#ifndef __ITVEEnhancement_FWD_DEFINED__
#define __ITVEEnhancement_FWD_DEFINED__
typedef interface ITVEEnhancement ITVEEnhancement;
#endif 	/* __ITVEEnhancement_FWD_DEFINED__ */


#ifndef __ITVEEnhancement_Helper_FWD_DEFINED__
#define __ITVEEnhancement_Helper_FWD_DEFINED__
typedef interface ITVEEnhancement_Helper ITVEEnhancement_Helper;
#endif 	/* __ITVEEnhancement_Helper_FWD_DEFINED__ */


#ifndef __ITVEEnhancements_FWD_DEFINED__
#define __ITVEEnhancements_FWD_DEFINED__
typedef interface ITVEEnhancements ITVEEnhancements;
#endif 	/* __ITVEEnhancements_FWD_DEFINED__ */


#ifndef __ITVEService_FWD_DEFINED__
#define __ITVEService_FWD_DEFINED__
typedef interface ITVEService ITVEService;
#endif 	/* __ITVEService_FWD_DEFINED__ */


#ifndef __ITVEService_Helper_FWD_DEFINED__
#define __ITVEService_Helper_FWD_DEFINED__
typedef interface ITVEService_Helper ITVEService_Helper;
#endif 	/* __ITVEService_Helper_FWD_DEFINED__ */


#ifndef __ITVEFeature_FWD_DEFINED__
#define __ITVEFeature_FWD_DEFINED__
typedef interface ITVEFeature ITVEFeature;
#endif 	/* __ITVEFeature_FWD_DEFINED__ */


#ifndef __ITVEServices_FWD_DEFINED__
#define __ITVEServices_FWD_DEFINED__
typedef interface ITVEServices ITVEServices;
#endif 	/* __ITVEServices_FWD_DEFINED__ */


#ifndef __ITVESupervisor_FWD_DEFINED__
#define __ITVESupervisor_FWD_DEFINED__
typedef interface ITVESupervisor ITVESupervisor;
#endif 	/* __ITVESupervisor_FWD_DEFINED__ */


#ifndef __ITVESupervisor_Helper_FWD_DEFINED__
#define __ITVESupervisor_Helper_FWD_DEFINED__
typedef interface ITVESupervisor_Helper ITVESupervisor_Helper;
#endif 	/* __ITVESupervisor_Helper_FWD_DEFINED__ */


#ifndef __ITVESupervisorGITProxy_FWD_DEFINED__
#define __ITVESupervisorGITProxy_FWD_DEFINED__
typedef interface ITVESupervisorGITProxy ITVESupervisorGITProxy;
#endif 	/* __ITVESupervisorGITProxy_FWD_DEFINED__ */


#ifndef __ITVEAttrMap_FWD_DEFINED__
#define __ITVEAttrMap_FWD_DEFINED__
typedef interface ITVEAttrMap ITVEAttrMap;
#endif 	/* __ITVEAttrMap_FWD_DEFINED__ */


#ifndef __ITVEAttrTimeQ_FWD_DEFINED__
#define __ITVEAttrTimeQ_FWD_DEFINED__
typedef interface ITVEAttrTimeQ ITVEAttrTimeQ;
#endif 	/* __ITVEAttrTimeQ_FWD_DEFINED__ */


#ifndef __ITVEMCast_FWD_DEFINED__
#define __ITVEMCast_FWD_DEFINED__
typedef interface ITVEMCast ITVEMCast;
#endif 	/* __ITVEMCast_FWD_DEFINED__ */


#ifndef __ITVEMCasts_FWD_DEFINED__
#define __ITVEMCasts_FWD_DEFINED__
typedef interface ITVEMCasts ITVEMCasts;
#endif 	/* __ITVEMCasts_FWD_DEFINED__ */


#ifndef __ITVEMCastManager_FWD_DEFINED__
#define __ITVEMCastManager_FWD_DEFINED__
typedef interface ITVEMCastManager ITVEMCastManager;
#endif 	/* __ITVEMCastManager_FWD_DEFINED__ */


#ifndef __ITVEMCastManager_Helper_FWD_DEFINED__
#define __ITVEMCastManager_Helper_FWD_DEFINED__
typedef interface ITVEMCastManager_Helper ITVEMCastManager_Helper;
#endif 	/* __ITVEMCastManager_Helper_FWD_DEFINED__ */


#ifndef __ITVEMCastCallback_FWD_DEFINED__
#define __ITVEMCastCallback_FWD_DEFINED__
typedef interface ITVEMCastCallback ITVEMCastCallback;
#endif 	/* __ITVEMCastCallback_FWD_DEFINED__ */


#ifndef __ITVECBAnnc_FWD_DEFINED__
#define __ITVECBAnnc_FWD_DEFINED__
typedef interface ITVECBAnnc ITVECBAnnc;
#endif 	/* __ITVECBAnnc_FWD_DEFINED__ */


#ifndef __ITVECBTrig_FWD_DEFINED__
#define __ITVECBTrig_FWD_DEFINED__
typedef interface ITVECBTrig ITVECBTrig;
#endif 	/* __ITVECBTrig_FWD_DEFINED__ */


#ifndef __ITVECBFile_FWD_DEFINED__
#define __ITVECBFile_FWD_DEFINED__
typedef interface ITVECBFile ITVECBFile;
#endif 	/* __ITVECBFile_FWD_DEFINED__ */


#ifndef __ITVECBDummy_FWD_DEFINED__
#define __ITVECBDummy_FWD_DEFINED__
typedef interface ITVECBDummy ITVECBDummy;
#endif 	/* __ITVECBDummy_FWD_DEFINED__ */


#ifndef __ITVEFile_FWD_DEFINED__
#define __ITVEFile_FWD_DEFINED__
typedef interface ITVEFile ITVEFile;
#endif 	/* __ITVEFile_FWD_DEFINED__ */


#ifndef __ITVENavAid_FWD_DEFINED__
#define __ITVENavAid_FWD_DEFINED__
typedef interface ITVENavAid ITVENavAid;
#endif 	/* __ITVENavAid_FWD_DEFINED__ */


#ifndef __ITVENavAid_NoVidCtl_FWD_DEFINED__
#define __ITVENavAid_NoVidCtl_FWD_DEFINED__
typedef interface ITVENavAid_NoVidCtl ITVENavAid_NoVidCtl;
#endif 	/* __ITVENavAid_NoVidCtl_FWD_DEFINED__ */


#ifndef __ITVENavAid_Helper_FWD_DEFINED__
#define __ITVENavAid_Helper_FWD_DEFINED__
typedef interface ITVENavAid_Helper ITVENavAid_Helper;
#endif 	/* __ITVENavAid_Helper_FWD_DEFINED__ */


#ifndef __ITVEFilter_FWD_DEFINED__
#define __ITVEFilter_FWD_DEFINED__
typedef interface ITVEFilter ITVEFilter;
#endif 	/* __ITVEFilter_FWD_DEFINED__ */


#ifndef __ITVEFilter_Helper_FWD_DEFINED__
#define __ITVEFilter_Helper_FWD_DEFINED__
typedef interface ITVEFilter_Helper ITVEFilter_Helper;
#endif 	/* __ITVEFilter_Helper_FWD_DEFINED__ */


#ifndef __ITVETriggerCtrl_FWD_DEFINED__
#define __ITVETriggerCtrl_FWD_DEFINED__
typedef interface ITVETriggerCtrl ITVETriggerCtrl;
#endif 	/* __ITVETriggerCtrl_FWD_DEFINED__ */


#ifndef __ITVETriggerCtrl_Helper_FWD_DEFINED__
#define __ITVETriggerCtrl_Helper_FWD_DEFINED__
typedef interface ITVETriggerCtrl_Helper ITVETriggerCtrl_Helper;
#endif 	/* __ITVETriggerCtrl_Helper_FWD_DEFINED__ */


#ifndef ___ITVEEvents_FWD_DEFINED__
#define ___ITVEEvents_FWD_DEFINED__
typedef interface _ITVEEvents _ITVEEvents;
#endif 	/* ___ITVEEvents_FWD_DEFINED__ */


#ifndef __TVETrigger_FWD_DEFINED__
#define __TVETrigger_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVETrigger TVETrigger;
#else
typedef struct TVETrigger TVETrigger;
#endif /* __cplusplus */

#endif 	/* __TVETrigger_FWD_DEFINED__ */


#ifndef __TVETrack_FWD_DEFINED__
#define __TVETrack_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVETrack TVETrack;
#else
typedef struct TVETrack TVETrack;
#endif /* __cplusplus */

#endif 	/* __TVETrack_FWD_DEFINED__ */


#ifndef __TVEVariation_FWD_DEFINED__
#define __TVEVariation_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEVariation TVEVariation;
#else
typedef struct TVEVariation TVEVariation;
#endif /* __cplusplus */

#endif 	/* __TVEVariation_FWD_DEFINED__ */


#ifndef __TVEEnhancement_FWD_DEFINED__
#define __TVEEnhancement_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEEnhancement TVEEnhancement;
#else
typedef struct TVEEnhancement TVEEnhancement;
#endif /* __cplusplus */

#endif 	/* __TVEEnhancement_FWD_DEFINED__ */


#ifndef __TVEEnhancements_FWD_DEFINED__
#define __TVEEnhancements_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEEnhancements TVEEnhancements;
#else
typedef struct TVEEnhancements TVEEnhancements;
#endif /* __cplusplus */

#endif 	/* __TVEEnhancements_FWD_DEFINED__ */


#ifndef __TVEService_FWD_DEFINED__
#define __TVEService_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEService TVEService;
#else
typedef struct TVEService TVEService;
#endif /* __cplusplus */

#endif 	/* __TVEService_FWD_DEFINED__ */


#ifndef __TVEFeature_FWD_DEFINED__
#define __TVEFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEFeature TVEFeature;
#else
typedef struct TVEFeature TVEFeature;
#endif /* __cplusplus */

#endif 	/* __TVEFeature_FWD_DEFINED__ */


#ifndef __TVEServices_FWD_DEFINED__
#define __TVEServices_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEServices TVEServices;
#else
typedef struct TVEServices TVEServices;
#endif /* __cplusplus */

#endif 	/* __TVEServices_FWD_DEFINED__ */


#ifndef __TVESupervisor_FWD_DEFINED__
#define __TVESupervisor_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVESupervisor TVESupervisor;
#else
typedef struct TVESupervisor TVESupervisor;
#endif /* __cplusplus */

#endif 	/* __TVESupervisor_FWD_DEFINED__ */


#ifndef __TVEAttrMap_FWD_DEFINED__
#define __TVEAttrMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEAttrMap TVEAttrMap;
#else
typedef struct TVEAttrMap TVEAttrMap;
#endif /* __cplusplus */

#endif 	/* __TVEAttrMap_FWD_DEFINED__ */


#ifndef __TVEAttrTimeQ_FWD_DEFINED__
#define __TVEAttrTimeQ_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEAttrTimeQ TVEAttrTimeQ;
#else
typedef struct TVEAttrTimeQ TVEAttrTimeQ;
#endif /* __cplusplus */

#endif 	/* __TVEAttrTimeQ_FWD_DEFINED__ */


#ifndef __TVEMCast_FWD_DEFINED__
#define __TVEMCast_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEMCast TVEMCast;
#else
typedef struct TVEMCast TVEMCast;
#endif /* __cplusplus */

#endif 	/* __TVEMCast_FWD_DEFINED__ */


#ifndef __TVEMCasts_FWD_DEFINED__
#define __TVEMCasts_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEMCasts TVEMCasts;
#else
typedef struct TVEMCasts TVEMCasts;
#endif /* __cplusplus */

#endif 	/* __TVEMCasts_FWD_DEFINED__ */


#ifndef __TVEMCastManager_FWD_DEFINED__
#define __TVEMCastManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEMCastManager TVEMCastManager;
#else
typedef struct TVEMCastManager TVEMCastManager;
#endif /* __cplusplus */

#endif 	/* __TVEMCastManager_FWD_DEFINED__ */


#ifndef __TVEMCastCallback_FWD_DEFINED__
#define __TVEMCastCallback_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEMCastCallback TVEMCastCallback;
#else
typedef struct TVEMCastCallback TVEMCastCallback;
#endif /* __cplusplus */

#endif 	/* __TVEMCastCallback_FWD_DEFINED__ */


#ifndef __TVECBAnnc_FWD_DEFINED__
#define __TVECBAnnc_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVECBAnnc TVECBAnnc;
#else
typedef struct TVECBAnnc TVECBAnnc;
#endif /* __cplusplus */

#endif 	/* __TVECBAnnc_FWD_DEFINED__ */


#ifndef __TVECBTrig_FWD_DEFINED__
#define __TVECBTrig_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVECBTrig TVECBTrig;
#else
typedef struct TVECBTrig TVECBTrig;
#endif /* __cplusplus */

#endif 	/* __TVECBTrig_FWD_DEFINED__ */


#ifndef __TVECBFile_FWD_DEFINED__
#define __TVECBFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVECBFile TVECBFile;
#else
typedef struct TVECBFile TVECBFile;
#endif /* __cplusplus */

#endif 	/* __TVECBFile_FWD_DEFINED__ */


#ifndef __TVECBDummy_FWD_DEFINED__
#define __TVECBDummy_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVECBDummy TVECBDummy;
#else
typedef struct TVECBDummy TVECBDummy;
#endif /* __cplusplus */

#endif 	/* __TVECBDummy_FWD_DEFINED__ */


#ifndef __TVEFile_FWD_DEFINED__
#define __TVEFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEFile TVEFile;
#else
typedef struct TVEFile TVEFile;
#endif /* __cplusplus */

#endif 	/* __TVEFile_FWD_DEFINED__ */


#ifndef __TVENavAid_FWD_DEFINED__
#define __TVENavAid_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVENavAid TVENavAid;
#else
typedef struct TVENavAid TVENavAid;
#endif /* __cplusplus */

#endif 	/* __TVENavAid_FWD_DEFINED__ */


#ifndef __TVEFilter_FWD_DEFINED__
#define __TVEFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVEFilter TVEFilter;
#else
typedef struct TVEFilter TVEFilter;
#endif /* __cplusplus */

#endif 	/* __TVEFilter_FWD_DEFINED__ */


#ifndef ___ITVETriggerCtrlEvents_FWD_DEFINED__
#define ___ITVETriggerCtrlEvents_FWD_DEFINED__
typedef interface _ITVETriggerCtrlEvents _ITVETriggerCtrlEvents;
#endif 	/* ___ITVETriggerCtrlEvents_FWD_DEFINED__ */


#ifndef __TVETriggerCtrl_FWD_DEFINED__
#define __TVETriggerCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVETriggerCtrl TVETriggerCtrl;
#else
typedef struct TVETriggerCtrl TVETriggerCtrl;
#endif /* __cplusplus */

#endif 	/* __TVETriggerCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mstve_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1999, 2000.
//
//--------------------------------------------------------------------------
#pragma once




























typedef 
enum NENH_Mode
    {	NENH_New	= 0,
	NENH_Duplicate	= NENH_New + 1,
	NENH_Updated	= NENH_Duplicate + 1,
	NENH_Starting	= NENH_Updated + 1,
	NENH_Expired	= NENH_Starting + 1
    } 	NENH_Mode;

typedef 
enum NPKG_Mode
    {	NPKG_Starting	= 0,
	NPKG_Received	= NPKG_Starting + 1,
	NPKG_Duplicate	= NPKG_Received + 1,
	NPKG_Resend	= NPKG_Duplicate + 1,
	NPKG_Expired	= NPKG_Resend + 1
    } 	NPKG_Mode;

typedef 
enum NTRK_Mode
    {	NTRK_New	= 0,
	NTRK_Duplicate	= NTRK_New + 1,
	NTRK_Updated	= NTRK_Duplicate + 1,
	NTRK_Starting	= NTRK_Updated + 1,
	NTRK_Expired	= NTRK_Starting + 1
    } 	NTRK_Mode;

typedef 
enum NFLE_Mode
    {	NFLE_Received	= 0,
	NFLE_Expired	= NFLE_Received + 1
    } 	NFLE_Mode;

typedef 
enum NTUN_Mode
    {	NTUN_New	= 0,
	NTUN_Retune	= NTUN_New + 1,
	NTUN_Reactivate	= NTUN_Retune + 1,
	NTUN_Turnoff	= NTUN_Reactivate + 1,
	NTUN_Fail	= NTUN_Turnoff + 1
    } 	NTUN_Mode;

typedef 
enum NWHAT_Mode
    {	NWHAT_Announcement	= 0,
	NWHAT_Trigger	= NWHAT_Announcement + 1,
	NWHAT_Data	= NWHAT_Trigger + 1,
	NWHAT_Other	= NWHAT_Data + 1,
	NWHAT_Extra	= NWHAT_Other + 1
    } 	NWHAT_Mode;



extern RPC_IF_HANDLE __MIDL_itf_mstve_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mstve_0000_v0_0_s_ifspec;

#ifndef __ITVETrigger_INTERFACE_DEFINED__
#define __ITVETrigger_INTERFACE_DEFINED__

/* interface ITVETrigger */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVETrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500101-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETrigger : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Service( 
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Expires( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Executes( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Script( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TVELevel( 
            /* [retval][out] */ float *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rest( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseTrigger( 
            /* [in] */ const BSTR rVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVETrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVETrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVETrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVETrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVETrigger * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Service )( 
            ITVETrigger * This,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsValid )( 
            ITVETrigger * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_URL )( 
            ITVETrigger * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITVETrigger * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Expires )( 
            ITVETrigger * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Executes )( 
            ITVETrigger * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Script )( 
            ITVETrigger * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TVELevel )( 
            ITVETrigger * This,
            /* [retval][out] */ float *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rest )( 
            ITVETrigger * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ParseTrigger )( 
            ITVETrigger * This,
            /* [in] */ const BSTR rVal);
        
        END_INTERFACE
    } ITVETriggerVtbl;

    interface ITVETrigger
    {
        CONST_VTBL struct ITVETriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETrigger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETrigger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETrigger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETrigger_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVETrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVETrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVETrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVETrigger_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVETrigger_get_Service(This,pVal)	\
    (This)->lpVtbl -> get_Service(This,pVal)

#define ITVETrigger_get_IsValid(This,pVal)	\
    (This)->lpVtbl -> get_IsValid(This,pVal)

#define ITVETrigger_get_URL(This,pVal)	\
    (This)->lpVtbl -> get_URL(This,pVal)

#define ITVETrigger_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITVETrigger_get_Expires(This,pVal)	\
    (This)->lpVtbl -> get_Expires(This,pVal)

#define ITVETrigger_get_Executes(This,pVal)	\
    (This)->lpVtbl -> get_Executes(This,pVal)

#define ITVETrigger_get_Script(This,pVal)	\
    (This)->lpVtbl -> get_Script(This,pVal)

#define ITVETrigger_get_TVELevel(This,pVal)	\
    (This)->lpVtbl -> get_TVELevel(This,pVal)

#define ITVETrigger_get_Rest(This,pVal)	\
    (This)->lpVtbl -> get_Rest(This,pVal)

#define ITVETrigger_ParseTrigger(This,rVal)	\
    (This)->lpVtbl -> ParseTrigger(This,rVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Parent_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITVETrigger_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Service_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVETrigger_get_Service_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_IsValid_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVETrigger_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_URL_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETrigger_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Name_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETrigger_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Expires_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITVETrigger_get_Expires_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Executes_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITVETrigger_get_Executes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Script_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETrigger_get_Script_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_TVELevel_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ float *pVal);


void __RPC_STUB ITVETrigger_get_TVELevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_get_Rest_Proxy( 
    ITVETrigger * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETrigger_get_Rest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrigger_ParseTrigger_Proxy( 
    ITVETrigger * This,
    /* [in] */ const BSTR rVal);


void __RPC_STUB ITVETrigger_ParseTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETrigger_INTERFACE_DEFINED__ */


#ifndef __ITVETrigger_Helper_INTERFACE_DEFINED__
#define __ITVETrigger_Helper_INTERFACE_DEFINED__

/* interface ITVETrigger_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVETrigger_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500201-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETrigger_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            /* [in] */ ITVETrack *pTrack) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CRC( 
            /* [in] */ const BSTR rVal,
            /* [retval][out] */ BSTR *pbstrCRC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateFrom( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [out] */ long *plgrfTRKChanged) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETrigger_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETrigger_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETrigger_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETrigger_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVETrigger_Helper * This,
            /* [in] */ ITVETrack *pTrack);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CRC )( 
            ITVETrigger_Helper * This,
            /* [in] */ const BSTR rVal,
            /* [retval][out] */ BSTR *pbstrCRC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateFrom )( 
            ITVETrigger_Helper * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [out] */ long *plgrfTRKChanged);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVETrigger_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVETrigger_Helper * This,
            /* [out] */ BSTR *pbstrBuff);
        
        END_INTERFACE
    } ITVETrigger_HelperVtbl;

    interface ITVETrigger_Helper
    {
        CONST_VTBL struct ITVETrigger_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETrigger_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETrigger_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETrigger_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETrigger_Helper_ConnectParent(This,pTrack)	\
    (This)->lpVtbl -> ConnectParent(This,pTrack)

#define ITVETrigger_Helper_get_CRC(This,rVal,pbstrCRC)	\
    (This)->lpVtbl -> get_CRC(This,rVal,pbstrCRC)

#define ITVETrigger_Helper_UpdateFrom(This,pTrigger,plgrfTRKChanged)	\
    (This)->lpVtbl -> UpdateFrom(This,pTrigger,plgrfTRKChanged)

#define ITVETrigger_Helper_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVETrigger_Helper_DumpToBSTR(This,pbstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,pbstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrigger_Helper_ConnectParent_Proxy( 
    ITVETrigger_Helper * This,
    /* [in] */ ITVETrack *pTrack);


void __RPC_STUB ITVETrigger_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrigger_Helper_get_CRC_Proxy( 
    ITVETrigger_Helper * This,
    /* [in] */ const BSTR rVal,
    /* [retval][out] */ BSTR *pbstrCRC);


void __RPC_STUB ITVETrigger_Helper_get_CRC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrigger_Helper_UpdateFrom_Proxy( 
    ITVETrigger_Helper * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [out] */ long *plgrfTRKChanged);


void __RPC_STUB ITVETrigger_Helper_UpdateFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrigger_Helper_RemoveYourself_Proxy( 
    ITVETrigger_Helper * This);


void __RPC_STUB ITVETrigger_Helper_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrigger_Helper_DumpToBSTR_Proxy( 
    ITVETrigger_Helper * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVETrigger_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETrigger_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVETrack_INTERFACE_DEFINED__
#define __ITVETrack_INTERFACE_DEFINED__

/* interface ITVETrack */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVETrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500102-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETrack : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Service( 
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Trigger( 
            /* [retval][out] */ ITVETrigger **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachTrigger( 
            /* [in] */ ITVETrigger *pTrigger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseTrigger( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTrigger( 
            /* [in] */ const BSTR bstrDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETrack * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETrack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETrack * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVETrack * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVETrack * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVETrack * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVETrack * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVETrack * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Service )( 
            ITVETrack * This,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Trigger )( 
            ITVETrack * This,
            /* [retval][out] */ ITVETrigger **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVETrack * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVETrack * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AttachTrigger )( 
            ITVETrack * This,
            /* [in] */ ITVETrigger *pTrigger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseTrigger )( 
            ITVETrack * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTrigger )( 
            ITVETrack * This,
            /* [in] */ const BSTR bstrDescription);
        
        END_INTERFACE
    } ITVETrackVtbl;

    interface ITVETrack
    {
        CONST_VTBL struct ITVETrackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETrack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETrack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETrack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETrack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVETrack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVETrack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVETrack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVETrack_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVETrack_get_Service(This,pVal)	\
    (This)->lpVtbl -> get_Service(This,pVal)

#define ITVETrack_get_Trigger(This,pVal)	\
    (This)->lpVtbl -> get_Trigger(This,pVal)

#define ITVETrack_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVETrack_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVETrack_AttachTrigger(This,pTrigger)	\
    (This)->lpVtbl -> AttachTrigger(This,pTrigger)

#define ITVETrack_ReleaseTrigger(This)	\
    (This)->lpVtbl -> ReleaseTrigger(This)

#define ITVETrack_CreateTrigger(This,bstrDescription)	\
    (This)->lpVtbl -> CreateTrigger(This,bstrDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrack_get_Parent_Proxy( 
    ITVETrack * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITVETrack_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrack_get_Service_Proxy( 
    ITVETrack * This,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVETrack_get_Service_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrack_get_Trigger_Proxy( 
    ITVETrack * This,
    /* [retval][out] */ ITVETrigger **pVal);


void __RPC_STUB ITVETrack_get_Trigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETrack_get_Description_Proxy( 
    ITVETrack * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETrack_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVETrack_put_Description_Proxy( 
    ITVETrack * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVETrack_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_AttachTrigger_Proxy( 
    ITVETrack * This,
    /* [in] */ ITVETrigger *pTrigger);


void __RPC_STUB ITVETrack_AttachTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_ReleaseTrigger_Proxy( 
    ITVETrack * This);


void __RPC_STUB ITVETrack_ReleaseTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_CreateTrigger_Proxy( 
    ITVETrack * This,
    /* [in] */ const BSTR bstrDescription);


void __RPC_STUB ITVETrack_CreateTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETrack_INTERFACE_DEFINED__ */


#ifndef __ITVETrack_Helper_INTERFACE_DEFINED__
#define __ITVETrack_Helper_INTERFACE_DEFINED__

/* interface ITVETrack_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVETrack_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500202-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETrack_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            ITVEVariation *pVariation) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETrack_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETrack_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETrack_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETrack_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVETrack_Helper * This,
            ITVEVariation *pVariation);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVETrack_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVETrack_Helper * This,
            /* [out] */ BSTR *pbstrBuff);
        
        END_INTERFACE
    } ITVETrack_HelperVtbl;

    interface ITVETrack_Helper
    {
        CONST_VTBL struct ITVETrack_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETrack_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETrack_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETrack_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETrack_Helper_ConnectParent(This,pVariation)	\
    (This)->lpVtbl -> ConnectParent(This,pVariation)

#define ITVETrack_Helper_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVETrack_Helper_DumpToBSTR(This,pbstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,pbstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_Helper_ConnectParent_Proxy( 
    ITVETrack_Helper * This,
    ITVEVariation *pVariation);


void __RPC_STUB ITVETrack_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_Helper_RemoveYourself_Proxy( 
    ITVETrack_Helper * This);


void __RPC_STUB ITVETrack_Helper_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETrack_Helper_DumpToBSTR_Proxy( 
    ITVETrack_Helper * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVETrack_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETrack_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVETracks_INTERFACE_DEFINED__
#define __ITVETracks_INTERFACE_DEFINED__

/* interface ITVETracks */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVETracks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500112-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETracks : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVETrack **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITVETrack *pTrack) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ int iLoc,
            /* [in] */ ITVETrack *pTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETracksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETracks * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETracks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETracks * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVETracks * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVETracks * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVETracks * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVETracks * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVETracks * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVETracks * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVETracks * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVETrack **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVETracks * This,
            /* [in] */ ITVETrack *pTrack);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVETracks * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVETracks * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ITVETracks * This,
            /* [in] */ int iLoc,
            /* [in] */ ITVETrack *pTrack);
        
        END_INTERFACE
    } ITVETracksVtbl;

    interface ITVETracks
    {
        CONST_VTBL struct ITVETracksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETracks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETracks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETracks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETracks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVETracks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVETracks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVETracks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVETracks_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVETracks_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVETracks_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVETracks_Add(This,pTrack)	\
    (This)->lpVtbl -> Add(This,pTrack)

#define ITVETracks_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVETracks_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVETracks_Insert(This,iLoc,pTrack)	\
    (This)->lpVtbl -> Insert(This,iLoc,pTrack)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETracks_get__NewEnum_Proxy( 
    ITVETracks * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVETracks_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETracks_get_Count_Proxy( 
    ITVETracks * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVETracks_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVETracks_get_Item_Proxy( 
    ITVETracks * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ ITVETrack **pVal);


void __RPC_STUB ITVETracks_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETracks_Add_Proxy( 
    ITVETracks * This,
    /* [in] */ ITVETrack *pTrack);


void __RPC_STUB ITVETracks_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETracks_Remove_Proxy( 
    ITVETracks * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVETracks_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETracks_RemoveAll_Proxy( 
    ITVETracks * This);


void __RPC_STUB ITVETracks_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVETracks_Insert_Proxy( 
    ITVETracks * This,
    /* [in] */ int iLoc,
    /* [in] */ ITVETrack *pTrack);


void __RPC_STUB ITVETracks_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETracks_INTERFACE_DEFINED__ */


#ifndef __ITVEVariation_INTERFACE_DEFINED__
#define __ITVEVariation_INTERFACE_DEFINED__

/* interface ITVEVariation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEVariation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500103-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEVariation : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Service( 
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tracks( 
            /* [retval][out] */ ITVETracks **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaName( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTitle( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileIPAdapter( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileIPAddress( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilePort( 
            /* [retval][out] */ LONG *lPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TriggerIPAdapter( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TriggerIPAddress( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TriggerPort( 
            /* [retval][out] */ LONG *lPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Languages( 
            /* [retval][out] */ ITVEAttrMap **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SDPLanguages( 
            /* [retval][out] */ ITVEAttrMap **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bandwidth( 
            /* [retval][out] */ LONG *lVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BandwidthInfo( 
            /* [retval][out] */ BSTR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ ITVEAttrMap **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rest( 
            /* [retval][out] */ ITVEAttrMap **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEVariationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEVariation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEVariation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEVariation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEVariation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEVariation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEVariation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEVariation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVEVariation * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Service )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tracks )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVETracks **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVEVariation * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsValid )( 
            ITVEVariation * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaName )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaTitle )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileIPAdapter )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileIPAddress )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilePort )( 
            ITVEVariation * This,
            /* [retval][out] */ LONG *lPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TriggerIPAdapter )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TriggerIPAddress )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TriggerPort )( 
            ITVEVariation * This,
            /* [retval][out] */ LONG *lPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Languages )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVEAttrMap **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SDPLanguages )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVEAttrMap **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bandwidth )( 
            ITVEVariation * This,
            /* [retval][out] */ LONG *lVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BandwidthInfo )( 
            ITVEVariation * This,
            /* [retval][out] */ BSTR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVEAttrMap **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rest )( 
            ITVEVariation * This,
            /* [retval][out] */ ITVEAttrMap **ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ITVEVariation * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ITVEVariationVtbl;

    interface ITVEVariation
    {
        CONST_VTBL struct ITVEVariationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEVariation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEVariation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEVariation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEVariation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEVariation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEVariation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEVariation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEVariation_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVEVariation_get_Service(This,pVal)	\
    (This)->lpVtbl -> get_Service(This,pVal)

#define ITVEVariation_get_Tracks(This,pVal)	\
    (This)->lpVtbl -> get_Tracks(This,pVal)

#define ITVEVariation_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVEVariation_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVEVariation_get_IsValid(This,pVal)	\
    (This)->lpVtbl -> get_IsValid(This,pVal)

#define ITVEVariation_get_MediaName(This,newVal)	\
    (This)->lpVtbl -> get_MediaName(This,newVal)

#define ITVEVariation_get_MediaTitle(This,newVal)	\
    (This)->lpVtbl -> get_MediaTitle(This,newVal)

#define ITVEVariation_get_FileIPAdapter(This,newVal)	\
    (This)->lpVtbl -> get_FileIPAdapter(This,newVal)

#define ITVEVariation_get_FileIPAddress(This,newVal)	\
    (This)->lpVtbl -> get_FileIPAddress(This,newVal)

#define ITVEVariation_get_FilePort(This,lPort)	\
    (This)->lpVtbl -> get_FilePort(This,lPort)

#define ITVEVariation_get_TriggerIPAdapter(This,newVal)	\
    (This)->lpVtbl -> get_TriggerIPAdapter(This,newVal)

#define ITVEVariation_get_TriggerIPAddress(This,newVal)	\
    (This)->lpVtbl -> get_TriggerIPAddress(This,newVal)

#define ITVEVariation_get_TriggerPort(This,lPort)	\
    (This)->lpVtbl -> get_TriggerPort(This,lPort)

#define ITVEVariation_get_Languages(This,ppVal)	\
    (This)->lpVtbl -> get_Languages(This,ppVal)

#define ITVEVariation_get_SDPLanguages(This,ppVal)	\
    (This)->lpVtbl -> get_SDPLanguages(This,ppVal)

#define ITVEVariation_get_Bandwidth(This,lVal)	\
    (This)->lpVtbl -> get_Bandwidth(This,lVal)

#define ITVEVariation_get_BandwidthInfo(This,newVal)	\
    (This)->lpVtbl -> get_BandwidthInfo(This,newVal)

#define ITVEVariation_get_Attributes(This,ppVal)	\
    (This)->lpVtbl -> get_Attributes(This,ppVal)

#define ITVEVariation_get_Rest(This,ppVal)	\
    (This)->lpVtbl -> get_Rest(This,ppVal)

#define ITVEVariation_Initialize(This,newVal)	\
    (This)->lpVtbl -> Initialize(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Parent_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITVEVariation_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Service_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVEVariation_get_Service_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Tracks_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVETracks **pVal);


void __RPC_STUB ITVEVariation_get_Tracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Description_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEVariation_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEVariation_put_Description_Proxy( 
    ITVEVariation * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEVariation_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_IsValid_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVEVariation_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_MediaName_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_MediaName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_MediaTitle_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_MediaTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_FileIPAdapter_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_FileIPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_FileIPAddress_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_FileIPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_FilePort_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ LONG *lPort);


void __RPC_STUB ITVEVariation_get_FilePort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_TriggerIPAdapter_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_TriggerIPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_TriggerIPAddress_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_TriggerIPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_TriggerPort_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ LONG *lPort);


void __RPC_STUB ITVEVariation_get_TriggerPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Languages_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVEAttrMap **ppVal);


void __RPC_STUB ITVEVariation_get_Languages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_SDPLanguages_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVEAttrMap **ppVal);


void __RPC_STUB ITVEVariation_get_SDPLanguages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Bandwidth_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ LONG *lVal);


void __RPC_STUB ITVEVariation_get_Bandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_BandwidthInfo_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ BSTR *newVal);


void __RPC_STUB ITVEVariation_get_BandwidthInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Attributes_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVEAttrMap **ppVal);


void __RPC_STUB ITVEVariation_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariation_get_Rest_Proxy( 
    ITVEVariation * This,
    /* [retval][out] */ ITVEAttrMap **ppVal);


void __RPC_STUB ITVEVariation_get_Rest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Initialize_Proxy( 
    ITVEVariation * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEVariation_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEVariation_INTERFACE_DEFINED__ */


#ifndef __ITVEVariation_Helper_INTERFACE_DEFINED__
#define __ITVEVariation_Helper_INTERFACE_DEFINED__

/* interface ITVEVariation_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVEVariation_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500203-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEVariation_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            /* [in] */ ITVEEnhancement *pEnhancement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DefaultTo( 
            /* [in] */ ITVEVariation *pVariationBase) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTriggerIPAdapter( 
            /* [in] */ BSTR bstrBuff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFileIPAdapter( 
            /* [in] */ BSTR bstrBuff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubParseSDP( 
            const BSTR *pbstrSDP,
            BOOL *pfMissingMedia) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseCBTrigger( 
            BSTR bstrTrig) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FinalParseSDP( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateVariation( 
            ITVEVariation *pVarNew,
            long *plNVAR_grfChanged) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitAsXOver( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewXOverLink( 
            /* [in] */ BSTR bstrLine21Trigger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaTitle( 
            /* [in] */ BSTR bstrBuff) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsValid( 
            /* [in] */ VARIANT_BOOL fValid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *bstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEVariation_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEVariation_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEVariation_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEVariation_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVEVariation_Helper * This,
            /* [in] */ ITVEEnhancement *pEnhancement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DefaultTo )( 
            ITVEVariation_Helper * This,
            /* [in] */ ITVEVariation *pVariationBase);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTriggerIPAdapter )( 
            ITVEVariation_Helper * This,
            /* [in] */ BSTR bstrBuff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFileIPAdapter )( 
            ITVEVariation_Helper * This,
            /* [in] */ BSTR bstrBuff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubParseSDP )( 
            ITVEVariation_Helper * This,
            const BSTR *pbstrSDP,
            BOOL *pfMissingMedia);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ParseCBTrigger )( 
            ITVEVariation_Helper * This,
            BSTR bstrTrig);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FinalParseSDP )( 
            ITVEVariation_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateVariation )( 
            ITVEVariation_Helper * This,
            ITVEVariation *pVarNew,
            long *plNVAR_grfChanged);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitAsXOver )( 
            ITVEVariation_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewXOverLink )( 
            ITVEVariation_Helper * This,
            /* [in] */ BSTR bstrLine21Trigger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVEVariation_Helper * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MediaTitle )( 
            ITVEVariation_Helper * This,
            /* [in] */ BSTR bstrBuff);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsValid )( 
            ITVEVariation_Helper * This,
            /* [in] */ VARIANT_BOOL fValid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEVariation_Helper * This,
            /* [out] */ BSTR *bstrBuff);
        
        END_INTERFACE
    } ITVEVariation_HelperVtbl;

    interface ITVEVariation_Helper
    {
        CONST_VTBL struct ITVEVariation_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEVariation_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEVariation_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEVariation_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEVariation_Helper_ConnectParent(This,pEnhancement)	\
    (This)->lpVtbl -> ConnectParent(This,pEnhancement)

#define ITVEVariation_Helper_DefaultTo(This,pVariationBase)	\
    (This)->lpVtbl -> DefaultTo(This,pVariationBase)

#define ITVEVariation_Helper_SetTriggerIPAdapter(This,bstrBuff)	\
    (This)->lpVtbl -> SetTriggerIPAdapter(This,bstrBuff)

#define ITVEVariation_Helper_SetFileIPAdapter(This,bstrBuff)	\
    (This)->lpVtbl -> SetFileIPAdapter(This,bstrBuff)

#define ITVEVariation_Helper_SubParseSDP(This,pbstrSDP,pfMissingMedia)	\
    (This)->lpVtbl -> SubParseSDP(This,pbstrSDP,pfMissingMedia)

#define ITVEVariation_Helper_ParseCBTrigger(This,bstrTrig)	\
    (This)->lpVtbl -> ParseCBTrigger(This,bstrTrig)

#define ITVEVariation_Helper_FinalParseSDP(This)	\
    (This)->lpVtbl -> FinalParseSDP(This)

#define ITVEVariation_Helper_UpdateVariation(This,pVarNew,plNVAR_grfChanged)	\
    (This)->lpVtbl -> UpdateVariation(This,pVarNew,plNVAR_grfChanged)

#define ITVEVariation_Helper_InitAsXOver(This)	\
    (This)->lpVtbl -> InitAsXOver(This)

#define ITVEVariation_Helper_NewXOverLink(This,bstrLine21Trigger)	\
    (This)->lpVtbl -> NewXOverLink(This,bstrLine21Trigger)

#define ITVEVariation_Helper_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVEVariation_Helper_put_MediaTitle(This,bstrBuff)	\
    (This)->lpVtbl -> put_MediaTitle(This,bstrBuff)

#define ITVEVariation_Helper_put_IsValid(This,fValid)	\
    (This)->lpVtbl -> put_IsValid(This,fValid)

#define ITVEVariation_Helper_DumpToBSTR(This,bstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,bstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_ConnectParent_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ ITVEEnhancement *pEnhancement);


void __RPC_STUB ITVEVariation_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_DefaultTo_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ ITVEVariation *pVariationBase);


void __RPC_STUB ITVEVariation_Helper_DefaultTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_SetTriggerIPAdapter_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ BSTR bstrBuff);


void __RPC_STUB ITVEVariation_Helper_SetTriggerIPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_SetFileIPAdapter_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ BSTR bstrBuff);


void __RPC_STUB ITVEVariation_Helper_SetFileIPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_SubParseSDP_Proxy( 
    ITVEVariation_Helper * This,
    const BSTR *pbstrSDP,
    BOOL *pfMissingMedia);


void __RPC_STUB ITVEVariation_Helper_SubParseSDP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_ParseCBTrigger_Proxy( 
    ITVEVariation_Helper * This,
    BSTR bstrTrig);


void __RPC_STUB ITVEVariation_Helper_ParseCBTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_FinalParseSDP_Proxy( 
    ITVEVariation_Helper * This);


void __RPC_STUB ITVEVariation_Helper_FinalParseSDP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_UpdateVariation_Proxy( 
    ITVEVariation_Helper * This,
    ITVEVariation *pVarNew,
    long *plNVAR_grfChanged);


void __RPC_STUB ITVEVariation_Helper_UpdateVariation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_InitAsXOver_Proxy( 
    ITVEVariation_Helper * This);


void __RPC_STUB ITVEVariation_Helper_InitAsXOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_NewXOverLink_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ BSTR bstrLine21Trigger);


void __RPC_STUB ITVEVariation_Helper_NewXOverLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_RemoveYourself_Proxy( 
    ITVEVariation_Helper * This);


void __RPC_STUB ITVEVariation_Helper_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_put_MediaTitle_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ BSTR bstrBuff);


void __RPC_STUB ITVEVariation_Helper_put_MediaTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_put_IsValid_Proxy( 
    ITVEVariation_Helper * This,
    /* [in] */ VARIANT_BOOL fValid);


void __RPC_STUB ITVEVariation_Helper_put_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariation_Helper_DumpToBSTR_Proxy( 
    ITVEVariation_Helper * This,
    /* [out] */ BSTR *bstrBuff);


void __RPC_STUB ITVEVariation_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEVariation_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVEVariations_INTERFACE_DEFINED__
#define __ITVEVariations_INTERFACE_DEFINED__

/* interface ITVEVariations */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEVariations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500113-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEVariations : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEVariation **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITVEVariation *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ int iLoc,
            /* [in] */ ITVEVariation *pEnh) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEVariationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEVariations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEVariations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEVariations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEVariations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEVariations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEVariations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEVariations * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEVariations * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEVariations * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEVariations * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEVariation **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEVariations * This,
            /* [in] */ ITVEVariation *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEVariations * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEVariations * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ITVEVariations * This,
            /* [in] */ int iLoc,
            /* [in] */ ITVEVariation *pEnh);
        
        END_INTERFACE
    } ITVEVariationsVtbl;

    interface ITVEVariations
    {
        CONST_VTBL struct ITVEVariationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEVariations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEVariations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEVariations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEVariations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEVariations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEVariations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEVariations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEVariations_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEVariations_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEVariations_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVEVariations_Add(This,pEnh)	\
    (This)->lpVtbl -> Add(This,pEnh)

#define ITVEVariations_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEVariations_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVEVariations_Insert(This,iLoc,pEnh)	\
    (This)->lpVtbl -> Insert(This,iLoc,pEnh)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariations_get__NewEnum_Proxy( 
    ITVEVariations * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEVariations_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariations_get_Count_Proxy( 
    ITVEVariations * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEVariations_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEVariations_get_Item_Proxy( 
    ITVEVariations * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ ITVEVariation **pVal);


void __RPC_STUB ITVEVariations_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariations_Add_Proxy( 
    ITVEVariations * This,
    /* [in] */ ITVEVariation *pEnh);


void __RPC_STUB ITVEVariations_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariations_Remove_Proxy( 
    ITVEVariations * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEVariations_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariations_RemoveAll_Proxy( 
    ITVEVariations * This);


void __RPC_STUB ITVEVariations_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEVariations_Insert_Proxy( 
    ITVEVariations * This,
    /* [in] */ int iLoc,
    /* [in] */ ITVEVariation *pEnh);


void __RPC_STUB ITVEVariations_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEVariations_INTERFACE_DEFINED__ */


#ifndef __ITVEEnhancement_INTERFACE_DEFINED__
#define __ITVEEnhancement_INTERFACE_DEFINED__

/* interface ITVEEnhancement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEEnhancement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500104-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEEnhancement : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Service( 
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Variations( 
            /* [retval][out] */ ITVEVariations **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionUserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionId( 
            /* [retval][out] */ LONG *plVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionVersion( 
            /* [retval][out] */ LONG *plVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionIPAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailAddresses( 
            /* [retval][out] */ ITVEAttrMap **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PhoneNumbers( 
            /* [retval][out] */ ITVEAttrMap **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DescriptionURI( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsPrimary( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TveType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TveSize( 
            /* [retval][out] */ LONG *plVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TveLevel( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ ITVEAttrMap **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rest( 
            /* [retval][out] */ ITVEAttrMap **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SAPHeaderBits( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SAPAuthLength( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SAPMsgIDHash( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SAPSendingIP( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SAPAuthData( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseAnnouncement( 
            /* [in] */ BSTR bstrAdapter,
            /* [in] */ const BSTR *pbstVal,
            /* [out] */ long *plgrfParseError,
            /* [out] */ long *plLineError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEEnhancementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEEnhancement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEEnhancement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEEnhancement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEEnhancement * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEEnhancement * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEEnhancement * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEEnhancement * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVEEnhancement * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Service )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Variations )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEVariations **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsValid )( 
            ITVEEnhancement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolVersion )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SessionUserName )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SessionId )( 
            ITVEEnhancement * This,
            /* [retval][out] */ LONG *plVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SessionVersion )( 
            ITVEEnhancement * This,
            /* [retval][out] */ LONG *plVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SessionIPAddress )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SessionName )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailAddresses )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEAttrMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PhoneNumbers )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEAttrMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVEEnhancement * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DescriptionURI )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UUID )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            ITVEEnhancement * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            ITVEEnhancement * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPrimary )( 
            ITVEEnhancement * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TveType )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TveSize )( 
            ITVEEnhancement * This,
            /* [retval][out] */ LONG *plVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TveLevel )( 
            ITVEEnhancement * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attributes )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEAttrMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rest )( 
            ITVEEnhancement * This,
            /* [retval][out] */ ITVEAttrMap **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SAPHeaderBits )( 
            ITVEEnhancement * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SAPAuthLength )( 
            ITVEEnhancement * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SAPMsgIDHash )( 
            ITVEEnhancement * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SAPSendingIP )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SAPAuthData )( 
            ITVEEnhancement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ParseAnnouncement )( 
            ITVEEnhancement * This,
            /* [in] */ BSTR bstrAdapter,
            /* [in] */ const BSTR *pbstVal,
            /* [out] */ long *plgrfParseError,
            /* [out] */ long *plLineError);
        
        END_INTERFACE
    } ITVEEnhancementVtbl;

    interface ITVEEnhancement
    {
        CONST_VTBL struct ITVEEnhancementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEEnhancement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEEnhancement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEEnhancement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEEnhancement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEEnhancement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEEnhancement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEEnhancement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEEnhancement_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVEEnhancement_get_Service(This,pVal)	\
    (This)->lpVtbl -> get_Service(This,pVal)

#define ITVEEnhancement_get_Variations(This,pVal)	\
    (This)->lpVtbl -> get_Variations(This,pVal)

#define ITVEEnhancement_get_IsValid(This,pVal)	\
    (This)->lpVtbl -> get_IsValid(This,pVal)

#define ITVEEnhancement_get_ProtocolVersion(This,pVal)	\
    (This)->lpVtbl -> get_ProtocolVersion(This,pVal)

#define ITVEEnhancement_get_SessionUserName(This,pVal)	\
    (This)->lpVtbl -> get_SessionUserName(This,pVal)

#define ITVEEnhancement_get_SessionId(This,plVal)	\
    (This)->lpVtbl -> get_SessionId(This,plVal)

#define ITVEEnhancement_get_SessionVersion(This,plVal)	\
    (This)->lpVtbl -> get_SessionVersion(This,plVal)

#define ITVEEnhancement_get_SessionIPAddress(This,pVal)	\
    (This)->lpVtbl -> get_SessionIPAddress(This,pVal)

#define ITVEEnhancement_get_SessionName(This,pVal)	\
    (This)->lpVtbl -> get_SessionName(This,pVal)

#define ITVEEnhancement_get_EmailAddresses(This,pVal)	\
    (This)->lpVtbl -> get_EmailAddresses(This,pVal)

#define ITVEEnhancement_get_PhoneNumbers(This,pVal)	\
    (This)->lpVtbl -> get_PhoneNumbers(This,pVal)

#define ITVEEnhancement_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVEEnhancement_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVEEnhancement_get_DescriptionURI(This,pVal)	\
    (This)->lpVtbl -> get_DescriptionURI(This,pVal)

#define ITVEEnhancement_get_UUID(This,pVal)	\
    (This)->lpVtbl -> get_UUID(This,pVal)

#define ITVEEnhancement_get_StartTime(This,pVal)	\
    (This)->lpVtbl -> get_StartTime(This,pVal)

#define ITVEEnhancement_get_StopTime(This,pVal)	\
    (This)->lpVtbl -> get_StopTime(This,pVal)

#define ITVEEnhancement_get_IsPrimary(This,pVal)	\
    (This)->lpVtbl -> get_IsPrimary(This,pVal)

#define ITVEEnhancement_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITVEEnhancement_get_TveType(This,pVal)	\
    (This)->lpVtbl -> get_TveType(This,pVal)

#define ITVEEnhancement_get_TveSize(This,plVal)	\
    (This)->lpVtbl -> get_TveSize(This,plVal)

#define ITVEEnhancement_get_TveLevel(This,pVal)	\
    (This)->lpVtbl -> get_TveLevel(This,pVal)

#define ITVEEnhancement_get_Attributes(This,pVal)	\
    (This)->lpVtbl -> get_Attributes(This,pVal)

#define ITVEEnhancement_get_Rest(This,pVal)	\
    (This)->lpVtbl -> get_Rest(This,pVal)

#define ITVEEnhancement_get_SAPHeaderBits(This,pVal)	\
    (This)->lpVtbl -> get_SAPHeaderBits(This,pVal)

#define ITVEEnhancement_get_SAPAuthLength(This,pVal)	\
    (This)->lpVtbl -> get_SAPAuthLength(This,pVal)

#define ITVEEnhancement_get_SAPMsgIDHash(This,pVal)	\
    (This)->lpVtbl -> get_SAPMsgIDHash(This,pVal)

#define ITVEEnhancement_get_SAPSendingIP(This,pVal)	\
    (This)->lpVtbl -> get_SAPSendingIP(This,pVal)

#define ITVEEnhancement_get_SAPAuthData(This,pVal)	\
    (This)->lpVtbl -> get_SAPAuthData(This,pVal)

#define ITVEEnhancement_ParseAnnouncement(This,bstrAdapter,pbstVal,plgrfParseError,plLineError)	\
    (This)->lpVtbl -> ParseAnnouncement(This,bstrAdapter,pbstVal,plgrfParseError,plLineError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Parent_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITVEEnhancement_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Service_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVEEnhancement_get_Service_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Variations_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEVariations **pVal);


void __RPC_STUB ITVEEnhancement_get_Variations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_IsValid_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVEEnhancement_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_ProtocolVersion_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SessionUserName_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_SessionUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SessionId_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ LONG *plVal);


void __RPC_STUB ITVEEnhancement_get_SessionId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SessionVersion_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ LONG *plVal);


void __RPC_STUB ITVEEnhancement_get_SessionVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SessionIPAddress_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_SessionIPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SessionName_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_SessionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_EmailAddresses_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEAttrMap **pVal);


void __RPC_STUB ITVEEnhancement_get_EmailAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_PhoneNumbers_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEAttrMap **pVal);


void __RPC_STUB ITVEEnhancement_get_PhoneNumbers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Description_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_put_Description_Proxy( 
    ITVEEnhancement * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEEnhancement_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_DescriptionURI_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_DescriptionURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_UUID_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_UUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_StartTime_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITVEEnhancement_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_StopTime_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITVEEnhancement_get_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_IsPrimary_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVEEnhancement_get_IsPrimary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Type_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_TveType_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_TveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_TveSize_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ LONG *plVal);


void __RPC_STUB ITVEEnhancement_get_TveSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_TveLevel_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITVEEnhancement_get_TveLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Attributes_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEAttrMap **pVal);


void __RPC_STUB ITVEEnhancement_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_Rest_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ ITVEAttrMap **pVal);


void __RPC_STUB ITVEEnhancement_get_Rest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SAPHeaderBits_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB ITVEEnhancement_get_SAPHeaderBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SAPAuthLength_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB ITVEEnhancement_get_SAPAuthLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SAPMsgIDHash_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITVEEnhancement_get_SAPMsgIDHash_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SAPSendingIP_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_SAPSendingIP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_get_SAPAuthData_Proxy( 
    ITVEEnhancement * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEEnhancement_get_SAPAuthData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_ParseAnnouncement_Proxy( 
    ITVEEnhancement * This,
    /* [in] */ BSTR bstrAdapter,
    /* [in] */ const BSTR *pbstVal,
    /* [out] */ long *plgrfParseError,
    /* [out] */ long *plLineError);


void __RPC_STUB ITVEEnhancement_ParseAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEEnhancement_INTERFACE_DEFINED__ */


#ifndef __ITVEEnhancement_Helper_INTERFACE_DEFINED__
#define __ITVEEnhancement_Helper_INTERFACE_DEFINED__

/* interface ITVEEnhancement_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVEEnhancement_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500204-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEEnhancement_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            ITVEService *pService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Deactivate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateEnhancement( 
            /* [in] */ ITVEEnhancement *pEnhNew,
            /* [out] */ long *plNENH_grfChanged) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitAsXOver( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewXOverLink( 
            /* [in] */ BSTR bstrLine21Trigger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEEnhancement_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEEnhancement_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEEnhancement_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEEnhancement_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVEEnhancement_Helper * This,
            ITVEService *pService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ITVEEnhancement_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            ITVEEnhancement_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateEnhancement )( 
            ITVEEnhancement_Helper * This,
            /* [in] */ ITVEEnhancement *pEnhNew,
            /* [out] */ long *plNENH_grfChanged);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitAsXOver )( 
            ITVEEnhancement_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewXOverLink )( 
            ITVEEnhancement_Helper * This,
            /* [in] */ BSTR bstrLine21Trigger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVEEnhancement_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEEnhancement_Helper * This,
            /* [out] */ BSTR *pbstrBuff);
        
        END_INTERFACE
    } ITVEEnhancement_HelperVtbl;

    interface ITVEEnhancement_Helper
    {
        CONST_VTBL struct ITVEEnhancement_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEEnhancement_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEEnhancement_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEEnhancement_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEEnhancement_Helper_ConnectParent(This,pService)	\
    (This)->lpVtbl -> ConnectParent(This,pService)

#define ITVEEnhancement_Helper_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define ITVEEnhancement_Helper_Deactivate(This)	\
    (This)->lpVtbl -> Deactivate(This)

#define ITVEEnhancement_Helper_UpdateEnhancement(This,pEnhNew,plNENH_grfChanged)	\
    (This)->lpVtbl -> UpdateEnhancement(This,pEnhNew,plNENH_grfChanged)

#define ITVEEnhancement_Helper_InitAsXOver(This)	\
    (This)->lpVtbl -> InitAsXOver(This)

#define ITVEEnhancement_Helper_NewXOverLink(This,bstrLine21Trigger)	\
    (This)->lpVtbl -> NewXOverLink(This,bstrLine21Trigger)

#define ITVEEnhancement_Helper_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVEEnhancement_Helper_DumpToBSTR(This,pbstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,pbstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_ConnectParent_Proxy( 
    ITVEEnhancement_Helper * This,
    ITVEService *pService);


void __RPC_STUB ITVEEnhancement_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_Activate_Proxy( 
    ITVEEnhancement_Helper * This);


void __RPC_STUB ITVEEnhancement_Helper_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_Deactivate_Proxy( 
    ITVEEnhancement_Helper * This);


void __RPC_STUB ITVEEnhancement_Helper_Deactivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_UpdateEnhancement_Proxy( 
    ITVEEnhancement_Helper * This,
    /* [in] */ ITVEEnhancement *pEnhNew,
    /* [out] */ long *plNENH_grfChanged);


void __RPC_STUB ITVEEnhancement_Helper_UpdateEnhancement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_InitAsXOver_Proxy( 
    ITVEEnhancement_Helper * This);


void __RPC_STUB ITVEEnhancement_Helper_InitAsXOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_NewXOverLink_Proxy( 
    ITVEEnhancement_Helper * This,
    /* [in] */ BSTR bstrLine21Trigger);


void __RPC_STUB ITVEEnhancement_Helper_NewXOverLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_RemoveYourself_Proxy( 
    ITVEEnhancement_Helper * This);


void __RPC_STUB ITVEEnhancement_Helper_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancement_Helper_DumpToBSTR_Proxy( 
    ITVEEnhancement_Helper * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVEEnhancement_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEEnhancement_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVEEnhancements_INTERFACE_DEFINED__
#define __ITVEEnhancements_INTERFACE_DEFINED__

/* interface ITVEEnhancements */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEEnhancements;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500114-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEEnhancements : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEEnhancement **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ int iLoc,
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEEnhancementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEEnhancements * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEEnhancements * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEEnhancements * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEEnhancements * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEEnhancements * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEEnhancements * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEEnhancements * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEEnhancements * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEEnhancements * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEEnhancements * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEEnhancement **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEEnhancements * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEEnhancements * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEEnhancements * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ITVEEnhancements * This,
            /* [in] */ int iLoc,
            /* [in] */ ITVEEnhancement *pEnh);
        
        END_INTERFACE
    } ITVEEnhancementsVtbl;

    interface ITVEEnhancements
    {
        CONST_VTBL struct ITVEEnhancementsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEEnhancements_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEEnhancements_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEEnhancements_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEEnhancements_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEEnhancements_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEEnhancements_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEEnhancements_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEEnhancements_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEEnhancements_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEEnhancements_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVEEnhancements_Add(This,pEnh)	\
    (This)->lpVtbl -> Add(This,pEnh)

#define ITVEEnhancements_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEEnhancements_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVEEnhancements_Insert(This,iLoc,pEnh)	\
    (This)->lpVtbl -> Insert(This,iLoc,pEnh)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_get__NewEnum_Proxy( 
    ITVEEnhancements * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEEnhancements_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_get_Count_Proxy( 
    ITVEEnhancements * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEEnhancements_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_get_Item_Proxy( 
    ITVEEnhancements * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ ITVEEnhancement **pVal);


void __RPC_STUB ITVEEnhancements_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_Add_Proxy( 
    ITVEEnhancements * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVEEnhancements_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_Remove_Proxy( 
    ITVEEnhancements * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEEnhancements_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_RemoveAll_Proxy( 
    ITVEEnhancements * This);


void __RPC_STUB ITVEEnhancements_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEEnhancements_Insert_Proxy( 
    ITVEEnhancements * This,
    /* [in] */ int iLoc,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVEEnhancements_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEEnhancements_INTERFACE_DEFINED__ */


#ifndef __ITVEService_INTERFACE_DEFINED__
#define __ITVEService_INTERFACE_DEFINED__

/* interface ITVEService */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500105-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEService : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enhancements( 
            /* [retval][out] */ ITVEEnhancements **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Deactivate( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_XOverLinks( 
            /* [retval][out] */ ITVETracks **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_XOverEnhancement( 
            /* [retval][out] */ ITVEEnhancement **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewXOverLink( 
            /* [in] */ BSTR bstrLine21Trigger) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpireOffset( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExpireOffset( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpireQueue( 
            /* [retval][out] */ ITVEAttrTimeQ **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExpireForDate( 
            /* [in] */ DATE dateExpireTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsActive( 
            /* [retval][out] */ VARIANT_BOOL *fIsActive) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Property( 
            /* [in] */ BSTR bstrPropName,
            BSTR bstrPropVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVEService * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enhancements )( 
            ITVEService * This,
            /* [retval][out] */ ITVEEnhancements **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVEService * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVEService * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ITVEService * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            ITVEService * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XOverLinks )( 
            ITVEService * This,
            /* [retval][out] */ ITVETracks **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XOverEnhancement )( 
            ITVEService * This,
            /* [retval][out] */ ITVEEnhancement **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewXOverLink )( 
            ITVEService * This,
            /* [in] */ BSTR bstrLine21Trigger);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireOffset )( 
            ITVEService * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExpireOffset )( 
            ITVEService * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireQueue )( 
            ITVEService * This,
            /* [retval][out] */ ITVEAttrTimeQ **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExpireForDate )( 
            ITVEService * This,
            /* [in] */ DATE dateExpireTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsActive )( 
            ITVEService * This,
            /* [retval][out] */ VARIANT_BOOL *fIsActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Property )( 
            ITVEService * This,
            /* [in] */ BSTR bstrPropName,
            BSTR bstrPropVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            ITVEService * This,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropVal);
        
        END_INTERFACE
    } ITVEServiceVtbl;

    interface ITVEService
    {
        CONST_VTBL struct ITVEServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEService_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVEService_get_Enhancements(This,pVal)	\
    (This)->lpVtbl -> get_Enhancements(This,pVal)

#define ITVEService_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVEService_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVEService_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define ITVEService_Deactivate(This)	\
    (This)->lpVtbl -> Deactivate(This)

#define ITVEService_get_XOverLinks(This,pVal)	\
    (This)->lpVtbl -> get_XOverLinks(This,pVal)

#define ITVEService_get_XOverEnhancement(This,pVal)	\
    (This)->lpVtbl -> get_XOverEnhancement(This,pVal)

#define ITVEService_NewXOverLink(This,bstrLine21Trigger)	\
    (This)->lpVtbl -> NewXOverLink(This,bstrLine21Trigger)

#define ITVEService_get_ExpireOffset(This,pVal)	\
    (This)->lpVtbl -> get_ExpireOffset(This,pVal)

#define ITVEService_put_ExpireOffset(This,newVal)	\
    (This)->lpVtbl -> put_ExpireOffset(This,newVal)

#define ITVEService_get_ExpireQueue(This,pVal)	\
    (This)->lpVtbl -> get_ExpireQueue(This,pVal)

#define ITVEService_ExpireForDate(This,dateExpireTime)	\
    (This)->lpVtbl -> ExpireForDate(This,dateExpireTime)

#define ITVEService_get_IsActive(This,fIsActive)	\
    (This)->lpVtbl -> get_IsActive(This,fIsActive)

#define ITVEService_put_Property(This,bstrPropName,bstrPropVal)	\
    (This)->lpVtbl -> put_Property(This,bstrPropName,bstrPropVal)

#define ITVEService_get_Property(This,bstrPropName,pbstrPropVal)	\
    (This)->lpVtbl -> get_Property(This,bstrPropName,pbstrPropVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_Parent_Proxy( 
    ITVEService * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITVEService_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_Enhancements_Proxy( 
    ITVEService * This,
    /* [retval][out] */ ITVEEnhancements **pVal);


void __RPC_STUB ITVEService_get_Enhancements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_Description_Proxy( 
    ITVEService * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEService_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEService_put_Description_Proxy( 
    ITVEService * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEService_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Activate_Proxy( 
    ITVEService * This);


void __RPC_STUB ITVEService_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Deactivate_Proxy( 
    ITVEService * This);


void __RPC_STUB ITVEService_Deactivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_XOverLinks_Proxy( 
    ITVEService * This,
    /* [retval][out] */ ITVETracks **pVal);


void __RPC_STUB ITVEService_get_XOverLinks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_XOverEnhancement_Proxy( 
    ITVEService * This,
    /* [retval][out] */ ITVEEnhancement **pVal);


void __RPC_STUB ITVEService_get_XOverEnhancement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_NewXOverLink_Proxy( 
    ITVEService * This,
    /* [in] */ BSTR bstrLine21Trigger);


void __RPC_STUB ITVEService_NewXOverLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_ExpireOffset_Proxy( 
    ITVEService * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITVEService_get_ExpireOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEService_put_ExpireOffset_Proxy( 
    ITVEService * This,
    /* [in] */ DATE newVal);


void __RPC_STUB ITVEService_put_ExpireOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_ExpireQueue_Proxy( 
    ITVEService * This,
    /* [retval][out] */ ITVEAttrTimeQ **pVal);


void __RPC_STUB ITVEService_get_ExpireQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_ExpireForDate_Proxy( 
    ITVEService * This,
    /* [in] */ DATE dateExpireTime);


void __RPC_STUB ITVEService_ExpireForDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_IsActive_Proxy( 
    ITVEService * This,
    /* [retval][out] */ VARIANT_BOOL *fIsActive);


void __RPC_STUB ITVEService_get_IsActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEService_put_Property_Proxy( 
    ITVEService * This,
    /* [in] */ BSTR bstrPropName,
    BSTR bstrPropVal);


void __RPC_STUB ITVEService_put_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_get_Property_Proxy( 
    ITVEService * This,
    /* [in] */ BSTR bstrPropName,
    /* [retval][out] */ BSTR *pbstrPropVal);


void __RPC_STUB ITVEService_get_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEService_INTERFACE_DEFINED__ */


#ifndef __ITVEService_Helper_INTERFACE_DEFINED__
#define __ITVEService_Helper_INTERFACE_DEFINED__

/* interface ITVEService_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVEService_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500205-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEService_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            /* [in] */ ITVESupervisor *pSupervisor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseCBAnnouncement( 
            /* [in] */ BSTR bstrFileTrigAdapter,
            /* [in] */ BSTR *pbstrBuff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAnncIPValues( 
            /* [in] */ BSTR bstrAnncIPAdapter,
            /* [in] */ BSTR bstrAnncIPAddress,
            /* [in] */ LONG lAnncPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAnncIPValues( 
            /* [in] */ BSTR *pbstrAnncIPAdapter,
            /* [in] */ BSTR *pbstrAnncIPAddress,
            /* [in] */ LONG *plAnncPort) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitXOverEnhancement( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddToExpireQueue( 
            /* [in] */ DATE dateExpires,
            /* [in] */ IUnknown *punkItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeInExpireQueue( 
            /* [in] */ DATE dateExpires,
            /* [in] */ IUnknown *punkItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveFromExpireQueue( 
            /* [in] */ IUnknown *punkItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveEnhFilesFromExpireQueue( 
            /* [in] */ ITVEEnhancement *pEnhancement) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpireQueueChangeCount( 
            /* [retval][out] */ long *pChangeCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEService_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEService_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEService_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEService_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVEService_Helper * This,
            /* [in] */ ITVESupervisor *pSupervisor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ParseCBAnnouncement )( 
            ITVEService_Helper * This,
            /* [in] */ BSTR bstrFileTrigAdapter,
            /* [in] */ BSTR *pbstrBuff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAnncIPValues )( 
            ITVEService_Helper * This,
            /* [in] */ BSTR bstrAnncIPAdapter,
            /* [in] */ BSTR bstrAnncIPAddress,
            /* [in] */ LONG lAnncPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAnncIPValues )( 
            ITVEService_Helper * This,
            /* [in] */ BSTR *pbstrAnncIPAdapter,
            /* [in] */ BSTR *pbstrAnncIPAddress,
            /* [in] */ LONG *plAnncPort);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitXOverEnhancement )( 
            ITVEService_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddToExpireQueue )( 
            ITVEService_Helper * This,
            /* [in] */ DATE dateExpires,
            /* [in] */ IUnknown *punkItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeInExpireQueue )( 
            ITVEService_Helper * This,
            /* [in] */ DATE dateExpires,
            /* [in] */ IUnknown *punkItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveFromExpireQueue )( 
            ITVEService_Helper * This,
            /* [in] */ IUnknown *punkItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveEnhFilesFromExpireQueue )( 
            ITVEService_Helper * This,
            /* [in] */ ITVEEnhancement *pEnhancement);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireQueueChangeCount )( 
            ITVEService_Helper * This,
            /* [retval][out] */ long *pChangeCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVEService_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEService_Helper * This,
            /* [out] */ BSTR *pbstrBuff);
        
        END_INTERFACE
    } ITVEService_HelperVtbl;

    interface ITVEService_Helper
    {
        CONST_VTBL struct ITVEService_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEService_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEService_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEService_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEService_Helper_ConnectParent(This,pSupervisor)	\
    (This)->lpVtbl -> ConnectParent(This,pSupervisor)

#define ITVEService_Helper_ParseCBAnnouncement(This,bstrFileTrigAdapter,pbstrBuff)	\
    (This)->lpVtbl -> ParseCBAnnouncement(This,bstrFileTrigAdapter,pbstrBuff)

#define ITVEService_Helper_SetAnncIPValues(This,bstrAnncIPAdapter,bstrAnncIPAddress,lAnncPort)	\
    (This)->lpVtbl -> SetAnncIPValues(This,bstrAnncIPAdapter,bstrAnncIPAddress,lAnncPort)

#define ITVEService_Helper_GetAnncIPValues(This,pbstrAnncIPAdapter,pbstrAnncIPAddress,plAnncPort)	\
    (This)->lpVtbl -> GetAnncIPValues(This,pbstrAnncIPAdapter,pbstrAnncIPAddress,plAnncPort)

#define ITVEService_Helper_InitXOverEnhancement(This)	\
    (This)->lpVtbl -> InitXOverEnhancement(This)

#define ITVEService_Helper_AddToExpireQueue(This,dateExpires,punkItem)	\
    (This)->lpVtbl -> AddToExpireQueue(This,dateExpires,punkItem)

#define ITVEService_Helper_ChangeInExpireQueue(This,dateExpires,punkItem)	\
    (This)->lpVtbl -> ChangeInExpireQueue(This,dateExpires,punkItem)

#define ITVEService_Helper_RemoveFromExpireQueue(This,punkItem)	\
    (This)->lpVtbl -> RemoveFromExpireQueue(This,punkItem)

#define ITVEService_Helper_RemoveEnhFilesFromExpireQueue(This,pEnhancement)	\
    (This)->lpVtbl -> RemoveEnhFilesFromExpireQueue(This,pEnhancement)

#define ITVEService_Helper_get_ExpireQueueChangeCount(This,pChangeCount)	\
    (This)->lpVtbl -> get_ExpireQueueChangeCount(This,pChangeCount)

#define ITVEService_Helper_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVEService_Helper_DumpToBSTR(This,pbstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,pbstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_ConnectParent_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ ITVESupervisor *pSupervisor);


void __RPC_STUB ITVEService_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_ParseCBAnnouncement_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ BSTR bstrFileTrigAdapter,
    /* [in] */ BSTR *pbstrBuff);


void __RPC_STUB ITVEService_Helper_ParseCBAnnouncement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_SetAnncIPValues_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ BSTR bstrAnncIPAdapter,
    /* [in] */ BSTR bstrAnncIPAddress,
    /* [in] */ LONG lAnncPort);


void __RPC_STUB ITVEService_Helper_SetAnncIPValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_GetAnncIPValues_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ BSTR *pbstrAnncIPAdapter,
    /* [in] */ BSTR *pbstrAnncIPAddress,
    /* [in] */ LONG *plAnncPort);


void __RPC_STUB ITVEService_Helper_GetAnncIPValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_InitXOverEnhancement_Proxy( 
    ITVEService_Helper * This);


void __RPC_STUB ITVEService_Helper_InitXOverEnhancement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_AddToExpireQueue_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ DATE dateExpires,
    /* [in] */ IUnknown *punkItem);


void __RPC_STUB ITVEService_Helper_AddToExpireQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_ChangeInExpireQueue_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ DATE dateExpires,
    /* [in] */ IUnknown *punkItem);


void __RPC_STUB ITVEService_Helper_ChangeInExpireQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_RemoveFromExpireQueue_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ IUnknown *punkItem);


void __RPC_STUB ITVEService_Helper_RemoveFromExpireQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_RemoveEnhFilesFromExpireQueue_Proxy( 
    ITVEService_Helper * This,
    /* [in] */ ITVEEnhancement *pEnhancement);


void __RPC_STUB ITVEService_Helper_RemoveEnhFilesFromExpireQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_get_ExpireQueueChangeCount_Proxy( 
    ITVEService_Helper * This,
    /* [retval][out] */ long *pChangeCount);


void __RPC_STUB ITVEService_Helper_get_ExpireQueueChangeCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_RemoveYourself_Proxy( 
    ITVEService_Helper * This);


void __RPC_STUB ITVEService_Helper_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEService_Helper_DumpToBSTR_Proxy( 
    ITVEService_Helper * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVEService_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEService_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVEFeature_INTERFACE_DEFINED__
#define __ITVEFeature_INTERFACE_DEFINED__

/* interface ITVEFeature */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEFeature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500305-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEFeature : public ITVEService
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TuneTo( 
            /* [in] */ BSTR bstrStation,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReTune( 
            /* [in] */ ITVEService *pService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BindToSupervisor( 
            /* [in] */ ITVESupervisor *pTVESupervisor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETune( 
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementNew( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementUpdated( 
            /* [in] */ ITVEEnhancement *pEnh,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementStarting( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementExpired( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerNew( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerUpdated( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerExpired( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEPackage( 
            /* [in] */ NPKG_Mode engPkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEFile( 
            /* [in] */ NFLE_Mode engFileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUrlName,
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEAuxInfo( 
            /* [in] */ NWHAT_Mode engAuxInfoMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lChangedFlags,
            /* [in] */ long lErrorLine) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEFeatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEFeature * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEFeature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEFeature * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEFeature * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEFeature * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEFeature * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEFeature * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITVEFeature * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enhancements )( 
            ITVEFeature * This,
            /* [retval][out] */ ITVEEnhancements **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVEFeature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVEFeature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ITVEFeature * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            ITVEFeature * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XOverLinks )( 
            ITVEFeature * This,
            /* [retval][out] */ ITVETracks **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XOverEnhancement )( 
            ITVEFeature * This,
            /* [retval][out] */ ITVEEnhancement **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewXOverLink )( 
            ITVEFeature * This,
            /* [in] */ BSTR bstrLine21Trigger);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireOffset )( 
            ITVEFeature * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExpireOffset )( 
            ITVEFeature * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireQueue )( 
            ITVEFeature * This,
            /* [retval][out] */ ITVEAttrTimeQ **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExpireForDate )( 
            ITVEFeature * This,
            /* [in] */ DATE dateExpireTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsActive )( 
            ITVEFeature * This,
            /* [retval][out] */ VARIANT_BOOL *fIsActive);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Property )( 
            ITVEFeature * This,
            /* [in] */ BSTR bstrPropName,
            BSTR bstrPropVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            ITVEFeature * This,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TuneTo )( 
            ITVEFeature * This,
            /* [in] */ BSTR bstrStation,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReTune )( 
            ITVEFeature * This,
            /* [in] */ ITVEService *pService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BindToSupervisor )( 
            ITVEFeature * This,
            /* [in] */ ITVESupervisor *pTVESupervisor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETune )( 
            ITVEFeature * This,
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementNew )( 
            ITVEFeature * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementUpdated )( 
            ITVEFeature * This,
            /* [in] */ ITVEEnhancement *pEnh,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementStarting )( 
            ITVEFeature * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementExpired )( 
            ITVEFeature * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerNew )( 
            ITVEFeature * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerUpdated )( 
            ITVEFeature * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerExpired )( 
            ITVEFeature * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEPackage )( 
            ITVEFeature * This,
            /* [in] */ NPKG_Mode engPkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEFile )( 
            ITVEFeature * This,
            /* [in] */ NFLE_Mode engFileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUrlName,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEAuxInfo )( 
            ITVEFeature * This,
            /* [in] */ NWHAT_Mode engAuxInfoMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lChangedFlags,
            /* [in] */ long lErrorLine);
        
        END_INTERFACE
    } ITVEFeatureVtbl;

    interface ITVEFeature
    {
        CONST_VTBL struct ITVEFeatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEFeature_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEFeature_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEFeature_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEFeature_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEFeature_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEFeature_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEFeature_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEFeature_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITVEFeature_get_Enhancements(This,pVal)	\
    (This)->lpVtbl -> get_Enhancements(This,pVal)

#define ITVEFeature_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVEFeature_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVEFeature_Activate(This)	\
    (This)->lpVtbl -> Activate(This)

#define ITVEFeature_Deactivate(This)	\
    (This)->lpVtbl -> Deactivate(This)

#define ITVEFeature_get_XOverLinks(This,pVal)	\
    (This)->lpVtbl -> get_XOverLinks(This,pVal)

#define ITVEFeature_get_XOverEnhancement(This,pVal)	\
    (This)->lpVtbl -> get_XOverEnhancement(This,pVal)

#define ITVEFeature_NewXOverLink(This,bstrLine21Trigger)	\
    (This)->lpVtbl -> NewXOverLink(This,bstrLine21Trigger)

#define ITVEFeature_get_ExpireOffset(This,pVal)	\
    (This)->lpVtbl -> get_ExpireOffset(This,pVal)

#define ITVEFeature_put_ExpireOffset(This,newVal)	\
    (This)->lpVtbl -> put_ExpireOffset(This,newVal)

#define ITVEFeature_get_ExpireQueue(This,pVal)	\
    (This)->lpVtbl -> get_ExpireQueue(This,pVal)

#define ITVEFeature_ExpireForDate(This,dateExpireTime)	\
    (This)->lpVtbl -> ExpireForDate(This,dateExpireTime)

#define ITVEFeature_get_IsActive(This,fIsActive)	\
    (This)->lpVtbl -> get_IsActive(This,fIsActive)

#define ITVEFeature_put_Property(This,bstrPropName,bstrPropVal)	\
    (This)->lpVtbl -> put_Property(This,bstrPropName,bstrPropVal)

#define ITVEFeature_get_Property(This,bstrPropName,pbstrPropVal)	\
    (This)->lpVtbl -> get_Property(This,bstrPropName,pbstrPropVal)


#define ITVEFeature_TuneTo(This,bstrStation,bstrIPAdapter)	\
    (This)->lpVtbl -> TuneTo(This,bstrStation,bstrIPAdapter)

#define ITVEFeature_ReTune(This,pService)	\
    (This)->lpVtbl -> ReTune(This,pService)

#define ITVEFeature_BindToSupervisor(This,pTVESupervisor)	\
    (This)->lpVtbl -> BindToSupervisor(This,pTVESupervisor)

#define ITVEFeature_NotifyTVETune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)	\
    (This)->lpVtbl -> NotifyTVETune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)

#define ITVEFeature_NotifyTVEEnhancementNew(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementNew(This,pEnh)

#define ITVEFeature_NotifyTVEEnhancementUpdated(This,pEnh,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTVEEnhancementUpdated(This,pEnh,lChangedFlags)

#define ITVEFeature_NotifyTVEEnhancementStarting(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementStarting(This,pEnh)

#define ITVEFeature_NotifyTVEEnhancementExpired(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementExpired(This,pEnh)

#define ITVEFeature_NotifyTVETriggerNew(This,pTrigger,fActive)	\
    (This)->lpVtbl -> NotifyTVETriggerNew(This,pTrigger,fActive)

#define ITVEFeature_NotifyTVETriggerUpdated(This,pTrigger,fActive,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTVETriggerUpdated(This,pTrigger,fActive,lChangedFlags)

#define ITVEFeature_NotifyTVETriggerExpired(This,pTrigger,fActive)	\
    (This)->lpVtbl -> NotifyTVETriggerExpired(This,pTrigger,fActive)

#define ITVEFeature_NotifyTVEPackage(This,engPkgMode,pVariation,bstrUUID,cBytesTotal,cBytesReceived)	\
    (This)->lpVtbl -> NotifyTVEPackage(This,engPkgMode,pVariation,bstrUUID,cBytesTotal,cBytesReceived)

#define ITVEFeature_NotifyTVEFile(This,engFileMode,pVariation,bstrUrlName,bstrFileName)	\
    (This)->lpVtbl -> NotifyTVEFile(This,engFileMode,pVariation,bstrUrlName,bstrFileName)

#define ITVEFeature_NotifyTVEAuxInfo(This,engAuxInfoMode,bstrAuxInfoString,lChangedFlags,lErrorLine)	\
    (This)->lpVtbl -> NotifyTVEAuxInfo(This,engAuxInfoMode,bstrAuxInfoString,lChangedFlags,lErrorLine)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_TuneTo_Proxy( 
    ITVEFeature * This,
    /* [in] */ BSTR bstrStation,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVEFeature_TuneTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_ReTune_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVEService *pService);


void __RPC_STUB ITVEFeature_ReTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_BindToSupervisor_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVESupervisor *pTVESupervisor);


void __RPC_STUB ITVEFeature_BindToSupervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVETune_Proxy( 
    ITVEFeature * This,
    /* [in] */ NTUN_Mode tuneMode,
    /* [in] */ ITVEService *pService,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVEFeature_NotifyTVETune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEEnhancementNew_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVEFeature_NotifyTVEEnhancementNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEEnhancementUpdated_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVEEnhancement *pEnh,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVEFeature_NotifyTVEEnhancementUpdated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEEnhancementStarting_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVEFeature_NotifyTVEEnhancementStarting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEEnhancementExpired_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVEFeature_NotifyTVEEnhancementExpired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVETriggerNew_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive);


void __RPC_STUB ITVEFeature_NotifyTVETriggerNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVETriggerUpdated_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVEFeature_NotifyTVETriggerUpdated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVETriggerExpired_Proxy( 
    ITVEFeature * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive);


void __RPC_STUB ITVEFeature_NotifyTVETriggerExpired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEPackage_Proxy( 
    ITVEFeature * This,
    /* [in] */ NPKG_Mode engPkgMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrUUID,
    /* [in] */ long cBytesTotal,
    /* [in] */ long cBytesReceived);


void __RPC_STUB ITVEFeature_NotifyTVEPackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEFile_Proxy( 
    ITVEFeature * This,
    /* [in] */ NFLE_Mode engFileMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrUrlName,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB ITVEFeature_NotifyTVEFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFeature_NotifyTVEAuxInfo_Proxy( 
    ITVEFeature * This,
    /* [in] */ NWHAT_Mode engAuxInfoMode,
    /* [in] */ BSTR bstrAuxInfoString,
    /* [in] */ long lChangedFlags,
    /* [in] */ long lErrorLine);


void __RPC_STUB ITVEFeature_NotifyTVEAuxInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEFeature_INTERFACE_DEFINED__ */


#ifndef __ITVEServices_INTERFACE_DEFINED__
#define __ITVEServices_INTERFACE_DEFINED__

/* interface ITVEServices */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEServices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500115-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEServices : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITVEService *pService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ int iLoc,
            /* [in] */ ITVEService *pService) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEServices * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEServices * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEServices * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEServices * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEServices * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEServices * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEServices * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEServices * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEServices * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEServices * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEServices * This,
            /* [in] */ ITVEService *pService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEServices * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEServices * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ITVEServices * This,
            /* [in] */ int iLoc,
            /* [in] */ ITVEService *pService);
        
        END_INTERFACE
    } ITVEServicesVtbl;

    interface ITVEServices
    {
        CONST_VTBL struct ITVEServicesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEServices_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEServices_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEServices_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEServices_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEServices_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEServices_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEServices_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVEServices_Add(This,pService)	\
    (This)->lpVtbl -> Add(This,pService)

#define ITVEServices_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEServices_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVEServices_Insert(This,iLoc,pService)	\
    (This)->lpVtbl -> Insert(This,iLoc,pService)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEServices_get__NewEnum_Proxy( 
    ITVEServices * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEServices_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEServices_get_Count_Proxy( 
    ITVEServices * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEServices_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEServices_get_Item_Proxy( 
    ITVEServices * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVEServices_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEServices_Add_Proxy( 
    ITVEServices * This,
    /* [in] */ ITVEService *pService);


void __RPC_STUB ITVEServices_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEServices_Remove_Proxy( 
    ITVEServices * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEServices_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEServices_RemoveAll_Proxy( 
    ITVEServices * This);


void __RPC_STUB ITVEServices_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEServices_Insert_Proxy( 
    ITVEServices * This,
    /* [in] */ int iLoc,
    /* [in] */ ITVEService *pService);


void __RPC_STUB ITVEServices_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEServices_INTERFACE_DEFINED__ */


#ifndef __ITVESupervisor_INTERFACE_DEFINED__
#define __ITVESupervisor_INTERFACE_DEFINED__

/* interface ITVESupervisor */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVESupervisor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500106-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVESupervisor : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Services( 
            /* [retval][out] */ ITVEServices **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TuneTo( 
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReTune( 
            /* [in] */ ITVEService *pService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewXOverLink( 
            /* [in] */ BSTR bstrLine21Trigger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExpireForDate( 
            /* [in] */ DATE dateExpireTime) = 0;
        
        virtual /* [helpstring][restricted][id] */ HRESULT STDMETHODCALLTYPE InitStats( void) = 0;
        
        virtual /* [helpstring][restricted][id] */ HRESULT STDMETHODCALLTYPE GetStats( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVESupervisorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVESupervisor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVESupervisor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVESupervisor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVESupervisor * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVESupervisor * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVESupervisor * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVESupervisor * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Services )( 
            ITVESupervisor * This,
            /* [retval][out] */ ITVEServices **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVESupervisor * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITVESupervisor * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TuneTo )( 
            ITVESupervisor * This,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReTune )( 
            ITVESupervisor * This,
            /* [in] */ ITVEService *pService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewXOverLink )( 
            ITVESupervisor * This,
            /* [in] */ BSTR bstrLine21Trigger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExpireForDate )( 
            ITVESupervisor * This,
            /* [in] */ DATE dateExpireTime);
        
        /* [helpstring][restricted][id] */ HRESULT ( STDMETHODCALLTYPE *InitStats )( 
            ITVESupervisor * This);
        
        /* [helpstring][restricted][id] */ HRESULT ( STDMETHODCALLTYPE *GetStats )( 
            ITVESupervisor * This,
            /* [out] */ BSTR *pbstrBuff);
        
        END_INTERFACE
    } ITVESupervisorVtbl;

    interface ITVESupervisor
    {
        CONST_VTBL struct ITVESupervisorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVESupervisor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVESupervisor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVESupervisor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVESupervisor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVESupervisor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVESupervisor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVESupervisor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVESupervisor_get_Services(This,pVal)	\
    (This)->lpVtbl -> get_Services(This,pVal)

#define ITVESupervisor_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITVESupervisor_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITVESupervisor_TuneTo(This,bstrDescription,bstrIPAdapter)	\
    (This)->lpVtbl -> TuneTo(This,bstrDescription,bstrIPAdapter)

#define ITVESupervisor_ReTune(This,pService)	\
    (This)->lpVtbl -> ReTune(This,pService)

#define ITVESupervisor_NewXOverLink(This,bstrLine21Trigger)	\
    (This)->lpVtbl -> NewXOverLink(This,bstrLine21Trigger)

#define ITVESupervisor_ExpireForDate(This,dateExpireTime)	\
    (This)->lpVtbl -> ExpireForDate(This,dateExpireTime)

#define ITVESupervisor_InitStats(This)	\
    (This)->lpVtbl -> InitStats(This)

#define ITVESupervisor_GetStats(This,pbstrBuff)	\
    (This)->lpVtbl -> GetStats(This,pbstrBuff)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_get_Services_Proxy( 
    ITVESupervisor * This,
    /* [retval][out] */ ITVEServices **pVal);


void __RPC_STUB ITVESupervisor_get_Services_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_get_Description_Proxy( 
    ITVESupervisor * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVESupervisor_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_put_Description_Proxy( 
    ITVESupervisor * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVESupervisor_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_TuneTo_Proxy( 
    ITVESupervisor * This,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVESupervisor_TuneTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_ReTune_Proxy( 
    ITVESupervisor * This,
    /* [in] */ ITVEService *pService);


void __RPC_STUB ITVESupervisor_ReTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_NewXOverLink_Proxy( 
    ITVESupervisor * This,
    /* [in] */ BSTR bstrLine21Trigger);


void __RPC_STUB ITVESupervisor_NewXOverLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_ExpireForDate_Proxy( 
    ITVESupervisor * This,
    /* [in] */ DATE dateExpireTime);


void __RPC_STUB ITVESupervisor_ExpireForDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_InitStats_Proxy( 
    ITVESupervisor * This);


void __RPC_STUB ITVESupervisor_InitStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_GetStats_Proxy( 
    ITVESupervisor * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVESupervisor_GetStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVESupervisor_INTERFACE_DEFINED__ */


#ifndef __ITVESupervisor_Helper_INTERFACE_DEFINED__
#define __ITVESupervisor_Helper_INTERFACE_DEFINED__

/* interface ITVESupervisor_Helper */
/* [unique][helpstring][hidden][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVESupervisor_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500206-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVESupervisor_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectParent( 
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActiveService( 
            /* [out] */ ITVEService **ppActiveService) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMCastManager( 
            /* [out] */ ITVEMCastManager **pMCastManager) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnpackBuffer( 
            /* [in] */ IUnknown *pTVEVariation,
            /* [in] */ unsigned char *m_rgbData,
            /* [in] */ int cBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyEnhancement( 
            /* [in] */ NENH_Mode enhMode,
            /* [in] */ ITVEEnhancement *pEnhancement,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTrigger( 
            /* [in] */ NTRK_Mode trgMode,
            /* [in] */ ITVETrack *pTrack,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPackage( 
            /* [in] */ NPKG_Mode pkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrPackageUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyFile( 
            /* [in] */ NFLE_Mode fileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrURLName,
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTune( 
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyAuxInfo( 
            /* [in] */ NWHAT_Mode whatMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lgrfWhatDiff,
            /* [in] */ long lLineError) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyEnhancement_XProxy( 
            /* [in] */ NENH_Mode enhMode,
            /* [in] */ ITVEEnhancement *pEnhancement,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTrigger_XProxy( 
            /* [in] */ NTRK_Mode trgMode,
            /* [in] */ ITVETrack *pTrack,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPackage_XProxy( 
            NPKG_Mode pkgMode,
            ITVEVariation *pVariation,
            BSTR bstrPackageUUID,
            long cBytesTotal,
            long cBytesReceived) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyFile_XProxy( 
            /* [in] */ NFLE_Mode fileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrURLName,
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTune_XProxy( 
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyAuxInfo_XProxy( 
            /* [in] */ NWHAT_Mode whatMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lgrfWhatDiff,
            /* [in] */ long lLineError) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HaltFlags( 
            /* [retval][out] */ LONG *plGrfHaltFlags) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HaltFlags( 
            /* [in] */ LONG lGrfHaltFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllListenersOnAdapter( 
            /* [in] */ BSTR bstrAdapter) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PossibleIPAdapterAddress( 
            /* [in] */ int iAdapter,
            /* [retval][out] */ BSTR *pbstrIPAdapterAddr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pbstrBuff) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupervisorGITProxy( 
            /* [out] */ ITVESupervisorGITProxy **ppSupervisorGITProxy) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVESupervisor_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVESupervisor_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVESupervisor_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVESupervisor_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectParent )( 
            ITVESupervisor_Helper * This,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetActiveService )( 
            ITVESupervisor_Helper * This,
            /* [out] */ ITVEService **ppActiveService);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMCastManager )( 
            ITVESupervisor_Helper * This,
            /* [out] */ ITVEMCastManager **pMCastManager);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnpackBuffer )( 
            ITVESupervisor_Helper * This,
            /* [in] */ IUnknown *pTVEVariation,
            /* [in] */ unsigned char *m_rgbData,
            /* [in] */ int cBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyEnhancement )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NENH_Mode enhMode,
            /* [in] */ ITVEEnhancement *pEnhancement,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTrigger )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NTRK_Mode trgMode,
            /* [in] */ ITVETrack *pTrack,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPackage )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NPKG_Mode pkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrPackageUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyFile )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NFLE_Mode fileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrURLName,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTune )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyAuxInfo )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NWHAT_Mode whatMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lgrfWhatDiff,
            /* [in] */ long lLineError);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyEnhancement_XProxy )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NENH_Mode enhMode,
            /* [in] */ ITVEEnhancement *pEnhancement,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTrigger_XProxy )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NTRK_Mode trgMode,
            /* [in] */ ITVETrack *pTrack,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPackage_XProxy )( 
            ITVESupervisor_Helper * This,
            NPKG_Mode pkgMode,
            ITVEVariation *pVariation,
            BSTR bstrPackageUUID,
            long cBytesTotal,
            long cBytesReceived);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyFile_XProxy )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NFLE_Mode fileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrURLName,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTune_XProxy )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyAuxInfo_XProxy )( 
            ITVESupervisor_Helper * This,
            /* [in] */ NWHAT_Mode whatMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lgrfWhatDiff,
            /* [in] */ long lLineError);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HaltFlags )( 
            ITVESupervisor_Helper * This,
            /* [retval][out] */ LONG *plGrfHaltFlags);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HaltFlags )( 
            ITVESupervisor_Helper * This,
            /* [in] */ LONG lGrfHaltFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllListenersOnAdapter )( 
            ITVESupervisor_Helper * This,
            /* [in] */ BSTR bstrAdapter);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PossibleIPAdapterAddress )( 
            ITVESupervisor_Helper * This,
            /* [in] */ int iAdapter,
            /* [retval][out] */ BSTR *pbstrIPAdapterAddr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVESupervisor_Helper * This,
            /* [out] */ BSTR *pbstrBuff);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupervisorGITProxy )( 
            ITVESupervisor_Helper * This,
            /* [out] */ ITVESupervisorGITProxy **ppSupervisorGITProxy);
        
        END_INTERFACE
    } ITVESupervisor_HelperVtbl;

    interface ITVESupervisor_Helper
    {
        CONST_VTBL struct ITVESupervisor_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVESupervisor_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVESupervisor_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVESupervisor_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVESupervisor_Helper_ConnectParent(This,pUnk)	\
    (This)->lpVtbl -> ConnectParent(This,pUnk)

#define ITVESupervisor_Helper_GetActiveService(This,ppActiveService)	\
    (This)->lpVtbl -> GetActiveService(This,ppActiveService)

#define ITVESupervisor_Helper_GetMCastManager(This,pMCastManager)	\
    (This)->lpVtbl -> GetMCastManager(This,pMCastManager)

#define ITVESupervisor_Helper_UnpackBuffer(This,pTVEVariation,m_rgbData,cBytes)	\
    (This)->lpVtbl -> UnpackBuffer(This,pTVEVariation,m_rgbData,cBytes)

#define ITVESupervisor_Helper_NotifyEnhancement(This,enhMode,pEnhancement,lChangedFlags)	\
    (This)->lpVtbl -> NotifyEnhancement(This,enhMode,pEnhancement,lChangedFlags)

#define ITVESupervisor_Helper_NotifyTrigger(This,trgMode,pTrack,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTrigger(This,trgMode,pTrack,lChangedFlags)

#define ITVESupervisor_Helper_NotifyPackage(This,pkgMode,pVariation,bstrPackageUUID,cBytesTotal,cBytesReceived)	\
    (This)->lpVtbl -> NotifyPackage(This,pkgMode,pVariation,bstrPackageUUID,cBytesTotal,cBytesReceived)

#define ITVESupervisor_Helper_NotifyFile(This,fileMode,pVariation,bstrURLName,bstrFileName)	\
    (This)->lpVtbl -> NotifyFile(This,fileMode,pVariation,bstrURLName,bstrFileName)

#define ITVESupervisor_Helper_NotifyTune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)	\
    (This)->lpVtbl -> NotifyTune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)

#define ITVESupervisor_Helper_NotifyAuxInfo(This,whatMode,bstrAuxInfoString,lgrfWhatDiff,lLineError)	\
    (This)->lpVtbl -> NotifyAuxInfo(This,whatMode,bstrAuxInfoString,lgrfWhatDiff,lLineError)

#define ITVESupervisor_Helper_NotifyEnhancement_XProxy(This,enhMode,pEnhancement,lChangedFlags)	\
    (This)->lpVtbl -> NotifyEnhancement_XProxy(This,enhMode,pEnhancement,lChangedFlags)

#define ITVESupervisor_Helper_NotifyTrigger_XProxy(This,trgMode,pTrack,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTrigger_XProxy(This,trgMode,pTrack,lChangedFlags)

#define ITVESupervisor_Helper_NotifyPackage_XProxy(This,pkgMode,pVariation,bstrPackageUUID,cBytesTotal,cBytesReceived)	\
    (This)->lpVtbl -> NotifyPackage_XProxy(This,pkgMode,pVariation,bstrPackageUUID,cBytesTotal,cBytesReceived)

#define ITVESupervisor_Helper_NotifyFile_XProxy(This,fileMode,pVariation,bstrURLName,bstrFileName)	\
    (This)->lpVtbl -> NotifyFile_XProxy(This,fileMode,pVariation,bstrURLName,bstrFileName)

#define ITVESupervisor_Helper_NotifyTune_XProxy(This,tuneMode,pService,bstrDescription,bstrIPAdapter)	\
    (This)->lpVtbl -> NotifyTune_XProxy(This,tuneMode,pService,bstrDescription,bstrIPAdapter)

#define ITVESupervisor_Helper_NotifyAuxInfo_XProxy(This,whatMode,bstrAuxInfoString,lgrfWhatDiff,lLineError)	\
    (This)->lpVtbl -> NotifyAuxInfo_XProxy(This,whatMode,bstrAuxInfoString,lgrfWhatDiff,lLineError)

#define ITVESupervisor_Helper_get_HaltFlags(This,plGrfHaltFlags)	\
    (This)->lpVtbl -> get_HaltFlags(This,plGrfHaltFlags)

#define ITVESupervisor_Helper_put_HaltFlags(This,lGrfHaltFlags)	\
    (This)->lpVtbl -> put_HaltFlags(This,lGrfHaltFlags)

#define ITVESupervisor_Helper_RemoveAllListenersOnAdapter(This,bstrAdapter)	\
    (This)->lpVtbl -> RemoveAllListenersOnAdapter(This,bstrAdapter)

#define ITVESupervisor_Helper_get_PossibleIPAdapterAddress(This,iAdapter,pbstrIPAdapterAddr)	\
    (This)->lpVtbl -> get_PossibleIPAdapterAddress(This,iAdapter,pbstrIPAdapterAddr)

#define ITVESupervisor_Helper_DumpToBSTR(This,pbstrBuff)	\
    (This)->lpVtbl -> DumpToBSTR(This,pbstrBuff)

#define ITVESupervisor_Helper_get_SupervisorGITProxy(This,ppSupervisorGITProxy)	\
    (This)->lpVtbl -> get_SupervisorGITProxy(This,ppSupervisorGITProxy)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_ConnectParent_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ITVESupervisor_Helper_ConnectParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_GetActiveService_Proxy( 
    ITVESupervisor_Helper * This,
    /* [out] */ ITVEService **ppActiveService);


void __RPC_STUB ITVESupervisor_Helper_GetActiveService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_GetMCastManager_Proxy( 
    ITVESupervisor_Helper * This,
    /* [out] */ ITVEMCastManager **pMCastManager);


void __RPC_STUB ITVESupervisor_Helper_GetMCastManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_UnpackBuffer_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ IUnknown *pTVEVariation,
    /* [in] */ unsigned char *m_rgbData,
    /* [in] */ int cBytes);


void __RPC_STUB ITVESupervisor_Helper_UnpackBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyEnhancement_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NENH_Mode enhMode,
    /* [in] */ ITVEEnhancement *pEnhancement,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVESupervisor_Helper_NotifyEnhancement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyTrigger_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NTRK_Mode trgMode,
    /* [in] */ ITVETrack *pTrack,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVESupervisor_Helper_NotifyTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyPackage_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NPKG_Mode pkgMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrPackageUUID,
    /* [in] */ long cBytesTotal,
    /* [in] */ long cBytesReceived);


void __RPC_STUB ITVESupervisor_Helper_NotifyPackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyFile_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NFLE_Mode fileMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrURLName,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB ITVESupervisor_Helper_NotifyFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyTune_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NTUN_Mode tuneMode,
    /* [in] */ ITVEService *pService,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVESupervisor_Helper_NotifyTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyAuxInfo_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NWHAT_Mode whatMode,
    /* [in] */ BSTR bstrAuxInfoString,
    /* [in] */ long lgrfWhatDiff,
    /* [in] */ long lLineError);


void __RPC_STUB ITVESupervisor_Helper_NotifyAuxInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyEnhancement_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NENH_Mode enhMode,
    /* [in] */ ITVEEnhancement *pEnhancement,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVESupervisor_Helper_NotifyEnhancement_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyTrigger_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NTRK_Mode trgMode,
    /* [in] */ ITVETrack *pTrack,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVESupervisor_Helper_NotifyTrigger_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyPackage_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    NPKG_Mode pkgMode,
    ITVEVariation *pVariation,
    BSTR bstrPackageUUID,
    long cBytesTotal,
    long cBytesReceived);


void __RPC_STUB ITVESupervisor_Helper_NotifyPackage_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyFile_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NFLE_Mode fileMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrURLName,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB ITVESupervisor_Helper_NotifyFile_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyTune_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NTUN_Mode tuneMode,
    /* [in] */ ITVEService *pService,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVESupervisor_Helper_NotifyTune_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_NotifyAuxInfo_XProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ NWHAT_Mode whatMode,
    /* [in] */ BSTR bstrAuxInfoString,
    /* [in] */ long lgrfWhatDiff,
    /* [in] */ long lLineError);


void __RPC_STUB ITVESupervisor_Helper_NotifyAuxInfo_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_get_HaltFlags_Proxy( 
    ITVESupervisor_Helper * This,
    /* [retval][out] */ LONG *plGrfHaltFlags);


void __RPC_STUB ITVESupervisor_Helper_get_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_put_HaltFlags_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ LONG lGrfHaltFlags);


void __RPC_STUB ITVESupervisor_Helper_put_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_RemoveAllListenersOnAdapter_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ BSTR bstrAdapter);


void __RPC_STUB ITVESupervisor_Helper_RemoveAllListenersOnAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_get_PossibleIPAdapterAddress_Proxy( 
    ITVESupervisor_Helper * This,
    /* [in] */ int iAdapter,
    /* [retval][out] */ BSTR *pbstrIPAdapterAddr);


void __RPC_STUB ITVESupervisor_Helper_get_PossibleIPAdapterAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_DumpToBSTR_Proxy( 
    ITVESupervisor_Helper * This,
    /* [out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVESupervisor_Helper_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisor_Helper_get_SupervisorGITProxy_Proxy( 
    ITVESupervisor_Helper * This,
    /* [out] */ ITVESupervisorGITProxy **ppSupervisorGITProxy);


void __RPC_STUB ITVESupervisor_Helper_get_SupervisorGITProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVESupervisor_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVESupervisorGITProxy_INTERFACE_DEFINED__
#define __ITVESupervisorGITProxy_INTERFACE_DEFINED__

/* interface ITVESupervisorGITProxy */
/* [unique][helpstring][dual][uuid][object][hidden] */ 


EXTERN_C const IID IID_ITVESupervisorGITProxy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500306-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVESupervisorGITProxy : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Supervisor( 
            /* [retval][out] */ ITVESupervisor **ppVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Supervisor( 
            /* [in] */ ITVESupervisor *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVESupervisorGITProxyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVESupervisorGITProxy * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVESupervisorGITProxy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVESupervisorGITProxy * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Supervisor )( 
            ITVESupervisorGITProxy * This,
            /* [retval][out] */ ITVESupervisor **ppVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Supervisor )( 
            ITVESupervisorGITProxy * This,
            /* [in] */ ITVESupervisor *pVal);
        
        END_INTERFACE
    } ITVESupervisorGITProxyVtbl;

    interface ITVESupervisorGITProxy
    {
        CONST_VTBL struct ITVESupervisorGITProxyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVESupervisorGITProxy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVESupervisorGITProxy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVESupervisorGITProxy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVESupervisorGITProxy_get_Supervisor(This,ppVal)	\
    (This)->lpVtbl -> get_Supervisor(This,ppVal)

#define ITVESupervisorGITProxy_put_Supervisor(This,pVal)	\
    (This)->lpVtbl -> put_Supervisor(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVESupervisorGITProxy_get_Supervisor_Proxy( 
    ITVESupervisorGITProxy * This,
    /* [retval][out] */ ITVESupervisor **ppVal);


void __RPC_STUB ITVESupervisorGITProxy_get_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVESupervisorGITProxy_put_Supervisor_Proxy( 
    ITVESupervisorGITProxy * This,
    /* [in] */ ITVESupervisor *pVal);


void __RPC_STUB ITVESupervisorGITProxy_put_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVESupervisorGITProxy_INTERFACE_DEFINED__ */


#ifndef __ITVEAttrMap_INTERFACE_DEFINED__
#define __ITVEAttrMap_INTERFACE_DEFINED__

/* interface ITVEAttrMap */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEAttrMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500121-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEAttrMap : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Key( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ BSTR *pKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Replace( 
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add1( 
            BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pDump) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEAttrMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEAttrMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEAttrMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEAttrMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEAttrMap * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEAttrMap * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEAttrMap * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEAttrMap * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEAttrMap * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEAttrMap * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEAttrMap * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Key )( 
            ITVEAttrMap * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ BSTR *pKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEAttrMap * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Replace )( 
            ITVEAttrMap * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEAttrMap * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEAttrMap * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add1 )( 
            ITVEAttrMap * This,
            BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEAttrMap * This,
            /* [out] */ BSTR *pDump);
        
        END_INTERFACE
    } ITVEAttrMapVtbl;

    interface ITVEAttrMap
    {
        CONST_VTBL struct ITVEAttrMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEAttrMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEAttrMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEAttrMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEAttrMap_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEAttrMap_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEAttrMap_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEAttrMap_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEAttrMap_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEAttrMap_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEAttrMap_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVEAttrMap_get_Key(This,var,pKey)	\
    (This)->lpVtbl -> get_Key(This,var,pKey)

#define ITVEAttrMap_Add(This,bstrKey,bstrValue)	\
    (This)->lpVtbl -> Add(This,bstrKey,bstrValue)

#define ITVEAttrMap_Replace(This,bstrKey,bstrValue)	\
    (This)->lpVtbl -> Replace(This,bstrKey,bstrValue)

#define ITVEAttrMap_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEAttrMap_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVEAttrMap_Add1(This,bstrValue)	\
    (This)->lpVtbl -> Add1(This,bstrValue)

#define ITVEAttrMap_DumpToBSTR(This,pDump)	\
    (This)->lpVtbl -> DumpToBSTR(This,pDump)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_get__NewEnum_Proxy( 
    ITVEAttrMap * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEAttrMap_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_get_Count_Proxy( 
    ITVEAttrMap * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEAttrMap_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_get_Item_Proxy( 
    ITVEAttrMap * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEAttrMap_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_get_Key_Proxy( 
    ITVEAttrMap * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ BSTR *pKey);


void __RPC_STUB ITVEAttrMap_get_Key_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_Add_Proxy( 
    ITVEAttrMap * This,
    /* [in] */ BSTR bstrKey,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB ITVEAttrMap_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_Replace_Proxy( 
    ITVEAttrMap * This,
    /* [in] */ BSTR bstrKey,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB ITVEAttrMap_Replace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_Remove_Proxy( 
    ITVEAttrMap * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEAttrMap_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_RemoveAll_Proxy( 
    ITVEAttrMap * This);


void __RPC_STUB ITVEAttrMap_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_Add1_Proxy( 
    ITVEAttrMap * This,
    BSTR bstrValue);


void __RPC_STUB ITVEAttrMap_Add1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrMap_DumpToBSTR_Proxy( 
    ITVEAttrMap * This,
    /* [out] */ BSTR *pDump);


void __RPC_STUB ITVEAttrMap_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEAttrMap_INTERFACE_DEFINED__ */


#ifndef __ITVEAttrTimeQ_INTERFACE_DEFINED__
#define __ITVEAttrTimeQ_INTERFACE_DEFINED__

/* interface ITVEAttrTimeQ */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEAttrTimeQ;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500122-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEAttrTimeQ : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Key( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ DATE *pKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ DATE dateKey,
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ DATE dateKey,
            /* [in] */ IUnknown *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockRead( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockWrite( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unlock( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveSimple( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pDump) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEAttrTimeQVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEAttrTimeQ * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEAttrTimeQ * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEAttrTimeQ * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEAttrTimeQ * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEAttrTimeQ * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEAttrTimeQ * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEAttrTimeQ * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEAttrTimeQ * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEAttrTimeQ * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEAttrTimeQ * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ IUnknown **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Key )( 
            ITVEAttrTimeQ * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ DATE *pKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEAttrTimeQ * This,
            /* [in] */ DATE dateKey,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEAttrTimeQ * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEAttrTimeQ * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            ITVEAttrTimeQ * This,
            /* [in] */ DATE dateKey,
            /* [in] */ IUnknown *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LockRead )( 
            ITVEAttrTimeQ * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LockWrite )( 
            ITVEAttrTimeQ * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unlock )( 
            ITVEAttrTimeQ * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveSimple )( 
            ITVEAttrTimeQ * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEAttrTimeQ * This,
            /* [out] */ BSTR *pDump);
        
        END_INTERFACE
    } ITVEAttrTimeQVtbl;

    interface ITVEAttrTimeQ
    {
        CONST_VTBL struct ITVEAttrTimeQVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEAttrTimeQ_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEAttrTimeQ_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEAttrTimeQ_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEAttrTimeQ_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEAttrTimeQ_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEAttrTimeQ_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEAttrTimeQ_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEAttrTimeQ_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEAttrTimeQ_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEAttrTimeQ_get_Item(This,var,ppVal)	\
    (This)->lpVtbl -> get_Item(This,var,ppVal)

#define ITVEAttrTimeQ_get_Key(This,var,pKey)	\
    (This)->lpVtbl -> get_Key(This,var,pKey)

#define ITVEAttrTimeQ_Add(This,dateKey,pUnk)	\
    (This)->lpVtbl -> Add(This,dateKey,pUnk)

#define ITVEAttrTimeQ_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEAttrTimeQ_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#define ITVEAttrTimeQ_Update(This,dateKey,pUnk)	\
    (This)->lpVtbl -> Update(This,dateKey,pUnk)

#define ITVEAttrTimeQ_LockRead(This)	\
    (This)->lpVtbl -> LockRead(This)

#define ITVEAttrTimeQ_LockWrite(This)	\
    (This)->lpVtbl -> LockWrite(This)

#define ITVEAttrTimeQ_Unlock(This)	\
    (This)->lpVtbl -> Unlock(This)

#define ITVEAttrTimeQ_RemoveSimple(This,var)	\
    (This)->lpVtbl -> RemoveSimple(This,var)

#define ITVEAttrTimeQ_DumpToBSTR(This,pDump)	\
    (This)->lpVtbl -> DumpToBSTR(This,pDump)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_get__NewEnum_Proxy( 
    ITVEAttrTimeQ * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEAttrTimeQ_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_get_Count_Proxy( 
    ITVEAttrTimeQ * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEAttrTimeQ_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_get_Item_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ IUnknown **ppVal);


void __RPC_STUB ITVEAttrTimeQ_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_get_Key_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ DATE *pKey);


void __RPC_STUB ITVEAttrTimeQ_get_Key_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_Add_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ DATE dateKey,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ITVEAttrTimeQ_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_Remove_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEAttrTimeQ_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_RemoveAll_Proxy( 
    ITVEAttrTimeQ * This);


void __RPC_STUB ITVEAttrTimeQ_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_Update_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ DATE dateKey,
    /* [in] */ IUnknown *pUnk);


void __RPC_STUB ITVEAttrTimeQ_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_LockRead_Proxy( 
    ITVEAttrTimeQ * This);


void __RPC_STUB ITVEAttrTimeQ_LockRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_LockWrite_Proxy( 
    ITVEAttrTimeQ * This);


void __RPC_STUB ITVEAttrTimeQ_LockWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_Unlock_Proxy( 
    ITVEAttrTimeQ * This);


void __RPC_STUB ITVEAttrTimeQ_Unlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_RemoveSimple_Proxy( 
    ITVEAttrTimeQ * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEAttrTimeQ_RemoveSimple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEAttrTimeQ_DumpToBSTR_Proxy( 
    ITVEAttrTimeQ * This,
    /* [out] */ BSTR *pDump);


void __RPC_STUB ITVEAttrTimeQ_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEAttrTimeQ_INTERFACE_DEFINED__ */


#ifndef __ITVEMCast_INTERFACE_DEFINED__
#define __ITVEMCast_INTERFACE_DEFINED__

/* interface ITVEMCast */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEMCast;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500130-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEMCast : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAdapter( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPAdapter( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPPort( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPPort( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Join( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Leave( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsJoined( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsSuspended( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Suspend( 
            VARIANT_BOOL fSuspend) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ByteCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE KeepStats( 
            VARIANT_BOOL fKeepStats) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetStats( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReadCallback( 
            /* [in] */ int nBuffers,
            /* [in] */ int iPrioritySetback,
            /* [in] */ IUnknown *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectManager( 
            /* [in] */ ITVEMCastManager *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Manager( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueueThreadId( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueueThreadId( 
            /* [in] */ long pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhatType( 
            /* [retval][out] */ NWHAT_Mode *pWhatType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WhatType( 
            /* [in] */ NWHAT_Mode whatType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEMCastVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEMCast * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEMCast * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEMCast * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEMCast * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEMCast * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEMCast * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEMCast * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAdapter )( 
            ITVEMCast * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAdapter )( 
            ITVEMCast * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddress )( 
            ITVEMCast * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAddress )( 
            ITVEMCast * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPPort )( 
            ITVEMCast * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPPort )( 
            ITVEMCast * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Join )( 
            ITVEMCast * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Leave )( 
            ITVEMCast * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsJoined )( 
            ITVEMCast * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSuspended )( 
            ITVEMCast * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Suspend )( 
            ITVEMCast * This,
            VARIANT_BOOL fSuspend);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PacketCount )( 
            ITVEMCast * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ByteCount )( 
            ITVEMCast * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *KeepStats )( 
            ITVEMCast * This,
            VARIANT_BOOL fKeepStats);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetStats )( 
            ITVEMCast * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetReadCallback )( 
            ITVEMCast * This,
            /* [in] */ int nBuffers,
            /* [in] */ int iPrioritySetback,
            /* [in] */ IUnknown *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectManager )( 
            ITVEMCast * This,
            /* [in] */ ITVEMCastManager *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Manager )( 
            ITVEMCast * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QueueThreadId )( 
            ITVEMCast * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QueueThreadId )( 
            ITVEMCast * This,
            /* [in] */ long pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WhatType )( 
            ITVEMCast * This,
            /* [retval][out] */ NWHAT_Mode *pWhatType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WhatType )( 
            ITVEMCast * This,
            /* [in] */ NWHAT_Mode whatType);
        
        END_INTERFACE
    } ITVEMCastVtbl;

    interface ITVEMCast
    {
        CONST_VTBL struct ITVEMCastVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEMCast_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEMCast_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEMCast_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEMCast_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEMCast_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEMCast_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEMCast_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEMCast_get_IPAdapter(This,pVal)	\
    (This)->lpVtbl -> get_IPAdapter(This,pVal)

#define ITVEMCast_put_IPAdapter(This,newVal)	\
    (This)->lpVtbl -> put_IPAdapter(This,newVal)

#define ITVEMCast_get_IPAddress(This,pVal)	\
    (This)->lpVtbl -> get_IPAddress(This,pVal)

#define ITVEMCast_put_IPAddress(This,newVal)	\
    (This)->lpVtbl -> put_IPAddress(This,newVal)

#define ITVEMCast_get_IPPort(This,pVal)	\
    (This)->lpVtbl -> get_IPPort(This,pVal)

#define ITVEMCast_put_IPPort(This,newVal)	\
    (This)->lpVtbl -> put_IPPort(This,newVal)

#define ITVEMCast_Join(This)	\
    (This)->lpVtbl -> Join(This)

#define ITVEMCast_Leave(This)	\
    (This)->lpVtbl -> Leave(This)

#define ITVEMCast_get_IsJoined(This,pVal)	\
    (This)->lpVtbl -> get_IsJoined(This,pVal)

#define ITVEMCast_get_IsSuspended(This,pVal)	\
    (This)->lpVtbl -> get_IsSuspended(This,pVal)

#define ITVEMCast_Suspend(This,fSuspend)	\
    (This)->lpVtbl -> Suspend(This,fSuspend)

#define ITVEMCast_get_PacketCount(This,pVal)	\
    (This)->lpVtbl -> get_PacketCount(This,pVal)

#define ITVEMCast_get_ByteCount(This,pVal)	\
    (This)->lpVtbl -> get_ByteCount(This,pVal)

#define ITVEMCast_KeepStats(This,fKeepStats)	\
    (This)->lpVtbl -> KeepStats(This,fKeepStats)

#define ITVEMCast_ResetStats(This)	\
    (This)->lpVtbl -> ResetStats(This)

#define ITVEMCast_SetReadCallback(This,nBuffers,iPrioritySetback,pVal)	\
    (This)->lpVtbl -> SetReadCallback(This,nBuffers,iPrioritySetback,pVal)

#define ITVEMCast_ConnectManager(This,pVal)	\
    (This)->lpVtbl -> ConnectManager(This,pVal)

#define ITVEMCast_get_Manager(This,ppVal)	\
    (This)->lpVtbl -> get_Manager(This,ppVal)

#define ITVEMCast_get_QueueThreadId(This,pVal)	\
    (This)->lpVtbl -> get_QueueThreadId(This,pVal)

#define ITVEMCast_put_QueueThreadId(This,pVal)	\
    (This)->lpVtbl -> put_QueueThreadId(This,pVal)

#define ITVEMCast_get_WhatType(This,pWhatType)	\
    (This)->lpVtbl -> get_WhatType(This,pWhatType)

#define ITVEMCast_put_WhatType(This,whatType)	\
    (This)->lpVtbl -> put_WhatType(This,whatType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_IPAdapter_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEMCast_get_IPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCast_put_IPAdapter_Proxy( 
    ITVEMCast * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEMCast_put_IPAdapter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_IPAddress_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVEMCast_get_IPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCast_put_IPAddress_Proxy( 
    ITVEMCast * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITVEMCast_put_IPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_IPPort_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEMCast_get_IPPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCast_put_IPPort_Proxy( 
    ITVEMCast * This,
    /* [in] */ long newVal);


void __RPC_STUB ITVEMCast_put_IPPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_Join_Proxy( 
    ITVEMCast * This);


void __RPC_STUB ITVEMCast_Join_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_Leave_Proxy( 
    ITVEMCast * This);


void __RPC_STUB ITVEMCast_Leave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_IsJoined_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVEMCast_get_IsJoined_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_IsSuspended_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVEMCast_get_IsSuspended_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_Suspend_Proxy( 
    ITVEMCast * This,
    VARIANT_BOOL fSuspend);


void __RPC_STUB ITVEMCast_Suspend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_PacketCount_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEMCast_get_PacketCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_ByteCount_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEMCast_get_ByteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_KeepStats_Proxy( 
    ITVEMCast * This,
    VARIANT_BOOL fKeepStats);


void __RPC_STUB ITVEMCast_KeepStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_ResetStats_Proxy( 
    ITVEMCast * This);


void __RPC_STUB ITVEMCast_ResetStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_SetReadCallback_Proxy( 
    ITVEMCast * This,
    /* [in] */ int nBuffers,
    /* [in] */ int iPrioritySetback,
    /* [in] */ IUnknown *pVal);


void __RPC_STUB ITVEMCast_SetReadCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCast_ConnectManager_Proxy( 
    ITVEMCast * This,
    /* [in] */ ITVEMCastManager *pVal);


void __RPC_STUB ITVEMCast_ConnectManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_Manager_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ IUnknown **ppVal);


void __RPC_STUB ITVEMCast_get_Manager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_QueueThreadId_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEMCast_get_QueueThreadId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCast_put_QueueThreadId_Proxy( 
    ITVEMCast * This,
    /* [in] */ long pVal);


void __RPC_STUB ITVEMCast_put_QueueThreadId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCast_get_WhatType_Proxy( 
    ITVEMCast * This,
    /* [retval][out] */ NWHAT_Mode *pWhatType);


void __RPC_STUB ITVEMCast_get_WhatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCast_put_WhatType_Proxy( 
    ITVEMCast * This,
    /* [in] */ NWHAT_Mode whatType);


void __RPC_STUB ITVEMCast_put_WhatType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEMCast_INTERFACE_DEFINED__ */


#ifndef __ITVEMCasts_INTERFACE_DEFINED__
#define __ITVEMCasts_INTERFACE_DEFINED__

/* interface ITVEMCasts */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEMCasts;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500131-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEMCasts : public IDispatch
    {
    public:
        virtual /* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEMCast **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ITVEMCast *punk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEMCastsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEMCasts * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEMCasts * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEMCasts * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEMCasts * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEMCasts * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEMCasts * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEMCasts * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITVEMCasts * This,
            /* [retval][out] */ IUnknown **pCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITVEMCasts * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITVEMCasts * This,
            /* [in] */ VARIANT var,
            /* [retval][out] */ ITVEMCast **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITVEMCasts * This,
            /* [in] */ ITVEMCast *punk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITVEMCasts * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITVEMCasts * This);
        
        END_INTERFACE
    } ITVEMCastsVtbl;

    interface ITVEMCasts
    {
        CONST_VTBL struct ITVEMCastsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEMCasts_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEMCasts_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEMCasts_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEMCasts_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEMCasts_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEMCasts_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEMCasts_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEMCasts_get__NewEnum(This,pCollection)	\
    (This)->lpVtbl -> get__NewEnum(This,pCollection)

#define ITVEMCasts_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITVEMCasts_get_Item(This,var,pVal)	\
    (This)->lpVtbl -> get_Item(This,var,pVal)

#define ITVEMCasts_Add(This,punk)	\
    (This)->lpVtbl -> Add(This,punk)

#define ITVEMCasts_Remove(This,var)	\
    (This)->lpVtbl -> Remove(This,var)

#define ITVEMCasts_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_get__NewEnum_Proxy( 
    ITVEMCasts * This,
    /* [retval][out] */ IUnknown **pCollection);


void __RPC_STUB ITVEMCasts_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_get_Count_Proxy( 
    ITVEMCasts * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITVEMCasts_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_get_Item_Proxy( 
    ITVEMCasts * This,
    /* [in] */ VARIANT var,
    /* [retval][out] */ ITVEMCast **pVal);


void __RPC_STUB ITVEMCasts_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_Add_Proxy( 
    ITVEMCasts * This,
    /* [in] */ ITVEMCast *punk);


void __RPC_STUB ITVEMCasts_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_Remove_Proxy( 
    ITVEMCasts * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ITVEMCasts_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCasts_RemoveAll_Proxy( 
    ITVEMCasts * This);


void __RPC_STUB ITVEMCasts_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEMCasts_INTERFACE_DEFINED__ */


#ifndef __ITVEMCastManager_INTERFACE_DEFINED__
#define __ITVEMCastManager_INTERFACE_DEFINED__

/* interface ITVEMCastManager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEMCastManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500132-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEMCastManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MCasts( 
            /* [retval][out] */ ITVEMCasts **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Supervisor( 
            /* [retval][out] */ ITVESupervisor **ppSupervisor) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Supervisor( 
            /* [in] */ ITVESupervisor *pSupervisor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMulticast( 
            /* [in] */ NWHAT_Mode whatType,
            /* [in] */ BSTR bsAdapter,
            /* [in] */ BSTR bsIPAddress,
            /* [in] */ LONG ulIPPort,
            /* [in] */ LONG cBuffers,
            /* [in] */ IUnknown *pICallback,
            /* [out] */ ITVEMCast **ppMCastAdded) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindMulticast( 
            /* [in] */ BSTR bstrIPAdapter,
            /* [in] */ BSTR bstrIPAddress,
            /* [in] */ LONG sPort,
            /* [out] */ ITVEMCast **ppMCast,
            /* [out] */ LONG *pcMatches) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveMulticast( 
            ITVEMCast *pMCast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE JoinAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LeaveAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SuspendAll( 
            /* [in] */ VARIANT_BOOL fSuspend) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Lock_( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unlock_( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpStatsToBSTR( 
            int iType,
            BSTR *pBSTR) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HaltFlags( 
            /* [retval][out] */ LONG *plGrfHaltFlags) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HaltFlags( 
            /* [in] */ LONG lGrfHaltFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEMCastManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEMCastManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEMCastManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEMCastManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEMCastManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEMCastManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEMCastManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEMCastManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MCasts )( 
            ITVEMCastManager * This,
            /* [retval][out] */ ITVEMCasts **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Supervisor )( 
            ITVEMCastManager * This,
            /* [retval][out] */ ITVESupervisor **ppSupervisor);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Supervisor )( 
            ITVEMCastManager * This,
            /* [in] */ ITVESupervisor *pSupervisor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddMulticast )( 
            ITVEMCastManager * This,
            /* [in] */ NWHAT_Mode whatType,
            /* [in] */ BSTR bsAdapter,
            /* [in] */ BSTR bsIPAddress,
            /* [in] */ LONG ulIPPort,
            /* [in] */ LONG cBuffers,
            /* [in] */ IUnknown *pICallback,
            /* [out] */ ITVEMCast **ppMCastAdded);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindMulticast )( 
            ITVEMCastManager * This,
            /* [in] */ BSTR bstrIPAdapter,
            /* [in] */ BSTR bstrIPAddress,
            /* [in] */ LONG sPort,
            /* [out] */ ITVEMCast **ppMCast,
            /* [out] */ LONG *pcMatches);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveMulticast )( 
            ITVEMCastManager * This,
            ITVEMCast *pMCast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *JoinAll )( 
            ITVEMCastManager * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LeaveAll )( 
            ITVEMCastManager * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SuspendAll )( 
            ITVEMCastManager * This,
            /* [in] */ VARIANT_BOOL fSuspend);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Lock_ )( 
            ITVEMCastManager * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unlock_ )( 
            ITVEMCastManager * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpStatsToBSTR )( 
            ITVEMCastManager * This,
            int iType,
            BSTR *pBSTR);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HaltFlags )( 
            ITVEMCastManager * This,
            /* [retval][out] */ LONG *plGrfHaltFlags);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HaltFlags )( 
            ITVEMCastManager * This,
            /* [in] */ LONG lGrfHaltFlags);
        
        END_INTERFACE
    } ITVEMCastManagerVtbl;

    interface ITVEMCastManager
    {
        CONST_VTBL struct ITVEMCastManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEMCastManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEMCastManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEMCastManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEMCastManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEMCastManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEMCastManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEMCastManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEMCastManager_get_MCasts(This,pVal)	\
    (This)->lpVtbl -> get_MCasts(This,pVal)

#define ITVEMCastManager_get_Supervisor(This,ppSupervisor)	\
    (This)->lpVtbl -> get_Supervisor(This,ppSupervisor)

#define ITVEMCastManager_put_Supervisor(This,pSupervisor)	\
    (This)->lpVtbl -> put_Supervisor(This,pSupervisor)

#define ITVEMCastManager_AddMulticast(This,whatType,bsAdapter,bsIPAddress,ulIPPort,cBuffers,pICallback,ppMCastAdded)	\
    (This)->lpVtbl -> AddMulticast(This,whatType,bsAdapter,bsIPAddress,ulIPPort,cBuffers,pICallback,ppMCastAdded)

#define ITVEMCastManager_FindMulticast(This,bstrIPAdapter,bstrIPAddress,sPort,ppMCast,pcMatches)	\
    (This)->lpVtbl -> FindMulticast(This,bstrIPAdapter,bstrIPAddress,sPort,ppMCast,pcMatches)

#define ITVEMCastManager_RemoveMulticast(This,pMCast)	\
    (This)->lpVtbl -> RemoveMulticast(This,pMCast)

#define ITVEMCastManager_JoinAll(This)	\
    (This)->lpVtbl -> JoinAll(This)

#define ITVEMCastManager_LeaveAll(This)	\
    (This)->lpVtbl -> LeaveAll(This)

#define ITVEMCastManager_SuspendAll(This,fSuspend)	\
    (This)->lpVtbl -> SuspendAll(This,fSuspend)

#define ITVEMCastManager_Lock_(This)	\
    (This)->lpVtbl -> Lock_(This)

#define ITVEMCastManager_Unlock_(This)	\
    (This)->lpVtbl -> Unlock_(This)

#define ITVEMCastManager_DumpStatsToBSTR(This,iType,pBSTR)	\
    (This)->lpVtbl -> DumpStatsToBSTR(This,iType,pBSTR)

#define ITVEMCastManager_get_HaltFlags(This,plGrfHaltFlags)	\
    (This)->lpVtbl -> get_HaltFlags(This,plGrfHaltFlags)

#define ITVEMCastManager_put_HaltFlags(This,lGrfHaltFlags)	\
    (This)->lpVtbl -> put_HaltFlags(This,lGrfHaltFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_get_MCasts_Proxy( 
    ITVEMCastManager * This,
    /* [retval][out] */ ITVEMCasts **pVal);


void __RPC_STUB ITVEMCastManager_get_MCasts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_get_Supervisor_Proxy( 
    ITVEMCastManager * This,
    /* [retval][out] */ ITVESupervisor **ppSupervisor);


void __RPC_STUB ITVEMCastManager_get_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_put_Supervisor_Proxy( 
    ITVEMCastManager * This,
    /* [in] */ ITVESupervisor *pSupervisor);


void __RPC_STUB ITVEMCastManager_put_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_AddMulticast_Proxy( 
    ITVEMCastManager * This,
    /* [in] */ NWHAT_Mode whatType,
    /* [in] */ BSTR bsAdapter,
    /* [in] */ BSTR bsIPAddress,
    /* [in] */ LONG ulIPPort,
    /* [in] */ LONG cBuffers,
    /* [in] */ IUnknown *pICallback,
    /* [out] */ ITVEMCast **ppMCastAdded);


void __RPC_STUB ITVEMCastManager_AddMulticast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_FindMulticast_Proxy( 
    ITVEMCastManager * This,
    /* [in] */ BSTR bstrIPAdapter,
    /* [in] */ BSTR bstrIPAddress,
    /* [in] */ LONG sPort,
    /* [out] */ ITVEMCast **ppMCast,
    /* [out] */ LONG *pcMatches);


void __RPC_STUB ITVEMCastManager_FindMulticast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_RemoveMulticast_Proxy( 
    ITVEMCastManager * This,
    ITVEMCast *pMCast);


void __RPC_STUB ITVEMCastManager_RemoveMulticast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_JoinAll_Proxy( 
    ITVEMCastManager * This);


void __RPC_STUB ITVEMCastManager_JoinAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_LeaveAll_Proxy( 
    ITVEMCastManager * This);


void __RPC_STUB ITVEMCastManager_LeaveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_SuspendAll_Proxy( 
    ITVEMCastManager * This,
    /* [in] */ VARIANT_BOOL fSuspend);


void __RPC_STUB ITVEMCastManager_SuspendAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Lock__Proxy( 
    ITVEMCastManager * This);


void __RPC_STUB ITVEMCastManager_Lock__Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Unlock__Proxy( 
    ITVEMCastManager * This);


void __RPC_STUB ITVEMCastManager_Unlock__Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_DumpStatsToBSTR_Proxy( 
    ITVEMCastManager * This,
    int iType,
    BSTR *pBSTR);


void __RPC_STUB ITVEMCastManager_DumpStatsToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_get_HaltFlags_Proxy( 
    ITVEMCastManager * This,
    /* [retval][out] */ LONG *plGrfHaltFlags);


void __RPC_STUB ITVEMCastManager_get_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_put_HaltFlags_Proxy( 
    ITVEMCastManager * This,
    /* [in] */ LONG lGrfHaltFlags);


void __RPC_STUB ITVEMCastManager_put_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEMCastManager_INTERFACE_DEFINED__ */


#ifndef __ITVEMCastManager_Helper_INTERFACE_DEFINED__
#define __ITVEMCastManager_Helper_INTERFACE_DEFINED__

/* interface ITVEMCastManager_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVEMCastManager_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500232-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEMCastManager_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpString( 
            BSTR bstrDump) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateQueueThread( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE KillQueueThread( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PostToQueueThread( 
            UINT uiMsg,
            WPARAM wParam,
            LPARAM lParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPacketCounts( 
            /* [out] */ LONG *pCPackets,
            /* [out] */ LONG *pCPacketsDropped,
            /* [out] */ LONG *pCPacketsDroppedTotal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEMCastManager_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEMCastManager_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEMCastManager_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEMCastManager_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpString )( 
            ITVEMCastManager_Helper * This,
            BSTR bstrDump);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateQueueThread )( 
            ITVEMCastManager_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *KillQueueThread )( 
            ITVEMCastManager_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostToQueueThread )( 
            ITVEMCastManager_Helper * This,
            UINT uiMsg,
            WPARAM wParam,
            LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPacketCounts )( 
            ITVEMCastManager_Helper * This,
            /* [out] */ LONG *pCPackets,
            /* [out] */ LONG *pCPacketsDropped,
            /* [out] */ LONG *pCPacketsDroppedTotal);
        
        END_INTERFACE
    } ITVEMCastManager_HelperVtbl;

    interface ITVEMCastManager_Helper
    {
        CONST_VTBL struct ITVEMCastManager_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEMCastManager_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEMCastManager_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEMCastManager_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEMCastManager_Helper_DumpString(This,bstrDump)	\
    (This)->lpVtbl -> DumpString(This,bstrDump)

#define ITVEMCastManager_Helper_CreateQueueThread(This)	\
    (This)->lpVtbl -> CreateQueueThread(This)

#define ITVEMCastManager_Helper_KillQueueThread(This)	\
    (This)->lpVtbl -> KillQueueThread(This)

#define ITVEMCastManager_Helper_PostToQueueThread(This,uiMsg,wParam,lParam)	\
    (This)->lpVtbl -> PostToQueueThread(This,uiMsg,wParam,lParam)

#define ITVEMCastManager_Helper_GetPacketCounts(This,pCPackets,pCPacketsDropped,pCPacketsDroppedTotal)	\
    (This)->lpVtbl -> GetPacketCounts(This,pCPackets,pCPacketsDropped,pCPacketsDroppedTotal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Helper_DumpString_Proxy( 
    ITVEMCastManager_Helper * This,
    BSTR bstrDump);


void __RPC_STUB ITVEMCastManager_Helper_DumpString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Helper_CreateQueueThread_Proxy( 
    ITVEMCastManager_Helper * This);


void __RPC_STUB ITVEMCastManager_Helper_CreateQueueThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Helper_KillQueueThread_Proxy( 
    ITVEMCastManager_Helper * This);


void __RPC_STUB ITVEMCastManager_Helper_KillQueueThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Helper_PostToQueueThread_Proxy( 
    ITVEMCastManager_Helper * This,
    UINT uiMsg,
    WPARAM wParam,
    LPARAM lParam);


void __RPC_STUB ITVEMCastManager_Helper_PostToQueueThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastManager_Helper_GetPacketCounts_Proxy( 
    ITVEMCastManager_Helper * This,
    /* [out] */ LONG *pCPackets,
    /* [out] */ LONG *pCPacketsDropped,
    /* [out] */ LONG *pCPacketsDroppedTotal);


void __RPC_STUB ITVEMCastManager_Helper_GetPacketCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEMCastManager_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVEMCastCallback_INTERFACE_DEFINED__
#define __ITVEMCastCallback_INTERFACE_DEFINED__

/* interface ITVEMCastCallback */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEMCastCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500133-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEMCastCallback : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMCast( 
            ITVEMCast *pMCast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ProcessPacket( 
            unsigned char *pchBuffer,
            long cBytes,
            long lPacketId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PostPacket( 
            unsigned char *pchBuffer,
            long cBytes,
            long wPacketId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEMCastCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEMCastCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEMCastCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEMCastCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEMCastCallback * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEMCastCallback * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEMCastCallback * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEMCastCallback * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMCast )( 
            ITVEMCastCallback * This,
            ITVEMCast *pMCast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ProcessPacket )( 
            ITVEMCastCallback * This,
            unsigned char *pchBuffer,
            long cBytes,
            long lPacketId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostPacket )( 
            ITVEMCastCallback * This,
            unsigned char *pchBuffer,
            long cBytes,
            long wPacketId);
        
        END_INTERFACE
    } ITVEMCastCallbackVtbl;

    interface ITVEMCastCallback
    {
        CONST_VTBL struct ITVEMCastCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEMCastCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEMCastCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEMCastCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEMCastCallback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEMCastCallback_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEMCastCallback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEMCastCallback_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEMCastCallback_SetMCast(This,pMCast)	\
    (This)->lpVtbl -> SetMCast(This,pMCast)

#define ITVEMCastCallback_ProcessPacket(This,pchBuffer,cBytes,lPacketId)	\
    (This)->lpVtbl -> ProcessPacket(This,pchBuffer,cBytes,lPacketId)

#define ITVEMCastCallback_PostPacket(This,pchBuffer,cBytes,wPacketId)	\
    (This)->lpVtbl -> PostPacket(This,pchBuffer,cBytes,wPacketId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastCallback_SetMCast_Proxy( 
    ITVEMCastCallback * This,
    ITVEMCast *pMCast);


void __RPC_STUB ITVEMCastCallback_SetMCast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastCallback_ProcessPacket_Proxy( 
    ITVEMCastCallback * This,
    unsigned char *pchBuffer,
    long cBytes,
    long lPacketId);


void __RPC_STUB ITVEMCastCallback_ProcessPacket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEMCastCallback_PostPacket_Proxy( 
    ITVEMCastCallback * This,
    unsigned char *pchBuffer,
    long cBytes,
    long wPacketId);


void __RPC_STUB ITVEMCastCallback_PostPacket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEMCastCallback_INTERFACE_DEFINED__ */


#ifndef __ITVECBAnnc_INTERFACE_DEFINED__
#define __ITVECBAnnc_INTERFACE_DEFINED__

/* interface ITVECBAnnc */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVECBAnnc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500141-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVECBAnnc : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            BSTR bstrFileTrigAdapter,
            ITVEService *pService) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVECBAnncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVECBAnnc * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVECBAnnc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVECBAnnc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVECBAnnc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVECBAnnc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVECBAnnc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVECBAnnc * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ITVECBAnnc * This,
            BSTR bstrFileTrigAdapter,
            ITVEService *pService);
        
        END_INTERFACE
    } ITVECBAnncVtbl;

    interface ITVECBAnnc
    {
        CONST_VTBL struct ITVECBAnncVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVECBAnnc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVECBAnnc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVECBAnnc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVECBAnnc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVECBAnnc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVECBAnnc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVECBAnnc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVECBAnnc_Init(This,bstrFileTrigAdapter,pService)	\
    (This)->lpVtbl -> Init(This,bstrFileTrigAdapter,pService)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVECBAnnc_Init_Proxy( 
    ITVECBAnnc * This,
    BSTR bstrFileTrigAdapter,
    ITVEService *pService);


void __RPC_STUB ITVECBAnnc_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVECBAnnc_INTERFACE_DEFINED__ */


#ifndef __ITVECBTrig_INTERFACE_DEFINED__
#define __ITVECBTrig_INTERFACE_DEFINED__

/* interface ITVECBTrig */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVECBTrig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500142-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVECBTrig : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            ITVEVariation *pIVariation) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVECBTrigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVECBTrig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVECBTrig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVECBTrig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVECBTrig * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVECBTrig * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVECBTrig * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVECBTrig * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ITVECBTrig * This,
            ITVEVariation *pIVariation);
        
        END_INTERFACE
    } ITVECBTrigVtbl;

    interface ITVECBTrig
    {
        CONST_VTBL struct ITVECBTrigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVECBTrig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVECBTrig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVECBTrig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVECBTrig_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVECBTrig_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVECBTrig_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVECBTrig_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVECBTrig_Init(This,pIVariation)	\
    (This)->lpVtbl -> Init(This,pIVariation)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVECBTrig_Init_Proxy( 
    ITVECBTrig * This,
    ITVEVariation *pIVariation);


void __RPC_STUB ITVECBTrig_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVECBTrig_INTERFACE_DEFINED__ */


#ifndef __ITVECBFile_INTERFACE_DEFINED__
#define __ITVECBFile_INTERFACE_DEFINED__

/* interface ITVECBFile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVECBFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500143-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVECBFile : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            ITVEVariation *pIVariation,
            ITVEService *pIService) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVECBFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVECBFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVECBFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVECBFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVECBFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVECBFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVECBFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVECBFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ITVECBFile * This,
            ITVEVariation *pIVariation,
            ITVEService *pIService);
        
        END_INTERFACE
    } ITVECBFileVtbl;

    interface ITVECBFile
    {
        CONST_VTBL struct ITVECBFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVECBFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVECBFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVECBFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVECBFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVECBFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVECBFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVECBFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVECBFile_Init(This,pIVariation,pIService)	\
    (This)->lpVtbl -> Init(This,pIVariation,pIService)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVECBFile_Init_Proxy( 
    ITVECBFile * This,
    ITVEVariation *pIVariation,
    ITVEService *pIService);


void __RPC_STUB ITVECBFile_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVECBFile_INTERFACE_DEFINED__ */


#ifndef __ITVECBDummy_INTERFACE_DEFINED__
#define __ITVECBDummy_INTERFACE_DEFINED__

/* interface ITVECBDummy */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVECBDummy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500144-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVECBDummy : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            int i) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVECBDummyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVECBDummy * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVECBDummy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVECBDummy * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVECBDummy * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVECBDummy * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVECBDummy * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVECBDummy * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ITVECBDummy * This,
            int i);
        
        END_INTERFACE
    } ITVECBDummyVtbl;

    interface ITVECBDummy
    {
        CONST_VTBL struct ITVECBDummyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVECBDummy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVECBDummy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVECBDummy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVECBDummy_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVECBDummy_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVECBDummy_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVECBDummy_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVECBDummy_Init(This,i)	\
    (This)->lpVtbl -> Init(This,i)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVECBDummy_Init_Proxy( 
    ITVECBDummy * This,
    int i);


void __RPC_STUB ITVECBDummy_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVECBDummy_INTERFACE_DEFINED__ */


#ifndef __ITVEFile_INTERFACE_DEFINED__
#define __ITVEFile_INTERFACE_DEFINED__

/* interface ITVEFile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVEFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500151-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEFile : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitializeFile( 
            /* [in] */ ITVEVariation *pVaria,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsLoc,
            /* [in] */ DATE dateExpires) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitializePackage( 
            /* [in] */ ITVEVariation *pVaria,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsLoc,
            /* [in] */ DATE dateExpires) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pBstrDesc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR *pBstrLoc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpireTime( 
            /* [retval][out] */ DATE *pDateExpires) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsPackage( 
            /* [retval][out] */ BOOL *pfVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Variation( 
            /* [retval][out] */ ITVEVariation **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Service( 
            /* [retval][out] */ ITVEService **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveYourself( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpToBSTR( 
            /* [out] */ BSTR *pBstrDump) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVEFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVEFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVEFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVEFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitializeFile )( 
            ITVEFile * This,
            /* [in] */ ITVEVariation *pVaria,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsLoc,
            /* [in] */ DATE dateExpires);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitializePackage )( 
            ITVEFile * This,
            /* [in] */ ITVEVariation *pVaria,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsLoc,
            /* [in] */ DATE dateExpires);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITVEFile * This,
            /* [retval][out] */ BSTR *pBstrDesc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ITVEFile * This,
            /* [retval][out] */ BSTR *pBstrLoc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExpireTime )( 
            ITVEFile * This,
            /* [retval][out] */ DATE *pDateExpires);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPackage )( 
            ITVEFile * This,
            /* [retval][out] */ BOOL *pfVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Variation )( 
            ITVEFile * This,
            /* [retval][out] */ ITVEVariation **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Service )( 
            ITVEFile * This,
            /* [retval][out] */ ITVEService **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveYourself )( 
            ITVEFile * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToBSTR )( 
            ITVEFile * This,
            /* [out] */ BSTR *pBstrDump);
        
        END_INTERFACE
    } ITVEFileVtbl;

    interface ITVEFile
    {
        CONST_VTBL struct ITVEFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVEFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVEFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVEFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVEFile_InitializeFile(This,pVaria,bsName,bsLoc,dateExpires)	\
    (This)->lpVtbl -> InitializeFile(This,pVaria,bsName,bsLoc,dateExpires)

#define ITVEFile_InitializePackage(This,pVaria,bsName,bsLoc,dateExpires)	\
    (This)->lpVtbl -> InitializePackage(This,pVaria,bsName,bsLoc,dateExpires)

#define ITVEFile_get_Description(This,pBstrDesc)	\
    (This)->lpVtbl -> get_Description(This,pBstrDesc)

#define ITVEFile_get_Location(This,pBstrLoc)	\
    (This)->lpVtbl -> get_Location(This,pBstrLoc)

#define ITVEFile_get_ExpireTime(This,pDateExpires)	\
    (This)->lpVtbl -> get_ExpireTime(This,pDateExpires)

#define ITVEFile_get_IsPackage(This,pfVal)	\
    (This)->lpVtbl -> get_IsPackage(This,pfVal)

#define ITVEFile_get_Variation(This,pVal)	\
    (This)->lpVtbl -> get_Variation(This,pVal)

#define ITVEFile_get_Service(This,pVal)	\
    (This)->lpVtbl -> get_Service(This,pVal)

#define ITVEFile_RemoveYourself(This)	\
    (This)->lpVtbl -> RemoveYourself(This)

#define ITVEFile_DumpToBSTR(This,pBstrDump)	\
    (This)->lpVtbl -> DumpToBSTR(This,pBstrDump)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFile_InitializeFile_Proxy( 
    ITVEFile * This,
    /* [in] */ ITVEVariation *pVaria,
    /* [in] */ BSTR bsName,
    /* [in] */ BSTR bsLoc,
    /* [in] */ DATE dateExpires);


void __RPC_STUB ITVEFile_InitializeFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFile_InitializePackage_Proxy( 
    ITVEFile * This,
    /* [in] */ ITVEVariation *pVaria,
    /* [in] */ BSTR bsName,
    /* [in] */ BSTR bsLoc,
    /* [in] */ DATE dateExpires);


void __RPC_STUB ITVEFile_InitializePackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_Description_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ BSTR *pBstrDesc);


void __RPC_STUB ITVEFile_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_Location_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ BSTR *pBstrLoc);


void __RPC_STUB ITVEFile_get_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_ExpireTime_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ DATE *pDateExpires);


void __RPC_STUB ITVEFile_get_ExpireTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_IsPackage_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ BOOL *pfVal);


void __RPC_STUB ITVEFile_get_IsPackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_Variation_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ ITVEVariation **pVal);


void __RPC_STUB ITVEFile_get_Variation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFile_get_Service_Proxy( 
    ITVEFile * This,
    /* [retval][out] */ ITVEService **pVal);


void __RPC_STUB ITVEFile_get_Service_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFile_RemoveYourself_Proxy( 
    ITVEFile * This);


void __RPC_STUB ITVEFile_RemoveYourself_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFile_DumpToBSTR_Proxy( 
    ITVEFile * This,
    /* [out] */ BSTR *pBstrDump);


void __RPC_STUB ITVEFile_DumpToBSTR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEFile_INTERFACE_DEFINED__ */


#ifndef __ITVENavAid_INTERFACE_DEFINED__
#define __ITVENavAid_INTERFACE_DEFINED__

/* interface ITVENavAid */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVENavAid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500160-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVENavAid : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WebBrowserApp( 
            /* [in] */ IDispatch *pWebBrowser) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WebBrowserApp( 
            /* [retval][out] */ IDispatch **ppWebBrowser) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TVETriggerCtrl( 
            /* [retval][out] */ ITVETriggerCtrl **ppTriggerCtrl) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableAutoTriggering( 
            /* [in] */ long lAutoTriggers) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableAutoTriggering( 
            /* [retval][out] */ long *plAutoTriggers) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveVariation( 
            /* [retval][out] */ ITVEVariation **ppActiveVariation) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ActiveVariation( 
            /* [in] */ ITVEVariation *pActiveVariation) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TVEFeature( 
            /* [retval][out] */ ITVEFeature **ppTVEFeature) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CacheState( 
            /* [retval][out] */ BSTR *pbstrBuff) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CacheState( 
            /* [in] */ BSTR bstrBuff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavUsingTVETrigger( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ long lForceNav,
            /* [in] */ long lForceExec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecScript( 
            /* [in] */ BSTR bstrScript,
            /* [in] */ BSTR bstrLanguage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate( 
            /* [in] */ VARIANT *URL,
            /* [in] */ VARIANT *Flags,
            /* [in] */ VARIANT *TargetFrameName,
            /* [in] */ VARIANT *PostData,
            /* [in] */ VARIANT *Headers) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrTVEName( 
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrTVEURL( 
            /* [retval][out] */ BSTR *pbstrURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETune( 
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementNew( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementUpdated( 
            /* [in] */ ITVEEnhancement *pEnh,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementStarting( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEEnhancementExpired( 
            /* [in] */ ITVEEnhancement *pEnh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerNew( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerUpdated( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerExpired( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEPackage( 
            /* [in] */ NPKG_Mode engPkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEFile( 
            /* [in] */ NFLE_Mode engFileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUrlName,
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVEAuxInfo( 
            /* [in] */ NWHAT_Mode engAuxInfoMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lChangedFlags,
            /* [in] */ long lErrorLine) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyStatusTextChange( 
            BSTR Text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyProgressChange( 
            LONG Progress,
            LONG ProgressMax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyCommandStateChange( 
            LONG Command,
            VARIANT_BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDownloadBegin( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDownloadComplete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTitleChange( 
            BSTR Text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyPropertyChange( 
            BSTR szProperty) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyBeforeNavigate2( 
            IDispatch *pDisp,
            VARIANT *URL,
            VARIANT *Flags,
            VARIANT *TargetFrameName,
            VARIANT *PostData,
            VARIANT *Headers,
            VARIANT_BOOL *Cancel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyNewWindow2( 
            IDispatch **ppDisp,
            VARIANT_BOOL *Cancel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyNavigateComplete2( 
            IDispatch *pDisp,
            VARIANT *URL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDocumentComplete( 
            IDispatch *pDisp,
            VARIANT *URL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnQuit( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnVisible( 
            VARIANT_BOOL Visible) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnToolBar( 
            VARIANT_BOOL ToolBar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnMenuBar( 
            VARIANT_BOOL MenuBar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnStatusBar( 
            VARIANT_BOOL StatusBar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnFullScreen( 
            VARIANT_BOOL FullScreen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyOnTheaterMode( 
            VARIANT_BOOL TheaterMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVENavAidVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVENavAid * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVENavAid * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVENavAid * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVENavAid * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVENavAid * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVENavAid * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVENavAid * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WebBrowserApp )( 
            ITVENavAid * This,
            /* [in] */ IDispatch *pWebBrowser);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WebBrowserApp )( 
            ITVENavAid * This,
            /* [retval][out] */ IDispatch **ppWebBrowser);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TVETriggerCtrl )( 
            ITVENavAid * This,
            /* [retval][out] */ ITVETriggerCtrl **ppTriggerCtrl);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableAutoTriggering )( 
            ITVENavAid * This,
            /* [in] */ long lAutoTriggers);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableAutoTriggering )( 
            ITVENavAid * This,
            /* [retval][out] */ long *plAutoTriggers);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveVariation )( 
            ITVENavAid * This,
            /* [retval][out] */ ITVEVariation **ppActiveVariation);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ActiveVariation )( 
            ITVENavAid * This,
            /* [in] */ ITVEVariation *pActiveVariation);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TVEFeature )( 
            ITVENavAid * This,
            /* [retval][out] */ ITVEFeature **ppTVEFeature);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CacheState )( 
            ITVENavAid * This,
            /* [retval][out] */ BSTR *pbstrBuff);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CacheState )( 
            ITVENavAid * This,
            /* [in] */ BSTR bstrBuff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NavUsingTVETrigger )( 
            ITVENavAid * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ long lForceNav,
            /* [in] */ long lForceExec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecScript )( 
            ITVENavAid * This,
            /* [in] */ BSTR bstrScript,
            /* [in] */ BSTR bstrLanguage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Navigate )( 
            ITVENavAid * This,
            /* [in] */ VARIANT *URL,
            /* [in] */ VARIANT *Flags,
            /* [in] */ VARIANT *TargetFrameName,
            /* [in] */ VARIANT *PostData,
            /* [in] */ VARIANT *Headers);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrTVEName )( 
            ITVENavAid * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrTVEURL )( 
            ITVENavAid * This,
            /* [retval][out] */ BSTR *pbstrURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETune )( 
            ITVENavAid * This,
            /* [in] */ NTUN_Mode tuneMode,
            /* [in] */ ITVEService *pService,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIPAdapter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementNew )( 
            ITVENavAid * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementUpdated )( 
            ITVENavAid * This,
            /* [in] */ ITVEEnhancement *pEnh,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementStarting )( 
            ITVENavAid * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEEnhancementExpired )( 
            ITVENavAid * This,
            /* [in] */ ITVEEnhancement *pEnh);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerNew )( 
            ITVENavAid * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerUpdated )( 
            ITVENavAid * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerExpired )( 
            ITVENavAid * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEPackage )( 
            ITVENavAid * This,
            /* [in] */ NPKG_Mode engPkgMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUUID,
            /* [in] */ long cBytesTotal,
            /* [in] */ long cBytesReceived);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEFile )( 
            ITVENavAid * This,
            /* [in] */ NFLE_Mode engFileMode,
            /* [in] */ ITVEVariation *pVariation,
            /* [in] */ BSTR bstrUrlName,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVEAuxInfo )( 
            ITVENavAid * This,
            /* [in] */ NWHAT_Mode engAuxInfoMode,
            /* [in] */ BSTR bstrAuxInfoString,
            /* [in] */ long lChangedFlags,
            /* [in] */ long lErrorLine);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyStatusTextChange )( 
            ITVENavAid * This,
            BSTR Text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyProgressChange )( 
            ITVENavAid * This,
            LONG Progress,
            LONG ProgressMax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyCommandStateChange )( 
            ITVENavAid * This,
            LONG Command,
            VARIANT_BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDownloadBegin )( 
            ITVENavAid * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDownloadComplete )( 
            ITVENavAid * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTitleChange )( 
            ITVENavAid * This,
            BSTR Text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyPropertyChange )( 
            ITVENavAid * This,
            BSTR szProperty);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyBeforeNavigate2 )( 
            ITVENavAid * This,
            IDispatch *pDisp,
            VARIANT *URL,
            VARIANT *Flags,
            VARIANT *TargetFrameName,
            VARIANT *PostData,
            VARIANT *Headers,
            VARIANT_BOOL *Cancel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyNewWindow2 )( 
            ITVENavAid * This,
            IDispatch **ppDisp,
            VARIANT_BOOL *Cancel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyNavigateComplete2 )( 
            ITVENavAid * This,
            IDispatch *pDisp,
            VARIANT *URL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDocumentComplete )( 
            ITVENavAid * This,
            IDispatch *pDisp,
            VARIANT *URL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnQuit )( 
            ITVENavAid * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnVisible )( 
            ITVENavAid * This,
            VARIANT_BOOL Visible);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnToolBar )( 
            ITVENavAid * This,
            VARIANT_BOOL ToolBar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnMenuBar )( 
            ITVENavAid * This,
            VARIANT_BOOL MenuBar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnStatusBar )( 
            ITVENavAid * This,
            VARIANT_BOOL StatusBar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnFullScreen )( 
            ITVENavAid * This,
            VARIANT_BOOL FullScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyOnTheaterMode )( 
            ITVENavAid * This,
            VARIANT_BOOL TheaterMode);
        
        END_INTERFACE
    } ITVENavAidVtbl;

    interface ITVENavAid
    {
        CONST_VTBL struct ITVENavAidVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVENavAid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVENavAid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVENavAid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVENavAid_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVENavAid_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVENavAid_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVENavAid_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVENavAid_put_WebBrowserApp(This,pWebBrowser)	\
    (This)->lpVtbl -> put_WebBrowserApp(This,pWebBrowser)

#define ITVENavAid_get_WebBrowserApp(This,ppWebBrowser)	\
    (This)->lpVtbl -> get_WebBrowserApp(This,ppWebBrowser)

#define ITVENavAid_get_TVETriggerCtrl(This,ppTriggerCtrl)	\
    (This)->lpVtbl -> get_TVETriggerCtrl(This,ppTriggerCtrl)

#define ITVENavAid_put_EnableAutoTriggering(This,lAutoTriggers)	\
    (This)->lpVtbl -> put_EnableAutoTriggering(This,lAutoTriggers)

#define ITVENavAid_get_EnableAutoTriggering(This,plAutoTriggers)	\
    (This)->lpVtbl -> get_EnableAutoTriggering(This,plAutoTriggers)

#define ITVENavAid_get_ActiveVariation(This,ppActiveVariation)	\
    (This)->lpVtbl -> get_ActiveVariation(This,ppActiveVariation)

#define ITVENavAid_put_ActiveVariation(This,pActiveVariation)	\
    (This)->lpVtbl -> put_ActiveVariation(This,pActiveVariation)

#define ITVENavAid_get_TVEFeature(This,ppTVEFeature)	\
    (This)->lpVtbl -> get_TVEFeature(This,ppTVEFeature)

#define ITVENavAid_get_CacheState(This,pbstrBuff)	\
    (This)->lpVtbl -> get_CacheState(This,pbstrBuff)

#define ITVENavAid_put_CacheState(This,bstrBuff)	\
    (This)->lpVtbl -> put_CacheState(This,bstrBuff)

#define ITVENavAid_NavUsingTVETrigger(This,pTrigger,lForceNav,lForceExec)	\
    (This)->lpVtbl -> NavUsingTVETrigger(This,pTrigger,lForceNav,lForceExec)

#define ITVENavAid_ExecScript(This,bstrScript,bstrLanguage)	\
    (This)->lpVtbl -> ExecScript(This,bstrScript,bstrLanguage)

#define ITVENavAid_Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)	\
    (This)->lpVtbl -> Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)

#define ITVENavAid_get_CurrTVEName(This,pbstrName)	\
    (This)->lpVtbl -> get_CurrTVEName(This,pbstrName)

#define ITVENavAid_get_CurrTVEURL(This,pbstrURL)	\
    (This)->lpVtbl -> get_CurrTVEURL(This,pbstrURL)

#define ITVENavAid_NotifyTVETune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)	\
    (This)->lpVtbl -> NotifyTVETune(This,tuneMode,pService,bstrDescription,bstrIPAdapter)

#define ITVENavAid_NotifyTVEEnhancementNew(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementNew(This,pEnh)

#define ITVENavAid_NotifyTVEEnhancementUpdated(This,pEnh,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTVEEnhancementUpdated(This,pEnh,lChangedFlags)

#define ITVENavAid_NotifyTVEEnhancementStarting(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementStarting(This,pEnh)

#define ITVENavAid_NotifyTVEEnhancementExpired(This,pEnh)	\
    (This)->lpVtbl -> NotifyTVEEnhancementExpired(This,pEnh)

#define ITVENavAid_NotifyTVETriggerNew(This,pTrigger,fActive)	\
    (This)->lpVtbl -> NotifyTVETriggerNew(This,pTrigger,fActive)

#define ITVENavAid_NotifyTVETriggerUpdated(This,pTrigger,fActive,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTVETriggerUpdated(This,pTrigger,fActive,lChangedFlags)

#define ITVENavAid_NotifyTVETriggerExpired(This,pTrigger,fActive)	\
    (This)->lpVtbl -> NotifyTVETriggerExpired(This,pTrigger,fActive)

#define ITVENavAid_NotifyTVEPackage(This,engPkgMode,pVariation,bstrUUID,cBytesTotal,cBytesReceived)	\
    (This)->lpVtbl -> NotifyTVEPackage(This,engPkgMode,pVariation,bstrUUID,cBytesTotal,cBytesReceived)

#define ITVENavAid_NotifyTVEFile(This,engFileMode,pVariation,bstrUrlName,bstrFileName)	\
    (This)->lpVtbl -> NotifyTVEFile(This,engFileMode,pVariation,bstrUrlName,bstrFileName)

#define ITVENavAid_NotifyTVEAuxInfo(This,engAuxInfoMode,bstrAuxInfoString,lChangedFlags,lErrorLine)	\
    (This)->lpVtbl -> NotifyTVEAuxInfo(This,engAuxInfoMode,bstrAuxInfoString,lChangedFlags,lErrorLine)

#define ITVENavAid_NotifyStatusTextChange(This,Text)	\
    (This)->lpVtbl -> NotifyStatusTextChange(This,Text)

#define ITVENavAid_NotifyProgressChange(This,Progress,ProgressMax)	\
    (This)->lpVtbl -> NotifyProgressChange(This,Progress,ProgressMax)

#define ITVENavAid_NotifyCommandStateChange(This,Command,Enable)	\
    (This)->lpVtbl -> NotifyCommandStateChange(This,Command,Enable)

#define ITVENavAid_NotifyDownloadBegin(This)	\
    (This)->lpVtbl -> NotifyDownloadBegin(This)

#define ITVENavAid_NotifyDownloadComplete(This)	\
    (This)->lpVtbl -> NotifyDownloadComplete(This)

#define ITVENavAid_NotifyTitleChange(This,Text)	\
    (This)->lpVtbl -> NotifyTitleChange(This,Text)

#define ITVENavAid_NotifyPropertyChange(This,szProperty)	\
    (This)->lpVtbl -> NotifyPropertyChange(This,szProperty)

#define ITVENavAid_NotifyBeforeNavigate2(This,pDisp,URL,Flags,TargetFrameName,PostData,Headers,Cancel)	\
    (This)->lpVtbl -> NotifyBeforeNavigate2(This,pDisp,URL,Flags,TargetFrameName,PostData,Headers,Cancel)

#define ITVENavAid_NotifyNewWindow2(This,ppDisp,Cancel)	\
    (This)->lpVtbl -> NotifyNewWindow2(This,ppDisp,Cancel)

#define ITVENavAid_NotifyNavigateComplete2(This,pDisp,URL)	\
    (This)->lpVtbl -> NotifyNavigateComplete2(This,pDisp,URL)

#define ITVENavAid_NotifyDocumentComplete(This,pDisp,URL)	\
    (This)->lpVtbl -> NotifyDocumentComplete(This,pDisp,URL)

#define ITVENavAid_NotifyOnQuit(This)	\
    (This)->lpVtbl -> NotifyOnQuit(This)

#define ITVENavAid_NotifyOnVisible(This,Visible)	\
    (This)->lpVtbl -> NotifyOnVisible(This,Visible)

#define ITVENavAid_NotifyOnToolBar(This,ToolBar)	\
    (This)->lpVtbl -> NotifyOnToolBar(This,ToolBar)

#define ITVENavAid_NotifyOnMenuBar(This,MenuBar)	\
    (This)->lpVtbl -> NotifyOnMenuBar(This,MenuBar)

#define ITVENavAid_NotifyOnStatusBar(This,StatusBar)	\
    (This)->lpVtbl -> NotifyOnStatusBar(This,StatusBar)

#define ITVENavAid_NotifyOnFullScreen(This,FullScreen)	\
    (This)->lpVtbl -> NotifyOnFullScreen(This,FullScreen)

#define ITVENavAid_NotifyOnTheaterMode(This,TheaterMode)	\
    (This)->lpVtbl -> NotifyOnTheaterMode(This,TheaterMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVENavAid_put_WebBrowserApp_Proxy( 
    ITVENavAid * This,
    /* [in] */ IDispatch *pWebBrowser);


void __RPC_STUB ITVENavAid_put_WebBrowserApp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_WebBrowserApp_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ IDispatch **ppWebBrowser);


void __RPC_STUB ITVENavAid_get_WebBrowserApp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_TVETriggerCtrl_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ ITVETriggerCtrl **ppTriggerCtrl);


void __RPC_STUB ITVENavAid_get_TVETriggerCtrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVENavAid_put_EnableAutoTriggering_Proxy( 
    ITVENavAid * This,
    /* [in] */ long lAutoTriggers);


void __RPC_STUB ITVENavAid_put_EnableAutoTriggering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_EnableAutoTriggering_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ long *plAutoTriggers);


void __RPC_STUB ITVENavAid_get_EnableAutoTriggering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_ActiveVariation_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ ITVEVariation **ppActiveVariation);


void __RPC_STUB ITVENavAid_get_ActiveVariation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVENavAid_put_ActiveVariation_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVEVariation *pActiveVariation);


void __RPC_STUB ITVENavAid_put_ActiveVariation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_TVEFeature_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ ITVEFeature **ppTVEFeature);


void __RPC_STUB ITVENavAid_get_TVEFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_CacheState_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ BSTR *pbstrBuff);


void __RPC_STUB ITVENavAid_get_CacheState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVENavAid_put_CacheState_Proxy( 
    ITVENavAid * This,
    /* [in] */ BSTR bstrBuff);


void __RPC_STUB ITVENavAid_put_CacheState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NavUsingTVETrigger_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ long lForceNav,
    /* [in] */ long lForceExec);


void __RPC_STUB ITVENavAid_NavUsingTVETrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_ExecScript_Proxy( 
    ITVENavAid * This,
    /* [in] */ BSTR bstrScript,
    /* [in] */ BSTR bstrLanguage);


void __RPC_STUB ITVENavAid_ExecScript_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_Navigate_Proxy( 
    ITVENavAid * This,
    /* [in] */ VARIANT *URL,
    /* [in] */ VARIANT *Flags,
    /* [in] */ VARIANT *TargetFrameName,
    /* [in] */ VARIANT *PostData,
    /* [in] */ VARIANT *Headers);


void __RPC_STUB ITVENavAid_Navigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_CurrTVEName_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB ITVENavAid_get_CurrTVEName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_get_CurrTVEURL_Proxy( 
    ITVENavAid * This,
    /* [retval][out] */ BSTR *pbstrURL);


void __RPC_STUB ITVENavAid_get_CurrTVEURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVETune_Proxy( 
    ITVENavAid * This,
    /* [in] */ NTUN_Mode tuneMode,
    /* [in] */ ITVEService *pService,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIPAdapter);


void __RPC_STUB ITVENavAid_NotifyTVETune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEEnhancementNew_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVENavAid_NotifyTVEEnhancementNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEEnhancementUpdated_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVEEnhancement *pEnh,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVENavAid_NotifyTVEEnhancementUpdated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEEnhancementStarting_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVENavAid_NotifyTVEEnhancementStarting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEEnhancementExpired_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVEEnhancement *pEnh);


void __RPC_STUB ITVENavAid_NotifyTVEEnhancementExpired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVETriggerNew_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive);


void __RPC_STUB ITVENavAid_NotifyTVETriggerNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVETriggerUpdated_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVENavAid_NotifyTVETriggerUpdated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVETriggerExpired_Proxy( 
    ITVENavAid * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive);


void __RPC_STUB ITVENavAid_NotifyTVETriggerExpired_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEPackage_Proxy( 
    ITVENavAid * This,
    /* [in] */ NPKG_Mode engPkgMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrUUID,
    /* [in] */ long cBytesTotal,
    /* [in] */ long cBytesReceived);


void __RPC_STUB ITVENavAid_NotifyTVEPackage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEFile_Proxy( 
    ITVENavAid * This,
    /* [in] */ NFLE_Mode engFileMode,
    /* [in] */ ITVEVariation *pVariation,
    /* [in] */ BSTR bstrUrlName,
    /* [in] */ BSTR bstrFileName);


void __RPC_STUB ITVENavAid_NotifyTVEFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTVEAuxInfo_Proxy( 
    ITVENavAid * This,
    /* [in] */ NWHAT_Mode engAuxInfoMode,
    /* [in] */ BSTR bstrAuxInfoString,
    /* [in] */ long lChangedFlags,
    /* [in] */ long lErrorLine);


void __RPC_STUB ITVENavAid_NotifyTVEAuxInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyStatusTextChange_Proxy( 
    ITVENavAid * This,
    BSTR Text);


void __RPC_STUB ITVENavAid_NotifyStatusTextChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyProgressChange_Proxy( 
    ITVENavAid * This,
    LONG Progress,
    LONG ProgressMax);


void __RPC_STUB ITVENavAid_NotifyProgressChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyCommandStateChange_Proxy( 
    ITVENavAid * This,
    LONG Command,
    VARIANT_BOOL Enable);


void __RPC_STUB ITVENavAid_NotifyCommandStateChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyDownloadBegin_Proxy( 
    ITVENavAid * This);


void __RPC_STUB ITVENavAid_NotifyDownloadBegin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyDownloadComplete_Proxy( 
    ITVENavAid * This);


void __RPC_STUB ITVENavAid_NotifyDownloadComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyTitleChange_Proxy( 
    ITVENavAid * This,
    BSTR Text);


void __RPC_STUB ITVENavAid_NotifyTitleChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyPropertyChange_Proxy( 
    ITVENavAid * This,
    BSTR szProperty);


void __RPC_STUB ITVENavAid_NotifyPropertyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyBeforeNavigate2_Proxy( 
    ITVENavAid * This,
    IDispatch *pDisp,
    VARIANT *URL,
    VARIANT *Flags,
    VARIANT *TargetFrameName,
    VARIANT *PostData,
    VARIANT *Headers,
    VARIANT_BOOL *Cancel);


void __RPC_STUB ITVENavAid_NotifyBeforeNavigate2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyNewWindow2_Proxy( 
    ITVENavAid * This,
    IDispatch **ppDisp,
    VARIANT_BOOL *Cancel);


void __RPC_STUB ITVENavAid_NotifyNewWindow2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyNavigateComplete2_Proxy( 
    ITVENavAid * This,
    IDispatch *pDisp,
    VARIANT *URL);


void __RPC_STUB ITVENavAid_NotifyNavigateComplete2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyDocumentComplete_Proxy( 
    ITVENavAid * This,
    IDispatch *pDisp,
    VARIANT *URL);


void __RPC_STUB ITVENavAid_NotifyDocumentComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnQuit_Proxy( 
    ITVENavAid * This);


void __RPC_STUB ITVENavAid_NotifyOnQuit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnVisible_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL Visible);


void __RPC_STUB ITVENavAid_NotifyOnVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnToolBar_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL ToolBar);


void __RPC_STUB ITVENavAid_NotifyOnToolBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnMenuBar_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL MenuBar);


void __RPC_STUB ITVENavAid_NotifyOnMenuBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnStatusBar_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL StatusBar);


void __RPC_STUB ITVENavAid_NotifyOnStatusBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnFullScreen_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL FullScreen);


void __RPC_STUB ITVENavAid_NotifyOnFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NotifyOnTheaterMode_Proxy( 
    ITVENavAid * This,
    VARIANT_BOOL TheaterMode);


void __RPC_STUB ITVENavAid_NotifyOnTheaterMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVENavAid_INTERFACE_DEFINED__ */


#ifndef __ITVENavAid_NoVidCtl_INTERFACE_DEFINED__
#define __ITVENavAid_NoVidCtl_INTERFACE_DEFINED__

/* interface ITVENavAid_NoVidCtl */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVENavAid_NoVidCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500360-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVENavAid_NoVidCtl : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NoVidCtl_Supervisor( 
            /* [in] */ ITVESupervisor *pSuper) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NoVidCtl_Supervisor( 
            /* [retval][out] */ ITVESupervisor **ppSuper) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVENavAid_NoVidCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVENavAid_NoVidCtl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVENavAid_NoVidCtl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVENavAid_NoVidCtl * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NoVidCtl_Supervisor )( 
            ITVENavAid_NoVidCtl * This,
            /* [in] */ ITVESupervisor *pSuper);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NoVidCtl_Supervisor )( 
            ITVENavAid_NoVidCtl * This,
            /* [retval][out] */ ITVESupervisor **ppSuper);
        
        END_INTERFACE
    } ITVENavAid_NoVidCtlVtbl;

    interface ITVENavAid_NoVidCtl
    {
        CONST_VTBL struct ITVENavAid_NoVidCtlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVENavAid_NoVidCtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVENavAid_NoVidCtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVENavAid_NoVidCtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVENavAid_NoVidCtl_put_NoVidCtl_Supervisor(This,pSuper)	\
    (This)->lpVtbl -> put_NoVidCtl_Supervisor(This,pSuper)

#define ITVENavAid_NoVidCtl_get_NoVidCtl_Supervisor(This,ppSuper)	\
    (This)->lpVtbl -> get_NoVidCtl_Supervisor(This,ppSuper)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NoVidCtl_put_NoVidCtl_Supervisor_Proxy( 
    ITVENavAid_NoVidCtl * This,
    /* [in] */ ITVESupervisor *pSuper);


void __RPC_STUB ITVENavAid_NoVidCtl_put_NoVidCtl_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVENavAid_NoVidCtl_get_NoVidCtl_Supervisor_Proxy( 
    ITVENavAid_NoVidCtl * This,
    /* [retval][out] */ ITVESupervisor **ppSuper);


void __RPC_STUB ITVENavAid_NoVidCtl_get_NoVidCtl_Supervisor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVENavAid_NoVidCtl_INTERFACE_DEFINED__ */


#ifndef __ITVENavAid_Helper_INTERFACE_DEFINED__
#define __ITVENavAid_Helper_INTERFACE_DEFINED__

/* interface ITVENavAid_Helper */
/* [unique][helpstring][dual][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVENavAid_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500260-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVENavAid_Helper : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LocateVidAndTriggerCtrls( 
            /* [out] */ IDispatch **pVidCtrl,
            /* [out] */ IDispatch **pTrigCtrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTVETriggerUpdated_XProxy( 
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReInitCurrNavState( 
            /* [in] */ long lReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVENavAid_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVENavAid_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVENavAid_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVENavAid_Helper * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LocateVidAndTriggerCtrls )( 
            ITVENavAid_Helper * This,
            /* [out] */ IDispatch **pVidCtrl,
            /* [out] */ IDispatch **pTrigCtrl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTVETriggerUpdated_XProxy )( 
            ITVENavAid_Helper * This,
            /* [in] */ ITVETrigger *pTrigger,
            /* [in] */ BOOL fActive,
            /* [in] */ long lChangedFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReInitCurrNavState )( 
            ITVENavAid_Helper * This,
            /* [in] */ long lReserved);
        
        END_INTERFACE
    } ITVENavAid_HelperVtbl;

    interface ITVENavAid_Helper
    {
        CONST_VTBL struct ITVENavAid_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVENavAid_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVENavAid_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVENavAid_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVENavAid_Helper_LocateVidAndTriggerCtrls(This,pVidCtrl,pTrigCtrl)	\
    (This)->lpVtbl -> LocateVidAndTriggerCtrls(This,pVidCtrl,pTrigCtrl)

#define ITVENavAid_Helper_NotifyTVETriggerUpdated_XProxy(This,pTrigger,fActive,lChangedFlags)	\
    (This)->lpVtbl -> NotifyTVETriggerUpdated_XProxy(This,pTrigger,fActive,lChangedFlags)

#define ITVENavAid_Helper_ReInitCurrNavState(This,lReserved)	\
    (This)->lpVtbl -> ReInitCurrNavState(This,lReserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_Helper_LocateVidAndTriggerCtrls_Proxy( 
    ITVENavAid_Helper * This,
    /* [out] */ IDispatch **pVidCtrl,
    /* [out] */ IDispatch **pTrigCtrl);


void __RPC_STUB ITVENavAid_Helper_LocateVidAndTriggerCtrls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_Helper_NotifyTVETriggerUpdated_XProxy_Proxy( 
    ITVENavAid_Helper * This,
    /* [in] */ ITVETrigger *pTrigger,
    /* [in] */ BOOL fActive,
    /* [in] */ long lChangedFlags);


void __RPC_STUB ITVENavAid_Helper_NotifyTVETriggerUpdated_XProxy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVENavAid_Helper_ReInitCurrNavState_Proxy( 
    ITVENavAid_Helper * This,
    /* [in] */ long lReserved);


void __RPC_STUB ITVENavAid_Helper_ReInitCurrNavState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVENavAid_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVEFilter_INTERFACE_DEFINED__
#define __ITVEFilter_INTERFACE_DEFINED__

/* interface ITVEFilter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITVEFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500180-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEFilter : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupervisorPunk( 
            /* [retval][out] */ IUnknown **ppSuperPunk) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAdapterAddress( 
            /* [retval][out] */ BSTR *pbstrIPAddr) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IPAdapterAddress( 
            /* [in] */ BSTR bstrIPAddr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StationID( 
            /* [retval][out] */ BSTR *pbstrStationID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StationID( 
            /* [in] */ BSTR bstrStationID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MulticastList( 
            /* [retval][out] */ BSTR *pbstrMulticastList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdapterDescription( 
            /* [retval][out] */ BSTR *pbstrAdapterDescription) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReTune( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HaltFlags( 
            /* [retval][out] */ LONG *plGrfHaltFlags) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HaltFlags( 
            /* [in] */ LONG lGrfHaltFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseCCBytePair( 
            /* [in] */ LONG lByteType,
            /* [in] */ BYTE byte1,
            /* [in] */ BYTE byte2) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IPSinkAdapterAddress( 
            /* [retval][out] */ BSTR *pbstrIPAddr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVEFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEFilter * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupervisorPunk )( 
            ITVEFilter * This,
            /* [retval][out] */ IUnknown **ppSuperPunk);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAdapterAddress )( 
            ITVEFilter * This,
            /* [retval][out] */ BSTR *pbstrIPAddr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IPAdapterAddress )( 
            ITVEFilter * This,
            /* [in] */ BSTR bstrIPAddr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StationID )( 
            ITVEFilter * This,
            /* [retval][out] */ BSTR *pbstrStationID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StationID )( 
            ITVEFilter * This,
            /* [in] */ BSTR bstrStationID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MulticastList )( 
            ITVEFilter * This,
            /* [retval][out] */ BSTR *pbstrMulticastList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AdapterDescription )( 
            ITVEFilter * This,
            /* [retval][out] */ BSTR *pbstrAdapterDescription);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReTune )( 
            ITVEFilter * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HaltFlags )( 
            ITVEFilter * This,
            /* [retval][out] */ LONG *plGrfHaltFlags);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HaltFlags )( 
            ITVEFilter * This,
            /* [in] */ LONG lGrfHaltFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ParseCCBytePair )( 
            ITVEFilter * This,
            /* [in] */ LONG lByteType,
            /* [in] */ BYTE byte1,
            /* [in] */ BYTE byte2);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPSinkAdapterAddress )( 
            ITVEFilter * This,
            /* [retval][out] */ BSTR *pbstrIPAddr);
        
        END_INTERFACE
    } ITVEFilterVtbl;

    interface ITVEFilter
    {
        CONST_VTBL struct ITVEFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVEFilter_get_SupervisorPunk(This,ppSuperPunk)	\
    (This)->lpVtbl -> get_SupervisorPunk(This,ppSuperPunk)

#define ITVEFilter_get_IPAdapterAddress(This,pbstrIPAddr)	\
    (This)->lpVtbl -> get_IPAdapterAddress(This,pbstrIPAddr)

#define ITVEFilter_put_IPAdapterAddress(This,bstrIPAddr)	\
    (This)->lpVtbl -> put_IPAdapterAddress(This,bstrIPAddr)

#define ITVEFilter_get_StationID(This,pbstrStationID)	\
    (This)->lpVtbl -> get_StationID(This,pbstrStationID)

#define ITVEFilter_put_StationID(This,bstrStationID)	\
    (This)->lpVtbl -> put_StationID(This,bstrStationID)

#define ITVEFilter_get_MulticastList(This,pbstrMulticastList)	\
    (This)->lpVtbl -> get_MulticastList(This,pbstrMulticastList)

#define ITVEFilter_get_AdapterDescription(This,pbstrAdapterDescription)	\
    (This)->lpVtbl -> get_AdapterDescription(This,pbstrAdapterDescription)

#define ITVEFilter_ReTune(This)	\
    (This)->lpVtbl -> ReTune(This)

#define ITVEFilter_get_HaltFlags(This,plGrfHaltFlags)	\
    (This)->lpVtbl -> get_HaltFlags(This,plGrfHaltFlags)

#define ITVEFilter_put_HaltFlags(This,lGrfHaltFlags)	\
    (This)->lpVtbl -> put_HaltFlags(This,lGrfHaltFlags)

#define ITVEFilter_ParseCCBytePair(This,lByteType,byte1,byte2)	\
    (This)->lpVtbl -> ParseCCBytePair(This,lByteType,byte1,byte2)

#define ITVEFilter_get_IPSinkAdapterAddress(This,pbstrIPAddr)	\
    (This)->lpVtbl -> get_IPSinkAdapterAddress(This,pbstrIPAddr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_SupervisorPunk_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ IUnknown **ppSuperPunk);


void __RPC_STUB ITVEFilter_get_SupervisorPunk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_IPAdapterAddress_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ BSTR *pbstrIPAddr);


void __RPC_STUB ITVEFilter_get_IPAdapterAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEFilter_put_IPAdapterAddress_Proxy( 
    ITVEFilter * This,
    /* [in] */ BSTR bstrIPAddr);


void __RPC_STUB ITVEFilter_put_IPAdapterAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_StationID_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ BSTR *pbstrStationID);


void __RPC_STUB ITVEFilter_get_StationID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEFilter_put_StationID_Proxy( 
    ITVEFilter * This,
    /* [in] */ BSTR bstrStationID);


void __RPC_STUB ITVEFilter_put_StationID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_MulticastList_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ BSTR *pbstrMulticastList);


void __RPC_STUB ITVEFilter_get_MulticastList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_AdapterDescription_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ BSTR *pbstrAdapterDescription);


void __RPC_STUB ITVEFilter_get_AdapterDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFilter_ReTune_Proxy( 
    ITVEFilter * This);


void __RPC_STUB ITVEFilter_ReTune_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_HaltFlags_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ LONG *plGrfHaltFlags);


void __RPC_STUB ITVEFilter_get_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVEFilter_put_HaltFlags_Proxy( 
    ITVEFilter * This,
    /* [in] */ LONG lGrfHaltFlags);


void __RPC_STUB ITVEFilter_put_HaltFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVEFilter_ParseCCBytePair_Proxy( 
    ITVEFilter * This,
    /* [in] */ LONG lByteType,
    /* [in] */ BYTE byte1,
    /* [in] */ BYTE byte2);


void __RPC_STUB ITVEFilter_ParseCCBytePair_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVEFilter_get_IPSinkAdapterAddress_Proxy( 
    ITVEFilter * This,
    /* [retval][out] */ BSTR *pbstrIPAddr);


void __RPC_STUB ITVEFilter_get_IPSinkAdapterAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVEFilter_INTERFACE_DEFINED__ */


#ifndef __ITVEFilter_Helper_INTERFACE_DEFINED__
#define __ITVEFilter_Helper_INTERFACE_DEFINED__

/* interface ITVEFilter_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVEFilter_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500280-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVEFilter_Helper : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITVEFilter_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVEFilter_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVEFilter_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVEFilter_Helper * This);
        
        END_INTERFACE
    } ITVEFilter_HelperVtbl;

    interface ITVEFilter_Helper
    {
        CONST_VTBL struct ITVEFilter_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVEFilter_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVEFilter_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVEFilter_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVEFilter_Helper_INTERFACE_DEFINED__ */


#ifndef __ITVETriggerCtrl_INTERFACE_DEFINED__
#define __ITVETriggerCtrl_INTERFACE_DEFINED__

/* interface ITVETriggerCtrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVETriggerCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500190-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETriggerCtrl : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_enabled( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_enabled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_sourceID( 
            /* [retval][out] */ BSTR *pbstrID) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_releasable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_releasable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_backChannel( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_contentLevel( 
            /* [retval][out] */ double *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETriggerCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETriggerCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETriggerCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETriggerCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVETriggerCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVETriggerCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVETriggerCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVETriggerCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_enabled )( 
            ITVETriggerCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_enabled )( 
            ITVETriggerCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_sourceID )( 
            ITVETriggerCtrl * This,
            /* [retval][out] */ BSTR *pbstrID);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_releasable )( 
            ITVETriggerCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_releasable )( 
            ITVETriggerCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_backChannel )( 
            ITVETriggerCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_contentLevel )( 
            ITVETriggerCtrl * This,
            /* [retval][out] */ double *pVal);
        
        END_INTERFACE
    } ITVETriggerCtrlVtbl;

    interface ITVETriggerCtrl
    {
        CONST_VTBL struct ITVETriggerCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETriggerCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETriggerCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETriggerCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETriggerCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITVETriggerCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITVETriggerCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITVETriggerCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITVETriggerCtrl_put_enabled(This,newVal)	\
    (This)->lpVtbl -> put_enabled(This,newVal)

#define ITVETriggerCtrl_get_enabled(This,pVal)	\
    (This)->lpVtbl -> get_enabled(This,pVal)

#define ITVETriggerCtrl_get_sourceID(This,pbstrID)	\
    (This)->lpVtbl -> get_sourceID(This,pbstrID)

#define ITVETriggerCtrl_put_releasable(This,newVal)	\
    (This)->lpVtbl -> put_releasable(This,newVal)

#define ITVETriggerCtrl_get_releasable(This,pVal)	\
    (This)->lpVtbl -> get_releasable(This,pVal)

#define ITVETriggerCtrl_get_backChannel(This,pVal)	\
    (This)->lpVtbl -> get_backChannel(This,pVal)

#define ITVETriggerCtrl_get_contentLevel(This,pVal)	\
    (This)->lpVtbl -> get_contentLevel(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_put_enabled_Proxy( 
    ITVETriggerCtrl * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITVETriggerCtrl_put_enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_get_enabled_Proxy( 
    ITVETriggerCtrl * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVETriggerCtrl_get_enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_get_sourceID_Proxy( 
    ITVETriggerCtrl * This,
    /* [retval][out] */ BSTR *pbstrID);


void __RPC_STUB ITVETriggerCtrl_get_sourceID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_put_releasable_Proxy( 
    ITVETriggerCtrl * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITVETriggerCtrl_put_releasable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_get_releasable_Proxy( 
    ITVETriggerCtrl * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVETriggerCtrl_get_releasable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_get_backChannel_Proxy( 
    ITVETriggerCtrl * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITVETriggerCtrl_get_backChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_get_contentLevel_Proxy( 
    ITVETriggerCtrl * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITVETriggerCtrl_get_contentLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETriggerCtrl_INTERFACE_DEFINED__ */


#ifndef __ITVETriggerCtrl_Helper_INTERFACE_DEFINED__
#define __ITVETriggerCtrl_Helper_INTERFACE_DEFINED__

/* interface ITVETriggerCtrl_Helper */
/* [unique][helpstring][hidden][uuid][object] */ 


EXTERN_C const IID IID_ITVETriggerCtrl_Helper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05500191-FAA5-4df9-8246-BFC23AC5CEA8")
    ITVETriggerCtrl_Helper : public IUnknown
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_sourceID( 
            /* [in] */ BSTR pSourceUUID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TopLevelPage( 
            /* [retval][out] */ BSTR *pURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVETriggerCtrl_HelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVETriggerCtrl_Helper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVETriggerCtrl_Helper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVETriggerCtrl_Helper * This);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_sourceID )( 
            ITVETriggerCtrl_Helper * This,
            /* [in] */ BSTR pSourceUUID);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopLevelPage )( 
            ITVETriggerCtrl_Helper * This,
            /* [retval][out] */ BSTR *pURL);
        
        END_INTERFACE
    } ITVETriggerCtrl_HelperVtbl;

    interface ITVETriggerCtrl_Helper
    {
        CONST_VTBL struct ITVETriggerCtrl_HelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVETriggerCtrl_Helper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITVETriggerCtrl_Helper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITVETriggerCtrl_Helper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITVETriggerCtrl_Helper_put_sourceID(This,pSourceUUID)	\
    (This)->lpVtbl -> put_sourceID(This,pSourceUUID)

#define ITVETriggerCtrl_Helper_get_TopLevelPage(This,pURL)	\
    (This)->lpVtbl -> get_TopLevelPage(This,pURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_Helper_put_sourceID_Proxy( 
    ITVETriggerCtrl_Helper * This,
    /* [in] */ BSTR pSourceUUID);


void __RPC_STUB ITVETriggerCtrl_Helper_put_sourceID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITVETriggerCtrl_Helper_get_TopLevelPage_Proxy( 
    ITVETriggerCtrl_Helper * This,
    /* [retval][out] */ BSTR *pURL);


void __RPC_STUB ITVETriggerCtrl_Helper_get_TopLevelPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVETriggerCtrl_Helper_INTERFACE_DEFINED__ */



#ifndef __MSTvELib_LIBRARY_DEFINED__
#define __MSTvELib_LIBRARY_DEFINED__

/* library MSTvELib */
/* [helpstring][version][uuid] */ 

typedef 
enum NENH_grfDiff
    {	NENH_grfNone	= 0,
	NENH_grfDescription	= 0x1,
	NENH_grfIsPrimary	= 0x2,
	NENH_grfProtocolVersion	= 0x4,
	NENH_grfSessionUserName	= 0x8,
	NENH_grfSessionId	= 0x10,
	NENH_grfSessionVersion	= 0x20,
	NENH_grfSessionIPAddress	= 0x40,
	NENH_grfSessionName	= 0x80,
	NENH_grfEmailAddresses	= 0x100,
	NENH_grfPhoneNumbers	= 0x200,
	NENH_grfUUID	= 0x400,
	NENH_grfStartTime	= 0x800,
	NENH_grfStopTime	= 0x1000,
	NENH_grfType	= 0x2000,
	NENH_grfTveType	= 0x4000,
	NENH_grfTveSize	= 0x8000,
	NENH_grfTveLevel	= 0x10000,
	NENH_grfAttributes	= 0x20000,
	NENH_grfRest	= 0x40000,
	NENH_grfVariationAdded	= 0x80000,
	NENH_grfVariationRemoved	= 0x100000,
	NENH_grfDescriptionURI	= 0x200000,
	NENH_grfSomeVarIP	= 0x400000,
	NENH_grfSomeVarText	= 0x800000,
	NENH_grfSomeVarBandwidth	= 0x1000000,
	NENH_grfSomeVarLanguages	= 0x2000000,
	NENH_grfSomeVarAttribute	= 0x4000000,
	NENH_grfUnused	= 0x8000000,
	NENH_grfSAPVersion	= 0x10000000,
	NENH_grfSAPAddressType	= 0x20000000,
	NENH_grfSAPOther	= 0x40000000,
	NENH_grfSAPEncryptComp	= 0x80000000,
	NENH_grfAnyIP	= NENH_grfSomeVarIP | NENH_grfVariationAdded | NENH_grfVariationRemoved,
	NENH_grfAll	= (NENH_grfSomeVarAttribute << 1) - 1
    } 	NENH_grfDiff;

typedef 
enum NVAR_grfDiff
    {	NVAR_grfNone	= 0,
	NVAR_grfDescription	= 0x1,
	NVAR_grfMediaName	= 0x2,
	NVAR_grfMediaTitle	= 0x4,
	NVAR_grfFilePort	= 0x8,
	NVAR_grfFileIPAddress	= 0x10,
	NVAR_grfFileIPAdapter	= 0x20,
	NVAR_grfTriggerPort	= 0x40,
	NVAR_grfTriggerIPAddress	= 0x80,
	NVAR_grfTriggerIPAdapter	= 0x100,
	NVAR_grfAttributes	= 0x200,
	NVAR_grfLanguages	= 0x400,
	NVAR_grfBandwidth	= 0x800,
	NVAR_grfBandwidthInfo	= 0x1000,
	NVAR_grfRest	= 0x2000,
	NVAR_grfAnyIP	= NVAR_grfFilePort | NVAR_grfFileIPAddress | NVAR_grfFileIPAdapter | NVAR_grfTriggerPort | NVAR_grfTriggerIPAddress | NVAR_grfTriggerIPAdapter,
	NVAR_grfAnyText	= NVAR_grfDescription | NVAR_grfMediaName | NVAR_grfMediaTitle,
	NVAR_grfAnyBandwidth	= NVAR_grfBandwidth | NVAR_grfBandwidthInfo,
	NVAR_grfAnyAttribute	= NVAR_grfAttributes | NVAR_grfRest,
	NVAR_grfAll	= (NVAR_grfRest << 1) - 1
    } 	NVAR_grfDiff;

typedef 
enum NTRK_grfDiff
    {	NTRK_grfNone	= 0,
	NTRK_grfURL	= 0x1,
	NTRK_grfName	= 0x2,
	NTRK_grfScript	= 0x4,
	NTRK_grfDate	= 0x8,
	NTRK_grfTVELevel	= 0x10,
	NTRK_grfExpired	= 0x20,
	NTRK_grfRest	= 0x40,
	NTRK_grfAll	= (NTRK_grfRest << 1) - 1
    } 	NTRK_grfDiff;

typedef 
enum NFLT_grfHaltFlags
    {	NFLT_grfNone	= 0,
	NFLT_grfTA_Listen	= 0x1,
	NFLT_grfTA_Decode	= 0x2,
	NFLT_grfTA_Parse	= 0x4,
	NFLT_grfTB_AnncListen	= 0x10,
	NFLT_grfTB_AnncDecode	= 0x20,
	NFLT_grfTB_AnncParse	= 0x40,
	NFLT_grfTB_TrigListen	= 0x100,
	NFLT_grfTB_TrigDecode	= 0x200,
	NFLT_grfTB_TrigParse	= 0x400,
	NFLT_grfTB_DataListen	= 0x1000,
	NFLT_grfTB_DataDecode	= 0x2000,
	NFLT_grfTB_DataParse	= 0x4000,
	NFLT_grf_ExpireQueue	= 0x10000,
	NFLT_grf_Extra1	= 0x100000,
	NFLT_grf_Extra2	= 0x200000,
	NFLT_grf_Extra3	= 0x400000,
	NFLT_grf_Extra4	= 0x800000
    } 	NFLT_grfHaltFlags;


EXTERN_C const IID LIBID_MSTvELib;

#ifndef ___ITVEEvents_DISPINTERFACE_DEFINED__
#define ___ITVEEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITVEEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITVEEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("05500000-FAA5-4df9-8246-BFC23AC5CEA8")
    _ITVEEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITVEEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITVEEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITVEEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITVEEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITVEEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITVEEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITVEEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITVEEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITVEEventsVtbl;

    interface _ITVEEvents
    {
        CONST_VTBL struct _ITVEEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITVEEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITVEEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITVEEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITVEEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITVEEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITVEEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITVEEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITVEEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVETrigger;

#ifdef __cplusplus

class DECLSPEC_UUID("05500001-FAA5-4df9-8246-BFC23AC5CEA8")
TVETrigger;
#endif

EXTERN_C const CLSID CLSID_TVETrack;

#ifdef __cplusplus

class DECLSPEC_UUID("05500002-FAA5-4df9-8246-BFC23AC5CEA8")
TVETrack;
#endif

EXTERN_C const CLSID CLSID_TVEVariation;

#ifdef __cplusplus

class DECLSPEC_UUID("05500003-FAA5-4df9-8246-BFC23AC5CEA8")
TVEVariation;
#endif

EXTERN_C const CLSID CLSID_TVEEnhancement;

#ifdef __cplusplus

class DECLSPEC_UUID("05500004-FAA5-4df9-8246-BFC23AC5CEA8")
TVEEnhancement;
#endif

EXTERN_C const CLSID CLSID_TVEEnhancements;

#ifdef __cplusplus

class DECLSPEC_UUID("05500014-FAA5-4df9-8246-BFC23AC5CEA8")
TVEEnhancements;
#endif

EXTERN_C const CLSID CLSID_TVEService;

#ifdef __cplusplus

class DECLSPEC_UUID("05500005-FAA5-4df9-8246-BFC23AC5CEA8")
TVEService;
#endif

EXTERN_C const CLSID CLSID_TVEFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("05500025-FAA5-4df9-8246-BFC23AC5CEA8")
TVEFeature;
#endif

EXTERN_C const CLSID CLSID_TVEServices;

#ifdef __cplusplus

class DECLSPEC_UUID("05500015-FAA5-4df9-8246-BFC23AC5CEA8")
TVEServices;
#endif

EXTERN_C const CLSID CLSID_TVESupervisor;

#ifdef __cplusplus

class DECLSPEC_UUID("05500006-FAA5-4df9-8246-BFC23AC5CEA8")
TVESupervisor;
#endif

EXTERN_C const CLSID CLSID_TVEAttrMap;

#ifdef __cplusplus

class DECLSPEC_UUID("05500021-FAA5-4df9-8246-BFC23AC5CEA8")
TVEAttrMap;
#endif

EXTERN_C const CLSID CLSID_TVEAttrTimeQ;

#ifdef __cplusplus

class DECLSPEC_UUID("05500022-FAA5-4df9-8246-BFC23AC5CEA8")
TVEAttrTimeQ;
#endif

EXTERN_C const CLSID CLSID_TVEMCast;

#ifdef __cplusplus

class DECLSPEC_UUID("05500030-FAA5-4df9-8246-BFC23AC5CEA8")
TVEMCast;
#endif

EXTERN_C const CLSID CLSID_TVEMCasts;

#ifdef __cplusplus

class DECLSPEC_UUID("05500031-FAA5-4df9-8246-BFC23AC5CEA8")
TVEMCasts;
#endif

EXTERN_C const CLSID CLSID_TVEMCastManager;

#ifdef __cplusplus

class DECLSPEC_UUID("05500032-FAA5-4df9-8246-BFC23AC5CEA8")
TVEMCastManager;
#endif

EXTERN_C const CLSID CLSID_TVEMCastCallback;

#ifdef __cplusplus

class DECLSPEC_UUID("05500040-FAA5-4df9-8246-BFC23AC5CEA8")
TVEMCastCallback;
#endif

EXTERN_C const CLSID CLSID_TVECBAnnc;

#ifdef __cplusplus

class DECLSPEC_UUID("05500041-FAA5-4df9-8246-BFC23AC5CEA8")
TVECBAnnc;
#endif

EXTERN_C const CLSID CLSID_TVECBTrig;

#ifdef __cplusplus

class DECLSPEC_UUID("05500042-FAA5-4df9-8246-BFC23AC5CEA8")
TVECBTrig;
#endif

EXTERN_C const CLSID CLSID_TVECBFile;

#ifdef __cplusplus

class DECLSPEC_UUID("05500043-FAA5-4df9-8246-BFC23AC5CEA8")
TVECBFile;
#endif

EXTERN_C const CLSID CLSID_TVECBDummy;

#ifdef __cplusplus

class DECLSPEC_UUID("05500049-FAA5-4df9-8246-BFC23AC5CEA8")
TVECBDummy;
#endif

EXTERN_C const CLSID CLSID_TVEFile;

#ifdef __cplusplus

class DECLSPEC_UUID("05500050-FAA5-4df9-8246-BFC23AC5CEA8")
TVEFile;
#endif

EXTERN_C const CLSID CLSID_TVENavAid;

#ifdef __cplusplus

class DECLSPEC_UUID("05500070-FAA5-4df9-8246-BFC23AC5CEA8")
TVENavAid;
#endif

EXTERN_C const CLSID CLSID_TVEFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("05500080-FAA5-4df9-8246-BFC23AC5CEA8")
TVEFilter;
#endif

#ifndef ___ITVETriggerCtrlEvents_DISPINTERFACE_DEFINED__
#define ___ITVETriggerCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITVETriggerCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITVETriggerCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("05500091-FAA5-4df9-8246-BFC23AC5CEA8")
    _ITVETriggerCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITVETriggerCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITVETriggerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITVETriggerCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITVETriggerCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITVETriggerCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITVETriggerCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITVETriggerCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITVETriggerCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITVETriggerCtrlEventsVtbl;

    interface _ITVETriggerCtrlEvents
    {
        CONST_VTBL struct _ITVETriggerCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITVETriggerCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITVETriggerCtrlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITVETriggerCtrlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITVETriggerCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITVETriggerCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITVETriggerCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITVETriggerCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITVETriggerCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVETriggerCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("05500090-FAA5-4df9-8246-BFC23AC5CEA8")
TVETriggerCtrl;
#endif
#endif /* __MSTvELib_LIBRARY_DEFINED__ */

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


