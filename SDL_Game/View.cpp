#include "View.h"

View::View() {
	//do nothing
};

View::View(string path, int x, int y) {

	this->x_render = x;
	this->y_render = y;
	this->path = path;

};

View::~View() {
	SDL_DestroyTexture(this->texture);
}

int View::getX() {

	return this->x_render;

};

int View::getY() {

	return this->y_render;

};

int View::setY(int y) {

	this->y_render = y;
	return 1;

};

int View::setX(int x) {

	this->x_render = x;
	return 1;

};

int View::setW(int w) {

	this->width_render = w;
	return 1;

};

int View::setH(int h) {

	this->height_render = h;
		return 1;

}

int View::setRect(SDL_Rect rect)
{
	this->x_render		= rect.x;
	this->y_render		= rect.y;
	this->width_render  = rect.w;
	this->height_render = rect.h;
	return 1;
}

int View::setCenterPoint(SDL_Point center_point) 
{
	this->center_point_render.x = center_point.x;
	this->center_point_render.y = center_point.y;
	this->x_render = center_point.x - this->width_render/2;
	this->y_render = center_point.y - this->height_render/2;
	return 0;
}

int View::setRenderer(SDL_Renderer* renderer) {

	this->renderer = renderer;
	return 1;

};

int View::clipImage(int x, int y ,int width, int height) {

	SDL_Rect temp_rect = { x, y, width, height };
	this->clip = &temp_rect;
	return 1;

}
bool View::animate(string animation)
{
	if (animation == "Scale Up") {
		double ratio_scale = 1.5;
		SDL_Point center_point;
		if (this->start_time == NULL) {
			this->start_time = SDL_GetTicks();
			this->x_render_backup = this->x_render;
			this->y_render_backup = this->y_render;
			this->width_render_backup = this->width_render;
			this->height_render_backup = this->height_render;
		}
		center_point = this->center_point_render;
		Uint32 time_offset = SDL_GetTicks() - this->start_time;
		if (time_offset > this->duration) return false;
		ratio_scale = ratio_scale - double(time_offset) / double(duration) * ratio_scale + 1;
		this->width_render = double(this->width_render_backup) * ratio_scale;
		this->height_render = double(this->height_render_backup) * ratio_scale;
		this->x_render = center_point.x - this->width_render / 2;
		this->y_render = center_point.y - this->height_render / 2;
	}
	return true;
}
void View::update()
{
	if (!View::animate(this->animation)) {
		this->animation = "";
		this->start_time = NULL;
		this->duration = NULL;
		this->x_render_backup = 0;
		this->y_render_backup = 0;
		this->width_render_backup = 0;
		this->height_render_backup = 0;
	}
}
;

void View::setAnimation(string animation, Uint32 duration)
{
	this->animation = animation;
	this->duration = duration;
}

int View::render() {
	if (this->texture == NULL) cerr << "Please load texture for View" << endl;
	if (this->renderer == NULL) cerr << "Please load renderer for View" << endl;
	View::update();
	SDL_Rect rect_des = { this->x_render + origin_point.x, this->y_render + origin_point.y, this->width_render, this->height_render };
	SDL_RenderCopy(this->renderer, texture, this->clip, &rect_des);
	return 1;

};

//Function return false when Texture = NULL
bool View::loadTexture(string path, bool have_color_key) {

	SDL_Surface* temp = IMG_Load(path.c_str());

	if (temp == NULL) 
		cout << "Unable to load image (path: " << path << " )" << endl << "Error :" << SDL_GetError() << endl;
	else {
		
		if (have_color_key)
			SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, this->R, this->G, this->B));

		SDL_Texture* nTexture = SDL_CreateTextureFromSurface(this->renderer, temp);
		this->texture = nTexture;
		SDL_FreeSurface(temp);

	};

	if (this->texture != NULL) {

		SDL_QueryTexture(this->texture, NULL, NULL, &(this->width_render), &(this->height_render));
		this->center_point_render = { this->width_render / 2, this->height_render / 2 };
		return true;

	}
	else
		return false;

};

TextView::TextView()
{
}

TextView::TextView(TTF_Font* tFont, int font_size)
{
	this->font_size = font_size;
	this->font = tFont;
}

bool TextView::makeTextTexture(const char* text, int size, SDL_Color color)
{
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	SDL_Surface* temp_surface = TTF_RenderText_Blended(this->font, text, color);
	if (temp_surface == NULL) {
		cerr << "Unable to make Text Surface, TTF_Error : " << TTF_GetError();
		return false;
	}
	else {
		double ratio = double(size) / double(this->font_size);
		this->width_render = double(temp_surface->w) * ratio;
		this->height_render = double(temp_surface->h) * ratio;
		//this->center_point_render = {this->origin_point.x + this->width_render / 2,this->origin_point.y + this->height_render / 2 };
		if (this->texture != NULL) {
			cout << "TextView texture pointer isn't NULL to make Texture" << endl;
			return false;
		};
		this->texture = SDL_CreateTextureFromSurface(this->renderer, temp_surface);
		if (this->texture == NULL) {
			cout << "Create Texture from surface error : " << SDL_GetError() << endl;
			return false;
		};
		SDL_FreeSurface(temp_surface);
	}
	return true;
}

void TextView::render(bool render_with_center_point)
{
	if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point) {
		this->x_render = this->center_point_render.x - this->width_render/2;
		this->y_render = this->center_point_render.y - this->height_render/2;
	}
	View::render();
}

