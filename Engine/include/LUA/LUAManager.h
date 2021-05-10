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
class RigidBody;
class InputSystem;


class LUAManager : public Manager {
private:
	lua_State* L;
	
	LUAManager();
	static LUAManager* instance_;
	
	bool CheckLua(lua_State* L, int r);
	void buildLuaEngine(const std::string& file);
	void registerClassAndFunctions(lua_State* L);
	bool reloadLuaScript(lua_State* L, const std::string& luafile);

public:
	~LUAManager();

	static LUAManager* getInstance();

	//METODOS DE PRUEBA
	RigidBody* getEntity();
	InputSystem* getInputManager();

	//Obtener el estado de LUA
	lua_State* getLuaState()const;
	//Metodos heredados de la clase padre
	virtual void start() override;
	virtual void update() override;

};

#endif // _LUA_MANAGER_H
