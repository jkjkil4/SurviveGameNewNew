#include "World.h"

using namespace My;
using namespace std;

vector<InfoManagerVersionControler<World_MainWorld>> World_MainWorld::imvc = {
	InfoManagerVersionControler<World_MainWorld>(
		WORLD_MAINWORLD_VERSION, {
		new InfoManager_Data<World_MainWorld, UINT>(&World_MainWorld::w),
		new InfoManager_Data<World_MainWorld, UINT>(&World_MainWorld::h)
		})
};

#define WORLD_PATH(name, worldName) _T("data/saves/") + name + _T("/Worlds/") + worldName
#define WORLD_INFO(name, worldName) WORLD_PATH(name, worldName) + _T("/info")
#define WORLD_DATA(name, worldName) WORLD_PATH(name, worldName) + _T("/data")


void World::createDirectory(const wstring& name, const wstring& worldName) {
	Dir::createDirectory(_T("data"));
	Dir::createDirectory(_T("data/saves"));
	Dir::createDirectory(_T("data/saves/") + name);
	Dir::createDirectory(_T("data/saves/") + name + _T("/Worlds"));
	Dir::createDirectory(_T("data/saves/") + name + _T("/Worlds/") + worldName);
}


bool World_MainWorld::load(const wstring& saveName, list<wstring>* errWhat) {
	bool hasErr = false;
	{//读取世界信息
		ifstream ifs(WORLD_INFO(saveName, _T("MainWorld")), ios::in | ios::binary);
		if (!ifs.is_open()) {	//如果文件没有成功打开
			if (errWhat) 
				errWhat->push_back(_T("Cannot open file \"") WORLD_INFO(saveName, _T("MainWorld")) _T("\" when loading"));
			hasErr = true;
			goto End;
		}
		ifs.read((char*)&version, sizeof(UINT));
		auto vc = getSuitableInfoManager(imvc, WORLD_MAINWORLD_VERSION, version);
		if (!vc) {	//判断能否读取
			if (errWhat) errWhat->push_back(_T("The world \"MainWorld\" is too new"));
			hasErr = true;
			ifs.close();
			goto End;
		}
		
		for (auto manager : *vc)	//读取
			manager->read(&ifs, this);

		ifs.close();
	}
	{//读取数据
		ifstream ifs(WORLD_DATA(saveName, _T("MainWorld")), ios::in | ios::binary);
		if (!ifs.is_open()) {
			if (errWhat)
				errWhat->push_back(_T("Cannot open file \"") WORLD_DATA(saveName, _T("MainWorld")) _T("\" when loading"));
			hasErr = true;
			goto End;
		}
		
		//读取
		int size = w * h;
		try {
			blocks = new Block[size];
		}
		catch (bad_alloc& mem) {	//如果bad_alloc了
			if (errWhat) errWhat->push_back(_T("Catch the error \"std::bad_alloc\" when loading -> " + stringToWstring(mem.what())));
			hasErr = true;
			ifs.close();
			goto End;
		}
		//ifs.read((char*)blocks, (streamsize)sizeof(Block) * size);
		int offset = 0;
		while (!ifs.eof()) {
			if (offset >= size) {
				if (errWhat) errWhat->push_back(_T("the size of file is bigger than the size of blockArray when loading world \"MainWorld\""));
				hasErr = true;
				ifs.close();
				goto End;
			}
			UCHAR len;
			ifs.read((char*)&len, sizeof(UCHAR));
			ifs.read((char*)(blocks + offset), (streamsize)sizeof(Block));
			for (int i = offset + 1; i < offset + len; i++) {
				blocks[i] = blocks[offset];
			}
			offset += len;
		}

		ifs.close();
	}

	End:
	return !hasErr;
}

bool World_MainWorld::save(const wstring& saveName, list<wstring>* errWhat) {
	createDirectory(saveName, _T("MainWorld"));
	bool hasErr = false;
	{//写入世界信息
		ofstream ofs(WORLD_INFO(saveName, _T("MainWorld")), ios::out | ios::binary);
		if (!ofs.is_open()) {
			if (errWhat) errWhat->push_back("Cannot open \"" WORLD_INFO(saveName, _T("MainWorld")) _T("\" when saving"));
			hasErr = true;
			goto End;
		}

		ofs.write((char*)&version, sizeof(UINT));
		for (auto manager : getNewestInfoManager(imvc))
			manager->write(&ofs, this);

		ofs.close();
	}
	{//写入数据
		ofstream ofs(WORLD_DATA(saveName, _T("MainWorld")), ios::out | ios::binary);
		if (!ofs.is_open()) {
			if (errWhat) errWhat->push_back("Cannot open \"" WORLD_DATA(saveName, _T("MainWorld")) _T("\" when saving"));
			hasErr = true;
			goto End;
		}

		int size = w * h;
		Block curBlock = blocks[0];
		UCHAR len = 1;
		int offset = 0;
		for (int i = 1; i < size; i++) {
			Block& rBlock = blocks[i];
			if (rBlock == curBlock && len != UCHAR_MAX) {
				len++;
			}
			else {
				ofs.write((char*)&len, sizeof(UCHAR));
				ofs.write((char*)(blocks + offset), sizeof(Block));
				offset += len;
				len = 1;
				curBlock = rBlock;
			}
		}
		ofs.write((char*)&len, sizeof(UCHAR));
		ofs.write((char*)(blocks + offset), sizeof(Block));

		ofs.close();
	}

	End:
	return !hasErr;
}

bool World_MainWorld::create(int w_, int h_, list<wstring>* errWhat) {
	bool hasErr = false;
	
	version = WORLD_MAINWORLD_VERSION;
	w = w_;
	h = h_;

	int size = w * h;
	try {
		blocks = new Block[size];
	}
	catch (std::bad_alloc& mem) {
		if (errWhat) errWhat->push_back(_T("Catch the error \"std::bad_alloc\" when creating -> ") + stringToWstring(mem.what()));
		hasErr = true;
		goto End;
	}
	{
		int index = 0;
		int inc = 1;
		while (index < size) {
			blocks[index] = Block(1, 2, false);
			index += inc;
			inc++;
		}
	}

	End:
	return !hasErr;
}