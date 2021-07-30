#ifndef __FOREVER_VERSION_H__
#define __FOREVER_VERSION_H__

#include <string>

#include <SDL2/SDL_version.h>
#include <lua.hpp>

#include "miscellaneous.h"
#include "constant.h"

namespace fr {
	class FOREVER_API Version
		: public SDL_version {
		std::string* str_;
	public:
		Version() : str_{ new std::string } {}
		inline const char* to_string() {
			*str_ << std::to_string(major) << "." << std::to_string(minor) << "." << std::to_string(patch);
			return str_->c_str();
		}
	};

	/* This function can be used to fill a version structure with the runtime
 version of the Forever library.
*/
	void FOREVER_API GetVersion(Version* version);
	std::string FOREVER_API MakeLibaryStr();
}

#endif // !__FOREVER_IMP_VERSION_H__
 
