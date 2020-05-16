

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Aug 30 16:32:31 2019
 */
/* Compiler settings for UDLServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __UDLServer_h_h__
#define __UDLServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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


#ifndef __IISwitchBoxInterface_FWD_DEFINED__
#define __IISwitchBoxInterface_FWD_DEFINED__
typedef interface IISwitchBoxInterface IISwitchBoxInterface;
#endif 	/* __IISwitchBoxInterface_FWD_DEFINED__ */


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


#ifndef __ISwitchBoxInterface_FWD_DEFINED__
#define __ISwitchBoxInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class ISwitchBoxInterface ISwitchBoxInterface;
#else
typedef struct ISwitchBoxInterface ISwitchBoxInterface;
#endif /* __cplusplus */

#endif 	/* __ISwitchBoxInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_UDLServer_0000_0000 */
/* [local] */ 

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("C21871A0-33EB-11D4-A13A-BE2573A1120F") struct ScanParam
    {
    BOOL m_bDoPDL;
    int m_nPDocChIndex;
    int m_nPDLType;
    int m_nSpeed;
    int m_nAvgTime;
    int m_dwNumberOfScan;
    int m_dwChannelNumber;
    int m_dwChannelCfgHigh;
    int m_dwChannelCfgLow;
    int m_dwSampleCount;
    double m_dblTLSPower;
    double m_dblPWMPower;
    double m_dbAlphaAngle;
    double m_dblStartWL;
    double m_dblStopWL;
    double m_dblStepSize;
    } 	stSetScanParam;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("C218719F-33EB-11D4-A13A-BE2573A1120F") struct Op816XRawData
    {
    double *m_pdblWavelengthArray;
    DWORD *m_pdwDataArrayAddr;
    } 	stGetOp816XRawData;



extern RPC_IF_HANDLE __MIDL_itf_UDLServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UDLServer_0000_0000_v0_0_s_ifspec;

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
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetVersion( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetLastMessage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEngineMgr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEngineMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEngineMgr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEngineMgr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEngineMgr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEngineMgr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEngineMgr * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GetVersion )( 
            IEngineMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GetVersion )( 
            IEngineMgr * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GetLastMessage )( 
            IEngineMgr * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GetLastMessage )( 
            IEngineMgr * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenEngine )( 
            IEngineMgr * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadConfiguration )( 
            IEngineMgr * This,
            /* [in] */ BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RegisterUDL )( 
            IEngineMgr * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUDLNET )( 
            IEngineMgr * This,
            /* [in] */ BOOL bIsNet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConnectToServer )( 
            IEngineMgr * This,
            /* [in] */ BSTR pstrIPAddress);
        
        END_INTERFACE
    } IEngineMgrVtbl;

    interface IEngineMgr
    {
        CONST_VTBL struct IEngineMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEngineMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEngineMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEngineMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEngineMgr_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEngineMgr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEngineMgr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEngineMgr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IEngineMgr_get_GetVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_GetVersion(This,pVal) ) 

#define IEngineMgr_put_GetVersion(This,newVal)	\
    ( (This)->lpVtbl -> put_GetVersion(This,newVal) ) 

#define IEngineMgr_get_GetLastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_GetLastMessage(This,pVal) ) 

#define IEngineMgr_put_GetLastMessage(This,newVal)	\
    ( (This)->lpVtbl -> put_GetLastMessage(This,newVal) ) 

#define IEngineMgr_OpenEngine(This)	\
    ( (This)->lpVtbl -> OpenEngine(This) ) 

#define IEngineMgr_LoadConfiguration(This,FileName)	\
    ( (This)->lpVtbl -> LoadConfiguration(This,FileName) ) 

#define IEngineMgr_RegisterUDL(This)	\
    ( (This)->lpVtbl -> RegisterUDL(This) ) 

#define IEngineMgr_SetUDLNET(This,bIsNet)	\
    ( (This)->lpVtbl -> SetUDLNET(This,bIsNet) ) 

