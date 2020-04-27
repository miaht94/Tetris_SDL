#include "Board.h"
Board::Board() {
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
	};
}
Board::Board(SDL_Renderer* renderer)
{
	Board::setRenderer(renderer);
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

	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			this->square[i][j] = View(this->renderer);
		}
	}
	Board::initMaterial();
};
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
	this->update();
	SDL_Point curr_block_location = block.matrix_origin_point;
	copyBoard(this->static_board, this->board);
	Board::setMatrix(block.matrix, this->board,curr_block_location,block.current_block);
	for (int j = 0; j < WIDTH_SQUARE; j++) {
		for (int i = 0; i < HEIGHT_SQUARE; i++) {

				SDL_Rect des = {this->origin_point.x + j * LENGTH_SQUARE + 2,this->origin_point.y + i * LENGTH_SQUARE + 2,LENGTH_SQUARE - 4,LENGTH_SQUARE - 4 };
				this->square[i][j].setRect(des);
				this->square[i][j].texture = (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture;
				this->square[i][j].render();
				//SDL_RenderFillRect(this->renderer, &des);
				//SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].clip, &des);
			
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
			for (int j = 0; j < WIDTH_SQUARE; j++) {
				this->square[i][j].setAnimation("Disappear", 500);
				this->square[i][j].ended = false;
			}
			score_gained += 100;

			/*
			for (int k = i + OFFSET_Y; k > OFFSET_Y; k--) {
				for (int l = 0; l < WIDTH_SQUARE + 2 * OFFSET_X; l++) {
					this->static_board[k][l] = this->static_board[k - 1][l];
				}
			}
			for (int l = 0; l < WIDTH_SQUARE; l++) {
				this->static_board[OFFSET_Y][l + OFFSET_X] = 0;
			}
			i--;*/
		}

	};
	return score_gained;
}

void Board::update()
{
	if (this->animationEnded()) {
		for (int i = 0; i < HEIGHT_SQUARE; i++) {
			bool full_filled = true;
			for (int j = 0; j < WIDTH_SQUARE; j++) {
				if (this->static_board[i + OFFSET_Y][j + OFFSET_X] == 0) full_filled = false;
			};
			if (full_filled) {
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
	}
}

bool Board::animationEnded() {
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			if (!this->square[i][j].ended) return false;
		}
	};
	return true;
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
bool Board::isGameOver()
{
	for (int i = 0; i < WIDTH_SQUARE; i++) {
		if (static_board[OFFSET_Y - 1][OFFSET_X + i] != 0) return true;
	};
	return false;
}
void Board::reset()
{
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			this->board[i + OFFSET_Y][j + OFFSET_X] = 0;
			this->static_board[i + OFFSET_Y][j + OFFSET_X] = 0;
		}
	}
}
;
