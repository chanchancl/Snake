#pragma once

#define ST_MENU		1
#define ST_GAMING	2
#define ST_PAUSE	3
#define ST_GAMEOVER	4

namespace state 
{
	class CStateMachine;
}
class CSnake;

using namespace state;

class CSnakeGame
{
private:
	//禁止外部通过构造函数创建这个类的实例
	CSnakeGame();
public:
	~CSnakeGame();

public:
	bool Init();


	CStateMachine* GetStateMachine();
	CConsole* GetConsole();
	static CSnakeGame* GetInstance();

private:
	CConsole *m_Console;
	CSnake	 *m_Snake;
	CStateMachine *m_StateMachine;

	bool m_bNeedToRender;

	static CSnakeGame *pInstance;
};


