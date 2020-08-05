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
		UINT version;
		std::vector<InfoManager*> infoManagers;
	};
	static InfoManagerVersionControler& getSuitableInfoManager() {

	}

	virtual ~SaveInfo() = default;

	virtual bool load(const std::wstring& name, std::list<std::wstring>* errWhat = nullptr);
	virtual bool save();

	virtual void createDirectory();

	static std::vector<InfoManager*> infoManagers;

	UINT version = 0;
	std::wstring saveName;
	std::wstring saveNameInFile;
	UINT seed = 1;
	time_t time = 2;
};