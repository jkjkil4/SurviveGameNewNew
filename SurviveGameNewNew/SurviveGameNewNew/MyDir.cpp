#include "MyDir.h"

using namespace std;


bool MyDir::isExists(string path) {
	struct stat buffer;
	return stat((path).c_str(), &buffer) == 0;
}

void MyDir::createDirectory(wstring path) {
	CreateDirectory(path.c_str(), nullptr);
}

bool MyDir::removeDirectory(std::wstring path) {
	vector<wstring> childs;
	//ɾ���ļ�
	entryList(path, &childs, File);
	for (auto it = childs.begin(); it < childs.end(); it++) {
		remove(wstringToString(path + TEXT("\\") + *it).c_str());
	}
	//ɾ���ļ���
	entryList(path, &childs, Dir);
	for (auto it = childs.begin(); it < childs.end(); it++) {
		removeDirectory(path + TEXT("\\") + *it);
	}
	return RemoveDirectory(path.c_str());
}

void MyDir::entryList(wstring path, vector<wstring>* files, int flags) {
	files->clear();
	if (!isExists(wstringToString(path)))
		return;
	HANDLE hFile = NULL;
	WIN32_FIND_DATA data;
	hFile = FindFirstFile((path + TEXT("\\*")).c_str(), &data);
	bool needDir = flags & Dir;
	bool needFile = flags & File;
	if (hFile != INVALID_HANDLE_VALUE) {	//���ҵ���һ���ļ�
		do {
			wstring fileName(data.cFileName);
			//�ļ�����16, �ļ���32
			if (data.dwFileAttributes & 16) {
				if (needDir) {
					if (fileName != TEXT(".") && fileName != TEXT(".."))
						files->push_back(fileName);
				}
			}
			else {
				if (needFile) {
					files->push_back(fileName);
				}
			}
		} while (FindNextFile(hFile, &data));	//�ܹ��ҵ������ļ�
		FindClose(hFile);	//��������
	}
}