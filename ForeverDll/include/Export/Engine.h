#ifndef __FORVER_ENGINE_FOREVER_API_H__
#define __FORVER_ENGINE_FOREVER_API_H__

#include "../define.h"
#include "../Engine.h"
#include "../type.h"

namespace fr {
	class FOREVER_API Engine {
		Imp::Engine* engine_;

	public:
		Engine(const InitData& data)
			: engine_{nullptr}
				{
			engine_ = new Imp::Engine(data);
			if (!engine_) throw std::runtime_error("Couldn't create Engine!");
		}
		~Engine() {
			if (engine_) delete engine_;
		}

		inline operator bool() {
			return engine_->operator bool();
		}

		inline const Event* Event() {
			return engine_->event_;
		}
		inline const Uint8* KeyStates() {
			return engine_->key_states_;
		}
		inline MouseState MouseState() {
			return engine_->mouse_state_;
		}
		inline float Framerate() {
			return engine_->framerate_;
		}

		inline Texture get_texture(size_t indx) const {
			return engine_->get_texture(indx);
		}
		inline Music get_music(size_t indx) const {
			return engine_->get_music(indx);
		}
		inline SoundEffect get_sound(size_t indx) const {
			return engine_->get_sound(indx);
		}
		inline TTF_Font* get_font(size_t indx, int size) {
			return engine_->get_font(indx, size);
		}

		inline uint64 GenerateRandomNumber() {
			return engine_->GenerateRandomNumber();
		}
		inline uint64 RanomSeed() {
			return engine_->RandomSeed();
		}

		inline void Shutdown() {
			engine_->Shutdown();
		}
		inline void Scene(Scene* scene) {
			engine_->Scene(scene);
		}
		inline fr::Scene* Scene() const {
			return engine_->Scene();
		}
		inline WindowContainer& Window() {
			return engine_->Window();
		}
		inline void Tick() {
			engine_->Tick();
		}
	};
}

#endif // !__FORVER_ENGINE_FOREVER_API_H__
