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
	//������ҷ���
	int direction = 1;

	//��Һ����ƶ��ļ��ٶ�
	int xSpd = 2;
	//��Һ����ƶ�������ٶ�
	int xSpdMax = 3;
	//��Һ����ƶ�������	(�����ٶ��й�)
	int xObs = 1;
	//���Ŀǰ�����ƶ����ٶ�
	int currentXSpd = 0;

	//�������
	float grav = 0.2f;
	//�����������ٶ�
	int ySpdMax = 10;
	//�����Ծ	(����Ϊʲô��int������bool?��������ΪҪ���������())
	int jumped = 0;
	//�����Ծ����ٶ�
	int jumpSpeed = -6;
	//��������Ծ����
	int jumpMax = 6;
	//���Ŀǰ�����ƶ����ٶ�
	float currentYSpd = 0.0f;

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
