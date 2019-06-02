
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for medparam.idl:
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

#ifndef __medparam_h__
#define __medparam_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMediaParamInfo_FWD_DEFINED__
#define __IMediaParamInfo_FWD_DEFINED__
typedef interface IMediaParamInfo IMediaParamInfo;
#endif 	/* __IMediaParamInfo_FWD_DEFINED__ */


#ifndef __IMediaParams_FWD_DEFINED__
#define __IMediaParams_FWD_DEFINED__
typedef interface IMediaParams IMediaParams;
#endif 	/* __IMediaParams_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "strmif.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_medparam_0000 */
/* [local] */ 

typedef float MP_DATA;

typedef 
enum _MP_Type
    {	MPT_INT	= 0,
	MPT_FLOAT	= MPT_INT + 1,
	MPT_BOOL	= MPT_FLOAT + 1,
	MPT_ENUM	= MPT_BOOL + 1,
	MPT_MAX	= MPT_ENUM + 1
    } 	MP_TYPE;

#define	MPBOOL_TRUE	( 1 )

#define	MPBOOL_FALSE	( 0 )

typedef 
enum _MP_CURVE_TYPE
    {	MP_CURVE_JUMP	= 0x1,
	MP_CURVE_LINEAR	= 0x2,
	MP_CURVE_SQUARE	= 0x4,
	MP_CURVE_INVSQUARE	= 0x8,
	MP_CURVE_SINE	= 0x10
    } 	MP_CURVE_TYPE;

typedef DWORD MP_CAPS;

#define	MP_CAPS_CURVE_JUMP	( MP_CURVE_JUMP )

#define	MP_CAPS_CURVE_LINEAR	( MP_CURVE_LINEAR )

#define	MP_CAPS_CURVE_SQUARE	( MP_CURVE_SQUARE )

#define	MP_CAPS_CURVE_INVSQUARE	( MP_CURVE_INVSQUARE )

#define	MP_CAPS_CURVE_SINE	( MP_CURVE_SINE )

typedef struct _MP_PARAMINFO
    {
    MP_TYPE mpType;
    MP_CAPS mopCaps;
    MP_DATA mpdMinValue;
    MP_DATA mpdMaxValue;
    MP_DATA mpdNeutralValue;
    WCHAR szUnitText[ 32 ];
    WCHAR szLabel[ 32 ];
    } 	MP_PARAMINFO;

typedef DWORD DWORD;

#define	DWORD_ALLPARAMS	( -1 )

typedef DWORD MP_TIMEDATA;

DEFINE_GUID(GUID_TIME_REFERENCE,
0x93ad712b, 0xdaa0, 0x4ffe, 0xbc, 0x81, 0xb0, 0xce, 0x50, 0xf, 0xcd, 0xd9);
DEFINE_GUID(GUID_TIME_MUSIC,
0x574c49d, 0x5b04, 0x4b15, 0xa5, 0x42, 0xae, 0x28, 0x20, 0x30, 0x11, 0x7b);
DEFINE_GUID(GUID_TIME_SAMPLES,
0xa8593d05, 0xc43, 0x4984, 0x9a, 0x63, 0x97, 0xaf, 0x9e, 0x2, 0xc4, 0xc0);
typedef DWORD MP_FLAGS;

#define	MPF_ENVLP_STANDARD	( 0 )

#define	MPF_ENVLP_BEGIN_CURRENTVAL	( 0x1 )

#define	MPF_ENVLP_BEGIN_NEUTRALVAL	( 0x2 )

typedef struct _MP_ENVELOPE_SEGMENT
    {
    REFERENCE_TIME rtStart;
    REFERENCE_TIME rtEnd;
    MP_DATA valStart;
    MP_DATA valEnd;
    MP_CURVE_TYPE iCurve;
    MP_FLAGS flags;
    } 	MP_ENVELOPE_SEGMENT;

#define	MPF_PUNCHIN_REFTIME	( 0 )

#define	MPF_PUNCHIN_NOW	( 0x1 )

#define	MPF_PUNCHIN_STOPPED	( 0x2 )



extern RPC_IF_HANDLE __MIDL_itf_medparam_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_medparam_0000_v0_0_s_ifspec;

#ifndef __IMediaParamInfo_INTERFACE_DEFINED__
#define __IMediaParamInfo_INTERFACE_DEFINED__

/* interface IMediaParamInfo */
/* [version][uuid][object] */ 


