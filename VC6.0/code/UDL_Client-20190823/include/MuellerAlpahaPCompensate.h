// MuellerAlpahaPCompensate.h: interface for the MuellerAlpahaPCompensate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUELLERALPAHAPCOMPENSATE_H__FE0F4123_9D52_11D6_B27F_00E01808A7F0__INCLUDED_)
#define AFX_MUELLERALPAHAPCOMPENSATE_H__FE0F4123_9D52_11D6_B27F_00E01808A7F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static struct {
	double wl;
	double Q_LinearVertical;
	double H_LinearVertical;

	double Q_LinearDiagonal;
	double H_LinearDiagonal;

	double Q_RHCircular;
	double H_RHCircular;

} AngleCompensationTable[10]={ 
	{1260.0, -21.2,  31.7, -24.2,   3.9,  64.7,   7.4},
	{1280.0, -19.6,  32.9, -21.2,   6.5,  62.9,   5.1},
	{1300.0, -17.9,  34.0, -18.5,   8.9,  61.2,   3.0},
	{1320.0, -16.3,  35.1, -16.0,  11.0,  59.6,   1.0},
	{1340.0, -14.7,  36.2, -13.9,  12.8,  58.1,  -0.7},
	{1500.0,  -2.7,  43.6,  -2.0,  21.4,  47.4, -12.4},
	{1520.0,  -1.4,  44.3,  -1.0,  22.0,  46.2, -13.8},
	{1540.0,   0.0,  45.0,   0.0,  22.5,  45.0, -15.1},
	{1560.0,   1.2,  45.6,   0.8,  22.9,  44.0, -16.5},
	{1580.0,   2.5,  46.2,   1.7,  23.3,  42.9, -17.1}
};

class MuellerAlpahaPCompensate 
{
public:
	MuellerAlpahaPCompensate();
	virtual ~MuellerAlpahaPCompensate();

	BOOL GetLinearHorizontalAngles(double AlphaPMax, double Wavelength, double *alphaP,double *alphaQ,double *alphaH);
	BOOL GetLinearRightHandCircularAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH);
	BOOL GetLinearDiagonalAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH);
	BOOL GetLinearVerticalAngles(double AlphaPMax, double Wavelength, double *alphaP, double *alphaQ, double *alphaH);

};

#endif // !defined(AFX_MUELLERALPAHAPCOMPENSATE_H__FE0F4123_9D52_11D6_B27F_00E01808A7F0__INCLUDED_)
