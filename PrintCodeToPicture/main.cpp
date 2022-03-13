#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <string>
#include <locale.h>
#include <fstream>
#include <graphics.h>
#include <Windows.h>

#include "CPrintCode.h"

#define DEBUG
#define TEST_PRINT

using namespace std;

#ifdef TEST_PRINT
int main(int argc, char** argv)
{
	const char* default_path = "D:\\work\\vs2019_project\\PrintCodeToPicture\\Debug\\gbk.c";
	const char* file_path = default_path;
	if (argc > 1)
	{
		file_path = argv[1];
	}
	CPrintCode printCode;
	printCode.setFilePath(file_path);
	printCode.printCode();
}

#else
int UTF8ToGB2312(char* srcStr, char* desBuff, size_t desBuffLength);
void s_setFont(LOGFONT& lf);
void s_initEnv();
int InsertTab(char* str);

#ifdef DEBUG
int width = 500, height = 500;
#else
int width = 2000, height = 4000;
#endif
int lineHeight = 20;

int main(int argc, char** argv)
{
	const char* default_path = "D:\\work\\vs2019_project\\PrintCodeToPicture\\Debug\\utf-8.c";
	const char* file_path = default_path;
	if (argc > 1)
	{
		file_path = argv[1];
	}
	char buff[10240];
	ifstream ifs;
	//open 前不能调用本地化 UTF-8，因为系统传入得参数是Unicode，一转UTF-8得话open时
	//就会把这个参数认为是UTF-8的编码。
	//ifstream 在打开文件时是默认把char* 在内部转换成 宽字符。
	ifs.open(file_path);
	// setlocale(LC_ALL, "zh_CN.UTF-8");
	// int c = GetLastError();

	if (!ifs.is_open()) {
		MessageBoxA(NULL, "请检查是否有权限", "打开失败", MB_OK);
		exit(EXIT_FAILURE);
	}
	int line = 0;
	int maxLength = 0;

	while (!ifs.eof()) {
		ifs.getline(buff, 10239);
		if (!ifs) break;
		line++;
		sprintf(buff, "%s", buff);
		printf("%s", buff);
		ifs.gcount() > maxLength ? maxLength = ifs.gcount() : 0;
	}
	width = maxLength * 10;
	height = line * 20 + 100;

	s_initEnv();
	int _height = textheight("123");
	int _width = textwidth("123");
	outtextxy(20, 20, file_path);
	ifs.seekg(ios::beg);
	// setlocale(LC_ALL, "C");
	int i = 1;
	while (i <= line)
	{
		ifs.getline(buff, 1023);
		char desbuff[1024] = { 0 };
		desbuff[UTF8ToGB2312(buff, desbuff, 1023) - 3] = '0';

		InsertTab(desbuff);

		outtextxy(20, (i + 1) * 20, desbuff);

		/*RECT rect;
		rect.left = 20;
		rect.right = 20 + textwidth(buff);
		rect.top = (i + 1) * 20;
		rect.bottom = rect.top + 20;
		drawtext(desbuff, &rect, DT_LEFT);*/
		i++;
	}
	saveimage("save.png");
	char ch = _getch();
	ch = _getch();
	closegraph();
}

void s_setFont(LOGFONT& lf) {
	printf("%d", lf.lfWidth);
	lf.lfHeight = 20;
	lf.lfWeight = FW_MEDIUM;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;
	strcpy(lf.lfFaceName, "Monaco");
}

void s_initEnv() {
	initgraph(width, height, SHOWCONSOLE);

	setbkcolor(RGB(0xee, 0xee, 0xee));
	settextcolor(RGB(0xff, 0x40, 0x40));
	setbkmode(TRANSPARENT);
	LOGFONT lf;
	char buff[128];
	gettextstyle(&lf);
	s_setFont(lf);
	settextstyle(&lf);
	cleardevice();
}

int UTF8ToGB2312(char* srcStr, char* desBuff, size_t desBuffLength)
{
	size_t iLen = strlen(srcStr);
	iconv_t cd;
	cd = iconv_open("gb2312", "utf-8");
	if (cd == 0)
	{
		return -1;
	}
	iconv(cd, &srcStr, &iLen, &desBuff, &desBuffLength);
	iconv_close(cd);
	return desBuffLength;
}

/*把tab转换成四个空格*/
// "\tabc" --> "    abc"
int InsertTab(char* str) {
	int tab = 0; int t = 0;
	for (int j = 0; j < strlen(str); j++) {
		if (str[j] == '\t') {
			t = strlen(str);
			while (--t != j) str[t + 3] = str[t];
			t = j + 4;
			while (j < t) str[j++] = ' ';
			tab++;
		}
	}
	return tab;
}

#endif