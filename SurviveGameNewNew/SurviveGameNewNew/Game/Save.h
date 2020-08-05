#pragma once

#include "InfoManager.h"

namespace My {
	class SaveInfo;
}

#define SAVE_CUR_VERSION 0


class My::SaveInfo 
{
public:
	struct InfoManagerVersionControler {
		InfoManagerVersionControler(UINT version, const std::vector<InfoManager*>& infoManagers)
			: version(version), infoManagers(infoManagers) {}
		UINT version;
		std::vector<InfoManager*> infoManagers;
	};

	static void onDestroyInfoManagers() {
		for (InfoManagerVersionControler& vc : infoManagerVersionControlers) {
			for (InfoManager* im : vc.infoManagers) {
				delete im;
			}
			vc.infoManagers.clear();
		}
		infoManagerVersionControlers.clear();
	}
	
	static std::vector<InfoManager*>* getSuitableInfoManager(UINT version) {
		if (version > SAVE_CUR_VERSION)
			return nullptr;
		for (auto iter = infoManagerVersionControlers.rbegin(); iter < infoManagerVersionControlers.rend(); iter++) {
			InfoManagerVersionControler& vc = *iter;
			if (vc.version <= version)
				return &vc.infoManagers;
		}
		return nullptr;
	}
	static std::vector<InfoManager*>& getNewestInfoManager() {
		return (*infoManagerVersionControlers.rbegin()).infoManagers;
	}

	static std::vector<InfoManagerVersionControler> infoManagerVersionControlers;

	virtual ~SaveInfo() = default;

	virtual bool load(const std::wstring& name, std::list<std::wstring>* errWhat = nullptr);
	virtual bool save(std::list<std::wstring>* errWhat = nullptr);

	virtual void createDirectory();

	UINT version = 0;
	std::wstring saveName;
	std::wstring saveNameInFile;
	UINT seed = 1;
	time_t time = 2;
};