#ifndef SNIFFER_HEADER
#define SNIFFER_HEADER

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

// Standard TCP flags 
#define URG 0x20 
#define ACK 0x10 
#define PSH 0x08 
#define RST 0x04 
#define SYN 0x02 
#define FIN 0x01 
typedef struct _iphdr //����IP�ײ� 
{ 
	unsigned char h_lenver; //4λ�ײ�����+4λIP�汾�� 
	unsigned char tos; //8λ��������TOS 
	unsigned short total_len; //16λ�ܳ��ȣ��ֽڣ� 
	unsigned short ident; //16λ��ʶ 
	unsigned short frag_and_flags; //3λ��־λ 
	unsigned char ttl; //8λ����ʱ�� TTL 
	unsigned char proto; //8λЭ�� (TCP, UDP ������) 
	unsigned short checksum; //16λIP�ײ�У��� 
	unsigned int sourceIP; //32λԴIP��ַ 
	unsigned int destIP; //32λĿ��IP��ַ 
}IP_HEADER; 

typedef struct psd_hdr //����TCPα�ײ� 
{ 
	unsigned long saddr; //Դ��ַ 
	unsigned long daddr; //Ŀ�ĵ�ַ 
	char mbz; 
	char ptcl; //Э������ 
	unsigned short tcpl; //TCP���� 
}PSD_HEADER; 

typedef struct _tcphdr //����TCP�ײ� 
{ 
	USHORT th_sport; //16λԴ�˿� 
	USHORT th_dport; //16λĿ�Ķ˿� 
	unsigned int th_seq; //32λ���к� 
	unsigned int th_ack; //32λȷ�Ϻ� 
	unsigned char th_lenres;   //4λ�ײ�����/6λ������ 
	unsigned char th_flag; //6λ��־λ 
	USHORT th_win; //16λ���ڴ�С 
	USHORT th_sum; //16λУ��� 
	USHORT th_urp; //16λ��������ƫ���� 
}TCP_HEADER; 

//TCPα�ײ��������������ڵģ�ֻ�����ڼ������͡�У��ͺ����� 

USHORT checksum(USHORT *buffer, int size) 
{ 
	unsigned long cksum=0; 
	while (size > 1) 
	{ 
		cksum += *buffer++; 
		size -= sizeof(USHORT);   
	} 
	if (size) 
	{ 
		cksum += *(UCHAR*)buffer;   
	} 
	cksum = (cksum >> 16) + (cksum & 0xffff); 
	cksum += (cksum >>16); 
	return (USHORT)(~cksum); 
} 


#endif