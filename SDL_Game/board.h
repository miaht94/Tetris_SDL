#pragma once
#include <iostream>
#include "Common.h"
#include "View.h"
#include "Block.h"
#include "vector"
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
		View* pieces = new View[15];
		View block_square[4][4];
		View square[HEIGHT_SQUARE][WIDTH_SQUARE];

		//handle effect
		View block_effect[4][4];
		vector<View*> arr_effect;
		
		Board();

		Board(SDL_Renderer* renderer);
		~Board();
		void initMaterial();
		void setRenderer(SDL_Renderer* renderer);

		// Danger: Must check available before setMatrix because have no checkAvailable in this function
		//void setMatrix(int matrix[][4], int board[][WIDTH_SQUARE + 2 * OFFSET_X], SDL_Point location, int curr_block);

		// Danger: Must check available before setMatrix because have no checkAvailable in this function
		void setMatrix(int matrix[][4], int** board, SDL_Point location, int curr_block);

		void setMatrixToStaticBoard(const Block& block);
		
		void renderNet();

		void renderPredict(const Block& block);
		
		void renderStaticBoard();

		void renderBlock(const Block& block);

		void renderEffect();
		//parram Block block: current Block moving on the board
		void renderBoard(Block block);

		//void renderBoard(Block block, int time);
		
		long checkGainPoint();

		void update();

		bool animationEnded();

		// True if available; False if not
		bool isAvailable(const int matrix[][4], int** board, SDL_Point location, int curr_block);

		//check game over
		bool isGameOver();

		bool clearLine(int line);

		void addViewEffect(View* effect);

		SDL_Point getEndPoint(const Block& block);

		void drawHardDropEffect(const Block& block);

		void reset();
};
