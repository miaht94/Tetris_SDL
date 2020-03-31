#include "Block.h"

Block::Block()
{
	//Set Appear Location for Block on middle top 
	this->matrix_origin_point.x = (WIDTH_SQUARE + 4) / 2;
	this->matrix_origin_point.y = 0;
}

Block::~Block()
{
	//Generate random Block for FIGURE
	srand(time(NULL));
	int rand_number = rand() % 6;
	this->current_block = rand_number;
	int count = 1;
	int mark = 0;
	for (int i = 0; i < LENGTH_EDGE[current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[current_block]; j++) {
			if (FIGURE[current_block][mark] == count) {

				this->matrix[i][j]=this->current_color;
				mark++;
			}
			else this->matrix[i][j] = 0;
			count++;
		}
	};
};

void Block::rotate()
{
}

int Block::Render()
{
	return 0;
}
