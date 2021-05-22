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
#include "MeshComponent.h"
#include "RenderManager.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "OgreContext.h"
#include "MeshStrider.h"
#include <Managers/SceneManager.h>
#include <Scene/Scene.h>

inline Vector3 convertVector(const btVector3& V) {
	return Vector3(V.x(), V.y(), V.z());
}

inline btVector3 convertVector(const Vector3& V) {
	return btVector3(V.x, V.y, V.z);
}

RigidBody::RigidBody() : Component(PhysicsManager::getInstance(), 0)
{
	init();
}

RigidBody::~RigidBody()
{
	if(st)
		delete st;
	st = nullptr;
	//if (rb) {
	//	delete rb;
	//}
	//delete rb->getCollisionShape();
	//delete rb->getMotionState();
	//PhysicsManager::getInstance()->destroyRigidBody(rb);
}

#pragma region Generales

void RigidBody::setUp()
{
	tr_ = static_cast<Transform*>(_entity->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	btQuaternion q;
	Vector3 vRot = tr_->getRot();
	q.setEulerZYX(vRot.x, vRot.y, vRot.z);
	rb->setWorldTransform(btTransform(q, convertVector(tr_->getPos())));

	MeshComponent* mesh = static_cast<MeshComponent*>(_entity->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh));
	if (mesh) {
		Ogre::MeshPtr meshPtr = mesh->getOgreEntity()->getMesh();
		//float x = meshPtr.getPointer()->getBounds().getSize().x;
		//float y = meshPtr.getPointer()->getBounds().getSize().y;
		//float z = meshPtr.getPointer()->getBounds().getSize().z;
		//rb->getCollisionShape()->setLocalScaling(btVector3(x, y, z));

		if (st)
			delete st;
		st = new MeshStrider(meshPtr.get());
		//btCollisionShape* newShape = new btBvhTriangleMeshShape(strider, true, true);
		//btConvexTriangleMeshShape* a = new btConvexTriangleMeshShape(strider, true);
		setCollisionShape(new btConvexTriangleMeshShape(st, true));
	}
}

void RigidBody::init()
{
	rb = PhysicsManager::getInstance()->createRB(Vector3(0, 0, 0), mass);
	rb->setMassProps(1.0f, btVector3(1.0, 1.0, 1.0));
	rb->setDamping(0.5, 0.5);
}

void RigidBody::update(float deltaTime)
{
	//actualizacion del transform a partir del btRigidbody
	const auto worldTransform = rb->getWorldTransform();
	const auto origin = worldTransform.getOrigin();

	btScalar roll;	//X
	btScalar pitch;	//Y
	btScalar yaw;	//Z
	auto rot = worldTransform.getRotation();
	rot.getEulerZYX(yaw, pitch, roll);
	tr_->setPos(Vector3(origin.x(), origin.y(), origin.z()));
	tr_->setRot(Vector3(roll, pitch, yaw));
}

