/*******************************************************
	文件名：Game.cpp
	功能：存放关卡生成和游玩的相关方式
	版本：1.2(22.05.29)
	作者：石皮幼鸟
	版本说明：优化了字体显示和数据结构，不醒目的“？”符号被“●”代替，暗红色改为亮红色

	版本日志：
		1.0(22.05.28) 完成关卡文件框架
		1.1(22.05.28) 优化了分数计算机制，现在计分系统更加合理
		1.2(22.05.29) 优化了字体显示和数据结构，不醒目的“？”符号被“●”代替，暗红色改为亮红色
*******************************************************/


#include "index.h"



/*******************************************************
	方式名：void creatMine(cube (* cubes)[], int num)
	功能：创建随机化关卡
	参数：传入方块数组行指针以及正方形区域边长（即一条边多少个小方块）
	返回：无
*******************************************************/

void creatMine(cube (* cubes)[], int num) {
	int maxMine = 10;
	if (num == 16) maxMine = 40;
	int flag = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			(*cubes + i * num + j)->type = 1;
			(*cubes + i * num + j)->recent = 0;
			(*cubes + i * num + j)->num = 0;
			(*cubes + i * num + j)->mark = 0;
		}
	}
	srand(time(0));
	for (int i = 0; i < num, flag!= maxMine; i++) {
		for (int j = 0; j < num; j++) {
			int k = rand() % 10 + 1;
			if (k == 1 || k == 5) {
				(*cubes + i * num + j)->type = 0;
				flag++;
				if (flag == maxMine) break;
			}
		}
	}
	if (flag < maxMine) creatMine(cubes, num);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (((*cubes + i * num) + j)->type == 0) {
				if (i != 0) {
					if (j != 0) ((*cubes + (i - 1) * num) + j - 1)->num++;
					((*cubes + (i - 1) * num) + j)->num++;
					if (j != num-1) ((*cubes + (i - 1) * num) + j + 1)->num++;
				}
				if (i != num-1) {
					if (j != 0) ((*cubes + (i + 1) * num) + j - 1)->num++;
					((*cubes + (i + 1) * num) + j)->num++;
					if (j != num-1) ((*cubes + (i + 1) * num) + j + 1)->num++;
				}
				if (j != 0) ((*cubes + i * num) + j - 1)->num++;
				if (j != num-1) ((*cubes + i * num) + j + 1)->num++;
			}
		}
	}
}

/*******************************************************
	方式名：void drawMap(cube (* cubes)[], int num)
	功能：在窗口中显示关卡图案
	参数：传入方块数组行指针以及正方形区域边长（即一条边多少个小方块）
	返回：无
*******************************************************/
void drawMap(cube(*cubes)[], int num) {
	cleardevice();
	
	for (int i = 0; i < num + 1; i++) {
		moveto(300 + i * 680 / (num + 1), 20);
		linerel(0, 680 - 680 / (num + 1));
	}
	for (int i = 0; i < num + 1; i++) {
		moveto(300, 20 + i * 680 / (num + 1));
		linerel(680 - 680 / (num + 1), 0);
	}
	settextcolor(BLACK);
	settextstyle(35 * 9 / (num - 3), 0, "微软雅黑");
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (((*cubes + i * num) + j)->recent == 0 && ((*cubes + i * num) + j)->mark == 0) {
				outtextxy(305 + i * 680 / (num + 1), 25 + j * 680 / (num + 1), "●");
			}
			else if (((*cubes + i * num) + j)->recent == 0 && ((*cubes + i * num) + j)->mark == 1) {
				settextcolor(LIGHTRED);
				outtextxy(305 + i * 680 / (num + 1), 25 + j * 680 / (num + 1), "●");
				settextcolor(BLACK);
			}
			else if (((*cubes + i * num) + j)->recent == 1) {
				if (((*cubes + i * num) + j)->type == 1 && ((*cubes + i * num) + j)->num != 0) {
					char N[5];
					sprintf(N, "%d", ((*cubes + i * num) + j)->num);
					outtextxy(305 + i * 680 / (num + 1), 25 + j * 680 / (num + 1), N);
				}
				else if(((*cubes + i * num) + j)->type == 0) {
					settextcolor(RED);
					outtextxy(305 + i * 680 / (num + 1), 25 + j * 680 / (num + 1), "M");
					settextcolor(BLACK);
				}
			}
		}
	}
}

