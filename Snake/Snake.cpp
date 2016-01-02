
#include "stdafx.h"
#include "Snake.h"

wstring CSnake::Head = L"@";
wstring CSnake::Body = L"#";
wstring CSnake::Food = L"*";

float CSnake::Speed = 1.0;
int   CSnake::InitLong = 3;

COORD GetVectorFromDir(CSnake::Dir dir,bool reversal = false)
{
	COORD cod = { 0,0 };
	switch (dir)
	{
	case CSnake::Left:
		cod.X = -1; cod.Y = 0;
		break;
	case CSnake::Up:
		cod.X = 0; cod.Y = 1;
		break;
	case CSnake::Right:
		cod.X = 1; cod.Y = 0;
		break;
	case CSnake::Down:
		cod.X = 0; cod.Y = -1;
		break;
	case CSnake::UnDefine:
	default:
		throw new std::exception("Get Undefine dir's vector.");
		break;
	}
	if (reversal)
	{
		cod.X = -cod.X; 
		cod.Y = -cod.Y;
	}
	return cod;
}
bool IsInGameRect(COORD cod)
{
	return (cod.X >= GameRect.Left && cod.X <= GameRect.Left) &&
		(cod.Y >= GameRect.Top && cod.Y <= GameRect.Bottom);
}

CSnake::CSnake() : m_Dir(UnDefine)
{
}

CSnake::~CSnake()
{
	m_lsBody.clear();
}

bool CSnake::Init()
{
	COORD cod = { (SHORT)RandomInt(GameRect.Left+5,GameRect.Right-5),
		(SHORT)RandomInt(GameRect.Top+5,GameRect.Bottom-5) };

	m_lsBody.push_back(cod);

	//随机产生朝向，并为生成身体做准备
	m_Dir = (Dir)RandomInt(0, 3);

	COORD v = GetVectorFromDir(m_Dir, true);

	// CSnake::InitLong 作用: 初始蛇的身长(包括头部)
	for (int index = 0; index < CSnake::InitLong; index++)
	{
		cod.X += v.X; cod.Y += v.Y;
		m_lsBody.push_back(cod);
	}

	return true;
}

void CSnake::Render()
{
	CConsole*  con = CSnakeGame::GetInstance()->GetConsole();

	bool first = true;
	for (auto const it : m_lsBody)
	{
		if (first)
		{
			first = false;
			con->DrawString(it.X, it.Y, CSnake::Head, STD_WHITE);
		}
		else
			con->DrawString(it.X, it.Y, CSnake::Body, STD_WHITE);
	}
}

bool CSnake::Exist(SHORT x, SHORT y)
{
	for (const auto& it : m_lsBody)
		if (it.X == x && it.Y == y)
			return true;
	return false;
}

bool CSnake::Advance()
{
	CFood *food = GameState::GetInstance()->GetFood();

	COORD cod = GetVectorFromDir(m_Dir);
	auto it = m_lsBody.begin();
	COORD newHead = { it->X + cod.X,it->Y + cod.Y };

	if (!IsInGameRect(newHead))
	{
		// you are die


		return false;
	}
	m_lsBody.push_front(newHead);

	if (food->GetPosition() == newHead)
		food->RandomFood();
	else
		m_lsBody.pop_back();

	return true;
}

void CSnake::ChangeDir(Dir dir)
{
	if (dir == Left)
	{
		m_Dir = (Dir)(m_Dir -1);
	}
	if (dir == Right)
	{
		m_Dir = (Dir)(m_Dir +1);
	}
	if (m_Dir == -1)
		m_Dir = Down;
	if (m_Dir == 4)
		m_Dir = Left;
}


