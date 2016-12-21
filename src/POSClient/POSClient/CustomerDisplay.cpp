// MyPrinter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CustomerDisplay.h"
#include "StringConvert.h"
#include "POSClient.h"

// CMyPrinter

CustomerDisplay::CustomerDisplay()
{
	m_strPort = _T("");
	m_BaudRate = 9600;
	m_ByteSize = 8;
	m_Parity = NOPARITY;
	m_StopBits = ONESTOPBIT;
	m_hPort = INVALID_HANDLE_VALUE;
	m_nDeviceType=0;
}

CustomerDisplay::~CustomerDisplay()
{
}


//strPort:com1, BaudRate���ò�����:9600,bytesize����λ, 8bit:8,parityУ��, ��,StopBits:ֹͣλ, 1λ
//ture :�򿪳ɹ���false����ʧ��
BOOL CustomerDisplay::Open(CString strPort, DWORD BaudRate,BYTE ByteSize,BYTE Parity,BYTE StopBits)
{
		BOOL bSuccess;
		DCB dcb;
		COMMTIMEOUTS TimeOuts;
		//�򿪶˿�
		m_hPort = CreateFile(strPort, GENERIC_READ | GENERIC_WRITE,
			0, NULL, 
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL );

		if (m_hPort == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		SetupComm(m_hPort, 1024, 1024);			//���ö˿ڻ���

		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;
		TimeOuts.WriteTotalTimeoutMultiplier = 50;
		TimeOuts.WriteTotalTimeoutConstant = 2000;

		SetCommTimeouts(m_hPort, &TimeOuts);		//���ó�ʱ����		

		bSuccess = GetCommState(m_hPort, &dcb);	//��õ�ǰ��������

		dcb.BaudRate = BaudRate;			//���ò����� 
		dcb.ByteSize = ByteSize;			//����λ, 8bit
		dcb.Parity = Parity;					//У��, ��
		dcb.StopBits = StopBits;				//ֹͣλ, 1λ

		bSuccess = SetCommState(m_hPort, &dcb);	//���ô���
		PurgeComm(m_hPort, PURGE_TXCLEAR);
		return TRUE;
}

//0:��ӡ����1������Ǯ�䣬2�����Բ���
//��ӡ����������������10�����б��ݴ�ӡ����ʹ�ñ��ݴ�ӡ����ӡ������30��˵�����ݴ�ӡ����ʹ��ԭʼ��ӡ��
BOOL CustomerDisplay::Open()
{
	try{
		if(m_strPort.IsEmpty())
			return FALSE;
		return Open(m_strPort,m_BaudRate,m_ByteSize,m_Parity,m_StopBits);
	}
	catch(...)
	{
	}
	return FALSE;

}
BOOL CustomerDisplay::IsOpen()
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;
}

//�ر��豸
void CustomerDisplay::Close()
{
	if(m_hPort != INVALID_HANDLE_VALUE)
	{
		try
		{
			BOOL re = CloseHandle(m_hPort);
			if(re==FALSE)
			{
				LOG4CPLUS_DEBUG(log_pos,"CloseHandle failed GetLastError="<<GetLastError());;
			}
			m_hPort = INVALID_HANDLE_VALUE;

		}
		catch (CException* e)
		{
			LOG4CPLUS_DEBUG(log_pos,"CloseHandle Exception");
		}

	}
}

void CustomerDisplay::Print(CString strOutput)
{
	DWORD iBytesLength;
	char chQueryCode2[512]={0};
	CString2MultiByte(strOutput,chQueryCode2,512);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strlen(chQueryCode2), &iBytesLength, NULL);
}

//���ƴ�ӡ����Ǯ��
void CustomerDisplay::OpenDrawer()
{
	DWORD iBytesLength;
	char chQueryCode2[] = "\x1B\x70\x30\x3C\xF0";
	WriteFile(m_hPort, chQueryCode2, (DWORD)5L, &iBytesLength, NULL);
}
void CustomerDisplay::OpenDrawer2()
{
	DWORD iBytesLength;
	char chQueryCode2[] = "\x1B\x70\x07\x1C";
	WriteFile(m_hPort, chQueryCode2, (DWORD)5L, &iBytesLength, NULL);
}

