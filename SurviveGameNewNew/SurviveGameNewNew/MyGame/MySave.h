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
		Info(std::wstring name, time_t time, UCHAR version, int seed, int width, int height) {
			this->name = name;
			this->time = time;
			this->version = version;
			this->seed = seed;
			this->width = width;
			this->height = height;
		}

		std::wstring name = TEXT("NULL");
		time_t time = 0;
		UCHAR version = 0;
		int seed = 114514, width = 400, height = 400;
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
	bool save(UINT* proc = nullptr, bool* needUpdate = nullptr);
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