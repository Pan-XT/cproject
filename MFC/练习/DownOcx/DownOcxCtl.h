#if !defined(AFX_DOWNOCXCTL_H__6378FE6F_BB9F_474F_98CC_76B838B9E5FB__INCLUDED_)
#define AFX_DOWNOCXCTL_H__6378FE6F_BB9F_474F_98CC_76B838B9E5FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxinet.h>
// DownOcxCtl.h : Declaration of the CDownOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CDownOcxCtrl : See DownOcxCtl.cpp for implementation.

class CDownOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDownOcxCtrl)

// Constructor
public:
	CDownOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CDownOcxCtrl();

	DECLARE_OLECREATE_EX(CDownOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDownOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDownOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDownOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDownOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDownOcxCtrl)
	afx_msg void DownLoad();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CDownOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDownOcxCtrl)
	dispidDownLoad = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNOCXCTL_H__6378FE6F_BB9F_474F_98CC_76B838B9E5FB__INCLUDED)
