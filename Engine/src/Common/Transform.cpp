#include "Transform.h"
#include "ecs.h"



Transform::Transform() :
	Component(ecs::Transform), position(),
	velocity(),
	dimensions(),
	rotation() 
{
}

Transform::Transform(Vector3 pos, Vector3 vel,Vector3 dim, double rotation = 0.0) :
	Component(ecs::Transform), position(pos), //
	velocity(vel), //
	dimensions(dim),
	rotation(rotation) //
{
}

Transform::~Transform() {
}

