#include "Engine.h"

using namespace My;
using namespace std;

#define THREAD_COUNT(oper) mutexThreadCount.lock(); threadCount##oper; mutexThreadCount.unlock();
#define DELAY_MICRO 16667

void Engine::funcLogic() {	//逻辑处理线程 的 函数
	THREAD_COUNT(++);

	timeBeginPeriod(1);
	Counter counter;
	counter.start();
	Delayer delayer(DELAY_MICRO);
	int fpsCount = 0;
	double fpsStartTime = counter.getTime();

	while (!getNeedExit()) {
		double startTime = counter.getTime();
		mutexLogicRender.lock();

		onLogic();

		mutexLogicRender.unlock();
		int spentMicro = (int)((counter.getTime() - startTime) * 1000);
		delayer.delay(DELAY_MICRO - spentMicro);

		fpsCount++;
		double time = counter.getTime();
		if (time - fpsStartTime > 1000) {
			setLogicFps(fpsCount);

			//#ifdef DEBUG_CONSOLE
			//mutexConsoleOutput.lock();
			//SetConsoleAtt(FORE_YELLOW);
			//cout << "Logic\t FPS: " << fpsCount << endl;
			//SetConsoleAtt(FORE_WHITE);
			//mutexConsoleOutput.unlock();
			//#endif

			fpsCount = 0;
			fpsStartTime = time;
		}
	}
	Sleep(1);
	timeEndPeriod(1);

	THREAD_COUNT(--);
}

void Engine::funcRender() {	//渲染线程 的 函数
	THREAD_COUNT(++);

	initDirectx();
	setDirectxInited(true);

	timeBeginPeriod(1);
	Counter counter;
	counter.start();
	Delayer delayer(DELAY_MICRO);
	int fpsCount = 0;
	double fpsStartTime = counter.getTime();

	while (!getNeedExit()) {
		double startTime = counter.getTime();
		RenderError err = RenderError::NoError;
		if (!IsIconic(g_hWnd)) {
			onRenderStart();
			mutexLogicRender.lock();

			onRender();

			mutexLogicRender.unlock();
			onRenderEnd(err);

			if (err == RenderError::ErrorCannotPresent) {
				resetDevice();
			}
		}
		int spentMicro = (err == RenderError::NoError) ? (int)((counter.getTime() - startTime) * 1000) : 0;
		delayer.delay(DELAY_MICRO - spentMicro, true);

		fpsCount++;
		double time = counter.getTime();
		if (time - fpsStartTime > 1000) {
			setRenderFps(fpsCount);

			//#ifdef DEBUG_CONSOLE
			//mutexConsoleOutput.lock();
			//SetConsoleAtt(FORE_PINK);
			//cout << "Render\t FPS: " << fpsCount << endl;
			//SetConsoleAtt(FORE_WHITE);
			//mutexConsoleOutput.unlock();
			//#endif

			fpsCount = 0;
			fpsStartTime = time;
		}
	}
	Sleep(1);
	timeEndPeriod(1);

	THREAD_COUNT(--);
}
