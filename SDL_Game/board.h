#pragma once
#include <iostream>
#include "Common.h"
#include "View.h"
#include "Block.h"

class Board
{
	private:
		SDL_Renderer* renderer;
	public:
		const int width_square = WIDTH_SQUARE;
		const int height_square = HEIGHT_SQUARE;

		SDL_Point origin_point = { BOARD_VIEWPORT.x, BOARD_VIEWPORT.y };
		//array for background processing
		int board[HEIGHT_SQUARE + OFFSET_Y + 1][WIDTH_SQUARE + 2 * OFFSET_X] = { {0} };

		//array for rendering what player can see
		//static board will be update whenever block finished its fall
		int** static_board = new int*[HEIGHT_SQUARE + OFFSET_Y + 1];

		View* pieces = new View[6];
		View square[HEIGHT_SQUARE][WIDTH_SQUARE];
		Board();

		Board(SDL_Renderer* renderer);
		~Board();
		void initMaterial();
		void setRenderer(SDL_Renderer* renderer);

		// Danger: Must check available before setMatrix because have no checkAvailable in this function
		void setMatrix(int matrix[][4], int board[][WIDTH_SQUARE + 2 * OFFSET_X], SDL_Point location, int curr_block);

		// Danger: Must check available before setMatrix because have no checkAvailable in this function
		void setMatrix(int matrix[][4], int** board, SDL_Point location, int curr_block);

		//parram Block block: current Block moving on the board
		void renderBoard(Block block);

		//void renderBoard(Block block, int time);
		
		long checkGainPoint();

		// True if available; False if not
		bool isAvailable(int matrix[][4], int** board, SDL_Point location, int curr_block);

		//check game over
		bool isGameOver();
};
