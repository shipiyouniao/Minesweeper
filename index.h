/*******************************************************
	�ļ�����index.h
	���ܣ���ŷ�ʽ������ȫ�ֱ�����ͷ�ļ������
	�汾��2.0(22.07.17)
	���ߣ�ʯƤ����
	�汾˵������

	�汾��־��
		1.0(22.05.28) ������к����������Լ�ȫ�ֱ����Ĵ���
		1.1(22.05.28) ��
		1.2(22.05.29) ��ͷ�ļ���������ע��
		1.3(22.05.31) ��
		2.0(22.07.17) ��
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
	char cName[21];				//�����
	int Score;								//����
	struct PLAYER* next;		//����ָ��
}player; //���а�����

typedef struct INF {
	char cnInf[9][30];		//����
	char enInf[9][30];	//Ӣ��
	char jpInf[9][30];		//����
}inf; //�˵���������

typedef struct CUBE {
	int type;        //�������࣬0���ף�1�ǿ�
	int num;        //��Χ������(��������)
	int recent;    //Ŀǰ״����0��δ������1���Ѵ���
	int mark;		 //�Ƿ񱻱�ǣ�0��δ����ǣ�1�Ǳ����
}cube;	//������Ϣ�ṹ��

typedef struct CUBEXY {
	int uMsg;				//��ǰ�����Ϣ, 0�������1���Ҽ�
	int x;						//������
	int y;						//������
}cubeXY;  //��괥���ķ�������



/*���˵�ģ����ط�ʽ*/
int selectLanguage();																										//ѡ�����Խ��棬����
void loadMenu(FILE* menu2, inf* infs);																		//��ȡ�˵��ı��������ļ�ָ��ʹ���ı�������
void menu(int language);																								//��ʾ���˵����������Ա��
void showTutorial(int language);																					//��ʾ���ֽ̳̣��������Ա��

/*�ײ���ӻ���ط�ʽ*/
bool cursorCheck(int x, int y, int xMin, int xMax, int yMin, int yMax);		//������
void creatWindow();																											//�������ڣ�Ĭ��1280*720��
void creatRect(int x, int y, int height, int width, COLORREF color);				//����һ�����ľ��Σ�������ʼ���꣬�ߺͿ��Լ����ε���ɫ

/*��Ϸģ����ط�ʽ*/
void creatMine(cube(*cubes)[], int num);																	//�����������飬���뷽��ṹ����ָ���һ�����ϵķ�����
int creatGame(int num);																									//�����ؿ�������һ�����ϵķ��������������շ���
void drawMap(cube(*cubes)[], int num);																	//�ؿ����ӻ������뷽��ṹ����ָ���һ�����ϵķ�����
void tapCheck(int num, cubeXY* tap);																		//ʶ����괥���ķ������꣬����һ�����ϵķ������ͷ�������ָ��
void emptyCube(cube(*cubes)[], int num, int x, int y, int* recent);				
																							//��������Ϊ0�Ŀհ׷����Լ��ܱ߿հ׷��飬���뷽����ָ�룬���߷����������������Ŀǰʣ��δ��������

/*���а�ģ����ط�ʽ*/
void setRank(int num, int score, int language);														//д�����а����ݣ����뵥�߷������������Ѷȣ�����ҷ��������Ա��
player* getRank();																												//��ȡ���а����ݣ��������а�����ͷָ��
void rank(int language);																									//���а��ܺ��������������ȡ������Ϣ���������Ա��
void showEasy(player* rank, int language);															//��ʾ���Ѷ����а񣬴������а���������Ա��
void showHard(player* rank, int language);															//��ʾ�����Ѷ����а񣬴������а���������Ա��


#endif