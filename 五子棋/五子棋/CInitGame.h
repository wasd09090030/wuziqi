#pragma once
#include <iostream>
#include <Windows.h>
#include <easyx.h>
#include <graphics.h>	// ͼ�ο�
#include <vector>		// ��̬���飬�õط����ڻ���
#include<mmsystem.h>   
#pragma comment(lib,"winmm.lib")	// ���� winmm.lid ���ļ�
using namespace std;

// ��Ϸѡ��
typedef struct PLAYER {
	int white;
	int black;
};

class CInitGame
{
public:
	IMAGE m_imgBack;
	IMAGE imageBlack;	// ����ͼƬ�洢����
	IMAGE imageWhite;	// ����ͼƬ�洢����
	PLAYER player;		// �������Ͻ���ʾѡ������
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

