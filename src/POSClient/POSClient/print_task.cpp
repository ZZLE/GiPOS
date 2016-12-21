// print_task.h : Cprint_task ���ʵ��



// Cprint_task ʵ��

// ���������� 2015��11��11��, 16:22

#include "stdafx.h"
#include "print_task.h"
IMPLEMENT_DYNAMIC(CPrint_Task, CRecordset)

CPrint_Task::CPrint_Task(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_data = L"";
	m_time;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CPrint_Task::GetDefaultConnect()
{
	return _T("DSN=agile_pos");
}

CString CPrint_Task::GetDefaultSQL()
{
	return _T("[print_task]");
}

void CPrint_Task::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[data]"), m_data,21840);
	RFX_Date(pFX, _T("[time]"), m_time);

}
/////////////////////////////////////////////////////////////////////////////
// Cprint_task ���

#ifdef _DEBUG
void CPrint_Task::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPrint_Task::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


