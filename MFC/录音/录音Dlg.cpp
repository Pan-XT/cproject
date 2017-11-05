// ¼��Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "¼��.h"
#include "mmsystem.h"     // ��Ƶ��غ�������ͷ�ļ�
#include "¼��Dlg.h"
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int                 nIn=2;       // pBufferIn[2]�У���ǰ���Ż�������
int                 nOut=2;      // pBufferOut[2]�У���ǰ¼����������

static HWAVEIN      hWaveIn ;        // ¼���豸���
static HWAVEOUT     hWaveOut ;       // �����豸���
static PBYTE        pBufferIn[2];    // ���ڽ��պͲ��ŵ����黺����
static PBYTE        pBufferOut[2];   // ���ڷ��ͺ�¼�������黺����

static PWAVEHDR     pWaveHdrIn[2];   // ����¼����PWAVEHDR�ṹ����
static PWAVEHDR     pWaveHdrOut[2];  // ���ڲ��ŵ�PWAVEHDR�ṹ����
static WAVEFORMATEX waveform ;       // ���ڴ���Ƶ�豸��WAVEFORMATEX�ṹ

#define INP_BUFFER_SIZE 4096   // ��������С
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
//{{AFX_MSG_MAP(CMyDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON1, OnLuyin)

	ON_MESSAGE(MM_WIM_OPEN,ON_MM_WIM_OPEN)
	ON_MESSAGE(MM_WIM_DATA,ON_MM_WIM_DATA)
	ON_MESSAGE(MM_WIM_CLOSE,ON_MM_WIM_CLOSE)
	ON_MESSAGE(MM_WOM_OPEN,ON_MM_WOM_OPEN)

