#include "Save.h"

using namespace My;
using namespace std;

#pragma region SaveInfo
vector<InfoManagerVersionControler<SaveInfo>> SaveInfo::imvc = {
	InfoManagerVersionControler<SaveInfo>(
		SAVE_CUR_VERSION,{
		new InfoManager_WString<SaveInfo>(&SaveInfo::saveNameInFile),
		new InfoManager_Data<SaveInfo, UINT>(&SaveInfo::seed),
		new InfoManager_Data<SaveInfo, time_t>(&SaveInfo::time)
		})
};

#define SF_INFOMATION(name) _T("data/saves/") + name + _T("/infomation")

bool SaveInfo::load(const wstring& name, list<wstring>* errWhat) {
	bool hasErr = false;

	saveName = name;
	{
		ifstream ifs(SF_INFOMATION(saveName), ios::in | ios::binary);
		if (!ifs.is_open()) {	//判断是否成功打开文件
			if (errWhat) errWhat->push_back(_T("Cannot open file \"") SF_INFOMATION(saveName) _T("\" when loading"));
			hasErr = true;
			goto End;
		}
		ifs.read((char*)&version, sizeof(UINT));
		vector<InfoManager<SaveInfo>*>* infoManagers = getSuitableInfoManager(imvc, SAVE_CUR_VERSION, version);
		if (!infoManagers) {	//判断该版本的存档是否能被读取
			if (errWhat) errWhat->push_back(_T("The save \"" + saveName + _T("\" is too new")));
			hasErr = true;
			ifs.close();
			goto End;
		}

		//读档
		for (auto manager : *infoManagers)
			manager->read(&ifs, this);
		ifs.close();
	}

	End:
	return !hasErr;
}

bool SaveInfo::save(list<wstring>* errWhat) {
	bool hasErr = false;

	createDirectory();
	{
		ofstream ofs(SF_INFOMATION(saveName), ios::out | ios::binary);
		if (!ofs.is_open()) {	//判断是否成功打开文件
			if (errWhat) errWhat->push_back(_T("Cannot open file \"") SF_INFOMATION(saveName) _T("\" when saving"));
			hasErr = true;
			goto End;
		}

		//存档
		ofs.write((char*)&version, sizeof(UINT));
		for (auto manager : getNewestInfoManager(imvc))
			manager->write(&ofs, this);
		ofs.close();
	}

	End:
	return !hasErr;
}

void SaveInfo::create(const wstring& name, UINT seed_) {
	version = SAVE_CUR_VERSION;
	saveName = name;
	saveNameInFile = name;
	seed = seed_;
	time = ::time(nullptr);
}

void SaveInfo::createDirectory() {
	Dir::createDirectory(_T("data"));
	Dir::createDirectory(_T("data/saves"));
	Dir::createDirectory(_T("data/saves/") + saveName);
}
#pragma endregion


#pragma region Save
bool Save::load(const wstring& name, list<wstring>* errWhat) {
	bool hasErr = false;

	if (!saveInfo.load(name, errWhat)) {
		if (errWhat) errWhat->push_back(_T("Failed in loading the infomation of the save"));
		hasErr = true;
		goto End;
	}
	if (!wMainWorld.load(name, errWhat)) {
		if (errWhat) errWhat->push_back(_T("Failed in loading the world \"MainWorld\""));
		hasErr = true;
		goto End;
	}

	End:
	return !hasErr;
}

bool Save::save(list<wstring>* errWhat) {
	bool hasErr = false;

	if (!saveInfo.save(errWhat)) {
		if (errWhat) errWhat->push_back(_T("Failed in saving the infomation of the save"));
		hasErr = true;
		goto End;
	}
	if (!wMainWorld.save(saveInfo.saveName, errWhat)) {
		if (errWhat) errWhat->push_back(_T("Failed in saving the world \"MainWorld\""));
		hasErr = true;
		goto End;
	}

	End:
	return !hasErr;
}

bool Save::create(const wstring& name, UINT seed, 
	int wMainWorldWidth, int wMainWorldHeight,
	list<wstring>* errWhat) 
{
	bool hasErr = false;

	saveInfo.create(name, seed);
	if (!wMainWorld.create(wMainWorldWidth, wMainWorldHeight, errWhat)) {
		if (errWhat) errWhat->push_back(_T("Failed in creating the world \"MainWorld\""));
		hasErr = true;
		goto End;
	}

	End:
	return !hasErr;
}
#pragma endregion
