#include "stdafx.h"
#include "SnakeGame.h"
#include <algorithm>


CSnakeGame* CSnakeGame::pInstance = nullptr;

CSnakeGame::CSnakeGame() : m_Console(nullptr)
{
}


CSnakeGame::~CSnakeGame()
{
	if (m_Console)
	{
		delete m_Console;
		m_Console = nullptr;
	}
}

bool CSnakeGame::Init()
{
	m_Console = CConsole::GetInstance();
	if (!m_Console && !m_Console->Init())
	{
		//Console 创建 或 初始化错误
		return false;
	}
	m_Snake = new CSnake;
	if (!m_Snake)
		return false;

	SetGameState(ST_MENU);


	return true;
}

bool CSnakeGame::Run()
{
	//m_Snake->Updata();
	switch (m_iState)
	{
	case ST_MENU:
		DrawMenu();
		break;


	default:
		break;
	}
	

	Render();
	return true;
}

bool CSnakeGame::Render()
{
	DrawContent();
	m_Snake->Draw();
	//DrawFood();

	return false;
}


void CSnakeGame::DrawContent()
{
	int x, y;
	for (x = 1; x <= 80; ++x)
		m_Console->DrawPixel(x, 1,STD_GREEN);
	for (y = 1; y <= 24; ++y)
	{
		m_Console->DrawPixel(1, y, STD_GREEN);
		m_Console->DrawPixel(2, y, STD_GREEN);
		m_Console->DrawPixel(79, y, STD_GREEN);
		m_Console->DrawPixel(80, y, STD_GREEN);
	}
	for (x = 1; x <= 80; ++x)
		m_Console->DrawPixel(x, 25, STD_GREEN);
}

void CSnakeGame::DrawMenu()
{
	
	wstring title = L"贪吃蛇";
	m_Console->DrawString((80 - (SHORT)title.size()) / 2-1, 25 * 1 / 3, title, STD_WHITE);
	wstring text[] = {
		L"【开始】",
		L"【退出】"
	};


	int sub = 10;
	int l = text[0].size() + text[1].size() + sub;

	m_Console->DrawString((80 - l) / 2, 25 * 2 / 3, text[0],STD_WHITE);
	m_Console->DrawLineX((80 - l) / 2+1, (80 - l) / 2 + (SHORT)text[0].size()*2-1,25*2/3, STD_RED);
	m_Console->DrawString((80 - l) / 2 + sub, 25 * 2 / 3, text[1],STD_WHITE);
	
}

void CSnakeGame::SetGameState(UINT state)
{
	m_iState = state;
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

