#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "View.h"
#include "Common.h"
#include "board.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int main(int agrc, char* argv[]) {
	
	if (Init()) {

		gRenderer = SDL_CreateRenderer(gWindow, -1, NULL);
		Board board;
		board.setRenderer(gRenderer);
		board.drawNet();
		SDL_RenderPresent(gRenderer);
		SDL_Delay(20000);
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);

	};
	return 0;

}