#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer(DWORD inteval) :m_LastTime(GetCurrentTime()),m_Inteval(inteval)
{
}


CTimer::~CTimer()
{
}

inline DWORD CTimer::OnTick()
{
	return m_LastTime = GetTime();
}

inline DWORD CTimer::GetTime()
{
	return GetCurrentTime();
}

inline DWORD CTimer::GetLastTime()
{
	return m_LastTime;
}

DWORD & CTimer::GetInteval()
{
	return m_Inteval;
}

DWORD CTimer::GetElapseTime()
{
	return GetTime() - GetLastTime();
}

void CTimer::WaitForTimer()
{
	if (m_Inteval == 0L)
		return;

	// 暂停线程，直到时间差大于即时间隔  因为是内联函数。。所以效率不用担心。。与原函数没区别。。
	while (GetTime() - GetLastTime() <= m_Inteval)
		Sleep(1);
	

}

// 语法糖，单纯是为了完成
// while(timer)  这个语法糖。。。
// 返回 true  表示 等待完成
//      false 表示 计时间隔为0，没有等待
CTimer::operator bool()
{
	WaitForTimer();
	OnTick();
	return m_Inteval != 0 ? true : false;
}


