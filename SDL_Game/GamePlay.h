#pragma once
#include <iostream>
#include "Board.h"
#include "Common.h"

using namespace std;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL; // Game's renderer 
SDL_Event e;						
int TIME_HOLDER[4] = { 0, 0, 0, 0 };
bool quit = false;
bool Init() {
	SDL_Init(SDL_INIT_VIDEO);
	srand(time(NULL));
	gWindow = SDL_CreateWindow("Game SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH_SQUARE * LENGTH_SQUARE + 30, HEIGHT_SQUARE * LENGTH_SQUARE + 30, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		cerr << SDL_GetError;
		return false;
	}
	else return true;
};
void playGame() {
	gRenderer = SDL_CreateRenderer(gWindow, -1, NULL);
	SDL_RenderSetViewport(gRenderer, &BOARD_VIEWPORT);
	Board board(gRenderer);
	Block curr_block;
	curr_block.matrix_origin_point.x = 8;
	curr_block.matrix_origin_point.y = 8;
	Uint32 prev_time = 0;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		// Handle keyboard press (get how much times player press a key in TIME_HOLDER) 
		handle(SDL_GetKeyboardState(NULL));
		if (TIME_HOLDER[UP_ARROW] > 60) {
			
			int temp_matrix[4][4];
			copyMatrix(curr_block.matrix, temp_matrix, LENGTH_EDGE[curr_block.current_block]);
			curr_block.rotate(temp_matrix);

			if (board.isAvailable(temp_matrix, board.static_board, curr_block.matrix_origin_point, curr_block.current_block)) {
				curr_block.rotate();
				TIME_HOLDER[UP_ARROW] = 0;
			}

		};
		if (TIME_HOLDER[LEFT_ARROW] > 60) {
			SDL_Point next_origin_point = { curr_block.matrix_origin_point.x - 1, curr_block.matrix_origin_point.y };
			if (board.isAvailable(curr_block.matrix, board.static_board, next_origin_point, curr_block.current_block)) {
				curr_block.matrix_origin_point = next_origin_point;
				TIME_HOLDER[LEFT_ARROW] = 0;
			};

		};
		if (TIME_HOLDER[RIGHT_ARROW] > 60) {
			SDL_Point next_origin_point = { curr_block.matrix_origin_point.x + 1, curr_block.matrix_origin_point.y };
			if (board.isAvailable(curr_block.matrix, board.static_board, next_origin_point, curr_block.current_block)) {
				curr_block.matrix_origin_point = next_origin_point;
				TIME_HOLDER[RIGHT_ARROW] = 0;
			};

		};
		if (TIME_HOLDER[DOWN_ARROW] > 30) {
			SDL_Point next_origin_point = { curr_block.matrix_origin_point.x, curr_block.matrix_origin_point.y + 1 };
			if (board.isAvailable(curr_block.matrix, board.static_board, next_origin_point, curr_block.current_block)) {
				curr_block.matrix_origin_point = next_origin_point;
				TIME_HOLDER[DOWN_ARROW] = 0;
			};

		};
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		board.drawNet();
		Uint32 curr_time = SDL_GetTicks();
		if (curr_time - prev_time >= 1000) {
			SDL_Point next_point = { curr_block.matrix_origin_point.x,curr_block.matrix_origin_point.y + 1 };
			if (board.isAvailable(curr_block.matrix, board.static_board, next_point, curr_block.current_block)) {
				curr_block.matrix_origin_point.y++;
			}
			else {
				board.setMatrix(curr_block.matrix, board.static_board, curr_block.matrix_origin_point, curr_block.current_block);
				Block next_block;
				curr_block = next_block;
			}
			prev_time = curr_time;
		};
		board.renderBoard(curr_block);
		
		SDL_RenderPresent(gRenderer);
	};
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}