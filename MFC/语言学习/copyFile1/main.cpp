#include <fstream>
#include <iostream>
using namespace std;
void main(int argc,char* argv[]){
	cout<<argc<<endl;
	for(int i=0;i<argc;i++){
		cout<<argv[i]<<endl;
	}
	ifstream in;
	
	in.open("test.txt");
	if(!in){
		cerr<<"���ļ�ʧ�ܣ�"<<endl;
		return ;
	}
	char x;
	while(in>>x){
		cout<<x;
	}
	cout<<endl;
	in.close();

}