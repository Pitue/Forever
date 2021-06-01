#include "../include/Font.h"

fr::Imp::Font::Font(const std::string& file)
	: file_(file) {

}

fr::Imp::Font::~Font() {
	auto it = loaded_fonts_.begin();
	for (; it != loaded_fonts_.end(); it++) {
		TTF_CloseFont(it->second);
		it->second = NULL;
	}
}

TTF_Font* fr::Imp::Font::GetFont(uint32 ptsize) {
	auto res = loaded_fonts_.find(ptsize);
	if (res == loaded_fonts_.end()) {
		TTF_Font* n_font = TTF_OpenFont(file_.c_str(), ptsize);

		if (n_font == NULL) throw std::runtime_error(std::string("Forever: Engine: ") + TTF_GetError());

		loaded_fonts_.insert({ ptsize, n_font });
		return n_font;
	}
	else {
		return res->second;
	}
	return NULL;
}
