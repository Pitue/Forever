#ifndef __FOREVER_TEXT_H__
#define __FOREVER_TEXT_H__

#include "common.h"
#include "Drawable.h"
#include "Color.h"
#include "Vector2.h"
#include "Rect.h"
#include "Sprite.h"

namespace fr {
	class Engine;

	/*
	A drawable Text,
	uses UTF-8 encoding
	*/
	class FOREVER_API Text: public Drawable {
		Sprite sprite_;
		TTF_Font* font_;
		std::string* text_;
		TextRenderMode mode_;
		Color fg_;

	public:
		Text(fr::Engine* engine, Renderer renderer, TTF_Font* font, Color color = FOREVER_COLOR_BLACK, TextRenderMode mode = TextRenderMode::RENDER_SOLID)
			: Drawable(engine, renderer),
			font_{ font },
			sprite_(engine, renderer),
			text_{ new std::string },
			mode_{ mode },
			fg_{ color }{}
		Text (fr::Engine* engine, Renderer renderer)
			:Drawable(engine, renderer),
			 sprite_(engine, renderer),
			 font_{ nullptr },
			 text_{ new std::string }, 
			 mode_{ TextRenderMode::RENDER_SOLID }{}
		~Text() {
			if (text_) delete text_;
		}

		inline Sprite& Sprite() {
			return sprite_;
		}

		inline void String(const std::string& str) { *text_ = str; }
		inline std::string String() { return *text_; }

		inline void Add(const std::string& str) { *text_ << str; }
		inline void Add(const char ch) { text_ += ch; }

		inline void Mode(TextRenderMode mode) {
			mode_ = mode;
		}
		inline TextRenderMode Mode() const {
			return mode_;
		}

		inline void Color(fr::Color color) {
			fg_ = color;
		}
		inline fr::Color Color() const {
			return fg_;
		}

		inline void Font(TTF_Font* font) {
			font_ = font;
		}
		inline TTF_Font* Font() const {
			return font_;
		}

		inline void Backspace() {
			UTF8_PopLast(*text_);
		}

		void Render(fr::Color bg = FOREVER_COLOR_WHITE);
		inline void Draw() override {
			sprite_.Draw();
		}
	};
}

#endif // !__FOREVER_TEXT_H__

