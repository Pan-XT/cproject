/***************************************************************************************
*                                                                                      *
*                                                                                      *
*	ʵ�ֹ���:                                                                          *
*	1.	һ�������ڰ��������Ӵ��ڣ��ֱ���ɣ��������ֺ���ʾʫ��                         *
*	����ʾ����λͼ����ʾ��̬�任λͼ                                                   *
*	2.  �����������ߵĳ������Ӵ��ڣ�������ʾ�������ֵĿؼ���                       *
*	����������ѡ���Լ������ϵ������ļ���֧�ֻ��������еĸ�ʽ                       *
*	3.	�˳������ҵڶ���Ϊ�Լ���Ů���ѱ�д�ģ�������������ң�ϣ���ܸ���Ҵ������   *
*                                                                                      *
*                                                                                      *
*                                                                                      *
*------------------------------------Դ�ļ�����LoveWindow.c                            *
*---------------------------------------�����ߣ���С��                                 *
*--------------------------------------ʱ�䣺2013/08/19                                *
****************************************************************************************/

#include<windows.h>
#include<stdio.h>
#include <vfw.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"resource.h"

#pragma comment(lib,"vfw32.lib")

//��ʱ��ID
#define ID_TIMER_POEM		0
#define ID_TIMER_LOVE		1
#define ID_TIMER_BMP		2
//���ڵĸ���
#define NUM					3

//Ϊ�˱��⺯���Ĳ����趨̫�࣬�Ե����࣬����趨һ�±���Ϊȫ��
FILE	*fp = NULL;//�ļ�ָ��
TCHAR	word[2];//�ַ����� , �����ȡ��һ����
int		row, col;//����кź��к�
int		cxChar, cyChar;//ϵͳ�ַ���size  �ֱ����ַ���ƽ����ȡ��ַ��ĸ߶�


