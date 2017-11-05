// Thread.h : main header file for the THREAD application
//

#if !defined(AFX_THREAD_H__8F567B5C_5E35_4E1B_B146_6D1AD6D1E280__INCLUDED_)
#define AFX_THREAD_H__8F567B5C_5E35_4E1B_B146_6D1AD6D1E280__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CThreadApp:
// See Thread.cpp for the implementation of this class
//

class CThreadApp : public CWinApp
{
public:
	CThreadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CThreadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREAD_H__8F567B5C_5E35_4E1B_B146_6D1AD6D1E280__INCLUDED_)
