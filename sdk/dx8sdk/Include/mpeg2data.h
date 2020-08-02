
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for mpeg2data.idl:
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


#ifndef __mpeg2data_h__
#define __mpeg2data_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMpeg2Data_FWD_DEFINED__
#define __IMpeg2Data_FWD_DEFINED__
typedef interface IMpeg2Data IMpeg2Data;
#endif 	/* __IMpeg2Data_FWD_DEFINED__ */


#ifndef __ISectionList_FWD_DEFINED__
#define __ISectionList_FWD_DEFINED__
typedef interface ISectionList ISectionList;
#endif 	/* __ISectionList_FWD_DEFINED__ */


#ifndef __IMpeg2Stream_FWD_DEFINED__
#define __IMpeg2Stream_FWD_DEFINED__
typedef interface IMpeg2Stream IMpeg2Stream;
#endif 	/* __IMpeg2Stream_FWD_DEFINED__ */


#ifndef __SectionList_FWD_DEFINED__
#define __SectionList_FWD_DEFINED__

#ifdef __cplusplus
typedef class SectionList SectionList;
#else
typedef struct SectionList SectionList;
#endif /* __cplusplus */

#endif 	/* __SectionList_FWD_DEFINED__ */


#ifndef __Mpeg2Stream_FWD_DEFINED__
#define __Mpeg2Stream_FWD_DEFINED__

#ifdef __cplusplus
typedef class Mpeg2Stream Mpeg2Stream;
#else
typedef struct Mpeg2Stream Mpeg2Stream;
#endif /* __cplusplus */

#endif 	/* __Mpeg2Stream_FWD_DEFINED__ */


#ifndef __Mpeg2Data_FWD_DEFINED__
#define __Mpeg2Data_FWD_DEFINED__

#ifdef __cplusplus
typedef class Mpeg2Data Mpeg2Data;
#else
typedef struct Mpeg2Data Mpeg2Data;
#endif /* __cplusplus */

#endif 	/* __Mpeg2Data_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "bdaiface.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mpeg2data_0000 */
/* [local] */ 


#pragma pack(push)

#pragma pack(1)


#define MPEG_PAT_PID                0x0000
#define MPEG_PAT_TID                0x00
#define MPEG_CAT_PID                0x0001
#define MPEG_CAT_TID                0x01
#define MPEG_PMT_TID                0x02
#define MPEG_TSDT_PID               0x0002
#define MPEG_TSDT_TID               0x03
#define ATSC_MGT_PID                0x1FFB
#define ATSC_MGT_TID                0xC7
#define ATSC_VCT_PID                0x1FFB
#define ATSC_VCT_TERR_TID           0xC8
#define ATSC_VCT_CABL_TID           0xC9
#define ATSC_RRT_PID                0x1FFB
#define ATSC_RRT_TID                0xCA
#define ATSC_EIT_TID                0xCB
#define ATSC_ETT_TID                0xCC
#define ATSC_STT_PID                0x1FFB
#define ATSC_STT_TID                0xCD
#define ATSC_PIT_TID                0xD0
#define DVB_NIT_PID                 0x0010
#define DVB_NIT_ACTUAL_TID          0x40
#define DVB_NIT_OTHER_TID           0x41
#define DVB_SDT_PID                 0x0011
#define DVB_SDT_ACTUAL_TID          0x42
#define DVB_SDT_OTHER_TID           0x46
#define DVB_BAT_PID                 0x0011
#define DVB_BAT_TID                 0x4A
#define DVB_EIT_PID                 0x0012
#define DVB_EIT_ACTUAL_TID          0x4E
#define DVB_EIT_OTHER_TID           0x4F
#define DVB_RST_PID                 0x0013
#define DVB_RST_TID                 0x71
#define DVB_TDT_PID                 0x0014
#define DVB_TDT_TID                 0x70
#define DVB_ST_PID_16               0x0010
#define DVB_ST_PID_17               0x0011
#define DVB_ST_PID_18               0x0012
#define DVB_ST_PID_19               0x0013
#define DVB_ST_PID_20               0x0014
#define DVB_ST_TID                  0x72
#define DVB_TOT_PID                 0x0014
#define DVB_TOT_TID                 0x73
#define DVB_DIT_PID                 0x001E
#define DVB_DIT_TID                 0x7E
#define DVB_SIT_PID                 0x001F
#define DVB_SIT_TID                 0x7F
#define ISDB_DCT_PID                0x0017
#define ISDB_DCT_TID                0xC0
#define ISDB_LIT_PID                0x0020
#define ISDB_LIT_TID                0xD0
#define ISDB_ERT_PID                0x0021
#define ISDB_ERT_TID                0xD1
#define ISDB_ITT_TID                0xD2
#define ISDB_DLT_TID                0xC1
#define ISDB_PCAT_PID               0x0022
#define ISDB_PCAT_TID               0xC2
#define ISDB_SDTT_PID               0x0023
#define ISDB_SDTT_TID               0xC3
class DECLSPEC_UUID("DBAF6C1B-B6A4-4898-AE65-204F0D9509A1") Mpeg2DataLib;


