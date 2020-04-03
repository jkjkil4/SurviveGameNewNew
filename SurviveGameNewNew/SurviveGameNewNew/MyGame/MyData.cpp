#include "MyData.h"
using namespace std;

void readLinesToTexture(string path, string file, LPDIRECT3DDEVICE9 g_pDevice, vector<LPDIRECT3DTEXTURE9>* vec) {
	fstream in(path + "\\" + file);
	if (in.is_open()) {
		char buffer[64];
		while (!in.eof()) {
			in.getline(buffer, 64);
			string fileName = buffer;
			if (fileName == "")
				continue;
			LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
			myCreateTexture(g_pDevice, path + "\\" + fileName, 16, 16, nullptr, &g_pTexture);
			vec->push_back(g_pTexture);
		}
	}
}

void MyBlockTexture::onInit(string path, LPDIRECT3DDEVICE9 g_pDevice) {
	readLinesToTexture(path + "\\blocks", "blocks.info", g_pDevice, &vec_textures);
}
void MyBlockTexture::onDestroy() {
	for (auto it = vec_textures.begin(); it < vec_textures.end(); it++)
		safeRelease(*it);
}
LPDIRECT3DTEXTURE9 MyBlockTexture::texture(int id) {
	int index = id - 1;
	return (index >= 0 && index < (int)vec_textures.size()) ? vec_textures[index] : nullptr;
}

void MyPlayerTexture::onInit(string path, LPDIRECT3DDEVICE9 g_pDevice) {
	myCreateTexture(g_pDevice, path + "\\player\\player.png", 24, 40, nullptr, &g_pPlayer);
}
void MyPlayerTexture::onDestroy() {
	safeRelease(g_pPlayer);
}

void MyData::onInit(string path, LPDIRECT3DDEVICE9 g_pDevice) {
	blockTexture.onInit(path, g_pDevice);
	playerTexture.onInit(path, g_pDevice);
	myCreateTexture(g_pDevice, path + "\\2.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &test1.info, &test1.g_pTexture);
	myCreateTexture(g_pDevice, path + "\\3.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &test2.info, &test2.g_pTexture);
}
void MyData::onDestroy() {
	blockTexture.onDestroy();
	playerTexture.onDestroy();
	safeRelease(test1.g_pTexture);
}