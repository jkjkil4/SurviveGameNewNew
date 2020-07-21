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

	//°´Å¥
	Image* btnVerySmall, * btnSmall, * btnMedium, * btnBig;

	//GUI
	Image* saveSelect, * saveCreate;
};

namespace My {
	extern Data gameData;
}