#pragma once

#include <thread>

#include "Counter.h"

namespace My {
	class Delayer;
}

class My::Delayer {
public:
	explicit Delayer(int needDelayMicro)
		: needDelayMicro(needDelayMicro) 
    {
        counter.start();
    }

	void delay(int micro) {
        if (needDelayMicro > 0) {
            double startTime = counter.get();
            std::this_thread::sleep_for(std::chrono::microseconds(needDelayMicro));
            int delayedMicro = (int)((counter.get() - startTime) * 1000);
            int outMicro = delayedMicro - needDelayMicro;
            needDelayMicro = micro - outMicro;
        }
        else {
            needDelayMicro += micro;
        }
	}

private:
    Counter counter;
	int needDelayMicro = 0;
};