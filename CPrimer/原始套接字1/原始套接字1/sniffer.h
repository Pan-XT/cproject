// ͷ�ļ�

#ifndef RAW_DEF_H
#define RAW_DEF_H

#include <winsock2.h> 
#pragma comment(lib,"ws2_32")

#include <ws2tcpip.h>
#include <mstcpip.h> // ���ļ��� Windows platform SDK �ĺ���������Ҳ������밲װSDK
#include <afx.h>
#include <iostream>

#define PROTOCOL_STRING_ICMP_TXT "ICMP"
#define PROTOCOL_STRING_TCP_TXT "TCP"
#define PROTOCOL_STRING_UDP_TXT "UDP"
#define PROTOCOL_STRING_SPX_TXT "SPX"
#define PROTOCOL_STRING_NCP_TXT "NCP"
#define PROTOCOL_STRING_UNKNOW_TXT "UNKNOW"

// ����IP�ײ� 
typedef struct ip_hdr 
{ 
 unsigned char h_verlen;   // 4λ�ײ�����,4λIP�汾�� 
 unsigned char tos;    // 8λ��������TOS 
 unsigned short total_len;       // 16λ�ܳ��ȣ��ֽڣ� 
 unsigned short ident;      // 16λ��ʶ 
 unsigned short frag_and_flags;  // 3λ��־λ 
 unsigned char ttl;       // 8λ����ʱ�� TTL 
 unsigned char proto;      // 8λЭ�� (TCP, UDP ������) 
 unsigned short checksum;  // 16λIP�ײ�У��� 
 unsigned int sourceIP;   // 32λԴIP��ַ 
 unsigned int destIP;   // 32λĿ��IP��ַ 
}IPHEADER;

// ����TCPα�ײ� 
typedef struct tsd_hdr 
{ 
 unsigned long saddr;    // Դ��ַ 
 unsigned long daddr;    // Ŀ�ĵ�ַ 
 char mbz;                        // 0
 char ptcl;       // Э������ UDP��Э������Ϊ17��TCPΪ6 
 unsigned short tcpl;    // TCP���ݰ����� 
}PSDHEADER;

// ����TCP�ײ� 
typedef struct tcp_hdr 
{ 
 USHORT th_sport;     // 16λԴ�˿� 
 USHORT th_dport;     // 16λĿ�Ķ˿� 
 unsigned int th_seq;    // 32λ���к� 
 unsigned int th_ack;    // 32λȷ�Ϻ� 
 unsigned char th_lenres;   // 4λ�ײ�����/6λ������ 
 unsigned char th_flag;    // 6λ��־λ 
 USHORT th_win;      // 16λ���ڴ�С 
 USHORT th_sum;      // 16λУ��� 
 USHORT th_urp;      // 16λ��������ƫ���� 
}TCPHEADER;

// ����ICMP�ײ�
typedef struct icmp_hdr
{
 unsigned char  i_type;           // ����
 unsigned char  i_code;           // ����
 unsigned short i_cksum;          // У����
 unsigned short i_id;             // �Ǳ�׼��ICMP�ײ�  
 unsigned short i_seq;
 unsigned long  timestamp;
}ICMPHEADER;

// ����UDP�ײ�
// The UDP packet is lick this. Took from RFC768.
//                  0      7 8     15 16    23 24    31  
//                 +--------+--------+--------+--------+ 
//                 |     Source      |   Destination   | 
//                 |      Port       |      Port       | 
//                 +--------+--------+--------+--------+ 
//                 |                 |                 | 
//                 |     Length      |    Checksum     | 
//                 +--------+--------+--------+--------+ 
//                 |                                     
//                 |          data octets ...            
//                 +---------------- ...      

typedef struct udp_hdr  // 8 Bytes
{
 unsigned short uh_sport;         
 unsigned short uh_dport;
 unsigned short uh_len;
 unsigned short uh_sum;
} UDPHEADER;


/* 
// ����ʵ�ֲ�Ҫ����ͷ�ļ�������ᵼ���ڲ�ͬ�ĵط��ظ�����
//CheckSum:����У��͵��Ӻ��� 
USHORT checksum(USHORT *buffer, int size) 
{ 
 unsigned long cksum=0; 
 while(size >1) 
 { 
  cksum+=*buffer++; 
  size -=sizeof(USHORT); 
 } 
 if(size ) 
 { 
  cksum += *(UCHAR*)buffer; 
 } 
 
 cksum = (cksum >> 16) + (cksum & 0xffff); 
 cksum += (cksum >>16); 
 return (USHORT)(~cksum); 
}
*/

USHORT checksum(USHORT *buffer, int size);


// �ص�����

// ץ��һ�����ͻ��������ص�����
typedef int (CALLBACK *CaptureDef)(CString  &strMsg);

class YRawSniffer
{
public:
 YRawSniffer();
 ~YRawSniffer();
 BOOL StartAll();
 BOOL ExitAll();
 BOOL Capture(CaptureDef CaptureFunc = NULL);
 BOOL StopCapture();

 static DWORD WINAPI CaptureThread(LPVOID lpParam);
 HANDLE m_hCaptureThread;

 // Filter ��������
 BOOL m_bCapTCP;
 BOOL m_bCapUDP;
 BOOL m_bCapICMP;
 CString m_strSrcIP;
 CString m_strDstIP;
 
 SOCKET m_rawSock;
// CString m_strFilePath;

private:
 CaptureDef m_CaptureFunc;
 BOOL m_bExitCapture;
 
 IPHEADER m_ipHeader; 
 TCPHEADER m_tcpHeader;
 ICMPHEADER m_icmpheader;
 UDPHEADER m_udpheader;
};

#endif

