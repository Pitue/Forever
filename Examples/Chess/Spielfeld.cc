#include "Spielfeld.h"

#include "Game.h"
#include "Feld.h"
#include "Figure.h"
#include "Player.h"

void Spielfeld::CleanMarks() {
	for (auto& x : *Felder()) {
		for (auto& y : x) {
			y->mark_ = false;
		}
	}
}
void Spielfeld::ChangePawn(Figure* which) {
	if (which->Type() != FIGURE::PAWN) return;
	const SDL_MessageBoxButtonData buttons[] = {
	{0, 0, "Queen"},
	{0, 1, "Rook"},
	{0, 2, "Bishop"},
	{0, 3, "Knight"}
	};

	const SDL_MessageBoxColorScheme colorScheme = {
		{
			{ 255,   0,   0 },
			{   0, 255,   0 },
			{ 255, 255,   0 },
			{   0,   0, 255 },
			{ 255,   0, 255 }
		}
	};


	SDL_MessageBoxData data;
	data.buttons = buttons;
	data.numbuttons = SDL_arraysize(buttons);
	data.colorScheme = &colorScheme;

	data.flags = SDL_MessageBoxFlags::SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT;
	data.title = "Change your pawn!";
	data.message = "Change to:";
	data.window = engine_->Window().window_;



	int buttonid = 0;
	SDL_ShowMessageBox(&data, &buttonid);

	if (buttonid == 0) {
		which->Type(FIGURE::QUEEN);

		if (which->white_) which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_WHITE_QUEEN));
		else which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_BLACK_QUEEN));
	}
	else if (buttonid == 1) {
		which->Type(FIGURE::ROOK);

		if (which->white_) which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_WHITE_ROOK));
		else which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_BLACK_ROOK));
	}
	else if (buttonid == 2) {
		which->Type(FIGURE::BISHOP);

		if (which->white_) which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_WHITE_BISHOP));
		else which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_BLACK_BISHOP));
	}
	else if (buttonid == 3) {
		which->Type(FIGURE::KNIGHT);

		if (which->white_) which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_WHITE_KNIGHT));
		else which->Sprite().Texture(engine_->get_texture(TEXTURES::GAME_BLACK_KNIGHT));
	}
}
void Spielfeld::GetPossibleMoves() {
	possible_moves_.resize(0);
	for (auto& x : player_[turn_]->figures) {
		for (auto& y : x->MakeMoveset()) {
			if (x->FakeMove(y)) possible_moves_.push_back(MoveData(x->current_feld_, y));
		}
	}
}
void Spielfeld::ChangeTurn() {
	Clean();
	if (!turn_) turn_ = 1;
	else turn_ = 0;

	GetPossibleMoves();
	CleanStatus();

	if (player_[turn_]->IsInCheckmate(*player_[(turn_ == 0 ? 1 : 0)])) {
		scene_->game_over_ = (turn_ == 0 ? 2 : 1);
	}
	else if (!player_[turn_]->IsInCheck(*player_[(turn_ == 0 ? 1 : 0)])) {
		if (possible_moves_.size() == 0) {
			scene_->game_over_ = 3;
		}
	}
	else if (player_[turn_]->IsInCheck(*player_[(turn_ == 0 ? 1 : 0)])) {
		if (turn_ == 0) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!", "Black got white in check!", engine_->Window().window_);
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!", "White got black in check!", engine_->Window().window_);
		}
	}
}
void Spielfeld::SpawnFigures() {
	for (int x = 0; x < static_cast<int>(felder_.at(1).size()); x++) {
		Figure* fig = new Figure(engine_, scene_, this, engine_->get_texture(TEXTURES::GAME_BLACK_PAWN), FIGURE::PAWN);
		fig->Sprite().Position(felder_.at(x).at(1)->Position());
		fig->current_feld_ = felder_.at(x).at(1);
		player_[1]->figures.push_back(fig);
		felder_.at(x).at(1)->fig_ = fig;
	}
	for (int x = 0; x < static_cast<int>(felder_.at(6).size()); x++) {
		Figure* fig = new Figure(engine_, scene_, this, engine_->get_texture(TEXTURES::GAME_WHITE_PAWN), FIGURE::PAWN);
		fig->Sprite().Position(felder_.at(x).at(6)->Position());
		fig->current_feld_ = felder_.at(x).at(6);
		fig->white_ = true;

		player_[0]->figures.push_back(fig);
		felder_.at(x).at(6)->fig_ = fig;
	}

	FIGURE type;
	fr::Texture text;
	for (int x = 0; x < static_cast<int>(felder_.at(0).size()); x++) {
		switch (x) {
		case 0:
			__fallthrough;
		case 7:
			type = FIGURE::ROOK;
			text = engine_->get_texture(TEXTURES::GAME_BLACK_ROOK);
			break;
		case 1:
			__fallthrough;
		case 6:
			type = FIGURE::KNIGHT;
			text = engine_->get_texture(TEXTURES::GAME_BLACK_KNIGHT);
			break;
		case 2:
			__fallthrough;
		case 5:
			type = FIGURE::BISHOP;
			text = engine_->get_texture(TEXTURES::GAME_BLACK_BISHOP);
			break;
		case 3:
			type = FIGURE::QUEEN;
			text = engine_->get_texture(TEXTURES::GAME_BLACK_QUEEN);
			break;
		case 4:
			type = FIGURE::KING;
			text = engine_->get_texture(TEXTURES::GAME_BLACK_KING);
			break;
		default:
			throw std::runtime_error("Something happened [0]!");
			break;
		}
		Figure* fig = new Figure(engine_, scene_, this, text, type);

		fig->Sprite().Position(felder_.at(x).at(0)->Position());
		fig->current_feld_ = felder_.at(x).at(0);

		player_[1]->figures.push_back(fig);
		if (fig->Type() == FIGURE::KING) player_[1]->king_ = fig;
		felder_.at(x).at(0)->fig_ = fig;
	}

	for (int x = 0; x < static_cast<int>(felder_.at(7).size()); x++) {
		switch (x) {
		case 0:
			__fallthrough;
		case 7:
			type = FIGURE::ROOK;
			text = engine_->get_texture(TEXTURES::GAME_WHITE_ROOK);
			break;
		case 1:
			__fallthrough;
		case 6:
			type = FIGURE::KNIGHT;
			text = engine_->get_texture(TEXTURES::GAME_WHITE_KNIGHT);
			break;
		case 2:
			__fallthrough;
		case 5:
			type = FIGURE::BISHOP;
			text = engine_->get_texture(TEXTURES::GAME_WHITE_BISHOP);
			break;
		case 3:
			type = FIGURE::QUEEN;
			text = engine_->get_texture(TEXTURES::GAME_WHITE_QUEEN);
			break;
		case 4:
			type = FIGURE::KING;
			text = engine_->get_texture(TEXTURES::GAME_WHITE_KING);
			break;
		default:
			throw std::runtime_error("Something happened [0]!");
			break;
		}
		Figure* fig = new Figure(engine_, scene_, this, text, type);

		fig->Sprite().Position(felder_.at(x).at(7)->Position());
		fig->current_feld_ = felder_.at(x).at(7);
		fig->white_ = true;

		player_[0]->figures.push_back(fig);
		if (fig->Type() == FIGURE::KING) player_[0]->king_ = fig;
		felder_.at(x).at(7)->fig_ = fig;
	}
}
Feld* Spielfeld::FeldInFocus(const fr::Vector2i& mouse) {
	for (auto& x : felder_) {
		for (auto& y : x) {
			if (y->InFocus(mouse)) return y;
		}
	}
	return nullptr;
}

