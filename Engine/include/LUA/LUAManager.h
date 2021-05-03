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
#include "Entity.h"


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

    int setPosiion(int x, int y,int z) {
        lua_State* L = luaL_newstate();
        if (luaL_loadfile(L, "sum.lua") || lua_pcall(L, 0, 0, 0)) {
            std::cout << "Error: failed to load sum.lua" << std::endl;
            return 0;
        }

        lua_getglobal(L, "sum");
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);

        std::cout << "loaded" << std::endl;
        lua_pcall(L, 2, 1, 0);

        int result = (int)lua_tonumber(L, -1);
        lua_pop(L, 1);
        return result;
    }


};

#endif // _LUA_MANAGER_H
