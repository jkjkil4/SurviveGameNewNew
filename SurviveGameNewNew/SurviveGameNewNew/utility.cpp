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

void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path, UINT w, UINT h,
	D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture) {
	D3DXCreateTextureFromFileEx(
		g_pDevice,	//设备指针
		stringToWstring(path).c_str(),
		w,	//图片的宽  //若要来自于图片本身则是 D3DX_FROM_FILE
		h,	//图片的高
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
void mySetScale(LPD3DXSPRITE pSpr, float scalePosX, float scalePosY, float xScale, float yScale, 
	float rotPosX, float rotPosY, float rot){
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


void getFiles(std::string path, std::string exd, std::vector<std::wstring>* files){
	files->clear();
	//文件句柄
	HANDLE hFile = 0;
	//文件信息
	WIN32_FIND_DATAW data;

	std::string file = path + "\\*" + (exd == "" ? "" : "." + exd);
	
	std::wstring wfile = stringToWstring(file);
	std::wstring dot = stringToWstring("."), dotdot = stringToWstring("..");

	hFile = FindFirstFile(wfile.c_str(), &data);
	if ((int)hFile != -1) {
		do {
			if (data.dwFileAttributes & 32) {
				if (data.cFileName != dot && data.cFileName != dotdot) {
					files->push_back(data.cFileName);
					OutputDebugString(data.cFileName);
				}
			}
		} while (FindNextFile(hFile, &data));
		FindClose(hFile);
	}
}