extern RPC_IF_HANDLE __MIDL_itf_mpeg2data_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mpeg2data_0000_v0_0_s_ifspec;


#ifndef __Mpeg2DataLib_LIBRARY_DEFINED__
#define __Mpeg2DataLib_LIBRARY_DEFINED__

/* library Mpeg2DataLib */
/* [version][uuid] */ 

#pragma once

#pragma pack(push)

#pragma pack(1)
typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0001
    {
    WORD Bits;
    } 	PID_BITS_MIDL;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0002
    {
    WORD Bits;
    } 	MPEG_HEADER_BITS_MIDL;

typedef /* [public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0003
    {
    BYTE Bits;
    } 	MPEG_HEADER_VERSION_BITS_MIDL;


#pragma pack(pop)
typedef WORD PID;

typedef BYTE TID;

typedef UINT ClientKey;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_mpeg2data_0000_0004
    {	MPEG_SECTION_IS_NEXT	= 0,
	MPEG_SECTION_IS_CURRENT	= 1
    } 	MPEG_CURRENT_NEXT_BIT;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0005
    {
    WORD wTidExt;
    WORD wCount;
    } 	TID_EXTENSION;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0005 *PTID_EXTENSION;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0006
    {
    TID TableId;
    union 
        {
        MPEG_HEADER_BITS_MIDL S;
        WORD W;
        } 	Header;
    BYTE SectionData[ 1 ];
    } 	SECTION;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0006 *PSECTION;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0008
    {
    TID TableId;
    union 
        {
        MPEG_HEADER_BITS_MIDL S;
        WORD W;
        } 	Header;
    WORD TableIdExtension;
    union 
        {
        MPEG_HEADER_VERSION_BITS_MIDL S;
        BYTE B;
        } 	Version;
    BYTE SectionNumber;
    BYTE LastSectionNumber;
    BYTE RemainingData[ 1 ];
    } 	LONG_SECTION;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0008 *PLONG_SECTION;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0011
    {
    TID TableId;
    union 
        {
        MPEG_HEADER_BITS_MIDL S;
        WORD W;
        } 	Header;
    WORD TableIdExtension;
    union 
        {
        MPEG_HEADER_VERSION_BITS_MIDL S;
        BYTE B;
        } 	Version;
    BYTE SectionNumber;
    BYTE LastSectionNumber;
    BYTE ProtocolDiscriminator;
    BYTE DsmccType;
    WORD MessageId;
    DWORD TransactionId;
    BYTE Reserved;
    BYTE AdaptationLength;
    WORD MessageLength;
    BYTE RemainingData[ 1 ];
    } 	DSMCC_SECTION;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0011 *PDSMCC_SECTION;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0014
    {
    DWORD dwLength;
    PSECTION pSection;
    } 	MPEG_RQST_PACKET;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0014 *PMPEG_RQST_PACKET;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0015
    {
    WORD wPacketCount;
    PMPEG_RQST_PACKET PacketList[ 1 ];
    } 	MPEG_PACKET_LIST;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0015 *PMPEG_PACKET_LIST;

typedef /* [public][public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0016
    {
    BOOL fSpecifyProtocol;
    BYTE Protocol;
    BOOL fSpecifyType;
    BYTE Type;
    BOOL fSpecifyMessageId;
    WORD MessageId;
    BOOL fSpecifyTransactionId;
    BOOL fUseTrxIdMessageIdMask;
    DWORD TransactionId;
    BOOL fSpecifyModuleVersion;
    BYTE ModuleVersion;
    BOOL fSpecifyBlockNumber;
    WORD BlockNumber;
    BOOL fGetModuleCall;
    WORD NumberOfBlocksInModule;
    } 	DSMCC_FILTER_OPTIONS;

typedef /* [public][public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0017
    {
    BOOL fSpecifyEtmId;
    DWORD EtmId;
    } 	ATSC_FILTER_OPTIONS;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0018
    {
    BYTE bVersionNumber;
    WORD wFilterSize;
    BOOL fUseRawFilteringBits;
    BYTE Filter[ 16 ];
    BYTE Mask[ 16 ];
    BOOL fSpecifyTableIdExtension;
    WORD TableIdExtension;
    BOOL fSpecifyVersion;
    BYTE Version;
    BOOL fSpecifySectionNumber;
    BYTE SectionNumber;
    BOOL fSpecifyCurrentNext;
    BOOL fNext;
    BOOL fSpecifyDsmccOptions;
    DSMCC_FILTER_OPTIONS Dsmcc;
    BOOL fSpecifyAtscOptions;
    ATSC_FILTER_OPTIONS Atsc;
    } 	MPEG2_FILTER;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0018 *PMPEG2_FILTER;

#define MPEG2_FILTER_VERSION_1_SIZE  124
typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0019
    {
    HRESULT hr;
    DWORD dwDataBufferSize;
    DWORD dwSizeOfDataRead;
    BYTE *pDataBuffer;
    } 	MPEG_STREAM_BUFFER;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0019 *PMPEG_STREAM_BUFFER;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0020
    {
    BYTE Hours;
    BYTE Minutes;
    BYTE Seconds;
    } 	MPEG_TIME;

typedef MPEG_TIME MPEG_DURATION;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0021
    {
    BYTE Date;
    BYTE Month;
    WORD Year;
    } 	MPEG_DATE;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0022
    {
    MPEG_DATE D;
    MPEG_TIME T;
    } 	MPEG_DATE_AND_TIME;

typedef /* [public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_mpeg2data_0000_0023
    {	MPEG_CONTEXT_BCS_DEMUX	= 0,
	MPEG_CONTEXT_WINSOCK	= MPEG_CONTEXT_BCS_DEMUX + 1
    } 	MPEG_CONTEXT_TYPE;

typedef /* [public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0024
    {
    DWORD AVMGraphId;
    } 	MPEG_BCS_DEMUX;

typedef /* [public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0025
    {
    DWORD AVMGraphId;
    } 	MPEG_WINSOCK;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0026
    {
    MPEG_CONTEXT_TYPE Type;
    union 
        {
        MPEG_BCS_DEMUX Demux;
        MPEG_WINSOCK Winsock;
        } 	U;
    } 	MPEG_CONTEXT;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0026 *PMPEG_CONTEXT;

typedef /* [public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_mpeg2data_0000_0028
    {	MPEG_RQST_UNKNOWN	= 0,
	MPEG_RQST_GET_SECTION	= MPEG_RQST_UNKNOWN + 1,
	MPEG_RQST_GET_SECTION_ASYNC	= MPEG_RQST_GET_SECTION + 1,
	MPEG_RQST_GET_TABLE	= MPEG_RQST_GET_SECTION_ASYNC + 1,
	MPEG_RQST_GET_TABLE_ASYNC	= MPEG_RQST_GET_TABLE + 1,
	MPEG_RQST_GET_SECTIONS_STREAM	= MPEG_RQST_GET_TABLE_ASYNC + 1,
	MPEG_RQST_GET_PES_STREAM	= MPEG_RQST_GET_SECTIONS_STREAM + 1,
	MPEG_RQST_GET_TS_STREAM	= MPEG_RQST_GET_PES_STREAM + 1,
	MPEG_RQST_START_MPE_STREAM	= MPEG_RQST_GET_TS_STREAM + 1
    } 	MPEG_REQUEST_TYPE;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0029
    {
    MPEG_REQUEST_TYPE Type;
    MPEG_CONTEXT Context;
    PID Pid;
    TID TableId;
    MPEG2_FILTER Filter;
    DWORD Flags;
    } 	MPEG_SERVICE_REQUEST;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0029 *PMPEG_SERVICE_REQUEST;

typedef /* [public] */ struct __MIDL___MIDL_itf_mpeg2data_0000_0030
    {
    DWORD IPAddress;
    WORD Port;
    } 	MPEG_SERVICE_RESPONSE;

