#pragma once

#define SC static constexpr

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
	inline bool operator&(Align all, Align part) {	//对于对齐方式的运算重载
		return (int)all & (int)part;
	}
	inline Align operator|(Align part1, Align part2) {	//对于对齐方式的运算重载
		return (Align)((int)part1 | (int)part2);
	}
}