#define IEngineMgr_ConnectToServer(This,pstrIPAddress)	\
    ( (This)->lpVtbl -> ConnectToServer(This,pstrIPAddress) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IEngineMgrEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IEngineMgrEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IEngineMgrEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IEngineMgrEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IEngineMgrEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IEngineMgrEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IEngineMgrEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IEngineMgrEventsVtbl;

    interface _IEngineMgrEvents
    {
        CONST_VTBL struct _IEngineMgrEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEngineMgrEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IEngineMgrEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IEngineMgrEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IEngineMgrEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IEngineMgrEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IEngineMgrEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IEngineMgrEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IEnginePtrEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IEnginePtrEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IEnginePtrEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IEnginePtrEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IEnginePtrEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IEnginePtrEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IEnginePtrEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IEnginePtrEventsVtbl;

    interface _IEnginePtrEvents
    {
        CONST_VTBL struct _IEnginePtrEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IEnginePtrEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IEnginePtrEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IEnginePtrEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IEnginePtrEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IEnginePtrEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IEnginePtrEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IEnginePtrEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

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
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IITLSInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IITLSInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IITLSInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IITLSInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IITLSInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IITLSInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IITLSInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IITLSInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSWavelength )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSSourcePower )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblPW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSCoherenceControl )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSSourceUnit )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lUnit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSParameters )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lLowSSE,
            /* [in] */ double dblPower,
            /* [in] */ double dblWavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTLSOutputEnable )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseTLSDevice )( 
            IITLSInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IITLSInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IITLSInterfaceVtbl;

    interface IITLSInterface
    {
        CONST_VTBL struct IITLSInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IITLSInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IITLSInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IITLSInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IITLSInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IITLSInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IITLSInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IITLSInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IITLSInterface_SetTLSWavelength(This,lChIndex,dblWL)	\
    ( (This)->lpVtbl -> SetTLSWavelength(This,lChIndex,dblWL) ) 

#define IITLSInterface_SetTLSSourcePower(This,lChIndex,dblPW)	\
    ( (This)->lpVtbl -> SetTLSSourcePower(This,lChIndex,dblPW) ) 

#define IITLSInterface_SetTLSCoherenceControl(This,lChIndex,bEnable)	\
    ( (This)->lpVtbl -> SetTLSCoherenceControl(This,lChIndex,bEnable) ) 

#define IITLSInterface_SetTLSSourceUnit(This,lChIndex,lUnit)	\
    ( (This)->lpVtbl -> SetTLSSourceUnit(This,lChIndex,lUnit) ) 

#define IITLSInterface_SetTLSParameters(This,lChIndex,lLowSSE,dblPower,dblWavelength)	\
    ( (This)->lpVtbl -> SetTLSParameters(This,lChIndex,lLowSSE,dblPower,dblWavelength) ) 

#define IITLSInterface_SetTLSOutputEnable(This,lChIndex,bEnable)	\
    ( (This)->lpVtbl -> SetTLSOutputEnable(This,lChIndex,bEnable) ) 

#define IITLSInterface_CloseTLSDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseTLSDevice(This,lChIndex) ) 

#define IITLSInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUnit( 
            /* [in] */ long lChan,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAverageTime( 
            /* [in] */ long lChan,
            /* [out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAverageTime( 
            /* [in] */ long lChan,
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWavelength( 
            /* [in] */ long lChan,
            /* [out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWavelength( 
            /* [in] */ long lChan,
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPower( 
            /* [in] */ long lChan,
            /* [out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRangeMode( 
            /* [in] */ long lChan,
            /* [out] */ long *pVal) = 0;
        
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
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseDevice( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPMMaxMinPowerStart( 
            /* [in] */ long lChan) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPMMaxMinPower( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdbGetMax,
            /* [out] */ double *pdbGetMin) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIPMInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIPMInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIPMInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIPMInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIPMInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIPMInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIPMInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUnit )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUnit )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAverageTime )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAverageTime )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWavelength )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWavelength )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPower )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRangeMode )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRangeMode )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetParameters )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ BOOL bAutoRange,
            /* [in] */ double dblWL,
            /* [in] */ double dblAvgTime,
            /* [in] */ double dblPMRange);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetZero )( 
            IIPMInterface * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IIPMInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseDevice )( 
            IIPMInterface * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPMMaxMinPowerStart )( 
            IIPMInterface * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPMMaxMinPower )( 
            IIPMInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdbGetMax,
            /* [out] */ double *pdbGetMin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPMMaxMinPowerStop )( 
            IIPMInterface * This,
            /* [in] */ long lChan);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPMPowerOffset )( 
            IIPMInterface * This,
            /* [in] */ long lChan,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IIPMInterfaceVtbl;

    interface IIPMInterface
    {
        CONST_VTBL struct IIPMInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPMInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIPMInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIPMInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIPMInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIPMInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIPMInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIPMInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIPMInterface_GetUnit(This,lChan,pVal)	\
    ( (This)->lpVtbl -> GetUnit(This,lChan,pVal) ) 

#define IIPMInterface_SetUnit(This,lChan,newVal)	\
    ( (This)->lpVtbl -> SetUnit(This,lChan,newVal) ) 

#define IIPMInterface_GetAverageTime(This,lChan,pVal)	\
    ( (This)->lpVtbl -> GetAverageTime(This,lChan,pVal) ) 

#define IIPMInterface_SetAverageTime(This,lChan,newVal)	\
    ( (This)->lpVtbl -> SetAverageTime(This,lChan,newVal) ) 

#define IIPMInterface_GetWavelength(This,lChan,pVal)	\
    ( (This)->lpVtbl -> GetWavelength(This,lChan,pVal) ) 

#define IIPMInterface_SetWavelength(This,lChan,newVal)	\
    ( (This)->lpVtbl -> SetWavelength(This,lChan,newVal) ) 

#define IIPMInterface_GetPower(This,lChan,pVal)	\
    ( (This)->lpVtbl -> GetPower(This,lChan,pVal) ) 

#define IIPMInterface_GetRangeMode(This,lChan,pVal)	\
    ( (This)->lpVtbl -> GetRangeMode(This,lChan,pVal) ) 

#define IIPMInterface_SetRangeMode(This,lChan,newVal)	\
    ( (This)->lpVtbl -> SetRangeMode(This,lChan,newVal) ) 

#define IIPMInterface_SetParameters(This,lChan,bAutoRange,dblWL,dblAvgTime,dblPMRange)	\
    ( (This)->lpVtbl -> SetParameters(This,lChan,bAutoRange,dblWL,dblAvgTime,dblPMRange) ) 

#define IIPMInterface_SetZero(This,lChan)	\
    ( (This)->lpVtbl -> SetZero(This,lChan) ) 

#define IIPMInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#define IIPMInterface_CloseDevice(This,lChan)	\
    ( (This)->lpVtbl -> CloseDevice(This,lChan) ) 

#define IIPMInterface_SetPMMaxMinPowerStart(This,lChan)	\
    ( (This)->lpVtbl -> SetPMMaxMinPowerStart(This,lChan) ) 

#define IIPMInterface_GetPMMaxMinPower(This,lChIndex,pdbGetMax,pdbGetMin)	\
    ( (This)->lpVtbl -> GetPMMaxMinPower(This,lChIndex,pdbGetMax,pdbGetMin) ) 

#define IIPMInterface_SetPMMaxMinPowerStop(This,lChan)	\
    ( (This)->lpVtbl -> SetPMMaxMinPowerStop(This,lChan) ) 

#define IIPMInterface_SetPMPowerOffset(This,lChan,newVal)	\
    ( (This)->lpVtbl -> SetPMPowerOffset(This,lChan,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAAttenuation( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblAtten) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVOAAttenuation( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAEnableOutput( 
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEanble) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVOAInputOffset( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVOAStatus( 
            /* [in] */ long lChIndex,
            /* [out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIVOAInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIVOAInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIVOAInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIVOAInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIVOAInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIVOAInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIVOAInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIVOAInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseVOADevice )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetVOADevice )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVOAWavelength )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblWL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVOAWavelength )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVOAAttenuation )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblAtten);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVOAAttenuation )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVOAEnableOutput )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bEanble);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVOAInputOffset )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVOAStatus )( 
            IIVOAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IIVOAInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IIVOAInterfaceVtbl;

    interface IIVOAInterface
    {
        CONST_VTBL struct IIVOAInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIVOAInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIVOAInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIVOAInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIVOAInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIVOAInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIVOAInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIVOAInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIVOAInterface_CloseVOADevice(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseVOADevice(This,lChIndex) ) 

#define IIVOAInterface_ResetVOADevice(This,lChIndex)	\
    ( (This)->lpVtbl -> ResetVOADevice(This,lChIndex) ) 

#define IIVOAInterface_SetVOAWavelength(This,lChIndex,dblWL)	\
    ( (This)->lpVtbl -> SetVOAWavelength(This,lChIndex,dblWL) ) 

#define IIVOAInterface_GetVOAWavelength(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetVOAWavelength(This,lChIndex,pVal) ) 

#define IIVOAInterface_SetVOAAttenuation(This,lChIndex,dblAtten)	\
    ( (This)->lpVtbl -> SetVOAAttenuation(This,lChIndex,dblAtten) ) 

#define IIVOAInterface_GetVOAAttenuation(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetVOAAttenuation(This,lChIndex,pVal) ) 

#define IIVOAInterface_SetVOAEnableOutput(This,lChIndex,bEanble)	\
    ( (This)->lpVtbl -> SetVOAEnableOutput(This,lChIndex,bEanble) ) 

#define IIVOAInterface_SetVOAInputOffset(This,lChIndex,dblOffset)	\
    ( (This)->lpVtbl -> SetVOAInputOffset(This,lChIndex,dblOffset) ) 

#define IIVOAInterface_GetVOAStatus(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetVOAStatus(This,lChIndex,pVal) ) 

#define IIVOAInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ double *pVal) = 0;
        
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
            /* [out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOSAAmpOffset( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblSourceOffset,
            /* [in] */ double dblAmpOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAAmpOffset( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSourceOffSet,
            /* [out] */ double *pdblAmpOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAEDFAResult( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSumSrcSigPwr,
            /* [out] */ double *pdblSumAmpSigPwr,
            /* [out] */ double *pdblSumGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAEDFAChResult( 
            /* [in] */ long lChIndex,
            /* [out] */ long *pwChCount,
            /* [out] */ double *pdblChWL,
            /* [out] */ double *pdblSrcpwr,
            /* [out] */ double *pdblChGain,
            /* [out] */ double *pdblChNF,
            /* [out] */ double *pdblChAse,
            /* [out] */ double *pdbGainFlatness,
            /* [out] */ double *pdblMaxNF,
            /* [out] */ double *pdblMaxGain,
            /* [out] */ double *pdblMinGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitOSASingleSweep( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW,
            /* [in] */ long lSweepPointCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunOSASweep( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ double *pdblPower,
            /* [in] */ BSTR szSelTrace) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSASweepData( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ double *pdblPower,
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
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelWaveLens( 
            /* [in] */ long lChanIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ DWORD *pdwlChanneCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelNF( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblNF,
            /* [out] */ DWORD *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelGain( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblGain,
            /* [out] */ DWORD *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelSNR( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSNR,
            /* [out] */ DWORD *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelSourcePower( 
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSourcePower,
            /* [out] */ DWORD *pdwChannelCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSAZoomValue( 
            /* [in] */ long lChIndex,
            /* [in] */ double dbWLNM,
            /* [in] */ double dbBWNM,
            /* [out] */ double *pdbGetValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOSASingleSweepPoint( 
            /* [in] */ long lChIndex,
            /* [out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitOSAWDMTest( 
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MeasureOSAWDM( 
            /* [in] */ long lChIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIOSAInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIOSAInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIOSAInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIOSAInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIOSAInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIOSAInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIOSAInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIOSAInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseDevice )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetDevice )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOSALocalCtrl )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOSARBW )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblRBW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSARBW )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitOSAAmpTest )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MeasureSource )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MeasureAmplifier )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BOOL bScanSrcOnly);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSAChannelCount )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOSAAmpOffset )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblSourceOffset,
            /* [in] */ double dblAmpOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSAAmpOffset )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSourceOffSet,
            /* [out] */ double *pdblAmpOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSAEDFAResult )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSumSrcSigPwr,
            /* [out] */ double *pdblSumAmpSigPwr,
            /* [out] */ double *pdblSumGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSAEDFAChResult )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ long *pwChCount,
            /* [out] */ double *pdblChWL,
            /* [out] */ double *pdblSrcpwr,
            /* [out] */ double *pdblChGain,
            /* [out] */ double *pdblChNF,
            /* [out] */ double *pdblChAse,
            /* [out] */ double *pdbGainFlatness,
            /* [out] */ double *pdblMaxNF,
            /* [out] */ double *pdblMaxGain,
            /* [out] */ double *pdblMinGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitOSASingleSweep )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW,
            /* [in] */ long lSweepPointCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunOSASweep )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ double *pdblPower,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSASweepData )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ double *pdblPower,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOSACalibration )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ long lCalibrationType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveOSADataToPC )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BSTR lpSavePath,
            /* [in] */ BSTR lpDataType,
            /* [in] */ BSTR lpFileType,
            /* [in] */ BSTR szSelTrace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IIOSAInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelWaveLens )( 
            IIOSAInterface * This,
            /* [in] */ long lChanIndex,
            /* [out] */ double *pdblWL,
            /* [out] */ DWORD *pdwlChanneCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelNF )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblNF,
            /* [out] */ DWORD *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelGain )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblGain,
            /* [out] */ DWORD *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelSNR )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSNR,
            /* [out] */ DWORD *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelSourcePower )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblSourcePower,
            /* [out] */ DWORD *pdwChannelCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSAZoomValue )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dbWLNM,
            /* [in] */ double dbBWNM,
            /* [out] */ double *pdbGetValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOSASingleSweepPoint )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitOSAWDMTest )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dblStartWL,
            /* [in] */ double dblStopWL,
            /* [in] */ double dblRBW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MeasureOSAWDM )( 
            IIOSAInterface * This,
            /* [in] */ long lChIndex);
        
        END_INTERFACE
    } IIOSAInterfaceVtbl;

    interface IIOSAInterface
    {
        CONST_VTBL struct IIOSAInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIOSAInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIOSAInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIOSAInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIOSAInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIOSAInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIOSAInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIOSAInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIOSAInterface_CloseDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseDevice(This,lChIndex) ) 

