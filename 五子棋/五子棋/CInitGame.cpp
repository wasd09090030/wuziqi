#include "CInitGame.h"
#include "CConfig.h"


CInitGame::CInitGame() {
	gameMusicFlag = true;
}
CInitGame::~CInitGame() {

}

void CInitGame::initgraphGame() {

	// 初始化图像界面
	initgraph(1080, 720);

	// 将图片应用于界面中
	loadimage(0, _T("begin-1.jpg"));

	// 设置字体颜色
	settextcolor(RGB(255, 255, 255));

	// 设置字体
	settextstyle(35, 0, _T("楷体"));

	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	// 写字
	outtextxy(415, 60, _T("游戏正在加载中......"));

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 5);

	// 画一个空心矩形
	rectangle(220, 195, 820, 305);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(120, 0, _T("微软雅黑"));

	// 写字
	outtextxy(244, 190, _T("哈 哈 五 子 棋"));

	// 设置字体颜色
	settextcolor(RGB(255, 200, 88));

	// 写字
	outtextxy(110, 410, _T("欢迎来到五子棋游戏"));

	Sleep(3000);
	closegraph();
}


void CInitGame::plate() {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	for (int i = 0; i < 13; i++) {
		//	固定值加上一个偏移量
		line(PLATE_X, PLATE_Y + (OFFSET * (i + 1)), PLATE_XX, PLATE_Y + (OFFSET * (i + 1)));	// 行
		line(PLATE_X + (OFFSET * (i + 1)), PLATE_Y, PLATE_X + (OFFSET * (i + 1)), PLATE_YY);	// 纵
	}
}
void CInitGame::gameButton() {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(255, 0, 0));

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 175, 850, 225);

	// 写字
	outtextxy(767, 185, _T("音乐开关"));

	// 字体外的方框
	rectangle(760, 250, 850, 300);

	// 写字
	outtextxy(767, PLATE_Y * 5 + 10, _T("开始游戏"));

	// 字体外的方框
	rectangle(760, 450, 850, 500);

	// 写字
	outtextxy(767, 460, _T("结束游戏"));

	// 字体外的方框
	rectangle(760, 650, 850, 700);

	// 设置字体颜色
	settextcolor(RGB(255, 0, 0));

	// 写字
	outtextxy(785, 662, _T("悔棋"));

	// 设置字体
	settextstyle(30, 0, _T("微软雅黑"));

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 五子棋
	outtextxy(700 / 2, 10, _T("五子棋"));
}
void CInitGame::gameHints() {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(28, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 50, 850, 150);

	// 写字	
	outtextxy(775, 65, _T("请点击"));
	outtextxy(763, 100, _T("开始游戏"));
}
void CInitGame::deleteHints() {
	IMAGE image;
	loadimage(&image, _T("cheng.jpg"));
	putimage(758, 48, &image);
}
void CInitGame::gameInterface() {
	mciSendString(L"play Sunburst.mp3 repeat", 0, 0, 0);  //unicode字符集要加 L


	// 初始化图像界面
	initgraph(GRAPHICS_X, GRAPHICS_Y);

	// 设置图像的背景颜色
	setbkcolor(RGB(255, 200, 88));
	// 应用到图像中
	cleardevice();

	// 设置画笔颜色
	setlinecolor(RGB(0, 0, 0));

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 3);

	// 画一个空心矩形
	rectangle(PLATE_X, PLATE_Y, PLATE_XX, PLATE_YY);

	// 画棋板
	plate();

	// 游戏按钮
	gameButton();

	// 开始游戏提示
	gameHints();
}


void CInitGame::gamePlayerShow() {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体
	settextstyle(30, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(750, 40, 860, 160);

	// 清除提示
	deleteHints();

	if (player.white) {
		// 设置字体颜色
		settextcolor(RGB(255, 255, 255));

		// 写字
		outtextxy(780, 52, _T("白方"));
		outtextxy(780, 80, _T("下棋"));

		// 预先加载图片
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);

		// 显示棋子
		putimage(790, 110, &imageWhite);
	}
	else if (player.black) {
		// 设置字体颜色
		settextcolor(RGB(0, 0, 0));

		// 写字
		outtextxy(780, 52, _T("黑方"));
		outtextxy(780, 80, _T("下棋"));

		// 预先加载图片
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);

		// 显示棋子
		putimage(790, 110, &imageBlack);
	}
	else {
		outtextxy(780, 52, _T("第三方"));
		outtextxy(780, 80, _T("下棋"));
	}
}