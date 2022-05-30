/*******************************************************
	文件名：Menu.cpp
	功能：存放主菜单相关方式
	版本：1.2(22.05.29)
	作者：石皮幼鸟
	版本说明：修复了主菜单可能变色的bug

	版本日志：
		1.0(22.05.28) 完成主菜单模块框架
		1.1(22.05.28) 修复xml读取后编码错乱的问题（UTF-8转GB2312）
		1.2(22.05.29) 修复了主菜单可能变色的bug
*******************************************************/


#include "index.h"



/*******************************************************
	方式名：int selectLanguage()
	功能：显示选择语言界面
	参数：无
	返回：1是汉语，2是英语，3是日语
*******************************************************/
int selectLanguage()
{
	cleardevice();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(50, 0, "微软雅黑");
	outtextxy(450, 50, "请选择您想使用的语言");
	settextstyle(35, 0, "微软雅黑");
	outtextxy(475, 100, "Please select the language");
	outtextxy(475, 135, "使用言語を選択してください");
	creatRect(565, 260, 55, 150, BLACK);
	outtextxy(575, 270, "1.中文");
	creatRect(565, 360, 55, 150, BLACK);
	outtextxy(575, 370, "2.English");
	creatRect(565, 460, 55, 150, BLACK);
	outtextxy(575, 470, "3.日本語");
	int language;
	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 565, 715, 260, 315)) {
				language = 1;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
			else if (cursorCheck(click.x, click.y, 565, 715, 360, 415)) {
				language = 2;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
			else if (cursorCheck(click.x, click.y, 565, 715, 460, 515)) {
				language = 3;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
		}
	}
	cleardevice();
	return language;
}

/*******************************************************
	方式名：void loadMenu(FILE* menu2, inf* infs)
	功能：读取菜单文本
	参数：传入文件指针和文本结构体指针
	返回：无
*******************************************************/
void loadMenu(FILE* menu2, inf* infs) {
	char* a = (char*)malloc(100 * sizeof(char));
	do {
		fscanf(menu2, "%s%*c", a);
	} while (strcmp("<cn>", a) != 0);
	for (int i = 0;; i++) {
		fgets(a, 100, menu2);
		if (strcmp("</cn>\n", a) != 0) strcpy(infs->cnInf[i], a);
		else break;
	}
	do {
		fscanf(menu2, "%s%*c", a);
	} while (strcmp("<en>", a) != 0);
	for (int i = 0;; i++) {
		fgets(a, 100, menu2);
		if (strcmp("</en>\n", a) != 0) strcpy(infs->enInf[i], a);
		else break;
	}
	do {
		fscanf(menu2, "%s%*c", a);
	} while (strcmp("<jp>", a) != 0);
	for (int i = 0;; i++) {
		fgets(a, 100, menu2);
		if (strcmp("</jp>\n", a) != 0) strcpy(infs->jpInf[i], a);
		else break;
	}
}

