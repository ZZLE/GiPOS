// ServerIpSetting.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MultiLanguage.h"

// CServerIpSettingApp:
// �йش����ʵ�֣������ ServerIpSetting.cpp
//

class CServerIpSettingApp : public CWinApp
{
public:
	CServerIpSettingApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServerIpSettingApp theApp;
extern CMultiLanguage	theLang;