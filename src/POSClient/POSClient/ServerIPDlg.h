#pragma once
#include "afxcmn.h"


// CServerIPDlg �Ի���

class CServerIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerIPDlg)

public:
	CServerIPDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerIPDlg();

// �Ի�������
	enum { IDD = IDD_SERVERIPSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CIPAddressCtrl m_IPCtrl;
};
