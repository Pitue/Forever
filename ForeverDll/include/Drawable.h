#ifndef __FOREVER_DRAWABLE_H__
#define __FOREVER_DRAWABLE_H__

#include <SDL2/SDL.h>

#include "type.h"
#include "define.h"

namespace fr {
	class Engine;
}

namespace fr {
	class FOREVER_API Drawable {
	protected:
		Renderer renderer_;
		Engine* engine_;
	public:
		Drawable(Engine* engine, Renderer renderer)
			: renderer_{ renderer }, engine_{ engine } {}
		virtual ~Drawable() {}
		virtual void Draw() = 0;

		inline Engine* Engine() {
			return engine_;
		}
	};
}

#endif // !__FOREVER_DRAWABLE_H__
