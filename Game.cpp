#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(OSHandler* oshandler, int bx, int by, int off)
{
	os = oshandler;
	base_x = bx;
	base_y = by;
	offset = off;

	for (int i = 0; i != 8; ++i)
	{
		for (int j = 0; j != 8; ++j)
		{
			board[i][j] = 0;
		}
	}

	//Delicious magic numbers! (Fuck you, don't judge me)
	int playbutton = os->getcolour(bx + 55, by + 280);
	cout << bx + 55 << ", " << by + 280 << endl;
	cout << playbutton << endl;
	if (abs(playbutton - 11438276) < 100)
	{
		//Ready state
		state = 0;
	} else {
		//WTF!?
		os->msgbox("Get to the 'Play Now' Screen or change some values");
		state = -1;
	}

	time = 0;
	//os->sleep(100);
}