#pragma once


// CMyPrinter

class CustomerDisplay
{

public:
	CustomerDisplay();
	virtual ~CustomerDisplay();

	BOOL Open(CString strPort, DWORD BaudRate,BYTE ByteSize=8,BYTE Parity = NOPARITY,BYTE StopBits = ONESTOPBIT);
	BOOL Open();
	BOOL IsOpen();
	void Close();

	//��ӡ������ز���
	void Print(CString strOutput);
	void SetOpenParam(int type,CString strPort, DWORD BaudRate = 9600,BYTE ByteSize=8,BYTE Parity=NOPARITY,BYTE StopBits=ONESTOPBIT);
	//Ǯ��Ĳ���
	void OpenDrawer();
	void OpenDrawer2();

	//�˿���ʾ���Ĳ���
	BOOL ShowCustomerScreen(double price,int type=0);
	BOOL ShowLine1(LPCTSTR pText);
	BOOL ShowLine2(LPCTSTR pText);
	BOOL ShowRollingText(LPCTSTR pText);
	BOOL Display(double price,int type);
	BOOL DisplayPrice(double price,LPCTSTR name);

	HANDLE m_hPort;

	CString m_strPort;
	DWORD m_BaudRate;
	BYTE m_ByteSize;
	BYTE m_Parity;
	BYTE m_StopBits;

	int m_nDeviceType;//0- LED8; 1- VFD220; 2-LD220

};


