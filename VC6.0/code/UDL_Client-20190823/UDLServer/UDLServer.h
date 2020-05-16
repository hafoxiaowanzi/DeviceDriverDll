/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jul 25 10:31:51 2019
 */
/* Compiler settings for C:\Users\wwang89\OneDrive - kochind.com\WorkShop\Project\Platfrom\UDL\NetVersion\code\UDL_Client\UDLServer\UDLServer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __UDLServer_h__
#define __UDLServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEngineMgr_FWD_DEFINED__
#define __IEngineMgr_FWD_DEFINED__
typedef interface IEngineMgr IEngineMgr;
#endif 	/* __IEngineMgr_FWD_DEFINED__ */


#ifndef ___IEngineMgrEvents_FWD_DEFINED__
#define ___IEngineMgrEvents_FWD_DEFINED__
typedef interface _IEngineMgrEvents _IEngineMgrEvents;
#endif 	/* ___IEngineMgrEvents_FWD_DEFINED__ */


#ifndef __EngineMgr_FWD_DEFINED__
#define __EngineMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class EngineMgr EngineMgr;
#else
typedef struct EngineMgr EngineMgr;
#endif /* __cplusplus */

#endif 	/* __EngineMgr_FWD_DEFINED__ */


#ifndef ___IEnginePtrEvents_FWD_DEFINED__
#define ___IEnginePtrEvents_FWD_DEFINED__
typedef interface _IEnginePtrEvents _IEnginePtrEvents;
#endif 	/* ___IEnginePtrEvents_FWD_DEFINED__ */


#ifndef __IITLSInterface_FWD_DEFINED__
#define __IITLSInterface_FWD_DEFINED__
typedef interface IITLSInterface IITLSInterface;
#endif 	/* __IITLSInterface_FWD_DEFINED__ */


#ifndef __IIPMInterface_FWD_DEFINED__
#define __IIPMInterface_FWD_DEFINED__
typedef interface IIPMInterface IIPMInterface;
#endif 	/* __IIPMInterface_FWD_DEFINED__ */


#ifndef __IIVOAInterface_FWD_DEFINED__
#define __IIVOAInterface_FWD_DEFINED__
typedef interface IIVOAInterface IIVOAInterface;
#endif 	/* __IIVOAInterface_FWD_DEFINED__ */


#ifndef __IIOSAInterface_FWD_DEFINED__
#define __IIOSAInterface_FWD_DEFINED__
typedef interface IIOSAInterface IIOSAInterface;
#endif 	/* __IIOSAInterface_FWD_DEFINED__ */


#ifndef __IIPolInterface_FWD_DEFINED__
#define __IIPolInterface_FWD_DEFINED__
typedef interface IIPolInterface IIPolInterface;
#endif 	/* __IIPolInterface_FWD_DEFINED__ */


#ifndef __IScanInterface_FWD_DEFINED__
#define __IScanInterface_FWD_DEFINED__
typedef interface IScanInterface IScanInterface;
#endif 	/* __IScanInterface_FWD_DEFINED__ */


#ifndef __IChamberInterface_FWD_DEFINED__
#define __IChamberInterface_FWD_DEFINED__
typedef interface IChamberInterface IChamberInterface;
#endif 	/* __IChamberInterface_FWD_DEFINED__ */


#ifndef __IIComDevInterface_FWD_DEFINED__
#define __IIComDevInterface_FWD_DEFINED__
typedef interface IIComDevInterface IIComDevInterface;
#endif 	/* __IIComDevInterface_FWD_DEFINED__ */


#ifndef __ITLSInterface_FWD_DEFINED__
#define __ITLSInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class ITLSInterface ITLSInterface;
#else
typedef struct ITLSInterface ITLSInterface;
#endif /* __cplusplus */

#endif 	/* __ITLSInterface_FWD_DEFINED__ */


#ifndef __IPMInterface_FWD_DEFINED__
#define __IPMInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class IPMInterface IPMInterface;
#else
typedef struct IPMInterface IPMInterface;
#endif /* __cplusplus */

#endif 	/* __IPMInterface_FWD_DEFINED__ */


#ifndef __IVOAInterface_FWD_DEFINED__
#define __IVOAInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class IVOAInterface IVOAInterface;
#else
typedef struct IVOAInterface IVOAInterface;
#endif /* __cplusplus */

#endif 	/* __IVOAInterface_FWD_DEFINED__ */


#ifndef __IOSAInterface_FWD_DEFINED__
#define __IOSAInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class IOSAInterface IOSAInterface;
#else
typedef struct IOSAInterface IOSAInterface;
#endif /* __cplusplus */

#endif 	/* __IOSAInterface_FWD_DEFINED__ */


#ifndef __IPolInterface_FWD_DEFINED__
#define __IPolInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class IPolInterface IPolInterface;
#else
typedef struct IPolInterface IPolInterface;
#endif /* __cplusplus */

#endif 	/* __IPolInterface_FWD_DEFINED__ */


#ifndef __ScanInterface_FWD_DEFINED__
#define __ScanInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScanInterface ScanInterface;
#else
typedef struct ScanInterface ScanInterface;
#endif /* __cplusplus */

#endif 	/* __ScanInterface_FWD_DEFINED__ */


#ifndef __ChamberInterface_FWD_DEFINED__
#define __ChamberInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChamberInterface ChamberInterface;
#else
typedef struct ChamberInterface ChamberInterface;
#endif /* __cplusplus */

#endif 	/* __ChamberInterface_FWD_DEFINED__ */


#ifndef __IComDevInterface_FWD_DEFINED__
#define __IComDevInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class IComDevInterface IComDevInterface;
#else
typedef struct IComDevInterface IComDevInterface;
#endif /* __cplusplus */

#endif 	/* __IComDevInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_UDLServer_0000 */
/* [local] */ 

typedef /* [helpstring][version][uuid] */ struct  ScanParam
    {
    /* [helpstring] */ BOOL m_bDoPDL;
    /* [helpstring] */ int m_nPDocChIndex;
    /* [helpstring] */ int m_nPDLType;
    /* [helpstring] */ int m_nSpeed;
    /* [helpstring] */ int m_nAvgTime;
    /* [helpstring] */ int m_dwNumberOfScan;
    /* [helpstring] */ int m_dwChannelNumber;
    /* [helpstring] */ int m_dwChannelCfgHigh;
    /* [helpstring] */ int m_dwChannelCfgLow;
    /* [helpstring] */ int m_dwSampleCount;
    /* [helpstring] */ double m_dblTLSPower;
    /* [helpstring] */ double m_dblPWMPower;
    /* [helpstring] */ double m_dbAlphaAngle;
    /* [helpstring] */ double m_dblStartWL;
    /* [helpstring] */ double m_dblStopWL;
    /* [helpstring] */ double m_dblStepSize;
    }	stSetScanParam;

typedef /* [helpstring][version][uuid] */ struct  Op816XRawData
    {
    /* [helpstring] */ double __RPC_FAR *m_pdblWavelengthArray;
    /* [helpstring] */ DWORD __RPC_FAR *m_pdwDataArrayAddr;
    }	stGetOp816XRawData;



extern RPC_IF_HANDLE __MIDL_itf_UDLServer_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UDLServer_0000_v0_0_s_ifspec;

