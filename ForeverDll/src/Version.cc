#include "../include/Version.h"

namespace fr {
	void GetVersion(Version* version) {
		version->major = VERSION_MAJOR;
		version->minor = VERSION_MINOR;
		version->patch = VERSION_PATCHLEVEL;
	}
	std::string MakeLibaryStr() {
		Version versions[5];

		SDL_GetVersion(&versions[0]);
		SDL_IMAGE_VERSION(&versions[1]);
		SDL_TTF_VERSION(&versions[2]);
		SDL_MIXER_VERSION(&versions[3]);
		versions[4].major = std::stoi(LUA_VERSION_MAJOR);
		versions[4].minor = std::stoi(LUA_VERSION_MINOR);
		versions[4].patch = 0;


		std::string t;
		t << fr::VERSION_STR << "\n"
			<< "Loaded Libaries:\n"
			<< "SDL2: " << versions[0].to_string() << "\n"
			<< "SDL2_image: " << versions[1].to_string() << "\n"
			<< "SDL2_ttf: " << versions[2].to_string() << "\n"
			<< "SDL2_mixer: " << versions[3].to_string() << "\n"
			<< "Lua: " << versions[4].to_string();
		return t;
	}
}