#include <WINSOCK2.H>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#define SIZE 1024*8
void main()
{
	//?????
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest=MAKEWORD(1,1);
	int err;
	err=WSAStartup(myVersionRequest,&wsaData);
	if (!err)
	{
		printf("�Ѵ��׽���!");
	} 
	else
	{
		//????????
		printf("�׽��ִ�ʧ��\n");
		return;
	}
	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//?????????
	//???????
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(6000);
	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));
	listen(serSocket,5);
	
	
	
	
	SOCKADDR_IN clientsocket;
	int len=sizeof(SOCKADDR);
	SOCKET serConn;
	char sendBuf[50];
	serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//??????accept??conection???????????
	sprintf(sendBuf,"welcome %s to bejing",inet_ntoa(clientsocket.sin_addr));//?????IP???????????
	//??????
	send(serConn,sendBuf,strlen(sendBuf)+1,0);
	
	FILE *fp;
lable1: printf("�ͻ����Ѵ�\n�������ļ���ŵ�ַ:\n");
		char path[100]={"0"};
		int i=0;
		while(path[i]!='\0')
		{
			if(path[i]=='/')
				path[i]='\\';
			i++;
		}
		gets(path);
		if((fp=fopen(path,"wb"))==NULL)
		{
			printf("�ļ�δ��\n");
			goto lable1;
		}
		else
		{
			printf("�ļ��Ѵ� ��ʼ�ļ�����......\n");
			//??????
			send(serConn,"��ʼ����",strlen("��ʼ����")+1,0); 
			//??????
			char datalength[20];
			long int length=0;
			recv(serConn,datalength,21,0);
			length=atol(datalength);
			printf("�õ��ļ���С: %d\n",length);
			//????
			double cent=0.0;
			char receiveBuf[SIZE];
			long int x=0;
			while (1)
			{
				x=x+SIZE;
				if(x<length)
				{
					cent=(double)x*100.0/(double)length;
					printf("�ѽ���: %4.2f%\n",cent);
					recv(serConn,receiveBuf,SIZE+1,0);
					fwrite(receiveBuf,1,SIZE,fp);
				}
				else
				{
					recv(serConn,receiveBuf,length+SIZE-x+1,0);
					printf("�ļ��������\n");
					fwrite(receiveBuf,1,length+SIZE-x,fp);
					fclose(fp);
					break;
				}
			}
		}
		closesocket(serConn);//??
		WSACleanup();//???????
		system("pause");
		
}