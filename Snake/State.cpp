#include "stdafx.h"
#include "State.h"

#include <time.h>
//

namespace state
{
	// define static class'member
	MenuState* MenuState::pInstance = nullptr;
	GameState* GameState::pInstance = nullptr;

	void State::DrawContent()
	{
		CConsole *con = CConsole::GetInstance();

		con->DrawLineX(1, 80, 1, STD_GREEN);
		con->DrawLineX(1, 80, 25, STD_GREEN);
		con->DrawLineY(1, 2, 24, STD_GREEN);
		con->DrawLineY(2, 2, 24, STD_GREEN);
		con->DrawLineY(79, 2, 24, STD_GREEN);
		con->DrawLineY(80, 2, 24, STD_GREEN);

	}

	void MenuState::Input()
	{
		CConsole *con = CConsole::GetInstance();
		if (con->IsKeyDown(VK_LEFT))
		{
			if (iChoose > 1)
				iChoose--;
		}
		if (con->IsKeyDown(VK_RIGHT))
		{
			if (iChoose < 2)
				iChoose++;
		}
		if (con->IsKeyDown(VK_RETURN))
		{
			CSnakeGame *game = CSnakeGame::GetInstance();
			game->GetStateMachine()->ChangeState(GetStateFromChoose());
		}
	}


	void MenuState::Render()
	{
		CConsole *con = CConsole::GetInstance();
		//wstring t = L"MenuState";
		//con->DrawString((80 - t.size()) / 2, 25 / 2, t, STD_WHITE);

		wstring title[] = { L"¨q©¤©¤¨s©¤¨r¡¡©°©´©°©¤©´¡¡¡¡©°¨r¨q©¤©Ø©´" ,
						    L"©¦©°©¤©Ø©´©¦¡¡©¦©¦©À©¤©¤©´¡¡©°©à¨r©°¡¡©¦",
							L"©¦¡¡©°©¤¨s©¦¡¡©¦©¦¨s©¤©¤©´¡¡©¦©¦©¦©¦¡¡¨s",
							L"©°©¤©¤©¤©¤©´¡¡©¦©¦©°©¤©¤¨s¡¡©¸©à©¼©¦¨q©¼",
							L"©¸¡¡¡¡©¦¡¡¨s¡¡©¦©¦©¦¡¡¡¡©´¡¡¡¡©¦©´©¦¡¡¡¡",
							L"©¸©¤©¤¨s©¤©¼  ©¸¨s©¸©¤©¤¨s  ¨t©Ø©¼¨t©¤©¼",
		};	
		SHORT num = sizeof(title) / sizeof(title[0]);
		SHORT x = (80 - title[0].size()*2) / 2;
		SHORT y = (25/2 - num) / 2;

		for (int i = 0; i < num;++i)
			con->DrawString(x, y+i,title[i],i+1);

		wstring MenuItems[] = {
			L"¡¾¿ªÊ¼¡¿",
			L"¡¾ÍË³ö¡¿",
		};
		
		SHORT pitch = 4;
		SHORT len = 0;
		num = sizeof(MenuItems) / sizeof(MenuItems[0]);
		for (int i = 0; i < num; ++i)
			len += CharWideIC(MenuItems[i]);
		x = (80 - ( len+(num-1)*pitch))/2;
		y = 25 / 2 + 3;
		for (int i = 0; i < num; ++i)
		{
			con->DrawString(x, y, MenuItems[i], STD_WHITE);
			con->DrawLineX(x + 1, x + CharWideIC(MenuItems[i]) - 2, y, STD_BLACK);
			if (iChoose-1 == i)
			{
				con->DrawLineX(x+1, x + CharWideIC(MenuItems[i])-2, y, STD_RED);
			}
			x += CharWideIC(MenuItems[i]) + pitch;
		}
		
	}

	State * MenuState::GetStateFromChoose()
	{
		switch (iChoose)
		{
		case ST_START:
			return GameState::GetInstance();
			break;

		case ST_EXIT:

			break;
		}
	}

	void GameState::Enter()
	{
		CSnakeGame *game = CSnakeGame::GetInstance();
		
	}

	void GameState::Exit()
	{
	}

	void GameState::Input()
	{
	}

	void GameState::Render()
	{
	}

}










