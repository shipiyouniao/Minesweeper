/*******************************************************
	�ļ�����LeaderBoard.cpp
	���ܣ�������а���ط�ʽ
	�汾��1.2(22.05.29)
	���ߣ�ʯƤ����
	�汾˵�����Ż���������ʾ�����ݽṹ���޸���д������ʱ������bug

	�汾��־��
		1.0(22.05.28) ������а��ļ����
		1.1(22.05.28) �޸�������д����ٶ�ȡʱ����һ���ַ������Ե�bug
		1.2(22.05.29) �Ż���������ʾ�����ݽṹ���޸���д������ʱ������bug
*******************************************************/


#include "index.h"


/*******************************************************
	��ʽ����player* getRank()
	���ܣ��������а�
	��������
	���أ��������а�����ͷָ��
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

		if (head) {	//�ж�head�Ƿ�NULL
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
		if (head) {	//�ж�head�Ƿ�NULL
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

		if (head) {	//�ж�head�Ƿ�NULL
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
		if (head) {	//�ж�head�Ƿ�NULL
			tail->next = p;
		}
		else head = p;
		tail = p;
	}

	return head;
}

/*******************************************************
	��ʽ����void setRank(int num, int score, int language)
	���ܣ�д�����а�
	�����������Ѷȣ��÷ֺ�����
	���أ���
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
	settextstyle(50, 0, "΢���ź�");
	if (language == 1) {
		outtextxy(100, 200, "��ϲ������˸߷�");
		outtextxy(100, 350, "������ID(20Ӣ���ַ�����)��Ȼ����Enter");
	}
	else if (language == 2) {
		outtextxy(100, 200, "Congratulations on your high score");
		outtextxy(100, 350, "Please enter the ID (within 20 characters), and then press Enter");
	}
	else if (language == 3) {
		outtextxy(100, 200, "�ϥ�����������ǤȤ��������ޤ�");
		outtextxy(100, 350, "ID����������20Ӣ�Z�������ڣ���Enter��Ѻ���Ƥ���������");
	}
	settextcolor(BLACK);
	scanf("%s%*c", cName);
	if (language == 1) {
		cleardevice();
		settextstyle(100, 0, "΢���ź�");
		outtextxy(300, 200, "ȷ������");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "΢���ź�");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "��");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "��");
	}
	else if (language == 2) {
		cleardevice();
		settextstyle(100, 0, "΢���ź�");
		outtextxy(300, 200, "Are you sure��");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "΢���ź�");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "Yes");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "No");
	}
	else if (language == 3) {
		cleardevice();
		settextstyle(100, 0, "΢���ź�");
		outtextxy(300, 200, "�g�`���ʤ��Ǥ�����");
		outtextxy(300, 350, cName);
		settextstyle(35, 0, "΢���ź�");
		creatRect(290, 540, 55, 100, BLACK);
		outtextxy(300, 550, "�Ϥ�");
		creatRect(440, 540, 55, 100, BLACK);
		outtextxy(450, 550, "������");
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
					fprintf(fp, "<?xml version=\"1.0\" encoding=\"gb2312\"?>\n<!--���ļ����ڴ�����а����ݣ�easy��ǩ��ż��Ѷȣ�hard��ǩ��������Ѷ�-->\n<root>\n<easy>\n");
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
	��ʽ����void rank(int language)
	���ܣ��鿴���а�
	��������������
	���أ���
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
	��ʽ����void showEasy(player* rank, int language)
	���ܣ���ʾ���Ѷ����а�
	�������������а����������
	���أ���
*******************************************************/

void showEasy(player* rank, int language) {
	cleardevice();
	for (int i = 0; i < 10; i++) {
		settextstyle(60, 0, "΢���ź�");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1);
		outtextxy(200, 20 + 68 * i, r);
		outtextxy(400, 20 + 68 * i, rank[i].cName);
		outtextxy(600, 20 + 68 * i, strScore);
	}
	settextstyle(35, 0, "΢���ź�");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "����");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "����");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "��");
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
	��ʽ����void showHard(player* rank, int language)
	���ܣ���ʾ�����Ѷ����а�
	�������������а����������
	���أ���
*******************************************************/

void showHard(player* rank, int language) {
	cleardevice();
	for (int i = 10; i < 20; i++) {
		settextstyle(60, 0, "΢���ź�");
		char r[3], strScore[12];
		sprintf(strScore, "%d pts", rank[i].Score);;
		sprintf(r, "#%d", i + 1 - 10);
		outtextxy(200, 20 + 68 * (i - 10), r);
		outtextxy(400, 20 + 68 * (i - 10), rank[i].cName);
		outtextxy(600, 20 + 68 * (i - 10), strScore);
	}
	settextstyle(35, 0, "΢���ź�");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "����");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "����");
	creatRect(1000, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1010, 610, "����");
	else if (language == 2)outtextxy(1010, 610, "Hard");
	else if (language == 3)outtextxy(1010, 610, "�y����");

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