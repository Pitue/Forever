#ifndef __MH_LUAUTILITY_H__
#define __MH_LUAUTILITY_H__

#include "common.h"

namespace fr {
	namespace lua {
		std::string FOREVER_API GetError(lua_State* L);
		bool FOREVER_API Check(lua_State* L, int r);

		bool FOREVER_API LoadVar(lua_State* L, const char* name, long long* res);
		bool FOREVER_API LoadVar(lua_State* L, const char* name, int* res);
		bool FOREVER_API LoadVar(lua_State* L, const char* name, double* res);
		bool FOREVER_API LoadVar(lua_State* L, const char* name, bool* res);
		bool FOREVER_API LoadVar(lua_State* L, const char* name, std::string* res);

		bool FOREVER_API LoadTable(lua_State* L, const char* name);

		bool FOREVER_API LoadFromTable(lua_State* L, long long key, std::string* res);
		bool FOREVER_API LoadFromTable(lua_State* L, long long key, long long* res);
		bool FOREVER_API LoadFromTable(lua_State* L, long long key, int* res);

		void FOREVER_API IterateThroughTable(lua_State* L, std::vector<long long>& vec);
		void FOREVER_API IterateThroughTable(lua_State* L, std::vector<int>& vec);
		void FOREVER_API IterateThroughTable(lua_State* L, std::vector<std::string>& vec);
	}
}

#endif // !__MH_LUAUTILITY_H__
