#include <stdio.h>
#include <io.h>
#include <string.h>
#include <time.h>
static int i=0;
FILE *file;
void findAll(const char *p){
	char path[2000];
	memset(path,0,sizeof(path));
	strcat(path,p);
	strcat(path,"\\*.*");
	_finddata_t t;
	long l=_findfirst(path,&t);
	if(l){
		int n=_findnext(l,&t);
		while(!n){
			if(t.name[0]!='.'){
				memset(path,0,sizeof(path));
				strcat(path,p);
				strcat(path,"\\");
				strcat(path,t.name);
				fprintf(file,"%s\t|����ʱ�䣺%s",path,ctime(&t.time_create));
				i++;
				findAll(path);
			}
			n=_findnext(l,&t);
		}
	}
	
}
void main(){
	time_t ct, et;
	time(&ct);
	file=fopen("D:\\�����ֻ��ļ�.txt","w");
	fprintf(file,"ɨ��ʱ�䣺%s\n",ctime(&ct));
	findAll("F:");
	fprintf(file,"һ����%d\n",i);
	time(&et);
	fprintf(file,"��ʱ%ld��\n",et-ct);
	fclose(file);

}
