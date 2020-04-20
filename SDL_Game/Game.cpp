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

	//Init Text
	arr_textview[SCORE_TEXT] = TextView(this->font, FONT_SIZE);
	arr_textview[SCORE_NUMBER] = TextView(this->font, FONT_SIZE);
	arr_textview[HIGH_SCORE_TEXT] = TextView(this->font, FONT_SIZE);
	arr_textview[HIGH_SCORE_NUMBER] = TextView(this->font, FONT_SIZE);

	//set origin point 
	arr_textview[SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[HIGH_SCORE_TEXT].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };
	arr_textview[HIGH_SCORE_NUMBER].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };

	//set Renderer
	arr_textview[HIGH_SCORE_TEXT].setRenderer(this->gRenderer);
	arr_textview[HIGH_SCORE_NUMBER].setRenderer(this->gRenderer);
	arr_textview[SCORE_TEXT].setRenderer(this->gRenderer);
	arr_textview[SCORE_NUMBER].setRenderer(this->gRenderer);

	//set default text
	arr_textview[SCORE_TEXT].makeTextTexture("Score", 36, color[SCORE_COLOR]);
	arr_textview[SCORE_NUMBER].makeTextTexture("0", 36, color[SCORE_COLOR]);
	arr_textview[HIGH_SCORE_TEXT].makeTextTexture("High Score", 36, color[SCORE_COLOR]);
	arr_textview[HIGH_SCORE_NUMBER].makeTextTexture("0", 36, color[SCORE_COLOR]);

	//add coordinate render for score number
	arr_textview[SCORE_TEXT].setCenterPoint({ 60,17 });
	arr_textview[SCORE_NUMBER].setCenterPoint({ 60,48 });
	arr_textview[HIGH_SCORE_TEXT].setCenterPoint({ 360,17 });
	arr_textview[HIGH_SCORE_NUMBER].setCenterPoint({ 360,48 });

	//_______________________________________________________________________________________________//

		//config button
	arr_button[PAUSE_BUTTON] = Button();

	//set Origin point
	arr_button[PAUSE_BUTTON].origin_point = { SCORE_VIEWPORT.x, SCORE_VIEWPORT.y };

	//set center point render
	arr_button[PAUSE_BUTTON].setCenterPoint({ 100,100 });

	//set height width for button
	arr_button[PAUSE_BUTTON].width_render = 90;
	arr_button[PAUSE_BUTTON].height_render = 90;

	//set Renderer
	arr_button[PAUSE_BUTTON].renderer = this->gRenderer;

	//load texture for button
	arr_button[PAUSE_BUTTON].loadTexture("textures/play_but_lighter.png", "textures/play_but.png");

}
void Game::onGUI()
{

}
void Game::onPause()
{
	bool unPause = false;
	View pauseNotification;
	TextView paused_text = TextView(this->font, FONT_SIZE);
	pauseNotification.setRenderer(this->gRenderer);
	pauseNotification.width_render = 300;
	pauseNotification.height_render = 300;
	pauseNotification.loadTexture("textures/but_background_1.png");
	pauseNotification.setAnimation("Appear", 200);
	pauseNotification.setCenterPoint({ SCREEN_WIDTH/2,SCREEN_HEIGHT/2 });

	paused_text.setRenderer(this->gRenderer);
	paused_text.makeTextTexture("GAME PAUSED", FONT_SIZE, color[PAUSED_TEXT_COLOR]);
	paused_text.x_render = 20;
	paused_text.y_render = 60;
	paused_text.setViewBackground(pauseNotification);
	while (!unPause) {
		SDL_SetRenderDrawColor(gRenderer,255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		renderCurrentGame();
		SDL_Rect blur_background = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 60);
		SDL_RenderFillRect(this->gRenderer, &blur_background);
		pauseNotification.render(true);
		paused_text.render();
		SDL_RenderPresent(gRenderer);
	}
}
void Game::playGame()
{
	Uint32 prev_time = 0;
	bool game_over = false;
	while (!(this->quit) && !game_over) {
		std::string score = "";
		while (SDL_PollEvent(&this->e) != 0) {
			if (this->e.type == SDL_QUIT) {
				this->quit = true;
			}
		};
		Game::handleEvent(SDL_GetKeyboardState(NULL));
		Game::handleGameStatus();
		SDL_SetRenderDrawColor(this->gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(this->gRenderer);
		Uint32 curr_time = SDL_GetTicks();
		if (curr_time - prev_time >= 1000) {
			SDL_Point next_point = { this->curr_block.matrix_origin_point.x,this->curr_block.matrix_origin_point.y + 1 };
			if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_point, this->curr_block.current_block)) {
				this->curr_block.matrix_origin_point.y++;
			}
			else {
				board.setMatrix(this->curr_block.matrix, this->board.static_board, this->curr_block.matrix_origin_point, this->curr_block.current_block);
				game_over = this->board.isGameOver();
				(game_over) ? cout << "Game Over" << endl : cout << "";
				long curr_turn_point = board.checkGainPoint();
				Block next_block;
				this->curr_block = next_block;
				this->curr_score += curr_turn_point;
				if (curr_turn_point != 0) {
					score += to_string(this->curr_score);
					this->arr_textview[SCORE_NUMBER].makeTextTexture(score.c_str(), 36, this->color[SCORE_COLOR]);
					this->arr_textview[SCORE_NUMBER].setAnimation("Scale Up", 200);
				}
				if (this->curr_high_score < this->curr_score) {
					this->curr_high_score = this->curr_score;
					this->arr_textview[HIGH_SCORE_NUMBER].makeTextTexture(to_string(this->curr_high_score).c_str(), 36, this->color[SCORE_COLOR]);
					this->arr_textview[HIGH_SCORE_NUMBER].setAnimation("Scale Up", 500);
				}
			}
			prev_time = curr_time;
		};
		/*this->board.renderBoard(this->curr_block);
		for (int i = 0; i < NUMBER_ELEMENT_TEXTVIEW; i++) {
			this->arr_textview[i].render(true);
		};

		for (int i = 0; i < 1; i++) {
			this->arr_button[i].render(true);
		};*/
		Game::renderCurrentGame();
		SDL_RenderPresent(this->gRenderer);
	};
}
void Game::handleGameStatus()
{
	if (this->status == 1) {
		Game::onPause();
	};
}
void Game::renderCurrentGame() {
	this->board.renderBoard(this->curr_block);
	for (int i = 0; i < NUMBER_ELEMENT_TEXTVIEW; i++) {
		this->arr_textview[i].render(true);
	};

	for (int i = 0; i < 1; i++) {
		this->arr_button[i].render(true);
	};
}
void Game::handleEvent(const Uint8* current_key_state)
{
	// Handle Keyboard
	if (current_key_state[SDL_SCANCODE_LEFT])
		this->TIME_HOLDER[LEFT_ARROW]++;
	else this->TIME_HOLDER[LEFT_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_UP])
		this->TIME_HOLDER[UP_ARROW]++;
	else this->TIME_HOLDER[UP_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_DOWN])
		this->TIME_HOLDER[DOWN_ARROW]++;
	else this->TIME_HOLDER[DOWN_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_RIGHT])
		this->TIME_HOLDER[RIGHT_ARROW]++;
	else this->TIME_HOLDER[RIGHT_ARROW] = 0;

	//Handle Mouse
	for (int i = 0; i < 1; i++) {
		this->arr_button[i].handleMouseEvent(&e);
	};

	//Process after Player's Event Done
		// Keyboard
	if (this->TIME_HOLDER[UP_ARROW] > 60) {
		int temp_matrix[4][4];
		copyMatrix(this->curr_block.matrix, temp_matrix, LENGTH_EDGE[this->curr_block.current_block]);
		this->curr_block.rotate(temp_matrix);

		if (this->board.isAvailable(temp_matrix, this->board.static_board, this->curr_block.matrix_origin_point, this->curr_block.current_block)) {
			this->curr_block.rotate();
			this->TIME_HOLDER[UP_ARROW] = 0;
		}
	};
	if (this->TIME_HOLDER[LEFT_ARROW] > 60) {
		SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x - 1, this->curr_block.matrix_origin_point.y };
		if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
			this->curr_block.matrix_origin_point = next_origin_point;
			this->TIME_HOLDER[LEFT_ARROW] = 0;
		};
	};
	if (this->TIME_HOLDER[RIGHT_ARROW] > 60) {
		SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x + 1, this->curr_block.matrix_origin_point.y };
		if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
			this->curr_block.matrix_origin_point = next_origin_point;
			this->TIME_HOLDER[RIGHT_ARROW] = 0;
		};
	};
	if (this->TIME_HOLDER[DOWN_ARROW] > 30) {
		SDL_Point next_origin_point = { this->curr_block.matrix_origin_point.x, this->curr_block.matrix_origin_point.y + 1 };
		if (this->board.isAvailable(this->curr_block.matrix, this->board.static_board, next_origin_point, this->curr_block.current_block)) {
			this->curr_block.matrix_origin_point = next_origin_point;
			this->TIME_HOLDER[DOWN_ARROW] = 0;
		};
	};

		//Mouse
	if (arr_button[PAUSE_BUTTON].cur_status == "Mouse Down") {
		this->status = 1;
	}
}
;