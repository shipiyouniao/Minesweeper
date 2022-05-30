/*******************************************************
	文件名：LeaderBoard.cpp
	功能：存放排行榜相关方式
	版本：1.2(22.05.29)
	作者：石皮幼鸟
	版本说明：优化了字体显示和数据结构，修复了写入数据时白屏的bug

	版本日志：
		1.0(22.05.28) 完成排行榜文件框架
		1.1(22.05.28) 修复了数据写入后再读取时，第一个字符被忽略的bug
		1.2(22.05.29) 优化了字体显示和数据结构，修复了写入数据时白屏的bug
*******************************************************/


#include "index.h"


/*******************************************************
	方式名：player* getRank()
	功能：读入排行榜
	参数：无
	返回：返回排行榜链表头指针
*******************************************************/

player* getRank() {
	FILE* fp = fopen("Rank.xml", "r");
	player* head = NULL, * tail = NULL;
	char* a = (char*)malloc(100 * sizeof(char));
	do {
		fscanf(fp, "%s%*c", a);
	} while (strcmp("<easy>", a) != 0);
	int k = 0;
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%s", a);
		player* p = (player*)malloc(sizeof(player));
		p->next = NULL;

		if (strcmp("</easy>", a) != 0) {
			strcpy(p->cName, a);
			fscanf(fp, "%d%*c", &p->Score);
			k++;
		}
		else {
			break;
		}

		if (head) {	//判断head是否NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}
	for (int i = 0; i < 10 - k; i++) {
		player* p = (player*)malloc(sizeof(player));
		p->next = NULL;
		strcpy(p->cName, "EMPTY");
		p->Score = 0;
		if (head) {	//判断head是否NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}
	k = 0;
	do {
		fscanf(fp, "%s%*c", a);
	} while (strcmp("<hard>", a) != 0);
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%s", a);
		player* p = (player*)malloc(sizeof(player));
		p->next = NULL;

		if (strcmp("</hard>", a) != 0) {
			strcpy(p->cName, a);
			fscanf(fp, "%d%*c", &p->Score);
			k++;
		}
		else {
			break;
		}

		if (head) {	//判断head是否NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}
	for (int i = 0; i < 10 - k; i++) {
		player* p = (player*)malloc(sizeof(player));
		p->next = NULL;
		strcpy(p->cName, "EMPTY");
		p->Score = 0;
		if (head) {	//判断head是否NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}

	return head;
}

/*******************************************************
	方式名：void setRank(int num, int score, int language)
	功能：写入排行榜
	参数：传入难度，得分和语言
	返回：无
*******************************************************/

void setRank(int num, int score, int language) {
	player* head = getRank();
	player* p = head, * mid;
	for (int i = 0; i < 10; i++) p = p->next;
	mid = p;
	if (num == 9) {
		if (score < head->Score) return;
	}
	else if (num == 16) {
		if (score < mid->Score) return;
	}

	char cName[21];
	settextcolor(RED);
	settextstyle(50, 0, "微软雅黑");
	if (language == 1) {
		outtextxy(100, 200, "恭喜您获得了高分");
		outtextxy(100, 350, "请输入ID(20英文字符以内)，然后按下Enter");
	}
	else if (language == 2) {
		outtextxy(100, 200, "Congratulations on your high score");
		outtextxy(100, 350, "Please enter the ID (within 20 characters), and then press Enter");
	}
	else if (language == 3) {
		outtextxy(100, 200, "ハイスコアおめでとうございます");
		outtextxy(100, 350, "IDを入力し（20英語文字以内）、Enterを押してください。");
	}
	settextcolor(BLACK);
	scanf("%s%*c", cName);
	if (language == 1) {
		cleardevice();
		settextstyle(100, 0, "微软雅黑");
		outtextxy(300, 200, "确定了吗？");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "微软雅黑");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "是");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "否");
	}
	else if (language == 2) {
		cleardevice();
		settextstyle(100, 0, "微软雅黑");
		outtextxy(300, 200, "Are you sure？");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "微软雅黑");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "Yes");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "No");
	}
	else if (language == 3) {
		cleardevice();
		settextstyle(100, 0, "微软雅黑");
		outtextxy(300, 200, "間違いないですか？");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "微软雅黑");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "はい");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "いいえ");
	}

	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 440, 540, 540, 595)) {
				cleardevice();
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) setRank(num, score, language);
			}
			if (cursorCheck(click.x, click.y, 290, 390, 540, 595)) {
				cleardevice();
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) {
					player* np = (player*)malloc(sizeof(player));
					strcpy(np->cName, cName);
					np->Score = score;
					if (num == 9)
					{
						np->next = head;
						head = np;
					}
					else if (num == 16) {
						np->next = mid;
						mid = np;
					}

					p = head;
					FILE* fp = fopen("Rank.xml", "w");
					fprintf(fp, "<?xml version=\"1.0\" encoding=\"gb2312\"?>\n<!--此文件用于存放排行榜数据，easy标签存放简单难度，hard标签存放困难难度-->\n<root>\n<easy>\n");
					for (int i = 0; i < 10; i++) {
						fprintf(fp, "%s %d\n", p->cName, p->Score);
						p = p->next;
					}
					p = mid;
					fprintf(fp, "</easy>\n<hard>\n");
					for (int i = 0; i < 10; i++) {
						fprintf(fp, "%s %d\n", p->cName, p->Score);
						p = p->next;
					}
					fprintf(fp, "</hard>\n</root>");
					fclose(fp);
					break;
				}
			}
		}
	}
}

