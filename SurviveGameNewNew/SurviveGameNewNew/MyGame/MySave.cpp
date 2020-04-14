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


bool MySave::create(Info* info, UINT* proc, bool* needUpdate) {
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
		if (proc && needUpdate)
			if (*needUpdate)
				*proc = j * info->width;
	}
	for (int i = 0; i < info->width; i += 5) {
		setBlockBy2d(i, 16, 3);
	}
	setBlockBy2d(info->width - 1, info->height - 1, 3);

	return true;
}


bool MySave::save(UINT* proc, bool* needUpdate) {
	if (!info || !playerState || !blocks)
		return false;

	wstring& saveName = info->name;
	//����Ƿ��Ѿ�����
	bool dirFlag = true;
	string fileName = wstringToString(saveName);
	while (dirFlag) {
		struct stat buffer;
		dirFlag = stat(("data\\saves\\" + fileName).c_str(), &buffer) == 0;
		if (!dirFlag)
			break;
		fileName += "_";
	}
	saveName = stringToWstring(fileName);
	//�����ļ���
	createDirectory();
	if (proc)
		*proc = 0;
	//�浵
	wstring path = TEXT("data\\saves\\") + info->name;
	{
		ofstream out(path + TEXT("\\saveInfo"), ios::out | ios::binary);
		if (out.fail())
			return false;
		string saveNameStr = wstringToString(saveName);
		out.write((char*)saveNameStr.c_str(), saveNameStr.size());	//����
		time_t now = time(nullptr);
		out.write((char*)&now, 8);			//ʱ��
		UCHAR ch = VERSION_SAVE;
		out.write((char*)&ch, 1);			//�浵�汾
		out.write((char*)&info->seed, 2);	//����
		out.write((char*)&info->width, 2);	//���򷽿�����
		out.write((char*)&info->height, 2);	//���򷽿�����
		out.close();
	}
	//���
	{
		ofstream out(path + TEXT("\\player"), ios::out | ios::binary);
		if (out.fail())
			return false;
		out.write((char*)&playerState->x, 2);	//��Һ�����
		out.write((char*)&playerState->y, 2);	//���������
		out.close();
	}
	//����
	{
		ofstream out(path + TEXT("\\world\\blocks"), ios::out | ios::binary);
		if (out.fail())
			return false;
		for (int i = 0; i < info->height; i++) {
			out.write((char*)(blocks->blocks + (i * info->width)), (streamsize)(info->width) * 2);
			if (proc && needUpdate)
				if (*needUpdate)
					*proc = i * info->width;
		}
		out.close();
	}
	return true;
}


bool MySave::load(UINT* proc, bool* needUpdate) {
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
	std::wstring path = TEXT("data\\saves\\") + info->name;
	CreateDirectory(TEXT("data"), nullptr);
	CreateDirectory(TEXT("data\\saves"), nullptr);
	CreateDirectory(path.c_str(), nullptr);
	CreateDirectory((path + TEXT("\\world")).c_str(), nullptr);		//�浵Ŀ¼�µ�world�ļ���
}