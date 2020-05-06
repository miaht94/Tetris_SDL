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
	(this->pieces)[0].loadTexture("textures/block_empty.png") != true ? std::cout << "Couldn't load texture /textures/block_empty.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[1].loadTexture("textures/Block_1.png") != true ? std::cout << "Couldn't load texture /textures/Block_1.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[2].loadTexture("textures/Block_2.png") != true ? std::cout << "Couldn't load texture /textures/Block_2.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[3].loadTexture("textures/Block_3.png") != true ? std::cout << "Couldn't load texture /textures/Block_3.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[4].loadTexture("textures/Block_4.png") != true ? std::cout << "Couldn't load texture /textures/Block_4.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[5].loadTexture("textures/Block_5.png") != true ? std::cout << "Couldn't load texture /textures/Block_5.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[6].loadTexture("textures/Block_1_.png") != true ? std::cout << "Couldn't load texture /textures/Block_1_.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[7].loadTexture("textures/Block_2_.png") != true ? std::cout << "Couldn't load texture /textures/Block_2_.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[8].loadTexture("textures/Block_3_.png") != true ? std::cout << "Couldn't load texture /textures/Block_3_.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[9].loadTexture("textures/Block_4_.png") != true ? std::cout << "Couldn't load texture /textures/Block_4_.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[10].loadTexture("textures/Block_5_.png") != true ? std::cout << "Couldn't load texture /textures/Block_5_.png in initMaterial for Board" << std::endl : std::cout << "";
    (this->pieces)[11].loadTexture("textures/block_locked.png") != true ? std::cout << "Couldn't load texture /textures/block_locked.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[12].loadTexture("textures/block_killed.png") != true ? std::cout << "Couldn't load texture /textures/block_killed.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[13].loadTexture("textures/hard_drop.png") != true ? std::cout << "Couldn't load texture /textures/hard_drop.png in initMaterial for Board" << std::endl : std::cout << "";
	(this->pieces)[13].setAlpha(150);
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
	(this->pieces)[6].renderer = this->renderer;
	(this->pieces)[7].renderer = this->renderer;
	(this->pieces)[8].renderer = this->renderer;
	(this->pieces)[9].renderer = this->renderer;
	(this->pieces)[10].renderer = this->renderer;
	(this->pieces)[11].renderer = this->renderer;
	(this->pieces)[12].renderer = this->renderer;
	(this->pieces)[13].renderer = this->renderer;
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			this->square[i][j] = View(this->renderer);
		}
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->block_square[i][j] = View(this->renderer);
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->block_effect[i][j] = View(this->renderer);
			this->block_effect[i][j].texture_may_null = true;
		}
	}
	Board::initMaterial();
};
// Danger: Must check available before setMatrix because have no checkAvailable in this function
//void Board::setMatrix(int matrix[][4], int board[][WIDTH_SQUARE + 2 * OFFSET_X], SDL_Point location, int curr_block)
//{
//	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
//		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			// Direcion of board opposite with matrix =)))
			// It's my fault but i'm so lazy to fix
//			if (matrix[i][j] != 0) board[i + location.y][j + location.x] = matrix[i][j]; //Dangerous !!!
//		}
//	};
//}
// Danger: Must check available before setMatrix because have no checkAvailable in this function
void Board::setMatrixToStaticBoard(const Block& block)
{
	int curr_block = block.current_block;
	SDL_Point location = block.matrix_origin_point;
	//SDL_Point end_point = this->getEndPoint(block);
	//bool effect = false;
	/*if (end_point.x == location.x && end_point.y - 1 == location.y) {
		effect = true;
	}*/
	for (int i = 0; i < LENGTH_EDGE[curr_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[curr_block]; j++) {
			if (block.matrix[i][j] != 0) {
				this->static_board[i + location.y][j + location.x] = block.matrix[i][j]; //Dangerous !!!
				SDL_Rect des_effect = { this->origin_point.x + (location.x - OFFSET_X + j) * LENGTH_SQUARE - 1,this->origin_point.y + (i + location.y - OFFSET_Y) * LENGTH_SQUARE + 1, LENGTH_SQUARE, LENGTH_SQUARE };
				View* new_effect = new View(this->renderer);
				new_effect->texture = this->pieces[11].texture;
				new_effect->setRect(des_effect);
				new_effect->setAnimation("Scale Up", 500);
				this->addViewEffect(new_effect);
				//this->block_effect[i][j].setRect(des_effect);
				//this->block_effect[i][j].setAnimation("Switch Texture", 500, pieces[11].texture);
				//this->block_effect[i][j].setAnimation("Scale Up", 500);
			}
			//if (effect && block.matrix[i][j] != 0 && end_point.y - OFFSET_Y + i >= 0) board.square[end_point.y - OFFSET_Y + i][end_point.x - OFFSET_X + j].setAnimation("Fade Out", 500);
		}
	};
	
}

