#pragma once

#define SC static constexpr

namespace My {
	enum class RenderError { NoError, ErrorCannotPresent };

	enum class Align { None = 0, Left = 0b1, Right = 0b10, Top = 0b100, Bottom = 0b1000 };
	inline bool operator&(Align all, Align part) {
		return (int)all & (int)part;
	}
	inline Align operator|(Align part1, Align part2) {
		return (Align)((int)part1 | (int)part2);
	}
}