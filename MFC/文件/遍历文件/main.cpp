#include <stdio.h>
#include <windows.h> 
#define MAX_PATH 200
BOOL IsRoot(LPCTSTR lpszPath){ 
	TCHAR szRoot[4]; 
	wsprintf(szRoot, "%c:\\", lpszPath[0]); 
	return (lstrcmp(szRoot, lpszPath) == 0); 
} 

void FindInAll(::LPCTSTR lpszPath) {
	TCHAR szFind[MAX_PATH]; 
	lstrcpy(szFind, lpszPath); 
	if (!IsRoot(szFind)) {
		lstrcat(szFind, "\\");
	} 
	lstrcat(szFind, "*.*"); // �������ļ� 
	WIN32_FIND_DATA wfd; 
	HANDLE hFind = FindFirstFile(szFind, &wfd); 
	if (hFind == INVALID_HANDLE_VALUE) // ���û���ҵ������ʧ�� 
		return; 
	
	do 
	{ 
		if (wfd.cFileName[0] == '.') 
			continue; // ����������Ŀ¼ 
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			TCHAR szFile[MAX_PATH]; 
			if (IsRoot(lpszPath)) 
				wsprintf(szFile, "%s%s", lpszPath, wfd.cFileName); 
			else 
				wsprintf(szFile, "%s\\%s", lpszPath, wfd.cFileName); 
			FindInAll(szFile); // ����ҵ�����Ŀ¼��������Ŀ¼���еݹ� 
		} 
		else 
		{ 
			TCHAR szFile[MAX_PATH]; 
			if (IsRoot(lpszPath)) 
				wsprintf(szFile, "%s%s", lpszPath, wfd.cFileName); 
			else 
				wsprintf(szFile, "%s\\%s", lpszPath, wfd.cFileName); 
			printf("%s\n",szFile); 
			// ���ļ����в��� 
		} 
	}while (FindNextFile(hFind, &wfd)); 
	FindClose(hFind); // �رղ��Ҿ�� 
	
} 
int main(int argc, char* argv[]){ 
	FindInAll("D:\\"); 

	return 0; 
} 