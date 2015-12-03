#pragma once

#define ST_MENU		1
#define ST_GAMING	2
#define ST_PAUSE	3
#define ST_GAMEOVER	4



class CSnakeGame
{
private:
	//禁止外部通过构造函数创建这个类的实例
	CSnakeGame();
public:
	~CSnakeGame();

public:
	bool Init();
	bool Run();
	bool Render();
	void NeedToRender();

	void DrawContent();
	void OnMenu();

	void SetGameState(UINT state);

	CConsole* GetConsole();

	static CSnakeGame* GetInstance();

	UINT m_uChoose;
private:
	CConsole *m_Console;
	CSnake	 *m_Snake;

	//  Menu
	//  Gaming
	//  Pause
	//  GameOver
	UINT m_uState;
	

	bool m_bNeedToRender;

	static CSnakeGame *pInstance;
};


