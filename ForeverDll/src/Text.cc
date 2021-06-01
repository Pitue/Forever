#include "../include/Text.h"

namespace fr {
	void Text::Render(fr::Color bg /*= FOREVER_COLOR_WHITE*/) {
		if (text_->length() == 0) {
			if (sprite_.Texture())
				SDL_DestroyTexture(sprite_.Texture());
			sprite_.Texture(nullptr);
			return;
		}

		if (sprite_.Texture()) {
			SDL_DestroyTexture(sprite_.Texture());
			sprite_.Texture(nullptr);
		}
		SDL_Surface* surf = nullptr;
		switch (mode_) {
		case TextRenderMode::RENDER_BLENDED:
			surf = TTF_RenderUTF8_Blended(font_, text_->c_str(), fg_);
			break;
		case TextRenderMode::RENDER_SHADED:
			surf = TTF_RenderUTF8_Shaded(font_, text_->c_str(), fg_, bg);
			break;
		case TextRenderMode::RENDER_SOLID:
			surf = TTF_RenderUTF8_Solid(font_, text_->c_str(), fg_);
			break;

		default:
			return;
			break;
		}
		if (surf) {
			sprite_.Texture(SDL_CreateTextureFromSurface(renderer_, surf));
			sprite_.Resize();
			SDL_FreeSurface(surf);
		}
		else throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_SDL) + TTF_GetError());
	}
}