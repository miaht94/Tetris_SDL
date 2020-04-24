#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
using namespace std;
class View
{
public:

	string path;

	// Tọa độ, diện tích của View trên màn hình
	// Đây là tọa độ tương đối so với Viewport
	// Tọa độ tuyệt đối của View trên màn hình = var_render + origin_point.var;
	int x_render      = 0;
	int y_render      = 0;
	int width_render  = 0;
	int height_render = 0;
	SDL_Point center_point_render = { 0,0 };

	//Xử lí animation
		Uint32 start_time = NULL;
		string animation;
		Uint32 duration = NULL;
		//Các biến backup đưa view về ban đầu sau animation
		int x_render_backup = 0;
		int y_render_backup = 0;
		int width_render_backup = 0;
		int height_render_backup = 0;
		SDL_Point center_point_render_backup = { 0,0 };
	
	//View Background 
		const View* view_background = NULL;
		double x_relative_ratio = 0;
		double y_relative_ratio = 0;
		double width_relative_ratio = 1;
		double height_relative_ratio = 1;

	//Key color RGB
	int R = 0;
	int G = 0;
	int B = 0;

	SDL_Renderer* renderer = NULL;

	SDL_Texture* texture = NULL;

	// mốc tọa độ để render (Viewport)
	SDL_Point origin_point = {0, 0};

	//xác định diện tích, tọa độ vùng lấy từ image để đưa vào texture 
	SDL_Rect* clip = NULL;

	View();

	View(string path, int x = 0, int y = 0);

	~View();
	int getX();
		
	int setX(int x);

	int getY();

	int setY(int y);

	int setW(int w);

	int setH(int h);	

	int setRect(SDL_Rect rect);

	int setCenterPoint(SDL_Point center_point);

	int setRenderer(SDL_Renderer* renderer);

	//Function return false when Texture = NULL
	bool loadTexture(string path, bool have_color_key = false);

	int clipImage(int x, int y, int width, int height);

	bool animate(string animation);

	void update();

	void setAnimation(string animation, Uint32 duration);

	int render(bool render_with_center_point = false);

	void handleMouseEvent(SDL_Event* e);

	void setViewBackground(const View& background);
};

class TextView : public View {
public:
	TTF_Font* font = NULL;
	int font_size;
	TextView();
	TextView(TTF_Font* tFont, int font_size);
	bool makeTextTexture(const char* text, int size, SDL_Color color);
	void render(bool render_with_center_point = false);
};


class Button : public View {
public:
	std::map<string, SDL_Texture*> button_texture;
	string cur_status = "Mouse Out";
	string pre_status = "";
	Button();
	~Button();
	void loadTexture(string on_mouse_over, string on_mouse_out);
	void handleMouseEvent(SDL_Event* e);
	void update();
	void render(bool render_with_center_point = false);

};