#define IIOSAInterface_ResetDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> ResetDevice(This,lChIndex) ) 

#define IIOSAInterface_SetOSALocalCtrl(This,lChIndex)	\
    ( (This)->lpVtbl -> SetOSALocalCtrl(This,lChIndex) ) 

#define IIOSAInterface_SetOSARBW(This,lChIndex,dblRBW)	\
    ( (This)->lpVtbl -> SetOSARBW(This,lChIndex,dblRBW) ) 

#define IIOSAInterface_GetOSARBW(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetOSARBW(This,lChIndex,pVal) ) 

#define IIOSAInterface_InitOSAAmpTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW)	\
    ( (This)->lpVtbl -> InitOSAAmpTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW) ) 

#define IIOSAInterface_MeasureSource(This,lChIndex)	\
    ( (This)->lpVtbl -> MeasureSource(This,lChIndex) ) 

#define IIOSAInterface_MeasureAmplifier(This,lChIndex,bScanSrcOnly)	\
    ( (This)->lpVtbl -> MeasureAmplifier(This,lChIndex,bScanSrcOnly) ) 

#define IIOSAInterface_GetOSAChannelCount(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetOSAChannelCount(This,lChIndex,pVal) ) 

#define IIOSAInterface_SetOSAAmpOffset(This,lChIndex,dblSourceOffset,dblAmpOffset)	\
    ( (This)->lpVtbl -> SetOSAAmpOffset(This,lChIndex,dblSourceOffset,dblAmpOffset) ) 

