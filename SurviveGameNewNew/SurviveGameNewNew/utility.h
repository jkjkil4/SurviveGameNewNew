#ifndef _UTILITY_H
#define _UTILITY_H

#include "utility_d3d9.h"
#include "utility_proc.h"

#include <string>

#include <thread>

#include <cmath>
#define PI acos(-1)

#include <mutex>
#define Mutex(m) std::lock_guard<std::mutex> guard(m)


void mySetScale(LPD3DXSPRITE pSpr, float scalePosX, float scalePosY, float xScale, float yScale, 
    float rotPosX = 0, float rotPosY = 0, float rot = 0);

//------类型转换-------
std::wstring stringToWstring(std::string orig);
std::string wstringToString(const std::wstring str);

//------文件操作-------
#include <vector>
#include <fstream>
//string file = path + "\\*" + (exd == "" ? "" : "." + exd);

//------别的东西-------
void wstring_trimmed(std::wstring& wstr);


//------Console-----
#define DEBUG_CONSOLE
#ifdef DEBUG_CONSOLE
#include <iostream>
#define myd(...) std::cout << __VA_ARGS__
#else
#define myd(...)
#endif


#endif