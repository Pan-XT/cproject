#include <iostream>
#include <stdio.h>
using namespace std;

void main(){
	int zm=0;//��ĸ
	int num=0;//����
	int blank=0;//�ո�
	int ot=0;//�����ַ�
	cout<<"������һ�λ�:"<<endl;
	char ch;
	while((ch=getchar())!='\n'){
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
			zm++;
		}else if(ch>='0'&&ch<='9'){
			num++;
		}else if(ch==' '){
			blank++;
		}else{
			ot++;
		}
	}
	cout<<"��ĸ�У�"<<zm<<"��"<<endl;
	cout<<"�����У�"<<num<<"��"<<endl;
	cout<<"�ո��У�"<<blank<<"��"<<endl;
	cout<<"�����У�"<<ot<<"��"<<endl;
	
}