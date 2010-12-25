#include <Windows.h>
#include <sstream>
#include <iostream>
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
		Sleep(20); //Let windows catch up a bit
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

int Win32Handler::getgem(int x, int y)
{
	int col = GetPixel(hDC, x, y);

	if (col == CLR_INVALID)
	{
		msgbox("colour invalid");
		return -1;
	}

	//int r = GetRValue(col); //Might need this at some point?
	
	int c = 0;
	int mindiff = abs(col - gemcolours[0]);
	for (int i = 1; i != gemtypes; ++i)
	{
		if (abs(col - gemcolours[i]) < mindiff)
		{
			mindiff = abs(col - gemcolours[i]);
			c = i;
		}
	}

	//cout << c << "\t" << mindiff << endl;
	if (mindiff > 100) //Yay magic!
	{
		return -1;
	} else {
		return c;
	}
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