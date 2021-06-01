#ifndef __CHESS_COMPUTERGEGNER_H__
#define __CHESS_COMPUTERGEGNER_H__

#include <Forever.h>

#include <vector>
#include <mutex>
#include <atomic>

#include "MoveData.h"

class Spielfeld;
struct Feld;

class ComputerGegner {
	Spielfeld* feld_;
	MoveData latest_move_;
	std::atomic_bool finished_;
	std::mutex move_mutex_;

public:
	ComputerGegner(Spielfeld* spielfeld) : feld_{ spielfeld }, finished_(true) {

	}

	inline bool Finished() {
		return finished_.load();
	}
	inline MoveData get_results() {
		std::scoped_lock(move_mutex_);
		return latest_move_;
	}

	void MakeMove();
};

#endif // !__CHESS_COMPUTERGEGNER_H__




