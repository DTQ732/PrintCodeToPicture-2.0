#include "CPrintCode.h"

CPrintCode::CPrintCode()
{
#ifdef _DEBUG
	initgraph(800, 800, EW_SHOWCONSOLE);
#else
	initgraph(800, 800);
#endif // _DEBUG
	initStyle();
	m_path = NULL;
	m_fontSize = 20;
	m_width = 0;
	m_height = 0;
	m_charset = NULL;
}

CPrintCode::~CPrintCode()
{
	resetText();
}

void CPrintCode::setFontSize(int size)
{
	m_fontSize = size;
}

void CPrintCode::setFilePath(const char* path)
{
	m_path = path;
}

int CPrintCode::initText()
{
	resetText();
	std::ifstream ifs(m_path);
	char* loc = setlocale(LC_ALL, "zh_CN.UTF-8");
	char buff[4096] = { 0 };
	char* temp = NULL;
	while (!ifs.eof()) 
	{
		ifs.getline(buff, 4096);
		if (!ifs) break;
		if (strlen(buff) > 1024)
		{
			// 后续再考虑换行的问题
			MessageBoxA(NULL, "单行文字过长，超过1024字节", "错误", MB_OK);
			return -1;
		}
		replaceTabToSpace(buff, 2048);
		int len = strlen(buff);
		temp = new char[len + 1];
		memcpy(temp, buff, len);
		temp[len] = 0;
		m_texts.push_back(temp);
	}
	considerCharset();
	// 无需转码
	if ((m_charset[0] == 'G' && m_charset[1] == 'B') || (m_charset[0] == 'g' && m_charset[1] == 'b'))
	{
		return 1;
	}
	vector<char*> texts;

	for (size_t i = 0, size = m_texts.size(); i < size; ++i)
	{
		memset(buff, 0, 4096);
		size_t dstSize = UTF8ToGB2312(m_texts[i], buff, 4096);
		if (dstSize < 0)
		{
			throw std::exception("转换文本失败");
		}
		buff[dstSize] = '\0';
		temp = new char[dstSize + 1];
		memcpy_s(temp, dstSize + 1, buff, dstSize + 1);
		texts.push_back(temp);
	}
	resetText();
	m_texts = texts;
}

void CPrintCode::resetText()
{
	for (size_t i = 0, size = m_texts.size(); i < size; ++i)
	{
		if (m_texts[i] != NULL)
		{
			delete[] m_texts[i];
		}
	}
	m_texts.clear();
}

int CPrintCode::printCode(const char* format)
{
	initText();
	m_height = (m_texts.size() + 5) * m_font.lfHeight;
	int width = 0;
	for (char* p : m_texts)
	{
		width = textwidth(p);
		if (width > m_width)
		{
			m_width = width;
		}
	}
	m_width += 3 * m_font.lfHeight;
	initgraph(m_width, m_height);
	initStyle();

	// 打印文件路径
	int x = m_font.lfHeight, y = m_font.lfHeight;
	outtextxy(x, y, m_path);
	y += m_font.lfHeight;
	outtextxy(x, y, m_charset);
	y += m_font.lfHeight;
	for (char* p : m_texts)
	{
		outtextxy(x, y, p);
		y += m_font.lfHeight;
	}
	string img_path = "D:\\work\\vs2019_project\\PrintCodeToPicture\\Debug\\";
	img_path += string(m_charset);
	img_path += string(".") + string(format);
	saveimage(img_path.c_str());
	return 1;
}

int CPrintCode::replaceTabToSpace(char* str, int maxLen)
{
	char* tstr = str;
	int n = 0;
	int realLen = strnlen_s(str, maxLen);
	if (realLen == maxLen)
	{
		return 0;
	}
	while (*tstr++ == '\t') ++n;
	// 小于最大长度
	if (n > 0 && realLen + n * 4 < maxLen)
	{
		memcpy_s(str + n * 4, maxLen - n * 4, str + n, realLen - n + 1);
		memset(str, ' ', n * 4);
		return n;
	}
	return 0;
}

void CPrintCode::considerCharset()
{
	csd_t csd = csd_open();  // 首先开启一个探测器
	if (csd == (csd_t)-1) {
		printf("csd_open failed\n");
		return;
	}
	string strs = "";
	// 猜测编码，需要足够多的字符，否则容易一次性结束判断
	for (size_t i = 0, size = m_texts.size(); i < size && strs.length() < 10000; ++i)
	{
		strs += string(m_texts[i]);
	}

	int result = csd_consider(csd, strs.c_str(), strs.length());
	if (result < 0) {
		printf("csd_consider failed\n");
		csd_close(csd);
		return;
	}
	else if (result > 0) {
		// Already have enough data
		m_charset = csd_close(csd);
	}
	else
	{
		m_charset = csd_close(csd);
		m_message += string("无法确信得到了正确转换，请使用GBK编码");
	}
}

size_t CPrintCode::UTF8ToGB2312(char* srcStr, char* desBuff, size_t desBuffLength)
{
	size_t iLen = strlen(srcStr), oriDestSize = desBuffLength;
	iconv_t cd;
	cd = iconv_open("gb2312", "utf-8");
	if (cd == 0)
	{
		return -1;
	}
	iconv(cd, &srcStr, &iLen, &desBuff, &desBuffLength);
	iconv_close(cd);
	return oriDestSize - desBuffLength;
}

void CPrintCode::initStyle()
{
	gettextstyle(&m_font);
	m_font.lfHeight = m_fontSize;
	m_font.lfWidth = 0;
	m_font.lfWeight = FW_MEDIUM;
	m_font.lfOutPrecision = OUT_TT_PRECIS;
	m_font.lfQuality = PROOF_QUALITY;
	m_font.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;
	strcpy(m_font.lfFaceName, "Monaco");
	setbkcolor(RGB(0xee, 0xee, 0xee));
	settextcolor(RGB(0xff, 0x40, 0x40));
	setbkmode(TRANSPARENT);
	settextstyle(&m_font);
	cleardevice();
}
