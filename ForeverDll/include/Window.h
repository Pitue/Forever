#ifndef __FOREVER_WINDOW_H__
#define __FOREVER_WINDOW_H__

#include "common.h"

namespace fr {
	class FOREVER_API WindowContainer {
		Event event_;
		bool is_open_;

	public:
		Window window_;
		Renderer renderer_;

		WindowContainer(Rect dimension, const std::string& title, uint32 window_flags, uint32 renderer_flags);
		WindowContainer();
		~WindowContainer();

		inline operator bool()const {
			return is_open_;
		}
		inline operator SDL_Window* () {
			return window_;
		}

		inline bool HasMouseFocus()const {
			return SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_MOUSE_FOCUS;
		}
		inline bool HasKeyboardFocus()const {
			return SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_INPUT_FOCUS;
		}
		inline bool IsShown()const {
			return SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_SHOWN;
		}
		inline bool IsMinimized() const {
			return SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_MINIMIZED;
		}
		inline bool IsFullscreen() const {
			return SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_FULLSCREEN || SDL_GetWindowFlags(window_) & WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		inline const Event* get_event() { return &event_; }
		inline Vector2i ScreenResolution() {
			SDL_DisplayMode res;
			SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(window_), &res);
			return Vector2i(res.w, res.h);
		}

		void Init(Rect dimension, const std::string& title, uint32 window_flags, uint32 renderer_flags);
		void Close();
		bool PollEvent();

		void SetIcon(const char* file);
		void SetIcon(SDL_Surface* icon);
		//void SetDisplay(int display_id);

		inline void SetFullscreen(uint32 flag) {
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_SetWindowFullscreen(window_, flag);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		//Returns the real size of the window
		inline Vector2i DisplaySize() const {
			int x, y;
			SDL_GetWindowSize(window_, &x, &y);
			return Vector2i(x, y);
		}
		//Returns the logicla size of the window
		inline Vector2i Size() const {
			int x, y;
			SDL_RenderGetLogicalSize(renderer_, &x, &y);
			return Vector2i(x, y);
		}
		inline void Size(const Vector2i& size) {
			SDL_SetWindowSize(window_, size.x, size.y);
			SDL_Log("Window was resized to (%i|%i)", size.x, size.y);
		}
		inline std::string Title() const {
			return SDL_GetWindowTitle(window_);
		}
		inline void Title(const std::string& str) {
			SDL_SetWindowTitle(window_, str.c_str());
		}
		inline Vector2i Position() const {
			Vector2i t;
			SDL_GetWindowPosition(window_, &t.x, &t.y);
			return t;
		}
		inline void Position(const Vector2i pos) {
			SDL_SetWindowPosition(window_, pos.x, pos.y);
			SDL_Log("Window was moved to (%i|%i)", pos.x, pos.y);
		}
	};
}

#endif // !__FOREVER_IMP_WINDOW_H__