#ifndef __IEngineMgr_INTERFACE_DEFINED__
#define __IEngineMgr_INTERFACE_DEFINED__

/* interface IEngineMgr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEngineMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CEBB9DF-8EE5-42E8-BC16-38D0D22267A7")
    IEngineMgr : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetVersion( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetLastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetLastMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenEngine( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadConfiguration( 
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterUDL( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUDLNET( 
            /* [in] */ BOOL bIsNet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectToServer( 
            /* [in] */ BSTR pstrIPAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEngineMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEngineMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEngineMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEngineMgr __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetVersion )( 
            IEngineMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetVersion )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetLastMessage )( 
            IEngineMgr __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetLastMessage )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenEngine )( 
            IEngineMgr __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadConfiguration )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterUDL )( 
            IEngineMgr __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUDLNET )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ BOOL bIsNet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectToServer )( 
            IEngineMgr __RPC_FAR * This,
            /* [in] */ BSTR pstrIPAddress);
        
        END_INTERFACE
    } IEngineMgrVtbl;

    interface IEngineMgr
    {
        CONST_VTBL struct IEngineMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEngineMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEngineMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEngineMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEngineMgr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEngineMgr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEngineMgr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEngineMgr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEngineMgr_get_GetVersion(This,pVal)	\
    (This)->lpVtbl -> get_GetVersion(This,pVal)

#define IEngineMgr_put_GetVersion(This,newVal)	\
    (This)->lpVtbl -> put_GetVersion(This,newVal)

#define IEngineMgr_get_GetLastMessage(This,pVal)	\
    (This)->lpVtbl -> get_GetLastMessage(This,pVal)

#define IEngineMgr_put_GetLastMessage(This,newVal)	\
    (This)->lpVtbl -> put_GetLastMessage(This,newVal)

#define IEngineMgr_OpenEngine(This)	\
    (This)->lpVtbl -> OpenEngine(This)

#define IEngineMgr_LoadConfiguration(This,FileName)	\
    (This)->lpVtbl -> LoadConfiguration(This,FileName)

#define IEngineMgr_RegisterUDL(This)	\
    (This)->lpVtbl -> RegisterUDL(This)

#define IEngineMgr_SetUDLNET(This,bIsNet)	\
    (This)->lpVtbl -> SetUDLNET(This,bIsNet)

#define IEngineMgr_ConnectToServer(This,pstrIPAddress)	\
    (This)->lpVtbl -> ConnectToServer(This,pstrIPAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEngineMgr_get_GetVersion_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEngineMgr_get_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEngineMgr_put_GetVersion_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEngineMgr_put_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEngineMgr_get_GetLastMessage_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEngineMgr_get_GetLastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEngineMgr_put_GetLastMessage_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEngineMgr_put_GetLastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEngineMgr_OpenEngine_Proxy( 
    IEngineMgr __RPC_FAR * This);


void __RPC_STUB IEngineMgr_OpenEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEngineMgr_LoadConfiguration_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB IEngineMgr_LoadConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEngineMgr_RegisterUDL_Proxy( 
    IEngineMgr __RPC_FAR * This);


void __RPC_STUB IEngineMgr_RegisterUDL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEngineMgr_SetUDLNET_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [in] */ BOOL bIsNet);


void __RPC_STUB IEngineMgr_SetUDLNET_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEngineMgr_ConnectToServer_Proxy( 
    IEngineMgr __RPC_FAR * This,
    /* [in] */ BSTR pstrIPAddress);


void __RPC_STUB IEngineMgr_ConnectToServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEngineMgr_INTERFACE_DEFINED__ */



#ifndef __UDLSERVERLib_LIBRARY_DEFINED__
#define __UDLSERVERLib_LIBRARY_DEFINED__

/* library UDLSERVERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_UDLSERVERLib;

#ifndef ___IEngineMgrEvents_DISPINTERFACE_DEFINED__
#define ___IEngineMgrEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IEngineMgrEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IEngineMgrEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F34AE487-9066-4F9E-AF71-7C1CBA2E9692")
    _IEngineMgrEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IEngineMgrEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IEngineMgrEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IEngineMgrEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IEngineMgrEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IEngineMgrEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IEngineMgrEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IEngineMgrEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IEngineMgrEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IEngineMgrEventsVtbl;

    interface _IEngineMgrEvents
    {
        CONST_VTBL struct _IEngineMgrEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEngineMgrEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IEngineMgrEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IEngineMgrEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IEngineMgrEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IEngineMgrEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IEngineMgrEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IEngineMgrEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IEngineMgrEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EngineMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("B73F2E4C-A43F-48BB-BA61-E25B4D2B96AF")
EngineMgr;
#endif

#ifndef ___IEnginePtrEvents_DISPINTERFACE_DEFINED__
#define ___IEnginePtrEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IEnginePtrEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IEnginePtrEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDF068AB-A4F9-45FC-8742-C1272FC4F1B0")
    _IEnginePtrEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IEnginePtrEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IEnginePtrEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IEnginePtrEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IEnginePtrEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IEnginePtrEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IEnginePtrEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IEnginePtrEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IEnginePtrEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IEnginePtrEventsVtbl;

    interface _IEnginePtrEvents
    {
        CONST_VTBL struct _IEnginePtrEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEnginePtrEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IEnginePtrEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IEnginePtrEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IEnginePtrEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IEnginePtrEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IEnginePtrEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IEnginePtrEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IEnginePtrEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IITLSInterface_INTERFACE_DEFINED__
#define __IITLSInterface_INTERFACE_DEFINED__

/* interface IITLSInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IITLSInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0B50A5FA-6D5A-46D3-BA2B-3608FEF0976A")
    IITLSInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSWavelength( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSSourcePower( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblPW) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSCoherenceControl( 
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSSourceUnit( 
            /* [in] */ long lChIndex,
            /* [in] */ long lUnit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSParameters( 
            /* [in] */ long lChIndex,
            /* [in] */ long lLowSSE,
            /* [in] */ double dblPower,
            /* [in] */ double dblWavelength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTLSOutputEnable( 
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseTLSDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IITLSInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IITLSInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IITLSInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IITLSInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSWavelength )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSSourcePower )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblPW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSCoherenceControl )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSSourceUnit )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lUnit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSParameters )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lLowSSE,
            /* [in] */ double dblPower,
            /* [in] */ double dblWavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTLSOutputEnable )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseTLSDevice )( 
            IITLSInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IITLSInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IITLSInterfaceVtbl;

    interface IITLSInterface
    {
        CONST_VTBL struct IITLSInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IITLSInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IITLSInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IITLSInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IITLSInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IITLSInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IITLSInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IITLSInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IITLSInterface_SetTLSWavelength(This,lChIndex,dblWL)	\
    (This)->lpVtbl -> SetTLSWavelength(This,lChIndex,dblWL)

#define IITLSInterface_SetTLSSourcePower(This,lChIndex,dblPW)	\
    (This)->lpVtbl -> SetTLSSourcePower(This,lChIndex,dblPW)

#define IITLSInterface_SetTLSCoherenceControl(This,lChIndex,bEnable)	\
    (This)->lpVtbl -> SetTLSCoherenceControl(This,lChIndex,bEnable)

#define IITLSInterface_SetTLSSourceUnit(This,lChIndex,lUnit)	\
    (This)->lpVtbl -> SetTLSSourceUnit(This,lChIndex,lUnit)

#define IITLSInterface_SetTLSParameters(This,lChIndex,lLowSSE,dblPower,dblWavelength)	\
    (This)->lpVtbl -> SetTLSParameters(This,lChIndex,lLowSSE,dblPower,dblWavelength)

#define IITLSInterface_SetTLSOutputEnable(This,lChIndex,bEnable)	\
    (This)->lpVtbl -> SetTLSOutputEnable(This,lChIndex,bEnable)

#define IITLSInterface_CloseTLSDevice(This,lChIndex)	\
    (This)->lpVtbl -> CloseTLSDevice(This,lChIndex)

#define IITLSInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSWavelength_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblWL);


void __RPC_STUB IITLSInterface_SetTLSWavelength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSSourcePower_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblPW);


void __RPC_STUB IITLSInterface_SetTLSSourcePower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSCoherenceControl_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IITLSInterface_SetTLSCoherenceControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSSourceUnit_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ long lUnit);


