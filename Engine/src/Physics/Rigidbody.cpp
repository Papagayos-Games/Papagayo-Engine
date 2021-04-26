#include "Rigidbody.h"
#include <cmath>

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
	delete rb;
}

#pragma region Generales

void Rigidbody::init()
{
	rb = PhysicsManager::getInstance()->createRB(Vector3(0, 0, 0), mass);
	rb->setMassProps(1.0f, btVector3(1.0, 1.0, 1.0));
	rb->setDamping(0.5, 0.5);
}

void Rigidbody::update()
{
	//actualizacion del transform a partir del btRigidbody
	CommonManager* instance = CommonManager::getInstance();
	auto* transform = reinterpret_cast<Transform*>(
		_entity->getComponent(instance->getId(), (int)CommonManager::CommonCmpId::TransId));

	const auto worldTransform = rb->getWorldTransform();
	const auto origin = worldTransform.getOrigin();

	btScalar roll;	//X
	btScalar pitch;	//Y
	btScalar yaw;	//Z
	auto rot = worldTransform.getRotation();
	rot.getEulerZYX(yaw, pitch, roll);
	transform->setPos(Vector3(origin.x(), origin.y(), origin.z()));
	transform->setRot(Vector3(roll, pitch, yaw));
}

void Rigidbody::load(nlohmann::json params)
{

	//Masa
	auto it = params.find("mass");
	if (it != params.end()) {
		float m = it->get<float>();
		rb->setMassProps(m, btVector3(1.0, 1.0, 1.0));
	}

	//Damping
	it = params.find("dampingLin");
	auto aux = params.find("dampingAng");
	if (it != params.end() && aux != params.end()) {
		float dL = it->get<float>();
		float dA = it->get<float>();
		rb->setDamping(dL, dA);
	}

	//Posicion
	it = params.find("position");
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
		setKinematic(isKinematic);
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
	it = params.find("friction");
	if (it != params.end()) {
		float friction = it->get<float>();
		setFriction(friction);
	}

	//Formas de la colision
	it = params.find("shape");
	if (it != params.end() && it->is_object()) {
		auto shape = it->find("id");
		if (shape != it->end()) {
			int shapeName = shape->get<int>();
			btCollisionShape* shapeColl = nullptr;
			switch (shapeName)
			{
			case (int)RbCmpId::RbBox: {
				auto size = it->find("size");
				if (size != it->end()) {
					std::vector<float> s = size->get<std::vector<float>>();
					shapeColl = new btBoxShape(btVector3(s[0], s[1], s[2]));
				}
				else {
					shapeColl = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
				}

				break;
			}
			case (int)RbCmpId::RbSphere: {
				auto radius = it->find("radius");
				if (radius != it->end()) {
					float r = it->get<float>();
					shapeColl = new btSphereShape(r);
				}
				else {
					shapeColl = new btSphereShape(1.0f);
				}
				break;
			}
			case (int)RbCmpId::RbCylinder: {
				auto size = it->find("size");
				if (size != it->end()) {
					std::vector<float> s = size->get<std::vector<float>>();
					shapeColl = new btCylinderShape(btVector3(s[0], s[1], s[2]));
				}
				else {
					shapeColl = new btCylinderShape(btVector3(1.0f, 1.0f, 1.0f));
				}
				break;
			}
			case (int)RbCmpId::RbCone: {
				auto radius = it->find("radius");
				auto height = it->find("height");

				if (radius != it->end() && height != it->end()) {
					float r = it->get<float>();
					float h = it->get<float>();
					shapeColl = new btConeShape(r, h);
				}
				else {
					shapeColl = new btConeShape(1.0f, 1.0f);
				}
				break;
			}
			case (int)RbCmpId::RbCapsule: {
				auto radius = it->find("radius");
				auto height = it->find("height");
				if (radius != it->end() && height != it->end()) {
					float r = it->get<float>();
					float h = it->get<float>();
					shapeColl = new btCapsuleShape(r, h);
				}
				else {
					shapeColl = new btCapsuleShape(1.0f, 1.0f);
				}
				break;
			}

			default:
				break;
			}

			setCollisionShape(shapeColl);
		}
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
		rb->setGravity(btVector3(0, 0, 0));
		rb->clearGravity();
	}
}

void Rigidbody::setTrigger(const bool trigger_) {
	trigger = trigger_;
	if (trigger) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

void Rigidbody::setKinematic(const bool kinematic_) {

	if (kinematic_) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
	}
}

void Rigidbody::setStatic(const bool _static) {

	if (_static) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
	}
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
	return rb->isKinematicObject();
}

bool Rigidbody::isStatic()
{
	return rb->isStaticObject();
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
	//Devuelve true en caso de existir colision
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