#pragma once

#include "../Widget/Widget.h"

#include "../utility.h"


namespace My {
	class Room;
}

class My::Room : public Object
{
public:
	~Room() override = default;

	virtual void onLogic();
	virtual void onRender();

	virtual void onDestroy();

	void evResized();

	void addWidget(Widget* widget);
	void removeWidget(Widget* widget);
	std::vector<Widget*> widgets;
};