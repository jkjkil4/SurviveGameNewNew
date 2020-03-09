#include "MyPlayer.h"

void MyPlayer::updatePos(int* arrayBlock, int width, int height, MyKey* key) {
	int blockCount = width * height;
	//���ҷ�����ж�
	if (key->d_pressed) {
		direction = 1;
	} else if (key->a_pressed) {
		direction = -1;
	}
	//���ٶ�
	if( key->d || key->a ){
		if (direction == 1) {
			currentVSpd += vSpd;
			if (currentVSpd > vSpdMax)
				currentVSpd = vSpdMax;
		}
		else if (direction == -1) {
			currentVSpd -= vSpd;
			if (currentVSpd < -vSpdMax)
				currentVSpd = -vSpdMax;
		}
	//����
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
	//��������ҵ��ж���ͨ�õ���������
	const int vStartY = (y - plH) / 16, vEndY = y / 16 - (y % 16 == 0);
	//һЩ����
	const int xMin = plW / 2;
	const int xMax = width * 16 - plW / 2;
	int toX = x + currentVSpd;
	//�����ƶ�
	if (currentVSpd < 0) {
		bool flag = false;
		int startX = (x - plW / 2) / 16 - 1;
		int endX = (x - plW / 2 + currentVSpd) / 16;
		for (int i = startX; i >= endX; i--) {
			for (int j = vStartY; j <= vEndY; j++) {
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
	//�����ƶ�
	else if (currentVSpd > 0) {
		bool flag = false;
		int startX = (x + plW / 2) / 16 + ((x + plW / 2) % 16 != 0);
		int endX = (x + plW / 2 + currentVSpd) / 16 - ((x + plW / 2 + currentVSpd) % 16 == 0);
		for (int i = startX; i <= endX; i++) {
			for (int j = vStartY; j <= vEndY; j++) {
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
	//���Ϻ����µ��ж���ͨ�õ���������
	const int hStartX = (x - plW / 2) / 16, hEndX = (x + plW / 2) / 16 - ((x + plW / 2) % 16 == 0);
	//��Ծ���ж�
	bool hasBlockBelow = false;
	for (int i = hStartX; i <= hEndX; i++) {
		int pos = i + y / 16 * width;
		int id = (pos >= 0 && pos < blockCount ? arrayBlock[pos] : -1);
		if (id) {
			hasBlockBelow = true;
			break;
		}
	}
	if (!hasBlockBelow) {
		if (jumped == 0) {
			jumped = 1;
		}
		currentHSpd += grav;
	}
	if (key->space_pressed) {
		if (jumped < jumpMax) {
			jumped++;
			currentHSpd = -(float)jumpSpeed;
		}
	}
	if (key->space_released) {
		if((int)currentHSpd < 0)
			currentHSpd = 0.0f;
	}
	//����
	const int yMin = plH;
	const int yMax = height * 16;
	int intHSpd = (int)currentHSpd;		//int�������ٶ�
	int toY = y + intHSpd;
	//�����ƶ�
	if (intHSpd < 0) {
		bool flag = false;
		int startY = (y - plH) / 16 - 1;
		int endY = (y - plH + intHSpd) / 16;	//�����intHSpdС��0��������+
		for (int j = startY; j >= endY; j--) {
			for (int i = hStartX; i <= hEndX; i++) {
				int pos = i + width * j;
				int id = (pos >= 0 && pos < blockCount ? arrayBlock[pos] : -1);
				if (id) {
					currentHSpd = 0.0f;
					toY = 16 * (j + 1) + plH;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	//�����ƶ�
	else if (intHSpd > 0) {
		bool flag = false;
		int startY = y / 16 + (y % 16 != 0);
		int endY = (y + intHSpd) / 16 - ((y + intHSpd) % 16 == 0);
		for (int j = startY; j <= endY; j++) {
			for (int i = hStartX; i <= hEndX; i++) {
				int pos = i + width * j;
				int id = (pos >= 0 && pos < blockCount ? arrayBlock[pos] : -1);
				if (id) {
					jumped = 0;
					currentHSpd = 0.0f;
					toY = 16 * j;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	y = toY;
	y = bound(yMin, y, yMax);
}


