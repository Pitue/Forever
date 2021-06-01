#include "../include/Sprite.h"
#include "../include/Export/Engine.h"

namespace fr {
	inline Sprite::Sprite(fr::Engine* engine, Renderer renderer)
		: Drawable(engine, renderer),
		texture_{ nullptr },
		flip_{ SDL_RendererFlip::SDL_FLIP_NONE },
		rotation_{ 0.f },
		clipped_{ false },
		centered_{ false },
		hide_{false},
		cam_{ nullptr } {

	}

	inline bool Sprite::IsInFrame() {
		if (!cam_) return false;
		fr::Rect me = dest_;
		me.Position(me.Position() - cam_->Position());

		/*if (me.y + me.h <= win.y || me.y >= win.y + win.h || me.x + me.w <= win.x || me.x >= win.x + win.w)	{
			return false;
		}

		return true;*/
		//SDL_Log("me rect: %i|%i %i|%i", me.x, me.y, me.w, me.h);;
		return SDL_HasIntersection(&me, cam_);
	}

	inline void Sprite::Move(const Vector2i& offset) {
		dest_.x += offset.x;
		dest_.y += offset.y;
	}
	inline void Sprite::Rotate(float offset) {
		rotation_ += offset;
		while (rotation_ < 0.f) rotation_ += 360.f;
		while (rotation_ > 360.f) rotation_ -= 360.f;
	}
	inline void Sprite::Draw() {
		if (!texture_ || hide_) return;

		if (cam_) {
			DrawAt(dest_.Position() - cam_->Position());
			return;
		}

		Rect t = dest_;
		if (cam_) t.Position(t.Position() - cam_->Position());

		if (clipped_ && centered_) {
			SDL_RenderCopyEx(renderer_, texture_, &source_, &t, rotation_, &center_, flip_);
		}
		else if (clipped_) {
			SDL_RenderCopyEx(renderer_, texture_, &source_, &t, rotation_, NULL, flip_);
		}
		else if (centered_) {
			SDL_RenderCopyEx(renderer_, texture_, NULL, &t, rotation_, &center_, flip_);
		}
		else {
			SDL_RenderCopyEx(renderer_, texture_, NULL, &t, rotation_, NULL, flip_);
		}
	}
	void Sprite::DrawAt(const Vector2i& pos) {
		if (!texture_ || hide_) return;

		Rect t = dest_;
		if (cam_) t.Position(pos - cam_->Position());
		else t.Position(pos);

		if (clipped_ && centered_) {
			SDL_RenderCopyEx(renderer_, texture_, &source_, &t, rotation_, &center_, flip_);
		}
		else if (clipped_) {
			SDL_RenderCopyEx(renderer_, texture_, &source_, &t, rotation_, NULL, flip_);
		}
		else if (centered_) {
			SDL_RenderCopyEx(renderer_, texture_, NULL, &t, rotation_, &center_, flip_);
		}
		else {
			SDL_RenderCopyEx(renderer_, texture_, NULL, &t, rotation_, NULL, flip_);
		}
	}
}