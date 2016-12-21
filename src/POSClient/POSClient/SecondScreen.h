#pragma once
#include "afxcmn.h"
//#include "POSClient.h"
#include "afxwin.h"
#include "CheckDlg.h"
//


// CMySecondScreen �Ի���

class SecondScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(SecondScreenDlg)

public:
	SecondScreenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SecondScreenDlg();

	// �Ի�������
	enum { IDD = IDD_SNDSCREEN };
	int m_picIndex;//ָ����ǰ��ʾ��ͼƬ
	std::vector<CString> m_vStrAllFiles;//����ָ���ļ��������е�ͼƬ
	CString m_scan_file;
	int m_total_width ;//�����Ի���Ĵ�С
	int m_total_height;
	BOOL m_bHideDetail;
	HBITMAP m_bpBackgrd;
	int i_image_width;
	int i_image_height;
	CCheckDlg m_checkDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL ReshowAll(CCheckDlg& from);
	VOID AddItem(CCheckDlg& from,LPCTSTR item);
	void ScanDiskFile(const CString& strPath);
	void ShowPicture(CString path);
	VOID ShowAmount(double m_fDue,double m_fDebt);
	void MoveWindow2(HWND m_hWnd,int width,int height);
	void HideDetail();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
