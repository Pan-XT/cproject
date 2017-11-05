#include "stdio.h"
#include "string.h"
const int len=128;




class Person{
private:
	char name[len];
	char age[len];
	char sex[len];
public:
	void setName(const char* n){
		strcpy(name,n);
	}
	void setAge(const char* age){
		strcpy(this->age,age);
	}
	void setSex(const char* sex){
		strcpy(this->sex,sex);
	}
	void printInfo();
	virtual void eat()=0;//�鷽��
	Person(){
		printf("Person���췽��!\n");
	}
};
void Person::printInfo(){
	printf("����:%s\n",name);
	printf("����:%s\n",age);
	printf("�Ա�:%s\n",sex);
}
class Men:virtual public Person{
public:
	void eat(){
		printf("men �Է���\n");
	}
	Men(){
		printf("Men ���췽��!\n");
	}
};
class Women:virtual public Person{
public:
	void eat(){
		printf("women �Է���\n");
	}
	Women(){
		printf("Women ���췽��!\n");
	}
};
class Child:public Men,public Women{
public:
	void eat(){
		printf("Child �Է�!\n");
	}
};

int main(){
/*	Person p;
	p.setName("lei");
	p.setAge("24");
	p.setSex("��");
	p.printInfo();
	*/
/*	Person *p=new Women();
	p->setName("������");
	p->setAge("24");
	p->setSex("Ů");
	p->printInfo();
	p->eat();
*/
	Child *c=new Child();
	c->eat();
	return 0;
}