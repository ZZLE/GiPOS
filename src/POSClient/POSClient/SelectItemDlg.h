#pragma once
#include "listboxex.h"
#include "afxwin.h"
#include "coloredit.h"


// SelectItemDlg �Ի���

class SelectItemDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectItemDlg)

public:
	SelectItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectItemDlg();
	CreatButton m_btnCtrl;
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
	int m_nCheckID;//��һ�ŵ�
	double percent;//���۵ı���
	//int discount_level;//���ڵ��ۿۼ���
	double amount;//����ѡ��Ĳ�Ʒ��������Ĵ��۽��
	CString m_strHint;
	int m_nType; //0 ����ʱѡ���Ʒ�� 1 ���Ʋ˵�ʱѡ��2 �����ѡ���Ʒ
// �Ի�������
	enum { IDD = IDD_SELECTITEM };
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSetActive();
	CListBoxEx m_list;
	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
	CColorEdit m_hint;
	afx_msg void OnBnClickedSelectAll();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClear();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
