#pragma once
/*********************************************************************
*Copyright (c) 2013 Coolroid Co.Ltd.
*DESCRIPTION��
*		��˺͸���Ի���ĸ��ࡣ
*AUTHOR ��zhangyi
*HISTORY��
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
#include "CoolTabCtrl.h"
#include "CheckDlg.h"
#include "order_detail.h"

// OrderDlg �Ի���
struct MenuItem
{
	int type;//-1 slu ,0 ��ͨ; 1 ����;2 ʱ�� ;3 �ײ�
	int item_number;
	int condiment;//��Ҫ��������
	int n_discount_level;//�Բ�Ʒ����ʹ�õ��ۿۼ���
	int n_service_level;//�Բ�Ʒ����ʹ�õķ���Ѽ���
	int bargain_stype;//0 ������ 1 �ֶ����� 2 ��������
	int time_accuracy;// >0 ��ʱ��Ʒ�ļ�ʱ���ȣ����ӣ�
	int tax_group;//˰����
	BOOL weight_required;//�Ƿ���Ҫ����
	BOOL modify;//�Ƿ���Ҫѡ����
	BOOL is_time;//
	double price;
	double bargain_num_cur;//��ǰʣ�������
	double default_num;//���ײ�����Ĭ�ϵ�����
	CString item_name1;
	CString item_name2;
	CString icon;
	CString unit;//Ĭ�Ϲ��
};
struct CourseInfo
{
	int id;//���
	int total_select;//���ײ����ܹ��ɵ�Ĵ���
	int can_select;//ʣ��ɵ�ķ���
	int slu_id;
	vector<OrderDetail*> m_orders;//�������ѵ��Ʒ
};
enum ITEM_TYPE{ITEM_CONDIMENT_GROUP=-2,ITEM_SLU=-1,ITEM_ITEM,ITEM_CONDIMENT,ITEM_PRICE,ITEM_SET,ITEM_OPEN,ITEM_TEXT};


class COrderPage :
	public CPosPage
{
public:
	COrderPage(int nId);
	~COrderPage();
	CCoolTabCtrl	m_TabCtrl;//�˵���Ϣ
	CCheckDlg		m_checkDlg[MAX_CHECKS];
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
	static int m_nLastActive;
	int m_nVoidState;//0 �������,1 �˲ˣ� 2 �˲ˣ�������ԭ��3 �ײ����˲�

	CStatic m_ctrlHint;
	CRect mRectHint;

	static CString m_strTAInfo;
	static BOOL bNewTainfo;
	static CString m_strCardID;

	void UpdateHint(LPCTSTR strHint);
	void UpdateCheckData();
	void LoadCheckData();
	void UpdateSencondScreen(int active,OrderDetail* pOder);
	void VoidItem(int active);
	void DeletePay(long order_id);
	virtual void UpdateSoldoutInfo(OrderDetail* item,double diff);
	static void CopyPrintItem(PrintItem& pItem,OrderDetail* from);
	static void readOrderDetail(CRecordset& rs,OrderDetail* order);
	static void SetRsDetail(COrder_Detail& rsDetail,OrderDetail* item);
	static void FormatTableInfo(JSONVALUE& root);
	static int RequeastAuth(CString& authID,CString strPrivilege,int nMiniPermission=1,WCHAR* pAuthUser=NULL);
};
