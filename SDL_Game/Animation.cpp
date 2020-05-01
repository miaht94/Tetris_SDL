
#include "Animation.h"

Animation::Animation(string name, int duration) :name(name), duration(duration) {}
Animation::Animation(string name, int duration, int wait_time) : name(name), duration(duration), wait_time(wait_time){}
Animation::Animation(string name, int duration, SDL_Point transform_vector, int wait_time): name(name), duration(duration),transform_vector(transform_vector), wait_time(wait_time)
{
	if (name != "Transform") cerr << "Invalid animation" << endl;
}
Animation::~Animation()
{
}


