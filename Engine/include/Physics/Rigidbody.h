#pragma once
#include "Component.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

class btCollisionShape;
class Vector3;
class Entity;

enum class Shapes
{
	BOX = 0, SPHERE = 1, TRIANGLE = 2
};

enum class Forces {
	NORMAL = 0,
	IMPULSE = 1
};

class Rigidbody : public Component
{
private:
	//Masa del Rigidbody
	btScalar mass = 1.0f;
	//Rigidbody principal
	btRigidBody* rb = nullptr;
	//gravedad que afecta al objeto
	const btVector3 GRAVITY = btVector3(0,-9.8,0); // TODO: ESTO VA A IR EN EL PHYSICS MANAGER
	//Transform fisico del rigidbody
	btTransform* tr = nullptr;

	btCollisionShape* shapeColl = nullptr;

	bool trigger = false;
	bool kinematic = false;
	bool static_ = false;
	bool collision = false;

public:
	Rigidbody(ecs::CmpId id);
	~Rigidbody() {};

	virtual void init();
	virtual void update() {};

#pragma region Setters
	//Activa/Desactiva la gravedad
	void setActiveGravtiy(const bool active);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como trigger,
	//si es false desactivara sus flags de colision para que este deje de ser un trigger.
	void setTrigger(bool trigger_);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como kinematic,
	//si es false desactivara sus flags de colision para que este deje de ser un kinematic.
	void setKinematic(bool kinematic_);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como static,
	//si es false desactivara sus flags de colision para que este deje de ser un static.
	void setStatic(bool _static);

	//metodo que setea el coeficiente de restitucion del rb
	//a mayor restitucion, mayor conservacion de la energia y,
	//a menor restitucion, menor conservacion de la energia.
	//Su valor oscila entre 0 y 1.
	void setRestitution(float restitution);

	//metodo que setea la velocidad lineal del rb
	void setLinearVelocity(Vector3 vel);

	//metodo que setea el rozamiento del rb
	void setFriction(float friction);

	//metodo que setea la posicion del rb
	void setPosition(Vector3 newPos);
#pragma endregion

#pragma region Getters
	//metodo que devuelve la velocidad lineal del rb
	Vector3 getLinearVelocity() const;

	//metodo que nos dice si el rigidbody es trigger o no
	bool isTrigger();

	//metodo que nos dice si el rigidbody es kinematic
	bool isKinematic();

	//metodo que nos dice si el rigidbody es estatico
	bool isStatic();
#pragma endregion

#pragma region Adders
	//Aplica fuerza al rigidbody de tipo Forces
	//a una posicion relativa del objeto, es decir,
	//la parte del cuerpo donde se aplica la fuerza
	void addForce(Vector3 force, Vector3 relativePos, Forces type = Forces::NORMAL);

	//Aplica una fuerza de giro al objeto de tipo Forces
	void addTorque(Vector3 torque, Forces type = Forces::NORMAL);
#pragma endregion

#pragma region Colisiones
	//metodo que comprueba 
	bool collidesWith(std::string id) const;

	Entity* collidesWithTag(std::string tag) const;
#pragma endregion
};

