#pragma once
#include <iostream>
#include <SDL_stdinc.h>
#include <SDL_scancode.h>
#include <SDL_rect.h>
using namespace std;
//Length of each square's edge
const int LENGTH_SQUARE = 30;

//Number of square on board
const int WIDTH_SQUARE = 15;
const int HEIGHT_SQUARE = 20;

// TIME HOLDER index of each key
const int LEFT_ARROW = 0;
const int UP_ARROW = 1;
const int DOWN_ARROW = 2;
const int RIGHT_ARROW = 3;

//Text Config
const int FONT_SIZE = 36;

//Renderer Viewport
const SDL_Rect SCORE_VIEWPORT = { 0, 0, WIDTH_SQUARE * LENGTH_SQUARE, 70 };
const SDL_Rect BOARD_VIEWPORT = { 0, SCORE_VIEWPORT.h, WIDTH_SQUARE * LENGTH_SQUARE, HEIGHT_SQUARE * LENGTH_SQUARE };

extern int TIME_HOLDER[4];

//Window Config
const int SCREEN_WIDTH = BOARD_VIEWPORT.w;
const int SCREEN_HEIGHT = BOARD_VIEWPORT.h + SCORE_VIEWPORT.h;

/*
Type 1:
	_____________
	|_1_|_2_|_3_|
	|_4_|_5_|_6_|
	|_7_|_8_|_9_|

Type 2: (Only I and O Block)
	_________________________
	|__1__|__2__|__3__|__4__|
	|__5__|__6__|__7__|__8__|
	|__9__|_10__|_11__|_12__|
	|_13__|_14__|_15__|_16__|
*/
const int FIGURE[7][4] = {
							{5,  6,  7,   8}, // S
							{4,  5,  8,   9}, // Z
							{2,  6, 10,  14}, // I
							{2,  5,  8,   9}, // L
							{2,  5,  7,   8}, // _|
							{4,  5,  6,   8}, // T 
							{6,  7,  10, 11} // O
};
// EDGE'S LENGTH of each matrix's FIGURE (2 type : 3x3 (almost block) , 4x4 (only I and O block)) 
const int LENGTH_EDGE[7] = { 3, 3, 4, 3, 3, 3, 4 };
// Because Board exceed 4 square on TOP to render block at starting point
// to access the player_board[x][y] must access board[OFFSET_X + x][OFFSET_Y + y] 
const int OFFSET_X = 2;
const int OFFSET_Y = 4;

// Function for process Block
void rotate(int matrix[][4], int n);
void copyMatrix(int src[][4], int des[][4], int n);
void copyBoard(int** src, int des[][WIDTH_SQUARE + 2 * OFFSET_X]);

//Function to handle key press
void handle(const Uint8 *current_key_state);