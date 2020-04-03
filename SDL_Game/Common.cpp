#include "Common.h"


using namespace std;

// Function for Block Processing
void copyMatrix(int src[][4], int des[][4], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			des[i][j] = src[i][j];

		}
	}
}
void copyBoard(int src[][HEIGHT_SQUARE + OFFSET_Y + 1], int des[][HEIGHT_SQUARE + OFFSET_Y + 1])
{
	for (int i = 0; i < WIDTH_SQUARE+OFFSET_X; i++) {
		for (int j = 0; j < HEIGHT_SQUARE+2*OFFSET_Y; j++) {

			des[i][j] = src[i][j];

		}
	}
}
void handle(const Uint8* current_key_state)
{
	if (current_key_state[SDL_SCANCODE_LEFT])
		TIME_HOLDER[LEFT_ARROW]++;
	else TIME_HOLDER[LEFT_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_UP])
		TIME_HOLDER[UP_ARROW]++;
	else TIME_HOLDER[UP_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_DOWN])
		TIME_HOLDER[DOWN_ARROW]++;
	else TIME_HOLDER[DOWN_ARROW] = 0;

	if (current_key_state[SDL_SCANCODE_RIGHT])
		TIME_HOLDER[RIGHT_ARROW]++;
	else TIME_HOLDER[RIGHT_ARROW] = 0;
};
void rotate(int matrix[][4], int n) {
	int temp_matrix[4][4];
	copyMatrix(matrix, temp_matrix, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			matrix[i][j] = temp_matrix[j][n - i - 1];

		}
	}

}