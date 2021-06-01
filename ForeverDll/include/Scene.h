#ifndef __FOREVER_SCENE_H__
#define __FOREVER_SCENE_H__

#include "common.h"
#include "ForeverTime.h"
#include "Drawable.h"
#include "Sprite.h"
#include "Actor.h"
#include "Camera.h"

//Forward declaration
namespace fr {
	class Engine;
}

namespace fr {
	class FOREVER_API Scene {
		Sprite background_;
		std::vector<Drawable*>* objects_;

	protected:
		Engine* engine_;
		Camera* cam_;
		bool running_;

	public:
		Scene(Engine* engine);
		~Scene();
		Scene(const Scene& other) = delete;
		Engine& operator = (const Scene& other) = delete;

		inline operator bool() const {
			return running_;
		}

		inline void Add(Drawable* ptr) {
			objects_->push_back(ptr);
		}

		inline void Bind(Camera* cam) {
			cam_ = cam;
		}

		inline Camera* Camera() {
			return cam_;
		}

		void Background(Texture bck);

		virtual void EventHandle(const Event& evt) = 0;
		virtual void Tick(const Time& time) = 0;
		virtual void Draw();
	};
}


#endif //!__FOREVER_IMP_SCENE_H__
