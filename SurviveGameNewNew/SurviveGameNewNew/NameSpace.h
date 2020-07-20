#pragma once

#define SC static constexpr

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
	inline bool operator&(Align all, Align part) {	//���ڶ��뷽ʽ����������
		return (int)all & (int)part;
	}
	inline Align operator|(Align part1, Align part2) {	//���ڶ��뷽ʽ����������
		return (Align)((int)part1 | (int)part2);
	}
}