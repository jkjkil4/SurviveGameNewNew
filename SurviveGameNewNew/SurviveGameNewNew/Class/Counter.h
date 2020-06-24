#pragma once

#include "../utility.h"

namespace My {
    class Counter;
}

class My::Counter {
public:
    void start() {
        LARGE_INTEGER li;
        
        if (!QueryPerformanceFrequency(&li)) {
            #ifdef DEBUG_CONSOLE
            SetConsoleAtt(FORE_RED + FORE_LIGHT);
            std::cout << "QueryPerformanceFrequency failed!\n";
            SetConsoleAtt(FORE_WHITE);
            #endif

            throw "QueryPerformanceFrequency failed!";
        }

        PCFreq = double(li.QuadPart) / 1000.0;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
    }
    double getTime() {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return double(li.QuadPart - CounterStart) / PCFreq;
    }

private:
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
};
