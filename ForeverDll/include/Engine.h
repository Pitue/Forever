#ifndef __FOREVER_ENGINE_H__
#define __FOREVER_ENGINE_H__

#include <random>

#include "common.h"

#include "Window.h"
#include "lua_utility.h"
#include "Clock.h"
#include "Export/Font.h"

/*Forward declaration*/
namespace fr {
	class Scene;
}

namespace fr {
	struct MouseState {
		uint32 btn;
		int x, y;
	};

	struct InitData {
		std::string title, config_file;
		Vector2i size;
		uint32 tick_time, window_flags, render_flags = RendererFlags::SDL_RENDERER_ACCELERATED | RendererFlags::SDL_RENDERER_PRESENTVSYNC, display_index = 0, fullscreen;
	};

	namespace Imp {
		class Engine {
			WindowContainer window_;
			lua_State* lua_state_;
			uint32 tick_time_;

			std::vector<Texture> textures_;
			std::vector<Music> music_;
			std::vector<SoundEffect> sounds_;
			std::vector<Font> fonts_;

			Clock game_clock_;
			Scene* scene_;
			bool running_;
			std::mt19937_64 random_engine_;
			uint64 seed_;

			Vector2i window_size_;

			void LoadTextures(const std::vector<std::string>& files);
			void LoadMusic(const std::vector<std::string>& files);
			void LoadSoundEffects(const std::vector<std::string>& files);
			void LoadFonts(const std::vector<std::string>& files);

			void LoadConfig(const char* file);
			void Quit();
			void Draw();
		public:
			const Event* event_;
			const Uint8* key_states_;
			MouseState mouse_state_;
			float framerate_;

			Engine(const InitData& data);
			~Engine();
			Engine(const Engine& other) = delete;
			Engine& operator = (const Engine& other) = delete;

			inline operator bool() {
				return running_;
			}

			inline Texture get_texture(size_t indx) const {
				if (indx >= textures_.size()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INDEX_OUT_OF_RANGE));
				return textures_.at(indx);
			}
			inline Music get_music(size_t indx) const {
				if (indx >= music_.size()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INDEX_OUT_OF_RANGE));
				return music_.at(indx);
			}
			inline SoundEffect get_sound(size_t indx) const {
				if (indx >= sounds_.size()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INDEX_OUT_OF_RANGE));
				return sounds_.at(indx);
			}
			inline TTF_Font* get_font(size_t indx, int ptsize) {
				if (indx >= fonts_.size()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INDEX_OUT_OF_RANGE));
				return fonts_.at(indx).GetFont(ptsize);
			}

			inline void Shutdown() {
				running_ = false;
			}
			inline uint64 GenerateRandomNumber() {
				return random_engine_();
			}
			inline uint64 RandomSeed() const {
				return seed_;
			}

			inline void Scene(Scene* scene) {
				scene_ = scene;
			}
			inline fr::Scene* Scene() const {
				return scene_;
			}

			inline WindowContainer& Window() {
				return window_;
			}

			void Tick();
		};
	}
}

#endif // !__FOREVER_IMP_ENGINE_H__



