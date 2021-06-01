#ifndef __FOREVER_RECT_H__
#define __FOREVER_RECT_H__

#include <SDL.h>
#include "Vector2.h"
#include "define.h"

namespace fr {
	class FOREVER_API Rect: public SDL_Rect {
	public:
		Rect() noexcept {
			x = y = w = h = 0;
		}
		Rect(int x, int y, int w, int h) noexcept {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		Rect(Vector2i pos, Vector2i size) noexcept {
			this->x = pos.x;
			this->y = pos.y;
			this->w = size.x;
			this->h = size.y;
		}


		inline Rect& operator = (const Rect& other) {
			x = (other.x);
			y = (other.y);
			w = (other.w);
			h = (other.h);
			return *this;
		}

		inline Rect& operator += (const Rect& other) {
			x += (other.x);
			y += (other.y);
			w += (other.w);
			h += (other.h);
			return *this;
		}
		inline Rect& operator -= (const Rect& other) {
			x -= (other.x);
			y -= (other.y);
			w -= (other.w);
			h -= (other.h);
			return *this;
		}
		inline Rect& operator *= (const Rect& other) {
			x *= (other.x);
			y *= (other.y);
			w *= (other.w);
			h *= (other.h);
			return *this;
		}
		inline Rect& operator /= (const Rect& other) {
			x /= (other.x);
			y /= (other.y);
			w /= (other.w);
			h /= (other.h);
			return *this;
		}

		inline Rect operator + (const Rect& other) {
			return Rect(
				x + (other.x),
				y + (other.y),
				w + (other.w),
				h + (other.h)
			);
		}
		inline Rect operator - (const Rect& other) {
			return Rect(
				x - (other.x),
				y - (other.y),
				w - (other.w),
				h - (other.h)
			);
		}
		inline Rect operator * (const Rect& other) {
			return Rect(
				x * (other.x),
				y * (other.y),
				w * (other.w),
				h * (other.h)
			);
		}
		inline Rect operator / (const Rect& other) {
			return Rect(
				x / (other.x),
				y / (other.y),
				w / (other.w),
				h / (other.h));
		}

		inline Vector2i Position() const {
			return Vector2i(x, y);
		}
		inline Vector2i Position(Vector2i val) {
			x = val.x;
			y = val.y;
			return val;
		}
		inline Vector2i Size() const {
			return Vector2i(w, h);
		}
		inline Vector2i Size(Vector2i val) {
			w = val.x;
			h = val.y;
			return val;
		}
	};
}

#endif // !__FOREVER_RECT_H__
