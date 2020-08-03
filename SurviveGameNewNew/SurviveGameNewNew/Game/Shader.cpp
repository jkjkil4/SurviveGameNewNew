#include "Shader.h"

using namespace My;
using namespace std;

PixelShaderMap My::pixelShaderMap;
VertexShaderMap My::vertexShaderMap;

void PixelShaderMap::onInit(const wstring& path) {
	vector<wstring> files;
	Dir::entryList(path, nullptr, &files, Dir::File);

	for (wstring file : files) {
		LPD3DXBUFFER codeBuffer = nullptr;
		LPD3DXBUFFER errorBuffer = nullptr;

		LPConstantTable g_pConstantTable = nullptr;

		HRESULT hr = D3DXCompileShaderFromFile((path + _T('/') + file).c_str(), 0, 0, "Main", "ps_2_0",
			/*D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY*/D3DXSHADER_DEBUG, &codeBuffer, &errorBuffer, &g_pConstantTable);

		if (errorBuffer) {
#ifdef DEBUG_CONSOLE
			cout << (char*)errorBuffer->GetBufferPointer() << endl;
#endif
			errorBuffer->Release();
			continue;
		}

		if (FAILED(hr)) {
#ifdef DEBUG_CONSOLE
			wcout << _T("D3DXCompileShaderFromFile() - FAILED \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		if (!g_pConstantTable) {
#ifdef DEBUG_CONSOLE
			wcout << _T("g_pConstantTable is nullptr \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		LPPixelShader g_pPixelShader = nullptr;
		hr = engine.g_pDevice->CreatePixelShader((DWORD*)codeBuffer->GetBufferPointer(), &g_pPixelShader);

		if (FAILED(hr)) {
#ifdef DEBUG_CONSOLE
			wcout << _T("CreatePixelShader - FAILED \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		if (codeBuffer != nullptr) safeRelease(codeBuffer);
		if (errorBuffer != nullptr) safeRelease(errorBuffer);

		wstring fileName;
		for (int i = file.length() - 1; i >= 0; i--) {
			if (file[i] == '.') {
				fileName = file.substr(0, i);
				break;
			}
		}

#ifdef DEBUG_CONSOLE
		wcout << _T("Succeed in Loading PixelShader \"") + file + _T("\"") << endl;
#endif

		PixelShader_Table& st = (*this)[fileName] = { g_pPixelShader, g_pConstantTable };
		UINT count;
		g_pConstantTable->GetConstantDesc(g_pConstantTable->GetConstantByName(0, "Tex"), &st.texDesc, &count);
	}
}

void PixelShaderMap::onDestroy() {
	for (auto iter = begin(); iter != end(); iter++) {
		safeRelease((*iter).second.g_pPixelShader);
	}
}


void VertexShaderMap::onInit(const wstring& path) {
	vector<wstring> files;
	Dir::entryList(path, nullptr, &files, Dir::File);

	for (wstring file : files) {
		LPD3DXBUFFER codeBuffer = nullptr;
		LPD3DXBUFFER errorBuffer = nullptr;

		LPConstantTable g_pConstantTable = nullptr;

		HRESULT hr = D3DXCompileShaderFromFile((path + _T('/') + file).c_str(), 0, 0, "Main", "vs_1_1",
			/*D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY*/D3DXSHADER_DEBUG, &codeBuffer, &errorBuffer, &g_pConstantTable);

		if (errorBuffer) {
#ifdef DEBUG_CONSOLE
			cout << (char*)errorBuffer->GetBufferPointer() << endl;
#endif
			errorBuffer->Release();
			continue;
		}

		if (FAILED(hr)) {
#ifdef DEBUG_CONSOLE
			wcout << _T("D3DXCompileShaderFromFile() - FAILED \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		if (!g_pConstantTable) {
#ifdef DEBUG_CONSOLE
			wcout << _T("g_pConstantTable is nullptr \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		LPVertexShader g_pVertexShader = nullptr;
		hr = engine.g_pDevice->CreateVertexShader((DWORD*)codeBuffer->GetBufferPointer(), &g_pVertexShader);

		if (FAILED(hr)) {
#ifdef DEBUG_CONSOLE
			wcout << _T("CreateVertexShader - FAILED \"") + file + _T("\"") << endl;
#endif
			continue;
		}

		if (codeBuffer != nullptr) safeRelease(codeBuffer);
		if (errorBuffer != nullptr) safeRelease(errorBuffer);

		wstring fileName;
		for (int i = file.length() - 1; i >= 0; i--) {
			if (file[i] == '.') {
				fileName = file.substr(0, i);
				break;
			}
		}

#ifdef DEBUG_CONSOLE
		wcout << _T("Succeed in Loading VertexShader \"") + file + _T("\"") << endl;
#endif

		D3DXMATRIX matWorld, matView, matProj;
		engine.g_pDevice->GetTransform(D3DTS_WORLD, &matWorld);
		engine.g_pDevice->GetTransform(D3DTS_VIEW, &matView);
		engine.g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		D3DXMATRIX matWVP = matWorld * matView * matProj;
		VertexShader_Table& st = (*this)[fileName] = { g_pVertexShader, g_pConstantTable };
		st.g_pConstantTable->SetMatrix(engine.g_pDevice, st.g_pConstantTable->GetConstantByName(0, "WVPMatrix"), &matWVP);

	}
}

void VertexShaderMap::onDestroy() {
	for (auto iter = begin(); iter != end(); iter++) {
		safeRelease((*iter).second.g_pVertexShader);
	}
}