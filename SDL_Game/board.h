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

		//array for background processing
		int board[WIDTH_SQUARE+ OFFSET_X][HEIGHT_SQUARE + 2*OFFSET_Y] = { {0} };

		//array for rendering what player can see
		//static board will be update whenever block finished its fall
		int static_board[WIDTH_SQUARE][HEIGHT_SQUARE];

		View pieces;

		Board(SDL_Renderer* renderer);
		~Board();
		void initMaterial();
		void setRenderer(SDL_Renderer* renderer);
		void drawNet(SDL_Point start_point = { 0,0 });

		// Danger: Must check available before setMatrix because have no checkAvailable in this function
		void setMatrix(int matrix[][4], int board[][HEIGHT_SQUARE+2*OFFSET_Y], SDL_Point location,int curr_block);

		//parram Block block: current Block moving on the board
		void renderBoard(Block block);
};
