// MuellerAlpahaPCompensate.cpp: implementation of the MuellerAlpahaPCompensate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\POC.H"
#include "..\\include\\MuellerAlpahaPCompensate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MuellerAlpahaPCompensate::MuellerAlpahaPCompensate()
{

}

MuellerAlpahaPCompensate::~MuellerAlpahaPCompensate()
{

}

//Get the angles under Linear Horizontal state according to AlphaPMax
BOOL MuellerAlpahaPCompensate::GetLinearHorizontalAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH)
{
	*alphaP=AlphaPMax;
	*alphaQ=AlphaPMax;
	*alphaH=AlphaPMax;
	return TRUE;
}

//Get the angles under Linear Vertical state according to AlphaPMax
BOOL MuellerAlpahaPCompensate::GetLinearVerticalAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH)
{
	*alphaP=AlphaPMax;
	//*alphaQ=AlphaPMax;
	//*alphaH=AlphaPMax+45;
	int index; double wl=Wavelength;
	for (index=0;index<10;index++){
		if (wl <= AngleCompensationTable[index].wl ) break;
	}

	if (index<=0) {
		*alphaQ=AngleCompensationTable[index].Q_LinearVertical; 
		*alphaH=AngleCompensationTable[index].H_LinearVertical; 
	}
	else if (index>=10) {
		*alphaQ=AngleCompensationTable[9].Q_LinearVertical; 
		*alphaH=AngleCompensationTable[9].H_LinearVertical; 
	}
	else{
		double factor=(wl - AngleCompensationTable[index-1].wl)/(AngleCompensationTable[index].wl - AngleCompensationTable[index-1].wl) ;
		*alphaQ=AngleCompensationTable[index-1].Q_LinearVertical +
			 (AngleCompensationTable[index].Q_LinearVertical - AngleCompensationTable[index-1].Q_LinearVertical) * factor;
		*alphaH=AngleCompensationTable[index-1].H_LinearVertical +
			 (AngleCompensationTable[index].H_LinearVertical - AngleCompensationTable[index-1].H_LinearVertical) * factor;
	}
	
	*alphaQ+=*alphaP; *alphaH+=*alphaP;
	return TRUE;

}

//Get the angles under Linear Diagonal state according to AlphaPMax
BOOL MuellerAlpahaPCompensate::GetLinearDiagonalAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH)
{
	*alphaP=AlphaPMax;
	//*alphaQ=AlphaPMax;
	//*alphaH=AlphaPMax+22.5;
	int index; double wl=Wavelength;
	for (index=0;index<10;index++){
		if (wl <= AngleCompensationTable[index].wl ) break;
	}

	if (index<=0) {
		*alphaQ=AngleCompensationTable[index].Q_LinearDiagonal; 
		*alphaH=AngleCompensationTable[index].H_LinearDiagonal; 
	}
	else if (index>=10) {
		*alphaQ=AngleCompensationTable[9].Q_LinearDiagonal; 
		*alphaH=AngleCompensationTable[9].H_LinearDiagonal; 
	}
	else{
		double factor=(wl - AngleCompensationTable[index-1].wl)/(AngleCompensationTable[index].wl - AngleCompensationTable[index-1].wl) ;
		*alphaQ=AngleCompensationTable[index-1].Q_LinearDiagonal +
			 (AngleCompensationTable[index].Q_LinearDiagonal - AngleCompensationTable[index-1].Q_LinearDiagonal) * factor;
		*alphaH=AngleCompensationTable[index-1].H_LinearDiagonal +
			 (AngleCompensationTable[index].H_LinearDiagonal - AngleCompensationTable[index-1].H_LinearDiagonal) * factor;
	}
	*alphaQ+=*alphaP; *alphaH+=*alphaP;
	return TRUE;
}

//Get the angles under Linear Right Hand state according to AlphaPMax
BOOL MuellerAlpahaPCompensate::GetLinearRightHandCircularAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH)
{
	*alphaP=AlphaPMax;
	//*alphaQ=AlphaPMax+45;
	//*alphaH=AlphaPMax;
	int index; double wl=Wavelength;
	for (index=0;index<10;index++){
		if (wl <= AngleCompensationTable[index].wl ) break;
	}

	if (index<=0) {
		*alphaQ=AngleCompensationTable[index].Q_RHCircular; 
		*alphaH=AngleCompensationTable[index].H_RHCircular; 
	}
	else if (index>=10) {
		*alphaQ=AngleCompensationTable[9].Q_RHCircular; 
		*alphaH=AngleCompensationTable[9].H_RHCircular; 
	}
	else{
		double factor=(wl - AngleCompensationTable[index-1].wl)/(AngleCompensationTable[index].wl - AngleCompensationTable[index-1].wl) ;
		*alphaQ=AngleCompensationTable[index-1].Q_RHCircular +
			 (AngleCompensationTable[index].Q_RHCircular - AngleCompensationTable[index-1].Q_RHCircular) * factor;
		*alphaH=AngleCompensationTable[index-1].H_RHCircular +
			 (AngleCompensationTable[index].H_RHCircular - AngleCompensationTable[index-1].H_RHCircular) * factor;
	}
	
	*alphaQ+=*alphaP; *alphaH+=*alphaP;
	return TRUE;
	
}