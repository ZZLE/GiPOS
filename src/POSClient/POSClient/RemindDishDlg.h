#pragma once

#include "OrderDlg.h"
#include "afxwin.h"
// RemindDishDlg �Ի���

class RemindDishDlg : public CDialog
{
	DECLARE_DYNAMIC(RemindDishDlg)

public:
	RemindDishDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RemindDishDlg();

// �Ի�������
	enum { IDD = IDD_REMIND };
	Gdiplus::Image* hbmp;
	Gdiplus::Image* hbmp1;
	CCheckDlg* pCheckDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void GetPrinters(int type);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4();
	CRoundButton2 m_btWaitAll;
	CRoundButton2 m_btMakeAll;
	CRoundButton2 m_btRemindAll;
	CRoundButton2 m_btRemindSelect;
	CRoundButton2 m_btExit;
	afx_msg void OnPaint();
};
