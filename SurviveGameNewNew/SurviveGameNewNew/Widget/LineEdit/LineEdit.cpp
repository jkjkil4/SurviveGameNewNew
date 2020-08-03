#include "LineEdit.h"

using namespace My;


LineEdit::LineEdit(LPFont font, TextAlign textAlign, int w, int h, Align align, Widget* parent)
	: AbstractLineEdit(font, textAlign, w, h, align, parent) 
{
	textColor = 0xffffffff;
	boxOffset = { 1, 1, -2, -2 };
}

void LineEdit::onSelfRender(int renderX, int renderY) {
	engine.drawRestart();
	engine.drawRect(renderX + 1, renderY + 1, w - 2, h - 2, backgroundColor);
	drawText(renderX, renderY);
	engine.drawRestart();
	engine.drawBorder(renderX, renderY, w, h, 1, borderColor);
}