#pragma once

#include "../utility.h"

namespace My {
    class Counter;
}

class My::Counter {
public:
    void start() {
        LARGE_INTEGER li;
        if (!QueryPerformanceFrequency(&li))
            /*cout << "QueryPerformanceFrequency failed!\n"*/OutputDebugString(_T("QueryPerformanceFrequency failed!\n"));

        PCFreq = double(li.QuadPart) / 1000.0;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
    }
    double get() {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        double result = double(li.QuadPart - CounterStart) / PCFreq;
        if (result > 100000)
            start();
        return result;
    }

private:
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
};
