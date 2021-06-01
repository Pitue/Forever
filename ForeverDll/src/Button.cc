#include "../include/Button.h"
#include "../include/Engine.h"

namespace fr {
	Button::Button(fr::Engine* engine, Renderer renderer)
		: Drawable(engine,  renderer),
		sprite_(engine, renderer),
		label_(engine, renderer),
		in_focus_{ nullptr },
		common_{ nullptr },
		clicked_text_{nullptr},
		has_focus_{ false },
		clicked_{ false },
		disable_{ false } {

	}

	void Button::Reset() {
		disable_ = false;
		clicked_ = false;
		has_focus_ = false;
		Sprite().Texture(this->common_, false);
	}

	void Button::Handle(const Event& evt) {
		bool t = has_focus_;

		if (evt.type == EventType::SDL_MOUSEMOTION && InFocus(Vector2i(evt.motion.x, evt.motion.y)) != t) {
			if (has_focus_) {
				Sprite().Texture(in_focus_, false);
			}
			else {
				Sprite().Texture(common_, false);
			}
		}
		if (evt.type == EventType::SDL_MOUSEBUTTONDOWN && evt.button.button & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (has_focus_ && !disable_) {
				clicked_ = true;
				Sprite().Texture(clicked_text_);
			}
		}
	}
	void Button::Draw() {
		sprite_.Draw();
		label_.Draw();
	}
}

