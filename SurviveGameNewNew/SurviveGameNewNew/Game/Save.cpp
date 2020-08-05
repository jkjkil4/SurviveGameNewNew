#include "Save.h"

using namespace My;
using namespace std;

#pragma region SaveInfo
vector<InfoManager*> SaveInfo::infoManagers = {
	new InfoManager_WString(&SaveInfo::saveNameInFile),
	new InfoManager_Data<UINT>(&SaveInfo::seed),
	new InfoManager_Data<time_t>(&SaveInfo::time)
};

#define SF_INFOMATION(name) _T("data/saves/") + name + _T("/infomation")

bool SaveInfo::load(const wstring& name, list<wstring>* errWhat) {
	/*saveName = name;
	wstring path = _T("data/saves/") + name + _T("/config.ini");
	WCHAR buf[100];
	//存档名称
	GetPrivateProfileString(_T("config"), _T("saveName"), name.c_str(), buf, 35, path.c_str());
	saveNameInFile = wstring(buf);
	//种子
	seed = GetPrivateProfileInt(_T("config"), _T("seed"), 0, path.c_str());
	//时间
	GetPrivateProfileString(_T("config"), _T("time"), _T("0"), buf, 100, path.c_str());
	time = stoll(wstringToString(wstring(buf)));*/
	saveName = name;
	{
		ifstream ifs(SF_INFOMATION(saveName), ios::in | ios::binary);
		if (!ifs.is_open()) {
			if (errWhat) errWhat->push_back(_T("Cannot open file \"") SF_INFOMATION(saveName) _T("\" when load"));
		}
		else {
			for (InfoManager* manager : infoManagers) {
				manager->read(&ifs, this);
			}
		}
	}

	wcout << saveName << "  " << saveNameInFile << "  " << seed << "  " << time << endl;

	return true;
}

bool SaveInfo::save() {
	createDirectory();

	/*wstring path = _T("data/saves/") + saveName + _T("/config.ini");
	//存档名称
	WritePrivateProfileString(_T("config"), _T("saveName"), saveNameInFile.c_str(), path.c_str());
	//种子
	WritePrivateProfileString(_T("config"), _T("seed"), to_wstring(seed).c_str(), path.c_str());
	//时间
	WritePrivateProfileString(_T("config"), _T("time"), to_wstring(time).c_str(), path.c_str());*/
	{
		ofstream ofs(SF_INFOMATION(saveName), ios::out | ios::binary);
		for (InfoManager* manager : infoManagers) {
			manager->write(&ofs, this);
		}
	}

	return true;
}

void SaveInfo::createDirectory() {
	Dir::createDirectory(_T("data"));
	Dir::createDirectory(_T("data/saves"));
	Dir::createDirectory(_T("data/saves/") + saveName);
}
#pragma endregion