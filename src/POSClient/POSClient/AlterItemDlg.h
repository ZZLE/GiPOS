#pragma once


// AlterItemDlg �Ի���

class AlterItemDlg : public CDialog
{
	DECLARE_DYNAMIC(AlterItemDlg)

public:
	AlterItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlterItemDlg();

// �Ի�������
	enum { IDD = IDD_ALTER };

	HBITMAP m_bpBackgrd;
	HWND hParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CreatButton m_btnCtrl;
	
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClicked(UINT uID);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
