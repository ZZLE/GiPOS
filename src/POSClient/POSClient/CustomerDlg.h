#pragma once
#include "afxwin.h"


// CCustomerDlg �Ի���

class CCustomerDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCustomerDlg();

// �Ի�������
	enum { IDD = IDD_CUSTOMER };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CStatic mEdit_card;
	CStatic mEdit_name;
	CStatic mEdit_phone;
	CStatic mEdit_amount;
	CStatic mEdit_state;
	CStatic mEdit_level;
	CStatic mEdit_score;
	CEdit mEdit_pay;
	CEdit mEdit_psw;
	CEdit mEdit_point;
	CButton mButtonPrint;
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_dConsume;//���ѽ��
	double toDisc;
	CString m_strCradId;
	CString m_strName;
	CString m_strPhone;
	double m_dBalance;
	double m_dOripay;
	double m_dDiscount;//�ۿ۽��
	double m_dDiscName;
	int m_iScore;
	long m_nConsume_id;
	CString server;
	int port;
	BOOL m_bPrint;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void UpdateMemeberInfo();
	afx_msg void OnPaint();
};
