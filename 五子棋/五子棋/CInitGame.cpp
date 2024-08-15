#include "CInitGame.h"
#include "CConfig.h"


CInitGame::CInitGame() {
	gameMusicFlag = true;
}
CInitGame::~CInitGame() {

}

void CInitGame::initgraphGame() {

	// ��ʼ��ͼ�����
	initgraph(1080, 720);

	// ��ͼƬӦ���ڽ�����
	loadimage(0, _T("begin-1.jpg"));

	// ����������ɫ
	settextcolor(RGB(255, 255, 255));

	// ��������
	settextstyle(35, 0, _T("����"));

	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	// д��
	outtextxy(415, 60, _T("��Ϸ���ڼ�����......"));

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 5);

	// ��һ�����ľ���
	rectangle(220, 195, 820, 305);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(120, 0, _T("΢���ź�"));

	// д��
	outtextxy(244, 190, _T("�� �� �� �� ��"));

	// ����������ɫ
	settextcolor(RGB(255, 200, 88));

	// д��
	outtextxy(110, 410, _T("��ӭ������������Ϸ"));

	Sleep(3000);
	closegraph();
}


void CInitGame::plate() {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	for (int i = 0; i < 13; i++) {
		//	�̶�ֵ����һ��ƫ����
		line(PLATE_X, PLATE_Y + (OFFSET * (i + 1)), PLATE_XX, PLATE_Y + (OFFSET * (i + 1)));	// ��
		line(PLATE_X + (OFFSET * (i + 1)), PLATE_Y, PLATE_X + (OFFSET * (i + 1)), PLATE_YY);	// ��
	}
}
void CInitGame::gameButton() {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(255, 0, 0));

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 175, 850, 225);

	// д��
	outtextxy(767, 185, _T("���ֿ���"));

	// ������ķ���
	rectangle(760, 250, 850, 300);

	// д��
	outtextxy(767, PLATE_Y * 5 + 10, _T("��ʼ��Ϸ"));

	// ������ķ���
	rectangle(760, 450, 850, 500);

	// д��
	outtextxy(767, 460, _T("������Ϸ"));

	// ������ķ���
	rectangle(760, 650, 850, 700);

	// ����������ɫ
	settextcolor(RGB(255, 0, 0));

	// д��
	outtextxy(785, 662, _T("����"));

	// ��������
	settextstyle(30, 0, _T("΢���ź�"));

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ������
	outtextxy(700 / 2, 10, _T("������"));
}
void CInitGame::gameHints() {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(28, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 50, 850, 150);

	// д��	
	outtextxy(775, 65, _T("����"));
	outtextxy(763, 100, _T("��ʼ��Ϸ"));
}
void CInitGame::deleteHints() {
	IMAGE image;
	loadimage(&image, _T("cheng.jpg"));
	putimage(758, 48, &image);
}
void CInitGame::gameInterface() {
	mciSendString(L"play Sunburst.mp3 repeat", 0, 0, 0);  //unicode�ַ���Ҫ�� L


	// ��ʼ��ͼ�����
	initgraph(GRAPHICS_X, GRAPHICS_Y);

	// ����ͼ��ı�����ɫ
	setbkcolor(RGB(255, 200, 88));
	// Ӧ�õ�ͼ����
	cleardevice();

	// ���û�����ɫ
	setlinecolor(RGB(0, 0, 0));

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 3);

	// ��һ�����ľ���
	rectangle(PLATE_X, PLATE_Y, PLATE_XX, PLATE_YY);

	// �����
	plate();

	// ��Ϸ��ť
	gameButton();

	// ��ʼ��Ϸ��ʾ
	gameHints();
}


void CInitGame::gamePlayerShow() {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ��������
	settextstyle(30, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(750, 40, 860, 160);

	// �����ʾ
	deleteHints();

	if (player.white) {
		// ����������ɫ
		settextcolor(RGB(255, 255, 255));

		// д��
		outtextxy(780, 52, _T("�׷�"));
		outtextxy(780, 80, _T("����"));

		// Ԥ�ȼ���ͼƬ
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);

		// ��ʾ����
		putimage(790, 110, &imageWhite);
	}
	else if (player.black) {
		// ����������ɫ
		settextcolor(RGB(0, 0, 0));

		// д��
		outtextxy(780, 52, _T("�ڷ�"));
		outtextxy(780, 80, _T("����"));

		// Ԥ�ȼ���ͼƬ
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);

		// ��ʾ����
		putimage(790, 110, &imageBlack);
	}
	else {
		outtextxy(780, 52, _T("������"));
		outtextxy(780, 80, _T("����"));
	}
}