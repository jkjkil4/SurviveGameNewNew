#include "Engine.h"

using namespace My;

void Engine::setCountCapture() {
	if (captureCount == 0)
		SetCapture(g_hWnd);
	captureCount++;
}

void Engine::releaseCountCapture() {
	captureCount--;
	if (captureCount == 0)
		ReleaseCapture();
}

bool Engine::isKeyPressed(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKeyPressed.lock();
		bool tmp = keyPressed[index];
		mutexKeyPressed.unlock();
		return tmp;
	}
	return false;
}

bool Engine::isKey(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKey.lock();
		bool tmp = key[index];
		mutexKey.unlock();
		return tmp;
	}
	return false;
}

bool Engine::isKeyReleased(int num) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKeyReleased.lock();
		bool tmp = keyReleased[index];
		mutexKeyReleased.unlock();
		return tmp;
	}
	return false;
}


void Engine::setKeyPressed(int num, bool on) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKeyPressed.lock();
		keyPressed[index] = on;
		mutexKeyPressed.unlock();
	}
}

void Engine::setKey(int num, bool on) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKey.lock();
		key[index] = on;
		mutexKey.unlock();
	}
}

void Engine::setKeyReleased(int num, bool on) {
	int index = num - 1;
	if (index >= 0 && index < keyNumber) {
		mutexKeyReleased.lock();
		keyReleased[index] = on;
		mutexKeyReleased.unlock();
	}
}

void Engine::clearKeys() {
	ZeroMemory(keyPressed, sizeof(keyPressed));
	ZeroMemory(key, sizeof(key));
	ZeroMemory(keyReleased, sizeof(keyReleased));
}