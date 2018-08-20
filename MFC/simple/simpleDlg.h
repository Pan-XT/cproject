
// simpleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyListBox.h"
#include "afxcmn.h"
#include "SoundRecord.h"

#define WM_RECEIVEBROCAST WM_USER+1


// CsimpleDlg �Ի���
class CsimpleDlg : public CDialogEx
{
private:
	//�㲥
	SOCKET broadcast;
	CSoundRecord record;
public:
	CsimpleDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_SIMPLE_DIALOG };

protected:
	// ʵ��
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString name;
	CMyListBox paths;
	afx_msg void OnDelete();
	void doSetKey();
	void InitBroadSocket();
	static DWORD WINAPI recvFromProc(LPVOID lpParameter);

protected:
	afx_msg LRESULT OnReceivebrocast(WPARAM wParam, LPARAM lParam);
public:
	// �û��б�
	CListCtrl m_userList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

struct RECVPARAM{
	SOCKET socket;
	HWND hWnd;
};