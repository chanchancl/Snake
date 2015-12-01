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
	game->DrawMenu();
	while (true)
	{
		//game->Run();
		game->DrawContent();
		
		if (con.IsKeyDown('a'))
			cout << "a  is down" << endl;
		else
			Sleep(1);
	}

	
    return 0;
}

