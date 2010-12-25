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
	os->movecursor(600, 620);

	delete os;
	return 0;
}

