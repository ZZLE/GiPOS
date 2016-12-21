#ifndef _CrBtnPara_H
#define _CrBtnPara_H
#include <vector>
#include "roundbutton2.h"

typedef std::vector<CRoundButton2*>CPButtonList;
typedef std::vector<CRoundButton2*>::iterator CPbuttonIter;
typedef struct{

	CString name;
	RECT	rect;//��ť��λ��
	//CString icon;//��ťͼƬ�Ĳ���
	CString picture;//����ͼƬ
	//CString iconPos;//��ťͼƬλ��
	CString font;//����
	int fontSize;//�����С
	//COLORREF bkg_color;//������ɫ
	COLORREF txt_color;//������ɫ
	int txt_pos;//����λ��
	int	next_page;//����ð�ť��ת���ĸ�ҳ��
	int	function;//����ð�ťִ���ĸ�����


}CR_BTN_PARA;


//#define GLOBAL		_T("GLOBAL")
#define BTN_NUM		_T("btn_num")


#define BTN_NAME	_T("btn_name")
#define BTN_RECT	_T("rect")
#define BTN_BKG_PIC	_T("pic")
#define BTN_ICON	_T("icon")
#define BTN_ICON_POSITION	_T("icon_position")
#define BTN_FONT	_T("font")
#define BTN_FONT_SIZE	_T("font_size")
#define BTN_BKG_COLOR	_T("bkg_color")
#define BTN_TXT_COLOR	_T("txt_color")
#define BTN_NEXT_PAGE	_T("next_page")
#define BTN_FUNCTION	_T("function")


class CreatButton{
public:
	CreatButton();
	static int m_nFullWidth;
	static int m_nFullHeight;
//private:
	BOOL bSetBk;//��ť͸������ֻ��Ҫ����һ��
public:
	int m_nShowStatus;
	CPButtonList m_buttonList;
	CRect GenaratePage2(CString fileName,CDialog* dlg);
	void CreateBtn2(CR_BTN_PARA btnParam,CDialog* dlg);
	void ReleaseBtn();
	void ShowButtons(int nCmdShow);
	void SetBkGnd(CDC* pDC);
};
#endif