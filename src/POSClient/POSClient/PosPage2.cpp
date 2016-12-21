// PosPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "PosPage2.h"


// CPosPage

IMPLEMENT_DYNAMIC(CPosPage2, CDialog)

CPosPage2::CPosPage2(int nId)
: CDialog(nId)
{
	m_nID=nId;
	m_x=1024;
	m_y=768;
	m_textColor=RGB(255,255,255);
	m_hParent=NULL;
}

CPosPage2::~CPosPage2()
{
	::DeleteObject(m_bpBackgrd);
}

BEGIN_MESSAGE_MAP(CPosPage2, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CPosPage ��Ϣ�������


/************************************************************************
* �������ܣ����ε��س�����esc��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL CPosPage2::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_SPACE:
			{
			TCHAR szClassName[32];
			GetClassName(GetFocus()->GetSafeHwnd(), szClassName, sizeof(szClassName));
			if (!lstrcmpi(szClassName, _T("Edit")))
				return CDialog::PreTranslateMessage(pMsg);
			else
				return TRUE;
			}
		case VK_ESCAPE:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_PRE);
			return TRUE;
		case VK_BACK:
			{//����������򲻽ػ�ɾ����
				TCHAR szClassName[32];
				GetClassName(GetFocus()->GetSafeHwnd(), szClassName, sizeof(szClassName));
				if (!lstrcmpi(szClassName, _T("Edit")))
				{
					return CDialog::PreTranslateMessage(pMsg);
				}
				else
				{
					this->SendMessage(WM_COMMAND,IDC_BUTTON_PRE);
					return TRUE;
				}	
			}
		case VK_INSERT:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_CHKNAME);
			return TRUE;
		case VK_HOME:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_FUNCTION);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg); 
}
void CPosPage2::InitDialog(CString strImgPath)
{
	CDialog::OnInitDialog();
	MoveWindow(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight);
	CenterWindow();
	if(m_hParent)
		m_hParent->ShowWindow(SW_HIDE);
	CImage img;
	if(img.Load(strImgPath)==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
}
BOOL CPosPage2::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight,&MemDc,0,0,m_x,m_y,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}
HBRUSH CPosPage2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_textColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //���ش˻�ˢ����ʹ��̬�ı�͸��
	}
	return   hbr; 
}
/************************************************************************
* �������ܣ��Զ������Ի���
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CPosPage2::OnCancel()
{
	if(m_hParent)
		m_hParent->ShowWindow(SW_SHOW);
	DestroyWindow();
}

void CPosPage2::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}