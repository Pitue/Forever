#ifndef __FOREVER_COMMON_H__
#define __FOREVER_COMMON_H__

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <mutex>
#include <queue>
#include <type_traits>
#include <thread>
#include <functional>

#if _HAS_CXX17
#include <filesystem>
#endif

#include <ctime>
#include <cmath>
#include <cassert>

#ifdef _WIN32
#include <Windows.h>
#endif

extern "C" {
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
}

#include <lua.hpp>

#include "constant.h"
#include "define.h"
#include "enum.h"
#include "miscellaneous.h"
#include "type.h"


#endif // !__FOREVER_COMMON_H__
