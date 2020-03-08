#include "MyReadGameData.h"
using namespace std;

void MyBlocksTextureData::onInit(string path, string file, LPDIRECT3DDEVICE9 g_pDevice) {
	fstream in(path + "\\" + file);
	if (in.is_open()) {
		char buffer[256];
		in.getline(buffer, 100);
		className = buffer;
		while (!in.eof()) {
			in.getline(buffer, 100);
			string fileName = buffer;
			if (fileName == "")
				continue;
			LPDIRECT3DTEXTURE9 g_pTexture = nullptr;
			myCreateTexture(g_pDevice, path + "\\" + fileName, 16, 16, nullptr, &g_pTexture);
			vec_textures.push_back(g_pTexture);
		}
	}
}

LPDIRECT3DTEXTURE9 MyBlocksTextureData::texture(int index){
	if (index >= 1 && index <= (int)(vec_textures.size()))
		return vec_textures[index - 1];
	return nullptr;
}

void MyBlocksTextureData::onDestroy(){
	for (int i = 0; i < (int)(vec_textures.size()); i++) {
		Safe_Release(vec_textures[i]);
	}
}
