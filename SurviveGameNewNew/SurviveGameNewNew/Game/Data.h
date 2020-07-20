#pragma once

#include "../Class/Image.h"

namespace My {
	class Data;
}

class My::Data {
public:
	void onInit();
	void onDestroy();
	Image* testImage1;
};

namespace My {
	extern Data gameData;
}