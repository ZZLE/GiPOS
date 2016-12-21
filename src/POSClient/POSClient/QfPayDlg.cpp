/*********************************************************************
*Copyright (c) 2016 Coolroid Co.Ltd.
*DESCRIPTION��
*		Ǯ��֧��
*AUTHOR ��zhangyi
*********************************************************************/
// CQfPayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "QfPayDlg.h"
#include "SSLCon.h"
#include <openssl/md5.h>
// CAliPayDlg �Ի���

IMPLEMENT_DYNAMIC(CQfPayDlg, CDialog)

CQfPayDlg::CQfPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQfPayDlg::IDD, pParent)
{
	m_bProcessing=FALSE;
	m_bDialogClosed=FALSE;
	m_nType=0;
}

CQfPayDlg::~CQfPayDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void CQfPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hint);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CQfPayDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CQfPayDlg ��Ϣ�������
BOOL CQfPayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(m_nType==1)
	{//֧����
		CStatic *pStatic=(CStatic *)GetDlgItem(IDC_STATIC_LOGO);
		bitmap.LoadBitmap(IDB_BITMAP_ALIPAY);
		pStatic->SetBitmap(bitmap);
		GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(_T("ɨ��֧����������"));
	}

	m_bpBackgrd=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_WEXIN_HINT), IMAGE_BITMAP, 0, 0, 0);
	m_hint.ModifyStyle(0,SS_CENTER);
	m_hint.GetWindowRect(&mRectHint);    
	ScreenToClient(&mRectHint);
	m_strTradeNO.Format(_T("%s_%09d_%d"),theApp.m_strResId.Mid(1,16),theApp.m_nOrderHeadid,time(NULL));
	m_edit.SetFocus();
	return FALSE;
}
static int  SortDescendingString(const void* left, const void* right)
{
	return ((CString*)left)->Compare(*((CString*)right));
}
UINT doPayQueryThreadQf(LPVOID pParam)
{
	CQfPayDlg *pDlg = (CQfPayDlg*)pParam;
	pDlg->doPayQueryLoop(6);
	return 0;
}
void CQfPayDlg::getSign(CString& sign,CStringArray& clist)
{
	qsort(clist.GetData(), clist.GetSize(), sizeof(CString*), SortDescendingString);
	CString str;
	for (int n = 0; n < clist.GetCount(); n++)
	{
		str.AppendFormat(_T("%s"),clist.GetAt(n));
		if(n!=clist.GetCount()-1)
			str.Append(_T("&"));
	}
	str.AppendFormat(_T("88AD0A27155B45F3B72D6C4F39A3F7FE"));
	//תΪUTF-8
	int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str, str.GetLength(), NULL, 0, NULL, NULL);
	char* sz0 = new char[wcsLen0 + 1];
	memset(sz0,0,wcsLen0+1);
	::WideCharToMultiByte(CP_UTF8, NULL, str, -1, sz0, wcsLen0,  NULL, NULL);
	sz0 [wcsLen0] = '\0';
	//����MD5
	MD5_CTX hash_ctx;
	unsigned char hash_ret[16];
	MD5_Init(&hash_ctx);
	MD5_Update(&hash_ctx, sz0, wcsLen0);
	MD5_Final(hash_ret, &hash_ctx);
	for( int i=0; i<16; i++ ){
		sign.AppendFormat(_T("%02X"),hash_ret[i]);
	}
	delete sz0;
}
void CQfPayDlg::OnCancel()
{
	m_bDialogClosed=TRUE;
	CDialog::OnCancel();
}
void CQfPayDlg::OnOK()
{
	try{
		if(m_bProcessing)
			return;//�������߳����ڴ���
		CSslConnection inetSec;
		inetSec.SetServerName(theApp.m_strQfServerURL);
		inetSec.SetObjectName(_T("/trade/v1/payment"));
		inetSec.m_bUseWechatCert=FALSE;
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			LOG4CPLUS_ERROR(log_pos,(LPCTSTR)inetSec.GetLastErrorString());
			CString hint;
			hint.Format(_T("Connect error %d"),inetSec.GetLastErrorCode());
			m_hint.SetWindowText(hint);
			return;
		}
		CStringArray clist;
		CString item;
		item.Format(_T("%s=%d"),_T("txamt"),total_fee);
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("txcurrcd"),_T("CNY"));
		clist.Add(item);
		if(m_nType==1)
			item.Format(_T("%s=%d"),_T("pay_type"),800108);//֧����ˢ��
		else
			item.Format(_T("%s=%d"),_T("pay_type"),800208);//΢��ˢ��
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("out_trade_no"),m_strTradeNO);
		clist.Add(item);
		CTime c_time=CTime::GetCurrentTime();
		item.Format(_T("%s=%s"),_T("txdtm"),c_time.Format(_T("%Y-%m-%d %H:%M:%S")));
		clist.Add(item);
		CString input;
		m_edit.GetWindowText(input);
		item.Format(_T("%s=%s"),_T("auth_code"),input);
		clist.Add(item);
		CString gName=theApp.m_strResName;
		gName.Replace('&',' ');
		item.Format(_T("%s=%s"),_T("goods_name"),gName);
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("mchid"),theApp.m_wxSubMchid);
		clist.Add(item);
		CString sign;
		getSign(sign,clist);
		CString strHeader;
		strHeader.Format(_T("X-QF-APPCODE:%s\r\n"),theApp.m_strQfAppcode);
		strHeader.AppendFormat(_T("X-QF-SIGN:%s"),sign);
		inetSec.SetHeader(strHeader);
		CString sendStr;
		for (int n = 0; n < clist.GetCount(); n++)
		{
			sendStr.AppendFormat(_T("%s"),clist.GetAt(n));
			if(n!=clist.GetCount()-1)
				sendStr.Append(_T("&"));
		}
		//תΪUTF-8
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, sendStr, sendStr.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, sendStr, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		if (!inetSec.SendHttpsRequest(sz0)) {
			LOG4CPLUS_ERROR(log_pos,(LPCTSTR)inetSec.GetLastErrorString());
			CString hint;
			hint.Format(_T("Connect error %d"),inetSec.GetLastErrorCode());
			m_hint.SetWindowText(hint);
			InvalidateRect(mRectHint);
			return;
		}
		CString line;
		inetSec.GetRequestResult(line);
		inetSec.ClearHandles();
		CString message;
		JSONVALUE::Unescape((LPCTSTR)line,message);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)message);
		JSONVALUE root;
		if(root.Parse((LPCTSTR)message,JSON_FLAG_LOOSE))
		{
			CString ret=root[_T("respcd")].asCString();
			if(ret==_T("0000"))
			{//ֱ�ӿۿ�ɹ�
				m_wxTransactionID.Format(_T("%s"),root[_T("syssn")].asCString());
				m_bDialogClosed=TRUE;
				CDialog::OnOK();
				return;
			}
			else if(ret==_T("1143")||ret==_T("1145"))
			{//�����У���Ҫ������ѯ���׽��
				CString hint=root[_T("resperr")].asCString();
				m_hint.SetWindowText(hint);
				InvalidateRect(mRectHint);
				//��ѯ�����н�ֹ�ظ�����
				m_wxTransactionID.Format(_T("%s"),root[_T("syssn")].asCString());
				AfxBeginThread(doPayQueryThreadQf,this);
				return;
			}
			else
			{
				CString hint=root[_T("respmsg")].asCString();
				if(hint.IsEmpty())
					hint=root[_T("resperr")].asCString();
				m_hint.SetWindowText(hint);
				InvalidateRect(mRectHint);
			}
		}
	}
	catch(...){
	}
}

