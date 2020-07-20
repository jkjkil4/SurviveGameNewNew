#pragma once

#define SC static constexpr

#define EnumClassOperator(EnumClass)\
	inline bool operator&(EnumClass all, EnumClass part) {\
		return (int)all & (int)part;\
	}\
	inline EnumClass operator|(EnumClass part1, EnumClass part2) {\
		return (EnumClass)((int)part1 | (int)part2);\
	}

namespace My {
	//不include的类(防止循环包含)
	class Room;

	class Object
	{
	public:
		virtual ~Object() = default;
	};

	class RoomGoto {	//用于跳转Room用到的类
	public:
		RoomGoto(Room* room)
			: room(room) {}
		Room* room;
	};

	enum class RenderError { NoError, ErrorCannotPresent };	//Render时遇到的错误

	enum class Align { None = 0, Left = 0b1, Right = 0b10, Top = 0b100, Bottom = 0b1000 };	//对齐方式
	EnumClassOperator(Align)

	enum class Mouse { None = 0, Left = 0b1, Middle = 0b10, Right = 0b100 };
	EnumClassOperator(Mouse)
}

#undef EnumClassOperator