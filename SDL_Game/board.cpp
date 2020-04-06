#include "Board.h"
Board::Board(SDL_Renderer* renderer)
{
	Board::setRenderer(renderer);
	for (int i = 0; i < WIDTH_SQUARE + 2 * OFFSET_X; i++) {
		this->board[i][HEIGHT_SQUARE + OFFSET_Y] = 1;
		this->static_board[i][HEIGHT_SQUARE + OFFSET_Y] = 1;
	};
	for (int i = 0; i < HEIGHT_SQUARE + OFFSET_Y; i++) {
		for (int j = 0; j < OFFSET_X; j++) {
			this->board[j][i] = 1;
			this->static_board[j][i] = 1;
			this->board[WIDTH_SQUARE + 2*OFFSET_X - j - 1][i] = 1;
			this->static_board[WIDTH_SQUARE + 2 * OFFSET_X - j - 1][i] = 1;
		}
	}
	//Board::initMaterial();
};

Board::~Board()
{
	
}
void Board::initMaterial()
{
	(this->pieces)[0].loadTexture("textures/Block_0.png") != true ? std::cout << "Couldn't load texture /textures/Block_0.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[1].loadTexture("textures/Block_1.png") != true ? std::cout << "Couldn't load texture /textures/Block_1.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[2].loadTexture("textures/Block_2.png") != true ? std::cout << "Couldn't load texture /textures/Block_2.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[3].loadTexture("textures/Block_3.png") != true ? std::cout << "Couldn't load texture /textures/Block_3.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[4].loadTexture("textures/Block_4.png") != true ? std::cout << "Couldn't load texture /textures/Block_4.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[5].loadTexture("textures/Block_5.png") != true ? std::cout << "Couldn't load texture /textures/Block_5.png in initMaterial for Board" << std::endl : std::cout << "";
}
;

void Board::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	(this->pieces)[0].renderer = this->renderer;
	(this->pieces)[1].renderer = this->renderer;
	(this->pieces)[2].renderer = this->renderer;
	(this->pieces)[3].renderer = this->renderer;
	(this->pieces)[4].renderer = this->renderer;
	(this->pieces)[5].renderer = this->renderer;
	Board::initMaterial();
};
void Board::drawNet(SDL_Point start_point)
{
	if (this->renderer == NULL) cerr << "Please set Renderer for Board"; else {
		for (int i = 0; i < this->width_square; i++) {

			for (int j = 0; j < this->height_square; j++) {

				//SDL_SetRenderDrawColor(this->renderer, 100, 100, 100, 100);
				SDL_Rect temp_rect = { i * LENGTH_SQUARE + 1, j * LENGTH_SQUARE + 1, LENGTH_SQUARE - 2, LENGTH_SQUARE - 2 };
				//SDL_RenderDrawRect(this->renderer, &temp_rect);
				SDL_RenderCopy(this->renderer, (this->pieces)[0].texture, (this->pieces)[0].clip, &temp_rect);
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
				SDL_Rect des = { i * LENGTH_SQUARE + 1,j * LENGTH_SQUARE + 1,LENGTH_SQUARE - 2,LENGTH_SQUARE - 2 };
				//SDL_RenderFillRect(this->renderer, &des);
				SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_X][j + OFFSET_Y]].texture, (this->pieces)[this->board[i + OFFSET_X][j + OFFSET_Y]].clip, &des);
			}
		}
	}
}
void Board::checkGainPoint()
{
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {

		}
	}
}
/*
void Board::renderBoard(Block block, int time)
{
	for (int i = 0; i < WIDTH_SQUARE; i++) {
		for (int j = 0; j < HEIGHT_SQUARE; j++) {
			if (this->static_board[i + OFFSET_X][j + OFFSET_Y] != 0) {
				SDL_Rect des = { i * LENGTH_SQUARE,j * LENGTH_SQUARE,LENGTH_SQUARE,LENGTH_SQUARE };
				SDL_RenderCopy(this->renderer, (this->pieces).texture, (this->pieces).clip, &des);
			}
		}
	}
	for (int i = 0; i < LENGTH_EDGE[block.current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[block.current_block]; j++) {
			if (block.matrix[j][i] != 0) {
				SDL_Rect des = { (i + block.matrix_origin_point.x - OFFSET_X) * LENGTH_SQUARE, (j + block.matrix_origin_point.y - OFFSET_Y) * LENGTH_SQUARE + (time * LENGTH_SQUARE) / 1000, LENGTH_SQUARE, LENGTH_SQUARE };
				SDL_RenderCopy(this->renderer, (this->pieces).texture, (this->pieces).clip, &des);
			}
		}
	}
}
*/
bool Board::isAvailable(int matrix[][4], int board[][HEIGHT_SQUARE + OFFSET_Y + 1], SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			if ((matrix[i][j] != 0) && (board[location.x + j][location.y + i] != 0)) return false;
		}
	}
	return true;
}
;
