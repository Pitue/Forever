#ifndef __FOREVER_FLAPPYBIRD_BIRD_H__
#define __FOREVER_FLAPPYBIRD_BIRD_H__

#include <Forever.h>

#include "enum.h"

class Game;

class Bird : public fr::Actor<Game> {
	fr::uint8 color;

	/*
	0 -> mid
	1 -> down
	2 -> up
	*/
	inline void SetSprite(fr::uint8 state) {
		if (color == 0) {
			if (state == 0) {
				Sprite().Texture(engine_->get_texture(Textures::BLUEBIRD_MIDFLAP));
			}
			else if (state == 1) {
				Sprite().Texture(engine_->get_texture(Textures::BLUEBIRD_DOWNFLAP));
			}
			else if (state == 2) {
				Sprite().Texture(engine_->get_texture(Textures::BLUEBIRD_UPFLAP));
			}
		}
		else if (color == 1) {
			if (state == 0) {
				Sprite().Texture(engine_->get_texture(Textures::REDBIRD_MIDFLAP));
			}
			else if (state == 1) {
				Sprite().Texture(engine_->get_texture(Textures::REDBIRD_DOWNFLAP));
			}
			else if (state == 2) {
				Sprite().Texture(engine_->get_texture(Textures::REDBIRD_UPFLAP));
			}
		}
		else {
			if (state == 0) {
				Sprite().Texture(engine_->get_texture(Textures::YELLOWBIRD_MIDFLAP));
			}
			else if (state == 1) {
				Sprite().Texture(engine_->get_texture(Textures::YELLOWBIRD_DOWNFLAP));
			}
			else if (state == 2) {
				Sprite().Texture(engine_->get_texture(Textures::YELLOWBIRD_UPFLAP));
			}
		}
	}
public:
	bool game_over_;
	Bird(fr::Engine* engine, Game* scene, fr::Renderer renderer) : Actor<Game>(engine, scene, renderer), game_over_{ false } {
		color = engine->GenerateRandomNumber() % 3;
		SetSprite(0);
	}

	inline void Tick(const fr::Time& tm) override {

	}
	inline void Draw() override {
		Sprite().Draw();
	}
};

#endif // !__FOREVER_FLAPPYBIRD_BIRD_H__