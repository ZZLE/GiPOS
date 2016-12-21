#pragma once
#include "afxwin.h"


// ShiftDlg �Ի���

class ShiftDlg : public CDialog
{
	DECLARE_DYNAMIC(ShiftDlg)

public:
	ShiftDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShiftDlg();

// �Ի�������
	enum { IDD = IDD_SHIFT };

	CString m_strMsg;
	CString str_from;
	CString str_to;
	JSONVALUE payinfo;
	BOOL m_bReadonly;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CEdit m_Edit;

	void ListAllShiftInfo();
	void GetShiftInfoByPos();
	void GetShiftInfoByUser(LPCTSTR strUser);
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
