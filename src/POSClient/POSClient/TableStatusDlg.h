#pragma once
#include "afxwin.h"
#include "roundbutton2.h"


// TableStatusDlg �Ի���

class TableStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(TableStatusDlg)

public:
	TableStatusDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TableStatusDlg();

// �Ի�������
	enum { IDD = IDD_TABLESTATUS };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_infoList;
	int m_nTblID;
	virtual BOOL OnInitDialog();
	CRoundButton2 m_closeButton;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};
