#include "Board.h"
Board::Board(SDL_Renderer* renderer)
{
	Board::setRenderer(renderer);
	for (int i = 0; i < WIDTH_SQUARE + 2 * OFFSET_X; i++) {
		this->board[i][HEIGHT_SQUARE + 2 * OFFSET_Y] = 1;
		this->static_board[i][HEIGHT_SQUARE + 2 * OFFSET_Y] = 1;
	};
	for (int i = 0; i < HEIGHT_SQUARE + OFFSET_Y; i++) {
		for (int j = 0; j < OFFSET_X; j++) {
			this->board[i][j] = 1;
			this->static_board[i][j] = 1;
			this->board[i][WIDTH_SQUARE - j - 1];
			this->static_board[i][WIDTH_SQUARE - j - 1];
		}
	}
	//Board::initMaterial();
};

Board::~Board()
{
	
}
void Board::initMaterial()
{
	srand(time(NULL));
	(this->pieces).loadTexture("textures/block.png") != true ? std::cout << "Couldn't load texture /textures/block.png in initMaterial for Board" <<std::endl : cout << "";
}
;

void Board::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	(this->pieces).renderer = this->renderer;
	Board::initMaterial();
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
void Board::setMatrix(int matrix[][4], int board[][HEIGHT_SQUARE + OFFSET_Y + 1], SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			// Direcion of board opposite with matrix =)))
			// It's my fault but i'm so lazy to fix
			if (matrix[i][j] != 0) board[j+location.x][i+location.y] = matrix[i][j]; //Dangerous !!!
		}
	}
}
void Board::renderBoard(Block block)
{
	SDL_Point curr_block_location = block.matrix_origin_point;
	copyBoard(this->static_board, this->board);
	Board::setMatrix(block.matrix, board,curr_block_location,block.current_block);
	for (int i = 0; i < WIDTH_SQUARE; i++) {
		for (int j = 0; j < HEIGHT_SQUARE; j++) {
			if (this->board[i + OFFSET_X][j + OFFSET_Y]!=0) {
				SDL_Rect des = { i * LENGTH_SQUARE,j * LENGTH_SQUARE,LENGTH_SQUARE,LENGTH_SQUARE };
				//SDL_RenderFillRect(this->renderer, &des);
				SDL_RenderCopy(this->renderer, (this->pieces).texture, (this->pieces).clip, &des);
			}
		}
	}
}
bool Board::isAvailable(int matrix[][4], int board[][HEIGHT_SQUARE + OFFSET_Y + 1], SDL_Point location)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((matrix[j][i] != 0) && (board[location.x + OFFSET_X][location.y + OFFSET_Y] != 0)) return false;
		}
	}
	return true;
}
;
