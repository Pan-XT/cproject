#include "Fac.h"
#include "iostream.h"
#pragma comment(lib,"DllDemo.lib")

void main(){
	int n;
	cout<<"��̬����DLL\n";
	while(true){
		cout<<"���������ڼ���׳˵���ֵ\n";
		cin>>n;
		int r=Fun(n);
		cout<<"����Ľ����"<<r<<endl;

	}
}