void __RPC_STUB IITLSInterface_SetTLSSourceUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSParameters_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ long lLowSSE,
    /* [in] */ double dblPower,
    /* [in] */ double dblWavelength);


void __RPC_STUB IITLSInterface_SetTLSParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_SetTLSOutputEnable_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IITLSInterface_SetTLSOutputEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IITLSInterface_CloseTLSDevice_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IITLSInterface_CloseTLSDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IITLSInterface_get_LastMessage_Proxy( 
    IITLSInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IITLSInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IITLSInterface_INTERFACE_DEFINED__ */


#ifndef __IIPMInterface_INTERFACE_DEFINED__
#define __IIPMInterface_INTERFACE_DEFINED__

/* interface IIPMInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIPMInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A078CFDE-41C1-45D2-ADC9-20E8B128996B")
    IIPMInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUnit( 
            /* [in] */ long lChan,
            /* [out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUnit( 
            /* [in] */ long lChan,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAverageTime( 
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAverageTime( 
            /* [in] */ long lChan,
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWavelength( 
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWavelength( 
            /* [in] */ long lChan,
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPower( 
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRangeMode( 
            /* [in] */ long lChan,
            /* [out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRangeMode( 
            /* [in] */ long lChan,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParameters( 
            /* [in] */ long lChan,
            /* [in] */ BOOL bAutoRange,
            /* [in] */ double dblWL,
            /* [in] */ double dblAvgTime,
            /* [in] */ double dblPMRange) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetZero( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseDevice( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPMMaxMinPowerStart( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPMMaxMinPower( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdbGetMax,
            /* [out] */ double __RPC_FAR *pdbGetMin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPMMaxMinPowerStop( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPMPowerOffset( 
            /* [in] */ long lChan,
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIPMInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIPMInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIPMInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIPMInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUnit )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUnit )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAverageTime )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAverageTime )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWavelength )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWavelength )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPower )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRangeMode )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRangeMode )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParameters )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ BOOL bAutoRange,
            /* [in] */ double dblWL,
            /* [in] */ double dblAvgTime,
            /* [in] */ double dblPMRange);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZero )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IIPMInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseDevice )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPMMaxMinPowerStart )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPMMaxMinPower )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdbGetMax,
            /* [out] */ double __RPC_FAR *pdbGetMin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPMMaxMinPowerStop )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPMPowerOffset )( 
            IIPMInterface __RPC_FAR * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IIPMInterfaceVtbl;

    interface IIPMInterface
    {
        CONST_VTBL struct IIPMInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPMInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIPMInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIPMInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIPMInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIPMInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIPMInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIPMInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIPMInterface_GetUnit(This,lChan,pVal)	\
    (This)->lpVtbl -> GetUnit(This,lChan,pVal)

#define IIPMInterface_SetUnit(This,lChan,newVal)	\
    (This)->lpVtbl -> SetUnit(This,lChan,newVal)

#define IIPMInterface_GetAverageTime(This,lChan,pVal)	\
    (This)->lpVtbl -> GetAverageTime(This,lChan,pVal)

#define IIPMInterface_SetAverageTime(This,lChan,newVal)	\
    (This)->lpVtbl -> SetAverageTime(This,lChan,newVal)

#define IIPMInterface_GetWavelength(This,lChan,pVal)	\
    (This)->lpVtbl -> GetWavelength(This,lChan,pVal)

#define IIPMInterface_SetWavelength(This,lChan,newVal)	\
    (This)->lpVtbl -> SetWavelength(This,lChan,newVal)

#define IIPMInterface_GetPower(This,lChan,pVal)	\
    (This)->lpVtbl -> GetPower(This,lChan,pVal)

#define IIPMInterface_GetRangeMode(This,lChan,pVal)	\
    (This)->lpVtbl -> GetRangeMode(This,lChan,pVal)

#define IIPMInterface_SetRangeMode(This,lChan,newVal)	\
    (This)->lpVtbl -> SetRangeMode(This,lChan,newVal)

#define IIPMInterface_SetParameters(This,lChan,bAutoRange,dblWL,dblAvgTime,dblPMRange)	\
    (This)->lpVtbl -> SetParameters(This,lChan,bAutoRange,dblWL,dblAvgTime,dblPMRange)

#define IIPMInterface_SetZero(This,lChan)	\
    (This)->lpVtbl -> SetZero(This,lChan)

#define IIPMInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#define IIPMInterface_CloseDevice(This,lChan)	\
    (This)->lpVtbl -> CloseDevice(This,lChan)

#define IIPMInterface_SetPMMaxMinPowerStart(This,lChan)	\
    (This)->lpVtbl -> SetPMMaxMinPowerStart(This,lChan)

#define IIPMInterface_GetPMMaxMinPower(This,lChIndex,pdbGetMax,pdbGetMin)	\
    (This)->lpVtbl -> GetPMMaxMinPower(This,lChIndex,pdbGetMax,pdbGetMin)

#define IIPMInterface_SetPMMaxMinPowerStop(This,lChan)	\
    (This)->lpVtbl -> SetPMMaxMinPowerStop(This,lChan)

#define IIPMInterface_SetPMPowerOffset(This,lChan,newVal)	\
    (This)->lpVtbl -> SetPMPowerOffset(This,lChan,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetUnit_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_GetUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetUnit_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ long newVal);


void __RPC_STUB IIPMInterface_SetUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetAverageTime_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_GetAverageTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetAverageTime_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ double newVal);


void __RPC_STUB IIPMInterface_SetAverageTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetWavelength_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_GetWavelength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetWavelength_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ double newVal);


void __RPC_STUB IIPMInterface_SetWavelength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetPower_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_GetPower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetRangeMode_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_GetRangeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetRangeMode_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ long newVal);


void __RPC_STUB IIPMInterface_SetRangeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetParameters_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ BOOL bAutoRange,
    /* [in] */ double dblWL,
    /* [in] */ double dblAvgTime,
    /* [in] */ double dblPMRange);


void __RPC_STUB IIPMInterface_SetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetZero_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan);


void __RPC_STUB IIPMInterface_SetZero_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIPMInterface_get_LastMessage_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIPMInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_CloseDevice_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan);


void __RPC_STUB IIPMInterface_CloseDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetPMMaxMinPowerStart_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan);