Spielfeld::Spielfeld(GameScene* scene)
	: scene_{ scene },
	felder_(scene->feld_size_, std::vector<Feld*>(scene->feld_size_)),
	turn_{ 0 },
	computer_{ false },
	engine_{scene->Engine()},
	board_(engine_, engine_->Window().renderer_),
	text_framerate_(engine_, engine_->Window().renderer_, engine_->get_font(0, 12), fr::Color(11, 167, 0)),
	status_(engine_, engine_->Window().renderer_, engine_->get_font(0, 12), fr::Color(11, 167, 0)),
	marking_(engine_, engine_->Window().renderer_),
	gegner_(this) {

	board_.Texture(engine_->get_texture(TEXTURES::GAME_BOARD));
	board_.Position((engine_->Window().Size() - board_.Size()) / 2);
	scene_->Add(&board_);

	text_framerate_.Sprite().Position(fr::Vector2i(5, 2));
	text_framerate_.String("Fps: ");
	text_framerate_.Render();
	scene_->Add(&text_framerate_);

	SetStatus("White is playing...");
	scene_->Add(&status_);

	marking_.Texture(engine_->get_texture(TEXTURES::GAME_MARKING));

	std::scoped_lock(player_mtx_);
	std::scoped_lock(feld_mtx_);

	constexpr int BOARD_TEXTURE_BORDER_PTS = 26;
	/*Initialize board / felder*/
	fr::Vector2i entry(board_.Position() + BOARD_TEXTURE_BORDER_PTS), size(63, 63);
	for (int x = 0; x < static_cast<int>(felder_.size()); x++) {
		for (int y = 0; y < static_cast<int>(felder_.at(x).size()); y++) {
			felder_.at(x).at(y) = new Feld(entry, size);
			felder_.at(x).at(y)->real_pos_ = fr::Vector2i(x, y);
			entry.y += size.y + 1;
		}
		entry.x += size.x + 1;
		entry.y = board_.Position().y + BOARD_TEXTURE_BORDER_PTS;
	}

	player_[0] = new Player(scene_, this);
	player_[1] = new Player(scene_, this);

	SpawnFigures();
	GetPossibleMoves();
}
Spielfeld::~Spielfeld() {
	player_[0]->DeleteAll();
	player_[1]->DeleteAll();
	delete player_[0];
	delete player_[1];

	for (auto& x : felder_) {
		for (auto& y : x) {
			delete y;
		}
	}

	if (computer_calc_thr_) {
		if (computer_calc_thr_->joinable()) {
			computer_calc_thr_->join();
		}
		delete computer_calc_thr_;
	}
}

