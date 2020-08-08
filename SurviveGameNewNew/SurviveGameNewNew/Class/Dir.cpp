#include "Dir.h"

bool Dir::isExists(const std::string& path) {
	struct stat buffer;
	return stat((path).c_str(), &buffer) == 0;
}

void Dir::createDirectory(const std::wstring& path) {
	CreateDirectory(path.c_str(), nullptr);
}

bool Dir::removeDirectory(const std::wstring& path) {
	std::vector<std::wstring> childFiles, childDirs;
	entryList(path, &childDirs, &childFiles);
	//ɾ���ļ�
	for (auto it = childFiles.begin(); it < childFiles.end(); it++) {
		remove(wstringToString(path + TEXT("\\") + *it).c_str());
	}
	//ɾ���ļ���
	for (auto it = childDirs.begin(); it < childDirs.end(); it++) {
		removeDirectory(path + TEXT("\\") + *it);
	}
	return RemoveDirectory(path.c_str());
}

bool Dir::deleteFile(const std::wstring& path) {
	DeleteFile(path.c_str());
}

void Dir::entryList(const std::wstring& path, std::vector<std::wstring>* dirs, std::vector<std::wstring>* files) {
	if (dirs) dirs->clear();
	if (files) files->clear();
	if (!isExists(path))
		return;
	HANDLE hFile = NULL;
	WIN32_FIND_DATA data;
	hFile = FindFirstFile((path + TEXT("\\*")).c_str(), &data);
	if (hFile != INVALID_HANDLE_VALUE) {	//���ҵ���һ���ļ�
		do {
			std::wstring fileName(data.cFileName);
			//�ļ�����16, �ļ���32
			if (data.dwFileAttributes & 16) {
				if (dirs && fileName != TEXT(".") && fileName != TEXT(".."))
					dirs->push_back(fileName);
			}
			else {
				if (files)
					files->push_back(fileName);
			}
		} while (FindNextFile(hFile, &data));	//�ܹ��ҵ������ļ�
		FindClose(hFile);	//��������
	}
}