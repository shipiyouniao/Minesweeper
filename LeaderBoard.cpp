/*******************************************************
	猟周兆��LeaderBoard.cpp
	孔嬬�佐羞電登舒駭犢愀淑�
	井云��2.0(22.07.17) 
	恬宀�妻�討嘛抵
	井云傍苧�采嶢惨緑涕漢撲竿詈�象扮易徳議bug

	井云晩崗��
		1.0(22.05.28) 頼撹電佩茨猟周崇尺
		1.1(22.05.28) 俐鹸阻方象亟秘朔壅響函扮��及匯倖忖憲瓜策待議bug
		1.2(22.05.29) 單晒阻忖悶�塋昇擁�象潤更��俐鹸阻亟秘方象扮易徳議bug
		1.3(22.05.31) 壅肝俐鹸阻亟秘方象扮易徳議bug
		2.0(22.07.17) 嗽匯肝俐鹸阻亟秘方象扮易徳議bug
*******************************************************/


#include "index.h"


/*******************************************************
	圭塀兆��player* getRank()
	孔嬬�唆組訶登舒�
	歌方�採�
	卦指�嵯技愿登舒饒官輙蛍胡�
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

		if (head) {	//登僅head頁倦NULL
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
		if (head) {	//登僅head頁倦NULL
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

		if (head) {	//登僅head頁倦NULL
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
		if (head) {	//登僅head頁倦NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}

	return head;
}

/*******************************************************
	圭塀兆��void setRank(int num, int score, int language)
	孔嬬�歳竿訶登舒�
	歌方�佐�秘佃業��誼蛍才囂冱
	卦指�採�
*******************************************************/

void setRank(int num, int score, int language) {
	cleardevice();
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
	settextstyle(50, 0, "裏罷囘菜");
	if (language == 1) {
		outtextxy(100, 200, "孝浪艇資誼阻互蛍");
		outtextxy(100, 350, "萩補秘ID(20哂猟忖憲參坪)��隼朔梓和Enter");
	}
	else if (language == 2) {
		outtextxy(100, 200, "Congratulations on your high score");
		outtextxy(100, 350, "Please enter the ID (within 20 characters), and then press Enter");
	}
	else if (language == 3) {
		outtextxy(100, 200, "ハイスコアおめでとうございます");
		outtextxy(100, 350, "IDを秘薦し��20哂�Z猟忖參坪��、Enterを兀してください。");
	}
	settextcolor(BLACK);
	scanf("%s%*c", cName);
	if (language == 1) {
		cleardevice();
		settextstyle(100, 0, "裏罷囘菜");
		outtextxy(300, 200, "鳩協阻宅��");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "裏罷囘菜");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "頁");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "倦");
	}
	else if (language == 2) {
		cleardevice();
		settextstyle(100, 0, "裏罷囘菜");
		outtextxy(300, 200, "Are you sure��");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "裏罷囘菜");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "Yes");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "No");
	}
	else if (language == 3) {
		cleardevice();
		settextstyle(100, 0, "裏罷囘菜");
		outtextxy(300, 200, "�g�`いないですか��");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "裏罷囘菜");
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
					fprintf(fp, "<?xml version=\"1.0\" encoding=\"gb2312\"?>\n<!--緩猟周喘噐贋慧電佩茨方象��easy炎禰贋慧酒汽佃業��hard炎禰贋慧是佃佃業-->\n<root>\n<easy>\n");
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
	圭塀兆��void rank(int language)
	孔嬬�魂蘓甘登舒�
	歌方�佐�秘囂冱
	卦指�採�
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
	圭塀兆��void showEasy(player* rank, int language)
	孔嬬�栽塋昭魑ツ儷氾登舒�
	歌方�佐�秘電佩茨方怏才囂冱
	卦指�採�
*******************************************************/

void showEasy(player* rank, int language) {
	cleardevice();
	for (int i = 0; i < 10; i++) {
		settextstyle(60, 0, "裏罷囘菜");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1);
		outtextxy(200, 20 + 68 * i, r);
		outtextxy(400, 20 + 68 * i, rank[i].cName);
		outtextxy(600, 20 + 68 * i, strScore);
	}
	settextstyle(35, 0, "裏罷囘菜");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "卦指");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "��る");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "酒汽");
	else if (language == 2)outtextxy(1010, 610, "Easy");
	else if (language == 3)outtextxy(1010, 610, "���g");

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
	圭塀兆��void showHard(player* rank, int language)
	孔嬬�栽塋樟�佃佃業電佩茨
	歌方�佐�秘電佩茨方怏才囂冱
	卦指�採�
*******************************************************/

void showHard(player* rank, int language) {
	cleardevice();
	for (int i = 10; i < 20; i++) {
		settextstyle(60, 0, "裏罷囘菜");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1 - 10);
		outtextxy(200, 20 + 68 * (i - 10), r);
		outtextxy(400, 20 + 68 * (i - 10), rank[i].cName);
		outtextxy(600, 20 + 68 * (i - 10), strScore);
	}
	settextstyle(35, 0, "裏罷囘菜");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "卦指");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "��る");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "是佃");
	else if (language == 2)outtextxy(1010, 610, "Hard");
	else if (language == 3)outtextxy(1010, 610, "�yしい");

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