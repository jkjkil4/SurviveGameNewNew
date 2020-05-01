#include "MySave.h"

using namespace std;

MySave::~MySave() {
	safeDelete(info);
	safeDelete(playerState);
	if (blocks) {
		blocks->onDestroy();
		safeDelete(blocks);
	}
}


bool MySave::create(Info* info, UINT* proc, bool* needUpdate, std::mutex* m) {
	this->info = info;
	playerState = new PlayerState(1020, 100);
	blocks = new Blocks(new short[info->width * info->height]);
	//���
	for (int j = 0; j < info->height; j++) {
		for (int i = 0; i < info->width; i++) {
			if (j > 15 && (i == j || i == 2 * j || i == 3 * j || i == 4 * j || i == 5 * j || i == 6 * j)) {
				setBlockBy2d(i, j, 1);
			}
			else {
				setBlockBy2d(i, j, 0);
			}
		}
		if (proc && needUpdate) {
			Mutex(*m);
			if (*needUpdate)
				*proc = j * info->width;
			
		}
	}
	for (int i = 0; i < info->width; i += 5) {
		setBlockBy2d(i, 16, 3);
	}
	setBlockBy2d(info->width - 1, info->height - 1, 3);

	return true;
}


bool MySave::save(UINT* proc, bool* needUpdate, bool checkName, std::mutex* m) {
	if (!info || !playerState || !blocks)
		return false;

	wstring& saveName = info->name;
	
	bool dirFlag = true;
	string fileName = wstringToString(saveName);
	if (checkName) {
		//����Ƿ��Ѿ�����
		int count = 0;
		while (true) {
			dirFlag = MyDir::isExists("data\\saves\\" + fileName + (count == 0 ? "" : "_" + to_string(count)));
			if (!dirFlag)
				break;
			count++;
		}
		fileName = fileName + (count == 0 ? "" : "_" + to_string(count));
		saveName = stringToWstring(fileName);
	}
	//�����ļ���
	createDirectory();
	m->lock();
	if (proc)
		*proc = 0;
	m->unlock();
	//�浵
	wstring path = TEXT("data\\saves\\") + saveName;
	bool isAccept = true;
	{
		ofstream out(path + TEXT("\\saveInfo"), ios::out | ios::binary);
		if (!out.fail()) {
			//�浵�汾
			UINT ver = VERSION_SAVE;
			out.write((char*)&ver, sizeof(UINT));
			//����
			size_t strLen = saveName.length();
			out.write((char*)&strLen, sizeof(size_t));
			out.write((char*)saveName.c_str(), (streamsize)strLen * sizeof(WCHAR));
			//ʱ��
			time_t now = time(nullptr);
			out.write((char*)&now, sizeof(time_t));
			//����
			out.write((char*)&info->seed, sizeof(UINT));
			//���򷽿�����
			out.write((char*)&info->width, sizeof(int));
			//���򷽿�����
			out.write((char*)&info->height, sizeof(int));

			out.close();
		}
		else {
			isAccept = false;
		}
	}
	//���
	{
		ofstream out(path + TEXT("\\player"), ios::out | ios::binary);
		if (!out.fail()) {
			out.write((char*)&playerState->x, sizeof(int));	//��Һ�����
			out.write((char*)&playerState->y, sizeof(int));	//���������
			out.close();
		}
		else {
			isAccept = false;
		}
	}
	//����
	{
		ofstream out(path + TEXT("\\world\\blocks"), ios::out | ios::binary);
		if (!out.fail()) {
			for (int i = 0; i < info->height; i++) {
				out.write((char*)(blocks->blocks + (i * info->width)), (streamsize)(info->width) * 2);
				if (proc && needUpdate) {
					Mutex(*m);
					if (*needUpdate)
						*proc = i * info->width;
				}
			}
			out.close();
		}
		else {
			isAccept = false;
		}
	}
	return isAccept;
}


bool MySave::load(wstring path, UINT* proc, bool* needUpdate, std::mutex* m) {
	//��ȡ��Ϣ
	if (!loadInfo(path + TEXT("\\saveInfo")))
		return false;
	//��ȡ�������
	{
		ifstream in(path + TEXT("\\player"), ios::in | ios::binary);
		if (in.fail())
			return false;
		int playerX = 1000, playerY = 100;
		in.read((char*)&playerX, sizeof(int));	//��Һ�����
		in.read((char*)&playerY, sizeof(int));	//���������
		in.close();
		playerState = new PlayerState(playerX, playerY);
	}
	//��ȡ��������
	{
		ifstream in(path + TEXT("\\world\\blocks"), ios::in | ios::binary);
		if (in.fail())
			return false;
		streamsize wSize = (streamsize)info->width * sizeof(short);
		blocks = new Blocks(new short[info->width * info->height]);
		short* pBlocks = blocks->blocks;
		for (int i = 0; i < info->height; i++) {
			int offset = info->width * i;
			short* pOffset = pBlocks + offset;
			in.read((char*)pOffset, wSize);
			if (proc && needUpdate) {
				Mutex(*m);
				if (*needUpdate)
					*proc = offset;
			}
		}
		in.close();
	}
	return true;
}

bool MySave::loadInfo(wstring path) {
	ifstream in(path, ios::in | ios::binary);
	if (in.fail())
		return false;
	//�浵�汾
	UINT ver = VERSION_SAVE;
	in.read((char*)&ver, sizeof(UINT));
	//���ƵĴ�С
	size_t strLen = 0;
	in.read((char*)&strLen, sizeof(size_t));
	//����
	WCHAR* name = new WCHAR[strLen + 1];
	name[strLen] = TEXT('\0');
	in.read((char*)name, (streamsize)strLen * sizeof(WCHAR));
	wstring nameStr(name);
	delete[] name;
	//ʱ��
	time_t time = 0;
	in.read((char*)&time, sizeof(time_t));
	//����
	UINT seed = 114514;
	in.read((char*)&seed, sizeof(UINT));
	//���򷽿�����
	int width = 400;
	in.read((char*)&width, sizeof(int));
	//���򷽿�����
	int height = 400;
	in.read((char*)&height, sizeof(int));

	in.close();
	safeDelete(info);
	info = new Info(nameStr, time, ver, seed, width, height);
	/*OutputDebugString((L"\n����: " + nameStr + L"\nʱ��: " + to_wstring(time) + L"\n�汾: " + to_wstring(ver) +
		L"\n����: " + to_wstring(seed) + L"\n���: " + to_wstring(width) + L"\n�߶�: " + to_wstring(height) + L"\n").c_str());*/
	return true;
}


int MySave::findBlockBy2d(int x, int y) {
	if (info && blocks) {
		bool ok = x >= 0 && y >= 0 && x < info->width && y < info->height;
		return (ok ? blocks->blocks[x + info->width * y] : -1);
	}
	return -1;
}
void MySave::setBlockBy2d(int x, int y, int id) {
	if (info && blocks) {
		if (x >= 0 && y >= 0 && x < info->width && y < info->height)
			blocks->blocks[x + info->width * y] = id;
	}
}


void MySave::createDirectory() {
	if (!info)
		return;
	std::wstring path = TEXT("data\\saves\\") + info->name;
	MyDir::createDirectory(TEXT("data"));
	MyDir::createDirectory(TEXT("data\\saves"));
	MyDir::createDirectory(path);
	MyDir::createDirectory(path + TEXT("\\world"));
}


