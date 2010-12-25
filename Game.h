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

public:
	Game(OSHandler* oshandler, int bx, int by, int off);

	void readboard();
};

#endif