#pragma once
class MyPlayer
{
public:
	explicit MyPlayer(int x, int y);
	void updatePos(int* arrayBlock, int width, int height);
	//玩家宽高
	static constexpr int plW = 12;
	static constexpr int plH = 20;
	//玩家坐标
	int plX = 0;
	int plY = 0;
	//玩家重力
	double grav = 0.2;

};
