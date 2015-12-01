#include "stdafx.h"
#include "Console.h"
#include <process.h>

void OnProcess(LPVOID process);

CConsole* CConsole::pInstance = nullptr;

CConsole::CConsole() : m_StdOut(NULL),m_StdIn(NULL),m_bKeyInput(false),m_InputThread(false)
{

}


CConsole::~CConsole()
{
	//ע������˳��
	//1.�رռ�������
	__SetKeyInput(false);
	
	//2.�����߳�
	__ExitInputThread();

	//3.��������������
	//CloseHandle(m_StdOut);
	//CloseHandle(m_StdIn);
	m_StdOut = NULL;
	m_StdIn = NULL;
}

bool CConsole::Init()
{
	m_StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	m_StdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (!m_StdOut || !m_StdIn)
		return false;
	/*
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // ���ڴ洢���ڻ�������Ϣ
	GetConsoleScreenBufferInfo(m_StdOut, &bInfo); // ��ȡ���ڻ�������Ϣ
	*/

	//����һ���߳���������������
	_beginthread(OnProcess, NULL, NULL);
	m_InputThread = true;
	m_bKeyInput = true;

	return true;
}

bool CConsole::SetTitle(std::wstring title)
{
	//if (!m_StdHandle)
	//	return false;
	return (SetConsoleTitle(title.c_str()) > 0) ? true : false;
}

void CConsole::SetCursorVisible(bool vi)
{
	if (!m_StdOut)
	{
		// ������
		return;
	}
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(m_StdOut, &info);
	info.bVisible = vi;
	SetConsoleCursorInfo(m_StdOut, &info);
}
void CConsole::MoveCursor(SHORT x, SHORT y)
{
	COORD coord = { x - 1,y - 1 };
	SetConsoleCursorPosition(m_StdOut, coord);
}
/*
  ����color
	  ����̨��color�洢��8λ��������
	  *********************************
	  | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
	  *********************************

	  ����  1 - 4 λ��ʾǰ��ɫ�����ַ���ɫ
	        5 - 8 λ��ʶ����ɫ��
	  ��ɫһ���� 2^4 = 16 ��
	  ��ÿ��4λ����ɫ��Ԫ  ��1λ��ʶblue
						   ��2λ��ʶgreen
						   ��3λ��ʶred
						   ��4λ��ʶ ��ǿ
	  ���Ը����±�
	  0=��ɫ  1=��ɫ  2=��ɫ  3=����ɫ  4=��ɫ

	  5=��ɫ  6=��ɫ  7=��ɫ  8=��ɫ    9=����ɫ

	  A=����ɫ B=��ǳ��ɫ  C=����ɫ  D=����ɫ

	  E=����ɫ   F=����ɫ
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


//����(x,y)�ı���ɫΪ color�����ı�������ɫ
//���x,y ʹ�õ������ǣ� ����̨���Ͻ�Ϊ(1,1)���½�Ϊ(80,25)
void CConsole::DrawPixel(SHORT x, SHORT y, Color color)
{
	COORD coord = { x - 1,y - 1 };
	color = MakeColor(color);
	DWORD p;
	//�Բۡ�������������������NULL����NULL�ͻᱨ������
	FillConsoleOutputAttribute(m_StdOut,color, 1,coord,&p);
}

void CConsole::DrawLineX(SHORT x0, SHORT x1, SHORT y, Color color)
{
	SHORT len = x1 - x0;
	COORD coord = { x0 - 1,y - 1 };
	DWORD p;

	StdColor *oldcolor = new StdColor[x1 - x0];
	ReadConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	for (int i = 0; i < len; i++)
		oldcolor[i] = MakeColor(color, GetForcColor(oldcolor[i]));

	WriteConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	//�Բۡ�������������������NULL����NULL�ͻᱨ������
}

//����(x,y)���������Ϊ str��������ɫΪcolor�������ı䱳��ɫ
void CConsole::DrawString(SHORT x, SHORT y, wstring str,Color color)
{
	int len = str.size();
	StdColor *oldcolor = new StdColor[len];
	COORD coord = { x-1,y-1 };
	DWORD p;
	if (len + x - 1 > 80) //CONSOLE_WIDTH
		return;
	ReadConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	for (int i = 0; i < len; i++)
		oldcolor[i] = MakeColor(GetBackColor(oldcolor[i]), color);

	WriteConsoleOutputAttribute(m_StdOut, oldcolor, len, coord, &p);
	WriteConsoleOutputCharacter(m_StdOut, str.c_str(), len, coord, &p);

	delete[] oldcolor;
}

bool CConsole::IsKeyDown(DWORD key)
{
	if (m_bKeyInput == false)
		return false;

	auto it = m_KeyMap.find(key);
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
	return m_InputThread;
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
}

void CConsole::__SetKeyInput(bool state)
{
	m_bKeyInput = state;
	m_KeyMap.clear();
}

void CConsole::__ExitInputThread()
{
	m_InputThread = false;
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
	while (con->IsThreadRun())
	{
		if (con->IsEnableKeyInput())
		{
			ReadConsoleInput(con->GetStdIn(), &record, 1, &num);
			if (record.EventType == KEY_EVENT) 
			{
				WORD key = record.Event.KeyEvent.wVirtualKeyCode;
				bool down = record.Event.KeyEvent.bKeyDown == 1 ? true : false;

				//��������������������������������������ʹ��ASCII������ȡ������������״̬
				if((key >=30 && key <=39) || (key>=41 && key <= 0x5a))
					con->__SetKeyState((DWORD)record.Event.KeyEvent.uChar.AsciiChar, down );
				else
					con->__SetKeyState(key, down);
			}
		}
		else
		{
			Sleep(1);
		}
	}
	_endthread();
}