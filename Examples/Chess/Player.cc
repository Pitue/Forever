#include "Player.h"
#include "Feld.h"

bool Player::IsInCheck(Player& other) {
	for (auto& x : other.figures) {
		for (auto& y : x->MakeMoveset()) {
			if (y->HasFigure() && y->fig_->Type() == FIGURE::KING) {
				return true;
			}
		}
	}
	return false;
}
bool Player::IsInCheckmate(Player& other) {
	if (!IsInCheck(other)) return false;

	for (auto& x : figures) {
		for (auto& y : x->MakeMoveset()) {
			if (x->FakeMove(y)) return false;
		}
	}

	return true;
}