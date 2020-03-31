#include "Board.h"
Board::Board()
{
	Board::initMaterial();
};

Board::~Board()
{
	//Do Nothing
}
void Board::initMaterial()
{
	(this->pieces).loadTexture("/textures/block.png") != false ? std::cout << "Couldn't load texture /textures/block.png in initMaterial for Board" <<std::endl : cout << "";
}
;

void Board::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
};
void Board::drawNet(SDL_Point start_point)
{
	if (this->renderer == NULL) cerr << "Please set Renderer for Board"; else {
		for (int i = 0; i < this->width_square; i++) {

			for (int j = 0; j < this->height_square; j++) {

				SDL_SetRenderDrawColor(this->renderer, 100, 100, 100, 100);
				SDL_Rect temp_rect = { i * LENGTH_SQUARE, j * LENGTH_SQUARE, LENGTH_SQUARE, LENGTH_SQUARE };
				SDL_RenderDrawRect(this->renderer, &temp_rect);

			}

		}
	}
}
// Danger: Must check available before setMatrix because have no checkAvailable in this function
void Board::setMatrix(int matrix[][4], int board[][HEIGHT_SQUARE + 2 * OFFSET_Y], SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			if (matrix[i][j] != 0) board[i][j] = matrix[i][j]; //Dangerous !!!
		}
	}
}
void Board::renderBoard(Block block)
{
	SDL_Point curr_block_location = block.matrix_origin_point;
	Board::setMatrix(block.matrix, board,curr_block_location,block.current_block);
	for (int i = 0; i < WIDTH_SQUARE; i++) {
		for (int j = 0; j < HEIGHT_SQUARE; j++) {
			if (this->board[i + OFFSET_X][j + OFFSET_Y]) {
				SDL_Rect des = { i * LENGTH_SQUARE,j * LENGTH_SQUARE,LENGTH_SQUARE,LENGTH_SQUARE };
				SDL_RenderCopy(this->renderer, (this->pieces).texture, (this->pieces).clip, &des);
			}
		}
	}
}
;
