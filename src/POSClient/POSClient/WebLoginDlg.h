#pragma once


// CWebLoginDlg �Ի���

class CWebLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CWebLoginDlg)

public:
	CWebLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWebLoginDlg();

// �Ի�������
	enum { IDD = IDD_WEBLOGIN };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btDemo;
	BOOL m_bDemo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel2();
};
