#ifndef __CHESS_MENU_H__
#define __CHESS_MENU_H__

#include <vector>
#include <Forever.h>
#include <Button.h>
#include <Text.h>

#include "enum.h"

class MenuScene: public fr::Scene {
	fr::Button button_start_ai_,
									button_start_pvp_,
									button_exit_;
	fr::Text text_framerate_;

public:
	bool play_computer_;
	MenuScene(fr::Engine* engine, fr::Camera* cam) 
		: Scene(engine),
		button_start_ai_(engine, engine->Window().renderer_),
		button_start_pvp_(engine, engine->Window().renderer_),
		button_exit_(engine, engine->Window().renderer_),
		text_framerate_(engine, engine->Window().renderer_, engine->get_font(0, 12), fr::Color(11, 167, 0)),
		play_computer_{false} {
		cam_ = cam;
		Background(engine->get_texture(TEXTURES::MENU_BACKGROUND));

		fr::Vector2i button_size(250, 50);
		button_start_ai_.Sprite().Bind(cam_);
		button_start_ai_.set_textures(engine->get_texture(TEXTURES::MENU_BUTTON), engine->get_texture(TEXTURES::MENU_BUTTON_FOCUS), NULL);
		button_start_ai_.Sprite().Size(button_size);
		button_start_ai_.Sprite().Position(fr::Vector2i((engine->Window().Size().x / 2) - (button_size.x / 2), (engine->Window().Size().y / 2) - (button_size.y / 2)));
		button_start_ai_.AddLabel(engine->get_font(0, 20), "Play against the Computer", fr::Color(12, 167, 0));
	

		button_start_pvp_.Sprite().Bind(cam_);
		button_start_pvp_.set_textures(engine->get_texture(TEXTURES::MENU_BUTTON), engine->get_texture(TEXTURES::MENU_BUTTON_FOCUS), NULL);
		button_start_pvp_.Sprite().Size(button_size);
		button_start_pvp_.Sprite().Position(button_start_ai_.Sprite().Position() + fr::Vector2i(0, button_size.y + 5));
		button_start_pvp_.AddLabel(engine->get_font(0, 20), "Play against each other", fr::Color(12, 167, 0));

		button_exit_.Sprite().Bind(cam_);
		button_exit_.set_textures(engine->get_texture(TEXTURES::MENU_BUTTON), engine->get_texture(TEXTURES::MENU_BUTTON_FOCUS), NULL);
		button_exit_.Sprite().Size(button_size);
		button_exit_.Sprite().Position(button_start_pvp_.Sprite().Position() + fr::Vector2i(0, button_size.y + 5));
		button_exit_.AddLabel(engine->get_font(0, 20), "Exit", fr::Color(12, 167, 0));

		text_framerate_.Sprite().Position(fr::Vector2i(5, 5));
		Add(&text_framerate_);
	}
	~MenuScene() {}

	inline bool Finished() {
		return !fr::Scene::operator bool();
	}

	inline void EventHandle(const fr::Event& evt) override {
		button_start_ai_.Handle(evt);
		button_start_pvp_.Handle(evt);
		button_exit_.Handle(evt);
	}
	inline void Tick(const fr::Time& time) override {
		if (button_start_ai_) {
			play_computer_ = true;
			running_ = false;
		}
		if (button_start_pvp_) {
			running_ = false;
		}
		if (button_exit_) engine_->Shutdown();

		text_framerate_.String("Fps: " + std::to_string(static_cast<int>(engine_->Framerate())));
		text_framerate_.Render();
	}
	inline void Draw() override {
		fr::Scene::Draw();
		button_start_ai_.Draw();
		button_start_pvp_.Draw();
		button_exit_.Draw();
	}
};

#endif // !__CHESS_MENU_H__
