#include "Engine.h"

using namespace My;

void Engine::drawRestart() {
	g_pSprite->End();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Engine::drawRect(int x, int y, int w, int h, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
	Vertex* vertexs;
	vbRectangle->Lock(0, 0, (void**)&vertexs, 0);
	vertexs[0] = Vertex{ (float)x, (float)y, 0.0f, 1.0f, col1 };
	vertexs[1] = Vertex{ (float)(x + w), (float)y, 0.0f, 1.0f, col2 };
	vertexs[2] = Vertex{ (float)(x + w), (float)(y + h), 0.0f, 1.0f, col3 };
	vertexs[3] = Vertex{ (float)x, (float)(y + h), 0.0f, 1.0f, col4 };
	vbRectangle->Unlock();

	g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	g_pDevice->SetStreamSource(0, vbRectangle, 0, sizeof(Vertex));
	g_pDevice->SetIndices(ibRectangle);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Engine::drawBorder(int x, int y, int w, int h, int size, DWORD col) {
	//×ó²à
	drawRect(x, y, size, h, col, col, col, col);
	//ÓÒ²à
	drawRect(x + w - size, y, size, h, col, col, col, col);
	//¶¥²¿
	drawRect(x + size, y, w - 2 * size, size, col, col, col, col);
	//µ×²¿
	drawRect(x + size, y + h - size, w - 2 * size, size, col, col, col, col);
}
