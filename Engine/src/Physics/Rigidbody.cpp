#include "Rigidbody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "btBulletCollisionCommon.h"
#include "Vector3.h"
#include "Collider.h"

Rigidbody::Rigidbody(ecs::CmpId id) : Component(id)
{
	//Informacion interna del rigidbody
	btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(), coll->getShape());
	rb = new btRigidBody(info);
	//info.m_mass = 1;
	//info.m_motionState = new btDefaultMotionState;
	//
	//rb = new btRigidBody(info);
};
