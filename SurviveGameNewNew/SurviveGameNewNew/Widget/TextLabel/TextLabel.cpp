#include "TextLabel.h"

using namespace My;

void TextLabel::onSelfRender(int renderX, int renderY) {
	font->DrawTextW(engine.g_pSprite, text.c_str(), -1, &mkRect(renderX, renderY, w, h), textAlign, textColor);
}
