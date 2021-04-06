#include "Rigidbody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btPointCollector.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Vector3.h"
#include "Entity.h"

bool Rigidbody::collidesWithEntity(Entity* other) const
{
	if (other == nullptr) return false;

	//Se obtiene el rb de la otra entidad
	auto* otherRigidBody = reinterpret_cast<Rigidbody*>(other->getComponent(ecs::CmpId::Rigidbody));
	
	if (!otherRigidBody->isActive())
		return false;

	//Declaracion del algoritmo de Vorono
	btVoronoiSimplexSolver simplexSolver;
	btGjkEpaPenetrationDepthSolver epaPenSolver;
	btPointCollector collPoint;

	//Detector de colisiones
	btGjkPairDetector convexConvex(
		static_cast<btConvexShape*>(shapeColl),
		static_cast<btConvexShape*>(otherRigidBody->getShape()),
		&simplexSolver, &epaPenSolver);

	//Mediante un input que guarda referencia de los dos objetos,
	//se genera un output (collPoint), de manera que, posteriormente, se puede
	//comprobar si se ha producido una colision.
	btGjkPairDetector::ClosestPointInput input;
	input.m_transformA = rb->getWorldTransform();
	input.m_transformB = otherRigidBody->rb->getWorldTransform();
	convexConvex.getClosestPoints(input, collPoint, nullptr);

	return collPoint.m_hasResult && collPoint.m_distance <= 0;
}

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

void Rigidbody::setActiveGravtiy(const bool active)
{
	if (active) {
		rb->applyGravity();
	}
	else {
		rb->clearGravity();
	}
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

btCollisionShape* Rigidbody::getShape()
{
	return shapeColl;
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

void Rigidbody::addForce(Vector3 force, Vector3 relativePos, Forces type)
{
	if (active) {
		if (relativePos == Vector3(0.0f, 0.0f, 0.0f)) {
			if (type == Forces::NORMAL)
				rb->applyCentralForce(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
			else if (type == Forces::IMPULSE)
				rb->applyCentralImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
		}
		else {
			if (type == Forces::NORMAL)
				rb->applyForce(
					(btVector3(btScalar(force.x), btScalar(force.y),
						btScalar(force.z))),
					(btVector3(btScalar(relativePos.x), btScalar(relativePos.y),
						btScalar(relativePos.z))));
			else if (type == Forces::IMPULSE)
				rb->applyImpulse(
					(btVector3(btScalar(force.x), btScalar(force.y),
						btScalar(force.z))),
					(btVector3(btScalar(relativePos.x), btScalar(relativePos.y),
						btScalar(relativePos.z))));
		}
	}
}

void Rigidbody::addTorque(Vector3 torque, Forces type)
{
	if (active) {
		if (type == Forces::NORMAL)
			rb->applyTorque(btVector3(torque.x, torque.y, torque.z));
		else if (type == Forces::IMPULSE)
			rb->applyTorqueImpulse(btVector3(torque.x, torque.y, torque.z));
	}
}

bool Rigidbody::collidesWith(std::string id) const
{
	// Recieves an id of an entity and checks if our father is colliding with it
	if (active) {
		//Se obtiene la entidad de la escena y se comprueba la colision
		//Entity* other = scene_->getEntityById(id);
		//return collidesWithEntity(other);
	}

	return false;
}

Entity* Rigidbody::collidesWithTag(std::string tag) const
{
	//Obtiene la lista de entidades de la escena
	//std::vector<Entity*> tagEntities = scene_->getEntitiesByTag(tag);

	//Busqueda de la entidad con el tag propuesto
	//for (auto it : tagEntities) {
	//	if (collidesWithEntity(it))
	//		return it;
	//}

	return nullptr;
}

