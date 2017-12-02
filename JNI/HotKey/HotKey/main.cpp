#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <Windows.h>

typedef HWND(WINAPI *PROCGETCONSOLEWINDOW)(void);
PROCGETCONSOLEWINDOW consoleWindow;

int main(int argc, char *argv[])
{
	HMODULE hKernel32;
	HWND hCmd;

	//	hKernel32 = GetModuleHandle(_T("kernel32"));
	//	GetConsoleWindow = (PROCGETCONSOLEWINDOW_)GetProcAddress(hKernel32, "GetConsoleWindow");
	//	hCmd = GetConsoleWindow(); //��ȡ����ǰcmd���ھ��
	printf("%d\n", GetConsoleWindow());
	//����Ϊ��ǰcmd����ע���ȼ�Ctrl+M
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 'M');


	//������������Ӧcmd���ڵ�WM_HOTKEY��Ϣ�أ�����

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)){
		if (WM_HOTKEY == msg.message){
			HWND hnd = WindowFromPoint(msg.pt);
			SetWindowText(hnd, L"HELLO");
			SetFocus(hnd);
			if (hnd){
				RECT rect ;
				GetWindowRect(hnd, &rect);
				POINT p;
				printf("hello,world--%d,%d\n", rect.top, rect.left);
			}
		}
	}

	return 0;

}