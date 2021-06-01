#include "ComputerGegner.h"
#include "Feld.h"
#include "Figure.h"
#include "Spielfeld.h"
#include "Player.h"

void ComputerGegner::MakeMove() {
	std::scoped_lock(move_mutex_);
	finished_.store(false);

	std::srand(SDL_GetTicks());

	std::vector<std::vector<Feld*>>* feld = feld_->Felder();
	Player *black = feld_->CurrentPlayer(), *white = feld_->CurrentEnemy();
	
	std::vector<MoveData> moveset;
	for (auto& x : black->figures) {
		for (auto& y : x->MakeMoveset()) {
			if (x->FakeMove(y)) moveset.push_back(MoveData(x->current_feld_, y));
		}
	}
	if (moveset.size() == 0) {
		latest_move_.Reset();
		finished_.store(true);
		return;
	}
	int fin_indx = std::rand() % moveset.size();

	latest_move_ = moveset.at(fin_indx);
	finished_.store(true);
	return;
}