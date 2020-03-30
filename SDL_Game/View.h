#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

using namespace std;
class View
{
private:

	string path;

	// Tọa độ, diện tích của View trên màn hình
	int x_render      = 0;
	int y_render      = 0;
	int width_render  = 0;
	int height_render = 0;

	//Key color RGB
	int R = 0;
	int G = 0;
	int B = 0;

public:
	SDL_Renderer* renderer = NULL;

	SDL_Texture* texture = NULL;

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

	int setRenderer(SDL_Renderer* renderer);

	bool loadTexture(string path, bool have_color_key = false);

	int clipImage(int x, int y, int width, int height);

	int render();
};

