// IPMInterface.h : Declaration of the CIPMInterface

#ifndef __IPMINTERFACE_H_
#define __IPMINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPMInterface
class ATL_NO_VTABLE CIPMInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIPMInterface, &CLSID_IPMInterface>,
	public IDispatchImpl<IIPMInterface, &IID_IIPMInterface, &LIBID_UDLSERVERLib>
{
public:
	CIPMInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IPMINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIPMInterface)
	COM_INTERFACE_ENTRY(IIPMInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IIPMInterface
public:
	STDMETHOD(SetPMPowerOffset)(/*[in]*/long lChan,/*[in]*/ double newVal);
	STDMETHOD(SetPMMaxMinPowerStop)(/*[in]*/ long lChan);
	STDMETHOD(GetPMMaxMinPower)(/*[in]*/long lChIndex,/*[out]*/double *pdbGetMax,/*[out]*/double *pdbGetMin);
	STDMETHOD(SetPMMaxMinPowerStart)(/*[in]*/long lChan);
	STDMETHOD(CloseDevice)(/*[in]*/long lChan);
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SetZero)(/*[in]*/long lChan);
	STDMETHOD(SetParameters)(/*[in]*/long lChan,/*[in]*/BOOL bAutoRange,/*[in]*/double dblWL,/*[in]*/double dblAvgTime,/*[in]*/double dblPMRange);
	STDMETHOD(GetRangeMode)(/*[in]*/long lChan, /*[out]*/ long *pVal);
	STDMETHOD(SetRangeMode)(/*[in]*/long lChan, /*[in]*/ long newVal);
	STDMETHOD(GetPower)(/*[in]*/long lChan, /*[out, retval]*/ double *pVal);
	STDMETHOD(GetWavelength)(/*[in]*/long lChan, /*[out]*/ double *pVal);
	STDMETHOD(SetWavelength)(/*[in]*/long lChan, /*[in]*/ double newVal);
	STDMETHOD(GetAverageTime)(/*[in]*/long lChan, /*[out]*/ double *pVal);
	STDMETHOD(SetAverageTime)(/*[in]*/long lChan, /*[in]*/ double newVal);
	STDMETHOD(GetUnit)(/*[in]*/long lChan, /*[out]*/ long *pVal);
	STDMETHOD(SetUnit)(/*[in]*/long lChan, /*[in]*/ long newVal);
	BSTR m_strMessage;
};

#endif //__IPMINTERFACE_H_
