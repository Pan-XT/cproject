#include "stdafx.h"
#include "FileTransferDialog.h"


CFileTransferDialog::CFileTransferDialog(CWnd* parent) :CDialogEx(CFileTransferDialog::IDD,parent
	)
{
}


CFileTransferDialog::~CFileTransferDialog()
{
}
BEGIN_MESSAGE_MAP(CFileTransferDialog, CDialogEx)
	ON_WM_DROPFILES()
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
		files.AddString(szFileName);
	}
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CFileTransferDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, files);
}


BOOL CFileTransferDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	ChangeWindowMessageFilter(WM_SETTINGCHANGE, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); //0x0049==WM_COPYGLOBALDATA
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
