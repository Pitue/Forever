#include "Game.h"

void GameScene::EndGame(Uint8 ergebnis) {
	const SDL_MessageBoxButtonData buttons[] = {
		{SDL_MessageBoxButtonFlags::SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
		{SDL_MessageBoxButtonFlags::SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT , 1, "No"}
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
	data.title = "The game is over!";
	data.window = engine_->Window().window_;

	switch (ergebnis)	{
	case 0:
		data.message = "White won! Do you want to play again?";
		break;
	case 1:
		data.message = "Black won! Do you want to play again?";
		break;
	case 2:
		data.message = "Remis! Do you want to play again?";
		break;
	default:
		break;
	}

	int buttonid = 0;
	SDL_ShowMessageBox(&data, &buttonid);

	if (buttonid == 0) {
		spielfeld_.Reset();
		return;
	}
	else if (buttonid == 1) {
		running_ = false;
	}
}

GameScene::GameScene(fr::Engine* engine, fr::Camera* cam)
	: Scene(engine),
	game_over_{ 0 },
	spielfeld_{ this } {
		int boarder_ = 18;

		cam_ = cam;
}
GameScene::~GameScene() {

}

bool GameScene::Finished() {
	return !fr::Scene::operator bool();
}

void GameScene::EventHandle(const fr::Event& evt) {
	spielfeld_.EventHandle(evt);
}

void GameScene::Tick(const fr::Time& time) {
	spielfeld_.Tick(time);
	if (game_over_ != 0) EndGame(game_over_ - 1);
}
void GameScene::Draw() {
	fr::Scene::Draw();
	spielfeld_.Draw();
}
	