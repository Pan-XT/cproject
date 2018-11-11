#include "stdafx.h"
#include "SoundRecord.h"

void prepareWaveHdr(PWAVEHDR &hdr, PBYTE &buf)
{
	buf = (PBYTE)malloc(INP_BUFFER_SIZE);
	if (!buf)
	{
		free(buf);
		AfxMessageBox(_T("�ڴ����ʧ��"), MB_ICONINFORMATION | MB_OK, NULL);
	}
	hdr = new WAVEHDR;

	hdr->lpData = (char*)buf;
	hdr->dwBufferLength = INP_BUFFER_SIZE;
	hdr->dwBytesRecorded = 0;
	hdr->dwUser = 0;
	hdr->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	hdr->dwLoops = 1;
	hdr->lpNext = NULL;
	hdr->reserved = 0;
}

/**
¼���Ļص�����
*/
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2){
	CSoundRecord* r = (CSoundRecord*)dwInstance;
	WAVEHDR *wave = (WAVEHDR*)dwParam1;
	switch (uMsg)
	{
	case WIM_DATA:
		//��������
		if (r){
			if (wave->lpData)
			{
				r->saveSound(wave->lpData, wave->dwBytesRecorded);
			}
			if (wave->dwBytesRecorded){//=0ʱreset
			}
				r->beginRecord();
		}
		break;
	case WIM_CLOSE:
		AfxMessageBox(_T("close"));
		break;
	case WIM_OPEN:
		
		break;
	default:
		break;
	}
}
/*
���ŵĻص�����
*/
void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD dwParam1, DWORD dwParam2){
	switch (uMsg)
	{
	case WOM_OPEN:
		
		break;
	case WOM_DONE:
		break;
	case WOM_CLOSE:
		AfxMessageBox(_T("out close"));
		break;
	default:
		break;
	}
}

CSoundRecord::CSoundRecord()
{
	initAudio();
}


CSoundRecord::~CSoundRecord()
{
}

void CSoundRecord::beginRecord(){
	//׼��¼��������
	waveInAddBuffer(hWaveIn, pWaveHdrIn[nIn], sizeof(WAVEHDR));
	nIn = ++nIn%BUF_LEN;
	//��ʼ¼��
	waveInStart(hWaveIn);
}

void CSoundRecord::soundPlay()
{
	waveInStop(hWaveIn);
	waveInReset(hWaveIn);
	for (int i = 0; i < BUF_LEN; i++){
		waveInUnprepareHeader(hWaveIn, pWaveHdrIn[i], sizeof(WAVEHDR));
	}

	waveInClose(hWaveIn);
	//waveOutWrite(hWaveOut, pWaveHdrIn[0], sizeof(WAVEHDR));
}


UINT_PTR CSoundRecord::IfWaveIn()
{
	MMRESULT mmresult = 0;
	UINT_PTR   m_iWaveInID = -1;
	mmresult = waveInGetNumDevs();
	if (mmresult == 0) return false;

	WAVEINCAPS waveincaps = { 0 };
	unsigned int i = 0;
	unsigned int num = mmresult;
	for (; i < num; i++)
	{
		mmresult = waveInGetDevCaps(i, &waveincaps, sizeof(WAVEINCAPS));
		if (mmresult != MMSYSERR_NOERROR)
			return m_iWaveInID;
		if ((waveincaps.dwFormats & WAVE_FORMAT_1M08) == 0)
			continue;
		else
		{
			m_iWaveInID = i;
			return m_iWaveInID;
		}
	}

	return m_iWaveInID;
}

UINT_PTR CSoundRecord::IfWaveOut()
{
	MMRESULT mmresult = 0;
	UINT_PTR   m_iWaveInID = -1;
	mmresult = waveOutGetNumDevs();

	if (mmresult == 0) return false;

	WAVEOUTCAPS waveincaps = { 0 };
	unsigned int i = 0;
	unsigned int num = mmresult;
	for (; i < num; i++)
	{
		mmresult = waveOutGetDevCaps(i, &waveincaps, sizeof(WAVEOUTCAPS));
		if (mmresult != MMSYSERR_NOERROR)
			return m_iWaveInID;
		if ((waveincaps.dwFormats & WAVE_FORMAT_1M08) == 0)
			continue;
		else
		{
			m_iWaveInID = i;
			return m_iWaveInID;
		}
	}

	return m_iWaveInID;
}

