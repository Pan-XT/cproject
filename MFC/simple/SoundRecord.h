#pragma once
#define INP_BUFFER_SIZE 4096

static HWAVEIN hWaveIn;//¼���豸���
static HWAVEOUT hWaveOut;//�����豸���

class CSoundRecord
{
private:
	HWND hwnd;
	WAVEFORMATEX waveForm;//���ڴ���Ƶ�豸�Ľṹ

	PBYTE pBufferIn[2];//���ڽ��պͲ��ŵ����黺����
	PBYTE pBufferOut[2];//���ڷ��ͺ�¼��������������

	PWAVEHDR pWaveHdrIn[2];//����¼����pwavehdr�ṹ����
	PWAVEHDR pWaveHdrOut[2];//���ڲ��ŵĽṹ����

public:
	CSoundRecord(HWND hwnd);
	virtual ~CSoundRecord();
	void beginRecord();
	void soundPlay();
	UINT_PTR IfWaveIn();
	UINT_PTR IfWaveOut();
	
};

