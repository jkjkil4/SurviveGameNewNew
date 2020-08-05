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
inline LONG rectWidth(RECT rect) { return rect.right - rect.left; }
inline LONG rectHeight(RECT rect) { return rect.bottom - rect.top; }

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
#include <list>
#include <map>
#include <mutex>
#include <regex>
#include <fstream>

#pragma region d3d9的一些typedef
typedef LPDIRECT3DTEXTURE9 LPTexture;
typedef LPDIRECT3DSURFACE9 LPSurface;
typedef LPD3DXSPRITE LPSprite;
typedef LPD3DXFONT LPFont;
typedef LPDIRECT3DVERTEXSHADER9 LPVertexShader;
typedef LPDIRECT3DPIXELSHADER9 LPPixelShader;
typedef LPD3DXCONSTANTTABLE LPConstantTable;

typedef LPDIRECT3D9 LPDirectx;
typedef LPDIRECT3DDEVICE9 LPDevice;

typedef D3DXIMAGE_INFO ImageInfo;
#pragma endregion

#pragma region 一些宏定义

#define repeat(id, times) for(int id = 0; id < times; id++)

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
	std::mutex mutex##FuncName;\
	NEEDLOCK_GET_FUNC(mutex##FuncName, FuncName, varibleName, varibleType)\
    NEEDLOCK_SET_FUNC(mutex##FuncName, FuncName, varibleName, varibleType)\

#pragma endregion

//#pragma region 数据结构的运算符重载
//
//template<typename T>inline const std::vector<T>& operator<<(const std::vector<T>& vec, const T& element) {
//    vec.push_back(element);
//    return vec;
//}
//
//#pragma endregion

std::wstring stringToWstring(const std::string& orig);
std::string wstringToString(const std::wstring& str);

inline bool isAscii(char ch) {
    return ch >= 0 && ch <= 127;
}

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



//------Console-----
#define DEBUG_CONSOLE
#ifdef DEBUG_CONSOLE
#include <iostream>
extern HANDLE hConsole;
#define SetConsoleAtt(att) SetConsoleTextAttribute(hConsole, att)

#define FORE_RED FOREGROUND_RED
#define FORE_GREEN FOREGROUND_GREEN
#define FORE_BLUE FOREGROUND_BLUE
#define FORE_LIGHT FOREGROUND_INTENSITY

#define FORE_YELLOW (FORE_RED + FORE_GREEN)
#define FORE_CYAN (FORE_GREEN + FORE_BLUE)
#define FORE_PINK (FORE_RED + FORE_BLUE)
#define FORE_WHITE (FORE_RED + FORE_GREEN + FORE_BLUE)
//#define myd(...) std::cout << __VA_ARGS__
#endif
