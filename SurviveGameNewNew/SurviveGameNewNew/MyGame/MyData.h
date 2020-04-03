#ifndef _MYDATA_H
#define _MYDATA_H

#include "../utility.h"
#include <string>
#include <fstream>
#include <vector>

class MyTexture
{
public:
	LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
	D3DXIMAGE_INFO info;
};

/*
	��Ҫ�ͷŵĶ���
	vec_textures����
*/
class MyBlockTexture {
public:
	void onInit(std::string path, LPDIRECT3DDEVICE9 g_pDevice);

	void onDestroy();

	LPDIRECT3DTEXTURE9 texture(int id);

	std::vector<LPDIRECT3DTEXTURE9> vec_textures;
};

/*
	��Ҫ�ͷŵĶ���
	g_pPlayer
	test1 -> g_pTexture
*/
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
	MyTexture test1, test2;
};

#endif