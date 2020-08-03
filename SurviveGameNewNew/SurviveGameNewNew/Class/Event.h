#pragma once

#include "../NameSpace.h"

namespace My {
	class RenderEvent;

	class MouseEvent;
}


class My::RenderEvent {
public:
	int targetX = 0, targetY = 0;
};


class My::MouseEvent {
public:
	Mouse button = Mouse::None;
	int mouseX = -1, mouseY = -1;
};



/*
namespace My {
	class Event;

	class EventResize;
}


class My::Event {
public:
	enum class Type { Resize };

	Event(Type type, bool isSingle = false)
		: type(type), isSingle(isSingle) {}

	Type type;
	bool isSingle;
};


class My::EventResize : public Event
{
public:
	EventResize(int w, int h)
		: Event(Type::Resize, true), w(w), h(h) {}

	int w, h;
};
*/