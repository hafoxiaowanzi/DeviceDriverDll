// AlgorithmFunction.cpp: implementation of the CAlgorithmFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\AlgorithmFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlgorithmFunction::CAlgorithmFunction()
{

}

CAlgorithmFunction::~CAlgorithmFunction()
{

}
////////////////////////////////////////////////////////////////////
//函数说明:
//    根据输入的X、Y、Target X,采用线性内插方法计算相应的Y，并返回
//    Target Y
//Add by wanxin
////////////////////////////////////////////////////////////////////
void CAlgorithmFunction::LinearFitRaw(double *pdblSrcX, double *pdblSrcY, int nSrcLen, double *pdblTarX,int nTargetLen,double *pdblTarY)
{
	int nPoint1 = -1, nPoint2 = -1;
	double k,c;
	int nCount;

	double x,y;
	double flag=0.0;
	double dblCurBase;
	int nSrcPoint=0;
	nCount =0;
	for ( int i = 0; i < nTargetLen; i++)
	{
		dblCurBase = pdblTarX[i];
		
		if (dblCurBase < pdblSrcX[0])
		{
			nPoint1 = 0;
			nPoint2 = 1;
		}
		else if (dblCurBase > pdblSrcX[nSrcLen-1])
		{
			nPoint1 = nSrcLen-1;
			nPoint2 = nSrcLen-2;
		}
		else 
		{
			flag = (dblCurBase - pdblSrcX[nSrcPoint])*(pdblSrcX[nSrcPoint+1] - dblCurBase);
			while (flag < 0)
			{
				nSrcPoint++;
				if (nSrcPoint >= (nSrcLen-2))
				{
					break;
                }
				flag = (dblCurBase -pdblSrcX[nSrcPoint])*(pdblSrcX[nSrcPoint+1] - dblCurBase);
			}
			nPoint1 = nSrcPoint;
			nPoint2 = nSrcPoint+1;	
		}
		
		x= pdblSrcY[nPoint1];
		y= pdblSrcY[nPoint2];
		
		k = (x - y) / (pdblSrcX[nPoint1] - pdblSrcX[nPoint2]);
		c = pdblSrcY[nPoint2] - k * pdblSrcX[nPoint2];
		pdblTarY[i] = k * pdblTarX[i] + c;
		
	}	
}
///////////////////////////////////////////////////////////
//函数说明:
//    根据输入数组，计算输入数组总和，并返回总和值
//Add by wanxin
///////////////////////////////////////////////////////////
double CAlgorithmFunction::Sum(double* srcX,int nCount)
{
	double dbResult=0.0;
	for (int i=0;i<nCount;i++)
	{
		dbResult += srcX[i];
	}
	return dbResult;
}
////////////////////////////////////////////////////////////
//函数说明:
//    根据输入的X、Y，求X*Y的总和，并返回总和
//Add by wanxin
////////////////////////////////////////////////////////////
double CAlgorithmFunction::SumProduct(double* srcX,double *srcY,int nCount)
{
	double dbResult=0.0;
	for(int i=0;i<nCount;i++)
	{
		dbResult +=srcX[i]*srcY[i];
	}
    return dbResult;
}
///////////////////////////////////////////////////////////////////
//函数说明:
//    加权平均算法,返回Y数组
//Add by wanxin
///////////////////////////////////////////////////////////////////
void CAlgorithmFunction::GetWeightedMeanResult(double *pdbSrx,double* pdbSrcY,int nCount,int nPoint)
{
	double *pdbXAarry=NULL,*pdbYAarry=NULL;
	int nLength = nCount + nPoint;
	if (pdbXAarry == NULL)
	{
        pdbXAarry = new double[nLength];
	}
	
	ZeroMemory(pdbXAarry,sizeof(double)*nLength);
	memcpy(pdbXAarry,pdbSrx,sizeof(double)*nCount);
	if (pdbYAarry == NULL)
	{
		pdbYAarry = new double[nLength];
	}

	ZeroMemory(pdbYAarry,sizeof(double)*nLength);
	memcpy(pdbYAarry,pdbSrcY,sizeof(double)*nCount);
	
	for (int i=0;i<nCount;i++)
	{
		pdbSrcY[i] = SumProduct(pdbXAarry+i,pdbYAarry+i,nPoint)/Sum(pdbXAarry+i,nPoint);
	}
	if (pdbXAarry != NULL) 
	{
		delete [] pdbXAarry;
		pdbXAarry = NULL;
	}
	if (pdbYAarry != NULL) 
	{
		delete [] pdbYAarry;
		pdbYAarry = NULL;
	}	
}
//////////////////////////////////////////////////////////////////////
//函数说明:
//    根据输入pdbFirstArry、pdbSecondArry两个数组，以nRange作为
//分界，合并两个数组，并将合并后的结果保存在pdbSecondArry
//Add by wanxin
//////////////////////////////////////////////////////////////////////
void CAlgorithmFunction::GetMergeArray(double *pdbFirstArry,double* pdbSecondArry,int nFirstRange,int  nDtValidRange,int nPointCount)
{
	double* pdbTemp =NULL;
	double dbMWPower1,dbMWPower2;
	if (pdbTemp ==NULL)
	{
		pdbTemp = (double*)VirtualAlloc(NULL,sizeof(double)*nPointCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	}
	for (int nIndex=0; nIndex < nPointCount;nIndex++)
	{
		
        dbMWPower1 = (double)pow(10,pdbFirstArry[nIndex]/10.0);
		if (dbMWPower1 < 0.0) 
		{
             pdbFirstArry[nIndex] = -90.0;
		}
		dbMWPower2 = (double)pow(10,pdbSecondArry[nIndex]/10.0);
		if (dbMWPower2 < 0.0) 
		{
             pdbSecondArry[nIndex] =-90.0;
		}
		if (pdbFirstArry[nIndex] > (nFirstRange - nDtValidRange+3)) 
		{
			pdbTemp[nIndex] = pdbFirstArry[nIndex] ;
		}
		else if(pdbSecondArry[nIndex] > (nFirstRange - nDtValidRange+3))
		{
			pdbTemp[nIndex] = pdbFirstArry[nIndex];
		}
		else if (dbMWPower1 > 0.0 && dbMWPower2 <0.0)
		{
			pdbTemp[nIndex] = pdbFirstArry[nIndex] ;
		}
		else
		{
            pdbTemp[nIndex] = pdbSecondArry[nIndex];
		}
	}
	//将结果保存在第一个数组中
	memcpy(pdbFirstArry,pdbTemp,sizeof(double)*nPointCount);
	if (pdbTemp !=NULL)
	{
		VirtualFree(pdbTemp,0,MEM_RELEASE);
		pdbTemp = NULL;
	}
}
///////////////////////////////////////////////////////
//函数说明：
//    根据获得功率点判断当前Range是否OK，
//    ok只扫一个Range，不OK扫两个Range叠加
//Add by wanxin
///////////////////////////////////////////////////////
BOOL CAlgorithmFunction::JudgePowerRangeIsOK(double * pdbPowerData,int nPoint)
{
   double dbMWPower;
   for (int nIndex =0;nIndex < nPoint;nIndex ++)
   {
        dbMWPower = (double)pow(10,pdbPowerData[nIndex]/10);
		if (dbMWPower < 0.0)
		{
             return FALSE;
		}
   }
   return TRUE;
}