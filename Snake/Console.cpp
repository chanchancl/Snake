
#include "stdafx.h"
#include "Console.h"
#include <ctype.h>
#include <process.h>

void OnProcess(LPVOID process);

CConsole* CConsole::pInstance = nullptr;

//关于color
/*
控制台的color存储在8位的数据上
*********************************
| 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
*********************************

其中  1 - 4 位表示前景色，即字符颜色
5 - 8 位标识背景色。
颜色一共有 2^4 = 16 种
对每个4位的颜色单元  第1位标识blue
第2位标识green
第3位标识red
第4位标识 增强
所以给出下表
0=黑色  1=蓝色  2=绿色  3=湖蓝色  4=红色

5=紫色  6=黄色  7=白色  8=灰色    9=淡蓝色

A=淡绿色 B=淡浅绿色  C=淡红色  D=淡紫色

E=淡黄色   F=亮白色
*/

StdColor MakeColor(Color back, Color font)
{
	return   (WORD)((back << 4) | font);
}

Color GetBackColor(StdColor color)
{
	return (Color)((color & 0xf0) >> 4);
}
Color GetForcColor(StdColor color)
{
	return (Color)(color & 0xf);
}

int CharWideInConsole(const wstring& str)
{
	int l = 0;
	for (const auto it : str)
		l += iswascii(it) ? 1 : 2;
	return l;
}


CConsole::CConsole() : m_StdOut(NULL),m_StdIn(NULL),m_bKeyInput(false),m_bInputThread(false), m_hInputThread(nullptr)
{

}


CConsole::~CConsole()
{
	//注意析构顺序
	//1.关闭键盘输入
	__SetKeyInput(false);
	
	//2.结束线程
	__ExitInputThread();

	//3.销毁输入输出句柄
	//CloseHandle(m_StdOut);
	//CloseHandle(m_StdIn);
	m_StdOut = NULL;
	m_StdIn = NULL;

	if (pInstance)
		pInstance = nullptr;
}

bool CConsole::Init()
{
	m_StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	m_StdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (!m_StdOut || !m_StdIn)
		return false;
	/*
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 用于存储窗口缓冲区信息
	GetConsoleScreenBufferInfo(m_StdOut, &bInfo); // 获取窗口缓冲区信息
	*/

	//创建一个线程来管理按键输入
	m_hInputThread = (HANDLE) _beginthread(OnProcess, NULL, NULL);
	m_bInputThread = true;
	m_bKeyInput = true;

	return true;
}

bool CConsole::SetTitle(wstring& title)
{
	//if (!m_StdHandle)
	//	return false;
	return (SetConsoleTitle(title.c_str()) > 0) ? true : false;
}

void CConsole::SetCursorVisible(bool vi)
{
	if (!m_StdOut)
	{
		// 错误句柄
		return;
	}
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(m_StdOut, &info);
	info.bVisible = vi;
	SetConsoleCursorInfo(m_StdOut, &info);
}
void CConsole::SetCursorPosition(SHORT x, SHORT y)
{
	COORD coord = { x - 1,y - 1 };
	SetConsoleCursorPosition(m_StdOut, coord);
}


//设置(x,y)的背景色为 color，不改变文字颜色
//这个x,y 使用的坐标是： 控制台左上角为(1,1)右下角为(80,25)
void CConsole::DrawPixel(SHORT x, SHORT y, Color color)
{
	COORD coord = { x - 1,y - 1 };
	color = MakeColor(color);
	DWORD p;
	//卧槽。。最后这个参数不能填NULL，填NULL就会报错。。
	FillConsoleOutputAttribute(m_StdOut,color, 1,coord,&p);
}

void CConsole::DrawLineX(SHORT x0, SHORT x1, SHORT y, Color color)
{
	SHORT len = x1 - x0 +1;
	COORD coord = { x0 - 1,y - 1 };
	DWORD p;

	StdColor *oldcolor = new StdColor[x1 - x0];
	ReadConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	for (int i = 0; i < len; i++)
		oldcolor[i] = MakeColor(color, GetForcColor(oldcolor[i]));

	WriteConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	//卧槽。。最后这个参数不能填NULL，填NULL就会报错。。

	//delete[] oldcolor;
	//...oldcolor不能delete，delete后会出问题
	
}

