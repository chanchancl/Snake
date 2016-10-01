#include "stdafx.h"
#include "SnakeGame.h"


CSnakeGame* CSnakeGame::pInstance = nullptr;

CSnakeGame::CSnakeGame() : m_Console(nullptr), m_bNeedToRender(true)
{
}

CSnakeGame::~CSnakeGame()
{
	SAFE_DELETE(m_Console)
	SAFE_DELETE(m_StateMachine)
	if (pInstance)
		pInstance = nullptr;

}

bool CSnakeGame::Init()
{
	m_Console = CConsole::GetInstance();
	m_Console->Init();

	//进入游戏， 目录状态
	//SetGameState(ST_MENU);
	m_StateMachine = new CStateMachine;
	m_StateMachine->ChangeState(MenuState::GetInstance());
	

	return true;
}

void CSnakeGame::Run()
{
	State *currentState = GetStateMachine()->GetCurrState();

	if (!currentState)
		return;

    

	currentState->Input();
	currentState->Update();
	currentState->Render();
    
    currentState->DrawContent();
	
    SetNeedRender(false);
}

bool CSnakeGame::IsNeedRender()
{
	return m_bNeedToRender;
}

void CSnakeGame::SetNeedRender(bool render)
{
	m_bNeedToRender = render;
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

