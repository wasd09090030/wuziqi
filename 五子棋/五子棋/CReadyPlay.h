#pragma once
#include"CInitGame.h"
#include"CConfig.h"

typedef struct VECTOR {
	vector<int> x;
	vector<int> y;
};

// frame of reference 坐标
typedef struct FOR {
	int x;
	int y;
};

// 鼠标坐标
typedef struct MOUSES {
	int x;
	int y;
};


class CReadyPlay:public CInitGame
{
public:
	// 悔棋标志
	VECTOR pullBack;	// 记录棋盘上一下好的棋子的坐标，好用于悔棋
	FOR fofr;			// 用于更新数组
	MOUSES mouses;		// 用于下棋
	int Map[15][15];
public:
	CInitGame m_initgame;
public:
	CReadyPlay();
	~CReadyPlay();
public:
	bool beginGame();
	void newGame();
	int ifbool();
	void playChess();
	void hint();
	void Victory(int victory);
	void ifVictory();
	void playGames();
};

