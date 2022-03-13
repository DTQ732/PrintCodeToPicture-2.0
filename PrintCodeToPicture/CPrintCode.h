#pragma once

#include <easyx.h>			// 引用图形库头文件
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
// 打印类
class CPrintCode
{
public:
	CPrintCode();
	~CPrintCode();

	void setFontSize(int size);

	void setFilePath(const char* path);

	// 支持bmp / gif / jpg / png / tif
	int printCode(const char* format = "bmp");

private:
	// 加载文本
	int initText();

	// 清空text
	void resetText();

	// 将tab转换为空格
	int replaceTabToSpace(char* str, int maxLen);

	// 猜测编码
	void considerCharset();

	size_t UTF8ToGB2312(char* srcStr, char* desBuff, size_t desBuffLength);

	void initStyle();

private:
	const char* m_path;
	vector<char*> m_texts; // 要转换的文本
	LOGFONT m_font;
	int m_fontSize; // 字体大小
	int m_width; // 画布宽
	int m_height; // 高
	const char* m_charset; // 编码
	string m_message; // 提示信息
};

