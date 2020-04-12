#include "Board.h"
Board::Board(SDL_Renderer* renderer)
{
	Board::setRenderer(renderer);
	for (int i = 0; i < HEIGHT_SQUARE + OFFSET_Y + 1; i++) {
		(this->static_board)[i] = new int[WIDTH_SQUARE + 2 * OFFSET_X];
	};
	for (int i = 0; i < HEIGHT_SQUARE + OFFSET_Y + 1; i++) {
		for (int j = 0; j < WIDTH_SQUARE + 2 * OFFSET_X; j++) {
			(this->static_board)[i][j] = 0;
		}
	};
	for (int i = 0; i < WIDTH_SQUARE + 2 * OFFSET_X; i++) {
		this->board[HEIGHT_SQUARE + OFFSET_Y][i] = 1;
		this->static_board[HEIGHT_SQUARE + OFFSET_Y][i] = 1;
	};
	for (int i = 0; i < HEIGHT_SQUARE + OFFSET_Y; i++) {
		for (int j = 0; j < OFFSET_X; j++) {
			this->board[i][j] = 1;
			this->static_board[i][j] = 1;
			this->board[i][WIDTH_SQUARE + 2 * OFFSET_X - j - 1] = 1;
			this->static_board[i][WIDTH_SQUARE + 2 * OFFSET_X - j - 1] = 1;
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
void Board::setMatrix(int matrix[][4], int board[][WIDTH_SQUARE + 2 * OFFSET_X], SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			// Direcion of board opposite with matrix =)))
			// It's my fault but i'm so lazy to fix
			if (matrix[i][j] != 0) board[i + location.y][j + location.x] = matrix[i][j]; //Dangerous !!!
		}
	}
}

// Danger: Must check available before setMatrix because have no checkAvailable in this function
void Board::setMatrix(int matrix[][4], int** board, SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			if (matrix[i][j] != 0) 
				board[i + location.y][j + location.x] = matrix[i][j]; //Dangerous !!!
		}
	}
}
void Board::renderBoard(Block block)
{
	SDL_Point curr_block_location = block.matrix_origin_point;
	copyBoard(this->static_board, this->board);
	Board::setMatrix(block.matrix, this->board,curr_block_location,block.current_block);
	for (int j = 0; j < WIDTH_SQUARE; j++) {
		for (int i = 0; i < HEIGHT_SQUARE; i++) {

				SDL_Rect des = { j * LENGTH_SQUARE + 1,i * LENGTH_SQUARE + 1,LENGTH_SQUARE - 2,LENGTH_SQUARE - 2 };
				//SDL_RenderFillRect(this->renderer, &des);
				SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].clip, &des);
			
		}
	}
}
long Board::checkGainPoint()
{
	long score_gained = 0;
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		bool full_filled = true;
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			if (this->static_board[i + OFFSET_Y][j + OFFSET_X] == 0) full_filled = false;
		};
		if (full_filled) {

			/*delete[](this->static_board[i + OFFSET_Y]);
			for (int k = i; k > OFFSET_Y; k--) {
				(this->static_board)[k + OFFSET_Y] = (this->static_board)[k + OFFSET_Y - 1];
			};
			(this->static_board[OFFSET_Y]) = new int[WIDTH_SQUARE + 2 * OFFSET_X];
			for (int k = 0; k < OFFSET_X; k++) {

				(this->static_board)[OFFSET_Y][k] = 1;
				(this->static_board)[OFFSET_Y][WIDTH_SQUARE + 2 * OFFSET_X - k - 1] = 1;
			};
			for (int k = 0; k < WIDTH_SQUARE; k++) {
				(this->static_board)[OFFSET_Y][k + OFFSET_X] = 0;
			}*/
			score_gained += 100;
			for (int k = i + OFFSET_Y; k > OFFSET_Y; k--) {
				for (int l = 0; l < WIDTH_SQUARE + 2 * OFFSET_X; l++) {
					this->static_board[k][l] = this->static_board[k - 1][l];
				}
			}
			for (int l = 0; l < WIDTH_SQUARE; l++) {
				this->static_board[OFFSET_Y][l + OFFSET_X] = 0;
			}
			i--;
		}

	};
	return score_gained;
}
bool Board::isAvailable(int matrix[][4], int** board, SDL_Point location, int curr_block)
{
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			if ((matrix[i][j] != 0) && (board[location.y + i][location.x + j] != 0)) return false;
		}
	}
	return true;
}
;
