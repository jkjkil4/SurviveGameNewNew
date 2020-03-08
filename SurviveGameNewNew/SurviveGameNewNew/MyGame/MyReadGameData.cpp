#include "MyReadGameData.h"
using namespace std;

void MyTextureData::onInit(string path, string file, LPDIRECT3DDEVICE9 g_pDevice) {
	fstream in(path);
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
			myCreateTexture(g_pDevice, path + "\\" + fileName, 8, 8, nullptr, &g_pTexture);
			vec_textures.push_back(g_pTexture);
		}
	}
}

LPDIRECT3DTEXTURE9 MyTextureData::texture(int index){
	if( index >=0 && index < vec_textures.size() )
		return vec_textures[index];
	return nullptr;
}

void MyTextureData::onDestroy(){
	for (int i = 0; i < vec_textures.size(); i++) {
		Safe_Release(vec_textures[i]);
	}
}