/*******************************************************
	方式名：void tapCheck(int num, cubeXY* tap)
	功能：读取鼠标触发的方块坐标
	参数：传入正方形区域边长（即一条边多少个小方块）以及方块坐标结构体指针
	返回：无
*******************************************************/

void tapCheck(int num, cubeXY* tap) {
	while (1) {
		FlushMouseMsgBuffer();
		MOUSEMSG click = GetMouseMsg();
		bool square = (click.x >= 300 && click.x <= (300 + 680 - 680 / (num + 1)) && click.y >= 20 && click.y <= (20 + 680 - 680 / (num + 1))); //判定区域限制
		if (click.mkLButton) {
			FlushMouseMsgBuffer();
			click = GetMouseMsg();
			if (click.uMsg == WM_LBUTTONUP && square) {
				tap->x = ((click.x - 300) / (680 / (num + 1)));
				tap->y = ((click.y - 20) / (680 / (num + 1)));
				tap->uMsg = 0;
				break;
			}
		}
		else if (click.mkRButton) {
			FlushMouseMsgBuffer();
			click = GetMouseMsg();
			if (click.uMsg == WM_RBUTTONUP && square) {
				tap->x = ((click.x - 300) / (680 / (num + 1))) ;
				tap->y = ((click.y - 20) / (680 / (num + 1))) ;
				tap->uMsg = 1;
				break;
			}
		}
	}
}

/*******************************************************
	方式名：void emptyCube(cube(*cubes)[], int num, int x, int y, int* recent)
	功能：触发空白方块旁边的空白方块
	参数：传入方块数组和正方形区域边长（即一条边多少个小方块），主方块坐标，以及当前剩余未触发的方块数
	返回：无
*******************************************************/

void emptyCube(cube(*cubes)[], int num, int x, int y, int* recent) {
	(* recent)--;
	((*cubes +x * num) + y)->recent = 1;
	if (x != 0) {
		if (y != 0) {
			if (((*cubes + (x - 1) * num) + y - 1)->type == 1 && ((*cubes + (x - 1) * num) + y - 1)->recent == 0) {
				if (((*cubes + (x - 1) * num) + y - 1)->num == 0) emptyCube(cubes, num, x - 1, y - 1, recent);
				else {
					((*cubes + (x - 1) * num) + y - 1)->recent = 1;
					(*recent)--;
				}
			}
		}
		if (((*cubes + (x - 1) * num) + y)->type == 1 && ((*cubes + (x - 1) * num) + y)->recent == 0) {
			if (((*cubes + (x - 1) * num) + y)->num == 0) emptyCube(cubes, num, x - 1, y, recent);
			else {
				((*cubes + (x - 1) * num) + y)->recent = 1;
				(*recent)--;
			}
		}
		if (y != num - 1) {
			if (((*cubes + (x - 1) * num) + y + 1)->type == 1 && ((*cubes + (x - 1) * num) + y + 1)->recent == 0) {
				if (((*cubes + (x - 1) * num) + y + 1)->num == 0) emptyCube(cubes, num, x - 1, y + 1, recent);
				else {
					((*cubes + (x - 1) * num) + y + 1)->recent = 1;
					(*recent)--;
				}
			}
		}
	}
		if (x != num - 1) {
			if (y != 0) {
				if (((*cubes + (x + 1) * num) + y - 1)->type == 1 && ((*cubes + (x + 1) * num) + y - 1)->recent == 0) {
					if (((*cubes + (x + 1) * num) + y - 1)->num == 0) emptyCube(cubes, num, x + 1, y - 1, recent);
					else {
						((*cubes + (x + 1) * num) + y - 1)->recent = 1;
						(*recent)--;
					}
				}
			}
			if (((*cubes + (x + 1) * num) + y)->type == 1 && ((*cubes + (x + 1) * num) + y)->recent == 0) {
				if (((*cubes + (x + 1) * num) + y)->num == 0) emptyCube(cubes, num, x + 1, y, recent);
				else {
					((*cubes + (x + 1) * num) + y)->recent = 1;
					(*recent)--;
				}
			}
			if (y != num - 1) {
				if (((*cubes + (x + 1) * num) + y + 1)->type == 1 && ((*cubes + (x + 1) * num) + y + 1)->recent == 0) {
					if (((*cubes + (x + 1) * num) + y + 1)->num == 0) emptyCube(cubes, num, x + 1, y + 1, recent);
					else {
						((*cubes + (x + 1) * num) + y + 1)->recent = 1;
						(*recent)--;
					}
				}
			}
		}
		if (y != 0) if (((*cubes + x * num) + y - 1)->type == 1 && ((*cubes + x * num) + y - 1)->recent == 0) {
			if (((*cubes + x * num) + y - 1)->num == 0) emptyCube(cubes, num, x, y - 1, recent);
			else {
				((*cubes + x * num) + y - 1)->recent = 1;
				(*recent)--;
			}
		}
		if (y != num - 1) if (((*cubes + x * num) + y + 1)->type == 1 && ((*cubes + x * num) + y + 1)->recent == 0) {
			if (((*cubes + x * num) + y + 1)->num == 0) emptyCube(cubes, num, x, y + 1, recent);
			else {
				((*cubes + x * num) + y + 1)->recent = 1;
				(*recent)--;
			}
		}
}

