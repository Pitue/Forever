#include "../include/Engine.h"
#include "../include/Scene.h"

namespace fr {
	namespace Imp {
		void Engine::LoadTextures(const std::vector<std::string>& files) {
			textures_.reserve(files.size());
			for (auto& x : files) {
				Texture t = IMG_LoadTexture(window_.renderer_, x.c_str());
				if (t == NULL) {
					throw std::runtime_error("Forever: Engine: Couldn't load \"" + x + "\"");
				}
				textures_.push_back(t);
			}
		}
		void Engine::LoadMusic(const std::vector<std::string>& files) {
			music_.reserve(files.size());
			for (auto& x : files) {
				music_.push_back(Mix_LoadMUS(x.c_str()));
				if (music_.at(music_.size() - 1) == NULL) {
					throw std::runtime_error("Forever: Engine: Couldn't load \"" + x + "\"");
				}
			}
		}
		void Engine::LoadSoundEffects(const std::vector<std::string>& files) {
			sounds_.reserve(files.size());
			for (auto& x : files) {
				sounds_.push_back(Mix_LoadWAV(x.c_str()));
				if (sounds_.at(sounds_.size() - 1) == NULL) {
					throw std::runtime_error("Forever: Engine: Couldn't load \"" + x + "\"");
				}
			}
		}
		void Engine::LoadFonts(const std::vector<std::string>& files) {
			for (auto& x : files) {
				fonts_.push_back(Font(x));
			}
		}

		void Engine::LoadConfig(const char* file) {
			if (luaL_dofile(lua_state_, file) == LUA_OK) {
				std::vector<std::string> texture_files;
				if (!lua::LoadTable(lua_state_, "textures")) {
					ERROR_HANDLE.Warning("Couldn't load table \"textures\" from config file!", window_.window_);
				}
				else {
					lua::IterateThroughTable(lua_state_, texture_files);
					LoadTextures(texture_files);
				}

				std::vector<std::string> music_files;
				if (!lua::LoadTable(lua_state_, "music")) {
					ERROR_HANDLE.Warning("Couldn't load table \"music\" from config file!", window_.window_);
				}
				else {
					lua::IterateThroughTable(lua_state_, music_files);
					LoadMusic(music_files);
				}

				std::vector<std::string> sound_files;
				if (!lua::LoadTable(lua_state_, "sound_effects")) {
					ERROR_HANDLE.Warning("Couldn't load table \"sound_effects\" from config file!", window_.window_);
				}
				else {
					lua::IterateThroughTable(lua_state_, sound_files);
					LoadSoundEffects(sound_files);
				}

				std::vector<std::string> font_files;
				if (!lua::LoadTable(lua_state_, "fonts")) {
					ERROR_HANDLE.Warning("Couldn't load table \"fonts\" from config file!", window_.window_);
				}
				else {
					lua::IterateThroughTable(lua_state_, font_files);
					if (font_files.size() != 0) LoadFonts(font_files);					
				}
			}
			else throw std::runtime_error(std::string("Lua Error: ") + lua::GetError(lua_state_));
		}
		void Engine::Quit() {
			running_ = false;
			window_.Close();
		}
		void Engine::Draw() {
			SDL_RenderClear(window_.renderer_);

			if (scene_) scene_->Draw();

			SDL_RenderPresent(window_.renderer_);
		}

		Engine::Engine(const InitData& data)
			: lua_state_{ luaL_newstate() },
			running_{ true },
			tick_time_{ data.tick_time },
			scene_{ nullptr },
			event_{ nullptr },
			key_states_{ nullptr },
			framerate_{ 0.f },
			window_size_{ data.size } {

			seed_ = static_cast<uint64>(std::chrono::system_clock::now().time_since_epoch().count() * SDL_GetTicks());
			random_engine_.seed(seed_);

			window_.Init(Rect(SDL_WINDOWPOS_CENTERED_DISPLAY(data.display_index), SDL_WINDOWPOS_CENTERED_DISPLAY(data.display_index), data.size.x, data.size.y), data.title, data.window_flags, data.render_flags);
			event_ = window_.get_event();
			if (data.fullscreen != 0) window_.SetFullscreen(data.fullscreen);		
			SDL_RenderSetLogicalSize(window_.renderer_, data.size.x, data.size.y);

			LoadConfig(data.config_file.c_str());
		}
		Engine::~Engine() {
			for (uint32 i = 0; i < textures_.size(); i++) SDL_DestroyTexture(textures_[i]);
			for (uint32 i = 0; i < music_.size(); i++) Mix_FreeMusic(music_[i]);
			for (uint32 i = 0; i < sounds_.size(); i++) Mix_FreeChunk(sounds_[i]);
		}

		void Engine::Tick() {
			static int frames = 0;
			while (window_.PollEvent()) {
				if (!window_) {
					Quit();
				}
				if (event_->type == SDL_EventType::SDL_WINDOWEVENT) {

				}
				if (scene_) scene_->EventHandle(*event_);
			}
			if (window_.IsMinimized()) {
				using namespace std::chrono_literals;
				std::this_thread::sleep_for(50ms);
				return;
			}

			SDL_PumpEvents();
			key_states_ = SDL_GetKeyboardState(NULL);
			mouse_state_.btn = SDL_GetMouseState(&mouse_state_.x, &mouse_state_.y);

			if (scene_ && game_clock_.ElapsedTime().AsMilliseconds() > tick_time_) {
				framerate_ = static_cast<float>(frames) / game_clock_.ElapsedTime().AsSeconds();
				frames = 0;
				scene_->Tick(game_clock_.Restart());
			}

			frames++;
			Draw();
		}
	}
}