#ifndef __FOREVER_COLOR_H__
#define __FOREVER_COLOR_H__

#include "common.h"

namespace fr {
	class FOREVER_API Color : public SDL_Color {
	public:
		Color(uint8 r, uint8 g, uint8 b, uint8 a = 255) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		Color() {
			this->r = 0;
			this->g = 0;
			this->b = 0;
			this->a = 255;
		}
	};
}

#endif // !__FOREVER_COLOR_H__
