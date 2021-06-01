#ifndef __CHES_FIGURE_H__
#define __CHES_FIGURE_H__

#include <Forever.h>
#include "enum.h"

class GameScene;
class Spielfeld;
struct Feld;
class Figure;

struct SwitchStruct {
	Figure* switch_partner_;
	Feld* my_position_, *partner_position_;

	SwitchStruct()
		: switch_partner_{ nullptr },
		my_position_{ nullptr },
		partner_position_{ nullptr } {}
	inline void Reset() {
		switch_partner_ = nullptr;
		my_position_ = partner_position_ = nullptr;
	}
	inline bool IsSwitching(Feld* dest) {
		if (switch_partner_ != nullptr && my_position_ != nullptr 
				&& partner_position_ != nullptr && my_position_ == dest) return true;
		return false;
 	}
	void operator()(Figure* king);
};

class Figure : public fr::Actor<GameScene> {
	FIGURE type_;

	bool InRange(const fr::Vector2i& pos);

	void Pawn(std::vector<Feld*>& vec);
	void Rook(std::vector<Feld* >& vec);
	void Bishop(std::vector<Feld*>& vec);
	void Knight(std::vector<Feld*>& vec);
	void King(std::vector<Feld*>& vec);
	void Queen(std::vector<Feld*>& vec);

	SwitchStruct switch_;
public:
	/*for pawns*/
	bool moved_;
	bool white_;
	bool alive_;

	Feld* current_feld_;
	Spielfeld* spielfeld_;

	Figure(fr::Engine* engine, GameScene* scene, Spielfeld* spielfeld, fr::Texture texture, FIGURE type)
		: fr::Actor<GameScene>(engine, scene, engine->Window().renderer_),
		type_{ type },
		white_{ false },
		moved_{ false },
		current_feld_{ nullptr },
		alive_{ true },
		spielfeld_{ spielfeld } {

		Sprite().Texture(texture);
	}

	std::vector<Feld*> MakeMoveset();
	void Move(Feld* to);
	bool FakeMove(Feld* to);

	inline FIGURE Type() const {
		return type_;
	}
	inline void Type(FIGURE type) {
		type_ = type;
	}
	inline void Hide() {
		Sprite().Hide();
	}

	void Tick(const fr::Time& time) override;
	inline void Draw() override {
		this->Sprite().Draw();
	}
};

#endif // !__CHES_FIGURE_H__
