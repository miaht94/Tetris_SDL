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
	if (this->texture != NULL)
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
	if (animation.find("Scale Up") != string::npos) {
		double ratio_scale = 1.5;
		SDL_Point center_point;
		if (this->start_time == NULL) {
			this->start_time = SDL_GetTicks();
			this->x_render_backup = this->x_render;
			this->y_render_backup = this->y_render;
			this->width_render_backup = this->width_render;
			this->height_render_backup = this->height_render;
			this->center_point_render_backup = this->center_point_render;
		}
		center_point = this->center_point_render_backup;
		Uint32 time_offset = SDL_GetTicks() - this->start_time;
		if (time_offset > this->duration) return false;
		ratio_scale = ratio_scale - double(time_offset) / double(duration) * ratio_scale + 1;
		this->width_render = double(this->width_render_backup) * ratio_scale;
		this->height_render = double(this->height_render_backup) * ratio_scale;
		this->x_render = center_point.x - this->width_render / 2;
		this->y_render = center_point.y - this->height_render / 2;
	};

	if (animation .find("Appear") != string::npos) {
		double ratio_scale = 1;
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
		ratio_scale = double(time_offset) / double(duration) * ratio_scale;
		this->width_render = double(this->width_render_backup) * ratio_scale;
		this->height_render = double(this->height_render_backup) * ratio_scale;
		this->x_render = center_point.x - this->width_render / 2;
		this->y_render = center_point.y - this->height_render / 2;
	};
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
		this->center_point_render_backup = { 0,0 };
	};
	
	if (this->view_background != NULL) {
		this->origin_point.x = view_background->origin_point.x + view_background->x_render;
		this->origin_point.y = view_background->origin_point.y + view_background->y_render;
		this->x_render = this->view_background->width_render * this->x_relative_ratio;
		this->y_render = this->view_background->height_render * this->y_relative_ratio;
		this->width_render = this->view_background->width_render * this->width_relative_ratio;
		this->height_render = this->view_background->height_render * this->height_relative_ratio;
	}
}
;

void View::setAnimation(string animation, Uint32 duration)
{
	this->animation = animation;
	this->duration = duration;
}

int View::render(bool render_with_center_point) {
	if (this->texture == NULL) cerr << "Please load texture for View" << endl;
	if (this->renderer == NULL) cerr << "Please load renderer for View" << endl;
	View::update();
	if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point) {
		this->x_render = this->center_point_render.x - this->width_render / 2;
		this->y_render = this->center_point_render.y - this->height_render / 2;
	}
	SDL_Rect rect_des = { this->x_render + origin_point.x, this->y_render + origin_point.y, this->width_render, this->height_render };
	SDL_RenderCopy(this->renderer, texture, this->clip, &rect_des);
	return 1;

}

void View::setViewBackground(const View& background)
{
	if (background.renderer == NULL) 
		cerr << "Invalid Background" << endl;
	else {
		
		this->origin_point.x = background.origin_point.x + background.x_render;
		this->origin_point.y = background.origin_point.y + background.y_render;
		this->x_relative_ratio = double(this->x_render) / double(background.width_render);
		this->y_relative_ratio = double(this->y_render) / double(background.height_render);
		this->width_relative_ratio = double(this->width_render) / double(background.width_render);
		this->height_relative_ratio = double(this->height_render) / double(background.height_render);
		this->view_background = &background;

	}
}

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

	if (this->texture != NULL && this->width_render == 0 && this->height_render == 0) {

		SDL_QueryTexture(this->texture, NULL, NULL, &(this->width_render), &(this->height_render));
		//this->center_point_render = { this->width_render / 2, this->height_render / 2 };
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

Button::Button()
{
}

Button::~Button()
{
	if (button_texture["Mouse Over"] != NULL) SDL_DestroyTexture(button_texture["Mouse Over"]);
	if (button_texture["Mouse Down"] != NULL) SDL_DestroyTexture(button_texture["Mouse Down"]);
	if (button_texture["Mouse Up"] != NULL) SDL_DestroyTexture(button_texture["Mouse Up"]);
	if (button_texture["Mouse Out"] != NULL) SDL_DestroyTexture(button_texture["Mouse Out"]);
}

void Button::loadTexture(string on_mouse_over, string on_mouse_out)
{

	View::loadTexture(on_mouse_over);
	this->button_texture["Mouse Over"] = this->texture;
	this->button_texture["Mouse Down"] = this->texture;
	this->button_texture["Mouse Up"] = this->texture;


	View::loadTexture(on_mouse_out);
	this->button_texture["Mouse Out"] = this->texture;

}
void Button::handleMouseEvent(SDL_Event* e)
{
	bool inside = true;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN) {
		SDL_Point MOUSE_POSITION;
		SDL_GetMouseState(&MOUSE_POSITION.x, &MOUSE_POSITION.y);
		cout << MOUSE_POSITION.x << "  -  " << MOUSE_POSITION.y << endl;
		if (MOUSE_POSITION.x < this->origin_point.x + this->x_render)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (MOUSE_POSITION.x > this->origin_point.x + this->x_render + this->width_render)
		{
			inside = false;
		}
		//Mouse above the button
		else if (MOUSE_POSITION.y  < this->origin_point.y + this->y_render)
		{
			inside = false;
		}
		//Mouse below the button
		else if (MOUSE_POSITION.y > this->origin_point.y + this->y_render + this->height_render)
		{
			inside = false;
		}

	}
	if (!inside) 
		this->cur_status = "Mouse Out";
	else {
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			this->cur_status = "Mouse Over";
			break;

		case SDL_MOUSEBUTTONDOWN:
			this->cur_status = "Mouse Down";
			break;

		case SDL_MOUSEBUTTONUP:
			this->cur_status = "Mouse Up";
			break;
		}
	}
}
void Button::update()
{
	if (pre_status != cur_status) {
		pre_status = cur_status;
		this->texture = button_texture[cur_status];
	};
}
void Button::render(bool render_with_center_point)
{
	Button::update();
	if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point) {
		this->x_render = this->center_point_render.x - this->width_render / 2;
		this->y_render = this->center_point_render.y - this->height_render / 2;
	}
	View::render();
};