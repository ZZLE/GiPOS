#pragma once
#include "listboxex.h"
#include "POSClient.h"

// CCheckDlg �Ի���

class CCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckDlg)

public:
	CCheckDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckDlg();
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
// �Ի�������
	enum { IDD = IDD_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListBoxEx m_ctrlDetailList;
	CListBoxEx m_subTotalList;
	double m_fSubtotal;//С�ƣ��������ۿۺͷ���ѣ�
	double m_fService;//�����
	double m_fDiscount;//�ۿ�
	double m_fTax;//˰��
	double m_fPayed;//�Ѹ����
	double m_fDebt;//ʣ��δ�����
	double m_fMolin;//Ĩ��
	int m_nTotal;//�ܲ�Ʒ��
	int m_nStatus;//0 -open, 1 -close
	int m_nEatType; //��ʳ�������
	BOOL m_bHideDesc;//�Ƿ���ʾ��ע
	BOOL m_bDiscountChange;//�����ۿ۱仯
	OrderDetail* m_pDiscount;//�����ۿ�
	OrderDetail* m_pService;//���������
	int m_iDxDiscount;
	int m_iDxService;
	//BOOL m_bTaxInclude;
	std::map<int,TaxItem*> mTaxGroup;
	static CString TAX_NAME;
	void ResetContent(BOOL bAll=TRUE);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int AddOrderItem(OrderDetail* order,BOOL bUpdate=TRUE,int index=-1);
	int DeleteOrderItem(int index);
	void InsertCondiment(int index,OrderDetail* order,BOOL bUpdate);
	OrderDetail* GetLastItem();
	BOOL UpdateItemString(int nIndex,BOOL bReCompute=TRUE);
	static void FormatString(OrderDetail* pOrder,CString& strLine,BOOL bHideDesc);
	void AddPay(double fPayed);
	void UpdateSubtotal();
	void ComputeSubtotal();
	double GetSubtotalToDiscount();
	//double GetSubtotalToService(int service);
	static double Round(double total,int round_type);
	afx_msg void OnLbnSelchangeList();
	LRESULT EnablePage(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
