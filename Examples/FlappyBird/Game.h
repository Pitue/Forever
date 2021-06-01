#ifndef __FOREVER_FLAPPYBIRD_GAME_H__
#define __FOREVER_FLAPPYBIRD_GAME_H__

#include <vector>
#include <Forever.h>

#include "Bird.h"
#include "Pipe.h"
#include "enum.h"

class Game : public fr::Scene {
	const int CAMERA_SPEED = 50;

	Bird bird_;
	std::vector<Pipe> active_pipes_;
	fr::Sprite background_[2], ground_;

	fr::Camera cam_;

public:
	Game(fr::Engine* engine) 
		: Scene(engine),
			bird_(engine, this, engine->Window().renderer_),
		background_{ fr::Sprite(engine, engine->Window().renderer_), fr::Sprite(engine, engine->Window().renderer_) },
			ground_(engine, engine->Window().renderer_) {
		if (engine->GenerateRandomNumber() % 100 < 50) {
			background_[0].Texture(engine->get_texture(Textures::BACKGROUND_DAY));
		}
		else {
			background_[0].Texture(engine->get_texture(Textures::BACKGROUND_NIGHT));
		}
		background_[1].Texture(background_[0].Texture());
		background_[0].Size(engine->Window().Size());
		background_[1].Size(background_[0].Size());
		background_[0].Bind(&cam_);
		background_[1].Bind(&cam_);
		background_[1].Position(fr::Vector2i(background_[0].Position().x + background_[0].Size().x, 0));

		ground_.Texture(engine->get_texture(Textures::BASE));
		ground_.Resize();
		ground_.Size(fr::Vector2i(ground_.Size().x * 2, ground_.Size().y));
		ground_.Bind(&cam_);
		ground_.Position(fr::Vector2i(0, engine->Window().Size().y - ground_.Size().y));

		bird_.Sprite().Bind(&cam_);
		bird_.Sprite().Position(fr::Vector2i(engine->Window().Size().x / 4 - bird_.Sprite().Size().x / 2, (engine->Window().Size().y - ground_.Size().y) / 2 - bird_.Sprite().Size().y / 2));
		bird_.Sprite().Center(bird_.Sprite().Size() / 2);

		Add(&background_[0]);
		Add(&background_[1]);
		Add(&ground_);
		Add(&bird_.Sprite());
	}

	inline void EventHandle(const fr::Event& evt) override {

	}
	inline void Tick(const fr::Time& tm) override {
		bird_.Tick(tm);
		if (bird_.game_over_) engine_->Shutdown();

		cam_.Move(fr::Vector2i(static_cast<int>(std::rint(tm.AsSeconds() * static_cast<float>(CAMERA_SPEED))), 0));
		if (!background_[0].IsInFrame()) {
			background_[0].Position(fr::Vector2i(background_[1].Position().x + background_[1].Size().x, 0));
		}
		else if (!background_[1].IsInFrame()) {
			background_[1].Position(fr::Vector2i(background_[0].Position().x + background_[0].Size().x, 0));
		}
	}
	inline void Draw() override {
		fr::Scene::Draw();
		for (auto& x : active_pipes_) x.Draw();
	}
};

#endif // !__FOREVER_FLAPPYBIRD_H__