#pragma once
#include "afxwin.h"


// TipsAddDlg �Ի���

class TipsAddDlg : public CDialog
{
	DECLARE_DYNAMIC(TipsAddDlg)

public:
	TipsAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TipsAddDlg();

// �Ի�������
	enum { IDD = IDD_TIPSADD };
	HWND   hOld;
	double m_fTotal;
	double m_fPayed;
	double m_fTips;
	double m_fChange;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonDel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic mCtrlTotal;
	CStatic mCtrlChange;
	CEdit mCtrlPayed;
	afx_msg void OnEnChangeEdit1();
	CEdit mCtrlTips;
	CString decPlace;
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
};