#define IIOSAInterface_GetOSAAmpOffset(This,lChIndex,pdblSourceOffSet,pdblAmpOffset)	\
    ( (This)->lpVtbl -> GetOSAAmpOffset(This,lChIndex,pdblSourceOffSet,pdblAmpOffset) ) 

#define IIOSAInterface_GetOSAEDFAResult(This,lChIndex,pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSumGain)	\
    ( (This)->lpVtbl -> GetOSAEDFAResult(This,lChIndex,pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSumGain) ) 

#define IIOSAInterface_GetOSAEDFAChResult(This,lChIndex,pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdbGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain)	\
    ( (This)->lpVtbl -> GetOSAEDFAChResult(This,lChIndex,pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdbGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain) ) 

#define IIOSAInterface_InitOSASingleSweep(This,lChIndex,dblStartWL,dblStopWL,dblRBW,lSweepPointCount)	\
    ( (This)->lpVtbl -> InitOSASingleSweep(This,lChIndex,dblStartWL,dblStopWL,dblRBW,lSweepPointCount) ) 

#define IIOSAInterface_RunOSASweep(This,lChIndex,pdblWL,pdblPower,szSelTrace)	\
    ( (This)->lpVtbl -> RunOSASweep(This,lChIndex,pdblWL,pdblPower,szSelTrace) ) 

