#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GamePlay.h"
using namespace std;

long curr_high_score = 0;

int main(int agrc, char* argv[]) {
	
	if (Init()) {

		/*gRenderer = SDL_CreateRenderer(gWindow, -1, NULL);
		Board board(gRenderer);
		board.drawNet();
		Block block;
		cout << block.current_block << endl;;
		SDL_Point point = { 10,10 };
		block.matrix_origin_point = point;
		board.renderBoard(block);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(20000);
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);*/
		playGame();
	};
	return 0;

}