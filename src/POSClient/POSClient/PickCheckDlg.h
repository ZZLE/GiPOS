#pragma once
/*********************************************************************
*Copyright (c) 2013 Coolroid Co.Ltd.
*DESCRIPTION��
*		���ģʽȡ��
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/
#include "afxcmn.h"
#include "afxwin.h"


// CPickCheck �Ի���

class CPickCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CPickCheckDlg)

public:
	CPickCheckDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPickCheckDlg();

// �Ի�������
	enum { IDD = IDD_PICKCHK };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CEdit m_editCtrl;
	CButton mButtonNum;

	long m_nHeadid;
	long m_nFilter;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl mList1;
	CListCtrl mList2;
	void ShowOrderheads(CString strSQL);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonNum();
	afx_msg void OnEnChangeEdit2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
