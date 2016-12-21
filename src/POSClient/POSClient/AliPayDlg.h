#pragma once
#include "afxwin.h"


// CAliPayDlgDlg �Ի���

typedef map<string, string> StringMap;

class CAliPayDlg : public CDialog
{
	DECLARE_DYNAMIC(CAliPayDlg)

public:
	CAliPayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAliPayDlg();

	BOOL doPayQueryLoop(int loopCount);
	BOOL doOnePayQuery();
	
// �Ի�������
	enum { IDD = IDD_ALIPAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	LRESULT OnThreadOK(WPARAM wParam, LPARAM lParam);
	string base64Encode(const unsigned char *bytes, int len);
	void rsaSign(const char* content,string& sign);
	string buildContent(const StringMap &contentPairs,bool bEncode);
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	CStatic m_hint;
	CRect mRectHint;
	CString m_strRandom;
	CString m_strTradeNO;
	CString m_wxTransactionID;
	double total_amount;
	CEdit m_edit;
	BOOL m_bProcessing;
	BOOL m_bDialogClosed;
};
