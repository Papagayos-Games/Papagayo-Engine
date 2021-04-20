#include "Rigidbody.h"

//bullet includes
#include "LinearMath/btDefaultMotionState.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btPointCollector.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

//includes de nuestro proyecto
#include "Vector3.h"
#include "Entity.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "CommonManager.h"

Rigidbody::Rigidbody() : Component(PhysicsManager::getInstance(), 0)
{
	init();
}

Rigidbody::~Rigidbody()
{
}

#pragma region Generales

void Rigidbody::init()
{
	rb = PhysicsManager::getInstance()->createRB(Vector3(0, 0, 0), mass);
}

void Rigidbody::update()
{
	//actualizacion del transform a partir del btRigidbody
	CommonManager* instance = CommonManager::getInstance();
	auto* transform = reinterpret_cast<Transform*>(
		_entity->getComponent(instance->getId(), (int)CommonManager::CommonCmpId::TransId));

	const auto worldTransform = rb->getWorldTransform();
	const auto origin = worldTransform.getOrigin();
	
	transform->setPos(Vector3(origin.x(), origin.y(), origin.z()));
}

void Rigidbody::load(nlohmann::json params)
{
	//Posicion
	auto it = params.find("position");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		setPosition(Vector3(pos[0], pos[1], pos[2]));
	}

	//Gravedad
	it = params.find("isGravity");
	if (it != params.end()) {
		bool isGravity = it->get<bool>();
		setActiveGravity(isGravity);
	}

	//Trigger
	it = params.find("isTrigger");
	if (it != params.end()) {
		bool isTrigger = it->get<bool>();
		setTrigger(isTrigger);
	}

	//Cinematico
	it = params.find("isKinematic");
	if (it != params.end()) {
		bool isKinematic = it->get<bool>();
		setActiveGravity(isKinematic);
	}

	//Estatico
	it = params.find("isStatic");
	if (it != params.end()) {
		bool isStatic = it->get<bool>();
		setStatic(isStatic);
	}

	//Restitucion
	it = params.find("restitution");
	if (it != params.end()) {
		float rest = it->get<float>();
		setRestitution(rest);
	}

	//Velocidad Lineal
	it = params.find("linealVel");
	if (it != params.end()) {
		std::vector<float> vel = it->get<std::vector<float>>();
		setLinearVelocity(vel);
	}

	//Friccion
	it = params.find("friccion");
	if (it != params.end()) {
		float friction = it->get<float>();
		setFriction(friction);
	}

	//Formas de la colision
	it = params.find("shape");
	if (it != params.end()) {
		int shapeName= it->get<int> ();
		btCollisionShape* shapeColl = nullptr;
		switch (shapeName)
		{
		case (int)RbCmpId::RbBox:
			shapeColl = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
			break;
		case (int)RbCmpId::RbSphere:
			shapeColl = new btSphereShape(1.0f);
			break;
		case (int)RbCmpId::RbCylinder:
			shapeColl = new btCylinderShape(btVector3(1.0f, 1.0f, 1.0f));
			break;
		case (int)RbCmpId::RbCone:
			shapeColl = new btConeShape(1.0f, 1.0f);
			break;
		case (int)RbCmpId::RbCapsule:
			shapeColl = new btCapsuleShape(1.0f, 1.0f);
			break;
		default:
			break;
		}

		setCollisionShape(shapeColl);
	}
}

#pragma endregion

#pragma region Setters
void Rigidbody::setPosition(Vector3 newPos)
{
	if (_active) {
		btTransform tr;
		btVector3 vec = btVector3(newPos.x, newPos.y, newPos.z);
		tr.setOrigin(vec);
		tr.setRotation(rb->getOrientation());

		rb->setWorldTransform(tr);
	}
}

void Rigidbody::setActiveGravity(const bool active)
{
	if (active) {
		rb->applyGravity();
	}
	else {
		rb->clearGravity();
	}
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
	if (_active) {
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
	if (_active) {
		btVector3 v = btVector3(vel.x, vel.y, vel.z);
		rb->setLinearVelocity(v);
	}
}

void Rigidbody::setFriction(float friction)
{
	if (_active) {
		rb->setFriction(friction);
	}
}

void Rigidbody::setCollisionShape(btCollisionShape* newShape)
{
	rb->setCollisionShape(newShape);
}
#pragma endregion

#pragma region Getters

Vector3 Rigidbody::getLinearVelocity() const
{
	if (_active) {
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
	return rb->getCollisionShape();
}

btRigidBody* Rigidbody::getBtRb()
{
	return rb;
}

#pragma endregion

#pragma region Adders

void Rigidbody::addForce(Vector3 force, Vector3 relativePos, Forces type)
{
	if (_active) {
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
	if (_active) {
		if (type == Forces::NORMAL)
			rb->applyTorque(btVector3(torque.x, torque.y, torque.z));
		else if (type == Forces::IMPULSE)
			rb->applyTorqueImpulse(btVector3(torque.x, torque.y, torque.z));
	}
}

#pragma endregion

#pragma region Colisiones

bool Rigidbody::collidesWithEntity(Entity* other) const
{
	if (other == nullptr) return false;

	//Se obtiene el rb de la otra entidad
	auto* otherRigidBody = reinterpret_cast<Rigidbody*>(other->getComponent((int)ManID::Physics, 0));
	
	if (!otherRigidBody->isActive())
		return false;

	//Declaracion del algoritmo de Vorono
	btVoronoiSimplexSolver simplexSolver;
	btGjkEpaPenetrationDepthSolver epaPenSolver;
	btPointCollector collPoint;

	//Detector de colisiones
	btGjkPairDetector convexConvex(
		static_cast<btConvexShape*>(rb->getCollisionShape()),
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

bool Rigidbody::onCollisionEnter(std::string id) const
{
	// Recieves an id of an entity and checks if our father is colliding with it
	if (_active) {
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

#pragma endregion