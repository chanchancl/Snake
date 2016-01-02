#pragma once


class CFood
{
public:
	CFood();
	~CFood();

public:
	bool Init();
	void Render();

	void RandomFood();
	COORD GetPosition();

private:
	SHORT m_X, m_Y;
};

