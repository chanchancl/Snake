#include "stdafx.h"
#include "Scheduler.h"

/*
CScheduler::CScheduler()
{
}

CScheduler::~CScheduler()
{
}

void CScheduler::Dispatch()
{
	//start dispatch
	for (const auto& it : m_lsFunc)
	{
		auto& info = m_FuncInfo[it];
		info.Dispatched++;
		if (info.Dispatched!= 0 && 
			info.Dispatched % info.Cycle == 0)
		{
			//可调度
			if (info.SkipCall > 0)
			{
				info.SkipCall--;
				continue;
			}
			//可调用
			info.Called++;
			it();
		}
	}
	//end dispatch
}

void CScheduler::AddFunction(CallBack fun, UINT cycle)
{
	CallBackInfo info;
	info.Cycle = cycle;
	info.SkipCall = 0;
	info.Dispatched = 0;
	info.Called = 0;

	m_lsFunc.push_back(fun);
	m_FuncInfo[fun] = info;
}

void CScheduler::DelFunction(CallBack fun)
{
	m_lsFunc.erase(find(m_lsFunc.begin(), m_lsFunc.end(), fun));
	m_FuncInfo.erase(fun);
}

void CScheduler::SkipCall(CallBack fun, UINT skipNum)
{
	m_FuncInfo[fun].SkipCall = skipNum;
}


bool operator<(const CallBack &op1,const CallBack &op2)
{
	return op1.target_type().hash_code() < op2.target_type().hash_code();
}

*/