#ifndef __FOREVER_FLAPPYBIRD_PIPE_H__
#define __FOREVER_FLAPPYBIRD_PIPE_H__

#include <Forever.h>
#include "enum.h"

class Game;

class Pipe : public fr::Actor<Game> {

public:
	Pipe(fr::Vector2i pos, int length, fr::Engine* engine, Game* scene, fr::Renderer renderer) : Actor<Game>(engine, scene, renderer) {
		if (engine->GenerateRandomNumber() % 100 < 50) {
			Sprite().Texture(engine->get_texture(Textures::PIPE_GREEN));
		}
		else {
			Sprite().Texture(engine->get_texture(Textures::PIPE_RED));
		}
		Sprite().Resize();
		Sprite().Position(pos);
		Sprite().Size(fr::Vector2i(Sprite().Size().x, length));
	}

	inline void Tick(const fr::Time& tm) override {}
	inline void Draw() override {
		Sprite().Draw();
	}
};

#endif // !__FOREVER_FLAPPYBIRD_PIPE_H__
