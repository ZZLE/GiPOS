// information_screens.h : Cinformation_screens ������

#pragma once

// ���������� 2011��4��22��, 16:21

class Cinformation_screens : public CRecordset
{
public:
	Cinformation_screens(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cinformation_screens)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_info_id;
	long	m_info_number;
	CString	m_info_name;
	CString	m_line1;
	CString	m_line2;
	CString	m_line3;
	CString	m_line4;
	CString	m_line5;
	CString	m_line6;
	CString	m_line7;
	CString	m_line8;
	CString	m_line9;
	CString	m_line10;

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


