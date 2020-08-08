#include "utility.h"

using namespace std;

std::wstring strTrimmed(const wstring& wstr) {
	int begin = 0, end = wstr.length();
	for (int i = 0; i < wstr.length(); i++) {
		if (wstr[i] != _T(' ')) {
			begin = i;
			break;
		}
	}
	bool hasExpectSpace = false;
	for (int i = wstr.length() - 1; i >= 0; i--) {
		if (wstr[i] != _T(' ')) {
			hasExpectSpace = true;
			end = i + 1;
			break;
		}
	}
	if (!hasExpectSpace) end = 0;
	return wstring(wstr.begin() + begin, wstr.begin() + end);
}

wstring stringToWstring(const string& orig) {
	wstring result;
	int slength = (int)orig.length() + 1;
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, orig.c_str(), slength, NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), slength, m_wchar, len);
	m_wchar[len] = '0';
	result.append(m_wchar);
	delete[] m_wchar;
	return result;
}
string wstringToString(const std::wstring& str) {// wstring转string
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char* p = new char[len];
	wcstombs(p, str.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
}

inline void My::createTextureFromFile(LPDevice g_pDevice, wstring& path, UINT w, UINT h, ImageInfo* imageInfo, LPTexture* g_pTexture) {
    D3DXCreateTextureFromFileEx(
        g_pDevice,
        path.c_str(),
        w, h,
        0, 0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL,
        imageInfo,
        nullptr,
        g_pTexture
        );
}
inline void My::createTextureSizeFromFile(LPDevice g_pDevice, wstring& path, ImageInfo* imageInfo, LPTexture* g_pTexture) {
    createTextureFromFile(g_pDevice, path, D3DX_FROM_FILE, D3DX_FROM_FILE, imageInfo, g_pTexture);
}

void My::setSpriteScale(LPSprite pSpr, float scalePosX, float scalePosY, float xScale, float yScale,
	float rotPosX, float rotPosY, float rot) {
	D3DXMATRIX g_scale;
	D3DXMatrixTransformation2D(
		&g_scale,		//返回的矩阵
		&D3DXVECTOR2(scalePosX, scalePosY),		//缩放的中心
		0.0f,			//影响缩放的因素
		&D3DXVECTOR2(xScale, yScale),	//缩放
		&D3DXVECTOR2(rotPosX, rotPosY),	//旋转中心
		rot,			//旋转弧度
		nullptr		//平移量
		);
	pSpr->SetTransform(&g_scale);
	D3DXMatrixIdentity(&g_scale);
}


#ifdef DEBUG_CONSOLE
HANDLE hConsole;
#endif