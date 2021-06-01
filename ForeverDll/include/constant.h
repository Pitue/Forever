#ifndef __FOREVER_COSTANT_H__
#define __FOREVER_COSTANT_H__

#include <vector>
#include <string>

#include "define.h"
#include "type.h"
#include "ErrorHandle.h"

namespace fr {
	extern const FOREVER_API uint8 VERSION_MAJOR;
	extern const FOREVER_API uint8 VERSION_MINOR;
	extern const FOREVER_API uint8 VERSION_PATCHLEVEL;
	extern const FOREVER_API std::string VERSION_STR;

	extern const FOREVER_API uint32 DEFAULT_VECTOR_SIZE;
	extern const std::vector<std::string> ERROR_MESSAGE;

	extern FOREVER_API ErrorHandle ERROR_HANDLE;
}

#endif