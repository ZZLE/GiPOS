#pragma once
#include "coloredit.h"
#include "afxwin.h"


// DiscountDlg �Ի���
struct DiscountItem
{
	int id;
	double percent;
	int privilege;//Ȩ��
	//int discount_level;//�ۿۼ���
	int round_type;//Ĩ������
	BOOL isOpenItem;//�Ƿ�Ϊ�Զ����ۿ�
	BOOL select;//ѡ����۷�Χ
	BOOL noDiscount;//������Ƿ񲻴���
	double amount;
	CString name;
	CString display_name;
};
class DiscountDlg : public CDialog
{
	DECLARE_DYNAMIC(DiscountDlg)

public:
	DiscountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DiscountDlg();

// �Ի�������
	enum { IDD = IDD_DISCOUNT };
	DiscountItem selectedItem;
	int m_nCheckID;//��һ�ŵ�
	int m_nIsService; //0 -�ۿۣ�1 �����
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void CreatButtons();
	CPButtonList m_itemButtons;
	vector<DiscountItem> m_Items;
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
