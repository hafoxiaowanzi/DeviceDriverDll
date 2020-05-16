
#ifndef NF_CALC_LIB_H
#define	NF_CALC_LIB_H

#define	MANUAL_FIX					0
#define	AUTO_FIX					1
#define RBW                         0.2
#define	AVE_MEASURE_RBW				0
#define	ACT_MEASURE_RBW				1
#define	CAL_SETTING_RBW				2

#define	MAX_CH_COUNT				128

#define ERROR_NUM1                  0       //实际光源通道和传的通道数不一致
#define ERROR_NUM2                  1       //实际光源通道和传的波长不一致

typedef struct tagScanSetting
{
	BYTE	m_bExcludeSourceASE;			// 0: 计算NF时不管源的SSE影响
											// 1: 计算NF时去掉SSE

	BYTE	m_bIncludeShotNosie;			// 0: 计算NF时不管Shot Noise影响
											// 1: 计算NF时包含Shot Noise影响

	BYTE	m_bInterpolationMode;			// 0: 手动选取插值间隔，具体间隔值由m_dblInterpolationVal决定
											// 1: 自动选取插值间隔

	BYTE	m_bNFCalculationRBW;			// 0: 计算NF时采用平均计算RBW
											// 1: 计算NF时采用实际计算RBW
											// 2: 计算NF时采用扫描设置的RBW即m_dblRBW值

	double	m_dblInterpolationVal;			// 手动设置的插值间隔，仅m_bInterpolationMode为0时有效
	double	m_dblStartWL;					// 起始扫描波长设置值
	double	m_dblStopWL;					// 终止扫描波长设置值
	double	m_dblRBW;						// 扫描设置的RBW，仅m_bNFCalculationRBW为2时有效

	double	m_dblSrcOffset;					// 扫源通道offset
	double	m_dblAmpOffset;					// 扫放大器通道offset

	double  m_pdblChannelWL;		        // 光源实际波长通道
	double  m_pdblASEIntervalL[MAX_CH_COUNT]; // ASE取点间距左右->奇偶/m_pdblASEIntervalL=NULL,使用默认值
	double  m_pdblASEIntervalR[MAX_CH_COUNT]; // ASE取点间距左右->奇偶/m_pdblASEIntervalR=NULL,使用默认值

	double  m_pdblInputWDL[MAX_CH_COUNT];	  // InputWDL
	double  m_pdblOutputWDL[MAX_CH_COUNT];	  // OutputWDL

}stScanSetting, *pstScanSetting;

typedef struct tagEDFAResult
{
	WORD	m_wChCount;						// 通道数量

	double	m_dblSumSrcSigPwr;				// 源总输入光功率 (dBm)
	double	m_dblSumAmpSigPwr;				// 放大器总输出光功率 (dBm)
	double	m_dblSunSigGain;				// 放大器总增益 (dB)

	double	m_dblMaxNF;						// 最大NF (dB)
	double	m_dblMinGain;					// 最小增益 (dB)
	double	m_dblMaxGain;					// 最大增益 (dB)
	double	m_dblGainFlatness;				// 增益平坦度 (dB) = 最大增益 - 最小增益
	
	double	m_pdblChWL[MAX_CH_COUNT];		// 各通道波长
	double	m_pdblSrcPwr[MAX_CH_COUNT];		// 各通道输入光功率
	double	m_pdblAmpPwr[MAX_CH_COUNT];		// 各通道放大器输出功率
	double	m_pdblASEPwr[MAX_CH_COUNT];		// 各通道ASE功率
	double	m_pdblChGain[MAX_CH_COUNT];		// 各通道增益
	double	m_pdblChNF[MAX_CH_COUNT];		// 各通道NF
	double	m_pdblActualRBW[MAX_CH_COUNT];	// 实际RBW
	double	m_pdblChOSNR[MAX_CH_COUNT];	    // 各通道OSNR

}stEDFAResult, *pstEDFAResult;


extern "C" _declspec(dllexport) BOOL GetAdoEDFAResult(stScanSetting MyScanSetting,	    // 扫描设定参数
													 pstEDFAResult pTestingResult,	// EDFA计算结果
													 double* m_pdblScanSrcData,		// 源输入扫描数据 (无需在扫描数据上+offset)
													 double* m_pdblScanAmpData,		// 放大器输出扫描数据 (无需在扫描数据上+offset)
													 double* m_pdblScanRBWData,     // OSA RBW数据
													 WORD m_wScanDataCout);			// 扫描数据点数量

extern "C" _declspec(dllexport) BOOL GetNormalModeEDFAResult(stScanSetting MyScanSetting,	// 扫描设定参数
													 pstEDFAResult pTestingResult,	// EDFA计算结果
													 double* m_pdblScanSrcData,		// 源输入扫描数据 (无需在扫描数据上+offset)
													 double* m_pdblScanAmpData,		// 放大器输出扫描数据 (无需在扫描数据上+offset)
													 WORD m_wScanDataCout);			// 扫描数据点数量

extern "C" _declspec(dllexport) double GetSourceOffset(double* pdblScanData,		// 源输入/放大器输出扫描数据 (无需在扫描数据上+offset)
													   WORD wDataPoint,				// 扫描数据点数量
													   double dblTargetPower);		// 目标光功率

extern "C" _declspec(dllexport) double GetSrcChPower(double dblStartWL,				// 起始扫描波长设置值
													 double dblStopWL,				// 终止扫描波长设置值
													 double dblOffset,				// 扫源通道offset
													 WORD wDataPoint,				// 扫描数据点数量
													 double* pdblScanData,			// 源输入扫描数据 (无需在扫描数据上+offset)
													 double* pdblChWL,				// 各通道波长
													 double* pdblChPower,			// 各通道输入光功率
													 WORD* pwChCount);				// 通道数量
#endif

