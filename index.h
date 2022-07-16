/*******************************************************
	文件名：index.h
	功能：存放方式声明、全局变量、头文件引入等
	版本：2.0(22.07.17)
	作者：石皮幼鸟
	版本说明：无

	版本日志：
		1.0(22.05.28) 完成所有函数的声明以及全局变量的创建
		1.1(22.05.28) 无
		1.2(22.05.29) 对头文件声明分类注释
		1.3(22.05.31) 无
		2.0(22.07.17) 无
*******************************************************/


#pragma once
#ifndef index_h
#define index_h
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <string.h>
#include <graphics.h>
#include <time.h>

typedef struct PLAYER
{
	char cName[21];				//玩家名
	int Score;								//分数
	struct PLAYER* next;		//链表指针
}player; //排行榜数组

typedef struct INF {
	char cnInf[9][30];		//中文
	char enInf[9][30];	//英文
	char jpInf[9][30];		//日文
}inf; //菜单界面文字

typedef struct CUBE {
	int type;        //方块种类，0是雷，1是空
	int num;        //周围的雷数(不含自身)
	int recent;    //目前状况，0是未触发，1是已触发
	int mark;		 //是否被标记，0是未被标记，1是被标记
}cube;	//方块信息结构体

typedef struct CUBEXY {
	int uMsg;				//当前鼠标消息, 0是左键，1是右键
	int x;						//横坐标
	int y;						//列坐标
}cubeXY;  //鼠标触发的方块坐标



/*主菜单模块相关方式*/
int selectLanguage();																										//选择语言界面，返回
void loadMenu(FILE* menu2, inf* infs);																		//读取菜单文本，传入文件指针和存放文本的数组
void menu(int language);																								//显示主菜单，传入语言编号
void showTutorial(int language);																					//显示新手教程，传入语言编号

/*底层可视化相关方式*/
bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax);		//检测鼠标
void creatWindow();																											//创建窗口（默认1280*720）
void creatRect(int x, int y, int height, int width, COLORREF color);				//绘制一个空心矩形，输入起始坐标，高和宽，以及矩形的颜色

/*游戏模块相关方式*/
void creatMine(cube(*cubes)[], int num);																	//创建方块数组，传入方块结构体行指针和一条边上的方块数
int creatGame(int num);																									//创建关卡，传入一条边上的方块数，返回最终分数
void drawMap(cube(*cubes)[], int num);																	//关卡可视化，传入方块结构体行指针和一条边上的方块数
void tapCheck(int num, cubeXY* tap);																		//识别鼠标触发的方块坐标，传入一条边上的方块数和方块坐标指针
void emptyCube(cube(*cubes)[], int num, int x, int y, int* recent);				
																							//触发数字为0的空白方块以及周边空白方块，传入方块行指针，单边方块数，方块坐标和目前剩余未触发方块

/*排行榜模块相关方式*/
void setRank(int num, int score, int language);														//写入排行榜数据，传入单边方块数（代表难度），玩家分数和语言编号
player* getRank();																												//获取排行榜数据，返回排行榜链表头指针
void rank(int language);																									//排行榜总函数，创建数组获取链表信息，传入语言编号
void showEasy(player* rank, int language);															//显示简单难度排行榜，传入排行榜数组和语言编号
void showHard(player* rank, int language);															//显示困难难度排行榜，传入排行榜数组和语言编号


#endif