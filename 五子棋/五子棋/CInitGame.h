#pragma once
#include <iostream>
#include <Windows.h>
#include <easyx.h>
#include <graphics.h>	// 图形库
#include <vector>		// 动态数组，该地方用于悔棋
#include<mmsystem.h>   
#pragma comment(lib,"winmm.lib")	// 加载 winmm.lid 库文件
using namespace std;

// 游戏选手
typedef struct PLAYER {
	int white;
	int black;
};

class CInitGame
{
public:
	IMAGE m_imgBack;
	IMAGE imageBlack;	// 黑棋图片存储变量
	IMAGE imageWhite;	// 白棋图片存储变量
	PLAYER player;		// 用于左上角提示选手下棋
	bool gameMusicFlag;
public:
	CInitGame();
	~CInitGame();
public:
	void initgraphGame();
	void plate();
	void gameButton();
	void gameHints();
	void deleteHints();
	void gameInterface();
	void gamePlayerShow();
};

