#include "Figure.h"
#include "Game.h"
#include "Spielfeld.h"

#define GET_FELD(pos) spielfeld_->Felder()->at(pos.x).at(pos.y)

void SwitchStruct::operator()(Figure* king) {
	king->current_feld_->fig_ = nullptr;
	switch_partner_->current_feld_->fig_ = nullptr;

	king->current_feld_ = my_position_;
	switch_partner_->current_feld_ = partner_position_;

	king->Sprite().Position(my_position_->Position());
	switch_partner_->Sprite().Position(partner_position_->Position());

	king->moved_ = switch_partner_->moved_ = true;
}

bool Figure::InRange(const fr::Vector2i& pos) {
	if (pos.x >= 0 && pos.x < GameScene::feld_size_ && pos.y >= 0 && pos.y < GameScene::feld_size_) return true;
	return false;
}

void Figure::Pawn(std::vector<Feld*>& vec) {
	int offset_mov[] = { 1, 2 },
			offset_att[] = { -1, 1 };
	if (white_) {
		for (int i = 0; i < 2; i++) {
			if (i == 1 && moved_) continue;
			fr::Vector2i pos = current_feld_->real_pos_ - fr::Vector2i(0, offset_mov[i]);		
			if (InRange(pos)) {
				if (!GET_FELD(pos)->HasFigure()) vec.push_back(GET_FELD(pos));
				else break;
			}
		}

		for (int i = 0; i < 2; i++) {
			fr::Vector2i pos = current_feld_->real_pos_ - fr::Vector2i(offset_att[i], 1);
			if (InRange(pos) && GET_FELD(pos)->fig_ && GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			if (i == 1 && moved_) continue;
			fr::Vector2i pos = current_feld_->real_pos_ + fr::Vector2i(0, offset_mov[i]);
			if (InRange(pos)) {
				if (!GET_FELD(pos)->fig_) vec.push_back(GET_FELD(pos));
				else break;
			}
		}

		for (int i = 0; i < 2; i++) {
			fr::Vector2i pos = current_feld_->real_pos_ + fr::Vector2i(offset_att[i], 1);
			if (InRange(pos) && GET_FELD(pos)->fig_ && GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
		}
	}
}
void Figure::Rook(std::vector<Feld*>& vec) {
	fr::Vector2i pos = current_feld_->real_pos_;
	for (int y = pos.y - 1; y >= 0; y--) {
		pos.y = y;
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
	}

	pos = current_feld_->real_pos_;
	for (int y = pos.y + 1; y < GameScene::feld_size_; y++) {
		pos.y = y;
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
	}

	pos = current_feld_->real_pos_;
	for (int x = pos.x - 1; x >= 0; x--) {
		pos.x = x;
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
	}

	pos = current_feld_->real_pos_;
	for (int x = pos.x + 1; x < GameScene::feld_size_; x++) {
		pos.x = x;
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
	}
}
void Figure::Bishop(std::vector<Feld*>& vec) {
	fr::Vector2i pos = current_feld_->real_pos_;
	while (true) {
		pos += fr::Vector2i(-1, -1);
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
		else {
			break;
		}
	}

	pos = current_feld_->real_pos_;
	while (true) {
		pos += fr::Vector2i(1, 1);
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
		else {
			break;
		}
	}

	pos = current_feld_->real_pos_;
	while (true) {
		pos += fr::Vector2i(-1, 1);
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
		else {
			break;
		}
	}

	pos = current_feld_->real_pos_;
	while (true) {
		pos += fr::Vector2i(1, -1);
		if (InRange(pos)) {
			if (!GET_FELD(pos)->fig_) {
				vec.push_back(GET_FELD(pos));
			}
			else {
				if (GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
				break;
			}
		}
		else {
			break;
		}
	}
}
void Figure::Knight(std::vector<Feld*>& vec) {
	fr::Vector2i pos = current_feld_->real_pos_;

	int offsets_x[] = { 2, 1, -1, -2, -2, -1, 1, 2 },
			offsets_y[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	for (int i = 0; i < 8; i++) {
		pos = current_feld_->real_pos_;
		pos.x += offsets_x[i];
		pos.y += offsets_y[i];
		if (InRange(pos)) {
			if (!GET_FELD(pos)->HasFigure() || GET_FELD(pos)->fig_->white_ != white_) vec.push_back(GET_FELD(pos));
		}
	}
}
void Figure::King(std::vector<Feld*>& vec) {
	fr::Vector2i pos = current_feld_->real_pos_;
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (x == 0 && y == 0) continue;
			pos = current_feld_->real_pos_ + fr::Vector2i(x, y);
			if (InRange(pos)) {
				if (!GET_FELD(pos)->fig_ || GET_FELD(pos)->fig_->white_ != white_) {
					vec.push_back(GET_FELD(pos));
				}
			}
		}
	}

	/*switching*/
	pos = current_feld_->real_pos_;
	if (!moved_) {
		Figure* fig = nullptr;
		if ((fig = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(3)).at(pos.y)->fig_) != nullptr) {
			if (!spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(2)).at(pos.y)->HasFigure() 
				&& !spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(1)).at(pos.y)->HasFigure()) {
				if (fig->Type() == FIGURE::ROOK && !fig->moved_) {
					vec.push_back(spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(2)).at(pos.y));

					switch_.my_position_ = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(2)).at(pos.y);
					switch_.partner_position_ = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) + static_cast<size_t>(1)).at(pos.y);
					switch_.switch_partner_ = fig;
				}
			}
		}
		if ((fig = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(3)).at(pos.y)->fig_) != nullptr) {
			if (!spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(2)).at(pos.y)->HasFigure()
				&& !spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(1)).at(pos.y)->HasFigure()) {
				if (fig->Type() == FIGURE::ROOK && !fig->moved_) {
					vec.push_back(spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(2)).at(pos.y));

					switch_.my_position_ = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(2)).at(pos.y);
					switch_.partner_position_ = spielfeld_->Felder()->at(static_cast<size_t>(pos.x) - static_cast<size_t>(1)).at(pos.y);
					switch_.switch_partner_ = fig;
				}
			}
		}
	}
}
void Figure::Queen(std::vector<Feld*>& vec) {
	Rook(vec);
	Bishop(vec);
}

