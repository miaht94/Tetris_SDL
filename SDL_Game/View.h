#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
class View
{
public:

	string path;

	// Tọa độ, diện tích của View trên màn hình
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

	int render();
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