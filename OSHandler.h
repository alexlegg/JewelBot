#ifndef OSHANDLER_H
#define OSHANDLER_H

#include <string>

class OSHandler
{

public:
	static const int gemtypes = 7;
	static const int gemcolours[];

public:
	virtual bool init(const char* windowname) = 0;
	//virtual void deinit();

	virtual void msgbox(std::string msg, int value = 0) = 0;
	virtual int getgem(int x, int y) = 0;
	virtual void movecursor(int x, int y) = 0;
	virtual void click(int x, int y) = 0;
};

#endif