BOOL CQfPayDlg::doPayQueryLoop(int loopCount)
{
	//����ѭ����ѯ
	m_bProcessing=TRUE;
	for (int i = 0; i < loopCount; i++){
		if(m_bDialogClosed)
			return FALSE;
		int ret=doOnePayQuery();
		if (ret==0) {//�ɹ�
			EndDialog(IDOK);
			return TRUE;
		}
		if(ret<0)
		{
			m_bProcessing=FALSE;
			return FALSE;
		}
	}
	m_bProcessing=FALSE;
	return FALSE;
}
/************************************************************************/
/* ����һ��֧��������ѯ����
/* ����ֵ 0 -���׳ɹ� ����-������ȷʧ�ܣ����ü�����ѯ ����-δ֪��������ѯ
/************************************************************************/
int CQfPayDlg::doOnePayQuery()
{
	Sleep(5000);
	LOG4CPLUS_DEBUG(log_pos,"CQfPayDlg::doOnePayQuery");
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(theApp.m_strQfServerURL);	
		CStringArray clist;
		CString item;
		item.Format(_T("%s=%s"),_T("syssn"),m_wxTransactionID);
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("mchid"),theApp.m_wxSubMchid);
		clist.Add(item);
		CString sign;
		getSign(sign,clist);
		CString strHeader;
		strHeader.Format(_T("X-QF-APPCODE:%s\r\n"),theApp.m_strQfAppcode);
		strHeader.AppendFormat(_T("X-QF-SIGN:%s"),sign);
		inetSec.SetHeader(strHeader);
		CString sendStr;
		for (int n = 0; n < clist.GetCount(); n++)
		{
			sendStr.AppendFormat(_T("%s"),clist.GetAt(n));
			sendStr.Append(_T("&"));
		}
		CString query;
		query.Format(_T("/trade/v1/query?%s"),sendStr);
		inetSec.SetObjectName(query);
		if (!inetSec.ConnectToHttpsServer(_T("GET"))) {
			return 1;
		}
		if (!inetSec.SendHttpsRequest(NULL)) {
			return 2;
		}
		CString line;
		inetSec.GetRequestResult(line);
		CString message;
		JSONVALUE::Unescape((LPCTSTR)line,message);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)message);
		JSONVALUE root;
		if(root.Parse((LPCTSTR)message,JSON_FLAG_LOOSE))
		{
			CString ret=root[_T("respcd")].asCString();
			if(ret==_T("0000"))
			{
				JSONVALUE order;
				root[_T("data")].At((size_t)0,order);
				CString status=order[_T("respcd")].asCString();
				if(status==_T("0000"))
					return 0;
				if(status==_T("1143")||status==_T("1145"))
				{//�����У���Ҫ������ѯ
					return 1145;
				}
				else
				{//����ʧ��
					return -1;
				}
			}
		}
	}catch(...){
	}
	return 3;
}

BOOL CQfPayDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		CDialog::OnEraseBkgnd(pDC);
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,SRCCOPY);
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	//MemDc.SelectObject(hOldBmp);
	return TRUE;
}

HBRUSH CQfPayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //���ش˻�ˢ����ʹ��̬�ı�͸��
	}
	return hbr;
}
