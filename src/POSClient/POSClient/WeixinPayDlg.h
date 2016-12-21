#pragma once
#include "afxwin.h"


// CWeixinPayDlg �Ի���
void getSign(CString& sign,CStringArray& clist);
UINT doReverseLoop(LPVOID pParam);
UINT doReverseLoop1(LPVOID pParam);

class CWeixinPayDlg : public CDialog
{
	DECLARE_DYNAMIC(CWeixinPayDlg)

public:
	CWeixinPayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWeixinPayDlg();

	BOOL doPayQueryLoop(int loopCount);
	BOOL doOnePayQuery();
	static void getSign(CString& sign,CStringArray& clist);
// �Ի�������
	enum { IDD = IDD_WEIXINPAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CStatic m_hint;
	CString m_strRandom;
	CString m_strTradeNO;
	CString m_wxTransactionID;
	int total_fee;
	CEdit m_edit;
};
