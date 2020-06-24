#pragma once

#include <thread>

#include "Counter.h"

namespace My {
	class Delayer;
}

class My::Delayer {
public:
	explicit Delayer(int standardMicro)
		: standardMicro(standardMicro)
    {
        counter.start();
    }

	void delay(int micro, bool skipBelowOffset = false) {
        needDelayMicro += micro;
        if (needDelayMicro > 0) {
            double startTime = counter.getTime();   //�õ���ʱ��ʼ��ʱ��(ms)
            std::this_thread::sleep_for(std::chrono::microseconds(needDelayMicro)); //��ʱ
            int delayedMicro = (int)((counter.getTime() - startTime) * 1000);   //�õ���ʱ���ĵ�΢����
            int outMicro = delayedMicro - needDelayMicro;   //�õ�������΢����
            needDelayMicro = -outMicro; //�� needDelayMicro ����Ϊ -outMicro��Ҳ��������һ����ʱ��ʱ��Ϳ�ȥ������¼�
        }
        else {
            if (skipBelowOffset && needDelayMicro < -standardMicro * 4)
                needDelayMicro = 1;
        }
	}

private:
    Counter counter;
    int standardMicro = 0;
    int needDelayMicro = 0;
};