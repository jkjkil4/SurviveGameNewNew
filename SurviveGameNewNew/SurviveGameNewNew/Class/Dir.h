#pragma once

#include "../utility.h"

namespace Dir {
	bool isExists(std::string path);

	void createDirectory(std::wstring path);

	bool removeDirectory(std::wstring path);
	bool deleteFile(std::wstring path);

	void entryList(std::wstring path, std::vector<std::wstring>* dirs, std::vector<std::wstring>* files);
}