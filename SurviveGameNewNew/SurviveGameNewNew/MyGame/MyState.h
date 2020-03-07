#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class MyKey
{
public:
	void clearState() {
		w_pressed = false;
		a_pressed = false;
		s_pressed = false;
		d_pressed = false;
		space_pressed = false;

		w_released = false;
		a_released = false;
		s_released = false;
		d_released = false;
		space_released = false;
	}
	bool w_pressed = false;
	bool a_pressed = false;
	bool s_pressed = false;
	bool d_pressed = false;
	bool space_pressed = false;

	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	bool space = false;

	bool w_released = false;
	bool a_released = false;
	bool s_released = false;
	bool d_released = false;
	bool space_released = false;
};

class MyMouse
{
public:
	void clearState() {
		left_pressed = false;
		mid_pressed = false;
		right_pressed = false;
		left_released = false;
		mid_released = false;
		right_released = false;
	}
	bool left_pressed = false;
	bool mid_pressed = false;
	bool right_pressed = false;

	bool left = false;
	bool mid = false;
	bool right = false;

	bool left_released = false;
	bool mid_released = false;
	bool right_released = false;

	int x = 0;
	int y = 0;
};

class MyVaribles
{
public:

	int viewW = 100;
	int viewH = 100;
};

static void setState(int chKey, bool* pKey, bool* pKeyPressed, bool* pKeyReleased) {
	bool has = GetKeyState(chKey) < 0;
	if (!*pKey && has) {
		*pKeyPressed = true;
		*pKey = has;
	}
	else if (*pKey && !has) {
		*pKeyReleased = true;
		*pKey = has;
	}
}
