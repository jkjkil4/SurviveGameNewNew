#ifndef _MYDATA_H
#define _MYDATA_H

#include "../utility.h"
#include <string>
#include <fstream>
#include <vector>

/*
	需要释放的对象：
	vec_textures内容
*/
class MyBlockTexture {
public:
	void onInit(std::string path, LPDIRECT3DDEVICE9 g_pDevice);

	void onDestroy();

	LPDIRECT3DTEXTURE9 texture(int id);

	std::vector<LPDIRECT3DTEXTURE9> vec_textures;
};
class MyPlayerTexture {
public:
	void onInit(std::string path, LPDIRECT3DDEVICE9 g_pDevice);

	void onDestroy();

	LPDIRECT3DTEXTURE9 g_pPlayer;
};

class MyData {
public:
	void onInit(std::string path, LPDIRECT3DDEVICE9 g_pDevice);

	void onDestroy();

	MyBlockTexture blockTexture;
	MyPlayerTexture playerTexture;

	//test
	LPDIRECT3DTEXTURE9 testAboutWidgets = nullptr;
	D3DXIMAGE_INFO info;
};

#endif