#pragma once


// CLanguageDlg �Ի���

class CLanguageDlg : public CDialog
{
	DECLARE_DYNAMIC(CLanguageDlg)

public:
	CLanguageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLanguageDlg();

// �Ի�������
	enum { IDD = IDD_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	Gdiplus::Image* hbmp;
	Gdiplus::Image* hbmp1;
	std::vector<CButton*> m_itemButtons;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio(UINT uID);
};
