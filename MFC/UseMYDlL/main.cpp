#include "iostream.h"
#include "windows.h"
typedef int (*aa)(int);
void main(){
	HINSTANCE hdll=LoadLibrary("DllDemo.dll");
	aa f;
	int a;
	
	if(hdll!=NULL){
		f=(aa)GetProcAddress(hdll,"Fun");
	
	}
		cout<<"������һ����"<<endl;
		cin>>a;
		cout<<"�׳�Ϊ��"<<f(a)<<endl;
	FreeLibrary(hdll);
	
}