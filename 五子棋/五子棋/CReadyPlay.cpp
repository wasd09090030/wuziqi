#include "CReadyPlay.h"
#include"CInitGame.h"


CReadyPlay::CReadyPlay() {
	Map[15][15] = {0};

}
CReadyPlay::~CReadyPlay() {

}


bool CReadyPlay::beginGame() {
	MOUSEMSG mouse;	// ������
	while (1) {
		mouse = GetMouseMsg();	// ����ϵͳ�ĺ���
		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
				return true;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
				return false;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
				if (gameMusicFlag) {
					gameMusicFlag = false;
					mciSendString(L"close Sunburst.mp3", NULL, 0, NULL);	// ��ͣ
				}
				else {
					gameMusicFlag = true;
					mciSendString(L"play Sunburst.mp3 repeat", 0, 0, 0);
				}
				continue;
			}
		}
		Sleep(10);
	}
}
void CReadyPlay::newGame() {
	// ���¿�ʼ��Ϸ
	gameInterface();  // ��ʼ����ͼ
	for (int i = 0; i < 15; i++) {	// ��ͼȫ����Ϊ��
		for (int j = 0; j < 15; j++) {
			Map[i][j] = 0;
		}
	}

	// ���¿�ʼ��Ϸ���������־���
	pullBack.x.clear();
	pullBack.y.capacity();

	// ���¿�ʼ��Ϸ֮�󣬻ָ������ȳ�
	player.black = 0;
	player.white = 1;
}
int CReadyPlay::ifbool() {
	MOUSEMSG mouse;	// ������
	while (1) {
		mouse = GetMouseMsg();	// ����ϵͳ�ĺ���
		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {	  // �������
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {	  // �ж����������Ƿ��ڸ�����
					if ((mouse.x >= i * 50 + PLATE_X - 15 && mouse.x <= i * 50 + PLATE_X + 15) &&
						(mouse.y >= j * 50 + PLATE_Y - 15 && mouse.y <= j * 50 + PLATE_Y + 15)) {
						// �����㣬������û������
						if (Map[i][j] == 0) {
							fofr.x = i;		// ���ڸ�������
							fofr.y = j;

							mouses.x = i * 50 + PLATE_X;	// ��������
							mouses.y = j * 50 + PLATE_Y;

							pullBack.x.push_back(i);	// ���ڻ���
							pullBack.y.push_back(j);
							return 1;
						}
						else {
							return 2;
						}
					}
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {	// ���¿�ʼ��Ϸ
						newGame();	// ���¿�ʼ��Ϸ����
						return 3;
					}
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 650 && mouse.y < 700)) {	// �������
						if (pullBack.x.size() > 0 && pullBack.y.size() > 0) {	// �����㣬˵�������Ӽ�¼�����Ի���
							int x = pullBack.x[pullBack.x.size() - 1];
							int y = pullBack.y[pullBack.y.size() - 1];

							// ɾ�������ϵ�һ�������¼
							pullBack.x.pop_back();
							pullBack.y.pop_back();

							Map[x][y] = 0;
							// ���¼�����Ϸ
							gameInterface();	// ��ʼ����ͼ

							for (int i = 0; i < 15; i++) {	// ����ͼ�ϵ����Ӱڻ���
								for (int j = 0; j < 15; j++) {
									if (Map[i][j] == 1) {
										loadimage(&imageWhite, _T("white.jpg"), 30, 30);
										putimage(i * 50 + PLATE_X - 15, j * 50 + PLATE_Y - 15, &imageWhite);

									}
									else if (Map[i][j] == 2) {
										loadimage(&imageBlack, _T("black.jpg"), 30, 30);
										putimage(i * 50 + PLATE_X - 15, j * 50 + PLATE_Y - 15, &imageBlack);
									}
								}
							}
							if (player.black == 1) {
								player.black = 0;
								player.white = 1;
							}
							else {
								player.black = 1;
								player.white = 0;
							}
							return 4;
						}
					}
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {		// �Ƴ���Ϸ����
					 // ��������
						closegraph();
						exit(1);
					}
				}
			}
		}
		Sleep(10);
	}
}
void CReadyPlay::playChess() {
	if (player.black) { // ���Ϊ��
		// Ԥ�ȼ���ͼƬ
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);

		// �������µ��������
		putimage(mouses.x - 15, mouses.y - 15, &imageBlack);
		player.black = 0;	// ����˳���־
		player.white = 1;	// ����˳���־
		Map[fofr.x][fofr.y] = 2;	// ��������
	}
	else {
		// Ԥ�ȼ���ͼƬ
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);

		// �������µ��������
		putimage(mouses.x - 15, mouses.y - 15, &imageWhite);
		player.black = 1;
		player.white = 0;
		Map[fofr.x][fofr.y] = 1;
	}
}
void CReadyPlay::hint() {
	// �����ʾ
	m_initgame.deleteHints();

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 3);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 50, 850, 150);

	// д��
	outtextxy(788, 52, _T("�˴�"));
	outtextxy(768, 80, _T("��������"));

	// ȷ�� ������ķ���
	rectangle(765, 110, 845, 145);

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// д��
	outtextxy(790, 115, _T("ȷ��"));

	MOUSEMSG mouse;	 // ������
	while (1) {
		mouse = GetMouseMsg();	//����ϵͳ�ĺ���
		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 765 && mouse.x < 845) && (mouse.y > 90 && mouse.y < 145)) {
				// �����ʾ
				m_initgame.deleteHints();
				break;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
				newGame();	// ���¿�ʼ��Ϸ����
				break;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
				// ��������
				closegraph();
				exit(1);
			}
		}
		Sleep(10);
	}
}
void playGames(void);
void CReadyPlay::Victory(int victory) {
	Sleep(300);
	settextstyle(77, 0, _T("����"));

	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));
	}
	else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));
	}
	else {
		outtextxy(200, 150, _T("���������⣡"));
	}

	// �����ʼ��Ϸ
	if (beginGame()) {
		newGame();	// ���¼�����Ϸ
		playGames();  // ����Ϸ
	}
	else {
		closegraph();
		exit(1);
	}
}
void CReadyPlay::ifVictory() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			// �����㷨����Ϸ�����ж�
			if ((Map[i][j] == 1 && Map[i - 1][j - 1] == 1 && Map[i - 2][j - 2] == 1 && Map[i - 3][j - 3] == 1 && Map[i - 4][j - 4] == 1) ||		// ���Ͻ�
				(Map[i][j] == 1 && Map[i + 1][j - 1] == 1 && Map[i + 2][j - 2] == 1 && Map[i + 3][j - 3] == 1 && Map[i + 4][j - 4] == 1) ||		// ���Ͻ�
				(Map[i][j] == 1 && Map[i - 1][j + 1] == 1 && Map[i - 2][j + 2] == 1 && Map[i - 3][j + 3] == 1 && Map[i - 4][j + 4] == 1) ||		// ���½�
				(Map[i][j] == 1 && Map[i + 1][j + 1] == 1 && Map[i + 2][j + 2] == 1 && Map[i + 3][j + 3] == 1 && Map[i + 4][j + 4] == 1) ||		// ���½�
				(Map[i][j] == 1 && Map[i][j - 1] == 1 && Map[i][j - 2] == 1 && Map[i][j - 3] == 1 && Map[i][j - 4] == 1) ||				// ��
				(Map[i][j] == 1 && Map[i][j + 1] == 1 && Map[i][j + 2] == 1 && Map[i][j + 3] == 1 && Map[i][j + 4] == 1) ||				// ��
				(Map[i][j] == 1 && Map[i - 1][j] == 1 && Map[i - 2][j] == 1 && Map[i - 3][j] == 1 && Map[i - 4][j] == 1) ||				// ��
				(Map[i][j] == 1 && Map[i + 1][j] == 1 && Map[i + 2][j] == 1 && Map[i + 3][j] == 1 && Map[i + 4][j] == 1)) {				// ��
				Victory(1);		// ִ��ʤ������
			}
			else if ((Map[i][j] == 2 && Map[i - 1][j - 1] == 2 && Map[i - 2][j - 2] == 2 && Map[i - 3][j - 3] == 2 && Map[i - 4][j - 4] == 2) ||		// ���Ͻ�
				(Map[i][j] == 2 && Map[i + 1][j - 1] == 2 && Map[i + 2][j - 2] == 2 && Map[i + 3][j - 3] == 2 && Map[i + 4][j - 4] == 2) ||		// ���Ͻ�
				(Map[i][j] == 2 && Map[i - 1][j + 1] == 2 && Map[i - 2][j + 2] == 2 && Map[i - 3][j + 3] == 2 && Map[i - 4][j + 4] == 2) ||		// ���½�
				(Map[i][j] == 2 && Map[i + 1][j + 1] == 2 && Map[i + 2][j + 2] == 2 && Map[i + 3][j + 3] == 2 && Map[i + 4][j + 4] == 2) ||		// ���½�
				(Map[i][j] == 2 && Map[i][j - 1] == 2 && Map[i][j - 2] == 2 && Map[i][j - 3] == 2 && Map[i][j - 4] == 2) ||				// ��
				(Map[i][j] == 2 && Map[i][j + 1] == 2 && Map[i][j + 2] == 2 && Map[i][j + 3] == 2 && Map[i][j + 4] == 2) ||				// ��
				(Map[i][j] == 2 && Map[i - 1][j] == 2 && Map[i - 2][j] == 2 && Map[i - 3][j] == 2 && Map[i - 4][j] == 2) ||				// ��
				(Map[i][j] == 2 && Map[i + 1][j] == 2 && Map[i + 2][j] == 2 && Map[i + 3][j] == 2 && Map[i + 4][j] == 2)) {				// ��
				Victory(2);		// ִ��ʤ������
			}
		}
	}
}

void CReadyPlay::playGames() {
	while (1) {
		gamePlayerShow();		// ѡ��������ʾ	
		int keyword = ifbool();	// ���������

		if (keyword == 1) {
			playChess();	// ����
			ifVictory();	// �ж��Ƿ����������һ��������
		}
		else if (keyword == 2) {
			hint();			// ��ʾ�ô���������
		}
		else if (keyword == 3) {
			// ��ִ�н������¼��أ������ʼ��Ϸ��ʾ
			deleteHints();
		}
		else if (keyword == 4) {
			// ��ִ�н������¼��أ������ʼ��Ϸ��ʾ
			deleteHints();
		}
	}
}