#pragma once

#include "../utility.h"

namespace Dir {
	inline bool isExists(std::string path) {
		struct stat buffer;
		return stat((path).c_str(), &buffer) == 0;
	}


	enum FileType { Dir = 0b1, File = 0b10 };
	inline void entryList(std::wstring path, std::vector<std::wstring>* dirs, std::vector<std::wstring>* files, FileType flags) {
		if (dirs) dirs->clear();
		if (files) files->clear();
		if (!isExists(wstringToString(path)))
			return;
		HANDLE hFile = NULL;
		WIN32_FIND_DATA data;
		hFile = FindFirstFile((path + TEXT("\\*")).c_str(), &data);
		bool needDir = flags & Dir;
		bool needFile = flags & File;
		if (hFile != INVALID_HANDLE_VALUE) {	//查找到第一个文件
			do {
				std::wstring fileName(data.cFileName);
				//文件夹是16, 文件是32
				if (data.dwFileAttributes & 16) {
					if (dirs && needDir) {
						if (fileName != TEXT(".") && fileName != TEXT(".."))
							dirs->push_back(fileName);
					}
				}
				else {
					if (files && needFile) {
						files->push_back(fileName);
					}
				}
			} while (FindNextFile(hFile, &data));	//能够找到其他文件
			FindClose(hFile);	//结束查找
		}
	}
}