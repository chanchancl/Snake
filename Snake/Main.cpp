// Snake.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	CSnakeGame *game = CSnakeGame::GetInstance();
	game->Init();
	CConsole &con = *game->GetConsole();
	con.Init();
	game->GetConsole()->SetCursorVisible(false);
	game->DrawContent();
	game->DrawMenu();

	CTimer timer(30);
	while (timer)
	{
		
		
		
	}

	
    return 0;
}

