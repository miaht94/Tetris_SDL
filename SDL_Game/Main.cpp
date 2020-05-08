#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

//Init Function from LazyFoo
bool Init() {
	bool success = true;
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
		success = false;
	};

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	};

	gFont = TTF_OpenFont("Fonts/eurof55.ttf", FONT_SIZE);
	if (gFont == NULL) {
		cerr << "TTF Error: " << TTF_GetError() << endl;
		success = false;
	}
	gWindow = SDL_CreateWindow("Game SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		cerr << SDL_GetError();
		success = false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	return success;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
};
void exit() {
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
	Mix_Quit();
	SDL_DestroyWindow(gWindow);
};

int main(int agrc, char* argv[]) {
	
	if (Init()) {
		Game game(gRenderer, gFont);
		//game.playIntro();
		while (!game.quit && game.status != GAME_EXIT) {
			game.handleGameStatus();
		}
		/*SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		View view(gRenderer);
		view.loadTexture("textures/hard_drop.png");
		view.setW(30);
		view.setH(300);
		view.setCenterPoint({ 300,300 });
		View view2(gRenderer);
		view2.loadTexture("textures/hard_drop.png");
		view2.setW(30);
		view2.setH(300);
		view2.setCenterPoint({ 360,300 });
		view2.setAnimation("Cut Down", 1000);
		//view.angle = 0;
		//Animation* a = new Animation("Rotate", 6000, 1000, NULL);
		//view.setAnimation(a);
		while (true) {
			SDL_SetRenderDrawColor(gRenderer, 30, 61, 79, 255);
			SDL_RenderClear(gRenderer);
			view.render(true);
			view2.render();
			SDL_RenderPresent(gRenderer);
		}*/
	};
	SDL_Delay(200);
	exit();
	return 0;

}