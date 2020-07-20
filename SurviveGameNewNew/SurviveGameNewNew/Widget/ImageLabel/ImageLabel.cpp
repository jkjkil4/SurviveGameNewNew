#include "ImageLabel.h"

using namespace My;

void ImageLabel::onSelfRender(int renderX, int renderY) {
	engine.g_pSprite->Draw(g_pTexture, nullptr, nullptr, &D3DXVECTOR3((float)renderX, (float)renderY, 0.0f), mixColor);
}