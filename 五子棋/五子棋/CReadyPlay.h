#pragma once
#include"CInitGame.h"
#include"CConfig.h"

typedef struct VECTOR {
	vector<int> x;
	vector<int> y;
};

// frame of reference ����
typedef struct FOR {
	int x;
	int y;
};

// �������
typedef struct MOUSES {
	int x;
	int y;
};


class CReadyPlay:public CInitGame
{
public:
	// �����־
	VECTOR pullBack;	// ��¼������һ�ºõ����ӵ����꣬�����ڻ���
	FOR fofr;			// ���ڸ�������
	MOUSES mouses;		// ��������
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

