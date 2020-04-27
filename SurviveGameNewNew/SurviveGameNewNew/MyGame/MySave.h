#ifndef _MYSAVE_H
#define _MYSAVE_H

#include "../utility.h"
#include "../MyNameSpace.h"
#include "../MyDir.h"

class MySave
{
public:
	class Info
	{
	public:
		Info(std::wstring name, time_t time, UCHAR version, UINT seed, int width, int height)
			: name(name), time(time), version(version), seed(seed), width(width), height(height) {}

		std::wstring name = TEXT("NULL");
		time_t time = 0;
		UCHAR version = 0;
		UINT seed = 114514;
		int width = 400, height = 400;
	};
	class PlayerState
	{
	public:
		PlayerState(int x, int y) {
			this->x = x;
			this->y = y;
		}

		int x = 0, y = 0;
	};
	class Blocks
	{
	public:
		Blocks(short* blocks) {
			this->blocks = blocks;
		}

		void onDestroy() {
			safeDeleteArray(blocks);
		}

		short* blocks = nullptr;
	};
//--------------------------------------------------
	~MySave();

	bool create(Info* info, UINT* proc = nullptr, bool* needUpdate = nullptr);
	bool save(UINT* proc = nullptr, bool* needUpdate = nullptr, bool checkName = false);
	bool load(std::wstring path, UINT* proc = nullptr, bool* needUpdate = nullptr);
	bool loadInfo(std::wstring path);

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);

	void createDirectory();

	Info* info = nullptr;
	PlayerState* playerState = nullptr;
	Blocks* blocks = nullptr;
};

#endif