/*******************************************************
	�ļ�����Menu.cpp
	���ܣ�������˵���ط�ʽ
	�汾��1.2(22.05.29)
	���ߣ�ʯƤ����
	�汾˵�����޸������˵����ܱ�ɫ��bug

	�汾��־��
		1.0(22.05.28) ������˵�ģ����
		1.1(22.05.28) �޸�xml��ȡ�������ҵ����⣨UTF-8תGB2312��
		1.2(22.05.29) �޸������˵����ܱ�ɫ��bug
*******************************************************/


#include "index.h"



/*******************************************************
	��ʽ����int selectLanguage()
	���ܣ���ʾѡ�����Խ���
	��������
	���أ�1�Ǻ��2��Ӣ�3������
*******************************************************/
int selectLanguage()
{
	cleardevice();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(50, 0, "΢���ź�");
	outtextxy(450, 50, "��ѡ������ʹ�õ�����");
	settextstyle(35, 0, "΢���ź�");
	outtextxy(475, 100, "Please select the language");
	outtextxy(475, 135, "ʹ�����Z���x�k���Ƥ�������");
	creatRect(565, 260, 55, 150, BLACK);
	outtextxy(575, 270, "1.����");
	creatRect(565, 360, 55, 150, BLACK);
	outtextxy(575, 370, "2.English");
	creatRect(565, 460, 55, 150, BLACK);
	outtextxy(575, 470, "3.�ձ��Z");
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
	��ʽ����void loadMenu(FILE* menu2, inf* infs)
	���ܣ���ȡ�˵��ı�
	�����������ļ�ָ����ı��ṹ��ָ��
	���أ���
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
	��ʽ����void menu(int language)
	���ܣ���ʾ�˵�
	�������������Զ�Ӧ�����֣�1�Ǻ��2��Ӣ�3������
	���أ���
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
	settextstyle(70, 0, "΢���ź�");
	outtextxy(525, 50, Inf[0]);
	settextstyle(35, 0, "΢���ź�");
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
		settextstyle(70, 0, "΢���ź�");
		outtextxy(505, 50, Inf[5]);
		settextstyle(35, 0, "΢���ź�");
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
	��ʽ����void showTutorial(int language)
	���ܣ���ʾ���ֽ̳�
	��������������
	���أ���
*******************************************************/

void showTutorial(int language) {
	cleardevice();
	settextstyle(30, 0, "΢���ź�");
	if (language == 1) {
		outtextxy(100, 200, "�����ɫ�ġ����ÿ����飻");
		outtextxy(100, 250, "����������ʾM������������ף���Ϸ������");
		outtextxy(100, 300, "����������֣�����ζ����Χ�ж�Ӧ���ֵĵ�������");
		outtextxy(100, 350, "����ǿհף�����Χ�޵��ף�");
		outtextxy(100, 400, "����һ�����㻳���ǵ��׵ġ��񡱷��飬����ʹ���죻");
		outtextxy(100, 450, "���һ�һ�ο��Իָ���ɫ��");
		outtextxy(100, 500, "�ÿ����зǵ��׷��飬Ӯ������ʤ����");
	}
	else if (language == 2) {
		outtextxy(100, 200, "Click on the black \" �� \" to crack open the square;");
		outtextxy(100, 250, "If M is displayed after clicking, it means the mine is triggered and the game is over;");
		outtextxy(100, 300, "If a number appears, it means that the number of mines with the corresponding number is around;");
		outtextxy(100, 350, "If blank, there are no mines around;");
		outtextxy(100, 400, "Right mouse click on the square that marks what you suspect is a mine to turn it red;");
		outtextxy(100, 450, "Right-click once more to restore the black color;");
		outtextxy(100, 500, "Knock out all the non-mine squares to win the final victory.");
	}
	else if (language == 3) {
		outtextxy(100, 200, "�\�����񡹤򥯥�å�����ȡ��ޥ����k�Ӥ��ޤ���");
		outtextxy(100, 250, "����å������Ȥ���M����ʾ���줿���Ϥϡ����פ����Ӥ��ƥ��`�४�`�Щ`�ˤʤä����Ȥ���ζ���ޤ���");
		outtextxy(100, 300, "���֤���ʾ���줿���ϡ��������֤ˌ��ꤹ����פ��������x�ˤ��뤳�Ȥ���ζ���ޤ���");
		outtextxy(100, 350, "�հפΈ��ϡ����פϤ���ޤ���");
		outtextxy(100, 400, "���פ�˼����ޥ���ޥ������ҥ���å��ǥީ`������ȳय�ʤ룻");
		outtextxy(100, 450, "�⤦һ���ҥ���å����\�ˑ��룻");
		outtextxy(100, 500, "���פΤʤ��ޥ��򤹤٤ƥȥꥬ�`�ˤ�����K�Ĥ˄������롣");
	}
	settextstyle(35, 0, "΢���ź�");
	creatRect(1100, 600, 55, 90, BLACK);
	if (language == 1)outtextxy(1110, 610, "����");
	else if (language == 2)outtextxy(1110, 610, "Back");
	else if (language == 3)outtextxy(1110, 610, "����");
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