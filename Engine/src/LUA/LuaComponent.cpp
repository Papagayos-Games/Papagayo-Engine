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
	delete class_;
	delete self_;
}

void LuaComponent::init()
{
	currState = LUAManager::getInstance()->getLuaState();
	class_ = new luabridge::LuaRef(currState);
	self_ = new luabridge::LuaRef(currState);
}

void LuaComponent::load(const nlohmann::json& params)
{
	auto it = params.find("Class");
	std::string className;

	//Cogemos el nombre del metodo al que llamar en el update
	if (it != params.end()) 
		className = it->get<std::string>();
	else {
		className = "default";
#ifdef _DEBUG
		std::cout << "No class found while loading LUAComponent. Assigned default\n";
#endif
	}
	(*class_) = luabridge::getGlobal(currState, className.c_str());

	it = params.find("Parameters");
	if (it != params.end()) {
		(*self_) = (*class_)["instantiate"]((*it).dump())[0];
		std::cout << (*self_)["hp"] << '\n';
		if (self_->isTable()) {
			std::cout << "tabla\n";
		}
	}
}

void LuaComponent::setUp()
{
	(*class_)["start"](self_, LUAManager::getInstance());
}

void LuaComponent::update()
{
	(*class_)["update"](self_, LUAManager::getInstance());
}
