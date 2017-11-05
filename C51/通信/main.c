#include "reg51.h"

typedef unsigned int u16;
typedef unsigned char u8;

void usartInit(){
	TMOD|=0x20;
	TH1=0xF3;//��������ʼֵ��������4800
	TL1=0xF3;
	PCON=0x80;//��Ƶ
	TR1=1;
	SCON=0x50;
	ES=1;//�����ж�
	EA=1;
}				
void main(){
	usartInit();
	while(1);
}	  
void usart() interrupt 4{
	u8 receiveData;
	receiveData=SBUF;
	RI=0;
	SBUF=receiveData;
	while(!TI);
	TI=0;
}