#include "CollisionObject.h"

CollisionObject::CollisionObject() : coll_ent_(nullptr)
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::onCollisionEnter(Entity* other)
{
}

void CollisionObject::onCollisionExit(Entity* other)
{
}

void CollisionObject::onCollisionStay(Entity* other)
{
}

void CollisionObject::setEntity(Entity* ent)
{
	coll_ent_ = ent;
}

Entity* CollisionObject::getEntity()
{
	return coll_ent_;
}
