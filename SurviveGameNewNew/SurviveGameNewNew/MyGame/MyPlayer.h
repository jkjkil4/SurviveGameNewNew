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
	//玩家左右方向
	int direction = 1;

	//玩家横向移动的加速度
	int xSpd = 2;
	//玩家横向移动的最大速度
	int xSpdMax = 3;
	//玩家横向移动的阻力	(还和速度有关)
	int xObs = 1;
	//玩家目前横向移动的速度
	int currentXSpd = 0;

	//玩家重力
	float grav = 0.2f;
	//玩家纵向最大速度
	int ySpdMax = 10;
	//玩家跳跃	(这里为什么用int而不用bool?可能是因为要做多段跳吧())
	int jumped = 0;
	//玩家跳跃后的速度
	int jumpSpeed = -6;
	//玩家最大跳跃次数
	int jumpMax = 6;
	//玩家目前纵向移动的速度
	float currentYSpd = 0.0f;

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
