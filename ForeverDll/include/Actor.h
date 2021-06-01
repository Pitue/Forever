#ifndef __FOREVER_ACTOR_H__
#define __FOREVER_ACTOR_H__

#include "common.h"
#include "Drawable.h"
#include "ForeverTime.h"
#include "Sprite.h"

namespace fr {
	class Engine;

	template <class Sc>
	class Actor: public Drawable {
		Sc* scene_;
		fr::Sprite sprite_;
	public:
		Actor(fr::Engine* engine, Sc* scene, Renderer renderer)
			: Drawable(engine, renderer), sprite_(engine, renderer), scene_{ scene } {}

		inline fr::Sprite& Sprite() {
			return sprite_;
		}
		inline const fr::Sprite& Sprite() const {
			return sprite_;
		}
		inline Sc* Scene() {
			return scene_;
		}
		inline const Sc* Scene() const {
			return scene_;
		}

		inline bool HasMouseFocus(const Vector2i& mouse_pos) const {
			if (
				(mouse_pos.x > sprite_.Position().x && mouse_pos.x < (sprite_.Position().x + sprite_.Size().x)) &&
				(mouse_pos.y > sprite_.Position().y && mouse_pos.y < (sprite_.Position().y + sprite_.Size().y))
				) {
				return true;
			}
			return false;
		}

		virtual void Tick(const Time& time) = 0;
		virtual void Draw() = 0;
	};
}

#endif // !__FOREVER_ACTOR_H__
