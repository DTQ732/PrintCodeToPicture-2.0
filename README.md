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

# LICENSE
MIT License

Copyright (c) 2022 DTQ732

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
