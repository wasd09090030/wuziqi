#include "CReadyPlay.h"
#include"CInitGame.h"


CReadyPlay::CReadyPlay() {
	Map[15][15] = {0};

}
CReadyPlay::~CReadyPlay() {

}


bool CReadyPlay::beginGame() {
	MOUSEMSG mouse;	// 鼠标变量
	while (1) {
		mouse = GetMouseMsg();	// 调用系统的函数
		// 如果有鼠标左键点击操作
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
					mciSendString(L"close Sunburst.mp3", NULL, 0, NULL);	// 暂停
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
	// 重新开始游戏
	gameInterface();  // 初始化地图
	for (int i = 0; i < 15; i++) {	// 地图全部置为零
		for (int j = 0; j < 15; j++) {
			Map[i][j] = 0;
		}
	}

	// 重新开始游戏，将悔棋标志清空
	pullBack.x.clear();
	pullBack.y.capacity();

	// 重新开始游戏之后，恢复白棋先出
	player.black = 0;
	player.white = 1;
}
int CReadyPlay::ifbool() {
	MOUSEMSG mouse;	// 鼠标变量
	while (1) {
		mouse = GetMouseMsg();	// 调用系统的函数
		// 如果有鼠标左键点击操作
		if (mouse.uMsg == WM_LBUTTONDOWN) {	  // 下棋操作
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {	  // 判断鼠标的坐标是否在该区域
					if ((mouse.x >= i * 50 + PLATE_X - 15 && mouse.x <= i * 50 + PLATE_X + 15) &&
						(mouse.y >= j * 50 + PLATE_Y - 15 && mouse.y <= j * 50 + PLATE_Y + 15)) {
						// 等于零，该区域没有棋子
						if (Map[i][j] == 0) {
							fofr.x = i;		// 用于更新数组
							fofr.y = j;

							mouses.x = i * 50 + PLATE_X;	// 用于下棋
							mouses.y = j * 50 + PLATE_Y;

							pullBack.x.push_back(i);	// 用于悔棋
							pullBack.y.push_back(j);
							return 1;
						}
						else {
							return 2;
						}
					}
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {	// 重新开始游戏
						newGame();	// 重新开始游戏函数
						return 3;
					}
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 650 && mouse.y < 700)) {	// 悔棋操作
						if (pullBack.x.size() > 0 && pullBack.y.size() > 0) {	// 大于零，说明有棋子记录，可以悔棋
							int x = pullBack.x[pullBack.x.size() - 1];
							int y = pullBack.y[pullBack.y.size() - 1];

							// 删除容器上的一个悔棋记录
							pullBack.x.pop_back();
							pullBack.y.pop_back();

							Map[x][y] = 0;
							// 重新加载游戏
							gameInterface();	// 初始化地图

							for (int i = 0; i < 15; i++) {	// 将地图上的棋子摆回来
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
					else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {		// 推出游戏操作
					 // 结束程序
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
	if (player.black) { // 如果为真
		// 预先加载图片
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);

		// 将棋子下到棋板上面
		putimage(mouses.x - 15, mouses.y - 15, &imageBlack);
		player.black = 0;	// 下棋顺序标志
		player.white = 1;	// 下棋顺序标志
		Map[fofr.x][fofr.y] = 2;	// 更新数组
	}
	else {
		// 预先加载图片
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);

		// 将棋子下到棋板上面
		putimage(mouses.x - 15, mouses.y - 15, &imageWhite);
		player.black = 1;
		player.white = 0;
		Map[fofr.x][fofr.y] = 1;
	}
}
void CReadyPlay::hint() {
	// 清除提示
	m_initgame.deleteHints();

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 3);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 50, 850, 150);

	// 写字
	outtextxy(788, 52, _T("此处"));
	outtextxy(768, 80, _T("已有棋子"));

	// 确认 字体外的方框
	rectangle(765, 110, 845, 145);

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 写字
	outtextxy(790, 115, _T("确认"));

	MOUSEMSG mouse;	 // 鼠标变量
	while (1) {
		mouse = GetMouseMsg();	//调用系统的函数
		// 如果有鼠标左键点击操作
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 765 && mouse.x < 845) && (mouse.y > 90 && mouse.y < 145)) {
				// 清除提示
				m_initgame.deleteHints();
				break;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
				newGame();	// 重新开始游戏函数
				break;
			}
			else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
				// 结束程序
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
	settextstyle(77, 0, _T("宋体"));

	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("恭喜白棋获胜"));
	}
	else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("恭喜黑棋获胜"));
	}
	else {
		outtextxy(200, 150, _T("参数有问题！"));
	}

	// 点击开始游戏
	if (beginGame()) {
		newGame();	// 重新加载游戏
		playGames();  // 玩游戏
	}
	else {
		closegraph();
		exit(1);
	}
}
void CReadyPlay::ifVictory() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			// 核心算法，游戏棋子判断
			if ((Map[i][j] == 1 && Map[i - 1][j - 1] == 1 && Map[i - 2][j - 2] == 1 && Map[i - 3][j - 3] == 1 && Map[i - 4][j - 4] == 1) ||		// 左上角
				(Map[i][j] == 1 && Map[i + 1][j - 1] == 1 && Map[i + 2][j - 2] == 1 && Map[i + 3][j - 3] == 1 && Map[i + 4][j - 4] == 1) ||		// 右上角
				(Map[i][j] == 1 && Map[i - 1][j + 1] == 1 && Map[i - 2][j + 2] == 1 && Map[i - 3][j + 3] == 1 && Map[i - 4][j + 4] == 1) ||		// 左下角
				(Map[i][j] == 1 && Map[i + 1][j + 1] == 1 && Map[i + 2][j + 2] == 1 && Map[i + 3][j + 3] == 1 && Map[i + 4][j + 4] == 1) ||		// 右下角
				(Map[i][j] == 1 && Map[i][j - 1] == 1 && Map[i][j - 2] == 1 && Map[i][j - 3] == 1 && Map[i][j - 4] == 1) ||				// 上
				(Map[i][j] == 1 && Map[i][j + 1] == 1 && Map[i][j + 2] == 1 && Map[i][j + 3] == 1 && Map[i][j + 4] == 1) ||				// 下
				(Map[i][j] == 1 && Map[i - 1][j] == 1 && Map[i - 2][j] == 1 && Map[i - 3][j] == 1 && Map[i - 4][j] == 1) ||				// 左
				(Map[i][j] == 1 && Map[i + 1][j] == 1 && Map[i + 2][j] == 1 && Map[i + 3][j] == 1 && Map[i + 4][j] == 1)) {				// 右
				Victory(1);		// 执行胜利代码
			}
			else if ((Map[i][j] == 2 && Map[i - 1][j - 1] == 2 && Map[i - 2][j - 2] == 2 && Map[i - 3][j - 3] == 2 && Map[i - 4][j - 4] == 2) ||		// 左上角
				(Map[i][j] == 2 && Map[i + 1][j - 1] == 2 && Map[i + 2][j - 2] == 2 && Map[i + 3][j - 3] == 2 && Map[i + 4][j - 4] == 2) ||		// 右上角
				(Map[i][j] == 2 && Map[i - 1][j + 1] == 2 && Map[i - 2][j + 2] == 2 && Map[i - 3][j + 3] == 2 && Map[i - 4][j + 4] == 2) ||		// 左下角
				(Map[i][j] == 2 && Map[i + 1][j + 1] == 2 && Map[i + 2][j + 2] == 2 && Map[i + 3][j + 3] == 2 && Map[i + 4][j + 4] == 2) ||		// 右下角
				(Map[i][j] == 2 && Map[i][j - 1] == 2 && Map[i][j - 2] == 2 && Map[i][j - 3] == 2 && Map[i][j - 4] == 2) ||				// 上
				(Map[i][j] == 2 && Map[i][j + 1] == 2 && Map[i][j + 2] == 2 && Map[i][j + 3] == 2 && Map[i][j + 4] == 2) ||				// 下
				(Map[i][j] == 2 && Map[i - 1][j] == 2 && Map[i - 2][j] == 2 && Map[i - 3][j] == 2 && Map[i - 4][j] == 2) ||				// 左
				(Map[i][j] == 2 && Map[i + 1][j] == 2 && Map[i + 2][j] == 2 && Map[i + 3][j] == 2 && Map[i + 4][j] == 2)) {				// 右
				Victory(2);		// 执行胜利代码
			}
		}
	}
}

void CReadyPlay::playGames() {
	while (1) {
		gamePlayerShow();		// 选手下棋提示	
		int keyword = ifbool();	// 鼠标点击棋盘

		if (keyword == 1) {
			playChess();	// 下棋
			ifVictory();	// 判断是否下完了五个一样的棋子
		}
		else if (keyword == 2) {
			hint();			// 提示该处已有棋子
		}
		else if (keyword == 3) {
			// 已执行界面重新加载，清楚开始游戏提示
			deleteHints();
		}
		else if (keyword == 4) {
			// 已执行界面重新加载，清楚开始游戏提示
			deleteHints();
		}
	}
}