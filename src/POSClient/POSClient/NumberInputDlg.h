#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION��
*		��������Ի���
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"


// NumberInputDlg �Ի���

class NumberInputDlg : public CDialog
{
	DECLARE_DYNAMIC(NumberInputDlg)

public:
	NumberInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NumberInputDlg();

// �Ի�������
	enum { IDD = IDD_NUMINPUT };

	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CreatButton m_btnCtrl;
	CStatic m_hint;
	CString m_strHint;
	CString m_strNum;
	BOOL m_bPassword;
	BOOL m_bSwipe;//�жϼ��������ˢ��
//	CString m_strTmplate;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	void UpdateHintData();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton100();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
