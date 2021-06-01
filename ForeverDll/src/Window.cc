#include "../include/Window.h"

namespace fr {
	WindowContainer::WindowContainer(Rect dimension, const std::string& title, uint32 window_flags, uint32 renderer_flags)
		: window_{ nullptr }, renderer_{ nullptr }, event_(), is_open_{ false }{
		Init(dimension, title, window_flags, renderer_flags);
	}
	WindowContainer::WindowContainer() : window_{ nullptr }, renderer_{ nullptr }, event_(), is_open_{ false } {}
	WindowContainer::~WindowContainer() {
		if (renderer_) SDL_DestroyRenderer(renderer_);
		if (window_) SDL_DestroyWindow(window_);
	}

	void WindowContainer::Init(Rect dimension, const std::string& title, uint32 window_flags, uint32 renderer_flags) {
		window_ = SDL_CreateWindow(title.c_str(), dimension.x, dimension.y, dimension.w, dimension.h, window_flags);
		if (window_ == NULL) {
			throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_CREATING) + SDL_GetError());
		}
		else {
			renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags);
			if (renderer_ == NULL) {
				throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_CREATING) + SDL_GetError());
			}
			else {
				SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
				is_open_ = true;
			}
		}
	}
	void WindowContainer::Close() {
		if(renderer_) SDL_DestroyRenderer(renderer_);
		if(window_) SDL_DestroyWindow(window_);
		renderer_ = nullptr;
		window_ = nullptr;
		is_open_ = false;	
	}
	bool WindowContainer::PollEvent() {
		if (SDL_PollEvent(&event_)) {
			if (event_.type == EventType::SDL_QUIT) {
				Close();
			}
			else if (event_.type == EventType::SDL_WINDOWEVENT) {
				switch (event_.window.event)	{
				case SDL_WindowEventID::SDL_WINDOWEVENT_CLOSE:
					Close();
					break;
				default:
					break;
				}
			}
			return true;
		}
		return false;
	}

	void WindowContainer::SetIcon(const char* filename) {
		SDL_Surface* icon = IMG_Load(filename);
		if (icon) {
			SDL_SetWindowIcon(window_, icon);
			SDL_FreeSurface(icon);
		}
		else {
			throw std::runtime_error(IMG_GetError());
		}
	}
	void WindowContainer::SetIcon(SDL_Surface* icon) {
		SDL_SetWindowIcon(window_, icon);
	}
	/*void WindowContainer::SetDisplay(int display_id) {
		if (display_id < 0 || display_id >= SDL_GetNumVideoDisplays()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_PARAM_OUT_OF_RANGE));

		int flag = SDL_GetWindowFlags(window_);
		if (flag & SDL_WindowFlags::SDL_WINDOW_FULLSCREEN || flag & SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP) SetFullscreen( 0);

		SDL_Rect bounds;
		SDL_GetDisplayBounds(display_id, &bounds);
		SDL_SetWindowPosition(window_, bounds.x + (bounds.w - Size().x) / 2, bounds.y + (bounds.h - Size().y) / 2);

		if (flag & SDL_WindowFlags::SDL_WINDOW_FULLSCREEN) {
			SetFullscreen(SDL_WindowFlags::SDL_WINDOW_FULLSCREEN);
		}
		else if (flag & SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP) {
			SetFullscreen(SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}*/
}