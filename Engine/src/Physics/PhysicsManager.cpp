#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "DebugDrawer.h"
#include "Rigidbody.h"
#include "Entity.h"
#include "OgreContext.h"

PhysicsManager* PhysicsManager::instance_ = nullptr;

PhysicsManager* PhysicsManager::getInstance()
{
	return instance_;
}

bool PhysicsManager::setUpInstance() {
	if (instance_ == nullptr) {
		try {
			instance_ = new PhysicsManager();
			instance_->init(Vector3(0.0, -9.8, 0.0));
		}
		catch (...) {
			return false;
		}
	}

	return true;
}

PhysicsManager::PhysicsManager() : Manager(ManID::Physics) {
	registerComponent("RigidBody", 0, []() -> RigidBody* { return new RigidBody(); });

};

PhysicsManager::~PhysicsManager() {
};

void PhysicsManager::init(const Vector3 gravity) {

	collConfig = new btDefaultCollisionConfiguration();

	collDispatcher = new btCollisionDispatcher(collConfig);

	broadPhaseInterface = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
		constraintSolver, collConfig);

	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

#ifdef _DEBUG
	//mDebugDrawer_ = new OgreDebugDrawer(OgreContext::getInstance()->getSceneManager());
	//mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	//dynamicsWorld->setDebugDrawer(mDebugDrawer_);
#endif // DEBUG
}

void PhysicsManager::destroyWorld()
{
	delete dynamicsWorld; dynamicsWorld = nullptr;

	delete collConfig; collConfig = nullptr;

	delete collDispatcher; collDispatcher = nullptr;

	delete broadPhaseInterface; broadPhaseInterface = nullptr;

	delete constraintSolver; constraintSolver = nullptr;

	delete mDebugDrawer_; mDebugDrawer_ = nullptr;
}

void PhysicsManager::destroyRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeCollisionObject(body);
	delete body->getCollisionShape();
	delete body->getMotionState();
	delete body;
	body = nullptr;
}

btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
	return dynamicsWorld;
}

btRigidBody* PhysicsManager::createRB(Vector3 pos, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	//btBoxShape shapeColl = btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

	//btDefaultMotionState motion = btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(transform), new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)));
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
	for (Component* cmp : _compsList)
	{
		cmp->setUp();
	}
}

void PhysicsManager::update()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	for (auto it = _compsList.begin(); it != _compsList.end(); ++it) {
		if (applyTorque) {
			applyTorque = false;
			static_cast<RigidBody*>(*it)->addTorque(Vector3(0.0f, 0.0, -5.0), Forces::IMPULSE);
			//static_cast<RigidBody*>(*it)->addForce(Vector3(0.0f, 1, 0.0f), Vector3(1.0f, 0.0, 1.0), Forces::IMPULSE);
		}
		(*it)->update();
	}

#ifdef _DEBUG
	//dynamicsWorld->debugDrawWorld();
#endif // _DEBUG

}

void PhysicsManager::clean()
{
	instance_->destroyAllComponents();
}

void PhysicsManager::destroy()
{
	instance_->clean();
	instance_->destroyWorld();
	delete instance_;
}

void PhysicsManager::destroyAllComponents()
{
	while (!_compsList.empty()) {
		auto i = _compsList.begin();
		destroyRigidBody(static_cast<RigidBody*>((*i))->getBtRb());
		delete *i;
		_compsList.erase(i);
	}
}

bool PhysicsManager::destroyComponent(Entity* ent, int compId)
{
	auto i = _compsList.begin();
	while (i != _compsList.end()) {
		if (ent == (*i)->getEntity()) {
			destroyRigidBody(static_cast<RigidBody*>((*i))->getBtRb());
			delete *i;
			_compsList.erase(i);
			return true;
		}
		else {
			++i;
		}
	}

	return false;
}