/*******************************************************
	方式名：void menu(int language)
	功能：显示菜单
	参数：传入语言对应的数字，1是汉语，2是英语，3是日语
	返回：无
*******************************************************/
void menu(int language) {
	cleardevice();
	FILE* menu2;
	if ((menu2 = fopen("Menu.xml", "r")) == NULL) {
		printf("\nCAN NOT OPEN THE FILE");
		exit(1);
	}
	inf *infs=(inf*)malloc(sizeof(inf));
	loadMenu(menu2,infs);
	char Inf[9][30];
	if (language == 1) {
		for (int i = 0; i < 9; i++) strcpy(Inf[i], infs->cnInf[i]);
	}else if (language == 2) {
		for (int i = 0; i < 9; i++) strcpy(Inf[i], infs->enInf[i]);
	}
	else if(language == 3) {
		for (int i = 0; i < 9; i++) strcpy(Inf[i], infs->jpInf[i]);
	}
	free(infs);
	settextcolor(BLACK);
	settextstyle(70, 0, "微软雅黑");
	outtextxy(525, 50, Inf[0]);
	settextstyle(35, 0, "微软雅黑");
	for (int i = 1; i < 5; i++) {
		creatRect(545, 260+100*(i-1), 55, 200, BLACK);
		outtextxy(555, 270 + 100 * (i - 1), Inf[i]);
	}
	int select;
	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 545, 745, 260, 315)) {
				select = 1;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
			else if (cursorCheck(click.x, click.y, 545, 745, 360, 415)) {
				select = 2;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
			else if (cursorCheck(click.x, click.y, 545, 745, 460, 515)) {
				select = 3;
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)break;
			}
			else if (cursorCheck(click.x, click.y, 545, 745, 560, 615)) {
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP)exit(1);
			}
		}
	}
	if (select == 1) {
		cleardevice();
		settextstyle(70, 0, "微软雅黑");
		outtextxy(505, 50, Inf[5]);
		settextstyle(35, 0, "微软雅黑");
		for (int i = 6; i < 8; i++) {
			creatRect(585, 300 + 200 * (i - 6), 55, 120, BLACK);
			outtextxy(595, 310 + 200 * (i - 6), Inf[i]);
		}
		creatRect(1100, 600, 55, 90, BLACK);
		outtextxy(1110, 610, Inf[8]);
		int score;
		while (1) {
			MOUSEMSG click = GetMouseMsg();
			if (click.mkLButton) {
				if (cursorCheck(click.x, click.y, 585, 705, 300, 355)) {
					select = 1;
					FlushMouseMsgBuffer();
					click = GetMouseMsg();
					if (click.uMsg == WM_LBUTTONUP) {
						score = creatGame(9);
						setRank(9, score, language);
						rank(language);
					}
				}
				else if (cursorCheck(click.x, click.y, 585, 705, 500, 555)) {
					select = 2;
					FlushMouseMsgBuffer();
					click = GetMouseMsg();
					if (click.uMsg == WM_LBUTTONUP) {
						score = creatGame(16);
						setRank(16, score, language);
						rank(language);
					}
				}
				else if (cursorCheck(click.x, click.y, 1100, 1190, 600, 655)) {
					FlushMouseMsgBuffer();
					click = GetMouseMsg();
					if (click.uMsg == WM_LBUTTONUP) menu(language);
				}
			}
		}
	}
	else if (select == 2) showTutorial(language);
	else if (select == 3) rank(language);
}

/*******************************************************
	方式名：void showTutorial(int language)
	功能：显示新手教程
	参数：传入语言
	返回：无
*******************************************************/

void showTutorial(int language) {
	cleardevice();
	settextstyle(30, 0, "微软雅黑");
	if (language == 1) {
		outtextxy(100, 200, "点击黑色的“●”敲开方块；");
		outtextxy(100, 250, "点击后如果显示M，则代表触发地雷，游戏结束；");
		outtextxy(100, 300, "如果出现数字，则意味着周围有对应数字的地雷数；");
		outtextxy(100, 350, "如果是空白，则周围无地雷；");
		outtextxy(100, 400, "鼠标右击标记你怀疑是地雷的“●”方块，可以使其变红；");
		outtextxy(100, 450, "再右击一次可以恢复黑色；");
		outtextxy(100, 500, "敲开所有非地雷方块，赢得最终胜利。");
	}
	else if (language == 2) {
		outtextxy(100, 200, "Click on the black \" ● \" to crack open the square;");
		outtextxy(100, 250, "If M is displayed after clicking, it means the mine is triggered and the game is over;");
		outtextxy(100, 300, "If a number appears, it means that the number of mines with the corresponding number is around;");
		outtextxy(100, 350, "If blank, there are no mines around;");
		outtextxy(100, 400, "Right mouse click on the square that marks what you suspect is a mine to turn it red;");
		outtextxy(100, 450, "Right-click once more to restore the black color;");
		outtextxy(100, 500, "Knock out all the non-mine squares to win the final victory.");
	}
	else if (language == 3) {
		outtextxy(100, 200, "黒い「●」をクリックすると、マスが発動します；");
		outtextxy(100, 250, "クリックしたときにMが表示された場合は、地雷が作動してゲームオーバーになったことを意味します；");
		outtextxy(100, 300, "数字が表示された場合、その数字に対応する地雷の数が周辺にあることを意味します；");
		outtextxy(100, 350, "空白の場合、地雷はありません；");
		outtextxy(100, 400, "地雷と思われるマスをマウスの右クリックでマークすると赤くなる；");
		outtextxy(100, 450, "もう一度右クリックで黒に戻る；");
		outtextxy(100, 500, "地雷のないマスをすべてトリガーにして最終的に勝利する。");
	}
	settextstyle(35, 0, "微软雅黑");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "返回");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "戻る");
	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 1100, 1190, 600, 655)) {
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) menu(language);
			}
		}
	}
}