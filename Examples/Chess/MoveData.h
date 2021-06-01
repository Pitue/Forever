#ifndef __CHESS_MOVEDATA_H__
#define __CHESS_MOVEDATA_H__

#include <Forever.h>

struct Feld;

struct MoveData {
	Feld *which, *dest;
	MoveData() : which{ nullptr }, dest{ nullptr } {}
	MoveData(Feld* _which, Feld* _dest) : which{ _which }, dest{ _dest } {}
	inline void Reset() {
		which = dest = nullptr;
	}
	inline bool operator == (const MoveData& other) const {
		if (which == other.which && dest == other.dest) return true;
		return false;
	}
	void operator() ();
};

#endif // !__CHESS_MOVEDATA_H__
