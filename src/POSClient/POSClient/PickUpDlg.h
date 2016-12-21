#pragma once
#include <vector>
using namespace std;

// PickUpDlg �Ի���
class PickUpDlg : public CDialog
{
	DECLARE_DYNAMIC(PickUpDlg)

public:
	PickUpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PickUpDlg();
	void GetOpenChecks(CString strSQL);
	void GetParties(CString strSQL);
	void ShowCurrentPage();
// �Ի�������
	enum { IDD = IDD_PICKUP };
	CStatic m_user;
	CStatic m_time;
	CStatic m_hint;
	vector<CheckItem> m_Items;
	CPButtonList m_itemButtons;
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	int m_x;
	int m_y;
	int m_nCurrentPage;
	int m_nPageCount;
	int m_nIndex;//ѡ���index
	int m_nFilterTable;//���˲���ʾ��table
	int m_nType;//0 ѡ���˵���1 ѡ����᣻2 �鿴�ѽᵥ
	CString m_strSQL;
	CString m_strHint;
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CreatButton m_btnCtrl;
	HBITMAP m_bpBackgrd;
	Gdiplus::Image* m_bpCheckItem[2];
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
