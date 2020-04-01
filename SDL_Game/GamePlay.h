#pragma once
#include <iostream>
#include "Board.h"
#include "Common.h"

using namespace std;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
bool Init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Game SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH_SQUARE * LENGTH_SQUARE, HEIGHT_SQUARE * LENGTH_SQUARE, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		cerr << SDL_GetError;
		return false;
	}
	else return true;
};
void playGame() {
	gRenderer = SDL_CreateRenderer(gWindow, -1, NULL);
	Board board(gRenderer);
	Block curr_block;
	curr_block.matrix_origin_point.x = 8;
	curr_block.matrix_origin_point.y = 8;
	int prev_time = 0;
	while (true) {
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		board.drawNet();
		int curr_time = SDL_GetTicks();
		if (curr_time - prev_time >= 1000) {
			curr_block.matrix_origin_point.y++;
			prev_time = curr_time;
		};
		board.renderBoard(curr_block);
		SDL_RenderPresent(gRenderer);
	};
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}