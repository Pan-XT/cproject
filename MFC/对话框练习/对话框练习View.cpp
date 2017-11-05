// �Ի�����ϰView.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "�Ի�����ϰ.h"

#include "�Ի�����ϰDoc.h"
#include "�Ի�����ϰView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView
static const UINT MsgFindReplace=::RegisterWindowMessage(FINDMSGSTRING);
IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_FONT, OnFont)
	ON_COMMAND(ID_FIND, OnFind)
	ON_COMMAND(ID_REPLACE, OnReplace)
	ON_COMMAND(ID_TEXTCOLOR, OnTextcolor)
	ON_COMMAND(ID_BACKCOLOR, OnBackcolor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(MsgFindReplace,OnFindReplace)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here
	frontColor=0;
	backColor=0xFFFFFF;
	fnt.CreateStockObject(SYSTEM_FONT);
	str="һ�����ڶԻ����MFC AppWizardӦ�ó����У���θı�Ի���ı�����ɫ�أ�����������⣬��ʵ���� �ɼ��ֲ�ͬ�ķ�����ʵ�֣��������£���б�����Ϊ����ģ���		---- ����һ������CWinApp��ĳ�Ա����SetDialogBkColor��ʵ�֡�		---- ���к����ĵ�һ������ָ���˱�����ɫ���ڶ�������ָ�����ı���ɫ������������ǽ�Ӧ�ó���Ի� ������Ϊ��ɫ�����ͺ�ɫ�ı����������£�		---- �� �½�һ������Dialog��MFC AppWizardӦ�ó���ExampleDlg��---- �� ��CExampleDlgApp ::InitInstance()��������´��룺BOOL CExampleDlgApp: : InitInstance ( )";
	pFindReplaceDlg=NULL;
	pos=0;

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFont *pOldFont;
	pOldFont=pDC->SelectObject(&fnt);
	pDC->SetTextColor(frontColor);
	pDC->SetBkColor(backColor);
	CRect textrect(40,50,540,500);
	pDC->DrawText(str,&textrect,DT_LEFT|DT_WORDBREAK);
	pDC->SelectObject(pOldFont);

	// TODO: add draw code for native data here
}
LRESULT CMyView::OnFindReplace(WPARAM wP,LPARAM lP){
	
	if(pFindReplaceDlg->IsTerminating())
		pFindReplaceDlg=NULL;
	
	CFindReplaceDialog *pDlg=CFindReplaceDialog::GetNotifier(lP);
	CString m_FindString=pDlg->GetFindString();
	CString m_ReplaceString=pDlg->GetReplaceString();
	CString strpos;
	if(pDlg->FindNext()){
		pos=str.Find(m_FindString,pos);
		if(pos==-1){
			AfxMessageBox("������ϣ�û���ҵ�ָ���ַ���");
			pos=0;
		}else{
			strpos.Format("���ҵ��ַ���λ��Ϊ%d",pos);
			pos++;
			AfxMessageBox(strpos);
		}
	}
	if(pDlg->ReplaceAll()){
		str.Replace(m_FindString,m_ReplaceString);
		Invalidate();
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnFont() 
{
	// TODO: Add your command handler code here
	LOGFONT lf;
	fnt.GetLogFont(&lf);
	CFontDialog dlg(&lf,CF_EFFECTS|CF_SCREENFONTS,0,this);
	if(dlg.DoModal()==IDOK){
		LOGFONT f;
		dlg.GetCurrentFont(&f);
		frontColor=dlg.GetColor();

		fnt.DeleteObject();
		fnt.CreateFontIndirect(&f);
		Invalidate();
	}
}

void CMyView::OnFind() 
{
	// TODO: Add your command handler code here
	pos=0;
	if(pFindReplaceDlg){
		if(bFindOnly){
			pFindReplaceDlg->SetActiveWindow();
			return;
		}else{
			pFindReplaceDlg->SendMessage(WM_CLOSE);
			return;
		}
	}
	bFindOnly=TRUE;
	pFindReplaceDlg=new CFindReplaceDialog();
	pFindReplaceDlg->Create(true,NULL,NULL,FR_DOWN,this);
}

void CMyView::OnReplace() 
{
	// TODO: Add your command handler code here
	pos=0;
	if(pFindReplaceDlg){
		if(!bFindOnly){
			pFindReplaceDlg->SetActiveWindow();
			return;
		}else
			pFindReplaceDlg->SendMessage(WM_CLOSE);
	}
	bFindOnly=false;
	pFindReplaceDlg=new CFindReplaceDialog();
	pFindReplaceDlg->Create(false,NULL,NULL,FR_DOWN,this);
}

void CMyView::OnTextcolor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg(frontColor,CC_FULLOPEN);
	if(dlg.DoModal()==IDOK){
		frontColor=dlg.GetColor();
	}
	Invalidate();
}

void CMyView::OnBackcolor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg(backColor,CC_FULLOPEN);
	if(dlg.DoModal()==IDOK){
		backColor=dlg.GetColor();
	}
	Invalidate();
}
