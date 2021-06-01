#ifndef __CHESS_FELD_H__
#define __CHESS_FELD_H__

#include <Forever.h>

class Figure;

struct Feld : public fr::Rect {
	Figure* fig_;
	bool mark_;
	fr::Vector2i real_pos_;

	Feld(const fr::Vector2i& pos, const fr::Vector2i& size)
		: fr::Rect(pos, size), fig_{ nullptr }, mark_{ false } {}

	inline bool HasFigure() {
		return fig_ != nullptr;
	}
	inline bool InFocus(const fr::Vector2i& mouse) {
		if (
			(mouse.x > x && mouse.x < (x + w)) &&
			(mouse.y > y && mouse.y < (y + h))
			) return true;
		return false;
	}
};

#endif // !__CHESS_FELD_H__



