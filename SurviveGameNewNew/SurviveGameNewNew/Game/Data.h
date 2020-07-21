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
	Image* testImage2;

	Image* btnVerySmall, * btnSmall, * btnMedium, * btnBig;
};

namespace My {
	extern Data gameData;
}