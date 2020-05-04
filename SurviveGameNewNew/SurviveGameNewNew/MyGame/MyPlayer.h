#ifndef _MYPLAYER_H
#define _MYPLAYER_H

#include "../MyEngine.h"
#include "MyPlayerData.h"

class MyPlayer : public MyPlayerData
{
public:
	MyPlayer(MyPlayerData* data) : MyPlayerData(*data) {}

	void updatePos(short* arrayBlock, int width, int height, MyEngine* e);

};
static int bound(int min, int value, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}

#endif