/*******************************************************
	�ļ�����Index.cpp
	���ܣ���ſ��ӻ���ط�ʽ
	�汾��1.2(22.05.29)
	���ߣ�ʯƤ����
	�汾˵������

	�汾��־��
		1.0(22.05.28) ��ɴ������ں;��λ��Ʒ�ʽ
		1.1(22.05.28) ������ж����������ķ�ʽ
		1.2(22.05.29) ��
*******************************************************/


#include "index.h"



/*******************************************************
	��ʽ����void creatWindow()
	���ܣ���Ϸ����ʱ����һ������
	��������
	���أ���
*******************************************************/
void creatWindow() {
	initgraph(1280, 720);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	settextstyle(150,0,"΢���ź�");
	outtextxy(525,200,"ɨ��");
	settextstyle(80, 0, "΢���ź�");
	outtextxy(455, 400, "ʯƤ��������");
	Sleep(3000);
	cleardevice();
}

/*******************************************************
	��ʽ����void creatRect(int x, int y, int height, int width, COLORREF color)
	���ܣ��ڱ����д���һ������
	������x,yΪ������㣨���Ͻǣ��������꣨�ײ�ͼ��������ƶ�������)��height��widthΪ�ߺͿ�,colorΪ������ɫ
	���أ���
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
	��ʽ����bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax)
	���ܣ�����������򣨾��Σ������ж�
	������x,yΪ���������꣬xMin/Max�Լ�yMin/Max�ֱ�Ϊx��y����С/����������
	���أ����ڸ����򷵻�0����֮����1
*******************************************************/
bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax) {
	if (xMin <= x && x <= xMax && y <= yMax && y >= yMin) return 1;
	else return 0;
}