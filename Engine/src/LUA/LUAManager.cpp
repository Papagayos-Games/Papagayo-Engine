#include <iostream>
#include "LUAManager.h"

LUAManager* LUAManager::instance_ = nullptr;

LUAManager::LUAManager() : Manager(ManID::LUA)
{
	script_ = luaL_newstate();
	luaL_openlibs(script_);

	
	if (CheckLua(script_, luaL_dofile(script_, "LuaScripts/prueba.lua"))) {
		std::cout << "[C++] tamos bien\n";
	}
}

bool LUAManager::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK) {
		std::string err = lua_tostring(L, -1);
		std::cout << err << "\n";
		return false;
	}
	return true;
}

LUAManager::~LUAManager()
{
}

LUAManager* LUAManager::getInstance()
{
	if (instance_ == nullptr) {
		instance_ = new LUAManager();
	}

	return instance_;
}

void LUAManager::start()
{
}

void LUAManager::update()
{
	//std::cout << "updating\n";
}
