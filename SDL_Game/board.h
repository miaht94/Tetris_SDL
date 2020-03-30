#include <iostream>
#include "Common.h"

using namespace std;
class Board
{
	public:
		const int width_square = WIDTH_SQUARE;
		const int height_square = HEIGHT_SQUARE;
		int board[WIDTH_SQUARE][HEIGHT_SQUARE] = { {0} };
		SDL_Renderer* renderer;

		Board();
		~Board();
		void setRenderer(SDL_Renderer* renderer);
		void drawNet(SDL_Point start_point = { 0,0 });
};
