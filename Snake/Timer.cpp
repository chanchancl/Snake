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
	// TODO: �ڴ˴����� return ���
	return m_Inteval;
}

void CTimer::WaitForTimer()
{
	if (m_Inteval == 0L)
		return;

	// ��ͣ�̣߳�ֱ��ʱ�����ڼ�ʱ���
	while (GetTime() - GetLastTime() <= m_Inteval)
		Sleep(1);
	

}

// �﷨�ǣ�������Ϊ�����
// while(timer)  ����﷨�ǡ�����
// ���� true  ��ʾ �ȴ����
//      false ��ʾ ��ʱ���Ϊ0��û�еȴ�
CTimer::operator bool()
{
	WaitForTimer();
	OnTick();
	return m_Inteval != 0 ? true : false;
}


