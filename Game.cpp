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
		for (int y = 0; y != 8; ++ y)
		{
			//Swap vertical (always up, no need to check down swaps)
			int row1[6];
			int row2[6];
			int row1len = getrow(x, y-1, 1, row1);
			int row2len = getrow(x, y, -1, row2);

			int score = 0;
			score += checkrow(row1, row1len);
			score += checkrow(row2, row2len);
			cout << "(" << x << ", " << y << ") = " << score << endl;
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

//Check a strip of the board for any matching sequences
int Game::checkrow(int row[], int length)
{
	int count = 1;
	int max = 0;
	int prev = -1;
	for (int i = 0; i != length; ++i)
	{
		if (row[i] == prev)
		{
			count++;
		} else {
			if (count > max) max = count;
			count = 1;
		}
		prev = row[i];
	}
	if (count > max) max = count;
	if (max < 3) max = 0;
	return max;
}

//Get a strip of the board - without overflowing off edges
//dir = -1 for up, dir = 1 for down
//Return value is length, and modifies row
int Game::getrow(int x, int y, int dir, int row[])
{
	if (y+dir < 0) return 0;
	int start = x-3;
	int end = x+3;
	if (start < 0) start = 0;
	if (end > 7) end = 7;
	for (int i = start; i != end; ++i)
	{
		if (i == x)
		{
			row[i-start] = board[y+dir][i];
		} else {
			row[i-start] = board[y][i];
		}
	}
	
	return end-start;
}