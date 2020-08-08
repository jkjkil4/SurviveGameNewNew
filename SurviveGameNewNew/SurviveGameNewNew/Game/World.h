#pragma once

#include "../utility.h"
#include "../NameSpace.h"

#include "InfoManager.h"

#include "Block.h"

namespace My {
	class World;
	class World_MainWorld;
}


class My::World {
public: 
	virtual ~World() { safeDeleteArray(blocks); }

	virtual bool load(const std::wstring&, std::list<std::wstring>* = nullptr) { return false; }
	virtual bool save(const std::wstring&, std::list<std::wstring>* = nullptr) { return false; }
	virtual bool create(int, int, std::list<std::wstring>* = nullptr) { return false; }

	void createDirectory(const std::wstring& name, const std::wstring& worldName);

	UINT version;
	UINT w;
	UINT h;
	Block* blocks = nullptr;
};

#define WORLD_MAINWORLD_VERSION 0

class My::World_MainWorld : public World
{
public:
	~World_MainWorld() override = default;

	static void onDestroyInfoManagers() {
		for (auto vc : imvc) {
			for (auto im : vc.infoManagers)
				delete im;
		}
		imvc.clear();
	}

	static std::vector<InfoManagerVersionControler<World_MainWorld>> imvc;

	bool load(const std::wstring& saveName, std::list<std::wstring>* errWhat = nullptr) override;
	bool save(const std::wstring& saveName, std::list<std::wstring>* errWhat = nullptr) override;
	bool create(int w_, int h_, std::list<std::wstring>* errWhat = nullptr) override;

	
};