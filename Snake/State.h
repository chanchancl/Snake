#pragma once

#include <string>
#include "Food.h"
#include "Console.h"
#include "SnakeGame.h"
using std::string;

/*
*
*
*
*/

namespace state
{

#define DECLARE_STATE(stateName)  \
	public: \
	virtual string GetStateName() { return #stateName; } \
	static stateName* GetInstance() { if(pInstance) return pInstance; else return pInstance = new stateName; } \
	private: static stateName* pInstance; \

#define ST_START 1
#define ST_EXIT  2

	class State
	{
	public:
		virtual void Enter() { throw new std::exception("Enter State State."); }
		virtual void Exit() {}

		virtual void Input() {}
		virtual void Update() {}
		virtual void Render() {}

		void DrawContent();

		//  试验下这种单件模式能不能在派生类正常工作 learn from MFC hhhhhh...
		DECLARE_STATE(State)
	};

	class CStateMachine
	{
	public:
		CStateMachine() : pPrevState(nullptr), pCurrState(nullptr) {}
		~CStateMachine() {}

		void ChangeState(State* state)
		{
			pPrevState = pCurrState;
			pCurrState = state;

            // 在切换到第一个State的时候，pPrevState可以为空
			if (pPrevState)
				pPrevState->Exit();

			if (pCurrState)
				pCurrState->Enter();

		}

		State* GetPrevState() { return pPrevState; }
		State* GetCurrState() { return pCurrState; }

	private:
		State* pPrevState;
		State* pCurrState;

	};

	class MenuState : public State
	{
	public:
		MenuState() : iChoose(0),iMenuItems(2) { }
	public:
        virtual void Enter();


		// will be called in every frame
		virtual void Input();
		virtual void Render();

		State* GetStateFromChoose();

		DECLARE_STATE(MenuState)

	private:
		int iChoose;

		const int iMenuItems;
	};

	class GameState : public State
	{
	public:
		virtual void Enter();

		virtual void Input();
		virtual void Update();
		virtual void Render();

		CSnake* GetSnake() const;
		CFood* GetFood() const;

	private:
		CSnake *m_Snake;
		CFood  *m_Food;

		DECLARE_STATE(GameState)
	};

	class PauseState : public State
	{
	public:
		virtual void Enter();
		virtual void Exit();

		virtual void Input();
		virtual void Render();

		DECLARE_STATE(PauseState)
	};




}