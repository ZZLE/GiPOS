#pragma once
#include "afxcmn.h"


// DisplaySettingDlg �Ի���

class DisplaySettingDlg : public CDialog
{
	DECLARE_DYNAMIC(DisplaySettingDlg)

public:
	DisplaySettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DisplaySettingDlg();

// �Ի�������
	enum { IDD = IDD_DISPLAYSET };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CButton mCheck1;
	CButton mCheck2;
	CButton mCheck3;
	CSpinButtonCtrl mSpin1;
	CSpinButtonCtrl mSpin2;
	CSpinButtonCtrl mSpin3;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
public:
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton1();
};
