#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "Common.h"
class Block
{
private:

public:
/*
Type 1:
	_____________
	|_1_|_2_|_3_|
	|_4_|_5_|_6_|
	|_7_|_8_|_9_|

Type 2: (Only I Block)
	_________________________
	|__1__|__2__|__3__|__4__|
	|__5__|__6__|__7__|__8__|
	|__9__|_10__|_11__|_12__|
	|_13__|_14__|_15__|_16__|
*/
	int matrix[4][4] = { {0} };
	int current_block = -1;
	int current_color = -1;
	SDL_Point matrix_origin_point = { 0,0 };
	Block();
	~Block();
	void rotate();
	int Render();
};

