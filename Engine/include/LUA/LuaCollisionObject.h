#pragma once
#include "CollisionObject.h"
class LuaComponent;
class LuaCollisionObject : public CollisionObject
{
public:
	LuaCollisionObject(LuaComponent* ptr);
	virtual ~LuaCollisionObject();
	void onCollisionEnter(Entity* e);
	void onCollisionStay(Entity* e);
	void onCollisionExit(Entity* e);

private:
	LuaComponent* _ptr;
};

