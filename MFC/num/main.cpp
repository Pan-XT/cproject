#include "stdio.h"
#include <conio.h>
void cup();
int main(){
	int arr[]={1,2,3,4,5,6,7,8,9,10};
	printf("��ʼλ��\n");
	for(int i=0;i<10;i++){
		printf("%d  ",arr[i]);
	}
	printf("\n��������ƶ�������");
	int move;
	scanf("%d",&move);
	printf("\n");
	int tmp[10];
	int j=0;
	for(i=10-move;i<10;i++){
		tmp[j++]=arr[i];
	}
	for(i=0;i<10-move;i++){
		tmp[j++]=arr[i];
	}
	printf("\n���\n");
	for(i=0;i<10;i++){
		printf("%d  ",tmp[i]);
	}
	printf("\n");
	cup();
	return 0;
}

void cup(){
	printf("����һ�е���\n");
	char str[128]={0};
	int i=0,j=0;
	
	while((i=getch())!=13){
		str[j++]=i;
		printf("%c",i);
	
	}
	for(i=0;i<128&&str[i]!=0;i++){
		if(i==0||str[i-1]==' '){
			if(str[i]>='a'&&str[i]<='z'){
				str[i]=str[i]-32; 
			}
		}
	}
	printf("\n");
	for(i=0;i<128&&str[i]!=0;i++){
		printf("%c",str[i]);
	}
	printf("\n");
}