/*******************************************************
	方式名：void rank(int language)
	功能：查看排行榜
	参数：传入语言
	返回：无
*******************************************************/

void rank(int language) {
	player* head = getRank();
	player rank[20];
	for (int i = 0; i < 20; i++) {
		strcpy(rank[i].cName, head->cName);
		rank[i].Score = head->Score;
		head = head->next;
	}
	showEasy(rank, language);
}

/*******************************************************
	方式名：void showEasy(player* rank, int language)
	功能：显示简单难度排行榜
	参数：传入排行榜数组和语言
	返回：无
*******************************************************/

void showEasy(player* rank, int language) {
	cleardevice();
	for (int i = 0; i < 10; i++) {
		settextstyle(60, 0, "微软雅黑");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1);
		outtextxy(200, 20 + 68 * i, r);
		outtextxy(400, 20 + 68 * i, rank[i].cName);
		outtextxy(600, 20 + 68 * i, strScore);
	}
	settextstyle(35, 0, "微软雅黑");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "返回");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "戻る");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "简单");
	else if (language == 2)outtextxy(1010, 610, "Easy");
	else if (language == 3)outtextxy(1010, 610, "簡単");

	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 1000, 1090, 600, 655)) {
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) showHard(rank, language);
			}
			else if (cursorCheck(click.x, click.y, 1100, 1190, 600, 655)) {
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) menu(language);
			}
		}
	}
}

/*******************************************************
	方式名：void showHard(player* rank, int language)
	功能：显示困难难度排行榜
	参数：传入排行榜数组和语言
	返回：无
*******************************************************/

void showHard(player* rank, int language) {
	cleardevice();
	for (int i = 10; i < 20; i++) {
		settextstyle(60, 0, "微软雅黑");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1 - 10);
		outtextxy(200, 20 + 68 * (i - 10), r);
		outtextxy(400, 20 + 68 * (i - 10), rank[i].cName);
		outtextxy(600, 20 + 68 * (i - 10), strScore);
	}
	settextstyle(35, 0, "微软雅黑");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "返回");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "戻る");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "困难");
	else if (language == 2)outtextxy(1010, 610, "Hard");
	else if (language == 3)outtextxy(1010, 610, "難しい");

	while (1) {
		MOUSEMSG click = GetMouseMsg();
		if (click.mkLButton) {
			if (cursorCheck(click.x, click.y, 1000, 1090, 600, 655)) {
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) showEasy(rank, language);
			}
			else if (cursorCheck(click.x, click.y, 1100, 1190, 600, 655)) {
				FlushMouseMsgBuffer();
				click = GetMouseMsg();
				if (click.uMsg == WM_LBUTTONUP) menu(language);
			}
		}
	}
}