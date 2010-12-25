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

void Game::play()
{
	//Not in ready state - can't play
	if (state != 0) return;

	cout << "test" << endl;
	//Click play button and wait a bit
	os->wait(500);
	//os->movecursor(base_x + 55, base_y + 280);
	os->click(base_x + 55, base_y + 280);
	os->wait(4000);

	//Get the cursor out the way (not sure if needed)
	os->movecursor(0, 0);

	//Get the current board
	readboard();

	printboard();

}

void Game::readboard()
{
	for (int x = 0; x != 8; ++x)
	{
		for (int y = 0; y != 8; ++y)
		{
			//os->movecursor(base_x + (x * offset), base_y + (y * offset));
			board[x][y] = os->getgem(base_x + (y * offset), base_y + (x * offset));
			//os->wait(50);
		}
	}
}

void Game::printboard()
{
	for (int x = 0; x != 8; ++x)
	{
		for (int y = 0; y != 8; ++y)
		{
			cout << board[x][y] << " ";
		}
		cout << endl;
	}
}