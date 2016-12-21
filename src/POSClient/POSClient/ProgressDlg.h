#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ProgressDlg �Ի���

class ProgressDlg : public CDialog
{
	DECLARE_DYNAMIC(ProgressDlg)

public:
	ProgressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProgressDlg();

// �Ի�������
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl mProgress;
	int m_nStep;//������ÿ��ǰ���ٷֱ�
	void Start();
	void Stop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void Reset();
	void Step(int nPos,CString msg);
	CStatic mCtrlHint;
};
