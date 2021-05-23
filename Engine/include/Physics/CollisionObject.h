#pragma once
#include "Rigidbody.h"

class Entity;

class CollisionObject
{
public:
	CollisionObject();
	virtual ~CollisionObject();
	// Callbacks de colision
	virtual void onCollisionEnter(Entity* other);
	virtual void onCollisionExit(Entity* other);
	virtual void onCollisionStay(Entity* other);

	void setEntity(Entity* ent);
	Entity* getEntity();
protected:
	Entity* coll_ent_ = nullptr;
};

