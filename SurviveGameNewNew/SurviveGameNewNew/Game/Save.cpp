#include "Save.h"

using namespace My;
using namespace std;

#pragma region SaveInfo
vector<SaveInfo::InfoManagerVersionControler> SaveInfo::infoManagerVersionControlers = {
	SaveInfo::InfoManagerVersionControler(
		SAVE_CUR_VERSION,{
		new InfoManager_WString(&SaveInfo::saveNameInFile),
		new InfoManager_Data<UINT>(&SaveInfo::seed),
		new InfoManager_Data<time_t>(&SaveInfo::time)
		})
};

#define SF_INFOMATION(name) _T("data/saves/") + name + _T("/infomation")

bool SaveInfo::load(const wstring& name, list<wstring>* errWhat) {
	saveName = name;
	{
		ifstream ifs(SF_INFOMATION(saveName), ios::in | ios::binary);
		if (!ifs.is_open()) {	//判断是否成功打开文件
			if (errWhat) errWhat->push_back(_T("Cannot open file \"") SF_INFOMATION(saveName) _T("\" when load"));
			goto End;
		}
		ifs.read((char*)&version, sizeof(UINT));
		vector<InfoManager*>* infoManagers = getSuitableInfoManager(version);
		if (!infoManagers) {	//判断该版本的存档是否能被读取
			if (errWhat) errWhat->push_back(_T("The save \"" + saveName + _T("\" is too new")));
			goto End;
		}

		for (InfoManager* manager : *infoManagers)
			manager->read(&ifs, this);
	}

	wcout << saveName << "  " << saveNameInFile << "  " << seed << "  " << time << endl;

	End:
	return true;
}

bool SaveInfo::save(list<wstring>* errWhat) {
	createDirectory();
	{
		ofstream ofs(SF_INFOMATION(saveName), ios::out | ios::binary);
		if (!ofs.is_open()) {	//判断是否成功打开文件
			if (errWhat) errWhat->push_back(_T("Cannot open file \"") SF_INFOMATION(saveName) _T("\" when save"));
			goto End;
		}
		ofs.write((char*)&version, sizeof(UINT));
		for (InfoManager* manager : getNewestInfoManager()) {
			manager->write(&ofs, this);
		}
	}

	End:
	return true;
}

void SaveInfo::createDirectory() {
	Dir::createDirectory(_T("data"));
	Dir::createDirectory(_T("data/saves"));
	Dir::createDirectory(_T("data/saves/") + saveName);
}
#pragma endregion