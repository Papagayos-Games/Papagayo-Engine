#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Rigidbody.h"

static PhysicsManager* instance_ = nullptr;

PhysicsManager* PhysicsManager::getInstance()
{
	if (instance_ == nullptr)
		if (!setUpInstance())
			throw "ERROR: PhysicsManager couldn't be created\n";
	return instance_;
}

bool PhysicsManager::setUpInstance()
{
	if (instance_ == nullptr) {
		instance_ = new PhysicsManager();
		return true;
	}

	return false;
}

PhysicsManager::PhysicsManager() : Manager(ManID::Physics) {};

PhysicsManager::~PhysicsManager() {};

void PhysicsManager::init(const Vector3 gravity) {

	collConfig = new btDefaultCollisionConfiguration();

	collDispatcher = new btCollisionDispatcher(collConfig);

	broadPhaseInterface = new btDbvtBroadphase();

	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
		constraintSolver, collConfig);

	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

	/* mDebugDrawer_ =
		 new OgreDebugDrawer(OgreSDLContext::getInstance()->getSceneManager());
	 mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	 discreteDynamicsWorld_->setDebugDrawer(mDebugDrawer_);*/
}

void PhysicsManager::destroyWorld()
{
	delete dynamicsWorld; dynamicsWorld = nullptr;

	delete collConfig; collConfig = nullptr;

	delete collDispatcher; collDispatcher = nullptr;

	delete broadPhaseInterface; broadPhaseInterface = nullptr;

	delete constraintSolver; constraintSolver = nullptr;

	//delete mDebugDrawer_; mDebugDrawer_ = nullptr;
}

void PhysicsManager::destroyRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeCollisionObject(body);
	delete body;
}


btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
	return dynamicsWorld;
}

btRigidBody* PhysicsManager::createRB(Vector3 pos, Vector3 shape, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	btBoxShape* box = new btBoxShape(btVector3(shape.x, shape.y, shape.z));

	btMotionState* motion = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box);
	btRigidBody* rb = new btRigidBody(info);
	rb->forceActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(rb);
	//rbs.push_back(rb);
	/*shapes_.push_back(box);
	states_.push_back(motion);*/

	return rb;
}

void PhysicsManager::addComponent(Entity* ent, int compId)
{

}

void PhysicsManager::start()
{
	//TODO: ESTO ES INUTIL BRUH
}

void PhysicsManager::update()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);
	//#ifdef _DEBUG
	//    dynamicsWorld->debugDrawWorld();
	//#endif
}

void PhysicsManager::destroyAllComponents()
{
	auto i = _compsList.begin();
	while (i != _compsList.end()) {
		destroyRigidBody(static_cast<Rigidbody*>((*i))->getBtRb());
		_compsList.remove((*i));
	}
	destroyWorld();
}

bool PhysicsManager::destroyComponent(Entity* ent, int compId)
{
	auto i = _compsList.begin();
	while (i != _compsList.end()) {
		if (ent == (*i)->getEntity()) {
			destroyRigidBody(static_cast<Rigidbody*>((*i))->getBtRb());
			_compsList.remove((*i));
			return true;
		}
		else {
			++i;
		}
	}

	return false;
}
