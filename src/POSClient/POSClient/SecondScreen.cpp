// SecondScreen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "SecondScreen.h"
#include "CheckDlg.h"


// SecondScreen �Ի���

IMPLEMENT_DYNAMIC(SecondScreenDlg, CDialog)

SecondScreenDlg::SecondScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SecondScreenDlg::IDD, pParent)
{
	m_picIndex = 0;
}

SecondScreenDlg::~SecondScreenDlg()
{
}

void SecondScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SecondScreenDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// SecondScreen ��Ϣ�������

BOOL SecondScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//�������ڴ�С
	m_total_width =GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("TOTAL_WIDTH"), 0,_T(".\\config.ini"));
	m_total_height=GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("TOTAL_HEIGHT"), 0,_T(".\\config.ini"));
	m_bHideDetail =GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("HIDE_DETAIL"), 0,_T(".\\config.ini"));
	int m_timeer = GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("PIC_TIMER"), 0,_T(".\\config.ini"));
	//�ƶ����ڵ��ڶ���Ļ
	MoveWindow2(m_hWnd,m_total_width,m_total_height);
	m_checkDlg.Create(IDD_CHECK,this);
	m_checkDlg.ShowWindow(SW_HIDE);
	m_checkDlg.EnableWindow(FALSE);
	m_checkDlg.MoveWindow(10,10,ScaleX(330),m_total_height-20);
	//����ͼƬ
	ScanDiskFile(m_scan_file);
	//����ͼƬ������ʱ��
	if (m_vStrAllFiles.size() > 0)
	{
		ShowPicture(m_vStrAllFiles[m_picIndex]);
		m_picIndex = (m_picIndex+1)%m_vStrAllFiles.size();
	}
	SetTimer(1001,m_timeer*1000,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//���¼�����ʾ���в�Ʒ�б�
BOOL SecondScreenDlg::ReshowAll(CCheckDlg& from)
{
	if(m_bHideDetail)
		return FALSE;
	m_checkDlg.ResetContent(FALSE);
	m_checkDlg.LockWindowUpdate();
	int size=from.m_ctrlDetailList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_ctrlDetailList.GetText(i,text);
		m_checkDlg.m_ctrlDetailList.AddString(text);
	}
	m_checkDlg.m_subTotalList.ResetContent();
	size=from.m_subTotalList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_subTotalList.GetText(i,text);
		m_checkDlg.m_subTotalList.AddString(text);
	}
	m_checkDlg.UnlockWindowUpdate();
	m_checkDlg.ShowWindow(SW_SHOW);
	return TRUE;
}
void SecondScreenDlg::HideDetail()
{
	m_checkDlg.ShowWindow(SW_HIDE);
}
//����һ�У�һ����Ʒ���������
VOID SecondScreenDlg::AddItem(CCheckDlg& from,LPCTSTR item)
{
	m_checkDlg.m_ctrlDetailList.AddString(item);
	m_checkDlg.m_subTotalList.ResetContent();
	int size=from.m_subTotalList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_subTotalList.GetText(i,text);
		m_checkDlg.m_subTotalList.AddString(text);
	}
}
//��ʾ�ܼ�
VOID SecondScreenDlg::ShowAmount(double m_fDue,double m_fDebt)
{
	if(m_bHideDetail)
		return;

}
void SecondScreenDlg::OnPaint()
{
	CPaintDC dc(this); 
	CDC MemDc;
	MemDc.CreateCompatibleDC(&dc);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	dc.SetStretchBltMode(HALFTONE);
	dc.StretchBlt(0,0,m_total_width,m_total_height,&MemDc,0,0,i_image_width,i_image_height,SRCCOPY);
}
//��ʾͼƬ����
void SecondScreenDlg::ShowPicture(CString path)
{
	CImage image;       //ʹ��ͼƬ��
	image.Load(path);   //װ��·����ͼƬ��Ϣ��ͼƬ��
	if(image.IsNull())                
		return;
	i_image_width=image.GetWidth();
	i_image_height=image.GetHeight();

	DeleteObject(m_bpBackgrd);
	m_bpBackgrd=image.Detach();
	
	Invalidate();
}
//��ʱ��
void SecondScreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1001)
	{
		if (m_vStrAllFiles.size() > 0)
		{
			ShowPicture(m_vStrAllFiles[m_picIndex]);
			m_picIndex = (m_picIndex+1)%m_vStrAllFiles.size();
		}
	}
	CDialog::OnTimer(nIDEvent);
}
//
void SecondScreenDlg::ScanDiskFile(const CString& strPath)
{
	m_vStrAllFiles.clear();
	CFileFind find;
	CString Path = strPath;
	CString lpsz =  Path +L"\\";
	Path = Path +L"\\*.*";
	BOOL IsFind = find.FindFile(Path);
	while(IsFind )
	{
		IsFind=find.FindNextFile();
		//�����"."��ɨ��
		if(find.IsDots())
			continue;
		//��Ŀ¼,����ɨ���Ŀ¼
		else if(find.IsDirectory())
		{
			continue;
		}
		//�ļ�
		else
		{
			//����ļ���·��
			CString  strFile= find.GetFileName();
			CString extend = strFile.Right(strFile.GetLength() - strFile.ReverseFind('.') - 1);//ȡ����չ��
			if (extend == _T("jpg") | extend == _T("png"))
			{
				m_vStrAllFiles.push_back(lpsz + strFile); 
			}
		}
	}
	find.Close();
}