void RigidBody::load(const nlohmann::json& params)
{
	//Masa
	auto it = params.find("mass");
	if (it != params.end()) {
		float m = it->get<float>();
		rb->setMassProps(m, btVector3(1.0, 1.0, 1.0));
	}

	//Restitucion
	it = params.find("restitution");
	if (it != params.end()) {
		float rest = it->get<float>();
		setRestitution(rest);
	}

	//Damping
	it = params.find("dampingLin");
	auto aux = params.find("dampingAng");
	if (it != params.end() && aux != params.end()) {
		float dL = it->get<float>();
		float dA = it->get<float>();
		rb->setDamping(dL, dA);
	}

	//Gravedad
	it = params.find("gravity");
	if (it != params.end()) {
		std::vector<float> newGrav = it->get<std::vector<float>>();
		setGravity(newGrav);
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

	//Estados del rigidbody
	it = params.find("state");
	if (it != params.end()) {
		std::string state = it->get<std::string>();
		if (state == "Kinematic") {
			setKinematic(true);
		}
		else if (state == "Trigger") {
			setTrigger(true);
		}
		else if (state == "Static") {
			setStatic(true);
		}
		else {
			std::cout << "RIGIDBODY:JSON_READING_STATE: " << state << " //FALLO AL LEER EL ESTADO. SE DEJARA POR DEFECTO\n";
		}
	}

	//Formas de la colision
	it = params.find("shape");
	if (it != params.end() && it->is_object()) {
		auto shape = it->find("id");
		if (shape != it->end()) {
			std::string shapeName = shape->get<std::string>();
			btCollisionShape* shapeColl = nullptr;
			if (shapeName == "Box") {
				auto size = it->find("size");
				if (size != it->end()) {
					std::vector<float> s = size->get<std::vector<float>>();
					shapeColl = new btBoxShape(btVector3(s[0], s[1], s[2]));
				}
				else {
					shapeColl = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
				}
			}
			else if (shapeName == "Sphere") {
				auto radius = it->find("radius");
				if (radius != it->end()) {
					float r = it->get<float>();
					shapeColl = new btSphereShape(r);
				}
				else {
					shapeColl = new btSphereShape(1.0f);
				}
			}
			else if (shapeName == "Cylinder") {
				auto size = it->find("size");
				if (size != it->end()) {
					std::vector<float> s = size->get<std::vector<float>>();
					shapeColl = new btCylinderShape(btVector3(s[0], s[1], s[2]));
				}
				else {
					shapeColl = new btCylinderShape(btVector3(1.0f, 1.0f, 1.0f));
				}
			}
			else if (shapeName == "Cone") {
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
			}
			else if (shapeName == "Capsule") {
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
			}

			setCollisionShape(shapeColl);
		}
	}
	// Grupo
	it = params.find("group");
	if (it != params.end() && it->is_number()) {
		 rb->getBroadphaseProxy()->m_collisionFilterGroup = it->get<short>();
	}
	// Mascara
	it = params.find("mask");
	if (it != params.end() && it->is_number()) {
		rb->getBroadphaseProxy()->m_collisionFilterMask = it->get<short>();
	}
}

#pragma endregion

#pragma region Setters
void RigidBody::setPosition(const Vector3& newPos)
{
	if (_active) {
		btTransform tr;
		tr.setOrigin(convertVector(newPos));
		tr.setRotation(rb->getOrientation());

		rb->setWorldTransform(tr);
	}
}

void RigidBody::setGravity(const Vector3& newGrav)
{
	rb->setGravity(convertVector(newGrav));
}

void RigidBody::setTrigger(const bool trigger_) {
	trigger = trigger_;
	if (trigger) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

void RigidBody::setKinematic(const bool kinematic_) {

	if (kinematic_) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
	}
}

void RigidBody::setStatic(const bool _static) {

	if (_static) {
		rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	}
	else {
		rb->setCollisionFlags(rb->getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
	}
}

void RigidBody::setRestitution(float restitution)
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

void RigidBody::setLinearVelocity(const Vector3& vel)
{
	if (_active) {
		btVector3 v = btVector3(vel.x, vel.y, vel.z);
		rb->setLinearVelocity(v);
	}
}

void RigidBody::setFriction(float friction)
{
	if (_active) {
		rb->setFriction(friction);
	}
}

void RigidBody::setCollisionShape(btCollisionShape* newShape)
{
	delete rb->getCollisionShape();
	rb->setCollisionShape(newShape);
}
#pragma endregion

#pragma region Getters

//const Vector3& RigidBody::getLinearVelocity()
//{
//	if (_active) {
//		btVector3 vel = rb->getLinearVelocity();
//		return Vector3(vel.x(), vel.y(), vel.z());
//	}
//	else {
//		return Vector3(0, 0, 0);
//	}
//}

const Vector3& RigidBody::getLinearVelocity() const
{
	if (_active) {
		btVector3 vel = rb->getLinearVelocity();
		return Vector3(vel.x(), vel.y(), vel.z());
	}
	else {
		return Vector3(0, 0, 0);
	}
}

bool RigidBody::isTrigger() const
{
	return trigger;
}

bool RigidBody::isKinematic() const
{
	return rb->isKinematicObject();
}

bool RigidBody::isStatic() const
{
	return rb->isStaticObject();
}

//btCollisionShape* RigidBody::getShape()
//{
//	return rb->getCollisionShape();
//}

btCollisionShape* RigidBody::getShape() const
{
	return rb->getCollisionShape();
}

//btRigidBody* RigidBody::getBtRb()
//{
//	return rb;
//}

btRigidBody* RigidBody::getBtRb() const
{
	return rb;
}

#pragma endregion

#pragma region Adders

void RigidBody::addForce(const Vector3& force, Vector3& relativePos, int type)
{
	if (_active) {
		if (relativePos == Vector3(0.0f, 0.0f, 0.0f)) {
			if (type == (int)Forces::NORMAL)
				rb->applyCentralForce(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
			else if (type == (int)Forces::IMPULSE)
				rb->applyCentralImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
		}
		else {
			if (type == (int)Forces::NORMAL)
				rb->applyForce(
					(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
					(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
			else if (type == (int)Forces::IMPULSE)
				rb->applyImpulse(
					(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
					(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
		}
	}
}

void RigidBody::addTorque(const Vector3& torque, Forces type)
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

bool RigidBody::collidesWithEntity(Entity* other) const
{
	if (other == nullptr) return false;

	//Se obtiene el rb de la otra entidad
	auto* otherRigidBody = reinterpret_cast<RigidBody*>(other->getComponent((int)ManID::Physics, 0));

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

bool RigidBody::onCollisionEnter(const std::string& id) const
{
	//Devuelve true en caso de existir colision
	if (_active) {
		//Se obtiene la entidad de la escena y se comprueba la colision
		Entity* other = SceneManager::getInstance()->getCurrentScene()->getEntity(id);
		return collidesWithEntity(other);
	}

	return false;
}

Entity* RigidBody::collidesWithTag(const std::string& tag) const
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