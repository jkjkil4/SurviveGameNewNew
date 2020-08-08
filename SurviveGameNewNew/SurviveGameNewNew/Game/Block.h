#pragma once

#include "../utility.h"

struct Block {
	enum CornerFlag { LeftTop, RightTop, LeftBottom, RightBottom };

	Block() = default;
	Block(USHORT fore, USHORT back, UCHAR cornerFlag) 
		: fore(fore), back(back), cornerFlag(cornerFlag) {}

	USHORT fore = 0, back = 0;
	UCHAR cornerFlag = 0;
};

inline bool operator==(Block& a, Block& b) {
	return a.fore == b.fore && a.back == b.back && a.cornerFlag == b.cornerFlag;
}