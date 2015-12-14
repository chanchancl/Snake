
#pragma once

#include <windows.h>
#include <string>
#include <map>
using namespace std;

// ��ʲô��ͬ�أ�
// StdColor����������ɣ���λ�͵�λ
// �� Color����Чֵֻ��ǰ4λ
typedef WORD StdColor;
typedef WORD Color;

//  �����³�����ɫ������
#ifndef _STD_COLOR_
#define _STD_COLOR_
#define STD_BLACK  0x0
#define STD_BLUE   0x1
#define STD_GREEN  0x2
#define STD_RED    0x4
#define STD_YELLOW 0x6
#define STD_WHITE  0xf
#endif

class CConsole
{
private:
	//��ֹ�ⲿͨ�����캯��������������ʵ��
	CConsole();
public:
	~CConsole();

public:
	bool Init();

	bool SetTitle(wstring title);
	void SetCursorVisible(bool vi);
	void SetCursorPosition(SHORT x, SHORT y);

	// ���������أ�������
	void DrawPixel(SHORT x, SHORT y, Color color);
	// ��X��������   (x0<x1)
	void DrawLineX(SHORT x0, SHORT x1, SHORT y, Color color);
	// ��Y��������  (y0<y1)
	void DrawLineY(SHORT x, SHORT y0, SHORT y1, Color color);
	void DrawString(SHORT x, SHORT y, wstring str,Color color);

	//��ȡָ������״̬ 
	//  key : ָ��������������   
	//         PS :  ���������İ�������ʹ�� ASCII������ȡ(���ִ�Сд)
	//				 �� IsKeyDown('a') IsKeyDown('A') IsKeyDown('0') ���0ָ�����������ϵ�0
	//				 С�����ϵ�0��ʹ�ö�Ӧ�������롣����
	//                
	//  return  true  ��ǰ����
	//			false ��ǰ����
	bool IsKeyDown(DWORD key);

	HANDLE GetStdIn();
	HANDLE GetStdOut();

	bool IsEnableKeyInput();
	bool IsThreadRun();
	
	static CConsole* GetInstance();

public:
	//��������ʹ�����к���
	void __SetKeyState(DWORD key, bool state);
	void __SetKeyInput(bool state);
	void __ExitInputThread();

private:
	HANDLE m_StdOut,m_StdIn;

	// =falseʱ���߳��˳�
	bool m_bInputThread;
	HANDLE m_hInputThread;
	
	// ����������̵�����״̬ ���ҽ��� m_bKeyInput Ϊtrueʱ��ֵ��Ч
	map<DWORD, bool> m_KeyMap;

	// ���ڿ����߳�2�Ƿ��ȡ��ǰ��������  
	//  true  : ��ȡ��������
	//  false : ����
	bool m_bKeyInput;


	static CConsole* pInstance;
};

//�� ����ɫ�� ǰ��ɫ�� �ϳ�һ����������ɫ
// ����:   back 0-15   font  0-15
StdColor MakeColor(Color back, Color font = 0);

// ��ö�Ӧ�� ǰ��ɫ���� ����ɫ
// ����:  color  0 - ff 
Color GetBackColor(StdColor color);
Color GetForcColor(StdColor color);


int CharWideInConsole(const wstring& str);
#define CharWideIC CharWideInConsole