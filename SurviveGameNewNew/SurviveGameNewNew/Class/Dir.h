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
		if (hFile != INVALID_HANDLE_VALUE) {	//���ҵ���һ���ļ�
			do {
				std::wstring fileName(data.cFileName);
				//�ļ�����16, �ļ���32
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
			} while (FindNextFile(hFile, &data));	//�ܹ��ҵ������ļ�
			FindClose(hFile);	//��������
		}
	}
}