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

int View::setRenderer(SDL_Renderer* renderer) {

	this->renderer = renderer;
	return 1;

};

int View::clipImage(int x, int y ,int width, int height) {

	SDL_Rect temp_rect = { x, y, width, height };
	this->clip = &temp_rect;
	return 1;

};

int View::render() {
	if (this->texture == NULL) cerr << "Please load texture for View" << endl;
	if (this->renderer == NULL) cerr << "Please load renderer for View" << endl;
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
		return true;

	}
	else
		return false;

};

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