ON_BN_CLICKED(IDC_BUTTON2, OnPlay)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitAudioDevice();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CMyDlg::InitAudioDevice()
{
	// ��ʼ��waveform
	waveform.wFormatTag      = WAVE_FORMAT_PCM ;  // ������ʽ,PCM(����������)
    waveform.nChannels       = 2 ;                // ˫����
    waveform.nSamplesPerSec  = 11025 ;            // ������11.025KHz
    waveform.nAvgBytesPerSec = 11025;             // ������11.025KB/s
    waveform.nBlockAlign     = 2 ;   // ��С�鵥Ԫ��wBitsPerSample��nChannels/8
    waveform.wBitsPerSample  = 8 ;                // ������СΪ8bit
    waveform.cbSize          = 0 ;                // ���Ӹ�ʽ��Ϣ
    
	// ׼��pWaveHdrIn��pWaveHdrOut
	for(int HdrNum=0;HdrNum<=1;HdrNum++)
	{
        // Ϊ�����������ڴ�
		pBufferIn[HdrNum]  = (PBYTE)malloc (INP_BUFFER_SIZE) ;   
        pBufferOut[HdrNum] = (PBYTE)malloc (INP_BUFFER_SIZE) ;
		if (!pBufferIn[HdrNum] || !pBufferOut[HdrNum])
		{
			if (pBufferIn[HdrNum])
				free (pBufferIn[HdrNum]) ;
			if (pBufferOut[HdrNum])
				free (pBufferIn[HdrNum]) ;
			AfxMessageBox(_T("�ڴ����ʧ�ܣ�"),MB_ICONINFORMATION|MB_OK,NULL);
        }
		
		pWaveHdrIn[HdrNum] =new WAVEHDR;
        pWaveHdrOut[HdrNum]=new WAVEHDR;
		
		pWaveHdrOut[HdrNum]->lpData          = (char *)pBufferIn[HdrNum];
        pWaveHdrOut[HdrNum]->dwBufferLength  = INP_BUFFER_SIZE ;
        pWaveHdrOut[HdrNum]->dwBytesRecorded = 0 ;
        pWaveHdrOut[HdrNum]->dwUser          = 0 ;
        pWaveHdrOut[HdrNum]->dwFlags         = WHDR_BEGINLOOP | WHDR_ENDLOOP ;
        pWaveHdrOut[HdrNum]->dwLoops         = 1;
        pWaveHdrOut[HdrNum]->lpNext          = NULL ;
        pWaveHdrOut[HdrNum]->reserved        = 0 ;
		
		pWaveHdrIn[HdrNum]->lpData           = (char *)pBufferOut[HdrNum] ;
		pWaveHdrIn[HdrNum]->dwBufferLength   = INP_BUFFER_SIZE ;
		pWaveHdrIn[HdrNum]->dwBytesRecorded  = 0 ;
		pWaveHdrIn[HdrNum]->dwUser           = 0 ;
		pWaveHdrIn[HdrNum]->dwFlags          = WHDR_BEGINLOOP | WHDR_ENDLOOP ;
		pWaveHdrIn[HdrNum]->dwLoops          = 1 ;
		pWaveHdrIn[HdrNum]->lpNext           = NULL ;
		pWaveHdrIn[HdrNum]->reserved         = 0 ;	
		
	}
	// �򿪲��Ų�����Ƶ�豸
	MMRESULT result;
	result=waveOutOpen (&hWaveOut, WAVE_MAPPER, &waveform, 
		(DWORD) this->m_hWnd, 0, CALLBACK_WINDOW);
    // ��¼�Ʋ�����Ƶ�豸
	if(result==MMSYSERR_NOERROR)
		result=waveInOpen (&hWaveIn, WAVE_MAPPER, &waveform, 
		(DWORD) this->m_hWnd, 0, CALLBACK_WINDOW);
	// Ϊ���ź�¼��׼��
    for(int Prepare=0;Prepare<=1;Prepare++)		
	{
		if(result==MMSYSERR_NOERROR)
			result=waveOutPrepareHeader(hWaveOut, pWaveHdrOut[Prepare], 
			sizeof (WAVEHDR)) ;
		if(result==MMSYSERR_NOERROR)
			result=waveInPrepareHeader(hWaveIn, pWaveHdrIn[Prepare], 
			sizeof (WAVEHDR)) ;	
	} 
	// ��������Ϊ���
	if(result==MMSYSERR_NOERROR)
		result=waveOutSetVolume(hWaveOut,65535);
	// �ɹ�����TRUE
	if(result==MMSYSERR_NOERROR)
    {      
		return TRUE;	
	}
	else
	{
		AfxMessageBox(_T("�򿪲�����Ƶ�豸ʱ��������"),MB_ICONINFORMATION | MB_OK,NULL);
		return FALSE;
	}
}

void CMyDlg::RecordBegin()
{
    // ׼��¼��������
	waveInAddBuffer(hWaveIn, pWaveHdrIn[nOut], sizeof (WAVEHDR)) ;
	// ��ʼ¼��
	waveInStart(hWaveIn) ; 	
	
}
bool flag=true;
void CMyDlg::OnLuyin() 
{
	if(flag){
		RecordBegin();
		flag=false;
		GetDlgItem(IDC_BUTTON1)->SetWindowText("ֹͣ");
	}else{
		waveInClose(hWaveIn);
		flag=true;
		GetDlgItem(IDC_BUTTON1)->SetWindowText("¼��");
		
	}
}

void CMyDlg::OnPlay() 
{
	waveOutWrite(hWaveOut, pWaveHdrOut[nIn], sizeof (WAVEHDR));
	
}
//MM_WIM_CLOSE��Ϣ���������ر�¼���豸ʱ����
void CMyDlg::ON_MM_WIM_CLOSE()
{       
	 waveInUnprepareHeader (hWaveIn, pWaveHdrIn[0], sizeof (WAVEHDR)) ;
	 waveInUnprepareHeader (hWaveIn, pWaveHdrIn[1], sizeof (WAVEHDR)) ;
	 waveInClose (hWaveIn); 	 
	 hWaveIn=NULL; //clear it   
}
void CMyDlg::ON_MM_WIM_DATA()
{
	MessageBox("aaa");
}

void CMyDlg::ON_MM_WIM_OPEN()
{
	//MessageBox("open");
}

void CMyDlg::ON_MM_WOM_OPEN()
{
	//MessageBox("open");
}