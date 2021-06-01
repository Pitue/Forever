#include "../include/miscellaneous.h"
#include "../include/Drawable.h"

namespace fr {
	std::string& operator << (std::string& obj, const char* data) {
		obj.append(data);
		return obj;
	}
	std::string& operator << (std::string& obj, const std::string& data) {
		obj.append(data);
		return obj;
	}

	std::string MakeTimeStr(const char* format /*= "%c"*/, const size_t reserved_size /*= 256*/) {
		std::time_t time;
		std::tm* tm;
		std::string str;
		str.resize(reserved_size);

		std::time(&time);

#ifdef _MSC_VER
		tm = new std::tm();
		localtime_s(tm, &time);
#else
		tm = std::localtime(&time);
#endif

		std::strftime(str.data(), str.size(), format, tm);

#ifdef _MSC_VER
		delete tm;
#endif
		return str;
	}
	std::string MakeErrorStr(ErrorCode err) {
		return fr::ERROR_MESSAGE[static_cast<uint8>(err)];
	}
	std::string ReadFile(std::ifstream& filestream, size_t filesize /*= 0*/) {
		std::string t; 
		if (filesize != 0) t.reserve(filesize);

		t.assign((std::istreambuf_iterator<char>(filestream)),
						(std::istreambuf_iterator<char>()));

		return t;
	}
	std::string ReadFile(std::string filename) {
		std::ifstream filestream;
		filestream.open(filename);
		if (!filestream.is_open()) throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_FILE_NOT_FOUND) + filename);

#ifdef __cpp_lib_filesystem
		return ReadFile(filestream, static_cast<size_t>(std::filesystem::file_size(std::filesystem::path(filename))));
#else
		return ReadFile(filestream);
#endif
	}

	bool UTF8_IsLeadingByte(char c) {
		auto first_bit_set = (c & 0x80) != 0;
		auto second_bit_set = (c & 0X40) != 0;
		return !first_bit_set || second_bit_set;
	}
	void UTF8_PopLast(std::string& str) {
		if (str.length() > 0) {
			while (!UTF8_IsLeadingByte(str.back()))
				str.pop_back();
			str.pop_back();
		}
	}

	void Init(uint32 sdl_flags, int img_flags, int mix_flags, bool init_ttf) {
		if (SDL_Init(sdl_flags) != 0) {
			throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INITIALIZATION) + SDL_GetError());
		}
		else if ((img_flags >= 0) && IMG_Init(img_flags) != img_flags) {
			throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INITIALIZATION) + SDL_GetError());
		}
		else if ((mix_flags >= 0) && Mix_Init(mix_flags) != mix_flags) {
			throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INITIALIZATION) + SDL_GetError());
		}
		else if ((init_ttf) && TTF_Init() != 0) {
			throw std::runtime_error(MakeErrorStr(ErrorCode::ERR_INITIALIZATION) + SDL_GetError());
		}

		if (mix_flags >= 0) {
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
		}
	}
	void Quit() {
		Mix_CloseAudio();

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}