﻿/*******************************************************
	文件名：Minesweeeper.cpp
	功能：存放主函数
	版本：1.2(22.05.29)
	作者：石皮幼鸟
	版本说明：修复了主菜单可能变色的bug

	版本日志：
		1.0(22.05.28) 创建主函数
		1.1(22.05.28) 无
		1.2(22.05.29) 无
*******************************************************/


#include "index.h"

int main()
{
	creatWindow();
	int language = selectLanguage();
	menu(language);
}