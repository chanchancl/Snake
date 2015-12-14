
#pragma once

#include <windows.h>
#include <string>
#include <map>
using namespace std;

// 有什么不同呢？
// StdColor由两部分组成，高位和低位
// 而 Color的有效值只有前4位
typedef WORD StdColor;
typedef WORD Color;

//  定义下常用颜色。。。
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
	//禁止外部通过构造函数来创建这个类的实例
	CConsole();
public:
	~CConsole();

public:
	bool Init();

	bool SetTitle(wstring title);
	void SetCursorVisible(bool vi);
	void SetCursorPosition(SHORT x, SHORT y);

	// 画单个像素（背景）
	void DrawPixel(SHORT x, SHORT y, Color color);
	// 按X方向画像素   (x0<x1)
	void DrawLineX(SHORT x0, SHORT x1, SHORT y, Color color);
	// 按Y方向画像素  (y0<y1)
	void DrawLineY(SHORT x, SHORT y0, SHORT y1, Color color);
	void DrawString(SHORT x, SHORT y, wstring str,Color color);

	//获取指定按键状态 
	//  key : 指定按键的虚拟码   
	//         PS :  主键盘区的按键可以使用 ASCII码来获取(区分大小写)
	//				 如 IsKeyDown('a') IsKeyDown('A') IsKeyDown('0') 这个0指的是主键盘上的0
	//				 小键盘上的0请使用对应的虚拟码。。。
	//                
	//  return  true  当前按下
	//			false 当前弹起
	bool IsKeyDown(DWORD key);

	HANDLE GetStdIn();
	HANDLE GetStdOut();

	bool IsEnableKeyInput();
	bool IsThreadRun();
	
	static CConsole* GetInstance();

public:
	//切勿随意使用下列函数
	void __SetKeyState(DWORD key, bool state);
	void __SetKeyInput(bool state);
	void __ExitInputThread();

private:
	HANDLE m_StdOut,m_StdIn;

	// =false时，线程退出
	bool m_bInputThread;
	HANDLE m_hInputThread;
	
	// 用来管理键盘的输入状态 当且仅当 m_bKeyInput 为true时其值有效
	map<DWORD, bool> m_KeyMap;

	// 用于控制线程2是否获取当前键盘输入  
	//  true  : 获取键盘输入
	//  false : 休眠
	bool m_bKeyInput;


	static CConsole* pInstance;
};

//由 背景色和 前景色和 合成一个完整的颜色
// 参数:   back 0-15   font  0-15
StdColor MakeColor(Color back, Color font = 0);

// 获得对应的 前景色，或 背景色
// 参数:  color  0 - ff 
Color GetBackColor(StdColor color);
Color GetForcColor(StdColor color);


int CharWideInConsole(const wstring& str);
#define CharWideIC CharWideInConsole