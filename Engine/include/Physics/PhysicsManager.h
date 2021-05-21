#pragma once

#ifndef _PHYSICS_PHYSICSMAN_H
#define _PHYSICS_PHYSICSMAN_H

#include <vector>
#include "Manager.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class OgreDebugDrawer;
class Vector3;


class PhysicsManager : public Manager
{
private:
	static PhysicsManager* instance_;

	//Configuracion sobre la gestion de colisiones con bullet, nosotros usaremos la configuracion por defecto
	btDefaultCollisionConfiguration* collConfig = nullptr;

	//Variable de bullet que hace de "pasador" de colisiones
	btCollisionDispatcher* collDispatcher = nullptr;

	//Variable de bullet que se usa para hacer calculos de manera eficiente para generar posibles colisiones
	btBroadphaseInterface* broadPhaseInterface = nullptr;

	//Variable de bullet que hace de solucionador de restricciones 
	btSequentialImpulseConstraintSolver* constraintSolver = nullptr;

	//Variable de bullet a la que se le pasa todas las variables anteriores como configuracion de la fisica
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	//estoy seria para dibujar los colliders en un modo debug, lo queremos?
	OgreDebugDrawer* mDebugDrawer_ = nullptr;

	//esto hay que ver si al eliminar el vector de rigidbodies deja basura y si es asi entonces es porque hay que eliminar
	//por partes el shape y el motionstate
	/*std::vector<btBoxShape*> shapes_;
	std::vector<btMotionState*> states_;*/

	PhysicsManager();
	virtual ~PhysicsManager();

	//TO ERASE
	bool applyTorque = true;

public:
	
	//nos devuelve la instancia
	static PhysicsManager* getInstance();
	static bool setUpInstance();

	//inicializa todas las variables fisicas asi como el "mundo" a partir de dichas variables
	void init(const Vector3 gravity);

	//destruye todas las variables relacionadas con la fisica
	void destroyWorld();

	//destruye un rigidbody en concreto
	void destroyRigidBody(btRigidBody* body);

	btDiscreteDynamicsWorld* getWorld() const;

	//Crea el componente Rigidbody a partir de los siguientes parametros:
	//Posicion, masa e identificador (el cual determina la forma del collider)
	btRigidBody* createRB(Vector3 pos, float mass, int group = -1, int mask = -1);

	virtual void addComponent(Entity* ent, int compId);
	virtual void start();
	virtual void update();
	
	static void clean();
	static void destroy();

	virtual void destroyAllComponents();
	virtual bool destroyComponent(Entity* ent, int compId);

	enum class PhysicsCmpId : int {
		RigigbodyId = 0,
		LastPhysicsCmpId
	};
};

#endif