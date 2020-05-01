#include "utility.h"

using namespace std;

wstring stringToWstring(string orig) {
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
std::string wstringToString(const std::wstring str) {// wstring转string
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char* p = new char[len];
	wcstombs(p, str.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
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

void wstring_trimmed(wstring& wstr) {
	//末尾
	int length = wstr.length();
	for (int i = length - 1; i >= 0; i--) {
		if (wstr[i] != TEXT(' ')) {
			if (i != length - 1)
				wstr.erase(i + 1);
			break;
		}
		if (i == 0)
			wstr.clear();
	}
	//开头
	length = wstr.length();
	for (int i = 0; i < length; i++) {
		if (wstr[i] != TEXT(' ')) {
			if (i != 0)
				wstr.erase(0, i);
			break;
		}
	}
}
