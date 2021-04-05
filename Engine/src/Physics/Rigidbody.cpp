#include "Rigidbody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "btBulletCollisionCommon.h"
#include "Vector3.h"
#include "Entity.h"

Rigidbody::Rigidbody(ecs::CmpId id) : Component(id)
{
	init();
}

void Rigidbody::init()
{
	//Informacion interna del rigidbody
	btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(), shapeColl);
	rb = new btRigidBody(info);
	//seteamos la gravedad por defecto TODO: ESTO VA A IR EN EL PHYSICS MANAGER
	rb->setGravity(GRAVITY); 

	//rb = PhysicsManager::getinstance->createRB(this);
};

void Rigidbody::activateGravity()
{
	rb->applyGravity();
};

void Rigidbody::deactivateGravity()
{
	rb->clearGravity();
}

Vector3 Rigidbody::getLinearVelocity() const
{
    if (active) {
        btVector3 vel = rb->getLinearVelocity();
        return Vector3(vel.x(), vel.y(), vel.z());
    }
    else {
        return Vector3(0, 0, 0);
    }
}

bool Rigidbody::isTrigger()
{
	return trigger;
}

bool Rigidbody::isKinematic()
{
	return kinematic;
}

bool Rigidbody::isStatic()
{
	return static_;
}

void Rigidbody::setTrigger(const bool trigger_) {
    if (trigger) {
        rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    else {
        rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }

    trigger = trigger_;
}

void Rigidbody::setKinematic(const bool kinematic_) {

    if (kinematic) {
        rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    else {
        rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
    }

    kinematic = kinematic_;
}

void Rigidbody::setStatic(const bool _static) {
    if (_static) {
        rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    }
    else {
        rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
    }

    static_ = _static;
}

void Rigidbody::setRestitution(float restitution)
{
    if (active) {
        //restricciones
        if (restitution < 0) {
            restitution = 0;
        }
        else if (restitution > 1) {
            restitution = 1;
        }

        rb->setRestitution(restitution);
    }
}

void Rigidbody::setLinearVelocity(Vector3 vel)
{
    if (active) {
        btVector3 v = btVector3(vel.x, vel.y, vel.z);
        rb->setLinearVelocity(v);
    }
}

void Rigidbody::setFriction(float friction)
{
    if (active) {
        rb->setFriction(friction);
    }
}

void Rigidbody::setPosition(Vector3 newPos)
{
    if (active) {
        btTransform tr;
        btVector3 vec = btVector3(newPos.x, newPos.y, newPos.z);
        tr.setOrigin(vec);
        tr.setRotation(rb->getOrientation());

        rb->setWorldTransform(tr);
    }
}

void Rigidbody::addForce(Vector3 force, Vector3 relativePos)
{
    if (active) {
        if (relativePos == Vector3(0.0f, 0.0f, 0.0f))
            rb->applyCentralForce((btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))));
        else
            rb->applyForce(
                (btVector3(btScalar(force.x), btScalar(force.y),
                    btScalar(force.z))),
                (btVector3(btScalar(relativePos.x), btScalar(relativePos.y),
                    btScalar(relativePos.z))));
    }
}

