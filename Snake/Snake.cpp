#include "stdafx.h"
#include "Snake.h"

wstring CSnake::Head = L"@";
wstring CSnake::Body = L"#";
wstring CSnake::Food = L"*";

float CSnake::Speed = 1.0;

CSnake::CSnake()
{
}


CSnake::~CSnake()
{
}

bool CSnake::Init()
{

	return false;
}

void CSnake::Draw()
{
	CConsole*  con = CSnakeGame::GetInstance()->GetConsole();

	for (auto const it : m_Snake)
	{
		//con->DrawPixel()
		con->DrawString(it.X, it.Y, CSnake::Head, STD_WHITE);
		con->DrawString(it.X, it.Y, CSnake::Body, STD_WHITE);
	}
}


