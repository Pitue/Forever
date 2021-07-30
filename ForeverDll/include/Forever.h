#ifndef __FOREVER_INCLUDE_H__
#define __FOREVER_INCLUDE_H__

/*libaries*/
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
}
#include <lua.hpp>
#include <utf8cpp/utf8.h>

/*common*/
#include "constant.h"
#include "define.h"
#include "enum.h"
#include "miscellaneous.h"
#include "type.h"

/*Classes*/
#include "Export/Engine.h"
#include "Export/Font.h"

#include "Clock.h"
#include "Color.h"
#include "Rect.h"
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "ForeverTime.h"
#include "Vector2.h"
#include "Version.h"
#include "Window.h"

#endif

/*
Note: Es soll eigene abgeleitete Klasse von Scene geschrieben werden, die dann unabhängig läuft(Event basiert)


*/