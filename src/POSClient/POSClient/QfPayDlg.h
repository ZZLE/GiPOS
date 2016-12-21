#pragma once
/*********************************************************************
*Copyright (c) 2016 Coolroid Co.Ltd.
*DESCRIPTION��
*		Ǯ��֧��
*AUTHOR ��zhangyi
*********************************************************************/
#include "afxwin.h"

// CAliPayDlgDlg �Ի���


class CQfPayDlg : public CDialog
{
	DECLARE_DYNAMIC(CQfPayDlg)

public:
	CQfPayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQfPayDlg();

	BOOL doPayQueryLoop(int loopCount);
	int doOnePayQuery();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	static void getSign(CString& sign,CStringArray& clist);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
// �Ի�������
	enum { IDD = IDD_WEIXINPAY };
	HBITMAP m_bpBackgrd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

	CEdit m_edit;
	CBitmap bitmap;
	BOOL m_bProcessing;
	BOOL m_bDialogClosed;
	CStatic m_hint;
	CRect mRectHint;
public:
	
	CString m_strTradeNO;
	CString m_wxTransactionID;
	int total_fee;
	int m_nType;//0 -΢�� 1-֧����
};
