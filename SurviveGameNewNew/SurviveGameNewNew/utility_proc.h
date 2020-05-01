#ifndef _UTILITY_PROC_H
#define _UTILITY_PROC_H

//-------SAFE_DELETE_----------
template<typename T>inline void safeDelete(T*& p) {
    if (p) { delete p; p = nullptr; }
}
template<typename T>inline void safeDeleteArray(T*& p) {
    if (p) { delete[] p; p = nullptr; }
}
template<typename T>inline void safeRelease(T*& p) {
    if (p) { p->Release(); p = nullptr; }
}

//------º∆À„-------
template<typename T>inline T myMax(T a, T b) {
    return a > b ? a : b;
}
template<typename T>inline T myMin(T a, T b) {
    return a > b ? b : a;
}
template<typename T>inline T myBound(T min, T value, T max) {
    return myMin(myMax(value, min), max);
}


#endif