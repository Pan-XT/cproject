#include <stdio.h>
void main(){
	FILE* file;
	FILE* f;
	file=fopen("F:\\��Ƶ\\C++\\thisָ�����ļ̳�\\thisָ�����ļ̳�.mp4","rb");
	f=fopen("F:\\��Ƶ\\C++\\thisָ�����ļ̳�.mp4","wb");
	if(file==NULL){
		printf("ʧ��");
		
	}else{
		printf("���ڸ��ơ���\n");
		while(!feof(file)){
			fputc(fgetc(file),f);
		}
		printf("�ɹ���\n");
	}
	
	fclose(f);
	fclose(file);

}