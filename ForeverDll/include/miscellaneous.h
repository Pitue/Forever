#ifndef __FOREVER_MISCELLANEOUS_H__
#define __FOREVER_MISCELLANEOUS_H__

#include <string>
#include <fstream>

#if _HAS_CXX17
#include <filesystem>
#endif

#include "enum.h"
#include "constant.h"

namespace fr {
	class Drawable;

	std::string& operator << (std::string& obj, const char* data);
	std::string& operator << (std::string& obj, const std::string& data);

	std::string FOREVER_API MakeTimeStr(const char* format = "%c", const size_t reserved_size = 256);
	std::string FOREVER_API MakeErrorStr(ErrorCode err);
	std::string FOREVER_API ReadFile(std::ifstream& filestream, size_t filesize = 0);
	std::string FOREVER_API ReadFile(std::string filename);

	bool FOREVER_API UTF8_IsLeadingByte(char c);
	void FOREVER_API UTF8_PopLast(std::string& x);

	/*
	Initialises the SDL libaries
	if flags (except sdl_flags) are < 0 libary will not be initialized
	*/
	void FOREVER_API Init(uint32 sdl_flags, int img_flags, int mix_flags, bool init_ttf);
	/*
	Quits all SDL libaries
	*/
	void FOREVER_API Quit();
}

#endif