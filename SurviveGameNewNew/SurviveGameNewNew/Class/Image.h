#pragma once

#include "../Engine/Engine.h"

namespace My {
	class Image;
}

class My::Image {
public:
	Image(std::wstring path) {
		ImageInfo info;
		HRESULT hr = D3DXCreateTextureFromFileEx(engine.g_pDevice, path.c_str(), D3DX_FROM_FILE, D3DX_FROM_FILE, 
			0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL,
			&info, nullptr, &g_pTexture
			);
		if (FAILED(hr))
			engine.showMsgBox(_T("a"), _T("ʧ��"), MB_OK);
		width = info.Width;
		height = info.Height;
	}
	~Image() {
		safeRelease(g_pTexture);
	}

	LPTexture g_pTexture = nullptr;
	int width, height;
};