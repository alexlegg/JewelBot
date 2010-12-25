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
	cout << endl;

	//Find a move
	for (int x = 0; x != 8; ++x)
	{
		for (int y = 1; y != 8; ++ y)
		{
			//Swap up
			int start = x-3;
			int end = x+3;
			if (start < 0) start = 0;
			if (end > 7) end = 7;
			int row[2][6];
			for (int i = start; i != end; ++i)
			{
				row[0][i] = board[y][i];
				row[1][i] = board[y-1][i];
				cout << row[0][i] << " ";
			}
			cout << endl;

			int score = 0;
			score += checkrow(row[0], end-start);
			score += checkrow(row[1], end-start);
			//cout << "(" << x << ", " << y << ") = " << score << endl;
			//cout << start << ", " << end << endl;
		}
	}

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

int Game::checkrow(int row[], int length)
{
	int count = 0;
	int max = 0;
	int prev = -1;
	for (int i = 0; i != length; ++i)
	{
		if (row[i] == prev)
		{
			count++;
		} else {
			max = count;
			count = 0;
		}
	}
	return max;
}