
// WinDeoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinDeo.h"
#include "WinDeoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinDeoDlg �Ի���



CWinDeoDlg::CWinDeoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinDeoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinDeoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinDeoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CWinDeoDlg ��Ϣ�������

BOOL CWinDeoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/**
	CRect rc;
	GetWindowRect(rc);
	CPoint pt[4];
	pt[0].x=0;
	pt[0].y=rc.Height();
	pt[1].x=rc.Width()/2;
	pt[1].y=rc.Height();
	pt[2].x=rc.Width();
	pt[2].y=0;
	pt[3].x=rc.Width()/2;
	pt[3].y=0;
	CRgn m;
	m.CreatePolygonRgn(pt,4,ALTERNATE);
	SetWindowRgn(m,TRUE);
	**/
	//�Զ�����״2
	COLORREF transColor=RGB(0,0,0);
	CBitmap cBitmap;
	cBitmap.LoadBitmapW(IDB_BITMAP1);
	CDC* pDC=this->GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOld=NULL;
	pOld=memDC.SelectObject(&cBitmap);
	CRgn wndRgn;
	wndRgn.CreateRectRgn(0,0,0,0);
	BITMAP bit;
	cBitmap.GetBitmap(&bit);
	int y;
	CRgn rgnTemp;
	for(y=0;y<bit.bmHeight;y++){
		int ix=0;
		do{
			while(ix<bit.bmWidth&&memDC.GetPixel(ix,y)==transColor)++ix;
			int iLeftX=ix;
			while(ix<bit.bmWidth&&memDC.GetPixel(ix,y)!=transColor)++ix;
			rgnTemp.CreateRectRgn(iLeftX,y,ix,y+1);
			wndRgn.CombineRgn(&wndRgn,&rgnTemp,RGN_OR);
			rgnTemp.DeleteObject();
		}while(ix<bit.bmWidth);
	}
	SetWindowRgn(wndRgn,TRUE);
	memDC.DeleteDC();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWinDeoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWinDeoDlg::OnPaint()
{
	CWindowDC wndDC(this);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush *pOldBrush=wndDC.SelectObject(&brush);
	wndDC.Rectangle(0,0,342,426);
	wndDC.SelectObject(pOldBrush);

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWinDeoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

