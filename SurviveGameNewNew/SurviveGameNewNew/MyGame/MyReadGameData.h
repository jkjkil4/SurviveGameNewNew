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

class MyData
{
public:
	LPDIRECT3DTEXTURE9 g_pTexturePlayer = nullptr;

	MyBlocksTextureData* origBlocksTextureData = nullptr;

	void onDestroy() {
		Safe_Release(g_pTexturePlayer);
		origBlocksTextureData->onDestroy();
	}

};