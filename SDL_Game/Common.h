#pragma once
#include <iostream>
#include <SDL.h>
using namespace std;

extern SDL_Window* gWindow;
const int LENGTH_SQUARE = 30;
const int WIDTH_SQUARE = 15;
const int HEIGHT_SQUARE = 20;
//bool checkResource(View view);
// Function to config game
bool Init();


// Function for process Block
void rotate(int matrix[][4], int n);
void copyMatrix(int src[][4], int des[][4], int n);