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

int* Win32Handler::getrgb(int x, int y)
{
	int col = GetPixel(hDC, 100, 100);

	if (col == CLR_INVALID)
	{
		msgbox("colour invalid");
		return NULL;
	}

	int *rgb = new int[3];
	rgb[0] = GetRValue(col);
	rgb[1] = GetGValue(col);
	rgb[2] = GetBValue(col);

	return rgb;
}

void Win32Handler::movecursor(int x, int y)
{
	SetCursorPos(x, y);
}