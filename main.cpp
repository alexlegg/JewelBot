#include "OSHandler.h"
#include "Win32Handler.h"
#include "Game.h"
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

	Game game(os, 545, 340, 40);

	game.play();
	
	os->msgbox("Read dem values!");

	delete os;
	return 0;
}

