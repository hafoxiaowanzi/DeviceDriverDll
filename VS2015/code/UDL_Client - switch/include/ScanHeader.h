#ifndef  __SCAN_HEARDER_H__

#define  __SCAN_HEARDER_H__

#ifndef DLLEXPORT
#define DLLEXPORT   __declspec( dllexport )
#endif
#ifndef DllImport
#define DllImport   __declspec( dllimport )
#endif


//�����趨ɨ��ʱ�������빦�ʼ������Ľṹ��
//��ԭ���Ľṹ��Ļ��������¶���
//���ṹ��׼��
typedef struct tagScanParam
{                                 
    BOOL    m_bDoPDL;                //�Ƿ��PDL;
	int     m_nPolChIndex;           //ƫ���������channel����
	int     m_nPDLType;              //PDLɨ������                
	int     m_nSpeed;                //ɨ���ٶ�   
	int     m_nAvgTime;              //���ʼƲ���ƽ��ʱ��
	int	m_dwNumberOfScan;            //ɨ�����
	int	m_dwChannelNumber;           //ɨ�蹦�ʼ�ͨ��
	int m_dwChannelCfgHigh;          //���ﱣ����������������������8164���ø߹���ߵ͹����ɨ��
	int	m_dwChannelCfgLow;           //���ʼƶ�ȡͨ��ɨ�����ݱ�־��0001--1��0010-2,0011-3  
	int	m_dwSampleCount;             //ɨ��ĵ��� 
	double	m_dblTLSPower;           //���������⹦��
	double  m_dblPWMPower; 		     //���ʼ�̽�⹦��
	double  m_dbAlphaAngle;          //ƫ��Ƕ�
	double	m_dblStartWL;            //ɨ�迪ʼ����
	double  m_dblStopWL;             //ɨ��ֹͣ����  
	double  m_dblStepSize;           //ɨ�貽�� 
	
} stScanParam, *PScanParam;

//������ɨ��ԭʼ���ݵĽṹ��
typedef struct tagOp816XRawData
{
	double		*m_pdblWavelengthArray;  // the array of WL
	PDWORD		m_pdwDataArrayAddr;      // the array of power point 
} stOp816XRawData, *POp816XRawData;

#endif