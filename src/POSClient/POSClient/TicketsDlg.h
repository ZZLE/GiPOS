#pragma once
#include "coloredit.h"
#include "afxwin.h"


// TicketsDlg �Ի���
struct TicketItem
{
	int id;
	double amount;
	CString name;
	CString display_name;
};
class TicketsDlg : public CDialog
{
	DECLARE_DYNAMIC(TicketsDlg)

public:
	TicketsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TicketsDlg();

// �Ի�������
	enum { IDD = IDD_DISCOUNT };
	TicketItem selectedItem;
	//int m_nCheckID;//��һ�ŵ�
	double m_fTax;
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void CreatButtons();
	CPButtonList m_itemButtons;
	vector<TicketItem> m_Items;
	Gdiplus::Image* m_bpButtonItem[2];
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnItemBnClicked(UINT uID);
	CColorEdit m_editDiscount;
	CRoundButton2 m_btnPrepage;
	afx_msg void OnBnClickedButtonPre();
};
