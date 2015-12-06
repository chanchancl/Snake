#include "stdafx.h"
#include "SnakeGame.h"
#include <algorithm>


CSnakeGame* CSnakeGame::pInstance = nullptr;

CSnakeGame::CSnakeGame() : m_Console(nullptr), m_Snake(nullptr), m_bNeedToRender(true)
{
}


CSnakeGame::~CSnakeGame()
{
	if (m_Console)
	{
		delete m_Console;
		m_Console = nullptr;
	}
	if (pInstance)
		pInstance = nullptr;

}

bool CSnakeGame::Init()
{
	m_Console = CConsole::GetInstance();
	if (!m_Console && !m_Console->Init())
	{
		//Console 创建 或 初始化错误
		return false;
	}
	
	/*
	//创建蛇，但不初始化
	m_Snake = new CSnake;
	if (!m_Snake)
		return false;*/

	//进入游戏， 目录状态
	//SetGameState(ST_MENU);
	m_StateMachine = new CStateMachine;
	m_StateMachine->ChangeState(MenuState::GetInstance());
	

	return true;
}

CStateMachine * CSnakeGame::GetStateMachine()
{
	return m_StateMachine;
}

CConsole* CSnakeGame::GetConsole()
{
	return m_Console != nullptr ? m_Console : nullptr;
}

CSnakeGame * CSnakeGame::GetInstance()
{
	if (!pInstance)
	{
		CSnakeGame* game = new CSnakeGame;
		if (game)
			return pInstance = game;
	}
	return pInstance;
}

