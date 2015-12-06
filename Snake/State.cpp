#include "stdafx.h"
#include "State.h"

#include <time.h>
//

namespace state
{

	void State::DrawContent()
	{
		CConsole *con = CConsole::GetInstance();

		//int time = clock();
		con->DrawLineX(1, 80, 1, STD_GREEN);
		con->DrawLineX(1, 80, 25, STD_GREEN);
		con->DrawLineY(1, 2, 24, STD_GREEN);
		con->DrawLineY(2, 2, 24, STD_GREEN);
		con->DrawLineY(79, 2, 24, STD_GREEN);
		con->DrawLineY(80, 2, 24, STD_GREEN);
		//time = clock() - time;

	}


	MenuState* MenuState::pInstance = nullptr;
	GameState* GameState::pInstance = nullptr;

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
			if (iChoose < iMenuItems)
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
		wstring t = L"MenuState";
		con->DrawString((80 - t.size()) / 2, 25 / 2, t, STD_WHITE);
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

}