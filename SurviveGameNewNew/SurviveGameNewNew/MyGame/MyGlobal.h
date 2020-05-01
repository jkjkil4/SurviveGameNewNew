#ifndef _MYGLOBAL_H
#define _MYGLOBAL_H

#include "MySave.h"

class MyGlobal
{
public:
#pragma region MyGlobal类的嵌套类
	class CreateSave
	{
	public:
		explicit CreateSave(std::wstring name, int width, int height, UINT seed)
			: name(name), width(width), height(height), seed(seed) {}
		void getVarible(std::wstring& pName, int& pWidth, int& pHeight, UINT& pSeed) {
			pName = name;
			pWidth = width;
			pHeight = height;
			pSeed = seed;
		}
		std::wstring name = TEXT("NULL");
		int width = 400;
		int height = 400;
		UINT seed = 114514;
	};
	class LoadSave
	{
	public:
		explicit LoadSave(std::wstring saveName)
			: saveName(saveName) {}
		void getVarible(std::wstring& pSaveName) {
			pSaveName = saveName;
		}
		std::wstring saveName = TEXT("");
	};
	class Game
	{
	public:
		explicit Game(MySave* save)
			: save(save) {}
		void getVarible(MySave*& pSave) {
			pSave = save;
		}
		MySave* save = nullptr;
	};
	class SaveSave
	{
	public:
		explicit SaveSave(MySave* save)
			:save(save) {}
		void getVarible(MySave*& pSave) {
			pSave = save;
		}
		MySave* save = nullptr;
	};
#pragma endregion
	void reset() {
		visibleFlag = 0;
		safeDelete(createSave);
		safeDelete(loadSave);
		safeDelete(game);
		safeDelete(saveSave);
	}

	//所显示的控件
	int visibleFlag = 0;

	CreateSave* createSave = nullptr;
	LoadSave* loadSave = nullptr;
	Game* game = nullptr;
	SaveSave* saveSave = nullptr;
};

#endif