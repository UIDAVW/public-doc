
// win_sdk_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cwin_sdk_demoApp:
// �йش����ʵ�֣������ win_sdk_demo.cpp
//

class Cwin_sdk_demoApp : public CWinApp
{
public:
	Cwin_sdk_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cwin_sdk_demoApp theApp;