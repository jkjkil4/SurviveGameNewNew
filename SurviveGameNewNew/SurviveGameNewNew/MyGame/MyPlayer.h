#pragma once

#include "MyState.h"

class MyPlayer
{
public:
	void updatePos(int* arrayBlock, int width, int height, MyKey* key);

	//玩家宽高
	static constexpr int plW = 24;
	static constexpr int plH = 40;
	//玩家坐标
	int x = 0;
	int y = 0;
	//玩家重力
	double grav = 0.2;
	//玩家横向移动的速度
	int vSpd = 8;

	//玩家左右方向
	int direction = 1;

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
