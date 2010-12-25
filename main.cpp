#include "OSHandler.h"
#include "Win32Handler.h"

int main(int argc, char **argv)
{
	OSHandler* os = new Win32Handler();

	if (!os->init("Bejeweled Blitz on Facebook - Mozilla Firefox"))
	{
		delete os;
		return -1;
	}

	//Play now button (for me)
	int base_x = 545;
	int base_y = 340;
	Pixel row[8];
	for (int x = 0; x != 8; ++x)
	{
		os->movecursor(base_x + (x*40), base_y);
		row[x] = os->getrgb(base_x + (x*40), base_y);
		Sleep(100);
	}
	//os->click(600, 620);

	delete os;
	return 0;
}

