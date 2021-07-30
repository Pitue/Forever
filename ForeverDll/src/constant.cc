#include "../include/constant.h"

namespace fr {
	const uint8 VERSION_MAJOR = 0;
	const uint8 VERSION_MINOR = 0;
	const uint8 VERSION_PATCHLEVEL = 0;
	const std::string VERSION_STR = "Forever V. 0.0.0";

	const uint32 DEFAULT_VECTOR_SIZE = 1024;
	const std::vector<std::string> ERROR_MESSAGE = {
		"Forever: Couldn't find/open the specified File: ",
		"Forever: Given Index is out of range",
		"Forever: Given Paramter is out of range",
		"Forever: An overflow has occured",
		"Forever: An underflow has occured",
		"Forever: Couldn't initialize Libary: ",
		"Forever: Couldn't create an object: ",
		"Forever: Lua: ",
		"Forever: Lua: Couldn't load Variable: ",
		"Forever: SDL Error: ",
		"Forever: utf8cpp: Not an valid UTF-8 string"
	};
	ErrorHandle ERROR_HANDLE(ErrorHandleMode::SHOW_MESSAGE_BOX);
}