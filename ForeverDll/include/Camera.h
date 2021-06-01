#ifndef __FOREVER_CAMERA_H__
#define __FOREVER_CAMERA_H__

#include "common.h"
#include "Vector2.h"
#include "Rect.h"

namespace fr {
	class FOREVER_API Camera : public Rect {

	public:
		Camera(): Rect() {}
		Camera(int x, int y, int w, int h): Rect(x, y, w, h) {}
		Camera(Vector2i pos, Vector2i size): Rect(pos, size) {}

		inline void Move(Vector2i val) {
			Position(Position() + val);
		}
	};
}

#endif // !__FOREVER_CAMERA_H__
