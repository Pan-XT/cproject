#include<iostream.h>
class Base{
private:
	int baseData;
public:
	Base(int baseIn);
	Base();
	void print() const;
};
Base::Base(int baseIn){
	this->baseData=baseIn;
};
Base::Base(){
};
void Base::print() const{
	cout<<"ާ����ʳ������ֵΪ��"<<baseData<<endl;
};

class Derived:public Base{
private:
	int deriveData;
public:
	Derived(int baseIn,int derivedIn);
	void print() const;
};
Derived::Derived(int baseIn,int derivedIn):Base(baseIn){
	deriveData=derivedIn;
};
void Derived::print() const{
	Base::print();
	cout<<"�������а���������ֵΪ��"<<deriveData<<endl;
}

void main(){
	cout<<"ת��֮ǰ:"<<endl;
	Base baseObj(10);
	baseObj.print();
	cout<<"ת��֮��:"<<endl;
	Derived derivedObj(3,5);
	baseObj=derivedObj;
	baseObj.print();

	cout<<"����ת������ָ��:===================="<<endl;
	Base *pB=new Derived(3,5);
	pB->print();
	Derived *pD=new Derived(4,10);
	pD=(Derived *)(pB);
	if(pD){
		pD->print();
	}
	return;
}
