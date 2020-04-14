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
std::string wstringToString(const std::wstring str) {// wstringתstring
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char* p = new char[len];
	wcstombs(p, str.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
}

void myCreateTexture(LPDIRECT3DDEVICE9 g_pDevice, string path, UINT w, UINT h,
	D3DXIMAGE_INFO* imageInfo, LPDIRECT3DTEXTURE9* g_pTexture) {
	D3DXCreateTextureFromFileEx(
		g_pDevice,	//�豸ָ��
		stringToWstring(path).c_str(),
		w,	//ͼƬ�Ŀ�  //��Ҫ������ͼƬ�������� D3DX_FROM_FILE
		h,	//ͼƬ�ĸ�
		0,				//�༶��������ĵȼ�
		0,				//ͼƬ������
		D3DFMT_UNKNOWN,	//δ֪�����ʽ
		D3DPOOL_MANAGED,	//��ϵͳ����Ĵ洢�ռ�
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		imageInfo,		//ͼƬ��ϸ��Ϣ�洢������ṹ����
		nullptr,		//��ɫ����Ϣ
		g_pTexture		//���ص�����ָ��
	);
}
void mySetScale(LPD3DXSPRITE pSpr, float scalePosX, float scalePosY, float xScale, float yScale, 
	float rotPosX, float rotPosY, float rot){
	D3DXMATRIX g_scale;
	D3DXMatrixTransformation2D(
		&g_scale,		//���صľ���
		&D3DXVECTOR2(scalePosX, scalePosY),		//���ŵ�����
		0.0f,			//Ӱ�����ŵ�����
		&D3DXVECTOR2(xScale, yScale),	//����
		&D3DXVECTOR2(rotPosX, rotPosY),	//��ת����
		rot,			//��ת����
		nullptr		//ƽ����
	);
	pSpr->SetTransform(&g_scale);
	D3DXMatrixIdentity(&g_scale);
}


void getFiles(string path, string exd, vector<wstring>* files){
	files->clear();
	//�ļ����
	HANDLE hFile = 0;
	//�ļ���Ϣ
	WIN32_FIND_DATAW data;

	string file = path + "\\*" + (exd == "" ? "" : "." + exd);
	
	wstring wfile = stringToWstring(file);
	wstring dot = stringToWstring("."), dotdot = stringToWstring("..");

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

void wstring_trimmed(wstring& wstr) {
	//ĩβ
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
	//��ͷ
	length = wstr.length();
	for (int i = 0; i < length; i++) {
		if (wstr[i] != TEXT(' ')) {
			if (i != 0)
				wstr.erase(0, i);
			break;
		}
	}
}