std::vector<Feld* > Figure::MakeMoveset() {
	std::vector<Feld*> r;
	r.reserve(64);

	if (!alive_) return r;

	switch (type_) {
	case FIGURE::PAWN:
		Pawn(r);
		break;
	case FIGURE::ROOK:
		Rook(r);
		break;
	case FIGURE::BISHOP:
		Bishop(r);
		break;
	case FIGURE::KNIGHT:
		Knight(r);
		break;
	case FIGURE::KING:
		King(r);
		break;
	case FIGURE::QUEEN:
		Queen(r);
		break;
	default:
		break;
	}

	return r;
}
void Figure::Move(Feld* to) {
	Figure* t = to->fig_;

	if (Type() == FIGURE::KING && !moved_) {
		if (switch_.IsSwitching(to)) {
			switch_(this);
			switch_.Reset();
		}
	}

	current_feld_->fig_ = nullptr;
	to->fig_ = this;

	current_feld_ = to;
	Sprite().Position(to->Position());
	moved_ = true;

	if (Type() == FIGURE::PAWN) {
		if (
			(white_ && current_feld_->real_pos_.y == 0) ||
			(!white_ && current_feld_->real_pos_.y == 7)
			) spielfeld_->ChangePawn(this);
	}

	if (t) {
		t->alive_ = false;
		t->Sprite().Hide();
		if (t->Type() == FIGURE::KING) Scene()->game_over_ = (t->white_ ? 2 : 1);
	}

}
bool Figure::FakeMove(Feld* to) {
	if (!alive_) return false;

	bool moved = moved_, allowed = true;
	Feld* orig = current_feld_;
	Figure* geg = to->fig_;

	/*do move*/
	current_feld_->fig_ = nullptr;
	to->fig_ = this;
	current_feld_ = to;
	moved_ = true;

	if (geg) geg->alive_ = false;

	/*Check*/
	if (spielfeld_->CurrentPlayer()->IsInCheck(*spielfeld_->CurrentEnemy())) allowed = false;

	if (geg) geg->alive_ = true;

	/*undo move*/
	orig->fig_ = this;
	to->fig_ = geg;
	current_feld_ = orig;
	moved_ = moved;

	return allowed;
}

void Figure::Tick(const fr::Time& time) {
	
}