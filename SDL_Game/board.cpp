#include "Board.h"

Board::Board()
{
	//Do Nothing
};

Board::~Board()
{
	//Do Nothing
};

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
};
