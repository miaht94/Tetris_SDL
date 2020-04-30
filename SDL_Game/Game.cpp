#include "Game.h"
Game::Game(SDL_Renderer* gRenderer, TTF_Font* font)
{
	this->gRenderer = gRenderer;
	this->font = font;
	this->board.setRenderer(gRenderer);
	Game::configResource();
}
void Game::configResource() {

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	//Init Color
	color[SCORE_COLOR] = { 255,255,255 };

	//Init Audio
	this->gMix[DROP_CHUNK] = Mix_LoadWAV("audio/Drop.wav");
	this->gMix[MOVE_CHUNK] = Mix_LoadWAV("audio/Move.wav");
	this->gMix[GAME_OVER_CHUNK] = Mix_LoadWAV("audio/GameOver.wav");
	this->gMix[LINE_CLEAR_CHUNK] = Mix_LoadWAV("audio/Lineclear.wav");

//INIT GAME_PLAYING_________________________________________________________________________
	//Init View
	arr_view[NOTIFICATION_VIEW].setRenderer(this->gRenderer);
	arr_view[BACKGROUND_VIEW].setRenderer(this->gRenderer);
	arr_view[HIGH_SCORE_FRAME].setRenderer(this->gRenderer);
	arr_view[SCORE_FRAME].setRenderer(this->gRenderer);
		//Set attribute
		arr_view[NOTIFICATION_VIEW].width_render = 310;
		arr_view[NOTIFICATION_VIEW].height_render = 200;
		arr_view[NOTIFICATION_VIEW].setCenterPoint({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });

		arr_view[BACKGROUND_VIEW].width_render = SCREEN_WIDTH;
		arr_view[BACKGROUND_VIEW].height_render = SCREEN_HEIGHT;
		arr_view[BACKGROUND_VIEW].clip = new SDL_Rect({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT });

		arr_view[HIGH_SCORE_FRAME].width_render = 300;
		arr_view[HIGH_SCORE_FRAME].height_render = 180;
		arr_view[HIGH_SCORE_FRAME].setCenterPoint({ 175, 150 });
		arr_view[HIGH_SCORE_FRAME].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };

		arr_view[SCORE_FRAME].width_render = 300;
		arr_view[SCORE_FRAME].height_render = 180;
		arr_view[SCORE_FRAME].setCenterPoint({ 175, 500 });
		arr_view[SCORE_FRAME].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };

		//Load Texture
		arr_view[NOTIFICATION_VIEW].loadTexture("textures/frame.png");
		arr_view[BACKGROUND_VIEW].loadTexture("textures/ingame_background.jpg");
		arr_view[HIGH_SCORE_FRAME].loadTexture("textures/score_frame.png");
		arr_view[SCORE_FRAME].loadTexture("textures/score_frame.png");
	//Init Text
	arr_textview[SCORE_TEXT] = TextView(this->font, FONT_SIZE);
	arr_textview[SCORE_NUMBER] = TextView(this->font, FONT_SIZE);
	arr_textview[HIGH_SCORE_TEXT] = TextView(this->font, FONT_SIZE);
	arr_textview[HIGH_SCORE_NUMBER] = TextView(this->font, FONT_SIZE);
	arr_textview[PAUSE_TEXT] = TextView(this->font, FONT_SIZE);
	arr_textview[COMBO] = TextView(this->font, FONT_SIZE);
		//set Renderer
		arr_textview[HIGH_SCORE_TEXT].setRenderer(this->gRenderer);
		arr_textview[HIGH_SCORE_NUMBER].setRenderer(this->gRenderer);
		arr_textview[SCORE_TEXT].setRenderer(this->gRenderer);
		arr_textview[SCORE_NUMBER].setRenderer(this->gRenderer);
		arr_textview[PAUSE_TEXT].setRenderer(this->gRenderer);
		arr_textview[COMBO].setRenderer(this->gRenderer);

		//set default text
		arr_textview[SCORE_TEXT].makeTextTexture("Score", 36, color[SCORE_COLOR]);
		arr_textview[SCORE_NUMBER].makeTextTexture("0", 36, color[SCORE_COLOR]);
		arr_textview[HIGH_SCORE_TEXT].makeTextTexture("High Score", 36, {255,255,255});
		arr_textview[HIGH_SCORE_NUMBER].makeTextTexture("0", 36, color[SCORE_COLOR]);
		arr_textview[PAUSE_TEXT].makeTextTexture("GAME PAUSED", FONT_SIZE, { 255,255,255 });

		//set attribute
		//arr_textview[SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
		//arr_textview[SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
		//arr_textview[HIGH_SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
		//arr_textview[HIGH_SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
		
		arr_textview[PAUSE_TEXT].setCenterPoint({ arr_view[NOTIFICATION_VIEW].width_render / 2, arr_view[NOTIFICATION_VIEW].height_render / 3 });
		arr_textview[HIGH_SCORE_TEXT].setCenterPoint({ arr_view[HIGH_SCORE_FRAME].width_render/2, 30 });
		arr_textview[HIGH_SCORE_NUMBER].setCenterPoint({ arr_view[HIGH_SCORE_FRAME].width_render/2, 120});
		arr_textview[SCORE_TEXT].setCenterPoint({ arr_view[SCORE_FRAME].width_render / 2, 30 });
		arr_textview[SCORE_NUMBER].setCenterPoint({ arr_view[HIGH_SCORE_FRAME].width_render / 2, 120 });
		arr_textview[COMBO].setCenterPoint({ 200,460 });
	//set textview's background
		arr_textview[PAUSE_TEXT].setViewBackground(arr_view[NOTIFICATION_VIEW]);
		arr_textview[SCORE_TEXT].setViewBackground(arr_view[SCORE_FRAME]);
		arr_textview[SCORE_NUMBER].setViewBackground(arr_view[SCORE_FRAME]);
		arr_textview[HIGH_SCORE_TEXT].setViewBackground(arr_view[HIGH_SCORE_FRAME]);
		arr_textview[HIGH_SCORE_NUMBER].setViewBackground(arr_view[HIGH_SCORE_FRAME]);
	//_______________________________________________________________________________________________

	//config button
	arr_button[PAUSE_BUTTON] = Button();
	arr_button[RESUME_BUTTON] = Button();
	arr_button[REPLAY_BUTTON] = Button();

	//set Renderer
	arr_button[PAUSE_BUTTON].setRenderer(this->gRenderer);
	arr_button[RESUME_BUTTON].setRenderer(this->gRenderer);
	arr_button[REPLAY_BUTTON].setRenderer(this->gRenderer);
	//set attribute
		arr_button[PAUSE_BUTTON].origin_point = { TASK_BAR_VIEWPORT.x, TASK_BAR_VIEWPORT.y };
		arr_button[PAUSE_BUTTON].width_render = 55;
		arr_button[PAUSE_BUTTON].height_render = 55;

		arr_button[RESUME_BUTTON].width_render = 60;
		arr_button[RESUME_BUTTON].height_render = 60;

		arr_button[REPLAY_BUTTON].width_render = 60;
		arr_button[REPLAY_BUTTON].height_render = 60;

	//set center point render
		arr_button[PAUSE_BUTTON].setCenterPoint({ 420,30 });
		arr_button[RESUME_BUTTON].setCenterPoint({ arr_view[NOTIFICATION_VIEW].width_render * 1 / 4,arr_view[NOTIFICATION_VIEW].height_render * 2 / 3 });
		arr_button[REPLAY_BUTTON].setCenterPoint({ arr_view[NOTIFICATION_VIEW].width_render * 3 / 4,arr_view[NOTIFICATION_VIEW].height_render * 2 / 3 });
	
	//load texture for button
		arr_button[PAUSE_BUTTON].loadTexture("textures/play_but_lighter.png", "textures/play_but.png");
		arr_button[RESUME_BUTTON].loadTexture("textures/play_but_lighter.png", "textures/play_but.png");
		arr_button[REPLAY_BUTTON].loadTexture("textures/replay_but_lighter.png", "textures/replay_but.png");
	//set button's background
		arr_button[RESUME_BUTTON].setViewBackground(arr_view[NOTIFICATION_VIEW]);
		arr_button[REPLAY_BUTTON].setViewBackground(arr_view[NOTIFICATION_VIEW]);
