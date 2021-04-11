#pragma once
#include <vector>
#include "Manager.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class Vector3;


class PhysicsManager : public Manager
{
private:
	static PhysicsManager* instance_;

	static bool setUpInstance();

	//Configuracion sobre la gestion de colisiones con bullet, nosotros usaremos la configuracion por defecto
	btDefaultCollisionConfiguration* collConfig;

	//Variable de bullet que hace de "pasador" de colisiones
	btCollisionDispatcher* collDispatcher;

	//Variable de bullet que se usa para hacer calculos de manera eficiente para generar posibles colisiones
	btBroadphaseInterface* broadPhaseInterface;

	//Variable de bullet que hace de solucionador de restricciones 
	btSequentialImpulseConstraintSolver* constraintSolver;

	//Variable de bullet a la que se le pasa todas las variables anteriores como configuracion de la fisica
	btDiscreteDynamicsWorld* dynamicsWorld;

	//estoy seria para dibujar los colliders en un modo debug, lo queremos?
	//OgreDebugDrawer* mDebugDrawer_ = nullptr;

	//esto hay que ver si al eliminar el vector de rigidbodies deja basura y si es asi entonces es porque hay que eliminar
	//por partes el shape y el motionstate
	/*std::vector<btBoxShape*> shapes_;
	std::vector<btMotionState*> states_;*/



	PhysicsManager();
	~PhysicsManager();

public:
	//nos devuelve la instancia
	static PhysicsManager* getInstance();

	//inicializa todas las variables fisicas asi como el "mundo" a partir de dichas variables
	void init(const Vector3 gravity);

	//destruye todas las variables relacionadas con la fisica
	void destroyWorld();

	//destruye un rigidbody en concreto
	void destroyRigidBody(btRigidBody* body);

	btDiscreteDynamicsWorld* getWorld() const;

	//hay que hablar esto
	btRigidBody* createRB(Vector3 pos, Vector3 shape, float mass);

	virtual void addComponent(Entity* ent, int compId);
	virtual void start();
	virtual void update();

	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);
};

