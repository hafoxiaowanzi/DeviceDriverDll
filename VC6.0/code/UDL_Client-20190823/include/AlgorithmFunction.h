// AlgorithmFunction.h: interface for the CAlgorithmFunction class.
// 该类包含各种算法函数，后续会将用到的基本算法函数加入该类
// 作为通用算法类
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHMFUNCTION_H__229A1D07_785F_4F6B_B71E_ABCB7AB57DB5__INCLUDED_)
#define AFX_ALGORITHMFUNCTION_H__229A1D07_785F_4F6B_B71E_ABCB7AB57DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "hearder.h"

class DLLEXPORT CAlgorithmFunction  
{
public:
	CAlgorithmFunction();
	virtual ~CAlgorithmFunction();
	void LinearFitRaw(double *pdblSrcX, double *pdblSrcY, int nSrcLen, double *pdblTarX,int nTargetLen,double *pdblTarY);
	double Sum(double* srcX,int nCount);
	double SumProduct(double* srcX,double *srcY,int nCount);
	void GetWeightedMeanResult(double *pdbSrx,double* pdbSrcY,int nCount,int nPoint);
	void GetMergeArray(double *pdbFirstArry,double* pdbSecondArry,int nFirstRange,int nDtValidRange,int nPointCount);
	BOOL JudgePowerRangeIsOK(double * pdbPowerData,int nPoint);

};

#endif // !defined(AFX_ALGORITHMFUNCTION_H__229A1D07_785F_4F6B_B71E_ABCB7AB57DB5__INCLUDED_)
