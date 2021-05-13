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
	delete self_;
}

void LuaComponent::init()
{
	currState = LUAManager::getInstance()->getLuaState();
	/*self_ = new luabridge::LuaRef(currState);

	luabridge::LuaRef mi_clase = luabridge::getGlobal(currState, className_.c_str());*/
#pragma region Pruebas

	//lua_getglobal(currState, "start");
	////luabridge::push(currState, LUAManager::getInstance(), errorCode);
	//lua_pcall(currState, 0, 0, 0);
	//(*self_) = luabridge::getGlobal(currState, "sj");

	//lua_getglobal(currState, "creaPinguino");
	//luabridge::push(currState, LUAManager::getInstance(), errorCode);
	//lua_pcall(currState, 1, 0, 0);

	//if (mi_clase.isTable()) {
	//	luabridge::LuaRef self = mi_clase["instantiate"](15)[0];
	//	if (self.isTable()) {
	//		try {
	//			std::cout << self["hp"] << " " << self["name"] << '\n';
	//		}
	//		catch (luabridge::LuaException e) {
	//			std::cout << e.what() << '\n';
	//		}
	//		luabridge::LuaRef update = mi_clase["update"](self)[0];
	//		if (update.isTable()) {
	//			std::cout << update["hp"] << '\n';
	//		}
	//	}
	//}
#pragma endregion


}

void LuaComponent::load(const nlohmann::json& params)
{


	auto it = params.find("Class");
	std::string method;

	//Cogemos el nombre del metodo al que llamar en el update
	if (it != params.end()) 
		className_ = it->get<std::string>();
	else {
		className_ = "default";
#ifdef _DEBUG
		std::cout << "No method name found while loading LUAComponent. Assigned default\n";
#endif
	}
	luabridge::LuaRef mi_clase = luabridge::getGlobal(currState, className_.c_str());

	it = params.find("Parameters");
	if (it != params.end()) {
		luabridge::LuaRef self = mi_clase["instantiate"]((*it).dump())[0];
	}
	
}

void LuaComponent::update()
{
	luabridge::LuaRef mi_clase = luabridge::getGlobal(currState, className_.c_str());
	mi_clase["update"](self_);
}
