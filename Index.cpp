/*******************************************************
	文件名：Index.cpp
	功能：存放可视化相关方式
	版本：1.2(22.05.29)
	作者：石皮幼鸟
	版本说明：无

	版本日志：
		1.0(22.05.28) 完成创建窗口和矩形绘制方式
		1.1(22.05.28) 完成了判定鼠标点击区域的方式
		1.2(22.05.29) 无
*******************************************************/


#include "index.h"



/*******************************************************
	方式名：void creatWindow()
	功能：游戏开启时创建一个窗口
	参数：无
	返回：无
*******************************************************/
void creatWindow() {
	initgraph(1280, 720);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	settextstyle(150,0,"微软雅黑");
	outtextxy(525,200,"扫雷");
	settextstyle(80, 0, "微软雅黑");
	outtextxy(455, 400, "石皮幼鸟制作");
	Sleep(3000);
	cleardevice();
}

/*******************************************************
	方式名：void creatRect(int x, int y, int height, int width, COLORREF color)
	功能：在背景中创建一个矩形
	参数：x,y为矩形起点（左上角）绝对坐标（底层图形坐标会移动到这里)，height和width为高和宽,color为线条颜色
	返回：无
*******************************************************/
void creatRect(int x, int y, int height, int width, COLORREF color) {
	moveto(x, y);
	setlinecolor(color);
	linerel(width, 0);
	linerel(0, height);
	linerel(-width, 0);
	linerel(0, -height);
}

/*******************************************************
	方式名：bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax)
	功能：对鼠标点击区域（矩形）进行判定
	参数：x,y为光标绝对坐标，xMin/Max以及yMin/Max分别为x，y的最小/最大绝对坐标
	返回：不在该区域返回0，反之返回1
*******************************************************/
bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax) {
	if (xMin <= x && x <= xMax && y <= yMax && y >= yMin) return 1;
	else return 0;
}