void CSoundRecord::initAudio(){
	//������ʽ
	waveForm.wFormatTag = WAVE_FORMAT_PCM;
	//˫����
	waveForm.nChannels = 2;
	//������ 11.025 KHZ
	waveForm.nSamplesPerSec = 11025;
	//��С�鵥Ԫ, wBitsPerSamle x nChannels/8
	waveForm.nBlockAlign = 2;
	//������ 11.025 KB/s
	waveForm.nAvgBytesPerSec = 11025*2;// waveForm.nSamplesPerSec * waveForm.nBlockAlign;
	//������СΪ8bit
	waveForm.wBitsPerSample = 8;
	//���Ӹ�ʽ��Ϣ
	waveForm.cbSize = 0;

	//׼��pWaveHdrIn �� pWaveHdrOut
	for (int hdrNum = 0; hdrNum < BUF_LEN; hdrNum++)
	{
		prepareWaveHdr(pWaveHdrIn[hdrNum], pBufferIn[hdrNum]);
		prepareWaveHdr(pWaveHdrOut[hdrNum], pBufferOut[hdrNum]);
	}


	//�򿪲��Ų����豸
	MMRESULT result;
	UINT_PTR in = IfWaveIn();

	result = waveInOpen(&hWaveIn, in, &waveForm, (DWORD)waveInProc, (DWORD)this, CALLBACK_FUNCTION);

	if (result == MMSYSERR_NOERROR)
	{
		UINT_PTR out = IfWaveOut();
		result = waveOutOpen(&hWaveOut, out, &waveForm, (DWORD)waveOutProc, (DWORD)this, CALLBACK_FUNCTION);
	}
	//Ϊ���ź�¼��׼��
	for (int prepare = 0; prepare < BUF_LEN; prepare++)
	{
		if (result == MMSYSERR_NOERROR)
			result = waveOutPrepareHeader(hWaveOut, pWaveHdrOut[prepare], sizeof(WAVEHDR));
		if (result == MMSYSERR_NOERROR)
			result = waveInPrepareHeader(hWaveIn, pWaveHdrIn[prepare], sizeof(WAVEHDR));
	}
	//��������Ϊ���
	if (result == MMSYSERR_NOERROR)
	{
		result = waveOutSetVolume(hWaveOut, 65535);
	}
	if (result != MMSYSERR_NOERROR)
	{
		CString msg;
		msg.Format(_T("�򿪲����豸ʱ����,������[%d]"), result);
		AfxMessageBox(msg, MB_ICONINFORMATION | MB_OK, NULL);
	}
}
FILE* fp;
int a = fopen_s(&fp, "C:\\Users\\Public\\Desktop\\a.wav", "wb+");
BOOL init = FALSE;

void CSoundRecord::saveSound(LPSTR buf, int size){
	if (!init){
		/* Ĭ��wav��Ƶͷ������ */
		WAVEPCMHDR WavHeader =
		{
			{ 'R', 'I', 'F', 'F' },
			0,
			{ 'W', 'A', 'V', 'E' },
			{ 'f', 'm', 't', ' ' },
			sizeof(PCMWAVEFORMAT),
			WAVE_FORMAT_PCM,
			2,
			11025,
			11025 * (8 / 8),
			8 / 8,
			8,
			{ 'd', 'a', 't', 'a' },
			0
		};
		fwrite(&WavHeader, sizeof(WAVEPCMHDR), 1, fp);
		init = TRUE;
	}
	fseek(fp, 0, SEEK_SET);
	WAVEPCMHDR head;
	fread(&head, sizeof(head), 1, fp);
	head.data_size += size;
	fseek(fp, 0, SEEK_SET);
	fwrite(&head, sizeof(WAVEPCMHDR), 1, fp);
	fseek(fp, 0, SEEK_END);
	fwrite(buf, sizeof(unsigned char), size-1, fp);
	pWaveHdrOut[nIn-1]->lpData = buf;

	waveOutWrite(hWaveOut, pWaveHdrOut[nIn-1], sizeof(WAVEHDR));
}