#pragma once


// ChangePswDlg �Ի���

class ChangePswDlg : public CDialog
{
	DECLARE_DYNAMIC(ChangePswDlg)

public:
	ChangePswDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangePswDlg();

// �Ի�������
	enum { IDD = IDD_CHANGEPSW };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_softButton;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonSoftkey();
	afx_msg void OnPaint();
};
