// information_screens.h : Cinformation_screens ���ʵ��



// Cinformation_screens ʵ��

// ���������� 2011��4��22��, 16:21

#include "stdafx.h"
#include "information_screens.h"
IMPLEMENT_DYNAMIC(Cinformation_screens, CRecordset)

Cinformation_screens::Cinformation_screens(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_info_id = 0;
	m_info_number = 0;
	m_info_name = "";
	m_line1 = "";
	m_line2 = "";
	m_line3 = "";
	m_line4 = "";
	m_line5 = "";
	m_line6 = "";
	m_line7 = "";
	m_line8 = "";
	m_line9 = "";
	m_line10 = "";
	m_nFields = 13;
	m_nDefaultType = snapshot;
}
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString Cinformation_screens::GetDefaultConnect()
{
	return _T("DATABASE=coolroid;DSN=agile_pos;");
}

CString Cinformation_screens::GetDefaultSQL()
{
	return _T("[information_screens]");
}

void Cinformation_screens::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[info_id]"), m_info_id);
	RFX_Long(pFX, _T("[info_number]"), m_info_number);
	RFX_Text(pFX, _T("[info_name]"), m_info_name);
	RFX_Text(pFX, _T("[line1]"), m_line1);
	RFX_Text(pFX, _T("[line2]"), m_line2);
	RFX_Text(pFX, _T("[line3]"), m_line3);
	RFX_Text(pFX, _T("[line4]"), m_line4);
	RFX_Text(pFX, _T("[line5]"), m_line5);
	RFX_Text(pFX, _T("[line6]"), m_line6);
	RFX_Text(pFX, _T("[line7]"), m_line7);
	RFX_Text(pFX, _T("[line8]"), m_line8);
	RFX_Text(pFX, _T("[line9]"), m_line9);
	RFX_Text(pFX, _T("[line10]"), m_line10);

}
/////////////////////////////////////////////////////////////////////////////
// Cinformation_screens ���

#ifdef _DEBUG
void Cinformation_screens::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cinformation_screens::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


