#pragma once
#include "../utility.h"
#include <string>
#include <fstream>
#include <vector>
class MyTextureData
{
public:
	void onInit(std::string path, std::string file, LPDIRECT3DDEVICE9 g_pDevice);
	LPDIRECT3DTEXTURE9 texture(int index);
	void onDestroy();

	std::string className = "";
	std::vector<LPDIRECT3DTEXTURE9> vec_textures;
};
