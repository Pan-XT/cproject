
// WinDeo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWinDeoApp:
// �йش����ʵ�֣������ WinDeo.cpp
//

class CWinDeoApp : public CWinApp
{
public:
	CWinDeoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinDeoApp theApp;