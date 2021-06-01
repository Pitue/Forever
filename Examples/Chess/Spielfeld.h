#ifndef __CHESS_SPIELFELD_H__
#define __CHESS_SPIELFELD_H__

#include <vector>
#include <thread>
#include <mutex>
#include <Forever.h>

#include "Feld.h"
#include "Figure.h"
#include "MoveData.h"
#include "ComputerGegner.h"

class GameScene;
class Player;
struct Feld;



class Spielfeld {
	GameScene* scene_;
	fr::Engine* engine_;

	fr::Sprite board_, marking_;
	fr::Text text_framerate_, status_;

	MoveData move_;
	std::vector<MoveData> possible_moves_;

	ComputerGegner gegner_;
	std::thread* computer_calc_thr_;

	std::vector<std::vector<Feld*>> felder_;
	Player* player_[2];
	fr::uint8 turn_;

	std::mutex player_mtx_, feld_mtx_;

	inline void SetStatus(const std::string& str) {
		status_.String(str);
		status_.Render();
		status_.Sprite().Position(fr::Vector2i(engine_->Window().Size().x / 2 - status_.Sprite().Size().x / 2, engine_->Window().Size().y - status_.Sprite().Size().y));
	}
	inline void CleanStatus() {
		if (turn_ == 0) SetStatus("White is playing...");
		else SetStatus("Black is playing...");
	}
	inline void SetStatusInfo(const Figure* fig) {
		static std::string names[] = { "Pawn", "Rook", "Bishop", "Knight", "King", "Queen" };
		std::string status;
		if (fig->white_) status += "White ";
		else status += "Black ";
		status += names[static_cast<int>(fig->Type())] + " at [" + std::to_string(fig->current_feld_->real_pos_.x) + '|' + std::to_string(fig->current_feld_->real_pos_.y) + ']';
		SetStatus(status);
	}
	void CleanMarks();
	inline void Clean() {
		CleanMarks();
		move_.Reset();
	}

	void GetPossibleMoves();
	void ChangeTurn();
	void SpawnFigures();
	Feld* FeldInFocus(const fr::Vector2i& mouse);
public:
	bool computer_;

	Spielfeld(GameScene* scene);
	~Spielfeld();


	inline std::vector<std::vector<Feld*>>* Felder() {
		std::scoped_lock(feld_mtx_);
		return &felder_;
	}
	inline Player* CurrentPlayer() {
		std::scoped_lock(player_mtx_);
		return player_[turn_];
	}
	inline Player* CurrentEnemy() {
		std::scoped_lock(player_mtx_);
		return player_[turn_ == 0 ? 1 : 0];
	}
	
	void ChangePawn(Figure* which);
	void EventHandle(const fr::Event& evt);
	void Tick(const fr::Time& time);

	void Reset();
	void Draw();
};



#endif // !__CHESS_SPIELFELD_H__
