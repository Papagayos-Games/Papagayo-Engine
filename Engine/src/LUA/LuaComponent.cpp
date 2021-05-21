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
	delete self_;
}

void LuaComponent::init()
{
	currState = LUAManager::getInstance()->getLuaState();
	self_ = new luabridge::LuaRef(currState);
}

void LuaComponent::load(const nlohmann::json& params)
{
	if (!LUAManager::getInstance()->getLuaClass(fileName_)["instantiate"].isFunction()) {
#ifdef _DEBUG
		std::cout << "No table created while loading LUAComponent. Assigned default\n";
#endif
		fileName_ = "default";
		throw std::exception("Assigned LUA component couldn't be instantiated\n");
	}
	(*self_) = LUAManager::getInstance()->getLuaClass(fileName_)["instantiate"](params.dump(), getEntity())[0];

#ifdef _DEBUG
	std::cout << fileName_ << " loaded correctly\n";
#endif
}

void LuaComponent::setUp()
{
	LUAManager::getInstance()->getLuaClass(fileName_)["start"](self_, LUAManager::getInstance());
}

void LuaComponent::update()
{
	LUAManager::getInstance()->getLuaClass(fileName_)["update"](self_, LUAManager::getInstance());
}

const std::string& LuaComponent::getFileName()
{
	return fileName_;
}

const std::string& LuaComponent::getFileName() const
{
	return fileName_;
}

const luabridge::LuaRef* LuaComponent::getSelf() const
{
	return self_;
}
