// Snake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int main()
{
	
	CSnakeGame *game = CSnakeGame::GetInstance();
	game->Init();
	CConsole &con = *game->GetConsole();
	con.Init();
	game->GetConsole()->SetCursorVisible(false);

	CTimer timer(30);
	while (timer)
	{
		
	}

    return 0;
}

