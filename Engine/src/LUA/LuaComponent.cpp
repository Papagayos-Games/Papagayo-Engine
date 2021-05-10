#include "LuaComponent.h"
#include "LUAManager.h"
#include <LuaBridge.h>
#include "lua.hpp"


LuaComponent::LuaComponent():Component(LUAManager::getInstance(), 0)
{
	init();
}

LuaComponent::~LuaComponent()
{
}

void LuaComponent::init()
{
	currState = LUAManager::getInstance()->getLuaState();
}

void LuaComponent::load(const nlohmann::json& params)
{
	auto it = params.find("luaMethod");
	std::string method;

	//Cogemos el nombre del metodo al que llamar en el update
	if (it != params.end()) methodName_ = it->get<std::string>();
	else {
		methodName_ = "default";
#ifdef _DEBUG
		std::cout << "No method name found while loading LUAComponent. Assigned default\n";
#endif
	}

}

void LuaComponent::update()
{
	lua_getglobal(currState, methodName_.c_str());
	luabridge::push(currState, LUAManager::getInstance(), errorCode);
	lua_pcall(currState, 1, 0, 0);
}
