#include<iostream>
#include<cstdlib>
using namespace std;

template<class type>
type max(type x,type y){
	return (x>y)?x:y;
};

void main(){
	int a,b;
	a=rand();
	b=rand();
	cout<<"a��ֵΪ��"<<a<<endl;
	cout<<"b��ֵΪ��"<<b<<endl;
	cout<<"���ǵ����ֵΪ��"<<max<int>(a,b)<<endl;


	double a1,b1;
	a1=rand();
	b1=rand();
	cout<<"a1��ֵΪ��"<<a1<<endl;
	cout<<"b1��ֵΪ��"<<b1<<endl;
	cout<<"���ǵ����ֵΪ��"<<max(a1,b1)<<endl;


}