#include "LuaComponent.h"
#include "LUAManager.h"
#include <LuaBridge.h>
#include "lua.hpp"

LuaComponent::LuaComponent(const std::string& fileName, int id) : Component(LUAManager::getInstance(), id), fileName_(fileName)
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
	(*class_) = luabridge::getGlobal(currState, "default");
	(*self_) = (*class_)["instantiate"]()[0];
}

void LuaComponent::load(const nlohmann::json& params)
{
	//Cogemos el nombre del metodo al que llamar en el update
	(*class_) = luabridge::getGlobal(currState, fileName_.c_str());
	
	if (class_->isNil()) {
#ifdef _DEBUG
		std::cout << "No class found while loading LUAComponent. Assigned default\n";
#endif
		delete class_;
		delete self_;
		fileName_ = "default";
		throw std::exception("Assigned LUA component to default in loader\n");
	}
	
	(*self_) = (*class_)["instantiate"](params.dump())[0];

	if (self_->isNil()) {
#ifdef _DEBUG
		std::cout << "No class found while loading LUAComponent. Assigned default\n";
#endif
		delete class_;
		delete self_;
		fileName_ = "default";
		throw std::exception("Assigned LUA component to default in loader\n");
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

const std::string& LuaComponent::getFileName()
{
	return fileName_;
}

const std::string& LuaComponent::getFileName() const
{
	return fileName_;
}

