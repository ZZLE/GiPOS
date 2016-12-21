// AlterItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "AlterItemDlg.h"


// AlterItemDlg �Ի���

IMPLEMENT_DYNAMIC(AlterItemDlg, CDialog)

AlterItemDlg::AlterItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AlterItemDlg::IDD, pParent)
{
	m_bpBackgrd=NULL;
}

AlterItemDlg::~AlterItemDlg()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}

void AlterItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AlterItemDlg, CDialog)
	ON_COMMAND_RANGE(IDC_BUTTON0,4000,OnBnClicked)
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATE()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// AlterItemDlg ��Ϣ�������
BOOL AlterItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	static CImage img;
	CString strTmplate=_T("Page\\IDD_ALTERITEM.ini");
	if(img.Load(_T("Picture\\alteritem.png"))==S_OK)
	{
		MoveWindow(100,300,img.GetWidth(),img.GetHeight());
		m_bpBackgrd=img.Detach();
	}
	m_btnCtrl.GenaratePage2(strTmplate,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void  AlterItemDlg::OnBnClicked(UINT uID)
{
	//�ظ�ѡ�У�������
	if(uID!=IDC_BUTTON_REPEAT)
		this->ShowWindow(SW_HIDE);
	//���͸������ڴ���
	::SendMessage(hParent,WM_COMMAND,MAKEWPARAM(uID,BN_CLICKED),0);
}
BOOL AlterItemDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}
void AlterItemDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	if (WA_INACTIVE == nState)   
	{   
		this->ShowWindow(SW_HIDE);
	}   
}

LRESULT AlterItemDlg::OnNcHitTest(CPoint point)
{
	LRESULT   nHitTest   =   CDialog::OnNcHitTest   (point); 
	if   (nHitTest   ==   HTCLIENT)
		nHitTest   =   HTCAPTION; 
	return   nHitTest;
}
