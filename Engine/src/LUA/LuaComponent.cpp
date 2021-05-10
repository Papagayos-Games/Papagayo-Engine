#include "LuaComponent.h"
#include "LUAManager.h"


LuaComponent::LuaComponent():Component(LUAManager::getInstance(), 0)
{
}

LuaComponent::~LuaComponent()
{
}

void LuaComponent::init()
{
}

void LuaComponent::load(const nlohmann::json& params)
{
}

void LuaComponent::update()
{

}
