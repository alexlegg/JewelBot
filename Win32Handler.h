#ifndef WIN32HANDLER_H
#define WIN32HANDLER_H

#include <Windows.h>
#include <string>
#include "OSHandler.h"

class Win32Handler : public OSHandler
{
	HDC hDC;
	HWND gamewindow;

public:
	bool init(const char* windowname);
	//void deinit();

	void msgbox(std::string msg, int value = 0);
	Pixel getrgb(int x, int y);
	void movecursor(int x, int y);
	void click(int x, int y);
};

#endif