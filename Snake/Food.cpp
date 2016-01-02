#include "stdafx.h"
#include "Food.h"

CFood::CFood() : m_X(0),m_Y(0)
{
}


CFood::~CFood()
{
}

bool CFood::Init()
{
	RandomFood();
	return true;
}

void CFood::Render()
{
	CConsole *con = CConsole::GetInstance();
	con->DrawString(m_X, m_Y, CSnake::Food, STD_RED);
}

void CFood::RandomFood()
{
	CSnake *snake = GameState::GetInstance()->GetSnake();
	// 找一个"没有蛇"的地方 233333
	do
	{
		m_X = RandomInt(GameRect.Left, GameRect.Right);
		m_Y = RandomInt(GameRect.Top, GameRect.Bottom);
	} while (snake->Exist(m_X, m_Y));
}

COORD CFood::GetPosition()
{
	COORD cod = { m_X,m_Y };
	return cod;
}
