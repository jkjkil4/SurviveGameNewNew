#include "utility.h"

std::wstring stringToWstring(std::string orig) {
	int slength = (int)orig.length() + 1;
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, orig.c_str(), slength, NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), slength, m_wchar, len);
	m_wchar[len] = '\0';
	std::wstring r(m_wchar);
	delete[] m_wchar;
	return r;
}

void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path,
	D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture) {
	D3DXCreateTextureFromFileEx(
		g_pDevice,	//设备指针
		stringToWstring(path).c_str(),
		D3DX_FROM_FILE,	//图片的宽来自于文件本身
		D3DX_FROM_FILE,	//图片的高来自于文件本身
		0,				//多级渐进纹理的等级
		0,				//图片的作用
		D3DFMT_UNKNOWN,	//未知纹理格式
		D3DPOOL_MANAGED,	//受系统管理的存储空间
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		imageInfo,		//图片详细信息存储在这个结构体中
		nullptr,		//调色板信息
		g_pTexture		//返回的纹理指针
	);
}

