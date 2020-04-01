#include "Block.h"

Block::Block()
{
	//Set Appear Location for Block on middle top 
	this->matrix_origin_point.x = (WIDTH_SQUARE + 4) / 2;
	this->matrix_origin_point.y = 0;

	//Generate random Block for FIGURE
	int rand_number = rand() % 6;
	this->current_block = rand_number;
	int count = 1;
	int mark = 0;
	for (int i = 0; i < LENGTH_EDGE[current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[current_block]; j++) {
			if (FIGURE[current_block][mark] == count) {

				this->matrix[i][j] = this->current_color;
				mark++;
			}
			else this->matrix[i][j] = 0;
			count++;
		}
	};
}

Block::~Block()
{
	//Do Nothing
};

void Block::rotate()
{
	int temp_matrix[4][4];

	copyMatrix(this->matrix, temp_matrix, LENGTH_EDGE[this->current_block]);
	
	for (int i = 0; i < LENGTH_EDGE[this->current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[this->current_block]; j++) {

			this->matrix[i][j] = temp_matrix[j][LENGTH_EDGE[this->current_block] - i - 1];

		}
	}
}

int Block::Render()
{
	return 0;
}
