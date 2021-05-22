#pragma once
#include "Rigidbody.h"

class Entity;

class CollisionObject
{
public:
	CollisionObject();
	virtual ~CollisionObject();
	// Callbacks de colision
	virtual void onCollisionEnter(Entity* other) {};

	// TO DO: variable privada, get y set
	Entity* coll_ent_ = nullptr;
};

