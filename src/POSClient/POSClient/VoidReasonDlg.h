#pragma once
#include "afxwin.h"


// CVoidReasonDlg �Ի���

class CVoidReasonDlg : public CDialog
{
	DECLARE_DYNAMIC(CVoidReasonDlg)

public:
	CVoidReasonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVoidReasonDlg();

// �Ի�������
	enum { IDD = IDD_VOIDREASON };
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_list;
	CString m_strReason;//�洢�˲�ԭ��
	CRoundButton2 m_btnOK;
	CRoundButton2 m_btCancel;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
