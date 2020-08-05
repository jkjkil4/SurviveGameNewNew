#include "Dir.h"

bool Dir::isExists(std::string path) {
	struct stat buffer;
	return stat((path).c_str(), &buffer) == 0;
}

void Dir::createDirectory(std::wstring path) {
	CreateDirectory(path.c_str(), nullptr);
}

bool Dir::removeDirectory(std::wstring path) {
	std::vector<std::wstring> childFiles, childDirs;
	entryList(path, &childDirs, &childFiles);
	//删除文件
	for (auto it = childFiles.begin(); it < childFiles.end(); it++) {
		remove(wstringToString(path + TEXT("\\") + *it).c_str());
	}
	//删除文件夹
	for (auto it = childDirs.begin(); it < childDirs.end(); it++) {
		removeDirectory(path + TEXT("\\") + *it);
	}
	return RemoveDirectory(path.c_str());
}

bool Dir::deleteFile(std::wstring path) {
	DeleteFile(path.c_str());
}

void Dir::entryList(std::wstring path, std::vector<std::wstring>* dirs, std::vector<std::wstring>* files) {
	if (dirs) dirs->clear();
	if (files) files->clear();
	if (!isExists(wstringToString(path)))
		return;
	HANDLE hFile = NULL;
	WIN32_FIND_DATA data;
	hFile = FindFirstFile((path + TEXT("\\*")).c_str(), &data);
	if (hFile != INVALID_HANDLE_VALUE) {	//查找到第一个文件
		do {
			std::wstring fileName(data.cFileName);
			//文件夹是16, 文件是32
			if (data.dwFileAttributes & 16) {
				if (dirs && fileName != TEXT(".") && fileName != TEXT(".."))
					dirs->push_back(fileName);
			}
			else {
				if (files)
					files->push_back(fileName);
			}
		} while (FindNextFile(hFile, &data));	//能够找到其他文件
		FindClose(hFile);	//结束查找
	}
}