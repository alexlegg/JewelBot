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

	//Click play button and wait a bit
	os->wait(500);
	os->click(base_x + 55, base_y + 280);
	os->wait(4000);

	//Get the cursor out the way (not sure if needed)
	os->movecursor(0, 0);

	//Get the current board
	readboard();

	printboard();
	cout << endl;

	//Find a move
	int movex, movey;
	bool moveup;
	int maxscore = 0;
	for (int x = 0; x != 8; ++x)
	{
		for (int y = 0; y != 8; ++ y)
		{
			int row1[6], row1len;
			int row2[6], row2len;
			int col1[6], col1len;
			int col2[6], col2len;
			int scoreup = 0, scoredown = 0;

			//Swap vertical (always up, no need to check down swaps)
			row1len = getrow(x, y-1, 1, row1);
			row2len = getrow(x, y, -1, row2);
			col1len = getcol(x, y, 0, col1);

			scoreup += checkstrip(row1, row1len);
			scoreup += checkstrip(row2, row2len);
			scoreup += checkstrip(col1, col1len);
			
			//Swap horizontal (always left)
			row1len = getrow(x, y, 0, col1);
			col1len = getcol(x-1, y, 1, col1);
			col2len = getcol(x, y, -1, col2);

			scoredown += checkstrip(row1, row1len);
			scoredown += checkstrip(col1, col1len);
			scoredown += checkstrip(col2, col2len);

			//Update max score
			if (scoreup > maxscore || scoredown > maxscore)
			{
				movex = x;
				movey = y;
				moveup = (scoreup > scoredown);
				maxscore = (moveup) ? scoreup : scoredown;
			}
		}
	}

	//Print it out for shits n giggles
	if (moveup)
	{
		cout << "Best move: (" << movex << ", " << movey << ", ^) = " << maxscore;
	} else {
		cout << "Best move: (" << movex << ", " << movey << ", <) = " << maxscore;
	}

	//Make the move
	os->click(base_x + (movex * offset), base_y + (movey * offset));
	if (moveup)
	{
		os->click(base_x + (movex * offset), base_y + ((movey-1) * offset));
	} else {
		os->click(base_x + ((movex-1) * offset), base_y + (movey * offset));
	}
}

void Game::readboard()
{
	for (int x = 0; x != 8; ++x)
	{
		for (int y = 0; y != 8; ++y)
		{
			board[x][y] = os->getgem(base_x + (y * offset), base_y + (x * offset));
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
int Game::checkstrip(int strip[], int length)
{
	int count = 1;
	int max = 0;
	int prev = -1;
	for (int i = 0; i != length; ++i)
	{
		if (strip[i] == prev)
		{
			count++;
		} else {
			if (count > max) max = count;
			count = 1;
		}
		prev = strip[i];
	}
	if (count > max) max = count;
	if (max < 3) max = 0;
	return max;
}

//Get a row of the board - without overflowing off edges
//dir = -1 for up, dir = 1 for down, dir = 0 for left
//Yes I realise that doesn't make any sense - fuck you
//Return value is length, and modifies row
int Game::getrow(int x, int y, int dir, int row[])
{
	if (y+dir <= 0) return 0;
	int start = (dir==0) ? x-3 : x-2;
	int end = x+3;
	if (start < 0) start = 0;
	if (end > 8) end = 8;
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

//Get a column of the board - without overflowing off edges
//dir = -1 for up, dir = 1 for down, dir = 0 for left
//Yes I realise that doesn't make any sense - fuck you
//Return value is length, and modifies col
int Game::getcol(int x, int y, int dir, int col[])
{
	if (x+dir <= 0) return 0;
	int start = (dir==0) ? y-3 : y-2;
	int end = y+3;
	if (start < 0) start = 0;
	if (end > 8) end = 8;
	for (int i = start; i != end; ++i)
	{
		if (i == x)
		{
			col[i-start] = board[i][x+dir];
		} else {
			col[i-start] = board[i][x+dir];
		}
	}
	return end-start;
}