#ifndef __FOREVER_IMP_FONT_H__
#define __FOREVER_IMP_FONT_H__

#include <map>
#include <string>
#include <stdexcept>

#include <SDL2/SDL_ttf.h>

#include "type.h"

namespace fr {
	namespace Imp {
		class Font {
			std::map<uint32, TTF_Font*> loaded_fonts_;
			std::string file_;
		public:
			Font(const std::string& file);
			~Font();

			TTF_Font* GetFont(uint32 ptsize);
		};
	}
}

#endif // !__FOREVER_IMP_FONT_H__