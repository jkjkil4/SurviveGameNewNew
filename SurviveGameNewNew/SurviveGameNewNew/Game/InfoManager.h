#pragma once

#include "../Class/Dir.h"

namespace My {
	template<typename Class>class InfoManager;
	template<typename Class>class InfoManager_WString;
	template<typename Class, typename T>class InfoManager_Data;

	template<typename Class>struct InfoManagerVersionControler;
}

template<typename Class>
class My::InfoManager {
public:
	virtual ~InfoManager() = default;
	virtual void read(std::ifstream*, Class*) {}
	virtual void write(std::ofstream*, Class*) {}
};

template<typename Class>
class My::InfoManager_WString : public InfoManager<Class>
{
public:
	InfoManager_WString(std::wstring Class::* pWString)
		: pWString(pWString) {}
	~InfoManager_WString() override = default;

	void read(std::ifstream* ifs, Class* saveInfo) override {
		int len;
		ifs->read((char*)&len, sizeof(int));
		WCHAR* wchArr = new WCHAR[len + 1];
		wchArr[len] = _T('\0');
		auto si = sizeof(int);
		ifs->read((char*)wchArr, (std::streamsize)sizeof(WCHAR) * len);
		saveInfo->*pWString = std::wstring(wchArr);
		delete[] wchArr;
	}
	void write(std::ofstream* ofs, Class* saveInfo) override {
		std::wstring& wstr = saveInfo->*pWString;
		int len = wstr.length();
		ofs->write((char*)&len, sizeof(int));
		ofs->write((char*)wstr.c_str(), (std::streamsize)sizeof(WCHAR) * len);
	}

	std::wstring Class::* pWString;
};

template<typename Class, typename T>
class My::InfoManager_Data : public InfoManager<Class>
{
public:
	InfoManager_Data(T Class::* pData)
		: pData(pData) {}
	~InfoManager_Data() override = default;

	void read(std::ifstream* ifs, Class* saveInfo) override {
		ifs->read((char*)&(saveInfo->*pData), sizeof(T));
	}
	void write(std::ofstream* ofs, Class* saveInfo) override {
		ofs->write((char*)&(saveInfo->*pData), sizeof(T));
	}

	T Class::* pData;
};


template<typename Class>
struct My::InfoManagerVersionControler {
	InfoManagerVersionControler(UINT version, const std::vector<InfoManager<Class>*>& infoManagers)
		: version(version), infoManagers(infoManagers) {}
	UINT version;
	std::vector<InfoManager<Class>*> infoManagers;
};


namespace My {
	template<typename Class>
	static std::vector<InfoManager<Class>*>& getNewestInfoManager(std::vector<InfoManagerVersionControler<Class>>& imvc) {
		return (*imvc.rbegin()).infoManagers;
	}

	template<typename Class>
	static std::vector<InfoManager<Class>*>* getSuitableInfoManager(std::vector<InfoManagerVersionControler<Class>>& imvc, UINT curVersion, UINT version) {
		if (version > curVersion)
			return nullptr;
		for (auto iter = imvc.rbegin(); iter < imvc.rend(); iter++) {
			InfoManagerVersionControler<Class>& vc = *iter;
			if (vc.version <= version)
				return &vc.infoManagers;
		}
		return nullptr;
	}
}