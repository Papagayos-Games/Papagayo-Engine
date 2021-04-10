#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


PhysicsManager* PhysicsManager::instance = nullptr;

void PhysicsManager::init() { 
	instance = new PhysicsManager(); 
}

PhysicsManager* PhysicsManager::getInstance()
{
	return instance;
}

PhysicsManager::PhysicsManager() {};

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
    destroyWorldContent();

    delete dynamicsWorld; dynamicsWorld = nullptr;

    delete collConfig; collConfig = nullptr;

    delete collDispatcher; collDispatcher = nullptr;

    delete broadPhaseInterface; broadPhaseInterface = nullptr;

    delete constraintSolver; constraintSolver = nullptr;

    //delete mDebugDrawer_; mDebugDrawer_ = nullptr;

    delete instance; instance = nullptr;
}

void PhysicsManager::destroyWorldContent()
{
    //se destruirian los vectores que hay comentados
}

void PhysicsManager::destroyRigidBody(btRigidBody* body)
{
    //buscaria en el vector de rigidbodies y lo destruiria, tambien desde el mundo dinamico
}

void PhysicsManager::updatePhys()
{
    dynamicsWorld->stepSimulation(1.f / 60.f, 10);
#ifdef _DEBUG
    dynamicsWorld->debugDrawWorld();
#endif
}

btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
    return dynamicsWorld;
}

btRigidBody* PhysicsManager::createRB(Vector3 pos, Vector3 shape, float mass)
{
    return nullptr;
}