EXTERN_C const IID IID_IMediaParamInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6d6cbb60-a223-44aa-842f-a2f06750be6d")
    IMediaParamInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParamCount( 
            /* [out] */ DWORD *pdwParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamInfo( 
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ MP_PARAMINFO *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamText( 
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ WCHAR **ppwchText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumTimeFormats( 
            /* [out] */ DWORD *pdwNumTimeFormats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSupportedTimeFormat( 
            /* [in] */ DWORD dwFormatIndex,
            /* [out] */ GUID *pguidTimeFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentTimeFormat( 
            /* [out] */ GUID *pguidTimeFormat,
            /* [out] */ MP_TIMEDATA *pTimeData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaParamInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaParamInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaParamInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaParamInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetParamCount )( 
            IMediaParamInfo * This,
            /* [out] */ DWORD *pdwParams);
        
        HRESULT ( STDMETHODCALLTYPE *GetParamInfo )( 
            IMediaParamInfo * This,
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ MP_PARAMINFO *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetParamText )( 
            IMediaParamInfo * This,
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ WCHAR **ppwchText);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumTimeFormats )( 
            IMediaParamInfo * This,
            /* [out] */ DWORD *pdwNumTimeFormats);
        
        HRESULT ( STDMETHODCALLTYPE *GetSupportedTimeFormat )( 
            IMediaParamInfo * This,
            /* [in] */ DWORD dwFormatIndex,
            /* [out] */ GUID *pguidTimeFormat);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentTimeFormat )( 
            IMediaParamInfo * This,
            /* [out] */ GUID *pguidTimeFormat,
            /* [out] */ MP_TIMEDATA *pTimeData);
        
        END_INTERFACE
    } IMediaParamInfoVtbl;

    interface IMediaParamInfo
    {
        CONST_VTBL struct IMediaParamInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaParamInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaParamInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaParamInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaParamInfo_GetParamCount(This,pdwParams)	\
    (This)->lpVtbl -> GetParamCount(This,pdwParams)

#define IMediaParamInfo_GetParamInfo(This,dwParamIndex,pInfo)	\
    (This)->lpVtbl -> GetParamInfo(This,dwParamIndex,pInfo)

#define IMediaParamInfo_GetParamText(This,dwParamIndex,ppwchText)	\
    (This)->lpVtbl -> GetParamText(This,dwParamIndex,ppwchText)

#define IMediaParamInfo_GetNumTimeFormats(This,pdwNumTimeFormats)	\
    (This)->lpVtbl -> GetNumTimeFormats(This,pdwNumTimeFormats)

#define IMediaParamInfo_GetSupportedTimeFormat(This,dwFormatIndex,pguidTimeFormat)	\
    (This)->lpVtbl -> GetSupportedTimeFormat(This,dwFormatIndex,pguidTimeFormat)

#define IMediaParamInfo_GetCurrentTimeFormat(This,pguidTimeFormat,pTimeData)	\
    (This)->lpVtbl -> GetCurrentTimeFormat(This,pguidTimeFormat,pTimeData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetParamCount_Proxy( 
    IMediaParamInfo * This,
    /* [out] */ DWORD *pdwParams);


void __RPC_STUB IMediaParamInfo_GetParamCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetParamInfo_Proxy( 
    IMediaParamInfo * This,
    /* [in] */ DWORD dwParamIndex,
    /* [out] */ MP_PARAMINFO *pInfo);


void __RPC_STUB IMediaParamInfo_GetParamInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetParamText_Proxy( 
    IMediaParamInfo * This,
    /* [in] */ DWORD dwParamIndex,
    /* [out] */ WCHAR **ppwchText);


void __RPC_STUB IMediaParamInfo_GetParamText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetNumTimeFormats_Proxy( 
    IMediaParamInfo * This,
    /* [out] */ DWORD *pdwNumTimeFormats);


void __RPC_STUB IMediaParamInfo_GetNumTimeFormats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetSupportedTimeFormat_Proxy( 
    IMediaParamInfo * This,
    /* [in] */ DWORD dwFormatIndex,
    /* [out] */ GUID *pguidTimeFormat);


void __RPC_STUB IMediaParamInfo_GetSupportedTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParamInfo_GetCurrentTimeFormat_Proxy( 
    IMediaParamInfo * This,
    /* [out] */ GUID *pguidTimeFormat,
    /* [out] */ MP_TIMEDATA *pTimeData);


void __RPC_STUB IMediaParamInfo_GetCurrentTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaParamInfo_INTERFACE_DEFINED__ */


#ifndef __IMediaParams_INTERFACE_DEFINED__
#define __IMediaParams_INTERFACE_DEFINED__

/* interface IMediaParams */
/* [version][uuid][object] */ 


EXTERN_C const IID IID_IMediaParams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6d6cbb61-a223-44aa-842f-a2f06750be6e")
    IMediaParams : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParam( 
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ MP_DATA *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParam( 
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ MP_DATA value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddEnvelope( 
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ DWORD cSegments,
            /* [in] */ MP_ENVELOPE_SEGMENT *pEnvelopeSegments) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FlushEnvelope( 
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ REFERENCE_TIME refTimeStart,
            /* [in] */ REFERENCE_TIME refTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimeFormat( 
            /* [in] */ GUID guidTimeFormat,
            /* [in] */ MP_TIMEDATA mpTimeData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaParamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaParams * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaParams * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaParams * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetParam )( 
            IMediaParams * This,
            /* [in] */ DWORD dwParamIndex,
            /* [out] */ MP_DATA *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetParam )( 
            IMediaParams * This,
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ MP_DATA value);
        
        HRESULT ( STDMETHODCALLTYPE *AddEnvelope )( 
            IMediaParams * This,
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ DWORD cSegments,
            /* [in] */ MP_ENVELOPE_SEGMENT *pEnvelopeSegments);
        
        HRESULT ( STDMETHODCALLTYPE *FlushEnvelope )( 
            IMediaParams * This,
            /* [in] */ DWORD dwParamIndex,
            /* [in] */ REFERENCE_TIME refTimeStart,
            /* [in] */ REFERENCE_TIME refTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimeFormat )( 
            IMediaParams * This,
            /* [in] */ GUID guidTimeFormat,
            /* [in] */ MP_TIMEDATA mpTimeData);
        
        END_INTERFACE
    } IMediaParamsVtbl;

    interface IMediaParams
    {
        CONST_VTBL struct IMediaParamsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaParams_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaParams_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaParams_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaParams_GetParam(This,dwParamIndex,pValue)	\
    (This)->lpVtbl -> GetParam(This,dwParamIndex,pValue)

#define IMediaParams_SetParam(This,dwParamIndex,value)	\
    (This)->lpVtbl -> SetParam(This,dwParamIndex,value)

#define IMediaParams_AddEnvelope(This,dwParamIndex,cSegments,pEnvelopeSegments)	\
    (This)->lpVtbl -> AddEnvelope(This,dwParamIndex,cSegments,pEnvelopeSegments)

#define IMediaParams_FlushEnvelope(This,dwParamIndex,refTimeStart,refTimeEnd)	\
    (This)->lpVtbl -> FlushEnvelope(This,dwParamIndex,refTimeStart,refTimeEnd)

#define IMediaParams_SetTimeFormat(This,guidTimeFormat,mpTimeData)	\
    (This)->lpVtbl -> SetTimeFormat(This,guidTimeFormat,mpTimeData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaParams_GetParam_Proxy( 
    IMediaParams * This,
    /* [in] */ DWORD dwParamIndex,
    /* [out] */ MP_DATA *pValue);


void __RPC_STUB IMediaParams_GetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParams_SetParam_Proxy( 
    IMediaParams * This,
    /* [in] */ DWORD dwParamIndex,
    /* [in] */ MP_DATA value);


void __RPC_STUB IMediaParams_SetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParams_AddEnvelope_Proxy( 
    IMediaParams * This,
    /* [in] */ DWORD dwParamIndex,
    /* [in] */ DWORD cSegments,
    /* [in] */ MP_ENVELOPE_SEGMENT *pEnvelopeSegments);


void __RPC_STUB IMediaParams_AddEnvelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParams_FlushEnvelope_Proxy( 
    IMediaParams * This,
    /* [in] */ DWORD dwParamIndex,
    /* [in] */ REFERENCE_TIME refTimeStart,
    /* [in] */ REFERENCE_TIME refTimeEnd);


void __RPC_STUB IMediaParams_FlushEnvelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaParams_SetTimeFormat_Proxy( 
    IMediaParams * This,
    /* [in] */ GUID guidTimeFormat,
    /* [in] */ MP_TIMEDATA mpTimeData);


void __RPC_STUB IMediaParams_SetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaParams_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


