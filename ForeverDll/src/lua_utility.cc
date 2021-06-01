#include "../include/lua_utility.h"

namespace fr {
	namespace lua {
		std::string GetError(lua_State* L) {
			return lua_tostring(L, -1);
		}
		bool Check(lua_State* L, int r) {
			if (r != LUA_OK) {
				throw std::runtime_error(fr::MakeErrorStr(fr::ErrorCode::ERR_LUA) + lua_tostring(L, -1));
				return false;
			}
			return true;
		}

		bool LoadVar(lua_State* L, const char* name, long long* res) {
			lua_getglobal(L, name);
			if (lua_isinteger(L, -1)) {
				lua_Integer t = lua_tointeger(L, -1);
				lua_pop(L, 1);
				*res = t;
				return true;
			}
			return false;
		}
		bool LoadVar(lua_State* L, const char* name, int* res) {
			lua_getglobal(L, name);
			if (lua_isinteger(L, -1)) {
				int t = static_cast<int>(lua_tointeger(L, -1));
				lua_pop(L, 1);
				*res = t;
				return true;
			}
			return false;
		}
		bool LoadVar(lua_State* L, const char* name, double* res) {
			lua_getglobal(L, name);
			if (lua_isinteger(L, -1)) {
				lua_Number t = lua_tonumber(L, -1);
				lua_pop(L, 1);
				*res = t;
				return true;
			}
			return false;
		}
		bool LoadVar(lua_State* L, const char* name, bool* res) {
			lua_getglobal(L, name);
			if (lua_isinteger(L, -1)) {
				bool t = lua_toboolean(L, -1);
				lua_pop(L, 1);
				*res = t;
				return true;
			}
			return false;
		}
		bool LoadVar(lua_State* L, const char* name, std::string* res) {
			lua_getglobal(L, name);
			if (lua_isstring(L, -1)) {
				std::string t = lua_tostring(L, -1);
				lua_pop(L, 1);
				*res = t;
				return true;
			}
			return false;
		}

		bool LoadTable(lua_State* L, const char* name) {
			lua_getglobal(L, name);
			if (!lua_istable(L, -1)) {
				return false;
			}
			return true;
		}

		bool LoadFromTable(lua_State* L, long long key, std::string* res) {
			lua_pushinteger(L, key);
			lua_gettable(L, -2);
			if (lua_isstring(L, -1)) {
				*res = lua_tostring(L, -1);
				lua_pop(L, 1);
				return true;
			}
			else return false;
		}
		bool LoadFromTable(lua_State* L, long long key, long long* res) {
			lua_pushinteger(L, key);
			lua_gettable(L, -2);
			if (lua_isstring(L, -1)) {
				*res = lua_tointeger(L, -1);
				lua_pop(L, 1);
				return res;
			}
			else return false;
		}
		bool LoadFromTable(lua_State* L, long long key, int* res) {
			lua_pushinteger(L, key);
			lua_gettable(L, -2);
			if (lua_isstring(L, -1)) {
				*res = static_cast<int>(lua_tointeger(L, -1));
				lua_pop(L, 1);
				return res;
			}
			else return false;
		}


		void IterateThroughTable(lua_State* L, std::vector<long long>& vec) {
			long long key = -1;
			do {
				vec.push_back(0);
				key++;
			} while (LoadFromTable(L, key, &vec.at(vec.size() - 1)));
			vec.pop_back();
		}
		void IterateThroughTable(lua_State* L, std::vector<int>& vec) {
			long long key = -1;
			do {
				vec.push_back(0);
				key++;
			} while (LoadFromTable(L, key, &vec.at(vec.size() - 1)));
			vec.pop_back();
		}

		void IterateThroughTable(lua_State* L, std::vector<std::string>& vec) {
			long long key = -1;
			do {
				vec.push_back("");
				key++;
			} while (LoadFromTable(L, key, &vec.at(vec.size() - 1)));
			vec.pop_back();
		}
	}
}

