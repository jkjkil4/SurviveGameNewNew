#ifndef _MYGLOBAL_H
#define _MYGLOBAL_H

class MyGlobal
{
public:
#pragma region MyGlobal类的嵌套类
	class CreateSave
	{
	public:
		explicit CreateSave(std::wstring name, int width, int height, UINT seed)
			: name(name), width(width), height(height), seed(seed) {}
		std::wstring name = TEXT("NULL");
		int width = 400;
		int height = 400;
		UINT seed = 114514;
	};
#pragma endregion
	void reset() {
		visibleFlag = 0;
		safeDelete(createSave);
	}

	//所显示的控件
	int visibleFlag = 0;

	CreateSave* createSave = nullptr;
	
};

#endif