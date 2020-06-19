#pragma once

#pragma region WINDOWS头文件和库文件

//-------Windows头及库文件-------
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

inline RECT mkRect(int x, int y, int w, int h) {
    RECT rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;
    return rect;
}

#define _T TEXT

#pragma endregion

#pragma region d3d9的头文件和库文件

//-------D3D头及库文件-------
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#define CHECK_HR(hr, ...) if(FAILED(hr))__VA_ARGS__

struct Vertex
{
	float x, y, z, rhw;
	DWORD color;
};

#pragma endregion

#include <string>
#include <vector>
#include <mutex>

#pragma region d3d9的一些typedef
typedef LPDIRECT3DTEXTURE9 LPTexture;
typedef LPDIRECT3DSURFACE9 LPSurface;
typedef LPD3DXSPRITE LPSprite;

typedef LPDIRECT3D9 LPDirectx;
typedef LPDIRECT3DDEVICE9 LPDevice;

typedef D3DXIMAGE_INFO ImageInfo;
#pragma endregion

#pragma region 一些宏定义

#define NEEDLOCK_GET_FUNC(mutexName, FuncName, varibleName, varibleType)\
    varibleType get##FuncName(){\
		mutexName.lock();\
		varibleType temp = varibleName;\
		mutexName.unlock();\
		return temp;\
	}

#define NEEDLOCK_SET_FUNC(mutexName, FuncName, varibleName, varibleType)\
    void set##FuncName(varibleType _##varibleName){\
		mutexName.lock();\
		varibleName = _##varibleName;\
		mutexName.unlock();\
	}

#define NEEDLOCK_VARIBLE_FUNC(FuncName, varibleName, varibleType)\
	std::mutex m##FuncName;\
	NEEDLOCK_GET_FUNC(m##FuncName, FuncName, varibleName, varibleType)\
    NEEDLOCK_SET_FUNC(m##FuncName, FuncName, varibleName, varibleType)\

#pragma endregion

namespace My {
    inline void createTextureFromFile(LPDevice g_pDevice, std::wstring& path, UINT w, UINT h, ImageInfo* imageInfo, LPTexture* g_pTexture);
    inline void createTextureSizeFromFile(LPDevice g_pDevice, std::wstring& path, ImageInfo* imageInfo, LPTexture* g_pTexture);

    void setSpriteScale(LPSprite pSpr, float scalePosX, float scalePosY, float xScale, float yScale,
        float rotPosX = 0, float rotPosY = 0, float rot = 0);
	
    template<typename T>inline void safeDelete(T*& p) {
        if (p) {
            delete p;
            p = nullptr;
        }
    }
    template<typename T>inline void safeDeleteArray(T*& p) {
        if (p) {
            delete[] p;
            p = nullptr;
        }
    }
    template<typename T>inline void safeRelease(T*& p) {
        if (p) {
            p->Release();
            p = nullptr;
        }
    }
}
