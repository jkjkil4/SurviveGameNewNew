#pragma once
class MyPlayer
{
public:
	explicit MyPlayer(int x, int y);
	void updatePos(int* arrayBlock, int width, int height);
	//��ҿ��
	static constexpr int plW = 12;
	static constexpr int plH = 20;
	//�������
	int plX = 0;
	int plY = 0;
	//�������
	double grav = 0.2;

};
