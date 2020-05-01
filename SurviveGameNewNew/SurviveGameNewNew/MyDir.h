#ifndef _MYDIR_H
#define _MYDIR_H

#include "utility.h"
#include <sys/stat.h>

namespace MyDir {
	enum EntryFlags {Dir = 0b01, File = 0b10};

	bool isExists(std::string path);
	void createDirectory(std::wstring path);
	bool removeDirectory(std::wstring path);
	void entryList(std::wstring path, std::vector<std::wstring>* files, int flags);
};

#endif