void __RPC_STUB IIPMInterface_SetPMMaxMinPowerStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_GetPMMaxMinPower_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdbGetMax,
    /* [out] */ double __RPC_FAR *pdbGetMin);


void __RPC_STUB IIPMInterface_GetPMMaxMinPower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetPMMaxMinPowerStop_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan);


void __RPC_STUB IIPMInterface_SetPMMaxMinPowerStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPMInterface_SetPMPowerOffset_Proxy( 
    IIPMInterface __RPC_FAR * This,
    /* [in] */ long lChan,
    /* [in] */ double newVal);


void __RPC_STUB IIPMInterface_SetPMPowerOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIPMInterface_INTERFACE_DEFINED__ */


#ifndef __IIVOAInterface_INTERFACE_DEFINED__
#define __IIVOAInterface_INTERFACE_DEFINED__

/* interface IIVOAInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIVOAInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1B84183-A9EF-41D9-A894-D008CBB0D5E4")
    IIVOAInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseVOADevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetVOADevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAWavelength( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVOAWavelength( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAAttenuation( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblAtten) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVOAAttenuation( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAEnableOutput( 
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEanble) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAInputOffset( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVOAStatus( 
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIVOAInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIVOAInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIVOAInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIVOAInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseVOADevice )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetVOADevice )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVOAWavelength )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVOAWavelength )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVOAAttenuation )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblAtten);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVOAAttenuation )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVOAEnableOutput )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEanble);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVOAInputOffset )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVOAStatus )( 
            IIVOAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IIVOAInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IIVOAInterfaceVtbl;

    interface IIVOAInterface
    {
        CONST_VTBL struct IIVOAInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIVOAInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIVOAInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIVOAInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIVOAInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIVOAInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIVOAInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIVOAInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIVOAInterface_CloseVOADevice(This,lChIndex)	\
    (This)->lpVtbl -> CloseVOADevice(This,lChIndex)

#define IIVOAInterface_ResetVOADevice(This,lChIndex)	\
    (This)->lpVtbl -> ResetVOADevice(This,lChIndex)

#define IIVOAInterface_SetVOAWavelength(This,lChIndex,dblWL)	\
    (This)->lpVtbl -> SetVOAWavelength(This,lChIndex,dblWL)

#define IIVOAInterface_GetVOAWavelength(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetVOAWavelength(This,lChIndex,pVal)

#define IIVOAInterface_SetVOAAttenuation(This,lChIndex,dblAtten)	\
    (This)->lpVtbl -> SetVOAAttenuation(This,lChIndex,dblAtten)

#define IIVOAInterface_GetVOAAttenuation(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetVOAAttenuation(This,lChIndex,pVal)

#define IIVOAInterface_SetVOAEnableOutput(This,lChIndex,bEanble)	\
    (This)->lpVtbl -> SetVOAEnableOutput(This,lChIndex,bEanble)

#define IIVOAInterface_SetVOAInputOffset(This,lChIndex,dblOffset)	\
    (This)->lpVtbl -> SetVOAInputOffset(This,lChIndex,dblOffset)

#define IIVOAInterface_GetVOAStatus(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetVOAStatus(This,lChIndex,pVal)

#define IIVOAInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_CloseVOADevice_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIVOAInterface_CloseVOADevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_ResetVOADevice_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIVOAInterface_ResetVOADevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_SetVOAWavelength_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblWL);


void __RPC_STUB IIVOAInterface_SetVOAWavelength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_GetVOAWavelength_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIVOAInterface_GetVOAWavelength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_SetVOAAttenuation_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblAtten);


void __RPC_STUB IIVOAInterface_SetVOAAttenuation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_GetVOAAttenuation_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIVOAInterface_GetVOAAttenuation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_SetVOAEnableOutput_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BOOL bEanble);


void __RPC_STUB IIVOAInterface_SetVOAEnableOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_SetVOAInputOffset_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblOffset);


void __RPC_STUB IIVOAInterface_SetVOAInputOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_GetVOAStatus_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIVOAInterface_GetVOAStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIVOAInterface_get_LastMessage_Proxy( 
    IIVOAInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIVOAInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIVOAInterface_INTERFACE_DEFINED__ */


#ifndef __IIOSAInterface_INTERFACE_DEFINED__
#define __IIOSAInterface_INTERFACE_DEFINED__

