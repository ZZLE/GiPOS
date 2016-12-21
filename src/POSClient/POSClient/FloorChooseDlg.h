#pragma once
// CFloorChooseDlg �Ի���

class CFloorChooseDlg : public CDialog
{
	DECLARE_DYNAMIC(CFloorChooseDlg)

public:
	CFloorChooseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFloorChooseDlg();

// �Ի�������
	enum { IDD = IDD_FLOORCHOOSE };
	int m_nTableId;
	int m_nFilterId;
	int m_nNoUsedTable;
	CString m_strPrefix;
	CString m_strTitle;
	BOOL m_bMultiSelect;
	std::vector<int> m_tableList;

protected:
	CFont mTableFont;
	Gdiplus::Image* m_bpTableStatus[6];
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btOK;

	int m_nPageSize;
	int m_nCurrentPage;
	int m_nPageCount;
	int m_x,m_y;

	std::vector<CButton*> m_itemButtons;
	vector<TableItem> m_RVCTables;//��ǰRVC��ʾ������

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void ShowCurrentPage();
	void UpdateRvc(int rvc_id,BOOL reset);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedRadio(UINT uID);
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnTableClicked(UINT uID);
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};
