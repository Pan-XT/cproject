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
	ON_BN_CLICKED(SEND2, &CFileTransferDialog::OnBnClickedSend2)
END_MESSAGE_MAP()


void CFileTransferDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	TCHAR szFileName[MAX_PATH];
	int iFileNumber;

	// 得到拖拽操作中的文件个数
	iFileNumber = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i = 0; i < iFileNumber; i++)
	{
		// 得到每个文件名
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);

		/*if (FindString(0, szFileName) != LB_ERR)
		continue;*/

		// 把文件名添加到list中
//		files.AddString(szFileName);
		//msg.SetWindowTextW(szFileName);
	}
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CFileTransferDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO:  在此添加专用代码和/或调用基类

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

	// TODO:  在此添加额外的初始化

	ChangeWindowMessageFilter(WM_SETTINGCHANGE, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); //0x0049==WM_COPYGLOBALDATA


	files.InsertColumn(0, L"序号", LVCFMT_CENTER,60);
	files.InsertColumn(1, L"文件名", LVCFMT_LEFT, 520);
	files.InsertColumn(2, L"完成度", LVCFMT_LEFT, 60);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
int index = 1;
void CFileTransferDialog::scan(CString dir){
	CFileFind find;
	bool f = find.FindFile(dir + "\\*.*");
	if (!f){
		return;
	}
	while (f){
		f = find.FindNextFile();
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
	// TODO:  在此添加控件通知处理程序代码
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

	int prefix = m_fpath.GetLength();

	int count = files.GetItemCount();
	WIN32_FIND_DATA info;
	char buf[4096];
	UINT len = 0;
	for (int i = 0; i < count; i++){
		CString name = files.GetItemText(i, 1);
		HANDLE h = FindFirstFile(name, &info);
		send(sock, (char*)&info, sizeof(info), 0);
		u_long pth = name.GetLength() - prefix;
		CString pname = name.Right(pth);
		pth = pname.GetLength()*sizeof(TCHAR);
		pth = htonl(pth);
		send(sock, (char*)&pth, sizeof(pth), 0);
		send(sock, CT2A(pname), pth, 0);
		if (info.dwFileAttributes != CFile::directory){
			CFile file(name,CFile::OpenFlags::modeRead|CFile::OpenFlags::typeBinary);
			len = file.Read(buf, 4096);
			while (len > 0){
				send(sock, buf, len, 0);
				len = file.Read(buf, 4096);
			}
			file.Close();
		}
		FindClose(h);
	}

}


void CFileTransferDialog::OnBnClickedSend2()
{
	UpdateData(TRUE);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock){
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	listen(sock, 5);
	int addrLen = sizeof(addr);
	SOCKET client = accept(sock, (SOCKADDR*)&addr, &addrLen);
	char buf[4096];
	int len;
	LPWIN32_FIND_DATA info;
	while (true){
		len = recv(client, buf, 4096, 0);
		if (len == -1){
			break;
		}
		if (len == 0){
			break;
		}
		info = (WIN32_FIND_DATA*)buf;
		char* pb = buf;
		pb += sizeof(*info);
		u_long plen = *(u_long*)pb;
		plen = ntohl(plen);
		pb += sizeof(int);
		CString path(pb, plen);

		CString s;
		s.Format(L"%d", index++);

		files.InsertItem(0, L"");
		files.SetItemText(0, 0, s);
		files.SetItemText(0, 1, path);
		files.SetItemText(0, 2, L"0%");
		if (info->dwFileAttributes == CFile::directory){
		//	GetFileAttributes()
		}

	}
}
