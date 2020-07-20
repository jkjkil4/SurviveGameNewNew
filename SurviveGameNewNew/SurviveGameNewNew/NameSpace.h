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
	//��include����(��ֹѭ������)
	class Room;

	class Object
	{
	public:
		virtual ~Object() = default;
	};

	class RoomGoto {	//������תRoom�õ�����
	public:
		RoomGoto(Room* room)
			: room(room) {}
		Room* room;
	};

	enum class RenderError { NoError, ErrorCannotPresent };	//Renderʱ�����Ĵ���

	enum class Align { None = 0, Left = 0b1, Right = 0b10, Top = 0b100, Bottom = 0b1000 };	//���뷽ʽ
	EnumClassOperator(Align)

	enum class Mouse { None = 0, Left = 0b1, Middle = 0b10, Right = 0b100 };
	EnumClassOperator(Mouse)
}

#undef EnumClassOperator