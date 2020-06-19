#pragma once

#include "../utility.h"

namespace My {
	class TextureManager;
}


typedef void(*TextureManagerFunc)(void*);


/*
	TextureManager
	在需要处理设备丢失时手动管理 非D3D_MANAGED 的 Texture
*/
class My::TextureManager {
public:
	//第一个参数是销毁Texture时调用的函数, 第二个参数是恢复Texture时调用的函数
	explicit TextureManager(TextureManagerFunc releaseFunc, TextureManagerFunc resetFunc, void* sendObj = nullptr);

	//销毁和恢复Texture
	void releaseTexture();
	void resetTexture();

	//静态函数，用于遍历所有TextureManager来销毁和恢复Texture
	static void onReleaseTextures();
	static void onResetTextures();

	//静态函数，用于添加和移除TextureManager
	static void addManager(TextureManager* manager);
	static void removeManager(TextureManager* manager);

private:
	//分别在销毁和恢复Texture时调用的函数
	TextureManagerFunc releaseFunc = nullptr, resetFunc = nullptr;
	//传递的类
	void* sendObj = nullptr;

	//储存所有的TextureManager，方便遍历
	static std::vector<TextureManager*> vecTextureManager;
};