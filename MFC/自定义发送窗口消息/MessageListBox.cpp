// MessageListBox.cpp : implementation file
//

#include "stdafx.h"
#include "�Զ��巢�ʹ�����Ϣ.h"
#include "MessageListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageListBox

CMessageListBox::CMessageListBox()
{
}

CMessageListBox::~CMessageListBox()
{
}


BEGIN_MESSAGE_MAP(CMessageListBox, CListBox)
	//{{AFX_MSG_MAP(CMessageListBox)
	ON_CONTROL_REFLECT(LBN_DBLCLK, OnDblclk)
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageListBox message handlers

void CMessageListBox::OnDblclk() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd=GetParent();
	char szMessage[100];
	strncpy(szMessage,"�б��˫����Ϣ",98);
	int nItemIndex=GetCurSel();
	pWnd->SendMessage(WM_LBMESSAGE_DBCLCK,(WPARAM)&nItemIndex,(LPARAM)szMessage);
}

void CMessageListBox::OnSelchange() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd=GetParent();
	char *pszMessage=new char[100];
	int nItemIndex=GetCurSel();
	strncpy(pszMessage,"�б���µ�ѡ����",98);
	pWnd->PostMessage(wm_selchange,(WPARAM)nItemIndex,(LPARAM)pszMessage);
}
