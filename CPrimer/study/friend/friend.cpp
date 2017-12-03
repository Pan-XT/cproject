// friend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;
class Z;
class A{
public:
	void put(Z* z);
	void get(Z* z);
};
class Z{
public:
	Z(int i){
		this->i = i;
	}
	void print(){
		cout << "i is " << i << endl;
	}
	//friend class A;// 只有你赋予某个类为你的友元时，那个类才有访问你的私有数据的权利。
	friend void A::put(Z* z);
	friend void put(Z* z);
private:
	int i;	
};
void A::put(Z* z){
	z->i = 20;
}
void A::get(Z* z){
	
}
void put(Z* z){
	z->i = 10;
}
int _tmain(int argc, _TCHAR* argv[])
{
	char ch[] = "178asdfasd";
	Z z(1);
	z.print();
	put(&z);
	z.print();
	A a;
	a.put(&z);
	z.print();
	return 0;
}

