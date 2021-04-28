#pragma once

#ifndef _LUA_MANAGER_H
#define _LUA_MANAGER_H

// Link to lua library
#ifdef _WIN64
#pragma comment(lib, "liblua54.a")
#endif

#include <string>

#include "Manager.h"

#include "lua.hpp"

class LUAManager : Manager {
private:
	LUAManager();
	bool CheckLua(lua_State* L, int r);

	lua_State* script_;

	static LUAManager* instance_;

public:
	~LUAManager();

	static LUAManager* getInstance();

	void start();
	void update();
};

#endif // _LUA_MANAGER_H
