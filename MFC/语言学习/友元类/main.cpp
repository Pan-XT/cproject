#include <iostream.h>
#include <string.h>
class student;
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
	friend class student;
};
class student{
	int num;
	char name[20];
	float grade;
	parent pt;
public:
	student(int n,char *str,float g,parent t){
		num=n;
		strcpy(name,str);
		grade=g;
		pt=t;
	}
	void show_parent(void) {		
		cout<<"���׵����֣�"<<pt.f_name<<endl;
		cout<<"ĸ�׵����֣�"<<pt.m_name<<endl;
		cout<<"�绰����  : "<<pt.tel<<endl;
		return;
	}
};
void main(void){
	parent p1("����","����","abc");
	student st(10001,"Сѧ��",91.6F,p1);
	cout<<"��ĸ��Ϣ:"<<endl;
	st.show_parent();
}