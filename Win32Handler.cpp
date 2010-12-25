#include <Windows.h>
#include <sstream>
#include "Win32Handler.h"

using namespace std;

bool Win32Handler::init(const char* windowname)
{
	hDC = GetDC(NULL);
	gamewindow = FindWindow(NULL, windowname);

	if (gamewindow == NULL || hDC == NULL)
	{
		msgbox("Couldn't get game window. Try opening it?");
		return false;
	} else {
		SetForegroundWindow(gamewindow);
		Sleep(10); //Let windows catch up a bit
		return true;
	}
}

void Win32Handler::msgbox(string msg, int value)
{
	if (value == 0)
	{
		MessageBox(NULL, msg.c_str(), "JewelBot", MB_OK);
	} else {
		stringstream str;
		str << " = " << value;
		msg.append(str.str());
		MessageBox(NULL, msg.c_str(), "Output", MB_OK);
	}
}

Pixel Win32Handler::getrgb(int x, int y)
{
	int col = GetPixel(hDC, 100, 100);
	Pixel p;

	if (col == CLR_INVALID)
	{
		msgbox("colour invalid");
		return p;
	}

	p.red = GetRValue(col);
	p.green = GetGValue(col);
	p.blue = GetBValue(col);

	return p;
}

void Win32Handler::movecursor(int x, int y)
{
	SetCursorPos(x, y);
}

void Win32Handler::click(int x, int y)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}