/* interface IIOSAInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIOSAInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("104889A9-452E-419F-85E0-EA5AEB72DBCA")
    IIOSAInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOSALocalCtrl( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOSARBW( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblRBW) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSARBW( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitOSAAmpTest( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MeasureSource( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MeasureAmplifier( 
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bScanSrcOnly) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAChannelCount( 
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOSAAmpOffset( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblSourceOffset,
            /* [in] */ double dblAmpOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAAmpOffset( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSourceOffSet,
            /* [out] */ double __RPC_FAR *pdblAmpOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAEDFAResult( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSumSrcSigPwr,
            /* [out] */ double __RPC_FAR *pdblSumAmpSigPwr,
            /* [out] */ double __RPC_FAR *pdblSumGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAEDFAChResult( 
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pwChCount,
            /* [out] */ double __RPC_FAR *pdblChWL,
            /* [out] */ double __RPC_FAR *pdblSrcpwr,
            /* [out] */ double __RPC_FAR *pdblChGain,
            /* [out] */ double __RPC_FAR *pdblChNF,
            /* [out] */ double __RPC_FAR *pdblChAse,
            /* [out] */ double __RPC_FAR *pdbGainFlatness,
            /* [out] */ double __RPC_FAR *pdblMaxNF,
            /* [out] */ double __RPC_FAR *pdblMaxGain,
            /* [out] */ double __RPC_FAR *pdblMinGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitOSASingleSweep( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW,
            /* [in] */ long lSweepPointCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunOSASweep( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ double __RPC_FAR *pdblPower,
            /* [in] */ BSTR szSelTrace) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSASweepData( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ double __RPC_FAR *pdblPower,
            /* [in] */ BSTR szSelTrace) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOSACalibration( 
            /* [in] */ long lChIndex,
            /* [in] */ long lCalibrationType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveOSADataToPC( 
            /* [in] */ long lChIndex,
            /* [in] */ BSTR lpSavePath,
            /* [in] */ BSTR lpDataType,
            /* [in] */ BSTR lpFileType,
            /* [in] */ BSTR szSelTrace) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelWaveLens( 
            /* [in] */ long lChanIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ DWORD __RPC_FAR *pdwlChanneCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelNF( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblNF,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelGain( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblGain,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelSNR( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSNR,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelSourcePower( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSourcePower,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAZoomValue( 
            /* [in] */ long lChIndex,
            /* [in] */ double dbWLNM,
            /* [in] */ double dbBWNM,
            /* [out] */ double __RPC_FAR *pdbGetValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSASingleSweepPoint( 
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIOSAInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIOSAInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIOSAInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIOSAInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseDevice )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetDevice )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOSALocalCtrl )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOSARBW )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblRBW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSARBW )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitOSAAmpTest )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MeasureSource )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MeasureAmplifier )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bScanSrcOnly);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSAChannelCount )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOSAAmpOffset )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblSourceOffset,
            /* [in] */ double dblAmpOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSAAmpOffset )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSourceOffSet,
            /* [out] */ double __RPC_FAR *pdblAmpOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSAEDFAResult )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSumSrcSigPwr,
            /* [out] */ double __RPC_FAR *pdblSumAmpSigPwr,
            /* [out] */ double __RPC_FAR *pdblSumGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSAEDFAChResult )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pwChCount,
            /* [out] */ double __RPC_FAR *pdblChWL,
            /* [out] */ double __RPC_FAR *pdblSrcpwr,
            /* [out] */ double __RPC_FAR *pdblChGain,
            /* [out] */ double __RPC_FAR *pdblChNF,
            /* [out] */ double __RPC_FAR *pdblChAse,
            /* [out] */ double __RPC_FAR *pdbGainFlatness,
            /* [out] */ double __RPC_FAR *pdblMaxNF,
            /* [out] */ double __RPC_FAR *pdblMaxGain,
            /* [out] */ double __RPC_FAR *pdblMinGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitOSASingleSweep )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW,
            /* [in] */ long lSweepPointCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunOSASweep )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ double __RPC_FAR *pdblPower,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSASweepData )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ double __RPC_FAR *pdblPower,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOSACalibration )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lCalibrationType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveOSADataToPC )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BSTR lpSavePath,
            /* [in] */ BSTR lpDataType,
            /* [in] */ BSTR lpFileType,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IIOSAInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelWaveLens )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChanIndex,
            /* [out] */ double __RPC_FAR *pdblWL,
            /* [out] */ DWORD __RPC_FAR *pdwlChanneCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelNF )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblNF,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelGain )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblGain,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelSNR )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSNR,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelSourcePower )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblSourcePower,
            /* [out] */ DWORD __RPC_FAR *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSAZoomValue )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dbWLNM,
            /* [in] */ double dbBWNM,
            /* [out] */ double __RPC_FAR *pdbGetValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOSASingleSweepPoint )( 
            IIOSAInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IIOSAInterfaceVtbl;

    interface IIOSAInterface
    {
        CONST_VTBL struct IIOSAInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIOSAInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIOSAInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIOSAInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIOSAInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIOSAInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIOSAInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIOSAInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIOSAInterface_CloseDevice(This,lChIndex)	\
    (This)->lpVtbl -> CloseDevice(This,lChIndex)

#define IIOSAInterface_ResetDevice(This,lChIndex)	\
    (This)->lpVtbl -> ResetDevice(This,lChIndex)

#define IIOSAInterface_SetOSALocalCtrl(This,lChIndex)	\
    (This)->lpVtbl -> SetOSALocalCtrl(This,lChIndex)

#define IIOSAInterface_SetOSARBW(This,lChIndex,dblRBW)	\
    (This)->lpVtbl -> SetOSARBW(This,lChIndex,dblRBW)

#define IIOSAInterface_GetOSARBW(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetOSARBW(This,lChIndex,pVal)

#define IIOSAInterface_InitOSAAmpTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW)	\
    (This)->lpVtbl -> InitOSAAmpTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW)

#define IIOSAInterface_MeasureSource(This,lChIndex)	\
    (This)->lpVtbl -> MeasureSource(This,lChIndex)

#define IIOSAInterface_MeasureAmplifier(This,lChIndex,bScanSrcOnly)	\
    (This)->lpVtbl -> MeasureAmplifier(This,lChIndex,bScanSrcOnly)

#define IIOSAInterface_GetOSAChannelCount(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetOSAChannelCount(This,lChIndex,pVal)

#define IIOSAInterface_SetOSAAmpOffset(This,lChIndex,dblSourceOffset,dblAmpOffset)	\
    (This)->lpVtbl -> SetOSAAmpOffset(This,lChIndex,dblSourceOffset,dblAmpOffset)

#define IIOSAInterface_GetOSAAmpOffset(This,lChIndex,pdblSourceOffSet,pdblAmpOffset)	\
    (This)->lpVtbl -> GetOSAAmpOffset(This,lChIndex,pdblSourceOffSet,pdblAmpOffset)

#define IIOSAInterface_GetOSAEDFAResult(This,lChIndex,pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSumGain)	\
    (This)->lpVtbl -> GetOSAEDFAResult(This,lChIndex,pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSumGain)

#define IIOSAInterface_GetOSAEDFAChResult(This,lChIndex,pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdbGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain)	\
    (This)->lpVtbl -> GetOSAEDFAChResult(This,lChIndex,pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdbGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain)

#define IIOSAInterface_InitOSASingleSweep(This,lChIndex,dblStartWL,dblStopWL,dblRBW,lSweepPointCount)	\
    (This)->lpVtbl -> InitOSASingleSweep(This,lChIndex,dblStartWL,dblStopWL,dblRBW,lSweepPointCount)

#define IIOSAInterface_RunOSASweep(This,lChIndex,pdblWL,pdblPower,szSelTrace)	\
    (This)->lpVtbl -> RunOSASweep(This,lChIndex,pdblWL,pdblPower,szSelTrace)

#define IIOSAInterface_GetOSASweepData(This,lChIndex,pdblWL,pdblPower,szSelTrace)	\
    (This)->lpVtbl -> GetOSASweepData(This,lChIndex,pdblWL,pdblPower,szSelTrace)

#define IIOSAInterface_SetOSACalibration(This,lChIndex,lCalibrationType)	\
    (This)->lpVtbl -> SetOSACalibration(This,lChIndex,lCalibrationType)

#define IIOSAInterface_SaveOSADataToPC(This,lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace)	\
    (This)->lpVtbl -> SaveOSADataToPC(This,lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace)

#define IIOSAInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#define IIOSAInterface_GetChannelWaveLens(This,lChanIndex,pdblWL,pdwlChanneCount)	\
    (This)->lpVtbl -> GetChannelWaveLens(This,lChanIndex,pdblWL,pdwlChanneCount)

#define IIOSAInterface_GetChannelNF(This,lChIndex,pdblNF,pdwChannelCount)	\
    (This)->lpVtbl -> GetChannelNF(This,lChIndex,pdblNF,pdwChannelCount)

#define IIOSAInterface_GetChannelGain(This,lChIndex,pdblGain,pdwChannelCount)	\
    (This)->lpVtbl -> GetChannelGain(This,lChIndex,pdblGain,pdwChannelCount)

#define IIOSAInterface_GetChannelSNR(This,lChIndex,pdblSNR,pdwChannelCount)	\
    (This)->lpVtbl -> GetChannelSNR(This,lChIndex,pdblSNR,pdwChannelCount)

#define IIOSAInterface_GetChannelSourcePower(This,lChIndex,pdblSourcePower,pdwChannelCount)	\
    (This)->lpVtbl -> GetChannelSourcePower(This,lChIndex,pdblSourcePower,pdwChannelCount)

#define IIOSAInterface_GetOSAZoomValue(This,lChIndex,dbWLNM,dbBWNM,pdbGetValue)	\
    (This)->lpVtbl -> GetOSAZoomValue(This,lChIndex,dbWLNM,dbBWNM,pdbGetValue)

#define IIOSAInterface_GetOSASingleSweepPoint(This,lChIndex,pVal)	\
    (This)->lpVtbl -> GetOSASingleSweepPoint(This,lChIndex,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_CloseDevice_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIOSAInterface_CloseDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_ResetDevice_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIOSAInterface_ResetDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_SetOSALocalCtrl_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIOSAInterface_SetOSALocalCtrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_SetOSARBW_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblRBW);


void __RPC_STUB IIOSAInterface_SetOSARBW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSARBW_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IIOSAInterface_GetOSARBW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_InitOSAAmpTest_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblStartWL,
    /* [in] */ double dblStopWL,
    /* [in] */ double dblRBW);