void Spielfeld::EventHandle(const fr::Event& evt) {
	if (computer_ && turn_ != 0) return;
	if (evt.type == fr::EventType::SDL_MOUSEBUTTONDOWN) {
		if (evt.button.button & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			Feld* akt = FeldInFocus(fr::Vector2i(scene_->Engine()->MouseState().x, scene_->Engine()->MouseState().y));

			if (!akt) {
				Clean();
				CleanStatus();
				return;
			}
			if (akt->HasFigure()) {
				SetStatusInfo(akt->fig_);
				if ((turn_ == 0 && akt->fig_->white_) || (turn_ != 0 && !akt->fig_->white_)) {
					CleanMarks();

					move_.which = akt;

					akt->mark_ = true;
					for (auto& x : possible_moves_) {
						if (x.which == akt) x.dest->mark_ = true;
					}
				}
			}
			if (!akt->HasFigure() || (turn_ == 0 && !akt->fig_->white_) || (turn_ != 0 && akt->fig_->white_)) {

				move_.dest = akt;
				for (auto& x : possible_moves_) {
					if (move_ == x) {
						move_();

						ChangeTurn();
						
						if (computer_) computer_calc_thr_ = new std::thread(&ComputerGegner::MakeMove, &gegner_);
						break;
					}
				}
				Clean();
				if (!akt->HasFigure()) CleanStatus();
			}
		}
	}
}

void Spielfeld::Tick(const fr::Time& time) {
	text_framerate_.String("Fps: " + std::to_string(static_cast<int>(engine_->Framerate())));
	text_framerate_.Render();
	
	/*let the computer play...*/
	if (turn_ != 0 && computer_) {
		if (gegner_.Finished()) {
			computer_calc_thr_->join();

			MoveData result = gegner_.get_results();
			if (result.which != nullptr && result.dest != nullptr) {
				result();
			}

			delete computer_calc_thr_;
			computer_calc_thr_ = nullptr;

			ChangeTurn();
		}
	}
	/**/
}

void Spielfeld::Reset() {
	Clean();
	for (int x = 0; x < static_cast<int>(felder_.size()); x++) {
		for (int y = 0; y < static_cast<int>(felder_.at(x).size()); y++) {
			felder_.at(x).at(y)->fig_ = nullptr;
		}
	}
	for (int i = 0; i < 2; i++) player_[i]->DeleteAll();
	turn_ = 0;
	SpawnFigures();
	GetPossibleMoves();

	status_.String("White is playing...");
	status_.Render();
	scene_->game_over_ = 0;
}

void Spielfeld::Draw() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < static_cast<int>(player_[i]->figures.size()); j++) {
			player_[i]->figures[j]->Draw();
		}
	}

	for (int x = 0; x < static_cast<int>(felder_.size()); x++) {
		for (int y = 0; y < static_cast<int>(felder_.at(x).size()); y++) {
			if (felder_.at(x).at(y)->mark_) marking_.DrawAt(felder_.at(x).at(y)->Position());
		}
	}
}