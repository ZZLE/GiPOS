#pragma once
#include "afxwin.h"
#include "xhyperlink.h"

// CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutDlg();
	BOOL GetOsInfo(CString& szOsName);

// �Ի�������
	enum { IDD = IDD_ABOUT };
	HBITMAP m_bpBackgrd;
	CEdit m_VersionCtrl;
	CXHyperLink m_url;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButton2 m_btOK;
};
