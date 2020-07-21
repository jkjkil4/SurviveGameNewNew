#include "Data.h"

My::Data My::gameData = Data();

using namespace My;

void Data::onInit() {
	testImage1 = new Image(_T("data/texture/test1.png"));
	testImage2 = new Image(_T("data/texture/test3.png"));
}

void Data::onDestroy() {
	safeDelete(testImage1);
	safeDelete(testImage2);
}