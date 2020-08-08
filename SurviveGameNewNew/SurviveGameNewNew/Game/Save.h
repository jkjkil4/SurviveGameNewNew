#pragma once

#include "InfoManager.h"

#include "World.h"

namespace My {
	class SaveInfo;
	class Save;
}

#define SAVE_CUR_VERSION 0

class My::SaveInfo 
{
public:
	static void onDestroyInfoManagers() {
		for (InfoManagerVersionControler<SaveInfo>& vc : imvc) {
			for (InfoManager<SaveInfo>* im : vc.infoManagers) {
				delete im;
			}
			vc.infoManagers.clear();
		}
		imvc.clear();
	}

	static std::vector<InfoManagerVersionControler<SaveInfo>> imvc;

	bool load(const std::wstring& name, std::list<std::wstring>* errWhat = nullptr);
	bool save(std::list<std::wstring>* errWhat = nullptr);
	void create(const std::wstring& name, UINT seed_);

	void createDirectory();

	UINT version = 0;
	std::wstring saveName;
	std::wstring saveNameInFile;
	UINT seed = 1;
	time_t time = 2;
};


class My::Save
{
public:
	bool load(const std::wstring& name, std::list<std::wstring>* errWhat = nullptr);
	bool save(std::list<std::wstring>* errWhat = nullptr);
	bool create(const std::wstring& name, UINT seed_, 
		int wMainWorldWidth, int wMainWorldHeight,
		std::list<std::wstring>* errWhat = nullptr);

	SaveInfo saveInfo;
	World_MainWorld wMainWorld;
};