// operator.cpp : �������̨Ӧ�ó������ڵ㡣
//2017��12��3��21:46:58

#include "stdafx.h"
#include <iostream>

using namespace std;

class sample{
private:
	int value;
public:
	sample();
	sample& operator++();//��������ǰ׺������++
	sample operator++(int);//�������غ�׺������++
	void display();
};
sample::sample(){
	value=0;
}
sample& sample::operator ++(){//ǰ׺
	value+=1;
	return (*this);
}
sample sample::operator ++(int){//��׺
	sample sold (*this);
	value+=1;
	return sold;
}
void sample::display(){
	cout<<"value="<<value<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	sample s1;
	s1.display();
	(s1++).display();
	s1.display();
	s1++;
	s1.display();
	(++s1).display();
	s1.display();

	cin.get();
	return 0;
}