typedef struct __MIDL___MIDL_itf_mpeg2data_0000_0030 *PMPEG_SERVICE_RESPONSE;

typedef struct _DSMCC_ELEMENT
    {
    PID pid;
    BYTE bComponentTag;
    DWORD dwCarouselId;
    DWORD dwTransactionId;
    struct _DSMCC_ELEMENT *pNext;
    } 	DSMCC_ELEMENT;

typedef struct _DSMCC_ELEMENT *PDSMCC_ELEMENT;

typedef struct _MPE_ELEMENT
    {
    PID pid;
    BYTE bComponentTag;
    struct _MPE_ELEMENT *pNext;
    } 	MPE_ELEMENT;

typedef struct _MPE_ELEMENT *PMPE_ELEMENT;

typedef struct _MPEG_STREAM_FILTER
    {
    WORD wPidValue;
    DWORD dwFilterSize;
    BOOL fCrcEnabled;
    BYTE rgchFilter[ 16 ];
    BYTE rgchMask[ 16 ];
    } 	MPEG_STREAM_FILTER;


EXTERN_C const IID LIBID_Mpeg2DataLib;

#ifndef __IMpeg2Data_INTERFACE_DEFINED__
#define __IMpeg2Data_INTERFACE_DEFINED__

/* interface IMpeg2Data */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMpeg2Data;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B396D40-F380-4e3c-A514-1A82BF6EBFE6")
    IMpeg2Data : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSection( 
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ ISectionList **ppSectionList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTable( 
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ ISectionList **ppSectionList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamOfSections( 
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ HANDLE hDataReadyEvent,
            /* [out] */ IMpeg2Stream **ppMpegStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMpeg2DataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMpeg2Data * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMpeg2Data * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMpeg2Data * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSection )( 
            IMpeg2Data * This,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ ISectionList **ppSectionList);
        
        HRESULT ( STDMETHODCALLTYPE *GetTable )( 
            IMpeg2Data * This,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ ISectionList **ppSectionList);
        
        HRESULT ( STDMETHODCALLTYPE *GetStreamOfSections )( 
            IMpeg2Data * This,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ HANDLE hDataReadyEvent,
            /* [out] */ IMpeg2Stream **ppMpegStream);
        
        END_INTERFACE
    } IMpeg2DataVtbl;

    interface IMpeg2Data
    {
        CONST_VTBL struct IMpeg2DataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMpeg2Data_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMpeg2Data_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMpeg2Data_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMpeg2Data_GetSection(This,pid,tid,pFilter,dwTimeout,ppSectionList)	\
    (This)->lpVtbl -> GetSection(This,pid,tid,pFilter,dwTimeout,ppSectionList)

#define IMpeg2Data_GetTable(This,pid,tid,pFilter,dwTimeout,ppSectionList)	\
    (This)->lpVtbl -> GetTable(This,pid,tid,pFilter,dwTimeout,ppSectionList)

#define IMpeg2Data_GetStreamOfSections(This,pid,tid,pFilter,hDataReadyEvent,ppMpegStream)	\
    (This)->lpVtbl -> GetStreamOfSections(This,pid,tid,pFilter,hDataReadyEvent,ppMpegStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMpeg2Data_GetSection_Proxy( 
    IMpeg2Data * This,
    /* [in] */ PID pid,
    /* [in] */ TID tid,
    /* [in] */ PMPEG2_FILTER pFilter,
    /* [in] */ DWORD dwTimeout,
    /* [out] */ ISectionList **ppSectionList);


void __RPC_STUB IMpeg2Data_GetSection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMpeg2Data_GetTable_Proxy( 
    IMpeg2Data * This,
    /* [in] */ PID pid,
    /* [in] */ TID tid,
    /* [in] */ PMPEG2_FILTER pFilter,
    /* [in] */ DWORD dwTimeout,
    /* [out] */ ISectionList **ppSectionList);


void __RPC_STUB IMpeg2Data_GetTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMpeg2Data_GetStreamOfSections_Proxy( 
    IMpeg2Data * This,
    /* [in] */ PID pid,
    /* [in] */ TID tid,
    /* [in] */ PMPEG2_FILTER pFilter,
    /* [in] */ HANDLE hDataReadyEvent,
    /* [out] */ IMpeg2Stream **ppMpegStream);


void __RPC_STUB IMpeg2Data_GetStreamOfSections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMpeg2Data_INTERFACE_DEFINED__ */


#ifndef __ISectionList_INTERFACE_DEFINED__
#define __ISectionList_INTERFACE_DEFINED__

/* interface ISectionList */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISectionList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFEC1EB5-2A64-46c6-BF4B-AE3CCB6AFDB0")
    ISectionList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ MPEG_REQUEST_TYPE requestType,
            /* [in] */ IMpeg2Data *pMpeg2Data,
            /* [in] */ PMPEG_CONTEXT pContext,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD timeout,
            /* [in] */ HANDLE hDoneEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeWithRawSections( 
            /* [in] */ PMPEG_PACKET_LIST pmplSections) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelPendingRequest( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumberOfSections( 
            /* [out] */ WORD *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSectionData( 
            /* [in] */ WORD sectionNumber,
            /* [out] */ DWORD *pdwRawPacketLength,
            /* [out] */ PSECTION *ppSection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProgramIdentifier( 
            PID *pPid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTableIdentifier( 
            TID *pTableId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISectionListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISectionList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISectionList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISectionList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ISectionList * This,
            /* [in] */ MPEG_REQUEST_TYPE requestType,
            /* [in] */ IMpeg2Data *pMpeg2Data,
            /* [in] */ PMPEG_CONTEXT pContext,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ DWORD timeout,
            /* [in] */ HANDLE hDoneEvent);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeWithRawSections )( 
            ISectionList * This,
            /* [in] */ PMPEG_PACKET_LIST pmplSections);
        
        HRESULT ( STDMETHODCALLTYPE *CancelPendingRequest )( 
            ISectionList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumberOfSections )( 
            ISectionList * This,
            /* [out] */ WORD *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSectionData )( 
            ISectionList * This,
            /* [in] */ WORD sectionNumber,
            /* [out] */ DWORD *pdwRawPacketLength,
            /* [out] */ PSECTION *ppSection);
        
        HRESULT ( STDMETHODCALLTYPE *GetProgramIdentifier )( 
            ISectionList * This,
            PID *pPid);
        
        HRESULT ( STDMETHODCALLTYPE *GetTableIdentifier )( 
            ISectionList * This,
            TID *pTableId);
        
        END_INTERFACE
    } ISectionListVtbl;

    interface ISectionList
    {
        CONST_VTBL struct ISectionListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISectionList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISectionList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISectionList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISectionList_Initialize(This,requestType,pMpeg2Data,pContext,pid,tid,pFilter,timeout,hDoneEvent)	\
    (This)->lpVtbl -> Initialize(This,requestType,pMpeg2Data,pContext,pid,tid,pFilter,timeout,hDoneEvent)

#define ISectionList_InitializeWithRawSections(This,pmplSections)	\
    (This)->lpVtbl -> InitializeWithRawSections(This,pmplSections)

#define ISectionList_CancelPendingRequest(This)	\
    (This)->lpVtbl -> CancelPendingRequest(This)

#define ISectionList_GetNumberOfSections(This,pCount)	\
    (This)->lpVtbl -> GetNumberOfSections(This,pCount)

#define ISectionList_GetSectionData(This,sectionNumber,pdwRawPacketLength,ppSection)	\
    (This)->lpVtbl -> GetSectionData(This,sectionNumber,pdwRawPacketLength,ppSection)

#define ISectionList_GetProgramIdentifier(This,pPid)	\
    (This)->lpVtbl -> GetProgramIdentifier(This,pPid)

#define ISectionList_GetTableIdentifier(This,pTableId)	\
    (This)->lpVtbl -> GetTableIdentifier(This,pTableId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISectionList_Initialize_Proxy( 
    ISectionList * This,
    /* [in] */ MPEG_REQUEST_TYPE requestType,
    /* [in] */ IMpeg2Data *pMpeg2Data,
    /* [in] */ PMPEG_CONTEXT pContext,
    /* [in] */ PID pid,
    /* [in] */ TID tid,
    /* [in] */ PMPEG2_FILTER pFilter,
    /* [in] */ DWORD timeout,
    /* [in] */ HANDLE hDoneEvent);


void __RPC_STUB ISectionList_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_InitializeWithRawSections_Proxy( 
    ISectionList * This,
    /* [in] */ PMPEG_PACKET_LIST pmplSections);


void __RPC_STUB ISectionList_InitializeWithRawSections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_CancelPendingRequest_Proxy( 
    ISectionList * This);


void __RPC_STUB ISectionList_CancelPendingRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_GetNumberOfSections_Proxy( 
    ISectionList * This,
    /* [out] */ WORD *pCount);


void __RPC_STUB ISectionList_GetNumberOfSections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_GetSectionData_Proxy( 
    ISectionList * This,
    /* [in] */ WORD sectionNumber,
    /* [out] */ DWORD *pdwRawPacketLength,
    /* [out] */ PSECTION *ppSection);


void __RPC_STUB ISectionList_GetSectionData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_GetProgramIdentifier_Proxy( 
    ISectionList * This,
    PID *pPid);


void __RPC_STUB ISectionList_GetProgramIdentifier_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISectionList_GetTableIdentifier_Proxy( 
    ISectionList * This,
    TID *pTableId);


void __RPC_STUB ISectionList_GetTableIdentifier_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISectionList_INTERFACE_DEFINED__ */


#ifndef __IMpeg2Stream_INTERFACE_DEFINED__
#define __IMpeg2Stream_INTERFACE_DEFINED__

/* interface IMpeg2Stream */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IMpeg2Stream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("400CC286-32A0-4ce4-9041-39571125A635")
    IMpeg2Stream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ MPEG_REQUEST_TYPE requestType,
            /* [in] */ IMpeg2Data *pMpeg2Data,
            /* [in] */ PMPEG_CONTEXT pContext,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ HANDLE hDataReadyEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SupplyDataBuffer( 
            /* [in] */ PMPEG_STREAM_BUFFER pStreamBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMpeg2StreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMpeg2Stream * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMpeg2Stream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMpeg2Stream * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMpeg2Stream * This,
            /* [in] */ MPEG_REQUEST_TYPE requestType,
            /* [in] */ IMpeg2Data *pMpeg2Data,
            /* [in] */ PMPEG_CONTEXT pContext,
            /* [in] */ PID pid,
            /* [in] */ TID tid,
            /* [in] */ PMPEG2_FILTER pFilter,
            /* [in] */ HANDLE hDataReadyEvent);
        
        HRESULT ( STDMETHODCALLTYPE *SupplyDataBuffer )( 
            IMpeg2Stream * This,
            /* [in] */ PMPEG_STREAM_BUFFER pStreamBuffer);
        
        END_INTERFACE
    } IMpeg2StreamVtbl;

    interface IMpeg2Stream
    {
        CONST_VTBL struct IMpeg2StreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMpeg2Stream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMpeg2Stream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMpeg2Stream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMpeg2Stream_Initialize(This,requestType,pMpeg2Data,pContext,pid,tid,pFilter,hDataReadyEvent)	\
    (This)->lpVtbl -> Initialize(This,requestType,pMpeg2Data,pContext,pid,tid,pFilter,hDataReadyEvent)

#define IMpeg2Stream_SupplyDataBuffer(This,pStreamBuffer)	\
    (This)->lpVtbl -> SupplyDataBuffer(This,pStreamBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMpeg2Stream_Initialize_Proxy( 
    IMpeg2Stream * This,
    /* [in] */ MPEG_REQUEST_TYPE requestType,
    /* [in] */ IMpeg2Data *pMpeg2Data,
    /* [in] */ PMPEG_CONTEXT pContext,
    /* [in] */ PID pid,
    /* [in] */ TID tid,
    /* [in] */ PMPEG2_FILTER pFilter,
    /* [in] */ HANDLE hDataReadyEvent);


void __RPC_STUB IMpeg2Stream_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMpeg2Stream_SupplyDataBuffer_Proxy( 
    IMpeg2Stream * This,
    /* [in] */ PMPEG_STREAM_BUFFER pStreamBuffer);


void __RPC_STUB IMpeg2Stream_SupplyDataBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMpeg2Stream_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SectionList;

#ifdef __cplusplus

class DECLSPEC_UUID("73DA5D04-4347-45d3-A9DC-FAE9DDBE558D")
SectionList;
#endif

EXTERN_C const CLSID CLSID_Mpeg2Stream;

#ifdef __cplusplus

class DECLSPEC_UUID("F91D96C7-8509-4d0b-AB26-A0DD10904BB7")
Mpeg2Stream;
#endif

EXTERN_C const CLSID CLSID_Mpeg2Data;

#ifdef __cplusplus

class DECLSPEC_UUID("C666E115-BB62-4027-A113-82D643FE2D99")
Mpeg2Data;
#endif
#endif /* __Mpeg2DataLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_mpeg2data_0432 */
/* [local] */ 


#pragma pack(pop)


extern RPC_IF_HANDLE __MIDL_itf_mpeg2data_0432_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mpeg2data_0432_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


