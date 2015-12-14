#pragma once

#include <string>
#include "Console.h"
#include "SnakeGame.h"
using std::wstring;
//#include <afxwin.h>

/*
*
*
*
*/

namespace state
{

#define DECLARE_STATE(StateName)  \
	virtual wstring GetStateName() { return L"StateName"; } \
	static StateName* GetInstance() { if(pInstance) return pInstance; else return pInstance = new StateName; } \
	private: static StateName* pInstance; \


	class State
	{
	public:
		virtual void Enter() { throw new std::exception("Enter State State."); }
		virtual void Exit() {}

		virtual void Input() {}
		virtual void Render() {}

		void DrawContent();

		//  试验下这种单件模式能不能在派生类正常工作
		DECLARE_STATE(State)
		//virtual wstring GetStateName() { return L"State"; };
		//static thistype GetInstance()
	};

	class CStateMachine
	{
	public:
		CStateMachine() : pPrevState(nullptr), pCurrState(nullptr) {}
		~CStateMachine() {}

		void ChangeState(State* state)
		{
			if (pCurrState)
				pCurrState->Exit();


			pPrevState = pCurrState;
			pCurrState = state;

			if (pCurrState)
				pCurrState->Enter();

		}

		State* GetPrevState() { return pPrevState; }
		State* GetCurrState() { return pCurrState; }

	private:
		State* pPrevState;
		State* pCurrState;

	};


	class MenuState;
	class GameState;

#define ST_START 1
#define ST_EXIT  2

	class MenuState : public State
	{
	public:
		MenuState() : iChoose(0),iMenuItems(2) { }
	public:
		virtual void Enter()
		{
			iChoose = 1;
		}
		virtual void Exit()
		{
		}


		// will be called in every frame
		virtual void Input();
		virtual void Render();

		State* GetStateFromChoose();

		DECLARE_STATE(MenuState)
		//virtual wstring GetStateName() { return L"MenuState"; }
		//static MenuState GetInstance() { static MenuState ms; return ms; }

	private:
		int iChoose;

		const int iMenuItems;
	};

	class GameState : public State
	{
	public:
		virtual void Enter();
		virtual void Exit();

		virtual void Input();
		virtual void Render();

		DECLARE_STATE(GameState)
	};





}