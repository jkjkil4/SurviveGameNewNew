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
		g_pDevice,	//�豸ָ��
#ifndef _DEBUG
		path.c_str(),//·�����ļ���
#else
		stringToLPCWSTR(path),//·�����ļ���
#endif
		D3DX_FROM_FILE,	//ͼƬ�Ŀ��������ļ�����
		D3DX_FROM_FILE,	//ͼƬ�ĸ��������ļ�����
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