LRESULT CALLBACK WndProc	(HWND, UINT, WPARAM, LPARAM);//�����ڻص�����
LRESULT CALLBACK PoemChild	(HWND, UINT, WPARAM, LPARAM);//ʫ���Ӵ��ڻص�����
LRESULT CALLBACK LoveChild	(HWND, UINT, WPARAM, LPARAM);//����λͼ�Ӵ��ڻص�����
LRESULT CALLBACK BmpChild	(HWND, UINT, WPARAM, LPARAM);//��̬�任λͼ�Ӵ��ڻص�����
int ShowWord(HDC);//��ʾһ����


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
                   PSTR szCmdLine,
				   int iCmdShow)
{
	static	TCHAR	szAppName[] = TEXT("LoveWindow");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;
	int				cxScreen, cyScreen;
	
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//CreateSolidBrush(RGB(57, 138, 219));
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szAppName;
	
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	
	hwnd = CreateWindow(szAppName,
						TEXT("LoveWindow"),
						WS_POPUPWINDOW,//����ʽ����(�ޱ߿�ͱ�����)
						cxScreen * 3 / 14,//������ʾ
						cyScreen / 8,
						cxScreen * 4 / 7,
						cyScreen * 3 / 4,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

//��ʾһ����
int ShowWord(HDC hdc)
{
	TCHAR c;

	if(fscanf(fp, "%c", &c) != EOF)
	{
		if(c == '\n')
		{
			row++;
			col = 0;

			/*
			�������'\n',˵����Ҫ����,���к�,��һ������
			Ҫ����һ�����ֶ���,���Ҫ���б�col����*/
		}

		else
		{
			word[0] = c;
			fscanf(fp, "%c", &c);
			word[1] = c;
			col++;

			/*
			�����޸�������Ĵ�С��ԭ���Ϻ��ϴε���ͬ
			*/

			TextOut(hdc, col * (23 * cxChar / 12 + 3) + 95, row * cyChar * 39 / 40 + 27, word, 2);
		}

		return 0;
	}

	return EOF;
}

//ʫ���Ӵ��ڻص�����(��̬��ʾʫ�衢��������(���ֿ�����ѡ��))
LRESULT CALLBACK PoemChild(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static	HBITMAP	hBmp;
	static	HFONT	hFont;
	static	int		cxBitmap, cyBitmap;
	static	HWND	hwndMci;
	BITMAP			bmp;
	LOGFONT			lf;
	HDC				hdc, hdcMem;
	PAINTSTRUCT		ps;
	TEXTMETRIC		tm;

	switch(message)
	{
	case WM_CREATE:
		//��ʼ���ز���������(ʹ��MCI�ؼ�)
		hwndMci = MCIWndCreate(hwnd, ((LPCREATESTRUCT)lParam)->hInstance,
							MCIWNDF_SHOWNAME,TEXT("˭.mp3"));
		
		ShowWindow(hwndMci, SW_HIDE);
		MCIWndPlay(hwndMci);

		//����λͼ
		hBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BMPPOEM));
		GetObject(hBmp, sizeof(BITMAP), &bmp);

		cxBitmap = bmp.bmWidth;
		cyBitmap = bmp.bmHeight;

		/**********************��ȡϵͳ�ı�����*************************/
		hdc = GetDC(hwnd);

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;

		ReleaseDC(hwnd, hdc);

		//�趨��ʱ��
		SetTimer(hwnd, ID_TIMER_POEM, 400, NULL);

		//��������
		ZeroMemory(&lf, sizeof(LOGFONT));

		lf.lfHeight		= -15;
		lf.lfUnderline	= 1;

		hFont = CreateFontIndirect(&lf);

		//��ʫ���ļ�
		if((fp = fopen("res\\Poem.txt", "r")) == NULL)
		{
			MessageBox(hwnd, TEXT("������˼�����Ҳ���������ʫ����o(�s���t)o"), TEXT("��ʾ"), MB_OK);
			exit(1);
		}
		row = col = 0;
		return 0 ;

	//���Ʊ���λͼ
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBmp);

		BitBlt(hdc, 0, 0, cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);

		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		return 0;

	//ͨ����Ӧ�����Ϣ������MCI����������ʾ������
	case WM_LBUTTONDOWN:
		if(IsWindowVisible(hwndMci))
		{
			ShowWindow(hwndMci, SW_HIDE);
		}

		else
		{
			ShowWindow(hwndMci, SW_NORMAL);
		}
		return 0;

	//ͨ����ʱ��������ʫ�����ʾ
	case WM_TIMER:
		hdc = GetDC(hwnd);

		//�趨�ı���ɫ
		SetTextColor(hdc, RGB(rand() % 255,
			rand() % 205, rand() % 255));
		SetBkMode(hdc,TRANSPARENT);//�趨�ı��ı���͸��

		SelectObject(hdc, hFont);

		//����ļ���ȡ���� , ��ʱ��ҲӦ�ùر� , ����˷���Դ
		if(ShowWord(hdc) == EOF)
		{
			KillTimer(hwnd, ID_TIMER_POEM);
		}
		
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_DESTROY:
		MCIWndDestroy(hwndMci);
		DeleteObject(hFont);
		DeleteObject(hBmp);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

//����λͼ�Ӵ��ڻص�����
LRESULT CALLBACK LoveChild(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP	hBmp[NUM];
	static POINT	bmpPos[NUM];
	static int		moveIndex[NUM] = {5, 5, 5};
	static WORD		bmpID[] = {IDB_BMPI, IDB_BMPLOVE, IDB_BMPYOU};
	static int		cxClient, cyClient, cxBitmap, cyBitmap;
	BITMAP			bmp;
	HDC				hdc, hdcMem;
	PAINTSTRUCT		ps;
	int				i;

	switch(message)
	{
	case WM_CREATE:
		//���ü�ʱ��
		SetTimer(hwnd, ID_TIMER_LOVE, 100, NULL);

		//����λͼ
		for(i=0; i<NUM; i++)
		{
			hBmp[i] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, 
								MAKEINTRESOURCE(bmpID[i]));
			bmpPos[i].x = bmpPos[i].y = -10;
		}

		GetObject(hBmp[0], sizeof(BITMAP), &bmp);

		cxBitmap = bmp.bmWidth;
		cyBitmap = bmp.bmHeight;
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		//�޸�λͼλ��
		for(i=0; i<NUM; i++)
		{	
			bmpPos[i].x = cxClient * i / 3;
			if(bmpPos[i].x == -10)
			{
				bmpPos[i].y = rand() % (cyClient - cyBitmap);
			}
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);

		for(i=0; i<NUM; i++)
		{
			//�ж�λͼ��λ��  ������Ӧ���˶�����ĸı�
			if(bmpPos[i].y < 0)//�ϱ߽�
			{
				moveIndex[i] = rand() % 10 + 5;
			}

			if(bmpPos[i].y >= (cyClient - cyBitmap))//�±߽�
			{
				moveIndex[i] = - (rand() % 10 + 5);
			}

			bmpPos[i].y += moveIndex[i];

			SelectObject(hdcMem, hBmp[i]);

			BitBlt(hdc, bmpPos[i].x, bmpPos[i].y, 
				cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);
		}

		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE);//������Ч����  ���ǲ��ػ汳��(FALSE)
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER_LOVE);
		
		for(i=0; i<NUM; i++)
		{
			DeleteObject(hBmp[i]);
		}
		
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

