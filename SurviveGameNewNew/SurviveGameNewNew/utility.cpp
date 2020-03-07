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

