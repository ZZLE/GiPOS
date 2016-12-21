#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION��
*		�������Ի���
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/
// CMainSheet �Ի���
#include "SplashWnd.h"

class CMainSheet : public CDialog
{
	DECLARE_DYNAMIC(CMainSheet)
public:
	CMainSheet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainSheet();
	// �Ի�������
	enum { IDD = IDD_MAINSHEET };

	CSplashWnd* pSplash;
	NOTIFYICONDATA m_tnd;
	static int m_iFullScreen;
	static int m_iStaticsInfo;
	//int GetPageCount() const;
	CPosPage* GetActivePage() const;
	int GetActiveIndex() const;
	CPosPage* GetPage(int nPage) const;
	//int GetPageIndex(CPosPage* pPage);
	void AddPage(CPosPage* pPage);
	BOOL SetActivePage(int nPage,BOOL bPre=FALSE);
	//BOOL SetActivePage(CPosPage* pPage);
	void ShowCurrentPage(int nCmd);


protected:
	int m_nCurrentPage;

	CPtrArray m_pages;
	friend class CPosPage;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	void CreateAllPages();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnPrintListFull(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSearch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgShowNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnVipCall(WPARAM wParam, LPARAM lParam);
};
