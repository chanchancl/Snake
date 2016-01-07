#pragma once

#ifndef __CSCHEDULER_H__
#define __CSCHEDULER_H__

#include <map>
#include <list>
#include <functional>

using namespace std;

// Rewrite this file
//CallBack 分类
// 1. Class member function
// 2. Global static function

/*
typedef function<void ()> CallBack;
static bool operator<(const CallBack &op1, const CallBack &op2);

class CScheduler
{
public:
	CScheduler();
	~CScheduler();

	void Dispatch();
	void AddFunction(CallBack fun, UINT cycle = 1);
	void DelFunction(CallBack fun);
	void SkipCall(CallBack fun, UINT skipNum);

	typedef struct _CallBackInfo
	{
		UINT Cycle;
		UINT SkipCall;
		UINT Dispatched;  //被调度的次数
		UINT Called;	  //被调用的次数
	}CallBackInfo;
	CallBack a;

	list<CallBack> m_lsFunc;
	map<CallBack, CallBackInfo> m_FuncInfo;

};

*/
#endif