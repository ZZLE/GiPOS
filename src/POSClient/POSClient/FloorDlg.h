#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION��
*		¥��ҳ�档
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
// FloorDlg �Ի���
class FloorDlg : public CPosPage
{
	DECLARE_DYNAMIC(FloorDlg)

public:
	FloorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FloorDlg();
	void OnSetActive();
	void UpdateTables();
	void EmptyTable();
	static long GetHeadID(long beginId);
	static BOOL ReadDiscountService(OrderDetail* item,int id);
	void AddDefaultItem();
	BOOL BeginTable(int uTableID,int nType,int parent_table=0,int nIsTakeout=TYPE_DINE);
	static int GetOrderDetail(CString strSQL,CTypedPtrList<CPtrList,OrderDetail *> *pOrderList);
	static BOOL GetLock(int table_id);
	static BOOL ReleaseLock(int table_id);
	static BOOL IsFreeLock(int table_id);
	virtual void ShowCurrentPage();
	void UpdateRvc(int rvc_id,BOOL reset);
// �Ի�������
	enum { IDD = IDD_FLOOR };
	CString m_strBackground;
	std::vector<CButton*> m_itemButtons;
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	int m_nPageSize;//ÿҳ�İ�ť������۳���ҳ��ť
	int m_nPageCount;//ҳ��
	static vector<TableItem> m_Tables;//ȫ��������
	vector<TableItem> m_RVCTables;//��ǰRVC��ʾ������
	int m_nCurrentPage;
	int m_nCurrentRvc;
	CString strStatus[4];
	int nStatus[4];
	int TIMER;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	Gdiplus::Image* m_bpStatusNormal[2];
	Gdiplus::Image* m_bpStatusPressed[2];
	HICON m_icTableStatus[4];
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedBeginTable();
	afx_msg void OnBnClickedPickTable();
	afx_msg void OnBnClickedPickCheck();
	afx_msg void OnTableClicked(UINT uID);
	afx_msg void OnBnClickedStatus();
	afx_msg void OnBnClickedEditCheck();
	afx_msg void OnBnClickedTakeOut();
	afx_msg void OnBnClickedEatIn();
	afx_msg void OnBnClickedRefund();
	afx_msg void OnBnClickedFunction();
	afx_msg void OnBnClickedNotifyKitchen();
	afx_msg void OnBnClickedParty();
	afx_msg void OnBnClickedReserve();
	afx_msg void OnMsgIncall();

	CStatic m_logCtrl;
	CRect m_timeRect;
	CStatic m_time;
	int m_nStatus;//1Ϊ�鿴��̬
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadio(UINT uID);
	afx_msg void OnBnClickedCleanTable();
	LRESULT OnMsgUpdate(WPARAM wParam, LPARAM lParam);
	//LRESULT OnMsgIncall(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
