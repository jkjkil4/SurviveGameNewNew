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
	int vSpd = 2;
	//��Һ����ƶ�������ٶ�
	int vSpdMax = 6;
	//��Һ����ƶ�������	(�����ٶ��й�)
	int vObs = 1;
	//���Ŀǰ�����ƶ����ٶ�
	int currentVSpd = 0;

	//�������
	float grav = 0.2f;
	//�����������ٶ�
	int hSpdMax = 7;
	//�����Ծ	(����Ϊʲô��int������bool?��������ΪҪ���������())
	int jumped = 0;
	//�����Ծ����ٶ�
	int jumpSpeed = 6;
	//��������Ծ����
	int jumpMax = 6;
	//���Ŀǰ�����ƶ����ٶ�
	float currentHSpd = 0.0f;

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
