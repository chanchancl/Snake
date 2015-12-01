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
	//ҵ���߼�
	// ����ֵ true  ��ʾ�ɹ�ǰ��
	//        false ��ʾʧ��
	//bool Advance();


public:
	static wstring Head;
	static wstring Body;
	static wstring Food;
	static float   Speed;

	Dir m_Dir;
	list<COORD> m_Snake;
};

