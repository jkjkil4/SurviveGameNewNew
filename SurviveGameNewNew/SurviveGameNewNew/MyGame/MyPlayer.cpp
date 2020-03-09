#include "MyPlayer.h"

void MyPlayer::updatePos(int* arrayBlock, int width, int height, MyKey* key) {
	//左右方向的判断
	if (key->d_pressed) {
		direction = 1;
	} else if (key->a_pressed) {
		direction = -1;
	}
	//加速度
	if (key->d) {
		currentVSpd += vSpd;
		if (currentVSpd > vSpdMax)
			currentVSpd = vSpdMax;
	} else if (key->a) {
		currentVSpd -= vSpd;
		if (currentVSpd < -vSpdMax)
			currentVSpd = -vSpdMax;
	//阻力
	} else {
		if (currentVSpd > 0) {
			currentVSpd -= vObs + currentVSpd / 8;
			if (currentVSpd < 0) {
				currentVSpd = 0;
			}
		}
		else if (currentVSpd < 0) {
			currentVSpd += vObs - currentVSpd / 8;
			if (currentVSpd > 0) {
				currentVSpd = 0;
			}
		}
	}
	int up_down = key->s - key->w;
	int xMin = plW / 2;
	int xMax = width * 16 - plW / 2;
	int yMin = plH;
	int yMax = height * 16;
	int blockCount = width * height;
	int toX = x + currentVSpd;
	//向左移动
	if (currentVSpd < 0) {
		bool flag = false;
		int startX = (x - plW / 2) / 16 - 1;
		int endX = (x - plW / 2 + currentVSpd) / 16;
		int startY = (y - plH) / 16;
		int endY = y / 16 - (y % 16 == 0);
		for (int i = startX; i >= endX; i--) {
			for (int j = startY; j <= endY; j++) {
				int pos = i + width * j;
				int id = (pos >= 0 && pos < blockCount ? arrayBlock[pos] : -1);
				if (id) {
					currentVSpd = 0;
					toX = 16 * (i + 1) + plW / 2;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	} 
	//向右移动
	else if (currentVSpd > 0) {
		bool flag = false;
		int startX = (x + plW / 2) / 16 + ((x + plW / 2) % 16 != 0);
		int endX = (x + plW / 2 + currentVSpd) / 16 - ((x + plW / 2 + currentVSpd) % 16 == 0);
		int startY = (y - plH) / 16;
		int endY = y / 16 - (y % 16 == 0);
		for (int i = startX; i <= endX; i++) {
			for (int j = startY; j < endY; j++) {
				int pos = i + width * j;
				int id = (pos >= 0 && pos < blockCount ? arrayBlock[pos] : -1);
				if (id) {
					currentVSpd = 0;
					toX = 16 * i - plW / 2;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	x = toX;
	x = bound(xMin, x, xMax);
	y += up_down * vSpdMax/3;
	y = bound(yMin, y, yMax);
}


