#pragma once

#include <list>
using std::list;

class CSnake
{
public:
	CSnake();
	~CSnake();

	enum Dir
	{
		Left,
		Up,
		Right,
		Down,
		UnDefine=-0xff,
	};

public:
	bool Init();
	void Render();

	bool Exist(SHORT x, SHORT y);
public:
	bool Advance();
	void ChangeDir(Dir dir);


public:
	static wstring Head;
	static wstring Body;
	static wstring Food;
	static float   Speed;
	static int	   InitLong;

	Dir m_Dir;
	list<COORD> m_lsBody;
};

