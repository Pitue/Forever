#ifndef __FOREVER_DEFINE_H__
#define __FOREVER_DEFINE_H__

#include <SDL.h>
#include <SDL_mixer.h>

#ifdef FOREVERDLL_EXPORTS
#define FOREVER_API __declspec(dllexport)
#else
#define FOREVER_API __declspec(dllimport)
#endif

/* https://www.colorpicker.me */
#define FOREVER_COLOR_WHITE fr::Color(255, 255, 255)
#define FOREVER_COLOR_BLACK fr::Color(0, 0, 0)

#define FOREVER_COLOR_RED fr::Color(251, 10, 39)
#define FOREVER_COLOR_GREEN fr::Color(31, 235, 43)
#define FOREVER_COLOR_BLUE fr::Color(33, 11, 240)

#define IMG_INIT_EVERYTHING (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP)
#define MIX_INIT_EVERYTHING (MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS | MIX_INIT_MID | MIX_INIT_MOD)


#endif // !__FOREVER_DEFINE_H__
