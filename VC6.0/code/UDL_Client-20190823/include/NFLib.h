
#ifndef NF_CALC_LIB_H
#define	NF_CALC_LIB_H

#define	MANUAL_FIX					0
#define	AUTO_FIX					1

#define	AVE_MEASURE_RBW				0
#define	ACT_MEASURE_RBW				1
#define	CAL_SETTING_RBW				2

#define	MAX_CH_COUNT				128

typedef struct tagScanSetting
{
	BYTE	m_bExcludeSourceASE;			// 0: ����NFʱ����Դ��SSEӰ��
											// 1: ����NFʱȥ��SSE

	BYTE	m_bIncludeShotNosie;			// 0: ����NFʱ����Shot NoiseӰ��
											// 1: ����NFʱ����Shot NoiseӰ��

	BYTE	m_bInterpolationMode;			// 0: �ֶ�ѡȡ��ֵ�����������ֵ��m_dblInterpolationVal����
											// 1: �Զ�ѡȡ��ֵ���

	BYTE	m_bNFCalculationRBW;			// 0: ����NFʱ����ƽ������RBW
											// 1: ����NFʱ����ʵ�ʼ���RBW
											// 2: ����NFʱ����ɨ�����õ�RBW��m_dblRBWֵ

	double	m_dblInterpolationVal;			// �ֶ����õĲ�ֵ�������m_bInterpolationModeΪ0ʱ��Ч
	double	m_dblStartWL;					// ��ʼɨ�貨������ֵ
	double	m_dblStopWL;					// ��ֹɨ�貨������ֵ
	double	m_dblRBW;						// ɨ�����õ�RBW����m_bNFCalculationRBWΪ2ʱ��Ч

	double	m_dblSrcOffset;					// ɨԴͨ��offset
	double	m_dblAmpOffset;					// ɨ�Ŵ���ͨ��offset
}stScanSetting, *pstScanSetting;

typedef struct tagEDFAResult
{
	WORD	m_wChCount;						// ͨ������

	double	m_dblSumSrcSigPwr;				// Դ������⹦�� (dBm)
	double	m_dblSumAmpSigPwr;				// �Ŵ���������⹦�� (dBm)
	double	m_dblSunSigGain;				// �Ŵ��������� (dB)

	double	m_dblMaxNF;						// ���NF (dB)
	double	m_dblMinGain;					// ��С���� (dB)
	double	m_dblMaxGain;					// ������� (dB)
	double	m_dblGainFlatness;				// ����ƽ̹�� (dB) = ������� - ��С����
	
	double	m_pdblChWL[MAX_CH_COUNT];		// ��ͨ������
	double	m_pdblSrcPwr[MAX_CH_COUNT];		// ��ͨ������⹦��
	double	m_pdblAmpPwr[MAX_CH_COUNT];		// ��ͨ���Ŵ����������
	double	m_pdblASEPwr[MAX_CH_COUNT];		// ��ͨ��ASE����
	double	m_pdblChGain[MAX_CH_COUNT];		// ��ͨ������
	double	m_pdblChNF[MAX_CH_COUNT];		// ��ͨ��NF
	double	m_pdblActualRBW[MAX_CH_COUNT];	// ʵ��RBW

}stEDFAResult, *pstEDFAResult;

extern "C" _declspec(dllexport) BOOL GetNormalModeEDFAResult(stScanSetting MyScanSetting,	// ɨ���趨����
													 pstEDFAResult pTestingResult,	// EDFA������
													 double* m_pdblScanSrcData,		// Դ����ɨ������ (������ɨ��������+offset)
													 double* m_pdblScanAmpData,		// �Ŵ������ɨ������ (������ɨ��������+offset)
													 WORD m_wScanDataCout);			// ɨ�����ݵ�����

extern "C" _declspec(dllexport) double GetSourceOffset(double* pdblScanData,		// Դ����/�Ŵ������ɨ������ (������ɨ��������+offset)
													   WORD wDataPoint,				// ɨ�����ݵ�����
													   double dblTargetPower);		// Ŀ��⹦��

extern "C" _declspec(dllexport) double GetSrcChPower(double dblStartWL,				// ��ʼɨ�貨������ֵ
													 double dblStopWL,				// ��ֹɨ�貨������ֵ
													 double dblOffset,				// ɨԴͨ��offset
													 WORD wDataPoint,				// ɨ�����ݵ�����
													 double* pdblScanData,			// Դ����ɨ������ (������ɨ��������+offset)
													 double* pdblChWL,				// ��ͨ������
													 double* pdblChPower,			// ��ͨ������⹦��
													 WORD* pwChCount);				// ͨ������
#endif