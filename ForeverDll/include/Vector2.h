#ifndef __FOREVER_VECTOR2_H__
#define __FOREVER_VECTOR2_H__

extern "C" {
#include <SDL.h>
}

namespace fr {

	/*
	Used for positions and sizes
	Why have two parameters when it can be one?
	This is in fact not an new Version of the Vector, sorry if i got you excited
	*/
	class FOREVER_API Vector2i: public SDL_Point {
	public:
		int x, y;

		inline Vector2i() noexcept {
			x = y = 0;
		}
		inline Vector2i(int x, int y) noexcept {
			this->x = x;
			this->y = y;
		}
		inline Vector2i(const Vector2i& other) noexcept {
			this->x = other.x;
			this->y = other.y;
		}

		inline Vector2i& operator = (const Vector2i& other) {
			x = (other.x);
			y = (other.y);
			return *this;
		}
		inline bool operator == (const Vector2i& other) {
			if (x == other.x && y == other.y) return true;
			return false;
		}

		inline Vector2i& operator += (const Vector2i& other) {
			x += (other.x);
			y += (other.y);
			return *this;
		}
		inline Vector2i& operator -= (const Vector2i& other) {
			x -= (other.x);
			y -= (other.y);
			return *this;
		}
		inline Vector2i& operator *= (const Vector2i& other) {
			x *= (other.x);
			y *= (other.y);
			return *this;
		}
		inline Vector2i& operator /= (const Vector2i& other) {
			x /= (other.x);
			y /= (other.y);
			return *this;
		}

		inline Vector2i operator + (const Vector2i& other) const {
			return Vector2i(x + (other.x),	y + (other.y));
		}
		inline Vector2i operator - (const Vector2i& other) const {
			return Vector2i(x - (other.x), y - (other.y));
		}
		inline Vector2i operator * (const Vector2i& other) const{
			return Vector2i(x * (other.x), y * (other.y));
		}
		inline Vector2i operator / (const Vector2i& other) const{
			return Vector2i(x / (other.x), y / (other.y));
		}

		inline Vector2i& operator += (int other) {
			x += other;
			y += other;
			return *this;
		}
		inline Vector2i& operator -= (int other) {
			x -= other;
			y -= other;
			return *this;
		}
		inline Vector2i& operator *= (int other) {
			x *= other;
			y *= other;
			return *this;
		}
		inline Vector2i& operator /= (int other) {
			x /= other;
			y /= other;
			return *this;
		}

		inline Vector2i operator + (int other) const {
			return Vector2i(x + (other), y + (other));
		}
		inline Vector2i operator - (int other) const {
			return Vector2i(x - (other), y - (other));
		}
		inline Vector2i operator * (int other) const {
			return Vector2i(x * (other), y * (other));
		}
		inline Vector2i operator / (int other) const {
			return Vector2i(x / (other), y / (other));
		}
	};
}

#endif // !__FOREVER_VECTOR2_H__
