#ifndef __FOREVER_FONT_H__
#define __FOREVER_FONT_H__

#include "../Font.h"
#include "../define.h"

namespace fr {
	class FOREVER_API Font {
		Imp::Font* font_;

	public:
		Font(const std::string& file)
			: font_{new Imp::Font(file)} {
		}
		~Font() {
			delete font_;
		}

		inline TTF_Font* GetFont(uint32 ptsize) {
			return font_->GetFont(ptsize);
		}
	};
}

#endif // __FOREVER_FONT_H__