#define IIOSAInterface_GetOSASweepData(This,lChIndex,pdblWL,pdblPower,szSelTrace)	\
    ( (This)->lpVtbl -> GetOSASweepData(This,lChIndex,pdblWL,pdblPower,szSelTrace) ) 

#define IIOSAInterface_SetOSACalibration(This,lChIndex,lCalibrationType)	\
    ( (This)->lpVtbl -> SetOSACalibration(This,lChIndex,lCalibrationType) ) 

#define IIOSAInterface_SaveOSADataToPC(This,lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace)	\
    ( (This)->lpVtbl -> SaveOSADataToPC(This,lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace) ) 

#define IIOSAInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#define IIOSAInterface_GetChannelWaveLens(This,lChanIndex,pdblWL,pdwlChanneCount)	\
    ( (This)->lpVtbl -> GetChannelWaveLens(This,lChanIndex,pdblWL,pdwlChanneCount) ) 

#define IIOSAInterface_GetChannelNF(This,lChIndex,pdblNF,pdwChannelCount)	\
    ( (This)->lpVtbl -> GetChannelNF(This,lChIndex,pdblNF,pdwChannelCount) ) 

#define IIOSAInterface_GetChannelGain(This,lChIndex,pdblGain,pdwChannelCount)	\
    ( (This)->lpVtbl -> GetChannelGain(This,lChIndex,pdblGain,pdwChannelCount) ) 

