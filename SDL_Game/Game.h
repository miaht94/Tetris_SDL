#pragma once
#include <iostream>
#include <string>
#include "Common.h"
#include "Board.h"
class Game
{
	public:
		SDL_Renderer* gRenderer;
		SDL_Event e;
		
		Board board;
		Block curr_block;
		SDL_Color color[NUMBER_ELEMENT_COLOR];
		TTF_Font* font = NULL;
		
		TextView arr_textview[NUMBER_ELEMENT_TEXTVIEW];
		Button arr_button[NUMBER_ELEMENT_BUTTON];
		View arr_view[NUMBER_ELEMENT_VIEW];

		//gui
		Button gui_button[NUMBER_ELEMENT_GUI_BUTTON];
		View gui_view[NUMBER_ELEMENT_GUI_VIEW];

		int status = GAME_ON_GUI;

		int TIME_HOLDER[5] = { 0, 0, 0, 0, 0 };
		
		int curr_high_score = 0;
		int curr_score = 0;
		int audio_status = 6; // 6 on 7 off
		int curr_level = 3;
		bool quit = false;

		Game(SDL_Renderer* gRenderer, TTF_Font* font);

		void configResource();
		void onGUI();
		void onPause();
		void playGame();
		void handleGameStatus();
		void renderCurrentGame();
		void handleEvent(const Uint8* current_key_state, Uint32& prev_time);
		void onReplay();
};

