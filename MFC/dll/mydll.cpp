#include "stdio.h"
extern "C" _declspec(dllexport)max(int,int);
int max(int i,int j){
	printf("�����ֵ��%d��%d",i,j);
	return i>j?i:j;
}