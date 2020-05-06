#include "Block.h"

Block::Block()
{
	//Set Appear Location for Block on middle top 
	this->matrix_origin_point.x = (WIDTH_SQUARE + 2 * OFFSET_X) / 2 ;
	this->matrix_origin_point.y = 1;

	//Generate random Block for FIGURE
	int rand_number = rand() % 7;
	this->current_block = rand_number;
	this->current_color = rand() % 5 + 1;
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

void Block::rotate(int matrix[][4])
{
	int temp_matrix[4][4];
	if (matrix == NULL) matrix = this->matrix;
	copyMatrix(matrix, temp_matrix, LENGTH_EDGE[this->current_block]);
	
	for (int i = 0; i < LENGTH_EDGE[this->current_block]; i++) {
		for (int j = 0; j < LENGTH_EDGE[this->current_block]; j++) {

			matrix[i][j] = temp_matrix[j][LENGTH_EDGE[this->current_block] - i - 1];

		}
	}
}
