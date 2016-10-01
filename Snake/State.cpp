#include "stdafx.h"
#include "State.h"

#include <time.h>
//

namespace state
{
	// define static class'member
	MenuState* MenuState::pInstance = nullptr;
	GameState* GameState::pInstance = nullptr;
	PauseState* PauseState::pInstance = nullptr;


	//
	// State
	//
	void State::DrawContent()
	{
		if (!CSnakeGame::GetInstance()->IsNeedRender())
			return;
		CConsole *con = CConsole::GetInstance();

		
		con->DrawLineX(1, 80, 1, STD_GREEN);
		con->DrawLineX(1, 80, 25, STD_GREEN);
		con->DrawLineY(1, 2, 24, STD_GREEN);
		con->DrawLineY(2, 2, 24, STD_GREEN);
		con->DrawLineY(79, 2, 24, STD_GREEN);
		con->DrawLineY(80, 2, 24, STD_GREEN);

	}

    void MenuState::Enter()
    {
        iChoose = 1;
        CSnakeGame::GetInstance()->SetNeedRender(true);
    }

	//
	// MenuState
	//
	void MenuState::Input()
	{
		CConsole *con = CConsole::GetInstance();
		if (con->IsKeyDown(VK_LEFT))
		{
			if (iChoose > 1)
			{
				iChoose--;
				CSnakeGame::GetInstance()->SetNeedRender(true);
			}
		}
		if (con->IsKeyDown(VK_RIGHT))
		{
			if (iChoose < 2)
			{
				iChoose++;
				CSnakeGame::GetInstance()->SetNeedRender(true);
			}
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

		if (!CSnakeGame::GetInstance()->IsNeedRender())
			return;

		wstring title[] = { L"╭──╯─╮　┌┐┌─┐　　┌╮╭─┴┐" ,
						    L"│┌─┴┐│　││├──┐　┌┼╮┌　│",
							L"│　┌─╯│　││╯──┐　││││　╯",
							L"┌────┐　││┌──╯　└┼┘│╭┘",
							L"└　　│　╯　│││　　┐　　│┐│　　",
							L"└──╯─┘  └╯└──╯  ╰┴┘╰─┘",
		};	
		SHORT num = sizeof(title) / sizeof(title[0]);
		SHORT x = (80 - (SHORT)title[0].size()*2) / 2;
		SHORT y = (25/2 - num) / 2;

		for (int i = 0; i < num;++i)
			con->DrawString(x, y+i,title[i],i+1);

		wstring MenuItems[] = {
			L"【开始】",
			L"【退出】",
		};
		
		SHORT pitch = 8;
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
		
		CSnakeGame::GetInstance()->SetNeedRender(false);
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

		// error
		return NULL;
	}

	//
	// GameState
	//
	void GameState::Enter()
	{
		CSnakeGame *game = CSnakeGame::GetInstance();
		CStateMachine* statemac = game->GetStateMachine();
        game->SetNeedRender(true);

		if (statemac->GetPrevState() != PauseState::GetInstance())
		{
			if (m_Snake)
				delete m_Snake;
			
			// 创建蛇
			m_Snake = new CSnake;
			m_Snake->Init();

			// 创建食物
			m_Food = new CFood;
			m_Food->Init();

		}

		//do nothing
	}

	void GameState::Input()
	{
		// 处理2个按键事件
		// 1.转向  2.暂停
        CConsole *con = CConsole::GetInstance();

        if ((m_Snake->m_Dir == CSnake::Dir::Up || m_Snake->m_Dir == CSnake::Dir::Down))
        {
            if (con->IsKeyDown(VK_LEFT))
            {
                m_Snake->ChangeDir(CSnake::Dir::Left);
                CSnakeGame::GetInstance()->SetNeedRender(true);
            }
            else if (con->IsKeyDown(VK_RIGHT))
            {
                m_Snake->ChangeDir(CSnake::Dir::Right);
                CSnakeGame::GetInstance()->SetNeedRender(true);
            }
        }
        if ((m_Snake->m_Dir == CSnake::Dir::Left || m_Snake->m_Dir == CSnake::Dir::Right))
        {
            if (con->IsKeyDown(VK_UP))
            {
                m_Snake->ChangeDir(CSnake::Dir::Up);
                CSnakeGame::GetInstance()->SetNeedRender(true);
            }
            else if (con->IsKeyDown(VK_DOWN))
            {
                m_Snake->ChangeDir(CSnake::Dir::Down);
                CSnakeGame::GetInstance()->SetNeedRender(true);
            }
        }

        // 暂停事件
        if (con->IsKeyDown(VK_SPACE))
        {
            CSnakeGame *game = CSnakeGame::GetInstance();
            game->GetStateMachine()->ChangeState(PauseState::GetInstance());
        }

	}

    void GameState::Update()
    {
        //called every frame
        static int Called = 0;

        Called++;
        if (Called >= 3)
        {
            m_Snake->Advance();
            Called = 0;
        }
    }

	void GameState::Render()
	{
        CSnakeGame *game = CSnakeGame::GetInstance();
        if (!game->IsNeedRender())
            return;

        system("cls");
        m_Snake->Render();
        m_Food->Render();
	}

	CSnake * GameState::GetSnake() const
	{
		return m_Snake;
	}

	CFood * GameState::GetFood() const
	{
		return m_Food;
	}

	//
	// PauseState
	//
	void PauseState::Enter()
	{

	}

	void PauseState::Exit()
	{
	}

	void PauseState::Input()
	{
        CConsole *con = CConsole::GetInstance();
        
        // 由于Run 非常快，在GameState中切换State后，暂停一段时间
        
        static CTimer *timer = nullptr;
        if (!timer)
            timer = new CTimer(500);

        if (timer->GetElapseTime() > timer->GetInteval() && con->IsKeyDown(VK_SPACE))
        {
            timer->OnTick();
            CSnakeGame *game = CSnakeGame::GetInstance();
            game->GetStateMachine()->ChangeState(GameState::GetInstance());
        }
	}

	void PauseState::Render()
	{
        wstring out = L"PAUSE NOW";
        CConsole *con = CConsole::GetInstance();

        // 覆盖式暂停 233
        GameState::GetInstance()->Render();

        con->DrawString((GameSizeWidth - out.size()) / 2, GameSizeHeight / 2, out, STD_RED);
	}

}










