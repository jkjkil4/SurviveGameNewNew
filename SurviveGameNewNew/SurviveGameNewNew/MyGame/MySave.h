#ifndef _MYSAVE_H
#define _MYSAVE_H

#include "../MyDir.h"
#include "../MyNameSpace.h"
#include "MyPlayerData.h"

class MySave
{
public:
#pragma region MySave类的嵌套类
	class Info
	{
	public:
		Info(std::wstring name, std::wstring fileName, time_t time, UCHAR version, UINT seed, int width, int height)
			: name(name), fileName(fileName), time(time), version(version), seed(seed), width(width), height(height) {}

		std::wstring name = TEXT("NULL");
		std::wstring fileName = TEXT("NULL");
		time_t time = 0;
		UCHAR version = 0;
		UINT seed = 114514;
		int width = 400, height = 400;
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
#pragma endregion
//--------------------------------------------------
	~MySave();

	bool create(Info* info, UINT* proc = nullptr, bool* needUpdate = nullptr, std::mutex* m = nullptr);
	bool save(UINT* proc = nullptr, bool* needUpdate = nullptr, std::mutex* m = nullptr);
	bool saveInfo();
	bool load(std::wstring path, std::wstring fileName, UINT* proc = nullptr, bool* needUpdate = nullptr, std::mutex* m = nullptr);
	bool loadInfo(std::wstring path, std::wstring fileName);

	int findBlockBy2d(int x, int y);
	void setBlockBy2d(int x, int y, int id);

	static std::wstring getSuitableFileName(std::wstring name);
	void checkFileName();
	void createDirectory();

	Info* info = nullptr;
	MyPlayerData* player = nullptr;
	Blocks* blocks = nullptr;
};

#ifdef DEBUG_CONSOLE
static std::ostream& operator<<(std::ostream& stream, MySave::Info& info) {
	stream << "名称:" << wstringToString(info.name) << "\t种子:" << info.seed << "\t大小:" << info.width << 'x' << info.height << '\n';
	return stream;
}
#endif

#endif