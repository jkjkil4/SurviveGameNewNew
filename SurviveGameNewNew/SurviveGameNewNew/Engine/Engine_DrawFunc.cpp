#include "Engine.h"

using namespace My;

#include "../Game/Shader.h"


void Engine::setBlendMode(D3DBLEND srcBlend, D3DBLEND destBlend) {
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, srcBlend);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, destBlend);
}

void Engine::setPixelShader(PixelShader_Table* pst) {
	pCurPST = pst;
	if (pst) {
		g_pDevice->SetPixelShader(pst->g_pPixelShader);
	}
	else {
		g_pSprite->End();
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void Engine::setVertexShader(VertexShader_Table* vst) {
	pCurVST = vst;
	if (vst) {
		g_pDevice->SetVertexShader(vst->g_pVertexShader);
	}
	else {
		g_pSprite->End();
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void Engine::drawBegin() {
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (pCurPST) setPixelShader(pCurPST);
}

void Engine::drawRestart() {
	g_pSprite->End();
	drawBegin();
}

void Engine::drawRect(int x, int y, int w, int h, DWORD col) {
	drawRect(mkRect(x, y, w, h), col, col, col, col);
}

void Engine::drawRect(int x, int y, int w, int h, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
	drawRect(mkRect(x, y, w, h), col1, col2, col3, col4);
}

void Engine::drawRect(RECT rect, DWORD col) {
	drawRect(rect, col, col, col, col);
}
void Engine::drawRect(RECT rect, DWORD col1, DWORD col2, DWORD col3, DWORD col4) {
	Vertex* vertexs;
	vbRectangle->Lock(0, 0, (void**)&vertexs, 0);
	vertexs[0] = Vertex{ (float)rect.left, (float)rect.top, 0.0f, 1.0f, col1 };
	vertexs[1] = Vertex{ (float)rect.right, (float)rect.top, 0.0f, 1.0f, col2 };
	vertexs[2] = Vertex{ (float)rect.right, (float)rect.bottom, 0.0f, 1.0f, col3 };
	vertexs[3] = Vertex{ (float)rect.left, (float)rect.bottom, 0.0f, 1.0f, col4 };
	vbRectangle->Unlock();

	g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	g_pDevice->SetStreamSource(0, vbRectangle, 0, sizeof(Vertex));
	g_pDevice->SetIndices(ibRectangle);

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Engine::drawBorder(int x, int y, int w, int h, int size, DWORD col) {
	//×ó²à
	drawRect(x, y, size, h, col);
	//ÓÒ²à
	drawRect(x + w - size, y, size, h, col);
	//¶¥²¿
	drawRect(x + size, y, w - 2 * size, size, col);
	//µ×²¿
	drawRect(x + size, y + h - size, w - 2 * size, size, col);
}