//����
/************************************************************************/
/*˵����priceΪ��ʾ�ļ۸�type����
(1)��   type=0�������ַ�   ȫ���� 
(2)��   type=1�������ۡ��ַ�   ������������   ȫ���� 
(3)��   type=2�����ܼơ��ַ�   ������������   ȫ���� 
(4)��   type=3�����տ�ַ�   ������������   ȫ���� 
(5)��   type=4�������㡱�ַ�   ������������   ȫ��                                                                     */
/************************************************************************/
BOOL CustomerDisplay::ShowCustomerScreen(double price,int type)
{
	if (type < 0 || type > 4)
	{
		return FALSE;
	}
	DWORD iBytesLength;
	//ESC  Q  A  d1d2d3��dn  CR
	CStringA strPrice;
	strPrice.Format("\x1B\x51\x41%0.2f\x0D",price);
	WriteFile(m_hPort, (LPCSTR)strPrice, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	//ESC  s  n
	CStringA strType;
	strType.Format("\x1B\x73%d",type);
	WriteFile(m_hPort, (LPCSTR)strType, (DWORD)3L, &iBytesLength, NULL);
	return TRUE;

}

BOOL CustomerDisplay::Display(double price,int type)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==0)
	{//LED8
		return ShowCustomerScreen(price,type);
	}
	else if(m_nDeviceType==1)
	{//VFD220
		CString line;
		if(type==1)
		{//����
			line.Format(_T("Price: %0.2f"),price);
		}
		else if(type==2)
		{//�ܼ�
			line.Format(_T("Total: %0.2f"),price);
		}
		else if(type==3)
		{//�տ�
			line.Format(_T("Paid: %0.2f"),price);
		}
		else if(type==4)
		{//����
			line.Format(_T("Change: %0.2f"),price);
		}
		return ShowLine1(line);
	}
	return FALSE;
}
BOOL CustomerDisplay::DisplayPrice(double price,LPCTSTR name)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==0)
	{//LED8
		return ShowCustomerScreen(price,1);
	}
	else if(m_nDeviceType==1)
	{//VFD220
		ShowLine1(name);
		CString line;
		line.Format(_T("Price: %0.2f"),price);
		return ShowLine2(line);
	}
	return FALSE;
}
//ESC  Q  A  d1d2d3����.dn  CR�ڵ�һ����ʾ�ַ�
BOOL CustomerDisplay::ShowLine1(LPCTSTR pText)
{
	DWORD iBytesLength;
	char chQueryCode3[] = "\xCH";//�����Ļ�ϵ������ַ���
	WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
	if(pText==NULL)
		return TRUE;
	CString strPrice;
	strPrice.Format(_T("\x1B\x51\x41%s\x0D"),pText);
	char chQueryCode2[256];
	CString2MultiByte(strPrice,chQueryCode2,256);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	return TRUE;
}
//ESC  Q  B  d1d2d3����.dn  CR�ڵڶ�����ʾ�ַ�
BOOL CustomerDisplay::ShowLine2(LPCTSTR pText)
{
	DWORD iBytesLength;
// 	char chQueryCode3[] = "\xCH";//�����Ļ�ϵ������ַ���
// 	WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
	if(pText==NULL)
		return TRUE;
	CString strPrice;
	strPrice.Format(_T("\x1B\x51\x42%s\x0D"),pText);
	char chQueryCode2[256];
	CString2MultiByte(strPrice,chQueryCode2,256);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	return TRUE;
}
//ESC  Q  D  d1d2d3��dn  CR�ڶ�����ʾ���������ַ�
BOOL CustomerDisplay::ShowRollingText(LPCTSTR pText)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==1)
	{
		DWORD iBytesLength;
		char chQueryCode3[] = "\xCH";//�����Ļ�ϵ������ַ���
		WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
		if(pText==NULL)
			return TRUE;
		CString strText;
		strText.Format(_T("\x1B\x51\x44%s\x0D"),pText);
		char chQueryCode2[256]={0};
		CString2MultiByte(strText,chQueryCode2,256);
		WriteFile(m_hPort, chQueryCode2, (DWORD)strlen(chQueryCode2), &iBytesLength, NULL);
	}
	return TRUE;
}

void CustomerDisplay::SetOpenParam(int type,CString strPort, DWORD BaudRate,BYTE ByteSize,BYTE Parity,BYTE StopBits)
{
	m_strPort = strPort;
	m_BaudRate = BaudRate;
	m_ByteSize = ByteSize;
	m_Parity = Parity;
	m_StopBits = StopBits;
	m_nDeviceType = type;
}
