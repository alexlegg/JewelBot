#include "OSHandler.h"
#include "Win32Handler.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	OSHandler* os = new Win32Handler();

	if (!os->init("Bejeweled Blitz on Facebook - Mozilla Firefox"))
	{
		delete os;
		return -1;
	}

	//Play now button (for me)
	//os->click(600, 620);

	Sleep(100);

	int base_x = 545;
	int base_y = 340;
	for (int x = 0; x != 8; ++x)
	{
		//os->movecursor(base_x + (x*40), base_y);
		int g = os->getgem(base_x + (x*40), base_y);
		cout << g << endl;
		Sleep(100);
	}
	
	os->msgbox("Read dem values!");

	delete os;
	return 0;
}

