#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION��
*		��ҳ��ĸ��ࡣ
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/

// CPosPage

class CPosPage : public CDialog
{
	DECLARE_DYNAMIC(CPosPage)

public:
	int m_nID;
	int m_nPrePage;//ǰҳҪ��ת��ҳ
	CString m_strTmplate;
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CPosPage(int nId);
	virtual ~CPosPage();
	virtual void OnSetActive();
	virtual BOOL LockScreen();
protected:
	CreatButton m_btnCtrl;//��ť�б�
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNextPage(UINT uID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void InitDialog(CString strImgPath);
};


