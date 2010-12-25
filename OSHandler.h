#ifndef OSHANDLER_H
#define OSHANDLER_H

#include <string>

struct Pixel
{
	int red;
	int green;
	int blue;
};

class OSHandler
{

public:
	virtual bool init(const char* windowname) = 0;
	//virtual void deinit();

	virtual void msgbox(std::string msg, int value = 0) = 0;
	virtual Pixel getrgb(int x, int y) = 0;
	virtual void movecursor(int x, int y) = 0;
	virtual void click(int x, int y) = 0;
};

#endif