#define IIOSAInterface_GetChannelSNR(This,lChIndex,pdblSNR,pdwChannelCount)	\
    ( (This)->lpVtbl -> GetChannelSNR(This,lChIndex,pdblSNR,pdwChannelCount) ) 

#define IIOSAInterface_GetChannelSourcePower(This,lChIndex,pdblSourcePower,pdwChannelCount)	\
    ( (This)->lpVtbl -> GetChannelSourcePower(This,lChIndex,pdblSourcePower,pdwChannelCount) ) 

#define IIOSAInterface_GetOSAZoomValue(This,lChIndex,dbWLNM,dbBWNM,pdbGetValue)	\
    ( (This)->lpVtbl -> GetOSAZoomValue(This,lChIndex,dbWLNM,dbBWNM,pdbGetValue) ) 

#define IIOSAInterface_GetOSASingleSweepPoint(This,lChIndex,pVal)	\
    ( (This)->lpVtbl -> GetOSASingleSweepPoint(This,lChIndex,pVal) ) 

#define IIOSAInterface_InitOSAWDMTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW)	\
    ( (This)->lpVtbl -> InitOSAWDMTest(This,lChIndex,dblStartWL,dblStopWL,dblRBW) ) 

#define IIOSAInterface_MeasureOSAWDM(This,lChIndex)	\
    ( (This)->lpVtbl -> MeasureOSAWDM(This,lChIndex) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ double *pdblAlphaP,
            /* [out] */ double *pdblAlphaQ,
            /* [out] */ double *pdblAlphaH) = 0;
        
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
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIPolInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIPolInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIPolInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIPolInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIPolInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIPolInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIPolInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIPolInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClosePolDevice )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetPolDevice )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPolCurrentPOSPolarizer )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *pdblAlphaP,
            /* [out] */ double *pdblAlphaQ,
            /* [out] */ double *pdblAlphaH);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolALL )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alphaP,
            /* [in] */ double alphaQ,
            /* [in] */ double alp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolDiagonalAngles )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolHorizontalAngles )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolPOSHalf )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolPOSPolarizer )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolPOSQuarter )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double alpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolRightHandCircularAngles )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolVerticalAngles )( 
            IIPolInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double AlphaPMax,
            /* [in] */ double Wavelength);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IIPolInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IIPolInterfaceVtbl;

    interface IIPolInterface
    {
        CONST_VTBL struct IIPolInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPolInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIPolInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIPolInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIPolInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIPolInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIPolInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIPolInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIPolInterface_ClosePolDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> ClosePolDevice(This,lChIndex) ) 

#define IIPolInterface_ResetPolDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> ResetPolDevice(This,lChIndex) ) 

#define IIPolInterface_GetPolCurrentPOSPolarizer(This,lChIndex,pdblAlphaP,pdblAlphaQ,pdblAlphaH)	\
    ( (This)->lpVtbl -> GetPolCurrentPOSPolarizer(This,lChIndex,pdblAlphaP,pdblAlphaQ,pdblAlphaH) ) 

#define IIPolInterface_SetPolALL(This,lChIndex,alphaP,alphaQ,alp)	\
    ( (This)->lpVtbl -> SetPolALL(This,lChIndex,alphaP,alphaQ,alp) ) 

#define IIPolInterface_SetPolDiagonalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    ( (This)->lpVtbl -> SetPolDiagonalAngles(This,lChIndex,AlphaPMax,Wavelength) ) 

#define IIPolInterface_SetPolHorizontalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    ( (This)->lpVtbl -> SetPolHorizontalAngles(This,lChIndex,AlphaPMax,Wavelength) ) 

#define IIPolInterface_SetPolPOSHalf(This,lChIndex,alpha)	\
    ( (This)->lpVtbl -> SetPolPOSHalf(This,lChIndex,alpha) ) 

#define IIPolInterface_SetPolPOSPolarizer(This,lChIndex,alpha)	\
    ( (This)->lpVtbl -> SetPolPOSPolarizer(This,lChIndex,alpha) ) 

#define IIPolInterface_SetPolPOSQuarter(This,lChIndex,alpha)	\
    ( (This)->lpVtbl -> SetPolPOSQuarter(This,lChIndex,alpha) ) 

