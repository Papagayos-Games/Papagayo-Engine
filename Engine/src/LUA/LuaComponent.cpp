#include "LuaComponent.h"
#include "LUAManager.h"
#include <LuaBridge.h>
#include "lua.hpp"
#include "Entity.h"
#include "LuaCollisionObject.h"


#include "checkML.h"

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
	luabridge::LuaRef class_ = LUAManager::getInstance()->getLuaClass(fileName_);
	if (!class_["instantiate"].isFunction()) {
#ifdef _DEBUG
		std::cout << "No table created while loading LUAComponent. Assigned default\n";
#endif
		fileName_ = "default";
		throw std::exception("Assigned LUA component couldn't be instantiated\n");
	}

	if (_entity->hasComponent((int)ManID::Physics, 0)) {
		if (class_["onCollisionEnter"].isFunction() || class_["onCollisionStay"].isFunction() || class_["onCollisionExit"].isFunction())
		{
			static_cast<RigidBody*>(_entity->getComponent((int)ManID::Physics, 0))->setUserPtr(new LuaCollisionObject(this));
		}
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

void LuaComponent::update(float deltaTime)
{
	LUAManager::getInstance()->getLuaClass(fileName_)["update"](self_, LUAManager::getInstance(), deltaTime);
}

void LuaComponent::fixedUpdate(float deltaTime)
{
	LUAManager::getInstance()->getLuaClass(fileName_)["fixedUpdate"](self_, LUAManager::getInstance(), deltaTime);
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

