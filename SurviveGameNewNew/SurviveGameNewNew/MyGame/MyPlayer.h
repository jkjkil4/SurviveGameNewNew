#pragma once

#include "MyState.h"

class MyPlayer
{
public:
	void updatePos(int* arrayBlock, int width, int height, MyKey* key);

	//��ҿ��
	static constexpr int plW = 24;
	static constexpr int plH = 40;
	//�������
	int x = 0;
	int y = 0;
	//�������
	double grav = 0.2;
	//��Һ����ƶ����ٶ�
	int vSpd = 8;

	//������ҷ���
	int direction = 1;

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
