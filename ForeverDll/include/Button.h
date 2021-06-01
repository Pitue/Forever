#ifndef __FOREVER_BUTTON_H__
#define __FOREVER_BUTTON_H__

#include <functional>

#include "common.h"
#include "Vector2.h"
#include "Sprite.h"
#include "Drawable.h"
#include "ForeverTime.h"
#include "Text.h"

namespace fr {
	class Engine;
}

namespace fr {

	class FOREVER_API Button : public Drawable {
		Sprite sprite_;
		Texture common_,
						in_focus_,
						clicked_text_;
		bool has_focus_, clicked_, disable_;
		Text label_;

		inline bool InFocus(Vector2i mouse_pos) {
			if (
				(mouse_pos.x > sprite_.Position().x && mouse_pos.x < (sprite_.Position().x + sprite_.Size().x)) &&
				(mouse_pos.y > sprite_.Position().y && mouse_pos.y < (sprite_.Position().y + sprite_.Size().y))
				) {
				has_focus_ = true;
			}
			else {
				has_focus_ = false;
			}
			return has_focus_;
		}
	public:
		Button(fr::Engine* engine, Renderer renderer);

		/*returns if button was clicked*/
		inline operator bool() {
			return clicked_;
		}

		void Reset();
		inline void Disable() {
			disable_ = true;
		}
		/*Button is enabled by default*/
		inline void Enable() {
			disable_ = false;
		}
		inline void AddLabel(TTF_Font* font, std::string text, Color color) {
			label_.Font(font);
			label_.String(text);
			label_.Color(color);
			label_.Render();

			label_.Sprite().Position(((sprite_.Size()) / 2 - (label_.Sprite().Size()) / 2) + sprite_.Position());
		}
		inline void set_textures(Texture common, Texture in_focus, Texture clicked) {
			has_focus_ = false;
			common_ = common;
			in_focus_ = in_focus;
			clicked_text_ = clicked;
			sprite_.Texture(common_, false);
		}
		inline Sprite& Sprite() {
			return sprite_;
		}

		/*Handles mouse events*/
		void Handle(const Event& evt);
		void Draw() override;
	};
}

#endif // !__FOREVER_IMP_BUTTON_H__