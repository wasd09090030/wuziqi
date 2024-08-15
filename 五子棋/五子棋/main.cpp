#include <iostream>
#include <Windows.h>
#include <graphics.h>	// 图形库
#include <vector>		// 动态数组，该地方用于悔棋
#pragma comment(lib,"winmm.lib")	// 加载 winmm.lid 库文件
using namespace std;

#include"CReadyPlay.h"

int main() {
	CInitGame m_Init;
	CReadyPlay m_Ready;

	// 白色为1，白棋先手
	m_Ready.player.black = 0;
	m_Ready.player.white = 1;

	// 加载游戏
	m_Init.initgraphGame();

	// 游戏界面
	m_Ready.gameInterface();

	// 开始游戏
	if (m_Ready.beginGame()) {
		m_Ready.playGames();	// 玩游戏
	}


}