BOOL SecondScreenDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; // CDialog::OnEraseBkgnd(pDC);
}

void SecondScreenDlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(1001);
	delete this;
}
// �����ʾ�����
short GetScreenWidth(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return 0;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return 0;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return 0;
	return (short) dm.dmPelsWidth;
}

// �����ʾ�����
short GetScreenHeight(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return 0;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return 0;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return 0;
	return (short) dm.dmPelsHeight;
}

// �@���@ʾ�^Y����
short GetScreenTop(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return -1;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return -1;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return -1;
	return (short) dm.dmPosition.y ;
}

// �@���@ʾ�^X����
short GetScreenLeft(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return -1;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return -1;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return -1;
	return (short) dm.dmPosition.x ;
}
// �@�����@ʾ�^
short GetPrimaryScreen(const int m_monitorNum)
{
	// TODO: Add your property handler here
	if (m_monitorNum <= 1) return 0;
	// if the Screen Top = 0 and Left = 0, then, it's the Primary Screen
	short i;
	for (i=0; i< m_monitorNum; i++)
	{
		if (GetScreenTop(i, m_monitorNum)==0 && GetScreenLeft(i, m_monitorNum)==0) return i;
	}
	return 0;
}
//�ƶ����ڵ��ڶ���ʾ��
//m_hWnd���ھ�� width:���ڴ�С height�����ڸ� ����һ��Ϊ0��ȫ����ʾ
void SecondScreenDlg::MoveWindow2(HWND m_hWnd,int width,int height)
{
	int cx, cy;
	RECT hMWork; 
	// �´���ԭ��λ��,��õ��Ƕ�������������˵��λ��
	::GetWindowRect(m_hWnd,&hMWork);
	int m_monitorNum = GetSystemMetrics(SM_CMONITORS); // ��Ļ��Ŀ

	vector<int> heights;
	vector<int> widths;
	int primNum = GetPrimaryScreen(m_monitorNum); //����Ļ���
	int secondNum = 0;
	for (int i = 0; i < m_monitorNum; ++i)
	{
		if (i != primNum)
		{
			secondNum = i;
		}
		widths.push_back(GetScreenWidth(i, m_monitorNum));
		heights.push_back(GetScreenHeight(i, m_monitorNum));
	}

	CString strMsg;
	HDC dc = ::GetDC(NULL);
	// ��������ĳ���
	cx = GetDeviceCaps(dc, HORZRES) + GetSystemMetrics(SM_CXBORDER);
	cy = GetDeviceCaps(dc, VERTRES) + GetSystemMetrics(SM_CYBORDER);

	// ���������Ļ�ĳ���
	int allX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int allY = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//���ڴ�С
	if (width ==0 ||height==0)
	{
		width = widths.at(secondNum);
		height = heights.at(secondNum);
		m_total_width = width;
		m_total_height = height;
	}

	// ���ֻ��һ������Ļ
	if (m_monitorNum == 1)
	{
		::MoveWindow(m_hWnd, 0, 0, width, height, 1);
	}
	else
	{
		::MoveWindow(m_hWnd, cx, 0, width, height, 1);
	}
	::ReleaseDC(0,dc);
}

HBRUSH SecondScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctlId=pWnd->GetDlgCtrlID();
	if ( ctlId== IDC_STATIC_AMOUNT)
	{
		pDC->SetTextColor(RGB(250,0,0));
		//pDC->SetBkMode(TRANSPARENT);
		//return (HBRUSH)::GetStockObject(NULL_BRUSH); //���ش˻�ˢ����ʹ��̬�ı�͸��
	}
	return hbr;
}
