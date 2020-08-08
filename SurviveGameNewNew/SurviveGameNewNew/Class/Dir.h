#pragma once

#include "../utility.h"

namespace Dir {
	bool isExists(const std::string& path);
	inline  bool isExists(const std::wstring& path) { return isExists(wstringToString(path)); }

	void createDirectory(const std::wstring& path);

	bool removeDirectory(const std::wstring& path);
	bool deleteFile(const std::wstring& path);

	void entryList(const std::wstring& path, std::vector<std::wstring>* dirs, std::vector<std::wstring>* files);
}