#include <iostream.h>
#include <string.h>

class parent{
	char f_name[20];
	char m_name[20];
	char tel[11];
public:
	parent(char *p1="",char *p2="",char *p3=""){
		strcpy(f_name,p1);
		strcpy(m_name,p2);
		strcpy(tel,p3);
	}
	friend void show(parent &p);
};
void show(parent &p) {
	cout<<"���׵����֣�"<<p.f_name<<endl;
	cout<<"ĸ�׵����֣�"<<p.m_name<<endl;
	cout<<"�� �� ���룺"<<p.tel<<endl;
	
}
void main(){
	
	parent p1;
	p1=parent("����","��ʫ","123213123");
	show(p1);
}