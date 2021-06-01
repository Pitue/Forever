#ifndef __FOREVER_SPRITE_H__
#define __FOREVER_SPRITE_H__

#include "common.h"
#include "Drawable.h"
#include "Camera.h"

namespace fr {
	class Engine;

	class FOREVER_API Sprite : public Drawable {
		Texture texture_;
		Rect dest_,
						source_;
		SDL_RendererFlip flip_;
		Point center_;
		float rotation_;
		bool clipped_,
			centered_,
			hide_;
		const Camera* cam_;

	public:
		inline void Resize() {
			if (texture_) SDL_QueryTexture(texture_, NULL, NULL, &dest_.w, &dest_.h);
		}

		Sprite(fr::Engine* engine, fr::Renderer renderer);

		inline void Texture(Texture texture, bool reset = true) {
			texture_ = texture;

			if (reset) {
				Resize();
				rotation_ = 0.f;
				centered_ = false;
				clipped_ = false;
				flip_ = SDL_RendererFlip::SDL_FLIP_NONE;
			}
		}
		inline fr::Texture Texture() const {
			return texture_;
		}
		inline void Flip(SDL_RendererFlip flip) {
			flip_ = flip;
		}
		inline SDL_RendererFlip Flip() const {
			return flip_;
		}
		inline void Size(const Vector2i& size) {
			dest_.w = size.x;
			dest_.h = size.y;
		}
		inline Vector2i Size() const {
			return dest_.Size();
		}
		inline void Scale(double x, double y) {
			dest_.w = std::lrint(x * static_cast<double>(dest_.w));
			dest_.h = std::lrint(y * static_cast<double>(dest_.h)); 
		}
		inline void Position(const Vector2i& pos) {
			dest_.x = pos.x;
			dest_.y = pos.y;
		}
		inline Vector2i Position() const {
			return dest_.Position();
		}

		inline void Center(const Point& center) {
			center_ = center;
			centered_ = true;
		}
		inline void Clip(Rect clip) {
			source_ = clip;
			clipped_ = true;
		}
		inline void Rotation(float rotation_) {
			rotation_ = rotation_;
			while (rotation_ < 0.f) rotation_ += 360.f;
			while (rotation_ > 360.f) rotation_ -= 360.f;
		}

		inline void Hide() {
			hide_ = true;
		}
		inline void Show() {
			hide_ = false;
		}

		inline void Bind(const Camera* cam) {
			cam_ = cam;
		}
		inline void Bind(fr::Engine* engine) {
			engine_ = engine;		
		}
		inline void Bind(fr::Renderer renderer) {
			renderer_ = renderer;
		}

		inline bool IsInFrame();

		void Move(const Vector2i& offset);
		void Rotate(float offset);
		void Draw() override;
		void DrawAt(const Vector2i& pos);
	};
}

#endif // !__FOREVER_SPRITE_H__
