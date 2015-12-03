#pragma once
#include <windows.h>

/*
   class CTimer
   计时器类
   功能:
		1.可以用来暂停线程指定时间（单位毫秒）
		  用法 设定Inteval后，在开始等待处调用OnTick()
		  在结束等待处调用WaitForTimer()
		  也可以  while(timer) 这样每隔inteval毫秒，循环才会运行一次
		
		2.新开一个线程，每隔指定毫秒运行指定函数
		  也可以设定为不循环的延时运行指定函数
		  PS：这些都是在另一个线程里执行，不会阻塞原进程
		  用法  还没写。。
*/

class CTimer
{
public:
	CTimer(DWORD inteval = 0);
	~CTimer();

public:
	//功能一区
	DWORD OnTick();

	DWORD  GetTime();
	DWORD  GetLastTime();
	DWORD& GetInteval();
	DWORD  GetElapseTime();

	void WaitForTimer();
	
	operator bool();


public:
	//功能二区
	
	

private:
	DWORD m_LastTime;

	// 0 即为无间隔，无等待，总是立刻返回
	DWORD m_Inteval;
};