void Board::renderNet()
{
	for (int j = 0; j < WIDTH_SQUARE; j++) {
		for (int i = 0; i < HEIGHT_SQUARE; i++) {

			SDL_Rect des = { this->origin_point.x + j * LENGTH_SQUARE ,this->origin_point.y + i * LENGTH_SQUARE ,LENGTH_SQUARE ,LENGTH_SQUARE };
			this->pieces[0].setRect(des);
			this->pieces[0].render();
			//SDL_RenderFillRect(this->renderer, &des);
			//SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].clip, &des);

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
	this->renderNet();
	this->renderStaticBoard();
	this->renderPredict(block);
	//Board::setMatrix(block, *this);
	this->renderBlock(block);
	this->renderEffect();
	//for (int j = 0; j < WIDTH_SQUARE; j++) {
	//	for (int i = 0; i < HEIGHT_SQUARE; i++) {

	//			SDL_Rect des = {this->origin_point.x + j * LENGTH_SQUARE ,this->origin_point.y + i * LENGTH_SQUARE ,LENGTH_SQUARE ,LENGTH_SQUARE  };
	//			this->square[i][j].setRect(des);
	//			this->square[i][j].texture = (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture;
	//			if (this->board[i + OFFSET_Y][j + OFFSET_X])
	//				this->square[i][j].render();
				//SDL_RenderFillRect(this->renderer, &des);
				//SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].clip, &des);
			
	//	}
	//}
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
				this->square[i][j].setAnimation("Fade Out", 500);
				SDL_Rect effect_rect = { this->origin_point.x + j * LENGTH_SQUARE,this->origin_point.y + i * LENGTH_SQUARE, LENGTH_SQUARE, LENGTH_SQUARE };
				View* new_effect = new View(this->renderer);
				new_effect->texture = this->pieces[12].texture;
				new_effect->texture_may_null = true;
				new_effect->setRect(effect_rect);
				Animation* animation = new Animation("Rotate", 500, double(180), 20*j);
				new_effect->setAnimation(animation);
				new_effect->setAnimation("Scale Up", 300,20*j);
				new_effect->setAnimation("Disappear", 200, 300 + 20*j);
				this->arr_effect.push_back(new_effect);
				//this->delete_queue.push_back({ i, j });
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
	vector<View*>::iterator it = this->arr_effect.begin();
	while (it != this->arr_effect.end()) {
		if ((*it)->animation_queue.size() == 0) {
			this->arr_effect.erase(it);
			it = this->arr_effect.begin();
			continue;
		};
		it++;
	}
}

bool Board::animationEnded() {
	for (int i = 0; i < HEIGHT_SQUARE; i++) {
		for (int j = 0; j < WIDTH_SQUARE; j++) {
			if (this->square[i][j].animation_queue.size() != 0) return false;
		}
	};
	return true;
}
bool Board::isAvailable(const int matrix[][4], int** board, SDL_Point location, int curr_block)
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
void Board::addViewEffect(View* effect)
{
	if (effect->renderer == NULL) {
		effect->setRenderer(this->renderer);
	}
	arr_effect.push_back(effect);
}
SDL_Point Board::getEndPoint(const Block& block)
{
	SDL_Point check_point = { block.matrix_origin_point.x, block.matrix_origin_point.y };

	while (this->isAvailable(block.matrix, this->static_board, check_point, block.current_block)) {
		check_point.y++;
	};
	check_point.y--;
	return check_point;
}
void Board::drawHardDropEffect(const Block& block)
{
	SDL_Point current_location = block.matrix_origin_point;
	SDL_Point end_point = this->getEndPoint(block);
	for (int i = 0; i < LENGTH_EDGE[block.current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[block.current_block]; j++) {
			if (block.matrix[i][j]) {
				View* new_effect = new View(this->renderer);
				SDL_Rect rect_effect;
				rect_effect.x = this->origin_point.x + (block.matrix_origin_point.x + j - OFFSET_X) * LENGTH_SQUARE;
				rect_effect.y = this->origin_point.y + (block.matrix_origin_point.y + i - OFFSET_Y) * LENGTH_SQUARE;
				rect_effect.w = LENGTH_SQUARE;
				rect_effect.h = (end_point.y - current_location.y) * LENGTH_SQUARE;
				new_effect->texture = this->pieces[13].texture;
				new_effect->setRect(rect_effect);
				new_effect->setAnimation("Cut Down", 300);
				this->addViewEffect(new_effect);
			}
		}
	}
	
	
}
void Board::renderPredict(const Block& block)
{
	SDL_Point check_point = getEndPoint(block);
	//SDL_Rect des = {this->origin_point.x + j * LENGTH_SQUARE ,this->origin_point.y + i * LENGTH_SQUARE ,LENGTH_SQUARE ,LENGTH_SQUARE  };
	for (int i = 0; i < LENGTH_EDGE[block.current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[block.current_block]; j++) {
			if (block.matrix[i][j] != 0) {
				//this->board[check_point.y + i][check_point.x + j] = block.current_color + 5;
				SDL_Rect des = { this->origin_point.x + (check_point.x + j - OFFSET_X) * LENGTH_SQUARE, this->origin_point.y + (check_point.y + i - OFFSET_Y) * LENGTH_SQUARE, LENGTH_SQUARE, LENGTH_SQUARE };
				pieces[block.current_color + 5].setRect(des);
				pieces[block.current_color + 5].render();
			}
		}
	}
}
void Board::renderStaticBoard()
{
	for (int j = 0; j < WIDTH_SQUARE; j++) {
		for (int i = 0; i < HEIGHT_SQUARE; i++) {

			SDL_Rect des = { this->origin_point.x + j * LENGTH_SQUARE ,this->origin_point.y + i * LENGTH_SQUARE ,LENGTH_SQUARE ,LENGTH_SQUARE };
			this->square[i][j].setRect(des);
			this->square[i][j].texture = (this->pieces)[this->static_board[i + OFFSET_Y][j + OFFSET_X]].texture;
			if (this->static_board[i + OFFSET_Y][j + OFFSET_X])
				this->square[i][j].render();
			//SDL_RenderFillRect(this->renderer, &des);
			//SDL_RenderCopy(this->renderer, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].texture, (this->pieces)[this->board[i + OFFSET_Y][j + OFFSET_X]].clip, &des);

		}
	}
}
void Board::renderBlock(const Block& block)
{
	//if (block.matrix[i][j] != 0) board.board[i + location.y][j + location.x] = block.matrix[i][j]; //Dangerous !!!
	//if (effect && block.matrix[i][j] != 0 && end_point.y - OFFSET_Y + i >= 0) board.square[end_point.y - OFFSET_Y + i][end_point.x - OFFSET_X + j].setAnimation("Fade Out", 500);
	SDL_Point location = block.matrix_origin_point;
	SDL_Point end_point = this->getEndPoint(block);
	bool effect = false;
	if (end_point.x == location.x && end_point.y -1== location.y) {
		effect = true;
	}
	for (int i = 0; i < LENGTH_EDGE[block.current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[block.current_block]; j++) {
			if (block.matrix[i][j] && location.x + j - OFFSET_X >= 0 && location.y + i - OFFSET_Y >= 0) {
				SDL_Rect des = { this->origin_point.x + (location.x + j - OFFSET_X) * LENGTH_SQUARE, this->origin_point.y + (location.y + i - OFFSET_Y) * LENGTH_SQUARE,  LENGTH_SQUARE, LENGTH_SQUARE };
				this->block_square[i][j].texture = pieces[block.current_color].texture;
				this->block_square[i][j].setRect(des);
				if (effect) 
					this->block_square[i][j].setAnimation("Fade Out", 900);
				this->block_square[i][j].render();
			};
		}
	}
}
void Board::renderEffect()
{
	vector<View*>::iterator it = this->arr_effect.begin();
	while (it != arr_effect.end()) {
		(*it)->render();
		it++;
	};
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
