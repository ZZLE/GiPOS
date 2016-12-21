// order_detail.h : COrder_Detail ������

#pragma once

// ���������� 2012-05-23 , 16:51

class COrder_Detail : public CRecordset
{
public:
	COrder_Detail(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COrder_Detail)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_order_detail_id;
	long	m_order_head_id;
	long	m_check_id;
	long	m_menu_item_id;
	CString	m_menu_item_name;
	float	m_product_price;
	BOOL	m_is_discount;
	float	m_original_price;
	long	m_discount_id;
	float	m_actual_price;
	BOOL	m_is_return_item;
	long	m_order_employee_id;
	CString	m_order_employee_name;
	long	m_pos_device_id;
	CString	m_pos_name;
	CTime	m_order_time;
	CTime	m_return_time;
	CString	m_return_reason;
	CString	m_unit;
	BOOL	m_is_send;
	long	m_condiment_belong_item;
	float	m_quantity;
	long	m_eat_type;
	long	m_auth_id;
	CString	m_auth_name;
	BOOL	m_weight_entry_required;
	CString	m_description;
	long	m_n_service_type;
	long    m_notprint;
	long	m_n_seat_num;
	float   m_discount_price;
	float	m_sales_amount;
	long	m_print_class;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


