#include "Data.h"

My::Data My::gameData = Data();

using namespace My;

void Data::onInit() {
	testImage1 = new Image(_T("data/texture/test1.png"));
	testImage2 = new Image(_T("data/texture/test3.png"));

	btnVerySmall = new Image(_T("data/texture/gui/button/btnVerySmall.png"));
	btnSmall = new Image(_T("data/texture/gui/button/btnSmall.png"));
	btnMedium = new Image(_T("data/texture/gui/button/btnMedium.png"));
	btnBig = new Image(_T("data/texture/gui/button/btnBig.png"));

	saveSelect = new Image(_T("data/texture/gui/menu/SaveSelect.png"));
	saveCreate = new Image(_T("data/texture/gui/menu/SaveCreate.png"));
}

void Data::onDestroy() {
	safeDelete(testImage1);
	safeDelete(testImage2);

	safeDelete(btnVerySmall);
	safeDelete(btnSmall);
	safeDelete(btnMedium);
	safeDelete(btnBig);

	safeDelete(saveSelect);
	safeDelete(saveCreate);
}