#pragma once

#include "../Class/Dir.h"

namespace My {
	class SaveInfo;

	class InfoManager;
	class InfoManager_WString;
	template<typename T>class InfoManager_Data;
}


class My::InfoManager {
public:
	virtual ~InfoManager() = default;
	virtual void read(std::ifstream*, SaveInfo*) {}
	virtual void write(std::ofstream*, SaveInfo*) {}
};

class My::InfoManager_WString : public InfoManager
{
public:
	InfoManager_WString(std::wstring SaveInfo::* pWString)
		: pWString(pWString) {}
	~InfoManager_WString() override = default;

	void read(std::ifstream* ifs, SaveInfo* saveInfo) override {
		int len;
		ifs->read((char*)&len, sizeof(int));
		WCHAR* wchArr = new WCHAR[len + 1];
		wchArr[len] = _T('\0');
		auto si = sizeof(int);
		ifs->read((char*)wchArr, (std::streamsize)sizeof(WCHAR) * len);
		saveInfo->*pWString = std::wstring(wchArr);
		delete[] wchArr;
	}
	void write(std::ofstream* ofs, SaveInfo* saveInfo) override {
		std::wstring& wstr = saveInfo->*pWString;
		int len = wstr.length();
		ofs->write((char*)&len, sizeof(int));
		ofs->write((char*)wstr.c_str(), (std::streamsize)sizeof(WCHAR) * len);
	}

	std::wstring SaveInfo::* pWString;
};

template<typename T>
class My::InfoManager_Data : public InfoManager 
{
public:
	InfoManager_Data(T SaveInfo::* pData)
		: pData(pData) {}
	~InfoManager_Data() override = default;

	void read(std::ifstream* ifs, SaveInfo* saveInfo) override {
		ifs->read((char*)&(saveInfo->*pData), sizeof(T));
	}
	void write(std::ofstream* ofs, SaveInfo* saveInfo) override {
		ofs->write((char*)&(saveInfo->*pData), sizeof(T));
	}

	T SaveInfo::* pData;
};
