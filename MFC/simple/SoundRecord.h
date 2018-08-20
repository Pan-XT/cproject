#pragma once
#define INP_BUFFER_SIZE 4096
#define BUF_LEN 5

static HWAVEIN hWaveIn;//¼���豸���
static HWAVEOUT hWaveOut;//�����豸���

class CSoundRecord
{
private:
	WAVEFORMATEX waveForm;//���ڴ���Ƶ�豸�Ľṹ

	PBYTE pBufferIn[BUF_LEN];//���ڽ��պͲ��ŵ����黺����
	PBYTE pBufferOut[BUF_LEN];//���ڷ��ͺ�¼��������������

	PWAVEHDR pWaveHdrIn[BUF_LEN];//����¼����pwavehdr�ṹ����
	PWAVEHDR pWaveHdrOut[BUF_LEN];//���ڲ��ŵĽṹ����

	char nIn = 0;
public:
	CSoundRecord();
	virtual ~CSoundRecord();
	void initAudio();
	void beginRecord();
	void soundPlay();
	void saveSound(LPSTR buf, int size);
	UINT_PTR IfWaveIn();
	UINT_PTR IfWaveOut();

};

/* wav��Ƶͷ����ʽ */
typedef struct WAVEPCMHDR
{
	char            riff[4];                    // = "RIFF"
	UINT32          size_8;                     // = FileSize - 8
	char            wave[4];                    // = "WAVE"
	char            fmt[4];                     // = "fmt "
	UINT32          fmt_size;                   // = PCMWAVEFORMAT�Ĵ�С : 
	//PCMWAVEFORMAT
	UINT16          format_tag;                 // = PCM : 1
	UINT16          channels;                   // = ͨ���� : 1
	UINT32          samples_per_sec;            // = ������ : 8000 | 6000 | 11025 | 16000
	UINT32          avg_bytes_per_sec;          // = ÿ��ƽ���ֽ��� : samples_per_sec * bits_per_sample / 8
	UINT16          block_align;                // = ÿ�������ֽ��� : wBitsPerSample / 8
	UINT16          bits_per_sample;            // = ��������: 8 | 16
	char            data[4];                    // = "data";
	//DATA
	UINT32          data_size;                  // = �����ݳ��� 
} WAVEPCMHDR;

/*
============mci����==============
//��������λ�
mciSendString ("set wave bitpersample 8", "", 0, 0);
//�������ò����ʣ�
mciSendString ("set wave samplespersec 16000", "", 0, 0);
//����������������
mciSendString ("set wave channels 1", "", 0, 0);
//��������WAVEPCM��
mciSendString ("set wave format tag pcm","", 0, 0);
//�������豸��
mciSendString ("open new type WAVEAudio alias WREC",0&,0,0); // �Ҽ��ܶ���дalias movie���������alias������
//������ʼ¼����
mciSendString ("record WREC",0&,0,0);
//����ֹͣ¼����
mciSendString ("stop WREC",0&,0,0);
//��������¼��
mciSendString ("save WREC C:\\test.wav",0&,0,0); // ����·��
//�����ر��豸��
mciSendString ("close WREC",0&,0,0);
*/