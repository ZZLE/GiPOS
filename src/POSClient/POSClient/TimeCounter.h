#pragma once
#include "afxwin.h"


// TimeCounter �Ի���

class TimeCounter : public CDialog
{
	DECLARE_DYNAMIC(TimeCounter)

public:
	TimeCounter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TimeCounter();

// �Ի�������
	enum { IDD = IDD_TIMECOUNT };
	CRoundButton2 m_btOK;
	CStatic m_hintCtrl;
	CString m_strText;
	CFont m_font;
	int m_nCount;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_ctrlTime;
};
