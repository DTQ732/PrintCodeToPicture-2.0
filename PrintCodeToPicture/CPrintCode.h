#pragma once

#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <string>
#include <locale.h>
#include <fstream>
#include <vector>
#include <graphics.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "iconv.h"
#include "charsetdetect.h"

#pragma comment(lib,"libiconv.lib")
#ifdef _DEBUG
#pragma comment(lib,"charsetdetect_d.lib")
#else
#pragma comment(lib,"charsetdetect.lib")
#endif // _DEBUG



using namespace std;
// ��ӡ��
class CPrintCode
{
public:
	CPrintCode();
	~CPrintCode();

	void setFontSize(int size);

	void setFilePath(const char* path);

	// ֧��bmp / gif / jpg / png / tif
	int printCode(const char* format = "bmp");

private:
	// �����ı�
	int initText();

	// ���text
	void resetText();

	// ��tabת��Ϊ�ո�
	int replaceTabToSpace(char* str, int maxLen);

	// �²����
	void considerCharset();

	size_t UTF8ToGB2312(char* srcStr, char* desBuff, size_t desBuffLength);

	void initStyle();

private:
	const char* m_path;
	vector<char*> m_texts; // Ҫת�����ı�
	LOGFONT m_font;
	int m_fontSize; // �����С
	int m_width; // ������
	int m_height; // ��
	const char* m_charset; // ����
	string m_message; // ��ʾ��Ϣ
};

