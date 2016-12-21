#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 
#include "WebDlgInterface.h"
// CWebDlg �Ի���

class CWebDlg : public CDHtmlDialog,public CWebDlgInterface
{
	DECLARE_DYNCREATE(CWebDlg)

public:
	CWebDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWebDlg();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	void PaySuccess(LPCTSTR str);
// �Ի�������
	enum { IDD = IDD_WEBDLG, IDH = 0 };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL IsExternalDispatchSafe(){ return TRUE;}
	

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	DECLARE_DISPATCH_MAP()
	virtual void OnOK();
};
