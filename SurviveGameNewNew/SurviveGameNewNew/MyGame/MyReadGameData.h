#pragma once
#include "../utility.h"
#include <string>
#include <fstream>
#include <vector>
class MyBlocksTextureData
{
public:
	void onInit(std::string path, std::string file, LPDIRECT3DDEVICE9 g_pDevice);
	LPDIRECT3DTEXTURE9 texture(int index);
	void onDestroy();

	std::string className = "";
	std::vector<LPDIRECT3DTEXTURE9> vec_textures;
};

class MyGUITextureData
{
public:
	void onInit(std::string path, LPDIRECT3DDEVICE9 g_pDevice);
	void onDestroy();

	LPDIRECT3DTEXTURE9 gui_selectSave_main;
	D3DXIMAGE_INFO gui_selectSave_main_info;
};

class MyData
{
public:
	//Íæ¼ÒÌùÍ¼
	LPDIRECT3DTEXTURE9 g_pTexturePlayer = nullptr;
	//·½¿éÌùÍ¼
	MyBlocksTextureData* origBlocksTextureData = nullptr;
	//GUIÌùÍ¼
	MyGUITextureData* guiTextureData = nullptr;

	void onDestroy() {
		Safe_Release(g_pTexturePlayer);
		if (origBlocksTextureData)
			origBlocksTextureData->onDestroy();
		if (guiTextureData)
			guiTextureData->onDestroy();
	}

};