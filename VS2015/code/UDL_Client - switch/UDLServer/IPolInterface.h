// S_FALSE.h : Declaration of the CS_FALSE

#ifndef __IPOLINTERFACE_H_
#define __IPOLINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CS_FALSE
class ATL_NO_VTABLE CIPolInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIPolInterface, &CLSID_IPolInterface>,
	public IDispatchImpl<IIPolInterface, &IID_IIPolInterface, &LIBID_UDLSERVERLib>
{
public:
	CIPolInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CIPOLINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIPolInterface)
	COM_INTERFACE_ENTRY(IIPolInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// CIPolInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SetPolVerticalAngles)(/*[in]*/long lChIndex,/*[in]*/double AlphaPMax,/*[in]*/double Wavelength);
	STDMETHOD(SetPolRightHandCircularAngles)(/*[in]*/long lChIndex,/*[in]*/double AlphaPMax,/*[in]*/double Wavelength);
	STDMETHOD(SetPolPOSQuarter)(/*[in]*/long lChIndex,/*[in]*/double alpha);
	STDMETHOD(SetPolPOSPolarizer)(/*[in]*/long lChIndex,/*[in]*/double alpha);
	STDMETHOD(SetPolPOSHalf)(/*[in]*/long lChIndex,/*[in]*/double alpha);
	STDMETHOD(SetPolHorizontalAngles)(/*[in]*/long lChIndex,/*[in]*/double AlphaPMax,/*[in]*/double Wavelength);
	STDMETHOD(SetPolDiagonalAngles)(/*[in]*/long lChIndex,/*[in]*/double AlphaPMax,/*[in]*/double Wavelength);
	STDMETHOD(SetPolALL)(/*[in]*/long lChIndex,/*[in]*/double alphaP,/*[in]*/double alphaQ,/*[in]*/double alp);
	STDMETHOD(GetPolCurrentPOSPolarizer)(/*[in]*/long lChIndex,/*[out]*/double *pdblAlphaP,/*[out]*/double *pdblAlphaQ,/*[out]*/double *pdblAlphaH);
	STDMETHOD(ResetPolDevice)(/*[in]*/long lChIndex);
	STDMETHOD(ClosePolDevice)(/*[in]*/ long lChIndex);
	BSTR m_strMessage;
};

#endif //__IPOLINTERFACE_H_
