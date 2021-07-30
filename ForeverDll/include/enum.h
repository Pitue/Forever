#ifndef __FOREVER_ENUM_H__
#define __FOREVER_ENUM_H__

#include "define.h"
#include "type.h"

namespace fr {
	/*
	These Codes all match to an meaningfull string,
	internally used to generate strings
	*/
	enum class FOREVER_API ErrorCode : uint8 {
		/*
		Expects a filename; (MakeErrorStr(...) + filename)
		*/
		ERR_FILE_NOT_FOUND = 0,
		ERR_INDEX_OUT_OF_RANGE,
		ERR_PARAM_OUT_OF_RANGE,
		ERR_OVERFLOW,
		ERR_UNDERFLOW,
		ERR_INITIALIZATION,
		ERR_CREATING,
		ERR_LUA,
		ERR_LUA_NOT_FOUND,
		ERR_SDL,
		ERR_STRING_ENCODING
	};
	enum class FOREVER_API TextRenderMode : uint8 {
		RENDER_BLENDED = 0,
		RENDER_SHADED,
		RENDER_SOLID
	};
	enum class FOREVER_API ErrorHandleMode : uint8 {
		PRINT_TO_CONSOLE = 0,
		LOG_IN_FILE,
		SHOW_MESSAGE_BOX,
		THROW_ERROR
	};
}
		

#endif // !__FOREVER_ENUM_H__
