#include "iostream.h"
#include "Windows.h"
typedef void (*fun)(double,double);
void main(){
	double s1,s2;
	cout<<"��ʽ����MFC DLL\n";
	while(true){
		HINSTANCE hdll;
		fun f;
		hdll=LoadLibrary("RegularDll.dll");
		if(hdll!=NULL){
			f=(fun)GetProcAddress(hdll,"ShowDlg");

		}
		cout<<"�������Ļ��ɼ���"<<endl;
		cin>>s1;
		cout<<"\n�����������ɼ�\n";
		cin>>s2;
		f(s1,s2);
		FreeLibrary(hdll);
	}
}