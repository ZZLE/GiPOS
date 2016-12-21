#pragma once
#include "afxwin.h"


// MSGBoxDlg �Ի���

class MSGBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(MSGBoxDlg)

public:
	MSGBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MSGBoxDlg();

// �Ի�������
	enum { IDD = IDD_MSGBOX };
	CString m_strText;
	CString m_strYes;
	CString m_strNo;
	int m_nType;
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CStatic m_hintCtrl;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
