#ifndef  __SCAN_HEARDER_H__

#define  __SCAN_HEARDER_H__

#ifndef DLLEXPORT
#define DLLEXPORT   __declspec( dllexport )
#endif
#ifndef DllImport
#define DllImport   __declspec( dllimport )
#endif


//定义设定扫描时激光器与功率及参数的结构体
//在原来的结构体的基础上重新定义
//将结构标准化
typedef struct tagScanParam
{                                 
    BOOL    m_bDoPDL;                //是否带PDL;
	int     m_nPolChIndex;           //偏振控制器的channel索引
	int     m_nPDLType;              //PDL扫描类型                
	int     m_nSpeed;                //扫描速度   
	int     m_nAvgTime;              //功率计采样平均时间
	int	m_dwNumberOfScan;            //扫描次数
	int	m_dwChannelNumber;           //扫描功率计通道
	int m_dwChannelCfgHigh;          //这里保留这两个参数，用来兼容8164采用高光或者低光进行扫描
	int	m_dwChannelCfgLow;           //功率计读取通道扫描数据标志，0001--1，0010-2,0011-3  
	int	m_dwSampleCount;             //扫描的点数 
	double	m_dblTLSPower;           //激光器出光功率
	double  m_dblPWMPower; 		     //功率计探测功率
	double  m_dbAlphaAngle;          //偏振角度
	double	m_dblStartWL;            //扫描开始波长
	double  m_dblStopWL;             //扫描停止波长  
	double  m_dblStepSize;           //扫描步长 
	
} stScanParam, *PScanParam;

//定义获得扫描原始数据的结构体
typedef struct tagOp816XRawData
{
	double		*m_pdblWavelengthArray;  // the array of WL
	PDWORD		m_pdwDataArrayAddr;      // the array of power point 
} stOp816XRawData, *POp816XRawData;

#endif