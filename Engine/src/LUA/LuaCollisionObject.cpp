#include "LuaCollisionObject.h"
#include "LuaComponent.h"
#include "LUAManager.h"
#include "Entity.h"
LuaCollisionObject::LuaCollisionObject(LuaComponent* ptr):CollisionObject()
{
	_ptr = ptr;
	setEntity( _ptr->getEntity());
}
LuaCollisionObject::~LuaCollisionObject()
{
}
void LuaCollisionObject::onCollisionEnter(Entity* e)
{
	if (LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionEnter"].isFunction())
	{
		LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionEnter"](_ptr->getSelf(), LUAManager::getInstance(), e);
	}
}

void LuaCollisionObject::onCollisionStay(Entity* e)
{
	if (LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionStay"].isFunction())
	{
		LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionStay"](_ptr->getSelf(), LUAManager::getInstance(), e);
	}
}

void LuaCollisionObject::onCollisionExit(Entity* e)
{
	if (LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionExit"].isFunction())
	{
		LUAManager::getInstance()->getLuaClass(_ptr->getFileName())["onCollisionExit"](_ptr->getSelf(), LUAManager::getInstance(), e);
	}
}
