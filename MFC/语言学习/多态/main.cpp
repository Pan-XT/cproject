#include <iostream.h>
class Base{
public:
	virtual void print() const{
		cout<<"���û����print����."<<endl;
	}
};
class Derived: public Base{
public:
	virtual void print() const{
		cout<<"�����������print������"<<endl;
	}
};
void main(){
	Base *pObj=new Base();
	pObj->print();
	delete pObj;
	pObj=new Derived();
	pObj->print();
	delete pObj;
	return;
	 
}