#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "DebugDrawer.h"
#include "Rigidbody.h"
#include "Entity.h"
#include "OgreContext.h"
#include "CollisionObject.h"

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
}
void PhysicsManager::checkCollision()
{
	std::map<const btCollisionObject*, std::pair< CollisionObject*, CollisionObject*>> newContacts;
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
		/* Check all contacts points */

		int numContacts = contactManifold->getNumContacts();
		std::cout << numContacts << '\n';

		for (int j = 0; j < numContacts; j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
				bool x = (ContactProcessedCallback)(pt, obA, obB);


				CollisionObject* coA = static_cast<CollisionObject*>(obA->getUserPointer());
				CollisionObject* coB = static_cast<CollisionObject*>(obB->getUserPointer());


				if (newContacts.find(obA) == newContacts.end())
				{
					newContacts[obA] = { coA,coB };
				}

			}
		}
	}
	/* Check for added contacts ... */

	std::map<const btCollisionObject*, std::pair< CollisionObject*, CollisionObject*>>::iterator it;

	if (!newContacts.empty())
	{
		for (it = newContacts.begin(); it != newContacts.end(); it++)
		{
			if (contacts.find((*it).first) == contacts.end())
			{
				(*it).second.first->onCollisionEnter((*it).second.second->coll_ent_);
				//coB->onCollisionEnter(coA->coll_ent_);
			}
			else
			{
				// Remove to filter no more active contacts
				(*it).second.first->onCollisionStay((*it).second.second->coll_ent_);
				contacts.erase((*it).first);
			}
		}
	}


	/* ... and removed contacts */
	if (!contacts.empty())
	{
		for (it = contacts.begin(); it != contacts.end(); it++)
		{
			// TODO: signal
			(*it).second.first->onCollisionExit((*it).second.second->coll_ent_);

		}
		contacts.clear();
	}

	contacts = newContacts;

}



void PhysicsManager::init(const Vector3 gravity) {

	collConfig = new btDefaultCollisionConfiguration();

	collDispatcher = new btCollisionDispatcher(collConfig);

	broadPhaseInterface = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
		constraintSolver, collConfig);

	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

#ifdef _DEBUG
	mDebugDrawer_ = new OgreDebugDrawer(OgreContext::getInstance()->getSceneManager());
	mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(mDebugDrawer_);
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

btRigidBody* PhysicsManager::createRB(Vector3 pos, float mass, int group, int mask)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	//btBoxShape shapeColl = btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

	//btDefaultMotionState motion = btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(transform), new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)));
	btRigidBody* rb = new btRigidBody(info);

	rb->forceActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(rb, group, mask);

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

void PhysicsManager::update(float deltaTime)
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	checkCollision();

	for (auto it = _compsList.begin(); it != _compsList.end(); ++it) {
		(*it)->update(deltaTime);
	}

#ifdef _DEBUG
	dynamicsWorld->debugDrawWorld();
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
		delete* i;
		_compsList.erase(i);
	}
}

bool PhysicsManager::destroyComponent(Entity* ent, int compId)
{
	auto i = _compsList.begin();
	while (i != _compsList.end()) {
		if (ent == (*i)->getEntity()) {
			destroyRigidBody(static_cast<RigidBody*>((*i))->getBtRb());
			delete* i;
			_compsList.erase(i);
			return true;
		}
		else {
			++i;
		}
	}

	return false;
}