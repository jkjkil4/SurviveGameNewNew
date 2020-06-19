#include "TextureManager.h"

using namespace My;


TextureManager::TextureManager(TextureManagerFunc releaseFunc, TextureManagerFunc resetFunc, void* sendObj)
	: releaseFunc(releaseFunc), resetFunc(resetFunc), sendObj(sendObj) {}


void TextureManager::releaseTexture() {
	releaseFunc(sendObj);
}

void TextureManager::resetTexture() {
	resetFunc(sendObj);
}


void TextureManager::onReleaseTextures() {
	for (auto manager : vecTextureManager)
		manager->releaseTexture();
}

void TextureManager::onResetTextures() {
	for (auto manager : TextureManager::vecTextureManager)
		manager->resetTexture();
}


void TextureManager::addManager(TextureManager* manager) {
	vecTextureManager.push_back(manager);
}

void TextureManager::removeManager(TextureManager* manager) {
	for (auto it = vecTextureManager.begin(); it < vecTextureManager.end(); it++) {
		if (*it == manager) {
			vecTextureManager.erase(it);
			break;
		}
	}
}


//外部定义static变量
std::vector<TextureManager*> TextureManager::vecTextureManager;