//__________________________________________________________________________________________________________________________________________________________

//INIT GUI
	//gui View
		gui_view[GUI_BACKGROUND].setRenderer(this->gRenderer);
		gui_view[GAME_TITLE].setRenderer(this->gRenderer);
		gui_view[MENU_BACKGROUND].setRenderer(this->gRenderer);
		gui_view[SELECT_BACKGOUND].setRenderer(this->gRenderer);

		gui_view[GUI_BACKGROUND].loadTexture("textures/background.png");
		gui_view[GAME_TITLE].loadTexture("textures/Title.png");
		gui_view[MENU_BACKGROUND].loadTexture("textures/menu_background.png");

		gui_view[GUI_BACKGROUND].x_render = 0;
		gui_view[GUI_BACKGROUND].y_render = 0;
		gui_view[GUI_BACKGROUND].width_render = SCREEN_WIDTH;
		gui_view[GUI_BACKGROUND].height_render = SCREEN_HEIGHT;

		gui_view[GAME_TITLE].width_render = 200;
		gui_view[GAME_TITLE].height_render = 70;
		gui_view[GAME_TITLE].setCenterPoint({ -115,100 });

		gui_view[MENU_BACKGROUND].width_render = 310;
		gui_view[MENU_BACKGROUND].height_render = 230;
		gui_view[MENU_BACKGROUND].setCenterPoint({ -100,300 });

	//gui Button
		gui_button[PLAY_GUI_BUTTON].setRenderer(this->gRenderer);
		gui_button[AUDIO_ON].setRenderer(this->gRenderer);
		gui_button[AUDIO_OFF].setRenderer(this->gRenderer);
		gui_button[LEVEL_1].setRenderer(this->gRenderer);
		gui_button[LEVEL_2].setRenderer(this->gRenderer);
		gui_button[LEVEL_3].setRenderer(this->gRenderer);

		gui_button[PLAY_GUI_BUTTON].loadTexture("textures/play.png","textures/play_light.png");
		gui_button[AUDIO_ON].loadTexture("textures/audio_on.png", "textures/audio_on_light.png");
		gui_button[AUDIO_OFF].loadTexture("textures/audio_off.png", "textures/audio_off_light.png");
		gui_button[LEVEL_1].loadTexture("textures/level_1.png", "textures/level_1_light.png");
		gui_button[LEVEL_2].loadTexture("textures/level_2.png", "textures/level_2_light.png");
		gui_button[LEVEL_3].loadTexture("textures/level_3.png", "textures/level_3_light.png");

		gui_button[PLAY_GUI_BUTTON].width_render = gui_button[PLAY_GUI_BUTTON].width_render/5;
		gui_button[PLAY_GUI_BUTTON].height_render = gui_button[PLAY_GUI_BUTTON].height_render/5;
		gui_button[AUDIO_ON].width_render = gui_button[AUDIO_ON].width_render/5;
		gui_button[AUDIO_ON].height_render = gui_button[AUDIO_ON].height_render/5;
		gui_button[AUDIO_OFF].width_render = gui_button[AUDIO_OFF].width_render / 5;
		gui_button[AUDIO_OFF].height_render = gui_button[AUDIO_OFF].height_render / 5;
		gui_button[LEVEL_1].width_render = gui_button[LEVEL_1].width_render/5;
		gui_button[LEVEL_1].height_render = gui_button[LEVEL_1].height_render/5;
		gui_button[LEVEL_2].width_render = gui_button[LEVEL_2].width_render/5;
		gui_button[LEVEL_2].height_render = gui_button[LEVEL_2].height_render/5;
		gui_button[LEVEL_3].width_render = gui_button[LEVEL_3].width_render/5;
		gui_button[LEVEL_3].height_render = gui_button[LEVEL_3].height_render/5;

		gui_button[PLAY_GUI_BUTTON].setCenterPoint({ 175,30 });
		gui_button[AUDIO_ON].setCenterPoint({ 175,115 });
		gui_button[AUDIO_OFF].setCenterPoint({ 175,115 });
		gui_button[LEVEL_1].setCenterPoint({ 175,200 });
		gui_button[LEVEL_2].setCenterPoint({ 175,200 });
		gui_button[LEVEL_3].setCenterPoint({ 175,200 });

		gui_button[PLAY_GUI_BUTTON].setViewBackground(gui_view[MENU_BACKGROUND]);
		gui_button[AUDIO_ON].setViewBackground(gui_view[MENU_BACKGROUND]);
		gui_button[AUDIO_OFF].setViewBackground(gui_view[MENU_BACKGROUND]);
		gui_button[LEVEL_1].setViewBackground(gui_view[MENU_BACKGROUND]);
		gui_button[LEVEL_2].setViewBackground(gui_view[MENU_BACKGROUND]);
		gui_button[LEVEL_3].setViewBackground(gui_view[MENU_BACKGROUND]);

		//gui_button[AUDIO_GUI_BUTTON] = gui_button[this->audio_status];
		//gui_button[LEVEL_BUTTON] = gui_button[this->curr_level];
}
void Game::playMusic(Mix_Chunk* chunk, Mix_Music* music)
{
	if (this->audio_status == 4 && chunk != NULL) {
		Mix_PlayChannel(-1, chunk, 0);
	};
	if (this->audio_status == 4 && music != NULL) {
		Mix_PlayMusic(music, -1);
	}
}
void Game::onGUI()
{
	gui_view[GAME_TITLE].setAnimation("Transform", 300, NULL ,{ 200,0 });
	gui_view[MENU_BACKGROUND].setAnimation("Transform", 400, NULL, { 200,0 });
	Uint32 temp;
	while (!this->quit && this->status == GAME_ON_GUI) {
		while (SDL_PollEvent(&this->e) != 0) {
			if (this->e.type == SDL_QUIT) {
				this->quit = true;
				this->status = GAME_EXIT;
			}
		};
		this->handleEvent(NULL, temp);
		SDL_SetRenderDrawColor(this->gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(this->gRenderer);
		gui_view[GUI_BACKGROUND].render();
		gui_view[GAME_TITLE].render();
		gui_view[MENU_BACKGROUND].render();
		gui_button[PLAY_GUI_BUTTON].render();
		gui_button[this->audio_status].render();
		gui_button[this->curr_level].render();
		SDL_RenderPresent(this->gRenderer);
	};
}
void Game::onPause()
{
	arr_view[NOTIFICATION_VIEW].setAnimation("Appear", 200);
	Uint32 temp;
	while (this->status == GAME_PAUSED) {
		while (SDL_PollEvent(&this->e) != 0) {
			if (this->e.type == SDL_QUIT) {
				this->quit = true;
				this->status = GAME_EXIT;
			}
		};
		this->handleEvent(NULL, temp);
		if (this->quit == true) break;
		SDL_SetRenderDrawColor(gRenderer,255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		renderCurrentGame(-1);
		SDL_RenderPresent(gRenderer);
	}
}

void Game::playGame()
{
	cout << SCREEN_WIDTH << "    -    " << SCREEN_HEIGHT << endl;
	Uint32 prev_time = 0;
	Uint32 prev_fall_time = 0;
	bool game_over = false;
	while (!(this->quit) && !game_over && this->status == GAME_PLAYING) {
		std::string score = "";
		while (SDL_PollEvent(&this->e) != 0) {
			if (this->e.type == SDL_QUIT) {
				this->quit = true;
				this->status = GAME_EXIT;
			}
		};
		Game::handleEvent(SDL_GetKeyboardState(NULL), prev_time);
		Game::handleGameStatus();
		SDL_SetRenderDrawColor(this->gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(this->gRenderer);
		Uint32 curr_time = SDL_GetTicks();
		if (arr_textview[COMBO].ended && arr_textview[COMBO].texture!=NULL) 
			arr_textview[COMBO].setAnimation("Disappear", 1000,1000);
		if (curr_time - prev_fall_time >= 1000/this->curr_level || this->hard_drop/*&& this->board.animationEnded()*/) {
			this->hard_drop = false;
			SDL_Point next_point = { this->curr_block.matrix_origin_point.x,this->curr_block.matrix_origin_point.y + 1 };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point.y++;
			}
			else {
				playMusic(gMix[DROP_CHUNK]);
				board.setMatrix(this->curr_block.matrix, this->board.static_board, this->curr_block.matrix_origin_point, this->curr_block.current_block);
				game_over = this->board.isGameOver();
				(game_over) ? cout << "Game Over" << endl : cout << "";
				long curr_turn_point = board.checkGainPoint();
				Block next_block;
				this->curr_block = next_block;
				this->curr_score += curr_turn_point;
				if (curr_turn_point != 0) {
					playMusic(gMix[LINE_CLEAR_CHUNK]);
					score += to_string(this->curr_score);
					string combo = "Combo " + to_string(curr_turn_point /100);
					this->arr_textview[COMBO].makeTextTexture(combo.c_str(), 36, { 0,0,0 });
					this->arr_textview[COMBO].setAnimation("Scale Up", 200);
					this->arr_textview[SCORE_NUMBER].makeTextTexture(score.c_str(), 36, this->color[SCORE_COLOR]);
					this->arr_textview[SCORE_NUMBER].setViewBackground(arr_view[SCORE_FRAME]);
					this->arr_textview[SCORE_NUMBER].setAnimation("Scale Up", 200);
				}
				if (this->curr_high_score < this->curr_score) {
					this->curr_high_score = this->curr_score;
					this->arr_textview[HIGH_SCORE_NUMBER].makeTextTexture(to_string(this->curr_high_score).c_str(), 36, this->color[SCORE_COLOR]);
					this->arr_textview[HIGH_SCORE_NUMBER].setViewBackground(arr_view[HIGH_SCORE_FRAME]);
					this->arr_textview[HIGH_SCORE_NUMBER].setAnimation("Scale Up", 200);
				}
			}
			prev_fall_time = curr_time;
		};
		prev_time = curr_time;
		/*this->board.renderBoard(this->curr_block);
		for (int i = 0; i < NUMBER_ELEMENT_TEXTVIEW; i++) {
			this->arr_textview[i].render(true);
		};

		for (int i = 0; i < 1; i++) {
			this->arr_button[i].render(true);
		};*/
		Game::renderCurrentGame(-1);
		SDL_RenderPresent(this->gRenderer);
	};
}
void Game::handleGameStatus()
{
	if (this->status == GAME_PAUSED) {
		this->onPause();
	};
	if (this->status == GAME_ON_GUI) {
		this->onGUI();
	}
	if (this->status == GAME_REPLAY) {
		this->status = GAME_PLAYING;
		this->playGame();
	}
}
void Game::renderCurrentGame(int arg_status) {
	if (arg_status == -1) arg_status = this->status;
	if (arg_status == GAME_PLAYING) {
		SDL_Rect blur_background = { BOARD_VIEWPORT.x,BOARD_VIEWPORT.y,BOARD_VIEWPORT.w,BOARD_VIEWPORT.h };
		SDL_Rect board_stroke = { BOARD_VIEWPORT.x,BOARD_VIEWPORT.y,BOARD_VIEWPORT.w,BOARD_VIEWPORT.h };
		this->arr_view[BACKGROUND_VIEW].render();
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(this->gRenderer, &blur_background);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(this->gRenderer, &blur_background);
		this->arr_view[HIGH_SCORE_FRAME].render(true);
		this->arr_view[SCORE_FRAME].render(true);
		this->board.renderBoard(this->curr_block);
		for (int i = 0; i < NUMBER_ELEMENT_TEXTVIEW_ON_PLAYING; i++) {
			if (arr_textview[i].texture != NULL)
				this->arr_textview[i].render(true);
		};

		for (int i = 0; i < NUMBER_ELEMENT_BUTTON_ON_PLAYING; i++) {
			if (arr_button[i].texture != NULL)
				this->arr_button[i].render(true);
		};
	}
	else if (arg_status == GAME_PAUSED) {
		this->renderCurrentGame(GAME_PLAYING);
		SDL_Rect blur_background = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 60);
		SDL_RenderFillRect(this->gRenderer, &blur_background);
		arr_view[NOTIFICATION_VIEW].render(true);
		arr_textview[PAUSE_TEXT].render(true);
		arr_button[RESUME_BUTTON].render(true);
		arr_button[REPLAY_BUTTON].render(true);
	}
}
void Game::handleEvent(const Uint8* current_key_state, Uint32& prev_time)
{
	if (this->status == GAME_PLAYING) {
		// Handle Keyboard
		int time_offset = SDL_GetTicks() - prev_time;
		if (current_key_state[SDL_SCANCODE_LEFT])
			this->TIME_HOLDER[LEFT_ARROW] += time_offset;
		else this->TIME_HOLDER[LEFT_ARROW] = 0;

		if (current_key_state[SDL_SCANCODE_UP])
			this->TIME_HOLDER[UP_ARROW] += time_offset;
		else this->TIME_HOLDER[UP_ARROW] = 0;

		if (current_key_state[SDL_SCANCODE_DOWN])
			this->TIME_HOLDER[DOWN_ARROW] += time_offset;
		else this->TIME_HOLDER[DOWN_ARROW] = 0;

		if (current_key_state[SDL_SCANCODE_RIGHT])
			this->TIME_HOLDER[RIGHT_ARROW] += time_offset;
		else this->TIME_HOLDER[RIGHT_ARROW] = 0;

		if (current_key_state[SDL_SCANCODE_SPACE])
			this->TIME_HOLDER[SPACE] += time_offset;
		else this->TIME_HOLDER[SPACE] = 0;
		//Handle Mouse
		for (int i = 0; i < 1; i++) {
			this->arr_button[i].handleMouseEvent(&this->e);
			//cout << arr_button[i].cur_status << endl;
		};

		//Process after Player's Event Done
			// Keyboard
		if (this->TIME_HOLDER[SPACE] > 5) {
			SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x, this->curr_block.matrix_origin_point.y + 1 };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point = next_origin_point;
				next_origin_point.y++;
				//Mix_PlayChannel(-1, gMix[MOVE_CHUNK], 0);
			}
			else {
				this->hard_drop = true;
				//playMusic(this->gMix[DROP_CHUNK]);
			}
			this->TIME_HOLDER[SPACE] = 0;
			//prev_time -= 1000;
		};
		if (this->TIME_HOLDER[UP_ARROW] > 80) {
			int temp_matrix[4][4];
			copyMatrix(this->curr_block.matrix, temp_matrix, LENGTH_EDGE[this->curr_block.current_block]);
			this->curr_block.rotate(temp_matrix);

			if (this->board.isAvailable(temp_matrix, this->board.static_board, this->curr_block.matrix_origin_point, this->curr_block.current_block)) {
				this->curr_block.rotate();
				this->TIME_HOLDER[UP_ARROW] = 0;
				//Mix_PlayChannel(-1, gMix[MOVE_CHUNK], 0);
			}
		};
		if (this->TIME_HOLDER[LEFT_ARROW] > 50) {
			SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x - 1, this->curr_block.matrix_origin_point.y };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point = next_origin_point;
				this->TIME_HOLDER[LEFT_ARROW] = 0;
				//Mix_PlayChannel(-1, gMix[MOVE_CHUNK], 0);
			};
		};
		if (this->TIME_HOLDER[RIGHT_ARROW] > 50) {
			SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x + 1, this->curr_block.matrix_origin_point.y };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point = next_origin_point;
				this->TIME_HOLDER[RIGHT_ARROW] = 0;
				//Mix_PlayChannel(-1, gMix[MOVE_CHUNK], 0);
			};
		};
		if (this->TIME_HOLDER[DOWN_ARROW] > 50) {
			SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x, this->curr_block.matrix_origin_point.y + 1 };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point = next_origin_point;
				this->TIME_HOLDER[DOWN_ARROW] = 0;
				//Mix_PlayChannel(-1, gMix[MOVE_CHUNK], 0);
			};
		};

		//Mouse
		if (arr_button[PAUSE_BUTTON].cur_status == "Mouse Down") {
			this->status = 1;
		}
	}
	// Handle of game pause
	else if (this->status == GAME_PAUSED) {
		arr_button[RESUME_BUTTON].handleMouseEvent(&this->e);
		arr_button[REPLAY_BUTTON].handleMouseEvent(&this->e);
		if (arr_button[RESUME_BUTTON].beClicked()) {
			this->status = GAME_PLAYING;
		}
		if (arr_button[REPLAY_BUTTON].beClicked()) {
			this->status = GAME_REPLAY;
			this->onReplay();
		}
	} 
	else if (this->status == GAME_ON_GUI) {
		gui_button[PLAY_GUI_BUTTON].handleMouseEvent(&this->e);
		gui_button[this->audio_status].handleMouseEvent(&this->e);
		gui_button[this->curr_level].handleMouseEvent(&this->e);
		if (gui_button[PLAY_GUI_BUTTON].beClicked()) {
			this->status = GAME_REPLAY;
		}
		if (gui_button[this->audio_status].beClicked()) {
			this->audio_status = AUDIO_ON + (this->audio_status + 1) % 2;
			/*cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << gui_button[this->audio_status].cur_status << endl;
			cout << gui_button[this->audio_status].pre_status << endl;*/
		};
		if (gui_button[this->curr_level].beClicked()) {
			this->curr_level = LEVEL_1 + (this->curr_level + 1) % 3;
			/*cout << "-----------------------------------------" << endl;
			cout << gui_button[this->curr_level].cur_status << endl;
			cout << gui_button[this->curr_level].pre_status << endl;*/
		};
	}
}
void Game::onReplay()
{
	this->board.reset();
	this->curr_block = Block();
	this->curr_score = 0;
	arr_textview[SCORE_NUMBER].makeTextTexture("0", 36, color[SCORE_COLOR]);
	arr_textview[SCORE_NUMBER].setCenterPoint({ arr_view[HIGH_SCORE_FRAME].width_render / 2, 120 });
	arr_textview[SCORE_NUMBER].setViewBackground(arr_view[SCORE_FRAME]);
}
