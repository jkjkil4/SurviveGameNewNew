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
	readLinesToTexture(path, "blocks.info", g_pDevice, &vec_textures);
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
	myCreateTexture(g_pDevice, path + "\\player.png", 24, 40, nullptr, &g_pPlayer);
}
void MyPlayerTexture::onDestroy() {
	safeRelease(g_pPlayer);
}



void MyGuiTexture::onInit(string path, LPDIRECT3DDEVICE9 g_pDevice) {
	//按钮
	myCreateTexture(g_pDevice, path + "\\btnVerySmall.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &btnVerySmall.info, &btnVerySmall.g_pTexture);
	myCreateTexture(g_pDevice, path + "\\btnSmall.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &btnSmall.info, &btnSmall.g_pTexture);
	myCreateTexture(g_pDevice, path + "\\btnMedium.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &btnMedium.info, &btnMedium.g_pTexture);
	myCreateTexture(g_pDevice, path + "\\btnBig.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &btnBig.info, &btnBig.g_pTexture);
	//存档选择界面
	myCreateTexture(g_pDevice, path + "\\guiSaveSelect.png", D3DX_FROM_FILE, D3DX_FROM_FILE, &guiSaveSelect.info, &guiSaveSelect.g_pTexture);
}
void MyGuiTexture::onDestroy() {
	safeRelease(btnVerySmall.g_pTexture);
	safeRelease(btnSmall.g_pTexture);
	safeRelease(btnMedium.g_pTexture);
	safeRelease(btnBig.g_pTexture);
	safeRelease(guiSaveSelect.g_pTexture);
}



void MyData::onInit(string path, LPDIRECT3DDEVICE9 g_pDevice) {
	blockTexture.onInit(path + "\\blocks", g_pDevice);
	playerTexture.onInit(path + "\\player", g_pDevice);
	guiTexture.onInit(path + "\\gui", g_pDevice);
}
void MyData::onDestroy() {
	blockTexture.onDestroy();
	playerTexture.onDestroy();
	guiTexture.onDestroy();
}