void __RPC_STUB IIOSAInterface_InitOSAAmpTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_MeasureSource_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIOSAInterface_MeasureSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_MeasureAmplifier_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BOOL bScanSrcOnly);


void __RPC_STUB IIOSAInterface_MeasureAmplifier_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSAChannelCount_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIOSAInterface_GetOSAChannelCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_SetOSAAmpOffset_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblSourceOffset,
    /* [in] */ double dblAmpOffset);


void __RPC_STUB IIOSAInterface_SetOSAAmpOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSAAmpOffset_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblSourceOffSet,
    /* [out] */ double __RPC_FAR *pdblAmpOffset);


void __RPC_STUB IIOSAInterface_GetOSAAmpOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSAEDFAResult_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblSumSrcSigPwr,
    /* [out] */ double __RPC_FAR *pdblSumAmpSigPwr,
    /* [out] */ double __RPC_FAR *pdblSumGain);


void __RPC_STUB IIOSAInterface_GetOSAEDFAResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSAEDFAChResult_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ long __RPC_FAR *pwChCount,
    /* [out] */ double __RPC_FAR *pdblChWL,
    /* [out] */ double __RPC_FAR *pdblSrcpwr,
    /* [out] */ double __RPC_FAR *pdblChGain,
    /* [out] */ double __RPC_FAR *pdblChNF,
    /* [out] */ double __RPC_FAR *pdblChAse,
    /* [out] */ double __RPC_FAR *pdbGainFlatness,
    /* [out] */ double __RPC_FAR *pdblMaxNF,
    /* [out] */ double __RPC_FAR *pdblMaxGain,
    /* [out] */ double __RPC_FAR *pdblMinGain);


void __RPC_STUB IIOSAInterface_GetOSAEDFAChResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_InitOSASingleSweep_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dblStartWL,
    /* [in] */ double dblStopWL,
    /* [in] */ double dblRBW,
    /* [in] */ long lSweepPointCount);


void __RPC_STUB IIOSAInterface_InitOSASingleSweep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_RunOSASweep_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblWL,
    /* [out] */ double __RPC_FAR *pdblPower,
    /* [in] */ BSTR szSelTrace);


void __RPC_STUB IIOSAInterface_RunOSASweep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSASweepData_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblWL,
    /* [out] */ double __RPC_FAR *pdblPower,
    /* [in] */ BSTR szSelTrace);


void __RPC_STUB IIOSAInterface_GetOSASweepData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_SetOSACalibration_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ long lCalibrationType);


void __RPC_STUB IIOSAInterface_SetOSACalibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_SaveOSADataToPC_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BSTR lpSavePath,
    /* [in] */ BSTR lpDataType,
    /* [in] */ BSTR lpFileType,
    /* [in] */ BSTR szSelTrace);


void __RPC_STUB IIOSAInterface_SaveOSADataToPC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_get_LastMessage_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIOSAInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetChannelWaveLens_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChanIndex,
    /* [out] */ double __RPC_FAR *pdblWL,
    /* [out] */ DWORD __RPC_FAR *pdwlChanneCount);


void __RPC_STUB IIOSAInterface_GetChannelWaveLens_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetChannelNF_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblNF,
    /* [out] */ DWORD __RPC_FAR *pdwChannelCount);


void __RPC_STUB IIOSAInterface_GetChannelNF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetChannelGain_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblGain,
    /* [out] */ DWORD __RPC_FAR *pdwChannelCount);


void __RPC_STUB IIOSAInterface_GetChannelGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetChannelSNR_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblSNR,
    /* [out] */ DWORD __RPC_FAR *pdwChannelCount);


void __RPC_STUB IIOSAInterface_GetChannelSNR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetChannelSourcePower_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblSourcePower,
    /* [out] */ DWORD __RPC_FAR *pdwChannelCount);


void __RPC_STUB IIOSAInterface_GetChannelSourcePower_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSAZoomValue_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dbWLNM,
    /* [in] */ double dbBWNM,
    /* [out] */ double __RPC_FAR *pdbGetValue);


void __RPC_STUB IIOSAInterface_GetOSAZoomValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIOSAInterface_GetOSASingleSweepPoint_Proxy( 
    IIOSAInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIOSAInterface_GetOSASingleSweepPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIOSAInterface_INTERFACE_DEFINED__ */


#ifndef __IIPolInterface_INTERFACE_DEFINED__
#define __IIPolInterface_INTERFACE_DEFINED__

/* interface IIPolInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIPolInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF1A856A-F3E6-4461-9DC4-F1F87EA61F37")
    IIPolInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClosePolDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetPolDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPolCurrentPOSPolarizer( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblAlphaP,
            /* [out] */ double __RPC_FAR *pdblAlphaQ,
            /* [out] */ double __RPC_FAR *pdblAlphaH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolALL( 
            /* [in] */ long lChIndex,
            /* [in] */ double alphaP,
            /* [in] */ double alphaQ,
            /* [in] */ double alp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolDiagonalAngles( 
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolHorizontalAngles( 
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolPOSHalf( 
            /* [in] */ long lChIndex,
            /* [in] */ double alpha) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolPOSPolarizer( 
            /* [in] */ long lChIndex,
            /* [in] */ double alpha) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolPOSQuarter( 
            /* [in] */ long lChIndex,
            /* [in] */ double alpha) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolRightHandCircularAngles( 
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolVerticalAngles( 
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIPolInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIPolInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIPolInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIPolInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClosePolDevice )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPolDevice )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPolCurrentPOSPolarizer )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *pdblAlphaP,
            /* [out] */ double __RPC_FAR *pdblAlphaQ,
            /* [out] */ double __RPC_FAR *pdblAlphaH);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolALL )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alphaP,
            /* [in] */ double alphaQ,
            /* [in] */ double alp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolDiagonalAngles )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolHorizontalAngles )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolPOSHalf )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolPOSPolarizer )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolPOSQuarter )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolRightHandCircularAngles )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolVerticalAngles )( 
            IIPolInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IIPolInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IIPolInterfaceVtbl;

    interface IIPolInterface
    {
        CONST_VTBL struct IIPolInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPolInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIPolInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIPolInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIPolInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIPolInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIPolInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIPolInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIPolInterface_ClosePolDevice(This,lChIndex)	\
    (This)->lpVtbl -> ClosePolDevice(This,lChIndex)

#define IIPolInterface_ResetPolDevice(This,lChIndex)	\
    (This)->lpVtbl -> ResetPolDevice(This,lChIndex)

#define IIPolInterface_GetPolCurrentPOSPolarizer(This,lChIndex,pdblAlphaP,pdblAlphaQ,pdblAlphaH)	\
    (This)->lpVtbl -> GetPolCurrentPOSPolarizer(This,lChIndex,pdblAlphaP,pdblAlphaQ,pdblAlphaH)

#define IIPolInterface_SetPolALL(This,lChIndex,alphaP,alphaQ,alp)	\
    (This)->lpVtbl -> SetPolALL(This,lChIndex,alphaP,alphaQ,alp)

#define IIPolInterface_SetPolDiagonalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    (This)->lpVtbl -> SetPolDiagonalAngles(This,lChIndex,AlphaPMax,Wavelength)

#define IIPolInterface_SetPolHorizontalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    (This)->lpVtbl -> SetPolHorizontalAngles(This,lChIndex,AlphaPMax,Wavelength)

#define IIPolInterface_SetPolPOSHalf(This,lChIndex,alpha)	\
    (This)->lpVtbl -> SetPolPOSHalf(This,lChIndex,alpha)

#define IIPolInterface_SetPolPOSPolarizer(This,lChIndex,alpha)	\
    (This)->lpVtbl -> SetPolPOSPolarizer(This,lChIndex,alpha)

#define IIPolInterface_SetPolPOSQuarter(This,lChIndex,alpha)	\
    (This)->lpVtbl -> SetPolPOSQuarter(This,lChIndex,alpha)

#define IIPolInterface_SetPolRightHandCircularAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    (This)->lpVtbl -> SetPolRightHandCircularAngles(This,lChIndex,AlphaPMax,Wavelength)

#define IIPolInterface_SetPolVerticalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    (This)->lpVtbl -> SetPolVerticalAngles(This,lChIndex,AlphaPMax,Wavelength)

#define IIPolInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_ClosePolDevice_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIPolInterface_ClosePolDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_ResetPolDevice_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIPolInterface_ResetPolDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_GetPolCurrentPOSPolarizer_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *pdblAlphaP,
    /* [out] */ double __RPC_FAR *pdblAlphaQ,
    /* [out] */ double __RPC_FAR *pdblAlphaH);


void __RPC_STUB IIPolInterface_GetPolCurrentPOSPolarizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolALL_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double alphaP,
    /* [in] */ double alphaQ,
    /* [in] */ double alp);


