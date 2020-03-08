#include "MyPlayer.h"

void MyPlayer::updatePos(int* arrayBlock, int width, int height, MyKey* key) {
	if (key->a_pressed) {
		direction = -1;
	} else if (key->d_pressed) {
		direction = 1;
	}
	int left_right = key->d - key->a;
	int up_down = key->s - key->w;
	int xMin = plW / 2;
	int xMax = width * 16 - plW / 2;
	int yMin = plH;
	int yMax = height * 16;
	x += left_right * 8;
	y += up_down * 8;
	x = bound(xMin, x, xMax);
	y = bound(yMin, y, yMax);
}


