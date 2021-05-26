#pragma once
#include "CollisionObject.h"
class LuaComponent;

//Clase que hereda de CollisionObject, cuyo objetivo era ayudar en la gestion de las colisiones entre
//las entidades del juego
//LuaCollisionObject tiene la misma función, pero para gestionar las colisiones desde LUA
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

