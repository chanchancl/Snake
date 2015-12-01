#pragma once

#include <list>
using std::list;

class CSnake
{
public:
	CSnake();
	~CSnake();

	typedef int Dir;

public:
	bool Init();
	void Draw();

public:
	//业务逻辑
	// 返回值 true  表示成功前进
	//        false 表示失败
	//bool Advance();


public:
	static wstring Head;
	static wstring Body;
	static wstring Food;
	static float   Speed;

	Dir m_Dir;
	list<COORD> m_Snake;
};

