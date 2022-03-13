# PrintCodeToPicture-2.0
 打印文本到图片上2.0版本

## 写在前面
编译器为VS2019,暂时没有找到libiconv的VS2019版本，所以使用时需要将 SDK设置为14.1开头的那个平台，然后设置工具V141

目前还未将项目完全配置正确，下次提交将完善代码，提高程序可靠性，提供cmake工具

## 示例 example
```C++
#include "CPrintCode.h"

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
```