//��̬�任λͼ�Ӵ��ڻص�����
LRESULT CALLBACK BmpChild(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP	hBmp[10];
	static WORD		bmpID[] = {IDB_BITMAP4, IDB_BITMAP5, IDB_BITMAP6, IDB_BITMAP7,
							   IDB_BITMAP8, IDB_BITMAP9, IDB_BITMAP10, IDB_BITMAP11,
							   IDB_BITMAP12, IDB_BITMAP13};
	static int		cxBitmap, cyBitmap, curBmpIndex;
	BITMAP			bmp;
	HDC				hdc, hdcMem;
	PAINTSTRUCT		ps;
	int				i;

	switch(message)
	{
	case WM_CREATE:
		//���ü�ʱ��
		SetTimer(hwnd, ID_TIMER_BMP, 5000, NULL);

		//����λͼ
		for(i=0; i<10; i++)
		{
			hBmp[i] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, 
								MAKEINTRESOURCE(bmpID[i]));
		}

		GetObject(hBmp[0], sizeof(BITMAP), &bmp);

		cxBitmap = bmp.bmWidth;
		cyBitmap = bmp.bmHeight;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);

		SelectObject(hdcMem, hBmp[curBmpIndex]);

		BitBlt(hdc, 3, 8, cxBitmap, cyBitmap, hdcMem, 0, 0, SRCCOPY);

		curBmpIndex = (curBmpIndex + 1) % 10;

		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER_BMP);

		for(i=0; i<10; i++)
		{
			DeleteObject(hBmp[i]);
		}

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND		hwndChild[NUM];
	static TCHAR*	szChildClassName[] = {TEXT("PoemChild"), TEXT("LoveChild"), TEXT("BmpChild")};
	static WNDPROC	childProc[] = {PoemChild, LoveChild, BmpChild};
	HINSTANCE		hInstance;
	WNDCLASS		wndclass;
	int				i, cxClient, cyClient;
	
	switch(message)
	{
	case WM_CREATE:
		if(IDYES == MessageBox(hwnd, TEXT("׼���������ҵ���������?"), TEXT("LoveWindow"), MB_YESNO))
		{
			Sleep(2000);
		}

		else
		{
			SendMessage(hwnd, WM_DESTROY, wParam, lParam);
		}

		//�����Ӵ���
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		wndclass.cbClsExtra		= 0;
		wndclass.cbWndExtra		= 0;
		wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon			= NULL;
		wndclass.hInstance		= hInstance;
		wndclass.lpszMenuName	= NULL;
		wndclass.style			= CS_HREDRAW | CS_VREDRAW;

		for(i=0; i<NUM; i++)
		{
			if(i == 2)
				wndclass.hbrBackground	= CreateSolidBrush(RGB(73, 229, 225));

			wndclass.lpfnWndProc	= childProc[i];
			wndclass.lpszClassName	= szChildClassName[i];

			RegisterClass(&wndclass);

			hwndChild[i] = CreateWindow(szChildClassName[i], NULL,
										WS_CHILD | WS_VISIBLE,
										0, 0, 0, 0,
										hwnd, NULL, hInstance,
										NULL);
		}
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		MoveWindow(hwndChild[0], 0, 0, cxClient / 2, cyClient, TRUE);
		MoveWindow(hwndChild[1], cxClient / 2 + 3, 0, cxClient / 2, cyClient / 2, TRUE);
		MoveWindow(hwndChild[2], cxClient / 2 + 3, cyClient / 2 + 3, cxClient / 2 , cyClient / 2, TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