#define IIPolInterface_SetPolRightHandCircularAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    ( (This)->lpVtbl -> SetPolRightHandCircularAngles(This,lChIndex,AlphaPMax,Wavelength) ) 

#define IIPolInterface_SetPolVerticalAngles(This,lChIndex,AlphaPMax,Wavelength)	\
    ( (This)->lpVtbl -> SetPolVerticalAngles(This,lChIndex,AlphaPMax,Wavelength) ) 

#define IIPolInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScanInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScanInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScanInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScanInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScanInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrepareScan )( 
            IScanInterface * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteScan )( 
            IScanInterface * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawDataPtr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseScan )( 
            IScanInterface * This,
            /* [in] */ long lTLSChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoScanRef )( 
            IScanInterface * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoScan )( 
            IScanInterface * This,
            /* [in] */ long lTLSChIndex,
            /* [in] */ long lpScanRawData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCalILResult )( 
            IScanInterface * This,
            /* [in] */ long lpScanResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCalILAndPDLResult )( 
            IScanInterface * This,
            /* [in] */ long lpScanResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseAllocStruct )( 
            IScanInterface * This,
            /* [in] */ long lpStructPtr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IScanInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IScanInterfaceVtbl;

    interface IScanInterface
    {
        CONST_VTBL struct IScanInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScanInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScanInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScanInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScanInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScanInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScanInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScanInterface_PrepareScan(This,lTLSChIndex,lpScanParam)	\
    ( (This)->lpVtbl -> PrepareScan(This,lTLSChIndex,lpScanParam) ) 

#define IScanInterface_ExecuteScan(This,lTLSChIndex,lpScanRawDataPtr)	\
    ( (This)->lpVtbl -> ExecuteScan(This,lTLSChIndex,lpScanRawDataPtr) ) 

#define IScanInterface_ReleaseScan(This,lTLSChIndex)	\
    ( (This)->lpVtbl -> ReleaseScan(This,lTLSChIndex) ) 

#define IScanInterface_DoScanRef(This,lTLSChIndex,lpScanRawData)	\
    ( (This)->lpVtbl -> DoScanRef(This,lTLSChIndex,lpScanRawData) ) 

#define IScanInterface_DoScan(This,lTLSChIndex,lpScanRawData)	\
    ( (This)->lpVtbl -> DoScan(This,lTLSChIndex,lpScanRawData) ) 

#define IScanInterface_GetCalILResult(This,lpScanResult)	\
    ( (This)->lpVtbl -> GetCalILResult(This,lpScanResult) ) 

#define IScanInterface_GetCalILAndPDLResult(This,lpScanResult)	\
    ( (This)->lpVtbl -> GetCalILAndPDLResult(This,lpScanResult) ) 

#define IScanInterface_ReleaseAllocStruct(This,lpStructPtr)	\
    ( (This)->lpVtbl -> ReleaseAllocStruct(This,lpStructPtr) ) 

#define IScanInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ double *dbSetPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChamberCurrentTemp( 
            /* [in] */ long lChIndex,
            /* [out] */ double *dbCurrTemp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChamberInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChamberInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChamberInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChamberInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChamberInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChamberInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChamberInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChamberInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseChamberDevice )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChamberRunStop )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChamberRunStart )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChamberSetPoint )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ double dbSetPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChamberSetPoint )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *dbSetPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChamberCurrentTemp )( 
            IChamberInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ double *dbCurrTemp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IChamberInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IChamberInterfaceVtbl;

    interface IChamberInterface
    {
        CONST_VTBL struct IChamberInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChamberInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IChamberInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IChamberInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IChamberInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IChamberInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IChamberInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IChamberInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IChamberInterface_CloseChamberDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseChamberDevice(This,lChIndex) ) 

#define IChamberInterface_SetChamberRunStop(This,lChIndex)	\
    ( (This)->lpVtbl -> SetChamberRunStop(This,lChIndex) ) 

#define IChamberInterface_SetChamberRunStart(This,lChIndex)	\
    ( (This)->lpVtbl -> SetChamberRunStart(This,lChIndex) ) 

#define IChamberInterface_SetChamberSetPoint(This,lChIndex,dbSetPoint)	\
    ( (This)->lpVtbl -> SetChamberSetPoint(This,lChIndex,dbSetPoint) ) 

#define IChamberInterface_GetChamberSetPoint(This,lChIndex,dbSetPoint)	\
    ( (This)->lpVtbl -> GetChamberSetPoint(This,lChIndex,dbSetPoint) ) 

#define IChamberInterface_GetChamberCurrentTemp(This,lChIndex,dbCurrTemp)	\
    ( (This)->lpVtbl -> GetChamberCurrentTemp(This,lChIndex,dbCurrTemp) ) 

#define IChamberInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ BSTR *pBuffer,
            /* [in] */ DWORD dwBufferSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSerial( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenSerial( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIComDevInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIComDevInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIComDevInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIComDevInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIComDevInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIComDevInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIComDevInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIComDevInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteBuffer )( 
            IIComDevInterface * This,
            /* [in] */ long lChIndex,
            /* [in] */ BSTR pBuffer,
            /* [in] */ DWORD dwBufferSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadBuffer )( 
            IIComDevInterface * This,
            /* [in] */ long lChIndex,
            /* [out] */ BSTR *pBuffer,
            /* [in] */ DWORD dwBufferSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseSerial )( 
            IIComDevInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenSerial )( 
            IIComDevInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IIComDevInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IIComDevInterfaceVtbl;

    interface IIComDevInterface
    {
        CONST_VTBL struct IIComDevInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIComDevInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIComDevInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIComDevInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIComDevInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIComDevInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIComDevInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIComDevInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIComDevInterface_WriteBuffer(This,lChIndex,pBuffer,dwBufferSize)	\
    ( (This)->lpVtbl -> WriteBuffer(This,lChIndex,pBuffer,dwBufferSize) ) 

#define IIComDevInterface_ReadBuffer(This,lChIndex,pBuffer,dwBufferSize)	\
    ( (This)->lpVtbl -> ReadBuffer(This,lChIndex,pBuffer,dwBufferSize) ) 

#define IIComDevInterface_CloseSerial(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseSerial(This,lChIndex) ) 

#define IIComDevInterface_OpenSerial(This,lChIndex)	\
    ( (This)->lpVtbl -> OpenSerial(This,lChIndex) ) 

#define IIComDevInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIComDevInterface_INTERFACE_DEFINED__ */


#ifndef __IISwitchBoxInterface_INTERFACE_DEFINED__
#define __IISwitchBoxInterface_INTERFACE_DEFINED__

/* interface IISwitchBoxInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IISwitchBoxInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE62156F-2AF7-4DD0-BB5E-AAE25A0B4BFA")
    IISwitchBoxInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenSwitchDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSwitchDevice( 
            /* [in] */ long lChIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SwitchPort2Port( 
            /* [in] */ int lChIndex,
            /* [in] */ int nInputPort,
            /* [in] */ int nOutputPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastMessage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IISwitchBoxInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IISwitchBoxInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IISwitchBoxInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IISwitchBoxInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IISwitchBoxInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IISwitchBoxInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IISwitchBoxInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IISwitchBoxInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenSwitchDevice )( 
            IISwitchBoxInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseSwitchDevice )( 
            IISwitchBoxInterface * This,
            /* [in] */ long lChIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SwitchPort2Port )( 
            IISwitchBoxInterface * This,
            /* [in] */ int lChIndex,
            /* [in] */ int nInputPort,
            /* [in] */ int nOutputPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastMessage )( 
            IISwitchBoxInterface * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IISwitchBoxInterfaceVtbl;

    interface IISwitchBoxInterface
    {
        CONST_VTBL struct IISwitchBoxInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IISwitchBoxInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IISwitchBoxInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IISwitchBoxInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IISwitchBoxInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IISwitchBoxInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IISwitchBoxInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IISwitchBoxInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IISwitchBoxInterface_OpenSwitchDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> OpenSwitchDevice(This,lChIndex) ) 

#define IISwitchBoxInterface_CloseSwitchDevice(This,lChIndex)	\
    ( (This)->lpVtbl -> CloseSwitchDevice(This,lChIndex) ) 

#define IISwitchBoxInterface_SwitchPort2Port(This,lChIndex,nInputPort,nOutputPort)	\
    ( (This)->lpVtbl -> SwitchPort2Port(This,lChIndex,nInputPort,nOutputPort) ) 

#define IISwitchBoxInterface_get_LastMessage(This,pVal)	\
    ( (This)->lpVtbl -> get_LastMessage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IISwitchBoxInterface_INTERFACE_DEFINED__ */


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

EXTERN_C const CLSID CLSID_ISwitchBoxInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("4885F744-A490-42F0-8FAF-7F0F5B90FBC6")
ISwitchBoxInterface;
#endif
#endif /* __UDLSERVERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