void __RPC_STUB IIPolInterface_SetPolALL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolDiagonalAngles_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double AlphaPMax,
    /* [in] */ double Wavelength);


void __RPC_STUB IIPolInterface_SetPolDiagonalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolHorizontalAngles_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double AlphaPMax,
    /* [in] */ double Wavelength);


void __RPC_STUB IIPolInterface_SetPolHorizontalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolPOSHalf_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double alpha);


void __RPC_STUB IIPolInterface_SetPolPOSHalf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolPOSPolarizer_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double alpha);


void __RPC_STUB IIPolInterface_SetPolPOSPolarizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolPOSQuarter_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double alpha);


void __RPC_STUB IIPolInterface_SetPolPOSQuarter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolRightHandCircularAngles_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double AlphaPMax,
    /* [in] */ double Wavelength);


void __RPC_STUB IIPolInterface_SetPolRightHandCircularAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIPolInterface_SetPolVerticalAngles_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double AlphaPMax,
    /* [in] */ double Wavelength);


void __RPC_STUB IIPolInterface_SetPolVerticalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIPolInterface_get_LastMessage_Proxy( 
    IIPolInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIPolInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIPolInterface_INTERFACE_DEFINED__ */


#ifndef __IScanInterface_INTERFACE_DEFINED__
#define __IScanInterface_INTERFACE_DEFINED__

/* interface IScanInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IScanInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7CDE6BE4-4B5C-46DC-99C5-1B680178713F")
    IScanInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrepareScan( 
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteScan( 
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawDataPtr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseScan( 
            /* [in] */ long lTLSChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoScanRef( 
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoScan( 
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCalILResult( 
            /* [in] */ long lpScanResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCalILAndPDLResult( 
            /* [in] */ long lpScanResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseAllocStruct( 
            /* [in] */ long lpStructPtr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScanInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IScanInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IScanInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IScanInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareScan )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteScan )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawDataPtr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseScan )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lTLSChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoScanRef )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoScan )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalILResult )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lpScanResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalILAndPDLResult )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lpScanResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseAllocStruct )( 
            IScanInterface __RPC_FAR * This,
            /* [in] */ long lpStructPtr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IScanInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IScanInterfaceVtbl;

    interface IScanInterface
    {
        CONST_VTBL struct IScanInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScanInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScanInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScanInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IScanInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IScanInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IScanInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IScanInterface_PrepareScan(This,lTLSChIndex,lpScanParam)	\
    (This)->lpVtbl -> PrepareScan(This,lTLSChIndex,lpScanParam)

#define IScanInterface_ExecuteScan(This,lTLSChIndex,lpScanRawDataPtr)	\
    (This)->lpVtbl -> ExecuteScan(This,lTLSChIndex,lpScanRawDataPtr)

#define IScanInterface_ReleaseScan(This,lTLSChIndex)	\
    (This)->lpVtbl -> ReleaseScan(This,lTLSChIndex)

#define IScanInterface_DoScanRef(This,lTLSChIndex,lpScanRawData)	\
    (This)->lpVtbl -> DoScanRef(This,lTLSChIndex,lpScanRawData)

#define IScanInterface_DoScan(This,lTLSChIndex,lpScanRawData)	\
    (This)->lpVtbl -> DoScan(This,lTLSChIndex,lpScanRawData)

#define IScanInterface_GetCalILResult(This,lpScanResult)	\
    (This)->lpVtbl -> GetCalILResult(This,lpScanResult)

#define IScanInterface_GetCalILAndPDLResult(This,lpScanResult)	\
    (This)->lpVtbl -> GetCalILAndPDLResult(This,lpScanResult)

#define IScanInterface_ReleaseAllocStruct(This,lpStructPtr)	\
    (This)->lpVtbl -> ReleaseAllocStruct(This,lpStructPtr)

#define IScanInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_PrepareScan_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lTLSChIndex,
    /* [in] */ long lpScanParam);


void __RPC_STUB IScanInterface_PrepareScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_ExecuteScan_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lTLSChIndex,
    /* [in] */ long lpScanRawDataPtr);


void __RPC_STUB IScanInterface_ExecuteScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_ReleaseScan_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lTLSChIndex);


void __RPC_STUB IScanInterface_ReleaseScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_DoScanRef_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lTLSChIndex,
    /* [in] */ long lpScanRawData);


void __RPC_STUB IScanInterface_DoScanRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_DoScan_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lTLSChIndex,
    /* [in] */ long lpScanRawData);


void __RPC_STUB IScanInterface_DoScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_GetCalILResult_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lpScanResult);


void __RPC_STUB IScanInterface_GetCalILResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_GetCalILAndPDLResult_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lpScanResult);


void __RPC_STUB IScanInterface_GetCalILAndPDLResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanInterface_ReleaseAllocStruct_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [in] */ long lpStructPtr);