/*******************************************************
	方式名：int creatGame(int num)
	功能：创建关卡
	参数：传入正方形区域边长（即一条边多少个小方块），9是简单难度，16是困难难度
	返回：游戏分数
*******************************************************/

int creatGame(int num) {
	time_t t1, t2;
	time(&t1);
	cube(*cubes)[] = (cube(*)[])malloc(num * num * sizeof(cube));
	creatMine(cubes, num);
	bool lose = FALSE;
	int maxMine = 10;
	if (num == 16) maxMine = 40;
	int recent = num * num;
	while (1) {
		drawMap(cubes, num);
		cubeXY* tap = (cubeXY*)malloc(sizeof(cubeXY));
		tapCheck(num,tap);
		if (tap->uMsg == 1) {
			if (((*cubes + tap->x * num) + tap->y)->recent == 0 && ((*cubes + tap->x * num) + tap->y)->mark == 0)((*cubes + tap->x * num) + tap->y)->mark = 1;
			else if (((*cubes + tap->x * num) + tap->y)->recent == 0 && ((*cubes + tap->x * num) + tap->y)->mark == 1)((*cubes + tap->x * num) + tap->y)->mark = 0;
		}
		else if (tap->uMsg == 0) {
			if (((*cubes + tap->x * num) + tap->y)->recent == 0) {
				if (((*cubes + tap->x * num) + tap->y)->type == 0) {
					((*cubes + tap->x * num) + tap->y)->recent = 1;
					lose = TRUE;
					time(&t2);
					free(tap);
					break;
				}
				else {
					if (((*cubes + tap->x * num) + tap->y)->num == 0) emptyCube(cubes, num, tap->x, tap->y, &recent);
					else {
						((*cubes + tap->x * num) + tap->y)->recent = 1;
						recent--;
					}
				}
			}
		}
		free(tap);
		if (recent == maxMine) {
			time(&t2);
			break;
		}
	}
	long time = t2 - t1;
	int score = 1000000 - time * 500 - (recent - maxMine) * 9000;
	drawMap(cubes, num);
	char strScore[12];
	sprintf(strScore, "%d pts", score);
	settextstyle(50, 0, "微软雅黑");
	outtextxy(980, 200, "Game Over");
	if (!lose)outtextxy(980, 250, "You Win");
	else outtextxy(980, 250, "You Lose");
	outtextxy(960, 300, "You've gained:");
	settextcolor(RED);
	outtextxy(960, 350, strScore);
	settextstyle(35, 0, "微软雅黑");
	creatRect(970, 490, 55, 100, BLACK);
	outtextxy(980, 500, "Next");
	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 970, 1070, 490, 545)) {
				free(cubes);
				cleardevice();
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)return score;
			}
		}
	}
}