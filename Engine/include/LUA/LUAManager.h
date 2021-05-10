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
class Entity;
class RigidBody;
class InputSystem;




class LUAManager : Manager {
private:
	LUAManager();
	bool CheckLua(lua_State* L, int r);

	
	lua_State* L;

	static LUAManager* instance_;
	lua_State* buildLuaEngine(const std::string& file);
	void registerClassAndFunctions(lua_State* L);
	void testCallLua(lua_State* L);
	bool reloadLuaScript(lua_State* L, const std::string& luafile);





public:
	~LUAManager();

	static LUAManager* getInstance();

	void start();
	void update();

	RigidBody* getEntity();
	InputSystem* getInputManager();

    


};

#endif // _LUA_MANAGER_H
