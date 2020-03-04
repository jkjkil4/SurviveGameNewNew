#include "utility.h"

LPCWSTR stringToLPCWSTR(std::string orig) {
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}
void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, std::string path, D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture) {
	D3DXCreateTextureFromFileEx(
		g_pDevice,	//设备指针
#ifndef _DEBUG
		path.c_str(),//路径及文件名
#else
		stringToLPCWSTR(path),//路径及文件名
#endif
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

long long getCurrentTime() {
	long long time_last;
	time_last = time(NULL);

	struct timeb t1;
	ftime(&t1);
	time_t ttt = t1.millitm + t1.time * 1000;
	//std::stringstream ss;
	//ss << ttt;
	//std::string ts = ss.str();
	//return ts;
	return static_cast<long long>(ttt);
}