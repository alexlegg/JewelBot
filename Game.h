#ifndef GAME_H
#define GAME_H

#include "OSHandler.h"

class Game
{
	int state;
	int board[8][8];
	int time;
	int base_x, base_y, offset;
	OSHandler* os;

	void readboard();
	void printboard();
	int checkrow(int row[], int length);

	//Could probably combine these, but it gets confusing so whatever
	int getrow(int x, int y, int dir, int row[]);
	int getcol(int x, int y, int dir, int row[]);

public:
	Game(OSHandler* oshandler, int bx, int by, int off);

	void play();
};

#endif