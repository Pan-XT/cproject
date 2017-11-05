// exec.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class Student{
private:
	string name;
	int age;
public:
	Student& show(){
		cout<<this->name<<":��ʼ��ı���"<<endl;
		return *this;
	}
	Student(){
		cout<<"constructor void"<<endl;
	}
	Student(string s):name(s){
		cout<<"constructor string"<<endl;
	}
	Student(int a):name("default"){
		cout<<"constructor int"<<endl;
	}
	~Student(){
		cout<<"name:"<<this->name<<": unconstructor "<<endl;
		this->name = "hehe";
	}
};

int main(int argc, char* argv[])
{
	//int i = atoi(" 1234A7af");
	//printf("%d\n",i);
	Student stu("a");
	stu.show();
	return 0;
}

