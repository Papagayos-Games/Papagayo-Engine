#pragma once
#include "Component.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

class Collider;
class Vector3;
class Rigidbody : public Component
{
private:
	//Masa del Rigidbody
	btScalar mass = 1.0f;
	//Rigidbody principal
	btRigidBody* rb = nullptr;
	//Transform fisico del rigidbody
	btTransform* tr = nullptr;
	//Componente Collider asociada al Rigidbody
	Collider* coll = nullptr;

public:
	Rigidbody(ecs::CmpId id);
	~Rigidbody() {};

	virtual void init() {};
	virtual void update() {};
};

