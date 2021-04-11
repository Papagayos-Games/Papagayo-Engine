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

//este metodo sera el metodo virtual "destroyAllComponents" heredado de Manager
void PhysicsManager::destroyWorldContent()
{
    auto i = rbs.size() - 1;
    while (i != 0) {
        dynamicsWorld->removeCollisionObject(rbs[i]);

        delete rbs[i];
        rbs.pop_back();
        --i;
    }
    //si deja basura poner aqui abajo la eliminacion de los shapes y motionstates
}

void PhysicsManager::destroyRigidBody(btRigidBody* body)
{
    //busca en el vector de rigidbodies y lo destruye, tambien desde el mundo dinamico
    auto it = rbs.begin();
    bool erased = false;
    while (it != rbs.end() && !erased) {
        if (*it == body) {
            dynamicsWorld->removeCollisionObject(*it);
            delete* it;
            erased = true;
        }
        else
            ++it;
    }
    rbs.erase(it);
}

void PhysicsManager::updatePhys()
{
    dynamicsWorld->stepSimulation(1.f / 60.f, 10);
//#ifdef _DEBUG
//    dynamicsWorld->debugDrawWorld();
//#endif
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
    rbs.push_back(rb);
    /*shapes_.push_back(box);
    states_.push_back(motion);*/

    return rb;
}
