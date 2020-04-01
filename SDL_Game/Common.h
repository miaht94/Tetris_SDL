#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>

using namespace std;


const int LENGTH_SQUARE = 30;
const int WIDTH_SQUARE = 15;
const int HEIGHT_SQUARE = 20;
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
const int FIGURE[6][4] = {
							{5,  6,  7,   8}, // S
							{4,  5,  8,   9}, // Z
							{2,  6, 10,  14}, // I
							{2,  5,  8,   9}, // L
							{2,  5,  7,   8}, // _|
							{4,  5,  6,   8}, // T 
};
// EDGE'S LENGTH of each matrix's FIGURE (2 type : 3x3 (almost block) , 4x4 (only I block)) 
const int LENGTH_EDGE[6] = { 3, 3, 4, 3, 3, 3 };
// Because Board exceed 4 square on TOP to render block at starting point
// to access the player_board[x][y] must access board[OFFSET_X + x][OFFSET_Y + y] 
const int OFFSET_X = 4;
const int OFFSET_Y = 2;

//bool checkResource(View view);
// Function to config game
bool Init();
//bool playGame();


// Function for process Block
void rotate(int matrix[][4], int n);
void copyMatrix(int src[][4], int des[][4], int n);