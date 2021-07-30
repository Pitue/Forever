#ifndef __FOREVER_TYPE_H__
#define __FOREVER_TYPE_H__

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdint.h>
}

#include "define.h"

#include "Vector2.h"
#include "Rect.h"

namespace fr {
	typedef FOREVER_API int_least8_t  int8;
	typedef FOREVER_API int_least16_t int16;
	typedef FOREVER_API int_least32_t int32;
	typedef FOREVER_API int_least64_t int64;

	typedef FOREVER_API uint_least8_t  uint8;
	typedef FOREVER_API uint_least16_t uint16;
	typedef FOREVER_API uint_least32_t uint32;
	typedef FOREVER_API uint_least64_t uint64;

	typedef FOREVER_API SDL_Scancode Keycode;
	typedef FOREVER_API SDL_WindowFlags WindowFlags;
	typedef FOREVER_API SDL_RendererFlags RendererFlags;
	typedef FOREVER_API SDL_EventType EventType;
	typedef FOREVER_API SDL_Window* Window;
	typedef FOREVER_API SDL_Renderer* Renderer;
	typedef FOREVER_API SDL_Event Event;
	typedef FOREVER_API SDL_Texture* Texture;

	typedef FOREVER_API Mix_Music* Music;
	typedef FOREVER_API Mix_Chunk* SoundEffect;

	typedef FOREVER_API Vector2i Point;
}

#endif // !__FOREVER_TYPE_H__
