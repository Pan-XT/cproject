#include <iostream.h>
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

void main(){
	sample s1;
	s1.display();
	(s1++).display();
	s1.display();
	s1++;
	s1.display();
	(++s1).display();
	s1.display();
	
}