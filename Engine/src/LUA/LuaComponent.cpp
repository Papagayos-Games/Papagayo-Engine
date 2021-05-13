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
	//¿QUIZA?
	delete tabla;
}

void LuaComponent::init()
{
	currState = LUAManager::getInstance()->getLuaState();
	tabla = new luabridge::LuaRef(currState);

#pragma region Pruebas

	lua_getglobal(currState, "start");
	//luabridge::push(currState, LUAManager::getInstance(), errorCode);
	lua_pcall(currState, 0, 0, 0);
	(*tabla) = luabridge::getGlobal(currState, "sj");

	lua_getglobal(currState, "creaPinguino");
	luabridge::push(currState, LUAManager::getInstance(), errorCode);
	lua_pcall(currState, 1, 0, 0);

	luabridge::LuaRef mi_clase = luabridge::getGlobal(currState, "miclase");
	if (mi_clase.isTable()) {
		luabridge::LuaRef self = mi_clase["instantiate"](15)[0];
		if (self.isTable()) {
			try {
				std::cout << self["hp"] << " " << self["name"] << '\n';
				//luabridge::call(self["func"], "hola");
			}
			catch (luabridge::LuaException e) {
				std::cout << e.what() << '\n';
			}
			luabridge::LuaRef update = mi_clase["update"](self)[0];
			if (update.isTable()) {
				std::cout << update["hp"] << '\n';
			}
			//luabridge::push(currState, update, errorCode);
			//luabridge::push(currState, self, errorCode);
			//lua_pcall(currState, 1, 0, 0);
		}
		//luabridge::push(currState, "hola", errorCode);
	}
	/*if (a.isTable()) {
		std::cout << "Es una funcion loco\n";
		a();
	}*/
#pragma endregion


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
	luabridge::push(currState, tabla, errorCode);
	luabridge::push(currState, LUAManager::getInstance(), errorCode);

	lua_pcall(currState, 2, 0, 0);
}
