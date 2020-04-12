#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "Common.h"
#include <vector>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL; // Game's renderer 
SDL_Event e;
TTF_Font* font = NULL;
SDL_Color score_color = { 209, 100, 85 };
TextView arr_textview[NUMBER_ELEMENT_TEXTVIEW];
int TIME_HOLDER[4] = { 0, 0, 0, 0 };
extern long curr_high_score;
bool quit = false;

bool Init() {
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
		success = false;
	};

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	};

	srand(time(NULL));
	font = TTF_OpenFont("Fonts/eurof55.ttf", FONT_SIZE);
	if (font == NULL) {
		cerr << "TTF Error: " << TTF_GetError() << endl;
		success = false;
	}
	gWindow = SDL_CreateWindow("Game SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		cerr << SDL_GetError();
		success = false;
	}
	return success;
};
void configPrePlay() {

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	arr_textview[SCORE_TEXT] = TextView(font, FONT_SIZE);
	arr_textview[SCORE_NUMBER] = TextView(font, FONT_SIZE);
	arr_textview[HIGH_SCORE_TEXT] = TextView(font, FONT_SIZE);
	arr_textview[HIGH_SCORE_NUMBER] = TextView(font, FONT_SIZE);
	//set origin point 
	arr_textview[SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[HIGH_SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[HIGH_SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };

	//set Renderer
	arr_textview[HIGH_SCORE_TEXT].setRenderer(gRenderer);
	arr_textview[HIGH_SCORE_NUMBER].setRenderer(gRenderer);
	arr_textview[SCORE_TEXT].setRenderer(gRenderer);
	arr_textview[SCORE_NUMBER].setRenderer(gRenderer);

	//set default text
	arr_textview[SCORE_TEXT].makeTextTexture("Score", 36, score_color);
	arr_textview[SCORE_NUMBER].makeTextTexture("0", 36, score_color);
	arr_textview[HIGH_SCORE_TEXT].makeTextTexture("High Score", 36, score_color);
	arr_textview[HIGH_SCORE_NUMBER].makeTextTexture("0", 36, score_color);

	//score_number.y_render = 10;

	//add coordinate render for score number
	arr_textview[SCORE_TEXT].setCenterPoint({ 60,17 });
	arr_textview[SCORE_NUMBER].setCenterPoint({ 60,48 });
	arr_textview[HIGH_SCORE_TEXT].setCenterPoint({ 360,17 });
	arr_textview[HIGH_SCORE_NUMBER].setCenterPoint({ 360,48 });

}
void playGame() {
	
	configPrePlay();
	Board board(gRenderer);
	Block curr_block;
	Uint32 prev_time = 0;
	long curr_score = 0;

	//Main Loop
	while (!quit) {
		std::string score = "";
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
		Uint32 curr_time = SDL_GetTicks();
		if (curr_time - prev_time >= 1000) {
			SDL_Point next_point = { curr_block.matrix_origin_point.x,curr_block.matrix_origin_point.y + 1 };
			if (board.isAvailable(curr_block.matrix, board.static_board, next_point, curr_block.current_block)) {
				curr_block.matrix_origin_point.y++;
			}
			else {
				board.setMatrix(curr_block.matrix, board.static_board, curr_block.matrix_origin_point, curr_block.current_block);
				long curr_turn_point = board.checkGainPoint();
				Block next_block;
				curr_block = next_block;
				curr_score += curr_turn_point;
				if (curr_turn_point != 0) {
					score += to_string(curr_score);
					arr_textview[SCORE_NUMBER].makeTextTexture(score.c_str(), 36, score_color);
					arr_textview[SCORE_NUMBER].setAnimation("Scale Up", 200);
				}
				if (curr_high_score < curr_score) {
					curr_high_score = curr_score;
					arr_textview[HIGH_SCORE_NUMBER].makeTextTexture(to_string(curr_high_score).c_str(), 36, score_color);
					arr_textview[HIGH_SCORE_NUMBER].setAnimation("Scale Up", 500);
				}
			}
			prev_time = curr_time;
		};
		board.renderBoard(curr_block);
		for (int i = 0; i < NUMBER_ELEMENT_TEXTVIEW; i++) {
			arr_textview[i].render(true);
		};
		SDL_RenderPresent(gRenderer);
	};
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}