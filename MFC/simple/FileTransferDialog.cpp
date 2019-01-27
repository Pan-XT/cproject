#include "stdafx.h"
#include "FileTransferDialog.h"


CFileTransferDialog::CFileTransferDialog(CWnd* parent) :CDialogEx(CFileTransferDialog::IDD,parent
	)
	, m_ip(_T("127.0.0.1"))
	, m_port(8899)
	, m_fpath(_T(""))
{
}


CFileTransferDialog::~CFileTransferDialog()
{
}
BEGIN_MESSAGE_MAP(CFileTransferDialog, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(SEND, &CFileTransferDialog::OnBnClickedSend)
END_MESSAGE_MAP()


void CFileTransferDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
//		files.AddString(szFileName);
		//msg.SetWindowTextW(szFileName);
	}
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CFileTransferDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, files);
	DDX_Control(pDX, IDC_EDIT1, msg);
	DDX_Text(pDX, IDC_EDIT2, m_ip);
	DDX_Text(pDX, IDC_EDIT3, m_port);
	DDX_Control(pDX, IDC_LIST1, files);
	DDX_Text(pDX, IDC_EDIT4, m_fpath);
}


BOOL CFileTransferDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	ChangeWindowMessageFilter(WM_SETTINGCHANGE, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); //0x0049==WM_COPYGLOBALDATA


	files.InsertColumn(0, L"���", LVCFMT_CENTER,60);
	files.InsertColumn(1, L"�ļ���", LVCFMT_LEFT, 520);
	files.InsertColumn(2, L"��ɶ�", LVCFMT_LEFT, 60);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
int index = 1;
void CFileTransferDialog::scan(CString dir){
	CFileFind find;
	bool f = find.FindFile(dir + "\\*.*");
	if (!f){
		return;
	}
	while (f){
		f = find.FindNextFileW();
		if (find.IsDots()){
			continue;
		}
		CString s;
		s.Format(L"%d", index++);

		files.InsertItem(0, L"");
		files.SetItemText(0, 0, s);
		files.SetItemText(0, 1, find.GetFilePath());
		files.SetItemText(0, 2, L"0%");
		if (find.IsDirectory()){
			scan(find.GetFilePath());
		}
	}
	find.Close();

}
void CFileTransferDialog::OnBnClickedSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	scan(m_fpath);
	sendFile();
}
void CFileTransferDialog::sendFile(){

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock){
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	addr.sin_addr.S_un.S_addr = inet_addr(CT2A(m_ip));

	int code = connect(sock, (SOCKADDR*)&addr, sizeof(addr));

	int count = files.GetItemCount();
	for (int i = 0; i < count; i++){
		CString name = files.GetItemText(i, 1);
		CFile file(name,CFile::OpenFlags::modeRead);
	}

}
