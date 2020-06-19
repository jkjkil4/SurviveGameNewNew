#pragma once

#include "../utility.h"

namespace My {
	class TextureManager;
}


typedef void(*TextureManagerFunc)(void*);


/*
	TextureManager
	����Ҫ�����豸��ʧʱ�ֶ����� ��D3D_MANAGED �� Texture
*/
class My::TextureManager {
public:
	//��һ������������Textureʱ���õĺ���, �ڶ��������ǻָ�Textureʱ���õĺ���
	explicit TextureManager(TextureManagerFunc releaseFunc, TextureManagerFunc resetFunc, void* sendObj = nullptr);

	//���ٺͻָ�Texture
	void releaseTexture();
	void resetTexture();

	//��̬���������ڱ�������TextureManager�����ٺͻָ�Texture
	static void onReleaseTextures();
	static void onResetTextures();

	//��̬������������Ӻ��Ƴ�TextureManager
	static void addManager(TextureManager* manager);
	static void removeManager(TextureManager* manager);

private:
	//�ֱ������ٺͻָ�Textureʱ���õĺ���
	TextureManagerFunc releaseFunc = nullptr, resetFunc = nullptr;
	//���ݵ���
	void* sendObj = nullptr;

	//�������е�TextureManager���������
	static std::vector<TextureManager*> vecTextureManager;
};