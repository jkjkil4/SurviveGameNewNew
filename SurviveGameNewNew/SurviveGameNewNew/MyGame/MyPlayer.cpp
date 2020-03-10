#include "MyPlayer.h"

void MyPlayer::updatePos(int* arrayBlock, int width, int height, MyKey* key) {
	/*
		ע: ������������ϵ��ж�����ʹ������д��
			XXX = (XX + 16) / 16 - 1;
		����ܻ��룬�ⲻ�Ƕ��һ����?
		����ôд��ԭ���Ǳ��⸺��ʱ��bug 
		(		������int�����У�-2 / 16 = 0			)
		(		��������Ҫ�õ����� -1					)
		(		���� (-2 + 16) / 16 - 1 = -1			)
	*/
	//���ҷ�����ж�
	if (key->d_pressed) {
		direction = 1;
	} 
	else if (key->a_pressed) {
		direction = -1;
	}
	//���ٶ�
	if( key->d || key->a ){
		if (direction == 1) {
			currentXSpd += xSpd;
			if (currentXSpd > xSpdMax)
				currentXSpd = xSpdMax;
		}
		else if (direction == -1) {
			currentXSpd -= xSpd;
			if (currentXSpd < -xSpdMax)
				currentXSpd = -xSpdMax;
		}
	
	}
	//����
	else {
		if (currentXSpd > 0) {
			currentXSpd -= xObs + currentXSpd / 8;
			if (currentXSpd < 0) {
				currentXSpd = 0;
			}
		}
		else if (currentXSpd < 0) {
			currentXSpd += xObs + (-currentXSpd) / 8;
			if (currentXSpd > 0) {
				currentXSpd = 0;
			}
		}
	}
	//��������ҵ��ж���ͨ�õ���������
	int vStartY = (y - plH) / 16, vEndY = y / 16 - (y % 16 == 0);
	//һЩ����
	int xMin = plW / 2;
	int xMax = width * 16 - plW / 2;
	int toX = x + currentXSpd;
	//�����ƶ�
	if (currentXSpd < 0) {
		bool flag = false;
		int startX = (x - plW / 2 + 16) / 16 - 2;
		int endX = (x - plW / 2 + currentXSpd + 16) / 16 - 1;
		for (int i = startX; i >= endX; i--) {
			for (int j = vStartY; j <= vEndY; j++) {
				int id = (i>=0 && j>=0 && i<width && j<height ? arrayBlock[i + width * j] : -1);
				if (id) {
					currentXSpd = 0;
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
	else if (currentXSpd > 0) {
		bool flag = false;
		int startX = (x + plW / 2) / 16 + ((x + plW / 2) % 16 != 0);
		int endX = (x + plW / 2 + currentXSpd) / 16 - ((x + plW / 2 + currentXSpd) % 16 == 0);
		for (int i = startX; i <= endX; i++) {
			for (int j = vStartY; j <= vEndY; j++) {
				int id = (i >= 0 && j >= 0 && i < width && j < height ? arrayBlock[i + width * j] : -1);
				if (id) {
					currentXSpd = 0;
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
	//x = bound(xMin, x, xMax);
	//���Ϻ����µ��ж���ͨ�õ���������
	int hStartX = (x - plW / 2) / 16, hEndX = (x + plW / 2) / 16 - ((x + plW / 2) % 16 == 0);
	//��Ծ���ж�
	bool hasBlockBelow = false;
	int belowY = y / 16;
	for (int i = hStartX; i <= hEndX; i++) {
		int id = (i >= 0 && belowY >= 0 && i < width && belowY < height ? arrayBlock[i + width * belowY] : -1);
		if (id) {
			hasBlockBelow = true;
			break;
		}
	}
	if (!hasBlockBelow) {
		if (jumped == 0) {
			jumped = 1;
		}
		currentYSpd += grav;
		if (currentYSpd > ySpdMax)
			currentYSpd = (float)ySpdMax;
	}
	else {
		jumped = 0;
	}
	if (key->space_pressed) {
		if (jumped < jumpMax) {
			jumped++;
			currentYSpd = (float)jumpSpeed;
		}
	}
	if (key->space_released) {
		if((int)currentYSpd < 0)
			currentYSpd = 0.0f;
	}
	//����
	int yMin = plH;
	int yMax = height * 16;
	int intHSpd = (int)currentYSpd;		//int�������ٶ�
	int toY = y + intHSpd;
	//�����ƶ�
	if (intHSpd < 0) {
		bool flag = false;
		int startY = (y - plH + 16) / 16 - 2;
		int endY = (y - plH + intHSpd + 16) / 16 - 1;	//�����intHSpdС��0��������+
		for (int j = startY; j >= endY; j--) {
			for (int i = hStartX; i <= hEndX; i++) {
				int id = (i >= 0 && j >= 0 && i < width && j < height ? arrayBlock[i + width * j] : -1);
				if (id) {
					currentYSpd = 0.0f;
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
				int id = (i >= 0 && j >= 0 && i < width && j < height ? arrayBlock[i + width * j] : -1);
				if (id) {
					jumped = 0;
					currentYSpd = 0.0f;
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


