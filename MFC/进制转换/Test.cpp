#include "iostream.h"
#include "string.h"
void main(){
	int num;
	int n;
	int c[128]={0};
	cout<<"����һ��������"<<endl;
	cin>>num;
	cout<<"����Ҫת���Ľ���"<<endl;
	cin>>n;
	int i=0,a=0;
	while(num!=0){
		c[i++]=num%n;
		num=num/n;
		a++;
	}
	cout<<"ת�����ֵΪ��";
	for(i=a-1;i>=0;i--){
		cout<<c[i];
	}
	cout<<endl;
}