#include <Forever.h>
#include <filesystem>

#include "Game.h"

int main(int argc, char** argv) {
	fr::Init(SDL_INIT_EVERYTHING, IMG_INIT_EVERYTHING, MIX_INIT_EVERYTHING, true);

	fr::InitData init;
	init.config_file = "config.lua";
	init.display_index = 0;
	init.fullscreen = false;
	init.render_flags = fr::RendererFlags::SDL_RENDERER_ACCELERATED | fr::RendererFlags::SDL_RENDERER_PRESENTVSYNC;
	init.size = fr::Vector2i(288, 512);
	init.tick_time = 20;
	init.title = "Flappy Bird! ver. 0.0.0";
	init.window_flags = fr::WindowFlags::SDL_WINDOW_SHOWN | fr::WindowFlags::SDL_WINDOW_RESIZABLE;

	try {
		fr::Engine engine(init);
		engine.Window().SetIcon("Media/icon.jpg");

		Game game_scene(&engine);

		engine.Scene(&game_scene);
		while (engine) {
			engine.Tick();
		}
	}
	catch (std::exception& ex) {
		fr::ERROR_HANDLE.Handle(ex.what());
	}

	fr::Quit();
	return 0;
}