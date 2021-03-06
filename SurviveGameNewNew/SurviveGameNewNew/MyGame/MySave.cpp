#include "MySave.h"

using namespace std;

MySave::~MySave() {
	safeDelete(info);
	safeDelete(player);
	if (blocks) {
		blocks->onDestroy();
		safeDelete(blocks);
	}
}


bool MySave::create(Info* info, UINT* proc, bool* needUpdate, std::mutex* m) {
	this->info = info;
	player = new MyPlayerData;
	blocks = new Blocks(new short[info->width * info->height]);
	//填充
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


bool MySave::save(UINT* proc, bool* needUpdate, std::mutex* m) {
	if (!info || !player || !blocks)
		return false;

	//创建文件夹
	createDirectory();
	m->lock();
	if (proc)
		*proc = 0;
	m->unlock();
	//存档
	wstring path = TEXT("data\\saves\\") + info->fileName;
	bool isAccept = true;
	if (!saveInfo())
		return false;
	//玩家
	{
		ofstream out(path + TEXT("\\player"), ios::out | ios::binary);
		if (!out.fail()) {
			out.write((char*)&player->x, sizeof(player->x));	//玩家横坐标
			out.write((char*)&player->y, sizeof(player->y));	//玩家纵坐标
			out.write((char*)&player->direction, sizeof(player->direction));		//玩家朝向
			out.write((char*)&player->currentXSpd, sizeof(player->currentXSpd));	//玩家横向速度
			out.write((char*)&player->currentYSpd, sizeof(player->currentYSpd));	//玩家纵向速度
			out.write((char*)&player->jumped, sizeof(player->jumped));				//玩家跳跃次数
			out.close();
		}
		else {
			isAccept = false;
		}
	}
	//方块
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
bool MySave::saveInfo() {
	if (!info)
		return false;
	wstring path = TEXT("data\\saves\\") + info->fileName;
	bool isAccept = true;
	{
		ofstream out(path + TEXT("\\saveInfo"), ios::out | ios::binary);
		if (!out.fail()) {
			//存档版本
			UINT ver = VERSION_SAVE;
			out.write((char*)&ver, sizeof(UINT));
			//名称
			wstring* saveName = &info->name;
			size_t strLen = saveName->length();
			out.write((char*)&strLen, sizeof(size_t));
			out.write((char*)saveName->c_str(), (streamsize)strLen * sizeof(WCHAR));
			//时间
			time_t now = time(nullptr);
			out.write((char*)&now, sizeof(time_t));
			//种子
			out.write((char*)&info->seed, sizeof(UINT));
			//横向方块数量
			out.write((char*)&info->width, sizeof(int));
			//纵向方块数量
			out.write((char*)&info->height, sizeof(int));

			out.close();
		}
		else {
			isAccept = false;
		}
	}
	return isAccept;
}


bool MySave::load(wstring path, wstring fileName, UINT* proc, bool* needUpdate, std::mutex* m) {
	//读取信息
	if (!loadInfo(path + TEXT("\\saveInfo"), fileName))
		return false;
	//读取玩家数据
	{
		ifstream in(path + TEXT("\\player"), ios::in | ios::binary);
		if (in.fail())
			return false;
		player = new MyPlayerData;
		in.read((char*)&player->x, sizeof(player->x));	//玩家横坐标
		in.read((char*)&player->y, sizeof(player->y));	//玩家纵坐标
		in.read((char*)&player->direction, sizeof(player->direction));		//玩家朝向
		in.read((char*)&player->currentXSpd, sizeof(player->currentXSpd));	//玩家横向速度
		in.read((char*)&player->currentYSpd, sizeof(player->currentYSpd));	//玩家纵向速度
		in.read((char*)&player->jumped, sizeof(player->jumped));			//玩家跳跃次数
		in.close();
	}
	//读取方块数据
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

bool MySave::loadInfo(wstring path, wstring fileName) {
	ifstream in(path, ios::in | ios::binary);
	if (in.fail())
		return false;
	//存档版本
	UINT ver = VERSION_SAVE;
	in.read((char*)&ver, sizeof(UINT));
	//名称的大小
	size_t strLen = 0;
	in.read((char*)&strLen, sizeof(size_t));
	//名称
	WCHAR* name = new WCHAR[strLen + 1];
	name[strLen] = TEXT('\0');
	in.read((char*)name, (streamsize)strLen * sizeof(WCHAR));
	wstring nameStr(name);
	delete[] name;
	//时间
	time_t time = 0;
	in.read((char*)&time, sizeof(time_t));
	//种子
	UINT seed = 114514;
	in.read((char*)&seed, sizeof(UINT));
	//横向方块数量
	int width = 400;
	in.read((char*)&width, sizeof(int));
	//纵向方块数量
	int height = 400;
	in.read((char*)&height, sizeof(int));

	in.close();
	safeDelete(info);
	info = new Info(nameStr, fileName, time, ver, seed, width, height);
	/*OutputDebugString((L"\n名称: " + nameStr + L"\n时间: " + to_wstring(time) + L"\n版本: " + to_wstring(ver) +
		L"\n种子: " + to_wstring(seed) + L"\n宽度: " + to_wstring(width) + L"\n高度: " + to_wstring(height) + L"\n").c_str());*/
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


wstring MySave::getSuitableFileName(wstring name) {
	string fileName = wstringToString(name);
	int count = 0;
	bool dirFlag = true;
	string result;
	while (true) {
		result = fileName + (count == 0 ? "" : "_" + to_string(count));
		dirFlag = MyDir::isExists("data\\saves\\" + result);
		if (!dirFlag)
			break;
		count++;
	}
	return stringToWstring(result);
}
void MySave::checkFileName() {
	if (!info)
		return;
	info->name = getSuitableFileName(info->fileName);
	info->fileName = info->name;
}
void MySave::createDirectory() {
	if (!info)
		return;
	std::wstring path = TEXT("data\\saves\\") + info->fileName;
	MyDir::createDirectory(TEXT("data"));
	MyDir::createDirectory(TEXT("data\\saves"));
	MyDir::createDirectory(path);
	MyDir::createDirectory(path + TEXT("\\world"));
}


