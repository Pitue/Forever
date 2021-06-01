#include <Forever.h>
#include "Menu.h"
#include "Game.h"


int main(int argc, char** argv) {
	try {
		fr::Init(SDL_INIT_EVERYTHING, IMG_INIT_EVERYTHING, MIX_INIT_EVERYTHING, true);

		fr::InitData init;
		init.config_file = "config.lua";
		init.display_index = 0;
		init.fullscreen = false;
		init.render_flags = fr::RendererFlags::SDL_RENDERER_ACCELERATED | fr::RendererFlags::SDL_RENDERER_PRESENTVSYNC;
		init.size = fr::Vector2i(800, 800);
		init.tick_time = 20;
		init.title = "Chess! ver. 0.0.0";
		init.window_flags = fr::WindowFlags::SDL_WINDOW_SHOWN | fr::WindowFlags::SDL_WINDOW_RESIZABLE;


		fr::Engine engine(init);
		engine.Window().SetIcon("Media/icon.png");

		fr::Camera cam0(fr::Vector2i(0, 0), engine.Window().Size());

		MenuScene scene0(&engine, &cam0);

		GameScene scene1(&engine, &cam0);

		engine.Scene(&scene0);
		while (engine) {
			engine.Tick();
			if (engine.Scene() == &scene0 && scene0.Finished()) {
				scene1.SetAiMode(scene0.play_computer_);
				engine.Scene(&scene1);
			}
			else if (engine.Scene() == &scene1 && scene1.Finished()) {
				engine.Shutdown();
			}
		}
	}
	catch (std::exception& ex) {
		fr::ERROR_HANDLE.Handle(ex.what());
	}

	fr::Quit();
	return 0;
}