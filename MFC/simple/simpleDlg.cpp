
// simpleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "simple.h"
#include "simpleDlg.h"
#include "afxdialogex.h"
#include "RegHandle.h"

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


// CsimpleDlg �Ի���



CsimpleDlg::CsimpleDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CsimpleDlg::IDD, pParent), name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH, name);
	DDV_MaxChars(pDX, name, 255);
	DDX_Control(pDX, IDC_PATHS, paths);
}

BEGIN_MESSAGE_MAP(CsimpleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_COMMAND(IDM_DELETE, &CsimpleDlg::OnDelete)
END_MESSAGE_MAP()


// CsimpleDlg ��Ϣ�������

BOOL CsimpleDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	ChangeWindowMessageFilter(WM_SETTINGCHANGE, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); //0x0049==WM_COPYGLOBALDATA
	// ::DragAcceptFiles(m_hWnd, TRUE); // �Ի����������䡾���ԡ�-����Ϊ��-��Accept Files����Ϊ��True���������õ��ô��С���֮��ɣ����߿�ѡ��һ��~~~
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CsimpleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsimpleDlg::OnPaint()
{
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
HCURSOR CsimpleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CsimpleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN){
		if (pMsg->wParam == VK_RETURN&&GetDlgItem(IDC_PATH) == GetFocus()){
			UpdateData(TRUE);
			while (paths.GetCount()){
				paths.DeleteString(0);
			}
			CRegHandle cReg;
			CString str = cReg.queryKey(name);
			int start = 0;
			int pos = 0;
			while ((pos = str.Find(_T(";"), start)) != -1)
			{
				paths.AddString(str.Mid(start, pos - start));
				start = pos + 1;
			}
			str = str.Mid(start);
			if (str != _T("")){
				paths.AddString(str);
			}

		}
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN){
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CsimpleDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH];
	int iFileNumber;

	// �õ���ק�����е��ļ�����
	iFileNumber = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i = 0; i < iFileNumber; i++)
	{
		// �õ�ÿ���ļ���
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);

		/*if (FindString(0, szFileName) != LB_ERR)
		continue;*/

		// ���ļ�����ӵ�list��
		paths.AddString(szFileName);
	}
	DragFinish(hDropInfo);
	doSetKey();
}


void CsimpleDlg::OnDelete()
{
	// TODO:  �ڴ���������������
	int index = paths.GetCurSel();
	CString str;
	paths.GetText(index, str);
	str.Insert(0, _T("ȷ��ɾ��:\n"));

	int ret = MessageBox(str, _T("��ʾ"), MB_OKCANCEL | MB_ICONWARNING);
	if (IDOK == ret){
		paths.DeleteString(index);
		doSetKey();
	}
}

void CsimpleDlg::doSetKey(){
	UpdateData(TRUE);
	if (name == _T("")){
		return;
	}
	CRegHandle reg;
	CString str;

	BOOL flag = reg.setKey(name, paths);
	str.Format(_T("��������[%s]����[%s]"), name, flag ? _T("�ɹ�") : _T("ʧ��"));
	MessageBox(str);
}