void __RPC_STUB IScanInterface_ReleaseAllocStruct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IScanInterface_get_LastMessage_Proxy( 
    IScanInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IScanInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScanInterface_INTERFACE_DEFINED__ */


#ifndef __IChamberInterface_INTERFACE_DEFINED__
#define __IChamberInterface_INTERFACE_DEFINED__

/* interface IChamberInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IChamberInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89A6FDE2-516B-4432-AF08-1DCE005D0B1E")
    IChamberInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseChamberDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChamberRunStop( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChamberRunStart( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChamberSetPoint( 
            /* [in] */ long lChIndex,
            /* [in] */ double dbSetPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChamberSetPoint( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *dbSetPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChamberCurrentTemp( 
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *dbCurrTemp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChamberInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IChamberInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IChamberInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IChamberInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseChamberDevice )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetChamberRunStop )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetChamberRunStart )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetChamberSetPoint )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dbSetPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChamberSetPoint )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *dbSetPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChamberCurrentTemp )( 
            IChamberInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ double __RPC_FAR *dbCurrTemp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IChamberInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IChamberInterfaceVtbl;

    interface IChamberInterface
    {
        CONST_VTBL struct IChamberInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChamberInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChamberInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChamberInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChamberInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IChamberInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IChamberInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IChamberInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IChamberInterface_CloseChamberDevice(This,lChIndex)	\
    (This)->lpVtbl -> CloseChamberDevice(This,lChIndex)

#define IChamberInterface_SetChamberRunStop(This,lChIndex)	\
    (This)->lpVtbl -> SetChamberRunStop(This,lChIndex)

#define IChamberInterface_SetChamberRunStart(This,lChIndex)	\
    (This)->lpVtbl -> SetChamberRunStart(This,lChIndex)

#define IChamberInterface_SetChamberSetPoint(This,lChIndex,dbSetPoint)	\
    (This)->lpVtbl -> SetChamberSetPoint(This,lChIndex,dbSetPoint)

#define IChamberInterface_GetChamberSetPoint(This,lChIndex,dbSetPoint)	\
    (This)->lpVtbl -> GetChamberSetPoint(This,lChIndex,dbSetPoint)

#define IChamberInterface_GetChamberCurrentTemp(This,lChIndex,dbCurrTemp)	\
    (This)->lpVtbl -> GetChamberCurrentTemp(This,lChIndex,dbCurrTemp)

#define IChamberInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_CloseChamberDevice_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IChamberInterface_CloseChamberDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_SetChamberRunStop_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IChamberInterface_SetChamberRunStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_SetChamberRunStart_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IChamberInterface_SetChamberRunStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_SetChamberSetPoint_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ double dbSetPoint);


void __RPC_STUB IChamberInterface_SetChamberSetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_GetChamberSetPoint_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *dbSetPoint);


void __RPC_STUB IChamberInterface_GetChamberSetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChamberInterface_GetChamberCurrentTemp_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ double __RPC_FAR *dbCurrTemp);


void __RPC_STUB IChamberInterface_GetChamberCurrentTemp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChamberInterface_get_LastMessage_Proxy( 
    IChamberInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IChamberInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChamberInterface_INTERFACE_DEFINED__ */


#ifndef __IIComDevInterface_INTERFACE_DEFINED__
#define __IIComDevInterface_INTERFACE_DEFINED__

/* interface IIComDevInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIComDevInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("309343A5-A079-4F81-9DA2-FE2D0538DC2D")
    IIComDevInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteBuffer( 
            /* [in] */ long lChIndex,
            /* [in] */ BSTR pBuffer,
            /* [in] */ DWORD dwBufferSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadBuffer( 
            /* [in] */ long lChIndex,
            /* [out] */ BSTR __RPC_FAR *pBuffer,
            /* [in] */ DWORD dwBufferSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSerial( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenSerial( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIComDevInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIComDevInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIComDevInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIComDevInterface __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteBuffer )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [in] */ BSTR pBuffer,
            /* [in] */ DWORD dwBufferSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadBuffer )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ long lChIndex,
            /* [out] */ BSTR __RPC_FAR *pBuffer,
            /* [in] */ DWORD dwBufferSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseSerial )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenSerial )( 
            IIComDevInterface __RPC_FAR * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastMessage )( 
            IIComDevInterface __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IIComDevInterfaceVtbl;

    interface IIComDevInterface
    {
        CONST_VTBL struct IIComDevInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIComDevInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIComDevInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIComDevInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIComDevInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIComDevInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIComDevInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIComDevInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIComDevInterface_WriteBuffer(This,lChIndex,pBuffer,dwBufferSize)	\
    (This)->lpVtbl -> WriteBuffer(This,lChIndex,pBuffer,dwBufferSize)

#define IIComDevInterface_ReadBuffer(This,lChIndex,pBuffer,dwBufferSize)	\
    (This)->lpVtbl -> ReadBuffer(This,lChIndex,pBuffer,dwBufferSize)

#define IIComDevInterface_CloseSerial(This,lChIndex)	\
    (This)->lpVtbl -> CloseSerial(This,lChIndex)

#define IIComDevInterface_OpenSerial(This,lChIndex)	\
    (This)->lpVtbl -> OpenSerial(This,lChIndex)

#define IIComDevInterface_get_LastMessage(This,pVal)	\
    (This)->lpVtbl -> get_LastMessage(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIComDevInterface_WriteBuffer_Proxy( 
    IIComDevInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [in] */ BSTR pBuffer,
    /* [in] */ DWORD dwBufferSize);


void __RPC_STUB IIComDevInterface_WriteBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIComDevInterface_ReadBuffer_Proxy( 
    IIComDevInterface __RPC_FAR * This,
    /* [in] */ long lChIndex,
    /* [out] */ BSTR __RPC_FAR *pBuffer,
    /* [in] */ DWORD dwBufferSize);


void __RPC_STUB IIComDevInterface_ReadBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIComDevInterface_CloseSerial_Proxy( 
    IIComDevInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIComDevInterface_CloseSerial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIComDevInterface_OpenSerial_Proxy( 
    IIComDevInterface __RPC_FAR * This,
    /* [in] */ long lChIndex);


void __RPC_STUB IIComDevInterface_OpenSerial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIComDevInterface_get_LastMessage_Proxy( 
    IIComDevInterface __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIComDevInterface_get_LastMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIComDevInterface_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ITLSInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("82E74FAE-D809-47C0-8CD3-7F653CBB4FD8")
ITLSInterface;
#endif

EXTERN_C const CLSID CLSID_IPMInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("2AA6F3FA-6507-49DF-8791-971F31301992")
IPMInterface;
#endif

EXTERN_C const CLSID CLSID_IVOAInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("E5B0D9E8-E9F9-4C14-9E48-A60C4EC74252")
IVOAInterface;
#endif

EXTERN_C const CLSID CLSID_IOSAInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("B4E0C31C-404B-41A6-843C-64770AA349B0")
IOSAInterface;
#endif

EXTERN_C const CLSID CLSID_IPolInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("17B09D77-2E06-4678-98E3-23DFEA8262F9")
IPolInterface;
#endif

EXTERN_C const CLSID CLSID_ScanInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("5B3B1877-867F-4742-B3D7-302F08CE032B")
ScanInterface;
#endif

EXTERN_C const CLSID CLSID_ChamberInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("90321366-D7CC-4F21-94F4-756CA1DB1B34")
ChamberInterface;
#endif

EXTERN_C const CLSID CLSID_IComDevInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("CB4F7BD8-2FC4-40C9-8F8F-C2FF01E5EA63")
IComDevInterface;
#endif
#endif /* __UDLSERVERLib_LIBRARY_DEFINED__ */

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
