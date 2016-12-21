#pragma once
#include "listboxex.h"
#include "CheckDlg.h"
#include "coloredit.h"

// SplitCheckDlg �Ի���

class SplitCheckDlg : public CPosPage
{
	DECLARE_DYNAMIC(SplitCheckDlg)

public:
	SplitCheckDlg();   // ��׼���캯��
	virtual ~SplitCheckDlg();
	void OnSetActive();
	BOOL LockScreen();
// �Ի�������
	enum { IDD = IDD_SPLIT };
	HBITMAP bpStatic;
	
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
	CTypedPtrList<CPtrList,OrderDetail *> m_splitedList;//�Ѳ�ֵĲ�Ʒ����Ҫ�����ݿ���ɾ��
	CTypedPtrList<CPtrList,OrderDetail *> m_newList;
	int m_nActive;//��ǰ����ĵ�
	int m_nCheckCount;//��������
	int m_nCurrentPage;//���ڷ�ҳ��ʾ����ǰ��ʾ�����
	int m_nWidth;
	int m_nHeight,m_nHeight1;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void ShowWindow(int i,int nCmd);
	void ShowCurrentPage();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedAddCheck();
	afx_msg void OnBnClickedDone();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedShare();
	afx_msg void OnBnClickedSplit();
	afx_msg void OnBnClickedCommbine();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	CStatic m_static[MAX_CHECKS];
	CListBoxEx m_list[MAX_CHECKS];
	CColorEdit m_edit[MAX_CHECKS];
	CColorEdit m_table[MAX_CHECKS];
	void MoveSelected(int from,int to);
	afx_msg void OnLbnSetfocusList1();
	afx_msg void OnLbnSetfocusList2();
	afx_msg void OnLbnSetfocusList3();
	afx_msg void OnLbnSetfocusList4();
	afx_msg void OnLbnSetfocusList5();
	afx_msg void OnLbnSetfocusList6();
	afx_msg void OnLbnSetfocusList7();
	afx_msg void OnLbnSetfocusList8();
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
};