void CConsole::DrawLineY(SHORT x, SHORT y0, SHORT y1, Color color)
{
	COORD coord = { x-1, y0-1 };
	DWORD p;
	StdColor oldcolor;

	
	for ( ; coord.Y <= y1-1 ; coord.Y++)
	{
		ReadConsoleOutputAttribute(m_StdOut, &oldcolor, 1, coord, &p);
		oldcolor = MakeColor(color, GetForcColor(oldcolor));
		WriteConsoleOutputAttribute(m_StdOut, &oldcolor, 1, coord, &p);
	}

	
}



//设置(x,y)后面的文字为 str，字体颜色为color，但不改变背景色
void CConsole::DrawString(SHORT x, SHORT y,const wstring& str,Color color)
{
	int WideInConsole = CharWideIC(str);
	int SizeOfCharacter = str.size();

	StdColor *oldcolor = new StdColor[WideInConsole];
	COORD coord = { x-1,y-1 };
	DWORD p;
	if (WideInConsole + x - 1 > 80) //CONSOLE_WIDTH
		return;
	ReadConsoleOutputAttribute(m_StdOut, oldcolor, WideInConsole, coord, &p);
	for (int i = 0; i < WideInConsole; i++)
		oldcolor[i] = MakeColor(GetBackColor(oldcolor[i]), color);

	WriteConsoleOutputAttribute(m_StdOut, oldcolor, WideInConsole, coord, &p);
	WriteConsoleOutputCharacter(m_StdOut, str.c_str(), SizeOfCharacter, coord, &p);

	delete[] oldcolor;
}


bool CConsole::IsKeyDown(DWORD key)
{
	if (m_bKeyInput == false)
		return false;

	auto it = m_KeyMap.find(key);

	//cout << key << " state is " << (it == m_KeyMap.end() ? false : it->second) <<endl;

	if (it == m_KeyMap.end())
		return false;
	return m_KeyMap[key];
}

HANDLE CConsole::GetStdIn()
{
	return m_StdIn;
}

HANDLE CConsole::GetStdOut()
{
	return m_StdOut;
}

bool CConsole::IsEnableKeyInput()
{
	return m_bKeyInput;
}

bool CConsole::IsThreadRun()
{
	return m_bInputThread && m_hInputThread != nullptr;
}

CConsole * CConsole::GetInstance()
{
	CConsole *con;
	if (pInstance == nullptr)
	{
		con = new CConsole;
		if (con)
			return pInstance = con;
	}
	return pInstance;
}

void CConsole::__SetKeyState(DWORD key, bool state)
{
	m_KeyMap[key] = state;
	//cout << "set " << key << " state is " << state << endl;
}

void CConsole::__SetKeyInput(bool state)
{
	m_bKeyInput = state;
	m_KeyMap.clear();
}

void CConsole::__ExitInputThread()
{
	m_bInputThread = false;
	if (m_hInputThread)
	{
		CloseHandle(m_hInputThread);
		m_bInputThread = nullptr;
	}
}


void OnProcess(LPVOID process)
{
	CConsole *con = CConsole::GetInstance();
	INPUT_RECORD record;
	DWORD num;
	/*while (!con)
	{
		con = CConsole::GetInstance();
		Sleep(30);
	}*/

	while (true)
	{
		if (con->IsEnableKeyInput())
		{
			ReadConsoleInput(con->GetStdIn(), &record, 1, &num);
			if (record.EventType == KEY_EVENT) 
			{
				DWORD key = record.Event.KeyEvent.wVirtualKeyCode;
				bool down = record.Event.KeyEvent.bKeyDown == 1 ? true : false;

				//。。。。区分主键盘区和其他按键。。方便使用ASCII码来获取主键盘区按键状态
				if((key >=0x30 && key <=0x39) || (key>=0x41 && key <= 0x5a))
					con->__SetKeyState((DWORD)record.Event.KeyEvent.uChar.AsciiChar, down );
				else
					con->__SetKeyState((DWORD)key, down);
			}
		}
		else
		{
			Sleep(1);
		}
	}
	//_endthread();
}

