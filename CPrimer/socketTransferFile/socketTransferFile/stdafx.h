// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <string>
#include <tchar.h>
#include <Windows.h>

struct FileTime
{
	FILETIME createTime, accessTime, writeTime;
	unsigned    attrib;
	_fsize_t    size;
};



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
