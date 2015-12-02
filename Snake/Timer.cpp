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
	// TODO: 在此处插入 return 语句
	return m_Inteval;
}

void CTimer::WaitForTimer()
{
	if (m_Inteval == 0L)
		return;

	// 暂停线程，直到时间差大于即时间隔
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


