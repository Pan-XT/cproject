
// windowDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CwindowDemoApp: 
// �йش����ʵ�֣������ windowDemo.cpp
//

class CwindowDemoApp : public CWinApp
{
public:
	CwindowDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CwindowDemoApp theApp;