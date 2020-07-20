#include "Button.h"

using namespace My;

void Button::onSelfRender(int renderX, int renderY) {
	engine.g_pSprite->Draw(g_pTexture, nullptr, nullptr, &D3DXVECTOR3((float)renderX, (float)renderY, 0.0f), mixColor);
	font->DrawText(engine.g_pSprite, text.c_str(), -1, &mkRect(renderX, renderY, w, h), textAlign, textColor);
}