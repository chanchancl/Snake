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
	game->DrawContent();
	game->OnMenu();

	CTimer timer(30);
	while (timer)
	{
		game->OnMenu();
		/*if (con.IsKeyDown(VK_LEFT))
		{
			cout << "Left is down" << endl;
		}
		else
			Sleep(1);*/
		
	}

	
    return 0;
}

