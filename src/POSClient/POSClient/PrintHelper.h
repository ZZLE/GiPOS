#pragma once
#include <vector>
using   namespace   std;
struct PrintItem
{
	int index;//���б��ڵ�����
	int item_id;//��Ʒ��id
	long n_belong_item;//�����ĸ��˵�����;<0 ��ʾ�ײ�
	int n_eattype;//��ʳ�������
	int n_class;  //��Ʒ����
	int n_seat;	  //������λ�� 
	int n_check;  //�ֵ���
	BOOL b_isfree;//�Ƿ����Ͳ�Ʒ
	BOOL b_isvoid;//�Ƿ��˲�
	double quantity;//��Ʒ������������
	double item_price;//����
	double total_price;//�ܼ�=����*����
	CString item_name; //��Ʒ����
	CString item_name2; //����2
	CString unit;
	CString return_reason;
	CString description;//��Ʒ����
	
	PrintItem()
	{
		index=0;
		item_id=0;
		n_belong_item=0;
		n_eattype=0;
		n_class=-1;
		n_seat=0;
		b_isfree=FALSE;
		b_isvoid=FALSE;
		quantity=0;
		item_price=0;
		total_price=0;
	}
};
#define TEMPLATE_SEND		_T("send_order")
#define TEMPLATE_VOID		_T("void_item")
#define TEMPLATE_REMIND		_T("reminder")
#define TEMPLATE_PAY		_T("payment")
#define TEMPLATE_PREPAY		_T("prepayment")
#define TEMPLATE_MESSAGE	_T("message")
#define TEMPLATE_REPORT		_T("report")
#define TEMPLATE_SHIFT		_T("shiftinfo")
#define TEMPLATE_VIP		_T("vip_modify")
#define TEMPLATE_MAKE		_T("make_item")
#define TEMPLATE_CHANGET	_T("change_table")

BOOL InitPrintService();
UINT NotifyThread(LPVOID pParam);
BOOL WritePrintTask(JSONVALUE& root,BOOL bNotify);
void PrintMenu(vector<PrintItem>& menu_list, JSONVALUE& root,int nSort);
void PrintItem2Json(PrintItem* pItem,JSONVALUE& retrunItem);
void GetPrinterInfo(CRecordset& rs,JSONVALUE& printTask);