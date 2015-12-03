#pragma once
#include <windows.h>

/*
   class CTimer
   ��ʱ����
   ����:
		1.����������ͣ�߳�ָ��ʱ�䣨��λ���룩
		  �÷� �趨Inteval���ڿ�ʼ�ȴ�������OnTick()
		  �ڽ����ȴ�������WaitForTimer()
		  Ҳ����  while(timer) ����ÿ��inteval���룬ѭ���Ż�����һ��
		
		2.�¿�һ���̣߳�ÿ��ָ����������ָ������
		  Ҳ�����趨Ϊ��ѭ������ʱ����ָ������
		  PS����Щ��������һ���߳���ִ�У���������ԭ����
		  �÷�  ��ûд����
*/

class CTimer
{
public:
	CTimer(DWORD inteval = 0);
	~CTimer();

public:
	//����һ��
	DWORD OnTick();

	DWORD  GetTime();
	DWORD  GetLastTime();
	DWORD& GetInteval();
	DWORD  GetElapseTime();

	void WaitForTimer();
	
	operator bool();


public:
	//���ܶ���
	
	

private:
	DWORD m_LastTime;

	// 0 ��Ϊ�޼�����޵ȴ����������̷���
	DWORD m_Inteval;
};

