#include "stdafx.h"
#include "SoundRecord.h"


CSoundRecord::CSoundRecord(HWND hwnd) :hwnd(hwnd)
{
	//������ʽ
	waveForm.wFormatTag = WAVE_FORMAT_PCM;
	//˫����
	waveForm.nChannels = 2;
	//������ 11.025 KHZ
	waveForm.nSamplesPerSec = 11025;
	//��С�鵥Ԫ, wBitsPerSamle x nChannels/8
	waveForm.nBlockAlign = 2;
	//������ 11.025 KB/s
	waveForm.nAvgBytesPerSec = 11025;// waveForm.nSamplesPerSec * waveForm.nBlockAlign;
	//������СΪ8bit
	waveForm.wBitsPerSample = 8;
	//���Ӹ�ʽ��Ϣ
	waveForm.cbSize = 0;

	//׼��pWaveHdrIn �� pWaveHdrOut
	for (int hdrNum = 0; hdrNum < 2; hdrNum++)
	{
		//Ϊ�����������ڴ�
		pBufferIn[hdrNum] = (PBYTE)malloc(INP_BUFFER_SIZE);
		pBufferOut[hdrNum] = (PBYTE)malloc(INP_BUFFER_SIZE);
		if (!pBufferIn[hdrNum] || !pBufferOut[hdrNum])
		{
			if (pBufferIn[hdrNum])
				free(pBufferIn[hdrNum]);
			if (pBufferOut[hdrNum])
				free(pBufferOut[hdrNum]);
			AfxMessageBox(_T("�ڴ����ʧ��"), MB_ICONINFORMATION | MB_OK, NULL);
		}
		pWaveHdrIn[hdrNum] = new WAVEHDR;
		pWaveHdrOut[hdrNum] = new WAVEHDR;

		pWaveHdrOut[hdrNum]->lpData = (char*)pBufferIn[hdrNum];
		pWaveHdrOut[hdrNum]->dwBufferLength = INP_BUFFER_SIZE;
		pWaveHdrOut[hdrNum]->dwBytesRecorded = 0;
		pWaveHdrOut[hdrNum]->dwUser = 0;
		pWaveHdrOut[hdrNum]->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		pWaveHdrOut[hdrNum]->dwLoops = 1;
		pWaveHdrOut[hdrNum]->lpNext = NULL;
		pWaveHdrOut[hdrNum]->reserved = 0;

		pWaveHdrIn[hdrNum]->lpData = (char*)pBufferOut[hdrNum];
		pWaveHdrIn[hdrNum]->dwBufferLength = INP_BUFFER_SIZE;
		pWaveHdrIn[hdrNum]->dwBytesRecorded = 0;
		pWaveHdrIn[hdrNum]->dwUser = 0;
		pWaveHdrIn[hdrNum]->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		pWaveHdrIn[hdrNum]->dwLoops = 1;
		pWaveHdrIn[hdrNum]->lpNext = NULL;
		pWaveHdrIn[hdrNum]->reserved = 0;

	}

	
	//�򿪲��Ų����豸
	MMRESULT result;
	UINT_PTR in=IfWaveIn();
	
	result = waveInOpen(&hWaveIn, in, &waveForm, (DWORD)hwnd, 0, CALLBACK_WINDOW);
	
	if (result == MMSYSERR_NOERROR)
	{
		UINT_PTR out = IfWaveOut();
		result = waveOutOpen(&hWaveOut, out, &waveForm, (DWORD)hwnd, 0, CALLBACK_WINDOW);
	}
	//Ϊ���ź�¼��׼��
	for (int prepare = 0; prepare <= 1; prepare++)
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


CSoundRecord::~CSoundRecord()
{
}

void CSoundRecord::beginRecord(){
	//׼��¼��������
	waveInAddBuffer(hWaveIn, pWaveHdrIn[0], sizeof(WAVEHDR));
	waveInReset(hWaveIn);
	//��ʼ¼��
	waveInStart(hWaveIn);
}

void CSoundRecord::soundPlay()
{
	waveOutWrite(hWaveOut, pWaveHdrIn[0], sizeof(WAVEHDR));
}


UINT_PTR CSoundRecord::IfWaveIn()
{
	MMRESULT mmresult = 0;
	UINT_PTR   m_iWaveInID=-1;
	mmresult = waveInGetNumDevs();
	if (mmresult == 0) return false;

	WAVEINCAPS waveincaps = { 0 };
	unsigned int i = 0;
	unsigned int num = mmresult;
	for (; i<num; i++)
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
	for (; i<num; i++)
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