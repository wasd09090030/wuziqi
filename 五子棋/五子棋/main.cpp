#include <iostream>
#include <Windows.h>
#include <graphics.h>	// ͼ�ο�
#include <vector>		// ��̬���飬�õط����ڻ���
#pragma comment(lib,"winmm.lib")	// ���� winmm.lid ���ļ�
using namespace std;

#include"CReadyPlay.h"

int main() {
	CInitGame m_Init;
	CReadyPlay m_Ready;

	// ��ɫΪ1����������
	m_Ready.player.black = 0;
	m_Ready.player.white = 1;

	// ������Ϸ
	m_Init.initgraphGame();

	// ��Ϸ����
	m_Ready.gameInterface();

	// ��ʼ��Ϸ
	if (m_Ready.beginGame()) {
		m_Ready.playGames();	// ����Ϸ
	}


}