#pragma once
#include "csdeft.h"
// CEftMsgDlg �Ի���

class CEftMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CEftMsgDlg)

public:
	CEftMsgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEftMsgDlg();

// �Ի�������
	enum { IDD = IDD_EFTMSG };
	CCsdEft m_CsdEft;
	double fPayed;
	afx_msg void OnTransactionEventCsdeft();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
};
