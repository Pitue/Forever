//C++ doesnt like it if i name the header Time.h

#ifndef __FOREVER_FOREVER_TIME_H__
#define __FOREVER_FOREVER_TIME_H__

#include "common.h"

namespace fr {
	class FOREVER_API Time {
		uint32 val_;

	public:
		Time() : val_{ 0 } {}
		Time(uint32 millisec): val_{ millisec } {}

		inline uint32 AsMilliseconds() const noexcept {
			return val_;
		}
		inline float AsSeconds() const noexcept {
			return static_cast<float>(val_) / 1000.f;
		}
		inline std::chrono::milliseconds AsMillisecondsC() const noexcept {
			return std::chrono::milliseconds(val_);
		}
		inline std::chrono::seconds AsSecondsC() const noexcept {
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(val_));
		}
	};

}

#endif // !__FOREVER_FOREVER_TIME_H__