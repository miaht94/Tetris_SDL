#pragma once
#include <iostream>
#include <SDL_rect.h>
using namespace std;

class Animation
{
public:
	string name = "";
	int duration = 0;
	Uint32 temp_time = NULL;
	Uint32 start_time = NULL;
	Uint32 wait_time = NULL;
	bool ended = false;
	SDL_Point transform_vector = { NULL, NULL };
	Animation(string name, int duration);
	Animation(string name, int duration, int wait_time);
	Animation(string name, int duration, SDL_Point transform_vector, int wait_time);
	~Animation();
};