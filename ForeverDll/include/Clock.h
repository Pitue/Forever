#ifndef __FOREVER_CLOCK_H__
#define __FOREVER_CLOCK_H__

#include "common.h"
#include "ForeverTime.h"

namespace fr {
	class FOREVER_API Clock {
		uint32 timestamp_;

	public:
		Clock(): timestamp_{SDL_GetTicks()} {}
		
		inline Time Restart() {
			uint32 t = timestamp_;
			timestamp_ = SDL_GetTicks();
			return Time(timestamp_ - t);
		}
		inline Time ElapsedTime() {
			return Time(SDL_GetTicks() - timestamp_);
		}
	};

}

#endif // !__FOREVER_CLOCK_H__
